PROFILE ?= ui-only
ifeq ($(PROFILE),ui-only)
  TITLE := Omarchy UI Prototype
  VERSION := 0.13
  PROFILE_CXXFLAGS :=
  OUTPUT_NAME := fpkg-ui-prototype
else ifeq ($(PROFILE),private-boot)
  TITLE := Omarchy
  VERSION := 0.14
  PROFILE_CXXFLAGS := -DOMARCHY_PRIVATE_BOOT=1
  OUTPUT_NAME := fpkg-private-boot
else ifeq ($(PROFILE),private-kernel-manager)
  TITLE := Omarchy
  VERSION := 0.28
  PROFILE_CXXFLAGS := -DOMARCHY_PRIVATE_BOOT=1 -DOMARCHY_INTERNAL_BOOT=1
  OUTPUT_NAME := fpkg-private-kernel-manager
else
  $(error Unsupported PROFILE '$(PROFILE)'; use ui-only, private-boot, or private-kernel-manager)
endif
TITLE_ID := OMCH42069
CONTENT_ID := IV0000-OMCH42069_00-OMARCHYPS4UI0000

TOOLCHAIN := $(OO_PS4_TOOLCHAIN)
REPO_ROOT := $(abspath ../..)
BUILD_DIR := $(CURDIR)/build/$(PROFILE)
OBJECT_DIR := $(BUILD_DIR)/obj
STAGE_DIR := $(BUILD_DIR)/stage
OUTPUT_DIR ?= $(REPO_ROOT)/output/$(OUTPUT_NAME)
PACKAGE := $(OUTPUT_DIR)/$(CONTENT_ID).pkg
GP4 := $(STAGE_DIR)/package.gp4

OMARCHY_PIN := $(REPO_ROOT)/cache/omarchy-quattro
OMARCHY_LOGO := $(OMARCHY_PIN)/default/plymouth/logo.png
OMARCHY_LICENSE := $(OMARCHY_PIN)/LICENSE
PRIVATE_LOADER := $(REPO_ROOT)/fpkg/vendor/payloads/ps4-linux-loader.elf
PRIVATE_LOADER_SHA := $(REPO_ROOT)/fpkg/vendor/payloads/ps4-linux-loader.elf.sha256
PRIVATE_LOADER_PROVENANCE := $(REPO_ROOT)/fpkg/vendor/provenance/loader.json
PRIVATE_LOADER_EXPECTED_SHA := c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65
PRIVATE_LOADER_EXPECTED_SIZE := 320936
PRIVATE_BOOT_SET := $(REPO_ROOT)/fpkg/vendor/internal-boot
PRIVATE_BOOT_PROVENANCE := $(REPO_ROOT)/fpkg/vendor/provenance/internal-boot-set.json

TOKYO_WALLPAPERS := 0-winding-road.jpg 2-swirl-buck.jpg 4-omakub.jpg
LAST_HORIZON_WALLPAPERS := 1-eyes-wide.jpg 2-blink.jpg 3-bokeh.jpg 4-new-horizons.jpg
LUPINE_WALLPAPERS := 01-cherry-blossom-bokeh.jpg 02-cherry-blossom-white.jpg \
	03-pastel-clouds.jpg 04-elegant-blue-wave.jpg 05-abstract-wave.jpg
SOLITUDE_WALLPAPERS := 1-on-pole.jpg 2-wreakage.jpg 3-climb.jpg 4-ether.jpg 5-eyed.jpg

STAGED_TOKYO_WALLPAPERS := $(addprefix $(STAGE_DIR)/assets/images/tokyo-night-,$(TOKYO_WALLPAPERS))
STAGED_LAST_HORIZON_WALLPAPERS := $(addprefix $(STAGE_DIR)/assets/images/last-horizon-,$(LAST_HORIZON_WALLPAPERS))
STAGED_LUPINE_WALLPAPERS := $(addprefix $(STAGE_DIR)/assets/images/lupine-,$(LUPINE_WALLPAPERS))
STAGED_SOLITUDE_WALLPAPERS := $(addprefix $(STAGE_DIR)/assets/images/solitude-,$(SOLITUDE_WALLPAPERS))
STAGED_WALLPAPERS := $(STAGED_TOKYO_WALLPAPERS) \
	$(STAGED_LAST_HORIZON_WALLPAPERS) \
	$(STAGED_LUPINE_WALLPAPERS) \
	$(STAGED_SOLITUDE_WALLPAPERS)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  PLATFORM_DIR := macos
  CXX ?= /opt/homebrew/opt/llvm/bin/clang++
  LD ?= /opt/homebrew/opt/lld@20/bin/ld.lld
  FSELF := $(TOOLCHAIN)/bin/macos/create-fself
