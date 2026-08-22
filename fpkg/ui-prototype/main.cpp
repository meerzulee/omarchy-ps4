#define _POSIX_C_SOURCE 200809L
#define STBI_ASSERT(x)
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <proto-include.h>
#include <orbis/Pad.h>
#include <orbis/SaveData.h>
#include <orbis/Sysmodule.h>
#include <orbis/UserService.h>
#include <orbis/VideoOut.h>
#include <orbis/libkernel.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "private_boot.hpp"

namespace {

constexpr int kWidth = 1920;
constexpr int kHeight = 1080;
constexpr int kDepth = 4;
constexpr size_t kDirectAlignment = 0x200000;
#ifdef OMARCHY_PRIVATE_BOOT
constexpr bool kPrivateBoot = true;
#else
constexpr bool kPrivateBoot = false;
#endif
#ifdef OMARCHY_INTERNAL_BOOT
constexpr bool kInternalBoot = true;
#else
constexpr bool kInternalBoot = false;
#endif

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct Theme {
  const char* id;
  const char* name;
  const char* const* wallpapers;
  int wallpaper_count;
  Color darker;
  Color dark;
  Color background;
  Color panel;
  Color selection;
  Color foreground;
  Color bright;
  Color accent;
  Color success;
  Color warning;
  Color error;
};

constexpr const char* kTokyoWallpapers[] = {
    "/app0/assets/images/tokyo-night-0-winding-road.jpg",
    "/app0/assets/images/tokyo-night-2-swirl-buck.jpg",
    "/app0/assets/images/tokyo-night-4-omakub.jpg",
};
constexpr const char* kLastHorizonWallpapers[] = {
    "/app0/assets/images/last-horizon-1-eyes-wide.jpg",
    "/app0/assets/images/last-horizon-2-blink.jpg",
    "/app0/assets/images/last-horizon-3-bokeh.jpg",
    "/app0/assets/images/last-horizon-4-new-horizons.jpg",
};
constexpr const char* kLupineWallpapers[] = {
    "/app0/assets/images/lupine-01-cherry-blossom-bokeh.jpg",
    "/app0/assets/images/lupine-02-cherry-blossom-white.jpg",
    "/app0/assets/images/lupine-03-pastel-clouds.jpg",
    "/app0/assets/images/lupine-04-elegant-blue-wave.jpg",
    "/app0/assets/images/lupine-05-abstract-wave.jpg",
};
constexpr const char* kSolitudeWallpapers[] = {
    "/app0/assets/images/solitude-1-on-pole.jpg",
    "/app0/assets/images/solitude-2-wreakage.jpg",
    "/app0/assets/images/solitude-3-climb.jpg",
    "/app0/assets/images/solitude-4-ether.jpg",
    "/app0/assets/images/solitude-5-eyed.jpg",
};

constexpr Theme kThemes[] = {
    {"tokyo-night", "Tokyo Night", kTokyoWallpapers, 3,
     {0x0e, 0x0e, 0x14}, {0x13, 0x14, 0x1c}, {0x1a, 0x1b, 0x26},
     {0x24, 0x28, 0x3b}, {0x29, 0x2e, 0x42}, {0xa9, 0xb1, 0xd6},
     {0xc0, 0xca, 0xf5}, {0x7a, 0xa2, 0xf7}, {0x9e, 0xce, 0x6a},
     {0xe0, 0xaf, 0x68}, {0xf7, 0x76, 0x8e}},
    {"last-horizon", "Last Horizon", kLastHorizonWallpapers, 4,
     {0x06, 0x06, 0x06}, {0x09, 0x08, 0x09}, {0x0c, 0x0b, 0x0c},
     {0x0c, 0x0b, 0x0c}, {0x58, 0x4e, 0x51}, {0xfa, 0xfc, 0xfb},
     {0xe2, 0xdd, 0xdc}, {0xb5, 0x97, 0x90}, {0x87, 0xa9, 0xb0},
     {0x6b, 0x5e, 0x73}, {0xc3, 0x8b, 0x7b}},
    {"lupine", "Lupine", kLupineWallpapers, 5,
     {0xde, 0xde, 0xde}, {0xec, 0xec, 0xec}, {0xfa, 0xfa, 0xfa},
     {0xf5, 0xf5, 0xf5}, {0xd0, 0xd0, 0xd0}, {0x21, 0x21, 0x21},
     {0x00, 0x00, 0x00}, {0x32, 0x64, 0xeb}, {0x4a, 0x2f, 0xd0},
     {0x02, 0x6f, 0xde}, {0xc9, 0x00, 0xc4}},
    {"solitude", "Solitude", kSolitudeWallpapers, 5,
     {0x08, 0x0a, 0x0b}, {0x0c, 0x0e, 0x10}, {0x10, 0x13, 0x15},
     {0x10, 0x13, 0x15}, {0x34, 0x3d, 0x41}, {0xca, 0xcc, 0xcc},
     {0xa5, 0xae, 0xb4}, {0x79, 0x81, 0x86}, {0x9f, 0xa5, 0xa9},
     {0xd9, 0xdb, 0xdc}, {0x56, 0x5d, 0x60}},
};
constexpr int kThemeCount = sizeof(kThemes) / sizeof(kThemes[0]);
constexpr const char* kSettingsDirName = "Settings";
constexpr const char* kSettingsPathPattern =
    "/mnt/sandbox/OMCH42069_000%s/settings.txt";
constexpr const char* kSettingsTempPathPattern =
    "/mnt/sandbox/OMCH42069_000%s/settings.tmp";

Color kDarker = kThemes[0].darker;
Color kDark = kThemes[0].dark;
Color kBackground = kThemes[0].background;
Color kPanel = kThemes[0].panel;
Color kSelection = kThemes[0].selection;
Color kForeground = kThemes[0].foreground;
Color kBright = kThemes[0].bright;
Color kBlue = kThemes[0].accent;
Color kGreen = kThemes[0].success;
Color kWarning = kThemes[0].warning;
Color kError = kThemes[0].error;

void apply_theme(int index) {
  if (index < 0 || index >= kThemeCount) index = 0;
  const Theme& theme = kThemes[index];
  kDarker = theme.darker;
  kDark = theme.dark;
  kBackground = theme.background;
  kPanel = theme.panel;
  kSelection = theme.selection;
  kForeground = theme.foreground;
  kBright = theme.bright;
  kBlue = theme.accent;
  kGreen = theme.success;
  kWarning = theme.warning;
  kError = theme.error;
}

class Framebuffer {
 public:
  bool init() {
    video_ = sceVideoOutOpen(ORBIS_VIDEO_USER_MAIN, ORBIS_VIDEO_OUT_BUS_MAIN, 0, 0);
    if (video_ < 0) return false;

    if (sceKernelCreateEqueue(&flip_queue_, "omarchy-ui-flip") < 0) return false;
    if (sceVideoOutAddFlipEvent(flip_queue_, video_, nullptr) < 0) return false;

    const size_t frame_size = static_cast<size_t>(kWidth) * kHeight * kDepth;
    const size_t requested = frame_size * 2;
    direct_size_ = (requested + kDirectAlignment - 1) / kDirectAlignment * kDirectAlignment;

    if (sceKernelAllocateDirectMemory(0, sceKernelGetDirectMemorySize(), direct_size_,
                                      kDirectAlignment, 3, &direct_offset_) < 0) {
      return false;
    }
    if (sceKernelMapDirectMemory(&direct_memory_, direct_size_, 0x33, 0,
                                 direct_offset_, kDirectAlignment) < 0) {
      return false;
    }

    buffers_[0] = static_cast<uint32_t*>(direct_memory_);
    buffers_[1] = reinterpret_cast<uint32_t*>(
        reinterpret_cast<uint8_t*>(direct_memory_) + frame_size);

    OrbisVideoOutBufferAttribute attribute;
    sceVideoOutSetBufferAttribute(&attribute, 0x80000000, 1, 0,
                                  kWidth, kHeight, kWidth);
    if (sceVideoOutRegisterBuffers(video_, 0,
                                   reinterpret_cast<void**>(buffers_), 2,
                                   &attribute) < 0) {
      return false;
    }
    sceVideoOutSetFlipRate(video_, 0);
    return true;
  }

