# Post-install LUKS2 encryption

Status: **local candidate**. Disposable OrbStack conversion passed; PS4 boot,
unlock, interruption recovery and performance are not accepted yet.

## Intended experience

The existing gift remains easy to flash and completes its offline first-owner
setup. The owner may later choose **Encrypt USB**. That action reboots into a
small recovery/initramfs environment because the running root filesystem must
not encrypt itself.

After encryption, the normal boot becomes:

```text
FPKG loader
  -> internal PS4 kernel + cryptsetup-capable initramfs
  -> centered Omarchy unlock screen
  -> LUKS2 USB unlocked
  -> ext4 OMARCHY-PS4 root mounted
  -> automatic owner login
```

The LUKS passphrase is the storage-unlock secret. The Unix account password
still exists for `sudo`, screen locking and recovery. A later UX decision may
let the owner deliberately choose the same value, but the implementation must
not copy or log either secret.

## Local proof

On 2026-08-22 a disposable 256 MiB whole-device ext4 image was tested in the
OrbStack Ubuntu VM with cryptsetup 2.7.0:

1. Create ext4 labelled `OMARCHY-PS4` and write a hashed sentinel file.
2. Unmount, run `e2fsck`, and shrink ext4 from 256 MiB to 160 MiB.
3. Run LUKS2 in-place encryption while reserving 32 MiB for the data shift and
   LUKS metadata.
4. Open the resulting AES-XTS LUKS2 mapping with its Argon2id keyslot.
5. Run read-only `e2fsck`, mount read-only, and verify the filesystem label and
   sentinel SHA-256.

The final label and sentinel digest matched. The first local attempt stopped
before formatting because its loop-device guard parsed headerless `losetup`
output incorrectly. A second conversion completed but OrbStack did not create
the usual mapper node until `dmsetup mknodes` was called. The corrected third
run passed. These were disposable VM images; no physical USB was touched.

Cryptsetup documents the supported in-place form as `reencrypt --encrypt
--type luks2 --reduce-device-size ...`. It also requires unused space at the
end of the plaintext device and a reliable backup:
<https://gitlab.com/cryptsetup/cryptsetup/-/blob/9d38ea70e2b11ba8208a7038b0d5223e4d1a62e0/man/cryptsetup-reencrypt.8.adoc>.

## Product safety requirements

- Never convert the mounted or currently running Omarchy root.
- Require a verified backup and clean offline `e2fsck` before shrinking.
- Resolve the exact USB by recorded serial, USB ancestry and filesystem label;
  never accept a device path supplied by the user or FPKG.
- Verify the shrunken filesystem ends before the space reserved for LUKS2.
- Back up the LUKS2 header somewhere other than the encrypted USB.
- Keep passwords, key material and prompt input out of UART, logs and process
  arguments.
- Treat power loss, USB disconnect and bad-passphrase recovery as mandatory
  tests. Cryptsetup can resume LUKS2 reencryption, but that is not a substitute
  for proving our exact recovery UX.
- Stage and verify the cryptsetup-capable boot set before committing the USB
  conversion. Both current and fallback boot sets must understand the new
  encrypted root or a separate recovery path must remain available.
- The current unencrypted gift intentionally uses permanent desktop auto-login
  for console convenience. Document clearly that it has no boot-time
  authentication boundary; an accepted LUKS unlock would add one before the
  same automatic desktop login.

## Remaining implementation gates

1. Audit the PS4 kernel config for device mapper, dm-crypt and required crypto
   algorithms, built in early enough for initramfs use.
2. Add pinned cryptsetup/device-mapper binaries and their libraries to the
   custom initramfs without importing a PC boot stack.
3. Replace the current root lookup with: find the exact outer LUKS UUID, show a
   centered local-keyboard unlock prompt, open the mapping, then verify the
   inner `OMARCHY-PS4` ext4 root and USB ancestry.
4. Build an offline recovery action that performs the guarded shrink,
   conversion, verification and resumable rollback flow.
5. Test the complete conversion and unlock path on disposable PS4 USB media in
   bounded UART experiments before offering it to an existing owner.

Until those gates pass, encryption is an experimental recovery action, not a
default gift-image feature.
