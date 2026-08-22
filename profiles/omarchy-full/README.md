# Full Omarchy Quattro profile

This profile keeps the complete upstream workstation and application set where
the package itself is safe to install. Unsupported hardware actions are
blocked at the command and menu layers rather than silently pretending to
work.

`packages.txt` is generated from the pinned upstream
`install/omarchy-base.packages`, minus the narrowly documented list in
`blocked-packages.txt`, with provider names normalized by
`package-replacements.txt`, plus PS4 packages and Quattro's conditional
Wayland, PipeWire, Mesa, and Vulkan dependencies from
`additional-packages.txt`.

Included areas:

- Foot, tmux, Neovim, LazyGit, Herdr, Mise, compilers, and terminal helpers;
- Chromium, Firefox, web applications, Thunar, mpv, image and document apps;
- LibreOffice, OBS, Obsidian, LocalSend, Moonlight, and drawing tools;
- Docker CLI/runtime packages, printing packages, Bluetooth packages, portals,
  PipeWire, international input, fonts, and every Quattro theme;
- all upstream `omarchy-*` commands, with unsafe originals retained for audit
  and guarded replacements presented to users.

Installation does not imply hardware support. Audio, Bluetooth, Vulkan,
screen recording, printing, Docker, SDDM takeover, gaming, and video decode
still require their individual gates. LightDM/XFCE remains the recovery path
until those gates pass.

Nautilus, GVfs-backed network mounts and applications whose dependency chains
activate UDisks are excluded because the PS4 internal SATA path is unsafe to
probe. Thunar preserves the core file-manager actions without touching
internal storage. `forbidden-closure-packages.txt` is enforced against the
complete Pacman transaction, not only the direct request list.

The package-by-package prerequisites and promotion procedure are maintained in
[`docs/BLOCKED-PACKAGE-RESTORATION.md`](../../docs/BLOCKED-PACKAGE-RESTORATION.md).

Regenerate and verify the committed package list with:

```bash
./scripts/compose-omarchy-full-profile
./scripts/compose-omarchy-full-profile --check
```
