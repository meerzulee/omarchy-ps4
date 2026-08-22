# Omarchy PS4 Manager FPKG

Status: UX and protocol draft with a staged private offline lab bundle. The
presentation-only native FPKG v0.11 was installed and rendered on the lab PS4;
it contains none of the manager's functional adapters. Theme persistence failed
that first hardware pass and is corrected in the staged v0.12. Local v0.13
moves the presentation to the final Omarchy 4.0.0 pin and remains pending a
separate bounded retest. Private v0.25 proved transactional internal boot-set
installation on hardware but exposed a 51,200-byte truncation in its loopback
multi-write loader handoff. Private v0.26 proved the corrected one-write
handoff on hardware. Private v0.28 is the current local kernel-manager
candidate: it retains that transport, restores persistent Baikal UART through
initramfs/systemd and removes duplicate install/boot review screens. On
2026-08-23, one bounded hardware launch verified the current internal set,
performed one complete loader write, reached the exact whole-device USB root,
showed the quiet splash and reached the desktop after manual login. That is a
private-beta boot-path pass, not full product acceptance: persistent autologin
still stopped at the greeter and repeated cold boots remain open. The FPKG must
not be published publicly while signing, loader licensing, and private
wallpaper rights remain unresolved.

The manager is the Orbis-side kernel manager and boot entry point for Omarchy
PS4:

- stage, update, verify and restore a signed internal kernel/initramfs set;
- automatically detect whether that bundled boot set is missing, current,
  outdated, interrupted or blocked; installation and updates remain explicit
  controller actions;
- boot Linux with an embedded PS4 Linux loader payload;
- emit structured UI, system-check, staging and handoff events over UART;
- export diagnostics and show exact source provenance.

The complete Omarchy installation is a separately flashed one-filesystem USB
image. The FPKG never contains, formats or extracts the Linux root filesystem.

GoldHEN is still a prerequisite. The FPKG does not jailbreak the console. It
sends its embedded loader ELF to GoldHEN's loopback PayLoader on port 9090, so
the user does not need Payload Guest or a separate payload file.

## User journey

```text
Launch FPKG
  -> check GoldHEN and console compatibility
  -> verify the bundled manifest, kernel, initramfs and boot profile
  -> stage /data/linux/boot with a journal and retain previous files
  -> return Home with Boot Omarchy as the first action
  -> user selects Boot Omarchy; the tested kernel starts without another review
  -> send embedded loader ELF to 127.0.0.1:9090
  -> Linux verifies the flashed OMARCHY-PS4 USB and boots
  -> first boot expands ext4 automatically
  -> Omarchy-themed first-boot TUI creates the owner's password
  -> automatic Omarchy session (target; the current beta still shows a greeter)
```

The password is never entered in Orbis, downloaded, logged, or baked into the
image. The future release image will contain
`/var/lib/omarchy-ps4/provisioning/pending`; Linux runs
`omarchy-ps4-provision-owner` on tty1 and removes the marker only after setup
completes.

## Draft layout

- `docs/REQUIREMENTS.md` — simple product requirements, GoldHEN dependency,
  user flows, safety rules, implementation order and acceptance gates.
- `docs/ARCHITECTURE.md` — trust, staging, payload and recovery boundaries.
- `manifest/` — signed release-manifest contract and an illustrative draft.
- `preview/fable5.html` — accepted controller/keyboard-driven 1080p UX mock
  using no web services; it includes the Quattro Appearance flow.
- `ui-prototype/` — native OpenOrbis renderer for an installable UI-only FPKG.
  Product actions are in-memory simulations; only the active user's appearance
  preference is saved. The default profile contains no loader, network, USB or
  boot adapter. The historical `private-boot` profile performs only the final
  loopback handoff. The `private-kernel-manager` profile adds the verified
  internal boot-set transaction used by the current product architecture.
- `docs/UI-PROTOTYPE.md` — exact prototype scope, screen flow, font/branding
  decision, build procedure and hardware-review gate.
- `tools/build-ui-prototype` — downloads and verifies the pinned OpenOrbis
  release, builds the native UI shell and audits the resulting package.
- `tools/validate-manifest` — dependency-free manifest policy validator.
- `tools/vendor-loader` — locally stages the pinned loader ELF for a private
  FPKG build and records its provenance.
- `tools/stage-offline-bundle` — legacy private installer-bundle staging for
  the superseded two-partition lab path.
- `CREDITS.md` — compact About-screen attribution and source links.
- `vendor/` — ignored private build inputs. Binary payloads, private keys and
  trademark artwork are never committed.

Open `preview/fable5.html?review=final` locally and use arrow keys plus Enter to
exercise the accepted draft. It deliberately simulates product actions; it
never contacts a server or touches a console. Browser appearance preferences
use only local storage. Build its native UI-only companion with
`./fpkg/tools/build-ui-prototype`. Build the non-publishable boot profile with
`./fpkg/tools/build-ui-prototype --private-kernel-manager`.

## Superseded full offline lab package

The older lab profile carried every boot/install input in the FPKG and staged
it to a FAT `PS4BOOT` filesystem. It remains only for reproducing historical
tests. Stage it with:

```sh
./fpkg/tools/stage-offline-bundle --allow-development-rootfs
```

The explicit flag is required because the available XFCE artifact is a lab
image: it contains a locked `ps4` account with LightDM autologin and does not
yet contain the deferred-owner marker. It has no working default password and
SSH password login is disabled, but it is still not release-quality account
setup. A release bundle must replace it with a freshly built image that starts
`omarchy-ps4-provision-owner` before the display manager.

“Credits” means attribution in `/app0/CREDITS.md`; no username/password is
baked into the FPKG.

## Public release blockers

1. The private lab profile embeds PS4 Linux Loader v25 with upstream credits,
   commit and digest. Its repository has no declared overall license, so public
   redistribution remains an explicit project-owner risk decision rather than
   something attribution alone resolves.
2. The release-signature/Ed25519 verification adapter and permanent signing-key
   policy still need implementation and review.
3. The kernel manager and one-filesystem image builder are implemented locally,
   but their final composed artifacts still require reproducibility review and
   destructive-path testing before hardware use.
4. The complete flow needs bounded UART acceptance on each supported
   model/southbridge. The current target remains the tested PS4 Slim Baikal B1.
5. The 17 private-preview wallpapers need per-image rights clearance before
   they can appear in a public package. The Sony PS4 format mark is not bundled.

No default password, production URL, signing key, or public title ID has been
created.
