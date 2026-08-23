#define _XOPEN_SOURCE 700

#include "private_boot.hpp"

#include "sha256.hpp"

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef OMARCHY_PRIVATE_BOOT
#include <orbis/libkernel.h>
#endif

namespace omarchy_ps4 {
namespace {

#ifndef OMARCHY_APP_MISC_PREFIX
#define OMARCHY_APP_MISC_PREFIX "/app0/assets/misc"
#endif

constexpr const char* kLoaderPath =
    OMARCHY_APP_MISC_PREFIX "/ps4-linux-loader.elf";
constexpr size_t kLoaderSize = 320936;
// GoldHEN's in-console loopback PayLoader can treat the first receive burst as
// the complete payload. Keep the entire ELF in the client send queue before
// the first write; never fall back to a multi-write stream.
constexpr int kLoaderSendBufferSize = 1024 * 1024;
constexpr uint8_t kLoaderDigest[32] = {
    0xc8, 0x13, 0xd1, 0x69, 0xef, 0x37, 0xe4, 0xbe,
    0xe5, 0x74, 0xa5, 0x05, 0x8b, 0xc6, 0xc0, 0xb9,
    0x25, 0x64, 0xe7, 0x4a, 0xb4, 0x45, 0xef, 0x08,
    0x46, 0xd6, 0x7f, 0xa9, 0xd1, 0xe5, 0xce, 0x65,
};

#ifdef OMARCHY_INTERNAL_BOOT
#ifndef OMARCHY_BOOT_PARENT_PATH
#define OMARCHY_BOOT_PARENT_PATH "/data/linux"
#endif

constexpr const char* kBootParent = OMARCHY_BOOT_PARENT_PATH;
constexpr const char* kBootDirectory = OMARCHY_BOOT_PARENT_PATH "/boot";
constexpr const char* kStagingDirectory =
    OMARCHY_BOOT_PARENT_PATH "/boot.omarchy-new";
constexpr const char* kPreviousDirectory =
    OMARCHY_BOOT_PARENT_PATH "/boot.omarchy-prev";
constexpr const char* kTransactionPath =
    OMARCHY_BOOT_PARENT_PATH "/.omarchy-ps4-staging";

struct BootArtifact {
  const char* source_path;
  const char* active_name;
  size_t size;
  uint8_t digest[32];
};

#ifdef OMARCHY_ULTRAWIDE_BOOT
constexpr BootArtifact kBootArtifacts[] = {
    {OMARCHY_APP_MISC_PREFIX "/bzImage", "bzImage", 11244544,
     {0x9d, 0x0f, 0xe9, 0x17, 0x71, 0xee, 0xa8, 0xe2,
      0xe6, 0x96, 0x9c, 0xe4, 0x64, 0x17, 0xbc, 0x8e,
      0x34, 0x97, 0xdc, 0x8c, 0xce, 0xc3, 0x83, 0x82,
      0x6e, 0xdb, 0x11, 0x60, 0xf2, 0xf0, 0xb2, 0x70}},
    {OMARCHY_APP_MISC_PREFIX "/initramfs.cpio.gz", "initramfs.cpio.gz", 1686552,
     {0x84, 0x1b, 0x7a, 0x1b, 0x59, 0xad, 0x0c, 0x53,
      0xd9, 0x7b, 0xe4, 0x9f, 0xb4, 0x36, 0x9b, 0xa7,
      0x91, 0x81, 0x58, 0xdf, 0x0f, 0xc5, 0x57, 0xf9,
      0x62, 0x0f, 0xd3, 0xbd, 0xdd, 0xdb, 0x15, 0xef}},
    {OMARCHY_APP_MISC_PREFIX "/bootargs.txt", "bootargs.txt", 465,
     {0x44, 0x5b, 0x95, 0x84, 0xdb, 0x98, 0x15, 0xc7,
      0x93, 0x57, 0x61, 0x93, 0xd1, 0xf7, 0xaf, 0xc3,
      0x3e, 0x99, 0xe0, 0x21, 0x15, 0x93, 0x83, 0x96,
      0xee, 0x19, 0xc5, 0xea, 0x23, 0xc5, 0x29, 0x2f}},
    {OMARCHY_APP_MISC_PREFIX "/vram.txt", "vram.txt", 5,
     {0x4f, 0x71, 0xbb, 0x76, 0x1a, 0xce, 0x37, 0xc8,
      0x88, 0x26, 0xcd, 0x8c, 0xc1, 0xc9, 0x48, 0xe1,
      0xcf, 0x5b, 0x5d, 0x0c, 0xd1, 0x53, 0xdc, 0x65,
      0x1a, 0x6e, 0xfd, 0xb3, 0xdf, 0xb9, 0xf2, 0xb1}},
};
#else
constexpr BootArtifact kBootArtifacts[] = {
    {OMARCHY_APP_MISC_PREFIX "/bzImage", "bzImage", 11060224,
     {0xb7, 0xc8, 0xb9, 0xd6, 0x7c, 0x60, 0x0e, 0xe0,
      0x8b, 0x23, 0x21, 0xf7, 0xf4, 0xfa, 0xc0, 0x8c,
      0x50, 0x67, 0x91, 0xb0, 0xab, 0x9c, 0x3f, 0x3d,
      0x01, 0x59, 0x8a, 0x90, 0x47, 0x1a, 0x9d, 0xe5}},
    {OMARCHY_APP_MISC_PREFIX "/initramfs.cpio.gz", "initramfs.cpio.gz", 1686508,
     {0x82, 0x45, 0x30, 0xe2, 0x23, 0x92, 0x37, 0x6d,
      0x5f, 0xc2, 0x79, 0x94, 0xa9, 0xcc, 0xff, 0x97,
      0xf0, 0x44, 0x2b, 0x7a, 0x41, 0x68, 0x11, 0x55,
      0xf4, 0x6e, 0x18, 0x3f, 0x89, 0x23, 0x65, 0xae}},
    {OMARCHY_APP_MISC_PREFIX "/bootargs.txt", "bootargs.txt", 502,
     {0x80, 0x64, 0xd9, 0x1f, 0x28, 0x6d, 0x42, 0x75,
      0xda, 0xc0, 0x8e, 0x2f, 0xae, 0x29, 0xe4, 0x3f,
      0xbf, 0x74, 0x5e, 0xa7, 0xbe, 0x15, 0xf7, 0x97,
      0xed, 0xbb, 0xd0, 0xe5, 0x03, 0x6a, 0x49, 0x30}},
    {OMARCHY_APP_MISC_PREFIX "/vram.txt", "vram.txt", 5,
     {0x4f, 0x71, 0xbb, 0x76, 0x1a, 0xce, 0x37, 0xc8,
      0x88, 0x26, 0xcd, 0x8c, 0xc1, 0xc9, 0x48, 0xe1,
      0xcf, 0x5b, 0x5d, 0x0c, 0xd1, 0x53, 0xdc, 0x65,
      0x1a, 0x6e, 0xfd, 0xb3, 0xdf, 0xb9, 0xf2, 0xb1}},
};
#endif

bool path_for(char* output, size_t output_size, const char* directory,
              const char* name) {
  const int written = snprintf(output, output_size, "%s/%s", directory, name);
  return written > 0 && static_cast<size_t>(written) < output_size;
}

// OpenOrbis libc exposes lstat(), but the retail Orbis runtime returns ENOSYS
// for it. Use the native file-status API in the FPKG; host tests retain lstat
// so their symlink-safety coverage remains strict.
int file_status(const char* path, struct stat* information) {
#ifdef OMARCHY_PRIVATE_BOOT
  return sceKernelStat(path,
                       reinterpret_cast<OrbisKernelStat*>(information));
#else
  return lstat(path, information);
#endif
}

bool status_is_missing(int result) {
#ifdef OMARCHY_PRIVATE_BOOT
  return static_cast<uint32_t>(result) == ORBIS_KERNEL_ERROR_ENOENT;
#else
  return result != 0 && errno == ENOENT;
#endif
}

bool file_exists(const char* path) {
  struct stat information;
  return file_status(path, &information) == 0;
}

bool unlink_if_present(const char* path) {
  return unlink(path) == 0 || errno == ENOENT;
}

bool directory_exists(const char* path) {
  struct stat information;
  return file_status(path, &information) == 0 &&
         S_ISDIR(information.st_mode);
}

bool is_boot_artifact_name(const char* name) {
  for (const BootArtifact& artifact : kBootArtifacts) {
    if (strcmp(name, artifact.active_name) == 0) return true;
  }
  return false;
}

bool owned_boot_directory_or_missing(const char* directory) {
  struct stat information;
  const int status_result = file_status(directory, &information);
  if (status_result != 0) return status_is_missing(status_result);
  if (!S_ISDIR(information.st_mode)) return false;

  DIR* stream = opendir(directory);
  if (!stream) return false;
  bool owned = true;
  for (;;) {
    errno = 0;
    dirent* entry = readdir(stream);
    if (!entry) {
      if (errno != 0) owned = false;
      break;
    }
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;
    if (!is_boot_artifact_name(entry->d_name)) {
      owned = false;
      break;
    }
  }
  closedir(stream);
  return owned;
}

// Remove only directories created and wholly owned by this manager. An
// unexpected file makes the transaction stop without deleting user data.
bool remove_owned_boot_directory(const char* directory) {
  if (!owned_boot_directory_or_missing(directory)) return false;
  if (!directory_exists(directory)) return true;

  for (const BootArtifact& artifact : kBootArtifacts) {
    char path[256];
    if (!path_for(path, sizeof(path), directory, artifact.active_name) ||
        !unlink_if_present(path)) {
      return false;
    }
  }
  return rmdir(directory) == 0 || errno == ENOENT;
}

bool verify_file(const char* path, size_t expected_size,
                 const uint8_t expected_digest[32]) {
  struct stat information;
  const int status_result = file_status(path, &information);
  if (status_result != 0) {
    printf("[omarchy-boot] verify path=%s status=stat-failed result=0x%08x "
           "errno=%d\n",
           path, static_cast<uint32_t>(status_result), errno);
    return false;
  }
  if (!S_ISREG(information.st_mode)) {
    printf("[omarchy-boot] verify path=%s status=not-regular mode=%o\n",
           path, static_cast<unsigned int>(information.st_mode));
    return false;
  }
#ifndef OMARCHY_PRIVATE_BOOT
  if (information.st_size != static_cast<off_t>(expected_size)) {
    printf("[omarchy-boot] verify path=%s status=size-mismatch "
           "expected=%zu actual=%lld\n",
           path, expected_size, static_cast<long long>(information.st_size));
    return false;
  }
#else
  // sceKernelStat() is required because Orbis returns ENOSYS for lstat(), but
  // the OpenOrbis struct ABI does not expose a trustworthy st_size here. The
  // streamed byte count and SHA-256 below are the authoritative file checks.
  printf("[omarchy-boot] verify path=%s native-stat=ok mode=%o\n", path,
         static_cast<unsigned int>(information.st_mode));
#endif
  FILE* stream = fopen(path, "rb");
  if (!stream) {
    printf("[omarchy-boot] verify path=%s status=open-failed errno=%d\n",
           path, errno);
    return false;
  }

  Sha256Context context;
  sha256_init(&context);
  uint8_t buffer[64 * 1024];
  size_t total = 0;
  bool read_ok = true;
  for (;;) {
    const size_t count = fread(buffer, 1, sizeof(buffer), stream);
    if (count > 0) {
      sha256_update(&context, buffer, count);
      total += count;
    }
    if (count < sizeof(buffer)) {
      if (ferror(stream) != 0) read_ok = false;
      break;
    }
  }
  if (fclose(stream) != 0) read_ok = false;
  if (!read_ok) {
    printf("[omarchy-boot] verify path=%s status=read-failed bytes=%zu "
           "errno=%d\n",
           path, total, errno);
    return false;
  }
  if (total != expected_size) {
    printf("[omarchy-boot] verify path=%s status=read-size-mismatch "
           "expected=%zu actual=%zu\n",
           path, expected_size, total);
    return false;
  }

  uint8_t digest[32];
  sha256_final(&context, digest);
  if (memcmp(digest, expected_digest, sizeof(digest)) != 0) {
    char actual[65];
    char expected[65];
    for (int index = 0; index < 32; ++index) {
      snprintf(actual + index * 2, 3, "%02x", digest[index]);
      snprintf(expected + index * 2, 3, "%02x", expected_digest[index]);
    }
    actual[64] = '\0';
    expected[64] = '\0';
    printf("[omarchy-boot] verify path=%s status=digest-mismatch "
           "expected=%s actual=%s\n",
           path, expected, actual);
    return false;
  }
  printf("[omarchy-boot] verify path=%s bytes=%zu status=verified\n", path,
         total);
  return true;
}

bool copy_and_flush(const char* source_path, const char* destination_path) {
  FILE* source = fopen(source_path, "rb");
  if (!source) return false;
  FILE* destination = fopen(destination_path, "wb");
  if (!destination) {
    fclose(source);
    return false;
  }

  uint8_t buffer[64 * 1024];
  bool ok = true;
  for (;;) {
    const size_t bytes_read = fread(buffer, 1, sizeof(buffer), source);
    if (bytes_read > 0 &&
        fwrite(buffer, 1, bytes_read, destination) != bytes_read) {
      ok = false;
      break;
    }
    if (bytes_read < sizeof(buffer)) {
      if (ferror(source) != 0) ok = false;
      break;
    }
  }
  if (ok && fflush(destination) != 0) ok = false;
  if (ok && fsync(fileno(destination)) != 0) ok = false;
  if (fclose(destination) != 0) ok = false;
  fclose(source);
  if (ok) chmod(destination_path, 0644);
  return ok;
}

bool all_files_match(const char* directory) {
  if (!directory_exists(directory) ||
      !owned_boot_directory_or_missing(directory)) return false;

  char path[256];
  for (const BootArtifact& artifact : kBootArtifacts) {
    if (!path_for(path, sizeof(path), directory, artifact.active_name) ||
        !verify_file(path, artifact.size, artifact.digest)) {
      return false;
    }
  }
  return true;
}

bool write_transaction_phase(const char* phase) {
  FILE* stream = fopen(kTransactionPath, "wb");
  if (!stream) return false;
  const int written = fprintf(
      stream,
      "schema=1\nrelease=omarchy-ps4-4.0.0-baikal-b1-beta1\nphase=%s\n",
      phase);
  bool ok = written > 0;
  if (ok && fflush(stream) != 0) ok = false;
  if (ok && fsync(fileno(stream)) != 0) ok = false;
  if (fclose(stream) != 0) ok = false;
  if (ok) chmod(kTransactionPath, 0600);
  return ok;
}

enum class TransactionPhase { Invalid, Staging, Activating, Promoting };

TransactionPhase read_transaction_phase() {
  FILE* stream = fopen(kTransactionPath, "rb");
  if (!stream) return TransactionPhase::Invalid;
  char contents[192] = {};
  const size_t count = fread(contents, 1, sizeof(contents) - 1, stream);
  const bool ok = ferror(stream) == 0;
  fclose(stream);
  if (!ok || count == 0) return TransactionPhase::Invalid;
  if (strstr(contents, "phase=staging\n")) return TransactionPhase::Staging;
  if (strstr(contents, "phase=activating\n"))
    return TransactionPhase::Activating;
  if (strstr(contents, "phase=promoting\n"))
    return TransactionPhase::Promoting;
  return TransactionPhase::Invalid;
}

bool recover_interrupted_stage() {
  if (!file_exists(kTransactionPath)) return true;
  const TransactionPhase phase = read_transaction_phase();
  if (phase == TransactionPhase::Invalid) return false;

  if (all_files_match(kBootDirectory)) {
    if (!remove_owned_boot_directory(kStagingDirectory)) return false;
    sync();
    return unlink_if_present(kTransactionPath);
  }

  if (phase == TransactionPhase::Promoting) {
    if (directory_exists(kPreviousDirectory)) {
      if (directory_exists(kBootDirectory) &&
          !remove_owned_boot_directory(kBootDirectory)) {
        return false;
      }
      if (rename(kPreviousDirectory, kBootDirectory) != 0) return false;
    }
  }

  if (!remove_owned_boot_directory(kStagingDirectory)) return false;
  sync();
  return unlink_if_present(kTransactionPath);
}
#endif

}  // namespace

BootSendResult stage_internal_boot_set() {
#ifndef OMARCHY_INTERNAL_BOOT
  return BootSendResult::Ok;
#else
  printf("[omarchy-boot] stage begin release=4.0.0 kernel=6.18.44-baikal\n");
  for (const BootArtifact& artifact : kBootArtifacts) {
    if (!verify_file(artifact.source_path, artifact.size, artifact.digest)) {
      return BootSendResult::StageVerifyFailed;
    }
  }
  printf("[omarchy-boot] stage embedded-artifacts=verified count=%zu\n",
         sizeof(kBootArtifacts) / sizeof(kBootArtifacts[0]));

  if (mkdir(kBootParent, 0755) != 0 && errno != EEXIST) {
    return BootSendResult::StageDirectoryFailed;
  }
  if (!directory_exists(kBootParent)) {
    return BootSendResult::StageDirectoryFailed;
  }
  if (!recover_interrupted_stage()) {
    return BootSendResult::StageRecoveryFailed;
  }
  printf("[omarchy-boot] stage interrupted-transaction=recovered-or-absent\n");
  if (!owned_boot_directory_or_missing(kBootDirectory)) {
    return BootSendResult::StageRecoveryFailed;
  }
  if (all_files_match(kBootDirectory)) {
    printf("[omarchy-boot] stage current-set=already-verified action=no-op\n");
    return BootSendResult::Ok;
  }
  if (!remove_owned_boot_directory(kStagingDirectory) ||
      mkdir(kStagingDirectory, 0755) != 0) {
    return BootSendResult::StageDirectoryFailed;
  }
  if (!write_transaction_phase("staging"))
    return BootSendResult::StageWriteFailed;

  for (const BootArtifact& artifact : kBootArtifacts) {
    char staged[256];
    if (!path_for(staged, sizeof(staged), kStagingDirectory,
                  artifact.active_name) ||
        !copy_and_flush(artifact.source_path, staged)) {
      return BootSendResult::StageWriteFailed;
    }
    if (!verify_file(staged, artifact.size, artifact.digest)) {
      return BootSendResult::StageVerifyFailed;
    }
    printf("[omarchy-boot] stage file=%s bytes=%zu status=verified\n",
           artifact.active_name, artifact.size);
  }

  if (!all_files_match(kStagingDirectory))
    return BootSendResult::StageVerifyFailed;
  if (!write_transaction_phase("activating"))
    return BootSendResult::StageWriteFailed;
  if (!remove_owned_boot_directory(kPreviousDirectory))
    return BootSendResult::StageActivateFailed;
  if (!write_transaction_phase("promoting"))
    return BootSendResult::StageWriteFailed;
  if (directory_exists(kBootDirectory) &&
      rename(kBootDirectory, kPreviousDirectory) != 0) {
    return BootSendResult::StageActivateFailed;
  }
  if (rename(kStagingDirectory, kBootDirectory) != 0)
    return BootSendResult::StageActivateFailed;
  sync();
  printf("[omarchy-boot] stage activation=current previous=retained\n");

  if (!all_files_match(kBootDirectory))
    return BootSendResult::StageVerifyFailed;
  if (!unlink_if_present(kTransactionPath)) {
    return BootSendResult::StageActivateFailed;
  }
  sync();
  printf("[omarchy-boot] stage complete status=ready\n");
  return BootSendResult::Ok;
#endif
}

InternalBootState inspect_internal_boot_set() {
#ifndef OMARCHY_INTERNAL_BOOT
  return InternalBootState::Missing;
#else
  if (file_exists(kTransactionPath)) return InternalBootState::Interrupted;
  if (!directory_exists(kBootDirectory)) return InternalBootState::Missing;
  if (!owned_boot_directory_or_missing(kBootDirectory))
    return InternalBootState::Blocked;
  if (all_files_match(kBootDirectory)) return InternalBootState::Ready;
  return InternalBootState::UpdateAvailable;
#endif
}

const char* internal_boot_state_name(InternalBootState state) {
  switch (state) {
    case InternalBootState::Missing: return "missing";
    case InternalBootState::Ready: return "ready";
    case InternalBootState::UpdateAvailable: return "update-available";
    case InternalBootState::Interrupted: return "interrupted";
    case InternalBootState::Blocked: return "blocked";
  }
  return "unknown";
}

bool internal_boot_set_ready() {
  return inspect_internal_boot_set() == InternalBootState::Ready;
}

BootSendResult send_embedded_loader() {
  printf("[omarchy-boot] handoff begin loader-bytes=%zu target=local-payloader\n",
         kLoaderSize);
  FILE* stream = fopen(kLoaderPath, "rb");
  if (!stream) return BootSendResult::OpenFailed;
  if (fseek(stream, 0, SEEK_END) != 0) {
    fclose(stream);
    return BootSendResult::ReadFailed;
  }
  const long file_size = ftell(stream);
  if (file_size != static_cast<long>(kLoaderSize)) {
    fclose(stream);
    return BootSendResult::SizeMismatch;
  }
  rewind(stream);

  uint8_t* bytes = static_cast<uint8_t*>(malloc(kLoaderSize));
  if (!bytes) {
    fclose(stream);
    return BootSendResult::ReadFailed;
  }
  const size_t read_size = fread(bytes, 1, kLoaderSize, stream);
  const bool read_ok = read_size == kLoaderSize && ferror(stream) == 0;
  fclose(stream);
  if (!read_ok) {
    free(bytes);
    return BootSendResult::ReadFailed;
  }

  uint8_t digest[32];
  sha256(bytes, kLoaderSize, digest);
  if (memcmp(digest, kLoaderDigest, sizeof(digest)) != 0) {
    free(bytes);
    return BootSendResult::DigestMismatch;
  }
  printf("[omarchy-boot] handoff loader=verified\n");

  const int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    free(bytes);
    return BootSendResult::SocketFailed;
  }

