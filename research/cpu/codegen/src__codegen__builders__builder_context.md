# Builder context: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/builder_context.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L42)

```text
/// Tracks which GPRs contain MMIO base addresses (bit N = rN is MMIO base)
```

## Source note 2, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L43)

```text
/// Set when lis loads a value with upper 16 bits >= 0x7F00 (address >= 0x7F000000)
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L44)

```text
/// or when oris sets upper bits >= 0xC800 (address >= 0xC8000000)
```

## Source note 4, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L58)

```text
/**
 * @brief CSR (Control/Status Register) flush mode state.
 *
 * Tracks the current MXCSR configuration for floating-point operations:
 * - **Unknown**: Initial state or after function call. Next FP/VMX instruction
 *   will emit a conditional mode check.
 * - **FPU**: Denormals preserved (flush-to-zero disabled). Used by scalar
 *   floating-point instructions (fadd, fmul, etc.)
 * - **VMX**: Denormals flushed to zero. Used by vector floating-point
 *   instructions (vaddfp, vmaddfp, etc.)
 */
```

## Source note 5, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L71)

```text
/**
 * @brief Context passed to instruction builders during code generation.
 */
```

## Source note 6, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L75)

```text
/// Raw output buffer for code generation
```

## Source note 7, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L78)

```text
/// Emission context (binary, config, graph, resolver)
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L81)

```text
/// The function currently being recompiled (FunctionNode from graph)
```

## Source note 9, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L84)

```text
/// The decoded instruction being processed (opcode, operands, disassembly)
```

## Source note 10, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L87)

```text
/// Address of the current instruction in guest memory
```

## Source note 11, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L90)

```text
/// Pointer to raw instruction data in the image
```

## Source note 12, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L93)

```text
/// Tracks which registers need local variable declarations
```

## Source note 13, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L96)

```text
/// Current CSR state for flush mode (FPU vs VMX)
```

## Source note 14, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L99)

```text
/// Pointer to active jump table for bctr dispatch, or nullptr
```

## Source note 15, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L102)

```text
/// Get the recompiler configuration
```

## Source note 16, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L105)

```text
/// Get the function graph (single source of truth for function info)
```

## Source note 17, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L109)

```text
// Register Accessors
```

## Source note 18, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L112)

```text
/**
   * @brief Whether non-volatiles may be localized in the current function.
   * False when the function shares registers with an intra-function bl partner.
   */
```

## Source note 19, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L118)

```text
/**
   * @brief Get expression for general-purpose register access.
   * @param index Register index (0-31)
   * @return "rN" for local variables, "ctx.rN" for context access
   */
```

## Source note 20, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L125)

```text
/**
   * @brief Get expression for floating-point register access.
   * @param index Register index (0-31)
   * @return "fN" for local variables, "ctx.fN" for context access
   */
```

## Source note 21, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L132)

```text
/**
   * @brief Get expression for vector register access.
   * @param index Register index (0-127, Xbox 360 extended VMX128)
   * @return "vN" for local variables, "ctx.vN" for context access
   */
```

## Source note 22, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L139)

```text
/**
   * @brief Get expression for condition register field access.
   * @param index CR field index (0-7)
   * @return "crN" for local variables, "ctx.crN" for context access
   */
```

## Source note 23, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L146)

```text
/// Get expression for count register ("ctr" or "ctx.ctr")
```

## Source note 24, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L149)

```text
/// Get expression for XER register ("xer" or "ctx.xer")
```

## Source note 25, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L152)

```text
/// Get expression for reservation register (used by lwarx/stwcx)
```

## Source note 26, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L156)

```text
/// Get expression for scalar temporary variable (always "temp")
```

## Source note 27, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L159)

```text
/// Get expression for vector temporary variable (always "vTemp")
```

## Source note 28, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L162)

```text
/// Get expression for setjmp environment storage (always "env")
```

## Source note 29, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L165)

```text
/// Get expression for effective address temporary (always "ea")
```

## Source note 30, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L169)

```text
// Output Helpers
```

## Source note 31, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L172)

```text
/**
   * @brief Print formatted text to the output buffer (no newline).
   * @tparam Args Format argument types (deduced)
   * @param fmt Format string with {} placeholders
   * @param args Values to substitute into placeholders
   */
```

## Source note 32, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L183)

```text
/**
   * @brief Print formatted text to output buffer with newline.
   * @tparam Args Format argument types (deduced)
   * @param fmt Format string with {} placeholders
   * @param args Values to substitute into placeholders
   */
```

## Source note 33, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L196)

```text
// Code Generation Helpers
```

## Source note 34, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L199)

```text
/**
   * @brief Check if current D-form load/store targets MMIO address.
   *
   * Checks: next instruction is eieio, or operands[2] (base register) is MMIO base.
   *
   * @return true if this is an MMIO access
   */
```

## Source note 35, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L208)

```text
/**
   * @brief Check if current X-form load/store targets MMIO address.
   *
   * Checks: next instruction is eieio, or operands[1]/operands[2] is MMIO base.
   *
   * @return true if this is an MMIO access
   */
```

## Source note 36, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L217)

```text
/**
   * @brief Find pre-resolved call target for an instruction site.
   * @param site Address of the call/branch instruction
   * @return Pointer to CallTarget if found, nullptr otherwise
   *
   * Searches the FunctionNode's calls and tailCalls for a matching site.
   */
```

## Source note 37, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L226)