  void pixel(int x, int y, Color color, uint8_t alpha = 255) {
    if (x < 0 || y < 0 || x >= kWidth || y >= kHeight) return;
    uint32_t* target = &buffers_[active_][y * kWidth + x];
    if (alpha == 255) {
      *target = pack(color);
      return;
    }
    const uint32_t previous = *target;
    const uint8_t old_r = (previous >> 16) & 0xff;
    const uint8_t old_g = (previous >> 8) & 0xff;
    const uint8_t old_b = previous & 0xff;
    const uint16_t inverse = 255 - alpha;
    Color mixed = {
        static_cast<uint8_t>((color.r * alpha + old_r * inverse) / 255),
        static_cast<uint8_t>((color.g * alpha + old_g * inverse) / 255),
        static_cast<uint8_t>((color.b * alpha + old_b * inverse) / 255),
    };
    *target = pack(mixed);
  }

  void rectangle(int x, int y, int width, int height, Color color) {
    int x0 = x < 0 ? 0 : x;
    int y0 = y < 0 ? 0 : y;
    int x1 = x + width > kWidth ? kWidth : x + width;
    int y1 = y + height > kHeight ? kHeight : y + height;
    const uint32_t encoded = pack(color);
    for (int py = y0; py < y1; ++py) {
      uint32_t* row = buffers_[active_] + py * kWidth;
      for (int px = x0; px < x1; ++px) row[px] = encoded;
    }
  }

  void border(int x, int y, int width, int height, int thickness, Color color) {
    rectangle(x, y, width, thickness, color);
    rectangle(x, y + height - thickness, width, thickness, color);
    rectangle(x, y, thickness, height, color);
    rectangle(x + width - thickness, y, thickness, height, color);
  }

  void present(int frame_id) {
    sceVideoOutSubmitFlip(video_, active_, ORBIS_VIDEO_OUT_FLIP_VSYNC, frame_id);
    for (;;) {
      OrbisVideoOutFlipStatus status;
      sceVideoOutGetFlipStatus(video_, &status);
      if (status.flipArg == frame_id) break;
      OrbisKernelEvent event;
      int count = 0;
      if (sceKernelWaitEqueue(flip_queue_, &event, 1, &count, nullptr) != 0) break;
    }
    active_ = (active_ + 1) % 2;
  }

 private:
  static uint32_t pack(Color color) {
    return 0x80000000u | (static_cast<uint32_t>(color.r) << 16) |
           (static_cast<uint32_t>(color.g) << 8) | color.b;
  }

  int video_ = -1;
  int active_ = 0;
  off_t direct_offset_ = 0;
  size_t direct_size_ = 0;
  void* direct_memory_ = nullptr;
  uint32_t* buffers_[2] = {nullptr, nullptr};
  OrbisKernelEqueue flip_queue_ = 0;
};

class Image {
 public:
  Image() = default;

  explicit Image(const char* path) { load(path); }

  bool load(const char* path) {
    if (pixels_) stbi_image_free(pixels_);
    pixels_ = nullptr;
    width_ = 0;
    height_ = 0;
    channels_ = 0;
    pixels_ = reinterpret_cast<uint32_t*>(
        stbi_load(path, &width_, &height_, &channels_, STBI_rgb_alpha));
    return pixels_ != nullptr;
  }

  ~Image() {
    if (pixels_) stbi_image_free(pixels_);
  }

  bool valid() const { return pixels_ != nullptr; }

  void draw(Framebuffer& framebuffer, int start_x, int start_y) const {
    if (!pixels_) return;
    for (int y = 0; y < height_; ++y) {
      for (int x = 0; x < width_; ++x) {
        const uint32_t value = pixels_[y * width_ + x];
        const Color color = {
            static_cast<uint8_t>(value & 0xff),
            static_cast<uint8_t>((value >> 8) & 0xff),
            static_cast<uint8_t>((value >> 16) & 0xff),
        };
        framebuffer.pixel(start_x + x, start_y + y, color,
                          static_cast<uint8_t>((value >> 24) & 0xff));
      }
    }
  }

  void draw_tinted(Framebuffer& framebuffer, int start_x, int start_y,
                   Color tint) const {
    if (!pixels_) return;
    for (int y = 0; y < height_; ++y) {
      for (int x = 0; x < width_; ++x) {
        const uint32_t value = pixels_[y * width_ + x];
        framebuffer.pixel(start_x + x, start_y + y, tint,
                          static_cast<uint8_t>((value >> 24) & 0xff));
      }
    }
  }

 private:
  int width_ = 0;
  int height_ = 0;
  int channels_ = 0;
  uint32_t* pixels_ = nullptr;
};

struct Fonts {
  FT_Library library = nullptr;
  FT_Face label = nullptr;
  FT_Face small = nullptr;
  FT_Face body = nullptr;
  FT_Face action = nullptr;
  FT_Face title = nullptr;
  FT_Face heading = nullptr;

  bool init() {
    if (sceSysmoduleLoadModule(ORBIS_SYSMODULE_FREETYPE_OL) < 0) return false;
    if (FT_Init_FreeType(&library) != 0) return false;

    bool ok = true;
    ok &= load(&label, 17, false);
    ok &= load(&small, 21, false);
    ok &= load(&body, 27, false);
    ok &= load(&action, 26, true);
    ok &= load(&title, 44, true);
    ok &= load(&heading, 66, true);
    return ok;
  }

