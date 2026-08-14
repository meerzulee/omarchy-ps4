# Omarchy PS4 checkpoint — 2026-08-13

This is the durable resume point for the current PS4 Slim Baikal B1 port. It
separates implemented source, local build evidence, real-hardware evidence and
the next gated work. Do not promote a local pass into a hardware support claim.

## Supported target and recovery path

- Console: PS4 Slim, Baikal B1 southbridge, firmware 12.02.
- Kernel: Linux `6.18.44-ps4-baikal` from the patch-based
  [`meerzulee/linux-ps4`](https://github.com/meerzulee/linux-ps4) repository.
- Linux root: external ext4 USB filesystem labelled `OMARCHY-PS4`.
- Boot files: FAT32 filesystem labelled `PS4BOOT`.
- Recovery desktop: LightDM plus XFCE. Do not replace this with SDDM.
- Known Linux DHCP address in this lab: `192.168.50.125`.
- Known Orbis/GoldHEN address in this lab: `192.168.50.215`.
- A development-only password exists on the current private lab root; its value
  is intentionally omitted here and it must never enter a release image.

## What is working on the real console

- Linux 6.18.44 boots from the external USB root.
- HDMI renders at fixed 1920×1080 at 60 Hz with the pinned EDID and PS4 GPU
  workarounds.
- XFCE remains usable as recovery.
- Native Wayland, Hyprland, UWSM, Foot and the Quattro RC3 shell have rendered.
- Tokyo Night theme and wallpaper work.
- The accepted 1080p presentation uses 14px shell text, about 1.2× GTK text,
  11pt Foot, fixed bar geometry and a borderless Omarchy menu card.
- Wi-Fi, NetworkManager and SSH key login have worked on the current root.

These are lab results, not broad PS4-model support. Display artifacting on the
legacy DCE8 path remains a known limitation.

## What was implemented in the repository

### Quattro RC3 runtime

- Pinned Omarchy Quattro commit:
  `144f4d1e31d6ddc2cba5dfd69278cabf02bafd05`.
- Built PS4-native `omarchy-ps4`, `omarchy-ps4-settings` and
  `omarchy-ps4-provisioning` package recipes.
- Added a versioned non-root portable runtime with exact rollback.
- Preserved upstream commands for audit and blocked commands that assume PC
  boot, storage, brightness, power or Plymouth behavior.
- Routed file-manager behavior to Thunar to avoid UDisks activation.
- Generated a 153-package workstation profile, with unsafe direct packages
  explicitly blocked and unsupported capabilities left unclaimed.

### Deferred owner setup

- Added `omarchy-ps4-prepare-for-owner` for an offline mounted release root.
- It refuses `/`, non-USB targets, a wrong filesystem label and any existing
  real owner account.
- It removes the temporary `ps4` account, development sudo/SSH access, SSH host
  keys, autologin and cloned machine identity.
- It arms `omarchy-ps4-provision-owner.service` on tty1.
- First boot collects keyboard, username, password, identity, hostname and
  timezone, then creates a passworded wheel user without touching the PS4 boot
  chain or internal disk.
- Package policy and synthetic-root destructive-flow fixtures pass locally.
- This flow is not hardware-accepted yet and must not be applied to the current
  lab root until a disposable release-image test is ready.

### FPKG and USB distribution design

- Drafted a single Omarchy PS4 Manager application with Install, Boot, Repair,
  Diagnostics and Credits states.
- Defined a signed release-manifest schema and an offline lab bundle policy.
- Added external-USB preparation and installer-initramfs tools.
- The installer resolves labels, proves the target is USB, verifies the rootfs
  digest, refuses a non-empty target and never formats or probes internal SATA
  as an install target.
- The intended first release pairs a small manager FPKG with a prepared or
  flashable USB image. Linux owns ext4 extraction; Orbis does not.
- The native OpenOrbis renderer, file-copy adapter, signature verifier and
  PayLoader adapter are not implemented yet.
- Public loader embedding remains blocked on an explicit redistribution policy.

### Persistent native Omarchy splash

- Replaced the one-frame placeholder with a static framebuffer renderer using
  the exact Quattro RC3 native `OMARCHY` wordmark.
- Source PNG SHA-256:
  `ba8f1547a02ab5db64fe3923d0b834a220e2c3798c1674374a0eb92a18dfddfb`.
- The renderer uses Tokyo Night background, Omarchy green and a restrained
  fake progress line.
- It waits for AMDGPU `/dev/fb0`, repaints once per second so fbcon/modeset
  transitions cannot permanently overwrite it, and remains alive until the
  validated root is ready.
- Success completes the green line; initramfs failure completes it in Omarchy
  red. Detailed evidence continues over Baikal UART.
- Plymouth is not installed into the custom PS4 loader chain.
- Static renderer SHA-256:
  `2124d28c21de2b2d96d0e9296fd51a9ccaf901bd8395645b3ee9df950bb11cc9`.
- Embedded logo mask SHA-256:
  `fe3b19a33bae79976f8cb27269facee14aff23a5f73739fde8d7d18717b88eac`.
- Rebuilt initramfs SHA-256:
  `acc08b4bbcb0535780161537033dc4a58d5b99a9fba659e23466bea95329d0ab`.
- Static build, boot-profile and initramfs content tests pass locally. The new
  splash has not been staged or booted on the PS4 yet.

## Known gaps

- HDMI audio is not working.
- Vulkan is not accepted.
- UVD/VA-API hardware video decode is not accepted.
- Screen capture/recording and sharing are not accepted.
- Bluetooth, printing, Docker service operation, gaming and controller UX are
  not accepted.
- Hyprsunset/nightlight gamma LUT use is blocked because it blacked out the
  legacy DCE8 display path.
- VRR/FreeSync remains disabled after the monitor failure experiment.
- Internal SATA remains outside normal Linux use; product SATA-off arguments
  still need their own cold-boot acceptance.
- The modern AMD Display Core/atomic path is a separate kernel workstream. The
  working legacy display path remains default and recovery.
- The complete release rootfs and user-first image have not been built.
- No public repository, package repository, release or FPKG has been published.

## Ordered plan

Only one hardware experiment may be active. Every PS4-side action requires its
own bounded UART slice and must close in `experiments/SESSIONS.md` before the
next action.

1. **A1 — temporary recovery prerequisite.** In its own bounded action, create
   the key-only `omarchy-recovery` account, allow only status and exact RC3
   foundation rollback through sudo, verify a fresh remote SSH login and prove
   arbitrary sudo is denied. This account and rule must block gift
   finalization until deliberately removed.
2. **A2 — native RC3 foundation preflight and install.** A44 closed
   inconclusive before any transaction after exposing three installer
   compatibility defects. The corrected bundle passed an uncached preflight
   from beneath mode-0700 `/root` in the booted OrbStack VM. Resolve Pacman's
   complete transaction before changing the root. Accept only the three local
   RC3 packages plus their explicitly recorded missing dependencies. Abort if
   the closure includes a kernel, bootloader, Plymouth, UDisks, SDDM takeover,
   graphics-stack replacement or an unplanned service. Install once, enable no
   services, retain the portable session and verify rollback.
3. **A45 — persistent native splash.** Stage only initramfs digest
   `acc08b4…`, retain the current kernel and product boot arguments, boot once,
   and verify that the Omarchy frame survives mode changes and hands off to the
   accepted desktop while UART remains complete.
4. **SATA-off acceptance.** In a separate boot, change only the product
   `libata.force=1.00:disable` argument. Prove the internal timeout disappears,
   the USB root remains correct and recovery boot arguments still work.
5. **Full Arch repository package batches.** Install the 80 currently
   available profile packages by functional batch. Preflight each dependency
   closure, keep services disabled, verify free space and preserve LightDM/XFCE.
6. **Remaining Omarchy/AUR packages.** Package the meaningful missing tools in
   the separate `omarchy-ps4-pkgs` source/repository design. Pin source and
   license for each; skip packages that add no value or cannot be maintained.
7. **Capability ladder.** Test Vulkan, audio, VA-API/UVD, capture, Bluetooth,
   printing, Docker and gaming one at a time. A package being installed is not
   evidence that its capability works.
8. **Build the release rootfs.** Produce an external-root Quattro image with no
   default account, the deferred-owner marker, PS4 packages, accepted splash,
   XFCE recovery and no release SSH password login.
9. **Owner-flow acceptance.** On a disposable release root, test interruption,
   resume, username/password creation, passworded sudo, networking, LightDM,
   XFCE recovery and Hyprland. Require three cold boots before promotion.
10. **Native FPKG implementation.** Implement OpenOrbis UI, atomic USB staging,
   Ed25519 manifest verification, PayLoader transport, Repair and Diagnostics.
11. **Release engineering.** Resolve loader redistribution, create signed
    `edge` and `stable` Pacman repositories, define A/B boot asset rollback,
    test corrupted downloads/power loss/full storage, then build a private
    release candidate. Public push and release remain explicit later actions.

## Immediate resume command

Temporary recovery experiment A1 and native foundation experiment A2 passed
with completed UART continuity. The three project packages are installed at
`4.0.0rc3-1`, provisioning remains unarmed, recovery SSH remains available and
the portable desktop remains active. No monitor change is expected from this
foundation-only state. Stop for owner direction before the next PS4 action.
Installing/launching the UI-only FPKG from Orbis and staging the native splash
as A45 are separate experiments; neither has begun.
