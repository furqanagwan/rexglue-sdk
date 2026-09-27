/**
 * @file        xecrypt_md5.h
 * @brief       XeCryptMd5 state in guest layout (RG-GDK-014)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include <rex/types.h>

namespace rex::kernel::xboxkrnl {

// XECRYPT_MD5_STATE as titles allocate and read it: a 32-bit byte count, the
// four MD5 words and the partial block, 0x54 bytes like XECRYPT_SHA_STATE.
// Quantum of Solace calls XeCryptMd5Final with no output buffer and reads the
// digest from the words at offsets 4-16 (its code at 0x8255B7xx), which fixes
// the 32-bit count; Xenia Edge's 64-bit count would move them. The words hold
// A, B, C and D as big-endian values, as the SHA state holds its words; what
// hardware leaves there after Final is not verified.
struct XECRYPT_MD5_STATE {
  rex::be<uint32_t> count;     // 0x0, bytes hashed
  rex::be<uint32_t> state[4];  // 0x4, A B C D
  uint8_t buffer[64];          // 0x14, count % 64 bytes pending
};
static_assert(sizeof(XECRYPT_MD5_STATE) == 0x54);
static_assert(offsetof(XECRYPT_MD5_STATE, state) == 0x4);

namespace md5 {

// RFC 1321.
inline void Transform(uint32_t abcd[4], const uint8_t block[64]) {
  static constexpr uint32_t kK[64] = {
      0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613,
      0xFD469501, 0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193,
      0xA679438E, 0x49B40821, 0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D,
      0x02441453, 0xD8A1E681, 0xE7D3FBC8, 0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED,
      0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A, 0xFFFA3942, 0x8771F681, 0x6D9D6122,
      0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, 0x289B7EC6, 0xEAA127FA,
      0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665, 0xF4292244,
      0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
      0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB,
      0xEB86D391};
  static constexpr uint32_t kShift[16] = {7, 12, 17, 22, 5, 9,  14, 20,
                                          4, 11, 16, 23, 6, 10, 15, 21};
  uint32_t m[16];
  for (int i = 0; i < 16; ++i) {
    m[i] = uint32_t(block[i * 4]) | (uint32_t(block[i * 4 + 1]) << 8) |
           (uint32_t(block[i * 4 + 2]) << 16) | (uint32_t(block[i * 4 + 3]) << 24);
  }
  uint32_t a = abcd[0], b = abcd[1], c = abcd[2], d = abcd[3];
  for (int i = 0; i < 64; ++i) {
    uint32_t f;
    int g;
    if (i < 16) {
      f = (b & c) | (~b & d);
      g = i;
    } else if (i < 32) {
      f = (d & b) | (~d & c);
      g = (5 * i + 1) % 16;
    } else if (i < 48) {
      f = b ^ c ^ d;
      g = (3 * i + 5) % 16;
    } else {
      f = c ^ (b | ~d);
      g = (7 * i) % 16;
    }
    uint32_t sum = a + f + kK[i] + m[g];
    uint32_t shift = kShift[(i / 16) * 4 + i % 4];
    a = d;
    d = c;
    c = b;
    b += (sum << shift) | (sum >> (32 - shift));
  }
  abcd[0] += a;
  abcd[1] += b;
  abcd[2] += c;
  abcd[3] += d;
}

inline void Init(XECRYPT_MD5_STATE* state) {
  std::memset(state, 0, sizeof(*state));
  state->state[0] = 0x67452301;
  state->state[1] = 0xEFCDAB89;
  state->state[2] = 0x98BADCFE;
  state->state[3] = 0x10325476;
}

inline void Update(XECRYPT_MD5_STATE* state, const uint8_t* input, size_t size) {
  uint32_t abcd[4] = {state->state[0], state->state[1], state->state[2], state->state[3]};
  uint32_t count = state->count;
  size_t pending = count % 64;
  while (size) {
    size_t take = std::min(size, 64 - pending);
    std::memcpy(state->buffer + pending, input, take);
    pending += take;
    input += take;
    size -= take;
    count += uint32_t(take);
    if (pending == 64) {
      Transform(abcd, state->buffer);
      pending = 0;
    }
  }
  state->count = count;
  for (int i = 0; i < 4; ++i) {
    state->state[i] = abcd[i];
  }
}

// Pads, leaves the final words in the state and writes up to 16 digest bytes
// (A to D, each little-endian) to `out`.
inline void Final(XECRYPT_MD5_STATE* state, uint8_t* out, size_t out_size) {
  // The 32-bit count limits messages to 4 GB, like XECRYPT_SHA_STATE.
  uint64_t bits = uint64_t(uint32_t(state->count)) * 8;
  static constexpr uint8_t kPadding[64] = {0x80};
  size_t pending = state->count % 64;
  Update(state, kPadding, pending < 56 ? 56 - pending : 120 - pending);
  uint8_t length[8];
  for (int i = 0; i < 8; ++i) {
    length[i] = uint8_t(bits >> (i * 8));
  }
  Update(state, length, 8);
  uint8_t digest[16];
  for (int i = 0; i < 4; ++i) {
    uint32_t word = state->state[i];
    for (int j = 0; j < 4; ++j) {
      digest[i * 4 + j] = uint8_t(word >> (j * 8));
    }
  }
  if (out) {
    std::memcpy(out, digest, std::min<size_t>(out_size, sizeof(digest)));
  }
}

}  // namespace md5

}  // namespace rex::kernel::xboxkrnl
