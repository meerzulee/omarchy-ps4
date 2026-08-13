#define STBI_ASSERT(x)
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <proto-include.h>
#include <orbis/Pad.h>
#include <orbis/Sysmodule.h>
#include <orbis/UserService.h>
#include <orbis/VideoOut.h>
#include <orbis/libkernel.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace {

constexpr int kWidth = 1920;
constexpr int kHeight = 1080;
constexpr int kDepth = 4;
constexpr size_t kDirectAlignment = 0x200000;

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

constexpr Color kDarker = {0x0e, 0x0e, 0x14};
constexpr Color kDark = {0x13, 0x14, 0x1c};
constexpr Color kBackground = {0x1a, 0x1b, 0x26};
constexpr Color kPanel = {0x24, 0x28, 0x3b};
constexpr Color kSelection = {0x29, 0x2e, 0x42};
constexpr Color kForeground = {0xa9, 0xb1, 0xd6};
constexpr Color kBright = {0xc0, 0xca, 0xf5};
constexpr Color kBlue = {0x7a, 0xa2, 0xf7};
constexpr Color kGreen = {0x9e, 0xce, 0x6a};
constexpr Color kWarning = {0xe0, 0xaf, 0x68};
constexpr Color kError = {0xf7, 0x76, 0x8e};

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
  explicit Image(const char* path) {
    pixels_ = reinterpret_cast<uint32_t*>(
        stbi_load(path, &width_, &height_, &channels_, STBI_rgb_alpha));
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

enum class Screen {
  Home,
  InstallReview,
  Progress,
  Ready,
  BootReview,
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
  uint64_t progress_started = 0;
};

void draw_header(Framebuffer& framebuffer, Fonts& fonts, const Image& logo) {
  framebuffer.rectangle(0, 0, kWidth, 160, kDark);
  framebuffer.rectangle(0, 158, kWidth, 2, kSelection);
  logo.draw(framebuffer, 96, 54);
  text(framebuffer, fonts.title, 390, 116, "PS4", kBlue);
  text(framebuffer, fonts.label, 1545, 76, "UI PROTOTYPE", kWarning);
  text(framebuffer, fonts.label, 1545, 108, "NO SYSTEM ACTIONS", kForeground);
}

void draw_footer(Framebuffer& framebuffer, Fonts& fonts, bool back) {
  framebuffer.rectangle(0, 1006, kWidth, 74, kDarker);
  framebuffer.rectangle(0, 1006, kWidth, 2, kSelection);
  text(framebuffer, fonts.small, 96, 1053, "D-PAD  NAVIGATE", kForeground);
  text(framebuffer, fonts.small, 735, 1053, "X  CONFIRM", kBright);
  if (back) text(framebuffer, fonts.small, 1120, 1053, "O  BACK", kBright);
  text(framebuffer, fonts.label, 1585, 1051, "QUATTRO RC3", kForeground);
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

void fact_row(Framebuffer& framebuffer, Fonts& fonts, int y,
              const char* label, const char* value, Color value_color = kBright) {
  text(framebuffer, fonts.small, 150, y, label, kForeground);
  text(framebuffer, fonts.small, 640, y, value, value_color);
  framebuffer.rectangle(150, y + 18, 1070, 1, kSelection);
}

void draw_home(Framebuffer& framebuffer, Fonts& fonts) {
  text(framebuffer, fonts.label, 110, 316, "READY TO INSTALL", kBlue);
  text(framebuffer, fonts.heading, 110, 405, "A clean path to Linux.", kBright);
  text(framebuffer, fonts.body, 110, 475,
       "Explore the Omarchy console interface on your PS4.", kForeground);
  text(framebuffer, fonts.body, 110, 518,
       "This build is visual only and never changes the console or USB drive.",
       kForeground);
  framebuffer.rectangle(110, 568, 12, 12, kWarning);
  text(framebuffer, fonts.small, 143, 582,
       "Prototype state - no hardware checks have run", kForeground);
}

void draw_home_actions(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  button(framebuffer, fonts, 110, 644, 620, "Install Omarchy", focus == 0, true);
  button(framebuffer, fonts, 110, 742, 620, "Recovery & diagnostics", focus == 1);
  button(framebuffer, fonts, 110, 840, 620, "Credits & licenses", focus == 2);
}

void page_title(Framebuffer& framebuffer, Fonts& fonts, const char* kicker,
                const char* title_value, const char* body_value) {
  text(framebuffer, fonts.label, 110, 245, kicker, kBlue);
  text(framebuffer, fonts.title, 110, 315, title_value, kBright);
  text(framebuffer, fonts.body, 110, 365, body_value, kForeground);
}

void draw_install_review(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts, "REVIEW INSTALLATION", "Install Omarchy RC3?",
             "Review the intended release settings before previewing the flow.");
  framebuffer.rectangle(110, 408, 1150, 334, kPanel);
  framebuffer.border(110, 408, 1150, 334, 1, kSelection);
  fact_row(framebuffer, fonts, 462, "Release", "Omarchy Quattro RC3");
  fact_row(framebuffer, fonts, 520, "Boot target", "External PS4BOOT");
  fact_row(framebuffer, fonts, 578, "Linux root", "OMARCHY-PS4 - checked later by Linux");
  fact_row(framebuffer, fonts, 636, "Video memory", "1024 MB");
  fact_row(framebuffer, fonts, 694, "Internal PS4 storage", "Untouched", kGreen);

  framebuffer.rectangle(1310, 408, 500, 210, kDarker);
  framebuffer.border(1310, 408, 500, 210, 2, kWarning);
  text(framebuffer, fonts.label, 1340, 456, "UI-ONLY BUILD", kWarning);
  text(framebuffer, fonts.small, 1340, 505,
       "Confirmation advances a visual", kForeground);
  text(framebuffer, fonts.small, 1340, 539,
       "simulation. Nothing is written.", kForeground);
  text(framebuffer, fonts.small, 1340, 573,
       "No boot handoff is included.", kForeground);

  button(framebuffer, fonts, 110, 812, 500, "Preview installation", focus == 0, true);
  button(framebuffer, fonts, 634, 812, 300, "Back", focus == 1);
}

void draw_progress(Framebuffer& framebuffer, Fonts& fonts, int phase) {
  static const char* names[] = {
      "Checking system", "Verifying release", "Preparing boot files"};
  static const char* details[] = {
      "Previewing the PS4BOOT and free-space checks.",
      "Previewing verification of the pinned Quattro RC3 manifest.",
      "Previewing atomic boot-set staging with the previous set retained."};
  static const int percents[] = {18, 52, 82};

  page_title(framebuffer, fonts, "INSTALLATION PREVIEW", "Installing Omarchy",
             "The timing and progress are simulated for interface testing.");
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
       "SIMULATED - cancel is always safe because this build performs no writes.",
       kWarning);
  button(framebuffer, fonts, 110, 822, 330, "Cancel preview", true);
}

