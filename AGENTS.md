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

- Change one variable per hardware experiment.
- Record the console model, southbridge, firmware, kernel, package versions,
  commands, result, and attached logs for every experiment.
- A failed experiment must have a documented rollback path.
- Do not promote a component to the root filesystem until its individual gate
  passes.

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
