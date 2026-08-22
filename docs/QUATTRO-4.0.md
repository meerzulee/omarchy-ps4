# Quattro 4.0 integration

Research date: 2026-08-14

Omarchy `4.0.0` is tagged at commit
`f0020448ca87329199de7cb12f2015ebc4a3e5e7`. The source tree's `version` file
still reports `4.0.0.alpha`; the official package repository assigns `4.0.0`
to that exact commit. The older Git branch named `rc` remains on the Omarchy
3.8.x line and is not the Quattro source.

The PS4 pin moved from RC3 commit
`144f4d1e31d6ddc2cba5dfd69278cabf02bafd05` to the final tag. The 147-package
base list, 59-package conditional list, themes, palettes, wallpapers and
Plymouth wordmark are unchanged. The final delta adds three helper commands,
one migration, notification/tray fixes, crash-capture support and an expanded
Omarchy icon font. PS4-owned configuration and safety guards remain in place;
the release pin does not automatically enable new services or privileged
upstream update/install commands.

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

Omarchy PS4 therefore reuses the shared question/validation contract and the
`pending` state model, but owns every privileged action. The first PS4 owner
flow will:

1. run only when `/var/lib/omarchy-ps4/provisioning/pending` exists;
2. refuse to proceed unless `/` is the expected external root labelled
   `OMARCHY-PS4`;
3. create a non-default user with a normal password and passworded `sudo`;
4. apply keyboard, hostname, and timezone without touching boot assets;
5. seed the tested PS4 Omarchy configuration and preserve XFCE recovery;
6. remove the pending marker only after all required steps succeed;
7. hand off to a persistent Omarchy desktop autologin; the password remains
   required for `sudo` and screen locking.

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

RC3 rendered on the Baikal B1 console, but the final `4.0.0` pin is not yet a
hardware support claim. Before promotion it needs local rootfs and package
tests followed by bounded UART experiments proving:

- the final runtime starts with the PS4 overrides and no new unsafe service;
- an image contains no default password or enabled SSH password login;
- interruption leaves the pending state recoverable;
- the new account receives the expected groups and desktop files;
- LightDM, XFCE recovery, Hyprland, network setup, and passworded `sudo` work;
- three cold boots complete without a display regression.

The historical RC3 integration record remains in `QUATTRO-RC3.md` and must not
be rewritten into final-release hardware evidence.