void draw_ready(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  text(framebuffer, fonts.label, 110, 285, "READY", kGreen);
  text(framebuffer, fonts.heading, 110, 388, "The UI preview is ready.", kBright);
  text(framebuffer, fonts.body, 110, 462,
       "No files were written. Continue to review the boot handoff screen.",
       kForeground);
  framebuffer.rectangle(110, 536, 900, 150, kPanel);
  text(framebuffer, fonts.small, 148, 591, "Release", kForeground);
  text(framebuffer, fonts.small, 410, 591, "Quattro RC3", kBright);
  text(framebuffer, fonts.small, 148, 646, "Video memory", kForeground);
  text(framebuffer, fonts.small, 410, 646, "1024 MB", kBright);
  button(framebuffer, fonts, 110, 764, 430, "Review boot", focus == 0, true);
  button(framebuffer, fonts, 564, 764, 300, "Home", focus == 1);
}

void draw_boot_review(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts, "REVIEW BOOT", "Boot Linux now?",
             "This is the final product confirmation, shown here as a simulation.");
  framebuffer.rectangle(110, 424, 1120, 250, kPanel);
  fact_row(framebuffer, fonts, 482, "Release", "Omarchy Quattro RC3");
  fact_row(framebuffer, fonts, 544, "Video memory", "1024 MB");
  fact_row(framebuffer, fonts, 606, "External root", "Verified by Linux after startup");
  text(framebuffer, fonts.small, 110, 742,
       "UI prototype: confirmation cannot start Linux; boot code is not included.",
       kWarning);
  button(framebuffer, fonts, 110, 812, 430, "Preview handoff", focus == 0, true);
  button(framebuffer, fonts, 564, 812, 300, "Back", focus == 1);
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
       "No network request, storage write, or boot handoff was attempted.", kGreen);
  button(framebuffer, fonts, 110, 786, 430, "Return home", true, true);
}

