# Native application boundary

`manager_state.*` is the platform-neutral protocol model. The host preview and
self-test exercise it today; a later OpenOrbis front end should render the same
states and provide these reviewed adapters:

- controller input and 1920×1080 framebuffer rendering;
- HTTPS Range downloads with ETag persistence;
- Ed25519 manifest-signature and SHA-256 artifact verification;
- atomic boot-set staging with last-known-good rollback;
- loopback PayLoader transport that proves the complete ELF fits its socket
  send buffer, then performs exactly one application write to port 9090;
- redacted diagnostics and exact provenance display.

The native package map for the offline prototype is:

```text
vendor/bundle/boot/*                         -> /app0/bundle/boot/
vendor/bundle/images/omarchy-ps4-rootfs.tar.zst -> /app0/bundle/images/
vendor/payloads/ps4-linux-loader.elf         -> /app0/payloads/
vendor/provenance/*.json                     -> /app0/provenance/
CREDITS.md                                   -> /app0/CREDITS.md
```

No native FPKG is produced yet. `make fpkg` fails intentionally instead of
shipping a shell with unimplemented trust or recovery behavior.
