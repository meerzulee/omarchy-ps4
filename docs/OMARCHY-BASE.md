# Omarchy base for PS4

## Short answer

Upstream Omarchy does not provide a safe bare-install mode for an existing PS4
Linux root. Its file named `install/omarchy-base.packages` is a complete PC
workstation package set, not a minimal Hyprland base.

| Upstream line | Pinned revision | What exists | PS4 decision |
|---|---|---|---|
| Stable 3.8.4 | `8fcc9d6048af4cb0e3af8512c78049857a3b53dd` | 149-package base list and a full machine installer | Do not run the installer |
| Quattro 4.0.0rc3 | `144f4d1e31d6ddc2cba5dfd69278cabf02bafd05` | 147-package base list, `omarchy`/`omarchy-settings` packages, and deferred-owner setup | Reuse desktop files and owner UX selectively |

Neither pinned tree contains `OMARCHY_BARE` or another bare-install switch.
Stable `boot.sh` replaces the Omarchy checkout and enters the complete install
pipeline. Quattro explicitly assigns orchestration to its ISO and retains
system setup for SDDM, services, firewall, Snapper, hardware detection, and
post-install policy.

The Git branch named `rc` remains on Omarchy 3.8.x. Quattro RC3 is the pinned
`quattro` commit above, released by the separate package repository.

Primary upstream references:

- [Omarchy repository](https://github.com/basecamp/omarchy)
- [Omarchy package repository](https://github.com/omacom-io/omarchy-pkgs)
- [Omarchy ISO repository](https://github.com/omacom-io/omarchy-iso)
- [stable v3.8.4](https://github.com/basecamp/omarchy/releases/tag/v3.8.4)
- [official installation manual](https://learn.omacom.io/2/the-omarchy-manual/50/manual-installation)

## PS4 base

The PS4 base is the known-good external Arch/XFCE root, extended through
independent compatibility gates:

```text
Arch + XFCE recovery
  -> Weston/native Wayland gate
  -> bare Hyprland
  -> UWSM
  -> Hyprland portal
  -> PipeWire integration
  -> minimal Quickshell
  -> pinned Omarchy settings and shell
```

The following upstream concerns stay outside the portable desktop path:

- kernel, initramfs, Limine and mkinitcpio boot installation;
- disk formatting, Btrfs, Snapper and hibernation;
- SDDM replacement until LightDM recovery is no longer needed;
- generic Intel, Nvidia, Apple, Surface and laptop hardware setup;
- automatic activation of Docker, printing, databases, office and production
  services before their individual gates pass.

## Portable first

The complete pinned Quattro user layer is now composed as a portable bundle.
It carries the shell, commands, themes, menus, application definitions, and
PS4-safe configuration under the user's home directory. Unsafe upstream
commands are guarded while the originals remain present for audit. See
[`PORTABLE.md`](PORTABLE.md).

The full native application list is composed separately from all 147 upstream
base packages, with only narrowly documented hardware/boot packages excluded.
Installing an
application package is not a hardware support claim and does not enable its
service.

## Current live result

On the Baikal B1 test console, Weston `15.0.1-3` visibly rendered a native EGL
client through radeonsi. Hyprland `0.56.2-1` is installed with a minimal
non-Omarchy configuration and passed direct DRM at 1920x1080/60 with a visible
native Wayland terminal plus physical keyboard and mouse input. Automated
LightDM recovery back to the original X11/XFCE session also passed. UWSM
`0.26.6-1` is installed; its direct LightDM login, systemd user lifecycle,
native terminal, and clean compositor stop passed. A clean stop returns to the
LightDM greeter instead of re-running autologin.

The Hyprland portal, Foot, Quickshell, and pinned Quattro shell have now been
exercised on the live system. Portable mode is the next controlled deployment;
native `omarchy-ps4` packages remain a later integration path.