void draw_recovery(Framebuffer& framebuffer, Fonts& fonts, int focus) {
  page_title(framebuffer, fonts, "TOOLS", "Recovery & diagnostics",
             "Explore the recovery information architecture. Every action is visual only.");
  button(framebuffer, fonts, 110, 430, 850, "Verify boot files", focus == 0);
  button(framebuffer, fonts, 110, 526, 850, "Restore previous boot set", focus == 1);
  button(framebuffer, fonts, 110, 622, 850, "Export diagnostics", focus == 2);
  button(framebuffer, fonts, 110, 718, 850, "Back to Home", focus == 3);
  framebuffer.rectangle(1030, 430, 700, 268, kDarker);
  framebuffer.border(1030, 430, 700, 268, 1, kSelection);
  text(framebuffer, fonts.label, 1065, 480, "PROTOTYPE SAFETY", kWarning);
  text(framebuffer, fonts.small, 1065, 530,
       "Verify reads no files.", kForeground);
  text(framebuffer, fonts.small, 1065, 568,
       "Restore changes no files.", kForeground);
  text(framebuffer, fonts.small, 1065, 606,
       "Export creates no support bundle.", kForeground);
  text(framebuffer, fonts.small, 1065, 652,
       "These are screen and controller tests only.", kForeground);
}

void draw_recovery_notice(Framebuffer& framebuffer, Fonts& fonts, int notice) {
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
  fact_row(framebuffer, fonts, 468, "Omarchy", "Quattro RC3 - MIT");
  fact_row(framebuffer, fonts, 526, "Theme", "Tokyo Night - MIT");
  fact_row(framebuffer, fonts, 584, "Native toolchain", "OpenOrbis v0.5.4 - GPL-3.0");
  fact_row(framebuffer, fonts, 642, "Primary UI font", "Console SST - loaded at runtime, not bundled");
  fact_row(framebuffer, fonts, 700, "Fallback UI font", "Gontserrat - OFL-1.1");
  fact_row(framebuffer, fonts, 758, "PS4 branding", "Plain platform text; no Sony logo asset bundled");
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
      draw_home(framebuffer, fonts);
      draw_home_actions(framebuffer, fonts, app.focus);
      draw_footer(framebuffer, fonts, false);
      break;
    case Screen::InstallReview:
      draw_install_review(framebuffer, fonts, app.focus);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::Progress:
      draw_progress(framebuffer, fonts, app.progress_phase < 0 ? 0 : app.progress_phase);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::Ready:
      draw_ready(framebuffer, fonts, app.focus);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::BootReview:
      draw_boot_review(framebuffer, fonts, app.focus);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::Complete:
      draw_complete(framebuffer, fonts);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::Recovery:
      draw_recovery(framebuffer, fonts, app.focus);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::RecoveryNotice:
      draw_recovery_notice(framebuffer, fonts, app.recovery_notice);
      draw_footer(framebuffer, fonts, true);
      break;
    case Screen::Credits:
      draw_credits(framebuffer, fonts);
      draw_footer(framebuffer, fonts, true);
      break;
  }
}

void show(App& app, Screen screen) {
  app.screen = screen;
  app.focus = 0;
  app.dirty_frames = 2;
}

int focus_count(Screen screen) {
  switch (screen) {
    case Screen::Home: return 3;
    case Screen::InstallReview: return 2;
    case Screen::Ready: return 2;
    case Screen::BootReview: return 2;
    case Screen::Recovery: return 4;
    default: return 1;
  }
}

