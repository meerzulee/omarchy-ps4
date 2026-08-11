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
| Baseline | Linux 5.4 systemd graphical boot | Supported | Include in automated probe |
| Baseline | Linux 6.18.44 external root/systemd boot | Degraded | A51 passed; diagnose internal-SATA delay, then repeat a true cold boot |
| Storage | Linux 6.18 Baikal MSI/xHCI/USB root | Degraded | Eliminate internal-SATA I/O retries and repeat cleanly |
| Display | Linux 5.4 HDMI 1080p60 | Supported | Capture connector/mode and EDID |
| Display | Linux 5.4 Xorg modesetting | Supported | Record Xorg and DRM logs |
| Display | Linux 6.18 HDMI 1080p60 | Candidate | A43 and A51 displayed XFCE; repeat unchanged from a true cold boot |
| Desktop | XFCE 4.20 | Supported | Two clean cold boots |
| Network | MT7668 Wi-Fi | Supported | Reconnect after cold boot |
| Network | OpenSSH over MT7668 | Candidate | A51 key login passed at `192.168.50.125`; repeat after cold boot |
| Network | Ethernet on Baikal | Needs replacement | Driver investigation after desktop gate |
| Graphics | Mesa EGL/OpenGL acceleration | Not tested | `eglinfo`, renderer, and stability test |
| Graphics | Linux 6.18 amdgpu command submission | Candidate | A25 had no ring/fence storm; verify renderer after visible HDMI |
| Graphics | Vulkan | Not tested | `vulkaninfo` and render test |
| Wayland | Minimal compositor/client | Candidate | A57 visibly rendered a native EGL client in nested Weston; direct DRM/seat test remains |
| Desktop | Bare Hyprland | Candidate | A64/A65 direct DRM, physical 1080p60, native terminal and USB input passed; repeat from a cold boot |
| Session | UWSM | Candidate | A73 direct login/runtime and A75 clean compositor stop passed; stopping returns to the LightDM greeter, and unattended XFCE recovery needs a connected retry |
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