 private:
  bool load(FT_Face* face, int size, bool bold) {
    const char* system_font = bold
        ? "/preinst/common/font/SST-Bold.otf"
        : "/preinst/common/font/SST-Roman.otf";
    if (FT_New_Face(library, system_font, 0, face) != 0) {
      if (FT_New_Face(library, "/app0/assets/fonts/Gontserrat-Regular.ttf", 0,
                      face) != 0) {
        return false;
      }
    }
    return FT_Set_Pixel_Sizes(*face, 0, size) == 0;
  }
};

void text(Framebuffer& framebuffer, FT_Face face, int start_x, int baseline,
          const char* value, Color color) {
  int pen_x = start_x;
  int pen_y = baseline;
  for (const unsigned char* cursor =
           reinterpret_cast<const unsigned char*>(value);
       *cursor; ++cursor) {
    if (*cursor == '\n') {
      pen_x = start_x;
      pen_y += face->size->metrics.height >> 6;
      continue;
    }
    if (FT_Load_Char(face, *cursor, FT_LOAD_RENDER) != 0) continue;
    FT_GlyphSlot glyph = face->glyph;
    for (int y = 0; y < glyph->bitmap.rows; ++y) {
      for (int x = 0; x < glyph->bitmap.width; ++x) {
        const uint8_t coverage =
            glyph->bitmap.buffer[y * glyph->bitmap.pitch + x];
        if (!coverage) continue;
        framebuffer.pixel(pen_x + glyph->bitmap_left + x,
                          pen_y - glyph->bitmap_top + y, color, coverage);
      }
    }
    pen_x += glyph->advance.x >> 6;
  }
}

int text_width(FT_Face face, const char* value) {
  int width = 0;
  for (const unsigned char* cursor =
           reinterpret_cast<const unsigned char*>(value);
       *cursor; ++cursor) {
    if (*cursor == '\n') break;
    if (FT_Load_Char(face, *cursor, FT_LOAD_DEFAULT) != 0) continue;
    width += face->glyph->advance.x >> 6;
  }
  return width;
}

void text_right(Framebuffer& framebuffer, FT_Face face, int right,
                int baseline, const char* value, Color color) {
  text(framebuffer, face, right - text_width(face, value), baseline, value,
       color);
}

enum class Screen {
  Home,
  Settings,
  InstallReview,
  Progress,
  Ready,
  KernelSelect,
  BootReview,
  Booting,
  BootError,
  Complete,
  Recovery,
  RecoveryNotice,
  Credits,
};

struct App {
  Screen screen = Screen::Home;
  int focus = 0;
  int dirty_frames = 2;
  int progress_phase = -1;
  int recovery_notice = 0;
  int theme_index = 0;
  int settings_original_theme = 0;
  int wallpaper_index = -1;
  int settings_original_wallpaper = -1;
  bool settings_saved = false;
  bool settings_save_failed = false;
  bool settings_original_saved = false;
  bool boot_set_ready = false;
  bool boot_update_available = false;
  bool boot_check_blocked = false;
  bool boot_stage_pending = false;
  bool boot_error_from_stage = false;
  bool boot_send_pending = false;
  const char* boot_message = nullptr;
  uint64_t progress_started = 0;
};

const char* screen_name(Screen screen) {
  switch (screen) {
    case Screen::Home: return "home";
    case Screen::Settings: return "appearance";
    case Screen::InstallReview: return "install-review";
    case Screen::Progress: return "install-progress";
    case Screen::Ready: return "boot-files-ready";
    case Screen::KernelSelect: return "kernel-select";
    case Screen::BootReview: return "launch-review";
    case Screen::Booting: return "launching";
    case Screen::BootError: return "launch-error";
    case Screen::Complete: return "complete";
    case Screen::Recovery: return "recovery";
    case Screen::RecoveryNotice: return "recovery-notice";
    case Screen::Credits: return "credits";
  }
  return "unknown";
}

void refresh_system_check(App& app) {
#ifdef OMARCHY_INTERNAL_BOOT
  const omarchy_ps4::InternalBootState state =
      omarchy_ps4::inspect_internal_boot_set();
  app.boot_set_ready = state == omarchy_ps4::InternalBootState::Ready;
  app.boot_update_available =
      state == omarchy_ps4::InternalBootState::UpdateAvailable;
  app.boot_check_blocked =
      state == omarchy_ps4::InternalBootState::Interrupted ||
      state == omarchy_ps4::InternalBootState::Blocked;
  printf("[omarchy-ui] system-check boot-files=%s kernel=linux-6.18.44-baikal "
         "usb=deferred-to-linux handoff=checked-at-launch\n",
         omarchy_ps4::internal_boot_state_name(state));
#else
  app.boot_set_ready = false;
  app.boot_update_available = false;
  app.boot_check_blocked = false;
  printf("[omarchy-ui] system-check boot-files=simulation kernel=none "
         "usb=not-checked handoff=not-checked\n");
#endif
}

bool mount_preferences(int user_id, uint32_t mode,
                       OrbisSaveDataMountResult* result) {
  OrbisSaveDataMount2 mount;
  OrbisSaveDataDirName directory;
  memset(&mount, 0, sizeof(mount));
  memset(&directory, 0, sizeof(directory));
  memset(result, 0, sizeof(*result));
  snprintf(directory.data, sizeof(directory.data), "%s", kSettingsDirName);
  mount.userId = user_id;
  mount.dirName = &directory;
  mount.blocks = ORBIS_SAVE_DATA_BLOCKS_MIN2;
  mount.mountMode = mode;
  return sceSaveDataMount2(&mount, result) >= 0;
}

void unmount_preferences(const OrbisSaveDataMountResult& result) {
  OrbisSaveDataMountPoint point;
  memset(&point, 0, sizeof(point));
  snprintf(point.data, sizeof(point.data), "%s", result.mountPathName);
  sceSaveDataUmount(&point);
}

int theme_index_for_id(const char* id) {
  for (int index = 0; index < kThemeCount; ++index) {
    if (strcmp(kThemes[index].id, id) == 0) return index;
  }
  return -1;
}

void load_preferences(App& app, int user_id, bool save_data_ready) {
  if (!save_data_ready || user_id < 0) return;
  OrbisSaveDataMountResult result;
  if (!mount_preferences(user_id, ORBIS_SAVE_DATA_MOUNT_MODE_RDONLY, &result)) {
    return;
  }
  char path[160];
  snprintf(path, sizeof(path), kSettingsPathPattern, result.mountPathName);
  FILE* stream = fopen(path, "r");
  if (stream) {
    int version = 0;
    char theme_id[32] = {};
    const int fields = fscanf(stream, "version=%d\ntheme=%31s", &version, theme_id);
    fclose(stream);
    const int theme = theme_index_for_id(theme_id);
    if (fields == 2 && version == 1 && theme >= 0) {
      app.theme_index = theme;
      app.settings_saved = true;
    }
  }
  unmount_preferences(result);
}

bool save_preferences(const App& app, int user_id, bool save_data_ready) {
  if (!save_data_ready || user_id < 0) return false;
  OrbisSaveDataMountResult result;
  const uint32_t mode = ORBIS_SAVE_DATA_MOUNT_MODE_CREATE2 |
                        ORBIS_SAVE_DATA_MOUNT_MODE_RDWR |
                        ORBIS_SAVE_DATA_MOUNT_MODE_COPY_ICON;
  if (!mount_preferences(user_id, mode, &result)) return false;

  char path[160];
  char temporary[160];
  snprintf(path, sizeof(path), kSettingsPathPattern, result.mountPathName);
  snprintf(temporary, sizeof(temporary), kSettingsTempPathPattern,
           result.mountPathName);
  FILE* stream = fopen(temporary, "w");
  if (!stream) {
    unmount_preferences(result);
    return false;
  }
  const int written = fprintf(stream, "version=1\ntheme=%s\n",
                              kThemes[app.theme_index].id);
  const bool flushed = fflush(stream) == 0 && fsync(fileno(stream)) == 0;
  const bool closed = fclose(stream) == 0;
  bool saved = written > 0 && flushed && closed;
  if (saved) saved = rename(temporary, path) == 0;
  if (!saved) remove(temporary);
  unmount_preferences(result);
  return saved;
}

int next_wallpaper_index(const App& app) {
  const int count = kThemes[app.theme_index].wallpaper_count;
  if (count <= 1) return 0;
  const uint64_t seed = sceKernelGetProcessTime() ^
      (static_cast<uint64_t>(app.theme_index + 1) << 33) ^
      static_cast<uint64_t>(app.wallpaper_index + 17);
  int next = static_cast<int>((seed ^ (seed >> 17) ^ (seed << 9)) % count);
  if (next == app.wallpaper_index) next = (next + 1) % count;
  return next;
}

bool shuffle_wallpaper(App& app, Image& background) {
  const int candidate = next_wallpaper_index(app);
  if (!background.load(kThemes[app.theme_index].wallpapers[candidate])) return false;
  app.wallpaper_index = candidate;
  app.dirty_frames = 2;
  return true;
}

bool load_default_wallpaper(App& app, Image& background) {
  if (kThemes[app.theme_index].wallpaper_count < 1 ||
      !background.load(kThemes[app.theme_index].wallpapers[0])) {
    return false;
  }
  app.wallpaper_index = 0;
  app.dirty_frames = 2;
  return true;
}

bool select_theme(App& app, Image& background, int theme_index) {
  if (theme_index < 0 || theme_index >= kThemeCount) return false;
  app.theme_index = theme_index;
  app.wallpaper_index = -1;
  app.settings_saved = false;
  app.settings_save_failed = false;
  apply_theme(theme_index);
  return load_default_wallpaper(app, background);
}

void draw_header(Framebuffer& framebuffer, Fonts& fonts, const Image& logo) {
  logo.draw_tinted(framebuffer, 96, 52, kGreen);
  text(framebuffer, fonts.label, 1552, 74,
       kInternalBoot ? "KERNEL MANAGER" : kPrivateBoot ? "LINUX LAUNCHER" : "UI PROTOTYPE",
       kForeground);
  text(framebuffer, fonts.small, 1552, 110, "OMARCHY 4.0.0", kBright);
}

void button(Framebuffer& framebuffer, Fonts& fonts, int x, int y, int width,
            const char* label, bool selected, bool primary = false) {
  const Color fill = selected ? (primary ? kBlue : kSelection) : kPanel;
  const Color label_color = selected && primary ? kDark : kBright;
  framebuffer.rectangle(x, y, width, 76, fill);
  framebuffer.border(x, y, width, 76, selected ? 3 : 1,
                     selected ? kBlue : kSelection);
  text(framebuffer, fonts.action, x + 28, y + 48, label, label_color);
  if (selected) {
    framebuffer.rectangle(x, y, 7, 76, primary ? kBright : kBlue);
  }
}

void flow_button(Framebuffer& framebuffer, Fonts& fonts, int x, int y,
                 int width, const char* label, bool selected,
                 bool primary = false, bool enabled = true) {
  const Color fill = !enabled ? kDarker
      : selected ? (primary ? kBlue : kSelection) : kDark;
  const Color label_color = !enabled ? kForeground
      : selected && primary ? kDarker : kBright;
  const Color accent_color = !enabled ? kForeground
      : selected && primary ? kDarker : kBlue;
  framebuffer.rectangle(x, y, width, 68, fill);
  framebuffer.border(x, y, width, 68, selected ? 3 : 1,
                     !enabled ? kDark : selected ? kBlue : kSelection);
  framebuffer.rectangle(x, y, selected ? 6 : 3, 68,
                        enabled ? kBlue : kSelection);
  text(framebuffer, fonts.small, x + 26, y + 44, label, label_color);
  if (enabled) {
    text(framebuffer, fonts.small, x + width - 39, y + 44, ">", accent_color);
  }
}

void fact_row(Framebuffer& framebuffer, Fonts& fonts, int y,
              const char* label, const char* value, Color value_color = kBright) {
  text(framebuffer, fonts.small, 150, y, label, kForeground);
  text(framebuffer, fonts.small, 640, y, value, value_color);
  framebuffer.rectangle(150, y + 18, 1070, 1, kSelection);
}

void status_card(Framebuffer& framebuffer, Fonts& fonts, int y,
                 const char* label, const char* value, Color value_color,
                 const char* value_line2 = nullptr) {
  framebuffer.rectangle(1050, y, 660, 62, kDark);
  framebuffer.border(1050, y, 660, 62, 1, kSelection);
  text(framebuffer, fonts.small, 1072, y + 40, label, kForeground);
  if (value_line2) {
    text_right(framebuffer, fonts.small, 1688, y + 27, value, value_color);
    text_right(framebuffer, fonts.small, 1688, y + 51, value_line2,
               value_color);
  } else {
    text_right(framebuffer, fonts.small, 1688, y + 40, value, value_color);
  }
}

void draw_home(Framebuffer& framebuffer, Fonts& fonts, const App& app) {
  text(framebuffer, fonts.label, 110, 244,
       app.boot_set_ready ? "READY"
           : app.boot_update_available ? "UPDATE AVAILABLE"
           : app.boot_check_blocked ? "RECOVERY REQUIRED"
                                       : "BOOT FILES NOT INSTALLED",
       app.boot_set_ready ? kGreen : app.boot_check_blocked ? kError : kWarning);
  text(framebuffer, fonts.heading, 110, 344, "Omarchy Linux", kBright);
  text(framebuffer, fonts.body, 110, 411,
       "Install the boot files once, then boot Omarchy.", kForeground);
  text(framebuffer, fonts.small, 110, 458,
       "The tested Baikal kernel is selected automatically. Linux stays on USB.",
       kForeground);

  if (app.boot_set_ready) {
    flow_button(framebuffer, fonts, 110, 526, 590, "Boot Omarchy",
                app.focus == 0, true);
    flow_button(framebuffer, fonts, 110, 606, 590,
                app.boot_update_available ? "Update boot files"
                                          : "Reinstall boot files",
                app.focus == 1);
  } else {
    flow_button(framebuffer, fonts, 110, 526, 590,
                app.boot_update_available ? "Update boot files"
                                          : "Install boot files",
                app.focus == 0, true);
    flow_button(framebuffer, fonts, 110, 606, 590, "Boot Omarchy",
                false, false, false);
  }
  text(framebuffer, fonts.small, 110, 735,
       "OPTIONS  Theme & wallpaper", kForeground);

  text(framebuffer, fonts.label, 1050, 390, "SYSTEM CHECK", kBlue);
  status_card(framebuffer, fonts, 422, "BOOT FILES",
              app.boot_set_ready ? "Verified and ready"
                  : app.boot_update_available ? "New bundled set"
                      : app.boot_check_blocked ? "Recovery required"
                                               : "Install required",
              app.boot_set_ready ? kGreen
                  : app.boot_check_blocked ? kError : kWarning);
  status_card(framebuffer, fonts, 496, "KERNEL",
              "6.18.44 - Baikal - automatic", kBright);
  status_card(framebuffer, fonts, 570, "OMARCHY USB",
              "Connect before boot -", kForeground, "checked by Linux");
}

void page_title(Framebuffer& framebuffer, Fonts& fonts, const char* kicker,
                const char* title_value, const char* body_value);

void draw_settings(Framebuffer& framebuffer, Fonts& fonts, const App& app) {
  page_title(framebuffer, fonts, "APPEARANCE", "Theme & wallpaper",
             "Each Omarchy theme opens on its upstream default wallpaper.");

  static const char* labels[] = {
      "Tokyo Night  -  3 wallpapers",
      "Last Horizon  -  4 wallpapers",
      "Lupine  -  5 wallpapers",
      "Solitude  -  5 wallpapers",
  };
  for (int index = 0; index < kThemeCount; ++index) {
    const int y = 408 + index * 86;
    button(framebuffer, fonts, 110, y, 790, labels[index], app.focus == index,
           app.theme_index == index);
    if (app.theme_index == index) {
      text(framebuffer, fonts.label, 820, y + 47, "SELECTED", kBright);
    }
  }

  framebuffer.rectangle(970, 408, 740, 334, kPanel);
  framebuffer.border(970, 408, 740, 334, 1, kSelection);
  text(framebuffer, fonts.label, 1010, 458, "CURRENT APPEARANCE", kForeground);
  text(framebuffer, fonts.title, 1010, 526, kThemes[app.theme_index].name, kBright);
  text(framebuffer, fonts.small, 1010, 580,
       "Upstream default wallpaper on launch", kForeground);
  text(framebuffer, fonts.small, 1010, 620,
       "Only this user's appearance preference is saved.", kForeground);
  const char* preference_status = app.settings_save_failed
      ? "Could not save. Your preview is still active."
      : app.settings_saved ? "Saved preference loaded"
                           : "Using default or unsaved preview";
  const Color preference_color = app.settings_save_failed
      ? kError : app.settings_saved ? kGreen : kWarning;
  text(framebuffer, fonts.small, 1010, 680, preference_status,
       preference_color);

  button(framebuffer, fonts, 110, 790, 370, "Shuffle now", app.focus == 4);
  button(framebuffer, fonts, 500, 790, 280, "Apply", app.focus == 5, true);
  button(framebuffer, fonts, 800, 790, 280, "Cancel", app.focus == 6);
}

void page_title(Framebuffer& framebuffer, Fonts& fonts, const char* kicker,
                const char* title_value, const char* body_value) {
  text(framebuffer, fonts.label, 110, 245, kicker, kBlue);
  text(framebuffer, fonts.title, 110, 315, title_value, kBright);
  text(framebuffer, fonts.body, 110, 365, body_value, kForeground);
}

void draw_install_review(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts,
             kInternalBoot ? "INSTALL BOOT FILES" : "REVIEW INSTALLATION",
             kInternalBoot ? "Install the verified boot set?" : "Install Omarchy 4.0.0?",
             kInternalBoot
                 ? "The kernel and initramfs go to internal app storage. Omarchy stays on USB."
                 : "Review the intended release settings before previewing the flow.");
  framebuffer.rectangle(110, 408, 1150, 334, kPanel);
  framebuffer.border(110, 408, 1150, 334, 1, kSelection);
  fact_row(framebuffer, fonts, 462, "Release", "Omarchy 4.0.0");
  fact_row(framebuffer, fonts, 520, "Kernel", "Linux 6.18.44 - Baikal");
  fact_row(framebuffer, fonts, 578, "Linux root", "External Omarchy USB");
  fact_row(framebuffer, fonts, 636, "Video memory", "1024 MB");
  fact_row(framebuffer, fonts, 694, "Internal storage",
           kInternalBoot ? "Verified boot files only" : "Untouched", kGreen);

