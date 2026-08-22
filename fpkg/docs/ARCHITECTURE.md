# FPKG kernel-manager architecture

## Product boundary

The product has two release artifacts with deliberately separate jobs:

```text
Omarchy PS4 FPKG
  -> controller-first manager UI
  -> signed kernel, initramfs, boot arguments and VRAM profile
  -> current/previous boot-set transaction in Orbis storage
  -> verified PS4 Linux loader handoff through GoldHEN

Omarchy PS4 USB image
  -> one full-device ext4 filesystem labelled OMARCHY-PS4
  -> complete, pinned Omarchy userspace
  -> PS4 kernel modules and firmware
  -> deferred-owner setup and first-boot storage expansion
```

Flashing the USB image is the Linux installation. The console application does
not download or extract a root filesystem, select a raw disk, format a USB
device, or edit Linux accounts. Linux owns the USB filesystem, owner password,
sudo, SSH, desktop and hardware drivers.

The FPKG manages only boot assets. It writes its exact verified boot set to the
loader's established Orbis path and then sends the pinned loader to GoldHEN.
This does not make the internal SATA disk a Linux block-device target: Orbis
reads the files before kexec and the Linux product profile disables the failing
Baikal SATA target.

## End-user boot chain

```text
Power on PS4
  -> start the firmware-appropriate exploit/HEN path
  -> GoldHEN is active with BinLoader enabled
  -> launch Omarchy PS4
  -> verify/stage the selected internal boot set
  -> select Boot Omarchy; use the bundled tested kernel and 1024 MB VRAM
  -> send the verified loader ELF to 127.0.0.1:9090
  -> loader reads /data/linux/boot
  -> kernel and initramfs start
  -> initramfs proves LABEL=OMARCHY-PS4 is a USB device
  -> mount the complete flashed Omarchy filesystem
  -> first boot expands ext4 and creates the owner
```

The PS4 cannot cold-boot Linux like a normal UEFI PC. Every cold boot starts in
Orbis and repeats the exploit/HEN and loader handoff. Restarting or shutting
down Linux does not create a persistent firmware boot entry.

## Package contents

The functional FPKG layout is:

```text
/app0/eboot.bin
/app0/assets/misc/bzImage
/app0/assets/misc/initramfs.cpio.gz
/app0/assets/misc/bootargs.txt
/app0/assets/misc/vram.txt
/app0/assets/images/...
/app0/keys/release-key.pub
/app0/manifest/release.json
/app0/manifest/release.json.sig
/app0/assets/misc/ps4-linux-loader.elf
/app0/provenance/...
```

The USB image and root filesystem are not bundled in the FPKG. This avoids
duplicating several gigabytes in Orbis application storage and keeps Linux
installation independent from console storage permissions.

Private v0.25 proved verified, transactional staging of the complete kernel
set, but its loopback multi-write handoff was rejected after GoldHEN consumed
only 51,200 bytes. v0.26 proved a send buffer large enough for the complete ELF
before connecting and one complete application write on hardware. v0.28
retains that transport, restores the persistent Baikal boot console needed to
observe USB-root/first-owner setup and removes duplicate review screens from
the two-action Home flow. It remains non-publishable and pending end-to-end
product acceptance while loader redistribution is unresolved. One bounded
Baikal B1 run has passed the complete FPKG-to-loader-to-USB-root boot path and
reached the Omarchy desktop after manual login; persistent autologin and
repeated cold-boot acceptance remain open.

## Internal boot-set transaction

PS4 Linux Loader v25 searches `/data/linux/boot` and then
`/user/system/boot`; a USB FAT boot directory has higher priority. The product
uses `/data/linux/boot` and the release USB image deliberately contains no
loader-visible FAT boot files.

The active names required by the loader are:

```text
/data/linux/boot/bzImage
/data/linux/boot/initramfs.cpio.gz
/data/linux/boot/bootargs.txt
/data/linux/boot/vram.txt
```

The manager never overwrites these files in place. For the complete set it:

1. verifies the `/app0` source length and SHA-256;
2. writes into the sibling `boot.omarchy-new` directory;
3. flushes and re-verifies all staged bytes;
4. records each transaction phase in `/data/linux/.omarchy-ps4-staging`;
5. retains the old complete directory as `boot.omarchy-prev`;
6. atomically renames the staged directory to the loader's active `boot` name;
7. verifies the complete active set against one signed release ID;
8. clears the transaction marker only after the set is complete.

The manager never sends the loader while the transaction marker is present or
the four active files do not match one manifest. After interruption, the next
launch either commits a fully matching new set or restores the complete
previous directory before attempting another stage.

The directory rename is atomic. Safety also comes from the
journal plus the rule that the manager is the only normal path to the loader.
A recovery action is always separate and confirmed.

## USB image

The release publishes one compressed raw filesystem image:

```text
omarchy-ps4-usb-4.0.0.img.xz
  -> ext4 filesystem over the whole image/device
  -> label OMARCHY-PS4
  -> no partition table
  -> no FAT PS4BOOT filesystem
  -> no kernel, initramfs or loader payload
```

