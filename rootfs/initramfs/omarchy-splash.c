#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define LOGO_PATH "/etc/omarchy-logo.pgm"
#define STOP_PATH "/run/omarchy-splash.stop"
#define FAIL_PATH "/run/omarchy-splash.failed"
#define FRAME_DELAY_NS 100000000L
#define FULL_REPAINT_FRAMES 10U
#define FAKE_PROGRESS_LIMIT 700U
#define FAKE_PROGRESS_FRAMES 150U

struct image {
  unsigned width;
  unsigned height;
  uint8_t *alpha;
};

struct framebuffer {
  int descriptor;
  size_t length;
  uint8_t *memory;
  struct fb_fix_screeninfo fixed;
  struct fb_var_screeninfo variable;
};

static volatile sig_atomic_t interrupted = 0;

static void handle_signal(int signal_number) {
  (void)signal_number;
  interrupted = 1;
}

static int read_token(FILE *stream, char *buffer, size_t size) {
  int character;
  size_t used = 0;

  do {
    character = fgetc(stream);
    if (character == '#') {
      do {
        character = fgetc(stream);
      } while (character != '\n' && character != EOF);
    }
  } while (character != EOF && character <= ' ');

  if (character == EOF) return -1;
  do {
    if (used + 1 >= size) return -1;
    buffer[used++] = (char)character;
    character = fgetc(stream);
  } while (character != EOF && character > ' ');
  buffer[used] = '\0';
  return 0;
}

static int load_logo(struct image *logo) {
  FILE *stream = fopen(LOGO_PATH, "rb");
  char token[32];
  if (stream == NULL) return -1;

  if (read_token(stream, token, sizeof(token)) != 0 || strcmp(token, "P5") != 0 ||
      read_token(stream, token, sizeof(token)) != 0) {
    fclose(stream);
    return -1;
  }
  logo->width = (unsigned)strtoul(token, NULL, 10);
  if (read_token(stream, token, sizeof(token)) != 0) {
    fclose(stream);
    return -1;
  }
  logo->height = (unsigned)strtoul(token, NULL, 10);
  if (read_token(stream, token, sizeof(token)) != 0 || strcmp(token, "255") != 0 ||
      logo->width == 0 || logo->height == 0 || logo->width > 4096 ||
      logo->height > 4096) {
    fclose(stream);
    return -1;
  }

  size_t length = (size_t)logo->width * logo->height;
  logo->alpha = malloc(length);
  if (logo->alpha == NULL || fread(logo->alpha, 1, length, stream) != length) {
    free(logo->alpha);
    logo->alpha = NULL;
    fclose(stream);
    return -1;
  }
  fclose(stream);
  return 0;
}

static uint32_t channel(unsigned value, const struct fb_bitfield *field) {
  if (field->length == 0) return 0;
  uint32_t maximum = (1U << field->length) - 1U;
  return ((value * maximum + 127U) / 255U) << field->offset;
}

static uint32_t pack_color(const struct fb_var_screeninfo *variable, unsigned red,
                           unsigned green, unsigned blue) {
  return channel(red, &variable->red) | channel(green, &variable->green) |
         channel(blue, &variable->blue);
}

static void close_framebuffer(struct framebuffer *framebuffer) {
  if (framebuffer->memory != MAP_FAILED && framebuffer->memory != NULL)
    munmap(framebuffer->memory, framebuffer->length);
  if (framebuffer->descriptor >= 0) close(framebuffer->descriptor);
  memset(framebuffer, 0, sizeof(*framebuffer));
  framebuffer->descriptor = -1;
  framebuffer->memory = MAP_FAILED;
}

static int open_framebuffer(struct framebuffer *framebuffer) {
  framebuffer->descriptor = open("/dev/fb0", O_RDWR | O_CLOEXEC);
  if (framebuffer->descriptor < 0) return -1;
  if (ioctl(framebuffer->descriptor, FBIOGET_FSCREENINFO, &framebuffer->fixed) != 0 ||
      ioctl(framebuffer->descriptor, FBIOGET_VSCREENINFO, &framebuffer->variable) != 0 ||
      framebuffer->variable.bits_per_pixel != 32 || framebuffer->fixed.line_length == 0 ||
      framebuffer->fixed.smem_len == 0) {
    close_framebuffer(framebuffer);
    return -1;
  }

  framebuffer->length = framebuffer->fixed.smem_len;
  framebuffer->memory = mmap(NULL, framebuffer->length, PROT_READ | PROT_WRITE,
                             MAP_SHARED, framebuffer->descriptor, 0);
  if (framebuffer->memory == MAP_FAILED) {
    close_framebuffer(framebuffer);
    return -1;
  }
  return 0;
}

static void pixel(struct framebuffer *framebuffer, unsigned x, unsigned y,
                  uint32_t color) {
  const struct fb_var_screeninfo *variable = &framebuffer->variable;
  if (x >= variable->xres || y >= variable->yres) return;
  size_t offset = (size_t)(y + variable->yoffset) * framebuffer->fixed.line_length +
                  (size_t)(x + variable->xoffset) * 4U;
  if (offset + sizeof(color) > framebuffer->length) return;
  memcpy(framebuffer->memory + offset, &color, sizeof(color));
}

