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

bool BuildAdd(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 + {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildAdde(BuilderContext& ctx) {
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

bool BuildAddi(BuilderContext& ctx) {
  ctx.print("\t{}.s64 = ", ctx.r(ctx.insn.operands[0]));
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.s64 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{};", static_cast<int32_t>(ctx.insn.operands[2]));
  return true;
}

bool BuildAddic(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 > {};", ctx.xer(), ctx.r(ctx.insn.operands[1]),
              ~ctx.insn.operands[2]);
  ctx.println("\t{}.s64 = {}.s64 + {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              static_cast<int32_t>(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildAddis(BuilderContext& ctx) {
  ctx.print("\t{}.s64 = ", ctx.r(ctx.insn.operands[0]));
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.s64 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{};", static_cast<int32_t>(ctx.insn.operands[2] << 16));
  return true;
}

bool BuildAddze(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = {}.s64 + {}.ca;", ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u32 < {}.u32;", ctx.xer(), ctx.temp(), ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.s64 = {}.s64;", ctx.r(ctx.insn.operands[0]), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildAddme(BuilderContext& ctx) {
  ctx.println("\t{}.u8 = ({}.u32 + 0xFFFFFFFFu < {}.u32) | ({}.u32 + 0xFFFFFFFFu + {}.ca < {}.ca);",
              ctx.temp(), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[1]), ctx.xer(), ctx.xer());
  ctx.println("\t{}.u64 = {}.u64 + {}.ca + 0xFFFFFFFFFFFFFFFFull;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildAddc(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 + {}.u32 < {}.u32;", ctx.xer(), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.u64 = {}.u64 + {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildDivd(BuilderContext& ctx) {
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println(
      "\t{}.s64 = ({}.s64 && !({}.s64 == INT64_MIN && {}.s64 == -1)) ? {}.s64 / {}.s64 : 0;", rD,
      rB, rA, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildDivdu(BuilderContext& ctx) {
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = {}.u64 ? {}.u64 / {}.u64 : 0;", rD, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildDivw(BuilderContext& ctx) {
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

bool BuildDivwu(BuilderContext& ctx) {
  auto rD = ctx.r(ctx.insn.operands[0]);
  auto rA = ctx.r(ctx.insn.operands[1]);
  auto rB = ctx.r(ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = uint32_t({}.u32 ? {}.u32 / {}.u32 : 0);", rD, rB, rA, rB);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildMulhw(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = (int64_t({}.s32) * int64_t({}.s32)) >> 32;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildMulhwu(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = (uint64_t({}.u32) * uint64_t({}.u32)) >> 32;",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildMulld(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = static_cast<int64_t>({}.u64 * {}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildMulli(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = static_cast<int64_t>({}.u64 * static_cast<uint64_t>({}));",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              static_cast<int32_t>(ctx.insn.operands[2]));
  return true;
}

bool BuildMullw(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = int64_t({}.s32) * int64_t({}.s32);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildMulhd(BuilderContext& ctx) {
  ctx.println(
      "\t{}.s64 = static_cast<int64_t>((static_cast<__int128>(static_cast<int64_t>({}.s64)) * "
      "static_cast<__int128>(static_cast<int64_t>({}.s64))) >> 64);",
      ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildMulhdu(BuilderContext& ctx) {
  ctx.println(
      "\t{}.u64 = static_cast<uint64_t>((static_cast<__uint128_t>({}.u64) * "
      "static_cast<__uint128_t>({}.u64)) >> 64);",
      ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildNeg(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = static_cast<int64_t>(-{}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSubf(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 - {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSubfc(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 >= {}.u32;", ctx.xer(), ctx.r(ctx.insn.operands[2]),
              ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.u64 = {}.u64 - {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSubfe(BuilderContext& ctx) {
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

bool BuildSubfic(BuilderContext& ctx) {
  ctx.println("\t{}.ca = {}.u32 <= {};", ctx.xer(), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = static_cast<uint64_t>({}) - {}.u64;", ctx.r(ctx.insn.operands[0]),
              static_cast<int32_t>(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]));
  return true;
}

bool BuildSubfze(BuilderContext& ctx) {
  ctx.println("\t{}.u8 = ~{}.u32 + {}.ca < ~{}.u32;", ctx.temp(), ctx.r(ctx.insn.operands[1]),
              ctx.xer(), ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.u64 = ~{}.u64 + {}.ca;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.xer());
  ctx.println("\t{}.ca = {}.u8;", ctx.xer(), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSubfme(BuilderContext& ctx) {
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

namespace {

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

  if (doubleword && isRecordForm(ctx.insn)) {
    ctx.println("\t{}.compare<int64_t>({}.s64, 0, {});", ctx.cr(0), ctx.r(ctx.insn.operands[0]),
                ctx.xer());
  }
  return true;
}

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

}

bool BuildAddo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), R(ctx, 2), "0", BuildAdd);
}
bool BuildAddco(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), R(ctx, 2), "0", BuildAddc);
}
bool BuildAddeo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), R(ctx, 2), Ca(ctx), BuildAdde);
}
bool BuildAddmeo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), "~uint64_t(0)", Ca(ctx), BuildAddme);
}
bool BuildAddzeo(BuilderContext& ctx) {
  return addOverflow(ctx, R(ctx, 1), "uint64_t(0)", Ca(ctx), BuildAddze);
}

bool BuildSubfo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), R(ctx, 2), "1", BuildSubf);
}
bool BuildSubfco(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), R(ctx, 2), "1", BuildSubfc);
}
bool BuildSubfeo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), R(ctx, 2), Ca(ctx), BuildSubfe);
}
bool BuildSubfmeo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), "~uint64_t(0)", Ca(ctx), BuildSubfme);
}
bool BuildSubfzeo(BuilderContext& ctx) {
  return addOverflow(ctx, NotR(ctx, 1), "uint64_t(0)", Ca(ctx), BuildSubfze);
}

bool BuildNego(BuilderContext& ctx) {
  emitOverflow(ctx, fmt::format("const uint64_t a = {};", R(ctx, 1)), "a == 0x8000000000000000ull");
  return finishOverflow(ctx, BuildNeg);
}

bool BuildMullwo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const int64_t p = int64_t({}.s32) * int64_t({}.s32);",
                           ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2])),
               "p != int64_t(int32_t(p))");
  return finishOverflow(ctx, BuildMullw, false);
}

