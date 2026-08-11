# Omarchy Quattro inventory for PS4

The base-install decision is documented separately in
[`OMARCHY-BASE.md`](OMARCHY-BASE.md): upstream has a full workstation package
list, but no safe bare-install mode for this existing PS4 root.

## Pinned upstream

| Field | Value |
|---|---|
| Version | `4.0.0.alpha` |
| Branch | `quattro` |
| Commit | `08204846ef6c2e2de8eba873d5888749e1d46ba5` |
| Commit date | 2026-08-11 18:34:07 +0200 |
| Core packages | 147 |
| Additional/conditional packages | 59 |
| Helper commands | 415 |
| Migrations | 70 |
| Quickshell plugin manifests | 37 |

Run `./scripts/sync-omarchy-upstream` to reproduce the ignored checkout under
`cache/omarchy-quattro`. The lock is in `../upstream/omarchy.lock`; the
machine-readable test graph is in `../inventory/quattro-components.toml`.

## What the desktop actually depends on

Quattro is not just Hyprland dotfiles. Its graphical session is a stack:

```text
PS4 kernel DRM/KMS
  -> PS4-compatible libdrm and Mesa
  -> Wayland + Hyprland
  -> UWSM session/environment lifecycle
  -> XDG portals + PipeWire/WirePlumber
  -> Quickshell
  -> Omarchy shell, plugins, Lua Hyprland configuration, and helper commands
  -> SDDM login and normal applications
```

This order is reflected in the component inventory. We test the lowest layer
that can explain a failure and do not install the next layer merely to see what
happens.

## Candidates to reuse

These are candidates, not support claims:

| Area | Quattro components |
|---|---|
| Compositor | Hyprland, Lua configuration, Foot terminal |
| Session | UWSM and the `omarchy.desktop` Wayland session |
| Shell | Quickshell, shell IPC, bar/panel/plugin system |
| Integration | GTK/Hyprland portals, PipeWire, WirePlumber, clipboard tools |
| UX | Themes, bindings, menus, notifications, OSD, application launchers |
| Maintenance | Update locking, migrations, package helpers, diagnostics |

Each candidate remains isolated until its gate passes on the PS4.

## Replace for PS4

| Upstream assumption | PS4 replacement |
|---|---|
| Stock `linux` and `linux-headers` | Matched PS4 kernel, modules, source, config, and build provenance |
| Limine and mkinitcpio boot hooks | PS4 Linux loader, custom initramfs, and Orbis-side A/B assets |
| Generic `linux-firmware` | Explicit AMD, Radeon, MediaTek, and Marvell subset plus loader-extracted firmware |
| Generic hardware detection | Known PS4 model/southbridge capability record |
| Normal package update freedom | Signed compatibility sets for kernel and graphics packages |
| Upstream all-packages acceptance | PS4 profile acceptance driven by the component ledger |

## Exclude from the first product

- Btrfs/Snapper and Limine snapshot integration; the MVP uses ext4.
- Suspend, hibernate, firmware updates, and unattended major graphics updates.
- UDisks/`udiskie` automount while the internal PS4 disk is exposed; A78 showed
  that device discovery probes `sdb` and produces repeated I/O errors.
- Intel, Nvidia, Apple, Surface, ASUS, Framework, Tuxedo, fingerprint, laptop,
  and DKMS hardware branches.
- Power-profile and brightness behavior that assumes a laptop battery/backlight.
- Printing, Docker, databases, office/video-production applications, and the
  remainder of the 145-package workstation profile until requested and tested.

## Why upstream acceptance cannot be copied unchanged

Quattro's acceptance suite deliberately verifies its complete PC product. It
requires every core package, Docker, printing and discovery services,
power-profiles, SDDM, and a Btrfs root filesystem. Those are valid upstream
requirements but false requirements for a PS4 desktop. We will reuse focused
runtime checks—such as monitor discovery, shell IPC, visible layer surfaces,
and PipeWire health—inside a smaller PS4-specific suite.
