# Omarchy PS4 Manager FPKG requirements

Status date: 2026-08-21. These are living requirements for the private beta.
The one-partition USB plus internal kernel-manager design is now the target;
it is not yet a hardware-supported release.

## Product in one sentence

Install one FPKG, flash one Omarchy USB image, then launch one controller-first
application whenever the user wants to boot Linux.

The FPKG is a kernel, initramfs and loader manager. The USB is the complete
Omarchy installation. GoldHEN is a prerequisite; this project does not
jailbreak the console or distribute GoldHEN.

## System design

```text
Firmware-appropriate exploit/HEN
  -> GoldHEN
       -> install and launch the Omarchy PS4 FPKG
       -> provide local BinLoader on 127.0.0.1:9090

Omarchy PS4 FPKG
  -> verify one signed release manifest
  -> stage kernel/initramfs/bootargs/VRAM under /data/linux/boot
  -> retain the previous verified boot set
  -> boot immediately when the user activates Boot Omarchy
  -> send the exact embedded PS4 Linux loader to GoldHEN

PS4 Linux loader
  -> read the internal Orbis boot set
  -> start the selected kernel and initramfs

Linux initramfs
  -> resolve LABEL=OMARCHY-PS4
  -> prove it is the external USB root
  -> mount the complete preinstalled Omarchy image
  -> allow guarded first-boot expansion and owner setup
```

The FPKG may write only its declared boot-set directory in Orbis storage. It
must never expose internal SATA as a Linux installation target or let Linux
mount it in the supported Baikal profile.

## Release deliverables

Every release provides:

```text
omarchy-ps4.pkg
omarchy-ps4-usb-4.0.0.img.xz
SHA256SUMS
SHA256SUMS.sig
FLASHING.md
```

The FPKG contains the UI, release public key, manifest, kernel, initramfs,
boot arguments, 1024 MB VRAM profile and pinned PS4 Linux loader. It does not
contain the Omarchy root filesystem.

The compressed USB image contains the complete pinned Omarchy userspace,
matching PS4 modules and firmware, recovery desktop, first-owner setup and
storage-expansion service. It contains no loader-facing boot files.

## First supported configuration

The first private beta targets only the configuration with recorded hardware
evidence:

- PS4 Slim in the CUH-2xxx family;
- Baikal B1 southbridge;
- lab firmware 12.02 path with the recorded compatible HEN/GoldHEN build;
- `linux-ps4` kernel `6.18.44-ps4-baikal`;
- 1024 MB VRAM;
- 1920x1080 at 60 Hz;
- internal Orbis boot files at `/data/linux/boot`;
- one external whole-device ext4 filesystem labelled `OMARCHY-PS4`;
- Omarchy 4.0 as the normal desktop and XFCE as recovery.

Another console model, southbridge, firmware, filesystem or VRAM profile
requires its own compatibility entry and bounded hardware acceptance. This is
a private beta target, not a universal PS4 compatibility claim.

## What the user needs

- A compatible jailbroken PS4 with GoldHEN active.
- GoldHEN BinLoader enabled.
- The Omarchy PS4 FPKG installed through the normal package workflow.
- One 32 GB or larger USB device; 64 GB is recommended.
- A Windows, macOS or Linux computer for flashing the image.
- A display and controller; a keyboard is required for first-owner setup.

The normal preparation flow is graphical:

1. Download the signed `.img.xz` release.
2. Open balenaEtcher or another validated raw-image writer.
3. Select the downloaded image and the removable USB device.
4. Flash and complete read-back verification.
5. Safely eject the USB and attach it to the PS4.

The image is an ext4 filesystem over the entire device. Windows or macOS may
offer to format it after flashing; the user must cancel that prompt. There is
no FAT partition and the user never runs `parted`, `resize2fs` or a terminal
installation command.

## What GoldHEN gives us

