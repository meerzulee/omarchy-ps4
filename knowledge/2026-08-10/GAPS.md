# Gaps and next investigations

Snapshot date: 2026-08-10

These are ordered by dependency, not novelty.

## 1. Reproduce the control system

The clean XFCE rootfs exists but has not booted on PS4 hardware. Two cold boots,
complete evidence capture, and a verified rollback are the next gate. No modern
kernel or Wayland experiment should replace this step.

## 2. Establish a modern Baikal kernel baseline

Pin `rmuxnet/linux` branch `baikal/7.0.8-Stable` at `d8cbb8e9`, build kernel
and matching modules from source, and test it with the unchanged XFCE rootfs.
This isolates kernel changes from Mesa and desktop changes.

Required observations: boot time, USB stability, rootfs mounting, HDMI mode,
GPU initialization/reset, MT7668 Wi-Fi and Bluetooth, SATA enumeration, audio,
fan/thermal readings, shutdown, and regression to the 5.4 baseline.

## 3. Own the graphics compatibility set

The existing Arch repository proves that current-ish Mesa can be patched for
Liverpool/Gladius, but it is not a product-quality dependency boundary.

We still need:

- exact source and patch commits for Mesa, libdrm, 32-bit variants, and Xorg;
- reproducible package builds;
- a record of required LLVM and kernel UAPI versions;
- signing and a repository key lifecycle;
- an update preflight that refuses partial graphics upgrades;
- EGL/OpenGL, Vulkan, video decode, and long-running stability tests.

## 4. Prove Wayland before Hyprland

No public PS4 Hyprland or Quickshell implementation was found. The first
Wayland experiment must therefore be intentionally small: one compositor, one
native client, keyboard/mouse input, correct HDMI mode, clean exit, and logs.

Only after that passes do we test bare Hyprland, followed by UWSM, portals,
PipeWire, Quickshell, and Omarchy configuration in that order.

## 5. Close desktop input and media gaps

XFCE does not yet have recorded end-to-end tests for HDMI audio, Bluetooth,
DualShock 4 over USB/Bluetooth, controller reconnection, or PipeWire recovery.
RetroBox's DS4 configuration is a useful UX reference, not proof for our stack.

## 6. Treat Baikal Ethernet as an engineering project

The public DWMAC work has identified the MAC and PHY and can create an
interface, but TX/RX is unverified and enabling it breaks Wi-Fi. Keep Wi-Fi as
the supported network path while the DMA/BAR/interrupt behavior is isolated.

## 7. Define the boot and recovery product

The loader can discover firmware/southbridge and load boot assets from USB or
Orbis storage, but the complete user journey is not owned by one project.

Missing product pieces include:

- exact exploit/homebrew provenance for our 12.02 path;
- licensed, pinned loader inputs;
- signed A/B kernel and initramfs assets;
- last-known-good selection and failed-boot recovery;
- a safe external-drive installer with exact-target confirmation;
- useful error reporting without requiring UART or SSH.

## 8. Resolve redistribution questions early

Before public artifacts, audit the loader's absent root license, graphics patch
licensing, proprietary GPU/Wi-Fi firmware, Orbis-extracted material, and every
prebuilt binary in the initramfs. “Available on GitHub” is not redistribution
permission.

## Deferred by design

- Baikal internal installation
- suspend and hibernate
- unattended kernel or graphics upgrades
- one-image support for every PS4 revision
- the full Omarchy workstation application set
- performance tuning before correctness and recovery are proven
