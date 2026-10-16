# PS4 Linux workspace rules

## Authoritative projects

- `linux-ps4-kernel/` owns the patch-based PS4 Linux kernel, configs, build
  containers, modules, provenance, and kernel artifacts.
- `omarchy-ps4/` owns the Arch/XFCE baseline, compatibility ladder,
  distribution UX, installation/recovery design, and curated experiment
  records. Its public repository is `https://github.com/meerzulee/omarchy-ps4`.
  Creating releases and pushing new work still require explicit task authority.
- `ps4-uart/` owns continuous UART collection and bounded action-session
  extraction.
- `references/`, `payloads/`, `backups/`, and `lab/` are workspace-local
  research, downloaded artifacts, recovery copies, and console inventory.

Treat `linux-ps4-kernel/` and `omarchy-ps4/` as the authoritative active
repositories. Older directories such as `linux-ps4/` and `linux-ps4-git/` are
historical references unless a task explicitly names them.

## Hardware development mode

Use one bounded UART session per coherent hardware experiment, not per click,
screen, cable movement, or sub-step. A session may include multiple
predeclared operator actions when they serve one question, for example update
boot files, launch once, observe the result, and return safely. Keep the
continuous logger running so an unexpected transition is still recoverable.

A bounded session is mandatory when evidence matters for a payload or Linux
boot, kernel/initramfs/boot-file change, storage write or format, driver load,
power/reboot test, or acceptance claim. Routine Orbis navigation, cosmetic UI
inspection, dismissing a message, and moving already-unmounted media do not
need their own session unless they are themselves the subject of the test.

The lightweight handshake is:

1. Give the experiment a stable `EXP-YYYYMMDD-NNN` identifier and state the
   single objective, expected evidence, timeout, and safe rollback. Use action
   suffixes only for genuinely independent variables, not ordinary workflow
   steps.
2. Confirm continuous UART capture and start one bounded session before the
   first consequential action.
3. Tell the operator the complete short sequence and its stop conditions.
4. Keep the session open through the coherent sequence, accepting operator
   observations as they arrive. Stop early on a terminal fault or safety
   boundary.
5. Stop once the objective is answered. Read the compact context first,
   inspect raw only when needed, and record one concise conclusion with the
   relevant artifacts. Only `completed` continuity supports acceptance; a
   logger restart or serial reconnect makes the partial session `invalid`.

Do not create sessions merely to satisfy bookkeeping. If UART cannot answer a
meaningful technical question for an action, rely on continuous capture and
the operator report instead. Local documentation, source inspection, builds,
VM tests, and read-only media inspection do not require a PS4 UART marker.

## Anti-loop rules

- Keep at most one active hardware experiment.
- Change one diagnostic variable per experiment; ordinary setup, observation,
  and cleanup steps may remain grouped around that variable.
- Never repeat a failed action without recording what new evidence or changed
  variable makes the retry different.
- If the same failure repeats three times without new evidence, stop retrying,
  mark the path blocked or inconclusive, and move down one layer or restore the
  rollback.
- Close and conclude a session before starting a different diagnostic branch,
  but do not split a coherent workflow into artificial action sessions.
- A successful boot once is evidence, not support. Promotion requires the
  acceptance count defined by the active plan.
- Agent agreement, compilation, package installation, and an absence of UART
  errors are not substitutes for observed real-hardware acceptance criteria.

The curated source of truth is `omarchy-ps4/experiments/SESSIONS.md`. Raw UART
data remains local unless deliberately reviewed and redacted.

## Agent collaboration

The project owner authorizes launching additional coding agents for bounded
advice, independent audit, research, testing, or implementation work. They may
run in isolated Herdr panes or through the available agent orchestration.
Commands such as `claude --dangerously-skip-permissions` or `codex --yolo` are
permitted only inside the intended workspace and only for the assigned scope.

This permission does not independently authorize an agent to:

- send a PS4 payload or operate the console;
- format or overwrite storage;
- overwrite console-internal boot files;
- push branches, create public repositories or releases;
- rewrite Git history;
- publish credentials, private logs, firmware, or unlicensed artifacts.

Those actions still require explicit task authority and the normal hardware or
destructive-action checks. The primary agent must verify delegated findings
against source, tests, or hardware evidence before adopting them.

## Local infrastructure

- Use OrbStack exclusively for Docker, containers, Linux virtual machines, and
  related local infrastructure.
- Before Docker work, verify OrbStack is running and the active Docker context
  is `orbstack`.
- Do not start Docker Desktop, Colima, Lima, Homebrew-managed PostgreSQL, or a
  competing runtime.

## Development hosts and handoff

- Read `README.md` and `omarchy-ps4/docs/DEVELOPMENT-HOSTS.md` for host setup.
- On a fresh computer, clone `https://github.com/meerzulee/omarchy-ps4.git`
  and run `scripts/setup-workspace`. Kernel/UART source URLs and full commit
  pins live in `omarchy-ps4/manifests/development-sources.json`.
- Obtain full upstream Linux through the kernel builder, upstream Omarchy
  through `scripts/sync-omarchy-upstream`, and the verified upstream loader
  through `scripts/fetch-ps4-loader`. Do not require a private source archive
  or manual transfer for inputs available from their recorded upstream source.
- The portable workspace README and these rules are versioned in
  `omarchy-ps4/workspace/`; setup copies only missing workspace files.
- On macOS ARM64, build the x86-64 PS4 kernel with the OrbStack helper; do not
  run the Linux kernel build directly on Darwin.
- On Linux x86-64, use native tools for kernel builds, source work and host
  tests. Native compilation does not require a container or virtual machine.
- The Omarchy container/image wrappers currently require OrbStack. On Linux,
  use the existing Mac build host until a native port is explicitly scoped;
  do not bypass their runtime guards or introduce another runtime.
- Keep `linux-ps4-kernel/`, `omarchy-ps4/` and `ps4-uart/` as siblings. Resolve
  local paths from the workspace instead of copying a Mac user's absolute path.
- Before moving devices, check live remote refs as well as local Git status.
  Preserve local commits, staged/unstaged changes and untracked files. Do not
  resolve divergence by resetting, rebasing or merging without task authority.
- Recreate virtual environments on the destination. Do not carry UART PID,
  lock, port-pointer or active-session state between machines; evidence may be
  copied privately, but capture must establish a new connection and session.
- Each active repository has its own `AGENTS.md`; read it even when working
  from a standalone clone.
