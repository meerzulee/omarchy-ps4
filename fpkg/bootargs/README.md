# PS4 boot profiles

- `6.18-baikal-install-usb.txt` boots the installer initramfs, reads the
  bundled rootfs from FAT32 label `PS4BOOT`, and targets only ext4 label
  `OMARCHY-PS4` on a USB device.
- `6.18-baikal-install-usb-lab.txt` permits the current locked-account XFCE
  artifact for private testing. It must never be selected by a release build.
- `6.18-baikal-product-splash.txt` is the intended normal profile. It keeps
  verbose earlycon evidence on Baikal UART, selects `console=null` so normal
  kernel/systemd chatter is not painted over HDMI, starts the initramfs splash,
  and disables only internal ATA device `1.00` with
  `libata.force=1.00:disable`.
- `6.18-baikal-internal-root.txt` is the schema-2 kernel-manager profile. Boot
  files come from internal Orbis storage; Linux requires one whole-device ext4
  USB labelled `OMARCHY-PS4` and never looks for `PS4BOOT`. It retains the
  Baikal boot console after the null console registers so initramfs, systemd
  and first-owner lifecycle events remain visible over UART. The first-owner
  form still writes directly to `/dev/tty1`; only diagnostic chatter is hidden.
- `6.18-baikal-debug-uart.txt` restores visible HDMI/fbcon messages plus
  `initcall_debug`; it does not disable SATA and is the rollback profile.
- `6.18-baikal-ultrawide-3440x1440.txt` belongs only to the uniquely named
  `6.18.44-ps4-baikal-ultrawide` test kernel. It requests the coherent
  3440x1440@50 raster and deliberately omits the forced 1080p EDID. The normal
  6.18 Baikal kernel plus `6.18-baikal-internal-root.txt` remains the rollback.

The SATA-disabled and splash profiles are candidates until separate bounded
UART cold-boot experiments accept them. Do not delete the debug profile.