  const int requested_send_buffer = kLoaderSendBufferSize;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &requested_send_buffer,
                 sizeof(requested_send_buffer)) != 0) {
    const int option_errno = errno;
    printf("[omarchy-boot] handoff send-buffer=request-failed errno=%d\n",
           option_errno);
    close(socket_fd);
    free(bytes);
    return BootSendResult::SocketBufferFailed;
  }
  int actual_send_buffer = 0;
  socklen_t actual_send_buffer_size = sizeof(actual_send_buffer);
  const int get_buffer_result =
      getsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &actual_send_buffer,
                 &actual_send_buffer_size);
  if (get_buffer_result != 0 ||
      actual_send_buffer < static_cast<int>(kLoaderSize)) {
    const int option_errno = get_buffer_result != 0 ? errno : 0;
    printf("[omarchy-boot] handoff send-buffer=requested=%d actual=%d "
           "required=%zu errno=%d status=unsafe\n",
           requested_send_buffer, actual_send_buffer, kLoaderSize,
           option_errno);
    close(socket_fd);
    free(bytes);
    return BootSendResult::SocketBufferFailed;
  }
  printf("[omarchy-boot] handoff send-buffer=requested=%d actual=%d "
         "required=%zu status=ready\n",
         requested_send_buffer, actual_send_buffer, kLoaderSize);

  sockaddr_in address;
  memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(9090);
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(socket_fd, reinterpret_cast<sockaddr*>(&address),
              sizeof(address)) < 0) {
    close(socket_fd);
    free(bytes);
    return BootSendResult::ConnectFailed;
  }
  printf("[omarchy-boot] handoff local-loader=connected\n");

  int send_flags = 0;
