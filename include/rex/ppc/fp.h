/**
 * @file        ppc/fp.h
 * @brief       PowerPC floating-point rules the host's IEEE arithmetic does not follow
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 *
 * @remarks     Rules measured against Xbox 360 hardware captures (xenia-edge
 *              PPC test corpus, RG-GDK-055); see docs/upstream-tracking.md.
 */

#pragma once

#include <cfenv>
#include <cmath>
#include <cstdint>
#include <cstring>

#include <simde/x86/fma.h>
#include <simde/x86/sse.h>
#include <simde/x86/sse2.h>
#include <simde/x86/sse4.1.h>

#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#include <intrin.h>
#endif

#include <rex/ppc/context.h>

namespace rex::ppc::fp {

//=============================================================================
// Scalar classification
//=============================================================================

/// PowerPC's default QNaN is positive; x86's is negative.
inline constexpr uint64_t kDefaultNaN = 0x7FF8000000000000ull;
inline constexpr uint64_t kQuietBit = 0x0008000000000000ull;
inline constexpr uint64_t kMagnitude = 0x7FFFFFFFFFFFFFFFull;
inline constexpr uint64_t kInfinity = 0x7FF0000000000000ull;

inline uint64_t bits(double x) noexcept {
  uint64_t u;
  std::memcpy(&u, &x, sizeof(u));
  return u;
}

inline double from_bits(uint64_t u) noexcept {
  double x;
  std::memcpy(&x, &u, sizeof(x));
  return x;
}

inline bool is_nan(double x) noexcept {
  return (bits(x) & kMagnitude) > kInfinity;
}
inline bool is_snan(double x) noexcept {
  return is_nan(x) && !(bits(x) & kQuietBit);
}
inline bool is_finite(double x) noexcept {
  return (bits(x) & kMagnitude) < kInfinity;
}
inline bool is_denormal(double x) noexcept {
  return (bits(x) & kMagnitude) - 1 < 0x000FFFFFFFFFFFFFull;
}
inline double quiet(double x) noexcept {
  return from_bits(bits(x) | kQuietBit);
}

/// A NaN result is the first NaN operand, quieted with its sign kept, or the
/// default QNaN when the operation itself was invalid.
inline double nan_result(double a, double b) noexcept {
  if (is_nan(a))
    return quiet(a);
  if (is_nan(b))
    return quiet(b);
  return from_bits(kDefaultNaN);
}

inline double nan_result(double a, double b, double c) noexcept {
  if (is_nan(a))
    return quiet(a);
  return nan_result(b, c);
}

/// Single-precision arithmetic answers the default QNaN when every operand is
/// finite and one is a denormalized double. Divide and square root don't.
/// It sits on every single-precision op, so the hot path is one subtract and
/// compare per operand (a zero wraps to the top and never reads as
/// denormal), with the finite check only once one hits (as xenia-edge
/// 078a07b53 does).
inline bool single_denormal(double a, double b, double c) noexcept {
  if (__builtin_expect(is_denormal(a) | is_denormal(b) | is_denormal(c), 0))
    return is_finite(a) && is_finite(b) && is_finite(c);
  return false;
}
inline bool single_denormal(double a, double b) noexcept {
  return single_denormal(a, b, b);
}

inline double to_single(double x) noexcept {
  return double(float(x));
}

//=============================================================================
// Scalar arithmetic
//=============================================================================
// The host result is kept unless it is a NaN, which costs one compare.

inline double add(double a, double b) noexcept {
  double r = a + b;
  return r == r ? r : nan_result(a, b);
}
inline double sub(double a, double b) noexcept {
  double r = a - b;
  return r == r ? r : nan_result(a, b);
}
inline double mul(double a, double b) noexcept {
  double r = a * b;
  return r == r ? r : nan_result(a, b);
}
inline double div(double a, double b) noexcept {
  double r = a / b;
  return r == r ? r : nan_result(a, b);
}
inline double sqrt(double b) noexcept {
  double r = std::sqrt(b);
  return r == r ? r : nan_result(b, b);
}

// Multiply-add takes frA, frC, frB, but a NaN is chosen in A, B, C order. The
// negated forms leave a NaN result's sign alone.
inline double madd(double a, double c, double b) noexcept {
  double r = std::fma(a, c, b);
  return r == r ? r : nan_result(a, b, c);
}
inline double msub(double a, double c, double b) noexcept {
  double r = std::fma(a, c, -b);
  return r == r ? r : nan_result(a, b, c);
}
inline double nmadd(double a, double c, double b) noexcept {
  double r = std::fma(a, c, b);
  return r == r ? -r : nan_result(a, b, c);
}
inline double nmsub(double a, double c, double b) noexcept {
  double r = std::fma(a, c, -b);
  return r == r ? -r : nan_result(a, b, c);
}

// The single-precision forms keep the host result unless it is a NaN or an
// operand is a denormalized double; both are rare, so one unlikely branch
// covers them and the exact answer is worked out out of line.

[[gnu::cold, gnu::noinline]] inline double SingleSlow(double r, double a, double b) noexcept {
  if (single_denormal(a, b))
    return from_bits(kDefaultNaN);
  return to_single(r == r ? r : nan_result(a, b));
}
// r is the multiply-add result (negated for the negated forms).
[[gnu::cold, gnu::noinline]] inline double SingleSlow(double r, double a, double c,
                                                      double b) noexcept {
  if (single_denormal(a, c, b))
    return from_bits(kDefaultNaN);
  return to_single(r == r ? r : nan_result(a, b, c));
}

inline bool Suspect(double r, double a, double b) noexcept {
  return __builtin_expect((r != r) | is_denormal(a) | is_denormal(b), 0);
}
inline bool Suspect(double r, double a, double c, double b) noexcept {
  return __builtin_expect((r != r) | is_denormal(a) | is_denormal(c) | is_denormal(b), 0);
}

inline double adds(double a, double b) noexcept {
  const double r = a + b;
  return Suspect(r, a, b) ? SingleSlow(r, a, b) : to_single(r);
}
inline double subs(double a, double b) noexcept {
  const double r = a - b;
  return Suspect(r, a, b) ? SingleSlow(r, a, b) : to_single(r);
}
inline double muls(double a, double b) noexcept {
  const double r = a * b;
  return Suspect(r, a, b) ? SingleSlow(r, a, b) : to_single(r);
}
// A denormalized operand keeps the double quotient and root, unrounded.
inline double divs(double a, double b) noexcept {
  const double r = div(a, b);
  return single_denormal(a, b) ? r : to_single(r);
}
inline double sqrts(double b) noexcept {
  const double r = sqrt(b);
  return single_denormal(b, b) ? r : to_single(r);
}
inline double madds(double a, double c, double b) noexcept {
  const double r = std::fma(a, c, b);
  return Suspect(r, a, c, b) ? SingleSlow(r, a, c, b) : to_single(r);
}
inline double msubs(double a, double c, double b) noexcept {
  const double r = std::fma(a, c, -b);
  return Suspect(r, a, c, b) ? SingleSlow(r, a, c, b) : to_single(r);
}
inline double nmadds(double a, double c, double b) noexcept {
  const double r = -std::fma(a, c, b);
  return Suspect(r, a, c, b) ? SingleSlow(r, a, c, b) : to_single(r);
}
inline double nmsubs(double a, double c, double b) noexcept {
  const double r = -std::fma(a, c, -b);
  return Suspect(r, a, c, b) ? SingleSlow(r, a, c, b) : to_single(r);
}

/// frsqrte: the Xenon's estimate, 5 bits from a 16-entry table indexed by the
/// exponent's parity and the top 3 mantissa bits (xenia-edge's frsqrte helper).
inline double rsqrte(double x) noexcept {
  static constexpr uint8_t kTable[16] = {241, 216, 192, 168, 152, 136, 128, 112,
                                         96,  76,  60,  48,  32,  24,  16,  8};
  uint64_t u = bits(x);
  if ((u & kMagnitude) == 0)
    return from_bits((u & ~kMagnitude) | kInfinity);  // +-0 -> +-inf
  if ((u & kInfinity) == kInfinity) {
    if (u == kInfinity)
      return 0.0;
    if (u & 0x000FFFFFFFFFFFFFull)
      return from_bits(u | kQuietBit);  // NaN, quieted
    return from_bits(kDefaultNaN);      // -inf
  }
  if (u >> 63)
    return from_bits(kDefaultNaN);
  int32_t exponent = int32_t(u >> 52);
  uint64_t mantissa = u & 0x000FFFFFFFFFFFFFull;
  if (exponent == 0) {  // denormal: normalise
    const int leading = __builtin_clzll(mantissa);
    mantissa <<= leading - 11;
    exponent = 12 - leading;
  }
  const uint32_t index = ((uint32_t(exponent & 1) << 3) | uint32_t((mantissa >> 49) & 7)) ^ 8;
  const uint64_t result_exponent = uint64_t(1022 - ((exponent - 1023) >> 1)) & 0x7FF;
  return from_bits((result_exponent << 52) | (uint64_t(kTable[index]) << 44));
}

/// The vrsqrtefp table (src/system/ppc_fp.cpp).
const uint32_t* VRsqrteTable();

/// vrsqrtefp on one element, with VSCR[NJ] set (denormals as zero).
inline uint32_t vrsqrte(uint32_t u) noexcept {
  const uint32_t exponent = (u >> 23) & 0xFF;
  if (!(u >> 31) && exponent - 1 < 254)  // positive normal
    return VRsqrteTable()[(u >> 9) & 0x7FFF] - (((u >> 24) - 63) << 23);
  if ((u & 0x7FFFFFFFu) > 0x7F800000u)
    return u | 0x00400000u;  // NaN, quieted
  if (u == 0x7F800000u)
    return 0;  // +inf
  if ((u & 0x7F800000u) == 0)
    return (u & 0x80000000u) | 0x7F800000u;  // +-0 and denormals -> +-inf
  return 0x7FC00000u;                        // negative: the default QNaN
}

/// fctiw/fctiwz: a NaN or too-negative value gives the sign-extended most
/// negative word, a too-positive one the most positive.
inline int64_t to_int32(double x, bool truncate) noexcept {
  if (is_nan(x))
    return int64_t(INT32_MIN);
  const double r = truncate ? std::trunc(x) : std::nearbyint(x);
  if (r >= 2147483648.0)
    return INT32_MAX;
  if (r < -2147483648.0)
    return int64_t(INT32_MIN);
  return int64_t(int32_t(r));
}

/// fctid/fctidz: as to_int32, on a doubleword.
inline int64_t to_int64(double x, bool truncate) noexcept {
  if (is_nan(x))
    return INT64_MIN;
  const double r = truncate ? std::trunc(x) : std::nearbyint(x);
  if (r >= 9223372036854775808.0)
    return INT64_MAX;
  if (r < -9223372036854775808.0)
    return INT64_MIN;
  return int64_t(r);
}

/// lfs: widening a single never quiets it on PowerPC, where the host convert
/// sets a signalling NaN's quiet bit.
inline double load_single(uint32_t u) noexcept {
  float f;
  std::memcpy(&f, &u, sizeof(f));
  const double d = double(f);
  if ((u & 0x7FFFFFFFu) > 0x7F800000u && !(u & 0x00400000u))
    return from_bits(bits(d) & ~kQuietBit);
  return d;
}

/// stfs: as load_single, narrowing.
inline uint32_t store_single(double d) noexcept {
  const float f = float(d);
  uint32_t u;
  std::memcpy(&u, &f, sizeof(u));
  if (is_snan(d))
    u &= ~0x00400000u;
  return u;
}

//=============================================================================
// Record forms (fadd. ...): CR1 is FX, FEX, VX, OX
//=============================================================================
// FX summarises every exception the instruction raised, VX the invalid ones
// and OX overflow. FEX needs the exception enables, which nothing sets. The
// host status flags supply what the arithmetic raised; `invalid` adds what
// the host doesn't report (a signalling operand it quieted, or 0 x inf with a
// quiet NaN addend). The flags are read per instruction rather than kept
// sticky in the FPSCR.

inline bool any_snan(double a, double b = 0.0, double c = 0.0) noexcept {
  return is_snan(a) || is_snan(b) || is_snan(c);
}

inline uint32_t snan_causes(double a, double b = 0.0, double c = 0.0) noexcept {
  return any_snan(a, b, c) ? FPSCRRegister::kVXSNAN : 0;
}

/// Compare operands and record the invalid causes specified by fcmpu/fcmpo.
inline void compare(FPSCRRegister& fpscr, CRRegister& cr, double a, double b,
                    bool ordered) noexcept {
  cr.compare(a, b);
  uint32_t causes = snan_causes(a, b);
  const bool has_nan = is_nan(a) || is_nan(b);
  const bool has_quiet_nan = (is_nan(a) && !is_snan(a)) || (is_nan(b) && !is_snan(b));
  if (ordered && (has_quiet_nan || (has_nan && !(fpscr.guest_bits & FPSCRRegister::kVE)))) {
    causes |= FPSCRRegister::kVXVC;
  }
  fpscr.recordExceptions(causes);

  // Compare updates FPCC, but preserves C, FR, and FI. An ordered compare
  // that raises an enabled invalid exception still reports unordered FPCC.
  uint32_t fpcc = FPSCRRegister::kFPCCUnordered;
  if (!has_nan) {
    fpcc = a < b ? FPSCRRegister::kFPCCLess
                 : (a > b ? FPSCRRegister::kFPCCGreater : FPSCRRegister::kFPCCEqual);
  }
  fpscr.guest_bits = (fpscr.guest_bits & ~FPSCRRegister::kFPCC) | fpcc;
}

/// Return the PowerPC FPRF encoding for a floating-point result.
inline uint32_t bits32(float x) noexcept;

inline uint32_t result_class(double result, bool single_precision = false) noexcept {
  constexpr uint32_t kQuietNaN = 0b10001;
  constexpr uint32_t kNegativeInfinity = 0b01001;
  constexpr uint32_t kNegativeNormal = 0b01000;
  constexpr uint32_t kNegativeDenormal = 0b11000;
  constexpr uint32_t kNegativeZero = 0b10010;
  constexpr uint32_t kPositiveZero = 0b00010;
  constexpr uint32_t kPositiveDenormal = 0b10100;
  constexpr uint32_t kPositiveNormal = 0b00100;
  constexpr uint32_t kPositiveInfinity = 0b00101;

  if (single_precision) {
    const uint32_t single = bits32(float(result));
    const uint32_t magnitude = single & 0x7FFFFFFFu;
    if (magnitude > 0x7F800000u)
      return kQuietNaN;
    if (magnitude == 0x7F800000u)
      return (single >> 31) ? kNegativeInfinity : kPositiveInfinity;
    if (magnitude == 0)
      return (single >> 31) ? kNegativeZero : kPositiveZero;
    if ((magnitude & 0x7F800000u) == 0)
      return (single >> 31) ? kNegativeDenormal : kPositiveDenormal;
    return (single >> 31) ? kNegativeNormal : kPositiveNormal;
  }
  if (is_nan(result))
    return kQuietNaN;
  const uint64_t magnitude = bits(result) & kMagnitude;
  if (magnitude == kInfinity)
    return std::signbit(result) ? kNegativeInfinity : kPositiveInfinity;
  if (magnitude == 0)
    return std::signbit(result) ? kNegativeZero : kPositiveZero;
  if (is_denormal(result))
    return std::signbit(result) ? kNegativeDenormal : kPositiveDenormal;
  return std::signbit(result) ? kNegativeNormal : kPositiveNormal;
}

inline void set_result_class(FPSCRRegister& fpscr, double result,
                             bool single_precision = false) noexcept {
  const uint32_t encoded = result_class(result, single_precision) << 12;
  fpscr.guest_bits = (fpscr.guest_bits & ~FPSCRRegister::kFPRF) | encoded;
}

inline uint32_t add_invalid_causes(double a, double b) noexcept {
  uint32_t causes = snan_causes(a, b);
  if (std::isinf(a) && std::isinf(b) && std::signbit(a) != std::signbit(b))
    causes |= FPSCRRegister::kVXISI;
  return causes;
}

inline uint32_t sub_invalid_causes(double a, double b) noexcept {
  uint32_t causes = snan_causes(a, b);
  if (std::isinf(a) && std::isinf(b) && std::signbit(a) == std::signbit(b))
    causes |= FPSCRRegister::kVXISI;
  return causes;
}

inline uint32_t mul_invalid_causes(double a, double b) noexcept {
  uint32_t causes = snan_causes(a, b);
  const uint64_t ma = bits(a) & kMagnitude, mb = bits(b) & kMagnitude;
  if ((ma == 0 && mb == kInfinity) || (ma == kInfinity && mb == 0))
    causes |= FPSCRRegister::kVXIMZ;
  return causes;
}

inline uint32_t div_invalid_causes(double a, double b) noexcept {
  uint32_t causes = snan_causes(a, b);
  const uint64_t ma = bits(a) & kMagnitude, mb = bits(b) & kMagnitude;
  if (ma == kInfinity && mb == kInfinity)
    causes |= FPSCRRegister::kVXIDI;
  if (ma == 0 && mb == 0)
    causes |= FPSCRRegister::kVXZDZ;
  return causes;
}

inline uint32_t sqrt_invalid_causes(double a) noexcept {
  uint32_t causes = snan_causes(a);
  const uint64_t magnitude = bits(a) & kMagnitude;
  if ((bits(a) >> 63) && magnitude != 0 && !is_nan(a))
    causes |= FPSCRRegister::kVXSQRT;
  return causes;
}

/// x86 skips the invalid signal for 0 x inf when the addend is a quiet NaN.
inline uint32_t madd_invalid_causes(double a, double c, double b,
                                    bool subtract_addend = false) noexcept {
  const uint64_t ma = bits(a) & kMagnitude, mc = bits(c) & kMagnitude;
  uint32_t causes = snan_causes(a, c, b);
  if ((ma == 0 && mc == kInfinity) || (ma == kInfinity && mc == 0))
    causes |= FPSCRRegister::kVXIMZ;
  const bool product_infinite =
      !is_nan(a) && !is_nan(c) && ((ma == kInfinity && mc != 0) || (mc == kInfinity && ma != 0));
  const bool product_negative = std::signbit(a) != std::signbit(c);
  const bool addend_negative = std::signbit(b) != subtract_addend;
  if (product_infinite && !is_nan(b) && std::isinf(b) && product_negative != addend_negative)
    causes |= FPSCRRegister::kVXISI;
  return causes;
}

inline uint32_t msub_invalid_causes(double a, double c, double b) noexcept {
  return madd_invalid_causes(a, c, b, true);
}

inline void set_cr1(CRRegister& cr1, int raised, bool invalid) noexcept {
  const bool vx = invalid || (raised & FE_INVALID);
  cr1.lt = vx || (raised & (FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT));  // FX
  cr1.gt = 0;                                                                          // FEX
  cr1.eq = vx;                                                                         // VX
  cr1.so = (raised & FE_OVERFLOW) != 0;                                                // OX
}

inline void set_cr1_from_fpscr(CRRegister& cr1, const FPSCRRegister& fpscr) noexcept {
  cr1.lt = (fpscr.guest_bits & FPSCRRegister::kFX) != 0;
  cr1.gt = (fpscr.guest_bits & FPSCRRegister::kFEX) != 0;
  cr1.eq = (fpscr.guest_bits & FPSCRRegister::kVX) != 0;
  cr1.so = (fpscr.guest_bits & FPSCRRegister::kOX) != 0;
}

inline uint32_t host_exception_causes(int raised) noexcept {
  uint32_t causes = 0;
  if (raised & FE_DIVBYZERO)
    causes |= FPSCRRegister::kZX;
  if (raised & FE_OVERFLOW)
    causes |= FPSCRRegister::kOX;
  if (raised & FE_UNDERFLOW)
    causes |= FPSCRRegister::kUX;
  if (raised & FE_INEXACT)
    causes |= FPSCRRegister::kXX;
  return causes;
}

enum class TrackedOp { kRoundSingle, kAdd, kSub, kMul, kDiv, kMadd, kMsub, kNmadd, kNmsub, kSqrt };

inline void set_rounding_flags(FPSCRRegister& fpscr, bool fraction_rounded, bool inexact) noexcept {
  fpscr.guest_bits &= ~(FPSCRRegister::kFR | FPSCRRegister::kFI);
  if (fraction_rounded)
    fpscr.guest_bits |= FPSCRRegister::kFR;
  if (inexact)
    fpscr.guest_bits |= FPSCRRegister::kFI;
}

inline double sum_residual(double a, double b, double rounded) noexcept {
  const double sum = a + b;
  const double b_virtual = sum - a;
  const double error = (a - (sum - b_virtual)) + (b - b_virtual);
  return error + (sum - rounded);
}

/// Return the sign of exact-result minus rounded-result. This uses an
/// error-free residual for addition and fused multiply-add to avoid comparing
/// only the already-rounded host result.
inline double rounding_residual(TrackedOp op, double a, double b, double c,
                                double rounded) noexcept {
  switch (op) {
    case TrackedOp::kRoundSingle:
      return a - rounded;
    case TrackedOp::kAdd:
      return sum_residual(a, b, rounded);
    case TrackedOp::kSub:
      return sum_residual(a, -b, rounded);
    case TrackedOp::kMul:
      return std::fma(a, b, -rounded);
    case TrackedOp::kDiv: {
      const double remainder = std::fma(-rounded, b, a);
      return remainder / b;
    }
    case TrackedOp::kMadd:
      return std::fma(a, b, c - rounded);
    case TrackedOp::kMsub:
      return std::fma(a, b, -c - rounded);
    case TrackedOp::kNmadd:
      return std::fma(a, b, c - rounded);
    case TrackedOp::kNmsub:
      return std::fma(a, b, -c - rounded);
    case TrackedOp::kSqrt:
      return std::fma(-rounded, rounded, a);
  }
  return 0.0;
}

inline bool fraction_incremented(TrackedOp op, double a, double b, double c,
                                 double rounded) noexcept {
  if (op == TrackedOp::kNmadd || op == TrackedOp::kNmsub)
    rounded = -rounded;
  if (rounded == 0.0 || !is_finite(rounded))
    return false;
  const double residual = rounding_residual(op, a, b, c, rounded);
  return residual != 0.0 && std::signbit(residual) != std::signbit(rounded);
}

/// Execute a scalar floating-point instruction, record its sticky FPSCR state,
/// and optionally update CR1 for the record form.
template <typename Op>
inline double tracked(FPSCRRegister& fpscr, CRRegister* cr1, Op op, uint32_t invalid_causes,
                      bool quiet, bool single_precision, TrackedOp tracked_op, double a,
                      double b = 0.0, double c = 0.0) noexcept {
  volatile double va = a, vb = b, vc = c;
  std::feclearexcept(FE_ALL_EXCEPT);
  volatile double vr = op(va, vb, vc);
  const int raised = quiet ? 0 : std::fetestexcept(FE_ALL_EXCEPT);
  const uint32_t causes = quiet ? 0 : (host_exception_causes(raised) | invalid_causes);
  fpscr.recordExceptions(causes);
  const bool invalid = invalid_causes || (raised & FE_INVALID);
  if (!(invalid && (fpscr.guest_bits & FPSCRRegister::kVE)))
    set_result_class(fpscr, vr, single_precision);
  if (invalid || (raised & FE_DIVBYZERO)) {
    set_rounding_flags(fpscr, false, false);
  } else if (raised & FE_OVERFLOW) {
    // FR is architecturally undefined for overflow; FI still reports the
    // overflowed, inexact result.
    set_rounding_flags(fpscr, false, (raised & FE_INEXACT) != 0);
  } else {
    const bool inexact = (raised & FE_INEXACT) != 0;
    set_rounding_flags(fpscr, inexact && fraction_incremented(tracked_op, a, b, c, vr), inexact);
  }
  if (cr1)
    set_cr1_from_fpscr(*cr1, fpscr);
  return vr;
}

/// Runs `op` on the operands with the host status flags cleared and sets CR1
/// from what it raised. The operands and result go through volatiles so the
/// arithmetic stays between the flag calls. `quiet` reports nothing raised
/// (a single-precision denormal operand).
template <typename Op>
inline double recorded(CRRegister& cr1, Op op, bool invalid, bool quiet, double a, double b = 0.0,
                       double c = 0.0) noexcept {
  volatile double va = a, vb = b, vc = c;
  std::feclearexcept(FE_ALL_EXCEPT);
  volatile double vr = op(va, vb, vc);
  const int raised = quiet ? 0 : std::fetestexcept(FE_ALL_EXCEPT);
  set_cr1(cr1, raised, invalid && !quiet);
  return vr;
}

inline uint64_t integer_magnitude(int64_t value) noexcept {
  const uint64_t bits = uint64_t(value);
  return value < 0 ? ~bits + 1 : bits;
}

inline uint64_t double_integer_magnitude(double value) noexcept {
  const uint64_t encoded = bits(value) & kMagnitude;
  const uint32_t exponent = uint32_t(encoded >> 52) & 0x7FF;
  if (!exponent)
    return 0;
  const uint64_t significand = (encoded & 0x000FFFFFFFFFFFFFull) | (1ull << 52);
  const int32_t shift = int32_t(exponent) - 1023 - 52;
  return shift >= 0 ? significand << shift : significand >> -shift;
}

/// Convert a signed guest integer to double and track its rounding fields.
inline double tracked_from_integer(FPSCRRegister& fpscr, CRRegister* cr1, int64_t value) noexcept {
  volatile int64_t source = value;
  volatile double result = double(source);
  const uint64_t magnitude = integer_magnitude(value);
  const uint64_t rounded_magnitude = double_integer_magnitude(result);
  const bool inexact = rounded_magnitude != magnitude;
  const bool fraction_rounded = inexact && rounded_magnitude > magnitude;
  set_rounding_flags(fpscr, fraction_rounded, inexact);
  fpscr.recordExceptions(inexact ? FPSCRRegister::kXX : 0);
  set_result_class(fpscr, result);
  if (cr1)
    set_cr1_from_fpscr(*cr1, fpscr);
  return result;
}

/// Convert to an integer and accumulate the guest FPSCR exception state.
inline int64_t tracked_convert(FPSCRRegister& fpscr, CRRegister* cr1, double x, bool truncate,
                               bool to_doubleword) noexcept {
  const double limit = to_doubleword ? 9223372036854775808.0 : 2147483648.0;
  const double rounded = is_nan(x) ? 0.0 : (truncate ? std::trunc(x) : std::nearbyint(x));
  const bool invalid = is_nan(x) || rounded >= limit || rounded < -limit;
  uint32_t causes = 0;
  if (is_snan(x))
    causes |= FPSCRRegister::kVXSNAN;
  else if (invalid)
    causes |= FPSCRRegister::kVXCVI;
  if (!invalid && rounded != x)
    causes |= FPSCRRegister::kXX;
  const bool inexact = !invalid && rounded != x;
  const bool fraction_rounded = inexact && std::fabs(rounded) > std::fabs(x);
  set_rounding_flags(fpscr, fraction_rounded, inexact);
  fpscr.recordExceptions(causes);
  if (cr1)
    set_cr1_from_fpscr(*cr1, fpscr);
  return to_doubleword ? to_int64(x, truncate) : to_int32(x, truncate);
}

/// Execute fres/frsqrte and accumulate the exception state defined by the
/// operand. These estimate instructions do not report inexact.
inline double tracked_estimate(FPSCRRegister& fpscr, CRRegister* cr1, double x,
                               bool sqrt_estimate) noexcept {
  const uint64_t magnitude = bits(x) & kMagnitude;
  uint32_t causes = snan_causes(x);
  if (sqrt_estimate && (bits(x) >> 63) && magnitude != 0 && !is_nan(x))
    causes |= FPSCRRegister::kVXSQRT;
  else if (magnitude == 0)
    causes |= FPSCRRegister::kZX;
  if (!sqrt_estimate && magnitude != 0 && magnitude < 0x37F0000000000000ull)
    causes |= FPSCRRegister::kOX;
  fpscr.recordExceptions(causes);
  if (cr1)
    set_cr1_from_fpscr(*cr1, fpscr);
  return sqrt_estimate ? rsqrte(x) : double(float(1.0 / x));
}

//=============================================================================
// Vector (VMX) NaN rules
//=============================================================================
// A NaN element is the first NaN operand element, quieted, or the positive
// default QNaN (x86 makes it negative). Results without a NaN element return
// after one compare.

inline constexpr uint32_t kDefaultNaN32 = 0x7FC00000u;

inline uint32_t bits32(float x) noexcept {
  uint32_t u;
  std::memcpy(&u, &x, sizeof(u));
  return u;
}
inline bool is_nan32(uint32_t u) noexcept {
  return (u & 0x7FFFFFFFu) > 0x7F800000u;
}

inline uint32_t nan_element(uint32_t a, uint32_t b, uint32_t c) noexcept {
  if (is_nan32(a))
    return a | 0x00400000u;
  if (is_nan32(b))
    return b | 0x00400000u;
  if (is_nan32(c))
    return c | 0x00400000u;
  return kDefaultNaN32;
}

/// Replaces r's NaN elements; `negate` flips the sign of the others.
inline simde__m128 vnan(simde__m128 r, simde__m128 a, simde__m128 b, simde__m128 c,
                        bool negate) noexcept {
  const simde__m128 sign = simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0x80000000u)));
  if (simde_mm_movemask_ps(simde_mm_cmpunord_ps(r, r)) == 0)
    return negate ? simde_mm_xor_ps(r, sign) : r;
  alignas(16) uint32_t ur[4], ua[4], ub[4], uc[4];
  simde_mm_store_ps(reinterpret_cast<float*>(ur), r);
  simde_mm_store_ps(reinterpret_cast<float*>(ua), a);
  simde_mm_store_ps(reinterpret_cast<float*>(ub), b);
  simde_mm_store_ps(reinterpret_cast<float*>(uc), c);
  for (int i = 0; i < 4; ++i) {
    if (is_nan32(ur[i]))
      ur[i] = nan_element(ua[i], ub[i], uc[i]);
    else if (negate)
      ur[i] ^= 0x80000000u;
  }
  return simde_mm_load_ps(reinterpret_cast<const float*>(ur));
}

