# Omarchy PS4 preparation and installation

Status date: 2026-08-13

This is the single preparation path for the first supported target: PS4 Slim,
Baikal B1, firmware 12.02, external USB root. It records the intended product
flow and the commands available today. The native FPKG and release owner image
are not finished yet.

Developers can download the exact hardware-tested Baikal B1 `bzImage`, config
and checksums from the
[`v6.18.44-ps4-baikal-r1` kernel prerelease](https://github.com/meerzulee/linux-ps4/releases/tag/v6.18.44-ps4-baikal-r1).
That release is a kernel test artifact, not the unfinished Omarchy installer:
it intentionally contains no payload, initramfs or root filesystem.

## What the user needs

- a PS4 already supported by a firmware-appropriate jailbreak;
- GoldHEN with its local PayLoader available on port 9090;
- the Omarchy PS4 Manager FPKG;
- one USB drive of at least 16 GiB;
- HDMI display, keyboard and mouse for first setup;
- UART only for development and support capture.

The FPKG does not jailbreak the console and does not contain GoldHEN. Our lab
firmware 12.02 path has used Vue After v2 to load GoldHEN, but that is an
external prerequisite rather than an Omarchy PS4 component.

## Complete user journey

```text
Prepare USB once on a Linux computer
  -> 2 GiB FAT32 PS4BOOT + remaining ext4 OMARCHY-PS4
Install Omarchy PS4 Manager FPKG through GoldHEN
Launch the manager
  -> verify model, firmware, free space and embedded manifest
  -> copy kernel, installer initramfs, rootfs and profiles to PS4BOOT
  -> send the embedded PS4 Linux Loader ELF to 127.0.0.1:9090
Installer initramfs
  -> verify rootfs SHA-256
  -> resolve ext4 LABEL=OMARCHY-PS4
  -> prove the target is below USB in sysfs
  -> refuse a non-empty target; never format or touch internal SATA
  -> extract rootfs and activate the product boot profile
Linux first boot
  -> show the Omarchy owner TUI
  -> create username, password, hostname and timezone
  -> start the desktop
```

## Prepare the USB

This step destroys the selected USB. Run it on a Linux computer, not macOS;
ordinary macOS tools do not create ext4 filesystems.

Preview the exact target first:

```sh
sudo ./scripts/prepare-usb-linux --device /dev/sdX
```

After checking model, serial number and size in the preview:

```sh
sudo ./scripts/prepare-usb-linux --device /dev/sdX --apply
```

The script has no default device. It requires USB transport, rejects the
running root disk, requires an exact typed confirmation, and creates:

```text
partition 1  FAT32  2 GiB  PS4BOOT       boot and install bundle
partition 2  ext4   rest   OMARCHY-PS4   Linux root
```

The installer will not format the ext4 partition. This makes target selection
separate, visible and recoverable rather than hiding disk destruction behind
the FPKG's Launch button.

## Developer build preparation

OrbStack must be running and Docker context must be `orbstack`:

```sh
./scripts/build-initramfs-tools
./scripts/build-xfce-initramfs
./fpkg/tools/stage-offline-bundle --allow-development-rootfs
```

The last flag permits only the current private XFCE laboratory rootfs. A
release build must replace it with the Quattro image containing
`/var/lib/omarchy-ps4/provisioning/pending` and must not use that flag.

Until the native FPKG copy adapter exists, a developer can preview or stage the
same verified layout onto a mounted `PS4BOOT` partition:

```sh
./scripts/stage-fpkg-bundle-to-fat --mount /path/to/PS4BOOT
./scripts/stage-fpkg-bundle-to-fat --mount /path/to/PS4BOOT --apply
```

Running the `--apply` command against hardware is a hardware-state action and
therefore requires the project's bounded UART experiment procedure when it is
part of a PS4 test.

## Fast product boot

The product profile adds:

```text
libata.force=1.00:disable
```

AHCI is built into the PS4 kernel, so a module blacklist cannot disable it.
The selector disables only the failing internal HDD at ATA `1.00`; the Linux
root remains on USB. The previous boot spent roughly 95 seconds timing out on
that internal disk, so this is expected to remove that delay. It is still a
candidate until a bounded cold boot proves the disk is absent and the USB root
and optical path remain correct.

## Splash and diagnostics

The product profile omits `console=tty0` and starts a small framebuffer splash
from the installer initramfs. It reuses the exact pinned Quattro Plymouth logo
and Tokyo Night colors, but not the Plymouth daemon: the PS4 uses a custom
loader/initramfs path. The renderer waits for AMDGPU `/dev/fb0`, animates a
restrained progress line, periodically restores the frame if fbcon or a mode
transition overwrites it, and remains alive until the root is ready. UART stays
verbose throughout. A failed initramfs handoff leaves the logo up with an
Omarchy-red status line instead of falsely showing a completed green boot; use
the debug profile for visible HDMI error text.

Baikal earlycon remains active at `0xC890E000`, so kernel and installer evidence
continues flowing over UART even while HDMI shows the splash. If display or
boot fails, replace FAT-root `bootargs.txt` with
`/omarchy-ps4/bootargs-debug.txt`. The debug profile restores visible console
messages, retains full UART logging and does not disable SATA.

Splash acceptance and SATA-off acceptance are separate hardware experiments:
one variable per bounded UART session.

## Current release blockers

- rebuild the full Quattro rootfs with deferred-owner provisioning;
- implement the native OpenOrbis copy, verification and PayLoader adapters;
- sign the bundle manifest and validate signature failure/recovery;
- complete SATA-off, installer, splash, first-owner and cold-boot hardware
  acceptance;
- decide the PS4 Linux Loader redistribution policy before public upload.
