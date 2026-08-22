# Omarchy PS4 Quattro 4.0.0 developer gift bundle

This is a private acceptance bundle for turning the current external-USB
development system into a reviewable gift candidate. It is not a public
release and it is not a standalone installer image.

## Included

- the three pinned native Arch packages:
  `omarchy-ps4`, `omarchy-ps4-settings`, and
  `omarchy-ps4-provisioning` at `4.0.0-1`;
- the pinned `desktop-file-utils`, `xdg-user-dirs`, and `xdg-utils` packages
  required by the stable owner finalizer;
- a local Pacman database for all six migration packages;
- the pinned 4.0.0 portable archive as recovery/provenance material;
- the UI-only FPKG prototype;
- temporary, key-only developer recovery tooling;
- checksums, build metadata, credits, licenses, and operator documentation.

The bundle does not contain a PS4 Linux loader, PayLoader client, kernel,
initramfs, root filesystem, firmware, signing key, or private console data.
The guarded foundation migration resolves only against the bundled local
repository and never synchronizes a live Arch mirror. Dependencies outside
this reviewed six-package set must already exist on the accepted development
root; otherwise the preflight stops before installation. This narrow offline
migration bundle is still not the complete clean-image package snapshot.

## Two separate modes

### 1. Temporary recovery access

Before changing the package foundation, arm a second account in its own
bounded hardware experiment:

```bash
sudo ./arm-recovery --check EXP-YYYYMMDD-NNN-A1
sudo ./arm-recovery --apply EXP-YYYYMMDD-NNN-A1
```

`omarchy-recovery` reuses only the already-pinned operator public key. It has
no known password, cannot use password SSH, and cannot obtain a general root
shell. Its sudo policy permits only recovery status and removal of the exact
4.0.0 project package foundation. Port forwarding, agent forwarding, X11
forwarding, and tunnels are disabled for that account. `sshd.service` must be
enabled and active, and a real remote key login must pass before package work.

The account and its narrow `NOPASSWD` rule are intentional release tripwires:
`omarchy-ps4-prepare-for-owner --check` refuses gift finalization while either
remains. Never weaken or bypass that refusal.

### 2. Development foundation

`install-foundation` installs the three native 4.0.0 packages and only the
missing reviewed support packages without activating them, changing the
running desktop, enabling owner provisioning, or touching boot files:

```bash
sudo ./install-foundation --check EXP-YYYYMMDD-NNN-A1
sudo ./install-foundation --apply EXP-YYYYMMDD-NNN-A1
```

Both commands require the running `/` filesystem to be the external USB root
labelled `OMARCHY-PS4`. `--check` uses an isolated temporary Pacman database,
prints the complete proposed transaction, and rejects kernel, bootloader,
Plymouth, UDisks, display-manager, Mesa, libdrm, Vulkan, or Xorg-driver changes.
`--apply` repeats the resolution against the live database and aborts if it
differs before committing one package transaction. Both refuse to run unless
the recovery account, restricted rollback command, and persistent SSH service
are healthy.

Installing the provisioning package does not arm it. The pending marker and
service symlink must remain absent.

From the recovery login, the only privileged operations are:

```bash
sudo /usr/local/sbin/omarchy-ps4-dev-recovery status
sudo /usr/local/sbin/omarchy-ps4-dev-recovery rollback-foundation
```

Rollback uses one Pacman removal transaction for only the installed 4.0.0
project packages. It leaves dependencies, the portable desktop, accounts,
SSH, and boot assets in place and records before/after evidence.

### 3. Gift finalization

Gift finalization is deliberately destructive. It removes the `ps4`
development account and home, passwordless development sudo rules, SSH host
keys, LightDM autologin, and cloned machine identity. It then arms the tty1
first-owner wizard.

Never run finalization on the currently running root or the only development
copy. Clone the accepted external root onto a second USB device, mount that
clone from another Linux environment, and run the installed command there:

```bash
sudo omarchy-ps4-prepare-for-owner --check /mnt/gift-root
sudo omarchy-ps4-prepare-for-owner \
  --confirm PREPARE-FOR-ANOTHER-OWNER /mnt/gift-root
```

The command refuses `/`, the wrong filesystem label, non-USB storage, an
unexpected passwordless sudo rule, or an existing real owner's account.

### 4. Recoverable first-owner rehearsal

Development hardware can show and complete the real keyboard, username,
password, identity, hostname and timezone wizard without irreversibly erasing
the accepted `ps4` environment. This path is a test harness, not release
finalization.

The rehearsal first verifies the external USB root, exact 4.0.0 packages,
running desktop and independent recovery SSH. Arming it creates a root-only
snapshot and grants only two narrow capabilities: `ps4` may enter the armed
rehearsal once, while `omarchy-recovery` may inspect or roll it back.

```bash
sudo ./owner-rehearsal check EXP-YYYYMMDD-NNN-A1
sudo ./owner-rehearsal arm EXP-YYYYMMDD-NNN-A1
sudo /usr/local/sbin/omarchy-ps4-owner-rehearsal enter
```

Entry closes the development desktop, atomically parks `/home/ps4` under the
root-only evidence directory, removes the account from the live account
databases, disables development autologin, and runs the installed owner wizard
on tty1. It retains the recovery account, SSH service, host identity and boot
files. After setup, LightDM presents the new owner login using the native 4.0.0
profile.

From recovery SSH, rollback stops the rehearsal owner session, parks that test
home for evidence, restores the exact account databases, development home,
hostname, timezone, LightDM configuration and provisioning state, then starts
the original development desktop:

```bash
sudo /usr/local/sbin/omarchy-ps4-owner-rehearsal status
sudo /usr/local/sbin/omarchy-ps4-owner-rehearsal rollback
```

The rehearsal deliberately does not remove SSH keys, regenerate machine
identity or claim final gift cleanliness. Only offline finalization on a clone
may do that.

## Hardware rule

Installing packages, cloning/finalizing a root, launching the FPKG, or booting
the owner wizard are separate PS4 hardware experiments. Continuous UART and a
bounded experiment must be active before the operator performs each action.
Do not combine foundation installation and gift finalization in one session.

The isolated recovery fixture is `tests/gift-dev-recovery-test`. The recorded
booted-VM acceptance and its explicit simulation boundaries are in
`docs/GIFT-DEV-VM-TEST-2026-08-14.md`.
