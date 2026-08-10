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
