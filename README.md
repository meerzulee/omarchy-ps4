# Omarchy PS4 Research and Architecture

> The active, gate-driven execution roadmap is in
> [`docs/PLAN.md`](docs/PLAN.md). The existing XFCE evidence is recorded in
> [`docs/BASELINE.md`](docs/BASELINE.md), and all support claims are tracked in
> [`docs/COMPATIBILITY.md`](docs/COMPATIBILITY.md). The current ecosystem
> snapshot—what exists, what changed in 2026, and what is still missing—is in
> [`knowledge/2026-08-10/WORLD-STATE.md`](knowledge/2026-08-10/WORLD-STATE.md).

Architecture research date: 2026-08-09

Ecosystem snapshot date: 2026-08-10

Status: clean XFCE rootfs built; real-hardware reproduction pending

## Executive summary

An Omarchy-derived Linux distribution can run on a jailbroken PS4, and it is
realistic to present it to users through a single PS4 FPKG installer/launcher.
It should not be implemented as a direct port of the normal Omarchy installer,
however. The practical design is:

1. Build a PS4-specific Arch root filesystem off-console.
2. Replace the stock kernel, GPU packages, bootloader integration, and generic
   PC hardware setup with PS4-specific components.
3. Use an explicitly identified external Linux device for the first product;
   treat an Orbis-hosted loop image as a later, hardware-dependent option.
4. Use a small OpenOrbis FPKG to download, verify, install, repair, update, and
   launch the system.
5. Boot through a PS4 Linux loader and kexec, not GRUB or Limine.

The internal PS4 disk must not be physically repartitioned. Some existing PS4
Linux installations use a large file as a virtual disk, which avoids changing
Sony's partition layout, but the current community guide does not consider
that path reliable on Baikal. The MVP therefore stays external.

The largest unresolved risk is whether current Hyprland and Quickshell work
reliably on the PS4's patched AMD graphics stack. That must be proven before
building the installer or full distribution.

## Project scope

The intended product is a homebrew application for an already jailbroken PS4.
It will not run on a stock console and it will not provide the jailbreak.

The application should eventually expose these actions:

- Install Omarchy PS4
- Boot Omarchy PS4
- Update system and boot assets
- Select VRAM allocation
- Repair an incomplete installation
- Roll back boot assets
- Export diagnostic logs
- Remove the Linux installation

Initial hardware work targets the known Baikal B1 console and external storage
because that is the machine we can test. Support will not be generalized to
other Baikal, Aeolia, or Belize revisions until each one has recorded hardware
evidence.

## What the Omarchy Quattro branch is

The researched Quattro branch reports version `4.0.0.alpha`. Its repository is
not a complete image installer. The branch's own contributor guide explains
that a separate ISO owns installation orchestration, while the repository
provides target-side setup commands, package lists, configuration, migrations,
themes, and desktop behavior.

Quattro assumes a normal Arch PC environment, including:

- Arch Linux x86-64 packages
- Hyprland, Quickshell, UWSM, and SDDM
- The stock Arch `linux` kernel and headers
- Limine and mkinitcpio integration
- Btrfs and Snapper
- Intel, Nvidia, laptop, fingerprint, firmware, and DKMS setup paths
- Pacman and AUR package updates

The PS4 uses an x86-64 AMD Jaguar CPU, so much of the normal Arch userland can
be reused. The kernel, GPU stack, boot path, installer, and hardware setup
cannot be reused unchanged.

### Reuse from Quattro

- Hyprland configuration, if the compositor passes PS4 testing
- Quickshell desktop and UI
- Themes and default application configuration
- Command routing and helper scripts
- Package-backed migrations
- Update locking, logging, confirmation, and post-update checks
- Pacman guard concept

### Replace or remove

- Omarchy ISO installation orchestration
- Stock Arch kernel and headers
- Limine boot management
- Generic mkinitcpio boot installation
- Limine/Snapper boot-menu integration
- Generic PC hardware detection
- Intel, Nvidia, Surface, T2 Mac, laptop, and fingerprint setup
- Unrestricted AUR update behavior
- Firmware update tooling such as `fwupd`
- Suspend and hibernate until explicitly validated

## Existing PS4 Linux boot chain

The current firmware-agnostic PS4 Linux loader supports multiple firmware
versions and detects the console southbridge at runtime. It loads:

- `bzImage`
- `initramfs.cpio.gz`
- optional `bootargs.txt`
- optional `vram.txt`

It checks USB first, then the internal paths:

```text
/data/linux/boot/
/user/system/boot/
```

The loader patches the Orbis kernel, installs a kexec-like path, loads the
Linux kernel and initramfs into memory, and performs a controlled transition
from Orbis OS to Linux.

