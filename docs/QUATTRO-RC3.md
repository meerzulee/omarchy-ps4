# Quattro RC3 integration

Research date: 2026-08-13

Omarchy `4.0.0rc3` is packaged from Quattro commit
`144f4d1e31d6ddc2cba5dfd69278cabf02bafd05`. The source tree still reports
`4.0.0.alpha`; the RC version is assigned by the official package repository.
The Git branch named `rc` is the older 3.8.x release channel and is not the
Quattro RC source.

## Deferred owner setup

The Quattro ISO can install a complete machine without creating its owner. A
pending marker starts `omarchy-provision-owner` on tty1 during the first boot.
It collects keyboard, username, password, identity, hostname, and timezone,
creates the account, completes user configuration, and then starts the display
manager.

That UX is a good fit for a prebuilt PS4 image. Its PC implementation is not:

- it configures SDDM while the known-good PS4 base uses LightDM;
- encrypted mode re-keys LUKS and rebuilds Limine boot entries;
- factory reset depends on Btrfs subvolumes and snapshots;
- system setup assumes normal PC firmware, boot, and hardware discovery.

Omarchy PS4 will therefore reuse the shared question/validation contract and
the `pending` state model, but own every privileged action. The first PS4 owner
flow will:

1. run only when `/var/lib/omarchy-ps4/provisioning/pending` exists;
2. refuse to proceed unless `/` is the expected external root labelled
   `OMARCHY-PS4`;
3. create a non-default user with a normal password and passworded `sudo`;
4. apply keyboard, hostname, and timezone without touching boot assets;
5. seed the tested PS4 Omarchy configuration and preserve XFCE recovery;
6. remove the pending marker only after all required steps succeed;
7. hand off to the configured display manager without permanent autologin.

The release-image side is implemented by
`omarchy-ps4-prepare-for-owner`. It operates only on an offline, mounted USB
root labelled `OMARCHY-PS4`, refuses the running root or an existing owner's
account, removes the temporary development account and access, clears cloned
machine identity, disables autologin, and then arms the pending marker. The
literal confirmation makes this an image-finalization step rather than a menu
command someone can trigger accidentally.

The initial release will not offer factory reset, internal-storage erasure,
LUKS re-keying, or automatic boot repair. Those require their own storage and
recovery designs.

## Acceptance gate

The flow is not supported on PS4 hardware yet. Before promotion it needs local
rootfs tests followed by bounded UART experiments proving:

- an image contains no default password or enabled SSH password login;
- interruption leaves the pending state recoverable;
- the new account receives the expected groups and desktop files;
- LightDM, XFCE recovery, Hyprland, network setup, and passworded `sudo` work;
- three cold boots complete without a display regression.
