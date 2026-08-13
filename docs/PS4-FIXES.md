# PS4 porting fixes

This is the handoff list for turning the laboratory root into a reproducible
Omarchy PS4 image. It records PS4-specific deltas only. Upstream Omarchy files
stay unchanged unless an accepted hardware result requires an override.

Status meanings:

- **Accepted** — passed the current real-hardware experiment.
- **Degraded** — required for a usable result, with a known limitation.
- **Candidate** — implemented or isolated, but its hardware gate is open.
- **Design** — product policy; the final installer/image still needs it.

The experiment details and UART evidence are in
[`experiments/SESSIONS.md`](../experiments/SESSIONS.md). General support claims
remain in [`docs/COMPATIBILITY.md`](COMPATIBILITY.md).

## Boot and storage

| Status | PS4 delta | Image/install owner |
|---|---|---|
| Degraded | Boot the PS4-patched 6.18.44 Baikal kernel from `linux-ps4-kernel/`; never install or update it as stock Arch `linux`. | FPKG boot bundle and signed release manifest |
| Accepted | Resolve the Linux root as `LABEL=OMARCHY-PS4`; never persist `/dev/sdX`. | `rootfs/initramfs/init`, `rootfs/xfce/overlay/etc/fstab`, installer preflight |
| Accepted | Use Baikal early UART at `0xC890E000`, keep UART logging, apply `pci=nocrs intremap=off`, force the proven `HDMI-A-1:1920x1080@60D` mode, and carry the pinned EDID firmware. | `fpkg/bootargs/` |
| Candidate | Disable only internal ATA target `1.00` with `libata.force=1.00:disable` in the product profile. The debug profile deliberately leaves SATA unchanged. | `fpkg/bootargs/6.18-baikal-product-splash.txt` |
| Design | Install only to a preformatted external USB root and refuse automatic formatting or internal-disk targets. | `scripts/prepare-usb-linux`, `rootfs/initramfs/install-rootfs` |
| Candidate | Render the pinned native Omarchy logo and Tokyo Night colors directly to the PS4 framebuffer; keep repainting through initramfs so mode changes cannot permanently overwrite it, while early logs continue over UART. Do not install Plymouth into the custom loader chain. | `rootfs/initramfs/omarchy-splash.c`, product bootargs |

## Display and desktop

| Status | PS4 delta | Image/install owner |
|---|---|---|
| Degraded | Export `AMD_DEBUG=notiling`. It makes the legacy DCE8 path usable but does not eliminate every compositor artifact. | `packages/omarchy-ps4-settings/10-omarchy-ps4`, `portable/10-omarchy-ps4-portable` |
| Degraded | Keep XFCE/LightDM as recovery and use Xorg modesetting with `AccelMethod "none"`. This trades acceleration for stable recovery output. | `rootfs/xfce/overlay/etc/X11/xorg.conf.d/20-omarchy-ps4-modesetting.conf` |
| Accepted | Pin HDMI to `1920x1080@60`, scale `1`, and disable Hyprland animations, blur and shadows for the current POC. | `profiles/quattro-beta/config/hypr/monitors.lua`, `profiles/quattro-beta/config/hypr/looknfeel.lua` |
| Accepted | Start exactly one Quattro shell; do not import PS4 autostart twice. | `packages/omarchy-ps4-settings/ps4-hyprland.lua`, `ps4-autostart.lua` |
| Accepted | Keep the bar only at the top and disable unqualified battery, Bluetooth, monitor-control, night-light and power plugins. | `packages/omarchy-ps4-settings/ps4-shell.json` |
| Accepted | Keep the upstream two-color active Hyprland border. EXP-20260813-001-A25 proved its solid replacement does not fix the artifact; the photographed fault is the separate Quickshell menu-card border. | `profiles/quattro-beta/config/hypr/looknfeel.lua` remains unchanged |
| Candidate | The Quickshell menu-card border is the broken renderer: width zero removes the artifact but also removes the outline. Keep this diagnostic override out of release UX until a visible low-cost replacement passes. | `packages/omarchy-ps4-settings/ps4-shell.toml` |
| Accepted | Keep VRR/FreeSync disabled in Linux and in the monitor. The legacy fixed 1080p60 bridge does not expose an accepted adaptive-sync path. | PS4 monitor profile and setup guidance |
| Candidate | Increase UI scale only in a separate display experiment. The accepted value remains `1`; fractional scaling may increase legacy-GPU load. | `profiles/quattro-beta/config/hypr/monitors.lua` |

