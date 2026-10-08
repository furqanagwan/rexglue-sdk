/**
 * @file        rexcodegen/builders/floating_point.cpp
 * @brief       PPC floating point instruction code generation
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

namespace {

/**
 * Emit frD = rex::ppc::fp::<fn>(operands...) for an arithmetic instruction.
 *
 * The helpers in rex/ppc/fp.h apply PowerPC's NaN and denormal rules. A record
 * form (fadd. ...) also sets CR1 from the exceptions the operation raised.
 * `causes` classifies invalid-operation subcauses not exposed by host fenv;
 * `quiet` reports nothing raised for a single-precision denormal operand.
 */
void emitFpArith(BuilderContext& ctx, std::string_view fn, int count,
                 std::string_view causes = "snan_causes", std::string_view quiet = "") {
  std::string args, params, names;
  static constexpr const char* kNames[] = {"a", "b", "c"};
  for (int i = 0; i < count; ++i) {
    const char* sep = i ? ", " : "";
    args += fmt::format("{}{}.f64", sep, ctx.f(ctx.insn.operands[i + 1]));
    names += fmt::format("{}{}", sep, kNames[i]);
  }
  const std::string quiet_expr =
      quiet.empty() ? "false" : fmt::format("rex::ppc::fp::{}({})", quiet, args);
  const std::string causes_expr = fmt::format("rex::ppc::fp::{}({})", causes, args);
  ctx.println(
      "\t{}.f64 = rex::ppc::fp::tracked(ctx.fpscr, {}, [](double a, double b, double c) {{ "
      "(void)b; (void)c; return rex::ppc::fp::{}({}); }}, {}, {}, {});",
      ctx.f(ctx.insn.operands[0]),
      isRecordForm(ctx.insn) ? fmt::format("&{}", ctx.cr(1)) : "nullptr", fn, names, causes_expr,
      quiet_expr, args);
}

/// fctiw/fctiwz/fctid/fctidz, with CR1 for the record forms.
void emitFpConvert(BuilderContext& ctx, bool to_int64, bool truncate) {
  const auto d = ctx.f(ctx.insn.operands[0]);
  const auto b = ctx.f(ctx.insn.operands[1]);
  ctx.println("\t{}.s64 = rex::ppc::fp::tracked_convert(ctx.fpscr, {}, {}.f64, {}, {});", d,
              isRecordForm(ctx.insn) ? fmt::format("&{}", ctx.cr(1)) : "nullptr", b, truncate,
              to_int64);
}

}  // namespace

//=============================================================================
// Sign Manipulation
//=============================================================================

bool build_fabs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\t{}.u64 = {}.u64 & ~0x8000000000000000;", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]));
  return true;
}

bool build_fnabs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\t{}.u64 = {}.u64 | 0x8000000000000000;", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]));
  return true;
}

bool build_fneg(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\t{}.u64 = {}.u64 ^ 0x8000000000000000;", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]));
  return true;
}

//=============================================================================
// Move and Conversion
//=============================================================================

bool build_fmr(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\t{}.f64 = {}.f64;", ctx.f(ctx.insn.operands[0]), ctx.f(ctx.insn.operands[1]));
  return true;
}

bool build_fcfid(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\t{}.f64 = double({}.s64);", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]));
  return true;
}

bool build_fctid(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpConvert(ctx, true, false);
  return true;
}

bool build_fctidz(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpConvert(ctx, true, true);
  return true;
}

bool build_fctiw(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpConvert(ctx, false, false);
  return true;
}

bool build_fctiwz(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpConvert(ctx, false, true);
  return true;
}

bool build_frsp(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "to_single", 1);
  return true;
}

//=============================================================================
// Comparison
//=============================================================================

bool build_fcmpu(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\trex::ppc::fp::compare(ctx.fpscr, {}, {}.f64, {}.f64, {});",
              ctx.cr(ctx.insn.operands[0]), ctx.f(ctx.insn.operands[1]),
              ctx.f(ctx.insn.operands[2]), ctx.insn.opcode->name[4] == 'o');
  return true;
}

bool build_fcmpo(BuilderContext& ctx) {
  return build_fcmpu(ctx);
}

//=============================================================================
// Addition
//=============================================================================

bool build_fadd(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "add", 2, "add_invalid_causes");
  return true;
}

bool build_fadds(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "adds", 2, "add_invalid_causes", "single_denormal");
  return true;
}

//=============================================================================
// Subtraction
//=============================================================================

bool build_fsub(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "sub", 2, "sub_invalid_causes");
  return true;
}

bool build_fsubs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "subs", 2, "sub_invalid_causes", "single_denormal");
  return true;
}

//=============================================================================
// Multiplication
//=============================================================================

bool build_fmul(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "mul", 2, "mul_invalid_causes");
  return true;
}

bool build_fmuls(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "muls", 2, "mul_invalid_causes", "single_denormal");
  return true;
}

//=============================================================================
// Division
//=============================================================================

bool build_fdiv(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "div", 2, "div_invalid_causes");
  return true;
}

bool build_fdivs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "divs", 2, "div_invalid_causes");
  return true;
}

//=============================================================================
// Fused Multiply-Add
//=============================================================================

bool build_fmadd(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "madd", 3, "madd_invalid_causes");
  return true;
}

bool build_fmadds(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "madds", 3, "madd_invalid_causes", "single_denormal");
  return true;
}

bool build_fmsub(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "msub", 3, "madd_invalid_causes");
  return true;
}

bool build_fmsubs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "msubs", 3, "madd_invalid_causes", "single_denormal");
  return true;
}

bool build_fnmadd(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "nmadd", 3, "madd_invalid_causes");
  return true;
}

bool build_fnmadds(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "nmadds", 3, "madd_invalid_causes", "single_denormal");
  return true;
}

bool build_fnmsub(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "nmsub", 3, "madd_invalid_causes");
  return true;
}

bool build_fnmsubs(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "nmsubs", 3, "madd_invalid_causes", "single_denormal");
  return true;
}

//=============================================================================
// Reciprocal and Square Root
//=============================================================================

bool build_fres(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  if (isRecordForm(ctx.insn)) {
    ctx.println("\trex::ppc::fp::set_cr1_estimate({}, {}.f64, false);", ctx.cr(1),
                ctx.f(ctx.insn.operands[1]));
  }
  ctx.println("\t{}.f64 = double(float(1.0 / {}.f64));", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]));
  return true;
}

bool build_frsqrte(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  if (isRecordForm(ctx.insn)) {
    ctx.println("\trex::ppc::fp::set_cr1_estimate({}, {}.f64, true);", ctx.cr(1),
                ctx.f(ctx.insn.operands[1]));
  }
  ctx.println("\t{}.f64 = rex::ppc::fp::rsqrte({}.f64);", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]));
  return true;
}

bool build_fsqrt(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "sqrt", 1, "sqrt_invalid_causes");
  return true;
}

bool build_fsqrts(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  emitFpArith(ctx, "sqrts", 1, "sqrt_invalid_causes");
  return true;
}

//=============================================================================
// Selection
//=============================================================================

bool build_fsel(BuilderContext& ctx) {
  ctx.emit_set_flush_mode(false);
  ctx.println("\t{}.f64 = {}.f64 >= 0.0 ? {}.f64 : {}.f64;", ctx.f(ctx.insn.operands[0]),
              ctx.f(ctx.insn.operands[1]), ctx.f(ctx.insn.operands[2]),
              ctx.f(ctx.insn.operands[3]));
  return true;
}

}  // namespace rex::codegen
