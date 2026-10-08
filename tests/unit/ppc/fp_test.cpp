/**
 * Tests for the PowerPC floating-point rules in rex/ppc/fp.h that the PPC
 * corpus doesn't cover (RG-GDK-055). The corpus covers the arithmetic.
 */

#include <cstdint>
#include <cmath>
#include <limits>

#include <catch2/catch_test_macros.hpp>

#include <rex/ppc/fp.h>

namespace fp = rex::ppc::fp;

TEST_CASE("FPSCR result classes match PowerPC FPRF encodings", "[ppc][fp]") {
  using FPSCR = rex::ppc::FPSCRRegister;
  CHECK(fp::result_class(fp::from_bits(fp::kDefaultNaN)) == 0b10001);
  CHECK(fp::result_class(-std::numeric_limits<double>::infinity()) == 0b01001);
  CHECK(fp::result_class(-1.0) == 0b01000);
  CHECK(fp::result_class(-std::numeric_limits<double>::denorm_min()) == 0b11000);
  CHECK(fp::result_class(-0.0) == 0b10010);
  CHECK(fp::result_class(0.0) == 0b00010);
  CHECK(fp::result_class(std::numeric_limits<double>::denorm_min()) == 0b10100);
  CHECK(fp::result_class(double(std::numeric_limits<float>::denorm_min()), true) == 0b10100);
  CHECK(fp::result_class(1.0) == 0b00100);
  CHECK(fp::result_class(std::numeric_limits<double>::infinity()) == 0b00101);

  rex::ppc::FPSCRRegister fpscr{};
  fpscr.guest_bits = FPSCR::kFR | FPSCR::kFI;
  rex::ppc::CRRegister cr{};
  fp::compare(fpscr, cr, 1.0, 2.0, false);
  CHECK((fpscr.guest_bits & FPSCR::kFPCC) == FPSCR::kFPCCLess);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));
  fp::compare(fpscr, cr, 2.0, 1.0, false);
  CHECK((fpscr.guest_bits & FPSCR::kFPCC) == FPSCR::kFPCCGreater);
  fp::compare(fpscr, cr, 1.0, 1.0, false);
  CHECK((fpscr.guest_bits & FPSCR::kFPCC) == FPSCR::kFPCCEqual);
  fp::compare(fpscr, cr, fp::from_bits(fp::kDefaultNaN), 1.0, false);
  CHECK((fpscr.guest_bits & FPSCR::kFPCC) == FPSCR::kFPCCUnordered);
}

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

TEST_CASE("integer conversions update FR and FI for the guest rounding mode", "[ppc][fp]") {
  using FPSCR = rex::ppc::FPSCRRegister;
  using Platform = FPSCR::Platform;
  const uint32_t original_csr = Platform::getcsr();
  FPSCR fpscr{};
  fpscr.csr = original_csr;

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  CHECK(fp::tracked_convert(fpscr, nullptr, 1.5, false, false) == 2);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));
  CHECK(fp::tracked_convert(fpscr, nullptr, 1.25, false, false) == 1);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);

  fpscr.storeFromGuest(rex::ppc::kRoundTowardZero);
  CHECK(fp::tracked_convert(fpscr, nullptr, 1.25, true, false) == 1);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);

  fpscr.storeFromGuest(rex::ppc::kRoundUp);
  CHECK(fp::tracked_convert(fpscr, nullptr, 1.25, false, false) == 2);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));
  CHECK(fp::tracked_convert(fpscr, nullptr, -1.25, false, false) == -1);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);

  fpscr.storeFromGuest(rex::ppc::kRoundDown);
  CHECK(fp::tracked_convert(fpscr, nullptr, 1.25, false, false) == 1);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);
  CHECK(fp::tracked_convert(fpscr, nullptr, -1.25, false, false) == -2);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  CHECK(fp::tracked_convert(fpscr, nullptr, 3e9, false, false) == INT32_MAX);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == 0);
  Platform::setcsr(original_csr);
}

TEST_CASE("integer-to-double conversion tracks FPRF FR and FI", "[ppc][fp]") {
  using FPSCR = rex::ppc::FPSCRRegister;
  using Platform = FPSCR::Platform;
  const uint32_t original_csr = Platform::getcsr();
  FPSCR fpscr{};
  fpscr.csr = original_csr;

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  CHECK(fp::bits(fp::tracked_from_integer(fpscr, nullptr, 9007199254740993ll)) ==
        0x4340000000000000ull);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI | FPSCR::kXX | FPSCR::kFPRF)) ==
        (FPSCR::kFI | FPSCR::kXX | FPSCR::kFPCCGreater));

  fpscr.storeFromGuest(rex::ppc::kRoundUp);
  CHECK(fp::bits(fp::tracked_from_integer(fpscr, nullptr, 9007199254740993ll)) ==
        0x4340000000000001ull);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  CHECK(fp::bits(fp::tracked_from_integer(fpscr, nullptr, INT64_MIN)) == 0xC3E0000000000000ull);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == 0);
  CHECK((fpscr.guest_bits & FPSCR::kFPRF) == 0x8000);
  Platform::setcsr(original_csr);
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