The Linux kernel must be selected for the console's southbridge. Current
maintained open-source kernel work has distinct Aeolia/Belize and Baikal
branches. Kernel binaries must always be distributed with the exact source,
configuration, commit, and toolchain information used to build them.

## Internal HDD design

### Existing method

The maintained internal installer does not create a physical disk partition.
Its initramfs performs roughly this sequence:

1. Obtain the PS4 HDD encryption key supplied by the loader.
2. Open the encrypted PS4 data partition with `cryptsetup`.
3. Mount the decrypted UFS filesystem.
4. Create a large `/user/home/linux.img` file.
5. Attach the file to a loop device.
6. Format the loop device as ext2 or ext4.
7. Extract the Linux root filesystem into it.
8. Mount it as `/newroot` and execute `switch_root`.

### Recommended layout

```text
/user/home/omarchy-ps4/root.img
/user/home/omarchy-ps4/home.img          # optional persistent home image
/user/home/omarchy-ps4/install-state.json

/data/linux/boot/slots/A/bzImage
/data/linux/boot/slots/A/initramfs.cpio.gz
/data/linux/boot/slots/A/bootargs.txt
/data/linux/boot/slots/A/manifest.json

/data/linux/boot/slots/B/...
/data/linux/boot/active-slot
```

For the first release, use ext4 inside `root.img`. Btrfs inside a loop image
could support snapshots later, but only after confirming that the selected PS4
kernel configuration supports it and that nested-filesystem performance is
acceptable.

### Why not create a physical partition

- Sony's internal partition scheme is encrypted and platform-managed.
- Repartitioning risks destroying games, saves, or the system installation.
- Firmware recovery or system updates may reject or overwrite a modified map.
- A loop image is easier to create, validate, back up, resize, and remove.
- A loop image already works with established PS4 Linux tooling.

## Proposed PS4 FPKG manager

Build the manager with the OpenOrbis PS4 Toolchain. The application should be
small; the complete Linux root filesystem should normally be downloaded after
installation or imported from USB.

### First-install flow

1. Verify that the required jailbreak/homebrew environment is active.
2. Detect firmware, PS4 model, southbridge, and available internal space.
3. Fetch a signed release manifest over HTTPS.
4. Select a compatible kernel, initramfs, loader, and rootfs release.
5. Let the user choose installation size and VRAM allocation.
6. Download into a staging directory with resumable transfers.
7. Verify file size, SHA-256 digest, and an offline release signature.
8. Write boot assets through temporary filenames, `fsync`, and atomic rename.
9. Write an install configuration consumed by the custom initramfs.
10. Launch the embedded PS4 Linux loader.
11. Let the initramfs create `root.img`, extract the rootfs, and boot it without
    requiring a keyboard or rescue-shell commands.
12. Record a successful boot before marking the new slot as trusted.

### Normal boot flow

```text
FPKG manager
  -> select last-known-good boot slot
  -> load kernel + initramfs + boot arguments
  -> invoke PS4 Linux loader/kexec
  -> decrypt and mount PS4 UFS in initramfs
  -> attach root.img to loop device
  -> mount Linux root
  -> switch_root into Omarchy PS4
```

### Online and offline installation

Recommended:

- Small bootstrap FPKG
- Signed downloads from a release CDN
- USB import for offline users

Optional later:

- A large offline FPKG containing the rootfs

A full offline FPKG temporarily duplicates storage because Orbis installs the
package and the manager then creates the separate Linux image. It should not be
the default distribution format.

## Root filesystem builder

The rootfs should be built on an x86-64 Linux build machine or CI runner, not on
the PS4. Building Mesa, LLVM, kernels, and large AUR packages on the PS4's
Jaguar CPU would be too slow and difficult to reproduce.

The builder should:

1. Bootstrap a minimal Arch rootfs.
2. Enable the signed Omarchy PS4 binary repository before normal repositories.
3. Install a PS4-specific package profile.
4. Install Quattro desktop files and PS4 overrides.
5. Remove PC bootloader and hardware-specific packages.
6. Create the default user and controller-friendly first-run configuration.
7. Enable networking, HDMI audio, SDDM, UWSM, Hyprland, and Quickshell.
8. Run validation in a chroot/container where possible.
9. Produce a deterministic `rootfs.tar.zst` plus a signed manifest.

Do not run the normal Omarchy ISO installer inside the PS4. Reuse its
target-side setup leaves selectively through a PS4-specific orchestrator.

## Package repositories

An “AUR repository” is not sufficient. AUR distributes PKGBUILDs and expects
the user to compile packages. This project needs:

1. A Git repository containing PKGBUILDs, patches, build scripts, and CI.
2. A signed binary Pacman repository containing prebuilt x86-64 packages.

Suggested packages:

