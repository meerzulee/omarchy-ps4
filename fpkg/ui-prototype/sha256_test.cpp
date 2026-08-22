#include "sha256.hpp"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

namespace {

bool check(const char* input, const char* expected) {
  uint8_t digest[32];
  char actual[65];
  omarchy_ps4::sha256(reinterpret_cast<const uint8_t*>(input), strlen(input),
                      digest);
  for (int index = 0; index < 32; ++index) {
    snprintf(actual + index * 2, 3, "%02x", digest[index]);
  }
  actual[64] = '\0';
  if (strcmp(actual, expected) == 0) return true;
  fprintf(stderr, "SHA-256 mismatch for '%s': %s\n", input, actual);
  return false;
}

bool check_streaming(const char* input, const char* expected) {
  omarchy_ps4::Sha256Context context;
  omarchy_ps4::sha256_init(&context);
  const size_t length = strlen(input);
  for (size_t offset = 0; offset < length;) {
    const size_t remaining = length - offset;
    const size_t chunk = remaining < 3 ? remaining : 3;
    omarchy_ps4::sha256_update(
        &context, reinterpret_cast<const uint8_t*>(input + offset), chunk);
    offset += chunk;
  }
  uint8_t digest[32];
  char actual[65];
  omarchy_ps4::sha256_final(&context, digest);
  for (int index = 0; index < 32; ++index) {
    snprintf(actual + index * 2, 3, "%02x", digest[index]);
  }
  actual[64] = '\0';
  if (strcmp(actual, expected) == 0) return true;
  fprintf(stderr, "Streaming SHA-256 mismatch for '%s': %s\n", input,
          actual);
  return false;
}

}  // namespace

int main() {
  bool ok = true;
  ok &= check("", "e3b0c44298fc1c149afbf4c8996fb924"
                  "27ae41e4649b934ca495991b7852b855");
  ok &= check("abc", "ba7816bf8f01cfea414140de5dae2223"
                     "b00361a396177a9cb410ff61f20015ad");
  ok &= check("Omarchy 4.0.0", "d86a5d162329db74ec7e6be941f951fb"
                               "336fc8b64581ac43fc6035260a83177b");
  ok &= check_streaming("abc", "ba7816bf8f01cfea414140de5dae2223"
                               "b00361a396177a9cb410ff61f20015ad");
  ok &= check_streaming(
      "The quick brown fox jumps over the lazy dog",
      "d7a8fbb307d7809469ca9abcb0082e4f"
      "8d5651e46d3cdb762d02d0bf37c9e592");
  if (!ok) return 1;
  printf("SHA-256 vectors passed.\n");
  return 0;
}
