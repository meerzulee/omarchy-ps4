# Private boot-capable FPKG

This is a private development package for the lab console. It is not an
installer and must not be published.

The package embeds exactly PS4 Linux Loader v25 `linux-1024mb.elf`, 320,936
bytes, SHA-256
`c813d169ef37e4bee574a5058bc6c0b92564e74ab445ef0846d67fa9d1e5ce65`.
After the user chooses **Boot Omarchy**, the app immediately
checks the embedded file's exact size and SHA-256, opens one connection to the
GoldHEN loopback PayLoader at `127.0.0.1:9090`, and sends the ELF with exactly
one application write after proving the socket send buffer can queue all
320,936 bytes. A short write is terminal and is never retried on that
connection.

It does not contain or write a kernel, initramfs, root filesystem or package
snapshot. It does not format or select a disk. The already-prepared legacy
external `PS4BOOT` files and `OMARCHY-PS4` Linux root remain separate and must
pass their own preflight. A failed loader check or local connection leaves
Orbis running and shows an error.

This v0.14 package predates the schema-2 architecture. Private v0.25 proved the
four-file transaction under `/data/linux/boot`, but its loopback multi-write
handoff let GoldHEN treat the first 51,200 bytes as a complete ELF. Private
v0.26 retained the accepted staging path and proved a safe whole-ELF send
buffer plus one write on hardware. v0.28 retains that accepted handoff,
restores `keep_bootcon 8250.nr_uarts=0` to the internal-root boot profile and
removes the duplicate install/kernel/launch review screens. USB verification
and first-owner lifecycle evidence remain on Baikal UART. The complete v0.28
boot remains pending a bounded hardware retest.

The loader repository does not declare an overall license. Its vendored
provenance therefore marks redistribution `private-test-only`; this build must
not be attached to a public release.
