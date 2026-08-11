# Development session ledger

Updated: 2026-08-11

This is the resume point for the project. Read this file, `docs/PLAN.md`, and
`docs/COMPATIBILITY.md` before proposing a new PS4-side action.

## Current position

- active phase: Phase 1, real-hardware XFCE baseline acceptance
- local preparation gate: `PREP-20260810-001` complete through read-only
  GoldHEN FTP after the Kingston USB was connected directly to the PS4.
  `/mnt/usb0` contains one complete boot bundle; `EXP-20260810-000-A1`
  corrected its only blocker and reverified every core-file hash
- active hardware experiment: `EXP-20260810-000` is closed as inconclusive
  because insertion happened without a bounded UART marker; its read-only FTP
  observation is still valid source-state evidence. `EXP-20260810-000-A1`
  completed. The first `EXP-20260810-001` capture was aborted before launch
  when the Vue menu exposed only an unverified BIN. `EXP-20260810-001-A1`
  installed and verified v25 ELF but the Vue refresh crashed; the separate ELF
  loader survived on port `9021`, but `EXP-20260810-001-A2` proved that its
  ELF handoff was unhealthy. `EXP-20260810-001-A3` completed a clean shutdown
  and `EXP-20260810-001-A4` completed a clean cold boot. The operator confirmed
  the installed jailbreak UI is full Vue After Free 2.0;
  `EXP-20260810-001-A5` established a clean GoldHEN runtime;
  `EXP-20260810-001-A6` passed loader/kexec handoff but the integrated boot
  failed, and `EXP-20260810-001-A7` captured the terminal root-device timeout
- next hardware action: none until the local 6.15.4-versus-6.18.44 scanout
  comparison and one-variable A39 diagnostic kernel are complete. A38 left
  Linux running with the ext4 root mounted read-write, so recovery to Orbis is
  itself the next separately declared bounded hardware action
- continuous UART: last verified `READY` on `/dev/cu.wchusbserial140`, PID
  `97034`, generation `274d8db2bb43469ea93e25d7befa6db1`; runtime
  identifiers must still be rechecked before every action
- known-good rollback: internal Linux `5.4.247-neocine-1.1` boot set plus FAT
  `recovery/` files on the prepared USB
- authoritative kernel repository: `linux-ps4-kernel`, branch
  `port/6.18.44-baikal`
- distribution repository: `omarchy-ps4`, local branch `main`, no remote yet

## Work-session history

| Session | State | Outcome | Evidence/resume pointer |
|---|---|---|---|
| `DEV-20260810-001` | complete | Refreshed PS4 Linux ecosystem and recorded current projects/gaps | [`knowledge/2026-08-10/`](../knowledge/2026-08-10/) |
| `DEV-20260810-002` | complete | Ported patch stack to Linux 6.18.44 LTS; 47 patches apply and kernel/modules build reproducibly | [`6.18-PORT.md`](../../linux-ps4-kernel/docs/6.18-PORT.md) and local kernel output |
| `DEV-20260810-003` | complete | Built clean pinned Arch/XFCE rootfs and label-aware initramfs | [`docs/BUILDING.md`](../docs/BUILDING.md) and local ignored output |
| `DEV-20260810-004` | complete | Prepared confirmed Kingston USB: 1GiB FAT32 boot plus ext4 `OMARCHY-PS4`; offline filesystem checks passed | [`docs/FIRST-BOOT-6.18-XFCE.md`](../docs/FIRST-BOOT-6.18-XFCE.md) |
| `DEV-20260810-005` | complete | Added continuous UART logger and bounded raw/LLM session extraction | [`ps4-uart/README.md`](../../ps4-uart/README.md); live logger PID is runtime state, not durable evidence |
| `DEV-20260810-006` | complete | Audited firmware-12.02 delivery chain; pinned loader v25, PSFree sender, Payload Guest, HenLoader fallback, and hashes | [`FW-12.02-PAYLOAD-CHAIN.md`](../knowledge/2026-08-10/FW-12.02-PAYLOAD-CHAIN.md) |
| `DEV-20260810-007` | complete | Backed up existing `/data/linux/boot` through read-only FTP and identified Linux 5.4.247-neocine rollback | [`backups/ps4-data-linux-boot/2026-08-10-fw12.02/`](../../backups/ps4-data-linux-boot/2026-08-10-fw12.02/) |
| `DEV-20260810-008` | complete | Independent UART workflow audit accepted; hardened exact-byte capture, readiness, continuity, collision safety, and storage guards | [`ps4-uart/README.md`](../../ps4-uart/README.md); automated suite and live capture report `READY` |
| `DEV-20260810-009` | complete | Final read-only audit found capture-drain, concurrent-start, cleanup, durability, storage-error, and recovery races; all accepted findings were fixed, 22 tests pass, and a live capture fence was acknowledged | `ps4-uart` generation `1307aff7e5324e438f69fdeee53d995b`; audit was advice only and touched no hardware |
| `DEV-20260811-010` | complete | Restored rmux-derived Baikal MSI patches 0007+0008+0009 as one treatment; strict gate applied 50/50 and clean OrbStack build/checksums passed | [`6.18-PORT.md`](../../linux-ps4-kernel/docs/6.18-PORT.md); bzImage SHA-256 `0d7cd17af71495df3e54f49fcfd31d41020ec096505f50e1938a4e92cb96f97b` |
| `DEV-20260811-011` | complete | Ported the PS4 DRM bridge to Linux 6.18's managed lifetime after A25 isolated the kref defect; strict gate applied 52/52 and clean OrbStack build/checksums passed | [`6.18-PORT.md`](../../linux-ps4-kernel/docs/6.18-PORT.md); bzImage SHA-256 `f1a6eabe49f12853a0cc93af462b2153dc09b58de0c5bfc28bb2d6cc50fdc1dd` |
| `DEV-20260811-012` | complete | Replaced the incompatible archived HDMI diagnostic with pointer-safe post-0034 patch 0035; strict gate applied 53/53 and clean OrbStack build/checksums passed | [`6.18-PORT.md`](../../linux-ps4-kernel/docs/6.18-PORT.md); A29 bzImage SHA-256 `ab754ca139d8c4a09fb6c57e81c07b3dfde618d31146e15b7ca6d1fa5de0d46e` |
| `DEV-20260811-013` | complete | Audited Vue After Free 2.0 PSN-prompt recovery and compared the exact 6.18 A29 hardware paths with rmux Baikal 7.0.8; identified loader-provided dynamic EDID as the clearest isolated display gap and corrected managed-bridge prior-art attribution | [`VUE-AFTER-2-RECOVERY.md`](../knowledge/2026-08-11/VUE-AFTER-2-RECOVERY.md); [`RMUX-7.0-BAIKAL-COMPARISON.md`](../../linux-ps4-kernel/docs/RMUX-7.0-BAIKAL-COMPARISON.md) |

The two older files under `experiments/uart/` captured the continuous OrbisOS
stream before this bounded-session protocol. They are useful background logs,
but they are not evidence of a Linux 6.18 boot.

## Release and repository queue

- `omarchy-ps4` remains local with no remote; public creation/push is an
  explicit later release action.
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

## Session-close checklist

- [ ] Bounded UART session stopped or explicitly aborted with reason.
- [ ] Raw `.raw`, logger `.events.jsonl`, and compact `.md` paths recorded.
- [ ] Operator outcome recorded.
- [ ] Result classified: pass, degraded, fail, inconclusive, or blocked.
- [ ] Rollback state recorded and verified when required.
- [ ] Compatibility ledger updated if evidence changes a claim.
- [ ] Exactly one next action or an explicit stop condition recorded.
