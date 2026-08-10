# Omarchy PS4 compatibility ledger

This ledger is evidence-driven. `Supported` means a repeatable real-hardware
test exists; package installation alone is not support.

## Status vocabulary

| Status | Meaning |
|---|---|
| Supported | Passed the defined test repeatedly on supported hardware |
| Degraded | Usable with a documented limitation |
| Candidate | Existing upstream solution identified; test pending |
| Blocked | A lower dependency is known to fail |
| Needs replacement | Upstream was tested and cannot satisfy the requirement |
| Not tested | No reliable result yet |
| Excluded | Intentionally outside the current product boundary |

## Current ledger

| Layer | Component/capability | Status | Next evidence required |
|---|---|---|---|
| Baseline | Linux 5.4.247 boot | Supported | Reproduce twice from a clean build |
| Baseline | systemd graphical boot | Supported | Include in automated probe |
| Display | HDMI 1080p60 | Supported | Capture connector/mode and EDID |
| Display | Xorg modesetting | Supported | Record Xorg and DRM logs |
| Desktop | XFCE 4.20 | Supported | Two clean cold boots |
| Network | MT7668 Wi-Fi | Supported | Reconnect after cold boot |
| Network | Ethernet on Baikal | Needs replacement | Driver investigation after desktop gate |
| Graphics | Mesa EGL/OpenGL acceleration | Not tested | `eglinfo`, renderer, and stability test |
| Graphics | Vulkan | Not tested | `vulkaninfo` and render test |
| Wayland | Minimal compositor/client | Not tested | Native client plus input/output test |
| Desktop | Bare Hyprland | Not tested | Start, render, open terminal, exit cleanly |
| Session | UWSM | Not tested | Login, environment, logout, restart |
| Integration | XDG desktop portals | Not tested | File picker and screen-share portal tests |
| Media | PipeWire HDMI audio | Not tested | Playback, levels, restart, and recovery |
| Media | PipeWire screen capture | Not tested | Portal-mediated capture test |
| Shell | Minimal Quickshell | Not tested | Render, input, memory, and restart test |
| Shell | Omarchy Quattro configuration | Blocked | Bare Hyprland and Quickshell must pass |
| Input | USB keyboard/mouse | Candidate | Record complete real-hardware test |
| Input | DualShock 4 | Not tested | USB and Bluetooth mapping tests |
| Apps | Chromium Wayland rendering | Not tested | Browse, video, WebGL, and stability |
| Power | Clean shutdown | Not tested | Repeated shutdown then normal Orbis boot |
| Power | Suspend/hibernate | Excluded | Requires a separate safety decision |
| Installer | Stock Omarchy installer | Excluded | PS4-specific rootfs orchestration instead |
| Boot | Limine/GRUB integration | Excluded | PS4 loader and kexec are required |

## Promotion rule

A row can move to `Supported` only when its experiment record includes:

- console model and southbridge;
- firmware and loader versions;
- kernel commit and configuration identity;
- exact package/source versions;
- test commands and acceptance criteria;
- raw logs;
- observed result and known limitations;
- successful rollback or XFCE regression check.
