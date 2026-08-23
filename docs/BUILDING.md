# Building Omarchy PS4

This document describes the current private Baikal B1 build: what is built,
where every input comes from, how the FPKG and USB system are assembled, and
which PS4-specific changes are applied to upstream Omarchy.

The result is **two matching artifacts**, not one installer:

1. an OpenOrbis FPKG containing the manager, PS4 Linux loader, kernel,
   initramfs, boot arguments and 1024 MB VRAM profile;
2. a compressed whole-device ext4 image containing the complete Omarchy Linux
   system and the matching kernel modules.

Flashing the USB image is the Linux installation. The FPKG never formats the
USB or carries the multi-gigabyte Linux root filesystem.

Status: public development beta. The build is reproducible enough for the
current lab workflow. Loader and wallpaper redistribution rights were confirmed
by the project owner on 2026-08-24, so v0.31 is published publicly. Release
signing and repeated hardware acceptance remain unresolved, so published
packages are unsigned development betas rather than production releases.

## Build graph

```text
linux-ps4-kernel
  -> bzImage + modules archive + checksums
                              \
pinned Omarchy 4.0.0           +-> owner-ready rootfs.tar.zst
  -> three PS4 packages        |       -> whole-device USB .img.xz
  -> locked offline snapshot --/

PS4 firmware initramfs seed
  -> PS4 USB initramfs -----------\
PS4 Linux Loader v25 --------------+-> OpenOrbis kernel-manager FPKG
bzImage + bootargs + VRAM ----------/

FPKG + USB image + manifests + SHA256SUMS
  -> one coordinated private beta release
```

The FPKG kernel and the modules inside the USB root must be from the same
kernel release. Do not replace one independently.

## Current pins

The source files are authoritative when a value below changes:

| Input | Current pin | Authority |
| --- | --- | --- |
| Omarchy | `4.0.0`, commit `f0020448ca87329199de7cb12f2015ebc4a3e5e7` | `upstream/omarchy.lock` |
| Omarchy packages | commit `bb66b9dafc2eaa10cde9280e0094aed9382b9b0b` | `upstream/omarchy.lock` |
| Arch package snapshot | `2026/08/20` | `scripts/build-package-snapshot` |
| Arch build container | immutable SHA-256 image digest | package/rootfs build scripts |
| PS4 kernel | `6.18.44-ps4-baikal` | `linux-ps4-kernel/` |
| OpenOrbis | `v0.5.4` archive plus SHA-256 | `fpkg/tools/build-ui-prototype` |
| PS4 Linux Loader | v25, 320,936 bytes, pinned SHA-256 | `fpkg/tools/vendor-loader` |
| FPKG title identity | `OMCH42069` | `fpkg/ui-prototype/Makefile` |
| Root filesystem | whole-device ext4, label `OMARCHY-PS4` | `scripts/build-usb-image` |

The Omarchy source checkout may report `4.0.0.alpha`; the official `4.0.0`
package release points at the same pinned commit. See
[`QUATTRO-4.0.md`](QUATTRO-4.0.md).

## Host requirements

The current build is driven from macOS, with all Linux containers and virtual
machines running through OrbStack. Do not use Docker Desktop, Colima or Lima
for this repository.

Required host tools are:

- Git, curl, make and SHA-256 utilities;
- OrbStack and its Docker CLI integration;
- Zstandard and XZ tools;
- ImageMagick (`magick`);
- LLVM Clang and `lld@20` for the native OpenOrbis application on macOS.

The FPKG wrapper downloads the pinned OpenOrbis archive on first use and
verifies its digest before extracting it.

Before any container build, verify the required runtime:

```sh
orb status
# Running

docker context show
# orbstack

docker info >/dev/null
```

The scripts stop if OrbStack is unavailable or another Docker context is
active.

## Private inputs that are not in Git

The repository intentionally does not commit generated binaries, proprietary
firmware-derived inputs or the private loader. A complete build expects:

