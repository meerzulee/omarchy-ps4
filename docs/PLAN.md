# Omarchy PS4 execution plan

Status date: 2026-08-13

This plan is the project sequence. Work moves forward by passing gates, not by
installing the entire Omarchy stack and debugging all failures at once.

## Operating rule

For every component:

1. Resume from `experiments/SESSIONS.md`; never rely on chat memory alone.
2. Pin the exact upstream source or Arch package version.
3. Install only that component and its required dependencies.
4. Start a bounded UART session before the operator performs a PS4-side action.
5. Run its defined test on the known console with one changed variable.
6. Save commands, versions, raw/compact UART logs, and the operator's observed
   result.
7. Close the session with a conclusion, rollback state, and one next action.
8. Classify it using `COMPATIBILITY.md`.
9. If it passes, keep upstream behavior and continue.
10. If it fails, isolate the lowest failing layer before considering a patch.
11. Build a PS4-specific replacement only when no maintained solution exists.
12. Confirm XFCE still boots after every change.

## Phase 0 — Repository foundation

Status: complete

- Create a standalone Git repository.
- Record the engineering, safety, and UX rules in `AGENTS.md`.
- Establish the roadmap, baseline, and compatibility ledger.
- Keep large kernels and root filesystem artifacts outside Git.

Exit gate: a contributor can identify the current phase, the next test, the
known-good fallback, and the evidence required for a support claim.

## Phase 1 — Freeze the known-good XFCE baseline

Status: clean rootfs built; real-hardware gate pending

- Preserve the Linux 5.4.247 Baikal kernel and matching modules.
- Preserve the Arch/XFCE rootfs recipe and artifact digests.
- Capture a complete hardware probe from a successful boot.
- Replace unstable disk device assumptions with label/UUID discovery.
- Remove development passwords and define safe first-boot access.
- Rebuild the image from a clean environment using OrbStack.

Exit gate: two cold boots into XFCE from a freshly rebuilt image, with HDMI,
USB input, storage, package management, and at least one network path tested.

## Phase 2 — Test and evidence tooling

Status: complete

- Add a single command that captures kernel, DRM, Mesa, display, input, audio,
  network, storage, service, and session information.
- Store human-readable results beside raw logs.
- Give every experiment a stable ID and explicit pass criteria.
- Add a comparison command for two experiment results.

Exit gate: a failed test produces enough evidence to locate the failing layer
without relying on memory or screenshots alone.

## Phase 3 — Pin and inventory Omarchy Quattro

Status: complete

- Pin one Quattro commit rather than tracking the moving branch.
- Extract its packages, services, configuration, migrations, and runtime
  assumptions into an inventory.
- Separate desktop essentials from applications and PC-specific integration.
- Map each item to a compatibility test or an explicit exclusion.

Exit gate: every item included in the proposed PS4 profile has an owner,
dependency chain, test, and status.

## Research checkpoint — PS4 Linux ecosystem

Status: complete as of 2026-08-10

- Create a dated, evidence-labelled snapshot under `knowledge/`.
- Separate current projects from historical patch ancestry and binary-only
  distribution options.
- Record what exists, what remains experimental, and what was not found.
- Track exact upstream branch heads in a machine-readable source manifest.
- Carry unresolved kernel, graphics, licensing, and desktop gaps into the
  compatibility ladder.

Exit gate: the next hardware experiment is based on current primary sources,
and a contributor can detect when those sources have moved.

## Phase 4 — Compatibility ladder

Status: active; XFCE, native Wayland, Hyprland, UWSM, Foot, and the Quattro
shell have reached visible hardware results. Display stability, audio, Vulkan,
video decode, capture, and remaining integrations are not accepted.

Test in this order:

1. Kernel boot, DRM/KMS, HDMI mode setting, and GPU reset behavior.
2. Mesa EGL/OpenGL software and hardware rendering.
3. Vulkan, only after OpenGL is understood.
4. A minimal Wayland compositor and native Wayland client.
5. Seat/logind, input, environment, and session lifecycle.
6. Bare Hyprland with no Omarchy configuration.
7. UWSM-managed Hyprland startup and shutdown.
8. XDG desktop portals, file picker, clipboard, notifications, and polkit.
9. PipeWire audio, screen capture, and sharing.
10. Quickshell with a minimal configuration.
11. Omarchy Quattro shell configuration and themes.
12. DualShock 4 navigation and controller-friendly interaction.
13. Chromium and the reduced default application profile.

