#pragma once

#include <stddef.h>
#include <stdint.h>

namespace omarchy_ps4 {

struct Sha256Context {
  uint32_t state[8];
  uint64_t total_size;
  uint8_t buffer[64];
  size_t buffer_size;
};

void sha256_init(Sha256Context* context);
void sha256_update(Sha256Context* context, const uint8_t* bytes, size_t size);
void sha256_final(Sha256Context* context, uint8_t digest[32]);
void sha256(const uint8_t* bytes, size_t size, uint8_t digest[32]);

}  // namespace omarchy_ps4
