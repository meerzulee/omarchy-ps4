# Development on macOS ARM64 and Linux x86-64

These instructions describe the current source and build paths. Linux x86
means x86-64, including the owner's Arch PC; check `uname -m` for `x86_64`.
The PS4 target is also x86-64. The development computer's CPU does not change
the console architecture.

## What can run where

| Task | Apple Silicon Mac | Arch x86-64 PC |
| --- | --- | --- |
| Source, docs, Python and C++ host checks | Native | Native |
| Kernel build | OrbStack helper, ARM64 container, x86-64 cross compiler | Native kernel `make` path |
| Omarchy package/snapshot/rootfs builds | OrbStack wrappers | Wrappers currently require OrbStack; use the Mac build host |
| Initramfs and whole-device USB image | OrbStack wrappers/VM | Native Linux port remains to be implemented and qualified |
| OpenOrbis FPKG application | Existing native macOS path | Linux path is present; not yet verified on this PC |
| UART | macOS auto-detection or explicit port | Explicit Linux serial port; real adapter capture is unverified here |

OrbStack remains the only authorized local container/VM runtime. Native Linux
compilation needs neither. Keep the full image build on the Mac initially;
porting the wrappers is a separate task, not a Docker-context workaround.

## Start from GitHub

Keep the repositories next to each other:

```text
ps4/
  linux-ps4-kernel/   # GitHub repository name: linux-ps4
  omarchy-ps4/
  ps4-uart/
  payloads/          # selected local inputs, when needed
  backups/           # local recovery/handoff data
```

Clone the distribution repository, then let its setup helper obtain the exact
kernel and UART revisions recorded in
[`manifests/development-sources.json`](../manifests/development-sources.json):

Git and Python 3 must be available first (`sudo pacman -Syu --needed git python`
on Arch, or `brew install git python` on a Mac with Homebrew). The full host
tool lists follow below.

```sh
mkdir -p "$HOME/Work/ps4"
cd "$HOME/Work/ps4"
git clone https://github.com/meerzulee/omarchy-ps4.git
cd omarchy-ps4
./scripts/setup-workspace
./scripts/setup-workspace --check
```

The helper creates missing sibling clones at their pinned commits and copies
the workspace README/AGENTS templates. It verifies existing repositories'
origins and that their current history contains the pinned revision; it never
switches, merges or resets them. A mismatched or older existing checkout stops
setup with a clear error. Local edits and customized workspace instructions
are preserved. `--check` uses no network and makes no changes.

Every active repository has its own `AGENTS.md`. Read those and the workspace
rules. No fixed `/Users/...` path or private source archive is required.

## Where each dependency comes from

| Input | Recorded source and pin | Acquisition |
| --- | --- | --- |
| PS4 kernel patches/configs | `meerzulee/linux-ps4`, development branch and full commit in `manifests/development-sources.json` | `scripts/setup-workspace` creates `../linux-ps4-kernel/` |
| Upstream Linux source | `gregkh/linux`, tag and `BASE_COMMIT` in kernel `targets/6.18-baikal.env` | Downloaded and commit-checked by the kernel build; stored in generated `src/` |
| UART tool | `meerzulee/ps4-uart`, merged bounded-session/diagnostics revision in the development manifest | `scripts/setup-workspace` creates `../ps4-uart/` |
| Omarchy Quattro source | `basecamp/omarchy`, full commit in `upstream/omarchy.lock` | `scripts/sync-omarchy-upstream` |
| Arch and Omarchy packages | Pinned Arch archive date, image digest and Omarchy package commit in the build scripts/lock | Package/snapshot builders download and lock the offline closure |
| PS4 Linux Loader v25 | Official upstream GitHub ZIP; ZIP and ELF hashes in the development manifest | `scripts/fetch-ps4-loader`, then `fpkg/tools/vendor-loader` |
| OpenOrbis toolchain | Official `v0.5.4` archive and SHA-256 in `fpkg/tools/build-ui-prototype` | FPKG wrapper downloads and verifies it on first use |
| Firmware initramfs seed | Kernel checkout's historical `checkpoint/initramfs/initramfs-v26-with-edid.cpio.gz` | Present in the pinned kernel clone; an alternate recorded seed can use `PS4_SOURCE_INITRAMFS` |
| Kernel and modules | Exact target/config/compiler from the kernel checkout | Build together; do not mix the old public kernel r1 with the current FPKG's boot pins |
| Omarchy USB rootfs | Source recipes and package snapshot; no public rootfs asset | Build on the existing OrbStack host or transfer an accepted local image privately |
| Raw UART evidence, personal keys and recovery archives | Local operator state | Private transfer only when needed; not part of source setup |

Repositories and upstream releases:

https://github.com/meerzulee/linux-ps4

https://github.com/meerzulee/ps4-uart

https://github.com/basecamp/omarchy

https://github.com/ps4-linux/ps4-linux-loader/releases/tag/v25

https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain/releases/tag/v0.5.4

For FPKG work, acquire the small loader input separately from its official
release. This only downloads a local file and does not operate the console:

```sh
./scripts/fetch-ps4-loader
./fpkg/tools/vendor-loader
```

The download helper verifies the pinned ZIP SHA-256, extracts only the named
1024 MB ELF, checks its size and SHA-256, and refuses to replace a different
existing loader. Its destination is
`../payloads/ps4-linux-loader/v25/elf/linux-1024mb.elf`. Runtime firmware and
generated images are not new source commits. Continue the full build with
[`BUILDING.md`](BUILDING.md) after the required host and inputs are available.