  framebuffer.rectangle(1310, 408, 500, 210, kDarker);
  framebuffer.border(1310, 408, 500, 210, 2, kWarning);
  text(framebuffer, fonts.label, 1340, 456,
       kInternalBoot ? "SAFE UPDATE" : "UI-ONLY BUILD", kWarning);
  text(framebuffer, fonts.small, 1340, 505,
       kInternalBoot ? "Keeps the previous boot set" : "Confirmation advances a visual",
       kForeground);
  text(framebuffer, fonts.small, 1340, 539,
       kInternalBoot ? "until the new files verify." : "simulation. No boot files are written.",
       kForeground);
  text(framebuffer, fonts.small, 1340, 573,
       kInternalBoot ? "The Omarchy USB is never written." : "No boot handoff is included.",
       kForeground);

  button(framebuffer, fonts, 110, 812, 500,
         kInternalBoot ? "Install files" : "Preview installation",
         focus == 0, true);
  button(framebuffer, fonts, 634, 812, 300, "Back", focus == 1);
}

void draw_progress(Framebuffer& framebuffer, Fonts& fonts, int phase) {
  static const char* names[] = {
      "Checking current files", "Verifying bundled files",
      "Activating boot files"};
  static const char* details[] = {
      "Looking for an installed boot set and retained recovery copy.",
      "Checking the kernel, initramfs, loader and boot arguments.",
      "Making the verified set active and keeping the previous set."};
  static const int percents[] = {18, 52, 82};

  page_title(framebuffer, fonts,
             kInternalBoot ? "INSTALLING BOOT FILES" : "INSTALLATION PREVIEW",
             kInternalBoot ? "Installing the tested boot set" : "Installing Omarchy",
             kInternalBoot
                 ? "The boot files are verified before they become active."
                 : "The timing and progress are simulated for interface testing.");
  framebuffer.rectangle(110, 420, 1350, 272, kPanel);
  framebuffer.border(110, 420, 1350, 272, 1, kSelection);
  text(framebuffer, fonts.label, 150, 475, "CURRENT PHASE", kForeground);
  text(framebuffer, fonts.title, 150, 543, names[phase], kBright);
  text(framebuffer, fonts.small, 150, 590, details[phase], kForeground);
  framebuffer.rectangle(150, 635, 1265, 12, kSelection);
  framebuffer.rectangle(150, 635, 1265 * percents[phase] / 100, 12, kBlue);
  text(framebuffer, fonts.small, 1360, 610,
       phase == 0 ? "18%" : phase == 1 ? "52%" : "82%", kBright);
  text(framebuffer, fonts.small, 110, 754,
       kInternalBoot
           ? "Do not close the app during final activation. The USB is never written."
           : "SIMULATED - cancel is safe; no boot, Linux or USB files are written.",
       kWarning);
  button(framebuffer, fonts, 110, 822, 330,
         kInternalBoot ? "Cancel" : "Cancel preview", true);
}

