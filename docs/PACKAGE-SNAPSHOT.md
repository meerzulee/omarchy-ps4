# Controlled developer package snapshot

The gift developer image installs from one coherent offline package repository.
It does not resolve against the latest Arch or Omarchy repositories during
installation.

Build it with OrbStack:

```bash
./scripts/build-package-snapshot
```

Downloads are retained in `output/package-snapshot-cache/` after an interrupted
developer build so a retry can resume the same pinned transaction.
After resolution, the builder removes cached package versions not selected by
the transaction lock before generating the repository database. A resumed
cache therefore cannot silently add a newer or older duplicate package to the
release snapshot. The repository database is regenerated from those exact
files on every build; matching package counts are not treated as matching
transactions.
The builder refuses to overwrite an existing final snapshot. Creating a new
package set is therefore an explicit release action, not an automatic update.

The builder combines the accepted XFCE recovery profile with the PS4-safe
Omarchy workstation profile, resolves the complete transaction against the
Arch Linux Archive snapshot dated `2026/08/20`, the Omarchy 4.0 stable package
repository, and the three locally-built Omarchy PS4 packages. It downloads
every package byte into one repository and records:

- the direct package request;
- the resolved package/version/repository/URL transaction;
- every package filename, size, and SHA-256;
- the source snapshot and Omarchy commit;
- a repository database usable without networking.

The final build gate starts a fresh Arch container with networking disabled and
requires its dependency resolution to reproduce the locked transaction using
only the generated repository. A second network-disabled container installs
the complete profile, compares all installed package versions with the lock,
checks required recovery/Omarchy commands, and rejects forbidden packages.
It also resolves every dynamic relocation in the Quickshell executable. This
catches an Omarchy package rebuilt against a newer Qt ABI even when Pacman can
otherwise satisfy its unversioned dependency declaration.

The build fails if any forbidden storage, generic-kernel, bootloader, snapshot,
or SDDM package appears through a transitive dependency. Normal `linux`,
modules, firmware selection, initramfs, and PS4 loader artifacts remain owned
by the separate `linux-ps4-kernel` release and must be matched in the final
release manifest.

This is a private developer snapshot. Package and repository signatures must
be replaced by the permanent Omarchy PS4 signing-key policy before public
publication. Its generated Pacman configuration deliberately uses
`SigLevel = Never` so an unknown upstream signing key cannot trigger a network
lookup during an offline install; integrity is instead enforced by the locked
filenames, sizes, and `SHA256SUMS`. This policy is not acceptable for a public
release. Root administrators can opt into an unmanaged development mode, but
the default image must not contain live upstream mirrors or automatic updates.