## macOS ARM64

Install Apple's command-line developer tools if they are missing:

```sh
xcode-select --install
```

With Homebrew available, install the host tools:

```sh
brew install git bash python coreutils zstd xz ripgrep imagemagick llvm lld@20
```

Use a shell whose PATH finds the Homebrew tools. The FPKG wrapper locates
LLVM and `lld@20` through `brew --prefix`; the kernel compiler lives inside
the OrbStack container rather than on Darwin.

Install/start OrbStack, then verify the engine before Docker work:

```sh
orb status
# Required: Running
docker context show
# Required: orbstack
docker info >/dev/null
```

If a different context is selected, select the existing OrbStack context:

```sh
docker context use orbstack
```

Build the PS4 kernel from the workspace:

```sh
cd "$HOME/Work/ps4/linux-ps4-kernel"
./scripts/build-kernel-orbstack --target 6.18-baikal
```

The helper explicitly uses `linux/arm64`, `CROSS_COMPILE=x86_64-linux-gnu-`
and `KERNEL_ARCH=x86_64`. Continue the distribution build using
[`BUILDING.md`](BUILDING.md), after transferring or reconstructing its exact
local inputs. Do not run the kernel's native `make` path directly on macOS.

## Arch Linux x86-64

Install native source, test and kernel-build dependencies. This command also
updates the Arch host; it does not install the PS4 kernel on the PC:

```sh
uname -m
# Required: x86_64
sudo pacman -Syu --needed base-devel git curl bc cpio pahole libelf openssl \
  kmod perl python python-pip rsync xz zstd ripgrep clang lld imagemagick
```

Some wrappers call `shasum`, provided by Arch's Perl package. Ensure its
directory is available in the shell:

```sh
export PATH="/usr/bin/core_perl:$PATH"
command -v shasum
```

Compile a native PS4 kernel:

```sh
cd "$HOME/Work/ps4/linux-ps4-kernel"
make TARGET=6.18-baikal
```

The builder fetches the pinned upstream source and writes to
`output/6.18-baikal/`; it never installs that kernel as the PC's own kernel.
Use a fresh checkout/output location to preserve accepted artifacts. A rolling
Arch compiler is not the pinned OrbStack compiler, so treat its output as a
new candidate with its own manifest and matching modules.

For source changes and local checks in Omarchy:

```sh
cd "$HOME/Work/ps4/omarchy-ps4"
./tests/development-setup-test
./tests/gift-rootfs-contract-test
make -C fpkg/ui-prototype host-test
```

The full-profile check additionally needs the pinned upstream source:

```sh
./scripts/sync-omarchy-upstream
./tests/full-profile-test
```

These commands also work with the Mac's host tools. They do not boot a PS4
or prove physical hardware compatibility. The OpenOrbis wrapper has a Linux
compiler/tool path, but complete FPKG packaging still needs its pinned assets
and a separate Linux validation run. Do not claim it is qualified from this
documentation alone.

## UART on either computer

Use the manifest-pinned UART checkout, which includes bounded sessions and
serial failure diagnostics. Recreate its environment instead of copying the
Mac `.venv`:

```sh
cd "$HOME/Work/ps4/ps4-uart"
python3 -m venv .venv
.venv/bin/python -m pip install -r requirements.txt
.venv/bin/python -m unittest discover -s tests
```

The current auto-detection patterns are macOS-specific. When ready for a
console session on Linux, list adapters and pass the actual stable path:

```sh
ls -l /dev/serial/by-id/
# Replace the path below with the listed adapter.
./uart start --port /dev/serial/by-id/YOUR_ADAPTER
./uart status
```

On macOS, use `./uart start` or select the actual `/dev/cu.*` port explicitly.
If Linux denies serial access, inspect the adapter's owning group and grant
the user access to that group, then log in again. Do not run the logger as
root merely to bypass permissions.

Do not migrate UART PID files, locks, active-session markers or port pointers.
Privately copied completed evidence remains historical evidence. A device
move creates a new connection and cannot continue an old bounded session.
Before consequential console work, confirm logger readiness and follow
[`DEVELOPMENT-MODE.md`](DEVELOPMENT-MODE.md).

## Local state and next work

The GitHub setup supplies the development sources. Downloadable inputs should
come from the source map above; generated caches and a full kernel source tree
do not need copying. Raw sessions, personal keys, known-good built images and
recovery archives may still need a private transfer. Preserve the quarantined
initramfs and its record in the old lab; never substitute it for an accepted
seed. Neither source setup nor successful compilation is hardware acceptance.

Recommended order after restoring the source:

1. Run `scripts/setup-workspace --check`; read each `AGENTS.md`.
2. Run native host checks and prepare a kernel candidate on Arch.
3. Recreate UART's environment and run its software tests before connecting an adapter.
4. Keep full images on the existing Mac host until native Linux build support
   is implemented and checked.
5. Resume console work only from the latest experiment ledger and current
   operator observations. Old checkpoint text is not a live console status.

Official host-tool references:

https://docs.orbstack.dev/docker/

https://archlinux.org/packages/core/any/base-devel/

https://archlinux.org/packages/extra/x86_64/pahole/

https://archlinux.org/packages/core/x86_64/perl/files/

https://formulae.brew.sh/formula/lld%4020
