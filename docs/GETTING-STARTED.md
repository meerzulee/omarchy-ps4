# Omarchy PS4 installation

Status date: 2026-08-21

This is the target preparation path for the first private beta: a PS4 Slim
Baikal B1, an internal FPKG-managed kernel set, and one external USB containing
the complete Omarchy system. The architecture is frozen, the final USB image
and kernel-manager FPKG build and audit locally, and a physical USB flash has
passed full read-back verification. PS4 boot support is not accepted yet.

## What the user downloads

```text
omarchy-ps4.pkg
omarchy-ps4-usb-4.0.0.img.xz
SHA256SUMS
SHA256SUMS.sig
```

The FPKG contains the PS4 kernel, initramfs, boot configuration and loader. The
USB image contains the installed Linux system. No separate kernel, initramfs,
rootfs archive or package list is handled by the user.

Flashing the image is the Omarchy installation step. There is no second Linux
installer and the FPKG never copies the desktop onto the USB.

## What the user needs

- a supported PS4 with its firmware-appropriate jailbreak already completed;
- GoldHEN with BinLoader enabled;
- one 32 GB or larger USB device; 64 GB is recommended;
- a Windows, macOS or Linux computer with a validated image writer;
- HDMI display, controller and keyboard.

GoldHEN, the jailbreak and firmware are not distributed by Omarchy PS4.

## Flash the USB

1. Verify the downloaded checksums and release signature.
2. Connect the removable USB device to the computer.
3. Open balenaEtcher.
4. Select `omarchy-ps4-usb-4.0.0.img.xz`.
5. Select the USB by its model and capacity.
6. Flash and wait for validation to finish.
7. Safely eject the USB and connect it to the PS4.

Flashing overwrites the complete selected USB. The image is one ext4
filesystem labelled `OMARCHY-PS4`; it has no FAT partition and may appear
unreadable to Windows or macOS afterward. Cancel any offer to format it.

The same image works on 32 GB, 64 GB and larger devices. On first Linux boot,
Omarchy verifies that `/` is the expected whole USB device and expands ext4 to
its full size. The user does not run a resize command.

## Install and launch the FPKG

1. Start GoldHEN and enable BinLoader.
2. Install `omarchy-ps4.pkg` through the normal GoldHEN package workflow.
3. Launch **Omarchy PS4**.
4. Review the exact kernel, initramfs and 1024 MB VRAM profile.
5. Confirm **Prepare boot files**.
6. Wait for the internal current/previous transaction to reach **Ready**.
7. Select **Boot Omarchy** and confirm.

The manager writes only its verified boot set under `/data/linux/boot`, then
sends its pinned loader to GoldHEN. It does not format the USB, install the
Linux root, collect a password or give Linux access to internal SATA.

## First Linux boot

```text
Kernel and initramfs start
  -> resolve LABEL=OMARCHY-PS4
  -> prove sysfs USB ancestry and whole-device layout
  -> mount the preinstalled Omarchy root
  -> expand ext4 to the USB capacity
  -> ask for keyboard, username, password, hostname and timezone
  -> start the Omarchy desktop
```

Owner setup is resumable. The image contains no working default password and
SSH password login remains disabled. If setup is interrupted, launch the FPKG
and boot again; the pending owner flow resumes.

The PS4 does not expose a usable hardware RTC to this Linux build. The gift
image therefore enables `systemd-timesyncd` by default. An offline boot may
temporarily show a 1970 date; after NetworkManager connects, systemd obtains
network time and corrects the clock automatically. First-owner setup never
blocks on the network or asks the user to enter the date manually.

## Later boots

```text
Power on PS4
  -> start jailbreak/HEN
  -> launch Omarchy PS4
  -> Boot Omarchy
```

The PS4 does not have a normal UEFI Linux boot entry. A cold boot always starts
Orbis first.

## Recovery

Private v0.15 verifies the current internal boot set and automatically cleans
up or rolls back an interrupted staging transaction before retrying. The
visible manual verify, restore and diagnostic actions are deliberately marked
as unavailable in this beta; they do not execute yet. These paths never edit
the ext4 USB.

If the Omarchy root is damaged, reflash a USB image or use a future
Linux-side snapshot recovery flow. Reinstalling the FPKG repairs boot assets,
not personal files on the USB.

## Developer-only USB formatting

End users flash the release image. `scripts/prepare-usb-linux` exists only for
developers who need a blank full-device ext4 target for image/rootfs work:

```sh
sudo ./scripts/prepare-usb-linux --device /dev/sdX
sudo ./scripts/prepare-usb-linux --device /dev/sdX --apply
```

The script requires an explicit whole USB device, rejects the running root
disk, inventories the model/serial/capacity and requires the literal wipe
confirmation. It creates no partition table and formats the whole device as
ext4 label `OMARCHY-PS4`. It does not install Omarchy.

## Development build boundary

Private v0.15 implements the final split locally: the FPKG contains the exact
boot set and stages it transactionally to internal app data, while the separate
USB image contains the complete Omarchy root. The native build verifies every
boot artifact before reaching Ready and keeps loader handoff behind a separate
confirmation. It has not yet passed bounded PS4 hardware acceptance.

Before any console-side staging or boot test, follow
[`DEVELOPMENT-MODE.md`](DEVELOPMENT-MODE.md): one experiment ID, continuous
UART, one changed variable, explicit operator action, exact evidence and a
recorded rollback.

## Current blockers

- exercise whole-device ext4 expansion from the verified image on PS4 Linux;
- test FPKG over-install and recovery without touching unrelated `/data`;
- complete separate bounded hardware acceptance for staging, boot, growth,
  owner setup and repeated cold boots;
- resolve PS4 Linux Loader and visual-asset redistribution before publication.
