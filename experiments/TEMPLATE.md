# Experiment: ID

## Session control

- Ledger ID: `EXP-YYYYMMDD-NNN`
- State: `planned`, `capturing`, `awaiting review`, or `closed`
- Continuous UART status checked:
- Bounded UART label:
- Raw UART slice:
- Compact UART context:
- Operator action-complete report:

## Question

State the single compatibility question this experiment answers.

## Changed variable

Record the one difference from the known-good XFCE baseline.

## Environment

- Console model:
- Southbridge:
- Firmware and homebrew loader:
- Kernel release and commit:
- Rootfs/build manifest:
- Package versions:

## Acceptance criteria

- [ ] Define an observable success condition before testing.
- [ ] Define the timeout or stability duration.
- [ ] Define the required cold-boot and XFCE regression checks.

## Procedure

List the exact commands and physical actions in order.

## Result

Choose one: `pass`, `degraded`, `fail`, `inconclusive`, or `blocked`.

Describe what was observed and link the minimal supporting evidence.

Record the primary LLM conclusion and any delegated-agent findings separately.
Agent consensus is not a substitute for hardware evidence.

## Rollback

Record how the known-good XFCE state was restored and verified.

## Compatibility decision

Record the corresponding ledger change, limitation, or next lower-layer test.

## Next action

Record exactly one next experiment or an explicit stop condition. A retry must
name the new evidence or changed variable that makes it different.
