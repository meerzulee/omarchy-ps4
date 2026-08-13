# FPKG manager architecture

## Product boundary

The FPKG owns presentation, downloads, verification, boot-file staging and
launching the loader payload. Linux owns filesystems, accounts, passwords,
sudo, SSH, the desktop and hardware drivers.

This boundary avoids teaching an Orbis application to edit ext4 or `/etc`, and
keeps credentials out of app storage. Launching the FPKG can lead directly to
the Linux owner form, but the form appears after kexec inside the trusted Linux
image.

## One-package contents

The eventual package layout is:

```text
/app0/eboot.bin
/app0/assets/omarchy-logo.png
/app0/assets/omarchy-font.ttf
/app0/keys/release-key.pub
/app0/payloads/ps4-linux-loader.elf
/app0/provenance/loader.json
```

Two package profiles use the same application. `bootstrap` downloads the
kernel, initramfs and root filesystem. `offline-private-lab` embeds those files
under `/app0/bundle/` together with the loader and credits. The current
prototype selects the full offline profile; bootstrap remains the later
bandwidth/storage-efficient release option.

The offline package is roughly the rootfs size plus package overhead and
temporarily duplicates the rootfs while installation is incomplete. The
installer must check that space before beginning.

## State machine

```text
HOME
  +-- Install/Update -> PREFLIGHT -> RELEASE -> STORAGE -> DOWNLOAD
  |                                              -> VERIFY -> STAGE -> READY
  +-- Boot -----------------------------------------------------------> READY
  +-- Repair -------> VERIFY_LOCAL -> RESTORE_OR_DOWNLOAD -----------> READY
  +-- Diagnostics -> EXPORT

READY -> confirm exact release/VRAM -> PAYLOADER_CHECK -> SEND_ELF -> KEXEC
```

Every long operation persists a small state record under the application's
owned data directory. Downloads use `.part` files, HTTP Range requests and a
saved ETag. A changed ETag discards only the partial object. Verified objects
are renamed into the release staging directory atomically.

`STAGE` writes boot files as temporary names, syncs them, retains the previous
known-good set, and only then changes the active marker. The loader is launched
only after kernel, initramfs, boot arguments, rootfs and manifest all match one
signed release ID.

## Trust model

HTTPS protects transport but does not define the release authority. The FPKG
embeds an Omarchy PS4 Ed25519 public key and verifies a detached signature over
the exact manifest bytes. The manifest pins the byte length and SHA-256 of
every downloaded artifact and identifies compatible firmware, model,
southbridge, root label and transport.

Release rules:

- reject an unknown manifest schema;
- reject unsupported or ambiguous hardware;
- reject a release sequence older than the installed sequence unless the user
  explicitly enters recovery mode;
- require HTTPS and a single configured download origin in production;
- require exact size and SHA-256 before staging;
- keep the prior verified release until the new release completes its boot
  acceptance count;
- never put a password, token, private key or Wi-Fi secret in the manifest.

Boot artifacts are outside Pacman, so their signed manifest is separate from
the signed Arch package repository.

## Embedded payload

The private prototype vendors the release ELF
`linux-1024mb.elf` from PS4 Linux Loader v25. The app verifies its pinned
SHA-256 before packaging. At launch it opens `127.0.0.1:9090` and sends the
complete ELF, handling partial socket writes. Failure is reported as “GoldHEN
PayLoader unavailable”; it never falls back to executing unverified memory.

VRAM is selected through the signed boot configuration and `vram.txt`; the
first UI offers the proven 1024 MB value. Other values stay advanced until
their desktop acceptance gates pass.

The loader's upstream commit and binary digest appear in the About screen and
release provenance. Redistribution remains blocked while its license is
undeclared.

## Image installation

The FPKG copies its verified `/app0/bundle` inputs onto FAT32 label `PS4BOOT`.
The loader reads `bzImage`, `initramfs.cpio.gz`, `bootargs.txt`, and `vram.txt`
from the FAT root. The rootfs archive, checksum, product/debug boot profiles,
and credits live below `/omarchy-ps4/`.

The initramfs—not Orbis—resolves ext4 label `OMARCHY-PS4`, verifies that its
sysfs ancestry is USB, requires the filesystem to be empty, verifies the
rootfs digest, and extracts it. It does not format a partition, accept a raw
device name, or consider internal SATA. After validation it atomically replaces
FAT-root `bootargs.txt` with the product profile and continues into the freshly
installed root.

For the first product:

- external USB root only;
- label `OMARCHY-PS4`;
- internal PS4 storage is not a candidate target;
- no physical repartitioning of the Sony disk;
- XFCE and the last-known-good kernel remain available for recovery.

Internal loop-image installation is a later backend with a separate threat and
recovery model.

## Splash and UART

The product profile has no `console=tty0`. A static initramfs helper waits for
AMDGPU's 32-bit `/dev/fb0` and paints the Omarchy mark, while Baikal MMIO
earlycon remains active for kernel and installer evidence. Rescue and
development use the separate debug profile, which restores visible tty0 logs.

This deliberately replaces Plymouth rather than carrying its PC boot-manager
assumptions into the PS4 loader path. Splash and SATA-off each require their
own bounded hardware acceptance session.

## First boot and password

After the loader starts Linux, `omarchy-ps4-provision-owner.service` owns tty1
before the display manager. It asks for keyboard, username, password,
hostname and timezone with the Quattro setup-form contract. It creates the
account with passworded sudo and never enables SSH password login by default.

If setup is interrupted, `pending` remains and the next boot resumes. The FPKG
only needs to know whether the image is `not-installed`, `owner-pending` or
`ready`; it never reads the password.

## Source and licensing

- Omarchy visual/runtime assets: MIT, preserve upstream notice.
- Payload Guest design reference: GPL-3.0; copying its renderer/controller or
  socket implementation makes the manager a GPL-3.0 program with source
  delivery obligations.
- OpenOrbis PS4 Toolchain: GPL-3.0; follow its distribution terms.
- PS4 Linux Loader: no declared license found at pinned commit; private test
  input only until clarified.

The package About screen includes `/app0/CREDITS.md` and the machine-readable
provenance. Attribution does not replace a redistribution license.
