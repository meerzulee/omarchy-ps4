# Native UI-only FPKG prototype

Status: private installable interface prototype. It is not the Omarchy PS4
installer or Linux launcher.

The accepted design source is `fpkg/preview/fable5.html`. The native package
recreates its minimal Tokyo Night presentation and controller flow at 1920x1080
so the interface can be judged on a real television and DualShock 4 before any
privileged functionality is added.

## Safety boundary

This package contains only:

- the native screen renderer and controller state machine;
- the pinned Omarchy Quattro RC3 wordmark and Tokyo Night background;
- an OFL fallback font;
- normal OpenOrbis runtime/package files;
- this prototype notice.

It contains no Linux loader ELF, PayLoader client, socket/network path, kernel,
initramfs, root filesystem, release bundle, storage writer, filesystem probe or
diagnostics exporter. Install, Boot, Verify, Restore and Export are UI labels;
confirming them changes only the in-memory screen state. Relaunching the app
always returns to the initial prototype screen.

## Screen architecture

```text
Home
  +-- Install Omarchy -> Review -> simulated progress -> Ready
  |                                              +-> Boot review
  |                                                   +-> stopped handoff
  +-- Recovery & diagnostics
  |     +-- Verify -> no-action result
  |     +-- Restore -> no-action result
  |     +-- Export -> no-action result
  +-- Credits & licenses
```

The D-pad moves focus, Cross confirms and Circle returns. Navigation focus is
separate from activation, boot receives its own review, and the product flow
stops explicitly because no boot handoff exists in this build.

## PS4 typography and branding

Sony states that the PS4 interface uses the SST typeface designed with
Monotype. The prototype attempts to load the console's read-only
`/preinst/common/font/SST-Roman.otf` and `SST-Bold.otf` at runtime, then falls
back to the bundled OFL `Gontserrat-Regular.ttf` if they are unavailable. No
SST font is copied into the repository or package.

The stylized PS4 format logo is a Sony Interactive Entertainment trademark
available through SIE's logo licensing program. This unlicensed private build
therefore uses plain `PS4` platform text and does not bundle a Sony or
PlayStation logo asset. The official Omarchy wordmark remains the product mark.

Sources:

- https://www.sony.com/en/SonyInfo/design/stories/sst-font/
- https://www.monotype.com/fonts/sst
- https://sonyinteractive.com/en/contact-us/official-licensing-program/
- https://www.playstation.com/en-gb/legal/copyright-and-trademark-notice/

## Build

The reproducible wrapper downloads OpenOrbis v0.5.4, verifies its published
SHA-256, and builds the native FPKG without Docker:

```sh
./fpkg/tools/build-ui-prototype
```

Expected output:

```text
output/fpkg-ui-prototype/IV0000-BREW09004_00-OMARCHYPS4UI0000.pkg
```

The wrapper runs `pkg_validate`, extracts the package for an entry audit and
rejects payload, bundle, kernel, initramfs and rootfs paths. It also rejects the
known local loader address, port and ELF name in the staged executable.

## Hardware review gate

Installing or launching the FPKG is a PS4 hardware action and must use the
workspace's bounded UART experiment handshake. Do not install it while another
hardware experiment is planned or active. The first hardware review should
change only one variable: install and launch this UI-only title, then inspect
visual fit, controller navigation and clean exit without selecting or staging
any Linux boot artifact.
