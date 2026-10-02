/**
 * Tests for the PowerPC floating-point rules in rex/ppc/fp.h that the PPC
 * corpus doesn't cover (RG-GDK-055). The corpus covers the arithmetic.
 */

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <rex/ppc/fp.h>

namespace fp = rex::ppc::fp;

TEST_CASE("lfs and stfs keep a signalling NaN signalling", "[ppc][fp]") {
  // Single SNaN 0x7F800001 widens to 0x7FF0000020000000, quiet bit clear.
  CHECK(fp::bits(fp::load_single(0x7F800001u)) == 0x7FF0000020000000ull);
  CHECK(fp::store_single(fp::from_bits(0x7FF0000020000000ull)) == 0x7F800001u);
  // A quiet NaN stays quiet, and ordinary values convert as before.
  CHECK(fp::bits(fp::load_single(0x7FC00001u)) == 0x7FF8000020000000ull);
  CHECK(fp::bits(fp::load_single(0x3F800000u)) == 0x3FF0000000000000ull);
  CHECK(fp::store_single(1.0) == 0x3F800000u);
  CHECK(fp::store_single(fp::from_bits(0xFFF4000000000000ull)) == 0xFFA00000u);
}

TEST_CASE("fctiw saturates and gives the sign-extended minimum for NaN", "[ppc][fp]") {
  CHECK(fp::to_int32(fp::from_bits(fp::kDefaultNaN), false) == int64_t(INT32_MIN));
  CHECK(uint64_t(fp::to_int32(fp::from_bits(fp::kDefaultNaN), true)) == 0xFFFFFFFF80000000ull);
  CHECK(fp::to_int32(3e9, true) == INT32_MAX);
  CHECK(fp::to_int32(-3e9, true) == int64_t(INT32_MIN));
  CHECK(fp::to_int32(-2.5, true) == -2);
  CHECK(fp::to_int64(fp::from_bits(fp::kDefaultNaN), true) == INT64_MIN);
}

TEST_CASE("Record forms set CR1 from what the operation raised", "[ppc][fp]") {
  rex::ppc::CRRegister cr1{};
  auto add = [](double a, double b, double) { return fp::add(a, b); };
  // 1 + 2 is exact: nothing raised.
  CHECK(fp::recorded(cr1, add, false, false, 1.0, 2.0) == 3.0);
  CHECK(cr1.raw() == 0);
  // 0.1 + 0.2 is inexact: FX alone.
  fp::recorded(cr1, add, false, false, 0.1, 0.2);
  CHECK(cr1.raw() == 0x8);
  // inf - inf is invalid: FX and VX, and the default QNaN.
  auto sub = [](double a, double b, double) { return fp::sub(a, b); };
  const double inf = fp::from_bits(fp::kInfinity);
  CHECK(fp::bits(fp::recorded(cr1, sub, false, false, inf, inf)) == fp::kDefaultNaN);
  CHECK(cr1.raw() == 0xA);
}
