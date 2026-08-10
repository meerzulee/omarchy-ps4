# Sources and research notes

Accessed: 2026-08-10

Primary sources were preferred. Community guides are used to discover
projects and describe current user-facing practice, but hardware claims stay
labelled as maintainer reports until this project reproduces them.

## Kernel

- [rmuxnet/linux project index](https://github.com/rmuxnet/linux): current
  stable branch map for Aeolia/Belize 7.1.7 and Baikal 7.0.8.
- [Aeolia/Belize 7.1.7 snapshot](https://github.com/rmuxnet/linux/tree/d67b62838b413ba9ce49c61d73a314439e0cab67):
  recorded source commit.
- [Baikal 7.0.8 snapshot](https://github.com/rmuxnet/linux/tree/d8cbb8e912f59c352479f1158103e8ce7b6ca8c4):
  recorded source commit and `BAIKAL_DEVLOG.md`.
- [Baikal Ethernet experiment](https://github.com/rmuxnet/linux/commit/aa0fe25425d2183f04bfd33f67d05fb49f56e032):
  probe/PHY success, untested DMA traffic, and Wi-Fi regression are stated in
  the commit itself.
- [feeRnt/ps4-linux-12xx](https://github.com/feeRnt/ps4-linux-12xx): release
  lines for Baikal 5.4.247, Belize 5.15.15, and Aeolia/Belize 6.15.4 plus newer
  development branches.
- [crashniels/linux](https://github.com/crashniels/linux) and
  [oberdfr/kernel-ps4linux](https://github.com/oberdfr/kernel-ps4linux): modern
  forward-port and display/EDID references.
- [fail0verflow/ps4-linux](https://github.com/fail0verflow/ps4-linux) and
  [codedwrench/ps4-linux](https://github.com/codedwrench/ps4-linux): historical
  platform and forward-port ancestry.
- [Linux mainline mirror](https://github.com/torvalds/linux): GitHub code
  searches for `CONFIG_PS4`, `AEOLIA`, and PS4 `LIVERPOOL` returned no platform
  implementation. This supports “not found upstream,” not an impossibility
  claim.

## Boot and homebrew

- [PS4 Linux Loader](https://github.com/ps4-linux/ps4-linux-loader): v25,
  supported-firmware table, runtime southbridge detection, boot paths,
  `vram.txt`, and `bootargs.txt`. The repository has no root license file in
  the checked commit.
- [feeRnt PS4 initramfs](https://github.com/feeRnt/ps4-linux-initramfs): source,
  v1.0 release, root label/UUID support, storage options, and mixed component
  licensing.
- [PPPwn](https://github.com/TheOfficialFloW/PPPwn): public proof of concept and
  its firmware list through 11.00.
- [GoldHEN](https://github.com/GoldHEN/GoldHEN): features, public binary
  releases, and explicit statement that its source is private.
- [PSFree 9.00 port](https://github.com/kmeps4/PSFree): firmware-specific
  PSFree/Lapse reference.

## Graphics and userspace

- [DionKill PS4 video packages](https://github.com/DionKill/ps4-video-archlinux):
  PKGBUILDs, PS4 patches, and binary package repository. The checked binaries
  are Mesa 26.0.4, libdrm 2.4.131, matching 32-bit packages, and
  xf86-video-amdgpu 25.0.0.
- [Mesa upstream RadeonSI PCI IDs](https://gitlab.freedesktop.org/mesa/mesa/-/blob/main/include/pci_ids/radeonsi_pci_ids.h)
  and [libdrm upstream AMDGPU IDs](https://gitlab.freedesktop.org/mesa/drm/-/blob/main/data/amdgpu.ids):
  checked for PS4 IDs `0x9920`, `0x9922`, `0x9923`, `0x9924` and the names
  Liverpool/Gladius; no matches were found.
- [Arch Linux mesa package](https://archlinux.org/packages/extra/x86_64/mesa/):
  official Arch version was 26.1.6-1 on the snapshot date.
- [DionKill PS4 Linux tutorial](https://github.com/DionKill/ps4-linux-tutorial):
  current install practice, distro list, graphics update instructions, and
  Baikal internal-install warning.
- [PS4 Linux compatibility database](https://github.com/ps4-linux/ps4-linux.github.io):
  early JSON-backed database project; the checked tree contains many distro
  entries but only two kernel records and one initramfs record.
- [PS4 RetroBox](https://github.com/danyboy666/ps4-retrobox): current
  controller-oriented distribution reference and DS4 mapping work.

## Superseded and contradictory evidence

- [Baikal checklist, 2026-05-09](https://gist.github.com/rmuxnet/d4c6c26753bcff0d1ae24c69fc9575ec)
  reports a double-probe/over-current USB blocker before rootfs mount.
- The next day's `BAIKAL_DEVLOG.md` in the pinned Baikal kernel commit records
  the xHCI interrupt fix, USB enumeration, and full userland boot. It is newer
  and corresponds to code in the kernel tree, so this snapshot treats the May
  9 blocker as superseded.
- [PS4 bridge status, 2026-04-21](https://gist.github.com/rmuxnet/51b7e5a0413070d71e46b28b4ad6f4e0)
  lists CPU frequency, EDID/mode detection, automatic hotplug, GPU audio under
  load, UVD sequencing, and GPU optimization gaps. Later branches contain
  additional display work, so each item still needs current hardware testing.

## Negative-search scope

On 2026-08-10, GitHub repository and code searches were run for combinations
of `PS4`, `PS4 Linux`, `Hyprland`, `Quickshell`, and `Wayland`. No public PS4
Hyprland or Quickshell implementation was found. A negative search can miss
private repositories, chats, videos, unindexed forums, or differently named
work; the claim must remain “not found,” never “does not exist anywhere.”

Repository activity was checked from branch heads, commits, and releases.
GitHub's general `updated_at` field was not used as proof of source activity
because issue edits and metadata changes can update it.