void draw_ready(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  text(framebuffer, fonts.label, 110, 285, "READY", kGreen);
  text(framebuffer, fonts.heading, 110, 388,
       kInternalBoot ? "Boot files installed." : "The UI preview is ready.",
       kBright);
  text(framebuffer, fonts.body, 110, 462,
       kInternalBoot
           ? "Choose the hardware-tested kernel, then launch Omarchy."
           : "No boot files were written. Continue to review the handoff screen.",
       kForeground);
  framebuffer.rectangle(110, 536, 900, 150, kPanel);
  text(framebuffer, fonts.small, 148, 591, "Release", kForeground);
  text(framebuffer, fonts.small, 410, 591, "Omarchy 4.0.0", kBright);
  text(framebuffer, fonts.small, 148, 646, "Video memory", kForeground);
  text(framebuffer, fonts.small, 410, 646, "1024 MB", kBright);
  button(framebuffer, fonts, 110, 764, 430, "Choose kernel", focus == 0, true);
  button(framebuffer, fonts, 564, 764, 430, "Launch Omarchy", focus == 1);
}

void draw_kernel_select(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts, "CHOOSE KERNEL", "Linux 6.18.44 - Baikal",
             "Only kernels tested for this hardware appear here.");
  framebuffer.rectangle(110, 430, 1120, 214, kPanel);
  framebuffer.border(110, 430, 1120, 214, focus == 0 ? 3 : 1,
                     focus == 0 ? kBlue : kSelection);
  text(framebuffer, fonts.label, 150, 478, "RECOMMENDED", kGreen);
  text(framebuffer, fonts.title, 150, 548, "Linux 6.18.44", kBright);
  text(framebuffer, fonts.small, 150, 596,
       "Baikal B1 - 1024 MB video memory - current verified build", kForeground);
  text(framebuffer, fonts.small, 1320, 472, "MORE KERNELS", kForeground);
  text(framebuffer, fonts.small, 1320, 516,
       "Added only after hardware acceptance.", kForeground);
  button(framebuffer, fonts, 110, 744, 470, "Use this kernel", focus == 0, true);
  button(framebuffer, fonts, 604, 744, 300, "Back", focus == 1);
}

