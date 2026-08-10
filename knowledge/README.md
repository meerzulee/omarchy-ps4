# PS4 Linux knowledge base

This directory is the project's dated view of the PS4 Linux ecosystem. It is
not a mirror of community claims and it is not a hardware support promise.

Start with [`2026-08-10/WORLD-STATE.md`](2026-08-10/WORLD-STATE.md).

## How to read it

Claims use four evidence classes:

| Class | Meaning |
|---|---|
| Project fact | Directly visible in source, a tagged release, or repository metadata |
| Maintainer report | Documented by the developer, but not reproduced by this project |
| Project test | Reproduced on our named PS4 with logs and exact versions |
| Not found | No public evidence was found in the stated search scope; this is not proof of impossibility |

Activity and compatibility are separate. A repository can be active while a
particular console remains unsupported, and an old build can remain the best
known fallback.

## Snapshot contents

- [`WORLD-STATE.md`](2026-08-10/WORLD-STATE.md): the short answer—what exists
  now and what does not.
- [`PROJECTS.md`](2026-08-10/PROJECTS.md): relevant upstream projects and how
  we intend to use them.
- [`HARDWARE.md`](2026-08-10/HARDWARE.md): southbridge-specific state and the
  distinction between upstream reports and our own evidence.
- [`GAPS.md`](2026-08-10/GAPS.md): missing or unproven pieces, ordered for this
  project.
- [`SOURCES.md`](2026-08-10/SOURCES.md): primary sources, exact refs, and
  research limits.
- [`repos.tsv`](repos.tsv): machine-readable repository refs captured by this
  snapshot.

Run `./scripts/check-knowledge-sources` to see whether a tracked branch has
moved since this snapshot. The command is read-only and exits non-zero when it
detects drift.

## Update rule

Do not silently rewrite a dated snapshot. Create a new `YYYY-MM-DD` directory,
copy only still-relevant claims, update `repos.tsv`, and record contradictions
or superseded reports explicitly.
