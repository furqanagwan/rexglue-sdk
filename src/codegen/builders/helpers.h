/**
 * @file        rexcodegen/internal/helpers.h
 * @brief       Recompiler helper utilities
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include "builder_context.h"

#include <cstring>

#include <rex/codegen/function_scanner.h>
#include <rex/logging.h>

#include "../codegen_logging.h"

#include <dis-asm.h>
#include <ppc-inst.h>

namespace rex::codegen {

inline uint64_t compute_mask(uint32_t mstart, uint32_t mstop) {
  mstart &= 0x3F;
  mstop &= 0x3F;
  uint64_t value = (UINT64_MAX >> mstart) ^ ((mstop >= 63) ? 0 : UINT64_MAX >> (mstop + 1));
  return mstart <= mstop ? value : ~value;
}

inline const char* crBitName(uint32_t bi) {
  static constexpr const char* names[] = {"lt", "gt", "eq", "so"};
  return names[bi & 3];
}

inline bool isRecordForm(const ppc_insn& insn) {
  return std::strchr(insn.opcode->name, '.') != nullptr;
}

inline void emitRecordFormCompare(BuilderContext& ctx) {
  if (isRecordForm(ctx.insn)) {
    ctx.println("\t{}.compare<int32_t>({}.s32, 0, {});", ctx.cr(0), ctx.r(ctx.insn.operands[0]),
                ctx.xer());
  }
}

inline void emitCRBitOperation(BuilderContext& ctx, std::string_view op, bool invertA = false,
                               bool invertB = false, bool invertResult = false) {
  uint32_t crD = ctx.insn.operands[0];
  uint32_t crA = ctx.insn.operands[1];
  uint32_t crB = ctx.insn.operands[2];

  uint32_t crField_D = crD / 4;
  uint32_t crBit_D = crD % 4;
  uint32_t crField_A = crA / 4;
  uint32_t crBit_A = crA % 4;
  uint32_t crField_B = crB / 4;
  uint32_t crBit_B = crB % 4;

  std::string aExpr = fmt::format("{}.{}", ctx.cr(crField_A), crBitName(crBit_A));

  std::string bExpr = fmt::format("{}.{}", ctx.cr(crField_B), crBitName(crBit_B));

  if (invertA)
    aExpr = "!(" + aExpr + ")";
  if (invertB)
    bExpr = "!(" + bExpr + ")";

  std::string expr = fmt::format("{} {} {}", aExpr, op, bExpr);

  if (invertResult)
    expr = "!(" + expr + ")";

  ctx.println("\t{}.{} = {};", ctx.cr(crField_D), crBitName(crBit_D), expr);
}

inline void emitCompareRegister(BuilderContext& ctx, const char* type_name, const char* field) {
  ctx.println("\t{}.compare<{}>({}.{}, {}.{}, {});", ctx.cr(ctx.insn.operands[0]), type_name,
              ctx.r(ctx.insn.operands[1]), field, ctx.r(ctx.insn.operands[2]), field, ctx.xer());
}

inline void emitCompareImmediate(BuilderContext& ctx, const char* type_name, const char* field,
                                 bool sign_extend) {
  if (sign_extend) {
    ctx.println("\t{}.compare<{}>({}.{}, {}, {});", ctx.cr(ctx.insn.operands[0]), type_name,
                ctx.r(ctx.insn.operands[1]), field, static_cast<int32_t>(ctx.insn.operands[2]),
                ctx.xer());
  } else {
    ctx.println("\t{}.compare<{}>({}.{}, {}, {});", ctx.cr(ctx.insn.operands[0]), type_name,
                ctx.r(ctx.insn.operands[1]), field, ctx.insn.operands[2], ctx.xer());
  }
}

inline void emitLoadWithUpdate(BuilderContext& ctx, const char* load_macro) {
  ctx.println("\t{} = {} + {}.u32;", ctx.ea(), static_cast<int32_t>(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));

  ctx.println("\t{}.u64 = {}({});", ctx.r(ctx.insn.operands[0]), load_macro, ctx.ea());

  ctx.println("\t{}.u32 = {};", ctx.r(ctx.insn.operands[2]), ctx.ea());
}

inline void emitLoadXFormWithUpdate(BuilderContext& ctx, const char* load_macro) {
  ctx.println("\t{} = {}.u32 + {}.u32;", ctx.ea(), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  ctx.println("\t{}.u64 = {}({});", ctx.r(ctx.insn.operands[0]), load_macro, ctx.ea());
  ctx.println("\t{}.u32 = {};", ctx.r(ctx.insn.operands[1]), ctx.ea());
}

inline void emitStoreWithUpdate(BuilderContext& ctx, const char* store_macro, const char* field) {
  ctx.println("\t{} = {} + {}.u32;", ctx.ea(), static_cast<int32_t>(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));

  ctx.println("\t{}({}, {}.{});", store_macro, ctx.ea(), ctx.r(ctx.insn.operands[0]), field);

  ctx.println("\t{}.u32 = {};", ctx.r(ctx.insn.operands[2]), ctx.ea());
}

inline void emitStoreXFormWithUpdate(BuilderContext& ctx, const char* store_macro,
                                     const char* mmio_macro, const char* field) {
  ctx.println("\t{} = {}.u32 + {}.u32;", ctx.ea(), ctx.r(ctx.insn.operands[1]),
              ctx.r(ctx.insn.operands[2]));
  ctx.println("\t{}({}, {}.{});", ctx.mmio_check_x_form() ? mmio_macro : store_macro, ctx.ea(),
              ctx.r(ctx.insn.operands[0]), field);
  ctx.println("\t{}.u32 = {};", ctx.r(ctx.insn.operands[1]), ctx.ea());
}

inline const char* getStoreMacro(BuilderContext& ctx, const char* normal_macro,
                                 const char* mmio_macro) {
  return ctx.mmio_check_d_form() ? mmio_macro : normal_macro;
}

inline void emitAtomicLoadReserve(BuilderContext& ctx, const char* ptr_type, const char* bswap_func,
                                  const char* reserved_field) {
  ctx.print("\t{} = ", ctx.ea());
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.u32 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{}.u32;", ctx.r(ctx.insn.operands[2]));
  ctx.println("\t{} = {};", ctx.reserved_address(), ctx.ea());
  ctx.println("\t{}.{} = *({}*)REX_RAW_ADDR({});", ctx.reserved(), reserved_field, ptr_type,
              ctx.ea());
  ctx.println("\t{}.u64 = {}({}.{});", ctx.r(ctx.insn.operands[0]), bswap_func, ctx.reserved(),
              reserved_field);
}

inline void emitAtomicStoreConditional(BuilderContext& ctx, const char* ptr_type,
                                       const char* bswap_func, const char* field) {
  ctx.print("\t{} = ", ctx.ea());
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.u32 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{}.u32;", ctx.r(ctx.insn.operands[2]));
  ctx.println("\t{}.lt = 0;", ctx.cr(0));
  ctx.println("\t{}.gt = 0;", ctx.cr(0));

  ctx.println(
      "\t{}.eq = {} == {} && __sync_bool_compare_and_swap(reinterpret_cast<{}*>(REX_RAW_ADDR({})), "
      "{}.{}, {}({}.{}));",
      ctx.cr(0), ctx.reserved_address(), ctx.ea(), ptr_type, ctx.ea(), ctx.reserved(), field,
      bswap_func, ctx.r(ctx.insn.operands[0]), field);
  ctx.println("\t{} = ~uint64_t(0);", ctx.reserved_address());
  ctx.println("\t{}.so = {}.so;", ctx.cr(0), ctx.xer());
}

inline void emitSignExtendLoadDForm(BuilderContext& ctx, const char* cast_type,
                                    const char* load_macro) {
  ctx.print("\t{}.s64 = {}({}(", ctx.r(ctx.insn.operands[0]), cast_type, load_macro);
  if (ctx.insn.operands[2] != 0)
    ctx.print("{}.u32 + ", ctx.r(ctx.insn.operands[2]));
  ctx.println("{}));", static_cast<int32_t>(ctx.insn.operands[1]));
}

inline void emitSignExtendLoadXForm(BuilderContext& ctx, const char* cast_type,
                                    const char* load_macro) {
  ctx.print("\t{}.s64 = {}({}(", ctx.r(ctx.insn.operands[0]), cast_type, load_macro);
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.u32 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{}.u32));", ctx.r(ctx.insn.operands[2]));
}

inline bool isMMIOUpperBits(uint32_t imm) {
  return (imm >= 0x7FC8 && imm <= 0x7FCF) || imm == 0x7FEA;
}

inline void emitBranchWithBoundsCheck(BuilderContext& ctx, uint32_t target,
                                      std::string_view condition, std::string_view instr_name) {
  if (target < ctx.fn.base() || target >= ctx.fn.end()) {
    REXCODEGEN_WARN("{} at {:X} branches outside function to {:X}", instr_name, ctx.base, target);
    ctx.println("\tif ({}) {{ /* branch to 0x{:X} outside function */ return; }}", condition,
                target);
  } else {
    ctx.println("\tif ({}) goto loc_{:X};", condition, target);
  }
}