TEST_CASE("Scalar arithmetic accumulates FPSCR exception causes and summaries", "[ppc][fp]") {
  rex::ppc::FPSCRRegister fpscr{};
  auto add = [](double a, double b, double) { return fp::add(a, b); };
  const uint32_t original_csr = rex::ppc::FPSCRRegister::Platform::getcsr();
  fpscr.csr = original_csr;

  // Inexact is sticky and sets FX when the cause flag first changes.
  CHECK(fp::tracked(fpscr, nullptr, add, 0, false, false, fp::TrackedOp::kAdd, 0.1, 0.2) != 0.0);
  CHECK((fpscr.guest_bits & (rex::ppc::FPSCRRegister::kFX | rex::ppc::FPSCRRegister::kXX)) ==
        (rex::ppc::FPSCRRegister::kFX | rex::ppc::FPSCRRegister::kXX));
  CHECK((fpscr.guest_bits & rex::ppc::FPSCRRegister::kFPRF) ==
        rex::ppc::FPSCRRegister::kFPCCGreater);
  CHECK((fpscr.guest_bits & (rex::ppc::FPSCRRegister::kFR | rex::ppc::FPSCRRegister::kFI)) ==
        (rex::ppc::FPSCRRegister::kFR | rex::ppc::FPSCRRegister::kFI));

  // An invalid operation records its PowerPC subcause and invalid summary.
  fpscr.guest_bits = 0;
  const double infinity = fp::from_bits(fp::kInfinity);
  auto sub = [](double a, double b, double) { return fp::sub(a, b); };
  fp::tracked(fpscr, nullptr, sub, fp::sub_invalid_causes(infinity, infinity), false, false,
              fp::TrackedOp::kSub, infinity, infinity);
  CHECK((fpscr.guest_bits & (rex::ppc::FPSCRRegister::kFX | rex::ppc::FPSCRRegister::kVX |
                             rex::ppc::FPSCRRegister::kVXISI)) ==
        (rex::ppc::FPSCRRegister::kFX | rex::ppc::FPSCRRegister::kVX |
         rex::ppc::FPSCRRegister::kVXISI));
  CHECK((fpscr.guest_bits & rex::ppc::FPSCRRegister::kFPRF) == 0x11000);

  // An enabled invalid exception leaves the result fields unchanged.
  fpscr.guest_bits = rex::ppc::FPSCRRegister::kVE | rex::ppc::FPSCRRegister::kFPCCGreater;
  fp::tracked(fpscr, nullptr, sub, fp::sub_invalid_causes(infinity, infinity), false, false,
              fp::TrackedOp::kSub, infinity, infinity);
  CHECK((fpscr.guest_bits & rex::ppc::FPSCRRegister::kFPRF) ==
        rex::ppc::FPSCRRegister::kFPCCGreater);

  // FEX reflects the corresponding enable and clears when the enabled cause is cleared.
  fpscr.storeFromGuest(rex::ppc::FPSCRRegister::kVE);
  CHECK((fpscr.guest_bits & rex::ppc::FPSCRRegister::kFEX) == 0);
  fpscr.recordExceptions(rex::ppc::FPSCRRegister::kVXSNAN);
  CHECK((fpscr.guest_bits & rex::ppc::FPSCRRegister::kFEX) != 0);
  fpscr.storeFromGuest(rex::ppc::FPSCRRegister::kVE);
  CHECK((fpscr.guest_bits & rex::ppc::FPSCRRegister::kFEX) == 0);

  rex::ppc::FPSCRRegister::Platform::setcsr(original_csr);
}