void draw_boot_review(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts, "READY TO LAUNCH", "Launch Omarchy?",
      kPrivateBoot
                 ? kInternalBoot
                       ? "The manager checks the boot set, then Linux verifies the Omarchy USB."
                       : "The console screen will be replaced by the existing USB Linux system."
                 : "This is the final product confirmation, shown here as a simulation.");
  framebuffer.rectangle(110, 424, 1120, 250, kPanel);
  fact_row(framebuffer, fonts, 482, "Release", "Omarchy 4.0.0");
  fact_row(framebuffer, fonts, 544, "Kernel", "Linux 6.18.44 - Baikal");
  fact_row(framebuffer, fonts, 606, "Omarchy USB", "Verified by Linux during startup");
  text(framebuffer, fonts.small, 110, 742,
       kPrivateBoot
           ? "Keep the Omarchy USB connected during the local Linux handoff."
           : "UI prototype: confirmation cannot start Linux; boot code is not included.",
       kWarning);
  button(framebuffer, fonts, 110, 812, 430,
         kPrivateBoot ? "Launch Omarchy" : "Preview handoff", focus == 0, true);
  button(framebuffer, fonts, 564, 812, 300, "Back", focus == 1);
}

void draw_booting(Framebuffer& framebuffer, Fonts& fonts, const App& app) {
  text(framebuffer, fonts.label, 110, 310, "STARTING LINUX", kGreen);
  text(framebuffer, fonts.heading, 110, 414, "Handing over to Omarchy.", kBright);
  text(framebuffer, fonts.body, 110, 490,
       app.boot_message ? app.boot_message
                        : "Checking the embedded loader before the one-time handoff.",
       kForeground);
  framebuffer.rectangle(110, 606, 1050, 96, kDarker);
  framebuffer.border(110, 606, 1050, 96, 2, kGreen);
  text(framebuffer, fonts.small, 145, 665,
       "Keep the console and USB drive powered while Linux starts.", kGreen);
}

void draw_boot_error(Framebuffer& framebuffer, Fonts& fonts, const App& app) {
  text(framebuffer, fonts.label, 110, 310, "BOOT NOT STARTED", kError);
  text(framebuffer, fonts.heading, 110, 414, "The console is unchanged.", kBright);
  text(framebuffer, fonts.body, 110, 490,
       app.boot_message ? app.boot_message : "The local boot handoff failed.",
       kForeground);
  text(framebuffer, fonts.small, 110, 570,
       app.boot_error_from_stage
           ? "The previous boot set was retained. Return and retry only after reviewing diagnostics."
           : "The local Linux handoff is unavailable. Return and review the UART diagnostics.",
       kWarning);
  button(framebuffer, fonts, 110, 690, 430, "Return home", true, true);
}

void draw_complete(Framebuffer& framebuffer, Fonts& fonts) {
  text(framebuffer, fonts.label, 110, 310, "PROTOTYPE COMPLETE", kGreen);
  text(framebuffer, fonts.heading, 110, 414, "Handoff intentionally stopped.", kBright);
  text(framebuffer, fonts.body, 110, 490,
       "The complete console flow is visible and controller-testable.", kForeground);
  text(framebuffer, fonts.body, 110, 535,
       "This package contains presentation code only and cannot boot Linux.",
       kForeground);
  framebuffer.rectangle(110, 606, 950, 96, kDarker);
  framebuffer.border(110, 606, 950, 96, 2, kGreen);
  text(framebuffer, fonts.small, 145, 665,
       "No network request, system-file write, or boot handoff was attempted.", kGreen);
  button(framebuffer, fonts, 110, 786, 430, "Return home", true, true);
}

void draw_recovery(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts, "TOOLS", "Recovery & diagnostics",
             kInternalBoot
                 ? "Recovery actions are visible for review but are not enabled in this beta."
                 : "Explore the recovery information architecture. Every action is visual only.");
  button(framebuffer, fonts, 110, 430, 850,
         kInternalBoot ? "Verify boot files  -  coming soon" : "Verify boot files",
         focus == 0);
  button(framebuffer, fonts, 110, 526, 850,
         kInternalBoot ? "Restore previous set  -  coming soon" : "Restore previous boot set",
         focus == 1);
  button(framebuffer, fonts, 110, 622, 850,
         kInternalBoot ? "Export diagnostics  -  coming soon" : "Export diagnostics",
         focus == 2);
  button(framebuffer, fonts, 110, 718, 850, "Back to Home", focus == 3);
  framebuffer.rectangle(1030, 430, 700, 268, kDarker);
  framebuffer.border(1030, 430, 700, 268, 1, kSelection);
  text(framebuffer, fonts.label, 1065, 480,
       kInternalBoot ? "BETA LIMIT" : "PROTOTYPE SAFETY", kWarning);
  text(framebuffer, fonts.small, 1065, 530,
       "Verify reads no files.", kForeground);
  text(framebuffer, fonts.small, 1065, 568,
       "Restore changes no files.", kForeground);
  text(framebuffer, fonts.small, 1065, 606,
       "Export creates no support bundle.", kForeground);
  text(framebuffer, fonts.small, 1065, 652,
       kInternalBoot ? "No recovery action is executed." : "These are screen and controller tests only.",
       kForeground);
}

void draw_recovery_notice(Framebuffer& framebuffer, Fonts& fonts, int notice) {
  if (kInternalBoot) {
    text(framebuffer, fonts.label, 110, 312, "NOT ENABLED", kWarning);
    text(framebuffer, fonts.title, 110, 397,
         "Recovery is not available in this beta.", kBright);
    text(framebuffer, fonts.body, 110, 472,
         "No boot file was read, replaced, restored or exported.", kForeground);
    button(framebuffer, fonts, 110, 610, 430, "Back to recovery", true, true);
    return;
  }
  const char* kicker = notice == 0 ? "VERIFY PREVIEW" : notice == 1 ? "RESTORE PREVIEW" : "EXPORT PREVIEW";
  const char* title_value = notice == 0 ? "Verification screen complete."
      : notice == 1 ? "Restore screen complete."
                    : "Export screen complete.";
  const char* body_value = notice == 0
      ? "No boot files were opened or checked by this UI-only package."
      : notice == 1
          ? "No boot set was replaced and no storage path was opened."
          : "No diagnostics file was created and no information was uploaded.";
  text(framebuffer, fonts.label, 110, 312, kicker, kGreen);
  text(framebuffer, fonts.title, 110, 397, title_value, kBright);
  text(framebuffer, fonts.body, 110, 472, body_value, kForeground);
  button(framebuffer, fonts, 110, 610, 430, "Back to recovery", true, true);
}

void draw_credits(Framebuffer& framebuffer, Fonts& fonts) {
  page_title(framebuffer, fonts, "ABOUT", "Credits & licenses",
             "The native package records exactly what is used by this private prototype.");
  framebuffer.rectangle(110, 410, 1520, 420, kPanel);
  fact_row(framebuffer, fonts, 468, "Omarchy", "4.0.0 - MIT");
  fact_row(framebuffer, fonts, 526, "Appearance", "4 Quattro themes - 17 private-preview wallpapers");
  fact_row(framebuffer, fonts, 584, "Theme setting", "Local app preference only");
  fact_row(framebuffer, fonts, 642, "Native toolchain", "OpenOrbis v0.5.4 - GPL-3.0");
  fact_row(framebuffer, fonts, 700, "Primary UI font", "Console SST - runtime only");
  fact_row(framebuffer, fonts, 758, "Fallback font", "Gontserrat - OFL-1.1");
  button(framebuffer, fonts, 110, 872, 430, "Back to Home", true, true);
}

