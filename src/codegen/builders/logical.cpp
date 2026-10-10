/**
 * @file        rexcodegen/builders/logical.cpp
 * @brief       PPC logical instruction code generation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "helpers.h"

namespace rex::codegen {

//=============================================================================
// AND Operations
//=============================================================================

bool BuildAnd(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 & {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildAndc(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 & ~{}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildAndi(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 & {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2]);
  // ANDI. always sets CR0
  ctx.println("\t{}.compare<int32_t>({}.s32, 0, {});", ctx.cr(0), ctx.r(ctx.insn.operands[0]),
              ctx.xer());
  return true;
}

bool BuildAndis(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 & {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2] << 16);
  // ANDIS. always sets CR0
  ctx.println("\t{}.compare<int32_t>({}.s32, 0, {});", ctx.cr(0), ctx.r(ctx.insn.operands[0]),
              ctx.xer());
  return true;
}

//=============================================================================
// OR Operations
//=============================================================================

bool BuildNand(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = ~({}.u64 & {}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildNor(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = ~({}.u64 | {}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildNot(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = ~{}.u64;", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildOr(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 | {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);

  // Propagates MMIO base flag if either source register is marked MMIO
  // covers mr rD,rS which assembles as or rD,rS,rS
  if (ctx.locals.is_mmio_base(ctx.insn.operands[1]) ||
      ctx.locals.is_mmio_base(ctx.insn.operands[2]))
    ctx.locals.set_mmio_base(ctx.insn.operands[0]);
  else
    ctx.locals.clear_mmio_base(ctx.insn.operands[0]);

  return true;
}

bool BuildOrc(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 | ~{}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildOri(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 | {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2]);

  // ori only sets low bits - propagate MMIO base from source
  if (ctx.locals.is_mmio_base(ctx.insn.operands[1]))
    ctx.locals.set_mmio_base(ctx.insn.operands[0]);
  else
    ctx.locals.clear_mmio_base(ctx.insn.operands[0]);

  return true;
}

bool BuildOris(BuilderContext& ctx) {
  uint32_t imm = static_cast<uint32_t>(ctx.insn.operands[2]);
  size_t dest_reg = ctx.insn.operands[0];

  ctx.println("\t{}.u64 = {}.u64 | {};", ctx.r(dest_reg), ctx.r(ctx.insn.operands[1]), imm << 16);

  if (isMMIOUpperBits(imm)) {
    ctx.locals.set_mmio_base(dest_reg);
  }
  // NOTE(tomc): don't clear flag here - oris may preserve MMIO base from source

  return true;
}

//=============================================================================
// XOR Operations
//=============================================================================

bool BuildXor(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 ^ {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildXori(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 ^ {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2]);
  return true;
}

bool BuildXoris(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 ^ {};", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2] << 16);
  return true;
}

bool BuildEqv(BuilderContext& ctx) {
  // eqv: rA = ~(rS ^ rB) (XNOR - equivalent)
  ctx.println("\t{}.u64 = ~({}.u64 ^ {}.u64);", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Count Leading Zeros
//=============================================================================

bool BuildCntlzd(BuilderContext& ctx) {
  ctx.println("\t{0}.u64 = {1}.u64 == 0 ? 64 : __builtin_clzll({1}.u64);",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildCntlzw(BuilderContext& ctx) {
  ctx.println("\t{0}.u64 = {1}.u32 == 0 ? 32 : __builtin_clz({1}.u32);",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Sign Extension
//=============================================================================

bool BuildExtsb(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = {}.s8;", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildExtsh(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = {}.s16;", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildExtsw(BuilderContext& ctx) {
  ctx.println("\t{}.s64 = {}.s32;", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Clear Left Word Immediate
//=============================================================================

bool BuildClrlwi(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u32 & 0x{:X};", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), (1ull << (32 - ctx.insn.operands[2])) - 1);
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Rotate Left Double Word
//=============================================================================

bool BuildRldicl(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {}) & 0x{:X};",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2],
              compute_mask(ctx.insn.operands[3], 63));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRldicr(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {}) & 0x{:X};",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2],
              compute_mask(0, ctx.insn.operands[3]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRldic(BuilderContext& ctx) {
  uint32_t sh = ctx.insn.operands[2];
  uint64_t mask = compute_mask(ctx.insn.operands[3], 63 - sh);
  if (sh)
    ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {}) & 0x{:X};",
                ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), sh, mask);
  else
    ctx.println("\t{}.u64 = {}.u64 & 0x{:X};", ctx.r(ctx.insn.operands[0]),
                ctx.r(ctx.insn.operands[1]), mask);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRldcl(BuilderContext& ctx) {
  uint64_t mask = compute_mask(ctx.insn.operands[3], 63);
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {}.u8 & 0x3F) & 0x{:X};",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]),
              mask);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRotld(BuilderContext& ctx) {
  // The disassembler uses rotld for rldcl with a zero mask.
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {}.u8 & 0x3F);",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRldcr(BuilderContext& ctx) {
  uint64_t mask = compute_mask(0, ctx.insn.operands[3]);
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {}.u8 & 0x3F) & 0x{:X};",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[2]),
              mask);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRldimi(BuilderContext& ctx) {
  const uint64_t mask = compute_mask(ctx.insn.operands[3], ~ctx.insn.operands[2]);
  ctx.println("\t{}.u64 = (__builtin_rotateleft64({}.u64, {}) & 0x{:X}) | ({}.u64 & 0x{:X});",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2], mask,
              ctx.r(ctx.insn.operands[0]), ~mask);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRotldi(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u64, {});", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2]);
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Rotate Left Word
//=============================================================================

bool BuildRlwimi(BuilderContext& ctx) {
  const uint64_t mask = compute_mask(ctx.insn.operands[3] + 32, ctx.insn.operands[4] + 32);
  ctx.println(
      "\t{}.u64 = (__builtin_rotateleft64({}.u32 | ({}.u64 << 32), {}) & 0x{:X}) | ({}.u64 & "
      "0x{:X});",
      ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
      ctx.insn.operands[2], mask, ctx.r(ctx.insn.operands[0]), ~mask);
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRlwinm(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u32 | ({}.u64 << 32), {}) & 0x{:X};",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
              ctx.insn.operands[2],
              compute_mask(ctx.insn.operands[3] + 32, ctx.insn.operands[4] + 32));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRlwnm(BuilderContext& ctx) {
  // Like rlwinm but shift amount comes from register, not immediate
  ctx.println("\t{}.u64 = __builtin_rotateleft64({}.u32 | ({}.u64 << 32), {}.u8 & 0x1F) & 0x{:X};",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]),  // Register, not immediate
              compute_mask(ctx.insn.operands[3] + 32, ctx.insn.operands[4] + 32));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRotlw(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = __builtin_rotateleft32({}.u32, {}.u8 & 0x1F);",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildRotlwi(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = __builtin_rotateleft32({}.u32, {});", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2]);
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Shift Left
//=============================================================================

bool BuildSld(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u8 & 0x40 ? 0 : ({}.u64 << ({}.u8 & 0x7F));",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSlw(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u8 & 0x20 ? 0 : ({}.u32 << ({}.u8 & 0x3F));",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Shift Right Algebraic (signed)
//=============================================================================

bool BuildSrad(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u64 & 0x7F;", ctx.temp(), ctx.r(ctx.insn.operands[2]));
  ctx.println("\tif ({}.u64 > 0x3F) {}.u64 = 0x3F;", ctx.temp(), ctx.temp());
  ctx.println("\t{}.ca = ({}.s64 < 0) & ((({}.s64 >> {}.u64) << {}.u64) != {}.s64);", ctx.xer(),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]), ctx.temp(), ctx.temp(),
              ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.s64 = {}.s64 >> {}.u64;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSradi(BuilderContext& ctx) {
  if (ctx.insn.operands[2] != 0) {
    ctx.println("\t{}.ca = ({}.s64 < 0) & (({}.u64 & 0x{:X}) != 0);", ctx.xer(),
                ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
                compute_mask(64 - ctx.insn.operands[2], 63));
    ctx.println("\t{}.s64 = {}.s64 >> {};", ctx.r(ctx.insn.operands[0]),
                ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2]);
  } else {
    ctx.println("\t{}.ca = 0;", ctx.xer());
    ctx.println("\t{}.s64 = {}.s64;", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  }
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSraw(BuilderContext& ctx) {
  ctx.println("\t{}.u32 = {}.u32 & 0x3F;", ctx.temp(), ctx.r(ctx.insn.operands[2]));
  ctx.println("\tif ({}.u32 > 0x1F) {}.u32 = 0x1F;", ctx.temp(), ctx.temp());
  ctx.println("\t{}.ca = ({}.s32 < 0) & ((({}.s32 >> {}.u32) << {}.u32) != {}.s32);", ctx.xer(),
              ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]), ctx.temp(), ctx.temp(),
              ctx.r(ctx.insn.operands[1]));
  ctx.println("\t{}.s64 = {}.s32 >> {}.u32;", ctx.r(ctx.insn.operands[0]),
              ctx.r(ctx.insn.operands[1]), ctx.temp());
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSrawi(BuilderContext& ctx) {
  if (ctx.insn.operands[2] != 0) {
    ctx.println("\t{}.ca = ({}.s32 < 0) & (({}.u32 & 0x{:X}) != 0);", ctx.xer(),
                ctx.r(ctx.insn.operands[1]), ctx.r(ctx.insn.operands[1]),
                compute_mask(64 - ctx.insn.operands[2], 63));
    ctx.println("\t{}.s64 = {}.s32 >> {};", ctx.r(ctx.insn.operands[0]),
                ctx.r(ctx.insn.operands[1]), ctx.insn.operands[2]);
  } else {
    ctx.println("\t{}.ca = 0;", ctx.xer());
    ctx.println("\t{}.s64 = {}.s32;", ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[1]));
  }
  emitRecordFormCompare(ctx);
  return true;
}

//=============================================================================
// Shift Right (unsigned)
//=============================================================================

bool BuildSrd(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u8 & 0x40 ? 0 : ({}.u64 >> ({}.u8 & 0x7F));",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildSrw(BuilderContext& ctx) {
  ctx.println("\t{}.u64 = {}.u8 & 0x20 ? 0 : ({}.u32 >> ({}.u8 & 0x3F));",
              ctx.r(ctx.insn.operands[0]), ctx.r(ctx.insn.operands[2]), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  emitRecordFormCompare(ctx);
  return true;
}

bool BuildCrand(BuilderContext& ctx) {
  // crand: CR[crD] = CR[crA] & CR[crB]
  emitCRBitOperation(ctx, "&");
  return true;
}

bool BuildCrandc(BuilderContext& ctx) {
  // crandc: CR[crD] = CR[crA] & ~CR[crB]
  emitCRBitOperation(ctx, "&", false, true, false);
  return true;
}

bool BuildCreqv(BuilderContext& ctx) {
  // creqv: CR[crD] = ~(CR[crA] ^ CR[crB])  (XNOR)
  emitCRBitOperation(ctx, "^", false, false, true);
  return true;
}

bool BuildCrnand(BuilderContext& ctx) {
  // crnand: CR[crD] = ~(CR[crA] & CR[crB])
  emitCRBitOperation(ctx, "&", false, false, true);
  return true;
}

bool BuildCrnor(BuilderContext& ctx) {
  // crnor: CR[crD] = ~(CR[crA] | CR[crB])
  emitCRBitOperation(ctx, "|", false, false, true);
  return true;
}

bool BuildCror(BuilderContext& ctx) {
  // cror: CR[crD] = CR[crA] | CR[crB]
  emitCRBitOperation(ctx, "|");
  return true;
}

bool BuildCrorc(BuilderContext& ctx) {
  // crorc: CR[crD] = CR[crA] | ~CR[crB]
  emitCRBitOperation(ctx, "|", false, true, false);
  return true;
}

bool BuildCrxor(BuilderContext& ctx) {
  // crxor: CR[crD] = CR[crA] ^ CR[crB]
  emitCRBitOperation(ctx, "^");
  return true;
}

}  // namespace rex::codegen
