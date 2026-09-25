/**
 * @file        float_precision_test.cpp
 * @brief       Opt-in scalar approximation rounding (RG-GDK-012, xenia-canary #1190)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cfloat>
#include <cmath>
#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/pipeline/shader/float_precision.h>

using rex::graphics::ReduceFloatPrecision;

namespace {

uint32_t Bits(float value) {
  return std::bit_cast<uint32_t>(value);
}

float Reduce21(uint32_t bits) {
  return ReduceFloatPrecision(std::bit_cast<float>(bits), 21);
}

}  // namespace

TEST_CASE("21-bit reduction rounds to nearest, halfway away from zero", "[float_precision]") {
  // The two discarded bits: below half truncates, half and above rounds up.
  CHECK(Bits(Reduce21(0x3F800001)) == 0x3F800000u);
  CHECK(Bits(Reduce21(0x3F800002)) == 0x3F800004u);
  CHECK(Bits(Reduce21(0x3F800003)) == 0x3F800004u);
  CHECK(Bits(Reduce21(0x3F800004)) == 0x3F800004u);
  // Away from zero for negative values too (magnitude bits round the same).
  CHECK(Bits(Reduce21(0xBF800002)) == 0xBF800004u);
  CHECK(Bits(Reduce21(0xBF800001)) == 0xBF800000u);
  // A carry into the exponent is still a correctly rounded value.
  CHECK(Bits(Reduce21(0x3FFFFFFE)) == 0x40000000u);
  // Results always have the low two mantissa bits clear.
  for (uint32_t bits : {0x3F812345u, 0x42F6E979u, 0x00800003u, 0xC1234567u}) {
    CHECK((Bits(Reduce21(bits)) & 3u) == 0u);
  }
}

TEST_CASE("21-bit reduction keeps non-finite values, signed zero and FLT_MAX finite",
          "[float_precision]") {
  CHECK(Bits(Reduce21(0x7F800000)) == 0x7F800000u);
  CHECK(Bits(Reduce21(0xFF800000)) == 0xFF800000u);
  CHECK(std::isnan(Reduce21(0x7FC00001)));
  CHECK(Bits(Reduce21(0x7FC00001)) == 0x7FC00001u);
  CHECK(Bits(Reduce21(0x00000000)) == 0x00000000u);
  CHECK(Bits(Reduce21(0x80000000)) == 0x80000000u);
  // FLT_MAX would round up into infinity; the truncated value is kept.
  CHECK(Bits(Reduce21(Bits(FLT_MAX))) == 0x7F7FFFFCu);
  CHECK(Bits(Reduce21(Bits(-FLT_MAX))) == 0xFF7FFFFCu);
}