Each step requires a cold-boot test and an XFCE regression check. A failure
stops advancement only for its dependent branch; unrelated tests may continue.

Exit gate: the ledger distinguishes proven, degraded, replaceable, blocked,
and intentionally excluded Omarchy capabilities.

## Phase 5 — Portable runtime and PS4 compatibility packages

Status: portable runtime and package recipes implemented; native package and
real-hardware installation gates remain

- Ship the pinned Quattro user layer first as a non-root, versioned portable
  bundle with an exact rollback.
- Keep XFCE, LightDM, `/etc`, boot assets, and system services outside the
  portable transaction.
- Package only the patches and overrides justified by Phase 4 evidence.
- Keep kernel, modules, Mesa, libdrm, LLVM, and 32-bit graphics libraries in a
  tested compatibility set.
- Publish signed packages from reproducible off-console builds.
- Add update preflight checks that prevent partial graphics-stack upgrades.

Exit gate: a clean rootfs can install the proven desktop stack entirely from
signed repositories and pinned source inputs.

## Deferred kernel workstream — Atomic PS4 display

Status: planned; keep the working legacy DCE8 kernel as the default and
recovery path

- Develop on a separate `wip/display-core-atomic` branch.
- Resolve the PS4 AMDGPU/Display Core patch rejects and make Liverpool and
  Gladius initialization internally consistent.
- Bring Liverpool up through AMD Display Core (`amdgpu_dm`) instead of merely
  forcing `amdgpu.dc=1` on the incomplete path.
- Convert the Aeolia-controlled MN864729 HDMI integration into a per-device,
  atomic DRM bridge and connect it to Display Core link/connector creation.
- Preserve the known-good firmware-trained DP transmitter state and begin with
  the proven 1920x1080 at 60 Hz mode.
- Validate atomic modesetting and page flips before testing color management,
  DPMS, hotplug, additional modes, HDMI audio, or hardware video decoding.

Exit gate: Aquamarine acquires `DRM_CLIENT_CAP_ATOMIC` without its legacy
fallback, HDMI and framebuffer output survive the defined cold-boot count, and
`modetest` exposes the expected atomic CRTC and plane properties. CTM, gamma,
audio, and other optional capabilities remain unsupported until their own
hardware gates pass.

## Phase 6 — Product integration

Status: active; Quattro RC3 source, deferred-owner design, package hosting
architecture, and the Orbis manager protocol draft are pinned. Native FPKG,
installer implementation, and real-hardware acceptance remain.

- Produce the full Omarchy PS4 workstation profile on top of the proven base,
  while keeping unsupported hardware services disabled by default.
- Add first-boot setup designed for television and controller use.
- Build installation, progress, diagnostics, repair, and removal flows.
- Add signed A/B boot assets and last-known-good rollback.
- Adapt Quattro's deferred-owner setup to the external PS4 root without SDDM,
  Limine, LUKS re-keying, or Btrfs factory-reset assumptions.
- Publish packages through a separate, signed `omarchy-ps4-pkgs` repository
  with edge/stable promotion and mandatory trusted signatures.
- Test interrupted downloads, power loss, full disks, invalid signatures, and
  failed boots as first-class user journeys.
- Build the `fpkg/` manager as the single Install/Boot/Repair entry point. It
  downloads signed image artifacts and carries the pinned Linux loader payload,
  while GoldHEN remains an explicit prerequisite.
- Keep owner/password entry in Linux first boot; the FPKG and downloadable
  image must contain no default credential.
- Resolve PS4 Linux Loader redistribution rights before any public FPKG embeds
  its ELF.
- Install only to a preformatted external USB root labelled `OMARCHY-PS4`;
  keep formatting as a separate, explicit Linux-host preparation step.
- Use the SATA-disabled product profile to avoid the internal-disk timeout,
  with the visible-log/no-SATA-change debug profile retained as rollback.
- Show the custom framebuffer splash on HDMI while keeping Baikal earlycon on
  UART; do not add Plymouth to the custom PS4 boot chain.

Exit gate: installation and recovery are understandable without a development
machine, SSH session, or undocumented shell command.

## UX and DX acceptance bar

- One obvious command per common development task.
- No mystery state: commands say what they are checking or changing.
- Errors identify the failed layer and point to the relevant log.
- Long work is resumable and reports meaningful progress.
- Destructive operations preview exact targets and remain opt-in.
- Defaults are safe for the supported console; advanced controls stay
  discoverable without crowding the main flow.
- Documentation is tested alongside the commands it describes.
