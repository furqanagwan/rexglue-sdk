// Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <rex/codegen/binary_view.h>
#include <rex/codegen/codegen_context.h>
#include <rex/codegen/crt_jump_scanner.h>
#include <rex/codegen/phases.h>
#include <rex/codegen/test_support.h>

#include <vector>

using namespace rex::codegen;
namespace {
constexpr uint32_t kBase = 0x82000000;
constexpr uint32_t kRestore = kBase + 0x400;

uint32_t D(uint32_t opcode, uint32_t reg, uint32_t base, uint16_t displacement) {
  return (opcode << 26) | (reg << 21) | (base << 16) | displacement;
}
uint32_t Bl(uint32_t from, uint32_t to) {
  return 0x48000001 | ((to - from) & 0x03FFFFFC);
}

// Synthetic CRT-shaped routines assembled from the documented register layout.
// Deliberately use different relocation values from every investigated title.
std::vector<uint32_t> Save() {
  std::vector<uint32_t> w{D(15, 4, 0, 0x8200), D(32, 0, 4, 0), 0x2C000000, 0x7C0903A6,
                          0x4C820420,          0x7C0802A6,     0x7C800026};
  for (uint32_t r = 14; r < 32; ++r)
    w.push_back(D(54, r, 3, uint16_t((r - 14) * 8)));
  for (uint32_t r = 13; r < 32; ++r)
    w.push_back(D(62, r, 3, uint16_t(152 + (r - 13) * 8)));
  for (uint32_t v = 64; v < 128; ++v) {
    w.push_back(D(14, 5, 0, uint16_t(320 + (v - 64) * 16)));
    w.push_back((4u << 26) | ((v & 31) << 21) | (5 << 16) | (3 << 11) | 0x50B | ((v & 32) >> 3));
  }
  w.insert(w.end(),
           {0x90030134, 0x90830130, 0xF8230090, 0x38000000, 0x90030138, 0x38600000, 0x4E800020});
  return w;
}

std::vector<uint32_t> Restore() {
  std::vector<uint32_t> w{
      0x7C0802A6, 0x9421FFB0, 0x90010008, 0x7C862378, 0x2C040000,
      0x80030138, 0x2C800000, 0x7C671B78, 0x38A00000, 0x40820008,
      0x38C00001, 0x408602C0, 0x80670134, 0x80870090, Bl(kRestore + 14 * 4, kBase + 0x800)};
  for (uint32_t r = 14; r < 32; ++r)
    w.push_back(D(50, r, 7, uint16_t((r - 14) * 8)));
  for (uint32_t r = 13; r < 32; ++r)
    w.push_back(D(58, r, 7, uint16_t(152 + (r - 13) * 8)));
  for (uint32_t v = 64; v < 128; ++v) {
    w.push_back(D(14, 3, 0, uint16_t(320 + (v - 64) * 16)));
    w.push_back((4u << 26) | ((v & 31) << 21) | (3 << 16) | (7 << 11) | 0xCB | ((v & 32) >> 3));
  }
  w.insert(w.end(),
           {0x80A70134, 0x80870130, 0x7CA803A6, 0xE8270090, 0x7C8FF120, 0x7CC33378, 0x4E800020,
            0x80670004, 0x80870000, Bl(kRestore + 189 * 4, kBase + 0x800), 0x80670000, 0x80870004,
            Bl(kRestore + 192 * 4, kBase + 0xF00), 0x80010008, 0x7C0803A6, 0x38210050, 0x4E800020});
  return w;
}

class Fixture : public TestModule {
 public:
  std::vector<uint32_t> words = std::vector<uint32_t>(0x1000 / 4);
  std::vector<uint8_t> bytes;
  Fixture() {
    Put(0, Save());
    Put(0x400, Restore());
    words[0x800 / 4] = words[0xF00 / 4] = 0x4E800020;
    binary_symbols_.push_back(
        {"xboxkrnl@327", kBase + 0xF00, 4, rex::runtime::BinarySymbolType::Import});
  }
  void Put(size_t offset, const std::vector<uint32_t>& source) {
    std::copy(source.begin(), source.end(), words.begin() + offset / 4);
  }
  CrtJumpCandidates Scan(bool executable = true, size_t trimBytes = 0) {
    bytes.clear();
    for (uint32_t word : words)
      for (int shift = 24; shift >= 0; shift -= 8)
        bytes.push_back(uint8_t(word >> shift));
    bytes.resize(bytes.size() - trimBytes);
    Load(kBase, bytes.data(), bytes.size());
    binary_sections_.front().executable = executable;
    return ScanCrtJumps(BinaryView::fromModule(*this));
  }
};
}  // namespace

TEST_CASE("CRT jump scanner recognizes a complete relocated pair", "[codegen][crt-jump]") {
  Fixture f;
  auto found = f.Scan();
  REQUIRE(found.uniquePair());
  CHECK(found.setjmp.front() == kBase);
  CHECK(found.longjmp.front() == kRestore);
  // Negative signed low-half relocation; points back inside this image.
  f.words[0] = D(15, 4, 0, 0x8201);
  f.words[1] = D(32, 0, 4, 0x8000);
  CHECK(f.Scan().setjmp.empty());  // unmapped hook pointer must be rejected
}

