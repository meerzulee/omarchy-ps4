# PS4 Linux world state

Snapshot date: 2026-08-10

## Bottom line

PS4 Linux is usable, actively developed, and still a specialist platform. The
working path is a chain of community components:

```text
firmware-specific entry point / homebrew environment
  -> PS4 Linux loader payload
  -> PS4-patched Linux kernel + initramfs
  -> external root filesystem or an Orbis-hosted image
  -> PS4-patched graphics userspace
  -> desktop and applications
```

In 2026, active work exists at every important lower layer:

- `rmuxnet/linux` carries Linux 7.1.7 for Aeolia/Belize and a separate Linux
  7.0.8 Baikal branch.
- `ps4-linux/ps4-linux-loader` released v25 on 2026-07-25, with runtime
  firmware/southbridge detection and a documented firmware table through
  13.52. Question marks in that table are upstream's, not confirmations by us.
- `feeRnt/ps4-linux-initramfs` provides a source-available rescue/initramfs
  path with label/UUID root discovery.
- `DionKill/ps4-video-archlinux` publishes PS4-patched Mesa, libdrm,
  32-bit counterparts, and Xorg AMDGPU packages for Arch.
- Current Arch-oriented distro images, an installation guide, a hardware
  collector, a compatibility-database project, and RetroBox all received 2026
  work.

That activity does **not** make PS4 a normal upstream Linux target. The kernel,
loader, firmware, and graphics stack still require PS4-specific integration,
and support varies by southbridge and sometimes by exact board revision.

## What exists today

| Area | Current public option | Confidence | Our decision |
|---|---|---|---|
| Known-good Baikal desktop | Linux 5.4.247 + Arch + XFCE | Project test | Preserve as rollback baseline |
| Modern Aeolia/Belize kernel | `rmuxnet/linux` 7.1.7 stable branch | Project fact; maintainer hardware reports | Candidate after baseline gate |
| Modern Baikal kernel | `rmuxnet/linux` 7.0.8 stable branch | Project fact; maintainer hardware reports | First modern-kernel candidate for our console |
| Conservative kernel fallbacks | `feeRnt/ps4-linux-12xx` 5.4/5.15/6.15 lines | Project fact; mixed hardware reports | Keep for bisecting, not as one universal kernel |
| Loader | PS4 Linux Loader v25 | Project fact | Pin and audit; do not rebuild from a moving branch |
| Initramfs | feeRnt v1.0 plus DionKill's packaged installer image | Project fact | Prefer source-auditable feeRnt base and own the PS4 policy layer |
| Arch graphics | PS4 Mesa/libdrm/Xorg package recipes and binary repo | Project fact | Rebuild and sign our own exact compatibility set |
| Desktop | XFCE, KDE, LXQt and other prebuilt images exist | Project fact | Use our clean XFCE image rather than inherit an opaque distro image |
| Gaming shell | RetroBox v1.7.x includes a DualShock 4 mapping path | Project fact | UX reference only; test components independently |
| Documentation | DionKill guide and early structured compatibility database | Project fact | Useful discovery sources, not sole truth |

## What does not exist, or is not publicly proven

The following wording is deliberate: “not found” means no verifiable public
implementation was found in this snapshot's search scope.

| Missing or unproven item | Why it matters |
|---|---|
| Mainline Linux PS4 platform support | PS4 kernels remain downstream forks with platform, bridge, interrupt, storage, USB, ICC, thermal, and GPU changes. |
| Stock Mesa support for Liverpool/Gladius | The current PS4 package still adds the PS4 PCI IDs and family handling; the same identifiers were not found in current upstream Mesa/libdrm source. |
| One modern kernel proven across every southbridge and board revision | Current stable work is split between Aeolia/Belize and Baikal, with model-specific caveats. |
| A reproducible, signed, update-safe PS4 Arch distribution | Images exist, but we found no single public product with pinned rootfs inputs, signed PS4 graphics sets, rollback, and hardware acceptance evidence. |
| A verified Hyprland-on-PS4 implementation | No public GitHub repository or code result was found for PS4 Linux + Hyprland. |
| A verified Quickshell or Omarchy-on-PS4 implementation | No public implementation or hardware evidence was found. |
| Working Baikal Ethernet | The experimental DWMAC branch creates an interface and finds the PHY, but its own commit says TX/RX is untested and the driver breaks Wi-Fi. |
| Reliable Baikal internal-install product path | Modern kernels report SATA enumeration, but the current installation guide still excludes Baikal from reliable internal installation. Detection is not an installer guarantee. |
| Complete public compatibility data | The structured database is young and sparse; community results remain scattered across repositories, forums, chats, and binary releases. |
| Clean redistribution provenance for every dependency | The loader repository has no root license file, PS4 graphics patches have unclear standalone licensing, and some required firmware is proprietary or privately fetched. |

## What changed since the older picture

The largest change is Baikal. It is no longer accurate to say Baikal is simply
stuck on Linux 5.4. The modern tree documents a successful Linux 7.0 bring-up,
including GPU, HDMI, USB, internal SATA enumeration, Wi-Fi, Bluetooth, SDHCI,
fan, LED, and power-button support. We have **not** reproduced that claim on
our console, and Ethernet remains open.

An older 2026-05-09 Baikal checklist says USB over-current/double-probe stopped
the rootfs from mounting. The kernel tree's 2026-05-10 development log records
the MSI/xHCI fix and a full userspace boot. The newer report supersedes the old
blocker for upstream status; both remain in `SOURCES.md` so the reasoning is
auditable.

The graphics situation is also healthier but still downstream. Arch packages
track Mesa 26.0.x with matching 32-bit packages, while official Arch was at
Mesa 26.1.6 on the snapshot date. A normal full-system update can therefore
replace the compatibility set unless package policy prevents it.

## Consequence for Omarchy PS4

Our order remains correct:

1. Reproduce the clean XFCE baseline on the real Baikal console.
2. Measure its DRM, EGL/OpenGL, input, network, and audio state.
3. Test the pinned Baikal 7.0.8 kernel without changing the userspace.
4. Rebuild the PS4 graphics set from source and test it on XFCE.
5. Prove a minimal Wayland compositor before Hyprland.
6. Add bare Hyprland, then UWSM/portals/PipeWire, then Quickshell, and only then
   the Omarchy configuration.

XFCE is not the intended final shell. It is the control group that prevents a
kernel, Mesa, Wayland, or Omarchy failure from being mistaken for another
layer's problem.
