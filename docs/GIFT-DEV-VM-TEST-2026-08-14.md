# Gift developer bundle — OrbStack VM acceptance

Date: 2026-08-14
OrbStack: 2.2.3
Machine retained for inspection: `omarchy-gift-rc3-test`

## Scope

This acceptance exercises the developer-gift account, SSH, Pacman install,
reboot and rollback workflow without touching the PS4. It does not claim PS4
hardware acceptance.

OrbStack removed two attempted emulated `amd64` Arch machines during image
provisioning. The surviving VM is native `arm64` Arch. All three Omarchy PS4
packages are `any`; PS4 architecture and hardware acceptance remains assigned
to the bounded real-console experiments.

The VM uses three explicit test fixtures:

- root label/USB transport wrappers, because the OrbStack root is virtio;
- an active systemd display-manager sentinel, because the VM has no console
  desktop seat;
- a compatibility package for the Arch Linux ARM font package rename from
  `ttf-jetbrains-mono-nerd-basic` to `ttf-jetbrains-mono-nerd`.

The SSH daemon, systemd enable/start/reload behavior, users, sudo policy,
Pacman transactions and reboot are real.

## Results

1. The bundle manifest and package policy passed.
2. `arm-recovery --check` correctly refused the unmodified virtio root.
3. With the USB-root fixture active, recovery preflight and apply passed.
4. A real network SSH login as `omarchy-recovery` passed using key fingerprint
   `SHA256:N64LAFp/1IpDOVOrMNVY3Bd6JHn2qxAyvT0/8FZ3T0M`.
5. Recovery SSH was public-key-only; password, TCP, agent and X11 forwarding
   were disabled. Arbitrary sudo was denied.
6. The first foundation preflight correctly rejected a blank VM because the
   transaction contained forbidden `mesa` and `libdrm` packages.
7. After those existing-PS4-baseline packages were preinstalled, preflight
   passed without changing the rejection policy.
8. Pacman installed `omarchy-ps4`, `omarchy-ps4-settings` and
   `omarchy-ps4-provisioning` at exactly `4.0.0rc3-1`.
9. The owner-provisioning marker and service remained absent. Recovery SSH and
   the display sentinel remained active.
10. After an OrbStack VM restart, the recovery account, SSH service, restricted
    command and all three RC3 packages remained available.
11. The remote restricted rollback removed exactly the three RC3 packages.
    Hyprland, Quickshell, Thunar, accounts, SSH and other dependencies remained.
12. The owner-finalization fixture refused both the temporary human recovery
    account and its temporary `NOPASSWD` rule.
13. After the first PS4 preflight exposed Pacman's private-home traversal
    boundary, the corrected bundle passed uncached preflight from beneath
    mode-0700 `/root`. Pacman resolved all three local package files from the
    temporary sandbox-readable repository without disabling its download
    sandbox.
14. A copy-on-write clone named `omarchy-owner-rehearsal-test` exercised the
    recoverable first-owner path without changing the accepted VM. Arming
    preserved the `ps4` account, home, display sentinel and process IDs, while
    granting only the exact one-shot enter command and recovery status/rollback.
15. Two deliberately incomplete virtual-root label fixtures stopped at the
    installed provisioner's own label check after the development home had
    been parked. In both cases, restricted recovery SSH restored the exact
    account databases, home, LightDM fixture and active display sentinel. This
    proved rollback from a failed wizard handoff before the fixture was fixed.
16. With `blkid`, `findmnt`, `readlink` and `lsblk` consistently describing the
    simulated external root, the actual packaged Gum form completed keyboard,
    username, password confirmation, optional identity, hostname, timezone and
    final owner confirmation. It created disposable owner `giftowner`, removed
    the pending marker and returned to the active display manager.
17. The recovery account then rolled the completed rehearsal back. All six
    account databases and the LightDM configuration matched their pre-run
    snapshots byte-for-byte; `ps4` and its original home returned; the test
    owner disappeared from NSS and its home was retained only below the
    root-mode-0700 evidence directory; hostname and timezone returned; SSH and
    the display sentinel stayed active.

Result: **pass for the isolated userspace workflow**. Hardware follow-up is
recorded separately below because VM results do not substitute for PS4
acceptance.

## Hardware follow-up

`EXP-20260814-001-A1` passed on the PS4 with key-only recovery SSH and a
responsive desktop. A44 closed before any transaction after exposing Pacman
sandbox compatibility issues. After the uncached private-path VM reproduction,
`EXP-20260814-001-A2` installed the reviewed RC3 package closure on the PS4.
All three project packages report `4.0.0rc3-1`; provisioning remains unarmed;
recovery SSH, LightDM and the portable desktop remained healthy; completed UART
continuity showed no hardware fault. No monitor change was expected because the
experiment installed only the native package foundation and deliberately did
not activate or restart the desktop.
