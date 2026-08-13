# Omarchy PS4 Manager FPKG

Status: UX and protocol draft with a staged private offline lab bundle. A
presentation-only native FPKG can now be built for private UI review; it has not
been installed or run on hardware and contains none of the manager's functional
adapters.

The manager is the single Orbis-side entry point for Omarchy PS4:

- install or update a signed Linux image;
- repair or restore boot assets;
- boot Linux with an embedded PS4 Linux loader payload;
- export diagnostics and show exact source provenance.

GoldHEN is still a prerequisite. The FPKG does not jailbreak the console. It
sends its embedded loader ELF to GoldHEN's loopback PayLoader on port 9090, so
the user does not need Payload Guest or a separate payload file.

## User journey

```text
Launch FPKG
  -> check GoldHEN, network, storage and console compatibility
  -> load the bundled manifest and verify all embedded inputs
  -> stage files atomically and retain previous boot assets
  -> send embedded loader ELF to 127.0.0.1:9090
  -> Linux boots
  -> Omarchy-themed first-boot TUI creates the owner's password
  -> login screen / Omarchy session
```

The password is never entered in Orbis, downloaded, logged, or baked into the
image. The future release image will contain
`/var/lib/omarchy-ps4/provisioning/pending`; Linux runs
`omarchy-ps4-provision-owner` on tty1 and removes the marker only after setup
completes.

## Draft layout

- `docs/ARCHITECTURE.md` — trust, staging, payload and recovery boundaries.
- `manifest/` — signed release-manifest contract and an illustrative draft.
- `preview/fable5.html` — accepted controller/keyboard-driven 1080p UX mock
  using no web services.
- `ui-prototype/` — native OpenOrbis renderer for an installable UI-only FPKG.
  All product actions are in-memory simulations; no loader or system adapter is
  linked or packaged.
- `docs/UI-PROTOTYPE.md` — exact prototype scope, screen flow, font/branding
  decision, build procedure and hardware-review gate.
- `tools/build-ui-prototype` — downloads and verifies the pinned OpenOrbis
  release, builds the native UI shell and audits the resulting package.
- `tools/validate-manifest` — dependency-free manifest policy validator.
- `tools/vendor-loader` — locally stages the pinned loader ELF for a private
  FPKG build and records its provenance.
- `tools/stage-offline-bundle` — verifies and stages the loader, kernel,
  initramfs, boot arguments, 1024 MB VRAM setting, rootfs, and credits as one
  ignored private-package input tree.
- `CREDITS.md` — compact About-screen attribution and source links.
- `vendor/` — ignored build inputs placed inside `/app0` by the future package
  build. Binary payloads and private keys are never committed.

Open `preview/fable5.html` locally and use arrow keys plus Enter to exercise the
accepted draft. It deliberately simulates product actions; it never contacts a
server or touches a console. Build its native UI-only companion with
`./fpkg/tools/build-ui-prototype`.

## Full offline lab package

The selected prototype profile carries every boot/install input in the FPKG so
the console needs no second payload file or release download. Stage it with:

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
2. The OpenOrbis application renderer, downloader and Ed25519 verification
   adapter still need implementation and review.
3. External-root installation needs a dedicated initramfs installer with
   explicit device identity, preview and rollback. The FPKG must never guess a
   disk device or format storage itself.
4. The complete flow needs bounded UART acceptance on each supported
   model/southbridge. The current target remains the tested PS4 Slim Baikal B1.

No default password, production URL, signing key, or public title ID has been
created.
