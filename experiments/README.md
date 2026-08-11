# Hardware experiments

Each compatibility claim begins as an experiment directory. Run:

```bash
./bin/omarchy-ps4-probe --experiment egl-baseline
```

The probe creates a timestamped directory containing a command index, a short
README, and raw diagnostic output. Raw output is ignored by Git because it can
contain network addresses and filesystem identifiers. Review it before sharing.

Before any PS4-side action, follow `docs/DEVELOPMENT-MODE.md` and open a bounded
UART session with the same stable experiment ID. `SESSIONS.md` is the durable
resume point and permits only one active hardware experiment at a time.

Copy `TEMPLATE.md` into the experiment directory and complete it after the
test. Commit the curated decision, relevant redacted evidence, and any small
reproduction files—not an indiscriminate dump of the machine.

Compare the check-level results from two runs with:

```bash
./bin/omarchy-ps4-compare experiments/RUN-A experiments/RUN-B
```