```text
../linux-ps4-kernel/output/6.18-baikal/
  bzImage
  modules-6.18.44-ps4-baikal.tar.zst
  version.txt
  SHA256SUMS

../linux-ps4-kernel/checkpoint/initramfs/
  initramfs-v26-with-edid.cpio.gz

../payloads/ps4-linux-loader/v25/elf/
  linux-1024mb.elf
```

The exact default paths are defined in `scripts/build-xfce-initramfs` and
`fpkg/tools/vendor-loader`. An alternate initramfs seed can be supplied with
`PS4_SOURCE_INITRAMFS`. Do not publish firmware-derived material or the loader
without completing their separate provenance and redistribution review.

## Complete build, step by step

Run the following commands from `omarchy-ps4/` unless a step says otherwise.
Use a new output name for every candidate; the release builders deliberately
refuse to overwrite an existing result.

### 1. Sync the exact Omarchy source

```sh
./scripts/sync-omarchy-upstream
```

This creates or refreshes `cache/omarchy-quattro`, checks out the immutable
commit from `upstream/omarchy.lock`, and refuses a dirty or unexpected remote.
The checkout supplies the runtime source, themes, Omarchy logo and package
build seed.

### 2. Build the matching PS4 kernel and modules

```sh
cd ../linux-ps4-kernel
./scripts/build-kernel-orbstack --target 6.18-baikal
cd ../omarchy-ps4
```

Expected kernel outputs are under:

```text
../linux-ps4-kernel/output/6.18-baikal/
```

