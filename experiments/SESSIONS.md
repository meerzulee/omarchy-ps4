# Development session ledger

Updated: 2026-08-21

This is the resume point for the project. Read this file, `docs/PLAN.md`, and
`docs/COMPATIBILITY.md` before proposing a new PS4-side action.

## Current position

- active phase: stable Omarchy 4.0.0 migration and private boot-capable FPKG
  development after the existing external USB desktop passed a fresh boot
- local preparation gate: `PREP-20260810-001` complete through read-only
  GoldHEN FTP after the Kingston USB was connected directly to the PS4.
  `/mnt/usb0` contains one complete boot bundle; `EXP-20260810-000-A1`
  corrected its only blocker and reverified every core-file hash
- active hardware experiment: none. `EXP-20260821-001-A2` is closed as a pass;
  the accepted external USB system is running and internal PS4 storage was not
  modified
- next hardware action: none until local stable-migration transaction tests
  pass. Stable package installation and FPKG installation remain separate
  later actions
- continuous UART: last confirmed `READY` on `/dev/cu.wchusbserial3110`, PID
  `5950`, generation `266b3d42494146d1afa5f4028ab6cfcf`; runtime identifiers
  must be rechecked before every action
- known-good rollback: internal Linux `5.4.247-neocine-1.1` boot set plus FAT
  `recovery/` files on the prepared USB
- authoritative kernel repository:
  [`meerzulee/linux-ps4`](https://github.com/meerzulee/linux-ps4), with
  `v6.18.44-ps4-baikal-r1` released from `master`
- distribution repository:
  [`meerzulee/omarchy-ps4`](https://github.com/meerzulee/omarchy-ps4), default
  branch `master`

## Work-session history

| Session | State | Outcome | Evidence/resume pointer |
|---|---|---|---|
| `DEV-20260810-001` | complete | Refreshed PS4 Linux ecosystem and recorded current projects/gaps | [`knowledge/2026-08-10/`](../knowledge/2026-08-10/) |
| `DEV-20260810-002` | complete | Ported patch stack to Linux 6.18.44 LTS; 47 patches apply and kernel/modules build reproducibly | [`6.18-PORT.md`](https://github.com/meerzulee/linux-ps4/blob/master/docs/6.18-PORT.md) and local kernel output |
| `DEV-20260810-003` | complete | Built clean pinned Arch/XFCE rootfs and label-aware initramfs | [`docs/BUILDING.md`](../docs/BUILDING.md) and local ignored output |
| `DEV-20260810-004` | complete | Prepared confirmed Kingston USB: 1GiB FAT32 boot plus ext4 `OMARCHY-PS4`; offline filesystem checks passed | [`docs/FIRST-BOOT-6.18-XFCE.md`](../docs/FIRST-BOOT-6.18-XFCE.md) |
| `DEV-20260810-005` | complete | Added continuous UART logger and bounded raw/LLM session extraction | [`ps4-uart/README.md`](../../ps4-uart/README.md); live logger PID is runtime state, not durable evidence |
| `DEV-20260810-006` | complete | Audited firmware-12.02 delivery chain; pinned loader v25, PSFree sender, Payload Guest, HenLoader fallback, and hashes | [`FW-12.02-PAYLOAD-CHAIN.md`](../knowledge/2026-08-10/FW-12.02-PAYLOAD-CHAIN.md) |
| `DEV-20260810-007` | complete | Backed up existing `/data/linux/boot` through read-only FTP and identified Linux 5.4.247-neocine rollback | [`backups/ps4-data-linux-boot/2026-08-10-fw12.02/`](../../backups/ps4-data-linux-boot/2026-08-10-fw12.02/) |
| `DEV-20260810-008` | complete | Independent UART workflow audit accepted; hardened exact-byte capture, readiness, continuity, collision safety, and storage guards | [`ps4-uart/README.md`](../../ps4-uart/README.md); automated suite and live capture report `READY` |
| `DEV-20260810-009` | complete | Final read-only audit found capture-drain, concurrent-start, cleanup, durability, storage-error, and recovery races; all accepted findings were fixed, 22 tests pass, and a live capture fence was acknowledged | `ps4-uart` generation `1307aff7e5324e438f69fdeee53d995b`; audit was advice only and touched no hardware |
| `DEV-20260811-010` | complete | Restored rmux-derived Baikal MSI patches 0007+0008+0009 as one treatment; strict gate applied 50/50 and clean OrbStack build/checksums passed | [`6.18-PORT.md`](https://github.com/meerzulee/linux-ps4/blob/master/docs/6.18-PORT.md); bzImage SHA-256 `0d7cd17af71495df3e54f49fcfd31d41020ec096505f50e1938a4e92cb96f97b` |
| `DEV-20260811-011` | complete | Ported the PS4 DRM bridge to Linux 6.18's managed lifetime after A25 isolated the kref defect; strict gate applied 52/52 and clean OrbStack build/checksums passed | [`6.18-PORT.md`](https://github.com/meerzulee/linux-ps4/blob/master/docs/6.18-PORT.md); bzImage SHA-256 `f1a6eabe49f12853a0cc93af462b2153dc09b58de0c5bfc28bb2d6cc50fdc1dd` |
| `DEV-20260811-012` | complete | Replaced the incompatible archived HDMI diagnostic with pointer-safe post-0034 patch 0035; strict gate applied 53/53 and clean OrbStack build/checksums passed | [`6.18-PORT.md`](https://github.com/meerzulee/linux-ps4/blob/master/docs/6.18-PORT.md); A29 bzImage SHA-256 `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e` |
| `DEV-20260811-013` | complete | Audited Vue After Free 2.0 PSN-prompt recovery and compared the exact 6.18 A29 hardware paths with rmux Baikal 7.0.8; identified loader-provided dynamic EDID as the clearest isolated display gap and corrected managed-bridge prior-art attribution | [`VUE-AFTER-2-RECOVERY.md`](../knowledge/2026-08-11/VUE-AFTER-2-RECOVERY.md); [`RMUX-7.0-BAIKAL-COMPARISON.md`](https://github.com/meerzulee/linux-ps4/blob/master/docs/RMUX-7.0-BAIKAL-COMPARISON.md) |

The two older files under `experiments/uart/` captured the continuous OrbisOS
stream before this bounded-session protocol. They are useful background logs,
but they are not evidence of a Linux 6.18 boot.

## Release and repository queue

- `omarchy-ps4` is public at
  [`meerzulee/omarchy-ps4`](https://github.com/meerzulee/omarchy-ps4); private
  build outputs and raw evidence remain intentionally unpublished.
- `linux-ps4-kernel` `origin/master` and current `HEAD` contain only Meerzulee
  as a commit author and no Claude/Anthropic co-author trailers; the current
  README also has no Claude tooling credit. The remote branch
  `origin/wip/uvd-vce-poc` still retains older history containing those
  trailers and may keep GitHub's contributor attribution alive. Replacing or
  deleting that remote history is destructive and remains pending explicit
  approval plus a remote-ref backup.

## Hardware experiment queue

### EXP-20260810-000 — external boot-media insertion

- state: inconclusive
- question: does OrbisOS/GoldHEN enumerate the verified FAT boot partition as
  one complete loader source without changing console-internal files?
- changed variable: insert the verified Kingston USB into the running PS4;
  no payload is sent and no FTP write is allowed
- expected evidence: bounded UART records the insertion without a serial
  continuity failure; read-only FTP shows one `/mnt/usbN` containing matching
  `bzImage`, `initramfs.cpio.gz`, `bootargs.txt`, and `vram.txt`
- timeout: 30 seconds after insertion, then one read-only FTP listing
- rollback: after stopping/reviewing the bounded session, safely remove the USB
  if enumeration is incomplete; leave internal `/data/linux/boot` unchanged
- bounded UART context: missing; the action occurred before a session marker
- operator report: "i plugged the usb"
- result: inconclusive as an insertion/UART experiment. Subsequent read-only
  FTP enumeration found the bundle together at `/mnt/usb0`, and streamed
  hashes matched its `SHA256SUMS`; however, `vram.txt` contained legacy value
  `1`, so the boot source was not yet valid for the v25 1024 MB loader
- rollback state: USB remains connected; internal `/data/linux/boot` was not
  written
- next action: `EXP-20260810-000-A1`

### EXP-20260810-000-A1 — correct v25 VRAM source value

- state: complete
- question: can the enumerated USB be made internally consistent for loader
  v25 without changing any kernel, initramfs, boot arguments, or internal file?
- changed variable: replace only `/mnt/usb0/vram.txt` value `1` with `1024`,
  then refresh only its corresponding `SHA256SUMS` entry over anonymous
  GoldHEN FTP
- expected evidence: bounded UART continuity remains valid; FTP reread returns
  exactly `1024`; streamed hashes for `bzImage`, `initramfs.cpio.gz`,
  `bootargs.txt`, and `vram.txt` all equal the refreshed manifest
- timeout: 30 seconds for each upload, followed by one complete read-only hash
  verification
- rollback: upload the preserved original value `1` and restore its original
  manifest hash `4355a46b19d348dc2f57c046f8ef63d4538ebb936000f3c9ee954a27460dd865`
- bounded UART context:
  [`20260810_235048_590531-exp-20260810-000-a1-correct-v25-vram-source-60698dcf.md`](../../ps4-uart/sessions/20260810_235048_590531-exp-20260810-000-a1-correct-v25-vram-source-60698dcf.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- result: pass. FTP reread returned exactly `1024`; `bzImage`,
  `initramfs.cpio.gz`, `bootargs.txt`, and `vram.txt` streamed hashes all
  matched the refreshed manifest. New `vram.txt` SHA-256 is
  `4f71bb761ace37c88826cd8cc1c948e1cf5b5d0cd153dc651a6efdb3dfb9f2b1`
- rollback state: not required; internal `/data/linux/boot` remained unchanged
- next action: `EXP-20260810-001`

### EXP-20260810-001 — Linux 6.18.44/XFCE cold boot 1

- state: failed at root-device discovery; rollback is ready as
  `EXP-20260810-001-A8`
- question: does the prepared external USB reach a stable XFCE desktop with
  the new patch-based Linux 6.18.44 kernel?
- changed variable: send the pinned v25 1024 MB loader while the already
  verified external boot bundle remains connected; this versioned bundle is
  the integration test unit and internal boot files remain unchanged
- payload: v25 `elf/linux-1024mb.elf`, SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`
- expected evidence: loader identifies firmware/southbridge and USB files;
  early UART continues into kernel; root label `OMARCHY-PS4` resolves; systemd,
  HDMI 1080p60, LightDM and XFCE appear; USB keyboard/mouse work
- timeout: allow 180 seconds to reach root mount or a stable error; if UART is
  still making forward progress, report that state before interrupting rather
  than treating the timer alone as a hang
- rollback: power off only after logging the stable failure state; remove the
  external USB and retain the internal 5.4 boot set unchanged
- bounded UART context: first pre-launch capture
  [`20260810_235225_728091-exp-20260810-001-linux-6-18-44-xfce-cold-boot-1-a3f48034.md`](../../ps4-uart/sessions/20260810_235225_728091-exp-20260810-001-linux-6-18-44-xfce-cold-boot-1-a3f48034.md)
  finalized `aborted`, generation `1307aff7e5324e438f69fdeee53d995b`,
  epoch `1`; no payload was launched. A new bounded capture is required
- operator report: Vue menu did not show an ELF; after the successful A6
  handoff, HDMI remained blank
- result: fail. The official loader and Linux kernel ran, but all PS4 PCI BARs
  inside the firmware-reserved `0x80000000-0xfbffffff` range lost their
  assignments. Baikal PCI could not map BARs, xHCI and amdgpu stayed deferred,
  and initramfs could not discover `LABEL=OMARCHY-PS4` after 60 seconds
- next action: `EXP-20260810-001-A8`

### EXP-20260810-001-A1 — add pinned v25 ELF to Vue payload menu

- state: complete
- question: will Vue After Free enumerate the exact pinned v25 ELF when it is
  added to GoldHEN's payload directory without replacing the existing BIN?
- changed variable: upload only `linux-1024mb-v25.elf` to `/data/payloads`;
  preserve the existing `linux-1024mb.bin`, whose unknown SHA-256 is
  `5185e7f42c15a1766a0e9e9129ac09aea38991466eebd74299dc3c47bf7738aa`
- expected evidence: anonymous FTP reread of the new ELF equals pinned SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`,
  and a Vue menu refresh exposes the new ELF label
- timeout: 30 seconds for upload and hash verification; menu refresh should
  expose the entry immediately
- rollback: delete only `/data/payloads/linux-1024mb-v25.elf`; preserve all
  pre-existing files and internal `/data/linux/boot`
- bounded UART context:
  [`20260810_235925_639673-exp-20260810-001-a1-add-pinned-v25-elf-a36e9064.md`](../../ps4-uart/sessions/20260810_235925_639673-exp-20260810-001-a1-add-pinned-v25-elf-a36e9064.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "error occured"
- result: degraded. FTP upload and reread passed with the pinned v25 SHA-256,
  but reopening Vue caused PlayStation Vue `CUSA00960` to receive `SIGBUS` in
  `JavaScriptThread` with a general-protection fault. This is a Vue exploit/app
  crash, not a Linux-loader or boot attempt. Before the crash, UART reported
  `Serving ELF loader on 192.168.50.215:9021`; the port remained reachable
  afterward
- rollback state: verified ELF retained for direct delivery; the pre-existing
  BIN and internal `/data/linux/boot` remain unchanged
- next action: `EXP-20260810-001-A2`

### EXP-20260810-001-A2 — direct v25 ELF delivery through live elfldr

- state: complete
- question: can the exact latest v25 1024 MB loader reach the verified external
  Linux 6.18.44/XFCE boot set when delivered without reopening Vue?
- changed variable: delivery path only—stream the same pinned
  `linux-1024mb.elf` directly to the already-running ELF loader at
  `192.168.50.215:9021`; no payload file, boot file, or boot argument changes
- preconditions: official GitHub release API still reports v25 as latest,
  published 2026-07-25; local ELF SHA-256 is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  port `9021`, FTP `2121`, and GoldHEN PayLoader `9090` were reachable after
  the Vue crash
- expected evidence: elfldr accepts and starts v25; loader identifies firmware
  and Baikal southbridge; it selects all four files from `/mnt/usb0`; early
  UART continues into Linux; root label `OMARCHY-PS4`, systemd, LightDM and
  XFCE reach a stable state; operator sees HDMI and working input
- timeout: allow 180 seconds to reach root mount or a stable error; continued
  UART progress extends observation instead of being treated as a hang
- rollback: after capturing a stable failure, power off; retain the external
  recovery files and unchanged internal Linux 5.4 boot set
- bounded UART context:
  [`20260811_000426_938897-exp-20260810-001-a2-direct-v25-elf-to-9021-ff06237f.md`](../../ps4-uart/sessions/20260811_000426_938897-exp-20260810-001-a2-direct-v25-elf-to-9021-ff06237f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- result: fail before Linux boot. The sender streamed all `320936` verified
  bytes once, and elfldr returned `Error running ELF file`. UART showed
  `pt_mprotect` and `pt_msync` errors, then `elfldr_load failed`; the spawned
  `Payload` process (`SceSpZeroConfMain`) received `SIGSEGV` on a protection
  violation. No v25 loader firmware/USB messages and no Linux lines appeared
- conclusion: this proves failure of the live Vue-provided elfldr handoff in
  the post-crash runtime; it does not establish a v25 payload or kernel defect
- rollback state: console remains in OrbisOS, FTP remains reachable, and no
  boot file changed. Do not reuse this runtime for another delivery attempt
- next action: `EXP-20260810-001-A3`

### EXP-20260810-001-A3 — clean shutdown after Vue/elfldr failures

- state: complete
- question: can the console leave the failed exploit/elfldr runtime through a
  normal shutdown without a kernel panic or forced power loss?
- changed variable: use the PS4 power menu once to select `Turn Off PS4`; do
  not restart, resend a payload, unplug the USB, or alter any file
- expected evidence: UART records the normal shutdown sequence and then stops;
  the operator reports HDMI loss and a fully-off power LED
- timeout: 60 seconds; if the UI is unresponsive, report it before using the
  physical power button
- rollback: none; the desired safe state is fully powered off. The next boot
  will establish a fresh exploit runtime before testing official v25 BIN via
  GoldHEN PayLoader rather than the failed Vue elfldr path
- bounded UART context:
  [`20260811_000603_064826-exp-20260810-001-a3-normal-shutdown-after-loader-failure-00fe2250.md`](../../ps4-uart/sessions/20260811_000603_064826-exp-20260810-001-a3-normal-shutdown-after-loader-failure-00fe2250.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "action complete"; HDMI off and power-off action confirmed
- result: pass. UART recorded the Quick Menu shutdown, USB automounter cleanup,
  completed pre-shutdown tasks, filesystem sync with `All buffers synced`,
  and final `ICC: Shutdown`; no kernel panic occurred
- rollback state: achieved; console is fully off with USB still connected
- next action: `EXP-20260810-001-A4`

### EXP-20260810-001-A4 — fresh power-on to OrbisOS

- state: complete
- question: does the console reach a normal, stable Orbis login/home screen
  after the clean shutdown while the prepared USB remains connected?
- changed variable: press the PS4 power button once; do not launch Vue, send a
  payload, remove the USB, or change a setting
- expected evidence: bounded UART records a normal cold boot without a safe
  mode or filesystem-repair path; operator reports stable HDMI and input at
  login/home
- timeout: 120 seconds to a stable login/home screen
- rollback: if boot enters safe mode or a repair screen, report the exact HDMI
  state and do not select an option; if it hangs, retain UART before shutdown
- bounded UART context:
  [`20260811_000756_348982-exp-20260810-001-a4-fresh-power-on-to-orbisos-a0162ce0.md`](../../ps4-uart/sessions/20260811_000756_348982-exp-20260810-001-a4-fresh-power-on-to-orbisos-a0162ce0.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "action complete"
- result: pass. UART recorded firmware `release_12.020`, automatic login,
  DUALSHOCK 4 assignment, USB device detection, `boot sequence finished`, and
  `Shell UI is Ready`; cold boot completed in about 40 seconds with no panic or
  safe-mode path
- rollback state: not required; console is at clean Orbis home with prepared
  USB connected
- next action: `EXP-20260810-001-A5`

### EXP-20260810-001-A5 — fresh Vue After Free 2.0 jailbreak

- state: complete
- question: does one fresh launch of the installed full Vue After Free 2.0
  establish a stable firmware-12.02 GoldHEN runtime without an app crash?
- changed variable: launch Vue After Free 2.0 once from clean OrbisOS and wait;
  do not reopen Vue or select/send a Linux payload
- expected evidence: UART records the userland and Lapse chain without a fatal
  signal or kernel panic; GoldHEN starts; read-only HTTP `/status` on TCP 9090
  reports ready and FTP TCP 2121 becomes available
- timeout: 180 seconds; if Vue crashes or the console powers off, report the
  exact HDMI/LED state and do not retry in the same runtime
- rollback: on Vue app crash, perform a separately captured normal shutdown as
  required by the upstream FAQ; on kernel panic, report power state before any
  recovery action
- bounded UART context:
  [`20260811_001522_969273-exp-20260810-001-a5-fresh-vue-2-0-jailbreak-720e87fe.md`](../../ps4-uart/sessions/20260811_001522_969273-exp-20260810-001-a5-fresh-vue-2-0-jailbreak-720e87fe.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "goldhen loaded action complete"
- result: pass. UART recorded GoldHEN installing kernel and shell patches,
  `All done!`, and `<payloader> Server started at 9090 port`; Vue then exited
  normally with no fatal signal or kernel panic. Read-only HTTP returned 200
  and `{ "status": "ready" }`; FTP remained available and `/mnt/usb0`
  retained the complete bundle with `vram.txt=1024`
- rollback state: not required; clean GoldHEN runtime remains active and Vue
  must not be reopened
- next action: `EXP-20260810-001-A6`

### EXP-20260810-001-A6 — Linux boot through GoldHEN PayLoader

- state: complete
- question: does the exact official v25 1024 MB ELF boot the prepared external
  Linux 6.18.44/XFCE bundle when delivered through a clean GoldHEN PayLoader?
- changed variable: HTTP POST the same pinned `linux-1024mb.elf` exactly once
  to GoldHEN TCP 9090; do not reopen Vue or change any payload/boot file
- preconditions: PayLoader `/status` is `ready`; `/mnt/usb0` contains
  `bzImage`, `initramfs.cpio.gz`, `bootargs.txt`, and `vram.txt=1024`; ELF
  SHA-256 is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`
- expected evidence: v25 identifies firmware 12.02 and Baikal, selects all four
  files from `/mnt/usb0`, enters kexec, and UART continues into Linux; root
  label `OMARCHY-PS4`, systemd, HDMI, LightDM and XFCE reach a stable state;
  operator reports display and input behavior
- timeout: 180 seconds to root mount or a stable error; continued UART progress
  extends observation rather than being classified as a hang
- rollback: after recording a stable failure, use a separately captured normal
  shutdown if OrbisOS remains; if Linux or the console hangs, report physical
  state before any power action. Internal Linux 5.4 files remain unchanged
- bounded UART context:
  [`20260811_002423_581723-exp-20260810-001-a6-v25-elf-through-goldhen-9090-c895980e.md`](../../ps4-uart/sessions/20260811_002423_581723-exp-20260810-001-a6-v25-elf-through-goldhen-9090-c895980e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: HDMI remained blank
- result: fail as an integrated XFCE boot, with a passed loader/kernel
  sub-gate. GoldHEN accepted the exact `320936`-byte v25 ELF with HTTP 200;
  v25 identified firmware `1202`, `VRAM 1024 MB`, and Baikal, selected the
  external bundle, armed kexec, and Linux `6.18.44-ps4-baikal` reached `/init`.
  During PCI enumeration, ACPI supplied no usable memory/IO host window after
  E820 clipping. All key firmware BAR assignments conflicted with Reserved
  `[mem 0x80000000-0xfbffffff]`; `baikal_pcie` could not map BAR 0/2/4 and
  failed with `-EIO`, leaving xHCI, amdgpu, SDHCI, and related functions
  deferred
- conclusion: the failure is below the root filesystem and XFCE. It does not
  implicate the USB partition contents, label, ext4 image, or desktop stack
- rollback state: Linux is alive in initramfs rescue; no root block device was
  mounted. A separately captured physical power-off is required
- next action: `EXP-20260810-001-A8`

### EXP-20260810-001-A7 — root-device timeout continuation

- state: complete
- question: after Linux reaches the initramfs with deferred PS4 PCI devices,
  does USB/root enumeration eventually recover or reach a stable failure?
- changed variable: none; observe the already-running A6 boot without input
- expected evidence: either xHCI and `LABEL=OMARCHY-PS4` appear, or initramfs
  reports a bounded timeout and rescue state
- timeout: the initramfs's configured 60-second discovery window
- rollback: after a stable failure is captured, power off in a new bounded
  action session; the root filesystem was never mounted
- bounded UART context:
  [`20260811_002526_247611-exp-20260810-001-a7-linux-boot-continuation-after-automatic-kexe-0d220e4e.md`](../../ps4-uart/sessions/20260811_002526_247611-exp-20260810-001-a7-linux-boot-continuation-after-automatic-kexe-0d220e4e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: HDMI remained blank; UART showed the initramfs wait and
  deferred probes
- result: fail. At `76.898424` seconds initramfs reported that
  `LABEL=OMARCHY-PS4` was not found after 60 seconds, then dropped to its root
  rescue shell. No Linux block device appeared
- conclusion: the terminal failure matches the earlier BAR/xHCI evidence.
  Existing same-console Linux 6.15 traces show that adding only `pci=nocrs`
  restores default root-bus IO/memory resources, Baikal probe, xHCI, this
  Kingston USB (`0951:1666`), root mount, systemd, and framebuffer. That is the
  next boot variable; generic `pci=realloc` is not the first test because the
  firmware BAR addresses are valid but rejected by the empty ACPI host window
- rollback state: pending `EXP-20260810-001-A8`
- next action: `EXP-20260810-001-A8`

### EXP-20260810-001-A8 — power off failed initramfs boot

- state: complete
- question: can the console be brought fully off from the rootless initramfs
  rescue state without introducing a storage-write risk?
- changed variable: hold the physical PS4 power button until the console beeps
  and its LED turns fully off; do not remove USB or UART while power remains
- expected evidence: UART stops, HDMI remains off, and the operator confirms
  the power LED is fully off
- timeout: 15 seconds of holding the power button, then 30 seconds to full off
- rollback: none; the desired state is powered off. The external root device
  never enumerated or mounted, so no ext4 filesystem was active
- bounded UART context:
  [`20260811_003139_738190-exp-20260810-001-a8-power-off-failed-initramfs-boot-e856919c.md`](../../ps4-uart/sessions/20260811_003139_738190-exp-20260810-001-a8-power-off-failed-initramfs-boot-e856919c.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: `done i am on ps4 no jb`
- result: pass, with an explicitly recorded additional cold-boot action. The
  forced-off boundary produced no UART text; the following power-on began at
  the firmware 12.02 secure loader, enumerated Kingston `0951:1666`, mounted
  FAT partition 1 at `/mnt/usb0`, completed normal login, and reported
  `Shell UI is Ready` at about 39 seconds. No panic or repair path appeared
- rollback state: achieved. Console is at clean OrbisOS without jailbreak;
  external USB and UART remain connected
- next action: `EXP-20260810-001-A9`

### EXP-20260810-001-A9 — clean Vue/GoldHEN for bootargs correction

- state: complete
- question: does one Vue After Free 2.0 launch establish the clean GoldHEN
  FTP/PayLoader runtime needed to change and verify one external boot argument?
- changed variable: launch Vue After Free 2.0 once; do not send Linux, reopen
  Vue, or alter a file during this action
- expected evidence: UART records successful kernel/shell patches and
  `<payloader> Server started at 9090 port`; HTTP `/status` reports `ready` and
  FTP 2121 exposes the already-mounted `/mnt/usb0`
- timeout: 180 seconds to GoldHEN success or a stable crash
- rollback: if Vue crashes, capture a separate normal shutdown; if the kernel
  panics, report HDMI/LED state before recovery
- bounded UART context:
  [`20260811_003907_685424-exp-20260810-001-a9-clean-vue-goldhen-for-bootargs-correction-195064d6.md`](../../ps4-uart/sessions/20260811_003907_685424-exp-20260810-001-a9-clean-vue-goldhen-for-bootargs-correction-195064d6.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: `done`
- result: pass. UART recorded all GoldHEN kernel/shell patches, `All done!`,
  and PayLoader on 9090 without a fatal signal or kernel panic. HTTP `/status`
  returned `ready`; read-only FTP returned the unchanged USB bootargs with
  SHA-256 `e616eab811bc9e528add56210dd427d7271967388096183d5bce2a71c961c882`
  and its matching manifest
- rollback state: not required; clean GoldHEN runtime remains active and Vue
  must not be reopened
- next action: `EXP-20260810-001-A10`

### EXP-20260810-001-A10 — append pci=nocrs to external bootargs

- state: complete
- question: can the one required PCI host-window workaround be installed on
  the FAT boot bundle with byte-for-byte verification and no other change?
- changed variable: append exactly ` pci=nocrs` to `/mnt/usb0/bootargs.txt`;
  update only the `bootargs.txt` line in `/mnt/usb0/SHA256SUMS`
- prepared values: old bootargs are 319 bytes with SHA-256
  `e616eab811bc9e528add56210dd427d7271967388096183d5bce2a71c961c882`;
  new bootargs are 329 bytes with SHA-256
  `c0d8b11ab759b1785f49a89e4125f6c734288a23a6f8976ce530ae4c90d376b3`
- expected evidence: FTP reread returns the exact prepared 329-byte file;
  its computed hash equals the new manifest entry, while every other manifest
  line remains byte-identical
- timeout: 30 seconds per upload and 30 seconds for complete reread/hash check
- rollback: upload the locally preserved `bootargs.before.txt` and
  `SHA256SUMS.before`; verify the old digest before any boot
- bounded UART context:
  [`20260811_004205_717824-exp-20260810-001-a10-append-pci-nocrs-to-external-bootargs-910855b0.md`](../../ps4-uart/sessions/20260811_004205_717824-exp-20260810-001-a10-append-pci-nocrs-to-external-bootargs-910855b0.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: no physical action required; primary LLM performs the two
  scoped FTP replacements while the operator leaves the console idle
- result: pass. FTP overwrote only `bootargs.txt` and `SHA256SUMS`. Remote
  reread returned exactly 329 bytes and SHA-256
  `c0d8b11ab759b1785f49a89e4125f6c734288a23a6f8976ce530ae4c90d376b3`;
  byte comparison against the prepared file passed. The complete remote
  manifest was byte-identical to the prepared manifest, proving that only the
  bootargs digest line changed. UART continuity remained valid
- rollback state: not required. Exact old bootargs and manifest remain under
  ignored local `output/EXP-20260810-001-A10/`
- next action: `EXP-20260810-001-A11`

### EXP-20260810-001-A11 — corrected Linux boot with pci=nocrs

- state: complete
- question: does adding only `pci=nocrs` restore PS4 PCI BAR ownership, Baikal
  xHCI, the external root filesystem, and the XFCE graphical baseline?
- changed variable: kernel command line now ends in `pci=nocrs`; kernel,
  initramfs, rootfs, VRAM, loader, delivery path, and console runtime are the
  same verified versions used by A6
- payload: v25 `elf/linux-1024mb.elf`, SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`
- expected evidence: `PCI: Ignoring host bridge windows from ACPI`, default
  root-bus IO/memory resources, no BAR-loss loop, successful `bpcie_probe`,
  xHCI/Kingston enumeration, `LABEL=OMARCHY-PS4` mount, systemd, amdgpu,
  framebuffer/HDMI, LightDM, XFCE, and working input
- timeout: 180 seconds to root mount, XFCE, or a stable error; continued UART
  progress extends observation instead of being treated as a hang
- rollback: after a stable failure, capture a separate power-off. To undo the
  boot change, restore the A10 `before` files over FTP from a clean GoldHEN
  runtime. Internal Linux 5.4 files remain untouched
- bounded UART context:
  [`20260811_004320_460072-exp-20260810-001-a11-corrected-linux-boot-with-pci-nocrs-e7140829.md`](../../ps4-uart/sessions/20260811_004320_460072-exp-20260810-001-a11-corrected-linux-boot-with-pci-nocrs-e7140829.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: HDMI panel/backlight came on but displayed no image
- result: fail, with two useful partial milestones. `pci=nocrs` did restore
  default PCI root-bus resources, allowed `bpcie_probe`, xHCI host creation,
  amdgpu probe, and `amdgpudrmfb` creation. It did not restore completion
  interrupts: xHCI aborted slot assignment twice, SDHCI and SATA commands
  timed out, and vector `0xef` was repeatedly reported as spurious. The
  Kingston device never enumerated; at 130.79 seconds initramfs reported that
  `LABEL=OMARCHY-PS4` was absent after 60 seconds and entered its rescue shell.
  Display remained degraded: the operator saw panel/backlight with no image.
  UART also reports the real Linux 6.18 API violation `DRM bridge corrupted or
  not allocated by devm_drm_bridge_alloc()` followed by refcount warnings.
  Independent source review corrected the initial conclusion that this warning
  prevented bridge enable: active patch 0007 directly force-calls bridge
  pre-enable/enable, and A11 proceeds through the same mode-fixup, DP-clock,
  TX-preservation, fbcon, and framebuffer markers as the hardware-proven v60
  boot. Verbose bridge/lane probes were disabled, so A11 neither proves nor
  disproves MN864729 lane lock. The refcount violation needs separate cleanup,
  but current evidence does not establish it as the cause of black HDMI
- rollback state: console remains in the initramfs rescue state; `pci=nocrs`
  remains deliberately installed because it fixed PCI resource assignment.
  A clean power-off still requires its own bounded capture
- next action: `EXP-20260810-001-A12`; after recovery, test interrupt remapping
  before changing kernel code

### EXP-20260810-001-A12 — power off failed A11 boot

- state: complete
- question: can the console leave the A11 initramfs rescue state cleanly with
  continuous UART evidence before local kernel work continues?
- changed variable: operator holds the physical power button until shutdown;
  no payload, file, boot argument, or storage change
- expected evidence: bounded UART remains continuous through the power event;
  console fan, LED, and HDMI turn off without a new kernel panic
- timeout: 30 seconds after the physical power-button action
- rollback: if the console does not power off, stop and review UART before any
  second attempt
- bounded UART context:
  [`20260811_004838_297836-exp-20260810-001-a12-power-off-failed-a11-boot-fce12888.md`](../../ps4-uart/sessions/20260811_004838_297836-exp-20260810-001-a12-power-off-failed-a11-boot-fce12888.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "done"; operator then announced intent to jailbreak
- result: pass for recovery, with an action-boundary overrun. The failed Linux
  state ended without a Linux panic and UART remained continuous. The same
  slice then captured a complete normal Orbis cold boot on firmware 12.02,
  `SceShellCore` run-level 80, `START Shell UI`, and `Ready to exec`. That
  post-power-on evidence is valid state observation but was not part of the
  predeclared power-off action
- rollback state: console is running clean, non-jailbroken OrbisOS; no rollback
  required and the external `pci=nocrs` bootargs remain installed
- next action: `EXP-20260810-001-A13`

### EXP-20260810-001-A13 — fresh Vue/GoldHEN after A11 recovery

- state: complete
- question: does one Vue After Free 2.0 jailbreak action establish a clean
  GoldHEN runtime after the failed Linux boot and recovery cycle?
- changed variable: operator launches the installed Vue jailbreak flow once;
  no Linux loader or other payload is sent
- expected evidence: exploit completes without a kernel panic, GoldHEN applies
  its patches, and PayLoader/FTP services become ready
- timeout: 120 seconds or an explicit success/failure screen
- rollback: on failure, stop and review UART before retrying; on panic, use a
  separately captured cold boot
- bounded UART context:
  [`20260811_005132_185005-exp-20260810-001-a13-fresh-vue-goldhen-after-a11-recovery-d539b1df.md`](../../ps4-uart/sessions/20260811_005132_185005-exp-20260810-001-a13-fresh-vue-goldhen-after-a11-recovery-d539b1df.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "goldhen loaded"
- result: pass for the declared jailbreak action. The bounded UART slice stayed
  continuous and contains ordinary Shell UI activity with no panic or fatal
  trap. GoldHEN itself did not emit an identifying UART marker in this short
  slice, so the loaded state is established by the operator's screen report;
  service reachability has not yet been separately exercised
- rollback state: not required; console remains in the reported GoldHEN runtime
- next action: `EXP-20260810-001-A14`. Two internal read-only audits and one
  independent Herdr Claude Opus audit agree the smallest next experiment is to
  disable interrupt remapping before restoring old MSI patches. The Opus audit
  argued for also adding `iommu=pt`; this plan intentionally does not, because
  A11 already logged `iommu: Default domain type: Passthrough`, making that
  token semantically redundant and `intremap=off` the single changed variable

### EXP-20260810-001-A14 — disable interrupt remapping in external bootargs

- state: complete
- question: can one bootarg change isolate the A11 command-completion failure
  to AMD interrupt remapping without changing the kernel or userspace?
- changed variable: append only `intremap=off` to `/mnt/usb0/bootargs.txt` and
  refresh only that file's line in `/mnt/usb0/SHA256SUMS`; keep `pci=nocrs`,
  kernel, initramfs, rootfs, VRAM, loader, and every other manifest line fixed
- expected evidence: FTP reread exactly matches the prepared file and digest;
  the complete manifest differs only in the bootargs digest line
- timeout: 30 seconds per upload and 30 seconds for reread/hash verification
- rollback: restore the exact A10/A11 bootargs and manifest preserved locally,
  then verify their old digest before another boot
- prepared values: old bootargs are 329 bytes with SHA-256
  `c0d8b11ab759b1785f49a89e4125f6c734288a23a6f8976ce530ae4c90d376b3`;
  new bootargs are 342 bytes with SHA-256
  `853c72a260dcc6d35108954639fbfc9b8e1db57e1bb9e1f302160e0124b0bf43`
- bounded UART context:
  [`20260811_010936_240271-exp-20260810-001-a14-disable-interrupt-remapping-in-external-boo-9c20843a.md`](../../ps4-uart/sessions/20260811_010936_240271-exp-20260810-001-a14-disable-interrupt-remapping-in-external-boo-9c20843a.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: no physical action required; operator leaves console idle
- result: pass. Remote precondition hashes exactly matched the preserved A11
  files. FTP replaced only `bootargs.txt` and `SHA256SUMS`; exact rereads match
  the prepared files byte-for-byte. The remote bootargs digest is
  `853c72a260dcc6d35108954639fbfc9b8e1db57e1bb9e1f302160e0124b0bf43`,
  remote manifest digest is
  `e612aa3acd9798d1b2c89780272357063504648721d7247a520afd799057e27e`,
  and only the bootargs digest line differs. UART remained continuous with
  ordinary Orbis UI output and no panic
- rollback state: exact prior files remain under ignored local
  `output/EXP-20260810-001-A14/`; rollback not required before the test boot
- next action: `EXP-20260810-001-A15`

### EXP-20260810-001-A15 — unchanged kernel boot with intremap=off

- state: complete
- question: does disabling AMD interrupt remapping restore Baikal command
  completions with the current Linux 6.18 kernel and patch stack?
- changed variable: effective kernel command line adds only `intremap=off`;
  the kernel, initramfs, rootfs, VRAM, v25 loader, `pci=nocrs`, delivery path,
  and console runtime remain fixed from A11
- payload: v25 `elf/linux-1024mb.elf`, SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`
- expected evidence: command line contains `pci=nocrs intremap=off` and does not
  log `AMD-Vi: Interrupt remapping enabled`; primary pass endpoint is zero xHCI
  `Command Aborted` plus Kingston `0951:1666` enumeration. A complete pass also
  mounts `LABEL=OMARCHY-PS4` and reaches systemd/XFCE. Record HDMI separately;
  ATA identify errors are secondary because the v60 pass still logged some
- timeout: 180 seconds to root mount/XFCE or a stable error; continued progress
  extends observation
- rollback: after a stable failure, capture a separate power-off; restore the
  A14 `before` files over FTP only after a clean GoldHEN runtime
- bounded UART context:
  [`20260811_011102_958920-exp-20260810-001-a15-unchanged-kernel-boot-with-intremap-off-c3d9853f.md`](../../ps4-uart/sessions/20260811_011102_958920-exp-20260810-001-a15-unchanged-kernel-boot-with-intremap-off-c3d9853f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: supplied the terminal initramfs/deferred-probe UART excerpt;
  HDMI outcome not yet reported
- result: fail, with the `intremap=off` hypothesis cleanly falsified as a
  standalone fix. The requested command line was exact and the A11
  `AMD-Vi: Interrupt remapping enabled`, vector-`0xef`, xHCI `Command Aborted`,
  MMC command-timeout, and early ATA identify-timeout cascade all disappeared.
  However xHCI `00:14.7`, amdgpu `00:01.0`, AHCI `00:14.2`, and SDHCI `00:14.3`
  instead remained deferred with return `517` (`-EPROBE_DEFER`), because the
  current 6.18 series does not install the MSI parent required when interrupt
  remapping is disabled. Initramfs arrived quickly at 7.72 seconds, but no
  Kingston/block device could bind; at 75.78 seconds it reported the root label
  absent and entered rescue. This is a different, cleaner failure than A11
- rollback state: console remains in the initramfs rescue shell;
  `intremap=off` stays installed because the next MSI-code experiment requires
  that known boot profile. A separate captured power-off is still required
- next action: `EXP-20260810-001-A16`, then re-enable 0200 patches 0007, 0008,
  and 0009 as one indivisible MSI treatment and clean-build. They are
  hardware-proven together with `intremap=off` on the earlier 6.15 line, but
  remain unproven after rebasing to 6.18; patch 0010 stays disabled because its
  per-subfunction mask experiment was documented as behaviorally inert

### EXP-20260810-001-A16 — power off failed A15 boot

- state: complete
- question: can the console leave the A15 initramfs rescue state cleanly before
  local kernel patch/build work begins?
- changed variable: operator holds the physical power button until shutdown;
  no payload, file, boot argument, or storage change
- expected evidence: bounded UART remains continuous through the power event;
  fan, LED, and HDMI turn off without a new kernel panic
- timeout: 30 seconds after the physical power-button action
- rollback: if the console does not power off, stop and review UART before any
  second attempt
- bounded UART context:
  [`20260811_011419_620299-exp-20260810-001-a16-power-off-failed-a15-boot-86c42ef5.md`](../../ps4-uart/sessions/20260811_011419_620299-exp-20260810-001-a16-power-off-failed-a15-boot-86c42ef5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`; slice length zero bytes
- operator report: asked to stop UART and stated intent to run GoldHEN next,
  implying the requested power-off action had completed; LED/fan/HDMI details
  were not separately reported
- result: pass for state recovery by operator report, with no UART payload.
  The silent zero-byte slice contains no panic or continuity failure but cannot
  independently prove shutdown quality
- rollback state: console is treated as powered off; no storage rollback needed
- next action: `EXP-20260810-001-A17`; do not combine power-on and jailbreak

### EXP-20260810-001-A17 — clean power-on after A15

- state: complete
- question: does the PS4 cold-boot normally after the A15 deferred-probe test?
- changed variable: operator presses the physical power button once and waits
  at normal Orbis; Vue/GoldHEN and other payloads are not launched
- expected evidence: firmware 12.02 reaches Shell UI/navigation without panic;
  operator confirms normal display/controller behavior
- timeout: 120 seconds to Shell UI or a stable error
- rollback: on boot failure, stop and review before another power action
- bounded UART context:
  [`20260811_011558_929308-exp-20260810-001-a17-clean-power-on-after-a15-24439955.md`](../../ps4-uart/sessions/20260811_011558_929308-exp-20260810-001-a17-clean-power-on-after-a15-24439955.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: first "done", then "goldhen loaded"
- result: pass for cold-boot recovery with an action-boundary overrun. UART
  confirms firmware 12.02 entered normal mode, started Shell UI, and reached
  `Ready to exec`. Before A17 could be closed, the operator also launched
  GoldHEN; the same continuous slice validly records all GoldHEN kernel/Shell
  patches, `All done!`, and PayLoader listening on port 9090. This proves the
  current runtime but does not retroactively make jailbreak part of A17's
  declared variable
- rollback state: not required. Console is in a confirmed GoldHEN runtime and
  the USB remains attached to the PS4
- next action: local-only restore/apply/build verification for 0200 patches
  0007+0008+0009. Do not send a Linux payload until the new artifact is staged
  and verified in a separate bounded session

### EXP-20260810-001-A18 — stage MSI-treatment kernel on external FAT

- state: complete
- question: can the verified 50-patch kernel replace only the external test
  kernel while preserving an exact rollback copy and every other boot input?
- changed variable: replace `/mnt/usb0/bzImage` with the clean-built
  `6.18.44-ps4-baikal` artifact, then replace only the corresponding bzImage
  line in `/mnt/usb0/SHA256SUMS`; bootargs, initramfs, vram, root filesystem,
  payload, and internal `/data/linux/boot` remain unchanged
- preconditions: clean build exit code 0; manifest has `active_patch_count=50`;
  local `SHA256SUMS` passes; new bzImage SHA-256 is
  `0d7cd17af71495df3e54f49fcfd31d41020ec096505f50e1938a4e92cb96f97b`;
  current remote bzImage and manifest must be downloaded and match the A14
  expected hash before either remote file is written
- expected evidence: bounded UART continuity remains valid; exact remote
  rereads of the new bzImage and refreshed manifest match their local hashes;
  every unchanged manifest entry remains byte-for-byte identical
- timeout: 120 seconds for the kernel upload, 30 seconds for the manifest,
  followed by one complete streamed hash verification
- rollback: restore the downloaded pre-action bzImage and `SHA256SUMS`, then
  reread and hash both. If the kernel upload or verification fails, do not
  launch Linux
- bounded UART context:
  [`20260811_012840_405243-exp-20260810-001-a18-stage-msi-treatment-kernel-on-external-fat-cffc433a.md`](../../ps4-uart/sessions/20260811_012840_405243-exp-20260810-001-a18-stage-msi-treatment-kernel-on-external-fat-cffc433a.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- result: pass. The downloaded pre-action kernel matched
  `bee03e870a9ab6116f9686f72bc1cf4872a1d65f13d20a62bd9fbb652775def1`
  and the pre-action manifest matched the A14 copy byte-for-byte. The uploaded
  kernel reread matched
  `0d7cd17af71495df3e54f49fcfd31d41020ec096505f50e1938a4e92cb96f97b`;
  the refreshed manifest reread matched
  `9a3e1142af8a9cd640ccc80ef5f3c9684dee36294abf05d56976f5f062e16bf6`.
  All ten manifest entries streamed from FTP and matched, including every
  unchanged boot and recovery file
- rollback state: exact pre-action `bzImage` and `SHA256SUMS` are preserved in
  ignored `output/EXP-20260810-001-A18/`; no rollback was needed
- next action: `EXP-20260810-001-A19`

### EXP-20260810-001-A19 — boot restored MSI treatment

- state: complete
- question: with interrupt remapping disabled, does the coherent Baikal MSI
  treatment let xHCI bind, enumerate the Kingston USB, and mount the XFCE root?
- changed variable: kernel code only relative to A15—the external bzImage now
  includes 0200 patches 0007+0008+0009. Use the same v25 1024 MB ELF, same
  `pci=nocrs intremap=off` bootargs, same initramfs, same USB, and same rootfs
- preconditions: PayLoader status `ready`; exact v25 ELF SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  remote bzImage and all manifest entries passed A18; continuous UART must be
  `READY` and a fresh bounded session active before the single POST
- expected evidence: loader identifies firmware 1202/Baikal and hands off;
  kernel reports the BPCIE MSI parent and `bpcie_config_msi`; xHCI avoids
  `Command Aborted`, Kingston `0951:1666` appears, `LABEL=OMARCHY-PS4` mounts,
  and systemd/LightDM/XFCE progress. HDMI outcome is recorded separately
- timeout: 180 seconds to root mount, desktop, or a stable terminal error;
  continued UART progress extends observation rather than being called a hang
- rollback: after recording a stable failure, power off in a separate bounded
  action. On the next clean GoldHEN runtime, restore A18's `.before` kernel and
  manifest over FTP and verify both before any further boot
- bounded UART context:
  [`20260811_013122_232315-exp-20260810-001-a19-boot-restored-msi-treatment-ef2cc9d5.md`](../../ps4-uart/sessions/20260811_013122_232315-exp-20260810-001-a19-boot-restored-msi-treatment-ef2cc9d5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: pending
- result: fail to reach xHCI within the action slice, with the restored MSI
  mechanism positively validated. The exact command line and kernel loaded;
  eight endpoint domains were marked MSI parents, 32 demux vectors registered,
  and `bpcie_config_msi` programmed southbridge messages. Unlike A15, BPCIE
  bound instead of remaining deferred. It then blocked in synchronous ICC
  setup: BT/WLAN timed out at 17.60 seconds and USB0 status timed out at 32.96
  seconds. The slice ended before xHCI, initramfs, or root discovery
- next action: `EXP-20260810-001-A20`, observation only; no second payload

### EXP-20260810-001-A20 — observe A19 ICC-probe continuation

- state: complete
- question: after the two captured ICC timeouts, does the already-running
  BPCIE probe finish, bind xHCI, or settle at another precise terminal point?
- changed variable: none. Observe the existing A19 boot without controller,
  payload, FTP, power, or USB action
- expected evidence: remaining ICC results and either BPCIE probe completion,
  xHCI/Kingston/root progress, or a stable last timeout
- timeout: observe to the original A19 180-second boundary; stop sooner only
  after UART has remained stable long enough to classify the terminal point
- rollback: none during observation. Any later power-off is a new bounded
  action after A20 is closed and reviewed
- bounded UART context:
  [`20260811_013331_842855-exp-20260810-001-a20-observe-a19-icc-probe-continuation-b36f7f01.md`](../../ps4-uart/sessions/20260811_013331_842855-exp-20260810-001-a20-observe-a19-icc-probe-continuation-b36f7f01.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- result: partial pass. BPCIE finished after about 105 seconds despite ICC
  setup timeouts. xHCI bound without `Command Aborted`; Kingston enumerated as
  `sda` with `sda1 sda2`; SDHCI bound and found its SDIO card; internal Toshiba
  SATA enumerated as `sdb`; and amdgpu initialized Liverpool through bridge
  attach. The display bridge then hit further ICC timeouts: pre-enable failed
  around 131.8 seconds, enable around 147.7 seconds, followed by another at
  163.0 seconds. UART continued after this slice, so root/initramfs outcome is
  not yet classified
- next action: `EXP-20260810-001-A21`, observation only

### EXP-20260810-001-A21 — observe post-bridge-timeout completion

- state: complete
- question: after MSI restored storage and GPU probing but ICC blocked HDMI
  sequencing, does the same boot still reach initramfs, mount the root, or stop
  at a later terminal error?
- changed variable: none. Observe the existing boot without any console,
  payload, FTP, USB, or power action
- expected evidence: final amdgpu result followed by `/init` and root mount, or
  an exact terminal error; HDMI remains an operator-observed outcome
- timeout: 60 seconds of stable UART after the final forward-progress marker
- rollback: none during observation; power-off is a separately declared action
- bounded UART context:
  [`20260811_013525_227610-exp-20260810-001-a21-observe-post-bridge-timeout-completion-823fc654.md`](../../ps4-uart/sessions/20260811_013525_227610-exp-20260810-001-a21-observe-post-bridge-timeout-completion-823fc654.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: first "check the logs it got stuck", then confirmed HDMI is
  black with the monitor backlight on
- result: fail to reach root, but not at the earlier MSI blocker. Repeated ICC
  bridge operations timed out through 241.34 seconds and emitted SDMA/GFX
  illegal-command errors. Nevertheless fbcon registered, amdgpu probe returned
  0, deferred AHCI bound, and `/init` ran at 242.88 seconds. Initramfs began at
  243.08 seconds with Kingston already enumerated as `sda` and partitions
  `sda1 sda2`, then stopped waiting for `LABEL=OMARCHY-PS4`
- next action: `EXP-20260810-001-A22`, observation only through the initramfs
  60-second root-discovery boundary

### EXP-20260810-001-A22 — observe visible-disk root-label timeout

- state: complete
- question: does initramfs eventually resolve the already-visible Kingston
  ext4 partition, or report a precise filesystem/label failure after 60 seconds?
- changed variable: none. Observe the existing boot without input or state
  change while inspecting the same initramfs locally
- expected evidence: root mount and switch-root, or the available-filesystem
  list and rescue-shell reason at the configured boundary
- timeout: the existing initramfs 60-second discovery window
- rollback: none during observation; power-off remains a separate action
- bounded UART context:
  [`20260811_013654_541250-exp-20260810-001-a22-observe-visible-disk-root-label-timeout-1b1c2dbd.md`](../../ps4-uart/sessions/20260811_013654_541250-exp-20260810-001-a22-observe-visible-disk-root-label-timeout-1b1c2dbd.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "check the logs it got stuck"
- result: pass for external root and graphical-userspace boot; fail for usable
  display/GPU. BusyBox `findfs` eventually resolved `LABEL=OMARCHY-PS4` to
  `/dev/sda2` at 321.69 seconds and ext4 mounted read-write. The delay exceeded
  the nominal 60 iterations because label scans also touched the internal
  `sdb` partition table and individual reads incurred I/O errors/timeouts.
  Systemd reached `Multi-User System`, started LightDM, reached `Graphical
  Interface`, and reported startup complete at 331.32 seconds. Wi-Fi scanning
  also ran. However the HDMI bridge ICC sequences had already timed out, and
  amdgpu continuously reported SDMA/GFX illegal command streams and ring fence
  fallback expirations. The console therefore appeared stuck even though
  userspace was alive
- rollback state: the new kernel remains on the external FAT and its exact A18
  rollback pair remains local; root mounted read-write, so power must be handled
  as a separately captured shutdown action
- next action: record exact HDMI state, then arm a bounded safe power-off. The
  next code experiment must separate ICC interrupt delivery from the already
  confirmed DRM bridge lifetime warning and GPU command-stream failures

### EXP-20260810-001-A23 — request orderly shutdown from black-display Linux

- state: complete with action-boundary overrun
- question: does one short PS4 power-button press reach Linux/systemd and
  produce an orderly shutdown without forcing power loss on the mounted root?
- changed variable: press and release the physical power button exactly once;
  do not hold it, press a controller button, remove USB, or send another input
- expected evidence: UART records a power-key event or systemd shutdown,
  filesystem sync/unmount, then LED/fan/backlight turn off
- timeout: 45 seconds after the single short press
- rollback: if nothing happens, report LED/fan/backlight state and review UART
  before considering a held-button shutdown
- bounded UART context:
  [`20260811_014011_232548-exp-20260810-001-a23-request-orderly-shutdown-from-black-display-3eb64ff6.md`](../../ps4-uart/sessions/20260811_014011_232548-exp-20260810-001-a23-request-orderly-shutdown-from-black-display-3eb64ff6.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "goldhen done loaded"
- result: fail for orderly Linux shutdown. UART contains continued amdgpu ring
  fence timeouts through kernel time 604.91 seconds, then jumps directly to the
  PS4 secure loader. There is no Linux power-key, systemd shutdown, sync, or
  unmount sequence. Orbis reports `last_shutdown_cause 01` and processes a cold
  system-crash report, confirming forced reset/power loss. The same slice then
  crosses undeclared cold-boot and jailbreak boundaries; firmware 12.02 reached
  Shell UI and GoldHEN reported `All done!` with PayLoader on port 9090
- rollback state: Orbis and GoldHEN recovered. The external ext4 root had been
  mounted read-write before forced reset, so the next boot must record journal
  recovery/filesystem evidence and no public support claim can rely on A23
- next action: stage the independently audited, single-variable rmux ICC poll
  fallback candidate. Keep the mandatory DRM lifetime repair and GPU ring
  failures separate; neither is changed in that candidate

### EXP-20260810-001-A24 — stage ICC polling candidate on external FAT

- state: complete
- question: can the verified 51-patch kernel replace only the external test
  kernel while preserving the exact A18 kernel/manifest rollback pair and every
  other boot input?
- changed variable: replace `/mnt/usb0/bzImage` with the clean-built
  `6.18.44-ps4-baikal` artifact containing only rmux patch 0012 in addition to
  A19's 50-patch kernel, then replace only the bzImage digest line in
  `/mnt/usb0/SHA256SUMS`; bootargs, initramfs, VRAM, root filesystem, payload,
  DRM lifetime, GPU code, and internal `/data/linux/boot` remain unchanged
- preconditions: OrbStack is running with Docker context `orbstack`; strict
  patch gate reports 51 applied, 0 skipped, 0 failed; complete build exited 0;
  local `SHA256SUMS` passes; manifest reports `active_patch_count=51`; candidate
  bzImage SHA-256 is
  `a5f3306d48a10762480701ef4e6721e34849e1603ee9b71aed63f69675766888`;
  continuous UART is `READY`; current remote bzImage and manifest must be
  downloaded and match A18 before either remote file is written
- expected evidence: bounded UART continuity remains valid; exact FTP rereads
  match the candidate kernel and refreshed manifest; the full remote manifest
  verifies all ten files and differs from A18 only in the bzImage digest line
- timeout: 120 seconds for the kernel upload, 30 seconds for the manifest, then
  one complete streamed verification pass
- rollback: restore A24's downloaded pre-action bzImage and manifest, reread
  and hash both, and do not launch Linux if any upload or verification fails
- bounded UART context:
  [`20260811_015619_231131-exp-20260810-001-a24-stage-icc-polling-candidate-on-external-fat-adbbb7f2.md`](../../ps4-uart/sessions/20260811_015619_231131-exp-20260810-001-a24-stage-icc-polling-candidate-on-external-fat-adbbb7f2.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- result: pass. Pre-action rereads were byte-identical to A18: bzImage
  `0d7cd17af71495df3e54f49fcfd31d41020ec096505f50e1938a4e92cb96f97b`
  and manifest
  `9a3e1142af8a9cd640ccc80ef5f3c9684dee36294abf05d56976f5f062e16bf6`.
  The candidate kernel reread matched
  `a5f3306d48a10762480701ef4e6721e34849e1603ee9b71aed63f69675766888`
  and the refreshed manifest reread matched
  `d50649d498ede96b44c89ae751d3aa1e3043e2d70370bd46fd823f608f69d4f7`.
  All ten manifest entries streamed from FTP and verified; only the bzImage
  digest line differs from A18. Exact pre-action rollback files are preserved
  under ignored `output/EXP-20260810-001-A24/`
- next action: `EXP-20260810-001-A25`

### EXP-20260810-001-A25 — boot ICC polling candidate

- state: complete
- question: does polling the BPCIE ICC status register recover the replies
  missed by IRQ delivery and allow the PS4 HDMI bridge to enable?
- changed variable: kernel code only relative to A19—the external bzImage adds
  rmux patch `0012-ps4-bpcie-icc-poll-fallback.patch`; use the same v25
  1024 MB ELF, exact `pci=nocrs intremap=off` bootargs, initramfs, VRAM, USB,
  Arch/XFCE root, and all DRM/GPU code from A19
- preconditions: PayLoader reports `ready`; exact v25 ELF SHA-256 is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  A24 verified the remote kernel and all ten manifest entries; continuous UART
  must be `READY` and a fresh bounded session active before one POST
- primary acceptance: `Turn ON BT/WLAN` completes without `ret=-110`; zero
  `icc: interrupted or timeout`; zero HDMI bridge pre-enable/config failures;
  preserve the MSI parent, xHCI/Kingston, `/dev/sda2` root, systemd, and XFCE
- separately recorded, not acceptance blockers for this one-variable test:
  `No irq handler for 0.227`, DRM bridge lifetime/refcount warnings, and GPU ring
  errors may remain. Root filesystem journal recovery or errors after A23's
  forced reset must be captured explicitly
- timeout: 180 seconds for the ICC/bridge result and 420 seconds for root and
  graphical userspace if UART continues making forward progress
- rollback: if the loader or kernel fails before providing stable evidence,
  return to a clean GoldHEN runtime in a separate action and restore A24's
  `.before` kernel and manifest; do not combine a DRM or GPU change into A25
- bounded UART context:
  [`20260811_015839_158378-exp-20260810-001-a25-boot-icc-polling-candidate-5d0a7857.md`](../../ps4-uart/sessions/20260811_015839_158378-exp-20260810-001-a25-boot-icc-polling-candidate-5d0a7857.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator HDMI report: "monitor flickered and backlight came out"; no visible
  console or XFCE image
- result: degraded overall and pass for the ICC hypothesis. `Turn ON BT/WLAN`
  completed at 6.19 seconds with `ret=20`; there were zero
  `icc: interrupted or timeout` lines. MSI/BPCIE remained bound, Kingston
  `0951:1666` appeared at 9.42 seconds, `/dev/sda2` resolved at 116.78 seconds,
  and ext4 removed one orphan inode, completed recovery, and mounted read-write.
  LightDM started and systemd reached `Graphical Interface` at 125.84 seconds.
  No SDMA/GFX illegal-command, ring-fence, or fence-timeout stream occurred in
  the bounded slice. HDMI still failed visually after a flicker/backlight
  transition: Linux 6.18 warned that the static PS4 bridge was not allocated by
  `devm_drm_bridge_alloc()`, then logged `refcount_t: underflow; use-after-free`
  from `drm_bridge_put()` during mode probing. fbcon still selected
  `amdgpudrmfb` and switched to its 240x67 framebuffer. Repeated
  `No irq handler for 0.227` remains, as expected with polling
- rollback state: candidate remains on external FAT; A24's exact pre-action
  kernel and manifest are preserved locally. Root is mounted read-write, so no
  power action may be combined with the next code/build work
- next action: local-only minimal Linux 6.18 devm DRM bridge lifetime patch and
  clean build. Keep ICC polling enabled and change no other boot or GPU input

### EXP-20260810-001-A26 — recover from A25 black-display Linux

- state: complete with action-boundary overrun
- question: can the console return from the inaccessible A25 Linux runtime to
  Orbis without introducing any staging or boot-input change?
- changed variable: one physical power action only, after operator confirmation;
  do not remove USB, send a payload, use FTP, or press another control inside
  this bounded action
- preconditions: A25 bounded session is closed; continuous UART is `READY`;
  the ext4 root is mounted read-write and no working power-key notification,
  visible console, network address, or SSH control path has been established
- expected evidence: Linux stops emitting, secure loader/Orbis boots, and the
  firmware reaches its normal UI; record whether the action was short, held,
  reset, or full power-off exactly as performed
- timeout: 120 seconds after the single confirmed physical action
- rollback: none; if Orbis does not boot, stop and inspect UART before another
  power action. Expect ext4 recovery again because this path is not orderly
- bounded UART context:
  [`20260811_021350_589864-exp-20260810-001-a26-recover-from-a25-black-display-linux-b60dd367.md`](../../ps4-uart/sessions/20260811_021350_589864-exp-20260810-001-a26-recover-from-a25-black-display-linux-b60dd367.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator report: "done, goldhen loaded"
- result: recovered, with undeclared additional power/boot/jailbreak actions.
  The slice first entered firmware 12.02 with `last_shutdown_cause 01`, later
  recorded a power-down/fatal-shutdown sequence, failed to mount system
  partitions, ran the firmware fsck/reboot path, then reached normal Orbis with
  `last_shutdown_cause 04`. Shell UI became ready and GoldHEN finished all
  patches with PayLoader on 9090. This proves the present runtime but cannot be
  treated as a clean single-action shutdown test
- rollback state: Orbis/GoldHEN recovered; PayLoader reports `ready`, FTP 2121
  is reachable, USB remains attached, and no boot files changed in A26
- next action: `EXP-20260810-001-A27`

### EXP-20260810-001-A27 — stage 6.18 DRM lifetime candidate

- state: complete
- question: can the verified 52-patch bzImage replace only A24's external test
  kernel while preserving an exact rollback copy and every other boot input?
- changed variable: replace `/mnt/usb0/bzImage` with the clean-built candidate
  that adds only `0034-amdgpu-ps4-bridge-devm-lifetime.patch` relative to A25,
  then replace only the bzImage digest line in `/mnt/usb0/SHA256SUMS`
- preconditions: GoldHEN/PayLoader and FTP are ready; OrbStack build exited 0;
  strict gate reports 52 applied, 0 skipped, 0 failed; all local output hashes
  pass; manifest reports `active_patch_count=52`; candidate bzImage SHA-256 is
  `f1a6eabe49f12853a0cc93af462b2153dc09b58de0c5bfc28bb2d6cc50fdc1dd`;
  current remote kernel and manifest must match A24 before either is written
- expected evidence: exact remote rereads match the candidate and refreshed
  manifest; the complete remote manifest verifies all ten files and differs
  from A24 only in the bzImage digest line; bounded UART continuity remains
  valid
- timeout: 120 seconds for kernel upload, 30 seconds for manifest, then one
  complete streamed verification pass
- rollback: restore A27's downloaded pre-action bzImage and manifest, reread
  and hash both, and do not launch Linux if any check fails
- bounded UART context:
  [`20260811_022044_478889-exp-20260810-001-a27-stage-6-18-drm-lifetime-candidate-8af5a301.md`](../../ps4-uart/sessions/20260811_022044_478889-exp-20260810-001-a27-stage-6-18-drm-lifetime-candidate-8af5a301.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- result: pass. Pre-action rereads matched A24 exactly: bzImage
  `a5f3306d48a10762480701ef4e6721e34849e1603ee9b71aed63f69675766888`
  and manifest
  `d50649d498ede96b44c89ae751d3aa1e3043e2d70370bd46fd823f608f69d4f7`.
  Candidate reread matched
  `f1a6eabe49f12853a0cc93af462b2153dc09b58de0c5bfc28bb2d6cc50fdc1dd`;
  refreshed manifest reread matched
  `8bd44ac612843d84e826d2b5db825b8c8d538ea1f079548f121e55c31260f620`.
  All ten manifest entries streamed and verified; only the bzImage digest line
  differs. Exact pre-action rollback files are preserved under ignored
  `output/EXP-20260810-001-A27/`
- next action: `EXP-20260810-001-A28`

### EXP-20260810-001-A28 — boot 6.18 DRM lifetime candidate

- state: complete
- question: with ICC completion and v60's proven TX-preservation behavior held
  constant, does a valid Linux 6.18 managed DRM bridge restore visible HDMI?
- changed variable: kernel code only relative to A25—the external bzImage adds
  `0034-amdgpu-ps4-bridge-devm-lifetime.patch`; same v25 1024 MB ELF, exact
  `pci=nocrs intremap=off` bootargs, initramfs, VRAM, USB, Arch/XFCE root,
  Liverpool firmware, ICC polling, and display programming patches
- preconditions: PayLoader reports `ready`; v25 ELF SHA-256 is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  A27 verified the remote kernel and all ten manifest files; continuous UART is
  `READY` and a fresh bounded session is active before one POST
- primary acceptance: zero `DRM bridge corrupted or not allocated`, zero bridge
  kref/refcount warning, and visible 1080p60 console or XFCE. Retain successful
  ICC, both `preserving PS4 DP TX lock` paths, xHCI/Kingston/root, systemd, and
  LightDM. Record flicker/backlight/image states separately
- firmware evidence: all eight Liverpool blobs must still extract; only
  missing `regulatory.db` is expected and belongs to later Wi-Fi setup
- timeout: 180 seconds for bridge/display result and 420 seconds for root and
  graphical userspace while UART makes forward progress
- rollback: if the kernel fails before stable evidence, return to a separately
  captured GoldHEN runtime and restore A27's `.before` pair. If lifetime errors
  disappear but HDMI remains black, do not change firmware blindly; next add a
  pointer-safe diagnostic for only bridge CQ results and `0x60f8/0x60f9`
- bounded UART context:
  [`20260811_022234_506080-exp-20260810-001-a28-boot-6-18-drm-lifetime-candidate-4c88e957.md`](../../ps4-uart/sessions/20260811_022234_506080-exp-20260810-001-a28-boot-6-18-drm-lifetime-candidate-4c88e957.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `1307aff7e5324e438f69fdeee53d995b`, epoch `1`
- operator HDMI report: "no hdmi output ... backlight black"
- result: fail for visible HDMI and pass for the isolated Linux 6.18 lifetime
  repair. All bridge-allocation and refcount/use-after-free warnings from A25
  disappeared. ICC returned `20`, Kingston enumerated, both v60 TX-preservation
  paths fired, fbcon selected `amdgpudrmfb`, and the console switched to its
  240x67 framebuffer. Root resolved at 90.28 seconds, ext4 recovery completed,
  LightDM started, and graphical target was reached at 98.95 seconds. There was
  no GPU illegal-command/ring/fence storm, but the monitor remained black with
  backlight. The exact booted initramfs does contain the 128-byte
  `edid/1920x1080.bin` and the kernel supports firmware EDID, but the PS4
  connector directly adds one hardcoded preferred 1080p60 mode and returns 1,
  so Linux's firmware-EDID fallback is not invoked. v60 used the same hardcoded
  mode path, so EDID consumption is cleanup—not the evidenced regression
- rollback state: A27's pre-action kernel/manifest pair is preserved locally;
  root is mounted read-write and no power action may be combined with local
  patch/build work
- next action: `EXP-20260810-001-A29`

### EXP-20260810-001-A29 — build post-lifetime HDMI diagnostic candidate

- state: complete
- question: can the missing MN864729 transmitter-state evidence be added after
  the accepted Linux 6.18 bridge-lifetime repair without changing EDID,
  display programming, payload, boot arguments, rootfs, or userspace?
- changed variable: add only local patch
  `0035-amdgpu-ps4-bridge-cq-lane-diagnostics.patch` after 0034. It timestamps
  bridge ICC command queues, brackets the unchanged monolithic MN864729 enable
  sequence, and reads `0x60f8`, `0x60f9`, `0x10f6`, and `0x7204` through the
  explicit devm-managed bridge pointer at enable entry and exit
- guard result: the first attempt to activate archived v55 patch 0029 failed
  the strict post-0034 apply gate at `ps4_bridge.c:595`. The gate exited 1; no
  kernel was built or staged from that attempt. Patch 0029 was returned to its
  disabled historical role and replaced by pointer-safe 0035
- build evidence: OrbStack was running and Docker context was `orbstack`;
  immutable base is `v6.18.44` at
  `1efe5d048a391de3ead2804b2e7f86376c356cc5`; the strict replacement gate
  applied 53 patches with 0 skipped and 0 failed; the full build exited 0; all
  six entries in `SHA256SUMS` verify; the built `ps4_bridge.o` contains all
  four `ps4_bridge_diag` UART format strings
- artifact evidence: bzImage size is 11,064,320 bytes and SHA-256 is
  `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`;
  manifest SHA-256 is
  `8e52f4510993ff2fc948999f860ff0e38109a2ee64d7ced81cd998383616a0f7`;
  manifest reports `active_patch_count=53` and series SHA-256
  `4feff2c8dc963a7947ad817b7c996fd973c2095e96c0353ae2ba1d7053199bda`
- provenance: 0035 is local diagnostic work derived from the hardware-tested
  v55/v60 history at commit `f5aea5d4d442d3227039d5bd0e7acb05aa4b01c7`,
  with rmux Liverpool comparison commit
  `c9e16f3ad2591c5e35fbe1fb81f02a8e799775ac` linked separately; it is not
  represented as an rmux patch
- result: pass for local build and artifact integrity; hardware result pending.
  No FTP write, USB mutation, PS4 power action, payload launch, or public push
  occurred. A28 Linux remains the last known console state and A27's verified
  rollback pair remains preserved
- next action: after the operator returns, recover A28 black-display Linux to
  Orbis in its own bounded UART action. Then load GoldHEN, stage the A29
  candidate rollback-safely, and boot it in a separate bounded session

### EXP-20260810-001-A30 — stage post-lifetime HDMI diagnostic candidate offline

- state: complete
- question: can the verified A29 diagnostic bzImage replace only the A28
  kernel on the externally attached FAT partition while preserving an exact
  rollback copy and every other boot input?
- changed variable: replace only `bzImage` with the A29 artifact that adds
  `0035-amdgpu-ps4-bridge-cq-lane-diagnostics.patch`, then replace only its
  digest line in `SHA256SUMS`; do not change initramfs, bootargs, VRAM,
  recovery files, root partition, payload, or console state
- preconditions: target is the 124.0 GB external physical USB with a 1.1 GB
  FAT32 partition and 122.9 GB Linux partition; the FAT manifest verifies;
  current bzImage is exact A28
  `f1a6eabe49f12853a0cc93af462b2153dc09b58de0c5bfc28bb2d6cc50fdc1dd`;
  candidate is exact A29
  `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`;
  continuous UART is `READY` and a fresh bounded session is active
- expected evidence: exact rollback copies of the old bzImage and manifest;
  candidate and refreshed manifest reread byte-identically; all ten FAT
  manifest entries verify; volume ejects cleanly
- timeout: 120 seconds for local backup, replacement, reread, full manifest
  verification, and clean eject
- rollback: restore A30's preserved `.before` bzImage and manifest, reread and
  verify both, and do not boot if any copy or verification fails
- bounded UART context:
  [`20260811_185253_415148-exp-20260810-001-a30-stage-post-lifetime-hdmi-diagnostic-candida-d4d386e5.md`](../../ps4-uart/sessions/20260811_185253_415148-exp-20260810-001-a30-stage-post-lifetime-hdmi-diagnostic-candida-d4d386e5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Preserved exact A28 bzImage
  `f1a6eabe49f12853a0cc93af462b2153dc09b58de0c5bfc28bb2d6cc50fdc1dd`
  and pre-action manifest
  `8bd44ac612843d84e826d2b5db825b8c8d538ea1f079548f121e55c31260f620`
  under ignored `output/EXP-20260810-001-A30/`. The staged bzImage reread
  byte-identically as
  `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`;
  refreshed manifest is
  `5794c8bd6ac9b30f94063ea71f106f6d672af7c9b102c1202d7c46be597f35a6`;
  all ten entries verified and the external disk ejected cleanly. The existing
  one-space `vram.txt` manifest separator still produces a formatting warning
  but its content digest passes. UART independently shows the PS4 is in Orbis
  and its proxied HTTP requests to `ps4-system.sec.np.dl.playstation.net`
  receive 404; this is proxy evidence, not DNS-blocking evidence
- rollback state: exact A28 kernel and manifest are preserved locally; USB is
  cleanly ejected from macOS and not attached to the PS4
- next action: `EXP-20260810-001-A31`

### EXP-20260810-001-A31 — attach staged USB to running Orbis

- state: complete with action-boundary overrun
- question: does Orbis detect the cleanly ejected USB containing the verified
  A29 boot set without a storage, USB, or filesystem error?
- changed variable: one physical action only—remove the already-ejected USB
  from the Mac and attach it to the PS4; do not launch GoldHEN, send a payload,
  power-cycle, or change network settings in this action
- preconditions: PS4 UART proves the console is in Orbis; continuous UART is
  `READY`; A30 is closed; candidate and complete FAT manifest verified before
  clean eject
- expected evidence: Orbis reports or UART records USB attachment without an
  error; record any visible notification exactly
- timeout: 60 seconds after insertion
- rollback: if Orbis reports corruption or an unsupported device, remove the
  USB only in a separate bounded action and restore A30's exact rollback pair
  on the Mac; do not boot Linux
- bounded UART context:
  [`20260811_185420_962608-exp-20260810-001-a31-attach-staged-usb-to-running-orbis-1f2cf3ec.md`](../../ps4-uart/sessions/20260811_185420_962608-exp-20260810-001-a31-attach-staged-usb-to-running-orbis-1f2cf3ec.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: USB attached and GoldHEN loaded
- result: pass for USB attachment. Kingston DataTraveler `0951:1666`
  enumerated at SuperSpeed as `da1`; Orbis mounted `da1s1` at `/mnt/usb0`
  as its exFAT-compatible FAT volume. `da1s2` was correctly reported as an
  unknown Orbis format because it is the Linux ext4 root. The initial whole-
  disk `REPORT LUNS` check-condition and mount rejection are normal probing,
  followed by successful partition mount. GoldHEN was an undeclared second
  action and is supported by the operator report, not an explicit marker in
  this compact UART slice
- rollback state: USB remains attached to the PS4; A29 boot set is staged;
  exact A28 rollback kernel and manifest remain local
- next action: `EXP-20260810-001-A32`

### EXP-20260810-001-A32 — boot 6.18 post-lifetime HDMI diagnostic candidate

- state: complete
- question: does the A29 pointer-safe diagnostic show whether the inherited
  MN864729 lane lock is valid at bridge-enable entry and whether the unchanged
  monolithic enable sequence preserves it on Linux 6.18?
- changed variable: kernel code only relative to A28—add
  `0035-amdgpu-ps4-bridge-cq-lane-diagnostics.patch`; keep the same v25
  1024 MB ELF, bootargs, initramfs, VRAM, USB/rootfs, firmware, ICC polling,
  devm bridge lifetime repair, and v60 TX-preservation fixes
- preconditions: user reports GoldHEN loaded; A30 verified and staged bzImage
  `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`;
  A31 proves FAT mounted at `/mnt/usb0`; continuous UART must be `READY` and a
  fresh bounded session active before one Linux payload launch
- primary acceptance: capture `ps4_bridge_diag` values for `0x60f8`, `0x60f9`,
  `0x10f6`, and `0x7204` at enable entry and exit plus main CQ return/timing;
  visible console/XFCE is the display pass condition. Preserve ICC, Kingston,
  `/dev/sda2`, systemd, and LightDM behavior from A28
- timeout: 180 seconds for bridge/display evidence and 420 seconds for root and
  graphical userspace while UART makes forward progress
- rollback: after closing A32, return to Orbis in a separate bounded action
  and restore A30's exact A28 kernel/manifest pair if the diagnostic kernel
  regresses boot stability; do not combine a command-queue split with A32
- bounded UART context:
  [`20260811_191304_976929-exp-20260810-001-a32-boot-6-18-post-lifetime-hdmi-diagnostic-can-f704e46f.md`](../../ps4-uart/sessions/20260811_191304_976929-exp-20260810-001-a32-boot-6-18-post-lifetime-hdmi-diagnostic-can-f704e46f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail before Linux launch. The local pinned ELF digest passed, but an
  empty TCP readiness probe connected to GoldHEN port 9090 before the actual
  send; UART then recorded `[GoldHEN] <payloader> Error handling payload` and
  no kexec or Linux marker. This is a client preflight error, not evidence
  about the A29 kernel, USB boot set, or HDMI
- rollback state: Orbis/GoldHEN remains running and USB remains attached; no
  Linux state or boot files changed
- next action: `EXP-20260810-001-A33`; use one connection containing the exact
  ELF and perform no empty port probe

### EXP-20260810-001-A33 — boot A29 with single-connection GoldHEN send

- state: complete
- question: with the client preflight error removed, does the pinned v25 ELF
  launch the staged A29 kernel and capture the post-lifetime HDMI diagnostics?
- changed variable relative to A32: sender behavior only—open exactly one TCP
  connection to GoldHEN 9090 containing the complete exact ELF; no preceding
  readiness connection. Kernel, loader bytes, boot set, USB, and console state
  remain unchanged
- preconditions: A32 closed without entering Linux; continuous UART must be
  `READY`; pinned ELF SHA-256 is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`
- primary acceptance: GoldHEN accepts and launches the ELF, sys_kexec loads
  Linux 6.18.44, and A29 records bridge entry/exit values and CQ timing; visible
  console/XFCE remains the display pass condition
- timeout: 30 seconds for loader/kexec evidence, 180 seconds for bridge/display,
  and 420 seconds for root/userspace while UART makes forward progress
- rollback: if 9090 refuses or rejects this single send, close A33 and reload
  GoldHEN separately before any further send; if Linux boots but fails, recover
  in its own bounded action using A30's exact rollback pair
- bounded UART context:
  [`20260811_191432_453104-exp-20260810-001-a33-boot-a29-with-single-connection-goldhen-sen-f047c333.md`](../../ps4-uart/sessions/20260811_191432_453104-exp-20260810-001-a33-boot-a29-with-single-connection-goldhen-sen-f047c333.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail before payload acceptance. The first corrected command failed
  locally because Apple `nc -N` requires an argument and therefore opened no
  connection. A subsequent one-connection `nc -w 5` send returned 1, while
  UART contained only normal Orbis messages—no PayLoader accept/error, kexec,
  or Linux marker. The A32 empty connection appears to have left port 9090's
  PayLoader unavailable. No kernel evidence was produced
- rollback state: Orbis remains running and USB attached; A29 boot set and A28
  local rollback are unchanged
- next action: `EXP-20260810-001-A34`; reload GoldHEN/PayLoader without sending
  Linux, then close and review that action before another payload connection

### EXP-20260810-001-A34 — reload GoldHEN PayLoader after empty connection

- state: complete
- question: does one operator GoldHEN reload restore the PayLoader service
  after A32's empty TCP connection without changing USB, boot inputs, or
  network configuration?
- changed variable: reload GoldHEN only; do not send the Linux ELF, launch a
  second payload, remove USB, or power-cycle
- preconditions: A33 closed with no payload acceptance or Linux transition;
  Orbis remains responsive; continuous UART must be `READY` and a fresh
  bounded session active
- expected evidence: GoldHEN completes normally and the operator reports it
  loaded; no shutdown, kexec, or Linux marker
- timeout: 120 seconds
- rollback: if GoldHEN fails, close A34 and diagnose its compact UART context
  before any repeat or power action
- bounded UART context:
  [`20260811_191552_104047-exp-20260810-001-a34-reload-goldhen-payloader-after-empty-connec-63326b9d.md`](../../ps4-uart/sessions/20260811_191552_104047-exp-20260810-001-a34-reload-goldhen-payloader-after-empty-connec-63326b9d.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: GoldHEN is up at `192.168.50.215`
- result: pass by operator report for the declared reload; UART continuity is
  valid and shows Orbis remained responsive with no shutdown, kexec, Linux, or
  explicit error, but this slice contains no definitive GoldHEN/PayLoader
  marker. Verify through FTP without touching port 9090 before the next send
- rollback state: Orbis/GoldHEN reported running; USB attached; boot inputs
  unchanged
- next action: `EXP-20260810-001-A35`

### EXP-20260810-001-A35 — verify GoldHEN FTP and staged A29 at 192.168.50.215

- state: complete
- question: does GoldHEN FTP respond at `192.168.50.215:2121`, and does a
  read-only stream of `/mnt/usb0/bzImage` still match the staged A29 digest?
- changed variable: one read-only FTP verification; do not connect to PayLoader
  9090, write a file, launch a payload, or change console state
- preconditions: A34 closed; user reports GoldHEN up; continuous UART must be
  `READY` and a fresh bounded session active
- expected evidence: anonymous FTP transfer succeeds and streamed bzImage is
  `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`
- timeout: 60 seconds
- rollback: none needed for a read-only transfer; if it fails, close and inspect
  before reloading or probing another port
- bounded UART context:
  [`20260811_191716_514010-exp-20260810-001-a35-verify-goldhen-ftp-and-staged-a29-at-192-16-ef866186.md`](../../ps4-uart/sessions/20260811_191716_514010-exp-20260810-001-a35-verify-goldhen-ftp-and-staged-a29-at-192-16-ef866186.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Anonymous GoldHEN FTP at `192.168.50.215:2121` streamed
  `/mnt/usb0/bzImage` successfully; its SHA-256 was exactly
  `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`.
  Port 9090 was not touched and no PS4 file was written
- rollback state: Orbis/GoldHEN remains running; verified A29 boot set remains
  attached and unchanged
- next action: `EXP-20260810-001-A36`

### EXP-20260810-001-A36 — boot verified A29 through one raw socket send

- state: complete
- question: does one raw socket connection containing the exact pinned v25
  ELF launch verified A29 and expose the Linux 6.18 bridge state responsible
  for the remaining black display?
- changed variable relative to A33: GoldHEN was reloaded and independently
  verified through FTP; use the existing socket sender for one `sendall()` to
  port 9090 with no readiness probe. All kernel and boot inputs remain exact
- preconditions: A35 proves `192.168.50.215` and A29 bzImage; pinned ELF is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  continuous UART must be `READY` and a fresh bounded session active
- primary acceptance: PayLoader accepts/launches, sys_kexec enters Linux
  6.18.44, and `ps4_bridge_diag` captures entry/exit values and CQ timing;
  visible console or XFCE is the HDMI pass condition
- timeout: 30 seconds for loader/kexec, 180 seconds for bridge/display, and
  420 seconds for root/userspace while UART makes forward progress
- rollback: if the sender cannot connect, close A36 without retry and reload
  PayLoader separately; if Linux boots but fails, recover to Orbis in a new
  bounded action and retain A30's exact rollback pair
- bounded UART context:
  [`20260811_191817_990060-exp-20260810-001-a36-boot-verified-a29-through-one-raw-socket-se-3bed31f0.md`](../../ps4-uart/sessions/20260811_191817_990060-exp-20260810-001-a36-boot-verified-a29-through-one-raw-socket-se-3bed31f0.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail before payload transfer. The pinned ELF digest passed, but the
  one real socket connection to `192.168.50.215:9090` returned
  `ConnectionRefusedError`; the bounded UART slice is empty and no bytes
  reached a PayLoader. A35 independently proves the address, FTP service, and
  staged kernel, so GoldHEN is running but its BinLoader/PayLoader listener is
  disabled or stopped. This is not kernel or HDMI evidence
- rollback state: Orbis/GoldHEN and FTP remain available; USB and boot inputs
  unchanged
- next action: `EXP-20260810-001-A37`

### EXP-20260810-001-A37 — enable GoldHEN BinLoader server on port 9090

- state: complete
- question: does enabling GoldHEN's BinLoader/PayLoader server expose port
  9090 without launching a payload or changing the USB boot set?
- changed variable: operator enables only the GoldHEN BinLoader Server setting;
  do not send Linux, remove USB, reload GoldHEN, or power-cycle
- preconditions: A36 closed after an explicit connection refusal; FTP at 2121
  remains proven; continuous UART must be `READY` and a fresh bounded session
  active
- expected evidence: GoldHEN UI reports BinLoader Server enabled/listening on
  port 9090; operator records the exact displayed state. Do not test it with an
  empty TCP connection
- timeout: 60 seconds after the setting is enabled
- rollback: if the setting is unavailable or errors, leave it unchanged, close
  A37, and inspect GoldHEN version/settings before another payload attempt
- bounded UART context:
  [`20260811_191905_476548-exp-20260810-001-a37-enable-goldhen-binloader-server-on-port-909-bff5bd2a.md`](../../ps4-uart/sessions/20260811_191905_476548-exp-20260810-001-a37-enable-goldhen-binloader-server-on-port-909-bff5bd2a.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: setting fixed; try again
- result: pass. UART records entry into `id_goldhen_servers_settings` followed
  by `[GoldHEN] <payloader> Server started at 9090 port`. No payload or Linux
  transition occurred in this action
- rollback state: PayLoader is listening at `192.168.50.215:9090`; FTP and USB
  remain available; boot inputs unchanged
- next action: `EXP-20260810-001-A38`

### EXP-20260810-001-A38 — boot verified A29 after PayLoader enable

- state: complete
- question: does one exact pinned-ELF `sendall()` to the now-proven PayLoader
  launch A29 and identify the Linux 6.18 HDMI regression state?
- changed variable relative to A36: PayLoader is now explicitly enabled and
  UART-proven listening; use the same one-connection socket sender and exact
  loader/kernel/boot inputs
- preconditions: A37 closed with `Server started at 9090 port`; A35 verified
  A29 bzImage; pinned v25 ELF is
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  continuous UART must be `READY` and a fresh bounded session active
- primary acceptance: PayLoader accepts and launches, sys_kexec enters Linux
  6.18.44, `ps4_bridge_diag` records entry/exit/CQ evidence, and the operator
  reports HDMI flicker/backlight/image state; visible console/XFCE is pass
- timeout: 30 seconds for loader/kexec, 180 seconds for bridge/display, and
  420 seconds for root/userspace while UART makes forward progress
- rollback: if the single send fails, close before another attempt; if Linux
  boots but display fails, recover in a new bounded action and retain A30's
  exact A28 rollback pair
- bounded UART context:
  [`20260811_192118_818421-exp-20260810-001-a38-boot-verified-a29-after-payloader-enable-d4e2c4d6.md`](../../ps4-uart/sessions/20260811_192118_818421-exp-20260810-001-a38-boot-verified-a29-after-payloader-enable-d4e2c4d6.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: monitor remained completely blank; no console or XFCE image
- result: fail for HDMI, pass for the loader, kernel, USB root, and userspace.
  PayLoader accepted and launched the exact v25 ELF; Linux 6.18.44 entered;
  both `ps4_bridge_diag` cycles completed their monolithic main queue in about
  0.8 seconds with lane state `0x60f8=0xff`, `0x60f9=0x1b`; the PS4-specific
  TX DISABLE and ENABLE preservation gates both fired; fbcon selected
  `amdgpudrmfb`; `/dev/sda2` mounted read-write; systemd reached graphical
  target and started LightDM. There is no bridge lifetime fault, CQ timeout,
  lane-lock loss, GPU ring/fence storm, or root-device failure. Compared with
  the visible v60 Linux 6.15.4 checkpoint, the unresolved fault is above the
  MN864729 bridge in the AMD CRTC/PLL/DIG/primary-plane scanout path. EDID is
  not implicated because the forced canonical 1080p mode was selected
- rollback state: Linux remains running with the ext4 root mounted read-write;
  do not remove the USB or power-cycle outside a new bounded recovery session.
  A30's exact A28 kernel pair remains available locally
- next action: local-only source comparison and a minimal A39 scanout-register
  diagnostic after patch 0035; no console action until that artifact passes
  the local build gate

### EXP-20260810-002 — Linux 6.18.44/XFCE cold boot 2

- state: ready after A43 HDMI/XFCE pass
- purpose: repeat the exact accepted A39 setup from a true cold boot without
  changing any artifact or boot parameter
- bounded UART context: pending
- result: pending

### EXP-20260810-001-A39 — stage split-boundary A39 kernel

- state: complete
- question: can the cleanly built 54-patch A39 kernel replace only the USB
  kernel artifact and its checksum metadata with an exact FTP-verifiable copy?
- changed variable: replace `/mnt/usb0/bzImage` with the A39 artifact SHA-256
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`
  and refresh only its `SHA256SUMS` entry; initramfs, bootargs, vram, rootfs,
  payload, and console settings remain unchanged
- preconditions: operator reports USB connected and GoldHEN loaded; the local
  OrbStack build applied 54/54 patches and completed kernel/modules output;
  continuous UART must be `READY` and a fresh bounded session active
- expected evidence: preserve the current remote kernel and manifest locally,
  upload the A39 pair, then stream both back over FTP and verify the exact
  kernel hash plus a passing manifest check
- timeout: 120 seconds for backup, upload, and read-back verification
- rollback: restore the preserved A29 `bzImage` and prior `SHA256SUMS` over FTP
  in a separately recorded bounded action if any verification fails
- bounded UART context:
  [`20260811_194211_038602-exp-20260810-001-a39-stage-split-boundary-kernel-af0b8c19.md`](../../ps4-uart/sessions/20260811_194211_038602-exp-20260810-001-a39-stage-split-boundary-kernel-af0b8c19.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. The prior remote kernel was preserved locally with exact A29
  SHA-256 `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e`.
  FTP upload and read-back produced exact A39 SHA-256
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`;
  the remote manifest matched the staged copy and every one of its ten files
  streamed back with the declared hash. UART continuity remained valid
- rollback state: A29 `bzImage` and the prior manifest are preserved in local
  ignored `output/EXP-20260810-001-A39/`; USB now contains the verified A39
  kernel pair and GoldHEN remains running
- next action: `EXP-20260810-001-A40` only after A39 closes as pass

### EXP-20260810-001-A40 — boot split-boundary A39 kernel

- state: complete
- question: with every other boot input unchanged, do the three v60-proven
  MN864729 transaction boundaries restore a visible HDMI console/XFCE image?
- changed variable relative to A38: kernel patch 0036 splits only the bridge
  lane, HDMI-update, and PLL/finalize stages and reads back their waited-on
  registers; loader, initramfs, bootargs, USB root, and userspace are unchanged
- expected evidence: all three `split-stage` records return successfully,
  `0x60f8=0xff`/`0x60f9=0x1b` remain locked, and the operator reports the exact
  flicker/backlight/image state; a visible console or XFCE session is pass
- timeout: 30 seconds for loader/kexec, 180 seconds for display, and 420
  seconds for root/userspace while UART makes forward progress
- rollback: if HDMI remains blank, close A40 before any retry; recover Orbis in
  a new bounded action and retain A39's saved A29 kernel/manifest pair
- bounded UART context:
  [`20260811_194414_210384-exp-20260810-001-a40-boot-split-boundary-kernel-d16c5dba.md`](../../ps4-uart/sessions/20260811_194414_210384-exp-20260810-001-a40-boot-split-boundary-kernel-d16c5dba.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: invalid as a PayLoader/kernel attempt, not kernel evidence. The exact
  v25 ELF passed its local hash preflight, but the host invocation omitted the
  port argument and the helper silently targeted its default port `50000`,
  which returned `ConnectionRefusedError`. UART contains no PayLoader accept,
  loader, kexec, or Linux transition because port 9090 was never contacted
- rollback state: Orbis/GoldHEN remains running, the verified A39 USB bundle is
  unchanged, and no payload bytes were sent
- next action: `EXP-20260810-001-A41`, enable BinLoader without sending Linux

### EXP-20260810-001-A41 — re-enable GoldHEN BinLoader for A39

- state: complete
- question: does toggling only GoldHEN's BinLoader Server setting restore its
  9090 listener without changing USB files or launching a payload?
- changed variable: enable only BinLoader Server in GoldHEN Server Settings
- expected evidence: UART records `<payloader> Server started at 9090 port`;
  do not probe the port or send Linux during this action
- timeout: 60 seconds after the setting is enabled
- rollback: if the setting errors, leave Orbis running and inspect GoldHEN
  state after closing this session
- bounded UART context:
  [`20260811_194457_406622-exp-20260810-001-a41-re-enable-goldhen-binloader-for-a39-43dd3246.md`](../../ps4-uart/sessions/20260811_194457_406622-exp-20260810-001-a41-re-enable-goldhen-binloader-for-a39-43dd3246.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: done
- result: pass. UART records entry into `id_goldhen_servers_settings`, the old
  socket aborting, and a fresh `<payloader> Server started at 9090 port`. No
  Linux payload was sent and no USB file changed
- rollback state: PayLoader is freshly listening; verified A39 USB unchanged
- next action: `EXP-20260810-001-A42` only after A41 passes

### EXP-20260810-001-A42 — boot split-boundary A39 after listener restore

- state: complete
- question, changed variable, acceptance, timeout, and rollback: identical to
  A40, except A41 must first provide fresh UART proof that PayLoader is
  listening; use one real exact-ELF connection with no readiness probe
- bounded UART context:
  [`20260811_194659_777042-exp-20260810-001-a42-boot-split-boundary-a39-after-listener-rest-cb732b09.md`](../../ps4-uart/sessions/20260811_194659_777042-exp-20260810-001-a42-boot-split-boundary-a39-after-listener-rest-cb732b09.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: invalid as a PayLoader/kernel attempt due to a host invocation error.
  The helper was called without its explicit port argument and silently used
  its default port `50000`, producing `ConnectionRefusedError`. UART contains
  no PayLoader activity because port 9090 was never contacted. This does not
  contradict A41's fresh listener evidence and did not consume the listener
- rollback state: Orbis/GoldHEN and verified A39 USB remain unchanged
- next action: `EXP-20260810-001-A43`, correct only the sender target to the
  explicit UART-proven port 9090

### EXP-20260810-001-A43 — boot A39 through explicit port 9090

- state: complete
- question and acceptance: identical to A40; does the A39 split-boundary
  kernel restore visible HDMI while preserving the proven bridge lane state?
- changed variable relative to invalid A42: invoke the same sender with the
  explicit GoldHEN port `9090`; ELF bytes and every boot input are unchanged
- expected evidence: PayLoader accepts exactly 320936 bytes, Linux 6.18.44
  enters, all three `split-stage` records complete, and operator reports the
  exact HDMI state
- timeout: 30 seconds for loader/kexec, 180 seconds for display, and 420
  seconds for root/userspace while UART makes forward progress
- rollback: close before any retry; if Linux boots blank, recover Orbis only in
  a new bounded action and retain the saved A29 rollback pair
- bounded UART context:
  [`20260811_194803_672932-exp-20260810-001-a43-boot-a39-through-explicit-port-9090-732b5410.md`](../../ps4-uart/sessions/20260811_194803_672932-exp-20260810-001-a43-boot-a39-through-explicit-port-9090-732b5410.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: monitor works and the GUI is visible
- result: pass. GoldHEN accepted and launched the exact 320936-byte v25 ELF;
  Linux reports `6.18.44-ps4-baikal` build `#5`. Both initial attach and fbcon
  modeset completed `split-stage=lane`, `split-stage=hdmi-update`, and
  `split-stage=pll-finalize` successfully. Lane readback remained locked at
  `0x60f8=0xff` and `0x60f9=0x1b`; HDMI-update reached `0x10f6=0xd5` before
  finalization. DRM selected `amdgpudrmfb` as fb0, `/dev/sda2` mounted
  read-write, systemd reached `Graphical Interface`, and the operator confirmed
  a visible monitor image and GUI. This isolates the A38 black-screen
  regression to the monolithic MN864729 command-queue transaction: restoring
  the v60-proven stage boundaries fixes HDMI on Linux 6.18.44
- accepted artifact: A39 bzImage SHA-256
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`;
  patch 0036 SHA-256
  `f0fd06a7951f3d5707b83ed88d9cdc19a3360436f69906b74d849be62acce2a2`;
  active series SHA-256
  `a498f73bfb6d7896187dd04f40e1bbb64ca4e5fb1eeb453534a38d2f661853f5`
- next action: preserve this exact boot set and perform
  `EXP-20260810-002` as a second cold boot before release acceptance; do not
  change the kernel, payload, boot arguments, initramfs, or userspace

### EXP-20260810-001-A44 — Wi-Fi adapter inventory

- state: complete
- question: which available internal or USB Wi-Fi path can NetworkManager use
  without changing the accepted A39 kernel?
- changed variable: none; inspect the already-running A39 system and adapters
  already connected by the operator
- expected evidence: identify each radio by USB/SDIO ID, driver, firmware
  status, rfkill state, NetworkManager state, and scan result before attempting
  a connection
- timeout: 10 minutes for the read-only inventory
- rollback: none required for inventory; do not install packages, unload
  drivers, or alter the accepted USB boot set during this action
- bounded UART context:
  [`20260811_195826_963311-exp-20260810-001-a44-wi-fi-adapter-inventory-159e40ea.md`](../../ps4-uart/sessions/20260811_195826_963311-exp-20260810-001-a44-wi-fi-adapter-inventory-159e40ea.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- preliminary UART evidence: the built-in MT7668 driver repeatedly enters and
  completes scans. USB `2357:0138` is a Realtek RTL8822BU; `rtw88_8822bu`
  binds but probe fails because `rtw88/rtw8822b_fw.bin` is absent. USB
  `0bda:8179` enumerates as an 802.11n Realtek adapter but no driver binds
- provenance check: rmuxnet's public kernel repository does not contain the
  firmware blob. Local tag `v62-wifi-ssh` records this exact TP-Link
  `2357:0138`/RTL8822BU path working with `rtw88` and SSH after firmware was
  installed in the rootfs. The canonical upstream `linux-firmware` file is
  `rtw88/rtw8822b_fw.bin`, 161240 bytes, SHA-256
  `a72da690597bfa99d8eb6fc2ab090d18d8ad92ac2befd35db1c9e3662d8d8418`;
  upstream WHENCE marks it redistributable under
  `LICENCE.rtlwifi_firmware.txt`. Arch ships it in `linux-firmware-realtek`,
  which is now included in the future XFCE image package list
- operator report: Wi-Fi works through `nmcli`
- result: pass for the internal MT7668 and NetworkManager path. The built-in
  radio scans and the operator established working Wi-Fi with `nmcli` without
  changing the kernel or installing firmware. The RTL8822BU remains a valid
  fallback after installing `linux-firmware-realtek`; USB `0bda:8179` remains
  unsupported by the current kernel configuration
- privilege note: the deployed baseline manifest records
  `development_ssh=false`, `root_account_locked=true`, and
  `user_account_locked=true`. There is no default `ps4` sudo password. Future
  development images should use an operator public key and passwordless sudo,
  or explicitly provision a private first-boot password
- next action: `EXP-20260810-001-A45`; verify noninteractive sudo state, then
  provision controlled administrative access as a separate changed variable

### EXP-20260810-001-A45 — verify deployed privilege boundary

- state: complete
- question: can the active local `ps4` session create a user-private
  NetworkManager connection without sudo?
- changed variable: request a user-private connection (`private yes`) instead
  of the rejected default system-wide connection; kernel, radio, firmware,
  rootfs files, and account state remain unchanged
- expected evidence: NetworkManager either creates and activates an
  owner-restricted profile or returns an exact polkit authorization failure
- timeout: 2 minutes
- rollback: delete the private profile only if it is created but cannot
  activate; no privilege or filesystem changes in this action
- bounded UART context:
  [`20260811_200420_309554-exp-20260810-001-a45-verify-deployed-sudo-state-3552ce6e.md`](../../ps4-uart/sessions/20260811_200420_309554-exp-20260810-001-a45-verify-deployed-sudo-state-3552ce6e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: the default connection failed with insufficient privileges,
  `sudo` required a password, and `nmcli --ask ... private yes` connected
- result: pass. The active `ps4` desktop session can create and activate an
  owner-private NetworkManager profile without administrative access. The
  deployed account has neither passwordless sudo nor a usable known password,
  matching the locked-account build manifest
- next action: `EXP-20260810-001-A46`; obtain the DHCP address and start a
  temporary unprivileged, key-only SSH daemon on a high port

### EXP-20260810-001-A46 — temporary key-only SSH on port 2222

- state: complete; superseded before SSH launch
- question: can the connected `ps4` user expose a temporary development shell
  without sudo, password authentication, or system configuration changes?
- changed variable: create user-owned SSH host/authorized-key files and run
  `/usr/bin/sshd` as `ps4` on unprivileged TCP port 2222; Wi-Fi, kernel,
  accounts, and system sshd remain unchanged
- expected evidence: report the DHCP IPv4 address, bind port 2222, and accept
  the operator's GitHub-published ED25519 key fingerprint
  `SHA256:N64LAFp/1IpDOVOrMNVY3Bd6JHn2qxAyvT0/8FZ3T0M`
- timeout: 5 minutes
- rollback: stop the user-owned sshd process and remove its files under
  `/home/ps4/.local/state/omarchy-ps4-sshd`; no system file is touched
- bounded UART context:
  [`20260811_201016_311087-exp-20260810-001-a46-temporary-key-only-ssh-on-port-2222-b770a8d4.md`](../../ps4-uart/sessions/20260811_201016_311087-exp-20260810-001-a46-temporary-key-only-ssh-on-port-2222-b770a8d4.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: Linux DHCP address is `192.168.50.125`; requested an
  offline USB provisioning path instead of entering a long console command
- result: no SSH daemon was launched and no files were changed. The empty
  bounded UART slice is expected. The address is recorded as a DHCP
  observation in the hardware knowledge base
- next action: `EXP-20260810-001-A47`; cleanly power off Linux, then attach the
  root USB to the Mac for offline administrative-access provisioning

### EXP-20260810-001-A47 — clean Linux shutdown before USB provisioning

- state: complete
- question: can the active graphical session power off cleanly so the ext4
  root USB can be moved to the Mac without filesystem damage?
- changed variable: power state only; use XFCE's authenticated local-session
  shutdown action, with no kernel, storage, network, or account changes
- expected evidence: systemd stops userspace, unmounts `/dev/sda2`, and reaches
  power-off without an ext4 error or forced reset
- timeout: 3 minutes
- rollback: if graphical shutdown is unavailable, stop and inspect; do not
  unplug USB or hard-power-off while Linux still runs
- bounded UART context:
  [`20260811_201542_454282-exp-20260810-001-a47-clean-linux-shutdown-before-usb-provisionin-25b2ac0b.md`](../../ps4-uart/sessions/20260811_201542_454282-exp-20260810-001-a47-clean-linux-shutdown-before-usb-provisionin-25b2ac0b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: USB plugged into the Mac after shutdown
- result: pass. systemd stopped the graphical and network targets, remounted
  ext4 root UUID `ef824166-99bd-453b-80b7-de1c50c7548b` read-only, reported
  all filesystems unmounted, synchronized block devices, and reached
  `reboot: Power down`. OrbStack's subsequent read-only `e2fsck -fn` completed
  all five passes without reporting an error
- next action: `EXP-20260810-001-A48`; provision only the verified ext4 root
  partition while preserving the FAT boot partition and accepted A39 kernel

### EXP-20260810-001-A48 — offline development access and UX provisioning

- state: complete
- question: can the verified USB root be provisioned with the requested debug
  credential, sudo, SSH, Realtek firmware, fastfetch, and graphical Wi-Fi
  controls without modifying the accepted kernel or FAT boot files?
- changed variable: ext4 root userspace only. Set `ps4/ps4`, add `ps4` to
  `wheel`, enable password and public-key SSH, install `fastfetch`,
  `network-manager-applet`, and `linux-firmware-realtek`, and unpack the exact
  RTL8822B firmware because the current kernel lacks Zstd firmware support
- preconditions: exact USB is Kingston `0951:1666`; OrbStack device
  `/dev/sda2`, label `OMARCHY-PS4`, UUID
  `ef824166-99bd-453b-80b7-de1c50c7548b`; read-only filesystem check passed;
  Docker context is `orbstack`
- expected evidence: package database records all three requested packages;
  `ps4` has a set password and wheel membership; sudoers and sshd validate;
  sshd is enabled; authorized key fingerprint is
  `SHA256:N64LAFp/1IpDOVOrMNVY3Bd6JHn2qxAyvT0/8FZ3T0M`; uncompressed
  `rtw8822b_fw.bin` SHA-256 is
  `a72da690597bfa99d8eb6fc2ab090d18d8ad92ac2befd35db1c9e3662d8d8418`
- timeout: 15 minutes while package downloads make progress
- rollback: restore account/SSH files from the timestamped backup under
  `/var/lib/omarchy-ps4/provision-backups`; remove the three packages and
  uncompressed firmware if validation fails. FAT `/dev/sda1` is never mounted
- bounded UART context: not applicable while the powered-off USB is attached
  to the Mac; filesystem and package-manager evidence replaces UART
- implementation: added reusable
  `scripts/provision-debug-rootfs`, development-only sudo/SSH policy templates,
  and future-image package entries for `fastfetch`, `network-manager-applet`,
  and `linux-firmware-realtek`. The provisioner creates timestamped account,
  SSH, and package backups before applying changes
- result: pass after two bounded pre-change failures. Attempt 1 stopped during
  pacman database synchronization because the offline chroot cannot use
  pacman's seccomp sandbox; `--disable-sandbox` was then scoped to this
  provisioner. Attempt 2 stopped at DNS because the powered-off rootfs had an
  empty NetworkManager-generated `resolv.conf`; OrbStack's resolver was bound
  into the chroot for the install only and the target file was not replaced.
  The final run installed `fastfetch 2.67.0-1`,
  `network-manager-applet 1.36.0-2`, and
  `linux-firmware-realtek 20260622-1`; set `ps4/ps4`; added groups include
  `wheel`; installed and validated sudo policy; generated SSH host keys;
  enabled `sshd.service`; enabled password and public-key SSH while keeping
  root login disabled; and installed the operator ED25519 key with the
  expected fingerprint
- firmware result: because A39 has `CONFIG_FW_LOADER_COMPRESS_ZSTD` disabled,
  the Arch package's `rtw8822b_fw.bin.zst` was also decompressed to the exact
  runtime path. The resulting 161240-byte `rtw88/rtw8822b_fw.bin` SHA-256 is
  `a72da690597bfa99d8eb6fc2ab090d18d8ad92ac2befd35db1c9e3662d8d8418`
- backup: latest pre-provision snapshot is
  `/var/lib/omarchy-ps4/provision-backups/20260811T142716Z`; earlier stopped
  attempts also created untouched timestamped backups
- close verification: sudoers, `pwck`, `grpck`, and `sshd -t` passed; package
  queries and systemd enable state passed; a post-write read-only `e2fsck -fn`
  completed all five passes without error. `/dev/sda1` was never mounted, so
  the accepted A39 FAT boot set was not modified. OrbStack detached the USB
  cleanly after all mounts were released
- security state: this intentionally weak `ps4/ps4` credential and password
  SSH are development-only and must not appear in a public image or release
- next action: `EXP-20260810-001-A49`; attach USB to the PS4, boot the exact
  unchanged A39 kernel, then verify GUI Wi-Fi controls, `fastfetch`, sudo, and
  SSH at the observed Linux address or its new DHCP lease

### EXP-20260810-001-A49 — attach provisioned USB to powered-off PS4

- state: complete; operator combined console startup
- question: can the cleanly detached, provisioned USB be physically returned
  to the powered-off console without combining attachment and boot actions?
- changed variable: USB physical attachment only; keep the PS4 powered off and
  do not start Orbis, GoldHEN, or Linux in this action
- expected evidence: operator confirms the correct Kingston USB is attached;
  no UART output is expected while the console remains powered off
- timeout: operator-paced
- rollback: unplug the USB while the PS4 remains off if the wrong port or
  device was used
- bounded UART context:
  [`20260811_202841_291676-exp-20260810-001-a49-attach-provisioned-usb-to-powered-off-ps4-7bf50dc4.md`](../../ps4-uart/sessions/20260811_202841_291676-exp-20260810-001-a49-attach-provisioned-usb-to-powered-off-ps4-7bf50dc4.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: USB connected, console restarted, and GoldHEN payload run
- result: pass for USB attachment, inconclusive for GoldHEN. UART identifies
  Kingston `0951:1666`, exposes it as `da1`, and mounts `da1s1` at `/mnt/usb0`.
  The operator also powered the console and entered GoldHEN server settings,
  crossing the declared attachment-only boundary, but the bounded slice has
  no definitive `All done` or PayLoader-start marker. No Linux payload ran
- next action: `EXP-20260810-001-A50`; verify GoldHEN and the staged FAT boot
  set through read-only FTP without probing or consuming port 9090

### EXP-20260810-001-A50 — verify GoldHEN and staged boot set after A49

- state: complete
- question: is GoldHEN FTP available at `192.168.50.215:2121`, and does the
  FAT partition still expose the accepted A39 boot set after offline ext4
  provisioning?
- changed variable: none; perform a read-only anonymous FTP listing and stream
  verification only. Do not connect to PayLoader port 9090
- expected evidence: FTP lists `/mnt/usb0`; `bzImage` retains A39 SHA-256
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`;
  manifest verification remains intact
- timeout: 60 seconds
- rollback: none for read-only verification; close before any payload send
- bounded UART context:
  [`20260811_203227_509034-exp-20260810-001-a50-verify-goldhen-and-staged-boot-set-after-a4-abd01de1.md`](../../ps4-uart/sessions/20260811_203227_509034-exp-20260810-001-a50-verify-goldhen-and-staged-boot-set-after-a4-abd01de1.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Anonymous FTP at `192.168.50.215:2121` listed the expected
  `/mnt/usb0` boot set, and streaming `bzImage` returned exact A39 SHA-256
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`.
  No connection was made to PayLoader port 9090 and no file was written
- next action: `EXP-20260810-001-A51`; boot the unchanged A39 kernel, then
  validate the provisioned ext4 userspace and SSH

### EXP-20260810-001-A51 — boot A39 and validate provisioned userspace

- state: complete
- question: does the unchanged HDMI-positive A39 kernel boot the provisioned
  ext4 root and expose the requested GUI networking, debug account, sudo,
  fastfetch, Realtek fallback, and SSH service?
- changed variable relative to A43: ext4 userspace changes from A48 only;
  A39 kernel, FAT manifest, v25 1024 MB ELF, initramfs, bootargs, and VRAM are
  unchanged
- expected evidence: PayLoader accepts the exact v25 ELF; A39 reaches the
  graphical target with HDMI; root mounts cleanly; the operator reports GUI;
  Linux receives DHCP; SSH accepts `ps4/ps4` and the pinned public key;
  package/firmware/service checks pass remotely
- timeout: 30 seconds for loader/kexec, 180 seconds for display, and 420
  seconds for userspace/network while UART makes forward progress
- rollback: close before any retry; if userspace fails, recover Orbis in a new
  session and retain A48's timestamped offline backup
- bounded UART context:
  [`20260811_203324_911610-exp-20260810-001-a51-boot-a39-and-validate-provisioned-userspace-f9fa7694.md`](../../ps4-uart/sessions/20260811_203324_911610-exp-20260810-001-a51-boot-a39-and-validate-provisioned-userspace-f9fa7694.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator outcome: reported the system connected successfully; the same boot
  exposed the XFCE session and remained reachable for remote validation
- result: pass for the provisioned userspace, HDMI/XFCE, internal MT7668,
  NetworkManager, and SSH. PayLoader accepted the exact v25 1024 MB ELF and
  Linux reported `6.18.44-ps4-baikal` build `#5`. All three split MN864729
  stages completed, `amdgpudrmfb` initialized, ext4 root mounted read-write,
  LightDM started, graphical target was reached, and user session `ps4`
  started. The internal MT7668 associated to the saved private profile and
  received DHCP address `192.168.50.125/24`
- remote validation: pinned-key SSH as `ps4` succeeded. `sshd`, NetworkManager,
  and LightDM were active; `sshd` was enabled; `nm-applet` was running;
  `fastfetch 2.67.0-1`, `network-manager-applet 1.36.0-2`, and
  `linux-firmware-realtek 20260622-1` were installed. The uncompressed
  `rtw88/rtw8822b_fw.bin` retained SHA-256
  `a72da690597bfa99d8eb6fc2ab090d18d8ad92ac2befd35db1c9e3662d8d8418`
- limitation: root discovery took about 96 seconds because reads against the
  internal Toshiba SATA disk timed out and produced buffer I/O errors while
  label discovery ran. The external Kingston USB root was then resolved as
  `/dev/sda2` and mounted normally. Total boot time was 1 minute 43.760
  seconds. The optional `hostname` command is absent, but this did not affect
  DHCP, NetworkManager, or SSH
- security state: `ps4/ps4` and password SSH remain development-only; remote
  acceptance used the pinned public key and did not expose the password
- next action: `EXP-20260810-001-A52`; perform read-only diagnosis of the
  internal SATA timeouts before changing boot or storage behavior

### EXP-20260810-001-A52 — live SATA and desktop prerequisite inventory

- state: complete
- question: what exact storage failure and userspace prerequisites are present
  in the still-running A51 system before the first Wayland package is added?
- changed variable: none; collect bounded, read-only SSH evidence only. Do not
  load a driver, restart a service, launch a renderer, or write configuration
- expected evidence: root filesystem identity, ATA error summary, installed
  graphics/session packages, current display manager and session type, and
  exact repository candidates for the first minimal compositor test
- timeout: 5 minutes
- rollback: none; this action is read-only
- bounded UART context:
  [`20260811_215757_912602-exp-20260810-001-a52-live-sata-and-desktop-prerequisite-inventor-37c142c5.md`](../../ps4-uart/sessions/20260811_215757_912602-exp-20260810-001-a52-live-sata-and-desktop-prerequisite-inventor-37c142c5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass for the read-only inventory. The running root is external USB
  ext4 label `OMARCHY-PS4` on a Kingston DataTraveler; the internal Toshiba
  SATA disk is separate and unmounted. The journal confirms `ata1.00` NCQ read
  failure, 5/10/30-second IDENTIFY timeouts, device disablement, and buffer I/O
  errors. LightDM, NetworkManager, and sshd are active. Mesa `26.1.6-1`,
  libinput `1.31.3-1`, Wayland `1.25.0-1`, PipeWire `1.6.8-1`, WirePlumber
  `0.5.15-1`, and generic/GTK portals are installed. Weston, Hyprland, UWSM,
  the Hyprland portal, and Foot are absent
- repository candidates: Arch offers Weston `15.0.1-3`, Hyprland `0.56.2-1`,
  UWSM `0.26.6-1`, xdg-desktop-portal-hyprland `1.4.1-1`, and Foot `1.27.0-2`
- UART conclusion: capture continuity completed with no logger event; UART
  contains only the two bounded SSH session lifecycles and routine MT7668 P2P
  trace noise. No new kernel error occurred
- next action: `EXP-20260810-001-A53`; install only the minimal Weston
  compositor package and its repository dependencies while preserving XFCE

### EXP-20260810-001-A53 — install minimal Wayland compositor package

- state: complete; failed safely before package transaction
- question: can the external Arch root accept the current official Weston
  package and dependencies without changing the PS4 kernel, boot chain,
  display manager, XFCE configuration, or enabled services?
- changed variable: install only Arch package `weston=15.0.1-3` and the
  dependencies selected by pacman; create a timestamped package/config backup
  first
- expected evidence: root resolves by label `OMARCHY-PS4`; pacman transaction
  succeeds; Weston reports the pinned version; LightDM and the active XFCE
  session remain running; no new kernel/DRM/storage error appears on UART
- timeout: 10 minutes while package downloads make forward progress
- rollback: remove the explicitly installed `weston` package and any newly
  orphaned dependencies listed in the transaction snapshot; restore only
  configuration files that the transaction actually changed
- bounded UART context:
  [`20260811_220033_199582-exp-20260810-001-a53-install-minimal-wayland-compositor-package-e68e2916.md`](../../ps4-uart/sessions/20260811_220033_199582-exp-20260810-001-a53-install-minimal-wayland-compositor-package-e68e2916.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail in the local safety wrapper before `pacman -S`. The empty
  `pacman -Qqm` result returned status 1 under strict mode. Weston remains
  absent, LightDM/XFCE remains active, and no package transaction occurred.
  The partial preflight snapshot is
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A53-20260723T190903Z`;
  the guest clock is stale, so the directory timestamp is not host evidence
- UART conclusion: capture continuity completed with no logger event and no
  new kernel error; it contains only bounded SSH session lifecycle messages
- rollback: not required because no package or configuration changed
- new evidence for retry: tolerate an empty foreign-package list while keeping
  every other strict-mode check. Use a new experiment instead of repeating A53
- next action: `EXP-20260810-001-A54`; run the corrected package-only installer

### EXP-20260810-001-A54 — install Weston after empty-list fix

- state: complete; blocked safely by stale guest clock
- question: can the corrected wrapper install the pinned official Weston
  package on the external USB root while preserving the running XFCE session?
- changed variable: relative to A53, only tolerate status 1 from an empty
  `pacman -Qqm`; intended package and system scope are unchanged
- expected evidence: root and package guards pass; signed pacman transaction
  installs Weston `15.0.1-3`; an exact new-package list and rollback preview
  are written; LightDM remains active; no new kernel error appears on UART
- timeout: 10 minutes while package downloads make forward progress
- rollback: inspect the generated `new-packages.txt`, then remove Weston and
  its transaction-only orphaned dependencies with the recorded preview
- bounded UART context:
  [`20260811_220207_258268-exp-20260810-001-a54-install-weston-after-empty-list-fix-aaba8da8.md`](../../ps4-uart/sessions/20260811_220207_258268-exp-20260810-001-a54-install-weston-after-empty-list-fix-aaba8da8.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: blocked before package commit. The corrected guard resolved the
  external USB root and selected only `seatd 0.9.3-1` plus `weston 15.0.1-3`,
  but archive.archlinux.org rejected both downloads because the guest clock is
  2026-07-23 and the TLS certificates are not yet valid from that date.
  Pacman reported that no package was upgraded; Weston remains absent
- backup: pre-transaction snapshot is
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A54-20260723T191035Z`;
  the directory uses the known-stale guest clock
- UART conclusion: capture continuity completed with no logger event and no
  new kernel error; it contains only bounded SSH session lifecycle messages
- rollback: not required because pacman committed no package
- next action: `EXP-20260810-001-A55`; enable systemd network time and verify
  clock synchronization without changing packages or desktop configuration

### EXP-20260810-001-A55 — synchronize the live guest clock

- state: complete
- question: can systemd-timesyncd correct the stale live guest clock through
  the working network so signed Arch packages can be fetched normally?
- changed variable: enable network time synchronization with
  `timedatectl set-ntp true`; do not install packages or change desktop state
- expected evidence: systemd-timesyncd becomes active, the UTC date advances
  to 2026-08-11, `NTPSynchronized=yes`, and a TLS HEAD request to the Arch
  archive succeeds
- timeout: 90 seconds while synchronization makes forward progress
- rollback: `timedatectl set-ntp false`; do not manually set the clock in the
  same experiment if network synchronization fails
- bounded UART context:
  [`20260811_220310_783746-exp-20260810-001-a55-synchronize-the-live-guest-clock-89ece545.md`](../../ps4-uart/sessions/20260811_220310_783746-exp-20260810-001-a55-synchronize-the-live-guest-clock-89ece545.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. The guest began at `2026-07-23T19:11:35Z` with NTP disabled.
  `timedatectl set-ntp true` started systemd-timesyncd, and its second
  three-second poll reported `NTPSynchronized=yes` at
  `2026-08-11T16:03:32Z`. An HTTPS HEAD request to archive.archlinux.org then
  returned HTTP/2 200
- UART conclusion: capture continuity completed with no logger event. UART
  records the time services, network-online target, and the distro's existing
  archlinux-keyring refresh unit starting; no new kernel error occurred
- rollback: not applied; correct network time is required for package signature
  and TLS validation. Disabling NTP remains the exact rollback
- next action: `EXP-20260810-001-A56`; retry the unchanged, pinned Weston
  transaction now that TLS validation is sound

### EXP-20260810-001-A56 — install Weston with synchronized time

- state: complete
- question: can the guarded package transaction install Weston now that the
  only observed blocker, stale time, is resolved?
- changed variable: install only Arch package `weston=15.0.1-3` and pacman's
  selected dependency `seatd=0.9.3-1`; no desktop launch or configuration
- expected evidence: signed transaction commits; exact new-package and
  rollback files are written; `weston --version` passes; LightDM/XFCE remains
  active; UART reports no new kernel/DRM/storage error
- timeout: 10 minutes while package downloads make forward progress
- rollback: inspect the generated `new-packages.txt`, then run the recorded
  package removal preview only if validation fails
- bounded UART context:
  [`20260811_220415_063018-exp-20260810-001-a56-install-weston-with-synchronized-time-1be46e4b.md`](../../ps4-uart/sessions/20260811_220415_063018-exp-20260810-001-a56-install-weston-with-synchronized-time-1be46e4b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass for package installation only. Pacman verified signatures and
  integrity, then installed exactly `seatd 0.9.3-1` and `weston 15.0.1-3`.
  `weston --version` reports `15.0.1`; LightDM remains active and enabled as
  the same unit; the existing XFCE seat session remains active
- backup and rollback: snapshot is
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A56-20260811T160427Z`.
  Its exact new-package list contains only `seatd` and `weston`; its rollback
  preview is `pacman -Rns -- seatd weston`
- UART conclusion: capture continuity completed with no logger event. UART
  records only systemd's package-hook reload, bounded SSH sessions, completion
  of the existing keyring refresh, and routine MT7668 trace noise. The kernel
  journal has no warning at or after the transaction start
- rollback: not applied because validation passed. XFCE remains the active
  recovery desktop, and Weston has not been launched
- next action: `EXP-20260810-001-A57`; launch Weston nested inside the current
  XFCE/Xorg session and render one native Wayland client without logging out

### EXP-20260810-001-A57 — nested Weston and native Wayland client

- state: complete; pass with known IRQ diagnostic noise
- question: can the running PS4 graphics stack display a Weston compositor
  window and a native Wayland client inside the known-good XFCE/Xorg session?
- changed variable: launch only a user-owned nested Weston process and one
  packaged native Wayland demo client; do not log out, claim DRM master,
  change LightDM, or install another package
- expected evidence: Weston selects its X11 backend and GL renderer, creates a
  visible 1280x720 window, the native client connects to its private socket,
  and both exit cleanly; operator confirms the visible result; no new GPU or
  kernel warning appears
- timeout: 30 seconds to display, then a maximum 60-second bounded run
- rollback: terminate the user-owned Weston/client process group and remove
  only its runtime socket and experiment log
- bounded UART context:
  [`20260811_220544_976195-exp-20260810-001-a57-nested-weston-and-native-wayland-client-5ece0d24.md`](../../ps4-uart/sessions/20260811_220544_976195-exp-20260810-001-a57-nested-weston-and-native-wayland-client-5ece0d24.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: a colorful triangle was visible and rotating inside the
  Weston window on the PS4 monitor
- renderer evidence: Weston `15.0.1` loaded its X11 backend and GL renderer,
  selected `/dev/dri/renderD128`, negotiated EGL 1.5 and OpenGL ES 3.2, and
  identified `AMD DG1401SNF87ID (radeonsi, kaveri, ACO, DRM 3.64,
  6.18.44-ps4-baikal)`. `weston-simple-egl` stayed alive and rendered visibly
- result: pass for the nested minimal-compositor/native-client gate. This does
  not yet prove direct DRM master, logind seat takeover, or a standalone
  Wayland login session
- UART conclusion: capture continuity completed with no logger event. Mapping
  the nested compositor caused the known PS4 bridge mode-fixup path and a
  burst of the already-tracked `No irq handler for 0.227` diagnostics. The
  three split MN864729 stages completed, display remained visible, and no GPU
  reset, fence timeout, page fault, or process crash appeared
- rollback: explicit TERM cleanup stopped Weston, its shell, terminal, and EGL
  client; the private `wayland-a57` socket was removed. The experiment logs
  remain under `/home/ps4/.local/state/omarchy-ps4/A57` as evidence
- next action: `EXP-20260810-001-A58`; install only the pinned Arch Hyprland
  package and dependencies, without configuration, UWSM, portal, or launch

### EXP-20260810-001-A58 — install bare Hyprland package

- state: complete
- question: can the external Arch root accept the current official Hyprland
  package and dependencies without changing the active XFCE recovery path?
- changed variable: install only Arch package `hyprland=0.56.2-1` and the
  dependencies selected by pacman; do not install UWSM, the Hyprland portal,
  Foot, Quickshell, or Omarchy configuration, and do not launch Hyprland
- expected evidence: guarded root and version checks pass; signed transaction
  commits; exact new-package and rollback files are written; `Hyprland
  --version` reports the pinned package; LightDM/XFCE remains active; UART has
  no new kernel/DRM/storage error
- timeout: 15 minutes while package downloads make forward progress
- rollback: inspect the generated `new-packages.txt`, then run its recorded
  package removal preview only if validation fails
- bounded UART context:
  [`20260811_221155_224009-exp-20260810-001-a58-install-bare-hyprland-package-fe826e52.md`](../../ps4-uart/sessions/20260811_221155_224009-exp-20260810-001-a58-install-bare-hyprland-package-fe826e52.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass for package installation only. Pacman verified and installed
  Hyprland `0.56.2-1` plus 23 repository dependencies. `Hyprland --version`
  reports v0.56.2 and matching Aquamarine `0.14.0`, Hyprutils `0.14.0`,
  Hyprgraphics `0.5.1`, Hyprcursor `0.1.13`, and Hyprlang `0.6.8` ABIs.
  LightDM remains active as the unchanged display manager, and the existing
  XFCE seat remains active
- backup and rollback: snapshot is
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A58-20260811T161208Z`.
  Its `new-packages.txt` records exactly 24 packages, and `ROLLBACK.txt`
  contains the corresponding `pacman -Rns` preview
- UART conclusion: capture continuity completed with no logger event. UART
  contains only bounded SSH session lifecycle messages; the kernel journal
  has no warning at or after the transaction start
- rollback: not applied because validation passed. UWSM, the Hyprland portal,
  Foot, Quickshell, and Omarchy configuration remain absent
- next action: `EXP-20260810-001-A59`; launch bare Hyprland as a nested
  Aquamarine Wayland backend inside a temporary Weston parent and render one
  native client, leaving the XFCE seat active

### EXP-20260810-001-A59 — nested bare Hyprland runtime

- state: complete; failed safely before Hyprland initialization
- question: can stock Hyprland `0.56.2-1`, with a minimal experiment-local
  configuration and no Omarchy layer, initialize Aquamarine/Mesa and visibly
  render a native Wayland client on this PS4?
- changed variable: launch a user-owned nested Hyprland process inside a
  temporary nested Weston parent; no package, home configuration, LightDM,
  service, login session, or boot change
- expected evidence: Hyprland selects Aquamarine's Wayland backend, exposes a
  private Wayland socket, `hyprctl` reports a monitor and client, a native EGL
  client renders visibly, operator confirms the output, and cleanup removes
  all test processes/sockets without a GPU reset or crash
- timeout: 45 seconds to display, then operator-paced confirmation with
  explicit cleanup
- rollback: terminate the exact Hyprland, client, and Weston parent processes;
  remove their private runtime sockets; preserve experiment logs
- bounded UART context:
  [`20260811_221432_967218-exp-20260810-001-a59-nested-bare-hyprland-runtime-6a5cb6f5.md`](../../ps4-uart/sessions/20260811_221432_967218-exp-20260810-001-a59-nested-bare-hyprland-runtime-6a5cb6f5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail before Hyprland initialized a backend or rendered. Config
  verification passed, and the Weston parent opened, but Hyprland 0.56.2
  rejected `--socket wayland-a59-hypr`: that option is a socket-handover input
  and is valid only together with `--wayland-fd`, not a server socket-name
  selector
- UART conclusion: capture continuity completed with no logger event and no
  new kernel, DRM, or GPU message; only bounded SSH session lifecycle appeared
- rollback: explicit cleanup terminated the Weston parent, confirmed no
  Weston or Hyprland process remained, and removed the private sockets.
  Experiment logs remain under `/home/ps4/.local/state/omarchy-ps4/A59`
- new evidence for retry: omit both handover options, record runtime Wayland
  sockets before launch, and identify Hyprland's automatically created socket
  from the set difference. Use a new experiment instead of repeating A59
- next action: `EXP-20260810-001-A60`; retry nested bare Hyprland with automatic
  server socket allocation

### EXP-20260810-001-A60 — nested Hyprland with automatic socket

- state: complete; nested path incompatible before rendering
- question: can stock Hyprland initialize its Aquamarine Wayland backend and
  render visibly when allowed to allocate its normal server socket?
- changed variable: relative to A59, omit the invalid `--socket` handover
  option and discover the new server socket from a before/after runtime
  inventory; package, config, parent compositor, and desktop state are unchanged
- expected evidence: Hyprland remains alive, one new numeric Wayland socket
  appears, `hyprctl instances` identifies the process, a native EGL client
  connects and renders visibly, and cleanup removes all exact processes/sockets
- timeout: 45 seconds to display, then operator-paced confirmation with
  explicit cleanup
- rollback: terminate the exact Hyprland, client, and Weston parent processes;
  remove only sockets created by the experiment; preserve logs
- bounded UART context:
  [`20260811_221602_658904-exp-20260810-001-a60-nested-hyprland-with-automatic-socket-4ae09a50.md`](../../ps4-uart/sessions/20260811_221602_658904-exp-20260810-001-a60-nested-hyprland-with-automatic-socket-4ae09a50.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail in the nested-only backend path before rendering. As expected
  while XFCE owns the seat, Aquamarine could not open seatd or logind and its
  DRM backend was unavailable. It then selected the Wayland backend, but
  Weston 15 advertised `wl_compositor` version 6 while Aquamarine 0.14 accepts
  at most version 5; backend allocation failed and Hyprland aborted
- crash evidence: Hyprland's report at
  `/home/ps4/.cache/hyprland/hyprlandCrashReport3296.txt` identifies v0.56.2,
  matching library ABIs, the PS4 AMD GPU, `CBackend::create() failed`, and the
  same seat/Wayland fallback sequence. This does not exercise or reject the
  direct PS4 DRM path
- UART conclusion: capture continuity completed with no logger event and no
  new kernel, DRM, or GPU warning; only bounded SSH session lifecycle appeared
- rollback: explicit cleanup terminated the Weston parent, confirmed no
  Weston or Hyprland process remained, and removed the private parent socket.
  Logs remain under `/home/ps4/.local/state/omarchy-ps4/A60`
- decision: do not downgrade Weston or patch production Hyprland for a
  disposable nested harness. Proceed to the actual logind/DRM session gate
- next action: `EXP-20260810-001-A61`; install a verified, minimal, backed-up
  Hyprland test config for user `ps4`, without starting a session

### EXP-20260810-001-A61 — install minimal Hyprland test config

- state: complete
- question: can a standalone, non-Omarchy Hyprland configuration be installed
  for the test user with exact backup state and no system/session change?
- changed variable: write only `/home/ps4/.config/hypr/hyprland.conf` after
  recording whether it existed and verifying the source; autostart only the
  already-installed native `weston-terminal` test client
- expected evidence: both source and installed config report `config ok`;
  backup state and installed file are stored under the user's experiment state;
  LightDM/XFCE stays active and UART has no new kernel error
- timeout: 2 minutes
- rollback: if the target was present, restore its exact backup; if absent,
  remove only the installed test file and empty test-created directory
- bounded UART context:
  [`20260811_221818_749925-exp-20260810-001-a61-install-minimal-hyprland-test-config-f18f00a4.md`](../../ps4-uart/sessions/20260811_221818_749925-exp-20260810-001-a61-install-minimal-hyprland-test-config-f18f00a4.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Both the repository source and installed
  `/home/ps4/.config/hypr/hyprland.conf` returned `config ok`. No prior target
  existed. The minimal config disables blur, shadows, and animations, enables
  logs, autostarts only `weston-terminal`, and defines explicit exit/close
  bindings; it has no Omarchy includes
- evidence and rollback: user-owned snapshot is
  `/home/ps4/.local/state/omarchy-ps4/experiments/EXP-20260810-001-A61-20260811T161827Z`.
  Its `target.before` records `absent`, so rollback is removal of only the test
  file and an empty test-created `~/.config/hypr` directory
- session evidence: the official package supplies
  `/usr/share/wayland-sessions/hyprland.desktop` with
  `Exec=/usr/bin/start-hyprland`; LightDM and the existing X11/XFCE session
  remained active
- UART conclusion: capture continuity completed with no logger event and only
  bounded SSH lifecycle messages; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A62`; inspect LightDM/autologin and session
  state read-only before releasing the current XFCE seat

### EXP-20260810-001-A62 — inspect LightDM transition path

- state: complete
- question: will terminating the current XFCE session expose a selectable
  LightDM greeter, or will configured autologin immediately start XFCE again?
- changed variable: none; inspect effective LightDM configuration, session
  files, PAM/autologin membership, and live logind state read-only
- expected evidence: identify the exact autologin user/session and the safest
  no-reboot path into the official Hyprland session entry
- timeout: 2 minutes
- rollback: none; this action is read-only
- bounded UART context:
  [`20260811_221923_754670-exp-20260810-001-a62-inspect-lightdm-transition-path-8aa72c44.md`](../../ps4-uart/sessions/20260811_221923_754670-exp-20260810-001-a62-inspect-lightdm-transition-path-8aa72c44.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Effective LightDM configuration has `autologin-user=ps4`,
  zero timeout, and both `autologin-session=xfce` and `user-session=xfce`.
  User `ps4` belongs to `autologin`, and the active seat session is X11 via
  `lightdm-autologin`. A normal logout would therefore immediately return to
  XFCE rather than expose a durable greeter
- session entries: package `hyprland 0.56.2-1` owns both the direct
  `hyprland.desktop` entry (`start-hyprland`) and a UWSM entry hidden while
  `uwsm` is absent. Weston and XFCE Wayland entries also exist but are outside
  this gate
- UART conclusion: capture continuity completed with no logger event and only
  bounded SSH lifecycle messages; no new kernel error occurred
- next action: `EXP-20260810-001-A63`; change only the pending LightDM default
  and autologin session from XFCE to direct Hyprland, without restarting it

### EXP-20260810-001-A63 — select Hyprland for the next LightDM login

- state: complete
- question: can the pending LightDM session be changed to the official direct
  Hyprland entry with exact backup while leaving the current XFCE seat intact?
- changed variable: replace only `autologin-session=xfce` and
  `user-session=xfce` with `hyprland` in the existing PS4 LightDM drop-in; do
  not reload or restart LightDM
- expected evidence: effective configuration reports both values as
  `hyprland`; the original drop-in and effective config are backed up; the
  current X11/XFCE session and SSH remain active; UART has no new kernel error
- timeout: 2 minutes
- rollback: restore the exact backed-up drop-in; because LightDM is not
  restarted in this action, rollback requires no seat transition
- bounded UART context:
  [`20260811_222059_556257-exp-20260810-001-a63-select-hyprland-for-next-lightdm-login-3259a833.md`](../../ps4-uart/sessions/20260811_222059_556257-exp-20260810-001-a63-select-hyprland-for-next-lightdm-login-3259a833.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Effective LightDM configuration now reports both
  `autologin-session=hyprland` and `user-session=hyprland`, targeting the
  package-owned direct entry. LightDM was not reloaded or restarted; session 1
  remained active X11/XFCE on display `:0`, and SSH remained available
- backup and rollback: exact prior drop-in and effective configuration are in
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A63-20260811T162115Z`;
  `ROLLBACK.txt` restores the original XFCE drop-in
- UART conclusion: capture continuity completed with no logger event and only
  bounded SSH lifecycle messages; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A64`; restart only LightDM so autologin releases
  the X11 seat and starts the direct Hyprland session

### EXP-20260810-001-A64 — direct Hyprland session through LightDM

- state: complete; pass for direct display, input and clean exit pending
- question: can stock `start-hyprland` acquire the real PS4 logind/DRM seat,
  initialize the HDMI output and radeonsi renderer, and run a native terminal?
- changed variable: restart only `lightdm.service`, consuming A63's pending
  session selection; do not restart the console, network, SSH, or another service
- expected evidence: old X11 session closes; a Wayland/Hyprland seat session
  becomes active; HDMI remains visible; `weston-terminal` appears; `hyprctl`
  reports the PS4 output and client; operator reports the screen; UART shows no
  GPU reset, page fault, fence timeout, or fatal bridge failure
- timeout: 60 seconds for session/display, then operator-paced confirmation
- rollback: if direct Hyprland fails, close A64 first; in a new experiment
  restore A63's exact XFCE LightDM drop-in and restart LightDM
- bounded UART context:
  [`20260811_222158_148245-exp-20260810-001-a64-direct-hyprland-session-through-lightdm-fbd5fa29.md`](../../ps4-uart/sessions/20260811_222158_148245-exp-20260810-001-a64-direct-hyprland-session-through-lightdm-fbd5fa29.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- software result: pass. LightDM cleanly stopped the 1h46m XFCE session and
  autologged `ps4` into a new seat session. `start-hyprland` launched Hyprland
  PID 3640 with `backend: drm` and socket `wayland-1`. Aquamarine selected
  `/dev/dri/card0` plus `/dev/dri/renderD128`, created a GBM allocator and
  high-priority robust EGL context, and identified radeonsi on the PS4 AMD GPU
- output/client evidence: `hyprctl` reports active `HDMI-A-1` at
  1920x1080/60, scale 1, XRGB8888, DPMS on, and hardware cursors. The native
  non-XWayland `weston-terminal` is mapped, visible, focused, and accepts
  input. Hyprland enumerates the attached USB keyboard and mouse devices
- operator report: terminal is visible on the PS4 monitor. This physically
  confirms direct Hyprland HDMI output; keyboard/mouse interaction was not yet
  reported and remains a separate gate
- UART conclusion: capture continuity completed with no logger event. The
  XFCE teardown and Hyprland modeset ran the known MN864729 split sequence and
  produced repeated already-tracked `No irq handler for 0.227` messages. No
  GPU reset, page fault, ring/fence timeout, compositor crash, or fatal bridge
  error appeared
- rollback: not applied; the direct Hyprland session remains running and SSH
  remains reachable. Exact XFCE LightDM rollback remains in A63's snapshot
- next action: `EXP-20260810-001-A65`; verify keyboard and mouse interaction in
  the visible native terminal before changing packages or session management

### EXP-20260810-001-A65 — direct Hyprland keyboard and mouse input

- state: complete
- question: do the attached physical keyboard and mouse deliver input to the
  visible native Wayland terminal under direct Hyprland?
- changed variable: operator input only; click the terminal, type a fixed
  harmless command, and press Enter. Do not change configuration or packages
- expected evidence: pointer moves and focuses the terminal; typed text is
  visible; `echo HYPRLAND-INPUT-OK` prints the matching marker; Hyprland and
  HDMI remain stable with no new GPU/input error on UART
- timeout: operator-paced, then 60 seconds after the action
- rollback: none for the harmless command; if input is unresponsive, leave the
  session unchanged and record which device failed
- bounded UART context:
  [`20260811_222834_326929-exp-20260810-001-a65-direct-hyprland-keyboard-and-mouse-input-617eb90c.md`](../../ps4-uart/sessions/20260811_222834_326929-exp-20260810-001-a65-direct-hyprland-keyboard-and-mouse-input-617eb90c.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: yes; the pointer moved and focused the terminal, keyboard
  input was accepted, and the fixed command produced the expected visible
  marker
- result: pass. Direct Hyprland physical mouse and keyboard input works in the
  native Wayland terminal on this Baikal B1 console
- UART conclusion: capture continuity completed with no logger event. The
  slice contains only routine MT7668 P2P trace noise; no input, DRM, GPU, or
  kernel error appeared
- rollback: not required; the command was harmless and Hyprland remains active
- next action: `EXP-20260810-001-A66`; restore XFCE as LightDM's pending default
  without stopping the proven Hyprland session

### EXP-20260810-001-A66 — queue XFCE as the recovery session

- state: complete
- question: can LightDM's pending default be returned to XFCE using the same
  guarded, backed-up mechanism while direct Hyprland remains active?
- changed variable: replace only `autologin-session=hyprland` and
  `user-session=hyprland` with `xfce`; do not restart LightDM or exit Hyprland
- expected evidence: effective configuration reports both values as `xfce`;
  current Wayland/Hyprland seat, terminal, SSH and HDMI remain active; UART has
  no new kernel error
- timeout: 2 minutes
- rollback: restore A66's exact backed-up Hyprland drop-in if validation fails
- bounded UART context:
  [`20260811_224406_312595-exp-20260810-001-a66-queue-xfce-as-recovery-session-fe929055.md`](../../ps4-uart/sessions/20260811_224406_312595-exp-20260810-001-a66-queue-xfce-as-recovery-session-fe929055.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Effective LightDM defaults are back to `xfce`; the direct
  Hyprland PID, native terminal, Wayland seat, HDMI, network and SSH remained
  active because LightDM was not reloaded or restarted
- backup and rollback: exact prior Hyprland drop-in is in
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A66-20260811T164418Z`
- UART conclusion: capture continuity completed with no logger event and only
  the bounded SSH session lifecycle; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A67`; use Hyprland's configured exit binding
  once and confirm LightDM recovers into XFCE

### EXP-20260810-001-A67 — clean Hyprland exit and XFCE recovery

- state: complete; degraded recovery path
- question: can the direct Hyprland session exit through its normal binding
  and allow unchanged LightDM to recover automatically into XFCE without reboot?
- changed variable: operator presses `SUPER+M` once, invoking Hyprland's `exit`
  dispatcher; no service command, package, or configuration change
- expected evidence: Hyprland and native terminal stop cleanly; LightDM starts
  a new X11/XFCE seat; HDMI returns visibly; SSH/network persist; UART shows no
  GPU reset, filesystem error, or fatal bridge failure
- timeout: 60 seconds for XFCE recovery, then operator-paced confirmation
- rollback: if the binding does not respond, leave the session unchanged and
  inspect before trying another exit mechanism; do not repeat the keypress
- bounded UART context:
  [`20260811_224455_714497-exp-20260810-001-a67-clean-hyprland-exit-and-xfce-recovery-1c439e93.md`](../../ps4-uart/sessions/20260811_224455_714497-exp-20260810-001-a67-clean-hyprland-exit-and-xfce-recovery-1c439e93.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- operator report: XFCE is visibly present after the single `SUPER+M` action
- result: degraded. The original direct Hyprland session exited and LightDM
  created a new seat without reboot; HDMI remained visible. However, a
  post-session read-only check found the new seat typed as Wayland with a new
  Hyprland process even though effective LightDM defaults are `xfce`. Visible
  XFCE is therefore not yet proof that the original X11 recovery path returned
- UART conclusion: capture continuity completed with no logger event. Several
  display handoffs ran the known bridge sequence and IRQ 0.227 diagnostics;
  no GPU reset, page fault, ring/fence timeout, filesystem error, or fatal
  bridge failure appeared
- rollback: LightDM defaults remain `xfce`, network and SSH remain active, and
  a visible desktop is available. Do not repeat the exit binding until the new
  session composition is understood
- next action: `EXP-20260810-001-A68`; inspect the new LightDM session,
  process tree, environment, and logs read-only to explain the mixed result

### EXP-20260810-001-A68 — diagnose mixed XFCE/Hyprland recovery

- state: complete
- question: why is XFCE visible while logind reports a Wayland seat and a new
  Hyprland process after LightDM defaults were restored to `xfce`?
- changed variable: none; collect bounded read-only process, cgroup,
  environment, AccountsService, LightDM and session-entry evidence
- expected evidence: identify which desktop entry LightDM actually launched,
  whether XFCE processes are children/clients of Hyprland, and which persisted
  session selection overrode the drop-in
- timeout: 3 minutes
- rollback: none; this action is read-only
- bounded UART context:
  [`20260811_230101_225139-exp-20260810-001-a68-diagnose-mixed-xfce-hyprland-recovery-0cfe882b.md`](../../ps4-uart/sessions/20260811_230101_225139-exp-20260810-001-a68-diagnose-mixed-xfce-hyprland-recovery-0cfe882b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass for diagnosis. LightDM logs show the direct session exited
  normally, an X11 greeter started, and the greeter explicitly requested
  `hyprland` after successful manual authentication. It wrote
  `/home/ps4/.dmrc` with `Session=hyprland`, then launched
  `/usr/bin/start-hyprland`. The current seat is therefore direct Hyprland,
  not X11/XFCE; its process tree is LightDM -> start-hyprland -> Hyprland ->
  weston-terminal
- root cause: changing only system `autologin-session` and `user-session` does
  not override a later manual greeter choice stored in `.dmrc`. The recovery
  automation must keep both system defaults and the per-user session selection
  consistent before restarting LightDM
- UART conclusion: capture continuity completed with no logger event and only
  the bounded SSH lifecycle; no new kernel error occurred
- rollback: none; read-only diagnosis left the visible direct session running
- next action: `EXP-20260810-001-A69`; atomically queue XFCE in both LightDM's
  PS4 drop-in and the user's `.dmrc`, without restarting the current session

### EXP-20260810-001-A69 — synchronize pending XFCE session selection

- state: complete
- question: can the guarded selector set both system and per-user LightDM
  state to XFCE while leaving the current direct Hyprland session active?
- changed variable: session selection only; keep system defaults at `xfce` and
  replace `.dmrc` `Session=hyprland` with `Session=xfce`, backing up both files
- expected evidence: effective LightDM config and `.dmrc` agree on XFCE;
  current Hyprland/HDMI/SSH remains active; UART has no new kernel error
- timeout: 2 minutes
- rollback: restore the exact system drop-in and `.dmrc` from the generated
  snapshot; do not restart LightDM in this action
- bounded UART context:
  [`20260811_230247_186627-exp-20260810-001-a69-synchronize-pending-xfce-session-selection-fcb6d97f.md`](../../ps4-uart/sessions/20260811_230247_186627-exp-20260810-001-a69-synchronize-pending-xfce-session-selection-fcb6d97f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Effective LightDM defaults and `/home/ps4/.dmrc` now all select
  `xfce`; the current direct Hyprland seat remained active and unchanged
- backup and rollback: exact system and prior per-user state are in
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A69-20260811T170312Z`
- UART conclusion: capture continuity completed with no logger event and only
  bounded SSH lifecycle messages; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A70`; remotely schedule one LightDM restart,
  reconnect automatically, and verify an actual X11/XFCE seat

### EXP-20260810-001-A70 — automated X11/XFCE recovery

- state: complete
- question: do synchronized system/per-user selections make one remotely
  scheduled LightDM restart recover the original X11/XFCE session automatically?
- changed variable: restart only `lightdm.service`; no operator keypress,
  greeter interaction, package, configuration, kernel, or console restart
- expected evidence: the direct Hyprland session stops; LightDM autologs `ps4`
  into an active seat with `Type=x11`; `xfce4-session` runs; Hyprland is absent;
  NetworkManager/sshd remain active; UART has no GPU reset or fatal error
- timeout: 60 seconds for automatic recovery and SSH reconnection
- rollback: if X11/XFCE does not become healthy, close A70 before restoring
  A69's snapshot or changing the session selection again
- bounded UART context:
  [`20260811_230358_270850-exp-20260810-001-a70-automated-x11-xfce-recovery-abb98a26.md`](../../ps4-uart/sessions/20260811_230358_270850-exp-20260810-001-a70-automated-x11-xfce-recovery-abb98a26.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. A transient systemd timer restarted only LightDM, after which
  SSH reconnected automatically. LightDM autologged `ps4` into session 76 with
  `Desktop=xfce`, `Type=x11`, display `:0`, and active `xfce4-session`.
  Hyprland is absent. LightDM, NetworkManager and sshd all remain active
- selection evidence: system defaults and `.dmrc` all remain `xfce`; the
  recovered service is `lightdm-autologin`, confirming the intended unattended
  path rather than another manual greeter selection
- UART conclusion: capture continuity completed with no logger event. The
  normal display handoff ran the known MN864729 sequence and IRQ 0.227
  diagnostics; no GPU reset, page fault, ring/fence timeout, filesystem error,
  or fatal bridge failure appeared
- rollback: not required because automatic X11/XFCE recovery passed
- next action: `EXP-20260810-001-A71`; install only the pinned UWSM package and
  dependencies while leaving the recovered XFCE session active

### EXP-20260810-001-A71 — install UWSM package

- state: complete
- question: can the external Arch root accept official UWSM `0.26.6-1` and its
  dependencies without changing the active XFCE session or starting Hyprland?
- changed variable: install only Arch package `uwsm=0.26.6-1` and pacman's
  selected dependencies; no session selection, service, portal, or config change
- expected evidence: guarded signed transaction commits; exact new-package and
  rollback files are written; `uwsm --version` succeeds; LightDM/X11/XFCE
  stays active; UART has no new kernel error
- timeout: 10 minutes while package downloads make forward progress
- rollback: inspect the generated `new-packages.txt`, then run its recorded
  removal preview only if validation fails
- bounded UART context:
  [`20260811_230525_294864-exp-20260810-001-a71-install-uwsm-package-efb9a181.md`](../../ps4-uart/sessions/20260811_230525_294864-exp-20260810-001-a71-install-uwsm-package-efb9a181.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass for package installation. Pacman verified and installed
  `uwsm 0.26.6-1`, `python 3.14.6-1`, `python-dbus 1.4.0-2`,
  `python-pyxdg 0.28-7`, and `mpdecimal 4.0.1-3`. `uwsm --version` reports
  `0.26.6`; the package-owned `hyprland-uwsm.desktop` entry now passes
  `TryExec=uwsm`
- backup and rollback: snapshot is
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A71-20260811T170541Z`;
  its exact new-package and rollback files cover the five-package transaction
- session evidence: LightDM/X11/XFCE remained active; Hyprland was absent; no
  kernel fault appeared after the transaction
- UART conclusion: capture continuity completed with no logger event. UART
  records the UWSM user-manager reload, bounded SSH sessions and routine Wi-Fi
  messages only; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A72`; synchronize LightDM system/per-user
  selection to the package-owned `hyprland-uwsm` entry without restarting

### EXP-20260810-001-A72 — queue UWSM-managed Hyprland

- state: complete
- question: can the guarded selector queue the package-owned UWSM Hyprland
  session while leaving the recovered X11/XFCE seat active?
- changed variable: session selection only; set system LightDM defaults and
  `.dmrc` to `hyprland-uwsm`, backing up both; do not restart LightDM
- expected evidence: effective and per-user selection agree; XFCE, HDMI,
  network and SSH remain active; UART has no new kernel error
- timeout: 2 minutes
- rollback: restore the exact generated system and `.dmrc` snapshot; no seat
  transition is needed because LightDM is not restarted
- bounded UART context:
  [`20260811_230659_485764-exp-20260810-001-a72-queue-uwsm-managed-hyprland-c0ccfe4f.md`](../../ps4-uart/sessions/20260811_230659_485764-exp-20260810-001-a72-queue-uwsm-managed-hyprland-c0ccfe4f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. System LightDM defaults and `.dmrc` all select
  `hyprland-uwsm`, targeting the package-owned entry. The active seat remained
  X11/XFCE and no process or service was restarted
- backup and rollback: exact system/per-user state is in
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A72-20260811T170715Z`
- UART conclusion: capture continuity completed with no logger event and only
  bounded SSH lifecycle messages; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A73`; remotely restart only LightDM and verify
  UWSM owns the direct Hyprland lifecycle

### EXP-20260810-001-A73 — automated UWSM Hyprland runtime

- state: complete
- question: can the package-owned UWSM LightDM entry start direct Hyprland,
  manage its systemd user lifecycle, and render the native test terminal?
- changed variable: restart only `lightdm.service`, consuming A72's synchronized
  session selection; no operator input, package, configuration, or console reboot
- expected evidence: active Wayland/Hyprland seat; UWSM compositor and graphical
  session units active; Hyprland direct DRM at HDMI 1080p60; native terminal
  mapped; SSH/network active; no GPU reset, crash, or fatal bridge error
- timeout: 60 seconds for automated session startup and SSH reconnection
- rollback: if UWSM does not become healthy, close A73 before synchronizing
  XFCE and restarting LightDM in a new recovery experiment
- bounded UART context:
  [`20260811_230751_230226-exp-20260810-001-a73-automated-uwsm-hyprland-runtime-cf59e886.md`](../../ps4-uart/sessions/20260811_230751_230226-exp-20260810-001-a73-automated-uwsm-hyprland-runtime-cf59e886.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. The transient restart returned an active `wayland` seat with
  `Desktop=hyprland-uwsm`. UWSM owns active compositor, session envelope,
  graphical-session, pre-session, and XDG-autostart user units; Hyprland runs
  as `wayland-wm@hyprland.desktop.service`
- display/client evidence: `HDMI-A-1` is enabled at 1920x1080/60 with DPMS on,
  XRGB8888 and hardware cursors. A visible, input-capable native Wayland
  terminal is mapped; Xwayland is false. SSH remained available
- UART conclusion: capture continuity completed with no logger event. The
  display handoff emitted the known MN864729 split-stage sequence and IRQ
  0.227 diagnostics; no GPU reset, page fault, ring/fence timeout, filesystem
  error, crash, or fatal bridge failure appeared
- rollback: not applied because UWSM startup and runtime validation passed
- next action: `EXP-20260810-001-A74`; synchronize the pending LightDM session
  to XFCE without changing the active UWSM/Hyprland runtime

### EXP-20260810-001-A74 — queue XFCE after UWSM validation

- state: complete
- question: can the guarded selector queue XFCE in both LightDM and `.dmrc`
  while leaving the active UWSM-managed Hyprland session unchanged?
- changed variable: session selection only; no package, live unit, compositor,
  kernel, display, or console restart
- expected evidence: both persistent selectors read `xfce`; UWSM/Hyprland,
  HDMI, SSH and network remain active; UART has no new kernel error
- timeout: 2 minutes
- rollback: restore the selector's generated snapshot; do not restart LightDM
- bounded UART context:
  [`20260811_231046_730257-exp-20260810-001-a74-queue-xfce-after-uwsm-validation-efcce40d.md`](../../ps4-uart/sessions/20260811_231046_730257-exp-20260810-001-a74-queue-xfce-after-uwsm-validation-efcce40d.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. Effective `autologin-session`, `user-session`, and the user's
  `.dmrc` now all select `xfce`; the active seat remained
  `Desktop=hyprland-uwsm`, `Type=wayland`, with both UWSM's compositor and
  graphical-session units active. LightDM, NetworkManager and sshd stayed active
- backup and rollback: exact prior selector state is in
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A74-20260811T171049Z`
- UART conclusion: capture continuity completed with no logger event and only
  bounded SSH lifecycle messages; no new kernel error occurred
- rollback: not applied because validation passed
- next action: `EXP-20260810-001-A75`; invoke UWSM's clean stop and verify the
  session exits before automatic XFCE recovery

### EXP-20260810-001-A75 — clean UWSM exit and XFCE recovery

- state: complete — degraded recovery behavior
- question: does `uwsm stop` cleanly terminate the managed Hyprland session and
  allow LightDM to recover the synchronized XFCE session without operator input?
- changed variable: request one UWSM-managed session stop; no package,
  configuration, kernel, console, or full-system restart
- expected evidence: UWSM and Hyprland units become inactive; an active X11/XFCE
  seat appears; LightDM, network and SSH remain healthy; UART has no GPU reset,
  crash, filesystem failure, or fatal bridge error
- timeout: 90 seconds for session teardown, LightDM transition, and SSH recovery
- rollback: if LightDM remains at the greeter, close A75 before a separate
  bounded recovery restart; persistent selectors already point to XFCE
- bounded UART context:
  [`20260811_231126_933431-exp-20260810-001-a75-clean-uwsm-exit-and-xfce-recovery-e5490b04.md`](../../ps4-uart/sessions/20260811_231126_933431-exp-20260810-001-a75-clean-uwsm-exit-and-xfce-recovery-e5490b04.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: UWSM exit passed, automatic XFCE recovery did not. `uwsm stop`
  identified and stopped `wayland-wm@hyprland.desktop.service`; Hyprland and
  every UWSM graphical-session unit became inactive. LightDM then opened an
  active X11 `lightdm-greeter` session instead of re-running autologin, despite
  the system and per-user selectors already pointing to XFCE
- service evidence: LightDM, NetworkManager and sshd remained active; SSH stayed
  available throughout the compositor teardown and greeter transition
- UART conclusion: capture continuity completed with no logger event. The known
  bridge handoff and IRQ 0.227 diagnostics occurred; no GPU reset, page fault,
  ring/fence timeout, filesystem error, crash, or fatal bridge failure appeared
- rollback: the predeclared recovery condition applies; no selector rollback is
  needed because persistent state is already safe and points to XFCE
- next action: `EXP-20260810-001-A76`; restart only LightDM and verify unattended
  XFCE autologin from the greeter state

### EXP-20260810-001-A76 — automated XFCE recovery after UWSM stop

- state: complete — inconclusive; action not confirmed
- question: can one remotely scheduled LightDM restart recover XFCE after the
  clean UWSM stop left LightDM at its greeter?
- changed variable: restart only `lightdm.service`; no operator input, package,
  configuration, kernel, console, or full-system restart
- expected evidence: active `Desktop=xfce`, `Type=x11` seat with
  `xfce4-session`; no Hyprland/UWSM compositor unit; LightDM, network and SSH
  active; UART has no GPU reset, crash, filesystem failure, or fatal bridge error
- timeout: 60 seconds for automatic login and SSH reconnection
- rollback: if recovery fails, close A76 before restoring A74's selector snapshot
- bounded UART context:
  [`20260811_231311_625034-exp-20260810-001-a76-automated-xfce-recovery-after-uwsm-stop-9bd3fbd0.md`](../../ps4-uart/sessions/20260811_231311_625034-exp-20260810-001-a76-automated-xfce-recovery-after-uwsm-stop-9bd3fbd0.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: inconclusive. The PS4 stopped answering at `192.168.50.125` before
  the transient `systemd-run` response or a LightDM transition could be
  confirmed. Repeated SSH polling, ICMP probes, and a bounded TCP/22 scan of
  `192.168.50.0/24` found no reachable replacement address
- UART conclusion: the slice contains only repeated MT7668 scan-to-idle cycles
  and one normal NetworkManager dispatcher deactivation. It contains no
  LightDM restart, display handoff, kernel crash, GPU reset, filesystem error,
  or fatal bridge failure, so the proposed changed variable must be treated as
  not executed rather than failed
- rollback: not applicable because the restart was not confirmed. Persistent
  LightDM and `.dmrc` selectors remain set to XFCE from A74
- next action: restore PS4 network reachability without rebooting, identify the
  visible LightDM/XFCE state, then retry the single LightDM restart as a new
  bounded experiment

### EXP-20260810-001-A77 — resume from visible XFCE and verify reachability

- state: complete — baseline mismatch identified
- question: after the operator reports XFCE visible, is the console again
  reachable over its recorded Linux address with the known recovery stack intact?
- changed variable: none; bounded read-only reachability, seat, service,
  package-manager, disk-space, and clock checks before any Quattro installation
- expected evidence: SSH at `192.168.50.125`; active X11/XFCE seat; LightDM,
  NetworkManager and sshd active; external USB root; synchronized clock; enough
  free space for the staged Quattro runtime transaction
- timeout: 2 minutes
- rollback: none; read-only probe
- bounded UART context:
  [`20260811_233809_705259-exp-20260810-001-a77-resume-visible-xfce-and-verify-reachability-93fd1504.md`](../../ps4-uart/sessions/20260811_233809_705259-exp-20260810-001-a77-resume-visible-xfce-and-verify-reachability-93fd1504.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: reachability and preflight passed, reported desktop identity did not.
  SSH is available at `192.168.50.125`; LightDM, NetworkManager and sshd are
  active; NTP is synchronized; the external USB ext4 root has 110 GiB free;
  pacman's lock is clear. The active seat is direct `Desktop=hyprland`,
  `Type=wayland`, with Hyprland and the native test terminal, not XFCE
- selection evidence: system LightDM defaults remain `xfce`, but the user's
  `.dmrc` again contains `Session=hyprland`, consistent with a later manual
  greeter choice. The running session remains usable and is not changed here
- UART conclusion: completed continuity, no logger event and no new kernel error
- rollback: none; the probe was read-only
- next action: `EXP-20260810-001-A78`; install the pinned PS4 Quattro runtime
  package profile without restarting or reconfiguring the live session

### EXP-20260810-001-A78 — install Quattro beta runtime packages

- state: complete — degraded by internal-disk probing
- question: can the PS4 external Arch root install the shell, portal, PipeWire,
  terminal, helper, font, and icon packages required by the reduced Quattro
  runtime while the proven direct Hyprland session remains healthy?
- changed variable: install only `profiles/quattro-beta/packages.txt` and its
  dependencies, resolving the Quattro-only packages through the temporary
  upstream edge repository; do not install `omarchy-dev`, Limine, Snapper,
  SDDM, applications, or modify permanent pacman/session/configuration state
- expected evidence: guarded transaction records exact resolved versions and
  new packages; Quickshell and Foot binaries run version probes; LightDM,
  Hyprland, HDMI, network and SSH remain active; UART has no GPU reset, crash,
  filesystem failure, or fatal bridge error
- timeout: 20 minutes while package downloads make forward progress
- rollback: inspect the generated `new-packages.txt` and use its recorded
  removal preview only if validation fails; leave the current session running
- bounded UART context:
  [`20260811_234145_856680-exp-20260810-001-a78-install-quattro-beta-runtime-packages-a5876034.md`](../../ps4-uart/sessions/20260811_234145_856680-exp-20260810-001-a78-install-quattro-beta-runtime-packages-a5876034.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: package transaction passed, hardware side effect degraded the gate.
  All 34 requested package versions resolved and installed; 74 packages were
  newly added. Quickshell `0.3.0` revision `28771c7`, Foot `1.27.0`, the
  Hyprland portal `1.4.1-1`, PipeWire `1.6.8`, fonts, and shell helpers are
  present. The exact version/URL/rollback evidence is stored in
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A78-20260811T174148Z`
- preservation evidence: `/etc/pacman.conf` has no permanent Omarchy repository;
  the temporary repository matched upstream's edge channel. The active direct
  Hyprland seat, LightDM, NetworkManager, sshd, HDMI and SSH remained healthy;
  the USB root retained 110 GiB free
- degraded evidence: installing `udiskie` pulled in and activated the UDisks2
  stack. Its discovery probed exposed internal device `sdb` and UART recorded
  repeated read and buffer I/O errors on `sdb` and its partitions. No error was
  recorded against USB root `sda2`, and no GPU reset or kernel crash occurred
- rollback: do not apply the broad generated rollback. Remove only the unsafe
  UDisks automount leaf and now-unneeded dependencies in a bounded mitigation
  experiment; omit upstream's `udiskie` autostart from the PS4 configuration
- next action: `EXP-20260810-001-A79`; remove the UDisks automount integration
  from the live PS4 profile and confirm internal-disk probing becomes inactive

### EXP-20260810-001-A79 — exclude UDisks automount on PS4

- state: complete — mitigation applied; quiescence check pending
- question: can the unsafe `udiskie`/UDisks discovery branch be removed from
  the reduced profile without affecting the active desktop, USB root, or network?
- changed variable: remove only `udiskie` plus dependencies that pacman proves
  are newly orphaned by it, and stop the UDisks2 service/socket if still active;
  keep every other A78 runtime package and the current session unchanged
- expected evidence: neither `udiskie` nor an active `udisks2.service` remains;
  the root stays on external `sda2`; Hyprland, LightDM, network and SSH remain
  healthy; no fresh `sdb` I/O burst appears after the mitigation
- timeout: 5 minutes
- rollback: reinstall the exact removed package versions recorded before the
  transaction only if an unrelated required capability regresses
- bounded UART context:
  [`20260811_234744_531196-exp-20260810-001-a79-exclude-udisks-automount-on-ps4-e5d2b397.md`](../../ps4-uart/sessions/20260811_234744_531196-exp-20260810-001-a79-exclude-udisks-automount-on-ps4-e5d2b397.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: mitigation applied. Pacman removed `udiskie`, `udisks2`, and 20
  dependencies proven orphaned by that leaf; the exact 22 versions and rollback
  command are recorded under
  `/var/lib/omarchy-ps4/experiments/EXP-20260810-001-A79-20260811T174846Z`.
  The UDisks2 service is inactive and both packages are absent
- preservation evidence: USB root remains `/dev/sda2`; the active direct
  Hyprland seat, LightDM, NetworkManager, sshd, SSH, Quickshell, Foot, portal,
  and PipeWire packages remain healthy
- UART conclusion: the package removal's systemd/udev reload caused one final
  burst of internal `sdb` reads and I/O errors. No error targeted USB root
  `sda2`, and no GPU reset or crash occurred. The capture was too short after
  the reload to claim that the errors are now quiescent
- rollback: not applied; the unsafe automount branch is intentionally excluded
- next action: `EXP-20260810-001-A80`; observe a quiet bounded interval with no
  UDisks process or hardware/configuration change before deploying Quattro

### EXP-20260810-001-A80 — verify internal-disk probe quiescence

- state: complete
- question: after the UDisks stack is absent and inactive, do internal `sdb`
  I/O errors stop recurring without another device-management action?
- changed variable: none; observe 30 seconds of continuous UART and verify the
  package/service state read-only
- expected evidence: no `sdb` read or buffer I/O error in the interval;
  `udiskie`/`udisks2` absent; external root, desktop, network and SSH healthy
- timeout: 1 minute
- rollback: none; observation only
- bounded UART context:
  [`20260811_234947_911589-exp-20260810-001-a80-verify-internal-disk-probe-quiescence-36980c81.md`](../../ps4-uart/sessions/20260811_234947_911589-exp-20260810-001-a80-verify-internal-disk-probe-quiescence-36980c81.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. A 48-second bounded interval contained only the two SSH session
  lifecycle records and no `sdb`, block, buffer, filesystem, GPU, or kernel
  error. `udiskie` and `udisks2` remain absent, UDisks2 inactive, external
  `sda2` remains root, and the desktop/network services remain active
- rollback: none; observation was read-only
- next action: `EXP-20260810-001-A81`; stage the pinned Quattro source and
  PS4-specific configuration without touching the active Hyprland config

### EXP-20260810-001-A81 — stage pinned Quattro source and PS4 overrides

- state: complete
- question: can the exact Quattro commit and reduced PS4 configuration be
  installed into versioned user-owned staging paths without reloading the live
  compositor or changing persistent LightDM/session state?
- changed variable: copy upstream commit
  `08204846ef6c2e2de8eba873d5888749e1d46ba5` plus the PS4 monitor,
  animation, autostart, shell, and environment overrides into versioned staging
  directories; do not replace `~/.config/hypr` or launch Quickshell
- expected evidence: archive digest and commit marker match; staged Lua/JSON
  files validate; current Hyprland instance PID/socket, HDMI, SSH and services
  remain unchanged; UART has no new kernel error
- timeout: 5 minutes
- rollback: remove only the versioned staged source/config directories and
  restore the recorded prior staging symlink if one existed
- bounded UART context:
  [`20260811_235401_576453-exp-20260810-001-a81-stage-pinned-quattro-source-and-ps4-overrid-08caadf3.md`](../../ps4-uart/sessions/20260811_235401_576453-exp-20260810-001-a81-stage-pinned-quattro-source-and-ps4-overrid-08caadf3.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. The archive digest is
  `1cee3d050db85b64f0b70625b04292ca09f41b2360c871e53a3cae8fb7184919`;
  its commit marker is `08204846ef6c2e2de8eba873d5888749e1d46ba5` and its version is
  `4.0.0.alpha`. Versioned source and PS4 config trees plus `current` staging
  symlinks are installed under `/home/ps4/.local/share/omarchy-ps4`
- preservation evidence: staged JSON validates and the staged Hyprland entry
  exists; live Hyprland remained the same PID `7036` and socket `wayland-1`;
  LightDM, NetworkManager, sshd and SSH remained active
- UART conclusion: completed continuity with only bounded SSH and routine Wi-Fi
  messages; no block, filesystem, display, GPU, or kernel error occurred
- rollback: not applied because staging passed and changes are not active
- next action: `EXP-20260810-001-A82`; launch only the staged Quattro shell as a
  transient user service inside the existing direct Hyprland session

### EXP-20260810-001-A82 — preview Quattro shell inside working Hyprland

- state: complete — degraded by Qt Quick GPU corruption
- question: can the pinned Quattro Quickshell render its reduced PS4 bar and
  answer shell IPC inside the current proven direct Hyprland session?
- changed variable: start one transient user service running Quickshell from
  the staged source with a disposable preview HOME and the reduced shell JSON;
  do not replace live Hyprland/UWSM/LightDM configuration or restart a session
- expected evidence: transient service stays active; a Quickshell client maps
  on HDMI; `shell ping` answers; logs have no fatal QML error; current terminal,
  input, SSH and services remain healthy; UART has no GPU reset or `sdb` errors
- timeout: 2 minutes
- rollback: stop and reset only `omarchy-ps4-quattro-poc.service`
- bounded UART context:
  [`20260811_235635_265878-exp-20260810-001-a82-preview-quattro-shell-inside-working-hyprla-aeec0181.md`](../../ps4-uart/sessions/20260811_235635_265878-exp-20260810-001-a82-preview-quattro-shell-inside-working-hyprla-aeec0181.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: lifecycle/IPC passed, visual result degraded. The transient service
  stayed active at PID `8576`; `shell ping` returned `ok`; Hyprland reported
  1920x1080 `omarchy-background` plus a 1920x26 `omarchy-bar` layer; the reduced
  plugin registry enabled the intended menu, workspaces, clock, network, audio,
  notifications, OSD and polkit components
- visual evidence: automated `grim` captures showed the bar and then the opened
  Omarchy root menu. The menu frame contained severe black striped and
  triangular corruption across the framebuffer, so the default Qt Quick RHI
  path initially appeared suspect. A84 later reproduced the same damage after
  every Quickshell layer was stopped, proving these captures cannot classify
  physical Quattro output. Capture digests are
  `d27a20d5429998379cb4988aabfddeb79e04fef130f26fbe57b85de96a7caa18`
  for the bar and
  `75c03d2b7444479289745208293e8d60c8ca5bfb3eff4417493931c05905ee56`
  for the open menu
- application logs: configuration loaded and the polkit agent registered.
  Missing `inotifywait` and a duplicate host-portal application ID produced
  nonfatal warnings; neither explains the framebuffer geometry corruption
- UART conclusion: completed continuity with only bounded SSH lifecycle;
  no `sdb` error, GPU reset, page fault, timeout, crash, or kernel error occurred
- rollback: applied. The transient preview unit was stopped and all Quickshell
  layers disappeared; the original Hyprland terminal session remains active
- next action: `EXP-20260810-001-A83`; rerun the identical preview with only
  Qt Quick's documented software scene-graph adaptation enabled

### EXP-20260810-001-A83 — preview Quattro with Qt software renderer

- state: complete — visual failure persists
- question: is the menu corruption specific to Qt Quick's default RHI renderer,
  and does the documented software scene-graph adaptation render the same POC
  cleanly on PS4?
- changed variable: relaunch the identical A82 source/config/unit with only
  `QT_QUICK_BACKEND=software` plus `QSG_INFO=1`; no package, shell JSON,
  compositor, session, service, kernel, or display change
- expected evidence: logs identify the software adaptation; bar and menu IPC
  pass; automated screenshots contain no striped/triangular corruption; current
  terminal, SSH and services stay healthy; UART has no GPU or `sdb` error
- timeout: 2 minutes
- rollback: stop and reset only `omarchy-ps4-quattro-poc.service`
- bounded UART context:
  [`20260811_235929_327889-exp-20260810-001-a83-preview-quattro-with-qt-software-renderer-66598a33.md`](../../ps4-uart/sessions/20260811_235929_327889-exp-20260810-001-a83-preview-quattro-with-qt-software-renderer-66598a33.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: fail for the proposed workaround. Quickshell PID `9713` stayed active,
  IPC returned `ok`, the expected background/bar layers mapped, and logs
  explicitly reported `Loading backend software`; nevertheless the automated
  bar capture still contained large diagonal damage artifacts before opening a
  menu. Capture digest:
  `41cc2261c0d01b935953aeda0d1e8b0db1ee261c502b9c58a3a4da91aee39f81`
- conclusion: switching away from Qt RHI/GPU rendering is insufficient. The
  A84 no-shell control later reproduced the same artifact, so this result does
  not distinguish Qt rendering from the already-broken capture/composition path
- application logs: the same nonfatal missing-`inotifywait` warning remained;
  no fatal QML or renderer error appeared
- UART conclusion: completed continuity with only bounded SSH lifecycle; no
  `sdb`, GPU reset, page fault, timeout, crash, or kernel error occurred
- rollback: applied; preview unit stopped and all shell layers disappeared
- next action: `EXP-20260810-001-A84`; keep the software adaptation and disable
  its partial updates, forcing full surface redraws

### EXP-20260810-001-A84 — force full Qt software surface updates

- state: complete — screenshot evidence invalidated by control
- question: does disabling Qt software scene-graph partial updates eliminate
  the diagonal framebuffer damage in the otherwise identical Quattro POC?
- changed variable: add only
  `QSG_SOFTWARE_RENDERER_FORCE_PARTIAL_UPDATES=0` to A83's software-rendered
  transient preview; all source, config, packages and session state stay fixed
- expected evidence: Qt software backend logged; bar and open menu screenshots
  are geometrically clean; IPC passes; current terminal/SSH/services remain;
  UART has no GPU or `sdb` error
- timeout: 2 minutes
- rollback: stop and reset only `omarchy-ps4-quattro-poc.service`
- bounded UART context:
  [`20260812_000101_455073-exp-20260810-001-a84-force-full-qt-software-surface-updates-699bbdfe.md`](../../ps4-uart/sessions/20260812_000101_455073-exp-20260810-001-a84-force-full-qt-software-surface-updates-699bbdfe.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: IPC/lifecycle passed; renderer comparison is inconclusive. Quickshell
  loaded the software backend, stayed active and answered `ok`; the full-update
  capture still showed diagonal damage. After stopping the unit and confirming
  that every Hyprland layer was gone, a control `grim` capture of only the
  original Weston terminal showed the same damage
- control evidence: full-update shell capture digest
  `8a69fe144dba18cda2494bf446ba2a54b1162c2b84b7c7f14c3d22779c3ca42f`;
  no-shell baseline digest
  `73cf1d3d7b2da7ed795dd657b7f7da170e4d7babea9dffd212dff73ba1025039`.
  Therefore automated screenshots are not valid evidence of HDMI appearance on
  this kernel/compositor stack
- UART conclusion: completed continuity with no `sdb`, GPU reset, page fault,
  timeout, crash, or kernel error
- rollback: applied; preview unit stopped and shell layers disappeared
- next action: `EXP-20260810-001-A85`; relaunch the normal RHI preview, open its
  menu through IPC, and use the operator's physical HDMI observation as the
  visual acceptance evidence

### EXP-20260810-001-A85 — physical HDMI Quattro POC preview

- state: complete — fail, physical presentation corruption confirmed
- question: does the pinned Quattro bar and root menu look geometrically clean
  on the physical HDMI display despite the invalid `grim` capture path?
- changed variable: relaunch A82's default-RHI transient preview and open only
  the root menu through IPC; no package, config, compositor, session, kernel, or
  display change
- expected evidence: bar/menu visible and clean on HDMI; IPC/service/layers
  healthy; current terminal, input, SSH and services remain; UART has no GPU or
  `sdb` error
- timeout: 3 minutes for operator observation
- rollback: stop only `omarchy-ps4-quattro-poc.service` if output is unusable;
  otherwise leave the POC visible for interaction
- bounded UART context:
  [`20260812_000250_731676-exp-20260810-001-a85-physical-hdmi-quattro-poc-preview-7b7073b2.md`](../../ps4-uart/sessions/20260812_000250_731676-exp-20260810-001-a85-physical-hdmi-quattro-poc-preview-7b7073b2.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: service, IPC and layer creation passed, but the operator confirmed the
  physical HDMI image was corrupt and stuttering. Continuous mouse movement
  temporarily restored a normal frame; corruption returned when movement
  stopped. This reproduces without relying on the invalid `grim` capture path
  and points below Quickshell at compositor/KMS presentation or damage cadence
- UART conclusion: completed continuity with only bounded SSH session lifecycle;
  no `sdb`, GPU reset, page fault, timeout, crash, or kernel error occurred
- rollback: applied; preview unit stopped and its layers disappeared
- next action: inspect the live Hyprland/Aquamarine presentation state, then run
  one shell-free test that disables variable frame scheduling while leaving the
  kernel, mode, scanout format, cursor mode and user applications unchanged

### EXP-20260810-001-A86 — disable variable frame scheduling

- state: complete — inconclusive, interaction path missing
- question: does continuously scheduling compositor frames keep the shell-free
  physical HDMI image clean after mouse movement stops?
- changed variable: set only live Hyprland `debug:vfr = 0`; keep Quickshell
  stopped, hardware cursors in automatic mode, damage tracking at full, direct
  scanout and VRR off, HDMI at 1920x1080/60 and XRGB8888
- expected evidence: after one mouse movement the existing terminal remains
  geometrically clean and smooth for at least 30 seconds at rest; SSH and input
  remain responsive; UART has no GPU or internal-disk error
- timeout: 2 minutes
- rollback: restore live `debug:vfr = 1`
- bounded UART context:
  [`20260812_000857_051658-exp-20260810-001-a86-disable-variable-frame-scheduling-de94ea93.md`](../../ps4-uart/sessions/20260812_000857_051658-exp-20260810-001-a86-disable-variable-frame-scheduling-de94ea93.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: live `debug:vfr` changed from `1` to `0` and back successfully, but
  the operator reached an empty desktop without a usable terminal/keybinding
  path and requested bindings before reporting a timed idle comparison. No
  HDMI pass/fail claim can be made from this action
- UART conclusion: completed continuity with only bounded SSH lifecycle; no
  GPU, internal-disk, timeout, fault or kernel error occurred
- rollback: applied; live `debug:vfr = 1` verified
- next action: install and live-load the PS4-safe subset of pinned Quattro
  bindings, then validate `Super+Return` using the physical keyboard

### EXP-20260810-001-A87 — load PS4-safe Omarchy bindings

- state: complete — pass for bindings, HDMI remains degraded
- question: can the current bare Hyprland session load the essential Omarchy
  interaction model and launch the installed Foot terminal from the keyboard?
- changed variable: replace only the current bare config with its repository
  version containing PS4-safe Quattro bindings, then reload Hyprland; do not
  start Quickshell or alter compositor rendering, display, cursor or kernel
- expected evidence: `hyprctl configerrors` is empty, the binding inventory
  contains `Super+Return`, and the operator opens Foot with `Super+Return`
- timeout: 2 minutes
- rollback: restore the saved remote `hyprland.conf` and reload Hyprland
- bounded UART context:
  [`20260812_001229_898300-exp-20260810-001-a87-load-ps4-safe-omarchy-bindings-d3049570.md`](../../ps4-uart/sessions/20260812_001229_898300-exp-20260810-001-a87-load-ps4-safe-omarchy-bindings-d3049570.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: config reload passed with no errors; `Super+Return` opened Foot and
  `Super+Shift+F` opened Thunar. The operator's physical photo shows correct
  window tiling/borders but severe repeating horizontal bands and stair-step
  reconstruction inside independent Foot and Thunar surfaces. This excludes
  fonts and Quickshell and strengthens a compositor buffer damage/age or
  modifier/pitch hypothesis
- UART conclusion: completed continuity with only SSH lifecycle and normal
  WLAN trace messages; no GPU reset, page fault, timeout, crash or `sdb` error
- rollback: not applied; the requested bindings are working and config is valid
- next action: keep the same clients and mode, set only
  `debug:damage_tracking = 0`, and obtain a physical idle observation

### EXP-20260810-001-A88 — disable compositor damage tracking

- state: complete — fail
- question: does forcing full-output damage eliminate the repeating stripes and
  stair-step reconstruction visible inside Foot and Thunar surfaces?
- changed variable: set only live Hyprland `debug:damage_tracking = 0`; retain
  VFR, hardware cursors, XRGB8888, 1920x1080/60, clients and shell state
- expected evidence: after mouse movement the existing windows redraw cleanly
  and stay geometrically correct for 30 seconds; SSH/input remain responsive;
  UART has no GPU or internal-disk error
- timeout: 2 minutes
- rollback: restore live `debug:damage_tracking = 2`
- bounded UART context:
  [`20260812_001834_610626-exp-20260810-001-a88-disable-compositor-damage-tracking-87e72f70.md`](../../ps4-uart/sessions/20260812_001834_610626-exp-20260810-001-a88-disable-compositor-damage-tracking-87e72f70.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: operator supplied a second physical photo showing the same severe
  horizontal striping, macro-tile stair steps and repeated surface fragments
  with damage tracking disabled. The corruption appears and disappears over
  time across independent Foot and Thunar surfaces; full damage is not a fix
- UART conclusion: completed continuity with only SSH lifecycle and normal WLAN
  trace messages; no GPU reset, page fault, timeout, crash or `sdb` error
- rollback: applied; live `debug:damage_tracking = 2` verified
- next action: restore the pinned Quattro shell as a separate UX action and
  validate its bar plus `Super+Space` IPC before continuing DRM isolation

### EXP-20260810-001-A89 — restore Quattro bar and menu

- state: complete — shell pass, binding environment defect found
- question: does the pinned Quattro shell return its top bar and answer the
  newly loaded `Super+Space` menu binding in the current Hyprland session?
- changed variable: start only the default-RHI transient Quattro preview unit;
  retain current clients, bindings, display, cursor, damage and VFR settings
- expected evidence: bar layer appears, shell IPC ping succeeds, and the
  operator opens the root menu with `Super+Space`; UART has no GPU or disk error
- timeout: 3 minutes
- rollback: stop and reset only `omarchy-ps4-quattro-poc.service`
- bounded UART context:
  [`20260812_002655_079015-exp-20260810-001-a89-restore-quattro-bar-and-menu-4f1359fc.md`](../../ps4-uart/sessions/20260812_002655_079015-exp-20260810-001-a89-restore-quattro-bar-and-menu-4f1359fc.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: transient default-RHI shell is active at PID `15465`; Hyprland maps
  `omarchy-background` at 1920x1080 and `omarchy-bar` at 1920x26; shell ping
  returns `ok`, and direct `omarchy-menu summon root` succeeds. Inspection found
  the bare `Super+Space` binding exported `PATH` but not the mandatory
  `OMARCHY_PATH`, explaining why the same wrapper failed only from the key
- UART conclusion: completed continuity with only bounded SSH lifecycle; no
  GPU, internal-disk, timeout, fault or kernel error occurred
- rollback: not applied; the requested shell remains active
- next action: add only `OMARCHY_PATH` to the existing binding, config-only
  reload Hyprland, and validate `Super+Space` physically

### EXP-20260810-001-A90 — repair Super+Space menu environment

- state: complete — binding fixed, HDMI remains degraded
- question: does exporting the pinned source as `OMARCHY_PATH` make the loaded
  `Super+Space` binding toggle the already-running Quattro root menu?
- changed variable: add only `OMARCHY_PATH` to the existing menu binding and
  run a config-only Hyprland reload; keep shell, clients and rendering fixed
- expected evidence: config errors remain empty, binding inventory contains the
  environment, and the operator toggles the root menu with `Super+Space`
- timeout: 2 minutes
- rollback: restore the A89 config and run a config-only reload
- bounded UART context:
  [`20260812_002833_096507-exp-20260810-001-a90-repair-super-space-menu-environment-d38adf94.md`](../../ps4-uart/sessions/20260812_002833_096507-exp-20260810-001-a90-repair-super-space-menu-environment-d38adf94.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: config-only reload succeeded with no errors and the binding inventory
  contains both the pinned `OMARCHY_PATH` and source `PATH`. Quattro remains
  active and answers IPC; the operator confirmed the bar returned, while also
  confirming continuing pixel corruption and stuttering
- UART conclusion: completed continuity with only SSH lifecycle and normal WLAN
  traces; no GPU reset, page fault, timeout, crash or `sdb` error
- rollback: not applied; the corrected binding and working shell remain active
- next action: do not restart the expensive current session without operator
  approval; prepare a bounded same-session restart with only
  `AMD_DEBUG=notiling` after the independent framebuffer audit is finalized

### EXP-20260810-001-A91 — force Mesa non-tiled buffers

- state: complete — degraded pass, major corruption removed
- question: does launching the identical Hyprland/Quattro stack with Mesa
  tiling disabled eliminate the temporal macro-tile stripes, stairs and
  checker corruption on physical HDMI?
- changed variable: install only `export AMD_DEBUG=notiling` at the LightDM
  session boundary and restart the graphical session; retain kernel, HDMI mode,
  Hyprland config, Quattro source/config, cursor, VFR and damage defaults
- expected evidence: new Hyprland process environment contains exactly
  `AMD_DEBUG=notiling`; Foot, Thunar and Quattro are restored; physical HDMI
  remains clean and responsive for at least two minutes while windows redraw;
  UART has no GPU, display or internal-disk error
- timeout: 5 minutes including LightDM autologin and application restoration
- rollback: remove the experiment `.xprofile` (it was absent before), restart
  the graphical session, and restore the same clients/shell
- bounded UART context:
  [`20260812_003309_602112-exp-20260810-001-a91-force-mesa-non-tiled-buffers-ee91ffac.md`](../../ps4-uart/sessions/20260812_003309_602112-exp-20260810-001-a91-force-mesa-non-tiled-buffers-ee91ffac.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: new LightDM-owned Hyprland PID `18150` and Quattro PID `20035` both
  contain `AMD_DEBUG=notiling`; Foot, Thunar, Firefox, background and bar were
  exercised. The operator reports no continuing stutter and only a residual
  artifact, versus the previous severe temporal macro-tile corruption. This is
  a strong degraded pass and confirms tiled-buffer layout as the primary fault
- UART conclusion: continuity completed across the controlled session restart;
  expected PS4 bridge modeset diagnostics appeared, with no GPU reset, page
  fault, timeout, crash or `sdb` error
- rollback: not applied; retain no-tiling as the working PS4 POC adaptation
- next action: separately tune excessive perceived brightness with a reversible
  software gamma experiment; do not conflate residual artifacts with color

### EXP-20260810-001-A92 — reduce display gamma to 85 percent

- state: complete — fail, output blacked out
- question: does a neutral 85% software gamma make browser whites and dark UI
  detail comfortable without crushing shadows or tinting the image?
- changed variable: start Hyprsunset in identity mode, then set only gamma to
  85%; retain Mesa no-tiling, HDMI mode, compositor, shell, clients and theme
- expected evidence: whites are less harsh, browser chrome and dark surfaces
  retain visible detail, colors remain neutral, and UART has no display/GPU
  error
- timeout: 2 minutes
- rollback: set Hyprsunset identity and stop/reset its transient user service
- bounded UART context:
  [`20260812_004412_046750-exp-20260810-001-a92-reduce-display-gamma-to-85-percent-3d58cb8d.md`](../../ps4-uart/sessions/20260812_004412_046750-exp-20260810-001-a92-reduce-display-gamma-to-85-percent-3d58cb8d.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: Hyprsunset accepted gamma 85 but the operator reported an immediate
  black monitor. The PS4 legacy DCE8 gamma-LUT path is therefore unsafe for
  this POC and must not be used for display tuning
- UART conclusion: completed continuity with routine WLAN scan messages only;
  no GPU, display, filesystem or internal-disk kernel error accompanied the
  blackout
- rollback: applied; identity request returned `ok`, the transient Hyprsunset
  service is inactive, no Hyprsunset process remains, and HDMI reports DPMS on
  at 1920x1080/60 XRGB8888
- next action: confirm physical HDMI recovery; use the monitor OSD for brightness
  and contrast, then improve compositor border colors separately if requested

### EXP-20260810-001-A93 — recover HDMI with one DPMS cycle

- state: complete — pass
- question: does one explicit HDMI DPMS off/on cycle restore physical output
  after the failed DCE8 gamma-LUT operation?
- changed variable: cycle only `HDMI-A-1` DPMS off and on; retain Hyprland,
  Mesa no-tiling, shell, clients, mode and all configuration
- expected evidence: physical HDMI image returns with the prior no-tiling state;
  SSH remains responsive and UART has no GPU/display error
- timeout: 1 minute
- rollback: DPMS on is the terminal state; if still black, close this experiment
  and restart only the graphical session in a new bounded action
- bounded UART context:
  [`20260812_005233_140586-exp-20260810-001-a93-recover-hdmi-with-one-dpms-cycle-e32cc103.md`](../../ps4-uart/sessions/20260812_005233_140586-exp-20260810-001-a93-recover-hdmi-with-one-dpms-cycle-e32cc103.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: one explicit HDMI-A-1 DPMS off/on cycle restored the physical image;
  the operator confirmed recovery. Hyprland, Quattro and Mesa no-tiling stayed
  in place, so no graphical-session restart was required
- UART conclusion: expected PS4 bridge modeset diagnostics completed with no GPU
  reset, page fault, timeout, crash or internal-disk error
- rollback: terminal state is DPMS on at 1920x1080/60 XRGB8888
- next action: mark Hyprsunset unsupported on this PS4 DCE8 path and use monitor
  OSD controls for brightness/contrast; await both independent UVD audits

### EXP-20260810-001-A94 — pin the Quattro bar to the top edge

- state: complete — pass
- question: can the active isolated Quattro preview be restored from its
  persisted left-edge override to the repository's intended top-edge layout?
- changed variable: change only the active preview's `bar.position` from
  `left` to `top`; retain its widget layout, Hyprland, Mesa no-tiling, HDMI
  mode, clients and all other shell settings
- expected evidence: the live JSON reads `top`; Quickshell reloads without a
  restart; Hyprland reserves only the 28-pixel top edge; HDMI stays visible
- timeout: 2 minutes
- rollback: restore the exact pre-change `shell.json` snapshot, which has
  `bar.position` set to `left`
- bounded UART context:
  [`20260812_010727_407472-exp-20260810-001-a94-pin-quattro-bar-to-top-edge-b5ae36c0.md`](../../ps4-uart/sessions/20260812_010727_407472-exp-20260810-001-a94-pin-quattro-bar-to-top-edge-b5ae36c0.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `274d8db2bb43469ea93e25d7befa6db1`, epoch `1`
- result: pass. The active Quattro process uses isolated preview HOME
  `EXP-20260810-001-A91`; its persisted override was `left` even though the
  repository profile default is `top`. The live value is now `top`, Quickshell
  reloaded in place with the same PID, and Hyprland reports reserved edges
  `[28, 0, 0, 0]` — top only
- UART conclusion: capture continuity completed with routine WLAN scan output
  only; no GPU, display, filesystem or internal-disk error appeared
- rollback: not applied. The exact former configuration remains beside the live
  file as `shell.json.a94.before`
- next action: treat the legacy DRM backend as a kernel/display architecture
  constraint; do not force AMD DC until the PS4 HDMI bridge path is ported or a
  separately bounded boot experiment has a recovery plan

### EXP-20260813-001-A1 — stage quiet splash boot set on existing USB

- state: complete — pass
- question: can the new installer-capable initramfs and quiet product command
  line replace visible HDMI boot logs without changing the accepted kernel,
  root filesystem, VRAM allocation, SATA selector, or desktop?
- changed variable: boot presentation stack only — replace
  `initramfs.cpio.gz` and `bootargs.txt` as one matched set; keep the exact
  accepted `bzImage`, `vram.txt=1024`, `root=LABEL=OMARCHY-PS4`,
  `libata.force=1.00:disable`, and existing ext4 root unchanged
- preflight evidence: external Kingston DataTraveler is `/dev/disk12`, MBR,
  FAT32 `disk12s1` (1 GiB, label `NO NAME`) plus Linux `disk12s2` (122.9 GB);
  active kernel SHA-256 is
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`;
  FAT has 1,046,556,672 bytes free. Existing `SHA256SUMS` is stale for the
  SATA-disabled `bootargs.txt`
- expected evidence: bounded logger continuity completes; old boot files are
  preserved under one timestamped recovery directory; staged initramfs and
  product bootargs match their pinned hashes; kernel and VRAM hashes do not
  change; filesystem sync and unmount succeed
- timeout: 5 minutes
- rollback: restore the exact pre-A1 `initramfs.cpio.gz`, `bootargs.txt`, and
  `SHA256SUMS` from the timestamped recovery directory; keep the existing 5.4
  recovery directory untouched
- bounded UART context:
  [`20260813_195838_203631-exp-20260813-001-a1-stage-quiet-splash-boot-set-on-existing-usb-faa8f04e.md`](../../ps4-uart/sessions/20260813_195838_203631-exp-20260813-001-a1-stage-quiet-splash-boot-set-on-existing-usb-faa8f04e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The accepted kernel and `vram.txt=1024` were unchanged. The
  active initramfs is now
  `307fcce4d3a4893fb9a729c9c43dec886979afe088e7d6f44e430e1132709264`
  and the quiet splash boot arguments are
  `3c023f27188299545d4929adfa9c2738f01f6a5108a706135516b23a9d27ee2c`.
  The prior initramfs, boot arguments and manifest are preserved under
  `recovery/EXP-20260813-001-A1-before-splash/`; every active manifest entry
  passed `shasum -a 256 -c SHA256SUMS`
- UART conclusion: continuity completed. The compact context contains only
  routine Orbis RNPS update failures while GoldHEN was idle; no logger restart,
  serial reconnect, storage error or console-state change occurred
- rollback: not applied; the exact pre-A1 initramfs SHA-256 is
  `d4585d1533de7ceb798a3e4464e1d1eb29e167d9ee22a2841e5d5d3abecb446e`
  and the exact pre-A1 boot-argument SHA-256 is
  `aa406f0c017b1c6bed7a4755754c3c869d4185c6273b39e34bd8f8f2b39865ae`
- next action: perform read-only FAT32 and ext4 checks and eject the USB as
  `EXP-20260813-001-A2`; boot validation remains a later operator action

### EXP-20260813-001-A2 — verify USB filesystems and eject

- state: complete — fail; device intentionally left unmounted and not ejected
- question: are both partitions on the prepared Kingston USB internally clean
  after staging, so the device can be ejected without risking the Arch rootfs?
- changed variable: no filesystem content; unmount `/dev/disk12`, run read-only
  FAT32 and ext4 checks, then eject the exact external Kingston device only if
  both checks pass
- expected evidence: `fsck_msdos -n` reports the FAT32 boot volume clean;
  `e2fsck -f -n` reports the ext4 root filesystem clean; `/dev/disk12`
  disappears after a successful `diskutil eject`
- timeout: 10 minutes
- rollback: if either check fails or the device identity changes, do not repair
  or eject; stop the session and leave the device unmounted for review. If the
  checks abort cleanly, remount only the FAT partition with `diskutil mount`
- bounded UART context:
  [`20260813_200151_985425-exp-20260813-001-a2-verify-usb-filesystems-and-eject-edc6ebe9.md`](../../ps4-uart/sessions/20260813_200151_985425-exp-20260813-001-a2-verify-usb-filesystems-and-eject-edc6ebe9.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: fail. `diskutil verifyVolume` ran `fsck_msdos -n` and returned exit
  code 0 for FAT32. Homebrew e2fsprogs 1.47.4 ran `e2fsck -f -n` against the
  unmounted ext4 partition and returned exit code 4. It found deleted inode
  `6292591` with zero deletion time, block- and inode-bitmap differences, and
  free-block/free-inode count mismatches. Because `-n` suppresses journal
  recovery and all repairs, the exact amount requiring repair remains unknown
- UART conclusion: continuity completed with routine idle Orbis shell status
  only; no logger restart, serial reconnect or PS4 storage action occurred
- rollback: applied by stop condition. No repair-mode tool ran. Both partitions
  remain unmounted and `/dev/disk12` remains attached; eject was withheld
- next action: with explicit approval, run one unmounted ext4 repair as
  `EXP-20260813-001-A3`, repeat the read-only check, and eject only after FAT32
  and ext4 both pass

### EXP-20260813-001-A3 — rebuild and restore the Kingston USB in OrbStack

- state: complete — pass
- question: can the damaged USB filesystem structure be rebuilt from zero
  while preserving the exact working Arch/XFCE/Hyprland/Quattro development
  root and the accepted 6.18.44 Baikal boot set?
- changed variable: USB storage structure as one atomic rebuild — repair the
  old ext4 only to make a private snapshot, replace the old 1 GiB FAT32 plus
  ext4 layout with the product 2 GiB `PS4BOOT` plus remaining
  `OMARCHY-PS4` layout, then restore the snapshot and accepted boot artifacts
- resolved target: Kingston DataTraveler 3.0, USB 3.0, 123,983,626,240 bytes,
  vendor/product `0951:1666`, serial `E0D55EA573F0194049CD0236`; macOS node is
  `/dev/disk12`, OrbStack USB ID is `00210000`. No Linux block-device name is
  assumed before dedicated passthrough
- pinned boot evidence: kernel
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`,
  initramfs
  `307fcce4d3a4893fb9a729c9c43dec886979afe088e7d6f44e430e1132709264`,
  product boot arguments
  `3c023f27188299545d4929adfa9c2738f01f6a5108a706135516b23a9d27ee2c`,
  and `vram.txt=1024`
- expected evidence: OrbStack resolves the attached disk by Kingston model,
  serial and 124 GB size; repair-mode `e2fsck` completes; a local snapshot and
  SHA-256 are preserved before erasure; the repository USB preparation tool
  creates only `PS4BOOT` FAT32 and `OMARCHY-PS4` ext4; restored root content
  includes the existing owner, XFCE recovery, Hyprland, Quattro and Firefox;
  both filesystems pass final read-only checks; boot artifacts match pinned
  hashes; OrbStack detaches and macOS ejects the exact Kingston device
- timeout: 90 minutes
- rollback: after the destructive boundary, recreate the same two-partition
  layout and restore the local pre-wipe snapshot. The repository XFCE archive
  remains an independent baseline fallback. Do not touch PS4 internal storage
- stop conditions: abort before `wipefs` if USB transport, model, serial, size,
  partition count or UART continuity differs; abort after snapshot creation if
  its archive test or SHA-256 fails; do not eject unless both final filesystem
  checks pass
- bounded UART context:
  [`20260813_201155_610289-exp-20260813-001-a3-rebuild-and-restore-the-kingston-usb-in-orbs-2ae2efcf.md`](../../ps4-uart/sessions/20260813_201155_610289-exp-20260813-001-a3-rebuild-and-restore-the-kingston-usb-in-orbs-2ae2efcf.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. OrbStack dedicated USB passthrough resolved only the expected
  Kingston as `/dev/sda` by model, serial and exact byte size. Repair-mode
  e2fsck replayed the old journal, cleared six orphaned inodes and corrected
  the free-block/free-inode counters; a second no-write check returned 0
- pre-wipe recovery: the repaired live root is preserved locally as
  `backups/EXP-20260813-001-A3-prewipe/omarchy-ps4-rootfs.tar.zst`, SHA-256
  `11bee76882cf5aa7e3c5fbfe79ba6255ffedde5e4f4b11886a2c9468dafff4f0`;
  its FAT companion is `ps4boot-fat.tar.zst`, SHA-256
  `653088cb500608a1ad0a2d9d2a5c48d6120091ecadfacd61996a0de62fdb0389`.
  Both zstd streams tested clean and required root/boot paths were enumerated
  before erasure
- rebuilt layout: DOS/MBR disk identifier `0x81dc94fb`; 2 GiB FAT32
  `PS4BOOT` UUID `1A86-7AB8`; remaining 113.5 GiB ext4 `OMARCHY-PS4` UUID
  `c465e199-07f3-49e0-8c0d-4da20feb29a2`. The repaired live snapshot was
  restored with numeric ownership, ACLs and extended attributes
- restored-content evidence: FAT `SHA256SUMS` validates the accepted kernel,
  splash initramfs, product boot arguments and `vram.txt=1024`; the product
  command line retains `libata.force=1.00:disable`. The root retains user
  `ps4`, label-based fstab, XFCE recovery, Firefox `153.0.3-2`, Hyprland
  `0.56.2-1`, Quickshell `0.3.0.r20.g28771c7-1`, and the existing Omarchy
  user state
- final integrity: after a full sync and unmount, `fsck.fat -n -v` returned 0
  for `PS4BOOT` and `e2fsck -f -n` returned 0 for `OMARCHY-PS4`. OrbStack then
  detached USB ID `00210000`; it reports `Machine: Not attached`. macOS did
  not re-enumerate the Kingston as a block disk, so no guessed `diskutil`
  target was used; the physical device entered a safe-removal state. The
  operator then unplugged it, and `orb usb list` confirmed the Kingston is no
  longer present while continuous CH340 UART capture remains READY
- UART conclusion: continuity completed with routine idle Orbis shell, RNPS,
  NetEv and heap messages only; no logger restart, serial reconnect or PS4
  storage action occurred
- rollback: not applied. The two validated local pre-wipe archives are the
  exact restore path; the pinned repository XFCE rootfs remains the baseline
  fallback
- next action: physically move the safely detached Kingston to the PS4, then
  define a separate bounded cold-boot experiment to validate splash, SATA-off,
  USB root, HDMI, XFCE recovery and Omarchy login

### EXP-20260813-001-A4 — connect rebuilt Kingston to GoldHEN PS4

- state: complete — pass
- question: does the GoldHEN-running PS4 remain stable when the freshly rebuilt
  Kingston USB is connected before any Linux payload is launched?
- changed variable: USB presence only — connect the serial-matched rebuilt
  Kingston to the PS4; do not open a payload menu or launch Linux
- precondition: operator reports GoldHEN is running; the Kingston was cleanly
  detached after FAT32 and ext4 checks returned 0 in A3; continuous CH340 UART
  must remain READY before the physical action
- expected evidence: Orbis remains responsive; no error dialog, reboot or
  kernel panic occurs; UART continuity completes without a USB/storage fault
- timeout: 1 minute after insertion
- rollback: if Orbis freezes, reboots or shows a storage error, do not launch
  Linux; unplug only the rebuilt Kingston after reporting the visible outcome
- stop condition: no Linux payload action belongs to A4. Close and review this
  bounded session before defining the separate boot experiment
- bounded UART context:
  [`20260813_202940_749891-exp-20260813-001-a4-connect-rebuilt-kingston-to-goldhen-ps4-deba4912.md`](../../ps4-uart/sessions/20260813_202940_749891-exp-20260813-001-a4-connect-rebuilt-kingston-to-goldhen-ps4-deba4912.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The operator reported completion with no error outcome. Orbis
  identified the exact Kingston serial as `/dev/da1`, 242,155,520 sectors,
  mounted partition 1 at `/mnt/usb0`, and left partition 2 unmounted because
  ext4 is intentionally unknown to Orbis. No payload was launched
- UART conclusion: routine whole-disk and partition automounter diagnostics
  only. The expected external-HDD metadata checks failed because this is not a
  Sony-encrypted extended-storage device; they were followed by a successful
  partition-1 mount. No kernel panic, reboot, disconnect or storage I/O fault
  occurred
- rollback: not applied; the rebuilt Kingston remains connected to the PS4
- next action: do not install an Omarchy manager FPKG because no native `.pkg`
  is produced yet. Define a separate bounded boot experiment and launch the
  already tested PS4 Linux Loader path against the staged USB boot set

### EXP-20260813-001-A5 — cold boot rebuilt USB with 1024 MiB Linux loader

- state: complete — degraded; boot passed, graphical scanout corrupted
- question: does one launch of the previously successful 1024 MiB PS4 Linux
  Loader boot the rebuilt USB through the splash initramfs into the restored
  Linux desktop without the former ext4 corruption or internal-SATA delay?
- changed variable: boot from the rebuilt USB once — use the same Vue After v2
  1024 MiB Linux Loader path that previously reached the working HDMI desktop;
  do not send a second payload or change loader, VRAM, boot files or ports
- precondition: GoldHEN is running; A4 proved the exact Kingston is connected
  as Orbis `/dev/da1`; FAT32 and ext4 passed host checks; continuous CH340 UART
  must remain READY before payload launch
- expected evidence: loader hands off to Linux 6.18.44-ps4-baikal; initramfs
  resolves `PS4BOOT` and `OMARCHY-PS4`; no filesystem repair is requested;
  SATA `1.00` does not cause the prior long timeout; HDMI shows splash then the
  restored LightDM/XFCE or Omarchy session; keyboard and mouse remain usable
- timeout: 4 minutes from payload launch
- rollback: if boot stalls, HDMI remains black, or a filesystem/GPU fault
  appears, do not resend the payload. Report HDMI, LED, controller and visible
  state; stop/review UART, then power-cycle only in a separately declared action
- stop condition: one payload launch only. A successful desktop appearance is
  evidence for this boot, not yet multi-boot support promotion
- bounded UART context:
  [`20260813_204337_332929-exp-20260813-001-a5-cold-boot-rebuilt-usb-with-1024-mib-linux-lo-4556fc57.md`](../../ps4-uart/sessions/20260813_204337_332929-exp-20260813-001-a5-cold-boot-rebuilt-usb-with-1024-mib-linux-lo-4556fc57.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- payload evidence: the primary agent sent the pinned 313 KiB x86-64 loader
  exactly once to GoldHEN PayLoader `192.168.50.215:9090`; SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  the TCP transfer returned 0 and the loader entered `sys_kexec`
- boot result: pass through the graphical target. Linux
  `6.18.44-ps4-baikal` initialized Liverpool/DCE8 with 1024 MiB VRAM; ATA
  `1.00` was explicitly disabled; initramfs resolved `OMARCHY-PS4` to
  `/dev/sda2` at 11.55 seconds and mounted the new ext4 UUID read/write without
  fsck or repair. systemd reached SSH at 22.63 seconds and the graphical target
  at 22.67 seconds, eliminating the former missing-root and long internal-SATA
  paths
- operator outcome: degraded. HDMI displayed severe full-screen blue/grey
  tiled scanout corruption with a visible mouse pointer rather than a usable
  desktop. This matches the class of prior Liverpool legacy-display corruption
  but is materially worse than the accepted no-tiling desktop state
- UART conclusion: the bridge completed its forced 1920x1080@60 sequences and
  repeated the expected mode programming at graphical startup. No amdgpu page
  fault, ring timeout, GPU reset, kernel panic, ext4 error or USB I/O error was
  logged. The renamed systemd journal was an old unclean-shutdown journal file,
  not an ext4 integrity failure
- rollback: no live rollback attempted; no second payload was sent. Linux
  remains running from the external USB with corrupted HDMI output
- next action: inspect the restored root snapshot locally for the accepted
  Mesa/Xorg no-tiling and session-selection state. If the cause is not proven
  locally, define a separate bounded read-only SSH diagnostic before changing
  one display variable

### EXP-20260813-001-A6 — identify live corrupted graphical session

- state: complete — pass; Xorg/XFCE path confirmed
- question: is the corrupted boot running the configured XFCE/Xorg session,
  where Xorg starts before the user `.xprofile` exports `AMD_DEBUG=notiling`,
  rather than the previously accepted no-tiling Hyprland session?
- changed variable: none; read-only SSH inspection of login sessions, graphical
  processes, command lines, selected environment variables and recent display
  service status. Do not restart or reconfigure the display stack
- local preflight evidence: the restored root has LightDM
  `autologin-session=xfce` and Xorg modesetting with default acceleration;
  `/home/ps4/.xprofile` exports `AMD_DEBUG=notiling`, but LightDM launches Xorg
  before its Xsession wrapper sources that user file. The A91 accepted result
  specifically proved the variable inside LightDM-owned Hyprland and Quattro
- expected evidence: live process/session inventory identifies Xorg plus XFCE;
  XFCE clients may contain `AMD_DEBUG=notiling` while the Xorg server does not;
  no GPU reset, page fault, filesystem error or service crash is introduced
- timeout: 2 minutes
- rollback: none for read-only inspection; close SSH and bounded UART session
- stop condition: do not restart LightDM, terminate Xorg, launch Hyprland or
  modify any file in A6
- bounded UART context:
  [`20260813_204938_900944-exp-20260813-001-a6-identify-live-corrupted-graphical-session-67cf918b.md`](../../ps4-uart/sessions/20260813_204938_900944-exp-20260813-001-a6-identify-live-corrupted-graphical-session-67cf918b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. Batch-mode SSH at `192.168.50.125` found root-owned Xorg PID
  369 on `:0`, `xfce4-session` PID 433 and `xfwm4` PID 498. No Hyprland or
  Quickshell process exists. XFCE and xfwm4 contain `AMD_DEBUG=notiling`,
  `DESKTOP_SESSION=xfce` and `XDG_SESSION_TYPE=x11`
- conclusion: LightDM launches Xorg before its Xsession wrapper sources the
  user's `.xprofile`; therefore the environment fixes Mesa clients but cannot
  change Xorg glamor's already-created tiled buffers. This explains why A91's
  no-tiling Hyprland restart improved HDMI while the restored default XFCE/Xorg
  boot immediately reproduces macro-tile scanout corruption
- UART conclusion: completed continuity with only the bounded SSH user session
  lifecycle; no GPU, display, filesystem or USB fault appeared
- rollback: none required; inspection was read-only
- next action: test one Xorg variable in A7 — set the modesetting driver's
  `AccelMethod` to `none`, restart only LightDM, and retain XFCE, kernel, mode,
  boot files and all other state

### EXP-20260813-001-A7 — disable Xorg glamor acceleration

- state: complete — pass; clear XFCE scanout with degraded 2D performance
- question: does setting only Xorg modesetting `AccelMethod` to `none` remove
  the severe tiled scanout corruption while preserving the XFCE recovery
  desktop at 1920x1080/60?
- changed variable: add only `Option "AccelMethod" "none"` to the existing
  `20-omarchy-ps4-modesetting.conf`, then restart LightDM once; retain XFCE,
  autologin, kernel, Mesa no-tiling user environment, mode and boot state
- expected evidence: a new Xorg/XFCE session starts without glamor-accelerated
  buffers; HDMI becomes geometrically stable with a usable cursor, panel and
  desktop; SSH remains available; UART has no GPU reset, page fault or ext4
  error. Lower 2D performance is acceptable for this recovery baseline
- timeout: 3 minutes after the LightDM restart
- rollback: preserve the exact pre-A7 Xorg file remotely; if HDMI becomes black
  or the display manager fails, restore it over SSH and restart LightDM once
- stop condition: do not launch Hyprland, Quickshell or a second payload; do
  not change damage tracking, cursor, mode or kernel in A7
- bounded UART context:
  [`20260813_205117_605290-exp-20260813-001-a7-disable-xorg-glamor-acceleration-4d0b1ebe.md`](../../ps4-uart/sessions/20260813_205117_605290-exp-20260813-001-a7-disable-xorg-glamor-acceleration-4d0b1ebe.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- candidate evidence: the staged configuration SHA-256 was
  `0a95a7e7e60013d5e3b5f87e589d5f17b807c1efc20a8308680bd94c48e21983`.
  The exact pre-A7 file is preserved on the console under
  `/var/lib/omarchy-ps4/experiments/EXP-20260813-001-A7/`
- result: pass. After exactly one LightDM restart, Xorg PID 1199 selected
  1920x1080 and logged `glamor disabled` plus `ShadowFB: preferred YES,
  enabled YES`; LightDM, XFCE and xfwm4 all restarted successfully. The
  operator reported that HDMI loaded clear, removing A5's full-screen
  macro-tile corruption
- conclusion: the corruption came from Xorg modesetting glamor buffers whose
  tiled layout is incompatible with Liverpool/DCE8 scanout on this legacy PS4
  display path. The XFCE recovery baseline must use `AccelMethod none`; the
  resulting software-rendered 2D desktop is intentionally classified degraded
- UART conclusion: completed continuity. UART contained the expected LightDM
  stop/start and display-bridge mode programming only; no GPU page fault, ring
  timeout, reset, kernel panic, ext4 error or USB I/O error appeared
- rollback: not applied because the display passed. The accepted setting is
  installed on the live USB and promoted to the XFCE image overlay
- next action: verify this recovery profile in a separate unchanged cold-boot
  experiment before promotion beyond degraded; test Hyprland/Omarchy as an
  independent path rather than changing the accepted XFCE baseline

### EXP-20260813-001-A8 — activate the Omarchy Quattro session

- state: complete — blocked by missing portable activation; no session change
- question: can the restored, previously proven UWSM/Hyprland/Quattro profile
  replace the currently clear XFCE session without reintroducing severe tiled
  scanout corruption?
- changed variable: graphical session profile only — synchronize LightDM and
  the user session selector from `xfce` to `hyprland-uwsm`, retaining the
  installed Quattro RC2 configuration and session-boundary
  `AMD_DEBUG=notiling`, then restart LightDM exactly once. Keep kernel, HDMI
  mode, boot files, VRAM, storage, network and user packages unchanged
- precondition: A7 is closed with completed UART continuity and the operator
  reports clear XFCE HDMI; continuous CH340 UART must remain READY before any
  live SSH action
- expected evidence: LightDM starts a UWSM-owned Wayland session; Hyprland and
  Quickshell remain alive; the Quattro bar appears only at the top;
  `Super+Space` opens the Omarchy menu; Foot, Thunar, keyboard and mouse work;
  HDMI has no severe macro-tile corruption; SSH remains reachable; UART has no
  GPU reset, page fault, kernel panic, ext4 error or USB I/O error
- timeout: 5 minutes after the single LightDM restart
- rollback: use the guarded session selector to synchronize both persistent
  selectors back to `xfce`, then restart LightDM once in a separately declared
  rollback action. The accepted A7 Xorg `AccelMethod none` recovery profile
  remains installed and unchanged
- stop condition: do not reboot, resend a payload, change Mesa, Quattro,
  Hyprland, display mode, damage tracking, cursor, kernel or boot files in A8.
  Stop and review A8 before any rollback or repair
- bounded UART context:
  [`20260813_210418_063824-exp-20260813-001-a8-activate-omarchy-quattro-session-4659bb88.md`](../../ps4-uart/sessions/20260813_210418_063824-exp-20260813-001-a8-activate-omarchy-quattro-session-4659bb88.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: stopped safely before the changed variable. SSH proved LightDM still
  selects `xfce` and `.xprofile` contains `AMD_DEBUG=notiling`; Hyprland,
  UWSM, Quickshell, Foot and Thunar are installed. The user still has the old
  direct-Hyprland test configuration, however, and neither
  `omarchy-launch-shell` nor the portable Quattro autostart is active. A8 would
  therefore have launched bare Hyprland rather than Omarchy
- UART conclusion: completed continuity with only two short SSH session
  lifecycles; no display restart, GPU error, filesystem error or USB fault
- rollback: none required. No selector, configuration, service or running
  process was changed; clear A7 XFCE remains active
- next action: install the locally validated RC2 portable user layer without
  restarting the current session as A9, close/review it, then activate the
  complete Omarchy profile in a separately bounded A10

### EXP-20260813-001-A9 — install portable Omarchy Quattro RC2 user layer

- state: complete — pass
- question: can the pinned Quattro RC2 portable bundle atomically replace the
  old test user configuration with its complete Omarchy command, theme, menu,
  bar and Hyprland configuration while leaving clear XFCE running?
- changed variable: user-owned portable Omarchy layer only — transfer and run
  `omarchy-ps4-portable-4.0.0rc2-38542a1.tar.zst`, SHA-256
  `f43b0e0a4d91ca6c75a0ad15a31c3c854829da5caa0b01e5861a0c8c87e4daf7`,
  as user `ps4`. Do not run Pacman, write `/etc`, select a session, or restart
  any service
- expected evidence: bundle preflight validates x86-64, USB root label and
  transport plus all runtime commands; payload manifest passes; the pinned
  commit `38542a1f513740559660a468ffbf68ed082b2381` becomes the active portable
  release; user config symlinks resolve inside the versioned install;
  `omarchy-launch-shell` and `omarchy-menu` resolve through the session PATH;
  XFCE, HDMI, SSH and UART remain healthy
- timeout: 5 minutes
- rollback: run the exact user-owned `ROLLBACK.sh` created by the installer;
  it restores the old direct-Hyprland test config and removes only this pinned
  portable release. Do not restart LightDM during A9
- stop condition: stop and review immediately after installation and read-only
  validation. Session activation belongs only to A10
- bounded UART context:
  [`20260813_210558_447508-exp-20260813-001-a9-install-portable-omarchy-quattro-rc2-user-la-4ab0f4c5.md`](../../ps4-uart/sessions/20260813_210558_447508-exp-20260813-001-a9-install-portable-omarchy-quattro-rc2-user-la-4ab0f4c5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The transferred archive matched its pinned SHA-256. Preflight
  resolved x86-64, every required runtime command, `/dev/sda2` label
  `OMARCHY-PS4`, and USB transport. The payload manifest passed and commit
  `38542a1f513740559660a468ffbf68ed082b2381` is active under the versioned
  user-owned runtime and configuration roots
- activation evidence: `~/.config/hypr`, `~/.config/omarchy`,
  `~/.config/mimeapps.list`, and the UWSM environment resolve into the pinned
  configuration release. That environment exports the portable command path
  and `AMD_DEBUG=notiling`; Hyprland autostart invokes
  `omarchy-launch-shell`. The executable rollback is
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A9-20260813T150647Z/ROLLBACK.sh`
- runtime preservation: XFCE PID 1235 remained active; Hyprland and Quickshell
  were absent as required; LightDM, NetworkManager and sshd remained active
- UART conclusion: completed continuity with expected SSH sessions and routine
  MT7668 P2P diagnostics only; no display restart, GPU error, filesystem error
  or USB fault appeared
- rollback: not applied because installation and validation passed
- next action: activate the complete portable profile as A10 by synchronizing
  both LightDM selectors to `hyprland-uwsm` and restarting LightDM once

### EXP-20260813-001-A10 — start UWSM Hyprland with Omarchy Quattro RC2

- state: complete — fail; Hyprland started but portable path was reset
- question: does the complete pinned portable profile start as a usable
  Omarchy Quattro desktop on physical HDMI with the no-tiling adaptation?
- changed variable: active graphical session only — synchronize LightDM and
  `.dmrc` from `xfce` to `hyprland-uwsm`, then restart LightDM exactly once.
  Retain the A9 portable files, `AMD_DEBUG=notiling`, kernel, HDMI mode, VRAM,
  boot files, packages, network and storage unchanged
- expected evidence: a UWSM-owned Wayland session starts Hyprland and
  Quickshell from pinned commit `38542a1`; the Quattro bar is present only on
  the top edge; `Super+Space` opens the Omarchy menu; Foot opens; keyboard,
  mouse and HDMI remain usable; SSH survives; UART has no GPU reset, page
  fault, kernel panic, ext4 error or USB I/O error
- timeout: 5 minutes after the single LightDM restart
- rollback: after closing A10, synchronize the selectors to `xfce` and restart
  LightDM once in a separate bounded action. This returns to A7's clear Xorg
  ShadowFB recovery desktop without uninstalling the portable layer
- stop condition: no reboot, payload, package transaction, config edit,
  display tuning, damage-tracking change or retry in A10. If activation fails,
  record the visible state and close/review before rollback
- operator action: after the Omarchy desktop appears, move the mouse, press
  `Super+Space` once, then press `Super+Enter` once. Report whether the top bar,
  Omarchy menu and Foot terminal are visible and whether any corruption or
  stutter appears
- bounded UART context:
  [`20260813_210757_902706-exp-20260813-001-a10-start-uwsm-hyprland-with-omarchy-quattro-rc-01d04939.md`](../../ps4-uart/sessions/20260813_210757_902706-exp-20260813-001-a10-start-uwsm-hyprland-with-omarchy-quattro-rc-01d04939.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- selector evidence: the guarded helper synchronized LightDM and `.dmrc` to
  `hyprland-uwsm`, preserving the exact prior selectors under
  `/var/lib/omarchy-ps4/experiments/EXP-20260813-001-A10-20260813T150823Z`.
  Exactly one LightDM restart completed successfully
- result: fail at portable configuration, not at the compositor or hardware
  layer. UWSM started Hyprland PID 2096 on a Wayland seat with
  `AMD_DEBUG=notiling`; the operator confirmed visible Hyprland but reported
  errors. Quickshell did not start and no layer surfaces were present
- exact error: `hyprctl configerrors` reported
  `cannot open /usr/share/omarchy/default/hypr/bootstrap.lua`. The portable
  UWSM environment first selected the versioned runtime, then sourced upstream
  `default/bash/env-bootstrap`; that upstream production helper deliberately
  reset `OMARCHY_PATH` to `/usr/share/omarchy`. Hyprland therefore loaded the
  portable user config against a nonexistent system-package runtime
- UART conclusion: completed continuity across the single planned display
  restart. The legacy bridge ran its expected 1920x1080 split mode sequence;
  there was no GPU page fault, ring timeout, reset, kernel panic, ext4 error or
  USB I/O fault
- rollback: not yet applied. The failed Hyprland session remains running and
  reachable by SSH; no retry or config change occurred within A10
- next action: as A11, remove only the upstream `env-bootstrap` sourcing from
  the portable UWSM environment, validate the resolved path without restarting
  the active failed session, then close/review before A12

### EXP-20260813-001-A11 — preserve portable OMARCHY_PATH in UWSM

- state: complete — pass
- question: does removing the inappropriate upstream production bootstrap keep
  `OMARCHY_PATH` pinned to the user-owned portable release for the next UWSM
  session?
- changed variable: one installed user environment file only — replace
  `~/.local/share/omarchy-ps4/portable/config/38542a1f513740559660a468ffbf68ed082b2381/uwsm/env.d/10-omarchy-ps4`
  with the corrected candidate, SHA-256
  `9514700eb7f5eb23eda72074a2012ca7f5f3e7290bf1e53fb6b0a78cb1ee411d`.
  It retains the portable path, no-tiling, terminal and editor exports but no
  longer sources `default/bash/env-bootstrap`
- source evidence: the repository portable source is corrected, the bundle
  policy test now rejects `env-bootstrap`, and rebuilt RC2 archive SHA-256 is
  `f6cb86b168a9edf93309446773de8e9c176ccb99d8bf5dc90eb8c087a1dc74e5`.
  The exact A9 archive is preserved under
  `output/superseded/2026-08-13-portable-omarchy-path-reset/`
- expected evidence: the installed file matches the candidate hash; evaluating
  it in a clean shell resolves `OMARCHY_PATH` to the versioned portable
  `current` symlink and keeps the portable `bin` first in PATH; its manifest
  targets exist; the active failed Hyprland PID and LightDM session are not
  restarted; SSH and UART remain healthy
- timeout: 3 minutes
- rollback: preserve and restore the exact pre-A11 environment file. No
  LightDM restart or selector change belongs to A11
- stop condition: close and review after file and offline-environment
  validation. Do not reload Hyprland, start Quickshell or retry activation
- bounded UART context:
  [`20260813_211200_007233-exp-20260813-001-a11-preserve-portable-omarchy-path-in-uwsm-7651c403.md`](../../ps4-uart/sessions/20260813_211200_007233-exp-20260813-001-a11-preserve-portable-omarchy-path-in-uwsm-7651c403.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The installed UWSM file matches candidate SHA-256
  `9514700eb7f5eb23eda72074a2012ca7f5f3e7290bf1e53fb6b0a78cb1ee411d`.
  A clean-shell evaluation resolves `OMARCHY_PATH` to the versioned portable
  `current` symlink, prepends its `bin`, retains `AMD_DEBUG=notiling`, and finds
  both `default/hypr/bootstrap.lua` and `omarchy-launch-shell`
- preservation evidence: active failed Hyprland PID 2096 remained unchanged;
  Quickshell remained absent; no service, selector or session was restarted.
  The exact pre-A11 file and restoration command are stored under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A11-20260813T151200Z/`
- UART conclusion: completed continuity with three short SSH session
  lifecycles only; no display, GPU, filesystem or USB fault appeared
- rollback: not applied because offline validation passed
- next action: restart LightDM exactly once as A12, keeping the already selected
  `hyprland-uwsm` profile, then validate Quattro and collect the operator result

### EXP-20260813-001-A12 — restart corrected Omarchy Quattro session

- state: complete — degraded fail; Quattro runs but Hyprland config is incomplete
- question: does one fresh UWSM/Hyprland login with the corrected portable path
  load the complete Quattro shell without the A10 configuration error?
- changed variable: consume the corrected A11 environment in a fresh graphical
  session by restarting LightDM exactly once. Keep both selectors at
  `hyprland-uwsm` and retain every config, package, kernel, display, storage,
  network and boot value unchanged
- expected evidence: new Hyprland environment contains the portable
  `OMARCHY_PATH` and `AMD_DEBUG=notiling`; `hyprctl configerrors` is empty;
  Quickshell is alive and `omarchy-shell shell ping` returns `ok`; the bar is
  only on top; `Super+Space` opens the menu and `Super+Enter` opens Foot;
  keyboard, mouse and HDMI remain usable without severe corruption; UART has
  no GPU reset, page fault, kernel panic, ext4 error or USB I/O error
- timeout: 5 minutes after the single restart
- rollback: after closing A12, use the guarded selector helper to select
  `xfce`, then restart LightDM once in a separate bounded recovery action
- stop condition: no second restart, config edit, shell relaunch, package
  transaction, reboot, payload or display tuning in A12. Report the visible
  result and close/review before any recovery
- operator action: when the desktop settles, move the mouse, press
  `Super+Space` once, close the menu if necessary, then press `Super+Enter`
  once. Report top bar, menu, terminal, responsiveness and any visual artifact
- bounded UART context:
  [`20260813_211316_155171-exp-20260813-001-a12-restart-corrected-omarchy-quattro-session-480363d7.md`](../../ps4-uart/sessions/20260813_211316_155171-exp-20260813-001-a12-restart-corrected-omarchy-quattro-session-480363d7.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- environment result: pass. One LightDM restart started Hyprland PID 2562 with
  the corrected portable `OMARCHY_PATH`, portable-first PATH,
  `AMD_DEBUG=notiling`, and a Wayland session
- shell result: degraded pass. Two `omarchy-launch-shell` supervisors and two
  Quickshell processes appeared; `omarchy-shell shell ping` returned `ok`, and
  Hyprland exposed `omarchy-background` plus `omarchy-bar` layers. This proves
  the RC2 shell is running but duplicate startup is not accepted
- configuration result: fail. `hyprctl configerrors` reports module
  `default.hypr.apps.._1password` missing while `require_all.lua` processes the
  applications directory. Configuration evaluation stops before the complete
  bindings can be accepted, so the operator key test was deliberately withheld
- UART conclusion: completed continuity across exactly one restart with the
  expected 1920x1080 legacy bridge sequence. No GPU page fault, ring timeout,
  reset, kernel panic, ext4 error or USB I/O error appeared
- rollback: not applied. The running degraded Omarchy session remains reachable
  through SSH; no second restart, shell relaunch or config edit occurred
- next action: inspect only the live pinned application directory and startup
  registration as A13 to identify the exact unexpected filename and duplicate
  launch source before changing either

### EXP-20260813-001-A13 — identify Quattro Lua filename and duplicate startup

- state: complete — pass; AppleDouble contamination proven
- question: what exact live file produces module
  `default.hypr.apps.._1password`, and why are two Quickshell supervisors alive
  after one corrected session start?
- changed variable: none; read-only SSH inspection of the pinned portable
  application filenames, inode/type metadata, relevant manifest entries,
  Hyprland event/autostart registrations, process parents and user units
- expected evidence: identify the exact unexpected path and its provenance;
  identify whether duplicate launch comes from two config registrations, an
  XDG autostart unit, or a surviving process; keep Hyprland PID 2562 and both
  Quickshell processes unchanged; UART remains healthy
- timeout: 3 minutes
- rollback: none for read-only inspection
- stop condition: do not remove a file, stop a process, reload config, restart
  LightDM, press bindings or change any package/configuration in A13
- bounded UART context:
  [`20260813_211518_114848-exp-20260813-001-a13-identify-quattro-lua-filename-and-duplicate-3a39782b.md`](../../ps4-uart/sessions/20260813_211518_114848-exp-20260813-001-a13-identify-quattro-lua-filename-and-duplicate-3a39782b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The live pinned runtime contains 1,796 macOS AppleDouble
  `._*` files and the pinned configuration contains 77. In
  `default/hypr/apps`, every real Lua file has a 163-byte `._` companion,
  including the exact `._1password.lua` that `require_all.lua` converted to
  invalid module `default.hypr.apps.._1password`
- duplicate evidence: only `~/.config/hypr/autostart.lua` registers
  `omarchy-launch-shell`; there is no matching XDG autostart or user service.
  Both launcher supervisors are direct children of Hyprland PID 2562 and each
  owns one Quickshell child in the compositor cgroup. With configuration
  evaluation already failing, remove archive contamination before deciding
  whether the duplicate callback needs an independent fix
- source correction: portable archives are now created with macOS metadata
  disabled; the installer and bundle test reject any `._*` payload file. New
  archive SHA-256 is
  `34b389a6a713dcd25726d330056aee0adafaae842f545b75399e72cb6953c1e8`.
  An OrbStack Ubuntu extraction contained zero AppleDouble files and its
  payload manifest passed
- UART conclusion: completed continuity with two read-only SSH sessions only;
  no process, file, display or hardware state changed and no fault appeared
- rollback: none required
- next action: quarantine only the 1,873 live `._*` files into a reversible
  user-owned A14 backup without reloading or restarting the running session

### EXP-20260813-001-A14 — quarantine live AppleDouble metadata

- state: complete — pass
- question: can all archive-generated `._*` metadata be removed from the
  active pinned runtime/config while preserving every real Omarchy file and
  the running degraded session?
- changed variable: AppleDouble metadata presence only — move the 1,796 runtime
  and 77 configuration `._*` files, preserving relative paths, into
  `~/.local/state/omarchy-ps4/portable/EXP-20260813-001-A14-appledouble/`.
  Do not remove or rewrite any non-`._*` path
- expected evidence: active runtime and config contain zero `._*` files;
  exactly 1,873 files exist in the quarantine tree; real `1password.lua`,
  portable bootstrap, launcher and configs retain their pre-A14 hashes;
  Hyprland PID 2562 and the current Quickshell processes remain unchanged;
  SSH and UART stay healthy
- timeout: 4 minutes
- rollback: move each quarantined file back to its recorded relative path. No
  config reload or LightDM restart belongs to A14
- stop condition: do not stop duplicate processes, reload Hyprland, restart a
  service or test bindings in A14. Clean evaluation belongs to A15
- bounded UART context:
  [`20260813_211804_701146-exp-20260813-001-a14-quarantine-live-appledouble-metadata-948b0328.md`](../../ps4-uart/sessions/20260813_211804_701146-exp-20260813-001-a14-quarantine-live-appledouble-metadata-948b0328.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. Exactly 1,796 runtime and 77 configuration AppleDouble files
  moved into the user-owned quarantine, for 1,873 total. Zero `._*` files
  remain under either active pinned tree
- preservation evidence: SHA-256 controls for real `1password.lua`, Hyprland
  bootstrap, shell launcher, top-level PS4 Hyprland/autostart configuration and
  UWSM environment all passed after the move. Hyprland PID 2562 and both
  pre-existing launcher/Quickshell pairs remained unchanged; LightDM,
  NetworkManager and sshd remained active
- rollback: the exact relative path lists, files and control hashes are under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A14-appledouble/`;
  rollback was not applied
- UART conclusion: completed continuity with two short SSH sessions only; no
  display, process or hardware transition and no fault appeared
- next action: restart LightDM exactly once as A15 and require clean Hyprland
  configuration plus exactly one Quattro shell before the physical key test

### EXP-20260813-001-A15 — start metadata-clean Omarchy Quattro session

- state: complete — degraded fail; config clean, shell duplicated
- question: does one fresh session after AppleDouble quarantine fully evaluate
  the Omarchy Lua configuration and start exactly one usable Quattro shell?
- changed variable: consume the metadata-clean A14 runtime in a fresh session
  by restarting LightDM exactly once. Keep selectors, portable path, no-tiling,
  every real file, package, kernel, mode, storage, network and boot value fixed
- expected evidence: `hyprctl configerrors` is empty; one Hyprland and exactly
  one `omarchy-launch-shell` plus Quickshell pair run; shell IPC returns `ok`;
  only top bar/background layers exist; `Super+Space` opens the Omarchy menu;
  `Super+Enter` opens Foot; mouse/keyboard and HDMI are responsive without
  severe corruption; UART has no GPU reset, page fault, panic, ext4 or USB error
- timeout: 5 minutes after the single restart
- rollback: after closing A15, synchronize selectors to `xfce` and restart
  LightDM once in a separate bounded recovery action if the session is unusable
- stop condition: no retry, config edit, process kill, shell relaunch, package
  transaction, reboot, payload or display tuning in A15
- operator action: after the desktop settles, move the mouse; press
  `Super+Space` once; close the menu if needed; press `Super+Enter` once. Report
  the top bar, menu, terminal, responsiveness and any visual artifact
- bounded UART context:
  [`20260813_211925_392491-exp-20260813-001-a15-start-metadata-clean-omarchy-quattro-sessio-151dc027.md`](../../ps4-uart/sessions/20260813_211925_392491-exp-20260813-001-a15-start-metadata-clean-omarchy-quattro-sessio-151dc027.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- configuration result: pass. One LightDM restart produced Hyprland PID 10241
  with portable `OMARCHY_PATH`, `AMD_DEBUG=notiling`, and no output from
  `hyprctl configerrors`. AppleDouble quarantine therefore resolved the Lua
  module failure
- shell result: degraded fail. Shell IPC returned `ok` and bar/background
  layers exist, but Hyprland started two launcher supervisors and two
  Quickshell children again. The physical key test was withheld because the
  acceptance criterion requires one shell owner
- cause: pinned `default.hypr.omarchy` already requires the PS4-overridden
  `default.hypr.autostart`; the PS4 top-level config also required the same file
  through module name `hypr.autostart`, registering its callback a second time
- UART conclusion: completed continuity across exactly one display restart,
  with the expected legacy bridge sequence and no GPU page fault, ring timeout,
  reset, kernel panic, ext4 error or USB fault
- rollback: not applied. The clean but duplicate-shell session remains active;
  no process was stopped and no retry occurred
- next action: remove only the redundant top-level `require("hypr.autostart")`
  as A16 without reloading, then restart once as A17

### EXP-20260813-001-A16 — remove duplicate PS4 autostart registration

- state: complete — pass
- question: does removing the redundant top-level autostart import leave
  exactly one PS4-safe shell launch registration for the next session?
- changed variable: one installed user config file only — replace the pinned
  `config/.../hypr/hyprland.lua` with candidate SHA-256
  `ad14354d524a24c74ac590a6143b0f53b88792474dbb5dce5badb5fdc0176fc6`,
  removing only `require("hypr.autostart")`. The PS4-overridden upstream
  default autostart remains unchanged and still launches the shell once
- source evidence: repository source and bundle regression test now reject the
  redundant import; rebuilt archive SHA-256 is
  `f270f2933791ddc04fe29ccca845f943448becdbe80e1981cbd281968d1f00ef`
- expected evidence: installed hash matches; the top-level config has no local
  autostart import; default autostart contains one shell launch; current
  Hyprland PID 10241 and its two existing shells remain untouched; UART/SSH are
  healthy
- timeout: 3 minutes
- rollback: preserve and restore the exact pre-A16 `hyprland.lua`; no reload,
  process stop or LightDM restart belongs to A16
- stop condition: close/review after offline validation. A fresh session and
  process-count test belong only to A17
- bounded UART context:
  [`20260813_212132_538031-exp-20260813-001-a16-remove-duplicate-ps4-autostart-registration-112a8859.md`](../../ps4-uart/sessions/20260813_212132_538031-exp-20260813-001-a16-remove-duplicate-ps4-autostart-registration-112a8859.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. Installed `hyprland.lua` matches candidate SHA-256
  `ad14354d524a24c74ac590a6143b0f53b88792474dbb5dce5badb5fdc0176fc6`,
  contains no `require("hypr.autostart")`, and the PS4-overridden default
  autostart contains exactly one `omarchy-launch-shell` invocation
- preservation evidence: Hyprland PID 10241 and the two already-running shell
  pairs remained unchanged. The exact previous file and restoration command
  are stored under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A16-20260813T152132Z/`
- UART conclusion: completed continuity with one SSH lifecycle only; no
  display, process or hardware transition and no fault appeared
- rollback: not applied because offline validation passed
- next action: restart LightDM once as A17 and require one clean shell owner
  plus successful physical Omarchy keybindings

### EXP-20260813-001-A17 — launch single-shell Omarchy Quattro desktop

- state: complete — degraded pass; usable Omarchy Quattro POC
- question: does one fresh session with the corrected portable path,
  metadata-clean payload and single autostart registration deliver the usable
  Omarchy Quattro POC?
- changed variable: consume the accepted A11/A14/A16 corrections in a new
  session by restarting LightDM exactly once. Keep selectors, all files,
  no-tiling, packages, kernel, mode, storage, network and boot values unchanged
- expected evidence: one Hyprland, one shell supervisor and one Quickshell;
  empty `hyprctl configerrors`; shell IPC `ok`; top-only bar and background;
  `Super+Space` opens the Omarchy menu; `Super+Enter` opens Foot; input and HDMI
  are responsive without severe corruption; UART contains no GPU reset, page
  fault, panic, ext4 or USB error
- timeout: 5 minutes after the single restart
- rollback: after closing A17, synchronize selectors to `xfce` and restart
  LightDM once in a separately bounded recovery action if required
- stop condition: no retry, config edit, process manipulation, package action,
  reboot, payload or display tuning in A17
- operator action: after I confirm clean remote state, move the mouse, press
  `Super+Space` once, close the menu if necessary, then press `Super+Enter`
  once. Report bar, menu, Foot, responsiveness and any visible artifact
- bounded UART context:
  [`20260813_212230_112029-exp-20260813-001-a17-launch-single-shell-omarchy-quattro-desktop-781a48a2.md`](../../ps4-uart/sessions/20260813_212230_112029-exp-20260813-001-a17-launch-single-shell-omarchy-quattro-desktop-781a48a2.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- remote result: pass. Exactly one Hyprland PID 12035, one
  `omarchy-launch-shell`, and one Quickshell run. `hyprctl configerrors` is
  empty; shell IPC returns `ok`; `omarchy-background` and `omarchy-bar` are the
  active shell layers; portable path, Wayland and `AMD_DEBUG=notiling` are
  present; LightDM, NetworkManager and sshd remain active
- operator result: degraded pass. Mouse input works, `Super+Space` opens the
  Omarchy menu, and `Super+Enter` opens the terminal. The operator reports a
  little stutter on the menu border, the leftmost Omarchy bar icon is missing,
  and the 1080p UI should be scaled slightly larger
- UART conclusion: completed continuity across exactly one display restart and
  the physical input test. The expected legacy bridge sequence appeared with
  no GPU page fault, ring timeout, reset, kernel panic, ext4 error or USB fault
- rollback: not applied. The accepted degraded Omarchy POC remains running
- next action: perform read-only A18 inspection of actual monitor scale,
  Omarchy icon-font availability, shell logs and terminal resolution before
  changing one UX variable at a time

### EXP-20260813-001-A18 — diagnose scale, missing bar icon and terminal choice

- state: complete — pass; all three UX causes identified
- question: are the small UI and missing leftmost icon explained by scale 1.0
  and the portable install not registering `omarchy.ttf`, and what terminal
  does pinned Quattro RC2 resolve on this root?
- changed variable: none; read-only SSH inspection of Hyprland monitor JSON,
  fontconfig matches and files, Quickshell warnings, `xdg-terminal-exec`
  preference/resolution, installed terminal commands and current processes
- expected evidence: exact active scale and logical size; whether font family
  `omarchy` and private glyph U+E900 resolve; exact missing/present font path;
  exact pinned/default terminal resolution; no process, config or service
  changes; UART remains healthy
- timeout: 3 minutes
- rollback: none for read-only inspection
- stop condition: do not install a font or terminal, rebuild font cache, change
  scale, restart/reload Quickshell or Hyprland, or open another application
- bounded UART context:
  [`20260813_212741_924505-exp-20260813-001-a18-diagnose-scale-missing-bar-icon-and-termina-761bc488.md`](../../ps4-uart/sessions/20260813_212741_924505-exp-20260813-001-a18-diagnose-scale-missing-bar-icon-and-termina-761bc488.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- scale result: Hyprland reports HDMI-A-1 at 1920x1080/60 with scale exactly
  `1.0`, explaining the requested larger UI
- font result: `/usr/share/fonts/omarchy/omarchy.ttf` and the user font path are
  absent. The portable runtime contains the valid font family `omarchy` with
  charset U+E900–E905, but fontconfig does not index it and maps family
  `omarchy` to Noto Sans. The bar requests U+E900 from family `omarchy`, exactly
  explaining the blank leftmost logo
- terminal result: pinned Quattro RC2 uses `xdg-terminal-exec` and ships
  `foot.desktop` first in its Hyprland preference list. Only Foot is installed
  among Foot/Ghostty/Kitty/Alacritty. The portable installer did not activate
  that list, however, so live `xdg-terminal-exec --print-id` resolves the older
  XFCE fallback while the session `TERMINAL` separately reads `foot`
- menu result: no GPU/reset/render failure was logged during the physical menu
  test. The slight border stutter remains a degraded legacy-rendering symptom
  to measure after icon and scale are corrected
- UART conclusion: completed continuity with two read-only SSH sessions only;
  no display, process, configuration or hardware state changed
- rollback: none required
- next action: register the portable Omarchy font in the user font hierarchy as
  A19 without restarting the shell, then restart only Quickshell as A20

### EXP-20260813-001-A19 — register portable Omarchy icon font

- state: complete — pass
- question: does registering the pinned `omarchy.ttf` in the user font
  hierarchy make family `omarchy` and glyph U+E900 resolvable without changing
  the running shell?
- changed variable: user font registration only — create
  `~/.local/share/fonts/omarchy-ps4/omarchy.ttf` as a symlink to the pinned
  portable runtime font, then refresh only the user font cache. Do not restart
  or signal Quickshell/Hyprland
- source evidence: the portable installer, rollback and preflight now own font
  registration/cache handling; bundle tests enforce it. Rebuilt portable RC2
  archive SHA-256 is
  `7121ad73038e9b737264fc6dfc94254ded606b59a3bcdb3aa9ba30962672c4b1`
- expected evidence: symlink resolves to the pinned font; `fc-match omarchy`
  selects it; `fc-query` contains U+E900–E905; Hyprland PID 12035 and
  Quickshell remain unchanged; UART/SSH stay healthy
- timeout: 3 minutes
- rollback: remove the new symlink, restore any pre-existing path captured by
  A19, and refresh the user font cache. No shell restart belongs to rollback
- stop condition: do not restart/reload a process, change scale or terminal, or
  test the visible icon in A19. Visibility belongs to A20
- bounded UART context:
  [`20260813_213108_340982-exp-20260813-001-a19-register-portable-omarchy-icon-font-adfbbda8.md`](../../ps4-uart/sessions/20260813_213108_340982-exp-20260813-001-a19-register-portable-omarchy-icon-font-adfbbda8.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The user font path now symlinks to the pinned Quattro runtime
  font. `fc-match omarchy` selects that user path and reports family
  `omarchy`; `fc-query` reports charset U+E900–E905
- preservation evidence: Hyprland PID 12035 and Quickshell PID 12117 remained
  unchanged. No process or service was restarted. Exact pre-A19 path state and
  rollback data are preserved under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A19-20260813T153108Z/`
- UART conclusion: completed continuity with two short SSH sessions only; no
  display transition or hardware fault appeared
- rollback: not applied because font registration and resolution passed
- next action: restart only the Omarchy Quickshell process as A20 and require
  the leftmost bar icon to render while Hyprland stays unchanged

### EXP-20260813-001-A20 — reload Quattro shell with registered icon font

- state: complete — degraded pass
- question: does one Quattro shell-only restart consume the registered
  `omarchy.ttf` and render the missing leftmost bar icon without disturbing
  Hyprland or HDMI?
- changed variable: Quickshell process generation only — invoke the pinned
  `omarchy-restart-shell` once. Do not reload/restart Hyprland or LightDM,
  change monitor scale, terminal preference, package state or configuration
- expected evidence: Hyprland PID 12035 remains; Quickshell PID 12117 is
  replaced by exactly one new process; shell IPC returns `ok`; Hyprland
  config errors remain empty; top bar/background layers return; the operator
  sees the Omarchy icon at the far left and `Super+Space` still opens the menu;
  UART has no GPU reset, page fault, panic, ext4 or USB error
- timeout: 3 minutes
- rollback: if the shell does not return, close A20 and launch one pinned shell
  in a separate bounded recovery action. Do not repeat the restart in A20
- stop condition: no scale, terminal, package, config or display-manager change
  belongs to A20
- operator action: after I confirm the replacement shell is healthy, inspect
  the far-left bar icon and press `Super+Space` once; report icon, menu and any
  visible corruption or stutter
- bounded UART context:
  [`20260813_213401_454905-exp-20260813-001-a20-reload-quattro-shell-with-registered-icon-f-60b7f12f.md`](../../ps4-uart/sessions/20260813_213401_454905-exp-20260813-001-a20-reload-quattro-shell-with-registered-icon-f-60b7f12f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- remote result: pass. Hyprland remained PID 12035; the old Quickshell PID
  12117 was replaced by PID 16310; exactly one Quickshell runs; shell IPC
  returns `ok`; config errors are empty; and only the expected
  `omarchy-background` and `omarchy-bar` layers returned
- operator result: degraded pass. The far-left Omarchy icon now renders,
  proving the registered font fix. The menu border still stutters, so that
  rendering symptom is independent of the missing font
- UART conclusion: completed continuity across one shell-only restart and the
  physical menu test. No GPU reset, page fault, kernel panic, ext4 or USB fault
  appeared
- rollback: not applied because the shell and icon are healthy
- next action: perform read-only A21 inspection of the actual terminal process,
  terminal decoration path and installed-versus-portable Quattro/theme surface
  before changing terminal or display configuration

### EXP-20260813-001-A21 — inspect terminal chrome and portable theme coverage

- state: complete — pass
- question: which terminal is actually open, what creates its top pane/title
  chrome, and how much of pinned Quattro RC2—including themes—is present in the
  portable POC versus a full Omarchy system install?
- changed variable: none; read-only source and SSH inspection of terminal
  processes, desktop-terminal resolution, Foot configuration, active clients,
  portable theme assets and full-profile/package manifests
- expected evidence: exact running terminal executable/app class; exact
  terminal preference and relevant decoration setting; counts/names of bundled
  themes; explicit list of full-system parts not installed by the portable POC;
  Hyprland PID 12035 and Quickshell PID 16310 unchanged
- timeout: 4 minutes
- rollback: none for read-only inspection
- stop condition: do not close/open a terminal, edit a preference, hide a
  titlebar, change theme/scale, restart a process or install a package in A21
- bounded UART context:
  [`20260813_213714_797444-exp-20260813-001-a21-inspect-terminal-chrome-and-portable-theme--78077b9e.md`](../../ps4-uart/sessions/20260813_213714_797444-exp-20260813-001-a21-inspect-terminal-chrome-and-portable-theme--78077b9e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- terminal result: the only terminal client/process is PID 17255
  `xfce4-terminal`; live `xdg-terminal-exec --print-id` resolves
  `xfce4-terminal.desktop`. The user has no XDG terminal preference file and
  no Foot config. The visible top pane is therefore XFCE Terminal's GTK
  header/chrome, not Foot
- theme result: all 22 pinned Quattro RC2 theme asset directories exist in the
  portable runtime, but `~/.local/state/omarchy/current/theme.name` is absent,
  so no managed Omarchy theme has been initialized on this root
- installation result: this is the complete portable Quattro UX, not the full
  workstation. Of the generated 153-package PS4-safe full profile, 100 package
  names remain absent. The missing surface includes compilers/editor tools,
  Chromium, LibreOffice, OBS, Kdenlive, Obsidian, Docker and other optional
  workstation applications/services
- rendering clue: pinned Quattro enables an animated Hyprland border at speed
  5.39. This is a source-backed candidate for the remaining border-only
  stutter, but A21 did not change or test it
- preservation evidence: Hyprland PID 12035 and Quickshell PID 16310 remained
  unchanged; no window, configuration, package or service changed
- UART conclusion: completed continuity with two read-only SSH sessions only;
  no hardware transition or fault appeared
- rollback: none required
- next action: activate only Quattro's XDG terminal preference as A22 so the
  next explicit terminal launch resolves Foot; theme initialization and border
  animation remain separate experiments

### EXP-20260813-001-A22 — select Foot through Quattro terminal preference

- state: complete — pass
- question: does activating pinned Quattro's Hyprland XDG terminal preference
  make terminal launches resolve Foot without closing the current XFCE
  Terminal or changing the compositor?
- changed variable: one user preference path only — create
  `~/.config/hyprland-xdg-terminals.list` as a symlink to the pinned portable
  runtime's list, whose first executable entry is `foot.desktop`. Do not alter
  Foot configuration, current theme, bindings, windows or processes
- source evidence: the portable installer/build/test now own and validate this
  preference path. Rebuilt portable RC2 archive SHA-256 is
  `08b6f07a6c1137bc1fe9a8a60cba444a819bd06aec8bb3791b70b6a69ac2e856`
- expected evidence: the symlink resolves into commit
  `38542a1f513740559660a468ffbf68ed082b2381`; its first executable entry is
  `foot.desktop`; `xdg-terminal-exec --print-id` returns `foot.desktop`;
  XFCE Terminal PID 17255, Hyprland PID 12035 and Quickshell PID 16310 remain
  unchanged
- timeout: 3 minutes
- rollback: remove the symlink and restore any pre-existing path recorded by
  A22. No process restart or terminal launch belongs to rollback
- stop condition: do not launch/close a terminal, initialize a theme, edit Foot
  config, tune borders/scale or restart a process in A22
- bounded UART context:
  [`20260813_213939_318812-exp-20260813-001-a22-select-foot-through-quattro-terminal-prefer-34be4218.md`](../../ps4-uart/sessions/20260813_213939_318812-exp-20260813-001-a22-select-foot-through-quattro-terminal-prefer-34be4218.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The new preference symlink resolves into the pinned commit and
  selects `foot.desktop` first. SSH has no desktop identity and therefore still
  reports the legacy fallback, but the authoritative user-manager environment
  is `XDG_CURRENT_DESKTOP=Hyprland`, `XDG_SESSION_TYPE=wayland`; under that
  exact environment `xdg-terminal-exec --print-id` returns `foot.desktop`
- preservation evidence: the existing XFCE Terminal PID 17255, Hyprland PID
  12035 and Quickshell PID 16310 remained unchanged. Pre-A22 path state and
  rollback data are under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A22-20260813T154200Z/`
- UART conclusion: completed continuity with two SSH sessions only; no window,
  process or hardware transition and no fault appeared
- rollback: not applied because session-context terminal resolution passed
- next action: launch exactly one terminal with `Super+Enter` as A23 and verify
  Foot plus removal of XFCE's top chrome

### EXP-20260813-001-A23 — accept Foot terminal launch

- state: complete — degraded pass
- question: does one `Super+Enter` launch create a native Foot window without
  XFCE Terminal's GTK top pane while preserving the running Quattro session?
- changed variable: one new terminal window only — the operator presses
  `Super+Enter` once. Do not close the existing XFCE Terminal or change any
  config, theme, scale, border or process manually
- expected evidence: one `foot` client/process appears; no second XFCE Terminal
  process appears; Hyprland PID 12035 and Quickshell PID 16310 remain; the
  operator sees a usable terminal without the unwanted top pane and reports
  any artifact/stutter
- timeout: 3 minutes
- rollback: close the new Foot window after A23 if it is unusable. The existing
  XFCE Terminal remains available throughout
- stop condition: no second launch, terminal config edit, theme selection,
  border/scale tuning or process restart belongs to A23
- operator action: press `Super+Enter` exactly once, then report whether Foot
  opens and whether the top pane is gone
- bounded UART context:
  [`20260813_214039_347341-exp-20260813-001-a23-accept-foot-terminal-launch-e92d837d.md`](../../ps4-uart/sessions/20260813_214039_347341-exp-20260813-001-a23-accept-foot-terminal-launch-e92d837d.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- terminal result: pass. One native Wayland Foot process/client appeared as PID
  17587 with class and initial class `foot`. The original XFCE Terminal remains
  PID 17255; no second XFCE Terminal appeared. Hyprland PID 12035 and
  Quickshell PID 16310 remain unchanged; config errors are empty
- operator result: degraded pass. The operator recognized a different terminal
  application and additionally reported that `Super+Space` still produces a
  border artifact. The new application is confirmed remotely as Foot. Exact
  removal of the former top pane was not explicitly classified by the operator
- correction to A21 hypothesis: the PS4 profile loads after upstream
  look-and-feel and sets global animations disabled. The upstream animated
  border declaration alone is therefore not sufficient to explain the live
  artifact; effective live options and Quickshell menu styling must be checked
- UART conclusion: completed continuity across the terminal launch and menu
  observation; only a short SSH lifecycle appeared, with no hardware fault
- rollback: not applied. Foot and the original XFCE Terminal remain open
- next action: inspect effective animation/border options and Quickshell menu
  styling read-only as A24 before changing one rendering variable

### EXP-20260813-001-A24 — diagnose remaining menu-border artifact

- state: complete — pass; one live candidate isolated
- question: is the `Super+Space` artifact produced by an effective Hyprland
  animation/gradient window border or by the Quickshell menu's own border and
  transition styling?
- changed variable: none; read-only SSH inspection of effective Hyprland
  options, active clients/layers, Quickshell logs and pinned menu QML/style
- expected evidence: effective global/border animation state and active border
  color; exact menu border/transition implementation; relevant shell warnings;
  Hyprland PID 12035, Quickshell PID 16310 and Foot PID 17587 unchanged
- timeout: 4 minutes
- rollback: none for read-only inspection
- stop condition: do not open/close the menu or a terminal, change theme,
  border, animation, scale or config, or restart any process in A24
- bounded UART context:
  [`20260813_214224_217032-exp-20260813-001-a24-diagnose-remaining-menu-border-artifact-576c143a.md`](../../ps4-uart/sessions/20260813_214224_217032-exp-20260813-001-a24-diagnose-remaining-menu-border-artifact-576c143a.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- effective compositor result: global animations are false; blur and shadows
  are false; border width is 2. The active border remains the two-color
  gradient `ee33ccff ee00ff99 45deg`; the inactive border is solid
- shell result: the open `omarchy-menu` is a layer surface. Because no managed
  theme has been initialized, its current menu border falls back to a uniform
  color/width and takes Quickshell's native `Rectangle.border` path, not its
  gradient `QtQuick.Shapes` overlay. The journal contains no rendering failure
- conclusion: the live two-color Hyprland active-window gradient is the only
  remaining gradient border effect established around the focused terminal
  during the observed menu state. Replacing it temporarily with one of its
  existing colors is the smallest evidence-backed comparison
- preservation evidence: Hyprland PID 12035, Quickshell PID 16310 and Foot PID
  17587 remained unchanged. No live option, config, window or process changed
- UART conclusion: completed continuity with one read-only SSH session only;
  no hardware fault appeared
- rollback: none required
- next action: replace only the live active-border gradient with its first
  solid color as A25, then ask for one `Super+Space` comparison

### EXP-20260813-001-A25 — test solid active border

- state: complete — fail for hypothesis; diagnostic pass
- question: does replacing the active-window two-color gradient with its first
  solid color remove the `Super+Space` border artifact on the PS4 display path?
- changed variable: effective `general:col.active_border` only — set it live
  from `rgba(33ccffee) rgba(00ff99ee) 45deg` to `rgba(33ccffee)` with one
  `hyprctl keyword`. Do not reload Hyprland or change width, animation, shell,
  theme, scale, terminal or any file
- expected evidence: effective active border becomes the single color;
  Hyprland PID 12035, Quickshell PID 16310 and Foot PID 17587 remain; the
  operator opens/closes `Super+Space` once and reports whether the border
  artifact is gone, reduced or unchanged; UART has no GPU or kernel fault
- timeout: 3 minutes
- rollback: restore the exact two-color 45-degree gradient with one
  `hyprctl keyword` after closing A25 if the comparison fails. Durable source
  changes belong only after acceptance
- stop condition: no retry, second option, config edit, reload, restart, theme
  selection or scale change belongs to A25
- operator action: after I confirm the single-color live option, press
  `Super+Space` once, observe the border, then close it once and report
- bounded UART context:
  [`20260813_214339_392630-exp-20260813-001-a25-test-solid-active-border-20408df7.md`](../../ps4-uart/sessions/20260813_214339_392630-exp-20260813-001-a25-test-solid-active-border-20408df7.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- setter evidence: legacy `hyprctl keyword` was rejected by the Lua parser and
  changed nothing. The required `hyprctl eval` then changed only the effective
  active border from `ee33ccff ee00ff99 45deg` to solid `ee33ccff 0deg`;
  Hyprland PID 12035, Quickshell PID 16310 and Foot PID 17587 remained
- operator result: the supplied photograph shows a clean cyan Hyprland window
  border behind the menu, while the broken/stuttering white rectangle is the
  Quickshell menu card border. The artifact therefore remains and is not caused
  by the Hyprland active-border gradient
- conclusion: fail for the gradient hypothesis, pass for isolating the affected
  surface as Quickshell's menu card. Do not carry the solid active border into
  the image
- UART conclusion: completed continuity across one effective border change and
  physical menu observation; no GPU reset, page fault or kernel fault appeared
- rollback: required. Restore the exact original gradient as A26 before testing
  a menu-only change
- next action: restore the original gradient as A26, then inspect/test only the
  Quickshell menu card border path

### EXP-20260813-001-A26 — restore accepted Hyprland gradient

- state: complete — pass
- question: can the rejected A25 comparison be rolled back exactly without
  changing the shell or display session?
- changed variable: effective `general:col.active_border` only — restore
  `rgba(33ccffee) rgba(00ff99ee) 45deg` with one Lua `hyprctl eval`
- expected evidence: effective gradient returns to
  `ee33ccff ee00ff99 45deg`; Hyprland PID 12035, Quickshell PID 16310 and Foot
  PID 17587 remain; config errors stay empty
- timeout: 2 minutes
- rollback: if the exact value cannot be restored, stop and keep the current
  session unchanged; do not reload Hyprland
- stop condition: no menu action, shell/style/config edit, restart, theme or
  scale change belongs to A26
- bounded UART context:
  [`20260813_214717_329740-exp-20260813-001-a26-restore-accepted-hyprland-gradient-52ee823c.md`](../../ps4-uart/sessions/20260813_214717_329740-exp-20260813-001-a26-restore-accepted-hyprland-gradient-52ee823c.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The parser rejected a gradient string and changed nothing; the
  source-form Lua table then restored the effective value exactly to
  `ee33ccff ee00ff99 45deg`
- preservation evidence: Hyprland PID 12035, Quickshell PID 16310 and Foot PID
  17587 remained unchanged; config errors are empty
- UART conclusion: completed continuity across the exact rollback with no
  display restart or hardware fault
- rollback: complete; A25's solid comparison value is no longer active
- next action: isolate a menu-card-only style override without touching the
  accepted Hyprland border

### EXP-20260813-001-A27 — disable only the PS4 menu-card border

- state: complete — degraded pass; affected renderer isolated
- question: does setting only Quickshell `[menu] border-width = 0` remove the
  photographed broken white rectangle while leaving menu content and the
  accepted Hyprland window border intact?
- changed variable: one watched user shell-style file only — create
  `~/.config/omarchy/shell.toml` containing only the `[menu]` section and
  `border-width = 0`. Do not restart/reload Quickshell or Hyprland and do not
  change theme, other surface borders, scale, terminal or packages
- source evidence: `packages/omarchy-ps4-settings/ps4-shell.toml` now owns the
  candidate for both the native settings package and portable bundle; tests
  require it. Rebuilt portable RC2 archive SHA-256 is
  `8757cdcc35e3a4d88d5501b6df4afa2e6b1bc2e7217dd47e0e7fe9dba2ace359`
- expected evidence: the exact file is present and Quickshell remains PID
  16310 with IPC `ok`; Hyprland remains PID 12035 with the original gradient;
  Foot remains PID 17587; the operator toggles `Super+Space` once and reports
  whether the white broken menu border is gone while content remains usable
- timeout: 3 minutes
- rollback: remove the new file or restore its exact pre-A27 copy; the watched
  path should revert live. Do not restart a process
- stop condition: no retry, second style token, theme initialization, scale,
  config reload or process restart belongs to A27
- operator action: after I confirm the override was consumed, press
  `Super+Space` once, inspect the menu card, close it once and report
- bounded UART context:
  [`20260813_214936_454435-exp-20260813-001-a27-disable-only-the-ps4-menu-card-border-6abe281b.md`](../../ps4-uart/sessions/20260813_214936_454435-exp-20260813-001-a27-disable-only-the-ps4-menu-card-border-6abe281b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- remote result: pass. The exact candidate SHA-256
  `17bbef67e36d1c444194526fbd13044ef5d5159aad0410e0cddc98b612b40a46`
  was consumed through Quickshell's watched user style path without restart.
  Hyprland PID 12035 kept the original gradient, Quickshell PID 16310 and Foot
  PID 17587 remained, shell IPC returned `ok`, and config errors stayed empty
- operator result: degraded pass. The broken menu rectangle disappeared when
  the menu border was disabled, proving the affected renderer/surface. The
  menu consequently has no visible outer outline, so width zero is diagnostic
  evidence rather than the final UX
- unrelated interruption: the operator accidentally enabled FreeSync in the
  monitor and reported display loss. Post-A27 Linux inspection reports
  `vrr=false`, `misc:vrr=0`, HDMI connected/enabled, DPMS on and the sole
  1920x1080@60 mode still active. This points to the monitor OSD setting rather
  than a Linux VRR transition
- UART conclusion: completed continuity. No GPU reset, page fault, kernel,
  ext4 or USB fault appeared
- rollback: the original Hyprland gradient is intact. The menu width-zero
  candidate remains active for later refinement; display recovery takes
  priority
- next action: turn off monitor-side FreeSync/Adaptive Sync only as A28

### EXP-20260813-001-A28 — disable monitor-side FreeSync

- state: complete — inconclusive
- question: does returning the monitor's own FreeSync/Adaptive Sync setting to
  off restore the already-active fixed 1920x1080@60 PS4 Linux signal?
- changed variable: monitor OSD FreeSync/Adaptive Sync only — operator uses the
  monitor's physical controls to set it off. Do not change a Linux option,
  toggle DPMS, unplug HDMI, restart Hyprland/LightDM or power-cycle the PS4
- expected evidence: picture returns or remains stable; Linux continues to
  report `vrr=false`, HDMI connected/enabled, DPMS on and 1920x1080@60;
  operator reports the monitor OSD result; UART has no GPU or kernel fault
- timeout: 3 minutes
- rollback: none; VRR is unsupported on this PS4 legacy display path and must
  stay off. If the picture does not return, close A28 and test a monitor-only
  power cycle as a separate recovery action
- stop condition: no Linux display command, gamma, brightness, menu-border,
  scale, cable or process change belongs to A28
- operator action: open the monitor's physical OSD, find Gaming/FreeSync or
  Adaptive Sync, set it to Off, exit the OSD, and report whether HDMI returns
- bounded UART context:
  [`20260813_215832_904718-exp-20260813-001-a28-disable-monitor-side-freesync-a9ac5139.md`](../../ps4-uart/sessions/20260813_215832_904718-exp-20260813-001-a28-disable-monitor-side-freesync-a9ac5139.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: inconclusive. No operator report confirmed the final OSD value or
  picture state before a reboot was requested. The bounded UART slice contains
  only Wi-Fi roaming/key traffic and no DRM, GPU or kernel fault
- post-session evidence: SSH remains reachable, systemd reports `running`, and
  `/` is still external `/dev/sda2` labelled `OMARCHY-PS4`
- rollback: none; Linux already reported VRR false before A28
- next action: perform one requested clean Linux reboot as A29; this is new
  evidence, not a repetition of the monitor-only A28 action

### EXP-20260813-001-A29 — clean Linux reboot after monitor VRR incident

- state: complete — pass; returned cleanly to Orbis boundary
- question: does one clean systemd reboot return this accepted external-root
  session and fixed 1080p60 display after the monitor FreeSync incident?
- changed variable: one `sudo systemctl reboot` over SSH only. Keep USB, HDMI,
  boot files, monitor settings and PS4 power state untouched
- expected evidence: orderly shutdown on UART followed by either a new Linux
  boot or a clear stop at the PS4 loader boundary; if Linux returns, external
  `OMARCHY-PS4` root, network, HDMI 1920x1080@60, VRR false and session state
  can be revalidated; operator reports the visible display result
- timeout: 5 minutes
- rollback: no second reboot. If PS4 Linux cannot self-return through its loader
  boundary, close A29 and request the exact GoldHEN/payload action in a new
  bounded session
- stop condition: no payload, power cycle, cable, OSD, gamma, border or config
  change belongs to A29
- operator action: none until UART establishes whether the reboot returns to
  Linux or to the Orbis/loader boundary
- bounded UART context:
  [`20260813_220701_857603-exp-20260813-001-a29-clean-linux-reboot-after-monitor-vrr-incide-b300cdf4.md`](../../ps4-uart/sessions/20260813_220701_857603-exp-20260813-001-a29-clean-linux-reboot-after-monitor-vrr-incide-b300cdf4.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The requested reboot stopped the graphical/user services,
  synchronized and unmounted every filesystem, detached device-mapper/loop
  state, reached `System Reboot`, and emitted `reboot: Restarting system`
- boundary result: the PS4 returned to Orbis rather than automatically loading
  Linux, as expected for this payload/kexec boot chain. SSH did not return in
  the bounded window; the operator then reported GoldHEN loaded
- UART conclusion: completed continuity across orderly Linux shutdown and the
  Orbis return. No unmount failure, ext4 fault or GPU reset appeared
- rollback: none required; external USB was cleanly unmounted
- next action: after source-owning the PS4 no-idle default, send the unchanged
  pinned Linux loader once through the newly loaded GoldHEN PayLoader as A30

### EXP-20260813-001-A30 — boot Linux after clean Orbis return

- state: complete — pass
- question: does one unchanged pinned loader send return the accepted external
  USB Linux/Quattro root after the clean A29 reboot?
- changed variable: one complete send of pinned v25 `linux-1024mb.elf` to
  GoldHEN PayLoader `192.168.50.215:9090`, with no prior connection/probe. Do
  not change the USB, boot files, VRAM, monitor, payload or PS4 power state
- expected evidence: PayLoader accepts exactly one ELF, loader/kexec enters
  Linux 6.18.44, initramfs finds `LABEL=OMARCHY-PS4`, systemd reaches the
  graphical root, network/SSH returns at `192.168.50.125`, and the operator
  reports fixed 1080p60 picture state; UART has no ext4, USB, GPU reset or panic
- timeout: 5 minutes
- rollback: no second payload. If PayLoader refuses before acceptance, close
  A30 and restore PayLoader in a separate action; if Linux fails after
  acceptance, preserve the exact UART result and return to Orbis separately
- stop condition: exactly one payload connection; no readiness probe, reboot,
  OSD, gamma, border, config or package change belongs to A30
- operator action: none until remote/UART establishes Linux state; then report
  the visible HDMI result
- bounded UART context:
  [`20260813_221230_596648-exp-20260813-001-a30-boot-linux-after-clean-orbis-return-cf42d0c6.md`](../../ps4-uart/sessions/20260813_221230_596648-exp-20260813-001-a30-boot-linux-after-clean-orbis-return-cf42d0c6.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- payload result: pass. One connection sent exactly 320,936 bytes of the pinned
  v25 ELF with SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`;
  no readiness probe or second send occurred
- Linux result: pass. SSH returned after about 35 seconds. `/` is external
  `/dev/sda2` ext4 labelled `OMARCHY-PS4`; systemd is `running`; LightDM,
  NetworkManager and sshd are active; one Hyprland PID 439 and one Quickshell
  PID 524 run with empty config errors
- display result: pass remotely. HDMI-A-1 is connected/enabled at the sole
  1920x1080@60 mode, scale 1, DPMS on, VRR false, XRGB8888 and sRGB. No GPU
  reset/ring/page-fault, kernel panic, ext4, USB or root I/O fault appeared
- UART conclusion: completed continuity from the single PayLoader send through
  the accepted Linux desktop
- rollback: none required
- next action: deploy the PS4 no-idle profile as A31, then initialize one pinned
  Quattro theme plus its wallpaper as A32

### EXP-20260813-001-A32 — initialize Tokyo Night theme and wallpaper

- state: complete — pass
- question: does the pinned upstream theme engine initialize Tokyo Night and
  its wallpaper on the accepted PS4 Quattro session without destabilizing the
  legacy display path?
- changed variable: managed Omarchy theme only — run one
  `omarchy-theme-set tokyo-night`. Keep HDMI mode, VRR, gamma, monitor, scale,
  compositor options, packages and PS4 overrides unchanged
- expected evidence: current theme name becomes `tokyo-night`; current theme
  and background symlinks resolve inside the pinned runtime/state; shell IPC
  remains `ok`; exactly one Hyprland and Quickshell run; menu/bar/wallpaper use
  the new palette; operator reports visible theme/wallpaper and artifacts;
  UART has no GPU or kernel fault
- timeout: 5 minutes
- rollback: preserve current theme/background state before A32. If unusable,
  restore that exact state or select the prior known theme in a separate
  bounded action; no second theme selection in A32
- stop condition: exactly one theme set; no theme carousel, gamma, VRR, scale,
  package, config edit or restart belongs to A31
- operator action: after remote validation, inspect wallpaper, bar/menu and
  terminal colors; report visibility, stutter and corruption
- bounded UART context:
  [`20260813_221827_786059-exp-20260813-001-a32-initialize-tokyo-night-theme-and-wallpaper-5b5a06b0.md`](../../ps4-uart/sessions/20260813_221827_786059-exp-20260813-001-a32-initialize-tokyo-night-theme-and-wallpaper-5b5a06b0.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The upstream engine selected `tokyo-night`, generated managed
  colors/shell state and selected the first bundled wallpaper
  `backgrounds/0-swirl-buck.jpg` (SHA-256
  `4a4ce5ba6c228771c89439710bfa81005791d3c4f76a62481e4d00939b702e3c`)
- preservation evidence: one Hyprland PID 439 and one Quickshell PID 524 remain;
  IPC is `ok`; automatic idle stays disabled; the PS4 menu-border override
  remains; animations, blur, shadows and VRR remain off; HDMI stays fixed
  1920x1080@60 with empty config errors
- operator result: pass — `nice`, confirming the visible theme and wallpaper
- UART conclusion: completed continuity across one managed theme change with
  no GPU, kernel, ext4 or USB fault
- rollback: not applied. Pre-theme path state is preserved under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A32-20260813T162100Z/`
- next action: inspect and activate pinned Omarchy Fastfetch branding as A33

### EXP-20260813-001-A33 — inspect Omarchy Fastfetch branding

- state: complete — pass
- question: is Fastfetch installed and which pinned Omarchy config/logo pieces
  are absent from the live portable root?
- changed variable: none; read-only SSH and pinned-source inspection of the
  Fastfetch executable, system/user config, logo, shell startup hooks and one
  explicit non-interactive Fastfetch render
- expected evidence: exact installed version; resolution path for config/logo;
  whether the current shell invokes it automatically; a bounded output sample;
  Hyprland PID 439 and Quickshell PID 524 unchanged
- timeout: 3 minutes
- rollback: none for read-only inspection
- stop condition: do not install a package, edit shell startup/config/logo,
  launch another terminal, change theme or restart a process in A33
- bounded UART context:
  [`20260813_222029_389407-exp-20260813-001-a33-inspect-omarchy-fastfetch-branding-a9df5b57.md`](../../ps4-uart/sessions/20260813_222029_389407-exp-20260813-001-a33-inspect-omarchy-fastfetch-branding-a9df5b57.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. Fastfetch 2.67.0 is installed. Neither
  `/etc/fastfetch/config.jsonc` nor `~/.config/fastfetch/config.jsonc` existed,
  and `~/.config/omarchy/branding/about.txt` was absent. The pinned portable
  runtime contains Omarchy's `logo.txt` and `icon.txt`; the shell startup does
  not invoke Fastfetch automatically
- render result: one explicit generic Arch render completed and reported the
  running PS4 kernel, GPU and local IP. Hyprland PID 439 and Quickshell PID 524
  remained unchanged
- UART conclusion: completed continuity; the slice contains only the bounded
  SSH session opening and closing, with no display, GPU or kernel fault
- rollback: none; A33 was read-only
- next action: activate the source-owned PS4 Fastfetch config and pinned About
  icon without restarting the desktop as A34

### EXP-20260813-001-A34 — activate PS4 Fastfetch branding

- state: complete — pass
- question: does the source-owned compact Fastfetch profile render the pinned
  Omarchy About icon and useful PS4 diagnostics without disturbing the accepted
  Quattro desktop?
- changed variable: Fastfetch user branding only — install the candidate
  `config/fastfetch/config.jsonc`, install pinned `icon.txt` as
  `config/omarchy/branding/about.txt`, and activate the missing
  `~/.config/fastfetch` symlink. Do not change shell startup, theme, wallpaper,
  HDMI, compositor, packages or running processes
- source evidence: portable RC2 archive SHA-256 is
  `b8a3cb0b011f9a2d57684b44570644d2cc5ba2a28a741c4ba1b5b7093e29049e`;
  the separate native candidate package set passed package-content policy
- expected evidence: installed profile SHA-256 is
  `e4d85deef993de4f59422372075cd8b6bf601678c0f0ea000b3da376208a8f95`;
  one explicit `fastfetch --pipe` render reports Omarchy PS4 Quattro RC2,
  PS4 Slim/Baikal, kernel, GPU, display and Tokyo Night; Hyprland PID 439 and
  Quickshell PID 524 remain; UART has no GPU or kernel fault
- timeout: 3 minutes
- rollback: preserve any existing Fastfetch path and About icon, remove the
  candidate files/symlink, and restore the exact prior state. No process restart
- stop condition: no About window, terminal launch, automatic shell hook,
  package install, config reload, theme or display change belongs to A34
- operator action: none; a visible About-window acceptance test will be a
  separate bounded experiment after A34 closes
- bounded UART context:
  [`20260813_222930_877891-exp-20260813-001-a34-activate-ps4-fastfetch-branding-d383abb6.md`](../../ps4-uart/sessions/20260813_222930_877891-exp-20260813-001-a34-activate-ps4-fastfetch-branding-d383abb6.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The active config matches expected SHA-256
  `e4d85deef993de4f59422372075cd8b6bf601678c0f0ea000b3da376208a8f95`
  and the pinned About icon matches SHA-256
  `5fe8adced2fe67e410e177477a7272d1807b3fedc81fbc3f030dd479bc046b76`
- render evidence: one explicit pipe render showed Omarchy PS4 Quattro RC2,
  PS4 Slim/Baikal B1, Linux 6.18.44-ps4-baikal, AMD Liverpool with amdgpu,
  1920x1080@60, external ext4 root, Tokyo Night, package count, local IP and
  uptime. Fastfetch's generic PCI name `Kingston/Clayton` was rejected as
  misleading and replaced in the same branding candidate with the accurate
  platform label `AMD Liverpool · amdgpu`
- preservation evidence: systemd remains `running`; Hyprland PID 439 and
  Quickshell PID 524 are unchanged. No process or desktop configuration was
  reloaded
- UART conclusion: completed continuity. The slice contains only bounded SSH
  session lifecycle lines; no display, GPU, kernel, ext4 or USB fault
- rollback: not applied; both paths were absent before A34. A dedicated state
  directory was reserved at
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A34-20260813T162930Z/`
- next action: launch the existing Omarchy About action once and collect the
  operator's visible acceptance as A35

### EXP-20260813-001-A35 — show the PS4 Fastfetch About window

- state: complete — fail; launcher integration gap isolated
- question: does the existing Quattro About action display the accepted compact
  PS4 Fastfetch profile legibly at fixed 1080p60?
- changed variable: one About window only — dispatch `omarchy-launch-about`
  once through the running Hyprland session. Do not change Fastfetch, terminal,
  theme, shell, display, compositor or package configuration
- expected evidence: exactly one floating `org.omarchy.about` client appears;
  its Foot terminal renders the Omarchy icon and PS4 diagnostics; the operator
  reports legibility and any corruption; Hyprland PID 439 and Quickshell PID
  524 remain; UART has no GPU or kernel fault
- timeout: 3 minutes
- rollback: close only the About client with `hyprctl dispatch closewindow` if
  it is unreadable or does not exit normally
- stop condition: no second About launch, terminal/theme/config change or
  desktop restart belongs to A35
- operator action: after I open it remotely, inspect the visible About card and
  report whether the logo/text are readable and whether any pixels stutter
- bounded UART context:
  [`20260813_223658_035300-exp-20260813-001-a35-show-the-ps4-fastfetch-about-window-bc4b6e24.md`](../../ps4-uart/sessions/20260813_223658_035300-exp-20260813-001-a35-show-the-ps4-fastfetch-about-window-bc4b6e24.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: fail without display regression. The one About dispatch created no
  `org.omarchy.about` client. Its UWSM scope selected `xfce4-terminal`, which
  exited with `cannot open display`, even though an interactive desktop-shell
  query selects `foot.desktop`
- isolation evidence: the activated Hyprland terminal preference is valid and
  `xdg-terminal-exec --print-id` returns Foot when `XDG_CURRENT_DESKTOP` is
  present. The failing UWSM app daemon did not retain that desktop selection,
  falling through to the system terminal list. This is launcher environment
  integration, not a Fastfetch render failure
- preservation evidence: About client count stayed zero; no Foot client or
  process remained; Hyprland PID 439 and Quickshell PID 524 were unchanged
- UART conclusion: completed continuity. Only bounded SSH session lifecycle
  appeared; no display, GPU, kernel, ext4 or USB fault
- rollback: none required because no window or persistent change was created
- next action: repin and rebuild Quattro RC3, then verify whether upstream RC3
  changes this launcher path before designing a PS4-specific correction

### EXP-20260813-001-A36 — activate portable Omarchy Quattro RC3

- state: complete — degraded; activation passed, validation command contaminated the slice
- question: can the verified RC3 portable bundle replace only the active
  versioned Omarchy user layer while the accepted graphical session remains
  stable?
- changed variable: portable release version only — install bundle
  `omarchy-ps4-portable-4.0.0rc3-144f4d1.tar.zst` and activate its managed
  runtime/config symlinks. Do not install native packages, restart/reload a
  process, log out, reboot, change theme, display or PS4 hardware state
- source evidence: official `omacom-io/omarchy-pkgs` release commit
  `84b86195cdeb0ddc71b58810b208df18f6907ffb` assigns `4.0.0rc3-1` to upstream
  Omarchy commit `144f4d1e31d6ddc2cba5dfd69278cabf02bafd05`; portable archive SHA-256
  is `6b1d155f54cb2fe2288778f6e9be223f6d55e85d45d8bdc0e0f957446bf56246`
- expected evidence: installer preflight and manifest verification pass; active
  runtime/config resolve to commit `144f4d1e...`; PS4 Fastfetch title is RC3;
  Hyprland PID 439 and Quickshell PID 524 remain; shell IPC/config errors and
  system state remain healthy; UART has no GPU, kernel, ext4 or USB fault
- timeout: 5 minutes
- rollback: run the exact installer-generated `ROLLBACK.sh`, which restores the
  pre-A36 runtime/config/user-path symlinks and removes the RC3 release trees.
  Do not improvise a partial symlink rollback
- stop condition: no desktop restart, login test, About launch, launcher fix,
  theme selection, package install or second activation belongs to A36
- operator action: none; visible RC3 session acceptance requires a separate
  bounded logout/login experiment after A36 closes
- bounded UART context:
  [`20260813_225217_419064-exp-20260813-001-a36-activate-portable-omarchy-quattro-rc3-9e31cbd7.md`](../../ps4-uart/sessions/20260813_225217_419064-exp-20260813-001-a36-activate-portable-omarchy-quattro-rc3-9e31cbd7.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- activation result: pass. Preflight and payload manifest verification passed;
  active runtime, config, Hyprland, Omarchy and Fastfetch symlinks all resolve
  to `144f4d1e31d6ddc2cba5dfd69278cabf02bafd05`. The explicit Fastfetch render
  reports RC3, Liverpool/amdgpu, fixed 1080p60 and Tokyo Night. Systemd remained
  `running`; original Hyprland PID 439 and Quickshell PID 524 remained
- contamination: the final validation incorrectly called
  `omarchy-launch-shell --ipc call ping`. That launcher does not accept IPC
  arguments; it started competing Quickshell processes, producing eight core
  dumps before their scopes exited. This was not part of the declared variable
  and prevents a clean A36 pass
- UART conclusion: completed continuity, but degraded by the eight coredumps.
  No GPU, kernel, ext4 or USB fault appeared
- rollback: not applied. The exact generated rollback remains executable at
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A36-20260813T165253Z/ROLLBACK.sh`
- next action: identify the coredumps and verify the original shell plus all
  supervisor/process counts read-only as A37 before any runtime restart

### EXP-20260813-001-A37 — audit post-RC3 activation coredumps

- state: complete — pass; contamination contained
- question: were all A36 coredumps only the accidentally competing Quickshell
  launches, and is the original accepted desktop still the sole live instance?
- changed variable: none; read-only SSH inspection of `coredumpctl`, process
  trees, user units, Hyprland clients, config errors and display state
- expected evidence: all eight dumps identify the accidental Quickshell starts;
  exactly one original Hyprland PID 439 and Quickshell PID 524 remain; no extra
  shell launcher/supervisor remains; HDMI stays 1920x1080@60 with VRR off;
  systemd stays running and config errors remain empty
- timeout: 3 minutes
- rollback: none for read-only inspection. If a stray process exists, close
  A37 and remove it in a separately declared cleanup action
- stop condition: do not kill/restart a process, reload config, launch About,
  change symlinks or roll back RC3 in A37
- operator action: none
- bounded UART context:
  [`20260813_225434_165269-exp-20260813-001-a37-audit-post-rc3-activation-coredumps-325434ba.md`](../../ps4-uart/sessions/20260813_225434_165269-exp-20260813-001-a37-audit-post-rc3-activation-coredumps-325434ba.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. `coredumpctl` identifies all eight A36 dumps as SIGABRT from
  `/usr/bin/quickshell` at the single contaminated validation timestamp. No
  other executable dumped
- containment evidence: exactly one original Hyprland PID 439, one shell
  supervisor PID 520 and one Quickshell PID 524 remain; no extra app scope or
  competing launcher remains. HDMI-A-1 is still 1920x1080@60, DPMS on, VRR
  false; config errors are empty and systemd remains `running`
- UART conclusion: completed continuity. Only the bounded SSH session lifecycle
  appeared; no GPU, kernel, ext4 or USB fault
- rollback: none; A37 was read-only
- next action: use the pinned RC3 `omarchy-restart-shell` command exactly once
  to hand the bar/menu runtime from the old loaded code to RC3 as A38

### EXP-20260813-001-A38 — restart only the Quattro shell onto RC3

- state: complete — degraded pass; RC3 loaded, 1080p UI is underscaled
- question: does one intended shell-only restart load the active RC3 Quickshell
  tree while preserving Hyprland and the fixed PS4 display path?
- changed variable: Quickshell runtime generation only — execute the pinned RC3
  `omarchy-restart-shell` once with the accepted desktop environment. Do not
  restart/reload Hyprland, log out, reboot, change config/theme/display or
  launch About
- expected evidence: the old supervisor PID 520 and Quickshell PID 524 exit;
  exactly one new RC3 supervisor and Quickshell appear; shell IPC is ready;
  Hyprland PID 439 remains; top bar/menu remain visible; HDMI stays 1080p60,
  VRR false and UART has no coredump, GPU or kernel fault
- timeout: 3 minutes
- rollback: if the shell does not return, run the generated A36 rollback and
  start the restored RC2 shell in a separately declared recovery action. Do not
  start a second competing shell inside A38
- stop condition: exactly one restart command; no retry or manual `quickshell`
  launch belongs to A38
- operator action: after remote readiness, inspect the bar and open/close
  `Super+Space` once; report whether the menu is responsive and whether pixels
  remain stable
- bounded UART context:
  [`20260813_225531_780652-exp-20260813-001-a38-restart-only-the-quattro-shell-onto-rc3-1741439d.md`](../../ps4-uart/sessions/20260813_225531_780652-exp-20260813-001-a38-restart-only-the-quattro-shell-onto-rc3-1741439d.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- runtime result: pass. The supported restart replaced supervisor PID 520 and
  Quickshell PID 524 with exactly one RC3 supervisor PID 5616 and Quickshell
  PID 5621. Hyprland PID 439 remained; HDMI stayed 1920x1080@60, DPMS on, VRR
  false; config errors stayed empty and no new coredump appeared
- operator result: degraded — the 1080p UI/font presentation is visibly too
  small. This is a sizing issue, not a failed RC3 runtime handoff
- UART conclusion: completed continuity; only bounded SSH session lifecycle
  appeared, with no GPU, kernel, ext4 or USB fault
- rollback: not applied
- next action: inspect the current RC3 typography controls and package delta
  read-only as A39, then tune only typography before considering monitor scale

### EXP-20260813-001-A39 — inspect 1080p typography and full-profile delta

- state: complete — pass
- question: which user-owned RC3 controls determine bar/menu/terminal/app font
  sizing at scale 1, and exactly which PS4-curated full-profile packages are
  still absent from the live root?
- changed variable: none; read-only source and SSH inspection of shell style,
  fontconfig, Foot/GTK settings, monitor geometry, installed packages, disk
  capacity and the generated 153-package PS4 profile
- expected evidence: one smallest safe typography override candidate; exact
  present/missing profile counts and package names; free disk and download-size
  feasibility; no process or display change
- timeout: 4 minutes
- rollback: none for read-only inspection
- stop condition: do not install a package, edit font/display config, restart a
  process, launch an app or run Pacman sync/upgrade in A39
- operator action: none
- result: pass. HDMI is fixed 1920x1080@60 at compositor scale 1. RC3 defaults
  the shell to 12px and Foot to 9pt; GTK scaling is 1.0. The supported
  `omarchy-display-text-size` command changes shell, GTK and terminal sizing in
  lockstep while keeping compositor scale 1; 16px maps to about 1.36x GTK and
  12pt terminal text
- portable gap: the RC3 config contains `config/foot/foot.ini`, but the
  portable installer did not activate `~/.config/foot`; that live path is
  absent. The source installer and tests now own this missing symlink before a
  typography preset is applied
- package result: 53 of the generated 153-package PS4 profile are installed;
  100 are missing. Eighty missing names exist in the configured Arch `core` and
  `extra` databases; twenty do not, including the three local PS4 packages and
  17 Omarchy/AUR packages. `/` has 108,561,211,392 bytes available and Pacman
  currently has 736 MiB cached
- UART conclusion: completed continuity; read-only inspection caused no GPU,
  kernel, ext4 or USB fault
- rollback: none; A39 was read-only
- next action: activate managed Foot config and apply the supported 16px
  desktop typography preset as A40

### EXP-20260813-001-A40 — apply coherent 1080p typography preset

- state: complete — fail for bar icon rendering
- question: does RC3's supported 16px text-size preset make the 1080p shell,
  GTK applications and new Foot windows comfortably readable without changing
  compositor scale or destabilizing DCE8?
- changed variable: desktop typography preset only — activate the missing
  managed `~/.config/foot` symlink, then execute exactly one
  `omarchy-display-text-size 16`. Keep HDMI/compositor scale 1, theme, shell
  process, packages and all other configuration unchanged
- expected evidence: `shell.toml` preserves the PS4 menu workaround and gains
  `[font] base-size = 16`; GTK text scale becomes about 1.36; Foot becomes
  12pt; Quickshell PID 5621 and Hyprland PID 439 remain; display stays
  1080p60/VRR off; operator reports improved legibility without clipping or
  corruption
- timeout: 4 minutes
- rollback: preserve exact `shell.toml`, GSettings value and prior absent Foot
  path; restore those values and remove the symlink. Do not change monitor scale
- stop condition: no second font size, compositor scale, shell restart, package
  install or app launch belongs to A40
- operator action: after remote validation, inspect the bar and menu at normal
  viewing distance and report whether 16px is comfortable or too large
- bounded UART context:
  [`20260813_230322_279600-exp-20260813-001-a40-apply-coherent-1080p-typography-preset-62c00592.md`](../../ps4-uart/sessions/20260813_230322_279600-exp-20260813-001-a40-apply-coherent-1080p-typography-preset-62c00592.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- remote result: the supported command set shell base to 16px, GTK text scale
  to 1.3 and Foot to 12pt while preserving the menu border override. Hyprland
  PID 439 and Quickshell PID 5621 remained; HDMI stayed 1080p60 at scale 1,
  VRR false, with zero new coredumps or config errors
- operator result: fail — top-bar icons rendered incorrectly after the size
  change. Typography cannot be accepted until glyph resolution versus icon
  scaling is isolated
- UART conclusion: completed continuity with no GPU, kernel, ext4 or USB fault
- rollback: not yet applied; exact pre-A40 shell/GTK/Foot state is preserved at
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A40-20260813T170300Z/`
- next action: inspect the resolved Omarchy/Nerd fonts and bar token sizes
  read-only as A41, then restore or decouple icon sizing in a separate action

### EXP-20260813-001-A41 — audit broken top-bar icon fonts

- state: complete — pass
- question: are the broken 16px top-bar icons caused by missing font assets,
  wrong fontconfig resolution, or RC3 icon tokens scaling beyond the DCE8-safe
  rendering size?
- changed variable: none; read-only SSH/source inspection of installed font
  files and hashes, `fc-list`/`fc-match`, Quickshell journal/config errors,
  `shell.toml`, resolved bar tokens and process/display state
- expected evidence: exact font presence and family resolution; whether a
  Quickshell glyph/font error exists; smallest rollback or per-icon-token fix
- timeout: 3 minutes
- rollback: none for read-only audit
- stop condition: do not change text size, font, config, process, package or
  display state in A41
- operator action: none
- bounded UART context:
  [`20260813_230638_424081-exp-20260813-001-a41-audit-broken-top-bar-icon-fonts-3a3e1790.md`](../../ps4-uart/sessions/20260813_230638_424081-exp-20260813-001-a41-audit-broken-top-bar-icon-fonts-3a3e1790.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. `omarchy.ttf` is installed in the portable user font hierarchy
  and resolves as `omarchy Regular`. Four JetBrains Mono Nerd Font faces are
  installed under `/usr/share/fonts/TTF`; the requested family resolves to its
  regular Nerd Font face. The shell emitted no missing glyph/font-family error
- cause: RC3 defaults `bar.scale-with-font = true`. Raising base size from 12
  to 16 multiplies bar size, icon slot, icon canvas and icon font by 1.333.
  The operator-visible corruption therefore follows enlarged bar glyph/canvas
  rendering on DCE8, not absent Omarchy fonts
- preservation evidence: Hyprland PID 439, Quickshell PID 5621, 1080p60 scale
  1 and VRR false remained unchanged
- UART conclusion: completed continuity with no hardware fault
- rollback: none; A41 was read-only
- next action: retain 16px desktop text but set only `[bar]
  scale-with-font = false` as A42

### EXP-20260813-001-A42 — decouple top-bar icons from 16px text

- state: complete — fail; fixed icons still do not fit at 16px
- question: does pinning RC3 bar geometry/icon canvases to their known-good
  default pixel sizes restore top-bar icons while retaining readable 16px shell,
  1.3x GTK and 12pt Foot text?
- changed variable: one shell style key only — append `[bar]
  scale-with-font = false` to the active PS4 `shell.toml`. Keep base-size 16,
  font families, menu border, theme, compositor scale, processes and packages
  unchanged
- expected evidence: the watched style file is consumed without restart;
  Hyprland PID 439 and Quickshell PID 5621 remain; bar icons return to their
  default 13/16/27px font/canvas/slot geometry; operator reports normal icons
  and readable text; no coredump or display fault
- timeout: 3 minutes
- rollback: restore exact pre-A42 `shell.toml`, retaining the A40 rollback if
  the complete 16px preset must later be removed
- stop condition: no font reinstall, second style key, process restart, package
  install or display change belongs to A42
- operator action: inspect the top-bar icons after the watched file updates and
  report whether they are normal
- bounded UART context:
  [`20260813_230815_309631-exp-20260813-001-a42-decouple-top-bar-icons-from-16px-text-62b1773e.md`](../../ps4-uart/sessions/20260813_230815_309631-exp-20260813-001-a42-decouple-top-bar-icons-from-16px-text-62b1773e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- remote result: the watched style file applied `[bar] scale-with-font = false`
  without restart; Hyprland PID 439 and Quickshell PID 5621 remained and no
  coredump appeared
- operator result: fail — the bar contents still cannot fit at 16px even with
  default-size icon geometry. This rules out 16px as the 1080p product preset
- UART conclusion: completed continuity; no GPU, kernel, ext4 or USB fault
- rollback: exact pre-A42 file remains at
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A42-20260813T170900Z/shell.toml.before`
- next action: reduce the coordinated desktop typography preset to 14px while
  retaining fixed bar geometry as A43

### EXP-20260813-001-A43 — set the 1080p typography preset to 14px

- state: complete — pass
- question: does a coordinated 14px preset fit the complete 1080p top bar while
  remaining more readable than the 12px default?
- changed variable: typography preset size only — execute exactly one
  `omarchy-display-text-size 14` while retaining `[bar]
  scale-with-font = false`. Keep fonts, menu workaround, compositor scale,
  processes, packages and display unchanged
- expected evidence: shell base becomes 14px, GTK text scale about 1.2 and Foot
  11pt; fixed bar geometry remains; PIDs remain; operator confirms the complete
  bar fits and icons/text are readable; no coredump or display fault
- timeout: 3 minutes
- rollback: restore the exact A40 pre-state if 14px also fails; do not test a
  second size inside A43
- stop condition: exactly one 14px application; no package install, restart or
  display change belongs to A43
- operator action: inspect the full top bar and `Super+Space` menu, then report
  fit, readability and corruption
- bounded UART context:
  [`20260813_231934_834495-exp-20260813-001-a43-set-the-1080p-typography-preset-to-14px-fed01ff5.md`](../../ps4-uart/sessions/20260813_231934_834495-exp-20260813-001-a43-set-the-1080p-typography-preset-to-14px-fed01ff5.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. The supported command set shell base to 14px, GTK text scale
  to 1.2 and Foot to 11pt while retaining fixed bar icon geometry and the menu
  border workaround. Hyprland PID 439 and Quickshell PID 5621 remained; no
  coredump appeared
- operator result: pass — `yes nice`, confirming the complete top bar fits and
  the 1080p presentation is readable
- UART conclusion: completed continuity with no GPU, kernel, ext4 or USB fault
- rollback: not applied. Exact pre-A43 state remains under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A43-20260813T171200Z/`
- next action: install the three locally built RC3 PS4 packages as A44 without
  restarting the active portable session

### EXP-20260814-001-A1 — arm temporary RC3 recovery access

- state: complete — pass
- question: can a second, key-only recovery account survive the native package
  test and invoke only status or the exact RC3 package rollback while the
  existing `ps4` login, desktop and boot state remain unchanged?
- changed variable: development recovery access only — create human account
  `omarchy-recovery`, copy the already-pinned operator ED25519 public key,
  install a user-specific public-key-only SSH policy, install two exact
  command-specific sudo rules, and keep the already-enabled system
  `sshd.service` persistent. Do not install the RC3 packages in this action
- source evidence: the isolated OrbStack/Arch fixture created the account,
  exercised restricted status and rollback, rejected general sudo, and
  confirmed `PasswordAuthentication no`, public-key-only authentication and
  disabled TCP/agent/X11 forwarding for this user. The owner-finalization
  fixture refuses both the extra human account and its temporary `NOPASSWD`
  rule. Booted OrbStack machine `omarchy-gift-rc3-test` additionally passed a
  real network SSH login, real systemd sshd enablement, exact RC3 install,
  reboot persistence and remote restricted rollback; see
  `docs/GIFT-DEV-VM-TEST-2026-08-14.md`. USB/label guards were simulated and
  the VM was arm64, so neither replaces PS4 acceptance
- expected evidence: account UID is in the human range and its SSH key has
  fingerprint `SHA256:N64LAFp/1IpDOVOrMNVY3Bd6JHn2qxAyvT0/8FZ3T0M`;
  `sshd.service` remains enabled and active; a fresh remote key login as
  `omarchy-recovery` succeeds; restricted status succeeds; arbitrary sudo is
  denied; `ps4`, Hyprland and Quickshell remain healthy
- timeout: 5 minutes
- rollback: from the still-working `ps4` administration path, remove only the
  recovery account/home, `/etc/sudoers.d/91-omarchy-ps4-recovery`,
  `/etc/ssh/sshd_config.d/30-omarchy-ps4-recovery.conf`,
  `/usr/local/sbin/omarchy-ps4-dev-recovery`, and
  `/var/lib/omarchy-ps4/recovery`, validate `sshd -t`, then reload sshd
- stop condition: no native package transaction, owner provisioning, desktop
  reload, boot-file change, restart or payload belongs to this experiment. A
  failed real SSH login closes the action without beginning A44
- operator action: none
- staged bundle: developer gift archive SHA-256
  `2eb7a02d047314db215c6d059368aa89b88f2989a11f5131905b536672767e1b`
  was copied to the `ps4` development home, verified in place and extracted;
  its internal policy check passed
- in-progress hardware evidence: continuous UART generation
  `f9d6fea5361b45449a0948ab0457f00c` is valid and ready. The unmodified root
  resolved to USB `/dev/sda2`, ext4 label `OMARCHY-PS4`; `sshd.service` was
  already enabled and active; Hyprland PID 439 and Quickshell PID 5621 were
  healthy before the change. Guarded check and apply created
  `omarchy-recovery` with the pinned fingerprint. A fresh network login passed,
  restricted status passed, arbitrary sudo was denied, provisioning remained
  unarmed, sshd remained enabled/active and both desktop PIDs remained
  unchanged
- bounded UART context:
  [`20260814_022120_506838-exp-20260814-001-a1-arm-temporary-rc3-recovery-access-95ea71b5.md`](../../ps4-uart/sessions/20260814_022120_506838-exp-20260814-001-a1-arm-temporary-rc3-recovery-access-95ea71b5.md),
  with exact 4,039-byte `.raw` slice and empty logger-event sidecar
- operator result: pass — Omarchy remained visible and responsive; no visible
  regression was reported
- UART conclusion: completed continuity on capture generation
  `f9d6fea5361b45449a0948ab0457f00c`. UART shows the expected systemd manager
  reload, successful OpenSSH reload and clean UID 1001 recovery login session
  lifecycle. No GPU, kernel, ext4, USB or service failure appeared. Periodic
  MT7668 P2P trace messages were unchanged background behavior
- rollback: not applied. Recovery account `omarchy-recovery`, its restricted
  command and persistent key-only SSH remain intentionally armed as the A44
  safety path. Gift finalization must continue to refuse this development state
- next action: A44 may begin in a new bounded session; resolve the full Pacman
  transaction first and do not proceed if it contains a forbidden or unreviewed
  dependency

### EXP-20260813-001-A44 — install native RC3 PS4 package foundation

- state: complete — inconclusive; no package transaction began and the root
  package set remained unchanged
- question: do the three verified local RC3 packages install cleanly on the
  external root without enabling provisioning or disturbing the active portable
  desktop?
- changed variable: native PS4 package foundation only — first resolve and
  record Pacman's complete transaction, then install the locally built
  `omarchy-ps4`, `omarchy-ps4-settings` and `omarchy-ps4-provisioning` RC3
  package files plus only their explicitly reviewed missing dependencies in one
  Pacman transaction. Do not enable services, activate provisioning, switch
  user symlinks or restart/reload the desktop
- source evidence: the rebuilt package SHA-256 values are runtime
  `1d02e1799e825ebd6fe275ac9bd483c53b62e8d50b5df6c3073470266339c025`,
  settings
  `e1fa55f97605ac403c1bf7d1d3b0c60fedd93637afe524a47033ff404907190a`
  and provisioning
  `295afa9789ca770471dc11238dc2710e57dcf3068a8747ad889d3696675e87cf`;
  package content and prepare-for-owner fixture tests passed in the pinned
  OrbStack/Arch build. The private developer gift archive is
  `omarchy-ps4-gift-dev-rc3.tar.zst`, SHA-256
  `2eb7a02d047314db215c6d059368aa89b88f2989a11f5131905b536672767e1b`;
  its extracted manifest passed, a clean rebuild produced the same content
  manifest, and Pacman listed exactly the three expected `4.0.0rc3-1` entries
  from its normalized local database
- expected evidence: Pacman reports all three at `4.0.0rc3-1`; no provisioning
  service or pending marker is enabled/created; active runtime stays portable
  commit `144f4d1e`; Hyprland PID 439 and Quickshell PID 5621 remain; display and
  system stay healthy; `sshd.service` and the independently verified
  `omarchy-recovery` status command remain available
- preflight rejection: abort before installation if the resolved transaction
  includes a kernel, bootloader, Plymouth, UDisks, display-manager takeover,
  graphics-stack replacement or any package outside the reviewed closure
- timeout: 6 minutes
- rollback: uninstall only the three local packages with `pacman -Rns` if the
  transaction succeeds but violates the gates; the portable runtime remains the
  desktop fallback
- stop condition: no full Pacman upgrade, service enablement, config
  activation, restart or second transaction belongs to A44. A rejected
  dependency closure closes A44 without modifying the root
- operator action: none
- bounded UART context:
  [`20260814_023335_582257-exp-20260813-001-a44-install-native-rc3-ps4-package-foundation-902ce3e2.md`](../../ps4-uart/sessions/20260814_023335_582257-exp-20260813-001-a44-install-native-rc3-ps4-package-foundation-902ce3e2.md),
  with exact 1,725-byte `.raw` slice and empty logger-event sidecar
- result: inconclusive before transaction resolution. Attempt 1 exposed that
  the PS4 baseline lacks optional `cmp`; the comparison was replaced with a
  Bash built-in. Attempt 2 proved Pacman's `alpm` download sandbox cannot
  traverse a root-only temporary ancestor; the ancestor was changed to mode
  0755 without disabling sandboxing. Attempt 3 proved `alpm` also cannot
  traverse the private `ps4` home to read the local repository. All three
  attempts stopped during guarded setup or database synchronization before a
  dependency closure or package transaction existed
- UART conclusion: completed continuity on generation
  `f9d6fea5361b45449a0948ab0457f00c`. Only clean `ps4` SSH session lifecycle
  and unchanged MT7668 background warnings appeared; there was no GPU, kernel,
  ext4, USB, display-manager, service or package-transaction fault
- rollback: not required because Pacman never began a transaction. The
  temporary recovery account and persistent SSH from A1 remain healthy. The
  staged development bundle remains under the `ps4` development home
- next action: copy the checksum-verified local repository into a temporary
  0755/0644 sandbox-readable directory, prove preflight from a private bundle
  path in the booted OrbStack VM, rebuild the bundle, then use fresh bounded
  experiment `EXP-20260814-001-A2`. Do not repeat A44 without that new evidence

### EXP-20260814-001-A2 — install native RC3 foundation after sandbox fixes

- state: complete — pass
- question: with the verified local repository copied to an ephemeral
  sandbox-readable directory, do the three RC3 packages resolve and install on
  the external PS4 root without changing the portable desktop or recovery SSH?
- changed variable: native RC3 package foundation only, identical to A44. The
  installer implementation changes only how already-checksummed local package
  files are exposed to Pacman's unprivileged download sandbox. Do not disable
  Pacman sandboxing or add a test-only dependency
- source evidence: developer gift archive SHA-256
  `abf563b0a23dc0978a1aa37247d1c81877bd909bb2f10b931aaa913e352ed931`;
  archive extraction, package policy, shell checks, recovery fixture and clean
  rebuild manifest comparison passed. On booted OrbStack machine
  `omarchy-gift-rc3-test`, the bundle was copied beneath mode-0700 `/root`, all
  cached Omarchy PS4 package files were moved aside temporarily, and Pacman
  still resolved exactly the three `4.0.0rc3-1` package URLs from the copied
  `/tmp/.../repository` while retaining its download sandbox. This directly
  reproduces and closes A44's private-parent traversal failure
- expected evidence: isolated and live transaction name/version sets match;
  the reviewed closure contains no forbidden component; exact three project
  packages report `4.0.0rc3-1`; provisioning remains unarmed; sshd and
  `omarchy-recovery` remain healthy; Hyprland PID 439, Quickshell PID 5621 and
  the visible responsive desktop remain unchanged
- timeout: 6 minutes
- rollback: from the independently verified recovery login, run only
  `sudo /usr/local/sbin/omarchy-ps4-dev-recovery rollback-foundation`; retain
  dependencies and portable runtime
- stop condition: no full upgrade, service activation, desktop reload, restart,
  boot-file change, splash or payload. Any transaction mismatch or unreviewed
  dependency closes A2 before installation
- operator action: none
- reviewed transaction: exact three project packages plus `fakeroot`, `git`,
  `pacman-contrib`, `perl-error`, `perl-timedate`, `perl-mailtools` and
  `zlib-ng`; 123.52 MiB downloaded and 155.58 MiB installed. No kernel,
  bootloader, Plymouth, UDisks, display manager, Mesa, libdrm, Vulkan, Xorg
  driver or service package was present
- result: Pacman installed `omarchy-ps4`, `omarchy-ps4-settings` and
  `omarchy-ps4-provisioning` at exactly `4.0.0rc3-1`. The transaction created
  only the standard locked `git` system account through its package hook; no
  service was enabled. Existing `/etc/sudoers.d` mode 0750 was retained despite
  the package archive declaring 0755
- postcheck: the package transaction completed, then the first evidence pass
  stopped because `comm` used the host locale against byte-sorted package
  lists. No second transaction ran. Package versions, recovery status,
  provisioning markers, services, portable release and desktop PIDs were
  checked read-only. The evidence directory
  `/var/lib/omarchy-ps4/experiments/EXP-20260814-001-A2-20260813T204418Z`
  was completed with correctly byte-sorted before/after lists,
  `new-packages.txt`, final Pacman log, recovery status and rollback command.
  The source installer now sorts and compares all three operations with
  `LC_ALL=C`. The post-A2 canonical archive containing that evidence fix is
  SHA-256
  `1a24445cf1409d3b523586e528b63157779aa0df6b79e09f6ca1cd6636aae28a`;
  clean-rebuild manifest, package policy and recovery fixture passed. Its three
  package payloads are unchanged from the hardware-tested archive
- expected-state evidence: provisioning marker and service are absent;
  LightDM and sshd are active; sshd is enabled; a fresh
  `omarchy-recovery` login reports all three versions and restricted rollback
  remains available; portable release still resolves to upstream commit
  `144f4d1e`; Hyprland PID 439 and Quickshell PID 5621 are unchanged
- bounded UART context:
  [`20260814_024213_769517-exp-20260814-001-a2-install-native-rc3-foundation-after-sandbox--0b7c0ed6.md`](../../ps4-uart/sessions/20260814_024213_769517-exp-20260814-001-a2-install-native-rc3-foundation-after-sandbox--0b7c0ed6.md),
  with exact 2,513-byte `.raw` slice and empty logger-event sidecar
- operator result: pass — the Omarchy desktop remained visible and responsive;
  nothing changed on the monitor, which is the expected foundation-only result
- UART conclusion: completed continuity on generation
  `f9d6fea5361b45449a0948ab0457f00c`. UART shows expected system and user
  manager reloads plus a clean UID 1001 recovery SSH session. No GPU, kernel,
  USB, ext4, display-manager, service or package fault appeared. The isolated
  MT7668 warning was unchanged background behavior
- rollback: not applied. The three RC3 packages remain installed, the portable
  desktop remains active and the restricted recovery rollback stays armed
- next action: stop for owner direction. Installing and launching the UI-only
  FPKG from Orbis is a separate hardware experiment and requires returning to
  the PS4 system software; persistent native splash A45 also remains separate

### EXP-20260814-001-A3 — stage native RC3 session with remote rollback

- state: complete — inconclusive before privileged staging; active desktop and
  native package foundation unchanged
- question: can the already-installed native RC3 profile be staged for the
  existing `ps4` user, together with an exact recovery-account rollback,
  without changing or reloading the active portable desktop?
- changed variable: inactive native-session staging and its restricted rollback
  control only. Copy the package-owned `/usr/share/omarchy/config` into a
  versioned user-owned candidate, preserve the current portable path map, and
  authorize `omarchy-recovery` for only the exact native-session status and
  rollback commands. Do not switch a live symlink, reload Hyprland or
  Quickshell, restart LightDM, change packages, services, boot files, storage,
  display settings or owner provisioning
- expected evidence: all three project packages remain exactly `4.0.0rc3-1`;
  the candidate is derived from the installed native files; its activation and
  rollback paths validate offline; a fresh restricted recovery SSH login can
  run native-session status but cannot activate it or obtain arbitrary sudo;
  active `OMARCHY_PATH`, Hyprland and Quickshell PIDs remain on portable commit
  `144f4d1e`; the visible desktop remains unchanged and responsive
- timeout: 5 minutes
- rollback: remove only the inactive native candidate, control command and its
  exact new sudo authorization. Because no live pointer or process changes in
  A3, rollback must not restart the graphical session
- stop condition: close and review A3 before session activation. Any live
  configuration pointer change, compositor/shell reload, LightDM restart,
  package transaction, payload or reboot is outside A3
- operator action: do not interact with the desktop during staging; when asked,
  confirm that the existing Omarchy desktop did not visibly change
- bounded UART context:
  [`20260814_025833_602853-exp-20260814-001-a3-stage-native-rc3-session-with-remote-rollbac-0ed206ed.md`](../../ps4-uart/sessions/20260814_025833_602853-exp-20260814-001-a3-stage-native-rc3-session-with-remote-rollbac-0ed206ed.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: preflight inspection passed: all three packages are `4.0.0rc3-1`,
  native runtime/config files exist, provisioning is unarmed, LightDM/sshd are
  active, sshd is enabled, and Hyprland PID 439 plus Quickshell PID 5621 still
  resolve to portable commit `144f4d1e`. Two inactive control sources were
  copied into the existing developer bundle directory, but `sudo` correctly
  required the `ps4` account password before either guarded check or apply
  could run. No native candidate, `/usr/local` command, sudo policy, live
  pointer or process changed
- UART conclusion: completed continuity with routine `ps4` and recovery SSH
  session lifecycles plus unchanged MT7668 P2P trace messages. No GPU, kernel,
  ext4, USB, display-manager or service fault appeared
- rollback: not required. The two inert user-owned source files may remain in
  the private development bundle; neither is referenced by the session
- next action: A4 may switch only the visible Quattro shell from the portable
  runtime to the installed `/usr/share/omarchy` runtime without root or a
  LightDM restart. Full native UWSM-profile activation remains a later action
  requiring an interactive sudo authentication or separately authorized root
  control

### EXP-20260814-001-A4 — launch installed native RC3 Quattro shell

- state: complete — pass for native shell activation; first-owner setup was
  deliberately not armed or exercised
- question: does the already-installed `/usr/share/omarchy` RC3 runtime launch
  the visible Quattro shell successfully inside the current accepted Hyprland
  session while persistent SSH remains available?
- changed variable: Quattro shell runtime only — stop the current portable
  `omarchy-launch-shell` supervisor and start one user-owned transient service
  with `OMARCHY_PATH=/usr/share/omarchy`, `/usr/bin` commands and the installed
  shell tree. Keep Hyprland PID 439, its portable configuration, LightDM,
  packages, services, display settings, boot files, storage and provisioning
  unchanged
- source evidence: installed and portable `omarchy-launch-shell` files have the
  same SHA-256
  `484f3af00ee3d13b8f4e33b118d9b7355c72d254a631fc740a160f5f1d140cff`;
  both derive from pinned commit `144f4d1e`, while the new process path and
  environment will independently prove consumption of the package-owned tree
- expected evidence: one new Quickshell process runs with
  `OMARCHY_PATH=/usr/share/omarchy` and `-p /usr/share/omarchy/shell`; shell IPC
  returns `ok`; Hyprland PID 439, LightDM, sshd and recovery access remain;
  the top bar/menu are visible and the operator reports a responsive desktop;
  UART has no GPU reset, page fault, kernel panic, ext4 or USB fault
- timeout: 4 minutes
- rollback: after closing A4, stop only the native transient user service and
  start one portable transient service with the accepted portable
  `OMARCHY_PATH`, PATH, launcher and shell tree. Do not restart LightDM
- stop condition: one shell stop/start only. No compositor reload/restart,
  config pointer change, package transaction, service/system change, reboot,
  payload or retry belongs to A4
- operator action: after the shell returns, move the pointer and press
  `Super+Space` once; report whether the top bar, Omarchy menu and desktop are
  visible and responsive
- result: the portable launcher PID 5616 and Quickshell PID 5621 stopped once.
  Transient user unit `omarchy-ps4-native-shell.service` then started installed
  `/usr/bin/omarchy-launch-shell` PID 19768 and Quickshell PID 19771 with exact
  command `quickshell -n -p /usr/share/omarchy/shell`,
  `OMARCHY_PATH=/usr/share/omarchy` and native-first PATH. Shell IPC returned
  `ok`; `omarchy-background` and `omarchy-bar` layers exist; `hyprctl
  configerrors` is empty; Hyprland PID 439, LightDM, sshd and recovery status
  remained healthy; no new coredump appeared
- operator result: the operator observed no initial password/setup prompt. This
  is expected for A4: it replaced only the shell inside the existing `ps4`
  development session. Owner provisioning remained intentionally unarmed and
  no development account, autologin, SSH identity or recovery path was removed
- bounded UART context:
  [`20260814_030341_403490-exp-20260814-001-a4-launch-installed-native-rc3-quattro-shell-800819f9.md`](../../ps4-uart/sessions/20260814_030341_403490-exp-20260814-001-a4-launch-installed-native-rc3-quattro-shell-800819f9.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- UART conclusion: completed continuity with only expected SSH/recovery session
  lifecycles. No GPU, kernel, ext4, USB, display-manager or service fault
  appeared
- rollback: not applied. The native shell transient remains active and the
  exact portable runtime remains present. Recovery requires stopping only
  `omarchy-ps4-native-shell.service` and starting one portable shell supervisor
  in a new bounded action
- next action: owner direction is required. A safe first-owner UX preview may
  render the setup form without creating an account or touching the current
  root. Actual gift finalization remains clone-only because it removes the
  development account, autologin, SSH host identity and machine identity

### EXP-20260814-001-A5 — capture current native RC3 desktop for README

- state: complete — pass
- question: can the accepted live 1920×1080 Omarchy desktop be captured through
  the existing Wayland session for project documentation without changing the
  visible session or hardware state?
- changed variable: none; read-only screenshot export only. Run the installed
  screenshot client inside the current `ps4` Wayland environment, write one
  temporary PNG, copy it to the repository and remove the temporary file. Do
  not open a menu, move input, reload shell/compositor, change configuration,
  install a package, restart a service, reboot or send a payload
- expected evidence: PNG is exactly 1920×1080 and visually shows the current
  Quattro RC3 desktop; Hyprland PID 439 and native Quickshell PID 19771 remain;
  shell IPC, LightDM, sshd and recovery status stay healthy; UART continuity is
  completed with no GPU, filesystem or USB fault
- timeout: 2 minutes
- rollback: remove only the temporary remote PNG if copying fails. The final
  repository image is documentation and does not affect the console
- stop condition: if no installed Wayland screenshot client exists, close A5
  without installing one. Any visual composition or desktop interaction is a
  separate experiment
- operator action: none; leave the displayed desktop untouched during capture
- result: installed `/usr/bin/grim` captured one exact 1920×1080, 8-bit RGB PNG
  from the existing Wayland display. Local and remote SHA-256 both equal
  `79938b462f8f34177dd8f814bf4856c50acac7906d0ca36a104d5d78abf65941`.
  Visual review shows the current Tokyo Night Quattro desktop, top bar and PS4
  Fastfetch identity; no menu or window was opened for composition
- preservation evidence: Hyprland PID 439 and native Quickshell PID 19771 with
  `-p /usr/share/omarchy/shell` remained; shell IPC returned `ok`; LightDM and
  sshd remained active. The remote temporary PNG was removed after its verified
  copy became `docs/assets/omarchy-ps4-quattro.png` (captured during the
  prerelease acceptance run)
- bounded UART context:
  [`20260814_032728_511428-exp-20260814-001-a5-capture-current-native-rc3-desktop-for-readm-e0806ec2.md`](../../ps4-uart/sessions/20260814_032728_511428-exp-20260814-001-a5-capture-current-native-rc3-desktop-for-readm-e0806ec2.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- UART conclusion: completed continuity with three clean `ps4` SSH session
  lifecycles only. No GPU, kernel, ext4, USB, display-manager or service fault
  appeared
- rollback: not required. The screenshot is documentation only and the console
  remains on the accepted native RC3 shell
- next action: publish the reviewed repository changes and screenshot on the
  existing `agent/full-omarchy-port` branch, after local validation and secret
  review

### EXP-20260813-001-A31 — disable Quattro automatic idle service

- state: complete — pass
- question: does deploying the source-owned PS4 shell profile and hot-reloading
  its configuration disable only automatic idle/screensaver/lock before theme
  work, without restarting the shell or compositor?
- changed variable: installed portable `config/omarchy/shell.json` only — add
  `omarchy.idle` to `disabledPlugins`, then call shell `reloadConfig` once. Keep
  manual lock, Hyprsunset block, layout and every other plugin/config value
  unchanged
- source evidence: corrected portable archive SHA-256 is
  `e62c825a3685284fc4e8605097b468d1176f30b820c7c0e8cc2b1ab96e64bfa8`;
  bundle/package tests require the idle service to be disabled
- expected evidence: installed file matches source; Quickshell PID 524 and
  Hyprland PID 439 remain; shell IPC stays `ok`; `omarchy-shell idle status`
  returns target-not-found/not-running after reload; no screensaver or lock
  process exists
- timeout: 3 minutes
- rollback: restore the exact pre-A31 shell JSON and call `reloadConfig`
  once. No process restart belongs to rollback
- stop condition: no theme, wallpaper, border, gamma, VRR, scale or package
  change belongs to this precondition experiment
- bounded UART context:
  [`20260813_221712_137027-exp-20260813-001-a31-disable-quattro-automatic-idle-service-feadb7cb.md`](../../ps4-uart/sessions/20260813_221712_137027-exp-20260813-001-a31-disable-quattro-automatic-idle-service-feadb7cb.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `f9d6fea5361b45449a0948ab0457f00c`, epoch `1`
- result: pass. Installed shell JSON matches source SHA-256
  `16ba16d951108165777c3ad533a395612956c5c45b301d2d6e0ba661f6570264`,
  includes `omarchy.idle` in `disabledPlugins`, and one shell `reloadConfig`
  returned `ok`
- acceptance evidence: idle IPC now returns `Target not found`; no screensaver
  process runs; Hyprland PID 439 and Quickshell PID 524 stayed unchanged; shell
  IPC returns `ok`. Manual lock was not disabled
- UART conclusion: completed continuity across the configuration hot reload;
  no display transition or hardware fault appeared
- rollback: not applied. Exact prior JSON is preserved under
  `/home/ps4/.local/state/omarchy-ps4/portable/EXP-20260813-001-A31-20260813T161900Z/`
- next action: initialize Tokyo Night plus one wallpaper as A32

### EXP-20260813-001-A45 — accept persistent native Omarchy boot splash

- state: planned; do not begin while A44 remains planned/active
- question: does the initramfs renderer keep the native Omarchy wordmark and
  progress line visible through framebuffer mode changes until the validated
  root hands off to systemd, without hiding UART evidence or blocking boot?
- changed variable: boot initramfs only — stage the locally verified artifact
  with SHA-256
  `acc08b4bbcb0535780161537033dc4a58d5b99a9fba659e23466bea95329d0ab`.
  Keep the accepted kernel, product boot arguments, root filesystem, VRAM,
  packages, display configuration and monitor settings unchanged
- source evidence: final renderer SHA-256 is
  `2124d28c21de2b2d96d0e9296fd51a9ccaf901bd8395645b3ee9df950bb11cc9`;
  embedded alpha mask is
  `fe3b19a33bae79976f8cb27269facee14aff23a5f73739fde8d7d18717b88eac`;
  its source PNG is the exact Quattro RC3 native Plymouth logo at upstream
  commit `144f4d1e31d6ddc2cba5dfd69278cabf02bafd05`, SHA-256
  `ba8f1547a02ab5db64fe3923d0b834a220e2c3798c1674374a0eb92a18dfddfb`
- expected evidence: HDMI displays a centered green `OMARCHY` wordmark on the
  Tokyo Night background and a restrained progress line; transient fbcon or
  modeset writes are repainted within one second; the splash stops immediately
  before `switch_root`; graphical Linux reaches the accepted session; UART
  retains kernel/initramfs messages and contains no new GPU, USB, ext4 or boot
  fault
- timeout: 4 minutes after payload delivery
- rollback: restore the exact pre-A45 initramfs and its manifest entry from the
  bounded staging backup, leaving kernel and boot arguments untouched
- stop condition: no kernel, command-line, rootfs, package, session or monitor
  change belongs to A45. If the red failure state appears, preserve UART
  evidence rather than retrying; use the unchanged debug profile later if HDMI
  error text is required
- operator action: after the bounded session is active and the artifact is
  staged, boot Linux once and report the splash appearance, whether anything
  overwrites it for longer than one second, and the final desktop outcome

### EXP-20260814-002-A1 — stage audited UI-only FPKG in GoldHEN

- state: complete — pass
- question: is the console currently in the operator-reported Orbis/GoldHEN
  runtime, and can the exact audited UI-only package be staged under
  `/data/pkg` without touching PS4BOOT, OMARCHY-PS4, boot files or any existing
  installed title?
- changed variable: create or reuse `/data/pkg` and upload exactly
  `IV0000-BREW09004_00-OMARCHYPS4UI0000.pkg`, 6.3 MiB, SHA-256
  `0e59847d8d3107fd183175fdca31285808e694b0135a7834e80fdecab4d97d5e`.
  No Package Installer selection, title installation, application launch,
  payload, boot, USB write or GoldHEN setting change belongs to A1
- source evidence: OpenOrbis package validation and extraction audit pass;
  exactly 16 normalized 1920x1080 wallpapers are present; no loader, payload,
  kernel, initramfs, rootfs, release bundle, network client or PayLoader string
  is packaged
- expected evidence: anonymous FTP at `192.168.50.215:2121` is reachable;
  upload completes to `/data/pkg`; a streamed reread returns the exact package
  SHA-256 and size; UART continuity remains `completed` with no panic, storage
  or service fault
- timeout: 3 minutes while transfer makes forward progress
- rollback: if upload or verification fails, remove only the exact partial A1
  destination before closing the session. After a successful A1, keep the
  staging file for A2; removing it after installation is a later bounded action
- stop condition: close and review A1 before opening Debug Settings or Package
  Installer. Any need to return from Linux to Orbis closes A1 without upload
- operator action: none; leave the current screen untouched during transfer
- result: anonymous GoldHEN FTP was reachable at `192.168.50.215:2121`. The
  exact package uploaded to `/data/pkg` in one transfer, and the remote listing
  reported 6,619,136 bytes. Streaming the staged file back through FTP returned
  SHA-256
  `0e59847d8d3107fd183175fdca31285808e694b0135a7834e80fdecab4d97d5e`,
  exactly matching the locally audited build
- bounded UART context:
  [`20260814_124655_026989-exp-20260814-002-a1-stage-audited-ui-only-fpkg-in-goldhen-821deead.md`](../../ps4-uart/sessions/20260814_124655_026989-exp-20260814-002-a1-stage-audited-ui-only-fpkg-in-goldhen-821deead.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `ac7a80625286433a86e5323e6136e68d`, epoch `1`
- UART conclusion: completed continuity with ordinary Orbis shell screensaver
  and memory telemetry only. No panic, filesystem, storage, USB or service
  fault appeared
- rollback: not applied. The exact verified staging file remains under
  `/data/pkg` for the next bounded installation action
- next action: A2 may select GoldHEN's HDD `/data/pkg` package source only;
  installation remains A3 and launch remains A4

### EXP-20260814-002-A2 — select GoldHEN internal package source

- state: complete — degraded (planned source-selection scope was crossed)
- question: can GoldHEN select its documented HDD package source
  `/data/pkg` without installing, launching or otherwise changing a title?
- changed variable: Package Installer source setting only, from its current
  value to HDD `/data/pkg` if needed. Do not select the staged package, confirm
  installation, launch an app, send a payload, boot Linux or modify USB
- expected evidence: the Package Installer source visibly reads HDD
  `/data/pkg`; UART continuity remains completed without a shell crash or panic
- timeout: 2 minutes, operator-paced
- rollback: if the setting causes an error, restore its exact prior value before
  closing A2. A successful HDD selection remains in place through A3, then may
  be restored in a later bounded cleanup action
- stop condition: close and review immediately after reporting the visible
  source setting. Opening/selecting an actual PKG is outside A2
- operator action: after the bounded marker is active, open GoldHEN Debug
  Settings, set Package Installer source to HDD `/data/pkg`, then stop without
  choosing a package and report the exact on-screen source text
- operator report: the operator installed and launched the staged title, then
  reported `ok loaded nice`; this is positive visual evidence for the UI but
  crossed the declared A2 stop condition
- result: GoldHEN installed `BREW09004` from the exact 6,619,136-byte staged
  package. UART recorded `sceAppInstaller::AppInstallApp=0`, task error `0x0`,
  and a 4.961-second install. Orbis then launched `BREW09004` v0.11 and executed
  `/app0/eboot.bin` as PID 73 without a panic or application crash. The title's
  first read-only SaveData mount and its later create/read-write mount both
  failed: internal result `0x809f8022`, mapped result `0x809f0008`. The rendered
  UI is accepted for this private prototype, but theme persistence is not
  accepted
- bounded UART context:
  [`20260814_124817_164170-exp-20260814-002-a2-select-goldhen-internal-package-source-973f6236.md`](../../ps4-uart/sessions/20260814_124817_164170-exp-20260814-002-a2-select-goldhen-internal-package-source-973f6236.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `ac7a80625286433a86e5323e6136e68d`, 51,840-byte raw slice
- UART conclusion: continuity is valid and install/launch behavior is normal,
  but A2 cannot be classified as a strict pass because multiple unplanned
  operator actions occurred and SaveData persistence failed
- rollback: not applied. The installed v0.11 title is a UI-only prototype and
  does not contain a payload, kernel, initramfs or rootfs; the staged package
  remains under `/data/pkg`
- next action: local-only v0.12 work must load and initialize the PS4 SaveData
  module correctly, rebuild, audit, and preserve UI-only scope. A later console
  update must receive its own bounded experiment ID

### EXP-20260814-003-A1 — stage audited private UI-only FPKG v0.12

- state: complete — degraded (staging passed; isolation condition was crossed)
- question: can GoldHEN FTP replace the staged v0.11 package with the exact
  locally audited v0.12 package without installing, launching or modifying any
  other console path?
- changed variable: the single regular file
  `/data/pkg/IV0000-BREW09004_00-OMARCHYPS4UI0000.pkg`, from the prior v0.11
  bytes to the audited v0.12 bytes. No title installation state, boot file,
  payload, USB path or system setting may change
- local input: 6,684,672 bytes; SHA-256
  `5fc3d24a3a61b4ed04fd7422ccccb0a9a9b50591ab44f92eefa832cc30d8146a`
- expected evidence: the prior remote file is preserved locally before the
  write; one FTP upload completes; remote listing reports 6,684,672 bytes; a
  streamed read-back produces the exact local SHA-256; UART continuity remains
  completed without a shell crash, storage error or panic
- timeout: 3 minutes for FTP reachability and 5 minutes total
- rollback: keep the read-only local copy of the prior staged file. If upload
  or verification fails, do not install or launch; restore that exact backup to
  the same remote path and reverify its size/hash before closing the experiment
- stop condition: close and review immediately after exact remote verification.
  Opening Package Installer, installing v0.12 or launching the title is outside
  A1
- operator action: none during transfer; leave the current Orbis screen and
  controller untouched
- result: before writing, the prior staged v0.11 package was preserved locally
  as 6,619,136 bytes with SHA-256
  `0e59847d8d3107fd183175fdca31285808e694b0135a7834e80fdecab4d97d5e`.
  One GoldHEN FTP upload replaced the target. FTP then reported a
  `Content-Length` of 6,684,672 bytes, and a complete streamed read-back
  produced SHA-256
  `5fc3d24a3a61b4ed04fd7422ccccb0a9a9b50591ab44f92eefa832cc30d8146a`,
  exactly matching the locally audited v0.12 package
- local rollback copy:
  `backups/fpkg-stage/2026-08-14/IV0000-BREW09004_00-OMARCHYPS4UI0000-v0.11.pkg`
- bounded UART context:
  [`20260814_141020_319204-exp-20260814-003-a1-stage-audited-private-ui-only-fpkg-v0-12-337661e4.md`](../../ps4-uart/sessions/20260814_141020_319204-exp-20260814-003-a1-stage-audited-private-ui-only-fpkg-v0-12-337661e4.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `ac7a80625286433a86e5323e6136e68d`, epoch `1`
- UART conclusion: continuity is valid and no package install, title launch,
  storage error, shell crash or panic appeared. The slice does contain ordinary
  navigation from Package Installer options back to GoldHEN Debug Settings,
  contrary to the declared untouched-screen condition. That unplanned UI
  action makes experimental isolation degraded but does not invalidate the
  independently exact FTP size/hash evidence
- rollback: not applied; v0.12 is the exact verified staged file and v0.11 is
  preserved locally for recovery
- next action: stop. Do not install or launch until the owner explicitly asks
  and a new bounded experiment is declared

### EXP-20260821-001-A1 — read-only GoldHEN and PS4BOOT preflight

- state: complete — pass
- question: before attempting one Linux boot, do the current GoldHEN runtime,
  PayLoader service and attached `PS4BOOT` volume still expose the exact
  previously accepted boot chain without changing console state?
- changed variable: none. Perform only one loopback PayLoader status read and
  read-only FTP listing/streaming of `/mnt/usb0/SHA256SUMS`, `bzImage`,
  `initramfs.cpio.gz`, `bootargs.txt` and `vram.txt`. Do not upload, delete,
  rename, install, launch the manager, send a payload, reboot, power-cycle or
  change any GoldHEN, USB or Orbis setting
- expected evidence: PayLoader reports ready; `/mnt/usb0` exposes one complete
  boot set; streamed hashes match kernel
  `b54490ed1f5d12432bf4ead11f27f1cf8aed008f0b76787c0060141b97414614`,
  initramfs
  `307fcce4d3a4893fb9a729c9c43dec886979afe088e7d6f44e430e1132709264`,
  product boot arguments
  `3c023f27188299545d4929adfa9c2738f01f6a5108a706135516b23a9d27ee2c`,
  and `vram.txt=1024`; UART continuity remains completed without reconnect,
  panic, filesystem, USB or storage fault
- timeout: 3 minutes
- rollback: none because A1 is read-only. If any endpoint, file, size, hash or
  continuity check fails, close A1 as fail or inconclusive and do not send the
  loader
- stop condition: close and review A1 before any payload connection. A Linux
  boot belongs only to separately declared `EXP-20260821-001-A2`
- operator action: none; leave the current Orbis screen, USB and controller
  untouched during the preflight
- result: pass. `http://192.168.50.215:9090/status` returned
  `{ "status": "ready" }`; anonymous FTP listed one complete boot set under
  `/mnt/usb0`. Streaming each file returned the exact expected SHA-256 for
  `bzImage`, `initramfs.cpio.gz`, `bootargs.txt` and `vram.txt`, and the remote
  `SHA256SUMS` listed the same four digests. `vram.txt` contains `1024`; the
  product command line retains `root=LABEL=OMARCHY-PS4`, `rootwait`,
  `pci=nocrs intremap=off` and `libata.force=1.00:disable`
- bounded UART context:
  [`20260821_195003_680204-exp-20260821-001-a1-read-only-goldhen-and-ps4boot-preflight-4734703d.md`](../../ps4-uart/sessions/20260821_195003_680204-exp-20260821-001-a1-read-only-goldhen-and-ps4boot-preflight-4734703d.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event
  sidecar, generation `266b3d42494146d1afa5f4028ab6cfcf`, epoch `1`
- UART conclusion: completed continuity with ordinary Orbis heap/network
  telemetry only. No logger restart, serial reconnect, panic, filesystem, USB
  or storage fault appeared
- rollback: none required; A1 made no changes
- next action: `EXP-20260821-001-A2` may send the unchanged pinned v25
  1024 MiB loader exactly once, then stop and review before any recovery action

### EXP-20260821-001-A2 — boot current USB through one pinned loader send

- state: complete — pass
- question: does one unchanged launch of the pinned v25 1024 MiB loader boot
  the currently attached, preflight-verified `PS4BOOT` set into the existing
  external `OMARCHY-PS4` Linux desktop?
- changed variable: one complete raw-socket send of exactly 320,936 bytes from
  `payloads/ps4-linux-loader/v25/elf/linux-1024mb.elf`, SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`,
  to the recorded console PayLoader address on port 9090. Do not reconnect,
  resend, change
  the FPKG, boot files, USB, VRAM, monitor, GoldHEN settings or PS4 power state
- precondition: A1 passed with PayLoader ready and exact accepted hashes for
  kernel, initramfs, product boot arguments and `vram.txt=1024`; continuous
  UART is READY and a fresh bounded A2 session must be active before the send
- expected evidence: GoldHEN accepts exactly one ELF; v25 identifies the tested
  firmware, Baikal and 1024 MiB VRAM; kexec enters Linux 6.18.44; initramfs finds
  `LABEL=OMARCHY-PS4`; systemd reaches the graphical target; HDMI shows the
  splash followed by the existing Omarchy desktop; UART shows no panic, ext4
  error, USB I/O fault or GPU reset/ring/page fault
- timeout: 5 minutes from the single send while UART makes forward progress
- rollback: no second payload. If the connection fails before acceptance,
  close A2 and restore PayLoader only in a separate action. If Linux stalls or
  fails after acceptance, preserve the visible and UART outcome, close A2,
  and declare any power-cycle or recovery as a separate experiment
- stop condition: exactly one payload connection and one boot observation.
  Installing/updating the manager, changing Linux configuration, rebooting,
  power-cycling or testing the unfinished FPKG Boot button is outside A2
- operator action: after A2 is active, do not press controller or keyboard
  buttons. Watch HDMI and report whether the Omarchy splash appears, whether
  the desktop appears, and any visible error, signal loss or corruption
- payload result: pass. The primary agent verified the local 320,936-byte ELF
  against its pinned SHA-256, opened exactly one raw TCP connection to the
  recorded console PayLoader address, and completed one `sendall()` with no
  retry or second connection. The loader reported the expected firmware,
  `VRAM 1024 MB`, Baikal and
  the exact 11,064,320-byte kernel plus 1,673,725-byte initramfs before kexec
- Linux result: pass. The initramfs resolved `LABEL=OMARCHY-PS4` to
  `/dev/sda2` at 11.570 seconds and mounted the expected ext4 UUID read/write.
  OpenSSH started at 18.547 seconds, LightDM at 18.619 seconds, the graphical
  target at 18.633 seconds, and system startup completed in 17.911 seconds
- operator report: `yes, i see omarchy`; HDMI therefore passed the declared
  visible desktop condition with no reported signal loss, error text, tiling
  or corruption
- bounded UART context:
  [`20260821_195134_364091-exp-20260821-001-a2-boot-current-usb-through-one-pinned-loader-s-cc8815d8.md`](../../ps4-uart/sessions/20260821_195134_364091-exp-20260821-001-a2-boot-current-usb-through-one-pinned-loader-s-cc8815d8.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event
  sidecar, generation `266b3d42494146d1afa5f4028ab6cfcf`, epoch `1`
- UART conclusion: completed continuity from the single PayLoader send through
  the visible graphical desktop. No kernel panic, ext4 error, USB I/O fault,
  AMDGPU reset/ring timeout/page fault or logger reconnect appeared. The
  downstream MT7668 driver retained its known verbose P2P/regulatory warnings
  while continuing through association; they did not block this boot
- rollback: none required. Linux remains running from the external USB root;
  internal PS4 storage and the UI-only FPKG were not modified
- next action: audit and build the latest pinned Omarchy gift snapshot plus a
  native boot-capable manager locally. Any root migration, FPKG installation
  or FPKG-triggered boot requires separately declared bounded experiments

### EXP-20260821-002-A1 — read-only stable Omarchy 4.0.0 migration preflight

- state: complete — pass
- question: is the running external USB system healthy, recoverable and ready
  for a narrow migration from the installed prerelease project packages to the
  locally built stable `4.0.0-1` package trio?
- changed variable: none. Use key-only SSH only to inspect the root device,
  filesystem, free space, installed project package versions, provisioning
  marker, active targets, Pacman lock and the existing restricted recovery
  status command. Do not transfer files, change configuration, run Pacman,
  restart a service or touch boot media
- expected evidence: `/` is the writable external ext4 filesystem labeled
  `OMARCHY-PS4`; at least 2 GiB is free; the three project packages are the
  expected prerelease versions; no Pacman lock or provisioning marker exists;
  `sshd`, LightDM and `graphical.target` are active; the independently armed
  recovery status command succeeds; UART remains continuous without a GPU,
  USB, ext4 or kernel fault
- timeout: 3 minutes
- rollback: none because the action is read-only. Any failed invariant blocks
  package transfer and installation
- stop condition: close and review before staging any stable package. Package
  transfer and installation require a separate bounded action
- operator action: leave the visible Omarchy desktop, keyboard, USB and
  controller untouched; report any blanking, corruption or visible error
- result: pass. `/` is `/dev/sda2`, ext4, label `OMARCHY-PS4`, read-write, with
  107,246,399,488 bytes available. The running kernel is
  `6.18.44-ps4-baikal`; `omarchy-ps4`, `omarchy-ps4-settings` and
  `omarchy-ps4-provisioning` are each `4.0.0rc3-1`. The provisioning marker
  and Pacman lock are absent. `sshd`, LightDM and `graphical.target` are active;
  `omarchy-recovery` UID 1001 completed its permitted root/device, package and
  recovery-status check
- bounded UART context:
  [`20260821_200303_417442-exp-20260821-002-a1-read-only-stable-omarchy-4-0-0-migration-pre-c11ae42f.md`](../../ps4-uart/sessions/20260821_200303_417442-exp-20260821-002-a1-read-only-stable-omarchy-4-0-0-migration-pre-c11ae42f.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event
  sidecar, generation `266b3d42494146d1afa5f4028ab6cfcf`, epoch `1`
- UART conclusion: completed continuity. UART shows only clean SSH session
  creation and teardown for the `ps4` and recovery users; no kernel, GPU,
  filesystem, USB or service fault appeared
- rollback: none required; no console state changed
- next action: locally verify a stable migration bundle and its exact
  transaction. Only then may a fresh bounded action transfer and install the
  three `4.0.0-1` packages

### EXP-20260821-002-A2 — stage checksum-verified stable 4.0.0 migration bundle

- state: complete — pass
- question: can the exact locally tested stable migration bundle be staged in
  the development user's external-root home and fully verified without running
  a package or recovery transaction?
- changed variable: create only
  `/home/ps4/omarchy-ps4-dev/releases/stable-4.0.0`, upload the 252,334,028-byte
  archive as a temporary name, verify SHA-256, rename it, extract it beneath
  that directory and run its read-only manifest policy check. Do not run sudo,
  Pacman, recovery update, service change, boot-file write or desktop restart
- expected evidence: remote archive SHA-256 equals
  `d33048fdbab2bab947a8b574a748b994327246b0d299e2a09689c80d5d81f709`;
  manifest verification passes; the extracted repository contains exactly the
  three stable project packages plus pinned `desktop-file-utils`,
  `xdg-user-dirs` and `xdg-utils`; UART stays continuous without USB, ext4,
  kernel or GPU failure
- timeout: 5 minutes
- rollback: remove only the newly created stable staging directory in a later
  declared action if transfer, hash or manifest verification fails. Do not
  install from an incomplete or mismatched directory
- operator action: leave the desktop, keyboard, controller and USB untouched;
  report any visible error or corruption
- result: pass. One SSH copy completed. The remote archive is exactly
  252,334,028 bytes with the expected SHA-256; extraction and the bundle's full
  content manifest passed. All six intended package files were listed. An
  initial read-back command failed before rename/extraction because its remote
  `awk` field was incorrectly shell-expanded; the corrected read used Bash
  `read`, the transfer bytes were not repeated, and the exact digest then
  passed
- bounded UART context:
  [`20260821_201938_933994-exp-20260821-002-a2-stage-checksum-verified-stable-4-0-0-migrati-d6bd07b1.md`](../../ps4-uart/sessions/20260821_201938_933994-exp-20260821-002-a2-stage-checksum-verified-stable-4-0-0-migrati-d6bd07b1.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event
  sidecar, generation `266b3d42494146d1afa5f4028ab6cfcf`, epoch `1`
- UART conclusion: completed continuity with clean SSH session teardown and
  only the known MT7668 trace/roaming messages. No kernel, ext4, USB, GPU or
  service fault appeared
- rollback: not applied; the exact verified bundle remains staged for the next
  recovery-command action
- next action: update only the restricted recovery command and record the
  installed predecessor version before any stable package transaction

### EXP-20260821-002-A3 — update restricted recovery command for stable migration

- state: complete — blocked before change; sudo authentication is required
- question: can the already-armed recovery path replace only its restricted
  command with the locally rehearsed version that accepts either the recorded
  predecessor or stable `4.0.0-1`, while preserving key-only SSH and denying
  general sudo?
- changed variable: intended but not applied —
  `/usr/local/sbin/omarchy-ps4-dev-recovery` plus the root-owned recovery marker
  recording the exact installed predecessor version. No package, service,
  account, sudo policy, boot file or desktop change is allowed
- expected evidence: the new command SHA-256 is
  `a7fe6b08e6ec7c866e1647aaf72818e962822a1bc1b2c4d27e46b1d8986e5b75`;
  the marker records the pre-migration foundation version; a fresh recovery
  status login succeeds; arbitrary sudo remains denied
- timeout: 3 minutes
- rollback: if the authenticated update starts and fails, restore the exact
  command and marker copies written by `arm-recovery` into its root-only
  evidence directory. Do not begin stable package installation
- operator action: none in this attempt
- result: blocked before change. The `ps4` account's non-interactive sudo
  correctly returned `a password is required`; key-only root SSH correctly
  returned permission denied. No privileged command ran and the old restricted
  recovery command and marker remain unchanged
- bounded UART context:
  [`20260821_202200_701774-exp-20260821-002-a3-update-restricted-recovery-command-for-stabl-ae873249.md`](../../ps4-uart/sessions/20260821_202200_701774-exp-20260821-002-a3-update-restricted-recovery-command-for-stabl-ae873249.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event
  sidecar, generation `266b3d42494146d1afa5f4028ab6cfcf`, epoch `1`
- UART conclusion: completed continuity. UART shows one clean `ps4` SSH session
  and only known MT7668 roaming traces; no package, service, filesystem, USB,
  GPU or kernel event occurred
- rollback: not required because the intended variable did not change
- next action: in a fresh bounded session, the operator must run the one staged
  `arm-recovery --apply` command in the visible terminal and enter the existing
  `ps4` sudo password. Close and verify before package installation

### EXP-20260821-002-A4 — operator-authenticated stable recovery command update

- state: complete — aborted before operator action; no console state changed
- question: can the operator authenticate the already staged
  `arm-recovery --apply` command so the restricted recovery path can be updated
  for the stable migration?
- changed variable: intended but not applied — the restricted recovery command
  and its root-owned predecessor marker only
- expected evidence: authenticated command success, exact command and marker
  hashes, a successful recovery-status login and continued denial of arbitrary
  sudo
- timeout: 3 minutes
- rollback: restore the exact root-owned command and marker backups if the
  authenticated update begins but fails; no rollback is required if it never
  begins
- operator action: not performed. The discussion moved to end-user
  installation architecture before the sudo command was started
- result: aborted. No authenticated command, package transaction, service
  change, boot-file write or desktop restart occurred
- bounded UART context:
  [`20260821_202403_878257-exp-20260821-002-a4-operator-authenticated-stable-recovery-comma-f7bfb7dd.md`](../../ps4-uart/sessions/20260821_202403_878257-exp-20260821-002-a4-operator-authenticated-stable-recovery-comma-f7bfb7dd.md),
  exact sibling `.raw`; evidence state `aborted`, empty logger-event sidecar,
  generation `266b3d42494146d1afa5f4028ab6cfcf`, epoch `1`
- UART conclusion: continuity remained intact. The slice contains only known
  MT7668 roaming traces; no authenticated action or kernel, ext4, USB, GPU or
  service fault occurred
- rollback: not required because the intended variable did not change
- next action: stop hardware work while the end-user installation architecture
  is decided. Any later migration attempt requires a fresh bounded session

### EXP-20260821-003-A1 — stage audited OMCH42069 kernel-manager FPKG

- state: complete — pass
- question: can the exact audited `OMCH42069` v0.15 kernel-manager FPKG be
  uploaded to GoldHEN `/data/pkg` and read back byte-for-byte without
  installing or launching it?
- changed variable: create only
  `/data/pkg/omarchy-ps4-v0.15-OMCH42069-beta.pkg`, first under a `.partial`
  name and then by same-directory rename after an exact read-back check. The
  local source is 20,119,552 bytes with SHA-256
  `82ad5425ea9d5ae95446918c7b38b4f67948f1834fb1693561290ae277098636`
- preconditions: continuous UART is READY on `/dev/cu.wchusbserial3130`, no
  bounded session is active, the operator reports GoldHEN and FTP active, and
  the flashed Omarchy USB remains untouched
- expected evidence: anonymous FTP at `192.168.50.215:2121` accepts one
  package upload; a single read-back has the exact local byte count and
  SHA-256; rename succeeds; UART continuity remains completed with no PS4,
  storage or filesystem fault
- timeout: 5 minutes
- rollback: if transfer or verification fails, remove only the newly created
  `.partial` file, or the final file if and only if it fails the exact
  verification. Do not alter any other `/data/pkg` entry
- stop condition: close and review the bounded session immediately after the
  verified rename or failure. Installing, launching, sending a loader,
  changing the USB or changing boot files is outside this action
- operator action: leave Orbis and GoldHEN idle; do not open Package Installer
  or launch Omarchy during A1. Report any visible error, notification,
  controller disconnect or unexpected screen change
- result: pass. Anonymous GoldHEN FTP accepted one upload to the declared
  `.partial` name. The remote temporary file was exactly 20,119,552 bytes; one
  complete FTP read-back produced SHA-256
  `82ad5425ea9d5ae95446918c7b38b4f67948f1834fb1693561290ae277098636`.
  Only after that match, FTP renamed it within `/data/pkg` to
  `omarchy-ps4-v0.15-OMCH42069-beta.pkg`; its final reported size remained
  20,119,552 bytes. No installation, launch, payload send, USB access or boot
  file change occurred
- bounded UART context:
  [`20260821_232213_928802-exp-20260821-003-a1-stage-audited-omch42069-kernel-manager-fpkg-1e90f8a9.md`](../../ps4-uart/sessions/20260821_232213_928802-exp-20260821-003-a1-stage-audited-omch42069-kernel-manager-fpkg-1e90f8a9.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event
  sidecar, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity. The slice contains four routine
  Orbis `SceWorkaroundCtl`/`SceShellCore` lines and no package, storage,
  filesystem, kernel or logger fault. No separate visible operator anomaly
  was reported before session close
- rollback: none required; the exact verified final package remains staged
- next action: installing `OMCH42069` from Package Installer requires a fresh
  `EXP-20260821-003-A2` bounded session and an explicit operator action. Do not
  combine installation with first launch or Linux boot

### EXP-20260822-001-A1 — stage audited OMCH42069 v0.19 FPKG

- state: complete — aborted before hardware action; no FTP connection or
  upload occurred
- question: can the exact audited `OMCH42069` v0.19 kernel-manager FPKG be
  uploaded to GoldHEN `/data/pkg` and read back byte-for-byte without
  installing or launching it?
- changed variable: create only
  `/data/pkg/omarchy-v0.19-OMCH42069-beta.pkg`, first under a `.partial` name
  and then by same-directory rename after an exact read-back check. The local
  source is 20,905,984 bytes with SHA-256
  `b1ddd4eca8eda76bfdc0803cb3883cb2845fcfa5c6b6d17db5af5531c2eaed97`
- preconditions: continuous UART is READY on `/dev/cu.wchusbserial3130`, no
  bounded session is active, the v0.19 package audit passed, and the flashed
  Omarchy USB remains untouched
- expected evidence: anonymous FTP at `192.168.50.215:2121` accepts one
  package upload; a single read-back has the exact local byte count and
  SHA-256; rename succeeds; UART continuity remains completed with no console,
  storage or filesystem fault
- timeout: 5 minutes
- rollback: if transfer or verification fails, remove only the newly created
  `.partial` file, or the final file if and only if it fails exact verification.
  Do not alter any other `/data/pkg` entry
- stop condition: close and review the bounded session immediately after the
  verified rename or failure. Installing, launching, sending a loader,
  changing the USB or changing boot files is outside this action
- operator action: leave Orbis and GoldHEN idle; do not open Package Installer
  or launch Omarchy during A1. Report any visible error, notification,
  controller disconnect or unexpected screen change
- result: aborted. The local transfer command was rejected before execution,
  and the operator redirected work back to interface design. No FTP connection,
  package upload, rename, installation, launch, payload send, USB access or
  boot-file change occurred
- bounded UART context:
  [`20260822_001703_416435-exp-20260822-001-a1-stage-audited-omch42069-v0-19-fpkg-a3e1a963.md`](../../ps4-uart/sessions/20260822_001703_416435-exp-20260822-001-a1-stage-audited-omch42069-v0-19-fpkg-a3e1a963.md),
  exact sibling `.raw`; evidence state `aborted`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: continuity remained intact. The slice contains routine Orbis
  shell/RNPS maintenance messages and no package, storage, filesystem, kernel
  or logger fault
- rollback: not required because no hardware-side action began
- next action: continue local UI work. Any later FTP staging or installation
  requires a fresh bounded experiment

### EXP-20260822-002-A1 — stage audited OMCH42069 v0.20 FPKG

- state: complete — pass
- question: can the exact audited `OMCH42069` v0.20 kernel-manager FPKG be
  uploaded to GoldHEN `/data/pkg` and read back byte-for-byte without
  installing or launching it?
- changed variable: create only
  `/data/pkg/omarchy-v0.20-OMCH42069-beta.pkg`, first under a `.partial` name
  and then by same-directory rename after an exact read-back check. The local
  source is 20,905,984 bytes with SHA-256
  `3dae32b7869b662f69e031e82ff65fe25f0bde42c0d64a6ee9d2af8448db2a9e`
- preconditions: continuous UART is READY on `/dev/cu.wchusbserial3130`, no
  bounded session is active, the v0.20 package audit passed, and the flashed
  Omarchy USB remains untouched
- expected evidence: anonymous FTP at `192.168.50.215:2121` accepts one
  package upload; one read-back has the exact local byte count and SHA-256;
  rename succeeds; UART continuity remains completed without console, storage
  or filesystem fault
- timeout: 5 minutes
- rollback: if transfer or verification fails, remove only the newly created
  `.partial` file, or the final file if and only if it fails exact verification.
  Do not alter any other `/data/pkg` entry
- stop condition: close and review immediately after verified rename or
  failure. Installation, launch, loader send, USB access and boot-file changes
  are outside this action
- operator action: leave Orbis and GoldHEN idle; do not open Package Installer
  or launch Omarchy during A1. Report any visible error, notification,
  controller disconnect or unexpected screen change
- result: pass. Anonymous GoldHEN FTP accepted one upload to the declared
  `.partial` name. One complete read-back was exactly 20,905,984 bytes with
  SHA-256
  `3dae32b7869b662f69e031e82ff65fe25f0bde42c0d64a6ee9d2af8448db2a9e`,
  exactly matching the audited local v0.20 package. FTP then renamed it within
  `/data/pkg` to `omarchy-v0.20-OMCH42069-beta.pkg`; the partial name no longer
  appeared. No installation, launch, loader send, USB access or boot-file
  change occurred
- bounded UART context:
  [`20260822_002212_182066-exp-20260822-002-a1-stage-audited-omch42069-v0-20-fpkg-64a821d2.md`](../../ps4-uart/sessions/20260822_002212_182066-exp-20260822-002-a1-stage-audited-omch42069-v0-20-fpkg-64a821d2.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity. The slice contains routine Orbis shell
  heap/VM telemetry and no package, filesystem, storage, kernel or logger fault
- rollback: none required; the exact verified package remains staged at the
  declared final path
- next action: installing or replacing `OMCH42069` through Package Installer
  requires a separate bounded operator-action session. Do not combine install
  with launch or Linux boot

### EXP-20260822-002-A2 — install v0.20 over existing OMCH42069 app

- state: complete — degraded; v0.20 installed and launched, but the operator
  path deleted/reinstalled the app and exceeded the install-only boundary
- question: does Package Installer accept the higher-version v0.20 FPKG with
  the same `OMCH42069` title/content identity as an in-place replacement while
  preserving application SaveData and without launching the app?
- changed variable: install only the already verified
  `/data/pkg/omarchy-v0.20-OMCH42069-beta.pkg` through the console Package
  Installer. Do not launch Omarchy, stage boot files, send a loader, touch the
  USB or alter any other package
- expected evidence: Package Installer reports success as an update/replace;
  one Omarchy icon remains; no delete-data prompt is accepted; UART continuity
  is completed and shows no package database, filesystem or kernel fault
- timeout: 5 minutes
- rollback: if installation fails before replacement, leave the current app
  untouched. If v0.20 installs but later proves unusable, reinstall the exact
  staged v0.15 package only in a separately declared rollback session. Do not
  delete app SaveData
- stop condition: cancel immediately if the UI requires deleting the current
  application or saved data. Otherwise close and review immediately after the
  install succeeds or fails; do not launch Omarchy in A2
- operator action: open GoldHEN Package Installer, select
  `omarchy-v0.20-OMCH42069-beta.pkg`, and accept only an install/update/replace
  prompt. Do not accept deletion of the current app or SaveData. Report the
  exact prompt/result and any visible error, then leave Omarchy closed
- result: degraded. UART first recorded
  `SCE_BGFT_ERROR_SAME_APPLICATION_ALREADY_INSTALLED`. The subsequent UI path
  entered the content-delete flow, suspended/killed/deleted `OMCH42069`,
  installed one 20,119,552-byte package, entered delete flow again, and then
  installed the intended 20,905,984-byte v0.20 package successfully with
  `sceAppInstaller::AppInstallApp(...)=0x00000000`. The console then launched
  `OMCH42069`, exceeding the declared install-only stop condition. Final UART
  identity is content ID `IV0000-OMCH42069_00-OMARCHYPS4UI0000`, version
  `0.20`. The app reached Home with controller and framebuffer ready,
  `boot-files=missing`, Tokyo Night wallpaper index 0 loaded, and structured
  `[omarchy-ui]` logging active. No boot files were staged and Linux was not
  launched
- bounded UART context:
  [`20260822_002353_729035-exp-20260822-002-a2-install-v0-20-over-existing-omch42069-app-38aaac07.md`](../../ps4-uart/sessions/20260822_002353_729035-exp-20260822-002-a2-install-v0-20-over-existing-omch42069-app-38aaac07.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity. Final v0.20 startup and Home rendering
  are proven. No package database, filesystem, storage or kernel fault appears.
  GoldHEN's pre-existing missing `plugins.ini`/game-patch XML notices remain
  non-blocking. SaveData mount reported no existing `Settings` entry, so this
  session does not prove preference retention across deletion
- rollback: not applied because the intended v0.20 build is the final installed
  and running app. The internal boot set remains missing
- next action: return to local UI iteration. Any later v0.21 package install or
  launch requires a fresh bounded session and must not be combined with
  boot-file staging

### EXP-20260822-003-A1 — stage audited OMCH42069 v0.21 FPKG

- state: complete — pass
- question: can the exact audited `OMCH42069` v0.21 kernel-manager FPKG be
  uploaded to GoldHEN `/data/pkg` and read back byte-for-byte without
  installing or launching it?
- changed variable: create only
  `/data/pkg/omarchy-v0.21-OMCH42069-beta.pkg`, first under a `.partial` name
  and then by same-directory rename after exact read-back verification. The
  local source is 20,905,984 bytes with SHA-256
  `15dbca5a84a5b83a28508b12b14ae523050aee39677cc2de63e678705d60b086`
- preconditions: continuous UART is READY on `/dev/cu.wchusbserial3130`, no
  bounded session is active, the v0.21 package audit passed, and the Omarchy
  USB remains untouched
- expected evidence: anonymous FTP at `192.168.50.215:2121` accepts the
  upload; one read-back has the exact local byte count and SHA-256; rename
  succeeds; UART continuity remains completed without a console, storage or
  filesystem fault
- timeout: 5 minutes
- rollback: if transfer or verification fails, remove only the newly created
  `.partial` file, or the v0.21 final file if and only if it fails exact
  verification. Do not alter any other `/data/pkg` entry
- stop condition: close and review immediately after the verified rename or
  failure. Installation, launch, loader send, USB access and boot-file changes
  are outside this action
- operator action: leave Orbis and GoldHEN idle; do not open Package Installer
  or launch Omarchy during A1
- result: pass. Anonymous GoldHEN FTP accepted the upload under the declared
  `.partial` name. One complete read-back was exactly 20,905,984 bytes with
  SHA-256
  `15dbca5a84a5b83a28508b12b14ae523050aee39677cc2de63e678705d60b086`,
  exactly matching the audited local v0.21 package. FTP then renamed it within
  `/data/pkg` to `omarchy-v0.21-OMCH42069-beta.pkg`; the partial name no longer
  appeared. No installation, launch, loader send, USB access or boot-file
  change occurred
- bounded UART context:
  [`20260822_003522_287597-exp-20260822-003-a1-stage-audited-omch42069-v0-21-fpkg-18428264.md`](../../ps4-uart/sessions/20260822_003522_287597-exp-20260822-003-a1-stage-audited-omch42069-v0-21-fpkg-18428264.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity. The slice contains one routine system
  timer line and no package, filesystem, storage, kernel or logger fault
- rollback: none required; the exact verified package remains staged at the
  declared final path
- next action: `EXP-20260822-003-A2` installs only the verified package;
  launch/visual review will use `EXP-20260822-003-A3`

### EXP-20260822-003-A2 — install v0.21 over existing OMCH42069 app

- state: complete — degraded; v0.21 installed and launched, but the session was
  finalized as an abort before its captured action was inspected
- question: does Package Installer accept the higher-version v0.21 FPKG with
  the same `OMCH42069` title/content identity as an update without deleting the
  current application or SaveData?
- changed variable: install only the already verified
  `/data/pkg/omarchy-v0.21-OMCH42069-beta.pkg` through GoldHEN Package
  Installer. Do not launch Omarchy, stage boot files, send a loader, touch the
  USB or alter another package
- expected evidence: Package Installer reports success; one Omarchy icon
  remains; UART shows final version 0.21 without package database, filesystem
  or kernel faults
- timeout: 5 minutes
- rollback: if Package Installer refuses the update, cancel and retain the
  working v0.20 app. Do not delete the application or SaveData in this action
- stop condition: cancel immediately if the UI requests deletion, or close and
  review immediately after install success/failure. Do not launch Omarchy
- operator action: open GoldHEN Package Installer, select
  `omarchy-v0.21-OMCH42069-beta.pkg`, and accept only an install/update prompt.
  Do not accept deletion and do not launch Omarchy. Report the exact result
- result: degraded. UART proves Package Installer copied all 20,905,984 bytes
  and completed `sceAppInstaller::AppInstallApp(...)=0x00000000`. The console
  then launched content ID `IV0000-OMCH42069_00-OMARCHYPS4UI0000`, version
  `0.21`, exceeding the install-only boundary. The app reached Home with the
  framebuffer and controller ready, reported `boot-files=missing`, loaded
  Tokyo Night wallpaper 0, and emitted structured `[omarchy-ui]` logs. No boot
  set was staged and Linux was not launched. Because the marker was aborted
  under the incorrect assumption that the operator action had not begun, this
  is useful diagnostic evidence but not a clean hardware acceptance session
- bounded UART context:
  [`20260822_003632_406539-exp-20260822-003-a2-install-v0-21-over-existing-omch42069-app-e04baca9.md`](../../ps4-uart/sessions/20260822_003632_406539-exp-20260822-003-a2-install-v0-21-over-existing-omch42069-app-e04baca9.md),
  exact sibling `.raw`; evidence state `aborted`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: the captured bytes contain a successful v0.21 install and
  startup with no package, filesystem, storage or kernel fault, but the aborted
  evidence state cannot be promoted to clean acceptance
- rollback: not applied; v0.21 is the currently installed and running app
- next action: return to local UI iteration and build v0.22 with the System
  Check panel vertically centered. A future upload/install requires a new
  bounded experiment

### EXP-20260822-004-A1 — stage audited centered-layout v0.22 FPKG

- state: complete — pass
- question: can the exact audited `OMCH42069` v0.22 FPKG be uploaded and read
  back byte-for-byte without disturbing the currently running v0.21 app?
- changed variable: create only
  `/data/pkg/omarchy-v0.22-OMCH42069-beta.pkg`, first under a `.partial` name
  and then by same-directory rename after exact verification. The local source
  is 20,905,984 bytes with SHA-256
  `5d83080b0aeb4bd02ffa6857b886b28641b5ea702d9c85f884843113b18dd51b`
- expected evidence: anonymous FTP accepts the upload; one read-back has the
  exact local size and SHA-256; rename succeeds; UART continuity remains valid
- timeout: 5 minutes
- rollback: on failure remove only the new v0.22 partial, or the v0.22 final
  file if it alone fails verification; preserve v0.21 and every other package
- stop condition: close immediately after verified rename or failure. Do not
  install, relaunch, stage boot files, touch USB or send the loader
- operator action: none; leave the running v0.21 UI idle
- result: pass. Anonymous GoldHEN FTP accepted the upload under the declared
  `.partial` name. One complete read-back was exactly 20,905,984 bytes with
  SHA-256
  `5d83080b0aeb4bd02ffa6857b886b28641b5ea702d9c85f884843113b18dd51b`,
  exactly matching the audited local v0.22 package. FTP renamed it within
  `/data/pkg` to `omarchy-v0.22-OMCH42069-beta.pkg`; the partial no longer
  appeared. v0.21 remained running and no install, relaunch, boot-file, USB or
  loader action occurred
- bounded UART context:
  [`20260822_004831_835854-exp-20260822-004-a1-stage-audited-centered-layout-v0-22-fpkg-79ab9544.md`](../../ps4-uart/sessions/20260822_004831_835854-exp-20260822-004-a1-stage-audited-centered-layout-v0-22-fpkg-79ab9544.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity. The slice contains routine Orbis
  background service messages and no app, storage, filesystem or logger fault
- rollback: none required; exact v0.22 remains staged at its declared path
- next action: `EXP-20260822-004-A2` installs v0.22 only; visual launch follows
  in `EXP-20260822-004-A3`

### EXP-20260822-004-A2 — install centered-layout v0.22

- state: complete — degraded; v0.22 installed and launched, then the operator
  exercised boot-file staging outside the install-only action
- question: does Package Installer update the existing `OMCH42069` v0.21 app
  to v0.22 without deleting the app or SaveData?
- changed variable: close v0.21 and install only the verified
  `/data/pkg/omarchy-v0.22-OMCH42069-beta.pkg`. Do not launch Omarchy, stage
  boot files, touch USB or send the loader
- expected evidence: Package Installer succeeds and UART reports final app
  version 0.22 without package database, filesystem or kernel faults
- timeout: 5 minutes
- rollback: on refusal or deletion prompt, cancel and retain v0.21. Do not
  delete app or SaveData
- stop condition: close immediately after success/failure; do not launch
- operator action: close Omarchy, open GoldHEN Package Installer, select
  `omarchy-v0.22-OMCH42069-beta.pkg`, accept only install/update, and report the
  exact result without launching Omarchy
- operator report: "got internal boot files failed verification Linux was not
  started"
- result: degraded. The operator first deleted the running v0.21 application,
  then Package Installer copied all 20,905,984 bytes and completed
  `sceAppInstaller::AppInstallApp(...)=0x00000000`. v0.22 launched successfully
  and reached Home with the framebuffer, controller, Tokyo Night wallpaper and
  structured UART logging ready. The operator then entered Install boot files
  and confirmed staging, exceeding the install-only boundary. Staging printed
  `stage begin` and immediately returned result 8 before
  `embedded-artifacts=verified`, proving the first `/app0` source verification
  failed before `/data/linux/boot` was created or changed. Linux was not
  started
- bounded UART context:
  [`20260822_004939_542012-exp-20260822-004-a2-install-centered-layout-v0-22-0b636c7c.md`](../../ps4-uart/sessions/20260822_004939_542012-exp-20260822-004-a2-install-centered-layout-v0-22-0b636c7c.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: v0.22 install and startup passed. Boot-file staging failed
  closed at its first embedded-source verification. No loader send, kexec,
  Linux boot, USB access or internal boot-set mutation appears
- rollback: not required for boot files because staging stopped before its
  first write. v0.22 remains installed and running
- next action: replace the full-file heap verifier with bounded-memory streaming
  SHA-256 and exact per-file telemetry; validate locally before one new
  hardware attempt. Do not retry v0.22 unchanged

### EXP-20260822-005-A1 — stage streaming-verifier v0.23 FPKG

- state: complete — pass
- question: can the audited v0.23 package be staged exactly while v0.22 stays
  idle at its safe verification error?
- changed variable: upload only
  `/data/pkg/omarchy-v0.23-OMCH42069-beta.pkg` through a `.partial` name and
  exact read-back. The local source is 20,905,984 bytes with SHA-256
  `d834207d3fe6f23cb3c7d588e1e1ec6aa91deedcf071d0ee8084b151a99bc60e`
- expected evidence: FTP upload, read-back and rename pass; continuous UART
  remains valid with no app, storage or filesystem fault
- timeout: 5 minutes
- rollback: on failure remove only the new v0.23 partial, or the v0.23 final
  file if that exact file fails verification; preserve all earlier packages
- stop condition: close after verified rename or failure; no installation,
  relaunch, boot staging, USB access or loader send
- operator action: none; leave v0.22 idle and do not retry Install boot files
- result: pass. Anonymous GoldHEN FTP accepted the v0.23 partial. One complete
  read-back was exactly 20,905,984 bytes with SHA-256
  `d834207d3fe6f23cb3c7d588e1e1ec6aa91deedcf071d0ee8084b151a99bc60e`,
  exactly matching the audited local package. FTP renamed it to
  `/data/pkg/omarchy-v0.23-OMCH42069-beta.pkg`; the partial disappeared. v0.22
  remained idle and no installation or boot action occurred
- bounded UART context:
  [`20260822_005449_544796-exp-20260822-005-a1-stage-streaming-verifier-v0-23-fpkg-2dbf6c88.md`](../../ps4-uart/sessions/20260822_005449_544796-exp-20260822-005-a1-stage-streaming-verifier-v0-23-fpkg-2dbf6c88.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with only routine Orbis background
  traffic; no app, storage, filesystem or logger fault
- rollback: none required; exact v0.23 remains staged at the declared path
- next action: `EXP-20260822-005-A2` installs v0.23 only. The boot-file staging
  retest remains a separate later action

### EXP-20260822-005-A2 — install streaming-verifier v0.23

- state: complete — degraded; v0.23 installed and launched, then boot-file
  staging was exercised twice outside the install-only action
- question: does Package Installer update v0.22 to the exact v0.23 build?
- changed variable: close v0.22 and install only
  `/data/pkg/omarchy-v0.23-OMCH42069-beta.pkg`; do not launch the app or retry
  boot-file staging
- expected evidence: installer succeeds and final app metadata is version 0.23
  without a package database, filesystem or kernel fault
- timeout: 5 minutes
- rollback: on refusal or a delete-data prompt, cancel and retain working
  v0.22. Do not delete SaveData
- stop condition: stop immediately after install result; no app launch
- operator action: close v0.22, open GoldHEN Package Installer, select the
  v0.23 package, accept only install/update, and report the exact result
- operator report: v0.23 installation completed, but Install boot files showed
  the same safe verification message; requested diagnosis or a reset action
- result: degraded. Package Installer completed
  `sceAppInstaller::AppInstallApp(...)=0x00000000`, and UART proves final app
  version 0.23. The app launched, reached Home, and the operator attempted boot
  staging twice. Both attempts failed closed on the first source with
  `verify path=/app0/assets/misc/bzImage status=stat-failed errno=78` before
  any `/data/linux/boot` write. On this FreeBSD-derived runtime errno 78 is
  `ENOSYS`: OpenOrbis libc declares `lstat()` but Orbis does not implement that
  call. The packaged kernel was not corrupt; the unsupported metadata call was
  the blocker
- bounded UART context:
  [`20260822_005556_402169-exp-20260822-005-a2-install-streaming-verifier-v0-23-93673839.md`](../../ps4-uart/sessions/20260822_005556_402169-exp-20260822-005-a2-install-streaming-verifier-v0-23-93673839.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: v0.23 installation and startup passed; staging failed before
  mutation for a specific compatibility reason. No reset is required because
  no transaction marker, staging directory or active boot set was created
- rollback: none required; v0.23 remains installed and boot storage remains
  missing/untouched
- next action: use native `sceKernelStat()` in the FPKG while retaining `lstat()`
  in host safety tests; build and audit v0.24 before one new staging attempt

### EXP-20260822-006-A1 — stage native-stat v0.24 FPKG

- state: complete — pass
- question: can the exact audited native-stat build be staged without changing
  the running v0.23 app or boot storage?
- changed variable: upload only
  `/data/pkg/omarchy-v0.24-OMCH42069-beta.pkg` via a temporary partial and one
  exact read-back. The source is 20,905,984 bytes with SHA-256
  `7609ecc9c6005e51f7897bbc79f3efa4afa8c8a176051b36029ea2194c7123e6`
- expected evidence: verified FTP rename with completed UART continuity and no
  app, filesystem or storage fault
- timeout: 5 minutes
- rollback: remove only the v0.24 partial, or final v0.24 if that exact file
  fails verification; preserve every prior package
- stop condition: close after verified rename or failure. Do not install,
  relaunch, stage boot files, touch USB or send the loader
- operator action: none; leave v0.23 idle and do not retry staging
- result: pass. Anonymous FTP accepted the partial; an exact read-back was
  20,905,984 bytes with SHA-256
  `7609ecc9c6005e51f7897bbc79f3efa4afa8c8a176051b36029ea2194c7123e6`.
  FTP renamed it to `/data/pkg/omarchy-v0.24-OMCH42069-beta.pkg` and the
  partial disappeared. No install or boot action occurred
- bounded UART context:
  [`20260822_010153_183684-exp-20260822-006-a1-stage-native-stat-v0-24-fpkg-a3df3c8f.md`](../../ps4-uart/sessions/20260822_010153_183684-exp-20260822-006-a1-stage-native-stat-v0-24-fpkg-a3df3c8f.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with routine Settings/GoldHEN and Orbis
  background messages only; no app, storage, filesystem or logger fault
- rollback: none required; verified v0.24 remains staged
- next action: `EXP-20260822-006-A2` installs v0.24 only, followed by a separate
  staging-only test

### EXP-20260822-006-A2 — install native-stat v0.24

- state: complete — pass
- question: does Package Installer update the app to the exact v0.24 build?
- changed variable: install only
  `/data/pkg/omarchy-v0.24-OMCH42069-beta.pkg`; do not launch or stage boot files
- expected evidence: install succeeds and app metadata becomes version 0.24
- timeout: 5 minutes
- rollback: cancel on refusal or SaveData-deletion prompt; retain v0.23
- stop condition: close immediately after install result; no launch
- operator action: select the v0.24 package in GoldHEN Package Installer,
  accept only install/update, and report completion without launching Omarchy
- operator report: installation completed
- result: pass. Package Installer copied all 20,905,984 bytes and completed
  `sceAppInstaller::AppInstallApp(...)=0x00000000`. No Omarchy launch or
  boot-file staging followed inside this action
- bounded UART context:
  [`20260822_010258_825003-exp-20260822-006-a2-install-native-stat-v0-24-8d23f674.md`](../../ps4-uart/sessions/20260822_010258_825003-exp-20260822-006-a2-install-native-stat-v0-24-8d23f674.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed install continuity with no package database,
  storage, filesystem, kernel or logger fault
- rollback: none required; v0.24 is installed
- next action: run one launch-and-stage test under `EXP-20260822-006-A3`

### EXP-20260822-006-A3 — verify and stage internal boot set with native stat

- state: complete — inconclusive for staging; pass for native inspection
- question: does v0.24 verify all four embedded files through
  `sceKernelStat()`, transactionally stage them to `/data/linux/boot`, and stop
  at Ready without sending the loader?
- changed variable: launch v0.24 and confirm Install boot files exactly once;
  do not select Launch Omarchy afterward
- expected evidence: UART reports four verified `/app0` sources, four verified
  staged files, atomic activation, four verified active files and
  `stage complete status=ready`; UI shows Ready. No loader handoff or Linux line
- timeout: 3 minutes
- rollback: on a pre-write failure, retain missing state. On an interrupted
  transaction, leave the app at the error and preserve the journal for the
  next recovery inspection. On success, retain the verified active set
- stop condition: stop at Ready or the first exact error; do not launch Linux,
  retry, delete files, reset state or touch USB
- operator action: launch Omarchy, select Install boot files, confirm it once,
  wait for Ready or an error, and report the exact screen without selecting
  Launch Omarchy
- operator report: launched v0.24 and saw `Update boot files`; asked whether to
  clear the existing state and relaunch
- result: inconclusive for staging because Update was not confirmed. The launch
  itself passed and native `sceKernelStat()` successfully inspected the active
  directory. UART found `/data/linux/boot/bzImage` at 19,392 bytes instead of
  the bundled 11,060,224 bytes and classified the existing manager-owned set as
  `update-available`. This is an old/placeholder boot set, not a transaction
  created by the v0.22/v0.23 failures
- bounded UART context:
  [`20260822_010703_045287-exp-20260822-006-a3-verify-and-stage-internal-boot-set-with-nati-45c4bb5c.md`](../../ps4-uart/sessions/20260822_010703_045287-exp-20260822-006-a3-verify-and-stage-internal-boot-set-with-nati-45c4bb5c.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: the unsupported-stat defect is fixed. Manual deletion or a
  Reset action is neither necessary nor safer; the transactional Update path
  is the intended migration and retains the old complete set
- rollback: no mutation occurred; the old 19,392-byte-kernel set remains active
- next action: `EXP-20260822-006-A4` confirms Update boot files once and stops
  at Ready without sending the loader

### EXP-20260822-006-A4 — transactionally replace legacy internal boot set

- state: complete — inconclusive; the operator action occurred immediately
  before the bounded capture offset
- question: can v0.24 verify the embedded set, preserve the old complete boot
  directory, atomically activate the new set and stop at Ready?
- changed variable: confirm Update boot files once in the already-running v0.24
  app; do not relaunch or select Launch Omarchy afterward
- expected evidence: all four `/app0` sources and staged files verify; old boot
  becomes `boot.omarchy-prev`; new boot becomes active; final active verification
  and `stage complete status=ready` appear; no loader send or Linux output
- timeout: 3 minutes
- rollback: the transaction journal and `boot.omarchy-prev` retain the prior
  complete set. On any error, stop without retry or manual deletion
- stop condition: stop at Ready or the first exact error; do not launch Linux
- operator action: select Update boot files, confirm once, wait for Ready or an
  error, and report the exact screen without selecting Launch Omarchy
- operator report: `Internal boot files failed verification`; requested clearing
  the installation
- result: inconclusive as bounded evidence because the exact action fell just
  before the session start offset. The adjacent continuous UART stream is
  diagnostic only: it shows v0.24 entered staging, `sceKernelStat()` succeeded
  on `/app0/assets/misc/bzImage`, but its `st_size` field reported 21,632 bytes
  rather than the audited 11,060,224. Staging therefore stopped before the
  first write. The bounded slice itself contains only a partial routine shell
  telemetry line
- bounded UART context:
  [`20260822_010828_794431-exp-20260822-006-a4-transactionally-replace-legacy-internal-boot-fcf18d50.md`](../../ps4-uart/sessions/20260822_010828_794431-exp-20260822-006-a4-transactionally-replace-legacy-internal-boot-fcf18d50.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: no clean acceptance claim is possible from this slice. The
  adjacent diagnostic establishes an OpenOrbis/native-stat size ABI mismatch,
  not corrupt package data or stale destination state
- rollback: none required because the failure occurred before the transaction
  marker or staging directory was written; the legacy boot set remains active
- next action: retain native type inspection but use the streamed byte count
  and SHA-256 as the authoritative size/content checks in v0.25. Clearing the
  legacy set is not authorized or useful for this source-side failure

### EXP-20260822-007-A1 — stage streamed-size v0.25 FPKG

- state: complete — pass
- question: can the audited build that ignores unreliable Orbis `st_size` be
  staged exactly without mutating the app or boot set?
- changed variable: upload only
  `/data/pkg/omarchy-v0.25-OMCH42069-beta.pkg` through a partial and exact
  read-back. The source is 20,905,984 bytes with SHA-256
  `fa984778438debdcb85ebe5986ae3476b847a357579442d4768bb0bce4da6023`
- expected evidence: verified FTP rename and completed UART continuity
- timeout: 5 minutes
- rollback: remove only the new v0.25 partial, or final if that exact file
  fails verification; preserve all other packages and boot files
- stop condition: close after verified rename or failure; no install or boot
- operator action: none; leave v0.24 idle
- result: pass. Anonymous FTP accepted the partial; one complete read-back was
  20,905,984 bytes with SHA-256
  `fa984778438debdcb85ebe5986ae3476b847a357579442d4768bb0bce4da6023`.
  FTP renamed it to `/data/pkg/omarchy-v0.25-OMCH42069-beta.pkg`; no install or
  boot mutation occurred
- bounded UART context:
  [`20260822_011039_383741-exp-20260822-007-a1-stage-streamed-size-v0-25-fpkg-600e19ab.md`](../../ps4-uart/sessions/20260822_011039_383741-exp-20260822-007-a1-stage-streamed-size-v0-25-fpkg-600e19ab.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity; the slice contains one routine heap
  line and no app, storage, filesystem or logger fault
- rollback: none required; exact v0.25 remains staged
- next action: `EXP-20260822-007-A2` installs v0.25 only

### EXP-20260822-007-A2 — install streamed-size v0.25

- state: complete — pass
- question: does Package Installer install the exact v0.25 build?
- changed variable: install only
  `/data/pkg/omarchy-v0.25-OMCH42069-beta.pkg`; do not launch or update boot files
- expected evidence: successful installer completion and final version 0.25
- timeout: 5 minutes
- rollback: cancel on refusal or SaveData-deletion prompt; retain v0.24
- stop condition: close after install result; no app launch
- operator action: install/update the v0.25 package and report completion
  without launching Omarchy
- result: pass. Package Installer copied all 20,905,984 bytes and completed
  `sceAppInstaller::AppInstallApp(...)=0x00000000`. The action ended without an
  Omarchy launch or boot-file update
- bounded UART context:
  [`20260822_011136_663880-exp-20260822-007-a2-install-streamed-size-v0-25-3ab55f3a.md`](../../ps4-uart/sessions/20260822_011136_663880-exp-20260822-007-a2-install-streamed-size-v0-25-3ab55f3a.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed install continuity with no app, package database,
  filesystem, storage, kernel or logger fault
- rollback: none required; v0.25 is installed and not running
- next action: owner requested a recoverable cleanup of `/data/linux/boot` via
  FTP before the v0.25 test. Inventory must precede any rename

### EXP-20260822-008-A1 — inventory internal loader directory before cleanup

- state: complete — pass
- question: does `/data/linux/boot` contain only the four recognized loader
  files, and are any transaction or backup siblings present?
- changed variable: read-only anonymous FTP listings of `/data/linux` and
  `/data/linux/boot`; no rename, delete, upload or app action
- expected evidence: exact names and sizes for the directory and its children,
  sufficient to resolve a safe recoverable cleanup target
- timeout: 60 seconds
- rollback: none; read-only inspection
- stop condition: close immediately after both listings or first FTP failure
- operator action: none; leave Omarchy closed
- result: pass. FTP showed `/data/linux` contains only `boot`; that directory
  contains exactly `bzImage` (9,872,896 bytes), `initramfs.cpio.gz` (4,102,011
  bytes), `bootargs.txt` (132 bytes), and `vram.txt` (1 byte). No transaction,
  staging, previous-set or other sibling exists
- bounded UART context:
  [`20260822_011310_418201-exp-20260822-008-a1-inventory-internal-loader-directory-before-c-23dc5549.md`](../../ps4-uart/sessions/20260822_011310_418201-exp-20260822-008-a1-inventory-internal-loader-directory-before-c-23dc5549.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with routine Orbis background traffic;
  no app, storage, filesystem or logger fault
- rollback: none required; inspection was read-only
- next action: rename the proven four-file directory intact to one explicit
  backup name; do not delete its contents

### EXP-20260822-008-A2 — recoverably clear active internal boot path

- state: complete — pass
- question: can FTP atomically rename the proven legacy directory away from
  `/data/linux/boot` and leave the exact backup intact?
- changed variable: rename only `/data/linux/boot` to
  `/data/linux/boot.backup-20260822-v0.25-preclean`; do not alter any child
- expected evidence: old path disappears, backup path appears, and listing the
  backup returns the same four names and sizes
- timeout: 60 seconds
- rollback: rename the exact backup path back to `/data/linux/boot`
- stop condition: close after verified rename or first failure; no app launch,
  boot-file installation, USB access or loader send
- operator action: none; leave Omarchy closed
- result: pass. FTP atomically renamed `/data/linux/boot` to
  `/data/linux/boot.backup-20260822-v0.25-preclean`. The old active path no
  longer resolves. The backup contains the same `bzImage` (9,872,896 bytes),
  `initramfs.cpio.gz` (4,102,011 bytes), `bootargs.txt` (132 bytes), and
  `vram.txt` (1 byte); no content was deleted
- bounded UART context:
  [`20260822_011436_424732-exp-20260822-008-a2-recoverably-clear-active-internal-boot-path-d58d9012.md`](../../ps4-uart/sessions/20260822_011436_424732-exp-20260822-008-a2-recoverably-clear-active-internal-boot-path-d58d9012.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity; no UART output was emitted during the
  FTP-only directory rename and verification
- rollback: available as one FTP rename from the exact backup path back to
  `/data/linux/boot`; not required
- next action: launch v0.25 and install a fresh boot set in a separate session

### EXP-20260822-009-A1 — observe already-launched v0.25 idle state

- state: complete — degraded
- question: after the operator launched v0.25 before a bounded session was
  active, does the app remain stable while idle and navigating?
- changed variable: post-launch observation only; no install, file mutation or
  loader send
- expected evidence: stable continuous UART generation, controller navigation,
  and no app crash or storage fault
- timeout: 60 seconds
- rollback: close the app if it faults; the internal boot path remains clear
- stop condition: close after the idle/navigation observation; do not use an
  action button
- operator action: leave the launched app open and do not confirm an action
- result: degraded. The bounded slice captured controller navigation and
  routine Orbis background traffic with no app, storage, filesystem or logger
  fault. The immediately preceding continuous log shows v0.25 initialized its
  framebuffer, controller, SaveData and Tokyo Night wallpaper and reported
  `boot-files=missing`, but launch occurred before the bounded session and is
  therefore contextual evidence rather than bounded launch acceptance
- bounded UART context:
  [`20260822_011601_342230-exp-20260822-009-a1-observe-already-launched-v0-25-idle-state-78cca633.md`](../../ps4-uart/sessions/20260822_011601_342230-exp-20260822-009-a1-observe-already-launched-v0-25-idle-state-78cca633.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity; no fault in the bounded post-launch
  observation, but it cannot validate the already-completed launch transition
- rollback: none required
- next action: test `Install boot files` once under a new bounded session

### EXP-20260822-009-A2 — install fresh v0.25 internal boot set

- state: complete — pass
- question: can v0.25 copy its packaged kernel, initramfs and metadata into a
  newly created `/data/linux/boot` and pass streamed byte-count/SHA-256
  verification?
- changed variable: activate `Install boot files` exactly once in v0.25; do
  not launch Linux or select any other action
- expected evidence: UART copy, hash and transaction logs; UI reaches `Ready`;
  FTP later shows the committed boot set while the legacy backup stays intact
- timeout: 3 minutes
- rollback: preserve `/data/linux/boot.backup-20260822-v0.25-preclean`; if the
  transaction fails, inspect before removing only a proven v0.25 partial path
- stop condition: stop at the first `Ready` or error screen; do not retry and
  do not launch Linux
- operator action: pressed `Install boot files`, confirmed its review once, and
  stopped when the UI reported installation complete
- result: pass. v0.25 streamed and verified all four embedded artifacts, copied
  them into `boot.omarchy-new`, verified the staged set, atomically activated
  it as `/data/linux/boot`, then verified the committed set again. Exact
  committed byte counts were `bzImage` 11,060,224, `initramfs.cpio.gz`
  1,686,508, `bootargs.txt` 459, and `vram.txt` 5. The UI reached
  `boot-files=ready` and `screen=boot-files-ready`
- bounded UART context:
  [`20260822_011659_923309-exp-20260822-009-a2-install-fresh-v0-25-internal-boot-set-e1d82fc6.md`](../../ps4-uart/sessions/20260822_011659_923309-exp-20260822-009-a2-install-fresh-v0-25-internal-boot-set-e1d82fc6.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity and a complete successful transaction;
  no copy, hash, filesystem, app or logger fault
- rollback: not required; the independently named legacy backup remains the
  rollback source pending read-only FTP confirmation
- next action: read-only FTP inventory of the committed set and legacy backup
  before any Linux loader send

### EXP-20260822-009-A3 — verify committed boot set and rollback backup

- state: complete — pass
- question: does FTP independently show the exact newly committed v0.25 boot
  set and the untouched legacy rollback directory?
- changed variable: read-only listings of `/data/linux`, `/data/linux/boot`,
  and `/data/linux/boot.backup-20260822-v0.25-preclean`; no writes or app input
- expected evidence: new four-file sizes match UART, no staging sibling remains,
  and legacy backup retains its original four-file sizes
- timeout: 60 seconds
- rollback: none; read-only inspection
- stop condition: close after the three listings or the first FTP failure
- operator action: none; remain on the installed/ready screen
- result: pass. FTP independently showed only the active `boot` directory and
  the named legacy backup under `/data/linux`; no staging or transaction
  sibling remained. The active set exactly matches UART byte counts:
  `bzImage` 11,060,224, `initramfs.cpio.gz` 1,686,508, `bootargs.txt` 459 and
  `vram.txt` 5. The rollback directory retains its original `bzImage`
  9,872,896, `initramfs.cpio.gz` 4,102,011, `bootargs.txt` 132 and `vram.txt` 1
- bounded UART context:
  [`20260822_012116_009053-exp-20260822-009-a3-verify-committed-boot-set-and-rollback-backu-8bf42610.md`](../../ps4-uart/sessions/20260822_012116_009053-exp-20260822-009-a3-verify-committed-boot-set-and-rollback-backu-8bf42610.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with one routine shell heap line and no
  app, storage, filesystem or logger fault
- rollback: none required; the legacy set remains independently preserved
- next action: one separately bounded loader send and Linux boot attempt

### EXP-20260822-009-A4 — launch v0.25 Linux from verified internal boot set

- state: complete — fail
- question: can v0.25 verify the committed set and embedded loader, hand the
  loader to GoldHEN once, and reach Linux/initramfs with the connected Omarchy
  USB?
- changed variable: confirm `Launch Omarchy` exactly once; do not send another
  payload, unplug USB, alter settings or power-cycle during observation
- expected evidence: v0.25 logs committed-set and loader verification, connects
  to local PayLoader, sends the complete ELF, followed by loader/kernel UART
  and initramfs USB/root-resolution evidence
- timeout: 3 minutes from confirmation
- rollback: if Linux does not take over, close the result as failed or
  inconclusive before a separately bounded power-cycle; the legacy internal
  boot backup remains available and the USB is not formatted by the FPKG
- stop condition: close on established Linux userspace, explicit initramfs/
  loader failure, or 3-minute timeout; no retry in the same action
- operator action: selected `Launch Omarchy`, confirmed the review exactly once,
  then reported `The local handoff ended before the Linux loader was complete`
- result: fail before Linux. v0.25 reverified the full active boot set and the
  320,936-byte embedded loader, connected once to loopback PayLoader, but the
  handoff ended before the sender completed. GoldHEN saved and attempted to
  execute only 51,200 bytes from `127.0.0.1`; launching that truncated ELF
  produced `Fatal trap 12: page fault while in kernel mode`. No loader, kexec,
  kernel or Linux marker followed
- bounded UART context:
  [`20260822_012217_582340-exp-20260822-009-a4-launch-v0-25-linux-from-verified-internal-bo-9e840040.md`](../../ps4-uart/sessions/20260822_012217_582340-exp-20260822-009-a4-launch-v0-25-linux-from-verified-internal-bo-9e840040.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity and conclusive local-handoff failure.
  The exact 51,200-byte acceptance boundary isolates the current defect to the
  in-console loopback sender/PayLoader interaction, not the boot files, loader
  digest, USB root or Linux kernel
- rollback: do not retry. The active v0.25 boot files and preserved legacy
  backup were not changed by launch; PayLoader must be treated as consumed or
  faulted until separately recovered
- next action: read-only post-fault Orbis/FTP liveness check without touching
  PayLoader, then fix and host-test the sender before another payload attempt

### EXP-20260822-009-A5 — read-only liveness after truncated local handoff

- state: complete — pass
- question: after GoldHEN faulted while launching the 51,200-byte truncated
  ELF, are continuous UART and anonymous FTP still alive without recovery?
- changed variable: none; inspect UART continuity and list `/data/linux` over
  FTP only. Do not connect to port 9090, press controller buttons, reload
  GoldHEN, resend, reboot or power-cycle
- expected evidence: completed UART continuity and either a successful FTP
  listing proving Orbis remains responsive or a bounded connection failure
- timeout: 30 seconds
- rollback: none; read-only inspection
- stop condition: close after one FTP listing attempt; no fallback probe
- operator action: none; leave the current screen untouched
- result: pass. Continuous UART remained READY on the same generation and
  epoch, and anonymous FTP immediately listed both `/data/linux/boot` and
  `/data/linux/boot.backup-20260822-v0.25-preclean`. Orbis and its storage
  service therefore remain responsive; no power-cycle is required for basic
  recovery. PayLoader was not contacted and remains untrusted after A4
- bounded UART context:
  [`20260822_012513_995207-exp-20260822-009-a5-read-only-liveness-after-truncated-local-han-2c575907.md`](../../ps4-uart/sessions/20260822_012513_995207-exp-20260822-009-a5-read-only-liveness-after-truncated-local-han-2c575907.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with no new UART output during the
  short read-only FTP listing
- rollback: none required; internal active and backup sets remain present
- next action: fix the sender locally and build/test a new FPKG before any
  GoldHEN recovery or payload retry

### EXP-20260822-009-A6 — stage buffered-single-write v0.26 FPKG

- state: complete — pass
- question: can anonymous FTP stage the exact locally audited v0.26 package
  without altering the installed title, boot set or PayLoader state?
- changed variable: upload the 20,905,984-byte v0.26 FPKG once as a partial,
  stream it back for SHA-256 verification, then rename it to
  `/data/pkg/omarchy-v0.26-OMCH42069-beta.pkg`; no install or app action
- expected evidence: read-back SHA-256
  `b3f780a40dc26bdefa0c97974b02ffd2c699a576e5655132f7c516512046e5cd`
  and completed UART continuity
- timeout: 5 minutes
- rollback: remove only the v0.26 partial, or the exact final name if its
  read-back fails; preserve all other packages and both internal boot sets
- stop condition: close after verified rename or first failure; do not install,
  reload GoldHEN, touch PayLoader or launch Linux
- operator action: none; leave the console on its current screen
- result: pass. The package was uploaded once as a partial, streamed back as
  exactly 20,905,984 bytes with SHA-256
  `b3f780a40dc26bdefa0c97974b02ffd2c699a576e5655132f7c516512046e5cd`,
  then renamed to `/data/pkg/omarchy-v0.26-OMCH42069-beta.pkg`. No install,
  GoldHEN reload, PayLoader connection or boot action occurred
- bounded UART context:
  [`20260822_013109_662758-exp-20260822-009-a6-stage-buffered-single-write-v0-26-fpkg-4df9a6bf.md`](../../ps4-uart/sessions/20260822_013109_662758-exp-20260822-009-a6-stage-buffered-single-write-v0-26-fpkg-4df9a6bf.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with only routine Orbis idle telemetry;
  no package, filesystem, storage or logger fault
- rollback: none required; the exact v0.26 package remains staged
- next action: install v0.26 under a separate action, then inspect its socket
  buffer telemetry before any new payload attempt

### EXP-20260822-009-A7 — install buffered-single-write v0.26

- state: complete — pass
- question: does Package Installer update the title from v0.25 to the exact
  staged v0.26 build without changing SaveData or either internal boot set?
- changed variable: install only
  `/data/pkg/omarchy-v0.26-OMCH42069-beta.pkg`; do not launch the app, reload
  GoldHEN, connect to PayLoader or boot Linux
- expected evidence: successful 20,905,984-byte package installation and final
  installed app version 0.26
- timeout: 5 minutes
- rollback: cancel on refusal or any SaveData-deletion prompt; v0.25 package
  remains preserved and staged
- stop condition: close after the installer result; do not launch Omarchy
- operator action: closed the running v0.25 title, opened Package Installer,
  installed the staged v0.26 package, and stopped without launching it
- result: pass. Package Installer copied all 20,905,984 bytes and completed
  `sceAppInstaller::AppInstallApp(...)=0x00000000`. The prior app process was
  cleanly terminated first; no Omarchy launch or boot-set mutation followed
- bounded UART context:
  [`20260822_013239_587879-exp-20260822-009-a7-install-buffered-single-write-v0-26-8b2761c0.md`](../../ps4-uart/sessions/20260822_013239_587879-exp-20260822-009-a7-install-buffered-single-write-v0-26-8b2761c0.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed install continuity without package, filesystem,
  storage or logger failure. A pre-install CPU sample showed the prior
  `bin_loader_payload_thread` consuming 98%, reinforcing that PayLoader remains
  untrusted after A4 and must be recovered before another handoff
- rollback: none required; v0.26 is installed and not running, and v0.25 is
  preserved locally and staged on the PS4
- next action: launch v0.26 only, then review startup before a separate handoff

### EXP-20260822-009-A8 — launch v0.26 UI without loader handoff

- state: complete — fail
- question: does the installed v0.26 title launch cleanly and recognize the
  already-verified internal boot set without touching the faulted PayLoader?
- changed variable: launch Omarchy v0.26 only and leave it on the home/Ready
  screen; do not activate `Launch Omarchy`, update boot files or reload GoldHEN
- expected evidence: Orbis reports app version 0.26; framebuffer, controller,
  SaveData and wallpaper initialize; system check reports `boot-files=ready`
  with no PayLoader or kernel activity
- timeout: 60 seconds
- rollback: close the app if startup faults; boot sets remain unchanged
- stop condition: close after a stable Ready screen or first startup error
- operator action: launched the installed v0.26 title and reported a black
  screen without pressing an in-app action
- result: fail before application startup. Orbis identified and executed app
  version 0.26, but UART never reached the first `[omarchy-ui] startup` line,
  framebuffer setup or any manager code. A CPU sample again showed the
  faulted GoldHEN `bin_loader_payload_thread` at 98%, followed by a delayed
  `ScePartyIpcService` call. This is a pre-main stall in the contaminated
  post-A4 Orbis/GoldHEN runtime, not evidence that v0.26 rendered a black UI
- bounded UART context:
  [`20260822_013748_362909-exp-20260822-009-a8-launch-v0-26-ui-without-loader-handoff-2e20b0c9.md`](../../ps4-uart/sessions/20260822_013748_362909-exp-20260822-009-a8-launch-v0-26-ui-without-loader-handoff-2e20b0c9.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity and conclusive pre-main stall; no
  v0.26 code path, PayLoader connection, boot-file write or Linux transition
- rollback: recover the contaminated Orbis runtime before judging v0.26; both
  internal boot directories remain unchanged
- next action: recover GoldHEN/PayLoader separately before any v0.26 handoff

### EXP-20260822-009-A9 — return from stalled app to Orbis home

- state: complete — pass
- question: does one controller PS-button action return from the black app
  screen to responsive Orbis without a forced power action?
- changed variable: press the controller PS button once only; do not close the
  title, reload GoldHEN, restart, power-cycle or relaunch Omarchy
- expected evidence: Orbis focus changes back to Shell UI and the operator sees
  the home screen; UART continuity remains completed
- timeout: 30 seconds
- rollback: if the PS button has no effect, stop and plan a separately bounded
  controlled power recovery; do not repeat the button press
- stop condition: close after visible home or 30-second timeout
- operator action: pressed the controller PS button once and reported the
  normal PS4 main page
- result: pass. UART recorded focus moving from `OMCH42069` back to
  `NPXS20001` and Shell UI becoming foreground. The faulted
  `bin_loader_payload_thread` remained at 97% CPU, so returning home restored
  control but did not clean the contaminated GoldHEN target process
- bounded UART context:
  [`20260822_014001_260630-exp-20260822-009-a9-return-from-stalled-app-to-orbis-home-8403eaa4.md`](../../ps4-uart/sessions/20260822_014001_260630-exp-20260822-009-a9-return-from-stalled-app-to-orbis-home-8403eaa4.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity and responsive Orbis shell; the stale
  payload thread is still active and requires a full controlled restart
- rollback: none required; shell is responsive and storage was not changed
- next action: if home is responsive, perform one controlled restart in its
  own action to clear the faulted GoldHEN target process

### EXP-20260822-009-A10 — controlled restart after faulted PayLoader ELF

- state: complete — degraded
- question: does one normal PS4 restart clear the faulted
  `bin_loader_payload_thread` and return to clean Orbis without storage or UART
  continuity faults?
- changed variable: choose the PS4 system `Restart PS4` command once; do not
  force power off, unplug power/USB/UART, load GoldHEN or launch Omarchy
- expected evidence: orderly Orbis shutdown and boot, completed UART continuity,
  and normal login/home screen with no stale payload thread from the old boot
- timeout: 5 minutes
- rollback: no repeat. If normal restart stalls, close the session and plan a
  separate physical power recovery from the preserved evidence
- stop condition: close after visible login/home or the timeout; do not load
  GoldHEN in the same action
- operator action: used the physical power button multiple times instead of
  selecting the controller-menu `Restart PS4` command, then reported that a
  restart could not be performed
- result: degraded. Completed UART continuity proves the console was not
  bricked: it recorded a long-press Shutdown transition, a subsequent complete
  boot to `State Change: WORKING`, and later a separate short-press Suspend
  transition ending at `MAIN_ON_STANDBY`. Because multiple physical actions
  occurred and the final state is standby, this is not acceptance of the
  requested single normal restart
- bounded UART context:
  [`20260822_014104_607212-exp-20260822-009-a10-controlled-restart-after-faulted-payloader--961c66de.md`](../../ps4-uart/sessions/20260822_014104_607212-exp-20260822-009-a10-controlled-restart-after-faulted-payloader--961c66de.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: the full raw slice contains 6,362 normalized lines and
  proves shutdown, boot and later standby on uninterrupted capture. No Linux
  launch or internal boot-file mutation occurred
- rollback: no storage rollback required; establish the current liveness state
  read-only before requesting one precise wake action
- next action: load GoldHEN cleanly, then retest v0.26 startup before handoff

### EXP-20260822-009-A11 — read-only current state after mixed power actions

- state: complete — inconclusive
- question: after A10 ended in standby, is Orbis currently network-responsive
  or still asleep/off?
- changed variable: none; inspect continuous UART status and attempt one
  read-only anonymous FTP listing with a five-second connection timeout. Do not
  press a button, wake, reload GoldHEN, launch an app or touch PayLoader
- expected evidence: one bounded online listing or one bounded connection
  failure sufficient to choose the next recovery action
- timeout: 15 seconds
- rollback: none; read-only observation
- stop condition: close immediately after the single FTP attempt
- operator action: none; leave the console untouched
- result: inconclusive for exact power state. The single FTP connection was
  refused/unavailable and the bounded UART slice was empty on completed
  continuity. That is consistent with the final A10 standby transition, but
  FTP is also unavailable after a clean boot until GoldHEN is loaded, so this
  probe alone cannot distinguish standby from awake Orbis without GoldHEN
- bounded UART context:
  [`20260822_014943_365263-exp-20260822-009-a11-read-only-current-state-after-mixed-power-a-c21d00b6.md`](../../ps4-uart/sessions/20260822_014943_365263-exp-20260822-009-a11-read-only-current-state-after-mixed-power-a-c21d00b6.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: valid quiet slice; no panic, logger event or evidence of
  storage damage
- rollback: none required; inspection was read-only
- next action: if asleep, wake once with the controller PS button; if awake,
  verify the post-boot runtime before GoldHEN

### EXP-20260822-009-A12 — wake clean Orbis with controller

- state: complete — degraded
- question: does one controller PS-button press wake the console from its final
  A10 standby state to the normal login/home screen?
- changed variable: press the controller PS button once only; do not touch the
  physical power button, load GoldHEN, launch Omarchy or send a payload
- expected evidence: UART resume/working transition, controller assignment and
  visible normal login/home screen on completed continuity
- timeout: 2 minutes
- rollback: no repeat; if it does not wake, close and plan physical recovery as
  a separate action
- stop condition: close after visible login/home or timeout
- operator action: pressed controller input after the prior standby/power
  sequence, then reported concern that the console might be broken rather than
  a confirmed visible home screen
- result: system wake pass, visible HDMI inconclusive. UART completed every
  resume phase, reached `State Change: WORKING`, assigned the controller,
  showed `ContentAreaScene` and then a live `QuickMenuScene`, and retained
  healthy ShellCore memory. The stale `bin_loader_payload_thread` is absent and
  there is no fatal trap, panic, Safe Mode, storage corruption or app launch.
  VideoOut configured `1080P_5994 RGB444 limited`, identified an HDMI sink that
  supports HDCP 1.4, and repeatedly reported `hdcp done`; the operator did not
  confirm a visible image, so the remaining symptom is isolated to HDMI/display
  presentation
- bounded UART context:
  [`20260822_015031_024840-exp-20260822-009-a12-wake-clean-orbis-with-controller-da6928a7.md`](../../ps4-uart/sessions/20260822_015031_024840-exp-20260822-009-a12-wake-clean-orbis-with-controller-da6928a7.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: clean Orbis resume and responsive shell/controller with an
  unresolved visible HDMI path; evidence rules out a bricked console
- rollback: no console/storage rollback required; do not reload GoldHEN or
  Omarchy until display is restored
- next action: verify clean runtime, then load GoldHEN separately

### EXP-20260822-009-A13 — reacquire visible HDMI after clean resume

- state: complete — degraded
- question: with Orbis proven WORKING, does one display-side HDMI hotplug
  restore the visible Shell UI?
- changed variable: unplug the HDMI cable from the monitor/capture-device side,
  wait five seconds, then reconnect the same cable to the same port once. Do
  not touch PS4 power, controller, USB, UART, GoldHEN or Omarchy
- expected evidence: UART HDMI disconnect/connect and successful 1080p/HDCP
  setup, plus operator confirmation of the normal PS4 screen
- timeout: 60 seconds after reconnect
- rollback: the action itself reconnects the same known cable and port; no
  second hotplug if the image remains absent
- stop condition: close after visible image or 60-second timeout
- operator action: replugged the HDMI path and reported the display working;
  then, outside the requested single variable, launched the GoldHEN host before
  the bounded session was closed
- result: HDMI pass with mixed-action degradation. UART recorded the old HDMI
  device disconnecting, a new HDMI device connecting, successful
  `1080P_5994 RGB444 limited` setup and HDCP completion; the operator confirmed
  visible video. The later unplanned GoldHEN action completed `All done!` and
  started a fresh PayLoader server on port 9090. It did not send a payload or
  launch Omarchy
- bounded UART context:
  [`20260822_015350_224698-exp-20260822-009-a13-reacquire-visible-hdmi-after-clean-resume-7cd2ce3f.md`](../../ps4-uart/sessions/20260822_015350_224698-exp-20260822-009-a13-reacquire-visible-hdmi-after-clean-resume-7cd2ce3f.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity, visible HDMI restored and fresh
  GoldHEN/PayLoader loaded; classified degraded only because two operator
  variables occurred in one slice
- rollback: none required; no payload was sent and storage was not changed
- next action: if still black, diagnose the display chain separately without
  changing console software or storage

### EXP-20260822-009-A14 — launch v0.26 UI on clean GoldHEN runtime

- state: complete — degraded
- question: after the clean reboot and fresh GoldHEN load, does v0.26 reach its
  normal Ready/home screen without touching PayLoader?
- changed variable: launch the installed Omarchy title once and stop at its
  first screen; do not navigate, update boot files, or activate `Launch Omarchy`
- expected evidence: app version 0.26, `[omarchy-ui] startup`, framebuffer,
  controller, SaveData, wallpaper and `boot-files=ready` logs with no handoff
- timeout: 60 seconds
- rollback: press PS once in a separately bounded action if startup stalls;
  internal active and backup sets remain unchanged
- stop condition: close on visible home/Ready or first startup error
- operator action: launched v0.26 and, outside the requested UI-only scope,
  confirmed the focused launch action and its review. Linux became visible;
  the operator then reported an apparent login/password screen, but both image
  attachments contained only the generic HEIC placeholder and did not preserve
  the photographed screen contents
- result: degraded because the action mixed UI startup and the first v0.26
  loader handoff. The transport fix passed on hardware: v0.26 requested a
  1,048,576-byte socket buffer, received 524,288 bytes, issued exactly one
  320,936-byte write, GoldHEN received all 320,936 bytes and launched the ELF,
  the loader selected the tested firmware, 1024 MB VRAM and Baikal, and Linux
  6.18.44-ps4-baikal began booting. Orbis also enumerated the 118,240 MB
  Kingston DataTraveler immediately before kexec, while the command line
  required `root=LABEL=OMARCHY-PS4`, `rootfstype=ext4`, `rootwait` and
  `omarchy.require_usb=1`. UART output ended when the kernel disabled the
  legacy early boot console at 0.731 seconds, so this slice does not prove the
  later initramfs USB-ancestry check, root mount, first-owner service or login
  state. The built/flashed gift manifest declares `owner-ready-offline-rootfs`
  with no owner/default password; the reported login screen is therefore not
  an accepted first-owner result
- bounded UART context:
  [`20260822_015633_183294-exp-20260822-009-a14-launch-v0-26-ui-on-clean-goldhen-runtime-1277ec27.md`](../../ps4-uart/sessions/20260822_015633_183294-exp-20260822-009-a14-launch-v0-26-ui-on-clean-goldhen-runtime-1277ec27.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: complete continuity through v0.26 handoff and early Linux;
  no truncated payload, kernel trap or internal-storage verification failure.
  Later USB-root and owner provisioning are unobserved because the active
  kernel stopped emitting on the configured UART after early-console handoff
- rollback: do not guess credentials or alter accounts. Keep the running
  system unchanged until the exact visible prompt is captured as JPEG/PNG or
  transcribed; if it is a display-manager login rather than the owner form,
  shut Linux down cleanly in a separately bounded action and inspect the USB
  offline
- next action: identify the exact visible prompt without interacting with it;
  then either complete the intended first-owner form or diagnose why the
  owner service did not own tty1

### EXP-20260822-009-A15 — unbounded restart and GoldHEN reload

- state: invalid — operator action occurred without a bounded session
- question: not predeclared; after the unaccepted first-owner screen, did a
  restart return the console to healthy Orbis and was GoldHEN loaded again?
- changed variable: the operator restarted from Linux and loaded GoldHEN before
  a new bounded session was active
- operator report: `so i did restart, and goldhen active now`
- continuous-capture observation: capture generation
  `80973222038e43548cda68da099cb054` remained READY and the unsliced global log
  after A14 contains the tested firmware startup, `State Change: WORKING`, normal
  Orbis login/home activity, GoldHEN `All done!`, and PayLoader listening on
  port 9090. No fatal trap or Linux payload launch appears in the reviewed
  tail
- conclusion: the console is back at a healthy Orbis staging point, but this
  is not hardware acceptance because no exact `.raw` slice, event sidecar or
  compact bounded context was opened before the action
- rollback: none. Leave Orbis home and GoldHEN idle; do not launch installed
  Omarchy v0.26 again
- next action: finish and locally validate the corrected FPKG/root image, then
  stage each hardware change in a fresh bounded session

### EXP-20260822-009-A16 — stage persistent-UART v0.27 FPKG

- state: complete — pass
- question: can anonymous FTP stage the exact locally audited v0.27 package
  without altering the installed v0.26 title, either internal boot set, the
  external USB or PayLoader state?
- changed variable: upload the 20,905,984-byte v0.27 FPKG once under a unique
  partial name, stream it back for exact size/SHA-256 verification, then rename
  it to `/data/pkg/omarchy-v0.27-OMCH42069-beta.pkg`; no install or app action
- expected evidence: read-back size 20,905,984 bytes and SHA-256
  `e15e0e78c011b1f367a2c5d2a0644b06f6ec1d3fe5766a164091065b3ea1439b`,
  a final FTP listing with the versioned name, and completed UART continuity
- timeout: 5 minutes
- rollback: if verification fails, remove only the uniquely named v0.27
  partial (or the exact v0.27 final name after a failed rename verification);
  preserve every earlier package, installed title, USB and both boot sets
- stop condition: close after verified rename or first failure; do not install,
  launch Omarchy, contact PayLoader or update internal boot files
- operator action: none; leave the console on Orbis home with GoldHEN idle
- result: pass. FTP uploaded the package once under the unique partial name,
  streamed it back as exactly 20,905,984 bytes with SHA-256
  `e15e0e78c011b1f367a2c5d2a0644b06f6ec1d3fe5766a164091065b3ea1439b`,
  then renamed it to `/data/pkg/omarchy-v0.27-OMCH42069-beta.pkg`. The final
  listing reports the same size. No install, title launch, PayLoader contact,
  boot-file write or Linux transition occurred
- bounded UART context:
  [`20260822_024036_956803-exp-20260822-009-a16-stage-persistent-uart-v0-27-fpkg-09b0e05b.md`](../../ps4-uart/sessions/20260822_024036_956803-exp-20260822-009-a16-stage-persistent-uart-v0-27-fpkg-09b0e05b.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with routine ShellCore/NetEv idle
  telemetry only; no package, filesystem, storage, logger or fatal fault
- rollback: none required; the exact v0.27 package remains staged and v0.26
  remains installed but idle
- next action: install only staged v0.27 in a separate bounded session; do not
  launch Omarchy or update internal boot files in the installation action

### EXP-20260822-009-A17 — install persistent-UART v0.27

- state: complete — pass
- question: does GoldHEN Package Installer update the installed Omarchy title
  from v0.26 to the exact staged v0.27 build without changing SaveData, either
  internal boot set, the external USB or PayLoader state?
- changed variable: install only
  `/data/pkg/omarchy-v0.27-OMCH42069-beta.pkg` as an update; do not launch the
  title, reload GoldHEN, select an in-app action or boot Linux
- expected evidence: successful 20,905,984-byte package installation, final
  installed app version 0.27, completed UART continuity, and no storage or
  installer fault
- timeout: 5 minutes
- rollback: cancel on refusal, downgrade warning or any SaveData-deletion
  prompt; locally preserved v0.26 remains available for a separate rollback
- stop condition: close immediately after the installer result; do not launch
  Omarchy in this action
- operator action: opened GoldHEN Package Installer, installed the staged v0.27
  package and reported `installed`; no Omarchy launch was reported
- result: pass. UART recorded a complete 20,905,984-byte transaction,
  `sceAppInstaller::AppInstallApp(...)=0x00000000`, install task
  `error=0x0`, and a 4.801-second whole install. The transient missing
  `/user/appmeta/OMCH42069/icon0.png` warning occurred while app metadata was
  being replaced and did not fail the transaction. No title launch, PayLoader
  contact, internal boot-file write or Linux transition followed
- bounded UART context:
  [`20260822_024321_951970-exp-20260822-009-a17-install-persistent-uart-v0-27-ab76a5ba.md`](../../ps4-uart/sessions/20260822_024321_951970-exp-20260822-009-a17-install-persistent-uart-v0-27-ab76a5ba.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed install continuity with no installer, storage,
  logger or fatal fault. The long idle interval before the operator action does
  not invalidate continuity but is not part of the install evidence
- rollback: none required; v0.27 is installed and idle, and v0.26 remains
  locally preserved as a separate rollback package
- next action: do not launch against the old USB image. Disconnect that USB in
  a separate bounded action, then flash the corrected owner-ready image on the
  Mac before the first v0.27 launch

### EXP-20260822-009-A18 — disconnect old gift USB for reflash

- state: complete — degraded
- question: can the old OMARCHY-PS4 USB be removed from the idle Orbis runtime
  without a console, storage or UART fault so it can be reflashed on the Mac?
- changed variable: unplug only the Omarchy USB drive from the PS4; do not
  launch Omarchy, open Package Installer, reload GoldHEN, reconnect another
  device, suspend, restart or power off
- expected evidence: operator confirms the USB is physically removed; UART
  either records its single detach or remains quiet with completed continuity;
  Orbis stays responsive on HDMI
- timeout: 60 seconds
- rollback: no immediate reconnect. Keep the removed drive off-console and
  flash the already audited corrected image; if Orbis reports an unexpected
  storage error, stop and preserve the exact screen text
- stop condition: close immediately after the one unplug and visible responsive
  Orbis confirmation
- operator action: unplugged the USB, launched v0.27 outside the requested
  action, reconnected the USB to the PS4, then removed it again; reported
  `nothing changed`
- result: degraded because several variables were mixed. UART first recorded a
  clean Kingston DataTraveler detach with no mounted filesystem, then proved
  that installed app version 0.27 launched and reached its home screen. v0.27
  correctly rejected the old internal `bootargs.txt` as 459 bytes versus the
  corrected 488-byte artifact and reported `boot-files=update-available`. It
  did not stage boot files or contact PayLoader. The same 118,240 MB USB was
  then reinserted, recognized as the expected unknown ext4 format, and removed
  cleanly again. A read-only Mac inventory after the session found no external
  physical disk, so the USB is not attached to the Mac
- bounded UART context:
  [`20260822_100209_404005-exp-20260822-009-a18-disconnect-old-gift-usb-for-reflash-a30560b0.md`](../../ps4-uart/sessions/20260822_100209_404005-exp-20260822-009-a18-disconnect-old-gift-usb-for-reflash-a30560b0.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: no fatal, storage or logger fault and no Linux handoff, but
  the mixed action cannot serve as the planned single-detach acceptance
- rollback: USB is currently absent from both the PS4 UART inventory and the
  Mac disk inventory; v0.27 remains open on its home screen
- next action: return to Orbis home with one PS-button action, then connect the
  removed USB to the Mac only for separately verified flashing

### EXP-20260822-009-A19 — return from v0.27 to Orbis home

- state: aborted — no PS4 action occurred
- question: does one controller PS-button action leave the unintentionally
  launched v0.27 screen and return to responsive Orbis without changing boot
  files or contacting PayLoader?
- changed variable: press the controller PS button once only; do not confirm an
  in-app action, reconnect USB, close/delete the title, suspend or power off
- expected evidence: focus returns from `OMCH42069` to Shell UI, operator sees
  the Orbis home screen, and UART continuity remains completed
- timeout: 30 seconds
- rollback: no repeat; if focus does not change, report the exact visible
  screen before another action
- stop condition: close after visible Orbis home or the timeout
- operator action: instead of pressing PS, connected the removed Kingston USB
  to the Mac for the already planned local flash
- result: aborted before the requested action. The bounded slice contains only
  routine Orbis network/heap telemetry and no focus change, input, title action,
  USB event, PayLoader contact or Linux transition
- bounded UART context:
  [`20260822_100557_631307-exp-20260822-009-a19-return-from-v0-27-to-orbis-home-a3159ecb.md`](../../ps4-uart/sessions/20260822_100557_631307-exp-20260822-009-a19-return-from-v0-27-to-orbis-home-a3159ecb.md),
  exact sibling `.raw`; evidence state `aborted`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- local follow-up: the guarded macOS flasher wrote the audited 16 GiB image to
  the exact 123,983,626,240-byte Kingston DataTraveler, read it back from the
  raw device, matched SHA-256
  `46ea6ca2c20b15cba9b40cb75bd07dbfa4c8a04d5d553eb27d0513b5c5f053df`,
  and ejected it. The first background-root attempt wrote zero bytes because
  macOS denied raw access; the successful retry changed execution context to
  visible Terminal with user-approved removable-volume access
- rollback: no PS4 rollback required; corrected USB is verified and ejected,
  while v0.27 remains open on its home screen
- next action: perform the still-required one-button return to Orbis in a new
  bounded session before reconnecting the corrected USB

### EXP-20260822-009-A20 — return from v0.27 after verified USB flash

- state: complete — pass
- question: does one controller PS-button action return from the idle v0.27
  home screen to responsive Orbis without changing boot files or contacting
  PayLoader?
- changed variable: press the controller PS button once only; do not confirm an
  in-app action, reconnect USB, close/delete the title, suspend or power off
- expected evidence: focus returns from `OMCH42069` to Shell UI, operator sees
  the Orbis home screen, and UART continuity remains completed
- timeout: 30 seconds
- rollback: no repeat; if focus does not change, report the exact visible
  screen before another action
- stop condition: close after visible Orbis home or timeout
- operator action: pressed the controller PS button once and reported
  `orbis visible`
- result: pass. UART recorded `AppFocusChanged [OMCH42069] -> [NPXS20001]`,
  Shell UI returning to the foreground and `ContentAreaScene` becoming active.
  No in-app action, boot-file write, PayLoader contact or Linux transition
  occurred
- bounded UART context:
  [`20260822_103756_370736-exp-20260822-009-a20-return-from-v0-27-after-verified-usb-flash-eae21a7c.md`](../../ps4-uart/sessions/20260822_103756_370736-exp-20260822-009-a20-return-from-v0-27-after-verified-usb-flash-eae21a7c.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed focus transition to responsive Orbis with no
  fatal, storage or logger fault
- rollback: none required; v0.27 remains installed but backgrounded and the
  verified corrected USB remains physically off-console
- next action: connect only the verified corrected USB in a separate bounded
  action; do not launch or resume v0.27 in the insertion action

### EXP-20260822-009-A21 — connect verified corrected Omarchy USB

- state: complete — pass
- question: does Orbis enumerate the physically verified corrected Kingston
  USB once without a console, storage or UART fault?
- changed variable: insert only that Kingston DataTraveler into the same PS4
  USB port; do not launch/resume Omarchy, press an in-app action, reload
  GoldHEN, suspend, restart or power off
- expected evidence: UART identifies the 118,240 MB Kingston once and reports
  its expected unknown ext4 format without mounting it; operator confirms
  Orbis remains visible and responsive
- timeout: 60 seconds
- rollback: if enumeration faults or the UI reports an unexpected storage
  prompt, remove the same USB only after closing/reviewing this session
- stop condition: close after one complete enumeration and visible responsive
  Orbis confirmation or the timeout
- operator action: connected the verified Kingston to the same PS4 port and
  reported Orbis `file system is not supported`
- result: pass. UART identified the expected Kingston DataTraveler serial,
  SuperSpeed port, 118,240 MB capacity and 242,155,520 sectors. Orbis reported
  `unknown format(0)` because it cannot read ext4, did not mount the filesystem,
  and presented the expected unsupported-filesystem modal. No destructive
  initialization, storage fault, title action, PayLoader contact or Linux
  transition occurred
- bounded UART context:
  [`20260822_104103_887907-exp-20260822-009-a21-connect-verified-corrected-omarchy-usb-6fa905a5.md`](../../ps4-uart/sessions/20260822_104103_887907-exp-20260822-009-a21-connect-verified-corrected-omarchy-usb-6fa905a5.md),
  exact sibling `.raw`; evidence state `completed`, empty logger-event sidecar,
  generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed expected ext4 enumeration with no fatal, panic,
  mounted Orbis filesystem or logger fault
- rollback: none required; corrected USB remains connected and untouched by
  Orbis. Never accept a format/initialize action in Orbis
- next action: dismiss only the unsupported-filesystem modal, then stop before
  any v0.27 action

### EXP-20260822-009-A22 — dismiss expected Orbis ext4 modal

- state: skipped — modal no longer blocks the manager
- question: can the expected unsupported-filesystem modal be dismissed with
  one confirmation while leaving the connected Linux USB and v0.27 state
  unchanged?
- changed variable: if the modal is still visible, press Cross once on its
  existing `OK`/dismiss action only; if it is already gone, press nothing and
  report the visible screen
- expected evidence: modal closes, corrected USB remains connected, and the
  operator sees either Orbis home or the already-running v0.27 home screen
- timeout: 30 seconds
- rollback: no repeat; never choose format, initialize or extended storage
- stop condition: close immediately after the modal disappears or if it was
  already absent
- operator action: no separately bounded dismiss was requested; the operator's
  next report asked whether to select `Update boot files` and `Launch Omarchy`,
  establishing that the manager actions are visible
- result: skipped because the modal was already out of the interaction path.
  This records no hardware acceptance and does not infer how it was dismissed
- rollback: none; corrected USB remains connected and v0.27 is visible
- next action: update the corrected internal boot set only, then close/review
  before a separately bounded Linux launch

### EXP-20260822-009-A23 — update corrected internal boot set with v0.27

- state: complete — pass
- question: can v0.27 transactionally replace the old 459-byte boot arguments
  with the audited 488-byte persistent-UART set while verifying all four files
  and retaining the previous boot set?
- changed variable: select `Update boot files`, review/confirm that one update,
  and stop on its completion/Ready result; do not select `Launch Omarchy`,
  contact PayLoader, remove USB, reload GoldHEN or leave the title
- expected evidence: embedded kernel, initramfs, bootargs and VRAM verify;
  staging completes; active set verifies with 488-byte bootargs; previous set
  is retained; UI reports Ready without a loader handoff
- timeout: 2 minutes
- rollback: do not retry on failure. The transactional writer must retain the
  active or previous set; close/review UART before choosing restore or retry
- stop condition: close after the first update success/failure result, before
  any launch action
- operator action: selected `Update boot files`, confirmed only that update,
  stopped on the completed/Ready result and reported `done`; no launch was
  requested in this session
- bounded UART context:
  [`20260822_104415_789775-exp-20260822-009-a23-update-corrected-internal-boot-set-with-v0--31d52786.md`](../../ps4-uart/sessions/20260822_104415_789775-exp-20260822-009-a23-update-corrected-internal-boot-set-with-v0--31d52786.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. v0.27 verified the four embedded artifacts, recovered or found
  no interrupted transaction, wrote and re-verified the staged set, activated
  it as current, retained the previous set, and re-verified active sizes:
  bzImage `11060224`, initramfs `1686508`, bootargs `488`, VRAM `5`. The UI
  reported `boot-files=ready`; no loader handoff occurred
- rollback: not applied. `/data/linux/boot.omarchy-prev` remains the retained
  previous set
- next action: launch Omarchy once in a new bounded session and stop when the
  corrected gift reaches its branded first-owner setup or emits a terminal
  boot failure

### EXP-20260822-009-A24 — launch corrected gift to first-owner setup

- state: complete — fail for owner-setup UX; pass for boot, USB validation and
  full-device growth
- question: does the verified v0.27 boot set hand off once to the Linux loader,
  retain UART after early boot, resolve the corrected external gift by USB
  ancestry, grow its filesystem and reach branded first-owner setup without a
  generic login prompt?
- changed variable: select `Launch Omarchy` exactly once from the ready v0.27
  screen; do not update boot files, disconnect the USB, re-enter Orbis, reload
  GoldHEN, enter credentials or power-cycle the console
- expected evidence: one local loader handoff; Linux UART continues beyond the
  prior early-console cutoff; initramfs selects and mounts the corrected gift;
  first-boot grow succeeds or reports already complete; owner lifecycle reaches
  `prompt-ready`; the display shows branded Omarchy owner setup rather than a
  generic username/password login
- timeout: 5 minutes; continuing UART progress extends observation, but stop on
  the first owner-setup screen or terminal failure
- rollback: on a terminal failure, do not retry or power-cycle automatically;
  close/review UART first. The retained previous boot set remains available
- stop condition: no credential entry or owner creation belongs to A24
- operator action: selected `Launch Omarchy` exactly once, entered no
  credentials, and reported the visible `omarchy-ps4 login:` prompt
- bounded UART context:
  [`20260822_105053_589967-exp-20260822-009-a24-launch-corrected-gift-to-first-owner-setup-72613fce.md`](../../ps4-uart/sessions/20260822_105053_589967-exp-20260822-009-a24-launch-corrected-gift-to-first-owner-setup-72613fce.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: the v0.27 no-op verified the active four-file set and sent the exact
  `320936`-byte loader once. Linux retained UART, detected the exact Kingston
  USB serial `E0D55EA573F0194049CD0236`, resolved `LABEL=OMARCHY-PS4` to
  `/dev/sda`, validated and mounted it, then grew ext4 from `17179869184` to
  the full `123983626240` bytes. Owner setup emitted `stage=start` and
  `stage=root-verified` but neither `stage=prompt-ready` nor `stage=failed`;
  the operator instead saw the generic getty prompt. No owner credentials were
  entered and no account-creation/finalization stage was reached
- conclusion: fail for the required password-only first-owner UX. The bounded
  evidence narrows the stall to the code path after USB root verification and
  before the prompt-ready marker, likely during console/header acquisition;
  the correct image, kernel, initramfs and root filesystem were used
- local exact-image reproduction: the published image with uncompressed SHA-256
  `46ea6ca2c20b15cba9b40cb75bd07dbfa4c8a04d5d553eb27d0513b5c5f053df`
  was booted through the same kernel/initramfs in QEMU inside the required
  OrbStack Ubuntu VM, with its root disk exposed as USB and writes isolated by
  QEMU snapshot mode. It reached grow ready, `stage=start`,
  `stage=root-verified`, then `stage=prompt-ready`. A VGA capture after
  switching to tty1 showed the complete branded `WELCOME TO OMARCHY` keyboard
  form, while the separate serial console simultaneously displayed
  `omarchy-ps4 login:`. This proves the exact image can run the form and makes
  wrong active-VT/console ownership the next hardware hypothesis
- rollback: no boot or storage rollback. Preserve the expanded USB and pending
  owner state; do not attempt a guessed login
- next action: request one orderly console reboot, prove ext4 unmount, then
  inspect the actual USB owner log and systemd state offline on the Mac

### EXP-20260822-009-A25 — orderly reboot from stalled owner setup

- state: superseded before action by the exact-image VM console finding
- question: does one console Ctrl+Alt+Delete request stop userspace, remount the
  expanded external ext4 root read-only and return to Orbis without forced
  power loss?
- changed variable: press `Ctrl+Alt+Delete` once at the visible login prompt;
  do not enter credentials, unplug USB, press the PS4 power button or repeat
  the key sequence
- expected evidence: systemd enters reboot, stops the owner/grow services,
  unmounts or remounts `/dev/sda` read-only, synchronizes storage and returns to
  the Orbis boundary
- timeout: 3 minutes
- rollback: if the key sequence has no effect, stop/review before choosing a
  different shutdown mechanism; never unplug the mounted USB
- stop condition: no USB removal, relaunch, payload or second reboot belongs to
  A25
- operator action: none; no reboot was requested
- result: skipped. The new QEMU evidence provides a smaller reversible test:
  switch once to tty1, where the same exact image renders the owner wizard
- next action: A26 switches only the active Linux virtual terminal

### EXP-20260822-009-A26 — switch stalled first boot to owner tty1

- state: complete — fail
- question: is the owner wizard alive on tty1 while the operator is viewing a
  different console's generic getty prompt?
- changed variable: press `Ctrl+Alt+F1` once at the visible
  `omarchy-ps4 login:` screen; do not type credentials, repeat the shortcut,
  reboot, remove USB or press the PS4 power button
- expected evidence: tty1 becomes active, the branded `WELCOME TO OMARCHY`
  keyboard-selection form appears, and UART advances to `stage=prompt-ready`;
  no account is created merely by switching VTs
- timeout: 30 seconds
- rollback: if the display remains at login or becomes blank, press nothing;
  stop/review before any alternate VT or shutdown action
- stop condition: no form input belongs to A26
- operator action: pressed `Ctrl+Alt+F1` once and reported `same console`; no
  credentials, retry, reboot or USB change followed
- bounded UART context:
  [`20260822_110504_593823-exp-20260822-009-a26-switch-stalled-first-boot-to-owner-tty1-1696570c.md`](../../ps4-uart/sessions/20260822_110504_593823-exp-20260822-009-a26-switch-stalled-first-boot-to-owner-tty1-1696570c.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: fail. The display remained on the generic login prompt. UART showed
  only ordinary Wi-Fi scan traffic and no `prompt-ready`, `failed`, account or
  storage event. The PS4 owner process is therefore stopped or stalled before
  rendering, rather than merely waiting unseen on tty1
- rollback: none required; no account or storage state changed
- next action: perform an orderly console reboot, prove external-root unmount,
  then inspect the persisted service journal and owner log offline

### EXP-20260822-009-A27 — orderly reboot after owner renderer stall

- state: complete — degraded pass
- question: can one console Ctrl+Alt+Delete request cleanly stop the stalled
  first-owner service, synchronize and unmount the expanded USB, and return to
  Orbis for offline diagnosis?
- changed variable: press `Ctrl+Alt+Delete` once at the visible login prompt;
  do not enter credentials, remove USB, repeat the shortcut or use the PS4
  power button
- expected evidence: systemd enters reboot, terminates the stalled owner unit,
  remounts or unmounts `/dev/sda`, synchronizes storage and returns to Orbis
- timeout: 3 minutes
- rollback: if the shortcut has no effect, stop/review before any forced
  shutdown; never unplug the mounted root USB
- stop condition: no USB removal or next boot belongs to A27
- operator action: pressed `Ctrl+Alt+Delete` once, did not repeat it or remove
  USB, and reported that the console rebooted
- bounded UART context:
  [`20260822_110938_076538-exp-20260822-009-a27-orderly-reboot-after-owner-renderer-stall-f22a0527.md`](../../ps4-uart/sessions/20260822_110938_076538-exp-20260822-009-a27-orderly-reboot-after-owner-renderer-stall-f22a0527.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: degraded pass. Linux journald received SIGTERM from
  `systemd-shutdown`, firmware entered S5 preparation, and the kernel emitted
  `reboot: Restarting system`/`machine restart`; no panic or forced-power event
  appeared. Continuous UART subsequently showed a complete Orbis boot and
  `network ready` at `192.168.50.215`
- degradation: the persistent boot console did not print an explicit ext4
  unmount/remount-read-only or sync line. Verify the filesystem with offline
  read-only `e2fsck -fn` before any write
- rollback: none; console is back in Orbis and the external root is no longer
  Linux-mounted
- next action: disconnect only the corrected USB from stable Orbis, then close
  the session before attaching it to the Mac

### EXP-20260822-009-A28 — disconnect expanded gift USB from Orbis

- state: complete — pass; offline audit found and fixed owner-console bug
- question: can the corrected expanded USB be disconnected from stable Orbis
  without changing any other console state?
- changed variable: physically remove only the Kingston Omarchy USB; leave
  power, UART, HDMI, controller, keyboard and all other devices unchanged
- expected evidence: Orbis records the matching USB device removal and remains
  responsive; no Linux/storage activity occurs
- timeout: 30 seconds
- rollback: if Orbis shows a prompt, do not select format/initialize; report it
  and stop
- stop condition: do not attach the USB to the Mac in A28
- operator action: removed the USB from Orbis and connected it to the Mac
- bounded UART context:
  [`20260822_111104_611449-exp-20260822-009-a28-disconnect-expanded-gift-usb-from-orbis-286d80d7.md`](../../ps4-uart/sessions/20260822_111104_611449-exp-20260822-009-a28-disconnect-expanded-gift-usb-from-orbis-286d80d7.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- offline conclusion: the actual USB journal proved
  `omarchy-ps4-provision-owner.service` was killed by `status=1/HUP` when
  `console-getty.service` occupied the PS4 console. Ext4 was repaired and
  rechecked clean. The USB was atomically upgraded to `omarchy-ps4-settings
  4.0.0-2`, `omarchy-ps4 4.0.0-2`, and provisioning `4.0.0-6`, adding the
  console-getty conflict plus the omitted fixed 1080p60/scale-one and
  animations-off overrides
- exact physical-USB VM result: QEMU snapshot boot in OrbStack reached owner
  `start`, `root-verified`, and `prompt-ready`; VGA tty1 displayed the branded
  keyboard form, with no HUP, failed unit, getty login or physical-disk write.
  Final `e2fsck -fn` returned zero
- next action: one direct-PayLoader PS4 boot of the hotfixed USB; the FPKG UI
  is not part of this iteration

### EXP-20260822-009-A29 — direct-loader boot of hotfixed owner USB

- state: complete — fail before Linux takeover
- objective: boot the hotfixed physical USB once through GoldHEN PayLoader and
  verify that PS4 hardware reaches the branded owner form without HUP/getty
- sequence: connect the clean USB, enable GoldHEN/PayLoader if needed, send the
  already-pinned loader once to port 9090, and observe through `prompt-ready`;
  do not enter owner data in this acceptance step
- expected evidence: existing internal boot set verifies, initramfs mounts the
  exact Kingston USB, owner service remains alive and reaches `prompt-ready`,
  and HDMI shows `WELCOME TO OMARCHY` rather than a login prompt
- timeout: 5 minutes; stop on the first owner form or terminal fault
- rollback: one Ctrl+Alt+Delete orderly return if the boot reaches a stable
  console failure; no repeated payload send
- operator action: connected the exact hotfixed USB, activated GoldHEN and
  PayLoader, and performed no input after the host sent the pinned loader once
- bounded UART context:
  [`20260822_113008_809346-exp-20260822-009-a29-direct-loader-boot-of-hotfixed-owner-usb-59ca2f3e.md`](../../ps4-uart/sessions/20260822_113008_809346-exp-20260822-009-a29-direct-loader-boot-of-hotfixed-owner-usb-59ca2f3e.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: fail before Linux takeover. The host `nc` process exited nonzero and
  UART recorded `[GoldHEN] <payloader> Error handling payload`; no loader,
  kernel, initramfs or USB-root output followed. Orbis remained running, so no
  boot or USB state changed
- conclusion: the generic `nc` stream did not preserve the FPKG adapter's
  required transport contract: a send buffer large enough for the complete
  `320936`-byte loader followed by exactly one application `send()` call
- rollback: none required; Linux never took over and the USB was not mounted
- next action: repeat only the transport with a locally verified single-write
  sender; keep the loader, internal boot set, USB and console state unchanged

### EXP-20260822-009-A30 — single-write direct-loader boot

- state: complete — pass on UART; HDMI confirmation pending
- question: does the pinned loader boot correctly when the remote transport
  matches the FPKG's proven one-buffer, one-`send()` contract?
- changed variable: replace `nc` with `fpkg/tools/send-loader-once.c`, using a
  1 MiB send buffer and exactly one application `send()` for the same verified
  `320936`-byte loader; change nothing else
- expected evidence: the sender reports `requested=320936 written=320936`,
  GoldHEN begins loader output without a payloader error, the initramfs mounts
  Kingston serial `E0D55EA573F0194049CD0236`, and owner setup reaches
  `stage=prompt-ready` with the branded HDMI form
- timeout: 5 minutes; continuing UART progress extends observation, but stop
  on the owner form or first terminal fault
- rollback: if Linux reaches a stable console failure, request one orderly
  Ctrl+Alt+Delete only after closing/reviewing the session; never resend the
  payload in the same experiment
- operator action: re-enabled GoldHEN BinLoader after the pre-send connection
  refusal, then performed no input while the verified sender made one complete
  loader write; visible HDMI outcome is pending operator report
- bounded UART context:
  [`20260822_120247_694265-exp-20260822-009-a30-single-write-direct-loader-boot-0ffb5de2.md`](../../ps4-uart/sessions/20260822_120247_694265-exp-20260822-009-a30-single-write-direct-loader-boot-0ffb5de2.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass for the UART acceptance criteria. The host reported one complete
  `320936`-byte write; GoldHEN logged the same received size and successful ELF
  launch. Linux 6.18.44-ps4-baikal started, detected exact Kingston serial
  `E0D55EA573F0194049CD0236`, mounted ext4 UUID
  `abb7b8bc-79f9-4efe-a325-01eabca940bb`, and owner setup advanced through
  `stage=start`, `stage=root-verified`, and `stage=prompt-ready` without the
  former HUP, console-getty collision or generic-login marker
- conclusion: the owner-console hotfix works on real PS4 hardware and direct
  iteration must use the new single-write sender rather than generic `nc`.
  Final visual classification waits only for the operator's HDMI report
- rollback: none; Linux is intentionally left at the non-destructive owner
  prompt and no credentials have been entered
- next action: record whether HDMI shows the branded `WELCOME TO OMARCHY`
  owner form; do not enter owner data until that report is captured

### EXP-20260822-009-A31 — local live graphics and Wi-Fi audit

- state: complete — pass; both causes identified
- question: did the PS4 no-tiling environment reach the current Hyprland
  session, and does NetworkManager see the built-in MT7668 radio?
- changed variable: none; print only `AMD_DEBUG` and `nmcli device` in the
  existing graphical terminal. Do not connect a network, start SSH, restart a
  process or modify configuration
- expected evidence: `AMD_DEBUG=notiling`; NetworkManager lists a Wi-Fi device
  and its exact state. The operator reports the terminal output while UART
  remains free of a new GPU, filesystem or USB fault
- timeout: 2 minutes after the operator command
- rollback: none for read-only inspection; leave the current desktop running
- operator action: opened Foot in the existing Omarchy session and ran exactly
  `echo AMD_DEBUG=$AMD_DEBUG; nmcli device`; supplied physical HDMI photo
  `IMG_0175.HEIC`
- bounded UART context:
  [`20260822_121436_516206-exp-20260822-009-a31-local-live-graphics-and-wi-fi-audit-52056e3f.md`](../../ps4-uart/sessions/20260822_121436_516206-exp-20260822-009-a31-local-live-graphics-and-wi-fi-audit-52056e3f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass for diagnosis. The terminal printed an empty `AMD_DEBUG`,
  proving the packaged global UWSM override did not reach this owner session;
  this exactly explains recurrence of the previously proven Liverpool tiled
  scanout corruption. NetworkManager listed `ap0`, `ap1`, and `wlan0` as Wi-Fi
  devices, all disconnected, plus their P2P interfaces. UART independently
  showed repeated successful MT7668 scan-to-idle cycles with no firmware-probe
  failure, so the internal Wi-Fi driver is present and operating
- conclusion: install the no-tiling environment in the owner-visible UWSM
  user-config boundary, not only `/usr/share/uwsm`; add Wi-Fi selection to the
  owner/onboarding flow instead of adding duplicate driver packages
- rollback: none; the diagnostic changed no state
- next action: implement and locally test the corrected session environment,
  quiet-HDMI boot profile, one-time first-owner autologin, branded LightDM
  recovery greeter, and PS4-owned update policy before one live application

### EXP-20260822-009-A32 — attach freshly flashed gift USB

- state: complete — inconclusive; scope mixed before attachment was proven
- question: does Orbis detect attachment of the freshly flashed, Etcher-verified
  Kingston gift USB without attempting to initialize or alter it?
- changed variable: attach only the freshly flashed Kingston DataTraveler 3.0
  USB to the PS4; do not open Omarchy, update boot files, send a payload, or
  launch Linux
- expected evidence: UART records one matching USB attachment while Orbis
  remains responsive; no Linux, loader, filesystem-mount, or storage-write
  activity occurs
- timeout: 30 seconds after attachment
- rollback: if Orbis offers to format or initialize the unsupported filesystem,
  cancel or dismiss the prompt; do not accept it, then leave the USB attached
- operator action: no attachment outcome was reported; during the open window,
  the operator attempted to launch the Netflix/Hack Vue mini-app instead
- bounded UART context:
  [`20260822_143746_989542-exp-20260822-009-a32-attach-freshly-flashed-gift-usb-af59d8f7.md`](../../ps4-uart/sessions/20260822_143746_989542-exp-20260822-009-a32-attach-freshly-flashed-gift-usb-af59d8f7.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: inconclusive for USB attachment. UART records repeated launches of
  `CUSA00960` version `01.24`, common-dialog focus/suspend activity, and a later
  Orbis boot sequence. It does not identify the freshly flashed Kingston USB
  or establish the predeclared attach-only outcome
- rollback: none applied; do not infer anything about the flashed USB from
  this mixed session
- next action: restore the local JB/DNS services in OrbStack, then start a new
  bounded attach-only session after the console-side Vue launcher is healthy

### EXP-20260822-010-A1 — observe one Netflix launch through local proxy

- state: superseded before bounded action; no UART session was started
- question: does Netflix `01.53` reach the local proxy and request the
  injectable error-page script before the app exits, hangs, or reboots?
- changed variable: replace the proxy's interactive TUI with functionally
  equivalent `mitmdump` request logging; leave DNS, proxy address, app,
  firmware, USB and payload unchanged
- expected evidence: proxy records the PS4 connection plus either the
  `config.text.lruderrorpage` injection request or the exact last host/path;
  UART identifies the CUSA/version and terminal app event
- timeout: 60 seconds after selecting Netflix; stop immediately on reboot,
  kernel panic or a displayed error
- rollback: press PS once to return home if the app merely hangs; do not retry
  the launch in this session
- operator action: before the bounded session began, the operator independently
  launched Netflix from the Apps library and reported that it worked
- conclusion: the report establishes that the current DNS/proxy path can load
  Netflix, but it is not bounded UART evidence and does not diagnose Vue. Close
  this proposed action without inventing a session artifact
- next action: recover Vue `CUSA00960` as a separate, predeclared backup and
  reinstall sequence using the already-curated procedure

### EXP-20260822-011-A1 — stage Vue recovery bundle over GoldHEN FTP

- state: complete — pass; Vue application absent and recovery set verified
- question: can the known-good Vue 1.01/1.24 recovery bundle be staged and
  reread over GoldHEN FTP while preserving the installed application, save,
  database and current GoldHEN runtime?
- changed variable: create only `/data/vue-after-free-recovery` and place the
  pinned local recovery artifacts there; inspect and back up current
  `CUSA00960` metadata without overwriting its live paths
- expected evidence: FTP inventory identifies the current Vue/save state and
  reread SHA-256 values for every staged artifact match the Mac originals;
  UART remains in the current stable Orbis/GoldHEN runtime
- timeout: 10 minutes; stop on FTP disconnect, storage error, hash mismatch,
  application exit or console reboot
- rollback: remove only `/data/vue-after-free-recovery`; the installed Vue app,
  live save, `/user/download/CUSA00960` and app database remain untouched
- operator action: operator reported Netflix/GoldHEN active and made no
  requested Vue install or delete action during staging
- bounded UART context:
  [`20260822_152121_109820-exp-20260822-011-a1-stage-vue-recovery-bundle-over-goldhen-ftp-57644cc3.md`](../../ps4-uart/sessions/20260822_152121_109820-exp-20260822-011-a1-stage-vue-recovery-bundle-over-goldhen-ftp-57644cc3.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. FTP proved `CUSA00960` is absent from `/user/app`,
  `/user/patch`, `/user/download`, and appmeta, so this is a missing
  application rather than a DNS or app-database presentation fault. Encrypted
  save containers and metadata for users `1ab07dc7`, `1ab07dc9`, and
  `1ab07dca`, all three savedata databases, `app.db`, and `addcont.db` were
  copied to `backups/vue-after-free/EXP-20260822-011-A1`
- staged evidence: existing `/data/pkg` base 1.01 and patch 1.24 reread hashes
  matched local SHA-256 `b6a0cb05...f797dd7` and
  `3b738e36...26b9e9`. The three recovery archives were uploaded to
  `/data/vue-after-free-recovery` and reread with exact matching hashes
- UART conclusion: continuity completed with no storage, database or console
  fault during transfer. The slice did show Apollo resident and an older
  GoldHEN PayLoader error, neither correlated with the FTP writes
- rollback: not required; live Vue/save/database paths were not modified
- next action: install only the verified Vue 1.01 base from `/data/pkg`, then
  close and inspect that bounded action before installing patch 1.24

### EXP-20260822-011-A2 — install verified Vue 1.01 base

- state: complete — pass
- question: does GoldHEN Package Installer restore the missing `CUSA00960`
  base application from the already-verified 1.01 FPKG?
- changed variable: install only
  `UT0016-CUSA00960_00-COBRAPCKGE000000-A0101-V0100.pkg`; do not install the
  1.24 patch, restore a save, copy `download0.dat`, or launch Vue yet
- expected evidence: package installation completes once, UART records the
  corresponding BGFT/app registration without storage error, and the Vue icon
  returns at base version 1.01
- timeout: 3 minutes after selecting the base package; stop on the first
  completion or exact error
- rollback: on error, do not retry, delete, rebuild databases or select the
  patch; leave the reported state for inspection
- operator action: installed the base package once and reported `installed
  v0100`; did not install patch 1.24 or launch Vue
- bounded UART context:
  [`20260822_152701_720359-exp-20260822-011-a2-install-verified-vue-1-01-base-93876276.md`](../../ps4-uart/sessions/20260822_152701_720359-exp-20260822-011-a2-install-verified-vue-1-01-base-93876276.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. BGFT copied all `72417280` bytes, app install returned
  `0x00000000`, and task `00000338` ended with `error=0x0`. FTP then proved
  `/user/app/CUSA00960` and appmeta exist while `/user/patch/CUSA00960` is
  still absent as required
- version evidence: appmeta `param.sfo` reports `TITLE_ID=CUSA00960`,
  `APP_VER=01.00`, and package `VERSION=01.01`; this is the intended base
- rollback: not required; the clean base remains installed
- next action: install only the verified 1.24 patch, then close and verify it
  before touching the live save or `download0.dat`

### EXP-20260822-011-A3 — install verified Vue 1.24 patch

- state: complete — pass
- question: does GoldHEN Package Installer apply the matching Vue 1.24 patch
  cleanly to the verified 1.01 base?
- changed variable: install only
  `UT0016-CUSA00960_00-COBRAPCKGE000000-A0124-V0100.pkg`; do not restore a
  save, copy `download0.dat`, launch Vue or alter account activation
- expected evidence: package installation completes once, UART records a
  clean patch registration, `/user/patch/CUSA00960` appears, and appmeta
  reports application version 01.24
- timeout: 3 minutes after selecting the patch; stop on the first completion
  or exact error
- rollback: on error, do not retry or launch Vue; retain the clean 1.01 base
  and inspect the partial patch state
- operator action: installed the 1.24 patch once and did not launch Vue
- bounded UART context:
  [`20260822_153426_205904-exp-20260822-011-a3-install-verified-vue-1-24-patch-3d81eb7f.md`](../../ps4-uart/sessions/20260822_153426_205904-exp-20260822-011-a3-install-verified-vue-1-24-patch-3d81eb7f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. BGFT transferred all `89849856` bytes,
  `AppInstallPatch2` returned `0x00000000`, and task `0000033a` ended with
  `error=0x0`. FTP proved `/user/patch/CUSA00960` exists and appmeta reports
  `APP_VER=01.24`
- rollback: not required; matching base 1.01 plus patch 1.24 remain installed
- next action: copy and reread the pinned `download0.dat` at the exact live
  `CUSA00960` path while leaving all saves unchanged

### EXP-20260822-011-A4 — install verified Vue download data

- state: complete — pass
- question: can the pinned 256 MiB Vue `download0.dat` be placed at the exact
  live path and reread byte-for-byte without disturbing the installed app or
  saves?
- changed variable: create `/user/download/CUSA00960` and write only
  `/user/download/CUSA00960/download0.dat` from the local recovery artifact
- expected evidence: FTP upload completes, remote size is `268435456`, reread
  SHA-256 equals `e043246ac9eec77387630a1b8e359bf60d742c94a8f1b77c024ae159de888e31`,
  and UART shows no storage fault
- timeout: 10 minutes; stop on disconnect, short transfer, hash mismatch,
  storage error or console reboot
- rollback: delete only the newly written live `download0.dat` and its empty
  `CUSA00960` download directory; retain the verified app and all saves
- operator action: keep Vue closed and do not change application or account
  state during the transfer
- bounded UART context:
  [`20260822_153605_629524-exp-20260822-011-a4-install-verified-vue-download-data-b13643d9.md`](../../ps4-uart/sessions/20260822_153605_629524-exp-20260822-011-a4-install-verified-vue-download-data-b13643d9.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. FTP reported remote length `268435456`; a complete remote
  reread produced SHA-256
  `e043246ac9eec77387630a1b8e359bf60d742c94a8f1b77c024ae159de888e31`,
  exactly matching the pinned local artifact
- UART conclusion: continuity completed with no storage, application or
  console fault during the write and reread
- rollback: not required; verified `download0.dat` remains at the exact live
  `CUSA00960` path
- next action: stage the supplied decrypted Vue save as a distinct Apollo Fake
  USB source without overwriting any live save

### EXP-20260822-011-A5 — stage Vue save for Apollo

- state: complete — pass
- question: can the supplied Vue decrypted save be staged as a distinct Apollo
  Fake USB entry with exact file hashes while preserving all live saves?
- changed variable: create only
  `/data/fakeusb/PS4/APOLLO/recovery_CUSA00960_localstorage.aes` from the pinned
  `save.zip`; do not invoke Apollo copy/resign or alter the active user
- expected evidence: all six staged files reread with hashes matching the
  extracted local source and UART shows no storage fault
- timeout: 5 minutes; stop on an existing-path conflict, disconnect, short
  transfer, hash mismatch, storage error or console reboot
- rollback: remove only the new `recovery_CUSA00960_localstorage.aes` Fake USB
  source directory; all live saves and their databases remain untouched
- operator action: keep Vue closed and do not use Apollo until staging is
  verified and this session is closed
- bounded UART context:
  [`20260822_153938_702383-exp-20260822-011-a5-stage-vue-save-for-apollo-22c85027.md`](../../ps4-uart/sessions/20260822_153938_702383-exp-20260822-011-a5-stage-vue-save-for-apollo-22c85027.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. A previously absent, uniquely named Fake USB source was
  created and all six files reread with SHA-256 values exactly matching the
  extracted pinned `save.zip`
- UART conclusion: continuity completed with no storage or console fault; the
  slice contains only a routine shell heap line
- rollback: not required; no live save was modified
- next action: use Apollo once to copy/resign this exact Fake USB source to the
  active user `1ab07dc7`, then inspect before launching Vue

### EXP-20260822-011-A6 — restore Vue save to active user with Apollo

- state: complete — pass with corrected UI description
- question: can Apollo copy and resign the verified supplied Vue save to the
  current user while preserving the now-verified application and download
  data?
- changed variable: in Apollo, copy only
  `recovery_CUSA00960_localstorage.aes` from Fake USB to HDD for the active
  user `1ab07dc7`; do not activate accounts, rebuild databases, launch Vue or
  alter the other two users' saves
- expected evidence: Apollo reports a successful copy/resign, UART records no
  save-mount/database fault, and the current user's CUSA00960 save remains
  present afterward
- timeout: 3 minutes after selecting Copy save game; stop on the first success
  or exact error
- rollback: do not launch Vue on error; retain the pre-action encrypted save,
  savedata database and app database backup under
  `backups/vue-after-free/EXP-20260822-011-A1` for deliberate recovery
- operator action: selected the staged Vue item and chose Apollo's Copy save
  game action. No separate user-selection or resign screen existed; the
  current user was handled automatically
- bounded UART context:
  [`20260822_154048_541812-exp-20260822-011-a6-restore-vue-save-to-active-user-with-apollo-4e37471f.md`](../../ps4-uart/sessions/20260822_154048_541812-exp-20260822-011-a6-restore-vue-save-to-active-user-with-apollo-4e37471f.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. UART records Apollo's PFS save mount and clean unmount, common
  dialogs, and successful return to Apollo without a save/database fault.
  Post-action FTP proves the active user's save remains present; its
  `sdimg_localstorage.aes` changed from SHA-256 `3e54889c...f10730` to
  `4cb93531...00a8e3`, while binding file `localstorage.aes.bin` correctly
  remained `8a966544...d54e4`
- correction: Apollo auto-detected the current user. The previously stated
  separate user-selection and resign confirmation steps do not exist in this
  flow and must not be repeated in operator guidance
- rollback: not required; the pre-action encrypted save and databases remain
  preserved locally
- next action: close Apollo and launch restored Vue once; dismiss only the
  documented PSN prompt with OK and stop on the first Vue UI or exact fault

### EXP-20260822-011-A7 — launch restored Vue once

- state: complete — pass
- question: does the fully restored Vue 1.24 application reach its exploit UI
  from the active user's resigned supplied save?
- changed variable: close Apollo and launch `CUSA00960` once; if the documented
  `This service requires you to sign in to PlayStation Network` prompt appears,
  press OK exactly once and make no other selection
- expected evidence: UART launches `CUSA00960` version 01.24 without package,
  PFS or save fault, and HDMI reaches the Vue After Free interface after at
  most the single expected PSN prompt
- timeout: 90 seconds after selecting Vue; stop immediately on exploit UI,
  exact displayed error, crash, hang or reboot
- rollback: if Vue merely hangs, press PS once to return home after reporting;
  do not relaunch, reinstall, rebuild or modify the save in this session
- operator action: closed Apollo, launched PlayStation Vue once, followed the
  documented prompt path, reported `done working`, and returned to the main
  Omarchy task without retrying
- bounded UART context:
  [`20260822_165244_536318-exp-20260822-011-a7-launch-restored-vue-once-e59f7713.md`](../../ps4-uart/sessions/20260822_165244_536318-exp-20260822-011-a7-launch-restored-vue-once-e59f7713.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. UART launched `CUSA00960` with `version: 01.24`, mounted the
  exact `download0.dat`, mounted active-user save `localstorage.aes`, focused
  the app, and later returned to Orbis through a deliberate app kill with all
  PFS/download mounts cleanly unmounted. There was no crash, panic or reboot
- conclusion: Vue After Free is restored and available as the known fallback;
  DNS was not the cause. The missing application was repaired with exact base
  1.01, patch 1.24, download data and Apollo save
- rollback: not required; preserve the verified working Vue installation
- next action: resume the Omarchy gift-USB boot plan from the last proven
  Orbis/GoldHEN state

### EXP-20260822-009-A33 — read-only gift USB presence check

- state: complete — blocked precondition identified
- question: is the freshly flashed Kingston Omarchy gift USB currently visible
  to stable Orbis/GoldHEN before any Linux loader is sent?
- changed variable: none; inspect only current FTP device/mount inventory and
  bounded UART state without attaching, removing, formatting or writing USB
- expected evidence: current Orbis device inventory distinguishes a connected
  mass-storage device from no external root, while FTP/PayLoader and UART stay
  healthy
- timeout: 60 seconds; stop on FTP loss, serial continuity loss or any console
  state transition
- rollback: none for read-only inspection; do not send a payload or ask the
  operator to reconnect hardware in this action
- operator action: none; leave the console and USB exactly as they are
- bounded UART context:
  [`20260822_165629_645931-exp-20260822-009-a33-read-only-gift-usb-presence-check-f31f4393.md`](../../ps4-uart/sessions/20260822_165629_645931-exp-20260822-009-a33-read-only-gift-usb-presence-check-f31f4393.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: blocked precondition. Orbis exposes only internal `da0`, known USB
  endpoints `0.2.0` through `0.5.0`, and empty `/mnt/usb0` through `usb7`;
  there is no external `da1` or Kingston device. The verified internal boot
  directory still contains `bzImage`, `initramfs.cpio.gz`, `bootargs.txt`, and
  `vram.txt`. PayLoader port 9090 is currently closed
- UART conclusion: continuity completed with only routine shell heap output;
  the read-only check changed no state
- rollback: none
- next action: attach only the freshly flashed Kingston gift USB and stop at
  any unsupported-filesystem prompt before enabling PayLoader or booting

### EXP-20260822-009-A34 — attach freshly flashed gift USB only

- state: complete — pass
- question: does Orbis enumerate the freshly flashed Kingston gift USB while
  remaining stable and leaving its Linux filesystem untouched?
- changed variable: attach only the Kingston DataTraveler 3.0 gift USB to the
  PS4; do not enable PayLoader, update boot files, launch Omarchy, format,
  initialize or dismiss a filesystem prompt
- expected evidence: UART records one new mass-storage device corresponding to
  the Kingston and Orbis remains responsive; the expected unsupported-filesystem
  prompt may appear and is left untouched
- timeout: 30 seconds after attachment; stop on the first prompt, device event,
  console fault or timeout
- rollback: if Orbis offers format/initialize, do not accept it; leave the USB
  attached and report the exact prompt
- operator action: attached the freshly flashed Kingston once and made no
  other reported UI or hardware action
- bounded UART context:
  [`20260822_165748_493491-exp-20260822-009-a34-attach-freshly-flashed-gift-usb-only-af8cd6ed.md`](../../ps4-uart/sessions/20260822_165748_493491-exp-20260822-009-a34-attach-freshly-flashed-gift-usb-only-af8cd6ed.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. UART identified exact Kingston serial
  `E0D55EA573F0194049CD0236` as SuperSpeed `/dev/da1`, size `118240MB`, and
  reported unknown format as expected for the Linux filesystem. Orbis did not
  format, encrypt or mount it
- rollback: none; leave the verified USB attached
- next action: dismiss only the unsupported-filesystem modal if visible, then
  separately enable PayLoader before one boot attempt

### EXP-20260822-009-A35 — dismiss unsupported-filesystem modal

- state: complete — pass by operator report
- question: can Orbis clear only the expected unsupported-filesystem modal and
  return to a responsive home screen while leaving `/dev/da1` attached?
- changed variable: if the unsupported-filesystem modal is visible, press OK
  once; otherwise perform no input and report that no modal is visible
- expected evidence: the modal closes or is confirmed absent, Orbis remains
  responsive, and UART records no USB detach, format, initialization or fault
- timeout: 30 seconds after the one input or no-modal report
- rollback: none; never select format, initialize or extended storage
- operator action: operator confirmed the modal step and requested the next
  action; no format, initialization or storage conversion was selected
- bounded UART context:
  [`20260822_165910_639070-exp-20260822-009-a35-dismiss-unsupported-filesystem-modal-497af87c.md`](../../ps4-uart/sessions/20260822_165910_639070-exp-20260822-009-a35-dismiss-unsupported-filesystem-modal-497af87c.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. Orbis remained idle and stable with no USB detach, format,
  initialization, storage write or fault in the bounded slice
- rollback: none; exact Kingston remains attached
- next action: enable only GoldHEN BinLoader/PayLoader and prove port 9090 is
  listening before any loader send

### EXP-20260822-009-A36 — enable GoldHEN BinLoader only

- state: complete — degraded; listener enabled but consumed by invalid probe
- question: does enabling GoldHEN BinLoader expose the expected PayLoader on
  TCP 9090 while Orbis and the attached Kingston remain stable?
- changed variable: enable only GoldHEN Settings → Servers Settings → BinLoader
  Server; do not open Omarchy, send a payload, update boot files or alter USB
- expected evidence: UART records the server start without payload handling or
  USB detach; a raw TCP connection was initially specified as listener proof
- timeout: 30 seconds after enabling; stop on listener proof or exact error
- rollback: if enabling fails, leave it off and do not retry in this session
- operator action: enabled only GoldHEN BinLoader in Servers Settings; no
  Omarchy UI action, boot-file change or USB action was performed
- bounded UART context:
  [`20260822_170213_396805-exp-20260822-009-a36-enable-goldhen-binloader-only-26c6e95c.md`](../../ps4-uart/sessions/20260822_170213_396805-exp-20260822-009-a36-enable-goldhen-binloader-only-26c6e95c.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: degraded. UART proves `[GoldHEN] <payloader> Server started at 9090
  port`, and the host TCP connection succeeded. GoldHEN then emitted
  `<payloader> Error handling payload` because the empty health-check
  connection was interpreted as a payload and consumed the one-shot listener.
  Orbis remained responsive and no USB detach or storage write occurred
- conclusion: never test GoldHEN BinLoader with a bare TCP connect. Listener
  readiness must come from the UART start marker; after enabling it, the next
  and only connection must be the complete loader transfer
- rollback: no storage rollback is needed. Treat the current listener as spent;
  toggle BinLoader off/on once in a new bounded action before the real send
- next action: re-arm BinLoader only, without any network probe, then close and
  review that bounded session before one separately bounded loader send

### EXP-20260822-009-A37 — one-write gift-USB boot after operator re-arm

- state: complete — blocked before payload transfer
- question: will the already-proven pinned loader boot the freshly flashed
  Kingston gift USB when its only BinLoader connection is one complete
  application-level write?
- changed variable: send exactly the pinned 320,936-byte PS4 Linux Loader v25
  ELF, SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`,
  to `192.168.50.215:9090` using the proven 1 MiB socket buffer and one
  `send()` call; do not probe, reconnect, retry, alter boot files or touch USB
- precondition note: the operator reports toggling BinLoader off/on immediately
  before A37, but that toggle occurred before a bounded session and is not
  accepted as standalone hardware evidence. A37 will rely only on the actual
  transfer and resulting UART evidence
- expected evidence: the sender reports
  `requested=320936 written=320936`; GoldHEN logs the matching receive and ELF
  launch; Linux 6.18.44-ps4-baikal identifies Kingston serial
  `E0D55EA573F0194049CD0236`, mounts the intended external root, and advances
  to either the branded owner setup or native Omarchy display without a login
  prompt or terminal fault
- timeout: 5 minutes; continuing boot output extends observation, but stop on
  the owner form, desktop, exact terminal fault, reboot or HDMI loss
- rollback: on connection failure or loader error, remain in Orbis and do not
  retry. On a stable Linux failure, close and review before any orderly reboot;
  never send another payload in A37
- operator action: none during the send; the operator had reported restarting
  BinLoader immediately before the bounded session
- bounded UART context:
  [`20260822_171012_352378-exp-20260822-009-a37-one-write-gift-usb-boot-after-operator-re-a-85ea55c6.md`](../../ps4-uart/sessions/20260822_171012_352378-exp-20260822-009-a37-one-write-gift-usb-boot-after-operator-re-a-85ea55c6.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`; the bounded slice contains
  zero bytes because the connection failed before the console emitted output
- result: blocked before payload transfer. The exact sender returned
  `connect: Connection refused` and therefore made no `send()` call. Linux did
  not start and neither internal boot files nor the attached USB were touched
- conclusion: the operator-reported pre-session restart did not leave a live
  listener. Continuous UART surrounding A37 contains no new
  `<payloader> Server started at 9090 port` marker, so readiness cannot be
  inferred from the UI report
- rollback: none required; no payload bytes or storage writes occurred
- next action: in a new bounded session, deliberately set BinLoader OFF, then
  ON once and accept only the UART `Server started` marker as proof. Do not
  connect to 9090 in that re-arm session

### EXP-20260822-009-A38 — deliberate UART-proven BinLoader re-arm

- state: complete — pass
- question: does an explicit OFF-to-ON BinLoader transition create one fresh
  listener, proven only by GoldHEN's UART start marker?
- changed variable: in GoldHEN Servers Settings, set BinLoader Server OFF and
  then ON exactly once; do not launch Omarchy, connect to port 9090, alter boot
  files, touch USB or change any other setting
- expected evidence: UART emits exactly one new
  `[GoldHEN] <payloader> Server started at 9090 port` marker and no payload
  handling error, crash, detach or storage event follows
- timeout: 45 seconds after the ON transition; stop immediately on the marker
  or exact error
- rollback: if the marker does not appear, leave the displayed toggle state as
  observed and do not repeat the transition in A38
- operator action: set BinLoader Server OFF and then ON exactly once, then
  returned to the Orbis content area without launching Omarchy or changing any
  other reported setting
- bounded UART context:
  [`20260822_171117_374432-exp-20260822-009-a38-deliberate-uart-proven-binloader-re-arm-41f5d5ca.md`](../../ps4-uart/sessions/20260822_171117_374432-exp-20260822-009-a38-deliberate-uart-proven-binloader-re-arm-41f5d5ca.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. UART contains exactly one fresh
  `[GoldHEN] <payloader> Server started at 9090 port` marker and no payload
  handling error, crash, USB detach or storage event
- rollback: none; preserve the untouched one-shot listener for the next action
- next action: send the pinned loader exactly once with the proven one-write
  sender in a separately bounded boot session; never probe or retry

### EXP-20260822-009-A39 — UART-proven one-write gift-USB boot

- state: complete — functional pass; UI/UX acceptance remains open
- question: does the pinned loader boot the freshly flashed Kingston gift USB
  from the freshly UART-proven GoldHEN listener?
- changed variable: make the listener's only connection and send exactly the
  pinned 320,936-byte Loader v25 ELF, SHA-256
  `c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`,
  with a 1 MiB socket buffer and one `send()` call; do not probe, reconnect,
  retry, alter boot files or touch USB
- expected evidence: host reports `requested=320936 written=320936`; GoldHEN
  logs the matching receive and successful ELF launch; Linux
  6.18.44-ps4-baikal finds Kingston serial `E0D55EA573F0194049CD0236`, mounts the
  intended external root, and reaches the branded owner setup or native
  Omarchy display without a generic login prompt or terminal fault
- timeout: 5 minutes; continuing boot output extends observation, but stop on
  the first stable owner form, desktop, exact terminal fault, reboot or HDMI
  loss
- rollback: if the connection or loader fails, remain in Orbis and do not
  retry. If Linux reaches a stable failure, close and review before a separate
  orderly reboot; never send another payload in A39
- operator action: left the controller and USB untouched during handoff and
  boot. After the branded owner form appeared, completed the username/password
  setup and confirmed that Linux reached the graphical login screen
- bounded UART context:
  [`20260822_171638_096973-exp-20260822-009-a39-uart-proven-one-write-gift-usb-boot-44ec4cb3.md`](../../ps4-uart/sessions/20260822_171638_096973-exp-20260822-009-a39-uart-proven-one-write-gift-usb-boot-44ec4cb3.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- transfer result: pass. The host made one complete write,
  `requested=320936 written=320936 send-buffer=1048576 errno=0`. GoldHEN
  recorded the same 320,936-byte payload, launched the ELF successfully, and
  emitted no PayLoader error
- boot result: pass. Linux `6.18.44-ps4-baikal` detected exact Kingston serial
  `E0D55EA573F0194049CD0236`; initramfs resolved `LABEL=OMARCHY-PS4` to
  `/dev/sda`, mounted ext4 UUID `f04782f3-7809-4e38-9325-1ea948086f7d`
  read-write, validated external root, and started systemd
- first-boot result: pass. The whole-device filesystem grew automatically from
  17,179,869,184 bytes to the full 123,983,626,240-byte device. Owner setup
  reached `stage=start`, `root-verified`, `prompt-ready`, `finalizing`, and
  `complete`; the operator confirmed the graphical login screen appeared
- isolation note: owner entry occurred after the boot criteria passed but
  before A39 closed. Functional evidence is valid within completed UART
  continuity, though boot and owner-flow interaction were combined in this
  bounded slice and therefore do not replace later repeated cold-boot
  acceptance
- HDMI UX finding: the post-setup login card is offset into the lower-right
  quadrant instead of being centered. Source inspection identified
  `position=50% 50%`, which anchors the card's top-left at the screen midpoint;
  it must use `position=50%,center 50%,center`. The first-boot console also
  exposes too much diagnostic output and needs a clean Omarchy-green branded
  setup surface while detailed evidence remains on UART and in the root-only
  provisioning log
- conclusion: the product architecture is now proven once end-to-end on the
  Baikal lab console: internal boot files plus GoldHEN Loader v25 start the
  external whole-device Omarchy USB, expand it automatically, and complete
  password-based first-owner provisioning. This is a development acceptance
  success, not a public-support or final-UX claim
- rollback: none required; preserve the running gift USB and newly created
  owner. Do not re-arm provisioning or erase the owner merely to iterate on UI
- next action: local-only first-boot/login UX work and tests. No console action
  is required until a reviewed visual candidate and boot-argument delta are
  ready for one separately bounded validation

### EXP-20260822-012-A1 — scan with the PS4 station interface

- state: complete — superseded before operator command
- question: does NetworkManager return nearby access points when explicitly
  scanning the PS4 station interface `wlan0`, independent of the empty Omarchy
  network panel?
- changed variable: trigger one NetworkManager scan on `wlan0` and print its
  SSID, signal and security list; do not connect, save credentials, toggle the
  radio, restart a service or modify network configuration
- source hypothesis: the stable Omarchy 4.0.0 panel uses NetworkManager through
  `Quickshell.Networking`, but its `findDevice(DeviceType.Wifi)` fallback picks
  the first disconnected Wi-Fi device. Prior hardware evidence lists `ap0`,
  `ap1`, then the real station `wlan0`; selecting `ap0` would produce an empty
  network list even while the MT7668 radio successfully scans
- expected evidence: `nmcli ... wifi list ifname wlan0 --rescan yes` prints one
  or more nearby SSIDs, or returns one exact driver/NetworkManager error that
  identifies the lower failing layer
- timeout: 90 seconds after the command; stop on complete output, exact error,
  display loss, hang or reboot
- rollback: none for a transient scan. Do not enter a Wi-Fi password in A1
- operator action: none. Before running the proposed command, the operator
  requested the shorter direct Wi-Fi setup path
- bounded UART context:
  [`20260822_175326_136745-exp-20260822-012-a1-scan-with-the-ps4-station-interface-6e7cddb1.md`](../../ps4-uart/sessions/20260822_175326_136745-exp-20260822-012-a1-scan-with-the-ps4-station-interface-6e7cddb1.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: no `nmcli` command was executed, so A1 does not prove SSID output.
  UART nevertheless retained repeated successful MT7668 full-scan transitions
  from `IDLE` to `SCAN` and back without a firmware or device failure
- rollback: none; no persistent configuration or connection changed
- next action: use NetworkManager's standard `nmtui` once to select and connect
  `wlan0`, rather than make the operator transcribe diagnostic commands

### EXP-20260822-012-A2 — connect gift owner through NetworkManager TUI

- state: pass
- question: can NetworkManager's standard terminal UI list nearby networks and
  connect the PS4 station interface without relying on the mis-selected
  Quickshell Wi-Fi device?
- changed variable: create and activate one NetworkManager Wi-Fi connection for
  the operator-selected SSID through `nmtui`; do not restart networking, edit
  drivers, change DNS, expose the password in a command line or modify another
  interface
- expected evidence: `nmtui` lists nearby networks, accepts the password
  privately, reports the selected connection active, and UART shows association
  without a driver crash, disconnect loop or display fault
- timeout: 3 minutes after opening `nmtui`; stop on successful activation or the
  first exact error
- rollback: on failure, exit `nmtui` without repeating or deleting profiles;
  inspect the exact NetworkManager state in a later bounded action
- operator action: the operator opened `nmtui`, selected the intended Wi-Fi
  network, entered its password privately, and reported `connected`
- bounded UART context:
  [`20260822_183902_717794-exp-20260822-012-a2-connect-gift-owner-through-networkmanager-tu-670fe043.md`](../../ps4-uart/sessions/20260822_183902_717794-exp-20260822-012-a2-connect-gift-owner-through-networkmanager-tu-670fe043.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass. UART recorded the MT7668 station progressing through scan,
  authentication, association and key installation to `NORMAL_TR`; subsequent
  station statistics showed the selected BSSID active without a disconnect or
  driver crash. This proves the radio, firmware, driver and NetworkManager path
  work. It also supports the source diagnosis that the empty native network
  panel is selecting an AP-mode device instead of the station interface
- isolation note: after connection, the operator also opened Omarchy's SSHD
  setup before A2 was closed. It failed at UFW with `Couldn't determine
  iptables version`; the additional action does not invalidate the earlier
  Wi-Fi association evidence, but this slice is not evidence for a completed
  SSH setup
- SSH source conclusion: stable Omarchy starts `sshd.service` before calling
  `ufw limit 22/tcp`. The PS4 6.18 Baikal config has
  `# CONFIG_NETFILTER is not set`, so the generic UFW stage is incompatible
  with this kernel and aborts before SSH-key authorization. The product must
  either gain reviewed netfilter support or provide a PS4-aware SSH setup that
  does not claim a firewall rule was installed
- rollback: none; retain the working NetworkManager profile. Do not delete or
  recreate it while repairing the native panel
- next action: authorize the owner's existing GitHub ED25519 key and confirm
  the already-started SSH daemon through a separately bounded setup action;
  do not change the Wi-Fi profile or firewall in that action

### EXP-20260822-012-A3 — complete LAN SSH access without UFW

- state: pass — key installed; remote authentication pending A4
- question: did the failed Omarchy helper leave `sshd` running, and can the
  owner's existing GitHub ED25519 key complete key-only LAN access without
  invoking the unavailable PS4 netfilter/UFW path?
- changed variable: install the owner's already-verified GitHub public key as
  `~/.ssh/authorized_keys`; do not alter password authentication, Wi-Fi,
  firewall state, kernel modules or network services
- expected evidence: the key installs with mode `0600`; no UART fault or Wi-Fi
  disconnect occurs. Service/IP and remote authentication will be checked in
  later read-only bounded actions rather than folded into this mutation
- timeout: 60 seconds after the command; stop on a returned prompt or the
  first exact error
- rollback: remove only the newly created `~/.ssh/authorized_keys` if the
  operator does not want this Mac key retained; otherwise preserve it
- operator action: the operator installed the published `meerzulee` GitHub
  ED25519 key and reported that SSH-key setup completed
- bounded UART context:
  [`20260822_184443_001374-exp-20260822-012-a3-complete-lan-ssh-access-without-ufw-5636e133.md`](../../ps4-uart/sessions/20260822_184443_001374-exp-20260822-012-a3-complete-lan-ssh-access-without-ufw-5636e133.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass for the declared key-install action. UART retained the Wi-Fi
  station in `NORMAL_TR` with no disconnect, driver crash or console fault;
  exact file mode and remote public-key authentication remain to be verified
  read-only over SSH in A4
- rollback: none; the operator wants this Mac key retained
- next action: make one bounded read-only SSH connection to `ps4` at the
  recorded private LAN address using the matching local ED25519 key and inspect only
  identity, service, key mode and NetworkManager station state

### EXP-20260822-012-A4 — verify key-only SSH and Wi-Fi state

- state: degraded — SSH and Wi-Fi pass; key mode requires correction
- question: can the Mac authenticate to `ps4` at the recorded private LAN
  address with the newly
  authorized ED25519 key, and does the remote read-only state confirm SSH and
  the NetworkManager station connection are healthy?
- changed variable: none on the console; open one noninteractive, read-only SSH
  command using the matching local ED25519 key, with a temporary host-key
  database on the Mac
- expected evidence: remote identity is user `ps4`; `sshd.service` is active;
  `authorized_keys` is mode `0600`; `wlan0` is connected with the reported
  address; password authentication is not used
- timeout: 15 seconds; stop on complete output, authentication rejection,
  route failure, hang, Wi-Fi disconnect or UART fault
- rollback: none for the console. Delete only the temporary Mac host-key file
  after the check
- operator action: none; the owner explicitly supplied the address and
  requested the SSH connection
- bounded UART context:
  [`20260822_184638_588390-exp-20260822-012-a4-verify-key-only-ssh-and-wi-fi-state-0b228472.md`](../../ps4-uart/sessions/20260822_184638_588390-exp-20260822-012-a4-verify-key-only-ssh-and-wi-fi-state-0b228472.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`. The slice is empty because
  the successful read-only SSH query emitted no kernel/UART messages
- SSH result: pass. The Mac authenticated noninteractively as `ps4` using the
  matching local ED25519 key; remote host `ps4` reported
  `sshd.service=active`
- network result: pass. NetworkManager reported `wlan0` connected to the
  operator-selected network at the recorded private LAN address; `ap0` and
  `ap1` were disconnected.
  This is direct live confirmation of the top-bar source bug: the generic
  Omarchy panel can select the first Wi-Fi device (`ap0`) instead of the
  station device (`wlan0`)
- firewall result: fail as expected. `iptables -V` returned
  `Failed to initialize nft: Protocol not supported`, matching the kernel's
  disabled netfilter configuration and the earlier UFW failure
- image result: the running system identifies as Omarchy `4.0.0-3` and has 816
  installed packages. Exact full-profile equality remains a local manifest
  audit rather than a package-count claim
- security finding: `~/.ssh/authorized_keys` is owned by `ps4:ps4` but is mode
  `0644`, not the intended `0600`. OpenSSH accepted the key, but the mode should
  be tightened in the next bounded mutation
- rollback: none; the check was read-only and used no persistent Mac host-key
  database
- next action: correct the key mode in one bounded mutation, then keep all
  Wi-Fi-panel and kernel changes local until their source tests pass and a
  separately reviewed rebuild/update experiment is ready

### EXP-20260822-012-A5 — tighten owner authorized-key mode

- state: pass
- question: can the owner key file be corrected from `0644` to the intended
  private mode without disturbing the active SSH or Wi-Fi sessions?
- changed variable: set only `/home/ps4/.ssh/authorized_keys` to mode `0600`;
  do not alter its contents, owner, daemon configuration, firewall or network
- expected evidence: remote `stat` returns `600 ps4 ps4`; the command completes
  without an SSH disconnect, Wi-Fi transition or UART fault
- timeout: 15 seconds; stop on verified mode, error or connection loss
- rollback: restore `0644` only if OpenSSH unexpectedly rejects the standard
  `0600` mode; otherwise preserve the tighter mode
- operator action: none; the owner requested remote SSH access and correction
  of the discovered integration faults
- bounded UART context:
  [`20260822_190017_640858-exp-20260822-012-a5-tighten-owner-authorized-key-mode-7e6bebd3.md`](../../ps4-uart/sessions/20260822_190017_640858-exp-20260822-012-a5-tighten-owner-authorized-key-mode-7e6bebd3.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`. The slice is empty because
  the successful file-mode mutation emitted no kernel/UART messages
- result: pass. Remote `stat` returned
  `600 ps4 ps4 /home/ps4/.ssh/authorized_keys`; the same key-authenticated SSH
  connection completed normally
- rollback: none; preserve the standard `0600` mode
- next action: local-only package/profile audit and source/build validation for
  the station-device panel patch and netfilter kernel fragment. Do not update
  the running package or boot kernel until those artifacts pass

### EXP-20260822-012-A6 — compare running package set to pinned closure

- state: pass
- question: does the running gift image contain exactly the 816 name/version
  pairs locked by the offline Omarchy 4.0.0 snapshot, rather than merely the
  same package count?
- changed variable: none on the console; read `pacman -Q` once over the proven
  key-only SSH connection and compare it locally with the first two fields of
  `manifest/packages.lock`
- expected evidence: sorted name/version sets are identical with zero missing,
  extra or version-drifted packages
- timeout: 20 seconds; stop on zero diff, the first diff, authentication loss
  or UART fault
- rollback: none; the action is read-only and uses no persistent host-key file
- operator action: none; the owner explicitly asked whether this is full or
  trimmed Omarchy and supplied working SSH access
- bounded UART context:
  [`20260822_190123_303380-exp-20260822-012-a6-compare-running-package-set-to-pinned-closur-8d0a2d37.md`](../../ps4-uart/sessions/20260822_190123_303380-exp-20260822-012-a6-compare-running-package-set-to-pinned-closur-8d0a2d37.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`. The slice is empty because
  the successful read-only package query emitted no kernel/UART messages
- result: pass. The running system has 816 packages. A live name/version diff
  against the earlier `owner-uart-v2` closure found exactly three differences:
  the running PS4-owned packages are `omarchy-ps4 4.0.0-3`, settings
  `4.0.0-3`, and provisioning `4.0.0-7` instead of their older revisions.
  A local diff proves those are exactly the only three changes between
  `owner-uart-v2` and the actual `ps4-fixes-v1` snapshot; therefore the running
  name/version set equals all 816 entries in the correct `ps4-fixes-v1` lock
- scope conclusion: this is the complete pinned **PS4-safe Omarchy profile**,
  not a small desktop subset. It intentionally excludes the documented 17
  upstream PC/storage packages whose services or dependency closure can probe
  unsafe internal SATA, replace the accepted display manager/boot path, or are
  irrelevant hardware helpers. Those exclusions are adaptations, not missing
  snapshot packages
- rollback: none; the action was read-only
- next action: complete local build tests for the Wi-Fi station-selector patch
  and UFW/nftables config. Installing the panel update and booting a new kernel
  remain separate reviewed hardware experiments

### EXP-20260822-012-A7 — install station-aware Omarchy runtime

- state: fail — package unchanged; retry condition identified
- question: can the tested `omarchy-ps4 4.0.0-4` package replace only the
  running runtime package and preserve the active session, Wi-Fi and recovery
  configuration?
- changed variable: transfer and install only
  `omarchy-ps4-4.0.0-4-any.pkg.tar.zst`; do not install the rebuilt settings or
  provisioning packages, restart the shell, alter the kernel, firewall or
  network profile
- expected evidence: package SHA-256 verifies before transfer; Pacman upgrades
  `4.0.0-3 -> 4.0.0-4` without dependency/file errors; current Wi-Fi and HDMI
  session remain alive
- timeout: 5 minutes for the 115 MiB Wi-Fi transfer plus installation; stop on
  complete Pacman output, checksum mismatch, connection loss or UART fault
- rollback: reinstall the preserved `4.0.0-3` runtime package from the
  `ps4-fixes-v1` snapshot if the package transaction fails or the current
  session becomes unusable. Do not reboot
- operator action: the owner authorized use of the development account's test
  sudo credential; the agent ran the single Pacman transaction remotely
- bounded UART context:
  [`20260822_190657_297894-exp-20260822-012-a7-install-station-aware-omarchy-runtime-86b33525.md`](../../ps4-uart/sessions/20260822_190657_297894-exp-20260822-012-a7-install-station-aware-omarchy-runtime-86b33525.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- transfer result: pass. Local and remote SHA-256 both equal
  `57d219a74a3eeb6a8d5c23907da3b354309c055bbceca2cdda32bb3e2b965ef1`
- install result: fail before transaction. Pacman returned
  `package missing required signature`; the gift's required-signature policy
  correctly rejected the unsigned local development package. No package file
  was installed or replaced
- UART result: the MT7668 station remained in `NORMAL_TR` through transfer and
  rejection; no disconnect, display fault or kernel crash occurred
- timeout note: the bounded session exceeded the declared five-minute wall
  time while waiting for the operator credential decision, but the transfer
  and transaction themselves completed promptly and continuity stayed valid
- rollback: none required because Pacman rejected the package before mutation;
  retain the verified file in `/tmp` for exactly one scoped retry
- next action: retry once with the same verified local file and an ephemeral
  Pacman configuration read from stdin that changes only `SigLevel = Never`.
  Do not edit `/etc/pacman.conf` or generalize the exception to downloads

### EXP-20260822-012-A8 — install verified unsigned development runtime

- state: fail — package unchanged; coupled dependency identified
- question: can the exact SHA-verified `omarchy-ps4 4.0.0-4` development
  package install when signature enforcement is disabled only for that one
  local transaction?
- changed variable: upgrade only `omarchy-ps4 4.0.0-3 -> 4.0.0-4` while feeding
  Pacman an ephemeral copy of its config with `SigLevel = Never`; do not write
  the config, install another package, restart the shell, or alter network,
  firewall, kernel or boot state
- new evidence enabling retry: A7 proved the package bytes match the locally
  tested artifact and that signature policy—not contents, dependency solving or
  file conflict—blocked the transaction
- expected evidence: Pacman reports the one-package upgrade and exits zero;
  `/etc/pacman.conf` remains unchanged; `pacman -Q omarchy-ps4` returns
  `4.0.0-4`; Wi-Fi and HDMI stay active
- timeout: 90 seconds; stop on success, the first new Pacman error, connection
  loss or UART fault
- rollback: reinstall the preserved signed/locked `4.0.0-3` package if the
  runtime upgrade completes but damages the current session. Do not reboot
- operator action: none; the owner supplied the development sudo credential
  for this test console
- bounded UART context:
  [`20260822_191609_326547-exp-20260822-012-a8-install-verified-unsigned-development-runtim-58af0da2.md`](../../ps4-uart/sessions/20260822_191609_326547-exp-20260822-012-a8-install-verified-unsigned-development-runtim-58af0da2.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: fail before transaction. The ephemeral signature policy allowed
  Pacman to parse and solve the verified package, then dependency validation
  correctly rejected runtime `4.0.0-4` because installed provisioning
  `4.0.0-7` requires runtime `4.0.0-3`. Pacman confirmed the installed runtime
  remains `4.0.0-3`
- persistence result: pass. `/etc/pacman.conf` SHA-256 was identical before and
  after (`eb496db460f7983f83b1a14bd433737373b58522db066418ca2efdfc8790d158`),
  proving the signature exception was not persisted
- UART result: Wi-Fi returned to `NORMAL_TR`; no disconnect, display fault or
  kernel crash occurred
- rollback: none required because dependency solving rejected the transaction
  before mutation
- next action: transfer the already-built matching provisioning `4.0.0-8`
  package and install it atomically with runtime `4.0.0-4` under the same
  ephemeral, local-file-only development signature exception

### EXP-20260822-012-A9 — install matched runtime and provisioning pair

- state: pass
- question: can Pacman atomically upgrade the tested, dependency-matched
  runtime/provisioning pair when both exact local artifacts are present?
- changed variable: one coupled package state: `omarchy-ps4 4.0.0-3 -> 4.0.0-4`
  and its exact dependency `omarchy-ps4-provisioning 4.0.0-7 -> 4.0.0-8`;
  settings remains `4.0.0-3`. Use the ephemeral `SigLevel = Never` config only
  for these two SHA-verified local files
- new evidence enabling retry: A8 progressed past signature verification and
  isolated the only solver error to the exact provisioning equality pin; the
  matching provisioning package was built and passed package/owner tests in
  the same artifact set
- expected evidence: both upgrades complete atomically; permanent Pacman config
  hash stays unchanged; queried versions are `4.0.0-4` and `4.0.0-8`; current
  Wi-Fi and HDMI session stay active
- timeout: 90 seconds after the small provisioning transfer; stop on success,
  the first new Pacman error, connection loss or UART fault
- rollback: reinstall both preserved `4.0.0-3`/`4.0.0-7` packages from
  `ps4-fixes-v1` together if the transaction completes but damages the session
- operator action: none; the owner supplied the development sudo credential
  for this test console
- bounded UART context:
  [`20260822_191726_600420-exp-20260822-012-a9-install-matched-runtime-and-provisioning-pai-bc064ad9.md`](../../ps4-uart/sessions/20260822_191726_600420-exp-20260822-012-a9-install-matched-runtime-and-provisioning-pai-bc064ad9.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- transfer result: pass. Provisioning SHA-256 matched locally and remotely at
  `6cdd2054faa7fbffa05bfb574cab5f046b0c1949aff66824619167d093fb0c2c`;
  A7 already proved the runtime SHA-256
- install result: pass. Pacman upgraded the exact two-package set and reported
  `omarchy-ps4 4.0.0-4`, provisioning `4.0.0-8`, settings unchanged at
  `4.0.0-3`. Its only warning was the pre-existing safer filesystem mode
  `0750` on `/etc/sudoers.d` versus package directory mode `0755`; no file
  conflict or hook failure occurred
- persistence result: pass. `/etc/pacman.conf` retained exact SHA-256
  `eb496db460f7983f83b1a14bd433737373b58522db066418ca2efdfc8790d158`
  before and after the scoped unsigned development transaction
- UART result: Wi-Fi returned to `NORMAL_TR`; no disconnect, HDMI fault or
  kernel crash occurred
- rollback: not required; preserve the matched runtime/provisioning pair. The
  prior pair remains available in the `ps4-fixes-v1` snapshot
- next action: restart only the Omarchy shell in a separate bounded action so
  the live top bar loads the station-aware QML; do not restart Hyprland,
  NetworkManager or the console

### EXP-20260822-012-A10 — reload station-aware Omarchy shell

- state: pass with driver-noise follow-up
- question: can `omarchy-restart-shell` reload the newly installed top-bar
  code while preserving Hyprland, the connected `wlan0` station and HDMI?
- changed variable: restart only the user Omarchy/Quickshell process through
  the upstream SSH-aware helper; do not restart the compositor, networking,
  display manager, kernel or console
- expected evidence: helper exits zero after shell IPC responds; current
  graphical session remains visible; Wi-Fi stays connected; the top-bar
  network panel lists station networks instead of binding to `ap0`
- timeout: 30 seconds; stop on helper success/error, blank display, connection
  loss or UART fault
- rollback: invoke the preserved runtime `4.0.0-3` package pair only if the new
  shell cannot start. Do not reboot
- operator action: after automated reload, inspect the network panel and report
  whether the connected network and nearby networks are visible
- bounded UART context:
  [`20260822_191917_044158-exp-20260822-012-a10-reload-station-aware-omarchy-shell-366becb2.md`](../../ps4-uart/sessions/20260822_191917_044158-exp-20260822-012-a10-reload-station-aware-omarchy-shell-366becb2.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: pass for the UI acceptance question. The helper returned the shell to
  ready state and the operator confirmed that the top-bar network panel showed
  the connected station and nearby networks instead of binding to `ap0`
- UART result: the panel scan briefly moved the MediaTek station through
  disconnect, scan, join and back to `NORMAL_TR`. It emitted repeated
  `mtk_p2p_cfg80211_mgmt_frame_register` errors and one mailbox warning, then
  recovered with `TxFailCount 0`; there was no logger discontinuity, kernel
  crash or persistent network loss
- rollback: not required; retain the station-aware runtime/provisioning pair
- next action: treat the transient scan disruption and noisy P2P registration
  as a separate Wi-Fi-driver follow-up. Do not combine it with another live
  package, display or network change

### EXP-20260822-013-A1 — Chromium software-rendering artifact isolation

- state: fail — test instance did not reach Wayland
- question: does disabling Chromium's GPU process eliminate the repeated
  rectangular corruption captured inside the browser surface?
- changed variable: gracefully close the current Chromium process and relaunch
  the same installed Chromium/profile through UWSM with only
  `--disable-gpu`; do not change Mesa, Hyprland, kernel, display mode, package
  files or persistent Chromium flags
- expected evidence: the new Chromium command line contains `--disable-gpu`;
  the same browser toolbar/page renders without rectangular tiles; a new
  screenshot does not contain the corruption; HDMI, compositor and Wi-Fi
  remain active; UART shows no new GPU reset, ring timeout or display fault
- timeout: 90 seconds from the relaunch; stop on clean/corrupt operator report,
  launch error, Chromium failing to exit, blank display, network loss or UART
  discontinuity
- rollback: close the test Chromium instance and relaunch normally without
  `--disable-gpu`; no persistent file is changed in this experiment
- operator action: watch the automated close/relaunch, then inspect the same
  GitHub toolbar area and report whether the rectangular blocks remain. If the
  prior tab is not restored, open the same page without changing browser
  settings
- bounded UART context:
  [`20260822_212512_036320-exp-20260822-013-a1-chromium-software-rendering-artifact-isolati-9f5cb561.md`](../../ps4-uart/sessions/20260822_212512_036320-exp-20260822-013-a1-chromium-software-rendering-artifact-isolati-9f5cb561.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: fail before the rendering test. The existing Chromium process exited
  cleanly, but the UWSM client launched from SSH lacked the active
  `WAYLAND_DISPLAY`/runtime environment. Chromium reported `Failed to connect
  to Wayland display` and exited, so `--disable-gpu` was not evaluated
- UART result: no GPU reset, ring timeout, display fault or logger
  discontinuity occurred; the only bounded output was routine Wi-Fi roaming
  discovery returning to `NORMAL_TR`
- rollback: no persistent state changed. Chromium remains closed pending the
  scoped relaunch retry
- next action: retry once in a separate bounded action while passing the
  already-active UWSM/Wayland session environment to the launcher. Do not
  change Chromium flags beyond the original `--disable-gpu`

### EXP-20260822-013-A2 — Chromium software-rendering retry in session environment

- state: pass
- question: with the existing graphical-session environment supplied to UWSM,
  does `--disable-gpu` eliminate the browser-surface artifacts?
- changed variable: relaunch the same Chromium/profile through UWSM with the
  active user's existing `XDG_RUNTIME_DIR`, `WAYLAND_DISPLAY`, `DISPLAY`,
  `XDG_SESSION_TYPE`, `AMD_DEBUG` and `OMARCHY_PATH`, plus only
  `--disable-gpu`; do not modify persistent files or another graphics setting
- new evidence enabling retry: A1 isolated the failure to a missing Wayland
  socket environment before Chromium initialized; it did not exercise the GPU
  flag and left no persistent mutation
- expected evidence: Chromium remains running with `--disable-gpu`; the same
  toolbar/page has no rectangular corruption; a new screenshot is clean;
  HDMI, compositor and Wi-Fi remain active; UART has no GPU/display fault
- timeout: 90 seconds from relaunch; stop on clean/corrupt operator report,
  launch failure, blank display, network loss or UART discontinuity
- rollback: close the test instance and use the same graphical-session launch
  environment without `--disable-gpu`
- operator action: inspect the relaunched Chromium at the same GitHub toolbar
  and report whether the rectangular blocks are gone
- bounded UART context:
  [`20260822_212647_906639-exp-20260822-013-a2-chromium-software-rendering-retry-in-session-60461c7b.md`](../../ps4-uart/sessions/20260822_212647_906639-exp-20260822-013-a2-chromium-software-rendering-retry-in-session-60461c7b.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- launch result: pass. The Chromium main process remained active with
  `--disable-gpu`; its GPU helper reported `--use-gl=disabled`, and renderer
  processes reported `--disable-gpu-compositing`. The expected VA-API
  initialization failure was non-fatal because hardware video acceleration is
  not accepted on this image
- operator result: pass. The owner inspected the same GitHub toolbar area and
  confirmed that the rectangular artifacts were gone
- UART result: completed with no logger event, GPU reset, ring timeout, HDMI
  fault or kernel crash. The bounded output contained only routine MediaTek
  roaming activity returning to `NORMAL_TR`
- rollback: not required; leave the test Chromium instance running with
  software rendering
- next action: package `--disable-gpu` as the default PS4 Chromium
  compatibility policy and document the narrower acceleration experiments
  required before removing it

### EXP-20260822-014-A1 — return from Linux to Orbis for clean-splash test

- state: inconclusive — restart action not observed
- question: can the current accepted USB root shut down cleanly and return the
  console to Orbis before staging the clean product boot arguments?
- changed variable: request one normal system restart from the current Omarchy
  session; do not change packages, boot files, USB connection, display mode or
  power manually
- expected evidence: systemd unmounts the external root cleanly; UART remains
  continuous through shutdown; the PS4 returns to the Orbis home screen; the
  operator reports visible HDMI and controller response
- timeout: 150 seconds; stop on Orbis home, shutdown hang, filesystem error,
  black HDMI after the normal restart interval or UART discontinuity
- rollback: if HDMI alone is missing but UART shows Orbis, reseat HDMI once. If
  shutdown is genuinely stuck after the timeout, stop and review UART before
  considering a physical power action
- operator action: use Omarchy's normal Restart action once, then report when
  the Orbis home screen is visible. Do not launch GoldHEN or the Omarchy FPKG
  yet
- bounded UART context:
  [`20260822_214152_878914-exp-20260822-014-a1-return-from-linux-to-orbis-for-clean-splash--f9562c5d.md`](../../ps4-uart/sessions/20260822_214152_878914-exp-20260822-014-a1-return-from-linux-to-orbis-for-clean-splash--f9562c5d.md),
  exact sibling `.raw`; evidence state `completed`, generation
  `80973222038e43548cda68da099cb054`, epoch `1`
- result: inconclusive because the declared restart did not occur before the
  timeout and no operator outcome arrived. UART continued to show the live
  Linux MediaTek station returning to `NORMAL_TR`; there was no systemd
  shutdown, unmount or Orbis transition
- rollback: none required because no hardware state changed
- next action: only after the operator confirms readiness, open a new bounded
  retry for the same normal Restart action; do not stage boot files in this
  state

### EXP-20260822-015-A1 — attach deferred-owner USB at Orbis

- state: aborted — operator action occurred, but the marker was closed as
  unused before that was recognized; preserve evidence but do not count it as
  acceptance
- question: does the prepared whole-device ext4 Omarchy USB attach while the
  console remains stable and responsive in Orbis?
- changed variable: move only the verified Kingston DataTraveler from the Mac
  to one PS4 USB port; do not launch the Omarchy FPKG or another payload
- expected evidence: continuous UART remains valid with no panic, reboot or
  fatal USB error; Orbis remains visible and controller-responsive. An Orbis
  unsupported-filesystem notice is acceptable because the product root is
  intentionally ext4
- timeout: 60 seconds from attachment; stop on stable Orbis/operator report,
  panic, reboot, black display or UART discontinuity
- rollback: leave the USB connected after a stable attach. If attachment alone
  destabilizes Orbis, close this session before unplugging it in a separately
  declared bounded recovery action
- operator action: unplug the prepared Kingston USB from the Mac, plug it into
  the PS4, and report the exact visible result; do not launch Omarchy yet
- bounded UART context:
  [`20260822_223307_791457-exp-20260822-015-a1-attach-deferred-owner-usb-at-orbis-d6d611ed.md`](../../ps4-uart/sessions/20260822_223307_791457-exp-20260822-015-a1-attach-deferred-owner-usb-at-orbis-d6d611ed.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `aborted`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- observed evidence: the exact Kingston serial attached as a 118240 MB
  SuperSpeed mass-storage device. Orbis correctly classified the intentional
  whole-device ext4 filesystem as an unknown/unsupported format and remained
  active in the retained slice, with no panic or reboot
- conclusion: informative only. Because finalization state is `aborted` and
  there is no operator display/controller outcome, this cannot promote the USB
  attach path
- rollback: none recorded. Before another console action, confirm current USB
  and Orbis state and open a fresh bounded session
- next action: finish and rebuild the locally requested two-action FPKG flow;
  hardware testing resumes only afterward in a new bounded experiment

### EXP-20260822-016-A1 — stage simplified v0.28 FPKG over GoldHEN FTP

- state: complete — pass
- question: can anonymous GoldHEN FTP stage the exact locally validated v0.28
  package without installing or launching the title, changing internal boot
  files, contacting PayLoader or altering the external USB?
- changed variable: upload the 20,905,984-byte v0.28 FPKG once under the unique
  partial name
  `/data/pkg/omarchy-v0.28-OMCH42069-beta.pkg.partial-d2061df4`, stream it back
  for exact verification, then rename it to
  `/data/pkg/omarchy-v0.28-OMCH42069-beta.pkg`
- expected evidence: remote read-back size 20,905,984 bytes and SHA-256
  `d2061df4b96e978a075c2cd088f904320c165500b96764e31276b4c6d17ea574`,
  final FTP size 20,905,984 bytes, and completed UART continuity
- timeout: 5 minutes; stop after verified rename or the first FTP, hash,
  storage or UART failure
- rollback: on verification failure remove only the unique v0.28 partial; if
  a mismatched v0.28 final already exists, preserve it and stop. Preserve the
  installed title, all earlier packages, both internal boot sets, external USB
  and PayLoader state
- operator action: none; leave the console in its current Orbis/GoldHEN state
- result: pass. The local artifact passed the declared size/hash gate, FTP
  uploaded the unique partial once, and a complete remote read-back matched
  exactly at 20,905,984 bytes with SHA-256
  `d2061df4b96e978a075c2cd088f904320c165500b96764e31276b4c6d17ea574`.
  FTP then renamed it to `/data/pkg/omarchy-v0.28-OMCH42069-beta.pkg` and
  reported the same final size. No install, app launch, boot-file update or
  PayLoader contact occurred
- bounded UART context:
  [`20260822_225535_187482-exp-20260822-016-a1-stage-simplified-v0-28-fpkg-over-goldhen-ftp-360d4df8.md`](../../ps4-uart/sessions/20260822_225535_187482-exp-20260822-016-a1-stage-simplified-v0-28-fpkg-over-goldhen-ftp-360d4df8.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: completed continuity with routine background mini-app and
  ShellCore heap telemetry only; no storage, package, logger or fatal fault
- rollback: none required; the exact v0.28 package is staged and the currently
  installed title remains untouched
- next action: install only the staged v0.28 update in a separate bounded
  session; do not launch it or update boot files during the installation action

### EXP-20260822-018-A1 — inspect live owner and LightDM state before autologin

- state: complete — inconclusive; SSH unavailable
- question: can the previously accepted key-only SSH path identify the active
  USB root, owner/provisioning state, installed provisioning package and
  LightDM autologin configuration without changing the running system?
- changed variable: none; make one batch-mode SSH connection to the recorded
  Linux account at the recorded private LAN address and read only identity,
  mount, package,
  marker, service and LightDM configuration state
- expected evidence: one coherent state report within 60 seconds while UART
  remains continuous; no file, package, service, network or display mutation
- timeout: 60 seconds; stop at the first connection or authentication failure
- rollback: none because the inspection is read-only
- operator action: none
- result: inconclusive. TCP port 22 at the recorded private LAN address refused
  the single SSH
  connection, so no remote command ran and no live state was read. The existing
  Mac neighbor table still maps that address to the recorded Linux Wi-Fi MAC
  `00:0c:43:26:60:48`; repeated connection was not attempted
- bounded UART context:
  [`20260822_232835_667580-exp-20260822-018-a1-inspect-live-owner-and-lightdm-state-before--83ffbd3a.md`](../../ps4-uart/sessions/20260822_232835_667580-exp-20260822-018-a1-inspect-live-owner-and-lightdm-state-before--83ffbd3a.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: the valid bounded slice is empty; it contains no logger
  discontinuity or hardware fault but cannot establish live service state
- rollback: none required; no connection or mutation occurred
- next action: return Linux to Orbis cleanly in a separate bounded action,
  then move the unmounted USB to the Mac for an offline v4.0.0-13 update

### EXP-20260822-018-A2 — cleanly return Linux USB to Orbis for offline owner update

- state: complete — degraded pass; the later USB move exceeded the declared
  restart-only operator action but occurred after Orbis owned the device
- question: can one `Ctrl+Alt+Delete` request leave the running external root
  and return the console to Orbis before the USB is removed for an offline
  owner/autologin update?
- changed variable: request one normal restart from Linux; do not repeat the
  key sequence or remove the USB before Orbis is visible
- expected evidence: Linux reaches firmware S5/restart and Orbis without a
  panic; timeout 3 minutes. If the request has no effect, leave the running
  system and USB untouched for review
- operator action: pressed the requested restart, later removed the Kingston
  from Orbis and attached it to the Mac without separately reporting the
  intermediate `Orbis visible` state
- bounded UART context:
  [`20260822_233021_273682-exp-20260822-018-a2-cleanly-return-linux-usb-to-orbis-for-offlin-6f1062c7.md`](../../ps4-uart/sessions/20260822_233021_273682-exp-20260822-018-a2-cleanly-return-linux-usb-to-orbis-for-offlin-6f1062c7.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- result: Linux reached ACPI S5 and emitted `reboot: Restarting system` and
  `reboot: machine restart`. A complete Orbis boot followed, and Orbis
  enumerated the exact Kingston serial as a 118240 MB USB mass-storage disk.
  The later disconnect reported zero outstanding I/O and explicitly said no
  filesystem was mounted on `/dev/da1`. No Linux panic, Orbis storage fault or
  logger discontinuity occurred
- degradation: the retained UART slice does not contain an explicit Linux ext4
  unmount/remount-read-only line, and USB removal was not a separately declared
  action. Therefore run an offline no-write `e2fsck` before any USB write
- rollback: none required. macOS now resolves the exact unmounted, writable
  Kingston as `/dev/disk10`, 123,983,626,240 bytes; OrbStack USB ID is
  `03240000`, vendor/product `0951:1666`, serial
  `E0D55EA573F0194049CD0236`, and it is not attached to a VM
- next action: in one separately bounded offline mutation, attach only USB ID
  `03240000` to OrbStack, require a clean ext4 check, back up the existing
  provisioning package state, install v4.0.0-13, verify the pending owner flow
  and persistent autologin contract, run a final clean check, then detach it

### EXP-20260822-018-A3 — preflight offline owner/autologin package installation

- state: complete — fail safe before write
- question: is the exact Kingston Omarchy USB clean enough to accept the
  offline provisioning package update without risking an already inconsistent
  filesystem?
- changed variable: attach only OrbStack USB ID `03240000` to the existing
  Arch rehearsal VM and run one no-write ext4 check; do not mount or install if
  the check is nonzero
- expected evidence: exact vendor/product, serial, byte size, whole-device ext4
  label `OMARCHY-PS4`, unmounted state and `e2fsck -f -n` status 0 before any
  write
- timeout: 3 minutes; stop at the first identity, attachment, filesystem or
  UART-continuity failure
- rollback: no write was permitted before a clean check; detach the exact USB
  from OrbStack on failure
- operator action: none; the USB was already physically connected to the Mac
- result: fail safe before write. Exact identity resolved uniquely as
  `/dev/sda` in the VM (Kingston DataTraveler 3.0, serial
  `E0D55EA573F0194049CD0236`, 123,983,626,240 bytes, USB, whole-device ext4,
  label `OMARCHY-PS4`, unmounted), but `e2fsck -f -n` returned status 4. It
  reported deleted inode `273568` with zero deletion time, block-bitmap
  difference `-(33952--33981)`, free-block count mismatch, inode-bitmap
  difference `-273568`, and free-inode count mismatch. The stop condition
  prevented mounting and package installation
- bounded UART context:
  [`20260822_234923_428338-exp-20260822-018-a3-install-offline-centered-owner-persistent-au-d55db0f6.md`](../../ps4-uart/sessions/20260822_234923_428338-exp-20260822-018-a3-install-offline-centered-owner-persistent-au-d55db0f6.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background mini-app/ShellCore telemetry only;
  no storage, logger or fatal fault, with completed continuity
- rollback: the exact USB was detached from OrbStack; `orb usb info 03240000`
  confirms `Machine: Not attached`. No filesystem or package write occurred
- next action: repair only the reported ext4 metadata with `e2fsck -f -y` in a
  separate bounded session, require a subsequent no-write status 0, then detach

### EXP-20260822-018-A4 — repair Kingston ext4 metadata before owner update

- state: complete — pass
- question: can the exact Kingston Omarchy USB metadata be repaired and then
  pass a no-write full ext4 check before any package is installed?
- changed variable: run repair-mode `e2fsck -f -y` once against only the exact
  unmounted Kingston whole-device filesystem
- expected evidence: exact stable USB serial symlink, byte size, ext4 type and
  `OMARCHY-PS4` label gates pass; repair exits 0 or 1; immediate
  `e2fsck -f -n` exits 0; device is detached afterward
- timeout: 3 minutes; stop at the first identity, mount, repair, verification,
  detachment or UART-continuity failure
- rollback: do not mount or install packages; the source image and recovery
  artifacts remain the recovery path if metadata repair cannot produce a clean
  no-write check
- operator action: none; the USB remained physically attached to the Mac
- result: pass. The first command made no mutation because a whitespace-based
  identity parser rejected the model `DataTraveler 3.0`; read-only evidence
  identified that parser defect. The replacement gate resolved stable symlink
  `/dev/disk/by-id/usb-Kingston_DataTraveler_3.0_E0D55EA573F0194049CD0236-0:0`
  to `/dev/sda` and proved exact serial, 123,983,626,240-byte size, ext4 type,
  label `OMARCHY-PS4`, and unmounted state. `e2fsck -f -y` recovered the
  journal and corrected free block/inode counts, exiting 1 as expected for a
  modified filesystem. The immediate no-write full check exited 0
- bounded UART context:
  [`20260822_235210_840534-exp-20260822-018-a4-repair-exact-kingston-ext4-metadata-before-o-b23a1d91.md`](../../ps4-uart/sessions/20260822_235210_840534-exp-20260822-018-a4-repair-exact-kingston-ext4-metadata-before-o-b23a1d91.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background telemetry only; no storage,
  logger or fatal fault, with completed continuity
- rollback: no package or owner state changed; the exact USB was synced and
  detached, and `orb usb info 03240000` confirms `Machine: Not attached`
- next action: install only the exact verified provisioning v4.0.0-13 package
  offline in a separate bounded session, preserve the pending-owner state,
  verify its files and package database, require a final clean check, and detach

### EXP-20260822-018-A5 — install centered owner UI and autologin package offline

- state: complete — degraded pass; package accepted, final filesystem gate
  requires repair before boot
- question: can exact package
  `omarchy-ps4-provisioning-4.0.0-13-any.pkg.tar.zst` be installed offline on
  the clean Kingston root while preserving its existing account and owner state?
- changed variable: upgrade only `omarchy-ps4-provisioning` from 4.0.0-11 to
  4.0.0-13 using the exact local package with SHA-256
  `7878c0774fc164eda9d94e15400fe5f478f88bc721b8f954bb9288c5c47aacc7`
- expected evidence: rollback archive hashes verify; package database reports
  4.0.0-13; human account and pending/completed markers are unchanged; owner UI
  contains no GitHub-key question, writes persistent-autologin configuration,
  sends stderr to journal; final no-write ext4 check exits 0; USB is detached
- timeout: 6 minutes; stop at first identity, backup, package, content,
  filesystem, detachment or UART-continuity failure
- rollback: preserve package-owned files, old pacman local database and
  LightDM/provisioning runtime state under
  `/var/lib/omarchy-ps4/backups/EXP-20260822-018-A5-before-owner-ui`; do not
  change accounts or provisioning markers
- operator action: none; the USB remained physically attached to the Mac
- result: degraded pass. Two pre-install compatibility gates failed safely:
  offline pacman returned mount-prefixed query paths, then pacman 7.1 rejected
  obsolete option `--nohooks`; neither attempt installed the package. The
  corrected flow created and hash-verified relative rollback archives and used
  an explicit empty `--hookdir` plus `--noscriptlet`. Pacman upgraded exactly
  4.0.0-11 to 4.0.0-13. Verification proved account
  `meerzulee:1000:/home/meerzulee:/bin/bash` unchanged, both owner markers still
  absent, GitHub-key UI absent, persistent-autologin output present, and
  `StandardError=journal` present. Pacman emitted only the pre-existing
  `/etc/sudoers.d` mode mismatch warning and skipped chroot service actions
- degradation: the final `e2fsck -f -n` returned status 4 after the offline
  upgrade and reported ten inodes in a corrupted orphan list. No boot is
  permitted until a repair-only session returns a clean status 0
- bounded UART context:
  [`20260822_235445_070632-exp-20260822-018-a5-install-verified-centered-owner-ui-and-persi-d930affe.md`](../../ps4-uart/sessions/20260822_235445_070632-exp-20260822-018-a5-install-verified-centered-owner-ui-and-persi-d930affe.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background/network-event telemetry only; no
  storage, logger or fatal fault, with completed continuity
- rollback: package rollback archive is intact on USB; the exact device was
  detached from OrbStack. No account, owner marker or PS4-internal state changed
- next action: repair only the post-upgrade orphan-list metadata and require an
  immediate no-write full check status 0 in a separate bounded session

### EXP-20260822-018-A6 — repair post-upgrade ext4 orphan metadata

- state: complete — pass
- question: can the post-upgrade orphan-list metadata be repaired so the exact
  Kingston root passes a full no-write check before any boot or further change?
- changed variable: run repair-mode `e2fsck -f -y` once against only the exact
  unmounted Kingston whole-device filesystem
- expected evidence: stable USB serial, byte size, ext4 type and label gates
  pass; the ten orphan-list entries are repaired; immediate `e2fsck -f -n`
  exits 0; USB is detached
- timeout: 3 minutes; stop at the first identity, repair, verification,
  detachment or UART-continuity failure
- rollback: do not mount or change package/account state; retain the verified
  A5 rollback archive and re-image only if repair cannot produce a clean check
- operator action: none; USB remained physically connected to the Mac
- result: pass. The first exact-gate command exited before repair because it
  raced USB enumeration and the stable symlink had not appeared; a read-only
  check then proved the expected symlink and `/dev/sda`. The single repair fixed
  all ten declared orphan-list inodes and exited 1 for a modified filesystem.
  The immediate full no-write check exited 0
- bounded UART context:
  [`20260822_235932_454137-exp-20260822-018-a6-repair-post-upgrade-ext4-orphan-metadata-00ae1a55.md`](../../ps4-uart/sessions/20260822_235932_454137-exp-20260822-018-a6-repair-post-upgrade-ext4-orphan-metadata-00ae1a55.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background telemetry only; no storage,
  logger or fatal fault, with completed continuity
- rollback: package v4.0.0-13 remains installed; exact USB was detached and is
  clean. No account, autologin runtime configuration or PS4-internal state changed
- next action: configure persistent LightDM autologin for the existing owner
  `meerzulee` in a separate bounded session, verify the `omarchy` desktop
  session exists, clean any metadata produced by that offline write, and detach

### EXP-20260823-018-A7 — enable persistent Omarchy autologin for existing owner

- state: complete — fail safe before write; missing PAM group exposed
- question: can persistent LightDM autologin be enabled for existing owner
  `meerzulee` using a real installed `omarchy` session and the package v4.0.0-13
  contract?
- changed variable: create only the persistent owner-autologin configuration
  after proving the owner, session and PAM prerequisites; do not write if any
  prerequisite is absent
- expected evidence: account `meerzulee` uid 1000 exists, session `omarchy`
  resolves through LightDM's declared session directories, PAM permits
  passwordless autologin for the account, exact configuration is written and
  verified, final filesystem check is clean, USB is detached
- timeout: 4 minutes; stop at the first identity, session, PAM, configuration,
  filesystem, detachment or UART-continuity failure
- rollback: no write before all gates; A5 contains a verified copy of the
  previous LightDM runtime state
- operator action: none; USB remained physically connected to the Mac
- result: fail safe before write. Read-only inspection proved the owner and the
  real session descriptor at `/usr/local/share/wayland-sessions/omarchy.desktop`
  (LightDM already includes that directory). It also proved the existing
  one-time config selects `meerzulee` and `omarchy`. However,
  `/etc/pam.d/lightdm-autologin` explicitly requires membership in group
  `autologin`, while the group does not exist and the owner belongs only to
  `audio,input,video,wheel`. Therefore the v4.0.0-13 implementation could not
  authenticate automatic login, and no configuration or account write ran
- bounded UART context:
  [`20260823_000123_779588-exp-20260823-018-a7-enable-persistent-omarchy-autologin-for-exis-d2d35b5c.md`](../../ps4-uart/sessions/20260823_000123_779588-exp-20260823-018-a7-enable-persistent-omarchy-autologin-for-exis-d2d35b5c.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background/network telemetry only; no storage,
  logger or fatal fault, with completed continuity
- rollback: no write occurred; exact USB was detached clean. Source was then
  corrected so first-owner setup creates system group `autologin` and includes
  the owner in it before LightDM configuration. Provisioning v4.0.0-14 built
  under OrbStack and package-content/prepare-for-owner tests passed; exact
  package SHA-256 is
  `8f423fb5ffeabfc8278c725f49318348ceb600ac979b530d35d020f8b4ecf71d`
- next action: install only verified provisioning v4.0.0-14 offline in a
  separate bounded session and require final repaired/clean ext4 evidence

### EXP-20260823-018-A8 — install provisioning v4.0.0-14 autologin-group fix

- state: complete — pass
- question: can exact provisioning v4.0.0-14 replace v4.0.0-13 offline while
  retaining a verified rollback and leaving the external root clean?
- changed variable: upgrade only `omarchy-ps4-provisioning` from 4.0.0-13 to
  4.0.0-14 using SHA-256
  `8f423fb5ffeabfc8278c725f49318348ceb600ac979b530d35d020f8b4ecf71d`
- expected evidence: rollback archives verify; target database reports
  4.0.0-14; installed owner program creates group `autologin`, includes the
  owner in that group and retains persistent config/no-GitHub contract; repair
  and no-write checks exit 0 or expected 1 then 0; USB detaches
- timeout: 5 minutes; stop at the first identity, backup, package, content,
  filesystem, detachment or UART-continuity failure
- rollback: preserve v4.0.0-13 package files/database under
  `/var/lib/omarchy-ps4/backups/EXP-20260823-018-A8-before-autologin-group-fix`;
  do not change accounts or LightDM runtime state in this action
- operator action: none; USB remained physically connected to the Mac
- result: pass. Hash-verified rollback archives were created, pacman upgraded
  exactly 4.0.0-13 to 4.0.0-14, and installed-content checks proved
  `groupadd --system autologin`, `groups=(wheel autologin)`, persistent owner
  autologin configuration, and no GitHub-key prompt. The existing sudoers
  directory mode warning remained non-mutating; chroot service hooks were
  skipped. Post-write repair and immediate no-write full check both exited 0
- bounded UART context:
  [`20260823_000613_185269-exp-20260823-018-a8-install-verified-autologin-group-provisionin-53cb7bbc.md`](../../ps4-uart/sessions/20260823_000613_185269-exp-20260823-018-a8-install-verified-autologin-group-provisionin-53cb7bbc.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background/HID/workaround telemetry only; no
  storage, logger or fatal fault, with completed continuity
- rollback: no rollback needed; USB was clean and exact device detached
- next action: create the missing system `autologin` group, add existing owner
  `meerzulee`, and write the package-defined persistent LightDM configuration
  in a separate bounded migration, then require clean filesystem evidence

### EXP-20260823-018-A9 — migrate existing owner to persistent Omarchy autologin

- state: complete — pass
- question: can existing owner `meerzulee` be migrated to the corrected
  persistent LightDM autologin contract without changing credentials or other
  group membership?
- changed variable: create system group `autologin`, append only that group to
  owner `meerzulee`, and create the package-defined persistent LightDM config
  selecting session `omarchy`
- expected evidence: exact device/package/account/session/PAM gates pass;
  previous login state is hash-backed; final group set is exactly
  `audio,autologin,input,video,wheel`; config contains the four exact declared
  lines; post-write repair and no-write checks pass; USB detaches
- timeout: 4 minutes; stop at the first identity, backup, account, session,
  PAM, configuration, filesystem, detachment or UART-continuity failure
- rollback: preserve `/etc/group`, `/etc/gshadow` and the full LightDM config
  directory under
  `/var/lib/omarchy-ps4/backups/EXP-20260823-018-A9-before-persistent-autologin`;
  do not remove the existing one-time config in this action
- operator action: none; USB remained physically connected to the Mac
- result: pass. The exact v4.0.0-14 root, owner, local Omarchy session and PAM
  group requirement passed. A system `autologin` group was created and owner
  `meerzulee` was appended without changing its other groups. Exact persistent
  config `/etc/lightdm/lightdm.conf.d/25-omarchy-ps4-owner-autologin.conf`
  selects `meerzulee`, zero timeout and `omarchy`. The rollback tar hash
  verified; repair-mode and immediate no-write full ext4 checks both exited 0
- bounded UART context:
  [`20260823_000800_092062-exp-20260823-018-a9-migrate-existing-owner-to-persistent-omarchy-b9fa3cfe.md`](../../ps4-uart/sessions/20260823_000800_092062-exp-20260823-018-a9-migrate-existing-owner-to-persistent-omarchy-b9fa3cfe.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: routine Orbis background telemetry only; no storage,
  logger or fatal fault, with completed continuity
- rollback: none required; exact USB is clean, detached from OrbStack, and safe
  to move. Password and owner identity remain unchanged
- next action: reconnect the exact Kingston USB to Orbis in a separate bounded
  session and prove enumeration before any Linux launch

### EXP-20260823-018-A10 — reconnect prepared Kingston USB to Orbis

- state: complete — pass
- question: does Orbis enumerate the exact prepared Kingston USB cleanly before
  any Linux launch?
- changed variable: physically move the safely detached Kingston from the Mac
  to one PS4 USB port; do not launch the FPKG or Linux
- expected evidence: Orbis identifies vendor/product `0951:1666`, serial
  `E0D55EA573F0194049CD0236`, expected 118240 MB capacity and SuperSpeed mass
  storage without disconnect, transport or fatal fault
- timeout: 2 minutes; if it fails to enumerate, leave it connected and stop for
  review; do not reseat or launch Linux
- rollback: unplug only after review if enumeration produces a transport fault;
  no filesystem is expected to mount because Orbis does not support ext4
- operator action: connected the Kingston to the PS4 and reported GoldHEN active
- result: pass. Orbis enumerated the exact Kingston as SuperSpeed SCSI mass
  storage `/dev/da1`, 118240 MB, 242155520 sectors at 400 MB/s. The REPORT LUNS
  illegal-request response is the device's normal single-LUN fallback. Orbis
  reported unknown filesystem and did not mount or claim it as encrypted,
  which is expected for the whole-device ext4 Linux root
- bounded UART context:
  [`20260823_000948_071455-exp-20260823-018-a10-reconnect-prepared-kingston-usb-to-orbis-an-582787e4.md`](../../ps4-uart/sessions/20260823_000948_071455-exp-20260823-018-a10-reconnect-prepared-kingston-usb-to-orbis-an-582787e4.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: exact USB enumeration is complete and stable; no disconnect,
  I/O, logger or fatal fault occurred
- rollback: none required; USB remains connected and Linux was not launched
- next action: launch Omarchy once in a separately bounded session and observe
  kernel/root/session/autologin evidence without changing boot files

### EXP-20260823-018-A11 — launch prepared USB and verify desktop autologin

- state: complete — degraded pass; boot/splash passed, persistent autologin
  acceptance failed
- question: does one unchanged v0.28 FPKG launch reach the prepared USB root,
  retain the quiet branded splash and automatically enter the Omarchy desktop?
- changed variable: launch Omarchy once through the already-installed v0.28
  FPKG; do not update boot files, reseat USB or retry the launch
- expected evidence: verified internal boot-set no-op, one loader handoff,
  expected kernel/initramfs, USB root label/ancestry validation, successful
  systemd/graphics transition, branded splash and desktop without a greeter
- timeout: 3 minutes; if loader/root/display stalls or a login screen appears,
  leave the system in that state and stop for review
- rollback: return through one separately bounded normal restart only after
  collecting live state; do not power-cycle or repeat the launch
- operator action: launched Omarchy once and reported the nice loading splash,
  followed by a visible login screen instead of the desktop
- result: degraded pass. FPKG v0.28 verified all four internal artifacts,
  recognized the current set as already verified, sent the 320936-byte loader
  in one complete write and kexec'd once. Linux 6.18.44 Baikal resolved label
  `OMARCHY-PS4` to `/dev/sda`, mounted ext4 read/write, validated the external
  root and started systemd. Graphics reached the fixed 1920x1080 output and the
  operator saw the accepted quiet splash. Wi-Fi rejoined the recorded network.
  However, LightDM displayed its greeter, so persistent autologin did not meet
  acceptance despite the offline group/config verification
- bounded UART context:
  [`20260823_001150_471334-exp-20260823-018-a11-launch-prepared-omarchy-usb-and-verify-pers-deb3dd30.md`](../../ps4-uart/sessions/20260823_001150_471334-exp-20260823-018-a11-launch-prepared-omarchy-usb-and-verify-pers-deb3dd30.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: no loader, root, ext4, display, logger or fatal fault. UART
  intentionally has no LightDM journal detail because the product boot uses
  `console=null` and journald-to-kmsg does not expose the greeter's PAM reason
- rollback: none yet; Linux remains running at the greeter with the USB root
  mounted. Do not remove the USB
- next action: inspect LightDM/PAM/account/session state and current-boot journal
  read-only over the previously configured network path in a separate bounded
  session; do not log in or change configuration first

### EXP-20260823-018-A12 — inspect live LightDM autologin failure read-only

- state: complete — inconclusive; network reachable, SSH disabled
- question: can current-boot LightDM/PAM/configuration evidence be collected
  read-only over the previously configured network path without first logging
  into the greeter?
- changed variable: none; make one batch-mode SSH connection to existing owner
  `meerzulee` at the recorded private LAN address and run one read-only state
  report only if authentication succeeds
- expected evidence: package/group/config/session identity, LightDM unit state
  and current-boot LightDM/PAM journal within 60 seconds
- timeout: 60 seconds; stop after the first connection or authentication error
- rollback: none because no mutation is allowed
- operator action: none; Linux remained at the LightDM greeter
- result: inconclusive. The Mac neighbor table resolves the recorded private
  LAN address to the recorded Linux Wi-Fi MAC, but TCP port 22 refused the one
  batch SSH connection. No remote command ran and no live LightDM state was read
- bounded UART context:
  [`20260823_001436_329261-exp-20260823-018-a12-inspect-live-lightdm-pam-autologin-failure--52dad33a.md`](../../ps4-uart/sessions/20260823_001436_329261-exp-20260823-018-a12-inspect-live-lightdm-pam-autologin-failure--52dad33a.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: empty completed slice; no discontinuity or hardware fault,
  but no evidence about LightDM's failure reason
- rollback: none required; no connection or change occurred
- next action: sign in once through the visible LightDM greeter in a separate
  bounded operator action, then start SSH separately for live diagnostics

### EXP-20260823-019-A1 — sign in once through LightDM for diagnostics

- state: complete — pass by operator/network outcome
- question: do the existing `meerzulee` credentials enter the running Omarchy
  session normally after automatic login failed?
- changed variable: submit the existing owner credentials once through the
  visible LightDM greeter; do not change settings or retry authentication
- expected evidence: desktop/session becomes usable within 2 minutes and the
  operator reports the result; leave the system running for read-only diagnosis
- timeout: 2 minutes; stop after the first authentication error or desktop
- rollback: leave the greeter or desktop running; do not restart or remove USB
- operator action: signed in and subsequently reported SSH working for
  `meerzulee` at the recorded private LAN address; also reported that the
  system clock is wrong
- result: pass for manual-session access. Current credentials and desktop path
  are usable; SSH became reachable after the interactive login. Persistent
  autologin remains failed and clock synchronization is a second diagnosed issue
- bounded UART context:
  [`20260823_001615_772534-exp-20260823-019-a1-sign-in-once-through-lightdm-greeter-for-dia-04f09c9e.md`](../../ps4-uart/sessions/20260823_001615_772534-exp-20260823-019-a1-sign-in-once-through-lightdm-greeter-for-dia-04f09c9e.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: Wi-Fi remained associated with routine roaming attempts; no
  disconnect, storage, display, logger or fatal fault. UART does not carry the
  user-space greeter/session authentication result
- rollback: none required; Linux remains running from USB
- next action: collect one read-only SSH report covering LightDM/PAM and system
  time/NTP state before changing either subsystem

### EXP-20260823-019-A2 — inspect LightDM and clock state read-only over SSH

- state: complete — pass; both failure boundaries identified without mutation
- question: what exact live LightDM/PAM and system-time state explains the
  greeter and wrong clock?
- changed variable: none; run a bounded read-only SSH report as owner
  `meerzulee` against identity, time services, effective LightDM configuration,
  unit/session state and owner-readable current-boot logs
- expected evidence: one coherent report within 60 seconds; no sudo, service,
  file, clock or session mutation
- timeout: 60 seconds; stop at first SSH/authentication failure or completed report
- rollback: none because inspection is read-only
- operator action: none; desktop and SSH remained running
- result: pass. The clock is exactly `1970-01-01 06:07 +06`: PS4 exposes no
  usable RTC, timezone is correctly `Asia/Bishkek`, `CanNTP=yes`, but
  `systemd-timesyncd` is installed, disabled and inactive; no other NTP daemon
  is installed. For autologin, live NSS proves `meerzulee` belongs to system
  group `autologin` (gid 961), package v4.0.0-14 is installed, and
  `lightdm --show-config` resolves the exact owner/session/timeout fields from
  the intended files. The local `omarchy.desktop` exists. LightDM started the
  greeter and later opened a normal password-authenticated owner session, but
  the unprivileged journal contains no autologin PAM attempt; privileged logs
  remain unreadable and noninteractive sudo correctly requires the password
- bounded UART context:
  [`20260823_001925_309943-exp-20260823-019-a2-inspect-lightdm-and-clock-synchronization-st-48f13625.md`](../../ps4-uart/sessions/20260823_001925_309943-exp-20260823-019-a2-inspect-lightdm-and-clock-synchronization-st-48f13625.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: Wi-Fi remained associated; no storage, display, logger or
  fatal fault during the read-only SSH report
- rollback: none required; no state changed
- next action: enable systemd network time once with `timedatectl set-ntp true`
  in a separate bounded privileged operator action, then verify real date,
  synchronization and persistent enabled state before changing LightDM

### EXP-20260823-019-A3 — enable persistent systemd network time synchronization

- state: complete — inconclusive; bounded session aborted before operator action
- question: does enabling systemd network time once correct the clock on the
  connected PS4 and persist the service for later network connections?
- changed variable: one intended privileged `timedatectl set-ntp true` action;
  do not change the timezone, network profile, package set, display session or
  LightDM configuration
- expected evidence: `NTP=yes`, `NTPSynchronized=yes`, an enabled and active
  `systemd-timesyncd.service`, and a real 2026 date within 2 minutes while UART
  continuity remains valid
- timeout: 2 minutes after the operator command; stop on authorization failure,
  loss of SSH/network, logger discontinuity or failure to synchronize
- rollback: `timedatectl set-ntp false` only if enabling the service causes a
  regression; otherwise retain it because the PS4 exposes no usable RTC
- operator action: the exact command was presented twice, but completion was
  not reported before the bounded-session timeout
- result: inconclusive with no mutation. Read-only SSH polling continued to
  report a 1970 date, `NTP=no`, `NTPSynchronized=no`, and the timesync service
  disabled/inactive. The session was aborted rather than claiming an unobserved
  result. Routine Wi-Fi roaming diagnostics were the only UART traffic
- bounded UART context:
  [`20260823_002059_976888-exp-20260823-019-a3-enable-persistent-systemd-network-time-synch-65dad27d.md`](../../ps4-uart/sessions/20260823_002059_976888-exp-20260823-019-a3-enable-persistent-systemd-network-time-synch-65dad27d.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `aborted`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: capture continuity remained valid and showed no storage,
  display, logger or fatal fault, but UART cannot substitute for the missing
  privileged time-service action
- source conclusion: release-image construction now enables
  `systemd-timesyncd.service`, with local builder, validator and artifact
  contracts passing. This source change is not yet live-hardware acceptance
- rollback: none required because no console state changed
- next action: when the operator is present, open a fresh A4 session, run the
  one privileged command and verify synchronization before any LightDM work

### EXP-20260823-020-A1 — stage Wi-Fi forget-path package update over SSH

- state: complete — inconclusive; SSH path unavailable
- question: can the locally verified Wi-Fi selector packages be staged on the
  running USB root without changing the installed system or desktop session?
- changed variable: create one temporary owner-writable staging directory and
  copy exactly `omarchy-ps4-4.0.0-6` plus its dependency-matched
  `omarchy-ps4-provisioning-4.0.0-15` package; do not install, reload the shell,
  change NetworkManager state or forget another connection
- expected evidence: key-only SSH succeeds, both remote sizes and SHA-256
  digests match the OrbStack-built artifacts, and UART continuity stays valid
- timeout: 60 seconds; stop on SSH failure, checksum mismatch, network loss or
  logger discontinuity
- rollback: remove only the temporary staged package directory; the installed
  package database and active shell remain unchanged
- operator action: none; keep the current desktop and network state unchanged
- result: inconclusive with no mutation. The first key-only SSH connection
  timed out before the remote staging directory was created, so neither package
  was copied and no checksum or install command ran. This is consistent with
  the reported forgotten/disconnected Wi-Fi profile; no retry was attempted
- bounded UART context:
  [`20260823_005306_062530-exp-20260823-020-a1-stage-wi-fi-forget-path-package-update-over--df288ff9.md`](../../ps4-uart/sessions/20260823_005306_062530-exp-20260823-020-a1-stage-wi-fi-forget-path-package-update-over--df288ff9.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `completed`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: the valid bounded slice is empty and contains no logger or
  hardware fault; it cannot establish live network state
- rollback: none required because the connection failed before any remote write
- next action: reconnect the existing Wi-Fi profile with `nmtui` in a fresh A2
  operator session, without forgetting or changing any other network; then
  stage the already-built packages in a new action

### EXP-20260823-020-A2 — restore one Wi-Fi connection through nmtui

- state: complete — inconclusive; bounded session aborted before outcome
- question: can NetworkManager reconnect the operator-selected Wi-Fi through
  `nmtui` so the existing SSH path returns without relying on the broken panel?
- changed variable: activate or recreate exactly one Wi-Fi connection through
  `nmtui`; do not forget another profile, restart NetworkManager, install a
  package, reload Quickshell or change DNS
- expected evidence: `nmtui` reports activation, the desktop regains network,
  one bounded SSH probe succeeds, and UART shows association without a driver
  crash or disconnect loop
- timeout: 3 minutes; stop on authentication failure, no visible networks,
  network-service error, logger discontinuity or successful connection
- rollback: use `nmtui` to disconnect only the newly activated profile if it is
  the wrong network; otherwise retain it for package staging
- operator action: open a terminal, run `nmtui`, choose **Activate a
  connection**, select the intended Wi-Fi and connect; do not delete any other
  profile, then report `connected`
- result: inconclusive. No operator completion or visible outcome was reported
  before the three-minute timeout, no SSH probe was made, and the session was
  aborted rather than treating silence as a connection result
- bounded UART context:
  [`20260823_005429_390275-exp-20260823-020-a2-restore-one-wi-fi-connection-through-nmtui-cffba7cf.md`](../../ps4-uart/sessions/20260823_005429_390275-exp-20260823-020-a2-restore-one-wi-fi-connection-through-nmtui-cffba7cf.md),
  exact sibling `.raw`; logger `.events.jsonl` is empty; evidence state
  `aborted`, generation `80973222038e43548cda68da099cb054`, epoch `1`
- UART conclusion: the valid slice is empty and contains no logger or hardware
  fault; it cannot prove that the operator opened or completed `nmtui`
- rollback: none required because no changed state was observed
- next action: after the operator explicitly reports that Wi-Fi is connected,
  open a fresh A3 session and stage the exact two package artifacts once

## Session-close checklist

- [ ] Bounded UART session stopped or explicitly aborted with reason.
- [ ] Raw `.raw`, logger `.events.jsonl`, and compact `.md` paths recorded.
- [ ] Operator outcome recorded.
- [ ] Result classified: pass, degraded, fail, inconclusive, or blocked.
- [ ] Rollback state recorded and verified when required.
- [ ] Compatibility ledger updated if evidence changes a claim.
- [ ] Exactly one next action or an explicit stop condition recorded.
