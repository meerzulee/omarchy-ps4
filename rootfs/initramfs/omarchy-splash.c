#include <errno.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>

static uint32_t pack_color(const struct fb_var_screeninfo *v, uint8_t r,
                           uint8_t g, uint8_t b) {
  uint32_t color = 0;
  color |= ((uint32_t)(r >> (8 - v->red.length))) << v->red.offset;
  color |= ((uint32_t)(g >> (8 - v->green.length))) << v->green.offset;
  color |= ((uint32_t)(b >> (8 - v->blue.length))) << v->blue.offset;
  return color;
}
static void pixel(uint8_t *memory, const struct fb_fix_screeninfo *f,
                  const struct fb_var_screeninfo *v, unsigned x, unsigned y,
                  uint32_t color) {
  if (x >= v->xres || y >= v->yres) return;
  uint32_t *target = (uint32_t *)(memory + (y + v->yoffset) * f->line_length +
                                 (x + v->xoffset) * 4);
  *target = color;
}

static void rectangle(uint8_t *memory, const struct fb_fix_screeninfo *f,
                      const struct fb_var_screeninfo *v, unsigned x,
                      unsigned y, unsigned width, unsigned height,
                      uint32_t color) {
  for (unsigned row = y; row < y + height && row < v->yres; ++row)
    for (unsigned column = x; column < x + width && column < v->xres; ++column)
      pixel(memory, f, v, column, row, color);
}

static void mark(uint8_t *memory, const struct fb_fix_screeninfo *f,
                 const struct fb_var_screeninfo *v, unsigned center_x,
                 unsigned center_y, unsigned size, uint32_t green,
                 uint32_t cyan, uint32_t purple) {
  for (unsigned y = 0; y < size; ++y) {
    unsigned width = (y * 2) / 3;
    unsigned left = center_x - width / 2;
    uint32_t color = y < size / 3 ? green : (y < (size * 2) / 3 ? cyan : purple);
    for (unsigned x = 0; x < width; ++x)
      if ((x + y / 5) % 17 > 2) pixel(memory, f, v, left + x, center_y - size / 2 + y, color);
  }
}

int main(void) {
  int descriptor = -1;
  const struct timespec delay = {.tv_sec = 0, .tv_nsec = 100000000};
  for (unsigned attempt = 0; attempt < 300; ++attempt) {
    descriptor = open("/dev/fb0", O_RDWR);
    if (descriptor >= 0) break;
    nanosleep(&delay, NULL);
  }
  if (descriptor < 0) return 1;

  struct fb_fix_screeninfo fixed;
  struct fb_var_screeninfo variable;
  if (ioctl(descriptor, FBIOGET_FSCREENINFO, &fixed) != 0 ||
      ioctl(descriptor, FBIOGET_VSCREENINFO, &variable) != 0 ||
      variable.bits_per_pixel != 32) {
    close(descriptor);
    return 2;
  }

  size_t length = fixed.smem_len;
  uint8_t *memory = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED,
                         descriptor, 0);
  if (memory == MAP_FAILED) {
    close(descriptor);
    return 3;
  }

  uint32_t background = pack_color(&variable, 21, 22, 30);
  uint32_t line = pack_color(&variable, 52, 56, 79);
  uint32_t green = pack_color(&variable, 158, 206, 106);
  uint32_t cyan = pack_color(&variable, 125, 207, 255);
  uint32_t purple = pack_color(&variable, 187, 154, 247);

  rectangle(memory, &fixed, &variable, 0, 0, variable.xres, variable.yres,
            background);
  unsigned size = variable.yres / 3;
  mark(memory, &fixed, &variable, variable.xres / 2, variable.yres / 2 - 20,
       size, green, cyan, purple);
  unsigned bar_width = variable.xres / 5;
  rectangle(memory, &fixed, &variable, (variable.xres - bar_width) / 2,
            variable.yres * 3 / 4, bar_width, 4, line);
  rectangle(memory, &fixed, &variable, (variable.xres - bar_width) / 2,
            variable.yres * 3 / 4, bar_width / 3, 4, green);

  msync(memory, length, MS_SYNC);
  munmap(memory, length);
  close(descriptor);
  return 0;
}