TEST_CASE("arithmetic rounding updates FR and FI from the rounded fraction", "[ppc][fp]") {
  using FPSCR = rex::ppc::FPSCRRegister;
  using Platform = FPSCR::Platform;
  const uint32_t original_csr = Platform::getcsr();
  FPSCR fpscr{};
  fpscr.csr = original_csr;
  auto add = [](double a, double b, double) { return fp::add(a, b); };
  const double half_ulp = std::ldexp(1.0, -53);

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  CHECK(fp::tracked(fpscr, nullptr, add, 0, false, false, fp::TrackedOp::kAdd, 1.0, half_ulp) ==
        1.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);

  fpscr.storeFromGuest(rex::ppc::kRoundUp);
  CHECK(fp::tracked(fpscr, nullptr, add, 0, false, false, fp::TrackedOp::kAdd, 1.0, half_ulp) ==
        std::nextafter(1.0, 2.0));
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  fpscr.storeFromGuest(rex::ppc::kRoundDown);
  CHECK(fp::tracked(fpscr, nullptr, add, 0, false, false, fp::TrackedOp::kAdd, 1.0, half_ulp) ==
        1.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);
  CHECK(fp::tracked(fpscr, nullptr, add, 0, false, false, fp::TrackedOp::kAdd, -1.0, -half_ulp) ==
        std::nextafter(-1.0, -2.0));
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  auto multiply = [](double a, double b, double) { return fp::mul(a, b); };
  const double next_one = std::nextafter(1.0, 2.0);
  fp::tracked(fpscr, nullptr, multiply, 0, false, false, fp::TrackedOp::kMul, next_one, next_one);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == FPSCR::kFI);

  auto madd = [](double a, double b, double c) { return fp::madd(a, b, c); };
  fp::tracked(fpscr, nullptr, madd, 0, false, false, fp::TrackedOp::kMadd, next_one,
              1.0 - std::ldexp(1.0, -52), 0.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  fpscr.storeFromGuest(rex::ppc::kRoundNearest);
  auto sub = [](double a, double b, double) { return fp::sub(a, b); };
  fp::tracked(fpscr, nullptr, sub, 0, false, false, fp::TrackedOp::kSub, 1.0, std::ldexp(1.0, -54));
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  auto divide = [](double a, double b, double) { return fp::div(a, b); };
  fp::tracked(fpscr, nullptr, divide, 0, false, false, fp::TrackedOp::kDiv, 1.0, 10.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  auto sqrt = [](double a, double, double) { return fp::sqrt(a); };
  fp::tracked(fpscr, nullptr, sqrt, 0, false, false, fp::TrackedOp::kSqrt, 2.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  auto msub = [](double a, double b, double c) { return fp::msub(a, b, c); };
  fp::tracked(fpscr, nullptr, msub, 0, false, false, fp::TrackedOp::kMsub, next_one,
              1.0 - std::ldexp(1.0, -52), 0.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  auto nmadd = [](double a, double b, double c) { return fp::nmadd(a, b, c); };
  fp::tracked(fpscr, nullptr, nmadd, 0, false, false, fp::TrackedOp::kNmadd, next_one,
              1.0 - std::ldexp(1.0, -52), 0.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  auto nmsub = [](double a, double b, double c) { return fp::nmsub(a, b, c); };
  fp::tracked(fpscr, nullptr, nmsub, 0, false, false, fp::TrackedOp::kNmsub, next_one,
              1.0 - std::ldexp(1.0, -52), 0.0);
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));

  auto round_single = [](double a, double, double) { return fp::to_single(a); };
  fpscr.storeFromGuest(rex::ppc::kRoundUp);
  CHECK(fp::tracked(fpscr, nullptr, round_single, 0, false, true, fp::TrackedOp::kRoundSingle,
                    1.0 + std::ldexp(1.0, -25)) == double(std::nextafter(1.0f, 2.0f)));
  CHECK((fpscr.guest_bits & (FPSCR::kFR | FPSCR::kFI)) == (FPSCR::kFR | FPSCR::kFI));
  Platform::setcsr(original_csr);
}

TEST_CASE("Host code runs in the host FP mode, guest code in its own", "[ppc][fp]") {
  using Platform = rex::ppc::FPSCRRegister::Platform;
  constexpr uint32_t kGuestBits = rex::ppc::FPSCRRegister::GuestMask;
  const uint32_t original = Platform::getcsr();

  // Guest code with VMX flush on and rounding toward zero calls an export.
  rex::ppc::FPSCRRegister guest{};
  guest.csr = original & ~kGuestBits;
  guest.storeFromGuest(rex::ppc::kRoundTowardZero);
  guest.enableFlushModeUnconditional();
  const uint32_t guest_mode = guest.csr;
  {
    rex::ppc::HostFpScope host(guest);
    CHECK((Platform::getcsr() & kGuestBits) == 0);
    {
      // The export calls back into guest code, which switches to rounding
      // down.
      rex::ppc::GuestFpScope callback(guest);
      CHECK(Platform::getcsr() == guest_mode);
      guest.storeFromGuest(rex::ppc::kRoundDown);
    }
    CHECK((Platform::getcsr() & kGuestBits) == 0);
  }
  // Back in guest code: the callback's rounding mode, and the cache agrees.
  CHECK(Platform::getcsr() == guest.csr);
  CHECK(guest.loadFromHost() == rex::ppc::kRoundDown);
  CHECK((guest.csr & rex::ppc::FPSCRRegister::FlushMask) == rex::ppc::FPSCRRegister::FlushMask);

  Platform::setcsr(original);
}
