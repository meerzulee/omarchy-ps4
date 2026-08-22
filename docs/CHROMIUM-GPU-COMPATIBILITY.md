# Chromium GPU compatibility

## Accepted beta policy

Omarchy PS4 launches Chromium with software rendering by default. The owner
configuration contains:

```text
--disable-gpu
```

This is an application-specific compatibility policy. It does not disable the
GPU for Hyprland, Quickshell or other applications.

`omarchy-ps4-chromium-software-rendering` manages the owner flag
idempotently:

```bash
omarchy-ps4-chromium-software-rendering --check
omarchy-ps4-chromium-software-rendering --enable
omarchy-ps4-chromium-software-rendering --disable
```

Chromium must be restarted after changing the flag. `--disable` is a developer
rollback and must not be exposed as a normal product toggle while the native
GPU path remains unaccepted.

## Evidence

The original Chromium 151 process used native Wayland, hardware acceleration
and `/dev/dri/renderD128`. Repeated dark rectangular tiles were present inside
a compositor-captured PNG, proving the corruption occurred before HDMI scanout
and was not caused by the cable or monitor.

In `EXP-20260822-013-A2`, the same Chromium package, user profile, page, Mesa,
kernel, compositor and display mode were retained. The only rendering change
was `--disable-gpu`. Chromium reported GL disabled and its renderers reported
GPU compositing disabled. The operator confirmed that the same GitHub toolbar
area was clean. The bounded UART slice contained no GPU reset, ring timeout,
HDMI fault or logger discontinuity.

The working diagnosis is an incompatibility in Chromium's accelerated
Skia/GBM/Wayland buffer path on Liverpool/DCE8. `AMD_DEBUG=notiling` remains
required for the wider session, but it does not prevent every Chromium GPU
buffer allocation or import path.

## Future acceleration work

Keep software rendering until all acceptance requirements below pass. Test
one variable per bounded experiment in this order:

1. Replace `--disable-gpu` with `--disable-gpu-compositing` and compare the
   same static toolbar, scrolling page, video and screenshot capture.
2. Return to the accepted baseline, then test `--disable-zero-copy` alone to
   isolate DMA-BUF/zero-copy presentation.
3. Audit Chromium's `chrome://gpu` feature status and GPU-process command line
   for each candidate without treating process survival as visual acceptance.
4. Compare pinned Mesa versions to determine whether the fault is a userspace
   regression or a persistent Liverpool modifier/tiling limitation.
5. Only after application-specific tests, consider a compositor-wide explicit
   modifier experiment. A global modifier override affects every client and
   is not an acceptable first workaround.
6. If the failure persists across Mesa versions, reduce it to a standalone
   Wayland/GBM reproducer before changing the PS4 kernel driver.

Promotion requires clean cold launches and restored sessions, static and
scrolling pages, browser chrome, WebGL-disabled fallback, video playback,
screenshot capture and repeated use without new UART GPU/display faults. CPU
load and frame pacing must also remain usable at 1920x1080 because software
rendering shifts work to the PS4 Jaguar CPU.

Hardware video decode remains a separate compatibility gate. The non-fatal
VA-API initialization error observed during the software-rendering experiment
does not invalidate this workaround.