| GoldHEN capability | Omarchy PS4 use |
|---|---|
| Homebrew Enabler and Debug Settings | Install and run the FPKG. |
| BinLoader on port `9090` | Receive only the verified loader ELF selected by the manager. |
| Internal package installation from `/data/pkg` | Convenient private-beta FPKG delivery; never a Linux root target. |
| Remote Package Install | Optional development and later manager-update delivery. |
| FTP server on port `2121` | Development-only transfer and inspection; not an end-user requirement and not FTPS. |
| UART enabler | Optional development aid; it does not replace the project's continuous external UART capture. |
| Klog server on port `3232` | Optional diagnostic input, not a boot dependency. |

GoldHEN does not provide the firmware exploit, PS4 Linux loader, patched
kernel, initramfs, Omarchy USB image, release signatures, rollback policy,
Linux password, sudo configuration or SSH policy.

BinLoader accepts privileged payloads and therefore is not an arbitrary file
browser in this product. The manager sends only the pinned loader whose exact
digest belongs to the signed release.

## Internal boot-set requirements

The loader-visible active files are:

```text
/data/linux/boot/bzImage
/data/linux/boot/initramfs.cpio.gz
/data/linux/boot/bootargs.txt
/data/linux/boot/vram.txt
```

The manager must:

- validate schema 2 with its embedded Ed25519 release key;
- verify every `/app0` source file's exact length and SHA-256;
- write only inside the temporary `boot.omarchy-new` directory during staging;
- flush and re-verify temporary files before activation;
- write `/data/linux/.omarchy-ps4-staging` before changing the active directory;
- retain the prior complete directory as `boot.omarchy-prev`;
- verify the complete active set before clearing the transaction marker;
- refuse to send the loader during an incomplete transaction;
- recover a completed candidate or restore the previous set after interruption;
- never accept a boot set assembled from different release IDs.

Initial installation, FPKG upgrade, kernel update and recovery use the same
transaction primitive. The active boot path is not user-configurable in the
first beta.

## USB-image requirements

The image contract is:

```text
layout                whole-device-filesystem
filesystem            ext4
label                  OMARCHY-PS4
boot files             none
owner                   deferred until first Linux boot
minimum target          32,000,000,000 bytes
recommended target      64 GB or larger
```

The image builder must preserve numeric ownership, permissions, symlinks,
POSIX ACLs, security xattrs and file capabilities. It must refuse a release
image that contains a default password, enabled SSH password login,
passwordless recovery backdoor, cloned machine identity, signing key or
production secret.

The release manifest pins compressed and uncompressed image sizes and hashes.
A public flashing guide must tell users that the complete target USB is
overwritten and must tell them how to identify it by model and capacity.

## Automatic first-boot expansion

The user does not resize anything. The image includes a one-shot service that
runs before owner provisioning and grows ext4 online to the physical USB size.

The service must refuse to run unless:

- `/` resolves to a block device;
- its label is exactly `OMARCHY-PS4`;
- its filesystem is ext4;
- its sysfs ancestry is USB;
- the filesystem occupies the whole block device rather than a partition;
- the image records `layout=whole-device-filesystem`;
- first-owner provisioning is still pending;
- the backing device is at least as large as the flashed image.

It records the before and after byte counts, invokes `resize2fs` without
partition-table manipulation, syncs, and writes a completion marker only after
the expanded size is verified. A failure stops owner provisioning and presents
a recoverable error; it never selects another disk.

## Application screens

### Home

Home is state-derived:

- **Install / update boot files** is the first action and reflects whether the
  bundled set is missing, outdated or already installed;
- the single hardware-accepted kernel is selected automatically and shown in
  System Check; kernel selection returns only when multiple kernels pass
  hardware acceptance;
- **Boot Omarchy** is the primary action once the internal set is verified;
- **Options** opens Appearance without adding a fourth job to the main flow.

The screen uses the accepted wide console layout: workflow and primary action
on the left, compact system-check cards on the right, and the released Quattro
wallpaper behind both. It has no persistent bottom bar.

