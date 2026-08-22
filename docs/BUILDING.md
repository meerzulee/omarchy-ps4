# Building the XFCE baseline

The baseline builder runs only through OrbStack and always targets x86-64,
matching the PS4's AMD Jaguar CPU. It pins both the Arch container digest and
the Arch Linux Archive date.

Verify the safe local build environment:

```bash
docker context show
# must print: orbstack
```

Build a release-style image with locked accounts and no SSH service:

```bash
./scripts/build-xfce-rootfs
```

For real-hardware development, explicitly provide your public SSH key:

```bash
./scripts/build-xfce-rootfs --authorized-key ~/.ssh/id_ed25519.pub
```

That development option enables SSH for `ps4`, disables all SSH password
authentication, assigns an unknown random password hash, and grants key-backed
passwordless sudo. The public key is passed as a BuildKit secret so it is not
left in an intermediate image layer.

The default output directory contains:

- `omarchy-ps4-xfce-rootfs.tar.zst` — root filesystem archive;
- `manifest.env` — exact image, archive hash, build mode, and package count;
- `packages.txt` — installed package versions.

The root filesystem expects its ext4 partition to be labelled
`OMARCHY-PS4`. No `/dev/sdX` name is embedded in the image.

The container build validates the XFCE session, LightDM, NetworkManager,
graphics probes, PipeWire tools, locked root account, and graphical systemd
target before exporting anything.

Pacman's download sandbox is disabled only inside the cross-architecture image
build because OrbStack's x86-64 translation cannot install Pacman's seccomp
filter. The builder removes `DisableSandbox` before exporting the rootfs, so
Pacman's normal runtime security policy remains intact on the PS4.

## Build the stable gift USB image

The release path is separate from the older XFCE baseline. It consumes the
controlled offline package snapshot and the module archive produced by the
matching `linux-ps4-kernel` build:

```bash
./scripts/build-package-snapshot \
  --output output/package-snapshot/omarchy-ps4-4.0.0-usb-dev \
  --package-source output/omarchy-packages-4.0.0-usb-dev-r3 \
  --cache output/package-snapshot-cache/4.0.0-usb-dev

./scripts/build-gift-rootfs
./scripts/build-usb-image \
  --rootfs output/gift-rootfs/omarchy-ps4-gift-4.0.0.tar.zst
```

All container work runs through the active OrbStack Docker context. The gift
root contains no owner account or usable default password. Its first boot grows
the ext4 filesystem, then starts the resumable owner setup before LightDM. The
USB builder creates one whole-device ext4 filesystem labelled `OMARCHY-PS4`
and compresses it as a directly flashable `.img.xz`; it does not create a
partition table or FAT boot partition.

The kernel, initramfs, boot arguments and loader are not copied into the USB
image. They belong to the separately built private kernel-manager FPKG. The
gift-root builder refuses a kernel module archive that is not covered by the
kernel release's `SHA256SUMS`.

For a bounded macOS lab flash, `scripts/flash-usb-image-macos` rechecks the
explicit whole-disk identifier, USB/removable/physical flags, model, capacity,
compressed image hash and uncompressed size before writing. It then reads back
the exact image length, requires the raw SHA-256 to match, and ejects the USB.
It is a developer verification helper; end users follow the graphical flashing
flow in `docs/GETTING-STARTED.md`.