/// Replaces the elements where a or b is a NaN (min and max return the other
/// operand there, so the result can't be tested).
inline simde__m128 vnan_operands(simde__m128 r, simde__m128 a, simde__m128 b) noexcept {
  if (simde_mm_movemask_ps(simde_mm_cmpunord_ps(a, b)) == 0)
    return r;
  alignas(16) uint32_t ur[4], ua[4], ub[4];
  simde_mm_store_ps(reinterpret_cast<float*>(ur), r);
  simde_mm_store_ps(reinterpret_cast<float*>(ua), a);
  simde_mm_store_ps(reinterpret_cast<float*>(ub), b);
  for (int i = 0; i < 4; ++i) {
    if (is_nan32(ua[i]) || is_nan32(ub[i]))
      ur[i] = nan_element(ua[i], ub[i], ub[i]);
  }
  return simde_mm_load_ps(reinterpret_cast<const float*>(ur));
}

/// VMX flushes a denormal element to zero, keeping its sign. The host's
/// denormals-are-zero mode does so for arithmetic but not for min and max,
/// which return the operand's own bits.
inline simde__m128 vflush(simde__m128 x) noexcept {
  const simde__m128i xi = simde_mm_castps_si128(x);
  const simde__m128i exponent = simde_mm_and_si128(xi, simde_mm_set1_epi32(0x7F800000));
  const simde__m128i denormal = simde_mm_cmpeq_epi32(exponent, simde_mm_setzero_si128());
  return simde_mm_castsi128_ps(
      simde_mm_andnot_si128(simde_mm_and_si128(denormal, simde_mm_set1_epi32(0x7FFFFFFF)), xi));
}

