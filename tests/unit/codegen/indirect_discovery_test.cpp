/**
 * @file        indirect_discovery_test.cpp
 * @brief       Entries that gap fill and branch resolution used to miss
 *              (RG-FIX-002), on synthetic PPC.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <array>
#include <optional>
#include <utility>
#include <vector>

#include <rex/codegen/analyze.h>
#include <rex/codegen/codegen_context.h>
#include <rex/codegen/phases.h>
#include <rex/codegen/test_support.h>

using namespace rex::codegen;

namespace {

constexpr uint32_t kBase = 0x82000000;

constexpr uint32_t Blr() {
  return 0x4E800020u;
}
constexpr uint32_t Li(uint32_t rd, int16_t imm) {
  return (14u << 26) | (rd << 21) | uint16_t(imm);
}
constexpr uint32_t Addi(uint32_t rd, uint32_t ra, int16_t imm) {
  return (14u << 26) | (rd << 21) | (ra << 16) | uint16_t(imm);
}
// b / bl from `from` to `to`.
constexpr uint32_t B(uint32_t from, uint32_t to, bool link = false) {
  return (18u << 26) | ((to - from) & 0x03FFFFFCu) | (link ? 1u : 0u);
}
constexpr uint32_t Cmpwi0(uint32_t ra) {
  return (11u << 26) | (ra << 16);
}
// beq cr0 from `from` to `to`.
constexpr uint32_t Beq(uint32_t from, uint32_t to) {
  return (16u << 26) | (12u << 21) | (2u << 16) | ((to - from) & 0xFFFCu);
}

class DiscoveryModule : public TestModule {
 public:
  // `pointer`, when set, is held by a data section as a method table would.
  void LoadCode(const uint8_t* data, size_t size, uint32_t pointer = 0) {
    Load(kBase, data, size);
    pdata_[0] = uint8_t(kBase >> 24);
    pdata_[1] = uint8_t(kBase >> 16);
    binary_sections_.push_back({".pdata", kBase + uint32_t(size), 8, pdata_.data(), false, false});
    for (size_t i = 0; i < 4; ++i) {
      rdata_[i] = uint8_t(pointer >> (24 - 8 * i));
    }
    binary_sections_.push_back(
        {".rdata", kBase + uint32_t(size) + 8, 8, rdata_.data(), false, false});
  }
  uint32_t image_size() const override { return TestModule::image_size() + 16; }
  uint32_t exception_directory_address() const override { return kBase + TestModule::image_size(); }
  uint32_t exception_directory_size() const override { return 8; }

 private:
  std::array<uint8_t, 8> pdata_{};
  std::array<uint8_t, 8> rdata_{};
};

// Runs the full analysis on `words` at kBase, with the given entries known
// from config (as pdata or a title hint would give them).
struct Analyzed {
  std::vector<uint8_t> bytes;
  DiscoveryModule module;
  std::optional<CodegenContext> ctx;

  // `sized` entries get a declared size, as a function table entry gives one.
  // `pointer`, when set, is held in data.
  Analyzed(const std::vector<uint32_t>& words, std::initializer_list<uint32_t> entries,
           std::initializer_list<std::pair<uint32_t, uint32_t>> sized = {}, uint32_t pointer = 0) {
    for (uint32_t word : words) {
      bytes.insert(bytes.end(),
                   {uint8_t(word >> 24), uint8_t(word >> 16), uint8_t(word >> 8), uint8_t(word)});
    }
    module.LoadCode(bytes.data(), bytes.size(), pointer);
    RecompilerConfig config;
    config.projectName = "discovery";
    for (uint32_t entry : entries) {
      config.functions[entry] = FunctionConfig{};
    }
    for (const auto& [entry, size] : sized) {
      config.functions[entry] = FunctionConfig{};
      config.functions[entry].size = size;
    }
    ctx.emplace(CodegenContext::Create(BinaryView::fromModule(module), std::move(config)));
    ctx->analysisState().format = "xex";
    ctx->analysisState().loadAddress = kBase;
    ctx->analysisState().entryPoint = kBase;
    ctx->analysisState().imageSize = uint32_t(bytes.size());
    auto result = Analyze(*ctx);
    if (!result) {
      INFO(result.error().message);
      REQUIRE(result);
    }
  }

  bool IsEntry(uint32_t address) const { return ctx->graph.isEntryPoint(address); }
};

}  // namespace

TEST_CASE("A function after a thunk whose tail call was not yet known is found",
          "[codegen][discovery]") {
  // 0x00 entry.
  // 0x04 Y: li r3,7; blr                 (a gap function)
  // 0x0C T: addi r3,r3,-4; b Y           (a thunk tail-calling Y)
  // 0x14 F: li r3,1; blr                 (only ever reached indirectly)
  // Gap fill cuts T..F as one segment, since Y isn't known when it splits;
  // discovery ends T at its `b`, and F used to be claimed by no one.
  const uint32_t y = kBase + 0x04, t = kBase + 0x0C, f = kBase + 0x14;
  Analyzed a({Blr(), Li(3, 7), Blr(), Addi(3, 3, -4), B(t + 4, y), Li(3, 1), Blr()}, {kBase});
  CHECK(a.IsEntry(y));
  CHECK(a.IsEntry(t));
  CHECK(a.IsEntry(f));
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("A function after a called thunk is found when only a tail branch reaches it",
          "[codegen][discovery]") {
  // 0x00 E: bl T; blr                   (8 bytes, from config)
  // 0x08 T: addi r3,r3,-4; b Y           (found by E's call, before gap fill)
  // 0x10 F: li r3,1; blr                 (reached only by G's tail branch)
  // 0x18 G: b F                          (an entry from config)
  // 0x1C Y: li r3,7; blr
  // Gap fill cuts T..F as one segment starting at T, a known entry, so the
  // whole segment used to be skipped (Blood Stone 0x8222D588, 007 Legends
  // 0x826D3F38).
  const uint32_t t = kBase + 0x08, f = kBase + 0x10, g = kBase + 0x18, y = kBase + 0x1C;
  Analyzed a({B(kBase, t, true), Blr(), Addi(3, 3, -4), B(t + 4, y), Li(3, 1), Blr(), B(g, f),
              Li(3, 7), Blr()},
             {g}, {{kBase, 8}});
  CHECK(a.IsEntry(t));
  CHECK(a.IsEntry(f));
  // T follows its branch to Y, not yet known, as its own code.
  CHECK(a.ctx->graph.getFunction(t)->containsAddress(y));
  CHECK(a.ctx->graph.classifyTarget(f, g, false) == TargetKind::Function);
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("A thunk right after a sized function is found", "[codegen][discovery]") {
  // 0x00 E: cmpwi r3,0; beq 0x0C; blr; bctr   (16 bytes, as .pdata gives)
  // 0x10 T: b Z                               (only ever reached indirectly)
  // 0x14 Z: li r3,1; blr                      (an entry from config)
  // Gap fill cuts 0x0C..0x14 as one segment, which starts inside E, so it
  // used to be skipped (007 Legends 0x82225D90).
  const uint32_t t = kBase + 0x10, z = kBase + 0x14;
  Analyzed a({Cmpwi0(3), Beq(kBase + 4, kBase + 0x0C), Blr(), 0x4E800420, B(t, z), Li(3, 1), Blr()},
             {z}, {{kBase, 16}});
  CHECK(a.IsEntry(t));
  CHECK(a.ctx->graph.getFunction(kBase)->containsAddress(kBase + 0x0C));
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("A called function's own branch past its first return is not split off",
          "[codegen][discovery]") {
  // 0x00 entry: bl T; blr
  // 0x08 T: cmpwi r3,0; beq L; blr       (found by the call)
  // 0x14 L: li r3,2; blr                 (T's own code, after its first blr)
  const uint32_t t = kBase + 0x08, l = kBase + 0x14;
  Analyzed a({B(kBase, t, true), Blr(), Cmpwi0(3), Beq(t + 4, l), Blr(), Li(3, 2), Blr()}, {kBase});
  REQUIRE(a.IsEntry(t));
  CHECK_FALSE(a.IsEntry(l));
  CHECK(a.ctx->graph.getFunction(t)->containsAddress(l));
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("A switch case another function branches into becomes an entry", "[codegen][discovery]") {
  // S: cmpwi r3,0; beq case; li r3,5; blr; case: li r3,9; blr.
  // The later caller tail-branches backwards into S's case.
  const uint32_t s = kBase, c = kBase + 0x10, caller = kBase + 0x18;
  Analyzed a({Cmpwi0(3), Beq(s + 4, c), Li(3, 5), Blr(), Li(3, 9), Blr(), B(caller, s, true),
              B(caller + 4, c)},
             {s, caller});
  CHECK(a.IsEntry(s));
  CHECK(a.IsEntry(c));
  // S keeps the case as its own label.
  CHECK(a.ctx->graph.getFunction(s)->containsAddress(c));
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("A branch into the caller's own body stays local even at another entry",
          "[codegen][discovery]") {
  // As above: S branches to `case`, which is also an entry now.
  const uint32_t s = kBase, c = kBase + 0x10, caller = kBase + 0x18;
  Analyzed a({Cmpwi0(3), Beq(s + 4, c), Li(3, 5), Blr(), Li(3, 9), Blr(), B(caller, s, true),
              B(caller + 4, c)},
             {s, caller});
  REQUIRE(a.IsEntry(c));
  const auto& graph = a.ctx->graph;
  // S's own beq: a local goto, which discovery already made it.
  CHECK(graph.classifyTarget(c, s + 4, false) == TargetKind::InternalLabel);
  // The entry's b: a tail call into the other function.
  CHECK(graph.classifyTarget(c, caller + 4, false) == TargetKind::Function);
  // Calls to it are calls, whoever makes them.
  CHECK(graph.classifyTarget(c, s + 4, true) == TargetKind::Function);
}

TEST_CASE("A leftover function does not promote its ordinary local return block",
          "[codegen][discovery]") {
  const uint32_t y = kBase + 4, t = kBase + 12, f = kBase + 20, local = kBase + 36;
  Analyzed a({Blr(), Li(3, 7), Blr(), Addi(3, 3, -4), B(t + 4, y), Cmpwi0(3), Beq(f + 4, local),
              Li(3, 1), Blr(), Li(3, 2), Blr()},
             {kBase});
  REQUIRE(a.IsEntry(f));
  CHECK_FALSE(a.IsEntry(local));
  CHECK(a.ctx->graph.getFunction(f)->containsAddress(local));
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("Zero padding and an internal loop do not become leftover entries",
          "[codegen][discovery]") {
  const uint32_t y = kBase + 4, t = kBase + 12;
  Analyzed a({Blr(), Li(3, 7), Blr(), Addi(3, 3, -4), B(t + 4, y), 0, 0, Cmpwi0(3),
              Beq(kBase + 32, kBase + 28), Blr()},
             {kBase});
  CHECK_FALSE(a.IsEntry(kBase + 20));
  CHECK_FALSE(a.IsEntry(kBase + 24));
  CHECK_FALSE(a.IsEntry(kBase + 32));
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("Merge requires an unconditional aligned branch into decoded blocks",
          "[codegen][discovery]") {
  for (int scenario = 0; scenario < 6; ++scenario) {
    CAPTURE(scenario);
    std::array<uint8_t, 64> bytes{};
    // A shared epilogue that reads the caller's frame is not a standalone leaf.
    const uint32_t instruction = scenario == 4 ? 0x80610008u : Li(3, 9);
    uint32_t target = scenario == 0 ? kBase + 12 : scenario == 1 ? kBase + 5 : kBase + 4;
    const uint32_t branch = scenario == 5 ? Beq(kBase + 40, target) : B(kBase + 40, target);
    for (size_t i = 0; i < 4; ++i) {
      bytes[4 + i] = uint8_t(instruction >> (24 - 8 * i));
      bytes[8 + i] = uint8_t(Blr() >> (24 - 8 * i));
      bytes[40 + i] = uint8_t(branch >> (24 - 8 * i));
    }
    TestModule module;
    module.Load(kBase, bytes.data(), bytes.size());
    auto ctx = CodegenContext::Create(BinaryView::fromModule(module), RecompilerConfig{});
    auto* host = ctx.graph.addFunction(kBase, 32, FunctionAuthority::PDATA, true);
    host->discover({{kBase, 12}, {kBase + 24, 8}}, {}, {});
    auto* caller = ctx.graph.addFunction(kBase + 40, 4, FunctionAuthority::CONFIG, true);
    caller->discover({{kBase + 40, 4}}, {}, {});
    ctx.graph.addUnresolvedJumpToFunction(caller->base(), caller->base(), target, scenario == 2,
                                          scenario == 3);
    REQUIRE(phases::Merge(ctx));
    CHECK_FALSE(ctx.graph.isEntryPoint(target));
    CHECK(caller->unresolvedJumps().size() == 1);
  }
}

TEST_CASE("Declared bounds alone do not turn a call to a different entry into a goto",
          "[codegen][discovery]") {
  FunctionGraph graph;
  auto* outer = graph.addFunction(kBase, 32, FunctionAuthority::PDATA, true);
  outer->discover({{kBase, 8}, {kBase + 24, 8}}, {}, {});
  auto* inner = graph.addFunction(kBase + 12, 4, FunctionAuthority::DISCOVERED, true);
  inner->discover({{kBase + 12, 4}}, {}, {});
  CHECK(graph.classifyTarget(kBase + 12, kBase, false) == TargetKind::Function);
}

TEST_CASE("An indirect tail dispatch leaves the following leaf discoverable",
          "[codegen][discovery]") {
  Analyzed a({Blr(), 0x81630000, 0x816B0024, 0x7D6903A6, 0x4E800420, Li(3, 42), Blr()}, {kBase});
  CHECK(a.IsEntry(kBase + 4));
  CHECK(a.IsEntry(kBase + 20));
  CHECK(a.ctx->graph.functionCount() == 3);
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("Shared blocks classify branches using the actual emitting function",
          "[codegen][discovery]") {
  FunctionGraph graph;
  auto* outer = graph.addFunction(kBase, 32, FunctionAuthority::DISCOVERED, true);
  outer->discover({{kBase, 32}}, {}, {});
  auto* inner = graph.addFunction(kBase + 16, 16, FunctionAuthority::DISCOVERED, true);
  inner->discover({{kBase + 16, 16}}, {}, {});
  CHECK(graph.classifyTarget(kBase + 4, kBase + 20, false, outer) == TargetKind::InternalLabel);
  CHECK(graph.classifyTarget(kBase + 16, kBase + 20, true, outer) == TargetKind::Function);
  CHECK(graph.classifyTarget(kBase + 16, kBase + 20, false, inner) == TargetKind::InternalLabel);
}

TEST_CASE("A return after an indirect tail dispatch is an entry when data points to it",
          "[codegen][discovery]") {
  // As below, but a method table holds 0x14: an empty method (Blood Stone's
  // sub_8218F208).
  Analyzed a({Blr(), 0x81630000, 0x816B0024, 0x7D6903A6, 0x4E800420, Blr()}, {kBase}, {},
             kBase + 20);
  CHECK(a.IsEntry(kBase + 20));
  CHECK(a.ctx->graph.functionCount() == 3);
  CHECK(a.ctx->graph.pendingCount() == 0);
}

TEST_CASE("An unreachable return after an indirect tail dispatch is not a new entry",
          "[codegen][discovery]") {
  Analyzed a({Blr(), 0x81630000, 0x816B0024, 0x7D6903A6, 0x4E800420, Blr()}, {kBase});
  CHECK_FALSE(a.IsEntry(kBase + 20));
  CHECK(a.ctx->graph.functionCount() == 2);
  CHECK(a.ctx->graph.pendingCount() == 0);
}