TEST_CASE("CRT jump scanner rejects every changed register-layout instruction",
          "[codegen][crt-jump]") {
  Fixture f;
  for (size_t i = 2; i < Save().size(); ++i) {
    INFO("setjmp word " << i);
    f.words[i] ^= 4;
    CHECK(f.Scan().setjmp.empty());
    f.words[i] ^= 4;
  }
  for (size_t i = 0; i < Restore().size(); ++i) {
    if (i == 14 || i == 189 || i == 192)
      continue;
    INFO("longjmp word " << i);
    f.words[0x100 + i] ^= 4;
    CHECK(f.Scan().longjmp.empty());
    f.words[0x100 + i] ^= 4;
  }
}

TEST_CASE("CRT jump scanner rejects invalid relocation and branch forms", "[codegen][crt-jump]") {
  Fixture f;
  SECTION("different common helper") {
    f.words[0x100 + 189] += 4;
  }
  SECTION("absolute branch") {
    f.words[0x100 + 14] |= 2;
  }
  SECTION("nonlink branch") {
    f.words[0x100 + 14] &= ~1u;
  }
  SECTION("unmapped helper") {
    f.words[0x100 + 192] = Bl(kRestore + 192 * 4, kBase - 4);
  }
  SECTION("ordinary code instead of RtlUnwind") {
    f.words[0x100 + 192] = Bl(kRestore + 192 * 4, kBase + 0x800);
  }
  CHECK(f.Scan().longjmp.empty());
}

TEST_CASE("CRT jump scanner refuses partial and ambiguous pairs", "[codegen][crt-jump]") {
  Fixture f;
  SECTION("non-executable bytes") {
    auto found = f.Scan(false);
    CHECK(found.setjmp.empty());
    CHECK(found.longjmp.empty());
  }
  SECTION("every truncated prefix") {
    for (size_t bytes = 0; bytes < Save().size() * 4; ++bytes) {
      auto found = f.Scan(true, 0x1000 - bytes);
      CHECK(found.setjmp.empty());
      CHECK_FALSE(found.uniquePair());
    }
    for (size_t bytes = 0; bytes < Restore().size() * 4; ++bytes)
      CHECK(f.Scan(true, 0x1000 - 0x400 - bytes).longjmp.empty());
  }
  SECTION("duplicate save") {
    f.Put(0x900, Save());
    auto found = f.Scan();
    REQUIRE(found.setjmp.size() == 2);
    CHECK_FALSE(found.uniquePair());
  }
}

TEST_CASE("CRT jump detection preserves explicit overrides", "[codegen][crt-jump]") {
  CrtJumpCandidates pair{{kBase}, {kRestore}};
  RecompilerConfig config;
  SECTION("fill both") {
    REQUIRE(ApplyCrtJumpCandidates(pair, config));
    CHECK(config.setJmpAddress == kBase);
    CHECK(config.longJmpAddress == kRestore);
  }
  SECTION("fill matching partial hint") {
    config.setJmpAddress = kBase;
    REQUIRE(ApplyCrtJumpCandidates(pair, config));
    CHECK(config.longJmpAddress == kRestore);
  }
  SECTION("conflicting hint stays explicit") {
    config.setJmpAddress = kBase + 4;
    CHECK_FALSE(ApplyCrtJumpCandidates(pair, config));
    CHECK(config.setJmpAddress == kBase + 4);
    CHECK(config.longJmpAddress == 0);
  }
  SECTION("duplicate longjmp") {
    pair.longjmp.push_back(kRestore + 4);
    CHECK_FALSE(ApplyCrtJumpCandidates(pair, config));
    CHECK(config.setJmpAddress == 0);
  }
  SECTION("incomplete pair") {
    pair.longjmp.clear();
    CHECK_FALSE(ApplyCrtJumpCandidates(pair, config));
    CHECK(config.setJmpAddress == 0);
  }
}

TEST_CASE("CRT registration refuses localized guest registers", "[codegen][crt-jump]") {
  Fixture f;
  REQUIRE(f.Scan().uniquePair());
  for (auto flag : {&RecompilerConfig::ctrAsLocalVariable, &RecompilerConfig::xerAsLocalVariable,
                    &RecompilerConfig::reservedRegisterAsLocalVariable,
                    &RecompilerConfig::crRegistersAsLocalVariables,
                    &RecompilerConfig::nonArgumentRegistersAsLocalVariables,
                    &RecompilerConfig::nonVolatileRegistersAsLocalVariables}) {
    RecompilerConfig config;
    config.*flag = true;
    auto ctx = CodegenContext::Create(BinaryView::fromModule(f), config);
    auto result = phases::Register(ctx, nullptr);
    REQUIRE_FALSE(result);
    CHECK(result.error().message.find("disable register localization") != std::string::npos);
    CHECK(ctx.Config().setJmpAddress == kBase);
    CHECK(ctx.Config().longJmpAddress == kRestore);
    CHECK(ctx.Config().setJmpHookAddress == kBase);
  }
}