//-----------------------------------------------------------------------------
// Fused multiply-add. vmaddfp and vnmsubfp round once, so a separate multiply
// and add can be an ulp out, or lose the sign of a product that flushes to
// zero. FMA3 does it in one instruction where the CPU has it (checked once);
// otherwise the elements go through double, where the product is exact.
//-----------------------------------------------------------------------------

#if defined(__x86_64__) || defined(_M_X64)
__attribute__((target("xsave"))) inline bool DetectFma() noexcept {
  int r[4];
  __cpuid(r, 1);
  const bool fma = r[2] & (1 << 12), osxsave = r[2] & (1 << 27), avx = r[2] & (1 << 28);
  return fma && osxsave && avx && (_xgetbv(0) & 6) == 6;
}
inline const bool kHasFma = DetectFma();

// Inline assembly rather than a target("fma") function, which can't be
// inlined into the SSE4.1 title code. VEX.128 clears the upper halves, so
// mixing it with the legacy SSE code costs no transition.
inline simde__m128 FusedMulAdd(simde__m128 a, simde__m128 c, simde__m128 b) noexcept {
  __m128 r = b;
  __asm__("vfmadd231ps %2, %1, %0" : "+x"(r) : "x"(__m128(a)), "x"(__m128(c)));
  return r;
}
inline simde__m128 FusedMulSub(simde__m128 a, simde__m128 c, simde__m128 b) noexcept {
  __m128 r = b;
  __asm__("vfmsub231ps %2, %1, %0" : "+x"(r) : "x"(__m128(a)), "x"(__m128(c)));
  return r;
}
#endif