void move_focus(App& app, int direction) {
  const int count = focus_count(app.screen);
  if (count <= 1) return;
  app.focus = (app.focus + direction + count) % count;
  app.dirty_frames = 2;
}

void confirm(App& app) {
  switch (app.screen) {
    case Screen::Home:
      if (app.focus == 0) show(app, Screen::InstallReview);
      else if (app.focus == 1) show(app, Screen::Recovery);
      else show(app, Screen::Credits);
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
      show(app, Screen::Home);
      break;
    case Screen::Ready:
      show(app, app.focus == 0 ? Screen::BootReview : Screen::Home);
      break;
    case Screen::BootReview:
      show(app, app.focus == 0 ? Screen::Complete : Screen::Ready);
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

void back(App& app) {
  switch (app.screen) {
    case Screen::Home: break;
    case Screen::InstallReview: show(app, Screen::Home); break;
    case Screen::Progress: show(app, Screen::Home); break;
    case Screen::Ready: show(app, Screen::Home); break;
    case Screen::BootReview: show(app, Screen::Ready); break;
    case Screen::Complete: show(app, Screen::Home); break;
    case Screen::Recovery: show(app, Screen::Home); break;
    case Screen::RecoveryNotice: show(app, Screen::Recovery); break;
    case Screen::Credits: show(app, Screen::Home); break;
  }
}

int open_controller() {
  if (scePadInit() != 0) return -1;
  OrbisUserServiceInitializeParams params;
  memset(&params, 0, sizeof(params));
  params.priority = ORBIS_KERNEL_PRIO_FIFO_LOWEST;
  sceUserServiceInitialize(&params);
  int user_id = -1;
  if (sceUserServiceGetInitialUser(&user_id) < 0) return -1;
  return scePadOpen(user_id, 0, 0, nullptr);
}

}  // namespace

int main() {
  setvbuf(stdout, nullptr, _IONBF, 0);

  Framebuffer framebuffer;
  if (!framebuffer.init()) {
    for (;;) sceKernelUsleep(1000000);
  }

  Fonts fonts;
  if (!fonts.init()) {
    framebuffer.rectangle(0, 0, kWidth, kHeight, kError);
    framebuffer.present(1);
    for (;;) sceKernelUsleep(1000000);
  }

  Image background("/app0/assets/images/background.png");
  Image logo("/app0/assets/images/omarchy-header.png");
  const int pad = open_controller();

  App app;
  uint32_t previous_buttons = 0;
  int frame_id = 1;

  for (;;) {
    if (pad >= 0) {
      OrbisPadData data;
      memset(&data, 0, sizeof(data));
      if (scePadReadState(pad, &data) >= 0) {
        const uint32_t pressed = data.buttons & ~previous_buttons;
        previous_buttons = data.buttons;
        if (pressed & (ORBIS_PAD_BUTTON_UP | ORBIS_PAD_BUTTON_LEFT)) {
          move_focus(app, -1);
        }
        if (pressed & (ORBIS_PAD_BUTTON_DOWN | ORBIS_PAD_BUTTON_RIGHT)) {
          move_focus(app, 1);
        }
        if (pressed & ORBIS_PAD_BUTTON_CROSS) confirm(app);
        if (pressed & ORBIS_PAD_BUTTON_CIRCLE) back(app);
      }
    }

    if (app.screen == Screen::Progress) {
      const uint64_t elapsed = sceKernelGetProcessTime() - app.progress_started;
      const int next_phase = static_cast<int>(elapsed / 1500000);
      if (next_phase >= 3) {
        show(app, Screen::Ready);
      } else if (next_phase != app.progress_phase) {
        app.progress_phase = next_phase;
        app.dirty_frames = 2;
      }
    }

    if (app.dirty_frames > 0) {
      draw(app, framebuffer, fonts, background, logo);
      framebuffer.present(frame_id++);
      --app.dirty_frames;
    } else {
      sceKernelUsleep(16000);
    }
  }
}