Using a whole-device filesystem avoids a first-boot partition-table rewrite.
The same base image can be flashed to 32 GB, 64 GB or larger USB media. The
filesystem initially retains the image's build size; a guarded first-boot
service grows ext4 online to the physical device size.

The grow operation is allowed only when all of these are true:

- `/` resolves to a block device labelled `OMARCHY-PS4`;
- the sysfs ancestry contains USB;
- the root is the whole USB block device, not an internal partition;
- the filesystem type is ext4;
- the release image contains the pending first-boot marker;
- the recorded image layout is `whole-device-filesystem`;
- the physical device is not smaller than the image.

No partition editor is involved. The service runs `resize2fs` itself, records
success under `/var/lib/omarchy-ps4`, and then allows deferred-owner setup to
continue. The owner never runs a storage command.

Ext4 remains the private-beta filesystem because it has already booted on the
lab PS4 and the current kernel enables its POSIX ACL and security support.
Btrfs is a later image format after enabling its POSIX ACL option and proving
snapshots, rollback, expansion and power-loss behavior on hardware.

## State machine

```text
HOME
  +-- Install/Update -> PREFLIGHT -> RELEASE -> VERIFY_PACKAGE
  |                                      -> STAGE_INTERNAL -> HOME_READY
  +-- Boot Omarchy ----------------------------------------> PAYLOADER_CHECK
  +-- Recovery ------> VERIFY_INTERNAL -> RESTORE_PREVIOUS ----------> READY
  +-- Diagnostics ---> EXPORT

PAYLOADER_CHECK -> SEND_ELF -> KEXEC
```

The manager can report that the expected USB image is required, but Orbis does
not mount ext4 and cannot claim to have verified the Linux root. That proof
happens in the initramfs after kexec.

## Trust model

HTTPS protects transport but does not define release authority. The FPKG
embeds an Omarchy PS4 Ed25519 public key and verifies a detached signature over
the exact schema-2 manifest bytes. The manifest pins:

- compatible model, firmware and southbridge;
- loader source, version, size and SHA-256;
- every internal boot artifact's `/app0` path, active name, size and SHA-256;
- the USB image URL, compressed and uncompressed hashes and sizes;
- the full-device ext4 layout, root label and minimum USB capacity;
- the deferred-owner contract and 1024 MB VRAM profile.

The manager rejects unknown schemas, ambiguous hardware, incomplete sets,
hash mismatches and unintended downgrades. Boot assets remain outside Pacman;
their release signature is separate from the Linux package repository.

## Updates and recovery

Installing a higher-version FPKG with the same title identity updates the UI,
loader and candidate boot set. The new FPKG does not rewrite the USB root.
Internal staging retains one previous complete kernel set until the candidate
has passed the required boot acceptance count.

At app startup the manager classifies the internal set as missing, ready,
update-available, interrupted or blocked by comparing it with the exact set
bundled in the installed FPKG. Detection is automatic; writing remains an
explicit user-selected action. A PayLoader connection is not used as a
background health probe because opening it may consume the listener. GoldHEN
is checked only after the user selects Boot Omarchy.

Linux userland updates run inside Omarchy through signed, pinned PS4 release
snapshots. Kernel updates are coordinated releases: the FPKG carries the
kernel/initramfs while the USB release installs the matching modules and
firmware. A manifest mismatch blocks boot rather than combining arbitrary
versions.

Recovery can verify the current boot set, restore `boot.omarchy-prev`, or reinstall
the set carried by the FPKG. A damaged Linux root is recovered by reflashing a
USB or, later, by a separately designed filesystem snapshot flow. The manager
does not modify ext4 from Orbis.

## Splash, first owner and diagnostics

The product boot profile omits `console=tty0`. A static initramfs helper waits
for AMDGPU's framebuffer and paints the Omarchy mark. Baikal `earlycon` uses
`keep_bootcon` with `8250.nr_uarts=0`, preserving UART as the development
evidence channel through initramfs and systemd without putting boot text on
HDMI. The debug profile restores visible HDMI logs.

After storage verification and expansion,
`omarchy-ps4-provision-owner.service` owns tty1 before the display manager. It
asks for keyboard, username, password, hostname and timezone. It creates a
passworded sudo user and never enables SSH password login by default. An
interrupted setup leaves `pending` in place and resumes on the next Linux boot.

Diagnostics may include the active and previous boot-set hashes, transaction
state, FPKG version, loader provenance, USB root label and Linux-reported
filesystem size. Passwords, SSH private keys, network secrets and personal
files are never exported.

## Source and licensing

- Omarchy visual/runtime assets: MIT; preserve the upstream notice.
- Payload Guest is a GPL-3.0 design reference; copied implementation carries
  its source-delivery obligations.
- OpenOrbis PS4 Toolchain: GPL-3.0; follow its distribution terms.
- PS4 Linux Loader: no declared repository-wide license at the pinned commit;
  private test input only until redistribution is resolved.

Attribution does not replace redistribution permission. Public image and FPKG
artifacts remain blocked until every bundled binary, font, logo and wallpaper
has recorded provenance and rights.
