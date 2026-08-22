# Omarchy PS4 contributor rules

## Product standard

- Treat this as a real distribution project, not a demo or a collection of
  one-off shell snippets.
- Prefer small, inspectable tools with clear inputs, progress, errors, and
  recovery instructions.
- Never claim hardware or software support without a recorded real-hardware
  test result.
- Do not hide uncertainty. Use the compatibility states defined in
  `docs/COMPATIBILITY.md`.
- Keep the known-good XFCE installation bootable while testing later layers.

## Test discipline

- Follow [`docs/DEVELOPMENT-MODE.md`](docs/DEVELOPMENT-MODE.md) for consequential
  PS4 hardware experiments. Keep continuous UART, but use one bounded session
  for a coherent objective rather than one session per operator action.
- Change one diagnostic variable per hardware experiment; group its necessary
  setup, observation, and cleanup steps.
- Record the console model, southbridge, firmware, kernel, package versions,
  commands, result, and relevant logs for acceptance or failure investigations,
  not for routine navigation with no diagnostic value.
- A failed experiment must have a documented rollback path.
- Do not promote a component to the root filesystem until its individual gate
  passes.
- Close the active entry in [`experiments/SESSIONS.md`](experiments/SESSIONS.md)
  before starting a different diagnostic branch.

## Agent collaboration

- Additional agents may perform bounded advice, independent audit, research,
  tests, or implementation work.
- Delegated conclusions must be verified by the primary agent. Agent agreement
  is not hardware evidence.
- Spawning an agent does not authorize console actions, destructive storage
  operations, public pushes/releases, or Git history rewrites.

## Local infrastructure

- Use OrbStack exclusively for Docker, containers, and Linux virtual machines.
- Before Docker work, verify OrbStack is running and the active Docker context
  is `orbstack`.
- Do not start Docker Desktop, Colima, Lima, or Homebrew-managed PostgreSQL.

## Safety

- Never assume a disk device name such as `/dev/sda` or `/dev/sdb`.
- Disk-writing tools must identify the target by stable metadata, show the
  resolved device, and require explicit confirmation.
- Do not ship default passwords or enable remote password login in release
  images.
- Keep downloaded artifacts out of Git. Track their source, version, size, and
  digest instead.

## Source policy

- Pin upstream commits used by builds and compatibility tests.
- Prefer upstream packages and patches when they work on PS4.
- Create a PS4-specific package or implementation only after a recorded test
  demonstrates that the upstream solution is missing or incompatible.
- Preserve license and source provenance for kernels, firmware handling,
  loaders, and patched packages.
