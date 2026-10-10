/**
 * @file        rex/codegen/builder_context.h
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <fmt/core.h>

#include <rex/codegen/config.h>
#include <rex/codegen/function_graph.h>

struct ppc_insn;

namespace rex::codegen {

class FunctionNode;

struct RecompilerLocalVariables {
  bool ctr{};
  bool xer{};
  bool reserved{};
  bool reserved_address{};
  bool cr[8]{};
  bool r[32]{};
  bool f[32]{};
  bool v[128]{};
  bool env{};
  bool temp{};
  bool v_temp{};
  bool ea{};

  uint32_t mmio_base_regs{0};

  void set_mmio_base(size_t reg) {
    if (reg < 32)
      mmio_base_regs |= (1u << reg);
  }
  void clear_mmio_base(size_t reg) {
    if (reg < 32)
      mmio_base_regs &= ~(1u << reg);
  }
  bool is_mmio_base(size_t reg) const { return reg < 32 && (mmio_base_regs & (1u << reg)); }
};

enum class CSRState { Unknown, FPU, VMX };

struct BuilderContext {
  std::string& out;

  const EmitContext& emitCtx;

  const FunctionNode& fn;

  const ppc_insn& insn;

  uint32_t base;

  const uint32_t* data;

  RecompilerLocalVariables& locals;

  CSRState& csrState;

  const JumpTable* activeJumpTable = nullptr;

  const RecompilerConfig& config() const;

  const FunctionGraph& graph() const;

  bool localizeNonVolatiles() const;

  std::string r(size_t index);

  std::string f(size_t index);

  std::string v(size_t index);

  std::string cr(size_t index);

  const char* ctr();

  const char* xer();

  const char* reserved();
  const char* reserved_address();

  const char* temp();

  const char* v_temp();

  const char* env();

  const char* ea();

  template <class... Args>
  void print(fmt::format_string<Args...> fmt, Args&&... args) {
    fmt::vformat_to(std::back_inserter(out), fmt.get(), fmt::make_format_args(args...));
  }

  template <class... Args>
  void println(fmt::format_string<Args...> fmt, Args&&... args) {
    fmt::vformat_to(std::back_inserter(out), fmt.get(), fmt::make_format_args(args...));
    out += '\n';
  }

  bool mmio_check_d_form();

  bool mmio_check_x_form();

  const CallTarget* findCallTarget(uint32_t site) const;

  void emit_function_call(uint32_t address);

  void emit_conditional_branch(bool not_, std::string_view cond);

  void emit_set_flush_mode(bool enable);

  void emit_mid_asm_hook();

  bool has_mid_asm_hook() const;

  void reset_switch_table() { activeJumpTable = nullptr; }

  void emit_vec_fp_binary(const char* simd_op);

  void emit_vec_fp_unary_expr(std::string_view simd_expr);

  void emit_vec_int_binary(const char* simd_op, const char* element_type);

  void emit_vec_int_binary_swapped(const char* simd_op, const char* element_type);

  void emit_vec_var_shift(const char* shift_dir, const char* element_type, uint32_t mask_value);

  void emit_load_d_form(const char* load_macro, const char* dest_type, bool check_mmio = true);

  void emit_load_x_form(const char* load_macro, const char* dest_type, bool check_mmio = true);

  void emit_store_d_form(const char* store_macro, const char* src_type, bool check_mmio = true);

  void emit_store_x_form(const char* store_macro, const char* src_type, bool check_mmio = true);
};
}