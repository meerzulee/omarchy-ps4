# Omarchy PS4 package repository

Research date: 2026-08-13

## Upstream deployment

Omarchy publishes its Arch packages with the MIT-licensed
[`omacom-io/omarchy-pkgs`](https://github.com/omacom-io/omarchy-pkgs)
tooling. This review is pinned to release commit
`84b86195cdeb0ddc71b58810b208df18f6907ffb`, which released Omarchy
`4.0.0rc3`.

The public implementation has five parts:

1. Each `pkgbuilds/<name>/` directory contains a PKGBUILD and small JSON file
   describing its source and release ring.
2. Arch containers build, sign, and run `repo-add`; the repository host itself
   is Ubuntu in production.
3. One repository host keeps the complete package tree and the private signing
   key. Faster machines may build large packages and transfer only the unsigned
   result to that host.
4. `rclone` publishes the tree to `pkgs.omarchy.org:omarchy-pkgs`. Package
   objects are uploaded before the repository database, so clients never see a
   database entry for a missing object. Remote deletion is an explicit
   `--prune` operation.
5. Systemd timers check versions and release `edge` and `stable` four times a
   day. A GitHub Actions workflow synchronizes selected AUR recipes through a
   reviewable pull request.

The public code does not identify the object-storage provider or expose its
`rclone` configuration. `pkgs.omarchy.org` is served through Cloudflare, but
that only proves the public proxy/CDN layer, not where the origin bucket lives.

The official package recipes contain `omarchy-4.0.0rc3-1` and
`omarchy-settings-4.0.0rc3-1`. Packages have detached signatures.
The database had no detached signature and upstream's RC Pacman configuration
used `Optional TrustAll` for the Omarchy repository.

## PS4 adaptation

Fork the deployment tooling into a separate `omarchy-ps4-pkgs` repository when
publication is authorized. Keep build recipes out of the desktop repository so
package publication, signing access, and desktop development have separate
permissions.

Start with one `x86_64` repository. Hardware variants belong in package names,
not separate mirrors:

- `omarchy-ps4-keyring`
- `linux-ps4-baikal` and `linux-ps4-baikal-headers`
- `omarchy-ps4`
- `omarchy-ps4-settings`
- `omarchy-ps4-provisioning`
- PS4 Mesa, firmware, or loader packages only after their individual hardware
  gates pass

Use `edge` for development experiments and promote the exact tested artifacts
to `stable`. Never rebuild a package during promotion. The compatibility
manifest must select the kernel package for the detected southbridge.

The server can be a small systemd Linux VM plus any reliable object store that
`rclone` supports. The minimum deployment is:

```text
build machine -> unsigned package + SHA-256 -> signing host
signing host  -> signed package + signed repo DB -> object storage
object storage -> HTTPS/CDN -> pacman clients
```

Do not copy Omarchy's production key or trust configuration. Generate an
offline Omarchy PS4 signing primary key, give the repository host a restricted
signing subkey, and ship only the public key through
`omarchy-ps4-keyring`. Require trusted signatures for packages and databases:

```ini
[omarchy-ps4]
SigLevel = Required TrustedOnly
Server = https://packages.example.invalid/stable/$arch
```

`repo-add --sign --key <fingerprint>` creates a detached database signature.
Release manifests for kernels, initramfs images, root filesystems, and PS4
payload metadata need their own offline-verifiable signature because Pacman
does not install those boot artifacts.

## Publication gate

Before the first public upload:

1. Create the separate repository and retain the upstream MIT notice.
2. Generate and back up the signing key offline; document rotation and
   revocation.
3. Configure a private signing host and a provider-neutral `rclone` remote.
4. Build packages from pinned source commits in OrbStack locally or in an
   isolated Linux builder.
5. Verify package contents, signatures, repository database signature, and a
   clean-machine install.
6. Publish to `edge`, complete the bounded UART acceptance count, then promote
   those same bytes to `stable`.

No hosting account, DNS record, key, public repository, or release has been
created yet.
