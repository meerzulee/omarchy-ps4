TITLE := Omarchy PS4 UI Prototype
VERSION := 0.10
TITLE_ID := BREW09004
CONTENT_ID := IV0000-BREW09004_00-OMARCHYPS4UI0000

TOOLCHAIN := $(OO_PS4_TOOLCHAIN)
REPO_ROOT := $(abspath ../..)
BUILD_DIR := $(CURDIR)/build
OBJECT_DIR := $(BUILD_DIR)/obj
STAGE_DIR := $(BUILD_DIR)/stage
OUTPUT_DIR ?= $(REPO_ROOT)/output/fpkg-ui-prototype
PACKAGE := $(OUTPUT_DIR)/$(CONTENT_ID).pkg
GP4 := $(STAGE_DIR)/package.gp4

OMARCHY_PIN := $(REPO_ROOT)/cache/omarchy-quattro
OMARCHY_LOGO := $(OMARCHY_PIN)/default/plymouth/logo.png
OMARCHY_WALLPAPER := $(OMARCHY_PIN)/themes/tokyo-night/backgrounds/2-swirl-buck.jpg

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
	-isystem $(TOOLCHAIN)/include -isystem $(TOOLCHAIN)/include/c++/v1
LIBS := -lc -lkernel -lc++ -lSceVideoOut -lSceSysmodule -lSceFreeType \
	-lScePad -lSceUserService
LDFLAGS := -m elf_x86_64 -pie --script $(TOOLCHAIN)/link.x --eh-frame-hdr \
	-L$(TOOLCHAIN)/lib $(LIBS) $(TOOLCHAIN)/lib/crt1.o

.PHONY: all fpkg audit clean check-tools

all: fpkg

fpkg: $(PACKAGE)

check-tools:
	@test -n "$(TOOLCHAIN)" || { echo "OO_PS4_TOOLCHAIN is not set" >&2; exit 1; }
	@test -x "$(CXX)" || { echo "C++ compiler not found: $(CXX)" >&2; exit 1; }
	@test -x "$(LD)" || { echo "LLD linker not found: $(LD)" >&2; exit 1; }
	@test -x "$(PKG_TOOL)" || { echo "PkgTool.Core not found: $(PKG_TOOL)" >&2; exit 1; }
	@test -x "$(CREATE_GP4)" || { echo "create-gp4 not found: $(CREATE_GP4)" >&2; exit 1; }
	@test -x "$(FSELF)" || { echo "create-fself not found: $(FSELF)" >&2; exit 1; }
	@test -f "$(OMARCHY_LOGO)" || { echo "Pinned Omarchy logo missing" >&2; exit 1; }
	@test -f "$(OMARCHY_WALLPAPER)" || { echo "Pinned Tokyo Night wallpaper missing" >&2; exit 1; }
	@command -v $(MAGICK) >/dev/null || { echo "ImageMagick is required" >&2; exit 1; }

$(OBJECT_DIR)/main.o: main.cpp | check-tools
	mkdir -p $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR)/prototype.elf: $(OBJECT_DIR)/main.o
	$(LD) $< -o $@ $(LDFLAGS)

$(STAGE_DIR)/eboot.bin: $(BUILD_DIR)/prototype.elf
	mkdir -p $(STAGE_DIR)
	$(FSELF) -in=$< -out=$(BUILD_DIR)/prototype.oelf --eboot $@ --paid 0x3800000000000011

$(STAGE_DIR)/assets/images/background.png: $(OMARCHY_WALLPAPER) | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) $< -resize '1920x1080^' -gravity center -extent 1920x1080 \
		-fill 'rgba(14,14,20,0.78)' -draw 'rectangle 0,0 1920,1080' \
		-alpha off -type TrueColor PNG24:$@

$(STAGE_DIR)/assets/images/omarchy-header.png: $(OMARCHY_LOGO) | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) -size 270x64 xc:'#13141c' \( $< -resize 260x61 \) \
		-gravity center -composite -alpha off -type TrueColor PNG24:$@

$(STAGE_DIR)/assets/fonts/Gontserrat-Regular.ttf: | check-tools
	mkdir -p $(dir $@)
	cp $(TOOLCHAIN)/samples/font/assets/fonts/Gontserrat-Regular.ttf $@
	cp $(TOOLCHAIN)/samples/font/assets/fonts/OFL.txt $(dir $@)/OFL.txt

$(STAGE_DIR)/sce_sys/icon0.png: $(OMARCHY_LOGO) | check-tools
	mkdir -p $(dir $@)
	$(MAGICK) -size 512x512 xc:'#13141c' \( $< -resize 420x \) \
		-gravity center -geometry +0-18 -composite -fill '#7aa2f7' \
		-draw 'rectangle 0,466 512,512' -alpha off -type TrueColor PNG24:$@

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
	cp $(TOOLCHAIN)/samples/font/sce_module/libSceFios2.prx $(dir $@)/libSceFios2.prx

$(STAGE_DIR)/PROTOTYPE.txt: ../docs/UI-PROTOTYPE.md
	mkdir -p $(dir $@)
	cp $< $@

STAGED_INPUTS := \
	$(STAGE_DIR)/eboot.bin \
	$(STAGE_DIR)/assets/images/background.png \
	$(STAGE_DIR)/assets/images/omarchy-header.png \
	$(STAGE_DIR)/assets/fonts/Gontserrat-Regular.ttf \
	$(STAGE_DIR)/sce_sys/icon0.png \
	$(STAGE_DIR)/sce_sys/param.sfo \
	$(STAGE_DIR)/sce_sys/about/right.sprx \
	$(STAGE_DIR)/sce_module/libc.prx \
	$(STAGE_DIR)/PROTOTYPE.txt

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
	@! find $(BUILD_DIR)/audit -type f | grep -Eiq '/(payloads?|bundle|kernel|initramfs|rootfs)(/|$$)'
	@! LC_ALL=C grep -aE '127[.]0[.]0[.]1|:9090|ps4-linux-loader[.]elf' $(STAGE_DIR)/eboot.bin
	@echo "UI-only package audit passed"

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(PACKAGE)
