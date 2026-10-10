// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <cstring>
#include <string_view>
#include <vector>

#include <rex/system/util/xdbf_utils.h>
#include <rex/system/xex_module.h>

using rex::runtime::XexModule;
using rex::system::util::XdbfGameData;

namespace {

void AppendBigEndian(std::vector<uint8_t>& out, uint64_t value, int bytes) {
  for (int i = bytes - 1; i >= 0; --i) {
    out.push_back(uint8_t(value >> (8 * i)));
  }
}

void PutBigEndian(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
  for (int i = 0; i < 4; ++i) {
    bytes[offset + i] = uint8_t(value >> (24 - 8 * i));
  }
}

constexpr size_t kXdbfEntryCountOffset = 8;
constexpr size_t kXdbfEntryOffset = 24;
constexpr size_t kXdbfEntrySizeOffset = kXdbfEntryOffset + 14;
constexpr size_t kXdbfContentOffset = kXdbfEntryOffset + 18;
constexpr size_t kXstrCountOffset = kXdbfContentOffset + 12;
constexpr size_t kXstrIdOffset = kXdbfContentOffset + 14;
constexpr size_t kXstrLengthOffset = kXdbfContentOffset + 16;

std::vector<uint8_t> TitleXdbf(std::string_view title) {
  std::vector<uint8_t> xstr;
  AppendBigEndian(xstr, 0x58535452, 4);
  AppendBigEndian(xstr, 1, 4);
  AppendBigEndian(xstr, 0, 4);
  AppendBigEndian(xstr, 1, 2);
  AppendBigEndian(xstr, 0x8000, 2);
  AppendBigEndian(xstr, title.size(), 2);
  xstr.insert(xstr.end(), title.begin(), title.end());

  std::vector<uint8_t> xdbf;
  AppendBigEndian(xdbf, 0x58444246, 4);
  AppendBigEndian(xdbf, 1, 4);
  AppendBigEndian(xdbf, 1, 4);
  AppendBigEndian(xdbf, 1, 4);
  AppendBigEndian(xdbf, 0, 4);
  AppendBigEndian(xdbf, 0, 4);
  AppendBigEndian(xdbf, 3, 2);
  AppendBigEndian(xdbf, 1, 8);
  AppendBigEndian(xdbf, 0, 4);
  AppendBigEndian(xdbf, xstr.size(), 4);
  xdbf.insert(xdbf.end(), xstr.begin(), xstr.end());
  return xdbf;
}

constexpr size_t kXexHeaderSize = 0x200;
constexpr size_t kXexSecurityOffset = 0x40;
constexpr size_t kXexPageCountOffset = kXexSecurityOffset + 0x180;
constexpr size_t kXexOptHeaderOffset = 0x1E0;

std::vector<uint8_t> MinimalXex() {
  std::vector<uint8_t> bytes(kXexHeaderSize + 0x10);
  std::memcpy(bytes.data(), "XEX2", 4);
  PutBigEndian(bytes, 0x08, kXexHeaderSize);
  PutBigEndian(bytes, 0x10, kXexSecurityOffset);
  PutBigEndian(bytes, 0x14, 1);
  PutBigEndian(bytes, 0x18, 0x000003FF);
  PutBigEndian(bytes, 0x1C, kXexOptHeaderOffset);
  PutBigEndian(bytes, kXexPageCountOffset, 1);
  PutBigEndian(bytes, kXexOptHeaderOffset, 0x10);
  return bytes;
}

bool XexHeaderAccepted(const std::vector<uint8_t>& bytes) {
  return XexModule::IsHeaderWellFormed(bytes.data(), bytes.size());
}

}

TEST_CASE("An XDBF title string inside its block reads back", "[system][xdbf]") {
  const auto bytes = TitleXdbf("Title");
  XdbfGameData data(bytes.data(), bytes.size());
  REQUIRE(data.is_valid());
  CHECK(data.title() == "Title");
}

TEST_CASE("An XDBF string longer than its block is not read", "[system][xdbf]") {
  auto bytes = TitleXdbf("Title");
  bytes[kXstrLengthOffset] = 0xFF;
  XdbfGameData data(bytes.data(), bytes.size());
  CHECK(data.title().empty());
}

TEST_CASE("An XDBF string table counting more entries than it holds stops at the end",
          "[system][xdbf]") {
  auto bytes = TitleXdbf("Title");
  bytes[kXstrCountOffset] = 0xFF;
  bytes[kXstrCountOffset + 1] = 0xFF;
  bytes[kXstrIdOffset + 1] = 0x01;
  XdbfGameData data(bytes.data(), bytes.size());
  CHECK(data.title().empty());
}

TEST_CASE("An XDBF block reaching past the data is not returned", "[system][xdbf]") {
  auto bytes = TitleXdbf("Title");
  PutBigEndian(bytes, kXdbfEntrySizeOffset, 0x10000);
  XdbfGameData data(bytes.data(), bytes.size());
  REQUIRE(data.is_valid());
  CHECK(data.title().empty());
}

TEST_CASE("An XDBF entry table larger than the data is refused", "[system][xdbf]") {
  auto bytes = TitleXdbf("Title");
  PutBigEndian(bytes, kXdbfEntryCountOffset, 0x10000);
  XdbfGameData data(bytes.data(), bytes.size());
  CHECK_FALSE(data.is_valid());
  CHECK(data.title().empty());
  CHECK(data.GetAchievements().empty());
}

TEST_CASE("A well-formed XEX header is accepted", "[system][xex]") {
  CHECK(XexHeaderAccepted(MinimalXex()));
}

TEST_CASE("A malformed XEX header is refused before it is copied", "[system][xex]") {
  auto bytes = MinimalXex();
  SECTION("Shorter than the fixed header") {
    bytes.resize(16);
  }
  SECTION("Header size past the input") {
    PutBigEndian(bytes, 0x08, uint32_t(bytes.size() + 1));
  }
  SECTION("Optional header count past the header") {
    PutBigEndian(bytes, 0x14, 0x1000);
  }
  SECTION("Security info past the header") {
    PutBigEndian(bytes, 0x10, kXexHeaderSize - 4);
  }
  SECTION("Page descriptors past the header") {
    PutBigEndian(bytes, kXexPageCountOffset, 3);
  }
  SECTION("Optional header data past the header") {
    PutBigEndian(bytes, 0x1C, kXexHeaderSize);
  }
  SECTION("Optional header size past the header") {
    PutBigEndian(bytes, kXexOptHeaderOffset, 0x40);
  }
  SECTION("Unknown magic") {
    bytes[3] = 'X';
  }
  CHECK_FALSE(XexHeaderAccepted(bytes));
}
