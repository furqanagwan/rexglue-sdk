/**
 * @file        rexcodegen/builders/vector.cpp
 * @brief       PPC vector instruction code generation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "builder_context.h"
#include "helpers.h"

#include <cmath>

#include <simde/x86/sse.h>

#include <rex/logging.h>

#include "../codegen_logging.h"

#include <ppc.h>

namespace rex::codegen {

//=============================================================================
// SIMD Constants Documentation
//=============================================================================
// This file uses several magic constants from Intel SSE/SSE4 intrinsics.
// Here are the key constants and their meanings:
//
// === Dot Product Masks (simde_mm_dp_ps) ===
// The mask byte controls which elements participate in the dot product and
// where the result is broadcast. Format: 0bAAAABBBB
//   High nibble (AAAA): Which source elements to multiply (bit 7=x, 6=y, 5=z, 4=w)
//   Low nibble (BBBB):  Which destination elements receive the result
//
// 0xEF = 0b11101111: Dot product of elements y,z,w (bits 765 set), result to all (bits 3210 set)
//        This computes dot(yzw) due to guest->host vector element reversal.
// 0xFF = 0b11111111: Full 4-element dot product, result broadcast to all elements
//
// === Floating-Point Sign Bit ===
// 0x80000000: IEEE 754 sign bit mask for 32-bit float
//             Used for negation via XOR and sign extraction
//
// === IEEE 754 Single Precision Exponent ===
// 0x7f800000: Exponent field mask (bits 23-30) for float
// 0x7FFFFFFF: Magnitude mask (clears sign bit)
// 0x3F800000: IEEE 754 representation of 1.0f (used for OR-ing in exponent)
// 0x40400000: IEEE 754 representation of 3.0f (D3D NORMSHORT encoding bias)
//
// === Half-Float (FP16) Conversion ===
// 0x7C00: FP16 exponent mask
// 0x1C000: Exponent bias adjustment for FP16->FP32 conversion
// 0x8000: FP16 sign bit
// 0x03FF: FP16 mantissa mask
// 0x7FFF: FP16 positive infinity/max value
//
// === Packed Integer Masks ===
// 0x3FF: 10-bit mask for NORMPACKED32 format (10 bits per component)
// 0xFFFFF: 20-bit mask for NORMPACKED64 format
// 0x1F: 5-bit mask for shift amounts (shifts are mod 32)
// 0xFF: 8-bit mask for byte values
// 0xFFFF: 16-bit mask for halfword values
//
// === D3D Color Format ===
// 0x404000FF: D3D color packing constant (ARGB8888)
//=============================================================================

//=============================================================================
// Vector Floating Point Arithmetic
//=============================================================================

bool BuildMtvscr(BuilderContext& ctx) {
  // Guest word 3 is host lane 0. Only NJ and SAT have defined local behavior.
  auto source = ctx.v(ctx.insn.operands[0]);
  ctx.println("\tctx.vscr_nj = ({}.u32[0] >> 16) & 1;", source);
  ctx.println("\tctx.vscr_sat = {}.u32[0] & 1;", source);
  ctx.csrState = CSRState::Unknown;
  return true;
}

bool BuildMfvscr(BuilderContext& ctx) {
  auto dest = ctx.v(ctx.insn.operands[0]);
  ctx.println("\t{}.u64[0] = 0;", dest);
  ctx.println("\t{}.u64[1] = 0;", dest);
  ctx.println("\t{}.u32[0] = (uint32_t(ctx.vscr_nj) << 16) | ctx.vscr_sat;", dest);
  return true;
}

bool BuildVaddfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vadd(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVsubfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vsub(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVmulfp128(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vmul(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVmaddfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  // (vA x vC) + vB, with PowerPC NaN rules (rex/ppc/fp.h).
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vmadd(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32), simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]),
      ctx.v(ctx.insn.operands[3]));
  return true;
}

bool BuildVnmsubfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  // -((vA x vC) - vB); a NaN result keeps its sign (rex/ppc/fp.h).
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vnmsub(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32), simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]),
      ctx.v(ctx.insn.operands[3]));
  return true;
}

bool BuildVmaxfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vmax(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVminfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vmin(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVrefp(BuilderContext& ctx) {
  // TODO: see if we can use rcp safely
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr("simde_mm_div_ps(simde_mm_set1_ps(1), simde_mm_load_ps({vA}.f32))");
  return true;
}

bool BuildVrsqrtefp(BuilderContext& ctx) {
  // The Xenon's estimate, from a table (rex/ppc/fp.h).
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr("rex::ppc::fp::vrsqrte(simde_mm_load_ps({vA}.f32))");
  return true;
}

bool BuildVexptefp(BuilderContext& ctx) {
  // The Xenon 2^x estimate (rex/ppc/fp.h).
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr("rex::ppc::fp::vexpte(simde_mm_load_ps({vA}.f32))");
  return true;
}

bool BuildVlogefp(BuilderContext& ctx) {
  // The Xenon log2 estimate (rex/ppc/fp.h).
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr("rex::ppc::fp::vloge(simde_mm_load_ps({vA}.f32))");
  return true;
}

//=============================================================================
// Vector Dot Products
//=============================================================================

bool BuildVmsum3fp128(BuilderContext& ctx) {
  // 3-element dot product accounting for guest->host vector element reversal
  // 0xEF = dot(yzw) with result broadcast to all elements (see constants doc)
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::simde_mm_vmsumfp<0xEF>(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVmsum4fp128(BuilderContext& ctx) {
  // 4-element dot product: 0xFF = all 4 elements, result to all (see constants doc)
  ctx.emit_set_flush_mode(true);
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::simde_mm_vmsumfp<0xFF>(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

//=============================================================================
// Vector Rounding
//=============================================================================

bool BuildVrfim(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr(
      "simde_mm_round_ps(simde_mm_load_ps({vA}.f32), "
      "SIMDE_MM_FROUND_TO_NEG_INF | SIMDE_MM_FROUND_NO_EXC)");
  return true;
}

bool BuildVrfin(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr(
      "simde_mm_round_ps(simde_mm_load_ps({vA}.f32), "
      "SIMDE_MM_FROUND_TO_NEAREST_INT | SIMDE_MM_FROUND_NO_EXC)");
  return true;
}

bool BuildVrfip(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr(
      "simde_mm_round_ps(simde_mm_load_ps({vA}.f32), "
      "SIMDE_MM_FROUND_TO_POS_INF | SIMDE_MM_FROUND_NO_EXC)");
  return true;
}

bool BuildVrfiz(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_unary_expr(
      "simde_mm_round_ps(simde_mm_load_ps({vA}.f32), "
      "SIMDE_MM_FROUND_TO_ZERO | SIMDE_MM_FROUND_NO_EXC)");
  return true;
}

//=============================================================================
// Vector Integer Arithmetic
//=============================================================================

namespace {
void emitArithmeticSaturation(BuilderContext& ctx, const char* lane, size_t count,
                              const char* lower, const char* upper, char operation) {
  for (size_t i = 0; i < count; ++i) {
    ctx.println(
        "\t{{ const int64_t value = int64_t({}.{}[{}]) {} int64_t({}.{}[{}]); "
        "if (value < {} || value > {}) ctx.vscr_sat = 1; }}",
        ctx.v(ctx.insn.operands[1]), lane, i, operation, ctx.v(ctx.insn.operands[2]), lane, i,
        lower, upper);
  }
}

void emitPackSaturation(BuilderContext& ctx, const char* lane, size_t count, const char* lower,
                        const char* upper) {
  for (size_t source = 1; source <= 2; ++source) {
    for (size_t i = 0; i < count; ++i) {
      ctx.println(
          "\tif (int64_t({}.{}[{}]) < {} || int64_t({}.{}[{}]) > {}) "
          "ctx.vscr_sat = 1;",
          ctx.v(ctx.insn.operands[source]), lane, i, lower, ctx.v(ctx.insn.operands[source]), lane,
          i, upper);
    }
  }
}
}  // namespace

bool BuildVaddsbs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "s8", 16, "INT8_MIN", "INT8_MAX", '+');
  ctx.emit_vec_int_binary("adds_epi8", "s8");
  return true;
}

bool BuildVaddshs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "s16", 8, "INT16_MIN", "INT16_MAX", '+');
  ctx.emit_vec_int_binary("adds_epi16", "s16");
  return true;
}

bool BuildVaddsws(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "s32", 4, "INT32_MIN", "INT32_MAX", '+');
  // vaddsws: Vector Add Signed Word Saturate
  auto vD = ctx.v(ctx.insn.operands[0]);
  auto vA = ctx.v(ctx.insn.operands[1]);
  auto vB = ctx.v(ctx.insn.operands[2]);

  ctx.println("\t{{");
  // No direct SSE intrinsic, so use overflow detection and blend
  ctx.println("\t\tsimde__m128i a = simde_mm_load_si128((simde__m128i*){}.u8);", vA);
  ctx.println("\t\tsimde__m128i b = simde_mm_load_si128((simde__m128i*){}.u8);", vB);
  ctx.println("\t\tsimde__m128i sum = simde_mm_add_epi32(a, b);");
  // Overflow if: (a ^ sum) & (b ^ sum) has MSB set (signs of a,b match but sum differs)
  ctx.println(
      "\t\tsimde__m128i overflow = simde_mm_and_si128(simde_mm_xor_si128(a, sum), "
      "simde_mm_xor_si128(b, sum));");
  // Saturation value: if a positive (MSB=0), use INT32_MAX;
  // if negative, use INT32_MIN (a >> 31) gives all 1s if negative, all 0s
  // if positive XOR with 0x7FFFFFFF: negative -> 0x80000000, positive -> 0x7FFFFFFF
  ctx.println(
      "\t\tsimde__m128i sat_val = simde_mm_xor_si128(simde_mm_srai_epi32(a, 31), "
      "simde_mm_set1_epi32(0x7FFFFFFF));");
  // Blend: select sat_val where overflow MSB is set, else sum
  ctx.println(
      "\t\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_castps_si128(simde_mm_blendv_ps("
      "simde_mm_castsi128_ps(sum), "
      "simde_mm_castsi128_ps(sat_val), "
      "simde_mm_castsi128_ps(overflow))));",
      vD);
  ctx.println("\t}}");
  return true;
}

bool BuildVaddubm(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("add_epi8", "u8");
  return true;
}

bool BuildVaddubs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "u8", 16, "0", "UINT8_MAX", '+');
  ctx.emit_vec_int_binary("adds_epu8", "u8");
  return true;
}

bool BuildVadduhm(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("add_epi16", "u16");
  return true;
}

bool BuildVadduwm(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("add_epi32", "u32");
  return true;
}

bool BuildVaddcuw(BuilderContext& ctx) {
  for (size_t i = 0; i < 4; ++i) {
    ctx.println("\t{}.u32[{}] = uint32_t(uint64_t({}.u32[{}]) + {}.u32[{}] > UINT32_MAX);",
                ctx.v(ctx.insn.operands[0]), i, ctx.v(ctx.insn.operands[1]), i,
                ctx.v(ctx.insn.operands[2]), i);
  }
  return true;
}

bool BuildVsubcuw(BuilderContext& ctx) {
  for (size_t i = 0; i < 4; ++i) {
    ctx.println("\t{}.u32[{}] = uint32_t({}.u32[{}] >= {}.u32[{}]);", ctx.v(ctx.insn.operands[0]),
                i, ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i);
  }
  return true;
}

bool BuildVavguw(BuilderContext& ctx) {
  for (size_t i = 0; i < 4; ++i) {
    ctx.println("\t{}.u32[{}] = uint32_t((uint64_t({}.u32[{}]) + {}.u32[{}] + 1) >> 1);",
                ctx.v(ctx.insn.operands[0]), i, ctx.v(ctx.insn.operands[1]), i,
                ctx.v(ctx.insn.operands[2]), i);
  }
  return true;
}

bool BuildVmaxuw(BuilderContext& ctx) {
  for (size_t i = 0; i < 4; ++i) {
    ctx.println("\t{}.u32[{}] = std::max({}.u32[{}], {}.u32[{}]);", ctx.v(ctx.insn.operands[0]), i,
                ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i);
  }
  return true;
}

bool BuildVadduws(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "u32", 4, "0", "UINT32_MAX", '+');
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u32, "
      "rex::ppc::simde_mm_adds_epu32(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_load_si128((simde__m128i*){}.u32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVadduhs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "u16", 8, "0", "UINT16_MAX", '+');
  ctx.emit_vec_int_binary("adds_epu16", "u16");
  return true;
}

bool BuildVsubsws(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "s32", 4, "INT32_MIN", "INT32_MAX", '-');
  // TODO: vectorize
  for (size_t i = 0; i < 4; i++) {
    ctx.println("\t{}.s64 = int64_t({}.s32[{}]) - int64_t({}.s32[{}]);", ctx.temp(),
                ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i);
    ctx.println("\t{}.s32[{}] = {}.s64 > INT_MAX ? INT_MAX : {}.s64 < INT_MIN ? INT_MIN : {}.s64;",
                ctx.v(ctx.insn.operands[0]), i, ctx.temp(), ctx.temp(), ctx.temp());
  }
  return true;
}

bool BuildVsububm(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("sub_epi8", "u8");
  return true;
}

bool BuildVsububs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "u8", 16, "0", "UINT8_MAX", '-');
  ctx.emit_vec_int_binary("subs_epu8", "u8");
  return true;
}

bool BuildVsubuws(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "u32", 4, "0", "UINT32_MAX", '-');
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u32, "
      "simde_mm_sub_epi32(simde_mm_load_si128((simde__m128i*) {}.u32), "
      "simde_mm_min_epu32(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_load_si128((simde__m128i*){}.u32))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]),
      ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVsubuhs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "u16", 8, "0", "UINT16_MAX", '-');
  ctx.emit_vec_int_binary("subs_epu16", "u16");
  return true;
}

bool BuildVsubuhm(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("sub_epi16", "u16");
  return true;
}

bool BuildVsubuwm(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("sub_epi32", "u32");
  return true;
}

bool BuildVmaxsw(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("max_epi32", "s32");
  return true;
}

bool BuildVmaxsh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("max_epi16", "s16");
  return true;
}

bool BuildVmaxsb(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("max_epi8", "s8");
  return true;
}

bool BuildVminsh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("min_epi16", "s16");
  return true;
}

bool BuildVminsb(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("min_epi8", "s8");
  return true;
}

bool BuildVminsw(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("min_epi32", "s32");
  return true;
}

bool BuildVmaxuh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("max_epu16", "u16");
  return true;
}

bool BuildVminuh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("min_epu16", "u16");
  return true;
}

bool BuildVminuw(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("min_epu32", "u32");
  return true;
}

bool BuildVsubsbs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "s8", 16, "INT8_MIN", "INT8_MAX", '-');
  ctx.emit_vec_int_binary("subs_epi8", "s8");
  return true;
}

bool BuildVmaxub(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("max_epu8", "u8");
  return true;
}

bool BuildVminub(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("min_epu8", "u8");
  return true;
}

bool BuildVsubshs(BuilderContext& ctx) {
  emitArithmeticSaturation(ctx, "s16", 8, "INT16_MIN", "INT16_MAX", '-');
  ctx.emit_vec_int_binary("subs_epi16", "s16");
  return true;
}

//=============================================================================
// Vector Average
//=============================================================================

bool BuildVavgsb(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_avg_epi8(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVavgsh(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u16, "
      "rex::ppc::simde_mm_avg_epi16(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_load_si128((simde__m128i*){}.u16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVavgsw(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s32, "
      "rex::ppc::simde_mm_avg_epi32("
      "simde_mm_load_si128((simde__m128i*){}.s32), "
      "simde_mm_load_si128((simde__m128i*){}.s32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVavgub(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("avg_epu8", "u8");
  return true;
}

bool BuildVavguh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("avg_epu16", "u16");
  return true;
}

//=============================================================================
// Vector Logical
//=============================================================================

bool BuildVand(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("and_si128", "u8");
  return true;
}

bool BuildVandc128(BuilderContext& ctx) {
  // vandc128: vD = vA & ~vB (simde_mm_andnot_si128 has reversed operand semantics)
  ctx.emit_vec_int_binary_swapped("andnot_si128", "u8");
  return true;
}

bool BuildVandc(BuilderContext& ctx) {
  // vandc: vD = vA & ~vB (simde_mm_andnot_si128 has reversed operand semantics)
  ctx.emit_vec_int_binary_swapped("andnot_si128", "u8");
  return true;
}

bool BuildVor(BuilderContext& ctx) {
  ctx.print("\tsimde_mm_store_si128((simde__m128i*){}.u8, ", ctx.v(ctx.insn.operands[0]));

  if (ctx.insn.operands[1] != ctx.insn.operands[2])
    ctx.println(
        "simde_mm_or_si128(simde_mm_load_si128((simde__m128i*){}.u8), "
        "simde_mm_load_si128((simde__m128i*){}.u8)));",
        ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  else
    ctx.println("simde_mm_load_si128((simde__m128i*){}.u8));", ctx.v(ctx.insn.operands[1]));

  return true;
}

bool BuildVxor(BuilderContext& ctx) {
  ctx.print("\tsimde_mm_store_si128((simde__m128i*){}.u8, ", ctx.v(ctx.insn.operands[0]));

  if (ctx.insn.operands[1] != ctx.insn.operands[2])
    ctx.println(
        "simde_mm_xor_si128(simde_mm_load_si128((simde__m128i*){}.u8), "
        "simde_mm_load_si128((simde__m128i*){}.u8)));",
        ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  else
    ctx.println("simde_mm_setzero_si128());");

  return true;
}

bool BuildVnor(BuilderContext& ctx) {
  // vnor: vD = ~(vA | vB)
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_xor_si128("
      "simde_mm_or_si128("
      "simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)), "
      "simde_mm_set1_epi32(-1)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVsel(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_or_si128(simde_mm_andnot_si128(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)), "
      "simde_mm_and_si128(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[3]), ctx.v(ctx.insn.operands[1]),
      ctx.v(ctx.insn.operands[3]), ctx.v(ctx.insn.operands[2]));
  return true;
}

//=============================================================================
// Vector Compare
//=============================================================================

bool BuildVcmpbfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  // vcmpbfp: Vector Compare Bounds Floating Point
  // For each element i:
  //   bit 0 (0x80000000) = 1 if vSrcA[i] > vSrcB[i]
  //   bit 1 (0x40000000) = 1 if vSrcA[i] < -vSrcB[i]
  auto vA = ctx.v(ctx.insn.operands[1]);
  auto vB = ctx.v(ctx.insn.operands[2]);
  auto vD = ctx.v(ctx.insn.operands[0]);

  // A NaN in either operand is out of bounds both ways (rex/ppc/fp.h).
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, rex::ppc::fp::vcmpb(simde_mm_load_ps({}.f32), "
      "simde_mm_load_ps({}.f32)));",
      vD, vA, vB);

  // CR6 from vD: movemask_ps only checks bit 31, but lower-bound violations only
  // set bit 30. Shift left by 1 to move bit 30 into bit 31, then OR with original
  // so movemask detects both upper and lower bound violations. vcmpbfp. sets
  // only CR6[2] (every element in bounds): 0x10 never matches, so CR6[0] stays
  // clear.
  if (isRecordForm(ctx.insn))
    ctx.println(
        "\t{}.setFromMask(simde_mm_castsi128_ps(simde_mm_or_si128("
        "simde_mm_load_si128((simde__m128i*){}.f32), "
        "simde_mm_slli_epi32(simde_mm_load_si128((simde__m128i*){}.f32), 1))), 0x10);",
        ctx.cr(6), vD, vD);
  return true;
}

bool BuildVcmpeqfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_binary("cmpeq");
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_ps({}.f32), 0xF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpequb(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("cmpeq_epi8", "u8");
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_si128((simde__m128i*){}.u8), 0xFFFF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpequh(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_cmpeq_epi16(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_load_si128((simde__m128i*){}.u16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_si128((simde__m128i*){}.u16), 0xFFFF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpequw(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_cmpeq_epi32(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_load_si128((simde__m128i*){}.u32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_ps({}.f32), 0xF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgefp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_binary("cmpge");
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_ps({}.f32), 0xF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtfp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.emit_vec_fp_binary("cmpgt");
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_ps({}.f32), 0xF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtub(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_cmpgt_epu8(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_si128((simde__m128i*){}.u8), 0xFFFF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtuh(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_cmpgt_epu16(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_load_si128((simde__m128i*){}.u16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_si128((simde__m128i*){}.u16), 0xFFFF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtuw(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u32, "
      "simde_mm_cmpgt_epi32(simde_mm_xor_si128(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_set1_epi32((int32_t)0x80000000)), "
      "simde_mm_xor_si128(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_set1_epi32((int32_t)0x80000000))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));

  if (isRecordForm(ctx.insn))
    ctx.println(
        "\t{}.setFromMask(simde_mm_castsi128_ps(simde_mm_load_si128((simde__m128i*){}.u32)), 0xF);",
        ctx.cr(6), ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtsb(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("cmpgt_epi8", "u8");
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_si128((simde__m128i*){}.u8), 0xFFFF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtsh(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_cmpgt_epi16(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_load_si128((simde__m128i*){}.u16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  if (isRecordForm(ctx.insn))
    ctx.println("\t{}.setFromMask(simde_mm_load_si128((simde__m128i*){}.u16), 0xFFFF);", ctx.cr(6),
                ctx.v(ctx.insn.operands[0]));
  return true;
}

bool BuildVcmpgtsw(BuilderContext& ctx) {
  ctx.emit_vec_int_binary("cmpgt_epi32", "u32");
  if (isRecordForm(ctx.insn))
    ctx.println(
        "\t{}.setFromMask(simde_mm_castsi128_ps(simde_mm_load_si128((simde__m128i*){}.u32)), 0xF);",
        ctx.cr(6), ctx.v(ctx.insn.operands[0]));
  return true;
}

//=============================================================================
// Vector Conversion
//=============================================================================

bool BuildVctsxs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.print("\tsimde_mm_store_si128((simde__m128i*){}.s32, rex::ppc::simde_mm_vctsxs(",
            ctx.v(ctx.insn.operands[0]));
  if (ctx.insn.operands[2] != 0)
    ctx.println("simde_mm_mul_ps(simde_mm_load_ps({}.f32), simde_mm_set1_ps({}))));",
                ctx.v(ctx.insn.operands[1]), 1u << ctx.insn.operands[2]);
  else
    ctx.println("simde_mm_load_ps({}.f32)));", ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVcfsx(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.print("\tsimde_mm_store_ps({}.f32, ", ctx.v(ctx.insn.operands[0]));
  if (ctx.insn.operands[2] != 0) {
    const float value = std::ldexp(1.0f, -static_cast<int32_t>(ctx.insn.operands[2]));
    ctx.println(
        "simde_mm_mul_ps(simde_mm_cvtepi32_ps(simde_mm_load_si128((simde__m128i*){}.u32)), "
        "simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0x{:X})))));",
        ctx.v(ctx.insn.operands[1]), *reinterpret_cast<const uint32_t*>(&value));
  } else {
    ctx.println("simde_mm_cvtepi32_ps(simde_mm_load_si128((simde__m128i*){}.u32)));",
                ctx.v(ctx.insn.operands[1]));
  }
  return true;
}

bool BuildVcfux(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(true);
  ctx.print("\tsimde_mm_store_ps({}.f32, ", ctx.v(ctx.insn.operands[0]));
  if (ctx.insn.operands[2] != 0) {
    const float value = std::ldexp(1.0f, -static_cast<int32_t>(ctx.insn.operands[2]));
    ctx.println(
        "simde_mm_mul_ps(rex::ppc::simde_mm_cvtepu32_ps_(simde_mm_load_si128((simde__m128i*){}.u32)"
        "), "
        "simde_mm_castsi128_ps(simde_mm_set1_epi32(int(0x{:X})))));",
        ctx.v(ctx.insn.operands[1]), *reinterpret_cast<const uint32_t*>(&value));
  } else {
    ctx.println("rex::ppc::simde_mm_cvtepu32_ps_(simde_mm_load_si128((simde__m128i*){}.u32)));",
                ctx.v(ctx.insn.operands[1]));
  }
  return true;
}

bool BuildVctuxs(BuilderContext& ctx) {
  // Vector Convert To Unsigned Fixed-Point Word Saturate
  ctx.emit_set_flush_mode(true);
  ctx.print("\tsimde_mm_store_si128((simde__m128i*){}.u32, rex::ppc::simde_mm_vctuxs(",
            ctx.v(ctx.insn.operands[0]));
  if (ctx.insn.operands[2] != 0)
    ctx.println("simde_mm_mul_ps(simde_mm_load_ps({}.f32), simde_mm_set1_ps({}))));",
                ctx.v(ctx.insn.operands[1]), 1u << ctx.insn.operands[2]);
  else
    ctx.println("simde_mm_load_ps({}.f32)));", ctx.v(ctx.insn.operands[1]));
  return true;
}

//=============================================================================
// Vector Merge
//=============================================================================

bool BuildVmrghb(BuilderContext& ctx) {
  ctx.emit_vec_int_binary_swapped("unpackhi_epi8", "u8");
  return true;
}

bool BuildVmrghh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary_swapped("unpackhi_epi16", "u16");
  return true;
}

bool BuildVmrghw(BuilderContext& ctx) {
  ctx.emit_vec_int_binary_swapped("unpackhi_epi32", "u32");
  return true;
}

bool BuildVmrglb(BuilderContext& ctx) {
  ctx.emit_vec_int_binary_swapped("unpacklo_epi8", "u8");
  return true;
}

bool BuildVmrglh(BuilderContext& ctx) {
  ctx.emit_vec_int_binary_swapped("unpacklo_epi16", "u16");
  return true;
}

bool BuildVmrglw(BuilderContext& ctx) {
  ctx.emit_vec_int_binary_swapped("unpacklo_epi32", "u32");
  return true;
}

//=============================================================================
// Vector Permute
//=============================================================================

bool BuildVperm(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_perm_epi8_(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8), simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]),
      ctx.v(ctx.insn.operands[3]));
  return true;
}

bool BuildVpermwi128(BuilderContext& ctx) {
  // NOTE: accounting for full vector reversal here
  uint32_t x = 3 - (ctx.insn.operands[2] & 0x3);
  uint32_t y = 3 - ((ctx.insn.operands[2] >> 2) & 0x3);
  uint32_t z = 3 - ((ctx.insn.operands[2] >> 4) & 0x3);
  uint32_t w = 3 - ((ctx.insn.operands[2] >> 6) & 0x3);
  uint32_t perm = x | (y << 2) | (z << 4) | (w << 6);
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u32, "
      "simde_mm_shuffle_epi32(simde_mm_load_si128((simde__m128i*){}.u32), 0x{:X}));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), perm);
  return true;
}

bool BuildVrlimi128(BuilderContext& ctx) {
  constexpr size_t shuffles[] = {SIMDE_MM_SHUFFLE(3, 2, 1, 0), SIMDE_MM_SHUFFLE(2, 1, 0, 3),
                                 SIMDE_MM_SHUFFLE(1, 0, 3, 2), SIMDE_MM_SHUFFLE(0, 3, 2, 1)};
  ctx.println(
      "\tsimde_mm_store_ps({}.f32, simde_mm_blend_ps(simde_mm_load_ps({}.f32), "
      "simde_mm_permute_ps(simde_mm_load_ps({}.f32), {}), {}));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]),
      shuffles[ctx.insn.operands[3]], ctx.insn.operands[2]);
  return true;
}

//=============================================================================
// Vector Shift
//=============================================================================

bool BuildVslb(BuilderContext& ctx) {
  ctx.emit_vec_var_shift("sllv", "epi8", 0x7);
  return true;
}

bool BuildVsldoi(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_alignr_epi8(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8), {}));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]),
      16 - ctx.insn.operands[3]);
  return true;
}

bool BuildVslh(BuilderContext& ctx) {
  ctx.emit_vec_var_shift("sllv", "epi16", 0xF);
  return true;
}

bool BuildVsrh(BuilderContext& ctx) {
  ctx.emit_vec_var_shift("srlv", "epi16", 0xF);
  return true;
}

bool BuildVsrb(BuilderContext& ctx) {
  // TODO(tomc): vectorize
  for (size_t i = 0; i < 16; i++)
    ctx.println("\t{}.u8[{}] = {}.u8[{}] >> ({}.u8[{}] & 0x7);", ctx.v(ctx.insn.operands[0]), i,
                ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i);
  return true;
}

bool BuildVsrab(BuilderContext& ctx) {
  // TODO(tomc): vectorize
  for (size_t i = 0; i < 16; i++)
    ctx.println("\t{}.s8[{}] = {}.s8[{}] >> ({}.u8[{}] & 0x7);", ctx.v(ctx.insn.operands[0]), i,
                ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i);
  return true;
}

bool BuildVsrah(BuilderContext& ctx) {
  ctx.emit_vec_var_shift("srav", "epi16", 0xF);
  return true;
}

bool BuildVrlb(BuilderContext& ctx) {
  // Rotate each byte left by the low 3 bits of the matching byte of vB.
  for (size_t i = 0; i < 16; i++) {
    ctx.println("	{{ uint8_t sh = {}.u8[{}] & 0x7;", ctx.v(ctx.insn.operands[2]), i);
    ctx.println("	{}.u8[{}] = uint8_t(({}.u8[{}] << sh) | ({}.u8[{}] >> ((8 - sh) & 0x7))); }}",
                ctx.v(ctx.insn.operands[0]), i, ctx.v(ctx.insn.operands[1]), i,
                ctx.v(ctx.insn.operands[1]), i);
  }
  return true;
}

bool BuildVrlh(BuilderContext& ctx) {
  auto vD = ctx.v(ctx.insn.operands[0]);
  auto vA = ctx.v(ctx.insn.operands[1]);
  auto vB = ctx.v(ctx.insn.operands[2]);
  ctx.println("\t{{");
  ctx.println("\t\tsimde__m128i a = simde_mm_load_si128((simde__m128i*){}.u8);", vA);
  ctx.println("\t\tsimde__m128i sh = simde_mm_and_si128(");
  ctx.println("\t\t\tsimde_mm_load_si128((simde__m128i*){}.u8), simde_mm_set1_epi16(0xF));", vB);
  ctx.println("\t\tsimde__m128i rsh = simde_mm_sub_epi16(simde_mm_set1_epi16(16), sh);");
  ctx.println("\t\tsimde__m128i result = simde_mm_or_si128(");
  ctx.println("\t\t\trex::ppc::simde_mm_sllv_epi16(a, sh),");
  ctx.println("\t\t\trex::ppc::simde_mm_srlv_epi16(a, rsh));");
  ctx.println("\t\tsimde_mm_store_si128((simde__m128i*){}.u8, result);", vD);
  ctx.println("\t}}");
  return true;
}

bool BuildVrlw(BuilderContext& ctx) {
  // TODO(tomc): vectorize
  for (size_t i = 0; i < 4; i++) {
    ctx.println("\t{{ uint32_t sh = {}.u32[{}] & 0x1F;", ctx.v(ctx.insn.operands[2]), i);
    ctx.println("\t{}.u32[{}] = ({}.u32[{}] << sh) | (sh ? ({}.u32[{}] >> (32 - sh)) : 0); }}",
                ctx.v(ctx.insn.operands[0]), i, ctx.v(ctx.insn.operands[1]), i,
                ctx.v(ctx.insn.operands[1]), i);
  }
  return true;
}

bool BuildVsl(BuilderContext& ctx) {
  // Vector Shift Left (128-bit) - shift entire vector left by bits specified in low 3 bits of vB
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_vsl(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVslo(BuilderContext& ctx) {
  // Vector Shift Left by Octet - shift entire vector left by bytes specified in bits 121:124 of vB
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_vslo(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVsro(BuilderContext& ctx) {
  // Vector Shift Right by Octet - shift entire vector right by bytes specified in bits 121:124 of
  // vB
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_vsro(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVslw(BuilderContext& ctx) {
  auto vD = ctx.v(ctx.insn.operands[0]);
  auto vA = ctx.v(ctx.insn.operands[1]);
  auto vB = ctx.v(ctx.insn.operands[2]);
  ctx.println("\t{{");
  ctx.println("\t\tsimde__m128i a = simde_mm_load_si128((simde__m128i*){}.u8);", vA);
  ctx.println("\t\tsimde__m128i b = simde_mm_load_si128((simde__m128i*){}.u8);", vB);
  ctx.println("\t\tsimde__m128i shift = simde_mm_and_si128(b, simde_mm_set1_epi32(0x1F));");
  ctx.println(
      "\t\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_sllv_epi32(a, shift));",
      vD);
  ctx.println("\t}}");
  return true;
}

bool BuildVsr(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "rex::ppc::simde_mm_vsr(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_load_si128((simde__m128i*){}.u8)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[2]));
  return true;
}

bool BuildVsraw(BuilderContext& ctx) {
  // TODO(tomc): vectorize
  for (size_t i = 0; i < 4; i++)
    ctx.println("\t{}.s32[{}] = {}.s32[{}] >> ({}.u8[{}] & 0x1F);", ctx.v(ctx.insn.operands[0]), i,
                ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i * 4);
  return true;
}

bool BuildVsrw(BuilderContext& ctx) {
  // TODO(tomc): vectorize
  for (size_t i = 0; i < 4; i++)
    ctx.println("\t{}.u32[{}] = {}.u32[{}] >> ({}.u8[{}] & 0x1F);", ctx.v(ctx.insn.operands[0]), i,
                ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[2]), i * 4);
  return true;
}

//=============================================================================
// Vector Splat
//=============================================================================

bool BuildVspltb(BuilderContext& ctx) {
  // NOTE: accounting for full vector reversal here
  uint32_t perm = 15 - ctx.insn.operands[2];
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*){}.u8), "
      "simde_mm_set1_epi8(char(0x{:X}))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), perm);
  return true;
}

bool BuildVsplth(BuilderContext& ctx) {
  // NOTE: accounting for full vector reversal here
  uint32_t perm = 7 - ctx.insn.operands[2];
  perm = (perm * 2) | ((perm * 2 + 1) << 8);
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u16, "
      "simde_mm_shuffle_epi8(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_set1_epi16(short(0x{:X}))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), perm);
  return true;
}

bool BuildVspltisb(BuilderContext& ctx) {
  // Sign-extend 5-bit immediate to 8-bit
  int8_t imm5 = static_cast<int8_t>(ctx.insn.operands[1] << 3) >> 3;
  ctx.println("\tsimde_mm_store_si128((simde__m128i*){}.u8, simde_mm_set1_epi8(char(0x{:X})));",
              ctx.v(ctx.insn.operands[0]), static_cast<uint8_t>(imm5));
  return true;
}

bool BuildVspltisw(BuilderContext& ctx) {
  // Sign-extend 5-bit immediate to 32-bit
  int8_t imm5 = static_cast<int8_t>(ctx.insn.operands[1] << 3) >> 3;
  ctx.println("\tsimde_mm_store_si128((simde__m128i*){}.u32, simde_mm_set1_epi32(int(0x{:X})));",
              ctx.v(ctx.insn.operands[0]), static_cast<uint32_t>(static_cast<int32_t>(imm5)));
  return true;
}

bool BuildVspltish(BuilderContext& ctx) {
  // Sign-extend 5-bit immediate to 16-bit
  int8_t imm5 = static_cast<int8_t>(ctx.insn.operands[1] << 3) >> 3;
  ctx.println("\tsimde_mm_store_si128((simde__m128i*){}.s16, simde_mm_set1_epi16(short(0x{:X})));",
              ctx.v(ctx.insn.operands[0]), static_cast<uint16_t>(static_cast<int16_t>(imm5)));
  return true;
}

bool BuildVspltw(BuilderContext& ctx) {
  // NOTE: accounting for full vector reversal here
  uint32_t perm = 3 - ctx.insn.operands[2];
  perm |= (perm << 2) | (perm << 4) | (perm << 6);
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u32, "
      "simde_mm_shuffle_epi32(simde_mm_load_si128((simde__m128i*){}.u32), 0x{:X}));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), perm);
  return true;
}

//=============================================================================
// Vector Pack
//=============================================================================

bool BuildVpkshus(BuilderContext& ctx) {
  emitPackSaturation(ctx, "s16", 8, "0", "UINT8_MAX");
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_packus_epi16(simde_mm_load_si128((simde__m128i*){}.s16), "
      "simde_mm_load_si128((simde__m128i*){}.s16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[2]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVpkuhum(BuilderContext& ctx) {
  // Vector Pack Unsigned Halfword Unsigned Modulo - pack low 8 bits from each halfword
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u8, "
      "simde_mm_packus_epi16(simde_mm_and_si128(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_set1_epi16(0xFF)), simde_mm_and_si128(simde_mm_load_si128((simde__m128i*){}.u16), "
      "simde_mm_set1_epi16(0xFF))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[2]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVpkuhus(BuilderContext& ctx) {
  emitPackSaturation(ctx, "u16", 8, "0", "UINT8_MAX");
  // Vector Pack Unsigned Halfword Unsigned Saturate
  // NOTE(tomc): _mm_packus_epi16 treats inputs as signed, so we need custom saturation for
  // unsigned. Unsigned halfwords >= 0x8000 would be interpreted as negative and clamped to 0
  // instead of 0xFF.
  // vD can alias vA/vB, so pack into vTemp first.
  for (size_t i = 0; i < 8; i++) {
    ctx.println("\t{}.u8[{}] = {}.u16[{}] > 0xFF ? 0xFF : (uint8_t){}.u16[{}];", ctx.v_temp(),
                15 - i, ctx.v(ctx.insn.operands[1]), 7 - i, ctx.v(ctx.insn.operands[1]), 7 - i);
    ctx.println("\t{}.u8[{}] = {}.u16[{}] > 0xFF ? 0xFF : (uint8_t){}.u16[{}];", ctx.v_temp(),
                7 - i, ctx.v(ctx.insn.operands[2]), 7 - i, ctx.v(ctx.insn.operands[2]), 7 - i);
  }
  ctx.println("\t{} = {};", ctx.v(ctx.insn.operands[0]), ctx.v_temp());
  return true;
}

bool BuildVpkuwum(BuilderContext& ctx) {
  // Vector Pack Unsigned Word Unsigned Modulo - pack low 16 bits from each word
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u16, "
      "simde_mm_packus_epi32(simde_mm_and_si128(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_set1_epi32(0xFFFF)), "
      "simde_mm_and_si128(simde_mm_load_si128((simde__m128i*){}.u32), "
      "simde_mm_set1_epi32(0xFFFF))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[2]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVpkuwus(BuilderContext& ctx) {
  emitPackSaturation(ctx, "u32", 4, "0", "UINT16_MAX");
  // Vector Pack Unsigned Word Unsigned Saturate

  // NOTE(tomc): _mm_packus_epi32 treats inputs as signed, so we need custom saturation for unsigned
  // Saturate each u32 to [0, 0xFFFF], then pack to u16
  // vD can alias vA/vB, so pack into vTemp first.
  for (size_t i = 0; i < 4; i++) {
    ctx.println("\t{}.u16[{}] = {}.u32[{}] > 0xFFFF ? 0xFFFF : (uint16_t){}.u32[{}];", ctx.v_temp(),
                7 - i, ctx.v(ctx.insn.operands[1]), 3 - i, ctx.v(ctx.insn.operands[1]), 3 - i);
    ctx.println("\t{}.u16[{}] = {}.u32[{}] > 0xFFFF ? 0xFFFF : (uint16_t){}.u32[{}];", ctx.v_temp(),
                3 - i, ctx.v(ctx.insn.operands[2]), 3 - i, ctx.v(ctx.insn.operands[2]), 3 - i);
  }
  ctx.println("\t{} = {};", ctx.v(ctx.insn.operands[0]), ctx.v_temp());
  return true;
}

bool BuildVpkshss(BuilderContext& ctx) {
  emitPackSaturation(ctx, "s16", 8, "INT8_MIN", "INT8_MAX");
  // Vector Pack Signed Halfword Signed Saturate
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s8, "
      "simde_mm_packs_epi16(simde_mm_load_si128((simde__m128i*){}.s16), "
      "simde_mm_load_si128((simde__m128i*){}.s16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[2]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVpkswss(BuilderContext& ctx) {
  emitPackSaturation(ctx, "s32", 4, "INT16_MIN", "INT16_MAX");
  // Vector Pack Signed Word Signed Saturate
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s16, "
      "simde_mm_packs_epi32(simde_mm_load_si128((simde__m128i*){}.s32), "
      "simde_mm_load_si128((simde__m128i*){}.s32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[2]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVpkswus(BuilderContext& ctx) {
  emitPackSaturation(ctx, "s32", 4, "0", "UINT16_MAX");
  // Vector Pack Signed Word Unsigned Saturate
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.u16, "
      "simde_mm_packus_epi32(simde_mm_load_si128((simde__m128i*){}.s32), "
      "simde_mm_load_si128((simde__m128i*){}.s32)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[2]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVpkpx(BuilderContext& ctx) {
  // Guest pixels are ARGB8888 and the packed result is A1R5G5B5.
  // Snapshot both inputs so vD may alias either source register.
  ctx.println("\t{{");
  for (size_t i = 0; i < 8; ++i) {
    const auto source = ctx.v(ctx.insn.operands[i < 4 ? 2 : 1]);
    ctx.println("\t\tconst uint32_t pixel{} = {}.u32[{}];", i, source, i & 3);
  }
  for (size_t i = 0; i < 8; ++i) {
    ctx.println(
        "\t\t{}.u16[{}] = uint16_t(((pixel{} >> 9) & 0xFC00) | "
        "((pixel{} >> 6) & 0x3E0) | "
        "((pixel{} >> 3) & 0x1F));",
        ctx.v(ctx.insn.operands[0]), i, i, i, i);
  }
  ctx.println("\t}}");
  return true;
}

bool BuildVpkd3d128(BuilderContext& ctx) {
  // TODO(tomc): vectorize
  // NOTE: handling vector reversal here too
  ctx.emit_set_flush_mode(true);
  switch (ctx.insn.operands[2]) {
    case 0:  // D3D color
    {
      uint32_t mask = ctx.insn.operands[3];
      uint32_t shift = ctx.insn.operands[4];

      // Pack the 4 floats to D3DCOLOR
      for (size_t i = 0; i < 4; i++) {
        constexpr size_t indices[] = {3, 0, 1, 2};
        ctx.println("\t{}.u32[{}] = 0x404000FF;", ctx.v_temp(), i);
        // Use !(x >= 3.0f) instead of (x < 3.0f) to properly clamp NaN to minimum
        ctx.println(
            "\t{}.f32[{}] = !({}.f32[{}] >= 3.0f) ? 3.0f : ({}.f32[{}] > {}.f32[{}] ? {}.f32[{}] : "
            "{}.f32[{}]);",
            ctx.v_temp(), i, ctx.v(ctx.insn.operands[1]), i, ctx.v(ctx.insn.operands[1]), i,
            ctx.v_temp(), i, ctx.v_temp(), i, ctx.v(ctx.insn.operands[1]), i);
        ctx.println("\t{}.u32 {}= uint32_t({}.u8[{}]) << {};", ctx.temp(), i == 0 ? "" : "|",
                    ctx.v_temp(), i * 4, indices[i] * 8);
      }

      // Handle mask operand:
      // mask=1: Write result to word[shift]
      // mask=2: Write result to word[shift], clear word[shift+1] to 0
      // mask=3: Same as mask=2, but for shift=3 only clear word[0] (don't write result)
      if (mask == 3 && shift == 3) {
        // Special case: mask=3, shift=3 - only clear word 0
        ctx.println("\t{}.u32[0] = 0;", ctx.v(ctx.insn.operands[0]));
      } else {
        // Write result to word[shift]
        ctx.println("\t{}.u32[{}] = {}.u32;", ctx.v(ctx.insn.operands[0]), shift, ctx.temp());
        // For mask=2 or mask=3, also clear the adjacent word
        if (mask >= 2 && shift < 3) {
          ctx.println("\t{}.u32[{}] = 0;", ctx.v(ctx.insn.operands[0]), shift + 1);
        }
      }
      break;
    }

    case 1:  // NORMSHORT2 - pack 2 floats (in 3.0+X form) to 2 signed shorts
    {
      // Extract signed 16-bit values from floats and pack into one 32-bit word
      // floats are in form: 3.0f + X (stored as integer add to 3.0f representation 0x40400000)
      // We need to saturate to signed 16-bit range [-32767, 32767] (NOT -32768, based on tests)
      // NOTE: Guest element 0 is at array index 3, element 1 is at index 2 (reversed for host)
      // Element 0 (index 3) goes to HIGH word, element 1 (index 2) goes to LOW word
      ctx.println("\t{}.s32 = {}.s32[3] - 0x40400000;", ctx.temp(), ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.s32 = {}.s32 > 32767 ? 32767 : ({}.s32 < -32767 ? -32767 : {}.s32);",
                  ctx.temp(), ctx.temp(), ctx.temp(), ctx.temp());
      ctx.println("\t{}.u32[0] = uint32_t(uint16_t({}.s32)) << 16;", ctx.v_temp(),
                  ctx.temp());  // element 0 to high word
      ctx.println("\t{}.s32 = {}.s32[2] - 0x40400000;", ctx.temp(), ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.s32 = {}.s32 > 32767 ? 32767 : ({}.s32 < -32767 ? -32767 : {}.s32);",
                  ctx.temp(), ctx.temp(), ctx.temp(), ctx.temp());
      ctx.println("\t{}.u32[0] |= uint16_t({}.s32);", ctx.v_temp(),
                  ctx.temp());  // element 1 to low word
      ctx.println("\t{}.u32[{}] = {}.u32[0];", ctx.v(ctx.insn.operands[0]), ctx.insn.operands[4],
                  ctx.v_temp());
      break;
    }

    case 2:  // NORMPACKED32 - pack 4 floats (in 3.0+X form) to 2:10:10:10 format (w:x:y:z)
    {
      // Format: 2 bits for w (element 3), 10 bits each for x, y, z (elements 0, 1, 2)
      // Input floats are in 3.0+X form where X is the integer to pack
      // Algorithm: saturate float to range, then mask low bits to extract X
      // Constants kPack2101010_* are defined in ppc/context.h
      ctx.println("\t{}.u32[0] = 0;", ctx.v_temp());

      // Pack x (10 bits, position 0-9) - Guest element 0 is at index 3
      ctx.println(
          "\t{}.f32 = {}.f32[3] < kPack2101010_Min10 ? kPack2101010_Min10 : ({}.f32[3] > "
          "kPack2101010_Max10 ? kPack2101010_Max10 : {}.f32[3]);",
          ctx.temp(), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]),
          ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u32[0] = {}.u32 & 0x3FF;", ctx.v_temp(), ctx.temp());

      // Pack y (10 bits, position 10-19) - Guest element 1 is at index 2
      ctx.println(
          "\t{}.f32 = {}.f32[2] < kPack2101010_Min10 ? kPack2101010_Min10 : ({}.f32[2] > "
          "kPack2101010_Max10 ? kPack2101010_Max10 : {}.f32[2]);",
          ctx.temp(), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]),
          ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u32[0] |= ({}.u32 & 0x3FF) << 10;", ctx.v_temp(), ctx.temp());

      // Pack z (10 bits, position 20-29) - Guest element 2 is at index 1
      ctx.println(
          "\t{}.f32 = {}.f32[1] < kPack2101010_Min10 ? kPack2101010_Min10 : ({}.f32[1] > "
          "kPack2101010_Max10 ? kPack2101010_Max10 : {}.f32[1]);",
          ctx.temp(), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]),
          ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u32[0] |= ({}.u32 & 0x3FF) << 20;", ctx.v_temp(), ctx.temp());

      // Pack w (2 bits, position 30-31) - Guest element 3 is at index 0
      ctx.println(
          "\t{}.f32 = {}.f32[0] < kPack2101010_Min2 ? kPack2101010_Min2 : ({}.f32[0] > "
          "kPack2101010_Max2 ? kPack2101010_Max2 : {}.f32[0]);",
          ctx.temp(), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]),
          ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u32[0] |= ({}.u32 & 0x3) << 30;", ctx.v_temp(), ctx.temp());

      ctx.println("\t{}.u32[{}] = {}.u32[0];", ctx.v(ctx.insn.operands[0]), ctx.insn.operands[4],
                  ctx.v_temp());
      break;
    }

    case 3:  // FLOAT16_2 - pack 2 floats to 2 float16s
    {
      // Pack 2 elements into 32 bits (1 word)
      // Guest element 0 goes to high 16 bits, element 1 to low 16 bits
      // Output u16 index = (1-i) + 2*shift for element i
      for (size_t i = 0; i < 2; i++) {
        size_t srcIdx = 3 - i;  // Guest element i is at host array index 3-i
        size_t dstIdx =
            (1 - i) + (2 * ctx.insn.operands[4]);  // Output reversed: elem 0 to high, elem 1 to low
        ctx.println("\t{}.u32 = ({}.u32[{}]&0x7FFFFFFF);", ctx.temp(), ctx.v(ctx.insn.operands[1]),
                    srcIdx);
        ctx.println(
            "\t{0}.u8[0] = ({1}.f32 != {1}.f32) || ({1}.f32 > 65504.0f) ? 0xFF : "
            "(({2}.u32[{3}]&0x7f800000)>>23);",
            ctx.v_temp(), ctx.temp(), ctx.v(ctx.insn.operands[1]), srcIdx);
        ctx.println("\t{}.u16 = {}.u8[0] != 0xFF ? (({}.u32[{}]&0x7FE000)>>13) : 0x0;", ctx.temp(),
                    ctx.v_temp(), ctx.v(ctx.insn.operands[1]), srcIdx);
        ctx.println(
            "\t{0}.u16[{1}] = {2}.u8[0] != 0xFF ? ({2}.u8[0] > 0x70 ? "
            "((({2}.u8[0]-0x70)<<10)+{3}.u16) : (0x71-{2}.u8[0] > 31 ? 0x0 : "
            "((0x400+{3}.u16)>>(0x71-{2}.u8[0])))) : 0x7FFF;",
            ctx.v(ctx.insn.operands[0]), dstIdx, ctx.v_temp(), ctx.temp());
        ctx.println("\t{}.u16[{}] |= (({}.u32[{}]&0x80000000)>>16);", ctx.v(ctx.insn.operands[0]),
                    dstIdx, ctx.v(ctx.insn.operands[1]), srcIdx);
      }
      break;
    }

    case 4:  // NORMSHORT4 - pack 4 floats (in 3.0+X form) to 4 signed shorts
    {
      // Pack 4 elements into 64 bits (2 words)
      // Guest element 0 goes to highest 16-bit position, element 3 to lowest
      // Output u16 index = (3-i) + 2*shift for element i
      for (size_t i = 0; i < 4; i++) {
        size_t srcIdx = 3 - i;  // Guest element i is at host array index 3-i
        size_t dstIdx = (3 - i) + (2 * ctx.insn.operands[4]);  // Output also reversed
        ctx.println("\t{}.s32 = {}.s32[{}] - 0x40400000;", ctx.temp(), ctx.v(ctx.insn.operands[1]),
                    srcIdx);
        ctx.println("\t{}.s32 = {}.s32 > 32767 ? 32767 : ({}.s32 < -32767 ? -32767 : {}.s32);",
                    ctx.temp(), ctx.temp(), ctx.temp(), ctx.temp());
        ctx.println("\t{}.u16[{}] = uint16_t({}.s32);", ctx.v(ctx.insn.operands[0]), dstIdx,
                    ctx.temp());
      }
      break;
    }

    case 5:  // float16_4
    {
      // Pack 4 elements into 64 bits (4 x 16-bit floats)
      // Guest element 0 goes to highest 16-bit position, element 3 to lowest
      // Output u16 index = (3-i) + 2*shift for element i
      // Packs 2 and 3 place the 64 bits alike except at shift 3 (Xenia's
      // vpkd3d128 permute masks).
      if ((ctx.insn.operands[3] != 2 && ctx.insn.operands[3] != 3) || ctx.insn.operands[4] > 2)
        REXCODEGEN_WARN("Unexpected float16_4 pack instruction at {:X}", ctx.base);

      for (size_t i = 0; i < 4; i++) {
        size_t srcIdx = 3 - i;  // Guest element i is at host array index 3-i
        size_t dstIdx = (3 - i) + (2 * ctx.insn.operands[4]);  // Output also reversed
        ctx.println("\t{}.u32 = ({}.u32[{}]&0x7FFFFFFF);", ctx.temp(), ctx.v(ctx.insn.operands[1]),
                    srcIdx);
        ctx.println(
            "\t{0}.u8[0] = ({1}.f32 != {1}.f32) || ({1}.f32 > 65504.0f) ? 0xFF : "
            "(({2}.u32[{3}]&0x7f800000)>>23);",
            ctx.v_temp(), ctx.temp(), ctx.v(ctx.insn.operands[1]), srcIdx);
        ctx.println("\t{}.u16 = {}.u8[0] != 0xFF ? (({}.u32[{}]&0x7FE000)>>13) : 0x0;", ctx.temp(),
                    ctx.v_temp(), ctx.v(ctx.insn.operands[1]), srcIdx);
        ctx.println(
            "\t{0}.u16[{1}] = {2}.u8[0] != 0xFF ? ({2}.u8[0] > 0x70 ? "
            "((({2}.u8[0]-0x70)<<10)+{3}.u16) : (0x71-{2}.u8[0] > 31 ? 0x0 : "
            "((0x400+{3}.u16)>>(0x71-{2}.u8[0])))) : 0x7FFF;",
            ctx.v(ctx.insn.operands[0]), dstIdx, ctx.v_temp(), ctx.temp());
        ctx.println("\t{}.u16[{}] |= (({}.u32[{}]&0x80000000)>>16);", ctx.v(ctx.insn.operands[0]),
                    dstIdx, ctx.v(ctx.insn.operands[1]), srcIdx);
      }
      break;
    }

    case 6:  // NORMPACKED64 - pack 4 floats to 4:20:20:20 format
    {
      // Format: 4 bits for w, 20 bits each for x, y, z (packed into 64 bits)
      ctx.println("\t{}.u64[0] = 0;", ctx.v_temp());
      // Pack x (20 bits, position 0-19)
      ctx.println("\t{}.s32 = int32_t({}.f32[0]);", ctx.temp(), ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u64[0] = uint64_t({}.s32 & 0xFFFFF);", ctx.v_temp(), ctx.temp());
      // Pack y (20 bits, position 20-39)
      ctx.println("\t{}.s32 = int32_t({}.f32[1]);", ctx.temp(), ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u64[0] |= uint64_t({}.s32 & 0xFFFFF) << 20;", ctx.v_temp(), ctx.temp());
      // Pack z (20 bits, position 40-59)
      ctx.println("\t{}.s32 = int32_t({}.f32[2]);", ctx.temp(), ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u64[0] |= uint64_t({}.s32 & 0xFFFFF) << 40;", ctx.v_temp(), ctx.temp());
      // Pack w (4 bits, position 60-63)
      ctx.println("\t{}.s32 = int32_t({}.f32[3]);", ctx.temp(), ctx.v(ctx.insn.operands[1]));
      ctx.println("\t{}.u64[0] |= uint64_t({}.s32 & 0xF) << 60;", ctx.v_temp(), ctx.temp());
      ctx.println("\t{}.u64[{}] = {}.u64[0];", ctx.v(ctx.insn.operands[0]),
                  ctx.insn.operands[4] >> 1, ctx.v_temp());
      break;
    }

    default:
      ctx.println("\t__builtin_debugtrap();");
      break;
  }
  return true;
}

//=============================================================================
// Vector Unpack
//=============================================================================

bool BuildVupkd3d128(BuilderContext& ctx) {
  // TODO(tomc): Vectorize
  // NOTE: handling vector reversal here too
  switch (ctx.insn.operands[2] >> 2) {
    case 0:  // D3D color
      for (size_t i = 0; i < 4; i++) {
        constexpr size_t indices[] = {3, 0, 1, 2};
        ctx.println("\t{}.u32[{}] = {}.u8[{}] | 0x3F800000;", ctx.v_temp(), i,
                    ctx.v(ctx.insn.operands[1]), indices[i]);
      }
      ctx.println("\t{} = {};", ctx.v(ctx.insn.operands[0]), ctx.v_temp());
      break;

    case 1:  // NORMSHORT2 - unpack 2 shorts to floats (3.0+X form)
      for (size_t i = 0; i < 2; i++) {
        ctx.println("\t{}.f32 = 3.0f;", ctx.temp());
        ctx.println("\t{}.s32 += {}.s16[{}];", ctx.temp(), ctx.v(ctx.insn.operands[1]), 1 - i);
        ctx.println("\t{}.f32[{}] = {}.f32;", ctx.v_temp(), 3 - i, ctx.temp());
      }
      ctx.println("\t{}.f32[1] = 0.0f;", ctx.v_temp());
      ctx.println("\t{}.f32[0] = 1.0f;", ctx.v_temp());
      ctx.println("\t{} = {};", ctx.v(ctx.insn.operands[0]), ctx.v_temp());
      break;

    case 2:  // NORMPACKED32 - unpack 2:10:10:10 to floats
    {
      // Format: w(2 bits):z(10 bits):y(10 bits):x(10 bits) in Guest element 3 (host s32[0])
      // x, y, z --> 3.0+X form (signed 10-bit), w --> 1.0+w form
      // Output: x --> Guest element 0 (host u32[3]), y --> Guest element 1 (host u32[2]),
      //         z --> Guest element 2 (host u32[1]), w --> Guest element 3 (host u32[0])
      auto vSrc = ctx.v(ctx.insn.operands[1]);
      auto vDst = ctx.v(ctx.insn.operands[0]);
      // x (bits 0-9) - sign extend from 10 bits --> Guest element 0 (host u32[3])
      ctx.println("\t{}.s32 = ({}.s32[0] << 22) >> 22;", ctx.temp(), vSrc);
      ctx.println("\t{}.s32[0] = {}.s32 == -512 ? 0x7FC00000 : ({}.s32 + 0x40400000);",
                  ctx.v_temp(), ctx.temp(), ctx.temp());
      ctx.println("\t{}.u32[3] = {}.u32[0];", vDst, ctx.v_temp());
      // y (bits 10-19) - sign extend from 10 bits --> Guest element 1 (host u32[2])
      ctx.println("\t{}.s32 = ({}.s32[0] << 12) >> 22;", ctx.temp(), vSrc);
      ctx.println("\t{}.s32[0] = {}.s32 + 0x40400000;", ctx.v_temp(), ctx.temp());
      ctx.println("\t{}.u32[2] = {}.u32[0];", vDst, ctx.v_temp());
      // z (bits 20-29) - sign extend from 10 bits --> Guest element 2 (host u32[1])
      ctx.println("\t{}.s32 = ({}.s32[0] << 2) >> 22;", ctx.temp(), vSrc);
      ctx.println("\t{}.s32[0] = {}.s32 + 0x40400000;", ctx.v_temp(), ctx.temp());
      ctx.println("\t{}.u32[1] = {}.u32[0];", vDst, ctx.v_temp());
      // w (bits 30-31) - 2 bits, convert to 1.0+w form --> Guest element 3 (host u32[0])
      ctx.println("\t{}.u32[0] = ({}.u32[0] >> 30) | 0x3F800000;", ctx.v_temp(), vSrc);
      ctx.println("\t{}.u32[0] = {}.u32[0];", vDst, ctx.v_temp());
      break;
    }

    case 3:  // FLOAT16_2 - unpack 2 float16 to floats
    {
      auto vSrc = ctx.v(ctx.insn.operands[1]);
      auto vDst = ctx.v(ctx.insn.operands[0]);
      // Unpack 2 float16s from u16[0,1] to elements 0,1 (stored at u32[3,2])
      // Element 0 (at u32[3]) from u16[1] (high), element 1 (at u32[2]) from u16[0] (low)
      for (size_t i = 0; i < 2; i++) {
        size_t srcIdx = 1 - i;  // Read from u16[1], u16[0]
        size_t dstIdx = 3 - i;  // Write to u32[3], u32[2]
        ctx.println("\t{}.u32 = {}.u16[{}];", ctx.temp(), vSrc, srcIdx);
        // Extract sign, exponent, mantissa
        ctx.println(
            "\t{}.u32[0] = (({}.u32 & 0x8000) << 16) | ((({}.u32 & 0x7C00) + 0x1C000) << 13) | "
            "(({}.u32 & 0x03FF) << 13);",
            ctx.v_temp(), ctx.temp(), ctx.temp(), ctx.temp());
        // Handle zero/denorm case
        ctx.println("\tif (({}.u32 & 0x7C00) == 0) {}.u32[0] = ({}.u32 & 0x8000) << 16;",
                    ctx.temp(), ctx.v_temp(), ctx.temp());
        ctx.println("\t{}.u32[{}] = {}.u32[0];", vDst, dstIdx, ctx.v_temp());
      }
      ctx.println("\t{}.f32[1] = 0.0f;", vDst);
      ctx.println("\t{}.f32[0] = 1.0f;", vDst);
      break;
    }

    case 4:  // NORMSHORT4 - unpack 4 shorts to floats (3.0+X form)
    {
      // Unpack 4 shorts from Guest elements 2-3 (host u16[0-3]) to 4 floats
      // Guest element order is reversed in host arrays
      for (size_t i = 0; i < 4; i++) {
        size_t srcIdx = 3 - i;  // Read from u16 indices 3, 2, 1, 0 (guest shorts 0, 1, 2, 3)
        size_t dstIdx = 3 - i;  // Write to f32 indices 3, 2, 1, 0 (Guest elements 0, 1, 2, 3)
        ctx.println("\t{}.f32 = 3.0f;", ctx.temp());
        ctx.println("\t{}.s32 += {}.s16[{}];", ctx.temp(), ctx.v(ctx.insn.operands[1]), srcIdx);
        ctx.println("\t{}.f32[{}] = {}.f32;", ctx.v(ctx.insn.operands[0]), dstIdx, ctx.temp());
      }
      break;
    }

    case 5:  // FLOAT16_4 - unpack 4 float16 to floats
    {
      auto vSrc = ctx.v(ctx.insn.operands[1]);
      auto vDst = ctx.v(ctx.insn.operands[0]);
      // Unpack 4 float16s from Guest elements 2-3 (host u16[0-3]) to elements 0-3
      // Guest element order is reversed in host arrays
      for (size_t i = 0; i < 4; i++) {
        size_t srcIdx = 3 - i;  // Read from u16 indices 3, 2, 1, 0 (guest shorts 0, 1, 2, 3)
        size_t dstIdx = 3 - i;  // Write to u32 indices 3, 2, 1, 0 (Guest elements 0, 1, 2, 3)
        ctx.println("\t{}.u32 = {}.u16[{}];", ctx.temp(), vSrc, srcIdx);
        // Extract sign, exponent, mantissa and convert to float32
        ctx.println(
            "\t{}.u32[0] = (({}.u32 & 0x8000) << 16) | ((({}.u32 & 0x7C00) + 0x1C000) << 13) | "
            "(({}.u32 & 0x03FF) << 13);",
            ctx.v_temp(), ctx.temp(), ctx.temp(), ctx.temp());
        // Handle zero/denorm case
        ctx.println("\tif (({}.u32 & 0x7C00) == 0) {}.u32[0] = ({}.u32 & 0x8000) << 16;",
                    ctx.temp(), ctx.v_temp(), ctx.temp());
        ctx.println("\t{}.u32[{}] = {}.u32[0];", vDst, dstIdx, ctx.v_temp());
      }
      break;
    }

    case 6:  // NORMPACKED64 - unpack 4:20:20:20 to floats
    {
      auto vSrc = ctx.v(ctx.insn.operands[1]);
      auto vDst = ctx.v(ctx.insn.operands[0]);
      // Format: w(4 bits):z(20 bits):y(20 bits):x(20 bits) in 64 bits
      // x, y, z --> floats, w --> float
      ctx.println("\t{}.u64[0] = {}.u64[1];", ctx.v_temp(), vSrc);
      // x (bits 0-19) - sign extend from 20 bits
      ctx.println("\t{}.s32 = (int32_t({}.u64[0] << 44) >> 44);", ctx.temp(), ctx.v_temp());
      ctx.println("\t{}.f32[0] = float({}.s32);", vDst, ctx.temp());
      // y (bits 20-39) - sign extend from 20 bits
      ctx.println("\t{}.s32 = (int32_t({}.u64[0] << 24) >> 44);", ctx.temp(), ctx.v_temp());
      ctx.println("\t{}.f32[1] = float({}.s32);", vDst, ctx.temp());
      // z (bits 40-59) - sign extend from 20 bits
      ctx.println("\t{}.s32 = (int32_t({}.u64[0] << 4) >> 44);", ctx.temp(), ctx.v_temp());
      ctx.println("\t{}.f32[2] = float({}.s32);", vDst, ctx.temp());
      // w (bits 60-63) - 4 bits
      ctx.println("\t{}.f32[3] = float({}.u64[0] >> 60);", vDst, ctx.v_temp());
      break;
    }

    default:
      ctx.println("\t__builtin_debugtrap();");
      break;
  }
  return true;
}

bool BuildVupkhsb(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s16, "
      "simde_mm_cvtepi8_epi16(simde_mm_unpackhi_epi64(simde_mm_load_si128((simde__m128i*){}.s8), "
      "simde_mm_load_si128((simde__m128i*){}.s8))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVupkhsh(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s32, "
      "simde_mm_cvtepi16_epi32(simde_mm_unpackhi_epi64(simde_mm_load_si128((simde__m128i*){}.s16), "
      "simde_mm_load_si128((simde__m128i*){}.s16))));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVupklsb(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s32, "
      "simde_mm_cvtepi8_epi16(simde_mm_load_si128((simde__m128i*){}.s16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]));
  return true;
}

bool BuildVupklsh(BuilderContext& ctx) {
  ctx.println(
      "\tsimde_mm_store_si128((simde__m128i*){}.s32, "
      "simde_mm_cvtepi16_epi32(simde_mm_load_si128((simde__m128i*){}.s16)));",
      ctx.v(ctx.insn.operands[0]), ctx.v(ctx.insn.operands[1]));
  return true;
}

}  // namespace rex::codegen
