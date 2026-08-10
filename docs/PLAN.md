# Omarchy PS4 execution plan

Status date: 2026-08-10

This plan is the project sequence. Work moves forward by passing gates, not by
installing the entire Omarchy stack and debugging all failures at once.

## Operating rule

For every component:

1. Pin the exact upstream source or Arch package version.
2. Install only that component and its required dependencies.
3. Run its defined test on the known console.
4. Save commands, versions, logs, and the observed result.
5. Classify it using `COMPATIBILITY.md`.
6. If it passes, keep upstream behavior and continue.
7. If it fails, isolate the lowest failing layer before considering a patch.
8. Build a PS4-specific replacement only when no maintained solution exists.
9. Confirm XFCE still boots after every change.

## Phase 0 — Repository foundation

Status: complete

- Create a standalone Git repository.
- Record the engineering, safety, and UX rules in `AGENTS.md`.
- Establish the roadmap, baseline, and compatibility ledger.
- Keep large kernels and root filesystem artifacts outside Git.

Exit gate: a contributor can identify the current phase, the next test, the
known-good fallback, and the evidence required for a support claim.

## Phase 1 — Freeze the known-good XFCE baseline

Status: evidence found; clean reproduction pending

- Preserve the Linux 5.4.247 Baikal kernel and matching modules.
- Preserve the Arch/XFCE rootfs recipe and artifact digests.
- Capture a complete hardware probe from a successful boot.
- Replace unstable disk device assumptions with label/UUID discovery.
- Remove development passwords and define safe first-boot access.
- Rebuild the image from a clean environment using OrbStack.

Exit gate: two cold boots into XFCE from a freshly rebuilt image, with HDMI,
USB input, storage, package management, and at least one network path tested.

## Phase 2 — Test and evidence tooling

Status: pending

- Add a single command that captures kernel, DRM, Mesa, display, input, audio,
  network, storage, service, and session information.
- Store human-readable results beside raw logs.
- Give every experiment a stable ID and explicit pass criteria.
- Add a comparison command for two experiment results.

Exit gate: a failed test produces enough evidence to locate the failing layer
without relying on memory or screenshots alone.

## Phase 3 — Pin and inventory Omarchy Quattro

Status: pending

- Pin one Quattro commit rather than tracking the moving branch.
- Extract its packages, services, configuration, migrations, and runtime
  assumptions into an inventory.
- Separate desktop essentials from applications and PC-specific integration.
- Map each item to a compatibility test or an explicit exclusion.

Exit gate: every item included in the proposed PS4 profile has an owner,
dependency chain, test, and status.

## Phase 4 — Compatibility ladder

Status: pending

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

## Phase 5 — PS4 compatibility packages

Status: pending

- Package only the patches and overrides justified by Phase 4 evidence.
- Keep kernel, modules, Mesa, libdrm, LLVM, and 32-bit graphics libraries in a
  tested compatibility set.
- Publish signed packages from reproducible off-console builds.
- Add update preflight checks that prevent partial graphics-stack upgrades.

Exit gate: a clean rootfs can install the proven desktop stack entirely from
signed repositories and pinned source inputs.

## Phase 6 — Product integration

Status: pending

- Produce the reduced Omarchy PS4 rootfs.
- Add first-boot setup designed for television and controller use.
- Build installation, progress, diagnostics, repair, and removal flows.
- Add signed A/B boot assets and last-known-good rollback.
- Test interrupted downloads, power loss, full disks, invalid signatures, and
  failed boots as first-class user journeys.

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
