# Omarchy Portal: portable PC and PS4 boot experience

Status: design idea, 2026-08-25. Nothing in this document is implemented or
accepted as supported hardware behavior yet.

## Idea

Create one encrypted, portable Omarchy installation that can travel between
normal x86-64 UEFI computers and a jailbroken PlayStation 4. Each platform has
its own trusted boot entrance and system profile, but both present the same
Omarchy-designed pre-OS experience and share the owner's files and desktop
identity.

The interface should feel like a small Omarchy UEFI menu. On a PC it begins as
a real UEFI application. On PS4 it is an imitation rendered by a program in the
Linux initramfs after the FPKG and GoldHEN have loaded the PS4 kernel. The PS4
does not gain or emulate UEFI firmware.

Working name: **Omarchy Portal**.

## User experience

### PC

```text
Power on
  -> UEFI loads EFI/BOOT/BOOTX64.EFI from the portable drive
  -> Omarchy Portal lists Portable Omarchy and existing EFI operating systems
  -> user selects Portable Omarchy
  -> a small Linux probe checks the hardware
  -> Portal recommends integrated, hybrid, dedicated or safe graphics
  -> user unlocks the encrypted system
  -> Omarchy starts with the matching PC profile
```

The PC menu may chainload an existing Windows or Linux EFI loader. Discovery
must be read-only and must not mount or modify Windows, BitLocker or another
operating system's root filesystem.

### PS4

```text
Start Orbis
  -> activate GoldHEN
  -> open the Omarchy FPKG
  -> choose Boot Omarchy
  -> FPKG loads the verified PS4 loader, kernel and initramfs
  -> quiet Omarchy splash
  -> PS4 edition of Omarchy Portal
  -> Portal verifies the console and portable root
  -> user unlocks the encrypted system
  -> Omarchy starts with the PS4 profile
```

The PS4 menu is not an EFI binary. It is the same Portal design and policy
implemented as a Linux initramfs program. It replaces visible kernel and
systemd chatter on HDMI; detailed logs remain available over UART.

Once Linux has replaced Orbis, returning to Orbis requires a restart. The PS4
Portal therefore offers **Restart to Orbis**, not EFI chainloading. GoldHEN and
the FPKG remain necessary after every cold boot. A portable drive cannot
jailbreak or cold-boot the PS4 by itself.

## Automatic platform routing

Do not rely on a guessed machine name. Use an explicit route plus independent
hardware verification.

```text
PC EFI entry passes:  omarchy.platform=pc
PS4 FPKG passes:      omarchy.platform=ps4
```

The probe then verifies the request:

- `pc` requires an EFI boot environment and a compatible x86-64 machine;
- `ps4` requires the expected Sony southbridge/platform devices and AMD
  Liverpool graphics path;
- an unknown platform or disagreement enters read-only recovery and does not
  mount a system profile read-write.

```text
requested=pc  + detected=pc  -> PC Portal and PC root
requested=ps4 + detected=ps4 -> PS4 Portal and PS4 root
anything else                -> safe recovery
```

This route is automatic. The owner should never be asked whether the current
machine is a PC or a PS4.

## Candidate portable-drive layout

```text
GPT
├── 1-2 GiB FAT32 EFI system partition
│   ├── EFI/BOOT/BOOTX64.EFI
│   ├── PC probe kernel/initramfs or signed UKI
│   ├── PC recovery image
│   └── signed compatibility manifest
│
└── LUKS2 encrypted Btrfs partition
    ├── @root-pc
    ├── @root-ps4
    ├── @home
    ├── @snapshots
    ├── @machine-profiles
    └── @package-cache
```

The PC and PS4 roots should be separate Btrfs subvolumes. They can originate
as copy-on-write snapshots of one Omarchy base, sharing unchanged extents, but
may safely carry different kernels, modules, graphics packages, services and
compatibility guards. This avoids making PS4-specific Mesa or platform changes
part of the normal PC root.

`@home` carries the owner's files, applications, themes and identity between
machines. Hardware-sensitive configuration such as outputs, scale, GPU mode,
audio routing and power behavior belongs in per-machine profiles rather than
one global configuration. Machine identifiers must remain local and must not
be sent anywhere without explicit consent.

The PS4 does not need to understand the FAT32 EFI partition. The FPKG continues
to manage its verified PS4 kernel/initramfs set under internal application
storage. The PS4 initramfs locates the encrypted portable root by a stable
filesystem or LUKS UUID and never enables or writes the internal SATA disk.

## Portal responsibilities

The common Portal core should:

- inventory CPU, memory, GPU, storage, network, audio and firmware state;
- compare detected identifiers with a pinned, signed compatibility manifest;
- distinguish **Verified**, **Supported**, **Experimental**, **Limited**,
  **Unsupported** and **Unknown** rather than claiming that detection equals
  support;
- verify the selected root, kernel/module relationship and required files;
- unlock LUKS without logging or storing the passphrase;
- select the correct Btrfs root and snapshot;
- preserve a known-good recovery path;
- expose concise information on screen and detailed diagnostics separately;
- make no internal-disk changes merely by opening the menu.

Candidate components:

```text
portal-core        hardware inventory, compatibility and profile policy
portal-ui          framebuffer/TUI interface and accessible input
portal-uefi        PC boot discovery and EFI chainloading
portal-initramfs   LUKS, Btrfs, snapshot and root handoff
portal-ps4         FPKG marker, PS4 verification and recovery actions
hardware-db        signed identifiers, support state and required profile
```

The common initramfs program can target an x86-64 baseline suitable for both
normal PCs and the PS4 Jaguar CPU. The PC and PS4 still use different kernels
and first-stage loaders.

## GPU selection on PCs

The base PC profile may contain AMD and Intel's open drivers together. Modern
NVIDIA support must be pinned to the selected kernel and kept in a deliberate
profile. Portal can offer:

- **Integrated** -- prefer battery life and the iGPU;
- **Hybrid** -- desktop on the iGPU with dGPU application offload;
- **Dedicated** -- prefer the dGPU when the display topology supports it;
- **Safe graphics** -- conservative recovery mode.

The recommendation cannot come from counting GPUs alone. Some laptop panels
are physically wired to only one GPU, some systems have a firmware-controlled
multiplexer, and NVIDIA generations require different driver treatment.
Unknown topology must default to a safe profile rather than risk a black
screen.

Omarchy already has useful, idempotent hardware detection and configuration
logic in `bin/omarchy-apply-hardware`, `install/hardware/nvidia.sh` and
`bin/omarchy-hw-hybrid-gpu`. Portable work should first extract their read-only
detection from their package installation and system mutation.

PS4 has one fixed Liverpool graphics path and does not show the PC GPU selector.

## Suggested screens

Healthy PS4 fast path:

```text
OMARCHY

PlayStation 4 Slim - Baikal B1
Omarchy drive - Ready

> Start Omarchy
  Previous snapshot
  Safe graphics
  System information
  Restart to Orbis
  Power off
```

Healthy PC fast path:

```text
OMARCHY

Portable system - Ready
Graphics - Hybrid recommended

> Start Portable Omarchy
  Graphics profile
  Windows
  Other Linux
  Recovery
  System information
```

Use the Omarchy Quattro visual language rather than copying a motherboard
vendor's firmware. A known healthy target may auto-start after a short visible
countdown; any input pauses the countdown. Missing media, verification failure
or an unknown platform must stop instead of auto-booting.

The first PS4 version may use a USB keyboard. Controller input requires its own
kernel/input validation and must not be claimed until accepted on hardware.

## Reference hardware idea

An actively cooled external NVMe hub such as
[SHARGE Disk Pro](https://sharge.com/products/disk-pro) is a possible reference
device, not a requirement or endorsement. Its external battery is a separate
accessory; it is not an internal UPS. The manufacturer documents that adding or
removing external PD power resets the USB connection briefly. A portable root
must therefore warn the user to connect power before boot and never change the
power source while the filesystem is mounted. The exact device still requires
firmware-boot, sustained-I/O and power-transition tests.

## Safety and trust

- Keep kernels, initramfs images, compatibility data and release manifests
  pinned and signed.
- Add Secure Boot support only after the unsigned development flow works; do
  not imply Secure Boot compatibility before it is tested.
- Keep the personal system encrypted with LUKS2.
- Never store a default password or recovery secret in the image.
- Enumerate internal disks read-only. Do not repartition, format, mount
  read-write or change EFI variables without a separate explicit operation.
- Keep PS4 internal SATA disabled and outside the Portal's storage scope.
- Treat a power loss or USB disconnect as a recoverable interrupted boot, not
  permission to repair or roll back automatically without evidence.
- Keep at least one known-good root snapshot and one safe graphics path.

## Implementation order

1. Specify the platform marker, hardware inventory and signed compatibility
   manifest schemas.
2. Prototype `portal-core` and a static initramfs UI with simulated PC and PS4
   inventories. No disk writes.
3. Insert the read-only PS4 Portal after the proven splash and before root
   mount. Preserve the existing direct-boot path as rollback.
4. Add PC UEFI entry and read-only discovery of existing EFI operating systems.
5. Add LUKS2 unlock and Btrfs root/snapshot selection.
6. Add per-machine configuration and the safe PC graphics profiles.
7. Qualify the portable disk across real Intel, AMD, NVIDIA, hybrid and PS4
   hardware; a VM proves logic, not physical compatibility.
8. Add signed atomic system updates and rollback only after the boot matrix is
   stable.

Each PS4 activation or boot change remains a bounded UART hardware experiment
under `docs/DEVELOPMENT-MODE.md`. PC compatibility claims require equivalent
recorded real-hardware evidence.

## Acceptance outline

Before calling Portal usable:

- the same prepared drive selects the PC route on verified PCs and the PS4
  route on the verified console without asking the user which platform it is;
- a forged or mismatched platform marker fails safely;
- PC discovery launches existing EFI operating systems without modifying them;
- PS4 Portal never touches internal SATA and retains UART diagnostics;
- LUKS unlock failure leaves all system roots unmounted;
- integrated, hybrid, dedicated and safe modes have independent hardware
  results on applicable machines;
- a failed update and a damaged current snapshot both recover through a
  known-good snapshot;
- repeated cold boots and one intentional USB-disconnect recovery test pass
  the acceptance count defined by the active plan.

This is a product direction, not a current support promise. The existing PS4
FPKG-to-external-root result proves one entrance to the design; portable PC
boot, encryption, multi-root selection and the Portal itself remain new work.