```text
/**
   * @brief Emit C++ code for a function call.
   * @param address Target function address
   *
   * Uses pre-resolved CallTarget from FunctionNode when available.
   * Falls back to symbol lookup for backward compatibility.
   * Handles special cases like setjmp/longjmp and __restgprlr_N functions.
   */
```

## Source note 38, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L236)

```text
/**
   * @brief Emit C++ code for a conditional branch.
   * @param not_ If true, invert the condition
   * @param cond Condition field name ("eq", "lt", "gt")
   *
   * Emits either `goto loc_X` for intra-function branches or a function
   * call for inter-function branches.
   */
```

## Source note 39, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L246)

```text
/**
   * @brief Emit CSR flush mode change if needed.
   * @param enable true for VMX mode (flush-to-zero), false for FPU mode
   */
```

## Source note 40, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L252)

```text
/// Emit mid-asm hook if configured for current address
```

## Source note 41, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L255)

```text
/// Check if mid-asm hook exists for current address
```

## Source note 42, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L258)

```text
/// Clear active jump table pointer (used after processing a switch)
```

## Source note 43, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L262)

```text
// Vector (SIMD) Code Generation Helpers
```

## Source note 44, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L265)

```text
/**
   * @brief Emit binary float vector operation: vD = op(vA, vB)
   * @param simd_op The SIMDE function name (e.g., "add_ps", "sub_ps", "mul_ps")
   *
   * Emits: simde_mm_store_ps(vD.f32, simde_mm_OP(load(vA.f32), load(vB.f32)));
   * Uses operands[0]=vD, operands[1]=vA, operands[2]=vB from current instruction.
   */
```

## Source note 45, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L274)

```text
/**
   * @brief Emit unary float vector operation: vD = op(vA)
   * @param simd_expr SIMDE expression for the operation (will be wrapped in store)
   *
   * Use when the operation is more complex than a single function call.
   * Emits: simde_mm_store_ps(vD.f32, EXPR);
   * Uses operands[0]=vD, operands[1]=vA from current instruction.
   * Example: emit_vec_fp_unary_expr("simde_mm_sqrt_ps(simde_mm_load_ps({vA}.f32))")
   */
```

## Source note 46, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L285)

```text
/**
   * @brief Emit binary integer vector operation: vD = op(vA, vB)
   * @param simd_op The SIMDE function name (e.g., "add_epi16", "and_si128")
   * @param element_type The vector element type suffix (e.g., "u8", "s16", "u32")
   *
   * Emits: simde_mm_store_si128((simde__m128i*)vD.TYPE, simde_mm_OP(load(vA), load(vB)));
   * Uses operands[0]=vD, operands[1]=vA, operands[2]=vB from current instruction.
   */
```

## Source note 47, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L295)

```text
/**
   * @brief Emit binary integer vector operation with swapped operands: vD = op(vB, vA)
   * @param simd_op The SIMDE function name
   * @param element_type The vector element type suffix
   *
   * Same as emit_vec_int_binary but swaps vA and vB order (useful for andnot, etc.)
   */
```

## Source note 48, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L304)

```text
/**
   * @brief Emit variable shift: vD = rex::ppc::simde_mm_{shift_dir}_{element_type}(vA, vB & mask)
   * @param shift_dir The shift direction ("sllv", "srlv", or "srav")
   * @param element_type The SIMDE element type suffix ("epi16")
   * @param mask_value Shift amount mask (e.g., 0xF for 16-bit)
   *
   * Uses the custom rex:: variable shift helpers (simde_mm_{sllv,srlv,srav}_epi16).
   * Uses operands[0]=vD, operands[1]=vA, operands[2]=vB from current instruction.
   */
```

## Source note 49, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L316)

```text
// Memory (Load/Store) Code Generation Helpers
```

## Source note 50, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L319)

```text
/**
   * @brief Emit load with D-form addressing: rD = LOAD(rA + offset)
   * @param load_macro The load macro name (e.g., "REX_LOAD_U8", "REX_LOAD_U32")
   * @param dest_type The destination type suffix (e.g., "u64", "s64")
   * @param check_mmio If true, uses mmio_load() to detect memory-mapped I/O
   *
   * Uses operands[0]=rD, operands[1]=offset (D), operands[2]=rA from current instruction.
   * If rA (operands[2]) is 0, omits the base register addition.
   */
```

## Source note 51, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L330)

```text
/**
   * @brief Emit load with X-form addressing: rD = LOAD(rA + rB)
   * @param load_macro The load macro name
   * @param dest_type The destination type suffix
   * @param check_mmio If true, uses mmio_load_x_form() to detect memory-mapped I/O
   *
   * Uses operands[0]=rD, operands[1]=rA, operands[2]=rB from current instruction.
   * If rA (operands[1]) is 0, omits the first register addition.
   */
```

## Source note 52, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L341)

```text
/**
   * @brief Emit store with D-form addressing: STORE(rA + offset, rS)
   * @param store_macro The store macro name (e.g., "REX_STORE_U8")
   * @param src_type The source type suffix (e.g., "u8", "u32")
   * @param check_mmio If true, uses mmio_store() to detect memory-mapped I/O
   *
   * Uses operands[0]=rS, operands[1]=offset (D), operands[2]=rA from current instruction.
   */
```

## Source note 53, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/builder_context.h#L351)

```text
/**
   * @brief Emit store with X-form addressing: STORE(rA + rB, rS)
   * @param store_macro The store macro name
   * @param src_type The source type suffix
   * @param check_mmio If true, uses mmio_store() to detect memory-mapped I/O
   *
   * Uses operands[0]=rS, operands[1]=rA, operands[2]=rB from current instruction.
   */
```
