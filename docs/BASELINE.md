# Known-good XFCE baseline

This records existing evidence from the sibling `linux-ps4` project. It is not
yet a fresh reproduction performed by this repository.

## Hardware and boot environment

| Field | Recorded value |
|---|---|
| Console | PS4 Slim, CUH-2xxx family |
| Southbridge | Baikal B1, CXD90036G, subsystem `0x30201` |
| Firmware | 12.02 |
| Homebrew environment | HEN 12.02, GoldHEN v2.4b18.5 |
| Boot medium | USB, FAT32 boot partition plus ext4 root filesystem |
| VRAM reservation | 1 GB |

## Known-good kernel

| Field | Recorded value |
|---|---|
| Kernel | Linux 5.4.247 Baikal |
| Release | `5.4.247-DFAUS-mt_hdmia_nilgpureg-g3070025bad39-dirty` |
| Source | `feeRnt/ps4-linux-12xx`, branch `ps4-linux-5.4.247-baikal-dfaus` |
| Commit | `3070025bad39` |
| Kernel image | 8.7 MB `bzImage` |
| Initramfs | 2.4 MB, BusyBox, EDID, MT7668 and Marvell firmware |

The preserved local artifacts currently live under
`../linux-ps4/dist/attempt-001/`. They are intentionally not copied into this
Git repository. Exact sizes and SHA-256 digests are recorded in
`../manifests/xfce-baikal-baseline.toml`.

## Root filesystem

| Field | Recorded value |
|---|---|
| Distribution | Arch Linux x86-64 |
| Desktop | XFCE 4.20 |
| Display manager | LightDM with development autologin |
| Display path | Xorg modesetting driver |
| Packages | 494 |
| Compressed rootfs | approximately 1.0 GB |
| Uncompressed rootfs | approximately 2.4 GB before filesystem expansion |

## Recorded results

| Capability | Result | Evidence quality |
|---|---|---|
| Kernel/initramfs/systemd boot | Passed | Real hardware |
| HDMI display | 1920x1080 at 60 Hz | Real hardware |
| XFCE session | Passed | Real hardware |
| Xorg modesetting driver | Passed | Real hardware |
| MT7668 Wi-Fi | Passed | Real hardware |
| SSH over Wi-Fi | Passed | Real hardware |
| Pacman/mirror access | Passed | Real hardware |
| Root filesystem expansion | Passed, 4 GB to 113 GB | Real hardware |
| Ethernet | Not working on Baikal | Real hardware/known kernel gap |
| HDMI audio | Not yet proven end-to-end on this baseline | Missing test |
| Bluetooth | Not yet proven | Missing test |
| DualShock 4 | Not yet proven | Missing test |
| OpenGL/EGL acceleration | Not yet measured | Missing test |
| Vulkan | Not yet measured | Missing test |
| Suspend/hibernate | Excluded until explicitly validated | Safety policy |

## Known baseline issues to fix during reproduction

- Historical documentation disagrees about USB device names and partition
  numbers. The initramfs must discover the root filesystem by label or UUID.
- The development image contains known default passwords and autologin. Those
  settings are not acceptable for a distributable image.
- The rootfs was produced from Arch's rolling repositories without a recorded
  package lock, so an identical rebuild is not currently guaranteed.
- GPU acceleration was inferred from desktop output but never measured with a
  recorded EGL/OpenGL/Vulkan probe.
- Audio, Bluetooth, controller input, clean shutdown, and repeated cold boots
  still need structured acceptance tests.
