# Omarchy PS4 gift-USB checkpoint — 2026-08-22

This checkpoint records the first successful end-to-end development boot of
the stable Omarchy 4.0.0 gift image on the Baikal B1 lab console. It separates
the proven boot/install behavior from the first-boot UI and UX that still needs
work.

The original bounded hardware evidence is `EXP-20260822-009-A39` in
[`experiments/SESSIONS.md`](../experiments/SESSIONS.md). This is a private
development success, not a public support or production-readiness claim.

The 2026-08-23 continuation adds FPKG v0.28 launch evidence in
`EXP-20260823-018-A11`: the application verified the current internal boot set,
sent the loader once, reached the exact USB root and displayed the accepted
quiet splash. The desktop remained reachable through manual login, but
persistent LightDM autologin did not pass. `EXP-20260823-019-A2` also proved
that the target has no usable RTC and had network time disabled. Gift-image
construction now enables `systemd-timesyncd` so a network connection corrects
the clock without adding a network dependency to first-owner setup.

## Architecture exercised

The successful path used:

1. GoldHEN in Orbis to provide the one-shot BinLoader service.
2. Loader v25 sent as one exact 320,936-byte application write.
3. Kernel, initramfs and boot arguments read from PS4 internal application
   storage under `/data/linux`.
4. A flashed external USB containing one whole-device ext4 filesystem labelled
   `OMARCHY-PS4`.
5. The initramfs refusing internal SATA as root, resolving the labelled USB,
   proving USB ancestry and mounting it read-write.
6. A first-boot service expanding ext4 from its compact 16 GiB image size to
   the complete physical USB size.
7. The offline owner form collecting keyboard, username and password, creating
   the owner, finalizing the Omarchy desktop and starting the graphical login.

The test sent the loader remotely to shorten iteration time. It proves the
loader, internal boot set, kernel, initramfs and gift USB together. It does not
by itself prove the final one-button FPKG launch experience.

## What passed

- Continuous UART capture remained valid through Orbis handoff, Linux boot,
  USB growth and owner setup.
- GoldHEN received exactly 320,936 bytes and launched the ELF successfully.
- Linux `6.18.44-ps4-baikal` started with 1024 MiB VRAM.
- The intended Kingston USB was detected and mounted as the external root.
- Internal SATA was disabled by the PS4 product boot arguments and was not used
  as the Linux root.
- The ext4 filesystem grew automatically from 17,179,869,184 bytes to the full
  123,983,626,240-byte device. The user did not resize or partition anything.
- Owner provisioning emitted every expected lifecycle stage: `start`,
  `root-verified`, `prompt-ready`, `finalizing` and `complete`.
- The operator created the passworded owner and reached the graphical login
  screen.
- No kernel panic, initramfs root failure, PayLoader error or filesystem-growth
  failure occurred.

## What is not accepted yet

- The first-boot and login visual design is not final.
- This was one successful boot, not the required repeated cold-boot acceptance.
- The FPKG's own v0.28 Launch action now passes through loader handoff, USB-root
  validation and the branded splash on this console.
- Persistent owner autologin was explicitly tested and failed: the effective
  LightDM owner/session configuration and PAM `autologin` group are present,
  but the greeter still appears. Privileged LightDM diagnostics are the next
  evidence boundary; manual login remains functional.
- Network time must be enabled in every composed gift image because no usable
  RTC is exposed. The source fix is implemented; the current live USB still
  needs the one-time `timedatectl set-ntp true` acceptance action.
- Wi-Fi generated noisy driver diagnostics on UART. Functionality and log
  severity need separate treatment, but those messages must not be hidden from
  UART evidence merely to make logs look clean.
- The current photo shows a pink deer greeter background instead of the pinned
  Tokyo Night `2-swirl-buck.jpg`; package/config precedence must be verified.

## UI and UX findings

### Graphical login card

The photographed LightDM GTK greeter card is offset to the lower-right of the
true screen center. The cause is deterministic: the configuration used
`position=50% 50%`, which places the card's top-left corner at the midpoint.

The local source is corrected to:

```ini
position=50%,center 50%,center
```

This must be packaged and visually verified at 1920x1080 before acceptance.

### First-owner setup

The current shell form works but still looks like a diagnostic console. The
next design pass should keep its reliable tty-and-`gum` implementation while
giving it a deliberate Omarchy presentation:

- full-screen deep green or Tokyo Night surface, not a bright green field;
- Omarchy wordmark in `#9ece6a`;
- one centered setup card inside the TV-safe area;
- consistent field width, typography and spacing;
- one question at a time with a small progress indication;
- concise user copy and no kernel, systemd, driver or package output;
- only an actionable branded error on HDMI;
- full technical evidence retained on UART and in the root-only provisioning
  log at `/var/log/omarchy-ps4-provision-owner.log`.

The reliable product flow should be:

```text
Omarchy splash
      ↓
Centered owner setup
      ↓
Preparing your desktop
      ↓
Omarchy desktop (first completion)
      ↓ later boots
Centered graphical login
```

### Clean HDMI, detailed UART

The internal boot set used by this successful run still carried diagnostic
arguments: it omitted `console=null` and used `systemd.show_status=auto`.
That explains why boot messages reached HDMI.

The repository already defines the intended product behavior in
`fpkg/bootargs/6.18-baikal-internal-root.txt`:

- `console=null` and `systemd.show_status=false` keep routine output off HDMI;
- `quiet splash` and `vt.global_cursor_default=0` keep the transition clean;
- the Baikal early UART console, `keep_bootcon`, kmsg target and developer
  loglevel preserve detailed serial evidence.

The next FPKG boot-file update should install that product boot-argument file.
It must be tested as a one-variable hardware change because UART visibility is
a release safety requirement.

## Next local work

1. Prototype the centered green first-owner form off-console at 1920x1080.
2. Keep the existing validation, interruption and safe-retry behavior unchanged.
3. Package the corrected LightDM center anchor and add a package-content test.
4. Verify why the greeter background and first-completion transition did not
   match the intended settings.
5. Build and test the clean product boot arguments locally.
6. Review screenshots before another PS4 action.
7. Validate the visual candidate and boot-argument change in separate bounded
   UART sessions; do not combine them with another storage or kernel change.