inline void emitVectorEA(BuilderContext& ctx, const char* align_mask = nullptr) {
  if (align_mask)
    ctx.print("\t{} = (", ctx.ea());
  else
    ctx.print("\t{} = ", ctx.ea());
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.u32 + ", ctx.r(ctx.insn.operands[1]));
  if (align_mask)
    ctx.println("{}.u32) & ~{};", ctx.r(ctx.insn.operands[2]), align_mask);
  else
    ctx.println("{}.u32;", ctx.r(ctx.insn.operands[2]));
}

inline void emitVectorTempEA(BuilderContext& ctx) {
  ctx.print("\t{}.u32 = ", ctx.temp());
  if (ctx.insn.operands[1] != 0)
    ctx.print("{}.u32 + ", ctx.r(ctx.insn.operands[1]));
  ctx.println("{}.u32;", ctx.r(ctx.insn.operands[2]));
}

inline void emitTrap(BuilderContext& ctx, uint32_t to, const std::string& aSigned,
                     const std::string& aUnsigned, const std::string& bSigned,
                     const std::string& bUnsigned) {
  if (to == 0)
    return;
  if (to == 0x1F) {
    ctx.println("\tppc_trap(ctx, base, 0);");
    return;
  }

  std::string cond;
  auto add = [&](std::string_view c) {
    if (!cond.empty())
      cond += " || ";
    cond += c;
  };
  if (to & 0x10)
    add(fmt::format("{} < {}", aSigned, bSigned));
  if (to & 0x08)
    add(fmt::format("{} > {}", aSigned, bSigned));
  if (to & 0x04)
    add(fmt::format("{} == {}", aSigned, bSigned));
  if (to & 0x02)
    add(fmt::format("{} < {}", aUnsigned, bUnsigned));
  if (to & 0x01)
    add(fmt::format("{} > {}", aUnsigned, bUnsigned));

  ctx.println("\tif ({}) ppc_trap(ctx, base, 0);", cond);
}

}
