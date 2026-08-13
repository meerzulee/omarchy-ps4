# Owner provisioning package

This package installs the PS4-specific first-boot owner program and its
disabled-by-default systemd service. Installing the package does not arm the
flow.

An image builder arms it only after confirming the release image has no
default user or password. For an already installed development root, mount the
USB filesystem from another Linux environment and use the guarded preparation
command:

```bash
sudo omarchy-ps4-prepare-for-owner --check /mnt
sudo omarchy-ps4-prepare-for-owner /mnt
```

On a terminal, the second command shows the Omarchy confirmation screen. An
image pipeline can use the explicit non-interactive form instead:

```bash
sudo omarchy-ps4-prepare-for-owner \
  --confirm PREPARE-FOR-ANOTHER-OWNER /mnt
```

It refuses `/`, non-USB filesystems, the wrong label, and any existing human
account other than the known `ps4` development account. Preparation removes
that account, development sudo/SSH access, LightDM autologin, cloned machine
identity, and SSH host keys before arming the next-boot service.

The program refuses any root that is not labelled `OMARCHY-PS4` and reached
through USB. It leaves `pending` in place after an error so setup can resume.
It does not touch the PS4 loader, kernel, initramfs, internal disk, LUKS,
Limine, SDDM, or Btrfs.