/// a x c + b (or - b), rounded once to single.
inline simde__m128 vfused(simde__m128 a, simde__m128 c, simde__m128 b, bool subtract) noexcept {
#if defined(__x86_64__) || defined(_M_X64)
  if (kHasFma)
    return subtract ? FusedMulSub(a, c, b) : FusedMulAdd(a, c, b);
#elif defined(__aarch64__) || defined(_M_ARM64)
  return subtract ? simde_mm_fmsub_ps(a, c, b) : simde_mm_fmadd_ps(a, c, b);
#endif
  if (subtract)
    b = simde_mm_xor_ps(b, simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0x80000000u))));
  const simde__m128d lo = simde_mm_add_pd(
      simde_mm_mul_pd(simde_mm_cvtps_pd(a), simde_mm_cvtps_pd(c)), simde_mm_cvtps_pd(b));
  const simde__m128d hi =
      simde_mm_add_pd(simde_mm_mul_pd(simde_mm_cvtps_pd(simde_mm_movehl_ps(a, a)),
                                      simde_mm_cvtps_pd(simde_mm_movehl_ps(c, c))),
                      simde_mm_cvtps_pd(simde_mm_movehl_ps(b, b)));
  return simde_mm_movelh_ps(simde_mm_cvtpd_ps(lo), simde_mm_cvtpd_ps(hi));
}