The app may say “Insert the flashed Omarchy USB,” but cannot claim to verify
ext4 from Orbis. Linux performs that verification after kexec.

### Actions and progress

Home and progress show:

- exact Omarchy and kernel release;
- detected console compatibility tuple;
- internal boot-set destination;
- external `OMARCHY-PS4` root expectation;
- 1024 MB VRAM;
- whether the previous boot set is retained;
- an explicit statement that Linux will not use internal SATA.

Moving focus never starts an action. Cross activates the focused action once;
there is no duplicate review/confirmation page for Install, Update or Boot.
Back cancels or returns. Progress reports real bytes and phases and identifies
whether cancellation is safe. Destructive recovery remains separately
reviewed and confirmed.

Staging returns to Home with **Boot Omarchy** first and focused.

### Recovery and diagnostics

Recovery diagnoses first, then separately offers:

- verify the active internal boot set;
- restore the complete `boot.omarchy-prev` directory;
- reinstall the boot set carried by the FPKG;
- clear only an invalid, recoverable staging transaction;
- export a sanitized support bundle to removable FAT media supplied
  specifically for diagnostics.

The Omarchy root USB is ext4 and is never edited by the Orbis application.
A damaged root is recovered by reflashing or by a future Linux-side snapshot
design.

### Credits and licenses

Show exact versions, commits, hashes, source links and licenses for the
manager, Omarchy, kernel, loader, font and visual assets. A component with
unresolved redistribution rights cannot enter a public artifact.

## Main flows

### First installation

1. User flashes the complete Omarchy USB image on a computer.
2. User installs the matching FPKG through GoldHEN.
3. Manager detects the supported console tuple and BinLoader readiness.
4. Manager verifies its signed release and embedded boot artifacts.
5. User selects Install boot files once.
6. Manager completes the journalled stage and returns Home with Boot first.
7. User selects Boot Omarchy once; the tested kernel and VRAM profile are
   automatic.
8. Manager sends the verified loader.
9. Initramfs proves `OMARCHY-PS4` is an external whole-device USB filesystem.
10. Linux expands ext4 automatically and runs owner setup.
11. User enters keyboard, username, password, hostname and timezone.
12. Linux starts the Omarchy desktop.

### Normal boot

1. Verify the signed manifest, active boot set and compatibility tuple.
2. Refuse an incomplete, unknown, mixed or corrupted set.
3. Check GoldHEN BinLoader.
4. Use the displayed tested release and 1024 MB VRAM profile automatically.
5. Send the pinned loader without another review screen.
6. Let initramfs resolve and verify the external root.

If GoldHEN is absent, explain the prerequisite and return to Home. The FPKG
does not attempt a jailbreak.

### Updates

Manager updates install a higher-version FPKG with the same title identity.
The candidate kernel set is staged only after the user activates Update boot
files, and the previous set is retained.

Linux userland updates use signed, pinned Omarchy PS4 snapshots from inside
Linux. There are no automatic rolling-Arch updates. Kernel and userspace
releases must declare compatible module/firmware versions in the same signed
release contract.

There are no silent updates and no unattended downgrade.

## Safety requirements

These are release blockers:

- Never format, repartition or mount a raw disk from Orbis.
- Never let Linux use the internal Baikal SATA target in the supported profile.
- Never write outside the declared internal boot directory and app SaveData.
- Never overwrite an active boot artifact in place.
- Never send the loader while a transaction is incomplete.
- Never delete the previous verified set during candidate staging.
- Never select a Linux root by guessed `/dev/sdX` name.
- Never let Orbis mount or edit ext4.
- Never collect or store the Linux password in Orbis.
- Never ship a default password, private signing key, SSH private key, Wi-Fi
  secret or production token.
- Never auto-chain staging, update or recovery into Boot.
- Never claim compatibility without recorded hardware evidence.

## Package profiles