void draw(App& app, Framebuffer& framebuffer, Fonts& fonts,
          const Image& background, const Image& logo) {
  if (background.valid()) {
    background.draw(framebuffer, 0, 0);
  } else {
    framebuffer.rectangle(0, 0, kWidth, kHeight, kBackground);
  }
  draw_header(framebuffer, fonts, logo);

  switch (app.screen) {
    case Screen::Home:
      draw_home(framebuffer, fonts, app);
      break;
    case Screen::Settings:
      draw_settings(framebuffer, fonts, app);
      break;
    case Screen::InstallReview:
      draw_install_review(framebuffer, fonts, app.focus);
      break;
    case Screen::Progress:
      draw_progress(framebuffer, fonts, app.progress_phase < 0 ? 0 : app.progress_phase);
      break;
    case Screen::Ready:
      draw_ready(framebuffer, fonts, app.focus);
      break;
    case Screen::KernelSelect:
      draw_kernel_select(framebuffer, fonts, app.focus);
      break;
    case Screen::BootReview:
      draw_boot_review(framebuffer, fonts, app.focus);
      break;
    case Screen::Booting:
      draw_booting(framebuffer, fonts, app);
      break;
    case Screen::BootError:
      draw_boot_error(framebuffer, fonts, app);
      break;
    case Screen::Complete:
      draw_complete(framebuffer, fonts);
      break;
    case Screen::Recovery:
      draw_recovery(framebuffer, fonts, app.focus);
      break;
    case Screen::RecoveryNotice:
      draw_recovery_notice(framebuffer, fonts, app.recovery_notice);
      break;
    case Screen::Credits:
      draw_credits(framebuffer, fonts);
      break;
  }
}

void show(App& app, Screen screen) {
  app.screen = screen;
  app.focus = 0;
  app.dirty_frames = 2;
  printf("[omarchy-ui] screen=%s boot_files=%s kernel=linux-6.18.44-baikal\n",
         screen_name(screen), app.boot_set_ready ? "ready" : "missing");
}

int focus_count(const App& app) {
  switch (app.screen) {
    case Screen::Home: return app.boot_set_ready ? 2 : 1;
    case Screen::Settings: return 7;
    case Screen::InstallReview: return 2;
    case Screen::Ready: return 2;
    case Screen::KernelSelect: return 2;
    case Screen::BootReview: return 2;
    case Screen::Recovery: return 4;
    default: return 1;
  }
}

void move_focus(App& app, int direction) {
  const int count = focus_count(app);
  if (count <= 1) return;
  app.focus = (app.focus + direction + count) % count;
  app.dirty_frames = 2;
  printf("[omarchy-ui] input=navigate screen=%s focus=%d\n",
         screen_name(app.screen), app.focus);
}

void cancel_settings(App& app, Image& background) {
  const bool was_saved = app.settings_original_saved;
  app.theme_index = app.settings_original_theme;
  app.wallpaper_index = app.settings_original_wallpaper;
  apply_theme(app.theme_index);
  if (app.wallpaper_index < 0 ||
      !background.load(kThemes[app.theme_index].wallpapers[app.wallpaper_index])) {
    app.wallpaper_index = -1;
    load_default_wallpaper(app, background);
  }
  app.settings_saved = was_saved;
  app.settings_save_failed = false;
  show(app, Screen::Home);
}

void confirm(App& app, Image& background, int user_id, bool save_data_ready) {
  printf("[omarchy-ui] input=confirm screen=%s focus=%d\n",
         screen_name(app.screen), app.focus);
  switch (app.screen) {
    case Screen::Home:
      refresh_system_check(app);
      if (app.boot_set_ready && app.focus == 0) {
        app.boot_message = nullptr;
        app.boot_error_from_stage = false;
        if (kPrivateBoot) {
          app.boot_send_pending = true;
          show(app, Screen::Booting);
        } else {
          show(app, Screen::Complete);
        }
      } else {
        show(app, Screen::Progress);
        app.progress_phase = 0;
        app.progress_started = sceKernelGetProcessTime();
      }
      break;
    case Screen::Settings:
      if (app.focus < kThemeCount) {
        select_theme(app, background, app.focus);
        printf("[omarchy-ui] appearance preview-theme=%s\n",
               kThemes[app.theme_index].id);
      } else if (app.focus == 4) {
        shuffle_wallpaper(app, background);
        printf("[omarchy-ui] appearance shuffle theme=%s wallpaper=%d\n",
               kThemes[app.theme_index].id, app.wallpaper_index);
      } else if (app.focus == 5) {
        app.settings_saved = save_preferences(app, user_id, save_data_ready);
        app.settings_save_failed = !app.settings_saved;
        printf("[omarchy-ui] appearance save theme=%s result=%s\n",
               kThemes[app.theme_index].id,
               app.settings_saved ? "ok" : "failed");
        if (app.settings_saved) {
          show(app, Screen::Home);
        } else {
          app.dirty_frames = 2;
        }
      } else {
        cancel_settings(app, background);
      }
      break;
    case Screen::InstallReview:
      if (app.focus == 0) {
        show(app, Screen::Progress);
        app.progress_phase = 0;
        app.progress_started = sceKernelGetProcessTime();
      } else {
        show(app, Screen::Home);
      }
      break;
    case Screen::Progress:
      if (!app.boot_stage_pending) show(app, Screen::Home);
      break;
    case Screen::Ready:
      show(app, app.focus == 0 ? Screen::KernelSelect : Screen::BootReview);
      break;
    case Screen::KernelSelect:
      if (app.focus == 0) {
        printf("[omarchy-ui] kernel selected=linux-6.18.44-baikal\n");
        refresh_system_check(app);
        show(app, app.boot_set_ready ? Screen::BootReview : Screen::Home);
      } else {
        show(app, Screen::Home);
      }
      break;
    case Screen::BootReview:
      if (app.focus == 0 && kPrivateBoot) {
        app.boot_message = nullptr;
        app.boot_error_from_stage = false;
        app.boot_send_pending = true;
        show(app, Screen::Booting);
      } else {
        show(app, app.focus == 0 ? Screen::Complete
                                : kPrivateBoot ? Screen::Home : Screen::Ready);
      }
      break;
    case Screen::Booting:
      break;
    case Screen::BootError:
      show(app, Screen::Home);
      break;
    case Screen::Complete:
      show(app, Screen::Home);
      break;
    case Screen::Recovery:
      if (app.focus == 3) {
        show(app, Screen::Home);
      } else {
        app.recovery_notice = app.focus;
        show(app, Screen::RecoveryNotice);
      }
      break;
    case Screen::RecoveryNotice:
      show(app, Screen::Recovery);
      break;
    case Screen::Credits:
      show(app, Screen::Home);
      break;
  }
}

void back(App& app, Image& background) {
  printf("[omarchy-ui] input=back screen=%s focus=%d\n",
         screen_name(app.screen), app.focus);
  switch (app.screen) {
    case Screen::Home: break;
    case Screen::Settings: cancel_settings(app, background); break;
    case Screen::InstallReview: show(app, Screen::Home); break;
    case Screen::Progress:
      if (!app.boot_stage_pending) show(app, Screen::Home);
      break;
    case Screen::Ready: show(app, Screen::Home); break;
    case Screen::KernelSelect: show(app, Screen::Home); break;
    case Screen::BootReview:
      show(app, Screen::Home);
      break;
    case Screen::Booting: break;
    case Screen::BootError:
      show(app, Screen::Home);
      break;
    case Screen::Complete: show(app, Screen::Home); break;
    case Screen::Recovery: show(app, Screen::Home); break;
    case Screen::RecoveryNotice: show(app, Screen::Recovery); break;
    case Screen::Credits: show(app, Screen::Home); break;
  }
}