else
  PLATFORM_DIR := linux
  CXX ?= clang++
  LD ?= ld.lld
  FSELF := $(TOOLCHAIN)/bin/linux/create-fself
endif

PKG_TOOL := $(TOOLCHAIN)/bin/$(PLATFORM_DIR)/PkgTool.Core
CREATE_GP4 := $(TOOLCHAIN)/bin/$(PLATFORM_DIR)/create-gp4
MAGICK ?= magick

CXXFLAGS := --target=x86_64-pc-freebsd12-elf -std=c++17 -O2 -Wall -Wextra \
	-fPIC -funwind-tables -c -isysroot $(TOOLCHAIN) \
	-isystem $(TOOLCHAIN)/include -isystem $(TOOLCHAIN)/include/c++/v1 \
	$(PROFILE_CXXFLAGS)
LIBS := -lc -lkernel -lc++ -lSceVideoOut -lSceSysmodule -lSceFreeType \
	-lScePad -lSceUserService -lSceSaveData
LDFLAGS := -m elf_x86_64 -pie --script $(TOOLCHAIN)/link.x --eh-frame-hdr \
	-L$(TOOLCHAIN)/lib $(LIBS) $(TOOLCHAIN)/lib/crt1.o

.PHONY: all fpkg private-boot private-kernel-manager host-test audit clean check-tools

all: fpkg

fpkg: $(PACKAGE)

private-boot:
	$(MAKE) PROFILE=private-boot clean fpkg audit

private-kernel-manager:
	$(MAKE) PROFILE=private-kernel-manager clean fpkg audit

host-test:
	mkdir -p $(BUILD_DIR)/host
	$${CXX:-c++} -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
		sha256.cpp sha256_test.cpp -o $(BUILD_DIR)/host/sha256-test
	$(BUILD_DIR)/host/sha256-test

check-tools:
	@test -n "$(TOOLCHAIN)" || { echo "OO_PS4_TOOLCHAIN is not set" >&2; exit 1; }
	@test -x "$(CXX)" || { echo "C++ compiler not found: $(CXX)" >&2; exit 1; }
	@test -x "$(LD)" || { echo "LLD linker not found: $(LD)" >&2; exit 1; }
	@test -x "$(PKG_TOOL)" || { echo "PkgTool.Core not found: $(PKG_TOOL)" >&2; exit 1; }
	@test -x "$(CREATE_GP4)" || { echo "create-gp4 not found: $(CREATE_GP4)" >&2; exit 1; }
	@test -x "$(FSELF)" || { echo "create-fself not found: $(FSELF)" >&2; exit 1; }
	@test -f "$(OMARCHY_LOGO)" || { echo "Pinned Omarchy logo missing" >&2; exit 1; }
	@test -f "$(OMARCHY_LICENSE)" || { echo "Pinned Omarchy license missing" >&2; exit 1; }
	@if test "$(PROFILE)" != ui-only; then set -e; \
		test -f "$(PRIVATE_LOADER)"; \
		test -f "$(PRIVATE_LOADER_SHA)"; \
		test -f "$(PRIVATE_LOADER_PROVENANCE)"; \
		test "$$(stat -f %z "$(PRIVATE_LOADER)" 2>/dev/null || stat -c %s "$(PRIVATE_LOADER)")" = "$(PRIVATE_LOADER_EXPECTED_SIZE)"; \
		test "$$(shasum -a 256 "$(PRIVATE_LOADER)" | awk '{print $$1}')" = "$(PRIVATE_LOADER_EXPECTED_SHA)"; \
	fi
	@if test "$(PROFILE)" = private-kernel-manager; then set -e; \
		test "$$(stat -f %z "$(PRIVATE_BOOT_SET)/bzImage" 2>/dev/null || stat -c %s "$(PRIVATE_BOOT_SET)/bzImage")" = 11060224; \
		test "$$(shasum -a 256 "$(PRIVATE_BOOT_SET)/bzImage" | awk '{print $$1}')" = b7c8b9d67c600ee08b2321f7f4fac08c506791b0ab9c3f3d01598a90471a9de5; \
		test "$$(stat -f %z "$(PRIVATE_BOOT_SET)/initramfs.cpio.gz" 2>/dev/null || stat -c %s "$(PRIVATE_BOOT_SET)/initramfs.cpio.gz")" = 1686508; \
		test "$$(shasum -a 256 "$(PRIVATE_BOOT_SET)/initramfs.cpio.gz" | awk '{print $$1}')" = 824530e22392376d5fc27994a9ccff97f0442b7a41681155f46e183f892365ae; \
		test "$$(stat -f %z "$(PRIVATE_BOOT_SET)/bootargs.txt" 2>/dev/null || stat -c %s "$(PRIVATE_BOOT_SET)/bootargs.txt")" = 502; \
		test "$$(shasum -a 256 "$(PRIVATE_BOOT_SET)/bootargs.txt" | awk '{print $$1}')" = 8064d91f286d4275dac08e2fae29e43fbf745ea7be15f797edbbd0e5036a4930; \
		test "$$(shasum -a 256 "$(PRIVATE_BOOT_SET)/vram.txt" | awk '{print $$1}')" = 4f71bb761ace37c88826cd8cc1c948e1cf5b5d0cd153dc651a6efdb3dfb9f2b1; \
		test -f "$(PRIVATE_BOOT_SET)/release.json"; \
		test -f "$(PRIVATE_BOOT_PROVENANCE)"; \
	fi
	@command -v $(MAGICK) >/dev/null || { echo "ImageMagick is required" >&2; exit 1; }