```text
omarchy-ps4
omarchy-ps4-settings
omarchy-ps4-keyring
omarchy-ps4-mirrorlist
linux-ps4-aeolia-belize
linux-ps4-baikal
mesa-ps4
lib32-mesa-ps4
libdrm-ps4
lib32-libdrm-ps4
xf86-video-amdgpu-ps4
ps4-boot-assets
ps4-update-guard
```

PS4 graphics packages should use correct `provides`, `conflicts`, and versioned
dependencies so official packages cannot silently replace them. The 64-bit and
32-bit Mesa/libdrm packages must be published and updated as a coherent set.

Repository databases and packages should require signatures from a dedicated
project keyring. Do not copy Quattro's current `Optional TrustAll` policy for
the Omarchy repository; kernels and privileged updater components require a
stronger trust model.

## Kernel and boot-asset updates

The Orbis loader cannot read the kernel from the Linux filesystem before Linux
has started. Installing a kernel package only into Linux `/boot` is therefore
not enough.

Use two related mechanisms:

- Pacman installs the matching kernel modules and metadata into the Linux
  rootfs.
- A controlled boot-asset updater stages the corresponding `bzImage` and
  initramfs into the Orbis-side A/B boot slots.

Never overwrite the active boot slot in place. A safe update is:

1. Download into the inactive slot.
2. Verify signature and hashes.
3. Verify the manifest matches the console southbridge and loader ABI.
4. Mark the inactive slot as pending.
5. Attempt one boot.
6. Commit it only after Linux reports a successful graphical session.
7. Fall back to the previous slot after a failed or timed-out boot.

## Update policy

Reuse Quattro's update locking, migrations, transcript logging, and direct
Pacman guard, but extend the guard with PS4 compatibility checks.

The default updater should not permit uncontrolled replacements of:

- PS4 kernel and headers
- Mesa and lib32-mesa
- libdrm and lib32-libdrm
- AMDGPU Xorg support package
- LLVM libraries required by the PS4 Mesa build
- initramfs and loader assets

Other protections:

- Disable automatic AUR upgrades by default.
- Do not build large AUR packages on the console.
- Require a complete compatible graphics package set before transaction start.
- Download all packages before changing the installed system.
- Retain the previous package versions in cache.
- Run post-update validation before recommending a reboot.
- Keep boot-asset updates separate from routine application updates.
- Disable hibernate, suspend, firmware updates, and internal-HDD swap until
  explicitly tested.
- Avoid unattended major upgrades of Hyprland, Quickshell, Mesa, or LLVM.

## Hardware and desktop risks

### Graphics proof of concept

No reliable public report was found proving current Quattro's exact Hyprland
and Quickshell stack on PS4 graphics. Other Wayland desktops have run on PS4
Linux, but that is not enough to establish Quattro compatibility.

The first technical milestone must test:

1. Current open-source PS4 kernel on a known Aeolia or Belize console.
2. Current PS4-patched Mesa and libdrm packages.
3. DRM/KMS output at 1080p over HDMI.
4. Bare Hyprland without Omarchy configuration.
5. Quickshell inside Hyprland.
6. USB keyboard/mouse and DualShock 4 input.
7. HDMI audio.
8. Ethernet and supported Wi-Fi/Bluetooth hardware.
9. Chromium and basic hardware-accelerated rendering.
10. Clean shutdown back to a state where Orbis OS can boot normally.

If Hyprland fails because of DRM, renderer, or GPU-reset limitations, the
project must either patch Hyprland/Aquamarine or use a simpler compositor. A
different compositor would make the result less directly compatible with
Omarchy and should be treated as a separate fallback product decision.

### Performance

The PS4 has enough x86-64 compatibility and memory for a desktop, but its
Jaguar CPU is weak by modern desktop standards. Quattro's default package list
is large and includes heavyweight software. The PS4 image should begin with a
reduced package profile and make large applications optional.

Recommended initial VRAM default: 2 GB, with selectable 1 GB, 2 GB, and 3 GB
profiles. This must be benchmarked against desktop responsiveness and GPU
stability.

### Baikal

Baikal uses a different kernel branch and is still reported as less stable for
internal installation. Do not claim Baikal support until installation, boot,
graphics, networking, and repeated update/rollback tests pass on real Baikal
hardware.

## Licensing and redistribution

- Omarchy's repository is MIT licensed.
- The Linux kernel is GPL-2.0-only with the Linux syscall note; binary releases
  must be accompanied by corresponding source and build information.
- Mesa, libdrm, initramfs components, and every bundled userland package retain
  their individual licenses and notices.
- OpenOrbis tooling is GPLv3; review which runtime components, if any, are
  incorporated into the distributed application.