static void rectangle(struct framebuffer *framebuffer, unsigned x, unsigned y,
                      unsigned width, unsigned height, uint32_t color) {
  unsigned end_y = y + height;
  unsigned end_x = x + width;
  if (end_y > framebuffer->variable.yres) end_y = framebuffer->variable.yres;
  if (end_x > framebuffer->variable.xres) end_x = framebuffer->variable.xres;
  for (unsigned row = y; row < end_y; ++row)
    for (unsigned column = x; column < end_x; ++column)
      pixel(framebuffer, column, row, color);
}

static void draw_logo(struct framebuffer *framebuffer, const struct image *logo,
                      unsigned foreground_red, unsigned foreground_green,
                      unsigned foreground_blue, unsigned background_red,
                      unsigned background_green, unsigned background_blue) {
  unsigned scale = 1;
  while ((logo->width * (scale + 1U)) <= framebuffer->variable.xres * 4U / 5U &&
         (logo->height * (scale + 1U)) <= framebuffer->variable.yres / 3U)
    ++scale;
  unsigned width = logo->width * scale;
  unsigned height = logo->height * scale;
  unsigned origin_x = (framebuffer->variable.xres - width) / 2U;
  unsigned origin_y = (framebuffer->variable.yres - height) / 2U -
                      framebuffer->variable.yres / 24U;

  for (unsigned source_y = 0; source_y < logo->height; ++source_y) {
    for (unsigned source_x = 0; source_x < logo->width; ++source_x) {
      unsigned alpha = logo->alpha[(size_t)source_y * logo->width + source_x];
      if (alpha == 0) continue;
      unsigned red = (foreground_red * alpha + background_red * (255U - alpha)) / 255U;
      unsigned green =
          (foreground_green * alpha + background_green * (255U - alpha)) / 255U;
      unsigned blue =
          (foreground_blue * alpha + background_blue * (255U - alpha)) / 255U;
      uint32_t color = pack_color(&framebuffer->variable, red, green, blue);
      rectangle(framebuffer, origin_x + source_x * scale,
                origin_y + source_y * scale, scale, scale, color);
    }
  }
}

static void draw_frame(struct framebuffer *framebuffer, const struct image *logo,
                       unsigned progress, int failed) {
  uint32_t background = pack_color(&framebuffer->variable, 26, 27, 38);
  uint32_t track = pack_color(&framebuffer->variable, 52, 56, 79);
  uint32_t foreground = failed ?
                            pack_color(&framebuffer->variable, 247, 118, 142) :
                            pack_color(&framebuffer->variable, 168, 205, 118);
  rectangle(framebuffer, 0, 0, framebuffer->variable.xres,
            framebuffer->variable.yres, background);
  draw_logo(framebuffer, logo, 168U, 205U, 118U, 26U, 27U, 38U);

  unsigned bar_width = framebuffer->variable.xres < 800 ?
                           framebuffer->variable.xres / 3U : 300U;
  unsigned bar_height = framebuffer->variable.yres < 720 ? 4U : 6U;
  unsigned bar_x = (framebuffer->variable.xres - bar_width) / 2U;
  unsigned bar_y = framebuffer->variable.yres * 3U / 4U;
  rectangle(framebuffer, bar_x, bar_y, bar_width, bar_height, track);
  rectangle(framebuffer, bar_x, bar_y, bar_width * progress / 1000U,
            bar_height, foreground);
}

static int stop_requested(void) {
  struct stat status;
  return interrupted || stat(STOP_PATH, &status) == 0;
}

static int failure_requested(void) {
  struct stat status;
  return stat(FAIL_PATH, &status) == 0;
}

int main(void) {
  struct image logo = {0};
  struct framebuffer framebuffer = {.descriptor = -1, .memory = MAP_FAILED};
  const struct timespec delay = {.tv_sec = 0, .tv_nsec = FRAME_DELAY_NS};
  unsigned frame = 0;

  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);
  if (load_logo(&logo) != 0) return 1;

  while (!stop_requested()) {
    if (framebuffer.descriptor < 0 && open_framebuffer(&framebuffer) != 0) {
      nanosleep(&delay, NULL);
      continue;
    }

    unsigned progress_frame = frame > FAKE_PROGRESS_FRAMES ? FAKE_PROGRESS_FRAMES : frame;
    unsigned inverse = FAKE_PROGRESS_FRAMES - progress_frame;
    unsigned progress = FAKE_PROGRESS_LIMIT *
                        (FAKE_PROGRESS_FRAMES * FAKE_PROGRESS_FRAMES - inverse * inverse) /
                        (FAKE_PROGRESS_FRAMES * FAKE_PROGRESS_FRAMES);
    if (frame % FULL_REPAINT_FRAMES == 0)
      draw_frame(&framebuffer, &logo, progress, 0);
    else {
      uint32_t foreground = pack_color(&framebuffer.variable, 168, 205, 118);
      unsigned bar_width = framebuffer.variable.xres < 800 ?
                               framebuffer.variable.xres / 3U : 300U;
      unsigned bar_height = framebuffer.variable.yres < 720 ? 4U : 6U;
      rectangle(&framebuffer, (framebuffer.variable.xres - bar_width) / 2U,
                framebuffer.variable.yres * 3U / 4U,
                bar_width * progress / 1000U, bar_height, foreground);
    }
    msync(framebuffer.memory, framebuffer.length, MS_ASYNC);
    ++frame;
    nanosleep(&delay, NULL);
  }

  if (framebuffer.descriptor >= 0) {
    draw_frame(&framebuffer, &logo, 1000U, failure_requested());
    msync(framebuffer.memory, framebuffer.length, MS_SYNC);
  }
  close_framebuffer(&framebuffer);
  free(logo.alpha);
  return 0;
}
