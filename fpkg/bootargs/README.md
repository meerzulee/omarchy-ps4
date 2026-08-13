# PS4 boot profiles

- `6.18-baikal-install-usb.txt` boots the installer initramfs, reads the
  bundled rootfs from FAT32 label `PS4BOOT`, and targets only ext4 label
  `OMARCHY-PS4` on a USB device.
- `6.18-baikal-install-usb-lab.txt` permits the current locked-account XFCE
  artifact for private testing. It must never be selected by a release build.
- `6.18-baikal-product-splash.txt` is the intended normal profile. It keeps
  verbose earlycon evidence on Baikal UART, omits `console=tty0`, starts the
  initramfs splash, and disables only internal ATA device `1.00` with
  `libata.force=1.00:disable`.
- `6.18-baikal-debug-uart.txt` restores visible HDMI/fbcon messages plus
  `initcall_debug`; it does not disable SATA and is the rollback profile.

The SATA-disabled and splash profiles are candidates until separate bounded
UART cold-boot experiments accept them. Do not delete the debug profile.
