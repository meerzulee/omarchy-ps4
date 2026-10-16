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

- Read `docs/DEVELOPMENT-HOSTS.md` when setting up another development device.
- Start a fresh device from `https://github.com/meerzulee/omarchy-ps4.git`
  and run `scripts/setup-workspace`. The authoritative kernel/UART URLs,
  branches and commits are in `manifests/development-sources.json`; do not
  substitute a historical workspace checkout or an unrelated PS4 kernel fork.
- Obtain upstream Linux through the sibling kernel's builder, upstream Omarchy
  through `scripts/sync-omarchy-upstream`, and the pinned loader through
  `scripts/fetch-ps4-loader`. Follow the manifest/hash gates instead of asking
  the operator to copy inputs that can be retrieved from their recorded source.
- Workspace README/AGENTS templates are versioned in `workspace/`; the setup
  helper copies only missing files and never resets an existing repository.
- macOS ARM64 uses the existing OrbStack build wrappers. On Linux x86-64,
  source work and host tests run natively, and the sibling kernel can build
  with native `make`. Full distribution image builds still use the Mac host.
- Use OrbStack exclusively for Docker, containers, and Linux virtual machines.
- Before Docker work, verify OrbStack is running and the active Docker context
  is `orbstack`.
- Do not start Docker Desktop, Colima, Lima, or Homebrew-managed PostgreSQL.
- Do not bypass OrbStack checks or substitute another runtime on Linux. A
  native Linux port of the image builders is separate implementation work.
- Keep the kernel, Omarchy and UART repositories as siblings and derive paths
  from the checkout. Recreate Python environments after a device move.
- Preserve local commits and uncommitted work during handoff; do not push,
  publish, merge divergent histories or reset a checkout without task authority.
- Include the full raw URL for operational web links and an absolute path for
  local artifacts; provide a macOS `open` command when immediately useful.

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