- The current PS4 Linux loader repository does not expose a clear root-level
  license file, although its nested kexec implementation has BSD licensing.
  Complete a file-by-file license audit or obtain clarification before
  redistributing a combined loader binary.
- Do not redistribute proprietary Sony firmware. The kexec implementation can
  extract required Radeon firmware from the user's running Orbis OS at boot.

## Recommended implementation phases

### Phase 0: Hardware proof

- Select one known Aeolia or Belize test console and firmware.
- Boot a minimal Arch rootfs with the maintained PS4 kernel and initramfs.
- Validate patched Mesa, Hyprland, Quickshell, input, audio, and networking.
- Record kernel commit, southbridge, firmware, model, and all test results.

Exit condition: a repeatable Quattro shell session boots manually.

### Phase 1: Reproducible rootfs

- Create the PS4 package repository and keyring.
- Package the PS4 graphics stack.
- Create the reduced Omarchy PS4 package profile.
- Build and validate `rootfs.tar.zst` in CI.
- Publish signed manifests and checksums.

Exit condition: a clean rootfs can be rebuilt and manually installed.

### Phase 2: Custom initramfs

- Automate encrypted UFS discovery and mounting.
- Create, format, resize, and validate `root.img`.
- Install the rootfs without interactive shell commands.
- Preserve diagnostic logs on both success and failure.
- Add recovery and uninstall paths.

Exit condition: kernel plus initramfs performs an unattended internal install.

### Phase 3: OpenOrbis manager FPKG

- Build the PS4-native UI.
- Add model, firmware, and southbridge detection.
- Add signed, resumable downloads and USB import.
- Add install, boot, repair, log export, and removal actions.
- Integrate the Linux loader with supported jailbreak environments.

Exit condition: a user installs and launches Linux without FTP or a keyboard.

### Phase 4: Safe updates

- Add signed Pacman repository updates.
- Add compatibility-set preflight checks.
- Add A/B boot assets and fallback behavior.
- Add staged kernel/Mesa updates and health reporting.
- Add release channels only after stable recovery exists.

Exit condition: failed updates recover without reinstalling the distro.

### Phase 5: Hardware matrix

- Expand testing across PS4 Fat, Slim, and Pro.
- Add Belize variations.
- Add Baikal only after internal-storage stability is demonstrated.
- Publish an explicit support matrix instead of assuming chassis equals
  southbridge.

## Initial decisions

- Build an Omarchy derivative rather than patching the stock installer at
  runtime.
- Target Aeolia/Belize first.
- Use an internal loopback image, not a physical partition.
- Use ext4 for the MVP.
- Build packages off-console and distribute a signed binary repository.
- Keep the FPKG small and download/import the rootfs separately.
- Manage kernel/initramfs separately from routine Pacman updates.
- Require A/B boot assets and last-known-good rollback before public release.
- Treat Hyprland plus Quickshell compatibility as the first hard gate.

## Open questions

- Which exact PS4 model, southbridge, and firmware will be the first target?
- Does current Hyprland/Aquamarine start successfully with the patched PS4 DRM
  and Mesa stack?
- Does Quickshell render reliably and within acceptable memory usage?
- Which PS4 kernel modules must be shipped in the rootfs rather than built in?
- Can the OpenOrbis application directly execute the integrated loader in all
  target jailbreak environments, or is a companion privileged payload/daemon
  required?
- Which PS4 filesystems and paths can the homebrew app access consistently
  across GoldHEN versions?
- Should user data live in a separate `home.img` for reinstall resilience?
- Is Btrfs worth supporting later, or should rollback remain package-cache and
  boot-slot based?
- What is the minimum practical internal installation size for the reduced
  Quattro package profile?

## Primary sources

- Omarchy Quattro branch: https://github.com/basecamp/omarchy/tree/quattro
- Quattro installer guide: https://github.com/basecamp/omarchy/blob/quattro/agents/skills/install-scripts.md
- Quattro package lists: https://github.com/basecamp/omarchy/tree/quattro/install
- Quattro update process: https://github.com/basecamp/omarchy/blob/quattro/docs/update-process.md
- Quattro Pacman configuration: https://github.com/basecamp/omarchy/blob/quattro/default/pacman/pacman-stable.conf
- PS4 Linux loader: https://github.com/ps4-linux/ps4-linux-loader
- Maintained PS4 kernel: https://github.com/rmuxnet/linux
- PS4 Linux compatibility database: https://github.com/ps4-linux/ps4-linux.github.io
- PS4 Linux installation guide: https://github.com/DionKill/ps4-linux-tutorial
- PS4 Arch graphics packages: https://github.com/DionKill/ps4-video-archlinux
- PS4 RetroBox internal installer reference: https://github.com/danyboy666/ps4-retrobox
- OpenOrbis PS4 Toolchain: https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain
