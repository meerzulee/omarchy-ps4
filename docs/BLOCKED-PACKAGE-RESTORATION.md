# Blocked package restoration plan

This document is the backlog for restoring upstream Omarchy packages that are
currently excluded from the PS4 image. A package stays blocked until its
prerequisite is implemented and its real-hardware acceptance experiment is
recorded in `experiments/SESSIONS.md`.

The exclusions are not all equivalent:

- **Safety blocks** prevent probing a PS4 hardware path that has already
  produced errors.
- **Boot/session blocks** prevent generic PC lifecycle tools from taking over
  the custom PS4 boot and recovery path.
- **Hardware applicability blocks** remove services for devices or firmware
  interfaces the PS4 does not provide.

Never restore a blocked group merely because Pacman resolves it or the image
build succeeds. Restore one dependency group at a time and use the bounded
UART hardware process in `AGENTS.md`.

## Storage and UDisks group

| Packages | Why blocked | Requirement for restoration |
|---|---|---|
| `udiskie`, `gnome-disk-utility` | They start UDisks discovery. Experiment A78 showed that discovery of the exposed internal disk produces repeated I/O errors. | Prove that internal SATA is inaccessible to generic userspace discovery while external USB storage still works. |
| `gvfs-mtp`, `gvfs-nfs`, `gvfs-smb` | Their resolved dependency chain activates `gvfs` and `udisks2` through D-Bus. | Pass the storage-isolation gate, then test each backend separately. |
| `nautilus`, `nautilus-python` | Nautilus relies on GVfs/UDisks. Thunar currently provides the safe file-manager path. | Pass the storage-isolation gate and retain Thunar as a recovery fallback. |
| `evince` | The resolved Arch dependency chain introduces GVfs. | Pass the storage-isolation gate, or use a document viewer whose closure does not contain GVfs/UDisks. |
| `sushi` | Depends on the Evince/GVfs preview path. | Restore only after the Evince and Nautilus groups pass. |
| `kdenlive` | KDE Solid introduces UDisks device discovery. | Pass the storage-isolation gate, or build and audit a package with the UDisks backend disabled. |

The storage-isolation gate requires all of the following:

1. Disable or hide the internal ATA target before normal userspace starts. The
   current candidate product profile uses `libata.force=1.00:disable`; it is
   not accepted until the hardware experiment passes.
2. Add a second-layer Udev/UDisks rule that marks internal Sony storage as
   ignored. This is defense in depth, not a substitute for kernel-level
   isolation, because Udev rules run after kernel discovery.
3. Continue resolving the Linux root by `LABEL=OMARCHY-PS4`, never by a
   persistent `/dev/sdX` name.
4. Prove cold boot, warm boot, external USB enumeration, USB reconnect and
   root mount behavior without internal-disk I/O errors.
5. Start UDisks deliberately and prove that only the external test media is
   exposed through its API.
6. Restore consumers in this order: document viewer, one GVfs backend,
   Nautilus, previews/video editor, and automatic mounting last.

## Boot and session group

| Package | Why blocked | Requirement for restoration |
|---|---|---|
| `sddm` | LightDM/XFCE is the accepted recovery login path. An unproven SDDM configuration can strand the owner at login or start the wrong session. | Pass owner creation, first automatic login, subsequent password login, Quattro selection, logout/reboot and recovery-session tests. Keep a bootable LightDM/XFCE rollback until SDDM is accepted. |
| `plymouth` | Upstream Plymouth assumes a conventional PC initramfs and DRM handoff; the PS4 loader uses a custom initramfs and framebuffer splash. | Port it explicitly to the PS4 initramfs, preserve UART diagnostics, and prove clean handoff across every mode change. Prefer the existing PS4 splash unless Plymouth provides a concrete benefit. |
| `kernel-modules-hook` | It assumes stock Arch kernel and mkinitcpio ownership and could install modules that do not match the PS4 kernel. | Do not restore the upstream hook. Replace its function with the signed PS4 kernel/modules compatibility set and recoverable A/B update transaction. |

## Hardware applicability group

| Package | Why blocked | Requirement for restoration |
|---|---|---|
| `ddcutil` | Generic I2C/DDC probing is unproven behind the Aeolia/MN864729 display path. | Use an isolated DDC experiment with a timeout and rollback; prove that probing cannot blank or destabilize HDMI. It is optional for the product. |
| `power-profiles-daemon` | It expects PC/laptop power-profile, battery and firmware interfaces. | Implement an explicit PS4 CPU/GPU/thermal backend with safe limits and hardware acceptance. Do not expose unsupported profile choices. |
| `asdcontrol` | It is an Apple Studio Display helper and installs a PS4-irrelevant passwordless-sudo rule. | No planned restoration. Reconsider only if the supported hardware scope changes and remove the generic sudo rule. |
| `bolt` | It manages Thunderbolt devices, which are not part of the PS4 hardware model. | No planned restoration. Reconsider only if a real supported Thunderbolt path exists. |

## Promotion procedure

For each restoration candidate:

1. Prove the full Pacman transaction closure does not introduce another
   forbidden package unexpectedly.
2. Implement the smallest required guard or replacement and test it in the
   OrbStack image environment.
3. Declare one bounded PS4 experiment with one changed variable, expected UART
   and operator evidence, timeout and rollback.
4. Preserve the UART session and record the result in
   `experiments/SESSIONS.md`.
5. Remove the package from `blocked-packages.txt` and, where applicable,
   `forbidden-closure-packages.txt` only after acceptance.
6. Regenerate the profile and snapshot lock, rebuild the USB image, and repeat
   the relevant boot, owner, recovery and update tests.

Restoring package installation does not automatically mean its hardware
feature is supported. Support is declared separately in
`docs/COMPATIBILITY.md` after the required acceptance count is reached.