struct Controller {
  int user_id = -1;
  int pad = -1;
};

Controller open_controller() {
  Controller controller;
  if (scePadInit() != 0) return controller;
  OrbisUserServiceInitializeParams params;
  memset(&params, 0, sizeof(params));
  params.priority = ORBIS_KERNEL_PRIO_FIFO_LOWEST;
  if (sceUserServiceInitialize(&params) < 0) return controller;
  if (sceUserServiceGetInitialUser(&controller.user_id) < 0) return controller;
  controller.pad = scePadOpen(controller.user_id, 0, 0, nullptr);
  return controller;
}

}  // namespace

int main() {
  setvbuf(stdout, nullptr, _IONBF, 0);
  setvbuf(stderr, nullptr, _IONBF, 0);
  printf("[omarchy-ui] startup title-id=OMCH42069 profile=%s\n",
         kInternalBoot ? "kernel-manager"
                       : kPrivateBoot ? "linux-launcher" : "ui-prototype");

  Framebuffer framebuffer;
  if (!framebuffer.init()) {
    printf("[omarchy-ui] fatal framebuffer-init-failed\n");
    for (;;) sceKernelUsleep(1000000);
  }
  printf("[omarchy-ui] framebuffer ready width=%d height=%d\n", kWidth, kHeight);

  Fonts fonts;
  if (!fonts.init()) {
    printf("[omarchy-ui] fatal font-init-failed\n");
    framebuffer.rectangle(0, 0, kWidth, kHeight, kError);
    framebuffer.present(1);
    for (;;) sceKernelUsleep(1000000);
  }

  Image logo("/app0/assets/images/omarchy-header.png");
  const Controller controller = open_controller();
  printf("[omarchy-ui] controller user=%d pad=%d status=%s\n",
         controller.user_id, controller.pad,
         controller.pad >= 0 ? "ready" : "unavailable");
#ifdef OMARCHY_PRIVATE_BOOT
  const int32_t net_module_result = static_cast<int32_t>(
      sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_NET));
  printf("[omarchy-ui] Network module=0x%08x\n",
         static_cast<uint32_t>(net_module_result));
#endif
  const int32_t save_data_module_result = static_cast<int32_t>(
      sceSysmoduleLoadModuleInternal(ORBIS_SYSMODULE_INTERNAL_SAVE_DATA));
  // Initialization is authoritative: a negative load result can also mean the
  // linked module was already resident, which is not a reason to disable saves.
  const int32_t save_data_initialize_result = sceSaveDataInitialize3(0);
  const bool save_data_ready = save_data_initialize_result >= 0;
  printf("[omarchy-ui] SaveData module=0x%08x initialize=0x%08x ready=%d\n",
         static_cast<uint32_t>(save_data_module_result),
         static_cast<uint32_t>(save_data_initialize_result),
         save_data_ready ? 1 : 0);

  App app;
  refresh_system_check(app);
  load_preferences(app, controller.user_id, save_data_ready);
  apply_theme(app.theme_index);
  Image background;
  const bool wallpaper_ready = load_default_wallpaper(app, background);
  printf("[omarchy-ui] appearance theme=%s wallpaper=%d loaded=%s\n",
         kThemes[app.theme_index].id, app.wallpaper_index,
         wallpaper_ready ? "yes" : "no");
  show(app, Screen::Home);
  uint32_t previous_buttons = 0;
  int frame_id = 1;

  for (;;) {
    if (controller.pad >= 0) {
      OrbisPadData data;
      memset(&data, 0, sizeof(data));
      if (scePadReadState(controller.pad, &data) >= 0) {
        const uint32_t pressed = data.buttons & ~previous_buttons;
        previous_buttons = data.buttons;
        if (pressed & (ORBIS_PAD_BUTTON_UP | ORBIS_PAD_BUTTON_LEFT)) {
          move_focus(app, -1);
        }
        if (pressed & (ORBIS_PAD_BUTTON_DOWN | ORBIS_PAD_BUTTON_RIGHT)) {
          move_focus(app, 1);
        }
        if (pressed & ORBIS_PAD_BUTTON_CROSS) {
          confirm(app, background, controller.user_id, save_data_ready);
        }
        if (pressed & ORBIS_PAD_BUTTON_CIRCLE) back(app, background);
        if ((pressed & ORBIS_PAD_BUTTON_OPTIONS) && app.screen == Screen::Home) {
          app.settings_original_theme = app.theme_index;
          app.settings_original_wallpaper = app.wallpaper_index;
          app.settings_original_saved = app.settings_saved;
          app.settings_save_failed = false;
          printf("[omarchy-ui] input=options action=open-appearance\n");
          show(app, Screen::Settings);
        }
      }
    }

    if (app.screen == Screen::Progress) {
      const uint64_t elapsed = sceKernelGetProcessTime() - app.progress_started;
      const int next_phase = static_cast<int>(elapsed / 1500000);
      if (next_phase >= 3) {
        app.progress_started = 0;
#ifdef OMARCHY_INTERNAL_BOOT
        app.boot_stage_pending = true;
#else
        app.boot_set_ready = true;
        show(app, Screen::Home);
#endif
      } else if (next_phase != app.progress_phase) {
        app.progress_phase = next_phase;
        app.dirty_frames = 2;
        printf("[omarchy-ui] install progress-phase=%d\n", next_phase);
      }
    }

    if (app.dirty_frames > 0) {
      draw(app, framebuffer, fonts, background, logo);
      framebuffer.present(frame_id++);
      --app.dirty_frames;
    } else {
#ifdef OMARCHY_PRIVATE_BOOT
      if (app.boot_stage_pending) {
        app.boot_stage_pending = false;
        const omarchy_ps4::BootSendResult result =
            omarchy_ps4::stage_internal_boot_set();
        app.boot_message = omarchy_ps4::boot_send_message(result);
        printf("[omarchy-ui] Boot stage result=%d: %s\n",
               static_cast<int>(result), app.boot_message);
        if (result == omarchy_ps4::BootSendResult::Ok) {
          refresh_system_check(app);
          show(app, Screen::Home);
        } else {
          app.boot_error_from_stage = true;
          show(app, Screen::BootError);
        }
      } else if (app.boot_send_pending) {
        app.boot_send_pending = false;
        omarchy_ps4::BootSendResult result = omarchy_ps4::BootSendResult::Ok;
#ifdef OMARCHY_INTERNAL_BOOT
        result = omarchy_ps4::stage_internal_boot_set();
#endif
        if (result == omarchy_ps4::BootSendResult::Ok) {
          result = omarchy_ps4::send_embedded_loader();
        }
        app.boot_message = omarchy_ps4::boot_send_message(result);
        printf("[omarchy-ui] Boot send result=%d: %s\n",
               static_cast<int>(result), app.boot_message);
        if (result == omarchy_ps4::BootSendResult::Ok) {
          app.dirty_frames = 2;
        } else {
          show(app, Screen::BootError);
        }
      } else {
        sceKernelUsleep(16000);
      }
#else
      sceKernelUsleep(16000);
#endif
    }
  }
}