bool BuildMulldo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const __int128 p = __int128({}.s64) * __int128({}.s64);",
                           ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2])),
               "p != __int128(int64_t(p))");
  return finishOverflow(ctx, BuildMulld);
}

bool BuildDivwo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const int32_t a = {}.s32, b = {}.s32;", ctx.r(ctx.insn.operands[1]),
                           ctx.r(ctx.insn.operands[2])),
               "b == 0 || (a == INT32_MIN && b == -1)");
  return finishOverflow(ctx, BuildDivw, false);
}

bool BuildDivwuo(BuilderContext& ctx) {
  emitOverflow(ctx, fmt::format("const uint32_t b = {}.u32;", ctx.r(ctx.insn.operands[2])),
               "b == 0");
  return finishOverflow(ctx, BuildDivwu, false);
}

bool BuildDivdo(BuilderContext& ctx) {
  emitOverflow(ctx,
               fmt::format("const int64_t a = {}.s64, b = {}.s64;", ctx.r(ctx.insn.operands[1]),
                           ctx.r(ctx.insn.operands[2])),
               "b == 0 || (a == INT64_MIN && b == -1)");
  return finishOverflow(ctx, BuildDivd);
}

bool BuildDivduo(BuilderContext& ctx) {
  emitOverflow(ctx, fmt::format("const uint64_t b = {}.u64;", ctx.r(ctx.insn.operands[2])),
               "b == 0");
  return finishOverflow(ctx, BuildDivdu);
}

bool BuildMcrxr(BuilderContext& ctx) {
  const auto cr = ctx.cr(ctx.insn.operands[0]);
  ctx.println("\t{}.lt = {}.so;", cr, ctx.xer());
  ctx.println("\t{}.gt = {}.ov;", cr, ctx.xer());
  ctx.println("\t{}.eq = {}.ca;", cr, ctx.xer());
  ctx.println("\t{}.so = 0;", cr);
  ctx.println("\t{0}.so = 0;\n\t{0}.ov = 0;\n\t{0}.ca = 0;", ctx.xer());
  return true;
}

}