SOURCES := main.cpp sha256.cpp
ifneq ($(PROFILE),ui-only)
SOURCES += private_boot.cpp
endif
OBJECTS := $(addprefix $(OBJECT_DIR)/,$(SOURCES:.cpp=.o))

$(OBJECT_DIR)/%.o: %.cpp | check-tools
	mkdir -p $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/prototype.elf: $(OBJECTS)
	$(LD) $(OBJECTS) -o $@ $(LDFLAGS)

$(STAGE_DIR)/eboot.bin: $(BUILD_DIR)/prototype.elf
	mkdir -p $(STAGE_DIR)
	$(FSELF) -in=$< -out=$(BUILD_DIR)/prototype.oelf --eboot $@ --paid 0x3800000000000011

$(STAGED_TOKYO_WALLPAPERS): $(STAGE_DIR)/assets/images/tokyo-night-%: $(OMARCHY_PIN)/themes/tokyo-night/backgrounds/% | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) $< -auto-orient -resize '1920x1080^' -gravity center -extent 1920x1080 \
		-fill 'rgba(14,14,20,0.58)' -draw 'rectangle 0,0 1920,1080' \
		-alpha off -strip -quality 84 $@

$(STAGED_LAST_HORIZON_WALLPAPERS): $(STAGE_DIR)/assets/images/last-horizon-%: $(OMARCHY_PIN)/themes/last-horizon/backgrounds/% | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) $< -auto-orient -resize '1920x1080^' -gravity center -extent 1920x1080 \
		-fill 'rgba(6,6,6,0.58)' -draw 'rectangle 0,0 1920,1080' \
		-alpha off -strip -quality 84 $@

$(STAGED_LUPINE_WALLPAPERS): $(STAGE_DIR)/assets/images/lupine-%: $(OMARCHY_PIN)/themes/lupine/backgrounds/% | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) $< -auto-orient -resize '1920x1080^' -gravity center -extent 1920x1080 \
		-fill 'rgba(250,250,250,0.58)' -draw 'rectangle 0,0 1920,1080' \
		-alpha off -strip -quality 84 $@

$(STAGED_SOLITUDE_WALLPAPERS): $(STAGE_DIR)/assets/images/solitude-%: $(OMARCHY_PIN)/themes/solitude/backgrounds/% | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) $< -auto-orient -resize '1920x1080^' -gravity center -extent 1920x1080 \
		-fill 'rgba(8,10,11,0.58)' -draw 'rectangle 0,0 1920,1080' \
		-alpha off -strip -quality 84 $@

$(STAGE_DIR)/assets/images/omarchy-header.png: $(OMARCHY_LOGO) | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) $< -resize '260x61>' -background none -gravity center \
		-extent 270x64 -type TrueColorAlpha PNG32:$@

$(STAGE_DIR)/assets/fonts/Gontserrat-Regular.ttf: | check-tools
	mkdir -p $(dir $@)
	cp $(TOOLCHAIN)/samples/font/assets/fonts/Gontserrat-Regular.ttf $@

$(STAGE_DIR)/assets/fonts/OFL.txt: | check-tools
	mkdir -p $(dir $@)
	cp $(TOOLCHAIN)/samples/font/assets/fonts/OFL.txt $@

$(STAGE_DIR)/sce_sys/icon0.png: $(OMARCHY_LOGO) | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) -size 512x512 xc:'#161722' -fill none -stroke '#414868' \
		-strokewidth 3 -draw 'roundrectangle 14,14 497,497 18,18' \
		\( $(OMARCHY_LOGO) -resize 380x \) -gravity center -composite \
		-alpha off -type TrueColor PNG24:$@

$(STAGE_DIR)/sce_sys/save_data.png: $(OMARCHY_LOGO) | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) -size 228x128 xc:'#161722' \( $< -resize '184x44>' \) \
		-gravity center -composite -alpha off -type TrueColor PNG24:$@

$(STAGE_DIR)/sce_sys/param.sfo: Makefile | check-tools
	mkdir -p $(dir $@)
	$(PKG_TOOL) sfo_new $@
	$(PKG_TOOL) sfo_setentry $@ APP_TYPE --type Integer --maxsize 4 --value 1
	$(PKG_TOOL) sfo_setentry $@ APP_VER --type Utf8 --maxsize 8 --value '$(VERSION)'
	$(PKG_TOOL) sfo_setentry $@ ATTRIBUTE --type Integer --maxsize 4 --value 0
	$(PKG_TOOL) sfo_setentry $@ CATEGORY --type Utf8 --maxsize 4 --value 'gd'
	$(PKG_TOOL) sfo_setentry $@ CONTENT_ID --type Utf8 --maxsize 48 --value '$(CONTENT_ID)'
	$(PKG_TOOL) sfo_setentry $@ DOWNLOAD_DATA_SIZE --type Integer --maxsize 4 --value 0
	$(PKG_TOOL) sfo_setentry $@ SYSTEM_VER --type Integer --maxsize 4 --value 0
	$(PKG_TOOL) sfo_setentry $@ TITLE --type Utf8 --maxsize 128 --value '$(TITLE)'
	$(PKG_TOOL) sfo_setentry $@ TITLE_ID --type Utf8 --maxsize 12 --value '$(TITLE_ID)'
	$(PKG_TOOL) sfo_setentry $@ VERSION --type Utf8 --maxsize 8 --value '$(VERSION)'

$(STAGE_DIR)/sce_sys/about/right.sprx: | check-tools
	mkdir -p $(dir $@)
	cp $(TOOLCHAIN)/samples/font/sce_sys/about/right.sprx $@

$(STAGE_DIR)/sce_module/libc.prx: | check-tools
	mkdir -p $(dir $@)
	cp $(TOOLCHAIN)/samples/font/sce_module/libc.prx $@

$(STAGE_DIR)/sce_module/libSceFios2.prx: | check-tools
	mkdir -p $(dir $@)
	cp $(TOOLCHAIN)/samples/font/sce_module/libSceFios2.prx $@

$(STAGE_DIR)/OMARCHY-LICENSE.txt: $(OMARCHY_LICENSE)
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/WALLPAPER-SOURCES.md: WALLPAPER-SOURCES.md
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/PROTOTYPE.txt: ../docs/UI-PROTOTYPE.md
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/PRIVATE-BOOT.txt: ../docs/PRIVATE-BOOT.md
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/KERNEL-MANAGER.txt: ../docs/ARCHITECTURE.md
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/assets/misc/ps4-linux-loader.elf: $(PRIVATE_LOADER)
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/assets/misc/ps4-linux-loader.elf.sha256: $(PRIVATE_LOADER_SHA)
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/assets/misc/loader-provenance.json: $(PRIVATE_LOADER_PROVENANCE)
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/assets/misc/%: $(PRIVATE_BOOT_SET)/%
	mkdir -p $(dir $@)
	cp $< $@

