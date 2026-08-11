# Hardware and southbridge state

Snapshot date: 2026-08-10

## Identification rule

Do not choose a kernel from the retail name alone. The same broad Slim or Pro
family—and in current maintainer documentation even the same CUH model—can
appear with different southbridge variants. Detect the hardware, preserve the
raw evidence, then select a kernel.

For this project, the known console is recorded as:

| Field | Recorded value | Evidence |
|---|---|---|
| Console | PS4 Slim, CUH-2xxx family | Project hardware record |
| Southbridge | Baikal B1, subsystem `0x30201` | Project hardware record |
| Wireless | MediaTek MT7668 | Project hardware record |
| Firmware | 12.02 | Project hardware record |

## Network identity

| Runtime | Address | Services / status |
|---|---|---|
| Orbis with GoldHEN | `192.168.50.215` | Anonymous FTP `2121`; PayLoader `9090` when enabled |
| Arch Linux 6.18/XFCE | `192.168.50.125` | Internal MT7668 connected through a user-private NetworkManager profile; provisioned OpenSSH verified with the pinned key on 2026-08-11 |

These are current DHCP observations on the local `192.168.50.0/24` network,
not permanently assigned addresses. Reconfirm after each reboot until DHCP
reservations or stable hostnames are configured.

Public sources disagree on some Sony chip-part-number mappings. This snapshot
therefore uses the kernel-facing names Aeolia, Belize, and Baikal and does not
pretend that an unverified part-number table is authoritative.

## Current upstream picture

| Capability | Aeolia / Belize | Baikal | Evidence quality |
|---|---|---|---|
| Modern kernel line | 7.1.7 stable branch | 7.0.8 stable branch | Project fact |
| Boot to userspace | Reported working | Reported working after May 2026 MSI/xHCI fixes | Maintainer report |
| GPU / HDMI | Reported working; EDID/mode and hotplug work continues | Liverpool reported working; Gladius/Pro called untested in bring-up log | Maintainer report |
| USB | Reported working | Reported working after xHCI interrupt fix | Maintainer report |
| Internal SATA enumeration | Supported in established lines | Reported detected; first-probe stale-MSI race documented | Maintainer report |
| Internal Linux installation | Community path exists | Current guide says not reliable/supported | Guide plus maintainer report; not our test |
| Wi-Fi / Bluetooth | Model/chip-specific Marvell and MediaTek work exists | MT7668 reported working | Maintainer report |
| Ethernet | `sky2` fixes remain experimental | DWMAC probe/PHY works, TX/RX unproven; experimental driver breaks Wi-Fi | Maintainer report and commit text |
| HDMI audio | Fixed in modern branch reports | Not yet proven by us | Maintainer report |
| CPU dynamic frequency | Listed incomplete | Listed incomplete | Maintainer status list |
| GPU clocking | Listed working | Needs our measurements | Maintainer status list |
| Display hotplug / EDID | Manual reprobe and wrong-mode issues remain in April status report; later fixes exist | Needs board-specific test | Conflicting/evolving maintainer reports |
| Fan / thermal / LED | Modern driver paths exist | Modern bring-up reports working | Maintainer report; safety-sensitive |

This is not a promise that every cell works on every board. The upstream
kernel README itself asks for model-by-model validation.

## Our Baikal evidence

The older Linux 5.4.247 baseline is the only stack currently promoted to
`Supported` in this project:

- kernel, initramfs, and systemd reach the graphical target;
- HDMI produces 1920×1080 at 60 Hz;
- XFCE 4.20 and Xorg modesetting work;
- MT7668 Wi-Fi, SSH, and package downloads work;
- external ext4 rootfs expansion works;
- Baikal Ethernet does not work;
- audio, Bluetooth, DualShock 4, EGL/OpenGL, Vulkan, repeated cold boots, and
  clean shutdown still lack complete recorded tests.

The freshly rebuilt XFCE rootfs has passed off-console validation only. Until
it cold-boots twice on the PS4, it is an artifact candidate, not a hardware
baseline.

## Safety notes

- A kernel reporting a fan or thermal interface is not enough. Before changing
  thresholds, verify temperature reads, fan RPM response, persistence, and
  recovery after a full power cycle.
- The Baikal research notes document damage caused by a legacy fan-control
  buffer-length bug. We will not reuse legacy fan-write tools blindly.
- Suspend and hibernate remain excluded until their power, storage, and Orbis
  recovery behavior is deliberately tested.
- Internal-disk support is not an invitation to write PS4 partitions. The MVP
  stays on an explicitly identified external device and uses filesystem labels
  or UUIDs.
