#include <catch2/catch_test_macros.hpp>

#include <rex/codegen/binary_view.h>
#include <rex/codegen/function_scanner.h>
#include <rex/system/module.h>

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "codegen/decoded_binary.h"

namespace {

void StoreBigEndian(uint8_t* bytes, uint32_t value) {
  bytes[0] = static_cast<uint8_t>(value >> 24);
  bytes[1] = static_cast<uint8_t>(value >> 16);
  bytes[2] = static_cast<uint8_t>(value >> 8);
  bytes[3] = static_cast<uint8_t>(value);
}

class JumpTableModule final : public rex::runtime::Module {
 public:
  JumpTableModule(bool table_in_rb, bool has_gap = false, bool distinct_base = false)
      : Module(nullptr) {
    // lis r9/r11,0; slwi r10,r3,2; addi r9,r9/r11,0x2000; lwzx r8,rA,rB;
    // mtctr r8; bctr; blr; blr.
    const uint32_t ra = table_in_rb ? 10 : 9;
    const uint32_t rb = table_in_rb ? 9 : 10;
    const std::array<uint32_t, 8> instructions = {
        (15u << 26) | ((distinct_base ? 11u : 9u) << 21),
        (21u << 26) | (3u << 21) | (10u << 16) | (2u << 11) | (29u << 1),
        (14u << 26) | (9u << 21) | ((distinct_base ? 11u : 9u) << 16) | 0x2000u,
        (31u << 26) | (8u << 21) | (ra << 16) | (rb << 11) | (23u << 1),
        (31u << 26) | (8u << 21) | (9u << 16) | (467u << 1),
        0x4E800420u,
        0x4E800020u,
        0x4E800020u};
    for (size_t i = 0; i < instructions.size(); ++i) {
      StoreBigEndian(code_.data() + i * 4, instructions[i]);
    }
    StoreBigEndian(table_.data(), 0x1018);
    StoreBigEndian(table_.data() + (has_gap ? 8 : 4), 0x101C);
    binary_sections_.push_back(
        {".text", 0x1000, static_cast<uint32_t>(code_.size()), code_.data(), true, false});
    binary_sections_.push_back(
        {".rdata", 0x2000, static_cast<uint32_t>(table_.size()), table_.data(), false, false});
  }

  const std::string& name() const override { return name_; }
  bool is_executable() const override { return true; }
  uint32_t base_address() const override { return 0x1000; }
  uint32_t image_size() const override { return 0x1020; }

 private:
  std::string name_ = "jump_table_fixture";
  std::array<uint8_t, 32> code_{};
  std::array<uint8_t, 16> table_{};
};

}  // namespace

TEST_CASE("Absolute PPC jump table selects the scaled index in either load operand",
          "[codegen][jump_table]") {
  for (bool table_in_rb : {false, true}) {
    for (bool has_gap : {false, true}) {
      for (bool distinct_base : {false, true}) {
        JumpTableModule module(table_in_rb, has_gap, distinct_base);
        auto binary = rex::codegen::BinaryView::fromModule(module);
        rex::codegen::DecodedBinary decoded(binary);
        decoded.decode();
        const auto* region = decoded.regionContaining(0x1000);
        REQUIRE(region != nullptr);
        auto table = rex::codegen::detectJumpTable(decoded, 0x1014, *region, 0x1000, 0x1020);
        REQUIRE(table.has_value());
        CHECK(table->indexRegister == 3);
        const std::vector<uint32_t> expected = has_gap ? std::vector<uint32_t>{0x1018, 0, 0x101C}
                                                       : std::vector<uint32_t>{0x1018, 0x101C};
        CHECK(table->targets == expected);
      }
    }
  }
}