The kernel repository fetches the pinned upstream Linux source, applies its
ordered Baikal patch series, uses the committed configuration, and records the
kernel, modules and checksums. The
[`linux-ps4` repository](https://github.com/meerzulee/linux-ps4) is the
authoritative public kernel build guide.

### 3. Build the PS4 initramfs

```sh
./scripts/build-initramfs-tools
./scripts/build-xfce-initramfs
```

The first command builds the static splash helper and the small userspace
needed before `switch_root`. The second reconstructs the initramfs from the
private firmware seed and installs:

- the USB-only root resolver;
- the external-root safety checks;
- the Omarchy framebuffer splash;
- the EDID and AMDGPU firmware already present in the seed;
- the rootfs extraction helper retained for development recovery.

The result is:

```text
output/xfce-baseline/initramfs.cpio.gz
```

Despite the historical directory name, this is also the initramfs currently
consumed by the Baikal kernel-manager profile.

### 4. Verify the PS4-safe package profile

```sh
./scripts/compose-omarchy-full-profile --check
./tests/full-profile-test
```

The profile starts from Omarchy's pinned base package list, normalizes Arch
provider names, adds the PS4 runtime dependencies, and removes packages whose
resolved dependency closure would activate unsafe storage or generic PC boot
paths. The committed policy is under `profiles/omarchy-full/`.

“Full Omarchy” means the complete upstream desktop, commands, themes and
normal workstation set where the package is safe to install. It does not mean
that every upstream hardware feature is enabled. The blocked groups and their
requirements are documented in
[`BLOCKED-PACKAGE-RESTORATION.md`](BLOCKED-PACKAGE-RESTORATION.md).

### 5. Build the three Omarchy PS4 packages

Choose a fresh candidate name:

```sh
./scripts/build-omarchy-packages \
  --output output/omarchy-packages-4.0.0-local1
```

This produces exactly three Arch packages:

| Package | Responsibility |
| --- | --- |
| `omarchy-ps4` | Pinned upstream runtime, PS4 command guards, network-panel and Chromium compatibility wrappers |
| `omarchy-ps4-settings` | Hyprland/Quickshell overrides, themes, monitor policy, LightDM look, Fastfetch/About and PS4 defaults |
| `omarchy-ps4-provisioning` | USB growth, owner creation, offline desktop finalization and first-boot systemd ordering |

`Containerfile.packages` builds them as `linux/amd64` against the pinned Arch
snapshot and runs package-content plus owner-preparation tests before exporting
anything. The output also contains `SHA256SUMS` and `manifest.env`.

### 6. Resolve the complete offline package snapshot

```sh
./scripts/build-package-snapshot \
  --output output/package-snapshot/omarchy-ps4-4.0.0-local1 \
  --package-source output/omarchy-packages-4.0.0-local1 \
  --cache output/package-snapshot-cache/omarchy-ps4-4.0.0-local1
```

The snapshot builder resolves one exact transaction from the Arch Linux
Archive, the pinned Omarchy repository and the three local packages. It
records every version, URL, filename, size and SHA-256. It then runs two fresh
network-disabled containers:

1. reproduce the dependency solution using only the generated repository;
2. install the complete solution, verify versions and commands, reject the
   forbidden closure and check Quickshell dynamic relocations.

The important output is not merely a directory full of packages:

```text
output/package-snapshot/omarchy-ps4-4.0.0-local1/
  RELEASE.env
  SHA256SUMS
  pacman.conf
  manifest/packages.lock
  manifest/packages.requested.txt
  manifest/forbidden-closure-packages.txt
  repo/*.pkg.tar.zst
```

See [`PACKAGE-SNAPSHOT.md`](PACKAGE-SNAPSHOT.md) for the snapshot trust model.

### 7. Compose the owner-ready Omarchy root

```sh
./scripts/build-gift-rootfs \
  --snapshot output/package-snapshot/omarchy-ps4-4.0.0-local1 \
  --kernel-output ../linux-ps4-kernel/output/6.18-baikal \
  --display-mode 1920x1080@60 \
  --output output/gift-rootfs/omarchy-ps4-4.0.0-local1-rootfs.tar.zst
```

The builder has no network access. It installs the exact package lock, copies
the accepted XFCE recovery overlay, installs only the matching PS4 kernel
modules, applies the PS4 environment and runs the rootfs policy validator.

The exported root has:

- no human account, default password, SSH host key or enabled SSH service;
- a locked root account and no passwordless sudo rule;
- the deferred-owner `pending` marker;
- NetworkManager and `systemd-timesyncd` enabled;
- LightDM gated on successful owner setup;
- Omarchy as the default session, with XFCE retained for recovery;
- no generic Arch kernel, bootloader or unmanaged Pacman mirror;
- a release-state file containing the package, kernel and display identities.

The archive export excludes Docker's `/.dockerenv`. Shipping that marker made
`systemd-detect-virt` report a container on the PS4 and prevented network time
from starting. LightDM's custom Wayland session path is written under the
global `[LightDM]` section; putting it under `[Seat:*]` caused LightDM to ignore
the Omarchy session and fall back to its greeter.

The output has a sibling `.manifest` containing its size, SHA-256, package
snapshot digest, kernel release, module digest and display mode.

### 8. Build the flashable USB image

```sh
./scripts/build-usb-image \
  --rootfs output/gift-rootfs/omarchy-ps4-4.0.0-local1-rootfs.tar.zst \
  --output output/usb-image/omarchy-ps4-4.0.0-local1.img.xz
```

The USB builder runs inside the OrbStack Ubuntu VM and creates a 16 GiB base
image by default. It formats the image itself as one ext4 filesystem labelled
`OMARCHY-PS4`, extracts the root with numeric ownership, ACLs and xattrs,
checks the release contract, runs `e2fsck`, and compresses it with XZ.

There is no partition table and no FAT `PS4BOOT` partition. The same image can
be flashed to 32 GB, 64 GB or larger USB media. On first boot, the guarded
`omarchy-ps4-grow-root` service verifies the label, ext4 type, whole-device
layout and USB ancestry, then runs `resize2fs` online to use the complete
device. The user never partitions or resizes the USB manually.

The output has a sibling `.manifest` with compressed and uncompressed sizes
and hashes. `--keep-raw` optionally retains the uncompressed `.img` for local
inspection. `--allow-development-rootfs` bypasses the deferred-owner gate and
must never be used for a release candidate.

### 9. Stage the exact internal boot set

```sh
./fpkg/tools/stage-internal-boot-set
```

This verifies the exact kernel, initramfs and boot-argument sizes and hashes,
adds `vram.txt` with `1024`, validates the schema-2 release manifest, and stages
the private inputs under:

```text
fpkg/vendor/internal-boot/
fpkg/vendor/provenance/internal-boot-set.json
```

These generated private files are ignored by Git. A hash mismatch is a release
coordination failure, not something to bypass. If a kernel, initramfs or boot
argument changes, update the release manifest, staging pins and FPKG audit
constants together, review the diff, and issue a new manager version.

### 10. Build and audit the FPKG

The current Baikal beta profile is:

```sh
./fpkg/tools/build-ui-prototype --baikal-beta
```

Expected output:

```text
output/fpkg-baikal-beta/IV0000-OMCH42069_00-OMARCHYPS4UI0000.pkg
```

For every non-UI profile, the wrapper first verifies and privately vendors the
pinned loader. The `baikal-beta` build expects step 9 to have already staged
`fpkg/vendor/internal-boot`; it does not regenerate that set implicitly.

The native audit performs `pkg_validate`, extracts the package, checks every
embedded boot asset's exact size and SHA-256, proves that no root filesystem
entered the FPKG, checks the required loader/transaction strings, verifies all
17 wallpapers are normalized to 1920x1080, and checks the package icon sizes.

Available source profiles are:

| Command | Purpose |
| --- | --- |
| `./fpkg/tools/build-ui-prototype` | UI-only prototype; no loader or boot files |
| `... --private-boot` | Historical loader-handoff-only package |
| `... --private-kernel-manager` | v0.28 internal boot-set manager |
| `... --private-kernel-manager-ultrawide` | Experimental v0.29 ultrawide set |
| `... --private-kernel-manager-1080-control` | Historical v0.30 control build |
| `... --baikal-beta` | Current v0.31 Baikal beta identity |

The version and output mapping in `fpkg/ui-prototype/Makefile` is authoritative.
The accepted UI source and package internals are documented in
[`fpkg/docs/UI-PROTOTYPE.md`](../fpkg/docs/UI-PROTOTYPE.md).

### 11. Assemble and verify a release directory

A release directory should contain at least:

```text
omarchy-ps4-v<manager-version>-baikal-beta.pkg
omarchy-ps4-4.0.0-baikal-b1-<release>.img.xz
omarchy-ps4-4.0.0-baikal-b1-<release>.img.xz.manifest
RELEASE.env
SHA256SUMS
```

Generate checksums from inside the final directory:

```sh
shasum -a 256 \
  omarchy-ps4-v*-baikal-beta.pkg \
  omarchy-ps4-*.img.xz \
  > SHA256SUMS

shasum -a 256 -c SHA256SUMS
```

`scripts/build-baikal-beta-release` automates the package build, offline
snapshot, rootfs composition and private FPKG bundle for the frozen `beta1`
identity. It deliberately refuses to overwrite existing outputs. At present it
places the **rootfs archive**, not the final flashable `.img.xz`, in its release
directory; run step 8 and assemble the final user-facing release directory
separately.

## What was changed for PS4

Upstream Omarchy is reused as a pinned desktop/runtime source, not run as a
normal PC installer. The PS4 port adds the following layers.

### Boot and storage

- The stock Arch kernel, mkinitcpio, Limine and generic boot update path are
  replaced by the patch-based Baikal kernel and FPKG-managed boot set.
- The FPKG writes only to the established Orbis application path
  `/data/linux/boot`; it never edits the Sony partition map.
- Boot assets are installed transactionally through a staging marker,
  `boot.omarchy-new`, the active `boot` directory and one retained
  `boot.omarchy-prev` rollback set.
- Before connecting to GoldHEN, the manager verifies the loader and all boot
  assets. Loader v25 is sent to `127.0.0.1:9090` in one complete application
  write; the older multi-write attempt was rejected after GoldHEN consumed a
  truncated 51,200-byte ELF.
- Initramfs resolves `LABEL=OMARCHY-PS4`, proves the root has USB ancestry and
  refuses internal SATA as the supported Linux root.
- The normal Baikal profile disables the failing internal ATA target and keeps
  the complete Linux system on external USB.

### Omarchy desktop and graphics

- Omarchy 4.0.0, Hyprland, Quickshell, UWSM, all 22 themes and the normal
  workstation applications are installed from one offline snapshot.
- XFCE and LightDM remain as the recovery session while the Wayland path is
  developed.
- `AMD_DEBUG=notiling` is exported at the PAM/session boundary for the legacy
  DCE8 display path.
- The accepted profile is fixed at 1920x1080/60, compositor scale 1, with
  expensive blur, shadow and animation effects disabled.
- Chromium is launched with `--disable-gpu` because hardware rendering caused
  rectangular corruption; other GPU paths remain separately gated.
- The About window uses a PS4-aware Fastfetch layout and reports Liverpool
  explicitly because the generic PCI database misidentifies the GPU.

### Network and services

- NetworkManager, `wpa_supplicant`, `wireless-regdb` and the required MediaTek
  firmware package are present for the internal MT7668 Wi-Fi path.
- The Quickshell network panel prefers `wlan0` and retains a disconnected
  station long enough to repopulate scans after a saved connection is removed.
- SSH is disabled in the owner-ready image. If the owner enables it later,
  password, keyboard-interactive and root SSH login remain disabled.
- Network time is enabled because the current PS4 Linux target exposes no
  usable RTC. The rootfs export removes the false Docker virtualization marker
  so `systemd-timesyncd` can run on real hardware.
- Suspend, hibernate, night light, generic firmware update, PC boot management,
  factory reset and unrestricted upstream update commands are hidden or
  guarded until separately supported.

### First boot and owner setup

- The release image contains no human account or default password.
- On first boot, ext4 expands before owner setup and LightDM is blocked until
  provisioning completes.
- A centered Omarchy TUI asks for keyboard, username, password, hostname and
  timezone. Gum's interactive renderer is sent only to the owned setup VT;
  technical errors remain in the journal and lifecycle evidence remains on
  UART.
- Timezone selection uses static region and location lists because the live
  filter left stale frames on the PS4 virtual console.
- The offline user finalizer creates XDG directories, theme/background state,
  bookmarks, launchers, associations, skill links, migration markers and the
  keyring without running upstream network installers.
- The password remains required for `sudo` and screen locking. Persistent
  LightDM autologin is the intended post-provisioning behavior, but the final
  reboot acceptance is still open. The proven greeter fallback cause was an
  incorrectly scoped `sessions-directory`; the source now puts it in the
  global `[LightDM]` section.

### Package and update policy

- Packages are pinned as one complete transaction, not installed from whatever
  happens to be latest on build day.
- The composed image removes live Pacman servers after installation. It cannot
  silently drift into a mixed rolling system.
- A normal update is a coordinated Omarchy PS4 release: a newer FPKG supplies
  the matching kernel/initramfs while a new USB/system snapshot supplies the
  matching modules and userland.
- Installing a higher FPKG with the same `OMCH42069` title identity updates the
  manager. It detects an old internal set and asks the user to update it; it
  does not silently write or download boot files.
- UDisks/GVfs consumers, SDDM takeover, generic kernel hooks and inapplicable
  PC hardware packages remain excluded until their explicit restoration gates
  pass.

The detailed implementation ledger and hardware status live in
[`PS4-FIXES.md`](PS4-FIXES.md) and
[`COMPATIBILITY.md`](COMPATIBILITY.md).

## Optional XFCE recovery-baseline build

The current gift image already includes the accepted XFCE/LightDM recovery
overlay. The older standalone baseline builder remains useful when isolating a
problem below the Omarchy layer:

```sh
./scripts/build-xfce-rootfs
```

That release-style mode creates no usable account and leaves SSH disabled. For
a private hardware-development root, explicitly pass a public key:

```sh
./scripts/build-xfce-rootfs --authorized-key /path/to/id_ed25519.pub
```

The development option creates the historical `ps4` lab user, enables only
key-based SSH, disables SSH password authentication, assigns an unknown random
password hash and grants key-backed passwordless sudo. It is not an acceptable
gift or release root.

The baseline output contains its rootfs archive, installed package list and a
manifest with the Arch snapshot, container image identity, package count,
archive size and SHA-256. The builder validates LightDM, XFCE,
NetworkManager, the locked release accounts and graphical target before
exporting.

## Tests and evidence boundary

Useful local gates are:

```sh
./tests/full-profile-test
./tests/gift-rootfs-contract-test
./tests/private-boot-transaction-test
./tests/package-content-test output/omarchy-packages-4.0.0-local1
./tests/package-snapshot-test \
  output/package-snapshot/omarchy-ps4-4.0.0-local1

make -C fpkg/ui-prototype host-test
```

The package snapshot and rootfs builders add their own network-disabled and
content-policy tests. The FPKG wrapper adds native package validation and
extraction audit.

A successful build is not proof that a console feature works. Installing an
FPKG, staging boot files, sending a loader, booting Linux, reconnecting a USB
or changing a display/network setting is a hardware experiment and must follow
[`DEVELOPMENT-MODE.md`](DEVELOPMENT-MODE.md) with continuous UART and one
bounded session. Curated conclusions belong in
[`experiments/SESSIONS.md`](../experiments/SESSIONS.md); raw logs remain local.

## Common build failures

### Docker context is not `orbstack`

Stop and select the OrbStack context. Do not start a second container runtime
to work around it.

### Output already exists

The snapshot, rootfs and image builders refuse overwrite by design. Give the
candidate a new output name or deliberately version the release. Do not delete
a known artifact merely to make a command pass.

### Boot artifact size or digest mismatch

The kernel, initramfs, bootargs, manifest and FPKG audit constants are one
release unit. Review the changed artifact, update all of its pins and bump the
manager/release identity. Never weaken the hash gate.

### `/.dockerenv` appears in an exported root

Reject that rootfs. The current exporter excludes the marker because it
disables required non-container systemd units on the PS4.

### LightDM shows the greeter instead of Omarchy

First verify that `sessions-directory` is in the global `[LightDM]` section and
that `/usr/local/share/wayland-sessions/omarchy.desktop` exists. A custom
session path under `[Seat:*]` is ignored. Autologin remains a hardware
acceptance item; manual password login is the safe fallback.

### macOS or Windows says the flashed USB is unsupported

That is expected. The release uses one whole-device ext4 filesystem. Do not
allow the host OS to initialize or reformat it.

## Related documents

- [`GETTING-STARTED.md`](GETTING-STARTED.md) — end-user flash, install and boot
  flow.
- [`fpkg/docs/ARCHITECTURE.md`](../fpkg/docs/ARCHITECTURE.md) — internal boot
  transaction and trust boundaries.
- [`PACKAGE-SNAPSHOT.md`](PACKAGE-SNAPSHOT.md) — offline package resolution and
  update policy.
- [`QUATTRO-4.0.md`](QUATTRO-4.0.md) — upstream pin and deferred-owner design.
- [`PS4-FIXES.md`](PS4-FIXES.md) — accepted, degraded and candidate PS4 deltas.
- [`BLOCKED-PACKAGE-RESTORATION.md`](BLOCKED-PACKAGE-RESTORATION.md) — why
  packages are excluded and how they may return.
- [`CHECKPOINT-2026-08-22.md`](CHECKPOINT-2026-08-22.md) — first end-to-end gift
  USB evidence and remaining UI/UX work.
