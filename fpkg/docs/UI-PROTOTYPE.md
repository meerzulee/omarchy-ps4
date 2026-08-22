# Native UI-only FPKG prototype

Status: private installable interface prototype. It is not the Omarchy PS4
installer or Linux launcher.

The accepted design source is `fpkg/preview/fable5.html?review=final`. The
native package preserves its minimal PS4 console presentation and controller
flow at 1920x1080 so the interface can be judged on a real television and
DualShock 4 before any privileged functionality is added.

## Safety boundary

This package contains only:

- the native screen renderer and controller state machine;
- the pinned Omarchy Quattro 4.0.0 wordmark, four theme palettes and 17
  private-preview wallpapers;
- a user-scoped SaveData preference intended to contain only the selected
  theme;
- an OFL fallback font;
- normal OpenOrbis runtime/package files;
- this prototype notice.

It contains no Linux loader ELF, PayLoader client, socket/network path, kernel,
initramfs, root filesystem, release bundle, boot/USB writer, filesystem probe
or diagnostics exporter. Install, Boot, Verify, Restore and Export are UI
labels; confirming them changes only the in-memory screen state. Appearance
Apply writes only this title's SaveData for the active PS4 user. Relaunching
returns to Home on the saved theme's upstream default wallpaper. Hardware
v0.11 exposed a missing SaveData module/create path; v0.12 corrects the native
initialization and keeps the Appearance screen open with a visible error if a
save still fails. Persistence remains unaccepted until a later bounded test.

## Screen architecture

```text
Home
  +-- Missing: Install / update boot files -> progress -> Home ready
  +-- Ready: Boot Omarchy is the first, primary action -> local handoff
  +-- Linux 6.18.44 / Baikal is selected automatically
  +-- Options -> Appearance settings
  |     +-- Tokyo Night / Last Horizon / Lupine / Solitude
  |     +-- Shuffle preview
  |     +-- Apply user preference / Cancel preview
```

The native Home screen follows the accepted wide console composition: one
large workflow area on the left and truthful system-check cards on the right.
There is no persistent footer bar. The D-pad moves focus, Cross confirms,
Circle returns and Options opens Appearance. Circle from Appearance restores
the pre-entry theme. Navigation focus is separate from activation; Cross on
Install, Update or Boot performs that action without a duplicate review page.

The system check verifies the internal boot set against the exact release
bundled in the FPKG and reports missing, ready, update-available, interrupted
or blocked state. It shows the automatically selected tested kernel. It does
not pretend Orbis can verify the ext4 Omarchy USB; Linux proves that USB during
startup. GoldHEN is checked only after the user selects Boot Omarchy so
PayLoader is not consumed by a speculative probe.

## Themes and wallpapers

The palette values come from the pinned upstream `colors.toml` files for Tokyo
Night, Last Horizon, Lupine and Solitude. Seventeen selected upstream images are
normalized and darkened/lightened at build time to keep native rendering
bounded to one decoded 1920x1080 image. Each theme starts with its first sorted
upstream background; for the default Tokyo Night theme this is
`0-winding-road.jpg`. Shuffle replaces it only on explicit input.

The source paths and SHA-256 values are recorded in
`fpkg/ui-prototype/WALLPAPER-SOURCES.md`. The Audi-branded Quattro image is
excluded. The remaining art has incomplete per-file rights metadata, so the
package remains a private prototype and must not be published without a
separate rights review.

## PS4 typography and branding

Sony states that the PS4 interface uses the SST typeface designed with
Monotype. The prototype attempts to load the console's read-only
`/preinst/common/font/SST-Roman.otf` and `SST-Bold.otf` at runtime, then falls
back to the bundled OFL `Gontserrat-Regular.ttf` if they are unavailable. No
SST font is copied into the repository or package.

The package does not bundle or render Sony's stylized PS4 format mark. The
Omarchy wordmark stands alone in the native header, web preview and home tile;
there is no adjacent platform label. The home tile cannot switch with the
in-app theme because Orbis loads it before the app starts, so it uses a
self-contained near-black surface, the high-contrast Omarchy mark and a
restrained Tokyo blue accent that remain legible on both light and dark system
backgrounds.

Sources:

- https://www.sony.com/en/SonyInfo/design/stories/sst-font/
- https://www.monotype.com/fonts/sst

## Build

The reproducible wrapper downloads OpenOrbis v0.5.4, verifies its published
SHA-256, and builds the native FPKG without Docker:

```sh
./fpkg/tools/build-ui-prototype
```

Expected output:

```text
output/fpkg-ui-prototype/IV0000-OMCH42069_00-OMARCHYPS4UI0000.pkg
```

The separate private boot profile is intentionally opt-in:

```sh
./fpkg/tools/build-ui-prototype --private-boot
```

It produces v0.14 under `output/fpkg-private-boot/`, embeds only the pinned
1024 MB loader, checks its exact size and SHA-256 at runtime, and sends it once
to GoldHEN loopback PayLoader when Boot Omarchy is activated. It does not install,
format or write Linux/boot files. See `fpkg/docs/PRIVATE-BOOT.md`.

The wrapper runs `pkg_validate`, extracts the package for an entry audit and
rejects payload, bundle, kernel, initramfs and rootfs paths. It also rejects the
known local loader address, port and ELF name in the staged executable, checks
for exactly 17 wallpapers and verifies that every staged wallpaper is
1920x1080.

The current product-architecture profile is also explicitly opt-in:

```sh
./fpkg/tools/build-ui-prototype --private-kernel-manager
```

It produces private v0.28 under `output/fpkg-private-kernel-manager/`. In
addition to the pinned loader it embeds and verifies the exact kernel,
initramfs, boot arguments, VRAM file and schema-2 release manifest. Preparing
boot files uses a staging marker and current/previous directory rotation under
`/data/linux/boot`; staging returns Home with Boot Omarchy first. Selecting it
starts the loader handoff immediately. It never contains or writes the Omarchy
root filesystem.

The same title identity is retained across manager versions. Installing a
higher-version FPKG updates the app. On launch, v0.28 automatically compares
the active internal boot set with the set bundled in the new package and shows
`Update boot files` when they differ. The user activates that explicit action
once, and the previous complete set is retained. There is no silent download,
unsigned execution, unattended downgrade or rolling-package update.

Native stdout and stderr are unbuffered for UART capture. Structured
`[omarchy-ui]` and `[omarchy-boot]` events cover startup, framebuffer/font and
controller readiness, system checks, screen transitions, focus and confirm
input, appearance changes, each verified staged boot artifact, activation,
GoldHEN connection and loader transmission. No password or Linux owner data is
available to this app or written to those logs.

## Hardware review gate

Installing or launching the FPKG is a PS4 hardware action and must use the
workspace's bounded UART experiment handshake. Do not install it while another
hardware experiment is planned or active. The first hardware review changes
only one variable: install and launch this UI-only title, then inspect visual
fit, controller navigation and clean exit without selecting or staging any
Linux boot artifact. Theme persistence and relaunch shuffle are reviewed in a
separate bounded action.
