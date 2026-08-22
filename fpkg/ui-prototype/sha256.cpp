#include "sha256.hpp"

#include <string.h>

namespace omarchy_ps4 {
namespace {

constexpr uint32_t kRoundConstants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

uint32_t rotate_right(uint32_t value, uint32_t count) {
  return (value >> count) | (value << (32 - count));
}

void transform(const uint8_t block[64], uint32_t state[8]) {
  uint32_t words[64];
  for (int index = 0; index < 16; ++index) {
    const int offset = index * 4;
    words[index] = (static_cast<uint32_t>(block[offset]) << 24) |
                   (static_cast<uint32_t>(block[offset + 1]) << 16) |
                   (static_cast<uint32_t>(block[offset + 2]) << 8) |
                   static_cast<uint32_t>(block[offset + 3]);
  }
  for (int index = 16; index < 64; ++index) {
    const uint32_t s0 = rotate_right(words[index - 15], 7) ^
                        rotate_right(words[index - 15], 18) ^
                        (words[index - 15] >> 3);
    const uint32_t s1 = rotate_right(words[index - 2], 17) ^
                        rotate_right(words[index - 2], 19) ^
                        (words[index - 2] >> 10);
    words[index] = words[index - 16] + s0 + words[index - 7] + s1;
  }

  uint32_t a = state[0];
  uint32_t b = state[1];
  uint32_t c = state[2];
  uint32_t d = state[3];
  uint32_t e = state[4];
  uint32_t f = state[5];
  uint32_t g = state[6];
  uint32_t h = state[7];
  for (int index = 0; index < 64; ++index) {
    const uint32_t sum1 = rotate_right(e, 6) ^ rotate_right(e, 11) ^
                          rotate_right(e, 25);
    const uint32_t choice = (e & f) ^ (~e & g);
    const uint32_t temporary1 = h + sum1 + choice +
                                kRoundConstants[index] + words[index];
    const uint32_t sum0 = rotate_right(a, 2) ^ rotate_right(a, 13) ^
                          rotate_right(a, 22);
    const uint32_t majority = (a & b) ^ (a & c) ^ (b & c);
    const uint32_t temporary2 = sum0 + majority;
    h = g;
    g = f;
    f = e;
    e = d + temporary1;
    d = c;
    c = b;
    b = a;
    a = temporary1 + temporary2;
  }
  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
  state[5] += f;
  state[6] += g;
  state[7] += h;
}

}  // namespace

void sha256_init(Sha256Context* context) {
  const uint32_t initial_state[8] = {
      0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
      0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
  };
  memcpy(context->state, initial_state, sizeof(initial_state));
  context->total_size = 0;
  context->buffer_size = 0;
  memset(context->buffer, 0, sizeof(context->buffer));
}

void sha256_update(Sha256Context* context, const uint8_t* bytes, size_t size) {
  context->total_size += size;

  if (context->buffer_size > 0) {
    const size_t available = 64 - context->buffer_size;
    const size_t take = size < available ? size : available;
    if (take > 0) {
      memcpy(context->buffer + context->buffer_size, bytes, take);
      context->buffer_size += take;
      bytes += take;
      size -= take;
    }
    if (context->buffer_size == 64) {
      transform(context->buffer, context->state);
      context->buffer_size = 0;
    }
  }

  while (size >= 64) {
    transform(bytes, context->state);
    bytes += 64;
    size -= 64;
  }
  if (size > 0) {
    memcpy(context->buffer, bytes, size);
    context->buffer_size = size;
  }
}

void sha256_final(Sha256Context* context, uint8_t digest[32]) {
  uint8_t tail[128];
  const size_t remaining = context->buffer_size;
  memset(tail, 0, sizeof(tail));
  if (remaining > 0) memcpy(tail, context->buffer, remaining);
  tail[remaining] = 0x80;
  const size_t tail_size = remaining < 56 ? 64 : 128;
  const uint64_t bit_size = context->total_size * 8;
  for (int index = 0; index < 8; ++index) {
    tail[tail_size - 1 - index] =
        static_cast<uint8_t>(bit_size >> (index * 8));
  }
  transform(tail, context->state);
  if (tail_size == 128) transform(tail + 64, context->state);

  for (int index = 0; index < 8; ++index) {
    digest[index * 4] = static_cast<uint8_t>(context->state[index] >> 24);
    digest[index * 4 + 1] = static_cast<uint8_t>(context->state[index] >> 16);
    digest[index * 4 + 2] = static_cast<uint8_t>(context->state[index] >> 8);
    digest[index * 4 + 3] = static_cast<uint8_t>(context->state[index]);
  }
}

void sha256(const uint8_t* bytes, size_t size, uint8_t digest[32]) {
  Sha256Context context;
  sha256_init(&context);
  sha256_update(&context, bytes, size);
  sha256_final(&context, digest);
}

}  // namespace omarchy_ps4