$(STAGE_DIR)/assets/misc/internal-boot-set.json: $(PRIVATE_BOOT_PROVENANCE)
	mkdir -p $(dir $@)
	cp $< $@

ifeq ($(PROFILE),private-boot)
STAGED_PROFILE_INPUTS := \
	$(STAGE_DIR)/PRIVATE-BOOT.txt \
	$(STAGE_DIR)/assets/misc/ps4-linux-loader.elf \
	$(STAGE_DIR)/assets/misc/ps4-linux-loader.elf.sha256 \
	$(STAGE_DIR)/assets/misc/loader-provenance.json
else ifeq ($(PROFILE),private-kernel-manager)
STAGED_PROFILE_INPUTS := \
	$(STAGE_DIR)/KERNEL-MANAGER.txt \
	$(STAGE_DIR)/assets/misc/ps4-linux-loader.elf \
	$(STAGE_DIR)/assets/misc/ps4-linux-loader.elf.sha256 \
	$(STAGE_DIR)/assets/misc/loader-provenance.json \
	$(STAGE_DIR)/assets/misc/bzImage \
	$(STAGE_DIR)/assets/misc/initramfs.cpio.gz \
	$(STAGE_DIR)/assets/misc/bootargs.txt \
	$(STAGE_DIR)/assets/misc/vram.txt \
	$(STAGE_DIR)/assets/misc/release.json \
	$(STAGE_DIR)/assets/misc/internal-boot-set.json
else
STAGED_PROFILE_INPUTS := $(STAGE_DIR)/PROTOTYPE.txt
endif

STAGED_INPUTS := \
	$(STAGE_DIR)/eboot.bin \
	$(STAGED_WALLPAPERS) \
	$(STAGE_DIR)/assets/images/omarchy-header.png \
	$(STAGE_DIR)/assets/fonts/Gontserrat-Regular.ttf \
	$(STAGE_DIR)/assets/fonts/OFL.txt \
	$(STAGE_DIR)/sce_sys/icon0.png \
	$(STAGE_DIR)/sce_sys/save_data.png \
	$(STAGE_DIR)/sce_sys/param.sfo \
	$(STAGE_DIR)/sce_sys/about/right.sprx \
	$(STAGE_DIR)/sce_module/libc.prx \
	$(STAGE_DIR)/sce_module/libSceFios2.prx \
	$(STAGE_DIR)/OMARCHY-LICENSE.txt \
	$(STAGE_DIR)/WALLPAPER-SOURCES.md \
	$(STAGED_PROFILE_INPUTS)

$(GP4): $(STAGED_INPUTS)
	mkdir -p $(BUILD_DIR)
	cd $(STAGE_DIR) && $(CREATE_GP4) -out $(GP4) --content-id=$(CONTENT_ID) \
		--files "$$(find . -type f ! -name '*.gp4' | sed 's#^./##' | LC_ALL=C sort | tr '\n' ' ')"

$(PACKAGE): $(GP4)
	mkdir -p $(OUTPUT_DIR)
	$(PKG_TOOL) pkg_build $(GP4) $(OUTPUT_DIR)
	@test -f $@

audit: $(PACKAGE)
	$(PKG_TOOL) pkg_validate --verbose $(PACKAGE)
	rm -rf $(BUILD_DIR)/audit
	mkdir -p $(BUILD_DIR)/audit
	$(PKG_TOOL) pkg_extract --verbose $(PACKAGE) $(BUILD_DIR)/audit
ifeq ($(PROFILE),ui-only)
	@! find $(BUILD_DIR)/audit -type f | grep -Eiq '/(payloads?|bundle|kernel|initramfs|rootfs)(/|$$)'
	@! LC_ALL=C grep -aE '127[.]0[.]0[.]1|:9090|ps4-linux-loader[.]elf' $(STAGE_DIR)/eboot.bin