inline simde__m128 vadd(simde__m128 a, simde__m128 b) noexcept {
  return vnan(simde_mm_add_ps(a, b), a, b, b, false);
}
inline simde__m128 vsub(simde__m128 a, simde__m128 b) noexcept {
  return vnan(simde_mm_sub_ps(a, b), a, b, b, false);
}
inline simde__m128 vmul(simde__m128 a, simde__m128 b) noexcept {
  return vnan(simde_mm_mul_ps(a, b), a, b, b, false);
}
/// vmaddfp: A x C + B, NaN in A, B, C order.
inline simde__m128 vmadd(simde__m128 a, simde__m128 c, simde__m128 b) noexcept {
  return vnan(vfused(a, c, b, false), a, b, c, false);
}
/// vnmsubfp: -(A x C - B), a NaN element not negated.
inline simde__m128 vnmsub(simde__m128 a, simde__m128 c, simde__m128 b) noexcept {
  return vnan(vfused(a, c, b, true), a, b, c, true);
}

/// vmaxfp/vminfp: denormals flushed, +0 above -0, and a NaN element quieted.
inline simde__m128 vmax(simde__m128 a, simde__m128 b) noexcept {
  const simde__m128 fa = vflush(a), fb = vflush(b);
  const simde__m128 eq = simde_mm_cmpeq_ps(fa, fb);
  simde__m128 r = simde_mm_max_ps(fa, fb);
  r = simde_mm_or_ps(simde_mm_andnot_ps(eq, r), simde_mm_and_ps(eq, simde_mm_and_ps(fa, fb)));
  return vnan_operands(r, a, b);
}
inline simde__m128 vmin(simde__m128 a, simde__m128 b) noexcept {
  const simde__m128 fa = vflush(a), fb = vflush(b);
  const simde__m128 eq = simde_mm_cmpeq_ps(fa, fb);
  simde__m128 r = simde_mm_min_ps(fa, fb);
  r = simde_mm_or_ps(simde_mm_andnot_ps(eq, r), simde_mm_and_ps(eq, simde_mm_or_ps(fa, fb)));
  return vnan_operands(r, a, b);
}

