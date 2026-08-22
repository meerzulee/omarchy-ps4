#include "private_boot.hpp"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef OMARCHY_BOOT_PARENT_PATH
#error OMARCHY_BOOT_PARENT_PATH is required
#endif

namespace {

using omarchy_ps4::BootSendResult;
using omarchy_ps4::InternalBootState;

void fail(const char* message) {
  fprintf(stderr, "private-boot-transaction-test: %s\n", message);
  _exit(1);
}

void require(bool condition, const char* message) {
  if (!condition) fail(message);
}

void path(char* output, size_t output_size, const char* suffix) {
  const int length =
      snprintf(output, output_size, "%s/%s", OMARCHY_BOOT_PARENT_PATH, suffix);
  require(length > 0 && static_cast<size_t>(length) < output_size,
          "test path overflow");
}

void write_file(const char* file_path, const char* contents) {
  FILE* stream = fopen(file_path, "wb");
  require(stream != nullptr, "could not create test file");
  require(fwrite(contents, 1, strlen(contents), stream) == strlen(contents),
          "could not write test file");
  require(fclose(stream) == 0, "could not close test file");
}

void remove_test_boot_directory(const char* directory) {
  static const char* artifacts[] = {
      "bzImage", "initramfs.cpio.gz", "bootargs.txt", "vram.txt"};
  char artifact_path[512];
  for (const char* artifact : artifacts) {
    const int length = snprintf(artifact_path, sizeof(artifact_path), "%s/%s",
                                directory, artifact);
    require(length > 0 && static_cast<size_t>(length) < sizeof(artifact_path),
            "test cleanup path overflow");
    require(unlink(artifact_path) == 0 || errno == ENOENT,
            "could not clear retained test artifact");
  }
  require(rmdir(directory) == 0 || errno == ENOENT,
          "could not clear retained test directory");
}

}  // namespace

int main() {
  char active[512];
  char previous[512];
  char staging[512];
  char marker[512];
  char unexpected[512];
  path(active, sizeof(active), "boot");
  path(previous, sizeof(previous), "boot.omarchy-prev");
  path(staging, sizeof(staging), "boot.omarchy-new");
  path(marker, sizeof(marker), ".omarchy-ps4-staging");

  require(omarchy_ps4::inspect_internal_boot_set() == InternalBootState::Missing,
          "missing boot set was not classified as missing");
  require(omarchy_ps4::stage_internal_boot_set() == BootSendResult::Ok,
          "initial stage failed");
  require(omarchy_ps4::internal_boot_set_ready(),
          "initial active set is not ready");
  require(omarchy_ps4::inspect_internal_boot_set() == InternalBootState::Ready,
          "verified boot set was not classified as ready");

  snprintf(unexpected, sizeof(unexpected), "%s/%s", active, "bootargs.txt");
  write_file(unexpected, "outdated\n");
  require(omarchy_ps4::inspect_internal_boot_set() ==
              InternalBootState::UpdateAvailable,
          "mismatched owned set was not classified as update available");
  require(omarchy_ps4::stage_internal_boot_set() == BootSendResult::Ok,
          "automatic update detection did not lead to a safe restage");
  require(omarchy_ps4::inspect_internal_boot_set() == InternalBootState::Ready,
          "restaged update did not become ready");

  snprintf(unexpected, sizeof(unexpected), "%s/%s", active, "keep-me");
  write_file(unexpected, "owned by someone else\n");
  require(!omarchy_ps4::internal_boot_set_ready(),
          "active set with an unexpected file was accepted");
  require(omarchy_ps4::inspect_internal_boot_set() == InternalBootState::Blocked,
          "active set with unexpected data was not classified as blocked");
  require(omarchy_ps4::stage_internal_boot_set() ==
              BootSendResult::StageRecoveryFailed,
          "stage moved an active directory containing unexpected data");
  require(access(unexpected, F_OK) == 0, "unexpected data was removed");
  require(unlink(unexpected) == 0, "could not reset unexpected-file fixture");

  remove_test_boot_directory(previous);
  require(rename(active, previous) == 0,
          "could not simulate active-to-previous promotion");
  require(mkdir(staging, 0755) == 0,
          "could not create interrupted staging directory");
  snprintf(unexpected, sizeof(unexpected), "%s/%s", staging, "bootargs.txt");
  write_file(unexpected, "partial\n");
  write_file(marker,
             "schema=1\nrelease=omarchy-ps4-4.0.0-baikal-b1-beta1\n"
             "phase=promoting\n");
  require(omarchy_ps4::inspect_internal_boot_set() ==
              InternalBootState::Interrupted,
          "transaction marker was not classified as interrupted");
  require(omarchy_ps4::stage_internal_boot_set() == BootSendResult::Ok,
          "interrupted promotion did not restore the previous complete set");
  require(omarchy_ps4::internal_boot_set_ready(),
          "restored active set is not ready");
  require(access(marker, F_OK) != 0 && errno == ENOENT,
          "transaction marker survived recovery");

  require(mkdir(staging, 0755) == 0,
          "could not create committed-transaction fixture");
  write_file(marker,
             "schema=1\nrelease=omarchy-ps4-4.0.0-baikal-b1-beta1\n"
             "phase=promoting\n");
  require(omarchy_ps4::stage_internal_boot_set() == BootSendResult::Ok,
          "committed active set did not finish marker cleanup");
  require(omarchy_ps4::internal_boot_set_ready(),
          "active set is not ready after marker cleanup");

  printf("Private boot transaction recovery passed.\n");
  return 0;
}
