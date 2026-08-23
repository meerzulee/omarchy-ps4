# Owner provisioning package

This package installs the PS4-specific automatic root-expansion program,
first-boot owner program and their disabled-by-default systemd services.
Installing the package does not arm either flow.

An image builder arms it only after confirming the release image has no
default user or password. For an already installed development root, mount the
USB filesystem from another Linux environment and use the guarded preparation
command:

```bash
sudo omarchy-ps4-prepare-for-owner --check /mnt
sudo omarchy-ps4-prepare-for-owner /mnt
```

On a terminal, the second command shows the Omarchy confirmation screen. An
image pipeline can use the explicit non-interactive form instead:

```bash
sudo omarchy-ps4-prepare-for-owner \
  --confirm PREPARE-FOR-ANOTHER-OWNER /mnt
```

It refuses `/`, non-USB filesystems, the wrong label, and any existing human
account other than the known `ps4` development account. Preparation removes
that account, development sudo/SSH access, LightDM autologin, cloned machine
identity, and SSH host keys before arming storage expansion followed by owner
setup.

An image builder may stage validated public keys at
`/var/lib/omarchy-ps4/provisioning/authorized_keys`. Owner setup installs them
for the newly created user and enables OpenSSH with password, keyboard-
interactive, and root login disabled. The staged file is removed after a
successful handoff. Public release images must not contain a maintainer's
personal key. Without a staged unattended key, first-owner setup leaves SSH
disabled and never requires network access. After the desktop starts, the
owner can use Omarchy's normal security setup to configure SSH.

Release images use one ext4 filesystem over the whole USB rather than a
partition table. Before owner setup, `omarchy-ps4-grow-root` proves that the
running root has the recorded whole-device layout, exact label, ext4 type and
USB ancestry. It then grows ext4 online to the device size and records the
verified result. It never edits a partition table or accepts a device argument.

The program refuses any root that is not labelled `OMARCHY-PS4` and reached
through USB. It leaves `pending` in place after an error so setup can resume.
Before removing that marker it runs an offline PS4-owned user finalizer that
creates the Tokyo Night theme/background state, XDG directories, bookmarks,
application launchers, default browser associations, skill links, migration
markers, and the default keyring. It does not run upstream Mise downloads or
enable unaudited user services.
LightDM requires this owner unit and is ordered after it. The owner unit keeps
control of tty1 even when storage expansion or setup fails. Its clean terminal
surface centers the pinned green Omarchy ASCII logo and every interactive
prompt; raw service errors go to the journal instead of being painted through
the form. Timezone selection uses separate region and location lists instead
of a live filter that repaints unreliably on the Linux virtual console. The
final review and confirmation are centered; Yes remains Omarchy green and No
remains neutral gray. A branded `OWNER-SETUP` support screen replaces an empty
login prompt on failure. UART receives only lifecycle stages and storage
evidence; usernames, passwords and prompt input are never mirrored to it.

After successful setup, the provisioner creates the PAM-required system
`autologin` group when absent and adds the owner to it. LightDM uses a
PS4-owned PAM service that admits only that group, plus an explicit per-owner
Omarchy session record, to persistently enter the desktop. The normal LightDM
password stack, `sudo`, and screen locking remain unchanged and still require
the password,
but the current unencrypted gift has no boot-time authentication boundary.
Anyone with physical access to the console or removable USB can reach the
desktop. A future accepted LUKS unlock flow may provide that boundary before
automatic desktop login.
It does not touch the PS4 loader, kernel, initramfs, internal disk, LUKS,
Limine, SDDM, Btrfs, or any partition table.
