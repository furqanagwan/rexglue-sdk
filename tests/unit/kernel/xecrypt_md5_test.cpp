/**
 * @file        xecrypt_md5_test.cpp
 * @brief       XeCryptMd5 state and digests (RG-GDK-014)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdio>
#include <string>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <rex/kernel/xboxkrnl/xecrypt_md5.h>

namespace {

namespace xboxkrnl = rex::kernel::xboxkrnl;

std::string Hex(const uint8_t* bytes, size_t size) {
  std::string out;
  char digit[3];
  for (size_t i = 0; i < size; ++i) {
    std::snprintf(digit, sizeof(digit), "%02x", bytes[i]);
    out += digit;
  }
  return out;
}

std::string Md5(std::string_view message, size_t chunk = 0) {
  xboxkrnl::XECRYPT_MD5_STATE state;
  xboxkrnl::md5::Init(&state);
  const auto* bytes = reinterpret_cast<const uint8_t*>(message.data());
  if (!chunk) {
    chunk = message.size() + 1;
  }
  for (size_t offset = 0; offset < message.size(); offset += chunk) {
    xboxkrnl::md5::Update(&state, bytes + offset, std::min(chunk, message.size() - offset));
  }
  uint8_t digest[16];
  xboxkrnl::md5::Final(&state, digest, sizeof(digest));
  return Hex(digest, sizeof(digest));
}

}

TEST_CASE("XeCryptMd5 matches the RFC 1321 test suite", "[kernel][xecrypt]") {
  CHECK(Md5("") == "d41d8cd98f00b204e9800998ecf8427e");
  CHECK(Md5("a") == "0cc175b9c0f1b6a831c399e269772661");
  CHECK(Md5("abc") == "900150983cd24fb0d6963f7d28e17f72");
  CHECK(Md5("message digest") == "f96b697d7cb7938d525a2f31aaf161d0");
  CHECK(Md5("abcdefghijklmnopqrstuvwxyz") == "c3fcd3d76192e4007dfb496cca67e13b");
  CHECK(Md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") ==
        "d174ab98d277d9f5a5611c2c9f419d9f");
  CHECK(Md5("123456789012345678901234567890123456789012345678901234567890123456789012345678"
            "90") == "57edf4a22be3c955ac49da2e2107b67a");
}

TEST_CASE("XeCryptMd5 updates in any split give the same digest", "[kernel][xecrypt]") {
  std::string message(1000, '\0');
  for (size_t i = 0; i < message.size(); ++i) {
    message[i] = char(i * 7 + 3);
  }
  std::string whole = Md5(message);

  for (size_t chunk : {1, 3, 55, 56, 63, 64, 65, 128, 999}) {
    INFO("chunk " << chunk);
    CHECK(Md5(message, chunk) == whole);
  }
}

TEST_CASE("XeCryptMd5 state has the layout titles read", "[kernel][xecrypt]") {
  uint8_t guest[0x54 + 4] = {};
  guest[0x54] = 0xAB;
  auto* state = reinterpret_cast<xboxkrnl::XECRYPT_MD5_STATE*>(guest);
  xboxkrnl::md5::Init(state);
  xboxkrnl::md5::Update(state, reinterpret_cast<const uint8_t*>("abc"), 3);
  CHECK(guest[3] == 3);

  xboxkrnl::md5::Final(state, nullptr, 0);

  CHECK(Hex(guest + 4, 4) == "98500190");
  CHECK(uint32_t(state->state[3]) == 0x727FE128);
  CHECK(guest[0x54] == 0xAB);
}
