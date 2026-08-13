# Portable Omarchy PS4

Portable mode installs the Omarchy user experience without running the
upstream machine installer or replacing the PS4 Linux base. It is the default
deployment path while the port is still under hardware qualification.

## What is portable

The bundle contains the pinned Quattro runtime, all `omarchy-*` commands, the
Quickshell UI, themes, menus, application definitions, Hyprland configuration,
and PS4 compatibility guards. It installs under:

```text
~/.local/share/omarchy-ps4/portable/
```

It activates the version through user-owned symlinks for `~/.config/hypr`,
`~/.config/omarchy`, `~/.config/fastfetch`, `~/.config/foot`, and one UWSM
environment file. The
Fastfetch profile uses Omarchy's pinned About icon and reports the PS4 model,
kernel, Liverpool GPU, display, external root, current theme and network state.
It runs from the About action or an explicit `fastfetch` command, not on every
shell startup. Portable mode does not write `/etc`, run Pacman, change LightDM,
modify boot assets, start services, probe internal storage, or restart the
running session.

Upstream Nautilus launch commands are routed to Thunar because Nautilus pulls
GVfs/UDisks into D-Bus activation. The original commands remain inside the
bundle for provenance and review.

The existing XFCE desktop remains the recovery environment. Every portable
install records the replaced user paths and creates an executable rollback
script under `~/.local/state/omarchy-ps4/portable/`.

## What still comes from the base system

Hyprland, Quickshell, UWSM, Foot, Thunar, Mesa, portals, PipeWire, fonts, and their
shared libraries must already be installed. Chromium, Firefox, LibreOffice,
Docker, OBS, Kdenlive, Obsidian, and the rest of the upstream workstation are
not copied into the portable archive. They are the separate native application
profile in `profiles/omarchy-full/packages.txt`.

This split lets us preview and update the complete Omarchy UX without allowing
an upstream installer to own the PS4 kernel, loader, disk, services, or login
manager.

## Build

```bash
./scripts/sync-omarchy-upstream
./scripts/build-omarchy-portable
```

The output is a versioned `.tar.zst` and matching SHA-256 file under
`output/portable/`. The build verifies the pinned commit, every payload file,
the complete top bar configuration, safe autostart, disabled command wrappers,
and preservation of the original upstream scripts for audit.

## Install on the PS4 root

A portable install is still a PS4-side change. Start continuous UART and a
bounded experiment before running it.

```bash
tar --zstd -xf omarchy-ps4-portable-*.tar.zst
cd omarchy-ps4-portable
./check
./install EXP-YYYYMMDD-NNN-A1
```

The installer requires an external USB root labelled `OMARCHY-PS4`, a normal
non-root desktop user, and the runtime commands `hyprland`, `qs`, `foot`,
`uwsm`, `jq`, and `thunar`. It deliberately does not reload Hyprland. The next session
activation is a separate hardware experiment.

If the session fails, run the exact `ROLLBACK.sh` path printed by the installer,
then return to XFCE.