#ifdef MSG_NOSIGNAL
  send_flags |= MSG_NOSIGNAL;
#endif
#ifdef MSG_DONTWAIT
  send_flags |= MSG_DONTWAIT;
#endif
  const ssize_t written = send(socket_fd, bytes, kLoaderSize, send_flags);
  const int send_errno = written < 0 ? errno : 0;
  printf("[omarchy-boot] handoff single-write requested=%zu written=%zd "
         "errno=%d\n",
         kLoaderSize, written, send_errno);
  close(socket_fd);
  free(bytes);
  if (written != static_cast<ssize_t>(kLoaderSize))
    return BootSendResult::SendFailed;
  printf("[omarchy-boot] handoff loader=sent bytes=%zu\n", kLoaderSize);
  return BootSendResult::Ok;
}

const char* boot_send_message(BootSendResult result) {
  switch (result) {
    case BootSendResult::Ok:
      return "The verified boot set and loader are ready. Waiting for Linux takeover.";
    case BootSendResult::OpenFailed:
      return "The embedded Linux loader could not be opened.";
    case BootSendResult::SizeMismatch:
      return "The embedded Linux loader has an unexpected size.";
    case BootSendResult::ReadFailed:
      return "The embedded Linux loader could not be read completely.";
    case BootSendResult::DigestMismatch:
      return "The embedded Linux loader failed its SHA-256 check.";
    case BootSendResult::StageDirectoryFailed:
      return "The internal Linux boot directory is unavailable.";
    case BootSendResult::StageRecoveryFailed:
      return "An interrupted boot-file update could not be recovered safely.";
    case BootSendResult::StageWriteFailed:
      return "The verified boot files could not be written completely.";
    case BootSendResult::StageVerifyFailed:
      return "The internal boot files failed verification; Linux was not started.";
    case BootSendResult::StageActivateFailed:
      return "The boot-file transaction is incomplete; Linux was not started.";
    case BootSendResult::SocketFailed:
      return "The local Linux handoff connection could not be created.";
    case BootSendResult::SocketBufferFailed:
      return "The complete Linux loader cannot be queued safely; nothing was sent.";
    case BootSendResult::ConnectFailed:
      return "The local Linux handoff service is unavailable.";
    case BootSendResult::SendFailed:
      return "The local handoff ended before the Linux loader was complete.";
  }
  return "The Linux boot handoff failed.";
}

}  // namespace omarchy_ps4
