# Project map

Snapshot date: 2026-08-10

“Active” below means meaningful source or release activity in 2026. It does
not mean we have tested the project on our console.

## Core boot and hardware stack

| Project | Snapshot | State | Use here |
|---|---|---|---|
| [rmuxnet/linux](https://github.com/rmuxnet/linux) | Aeolia/Belize `zaebiz/7.1.7-Stable` at `d67b6283`; Baikal `baikal/7.0.8-Stable` at `d8cbb8e9` | Active, experimental hardware platform | Primary modern-kernel candidate |
| [feeRnt/ps4-linux-12xx](https://github.com/feeRnt/ps4-linux-12xx) | 5.4.247 Baikal, 5.15 Belize, 6.15 Aeolia/Belize, and newer staging branches; latest checked head `4a10fe66` | Active collection of stable and experimental lines | Known-good Baikal source plus comparison/fallback branches |
| [crashniels/linux](https://github.com/crashniels/linux) | PS4 branches through 6.15, including a Baikal branch | Active reference work | Trace patch provenance; do not select by default branch |
| [oberdfr/kernel-ps4linux](https://github.com/oberdfr/kernel-ps4linux) | 6.17-era PS4 branches and a 6.17.1 release | Recent reference work | Display/EDID and forward-port comparison |
| [ps4-linux/ps4-linux-loader](https://github.com/ps4-linux/ps4-linux-loader) | v25, commit `9acef9fb`, released 2026-07-25 | Active | Loader candidate; license/provenance audit required |
| [feeRnt/ps4-linux-initramfs](https://github.com/feeRnt/ps4-linux-initramfs) | v1.0, main `04d91daa`, BSD-3-Clause scripts plus separately licensed binaries/firmware | Active | Preferred auditable initramfs base |
| [rmuxnet/ps4-hwinfo-collect](https://github.com/rmuxnet/ps4-hwinfo-collect) | `8a0fa75f`, 2026-07-01 | Active | Compare with and improve our evidence collector |

Important branch rule: `rmuxnet/linux` uses its default branch as a project
index. Kernel consumers must pin a named hardware branch and commit, never the
repository default.

## Graphics and userspace

| Project | Snapshot | State | Use here |
|---|---|---|---|
| [DionKill/ps4-video-archlinux](https://github.com/DionKill/ps4-video-archlinux) | `ccea8d2c`; binary repo contains Mesa 26.0.4, libdrm 2.4.131, their 32-bit variants, and xf86-video-amdgpu 25.0.0 | Active candidate | Rebuild recipes, pin all ABI-coupled packages, sign our output |
| [Ps3itaTeam/ps4linux-video-drivers](https://github.com/Ps3itaTeam/ps4linux-video-drivers) | Last source push 2021 | Historical | Patch ancestry only |
| [DionKill/ps4-linux-tutorial](https://github.com/DionKill/ps4-linux-tutorial) | `1609a51d`, 2026-07-25 | Active guide | Discovery and cross-checking, never substitute for tests |
| [ps4-linux compatibility database](https://github.com/ps4-linux/ps4-linux.github.io) | `0e83119d`, 2026-05-24 | Active but sparse | Potential schema/reference; not yet complete enough as authority |
| [ErkkolaMaitohappo Arch images](https://github.com/ErkkolaMaitohappo/arch-ps4-aur-smth-fork) | XFCE/KDE releases in 2026 | Active binary distro option | Compare package choices; do not inherit as our base |
| [PS4 Arch-based distros](https://github.com/ErkkolaMaitohappo/ps4-arch-based-distros) | Artix and Nyarch releases in 2026 | Active binary distro option | Ecosystem reference only |
| [PS4 RetroBox](https://github.com/danyboy666/ps4-retrobox) | v1.7.x releases in July 2026; master `6c79062a` | Active | Controller-first UX and DS4 mapping reference |

The public PS4 video repository instructs users to configure `SigLevel =
Optional`. That is acceptable as a community convenience, not as our product
update policy. We need signed packages and an atomic compatibility set for
Mesa, libdrm, LLVM dependencies, 32-bit libraries, and Xorg/Wayland consumers.

## Entry-point and homebrew context

These projects enable the Orbis side of the chain. They are not Linux drivers.

| Project | Verified public scope | State | Relevance |
|---|---|---|---|
| [PPPwn](https://github.com/TheOfficialFloW/PPPwn) | Proof-of-concept kernel RCE lists firmware 7.00 through 11.00; adapting stage 2 is required for homebrew | Stable historical reference | Explains one common entry path, not our 12.02 path |
| [GoldHEN](https://github.com/GoldHEN/GoldHEN) | Public binary releases through 2.4b18; source is explicitly private | Maintained binary project | Provides binloader/homebrew environment on supported setups |
| [PSFree 9.00 port](https://github.com/kmeps4/PSFree) | WebKit + Lapse port for 9.00 | Active but firmware-specific | Reference only |
| [archived PS4 Linux payloads](https://github.com/ps4boot/ps4-linux-payloads-archive) | Prebuilt payload archive for 5.05–12.02 | Archived in 2026 | Historical binaries; superseded by the current loader repo |

Our console's 12.02 HEN/GoldHEN path is a **project test fact** from the sibling
hardware work. Its exact public exploit-host provenance is not yet good enough
for redistribution and must be captured before an installer can own that part
of the journey.

## Historical roots worth preserving

| Project | Role |
|---|---|
| [fail0verflow/ps4-linux](https://github.com/fail0verflow/ps4-linux) | Original PS4 Linux platform and device work; last PS4 branch commit in 2016 |
| [fail0verflow/ps4-kexec](https://github.com/fail0verflow/ps4-kexec) | Original BSD-licensed kexec payload reference |
| [codedwrench/ps4-linux](https://github.com/codedwrench/ps4-linux) | Important 5.15 forward-port ancestry used by later trees |
| [fail0verflow PS4 Radeon patches](https://github.com/fail0verflow/ps4-radeon-patches) | Original Liverpool userspace patch ancestry |

Old does not mean useless: these repositories are often the clearest place to
understand why a patch exists. They should not be treated as current binaries.