### UI-only

Contains presentation and user-scoped appearance preferences only. It performs
no system action.

### Private loader-only v0.14

Contains and verifies the pinned loader and sends it through GoldHEN. It
requires an already prepared legacy two-partition USB and is superseded as the
target architecture, but remains useful historical evidence.

### Private kernel-manager v0.28 beta candidate

Contains the loader plus the exact kernel, initramfs, boot arguments, VRAM file
and schema-2 manifest. It stages `/data/linux/boot` and boots a separately
flashed one-filesystem USB. Its local PayLoader adapter must queue the complete
ELF and use one application write; it must never retry a partial write. It
contains no rootfs or package snapshot. The internal-root boot profile must
retain the Baikal boot console through initramfs and systemd without enabling
visible HDMI boot text.

### Public release — later

Uses only redistributable assets, a production release key and signed release
metadata. Public publication remains a separate owner-approved action.

## Diagnostics

Record and display, under Details where appropriate:

- manager title ID and version;
- detected GoldHEN/BinLoader readiness;
- PS4 model, firmware and southbridge;
- release ID, sequence, kernel and VRAM profile;
- active, previous and candidate boot-set hashes;
- transaction state and last human-readable error;
- Linux-reported root label, filesystem, device size and expanded size after a
  successful boot;
- source commits and license provenance.

Do not export passwords, tokens, private keys, Wi-Fi configuration, personal
files or raw unreviewed UART logs.

## Explicit non-goals for the first beta

- Jailbreaking the PS4 or bundling GoldHEN.
- Direct firmware/UEFI-style USB boot.
- Installing Linux onto internal PS4 storage.
- Formatting storage from the FPKG.
- A FAT `PS4BOOT` partition on the release USB.
- Btrfs/Snapper until its kernel ACL and hardware gates pass.
- Silent self-updates or live rolling-Arch updates.
- Linux suspend, hibernate or rest-mode claims.
- Automatic root-filesystem repair from Orbis.

## Implementation order

1. Freeze this schema-2 storage and trust contract.
2. Build and locally test the whole-device ext4 USB image generator.
3. Add and test automatic full-device ext4 expansion before owner setup.
4. Add verified internal boot-set staging and interruption recovery to a new
   private FPKG profile.
5. Update the native UI to show internal boot state instead of `PS4BOOT`.
6. Test the FPKG and USB image independently in OrbStack where possible.
7. Run one bounded UART experiment for internal boot staging only.
8. Close and review that evidence before a separate bounded boot experiment.
9. Prove first expansion and owner setup on disposable USB media.
10. Run the required repeated cold-boot and rollback acceptance count.

## Acceptance gates

Before the private kernel-manager beta is called ready:

- manifest positive and negative tests pass;
- the extracted FPKG contains exactly the pinned loader and four boot files;
- interrupted internal staging never leads to loader execution;
- restore recovers the complete previous boot set;
- the raw USB image passes filesystem, ownership, ACL, xattr, capability,
  account and secret audits;
- 32 GB and 64 GB media both expand without user commands;
- initramfs rejects a same-label non-USB or partitioned target;
- first-owner setup resumes after interruption;
- XFCE recovery and Omarchy normal sessions remain usable;
- all hardware actions have completed UART sessions and operator observations;
- loader, fonts, logos, wallpapers and binaries have recorded redistribution
  permission before any public build.

## Current state

- The Baikal 6.18 kernel, external ext4 root, XFCE recovery and Omarchy desktop
  have each run on the lab console.
- Private v0.14 verifies and sends the embedded loader only.
- Stable Omarchy 4.0 package and gift-development inputs exist locally, but the
  final clean owner image has not been built or accepted end to end.
- Internal boot-set staging, whole-device image generation, automatic growth
  and the schema-2 native UI remain implementation candidates until their
  local tests and bounded hardware experiments pass.
- Loader and some visual-asset redistribution rights remain unresolved.
