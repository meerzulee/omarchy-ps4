CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2
OUTPUT := ../output
HOST_PREVIEW := $(OUTPUT)/manager-host-preview

.PHONY: all preview test fpkg clean

all: test

$(HOST_PREVIEW): manager_state.cpp manager_state.hpp payload_transport.cpp payload_transport.hpp host_preview.cpp
	mkdir -p $(OUTPUT)
	$(CXX) $(CXXFLAGS) manager_state.cpp payload_transport.cpp host_preview.cpp -o $@

preview: $(HOST_PREVIEW)
	$(HOST_PREVIEW)

test: $(HOST_PREVIEW)
	$(HOST_PREVIEW) --self-test

# This target is deliberately honest until the native renderer/downloader and
# package metadata exist. It prevents a protocol mock from being called an FPKG.
fpkg:
	@test -n "$(OO_PS4_TOOLCHAIN)" || { echo "fpkg: OO_PS4_TOOLCHAIN is not set" >&2; exit 1; }
	@echo "fpkg: native OpenOrbis application is not implemented yet" >&2
	@exit 2

clean:
	rm -f $(HOST_PREVIEW)
