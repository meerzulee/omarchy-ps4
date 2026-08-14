# First hardware boot: Linux 6.18.44 and XFCE

Prepared: 2026-08-10

## Installed USB

- device: Kingston DataTraveler 3.0
- serial: `E0D55EA573F0194049CD0236`
- partition table: MBR
- partition 1: 1 GiB FAT32, active PS4 boot files
- partition 2: ext4, label `OMARCHY-PS4`, clean Arch/XFCE rootfs
- active kernel: `6.18.44-ps4-baikal`
- kernel source and provenance:
  [`meerzulee/linux-ps4`](https://github.com/meerzulee/linux-ps4)
- VRAM reservation: 1 GiB
- offline rollback: verified Linux 5.4 files under `recovery/` on FAT32

The active initramfs resolves `LABEL=OMARCHY-PS4`; it does not assume that the
USB root is `/dev/sda2` or `/dev/sdb2`.

## Before powering on

1. Keep the known-good 5.4 rollback files on the USB.
2. Connect the Linux USB, keyboard and mouse through the known-good USB path.
3. Set the PS4 to 1080p and disable HDR/wide-color output for the first test.
4. Connect UART ground, adapter RX to PS4 TX, and adapter TX to PS4 RX only if
   the adapter voltage and console pinout were already verified. Do not connect
   the adapter VCC pin to the console.
5. Start capture at 115200 baud, 8 data bits, no parity, one stop bit, no flow
   control before launching the Linux loader.

On macOS:

```sh
./scripts/capture-uart-macos /dev/cu.YOUR_USB_UART
```

The capture is written under `experiments/uart/`. The active command line uses
Baikal MMIO earlycon at `0xC890E000`, keeps the boot console, and deliberately
does not use the broken legacy `earlyprintk=serial,ttyS0` path.

## Active debug logging profile

The FAT boot partition currently contains this command line:

```text
root=LABEL=OMARCHY-PS4 rootfstype=ext4 rootwait rw earlycon=uart8250,mmio32,0xC890E000,115200n8 console=tty0 keep_bootcon 8250.nr_uarts=0 panic=0 loglevel=8 ignore_loglevel printk.devkmsg=on initcall_debug drm.edid_firmware=edid/1920x1080.bin video=HDMI-A-1:1920x1080@60D systemd.log_target=kmsg systemd.log_level=info pci=nocrs
```

This captures early kernel output, timestamps, all kernel severity levels,
driver initialization calls, and systemd messages over UART. The initramfs
also mirrors its own root-device and rescue diagnostics to `/dev/kmsg`.

`pci=nocrs` is required on the tested firmware 12.02 Baikal console. Its ACPI
PCI root bridge exposes no usable host window after E820 clipping, so Linux
otherwise rejects the firmware-programmed PS4 BARs and xHCI never discovers
the USB root device. The option keeps ACPI enabled but makes x86 use its
default root-bus IO and memory windows. It was selected from the kernel's own
`pci=nocrs` diagnostic and a prior same-console Linux 6.15 hardware trace in
which Baikal, xHCI, Kingston USB, root mount, systemd, and framebuffer all
proceeded with this option.

The kernel was built with `CONFIG_PRINTK_TIME`, `CONFIG_DEBUG_KERNEL`, full
kallsyms, frame pointers, stack traces, DWARF debug information,
`CONFIG_EARLY_PRINTK`, and the 8250 console. Full dynamic debug, ftrace and
pstore are intentionally not enabled in the first image because they add
noise, overhead, or require a separate persistent-memory design. They can be
enabled for a targeted second image if the first UART trace points to a driver
or timing problem.

## First-boot observations

Do not change packages or configuration during the first run. Record:

1. loader handoff and first UART line;
2. kernel panic, warning, interrupt storm, or deferred-probe messages;
3. xHCI and USB-storage enumeration;
4. resolution of `LABEL=OMARCHY-PS4` and systemd start;
5. amdgpu/Liverpool initialization and stable HDMI at 1080p60;
6. LightDM autologin and XFCE session;
7. keyboard and mouse input;
8. fan and temperature behavior;
9. clean shutdown.

If XFCE starts, open a terminal and run:

```sh
sudo journalctl -b -k --no-pager > /home/ps4/kernel-first-boot.log
omarchy-ps4-probe --experiment linux-6.18.44-xfce-cold-boot-1
```

The release rootfs has locked accounts and no password-based sudo or SSH.
Therefore the `sudo` command is expected to require a later development-access
decision; the unprivileged probe still captures most evidence. Do not add a
shared default password merely for convenience.

## Pass gate

Phase 1 passes only after two cold boots reach XFCE with stable HDMI, USB input,
the external ext4 root, package-manager access, and at least one network path.
The UART log and probe result must be retained for both boots. A first boot that
works once is encouraging evidence, not the completed gate.