else ifeq ($(PROFILE),private-boot)
	@test -f $(BUILD_DIR)/audit/uroot/PRIVATE-BOOT.txt
	@test -f $(BUILD_DIR)/audit/uroot/assets/misc/loader-provenance.json
	@test "$$(stat -f %z $(BUILD_DIR)/audit/uroot/assets/misc/ps4-linux-loader.elf 2>/dev/null || stat -c %s $(BUILD_DIR)/audit/uroot/assets/misc/ps4-linux-loader.elf)" = "$(PRIVATE_LOADER_EXPECTED_SIZE)"
	@test "$$(shasum -a 256 $(BUILD_DIR)/audit/uroot/assets/misc/ps4-linux-loader.elf | awk '{print $$1}')" = "$(PRIVATE_LOADER_EXPECTED_SHA)"
	@LC_ALL=C grep -aqF '/app0/assets/misc/ps4-linux-loader.elf' $(STAGE_DIR)/eboot.bin
	@LC_ALL=C grep -aqF '127.0.0.1' $(STAGE_DIR)/eboot.bin
	@LC_ALL=C grep -aqF 'local port 9090' $(STAGE_DIR)/eboot.bin
	@! find $(BUILD_DIR)/audit -type f | grep -Eiq '/(bundle|kernel|initramfs|rootfs)(/|$$)'
else
	@test -f $(BUILD_DIR)/audit/uroot/KERNEL-MANAGER.txt
	@test -f $(BUILD_DIR)/audit/uroot/assets/misc/internal-boot-set.json
	@test "$$(stat -f %z $(BUILD_DIR)/audit/uroot/assets/misc/bzImage 2>/dev/null || stat -c %s $(BUILD_DIR)/audit/uroot/assets/misc/bzImage)" = 11060224
	@test "$$(shasum -a 256 $(BUILD_DIR)/audit/uroot/assets/misc/bzImage | awk '{print $$1}')" = b7c8b9d67c600ee08b2321f7f4fac08c506791b0ab9c3f3d01598a90471a9de5
	@test "$$(shasum -a 256 $(BUILD_DIR)/audit/uroot/assets/misc/initramfs.cpio.gz | awk '{print $$1}')" = 824530e22392376d5fc27994a9ccff97f0442b7a41681155f46e183f892365ae
	@test "$$(stat -f %z $(BUILD_DIR)/audit/uroot/assets/misc/bootargs.txt 2>/dev/null || stat -c %s $(BUILD_DIR)/audit/uroot/assets/misc/bootargs.txt)" = 502
	@test "$$(shasum -a 256 $(BUILD_DIR)/audit/uroot/assets/misc/bootargs.txt | awk '{print $$1}')" = 8064d91f286d4275dac08e2fae29e43fbf745ea7be15f797edbbd0e5036a4930
	@test "$$(shasum -a 256 $(BUILD_DIR)/audit/uroot/assets/misc/vram.txt | awk '{print $$1}')" = 4f71bb761ace37c88826cd8cc1c948e1cf5b5d0cd153dc651a6efdb3dfb9f2b1
	@LC_ALL=C grep -aqF '/data/linux/boot' $(STAGE_DIR)/eboot.bin
	@LC_ALL=C grep -aqF '.omarchy-ps4-staging' $(STAGE_DIR)/eboot.bin
	@LC_ALL=C grep -aqF '/app0/assets/misc/bzImage' $(STAGE_DIR)/eboot.bin
	@LC_ALL=C grep -aqF '127.0.0.1' $(STAGE_DIR)/eboot.bin
	@! find $(BUILD_DIR)/audit -type f | grep -Eiq '/rootfs(/|$$)'
endif
	@test "$$(find $(BUILD_DIR)/audit -path '*/assets/images/*' -type f -name '*.jpg' | wc -l | tr -d ' ')" = "17"
	@test "$$($(MAGICK) identify -format '%wx%h\n' $(STAGED_WALLPAPERS) | LC_ALL=C sort -u)" = "1920x1080"
	@test "$$($(MAGICK) identify -format '%wx%h' $(STAGE_DIR)/sce_sys/icon0.png)" = "512x512"
	@test "$$($(MAGICK) identify -format '%wx%h' $(STAGE_DIR)/sce_sys/save_data.png)" = "228x128"
	@! find $(BUILD_DIR)/audit -type f -name 'ps4-format-logo.*' | grep -q .
	@echo "$(PROFILE) package audit passed"

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(PACKAGE)