/// vrsqrtefp on each element.
inline simde__m128 vrsqrte(simde__m128 x) noexcept {
  alignas(16) uint32_t u[4];
  simde_mm_store_ps(reinterpret_cast<float*>(u), x);
  for (uint32_t& e : u)
    e = vrsqrte(e);
  return simde_mm_load_ps(reinterpret_cast<const float*>(u));
}

// vexptefp and vlogefp: minimax polynomials snapped onto the guest's 2^-11
// estimate grid, which keeps 2^0 == 1 and log2(2^n) == n exact (xenia-edge
// fb225d975 coefficients).

inline simde__m128 EstPoly(simde__m128 x, const float* coefficients, int count) noexcept {
  simde__m128 p = simde_mm_set1_ps(coefficients[count - 1]);
  for (int k = count - 2; k >= 0; --k)
    p = simde_mm_add_ps(simde_mm_mul_ps(p, x), simde_mm_set1_ps(coefficients[k]));
  return p;
}

inline simde__m128 EstGridSnap(simde__m128 x) noexcept {
  x = simde_mm_mul_ps(x, simde_mm_set1_ps(2048.0f));
  x = simde_mm_round_ps(x, SIMDE_MM_FROUND_TO_NEAREST_INT | SIMDE_MM_FROUND_NO_EXC);
  return simde_mm_mul_ps(x, simde_mm_set1_ps(1.0f / 2048.0f));
}

