# Omarchy base for PS4

## Short answer

Upstream Omarchy does not provide a safe bare-install mode for an existing PS4
Linux root. Its file named `install/omarchy-base.packages` is a complete PC
workstation package set, not a minimal Hyprland base.

| Upstream line | Pinned revision | What exists | PS4 decision |
|---|---|---|---|
| Stable 3.8.4 | `8fcc9d6048af4cb0e3af8512c78049857a3b53dd` | 149-package base list and a full machine installer | Do not run the installer |
| Quattro alpha | `08204846ef6c2e2de8eba873d5888749e1d46ba5` | 147-package base list, `omarchy`/`omarchy-settings` packages, and target-side ISO setup commands | Reuse desktop files selectively |

Neither pinned tree contains `OMARCHY_BARE` or another bare-install switch.
Stable `boot.sh` replaces the Omarchy checkout and enters the complete install
pipeline. Quattro explicitly assigns orchestration to its ISO and retains
system setup for SDDM, services, firewall, Snapper, hardware detection, and
post-install policy.

Primary upstream references:

- [Omarchy repository](https://github.com/basecamp/omarchy)
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

The following upstream concerns stay outside this desktop path:

- kernel, initramfs, Limine and mkinitcpio boot installation;
- disk formatting, Btrfs, Snapper and hibernation;
- SDDM replacement until LightDM recovery is no longer needed;
- generic Intel, Nvidia, Apple, Surface and laptop hardware setup;
- Docker, printing, databases, office and production applications.

## Current live result

On the Baikal B1 test console, Weston `15.0.1-3` visibly rendered a native EGL
client through radeonsi. Hyprland `0.56.2-1` is installed with a minimal
non-Omarchy configuration and passed direct DRM at 1920x1080/60 with a visible
native Wayland terminal plus physical keyboard and mouse input. Automated
LightDM recovery back to the original X11/XFCE session also passed. UWSM
`0.26.6-1` is installed; its direct LightDM login, systemd user lifecycle,
native terminal, and clean compositor stop passed. A clean stop returns to the
LightDM greeter instead of re-running autologin.

The Hyprland portal, Foot, Quickshell, `omarchy`, and
`omarchy-settings` remain deliberately uninstalled until their preceding gates
close.
