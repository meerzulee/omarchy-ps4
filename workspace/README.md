# PS4 Linux development workspace

This file is installed at the workspace root by `scripts/setup-workspace`;
relative links refer to that installed location. The workspace contains
separate repositories. With Git and Python 3 available, start from the distribution:

```sh
mkdir -p "$HOME/Work/ps4"
cd "$HOME/Work/ps4"
git clone https://github.com/meerzulee/omarchy-ps4.git
cd omarchy-ps4
./scripts/setup-workspace
```

The setup helper clones pinned kernel and UART revisions beside Omarchy and
creates the workspace README/AGENTS files. Existing repositories are verified;
their branches and local edits are preserved. Existing workspace instructions
are also preserved. Use `./scripts/setup-workspace --check` for an offline,
read-only check.

## Project map

| Directory | Responsibility | Source |
| --- | --- | --- |
| `linux-ps4-kernel/` | PS4 patch series, kernel configs, builds and provenance | https://github.com/meerzulee/linux-ps4 |
| `omarchy-ps4/` | Distribution, PS4 manager, provisioning and curated experiments | https://github.com/meerzulee/omarchy-ps4 |
| `ps4-uart/` | Continuous UART capture and bounded sessions | https://github.com/meerzulee/ps4-uart |
| `payloads/`, `backups/`, `lab/` | Locally acquired inputs, recovery and inventory | Created only when required |

The dependency revisions and loader hashes are in
[`omarchy-ps4/manifests/development-sources.json`](omarchy-ps4/manifests/development-sources.json).
Read the workspace [`AGENTS.md`](AGENTS.md) and each repository's instructions.
The experiment source of truth is
[`omarchy-ps4/experiments/SESSIONS.md`](omarchy-ps4/experiments/SESSIONS.md).

## Development hosts

| Work | macOS ARM64 | Arch Linux x86-64 |
| --- | --- | --- |
| Source and host tests | Native tools | Native tools |
| PS4 kernel | OrbStack ARM64 container with an x86-64 cross compiler | Native `make TARGET=6.18-baikal` |
| Distribution packages, initramfs, rootfs and image | Existing OrbStack builders | Use the Mac build host pending a native Linux port |
| UART | macOS discovery or explicit port | Explicit `/dev/serial/by-id/...` port |

Full setup commands and input acquisition are in
[`omarchy-ps4/docs/DEVELOPMENT-HOSTS.md`](omarchy-ps4/docs/DEVELOPMENT-HOSTS.md).
Linux x86 means x86-64; verify `uname -m` reports `x86_64`.

The kernel build downloads its pinned upstream Linux source automatically.
Omarchy upstream comes from `scripts/sync-omarchy-upstream`. Download the
pinned loader only when needed with `scripts/fetch-ps4-loader`; both its ZIP
and ELF are hash-checked. No complete kernel source directory or private source
archive needs to be copied from the previous computer.

## Published artifacts and local state

Kernel release:

https://github.com/meerzulee/linux-ps4/releases/tag/v6.18.44-ps4-baikal-r1

Omarchy manager release:

https://github.com/meerzulee/omarchy-ps4/releases/tag/v0.31-baikal-beta

The Omarchy USB rootfs is not published. Source setup does not flash storage,
install an FPKG or launch a payload. Generated rootfs/modules/boot outputs must
remain a matching, verified set; the old kernel release is not a drop-in
replacement for the current manager's pinned boot set.

Recreate Python virtual environments on each host. Raw UART logs, active
capture state, personal keys and recovery copies remain local. GitHub source
availability does not constitute hardware acceptance.
