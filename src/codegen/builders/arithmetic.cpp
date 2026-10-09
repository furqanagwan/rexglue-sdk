/**
 * @file        rexcodegen/builders/arithmetic.cpp
 * @brief       PPC arithmetic instruction code generation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "builder_context.h"
#include "helpers.h"
namespace rex::codegen {

//=============================================================================
// Addition
//=============================================================================

bool build_add(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 + {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_adde(BuilderContext& ctx) {
  ctx.println("\t{}.u8 = ({}.u32 + {}.u32 < {}.u32) | ({}.u32 + {}.u32 + {}.ca < {}.ca);",
              ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]),
              ctx.xer(), ctx.xer());
  ctx.println("\t{}.u64 = {}.u64 + {}.u64 + {}.ca;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool build_addi(BuilderContext& ctx) {
  ctx.print("\t{}.s64 = ", ctx.r(ctx.insn.operands[0]));
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.s64 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{};", static_cast<int32_t>(ctx.insn.operands[2]));
  return true;
}

bool build_addic(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 > {};", ctx.xer(), ctx.r(ctx.insn.operands[1]),
              ~ctx.insn.operands[2]);
  ctx.println("\t{}.s64 = {}.s64 + {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              static_cast<int32_t>(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_addis(BuilderContext& ctx) {
  ctx.print("\t{}.s64 = ", ctx.r(ctx.insn.operands[0]));
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.s64 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{};", static_cast<int32_t>(ctx.insn.operands[2] << 16));
  return true;
}

bool build_addze(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = {}.s64 + {}.ca;", ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u32 < {}.u32;", ctx.xer(), ctx.temp(), ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.s64 = {}.s64;", ctx.r(ctx.insn.operands[0]), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool build_addme(BuilderContext& ctx) {
  // addme: rD = rA + CA - 1 (which is rA + CA + 0xFFFFFFFFFFFFFFFF)
  ctx.println("\t{}.u8 = ({}.u32 + 0xFFFFFFFFu < {}.u32) | ({}.u32 + 0xFFFFFFFFu + {}.ca < {}.ca);",
              ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[1]), ctx.xer(), ctx.xer());
  ctx.println("\t{}.u64 = {}.u64 + {}.ca + 0xFFFFFFFFFFFFFFFFull;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool build_addc(BuilderContext& ctx) {
  // addc: rD = rA + rB, CA = carry out
  ctx.println("\t{}.ca = {}.u32 + {}.u32 < {}.u32;", ctx.xer(), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.u64 = {}.u64 + {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Division
//=============================================================================
// PPC division instructions do NOT trap on divide-by-zero - they produce undefined results.
// We generate safe division that returns 0 when the divisor is zero.

bool build_divd(BuilderContext& ctx) {
  // divd rD,rA,rB: rD = rA / rB (64-bit signed)
  // Safe division: return 0 if divisor is zero or INT64_MIN / -1 (UB in C)
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println(
      "\t{}.s64 = ({}.s64 && !({}.s64 == INT64_MIN && {}.s64 == -1)) ? {}.s64 / {}.s64 : 0;", rD,
      rB, rA, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

bool build_divdu(BuilderContext& ctx) {
  // divdu rD,rA,rB: rD = rA / rB (64-bit unsigned)
  // Safe division: return 0 if divisor is zero
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = {}.u64 ? {}.u64 / {}.u64 : 0;", rD, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

bool build_divw(BuilderContext& ctx) {
  // divw rD,rA,rB: rD = rA / rB (32-bit signed)
  // Safe division: return 0 if divisor is zero or INT32_MIN / -1 (UB in C)
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println(
      "\t{}.u64 = uint32_t(({}.s32 && !({}.s32 == INT32_MIN && {}.s32 == -1)) ? {}.s32 / {}.s32 : "
      "0);",
      rD, rB, rA, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

bool build_divwu(BuilderContext& ctx) {
  // divwu rD,rA,rB: rD = rA / rB (32-bit unsigned)
  // Safe division: return 0 if divisor is zero
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = uint32_t({}.u32 ? {}.u32 / {}.u32 : 0);", rD, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Multiplication
//=============================================================================

bool build_mulhw(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = (int64_t({}.s32) * int64_t({}.s32)) >> 32;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_mulhwu(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = (uint64_t({}.u32) * uint64_t({}.u32)) >> 32;",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_mulld(BuilderContext& ctx) {
  // Use unsigned multiplication to avoid signed overflow UB (PPC wraps on overflow)
  ctx.println("\t{}.s64 = static_cast<int64_t>({}.u64 * {}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_mulli(BuilderContext& ctx) {
  // Use unsigned multiplication to avoid signed overflow UB (PPC wraps on overflow)
  ctx.println("\t{}.s64 = static_cast<int64_t>({}.u64 * static_cast<uint64_t>({}));",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              static_cast<int32_t>(ctx.insn.operands[2]));
  return true;
}

bool build_mullw(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = int64_t({}.s32) * int64_t({}.s32);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_mulhd(BuilderContext& ctx) {
  // mulhd: rD = high 64 bits of (rA * rB) (signed)
  ctx.println(
      "\t{}.s64 = static_cast<int64_t>((static_cast<__int128>(static_cast<int64_t>({}.s64)) * "
      "static_cast<__int128>(static_cast<int64_t>({}.s64))) >> 64);",
      ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_mulhdu(BuilderContext& ctx) {
  // mulhdu: rD = high 64 bits of (rA * rB) (unsigned)
  ctx.println(
      "\t{}.u64 = static_cast<uint64_t>((static_cast<__uint128_t>({}.u64) * "
      "static_cast<__uint128_t>({}.u64)) >> 64);",
      ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Negation
//=============================================================================

bool build_neg(BuilderContext& ctx) {
  // Use unsigned negation to avoid signed overflow UB when negating INT64_MIN
  ctx.println("\t{}.s64 = static_cast<int64_t>(-{}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Subtraction
//=============================================================================

bool build_subf(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 - {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_subfc(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 >= {}.u32;", ctx.xer(), ctx.r(ctx.insn.operands[2]),
              ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.u64 = {}.u64 - {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool build_subfe(BuilderContext& ctx) {
  ctx.println("\t{}.u8 = (~{}.u32 + {}.u32 < ~{}.u32) | (~{}.u32 + {}.u32 + {}.ca < {}.ca);",
              ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]),
              ctx.xer(), ctx.xer());
  ctx.println("\t{}.u64 = ~{}.u64 + {}.u64 + {}.ca;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool build_subfic(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 <= {};", ctx.xer(), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = static_cast<uint64_t>({}) - {}.u64;", ctx.r(ctx.insn.operands[0]),
              static_cast<int32_t>(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  return true;
}

bool build_subfze(BuilderContext& ctx) {
  // subfze: rD = ~rA + CA (subtract from zero extended)
  ctx.println("\t{}.u8 = ~{}.u32 + {}.ca < ~{}.u32;", ctx.temp(), ctx.r(ctx.insn.operands[1]),
              ctx.xer(), ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.u64 = ~{}.u64 + {}.ca;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool build_subfme(BuilderContext& ctx) {
  // subfme: rD = ~rA + CA - 1 (subtract from minus one extended)
  ctx.println(
      "\t{}.u8 = (~{}.u32 + 0xFFFFFFFFu < ~{}.u32) | (~{}.u32 + 0xFFFFFFFFu + {}.ca < {}.ca);",
      ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
      ctx.r(ctx.insn.operands[1]), ctx.xer(), ctx.xer());
  ctx.println("\t{}.u64 = ~{}.u64 + {}.ca + 0xFFFFFFFFFFFFFFFFull;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Overflow-enable (OE) forms: XER[OV] for the result, XER[SO] sticky
//=============================================================================
// OV is worked out from the operands before the base instruction runs (its
// result may overwrite a source), so the base instruction's record form sees
// the updated SO in CR0. Additions and subtractions judge overflow on 64
// bits, as has207/xenia-edge 10da45ea4 does: SO is sticky, so a false
// positive from a 32-bit view would never clear.

namespace {

// Sets OV to `ov`, a C++ expression over `a`, `b` and `r` (64-bit unsigned).
void emitOverflow(BuilderContext& ctx, const std::string& setup, const char* ov) {
  ctx.println("\t{{");
  ctx.println("\t\t{}", setup);
  ctx.println("\t\t{}.ov = uint8_t({});", ctx.xer(), ov);
  ctx.println("\t\t{0}.so = uint8_t({0}.so | {0}.ov);", ctx.xer());
  ctx.println("\t}}");
}

bool finishOverflow(BuilderContext& ctx, bool (*base)(BuilderContext&), bool doubleword = true) {
  if (!base(ctx))
    return false;
  // The shared record helper compares the low word; OE doubleword forms must
  // compare the full result. Emit after the base builder to replace CR0.
  if (doubleword && isRecordForm(ctx.insn)) {
    ctx.println("\t{}.compare<int64_t>({}.s64, 0, {});", ctx.cr(0), ctx.r(ctx.insn.operands[0]),
                ctx.xer());
  }
  return true;
}

// a + b (+ carry_in): overflow when both addends' signs differ from the sum's.
bool addOverflow(BuilderContext& ctx, const std::string& a, const std::string& b,
                 const std::string& carry, bool (*base)(BuilderContext&)) {
  emitOverflow(ctx, fmt::format("const uint64_t a = {}, b = {}, r = a + b + {};", a, b, carry),
               "((a ^ r) & (b ^ r)) >> 63");
  return finishOverflow(ctx, base);
}

std::string R(BuilderContext& ctx, size_t i) {
  return fmt::format("{}.u64", ctx.r(ctx.insn.operands[i]));
}
std::string NotR(BuilderContext& ctx, size_t i) {
  return fmt::format("~{}.u64", ctx.r(ctx.insn.operands[i]));
}
std::string Ca(BuilderContext& ctx) {
  return fmt::format("uint64_t({}.ca)", ctx.xer());
}

}  // namespace

bool build_addo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), R(ctx, 2), "0", build_add);
}
bool build_addco(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), R(ctx, 2), "0", build_addc);
}
bool build_addeo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), R(ctx, 2), Ca(ctx), build_adde);
}
bool build_addmeo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), "~uint64_t(0)", Ca(ctx), build_addme);
}
bool build_addzeo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), "uint64_t(0)", Ca(ctx), build_addze);
}
// subf rD,rA,rB is rB + ~rA + 1.
bool build_subfo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), R(ctx, 2), "1", build_subf);
}
bool build_subfco(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), R(ctx, 2), "1", build_subfc);
}
bool build_subfeo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), R(ctx, 2), Ca(ctx), build_subfe);
}
bool build_subfmeo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), "~uint64_t(0)", Ca(ctx), build_subfme);
}
bool build_subfzeo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), "uint64_t(0)", Ca(ctx), build_subfze);
}

bool build_nego(BuilderContext& ctx) {
  emitOverflow(ctx, fmt::format("const uint64_t a = {};", R(ctx, 1)), "a == 0x8000000000000000ull");
  return finishOverflow(ctx, build_neg);
}

bool build_mullwo(BuilderContext& ctx) {
  // The product of the low words overflows when it doesn't fit 32 signed bits.
  emitOverflow(ctx,
               fmt::format("const int64_t p = int64_t({}.s32) * int64_t({}.s32);",
                           ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2])),
               "p != int64_t(int32_t(p))");
  return finishOverflow(ctx, build_mullw, false);
}

bool build_mulldo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const __int128 p = __int128({}.s64) * __int128({}.s64);",
                           ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2])),
               "p != __int128(int64_t(p))");
  return finishOverflow(ctx, build_mulld);
}

bool build_divwo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const int32_t a = {}.s32, b = {}.s32;", ctx.r(ctx.insn.operands[1]),
                           ctx.r(ctx.insn.operands[2])),
               "b == 0 || (a == INT32_MIN && b == -1)");
  return finishOverflow(ctx, build_divw, false);
}

bool build_divwuo(BuilderContext& ctx) {
  emitOverflow(ctx, fmt::format("const uint32_t b = {}.u32;", ctx.r(ctx.insn.operands[2])),
               "b == 0");
  return finishOverflow(ctx, build_divwu, false);
}

bool build_divdo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const int64_t a = {}.s64, b = {}.s64;", ctx.r(ctx.insn.operands[1]),
                           ctx.r(ctx.insn.operands[2])),
               "b == 0 || (a == INT64_MIN && b == -1)");
  return finishOverflow(ctx, build_divd);
}

bool build_divduo(BuilderContext& ctx) {
  emitOverflow(ctx, fmt::format("const uint64_t b = {}.u64;", ctx.r(ctx.insn.operands[2])),
               "b == 0");
  return finishOverflow(ctx, build_divdu);
}

bool build_mcrxr(BuilderContext& ctx) {
  // CR field = XER[SO, OV, CA, 0]; those XER bits are cleared.
  const auto cr = ctx.cr(ctx.insn.operands[0]);
  ctx.println("\t{}.lt = {}.so;", cr, ctx.xer());
  ctx.println("\t{}.gt = {}.ov;", cr, ctx.xer());
  ctx.println("\t{}.eq = {}.ca;", cr, ctx.xer());
  ctx.println("\t{}.so = 0;", cr);
  ctx.println("\t{0}.so = 0;\n\t{0}.ov = 0;\n\t{0}.ca = 0;", ctx.xer());
  return true;
}

}  // namespace rex::codegen