inline simde__m128 BlendMask(simde__m128 a, simde__m128 b, simde__m128 mask) noexcept {
  return simde_mm_or_ps(simde_mm_andnot_ps(mask, a), simde_mm_and_ps(mask, b));
}

/// vexptefp: 2^x estimate.
inline simde__m128 vexpte(simde__m128 x) noexcept {
  static constexpr float kExp2[6] = {0.9999999266823865f,   0.6931530239113992f,
                                     0.24015381838022493f,  0.055826172900559086f,
                                     0.008989127362479102f, 0.0018777841277241077f};
  const simde__m128 n = simde_mm_round_ps(x, SIMDE_MM_FROUND_TO_NEG_INF | SIMDE_MM_FROUND_NO_EXC);
  simde__m128 r = EstGridSnap(EstPoly(simde_mm_sub_ps(x, n), kExp2, 6));
  const simde__m128i scale = simde_mm_add_epi32(simde_mm_slli_epi32(simde_mm_cvtps_epi32(n), 23),
                                                simde_mm_set1_epi32(0x3F800000));
  r = simde_mm_mul_ps(r, simde_mm_castsi128_ps(scale));
  // Out-of-range and non-finite inputs never reach the estimator.
  r = BlendMask(r, simde_mm_castsi128_ps(simde_mm_set1_epi32(0x7F800000)),
                simde_mm_cmpge_ps(x, simde_mm_set1_ps(128.0f)));
  r = BlendMask(r, simde_mm_setzero_ps(), simde_mm_cmplt_ps(x, simde_mm_set1_ps(-126.0f)));
  const simde__m128 quieted =
      simde_mm_or_ps(x, simde_mm_castsi128_ps(simde_mm_set1_epi32(0x00400000)));
  return BlendMask(r, quieted, simde_mm_cmpunord_ps(x, x));
}