## Portable and user-session integration

| Status | PS4 delta | Image/install owner |
|---|---|---|
| Accepted | Preserve the pinned portable `OMARCHY_PATH`; do not source upstream `env-bootstrap`, which resets it to `/usr/share/omarchy`. | `portable/10-omarchy-ps4-portable` |
| Accepted | Strip and reject macOS AppleDouble `._*` files. They were interpreted as Lua modules and broke Quattro startup. | `scripts/build-omarchy-portable`, `portable/install`, bundle test |
| Accepted | Register `omarchy.ttf` in the user font hierarchy and refresh fontconfig. This restores the far-left Omarchy bar icon. | `portable/install` |
| Accepted | Activate Quattro's Hyprland XDG terminal preference so `Super+Enter` opens native Wayland Foot instead of XFCE Terminal. | `portable/install`, `config/hyprland-xdg-terminals.list` in the bundle |
| Accepted | Use RC3's 14px desktop text preset at compositor scale 1, but disable bar geometry/icon scaling with the font. The Omarchy and Nerd fonts are present; 16px does not fit the 1080p bar and enlarged icon canvases corrupt on DCE8. | `packages/omarchy-ps4-settings/ps4-shell.toml` |
| Accepted | Initialize one of the 22 included Quattro themes through the upstream theme engine. Tokyo Night plus its managed wallpaper passed on the current lab root. | image owner provisioning |
| Accepted | Use a compact PS4-aware Fastfetch profile and the pinned Omarchy About icon. Report Liverpool explicitly because generic PCI naming misidentifies device `1002:9923` as Kingston/Clayton. Do not run Fastfetch automatically in every shell. | `packages/omarchy-ps4-settings/ps4-fastfetch.jsonc`, portable config |
| Design | Use deferred-owner provisioning for username, password, hostname and timezone. Never ship the development `ps4` credential in a release image. | `packages/omarchy-ps4-provisioning` |

## Hardware and service guards

| Status | PS4 delta | Image/install owner |
|---|---|---|
| Accepted | Do not autostart UDisks/udiskie or generic disk utilities while internal SATA is exposed; prior probing produced internal-disk I/O failures. Use Thunar without GVfs/UDisks activation. | `profiles/omarchy-full/blocked-packages.txt`, PS4 launch wrappers |
| Accepted | Keep Hyprsunset/night-light disabled. Gamma LUT programming blacked out this legacy DCE8 display path. | `packages/omarchy-ps4-settings/ps4-menu.jsonc`, disabled command guards |
| Accepted | Disable Quattro's automatic idle service by default on PS4 so it cannot launch the screensaver or five-minute lock. This is independent of Hyprsunset; manual locking remains. | `packages/omarchy-ps4-settings/ps4-shell.json` |
| Design | Guard generic PC hardware, brightness/DDC, power-profile, hibernation, Limine, Plymouth, firmware-update, factory-reset and unrestricted update commands. Preserve upstream originals for audit. | `packages/omarchy-ps4/ps4-disabled-commands.txt` |
| Candidate | Audio, Vulkan, hardware video decode, screen capture, Bluetooth, printing, Docker and SDDM remain gated even if their packages are present. | `docs/COMPATIBILITY.md`, full profile gates |

## What “full Omarchy” means here

The portable bundle contains the pinned Quattro commands, shell, menus,
configuration and all 22 themes. It is not the full workstation root. The
PS4-safe full profile currently contains 153 package names; the live POC still
lacks 100 of them. Applications and services are added from
[`profiles/omarchy-full/packages.txt`](../profiles/omarchy-full/packages.txt)
only after their dependency gates pass.

The final image composition order is:

1. Install the PS4 kernel/modules and boot profiles from their pinned release.
2. Build the Arch base plus XFCE/LightDM recovery root.
3. Install `omarchy-ps4`, `omarchy-ps4-settings` and the accepted package set.
4. Install the pinned Quattro runtime and PS4-owned configuration.
5. Mark deferred-owner provisioning pending; remove every development
   credential and autologin override.
6. Run rootfs, package, boot-profile and portable-bundle tests before creating
   the image manifest.

An item moves from Candidate to Accepted only after its bounded UART session is
closed with the operator outcome and rollback recorded.
