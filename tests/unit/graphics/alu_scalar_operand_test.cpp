// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <array>
#include <cstdint>
#include <cstring>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/format/ucode.h>
#include <rex/graphics/pipeline/shader/shader.h>

namespace {

using rex::graphics::ParsedAluInstruction;
using rex::graphics::SwizzleSource;
using rex::graphics::ucode::AluInstruction;
using rex::graphics::ucode::AluScalarOpcode;
using rex::graphics::ucode::AluVectorOpcode;

AluInstruction MakeAluInstruction(AluVectorOpcode vector_opcode, AluScalarOpcode scalar_opcode,
                                  uint32_t src3_swizzle) {
  const std::array<uint32_t, 3> words = {
      (uint32_t(scalar_opcode) << 26) | (0b0001u << 20),
      src3_swizzle,
      (uint32_t(vector_opcode) << 24) | (0b111u << 29) | (3u << 16) | (2u << 8) | 1u,
  };
  AluInstruction instruction;
  static_assert(sizeof(instruction) == sizeof(words));
  std::memcpy(&instruction, words.data(), sizeof(words));
  return instruction;
}

ParsedAluInstruction Parse(AluVectorOpcode vector_opcode, AluScalarOpcode scalar_opcode,
                           uint32_t src3_swizzle = 0) {
  ParsedAluInstruction parsed;
  rex::graphics::ParseAluInstruction(MakeAluInstruction(vector_opcode, scalar_opcode, src3_swizzle),
                                     rex::graphics::xenos::ShaderType::kPixel, parsed);
  return parsed;
}

}  // namespace

TEST_CASE("Two-component scalar ops read W and X beside a two-source vector op",
          "[graphics][shader]") {
  const ParsedAluInstruction parsed = Parse(AluVectorOpcode::kMul, AluScalarOpcode::kMaxs);
  REQUIRE(parsed.scalar_operand_count == 1);
  REQUIRE(parsed.scalar_operands[0].component_count == 2);
  CHECK(parsed.scalar_operands[0].components[0] == SwizzleSource::kW);
  CHECK(parsed.scalar_operands[0].components[1] == SwizzleSource::kX);
}

TEST_CASE("Two-component scalar ops read W and Z beside a three-source vector op",
          "[graphics][shader]") {
  const ParsedAluInstruction parsed = Parse(AluVectorOpcode::kMad, AluScalarOpcode::kMaxs);
  REQUIRE(parsed.scalar_operand_count == 1);
  REQUIRE(parsed.scalar_operands[0].component_count == 2);
  CHECK(parsed.scalar_operands[0].components[0] == SwizzleSource::kW);
  CHECK(parsed.scalar_operands[0].components[1] == SwizzleSource::kZ);
}

TEST_CASE("The scalar Z read follows the source swizzle", "[graphics][shader]") {
  const uint32_t z_reads_x = 2u << 4;
  const ParsedAluInstruction parsed =
      Parse(AluVectorOpcode::kMad, AluScalarOpcode::kAdds, z_reads_x);
  CHECK(parsed.scalar_operands[0].components[0] == SwizzleSource::kW);
  CHECK(parsed.scalar_operands[0].components[1] == SwizzleSource::kX);
}

TEST_CASE("One-component scalar ops read only W", "[graphics][shader]") {
  const ParsedAluInstruction parsed = Parse(AluVectorOpcode::kMad, AluScalarOpcode::kRcp);
  REQUIRE(parsed.scalar_operand_count == 1);
  CHECK(parsed.scalar_operands[0].component_count == 1);
  CHECK(parsed.scalar_operands[0].components[0] == SwizzleSource::kW);
}