/// vlogefp: log2(x) estimate.
inline simde__m128 vloge(simde__m128 x) noexcept {
  static constexpr float kLog2[7] = {
      1.8456866772102942e-06f, 1.4424953159391898f,  -0.7177910762015521f,  0.4565216600899004f,
      -0.2765407398023532f,    0.12100223739860312f, -0.025691088797142478f};
  const simde__m128i xi = simde_mm_castps_si128(x);
  const simde__m128 exponent = simde_mm_cvtepi32_ps(
      simde_mm_sub_epi32(simde_mm_srli_epi32(xi, 23), simde_mm_set1_epi32(127)));
  const simde__m128 one = simde_mm_set1_ps(1.0f);
  const simde__m128 mantissa = simde_mm_sub_ps(
      simde_mm_or_ps(simde_mm_and_ps(x, simde_mm_castsi128_ps(simde_mm_set1_epi32(0x007FFFFF))),
                     one),
      one);
  simde__m128 r = EstGridSnap(simde_mm_add_ps(EstPoly(mantissa, kLog2, 7), exponent));
  const simde__m128 inf = simde_mm_castsi128_ps(simde_mm_set1_epi32(0x7F800000));
  r = BlendMask(r, inf, simde_mm_cmpeq_ps(x, inf));
  r = BlendMask(r, simde_mm_castsi128_ps(simde_mm_set1_epi32(int(kDefaultNaN32))),
                simde_mm_castsi128_ps(simde_mm_srai_epi32(xi, 31)));
  // Zero and denormals reach the estimator as zero: -inf.
  const simde__m128 zero_exponent = simde_mm_castsi128_ps(simde_mm_cmpeq_epi32(
      simde_mm_and_si128(xi, simde_mm_set1_epi32(0x7F800000)), simde_mm_setzero_si128()));
  r = BlendMask(r, simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0xFF800000u))), zero_exponent);
  const simde__m128 quieted =
      simde_mm_or_ps(x, simde_mm_castsi128_ps(simde_mm_set1_epi32(0x00400000)));
  return BlendMask(r, quieted, simde_mm_cmpunord_ps(x, x));
}

/// vcmpbfp: bit 31 when a > b, bit 30 when a < -b, both for a NaN element.
inline simde__m128 vcmpb(simde__m128 a, simde__m128 b) noexcept {
  const simde__m128 nan = simde_mm_cmpunord_ps(a, b);
  const simde__m128 gt = simde_mm_or_ps(simde_mm_cmpgt_ps(a, b), nan);
  const simde__m128 neg_b =
      simde_mm_xor_ps(b, simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0x80000000u))));
  const simde__m128 lt = simde_mm_or_ps(simde_mm_cmplt_ps(a, neg_b), nan);
  return simde_mm_or_ps(
      simde_mm_and_ps(gt, simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0x80000000u)))),
      simde_mm_and_ps(lt, simde_mm_castsi128_ps(simde_mm_set1_epi32(0x40000000))));
}

}  // namespace rex::ppc::fp
