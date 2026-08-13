# PS4 development mode

Status date: 2026-08-10

Development mode is a turn-based protocol between the operator, the primary
LLM, UART capture, and optional review agents. Its purpose is to keep every
hardware action attributable and prevent repeated guesses from becoming a
debugging loop.

## Roles

- **Operator:** performs the physical or PS4 UI action and reports outcomes
  that UART cannot show: HDMI, LEDs, fan, controller, sound, timing, and errors
  visible on screen.
- **Primary LLM:** defines one experiment, starts/stops its bounded capture,
  reads the logs and operator report, records the conclusion, and chooses the
  next smallest action.
- **UART logger:** continuously retains the complete stream and extracts an
  exact bounded slice plus compact Markdown context for each action.
- **Review agents:** provide independent source review, audit, hypotheses, or
  implementation help. They do not promote support claims or control hardware
  without a separately recorded experiment.

## Mandatory action handshake

Before any payload send, boot, power cycle, device reconnect, PS4-side setting
change, or driver/runtime experiment:

1. The primary LLM creates the next identifier from
   `experiments/SESSIONS.md`, for example `EXP-20260810-001`. If an experiment
   has multiple predeclared operator actions, label them `-A1`, `-A2`, and so
   on; each action gets its own bounded UART session and review.
2. The question, only changed variable, expected evidence, timeout, and
   rollback are written before action.
3. Verify the continuous logger:

   ```sh
   cd /Users/meerzulee/Work/ps4/ps4-uart
   ./uart status
   ```

4. Start the bounded session:

   ```sh
   ./uart session start "EXP-20260810-001 Linux 6.18 XFCE cold boot 1"
   ```

5. Only after the tool confirms the marker is active does the primary LLM say
   **ready for action** and give the operator one exact action.
6. The operator performs it and replies with **action complete** plus observed
   HDMI, LED, fan, input, network, sound, and timing state.
7. Stop and extract:

   ```sh
   ./uart session stop
   ```

8. Read the generated `sessions/*.md` first. Open its sibling raw `.raw` when
   the compact context omits lines, contains corruption, or needs exact timing.
9. Correlate UART with the operator report. Update the session ledger with a
   result, evidence, rollback state, conclusion, and exactly one next action.

The interactive equivalent is:

```sh
./uart session capture "EXP-20260810-001 Linux 6.18 XFCE cold boot 1"
```

Use separate start/stop commands when the primary LLM is coordinating the
operator; use `capture` when one person controls both terminal and console.

## Evidence rules

- Preserve the exact raw slice even when the Markdown context is shortened.
- Treat only a `completed` bounded session as continuity-valid. The UART tool
  records a session as `invalid` if the capture heartbeat is stale, the logger
  restarts, the serial adapter reconnects, or either source file is replaced
  or truncated. Partial raw evidence remains useful for diagnosis but cannot
  prove an acceptance gate.
- Operator observations are evidence and must be quoted as observations, not
  rewritten as UART facts.
- Record absence explicitly: “no HDMI signal after 90 seconds” is useful;
  “didn't work” is not.
- Record first and last relevant UART lines, elapsed time, panic/warning text,
  and whether output stopped or continued.
- Do not infer success from a quiet serial line. Require the experiment's
  positive acceptance criteria.
- Redact private network identifiers or filesystem data before committing raw
  evidence publicly.

## Failure and retry policy

After a failure, choose one:

- inspect more of the same raw log;
- collect a missing operator observation;
- restore the recorded rollback;
- create a new experiment that changes one lower-layer variable;
- mark the branch blocked or inconclusive.

Do not rerun the same payload or power cycle merely hoping for a different
result. A retry must say what changed or what nondeterministic condition it is
measuring. Three identical failures without new evidence end that retry path.

If capture or the controlling terminal dies, run `./uart session status`, then
run `./uart session stop` so the partial slice and continuity failure are
preserved. Use `session abort --reason "why this operator action never began"`
only when no hardware action occurred. The abort is indexed and its bounded
raw, event, and context artifacts are still preserved. Also record the reason
in the curated ledger.

Local source review, builds, documentation, and attaching media to the Mac for
read-only inspection do not require a PS4 UART marker. A PS4-side reconnect,
payload, boot, power cycle, device insertion, or configuration change always
does.

## Repository boundaries

| Repository | Owns | Does not own |
|---|---|---|
| [`meerzulee/linux-ps4`](https://github.com/meerzulee/linux-ps4) (local checkout: `linux-ps4-kernel`) | kernel patches, config, modules, reproducible kernel builds, patch provenance | desktop UX and distribution policy |
| [`meerzulee/omarchy-ps4`](https://github.com/meerzulee/omarchy-ps4) | rootfs, XFCE baseline, compatibility ladder, install/recovery UX, experiments | vendored kernel history or opaque payload binaries |
| `ps4-uart` | continuous capture, bounded session extraction, local session index | compatibility decisions |

`omarchy-ps4` is public with `master` as its default branch. Private build
outputs, payload inputs, credentials and raw UART evidence remain local unless
they pass a deliberate publication audit.

## Delegated-agent policy

Additional Claude, Codex, or other agents may be launched in isolated Herdr
tabs for bounded tasks. Full-workspace permission modes may be used when the
owner requests them, but the assignment must name its directories, expected
output, and forbidden external actions. Prefer read-only independent audits
for uncertain kernel, loader, storage, or licensing conclusions.

Every delegated result is recorded as one of:

- accepted after primary verification;
- useful hypothesis awaiting hardware evidence;
- rejected with reason;
- unresolved disagreement requiring another source or experiment.

This keeps parallel advice from silently changing the project state.
