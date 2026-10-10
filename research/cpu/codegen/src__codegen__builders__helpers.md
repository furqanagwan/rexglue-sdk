# Helpers: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/helpers.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L28)

```text
/**
 * Compute a 64-bit mask for PPC rotate/mask instructions.
 * @param mstart Starting bit position (0-63)
 * @param mstop Ending bit position (0-63)
 * @return 64-bit mask with bits set between mstart and mstop
 */
```

## Source note 2, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L42)

```text
// CR Bit Helpers
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L45)

```text
/// Map PPC BI field bit index (0-3) to CRRegister member name.
```

## Source note 4, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L52)

```text
// Record-Form Helpers
```

## Source note 5, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L55)

```text
/**
 * Check if the current instruction is a record form (has '.' suffix).
 *
 * Record-form instructions update CR0 based on the result.
 *
 * @param insn The ppc_insn being processed
 * @return true if the instruction name contains '.' (record form)
 */
```

## Source note 6, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L67)

```text
/**
 * Emit CR0 comparison for record-form instructions.
 *
 * Record-form instructions (those with '.' suffix like add., and., etc.)
 * update CR0 based on the result compared to zero:
 *   CR0[LT] = result < 0
 *   CR0[GT] = result > 0
 *   CR0[EQ] = result == 0
 *   CR0[SO] = XER[SO]
 *
 * @param ctx The builder context containing the instruction being processed
 */
```

## Source note 7, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L86)

```text
/**
 * Emit a CR bit operation: crD = crA <op> crB
 *
 * CR bit operations work on individual CR bits (0-31). This helper:
 * - Maps bit indices to CR field (0-7) and field bit (0-3)
 * - Emits code to access CR fields by bit name
 *
 * @param ctx The builder context
 * @param op The operation symbol as a string (e.g., "|", "&", "^")
 * @param invertA If true, invert the value of crA before the operation
 * @param invertB If true, invert the value of crB before the operation
 * @param invertResult If true, invert the final result before storing in crD
 */
```

## Source note 8, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L130)

```text
// Comparison Instruction Helpers
```

## Source note 9, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L133)

```text
/**
 * Emit register-to-register comparison.
 *
 * Pattern: crD.compare<T>(rA.field, rB.field, XER)
 * Used by: cmpd, cmpld, cmplw, cmpw
 *
 * @param ctx The builder context
 * @param type_name The comparison type (e.g., "int64_t", "uint32_t")
 * @param field The register field accessor (e.g., "s64", "u32")
 */
```

## Source note 10, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L148)

```text
/**
 * Emit register-to-immediate comparison.
 *
 * Pattern: crD.compare<T>(rA.field, imm, XER)
 * Used by: cmpdi, cmpldi, cmplwi, cmpwi
 *
 * @param ctx The builder context
 * @param type_name The comparison type (e.g., "int64_t", "uint32_t")
 * @param field The register field accessor (e.g., "s64", "u32")
 * @param sign_extend If true, sign-extend the immediate via static_cast<int32_t>
 */
```

## Source note 11, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L172)

```text
// Memory Operation Helpers
```

## Source note 12, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L175)

```text
/**
 * Emit D-form load with update instruction.
 *
 * Pattern: EA = (rA) + d; rD = MEM[EA]; rA = EA
 * Used by: lbzu, lwzu, ldu, etc.
 *
 * @param ctx The builder context
 * @param load_macro The REX_LOAD_* macro to use (e.g., "REX_LOAD_U8")
 */
```

## Source note 13, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L185)

```text
// EA = displacement + rA
```

## Source note 14, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L188)

```text
// rD = MEM[EA]
```

## Source note 15, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L190)

```text
// rA = EA (update)
```

## Source note 16, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L194)

```text
/**
 * Emit X-form load with update instruction.
 *
 * Pattern: EA = rA + rB; rD = MEM[EA]; rA = EA
 * Used by: lbzux, lhzux, lwzux, ldux
 *
 * @param ctx The builder context
 * @param load_macro The REX_LOAD_* macro to use (e.g., "REX_LOAD_U8")
 */
```

## Source note 17, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L210)

```text
/**
 * Emit D-form store with update instruction.
 *
 * Pattern: EA = (rA) + d; MEM[EA] = rS; rA = EA
 * Used by: stbu, stwu, stdu, etc.
 *
 * @param ctx The builder context
 * @param store_macro The REX_STORE_* macro to use (e.g., "REX_STORE_U8")
 * @param field The register field to store (e.g., "u8", "u32", "u64")
 */
```

## Source note 18, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L221)

```text
// EA = displacement + rA
```

## Source note 19, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L224)

```text
// MEM[EA] = rS
```

## Source note 20, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L226)

```text
// rA = EA (update)
```

## Source note 21, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L230)

```text
/**
 * Emit X-form store with update instruction.
 *
 * Pattern: EA = rA + rB; MEM[EA] = rS; rA = EA
 * Used by: stbux, sthux, stwux, stdux
 *
 * @param ctx The builder context
 * @param store_macro The REX_STORE_* normal macro (e.g., "REX_STORE_U8")
 * @param mmio_macro The REX_MM_STORE_* MMIO macro (e.g., "REX_MM_STORE_U8")
 * @param field The register field to store (e.g., "u8", "u32", "u64")
 */
```

## Source note 22, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L250)

```text
/**
 * Get the appropriate store macro based on MMIO context.
 *
 * @param ctx The builder context
 * @param normal_macro Normal store macro (e.g., "REX_STORE_U32")
 * @param mmio_macro MMIO store macro (e.g., "REX_MM_STORE_U32")
 * @return The appropriate macro string
 */
```

## Source note 23, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L264)

```text
// Atomic Operation Helpers
```

## Source note 24, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L267)

```text
/**
 * Emit atomic load-and-reserve instruction (lwarx/ldarx pattern).
 *
 * Pattern: EA = rA + rB; reserved = *(T*)REX_RAW_ADDR(EA); rD = bswap(reserved)
 *
 * @param ctx The builder context
 * @param ptr_type The pointer type (e.g., "uint32_t", "uint64_t")
 * @param bswap_func The byte-swap builtin (e.g., "__builtin_bswap32")
 * @param reserved_field The reserved register field (e.g., "u32", "u64")
 */
```

## Source note 25, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L290)

```text
/**
 * Emit atomic store-conditional instruction (stwcx./stdcx. pattern).
 *
 * Pattern: EA = rA + rB; cr0 = CAS(EA, reserved, bswap(rS))
 *
 * @param ctx The builder context
 * @param ptr_type The pointer type (e.g., "uint32_t", "uint64_t")
 * @param bswap_func The byte-swap builtin (e.g., "__builtin_bswap32")
 * @param field The register field (e.g., "s32", "s64")
 */
```

## Source note 26, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L308)

```text
// Fails without storing unless the reservation is on this address; either
```

## Source note 27, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L309)

```text
// way the reservation is gone afterwards.
```

## Source note 28, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L320)

```text
// Sign-Extending Load Helpers
```

## Source note 29, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L323)

```text
/**
 * Emit D-form sign-extending load instruction.
 *
 * Pattern: rD = sign_extend(LOAD(rA + d))
 * Used by: lha, lwa (halfword/word algebraic loads)
 *
 * @param ctx The builder context
 * @param cast_type The cast for sign extension (e.g., "int16_t", "int32_t")
 * @param load_macro The REX_LOAD_* macro to use
 */
```

## Source note 30, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L341)

```text
/**
 * Emit X-form sign-extending load instruction.
 *
 * Pattern: rD = sign_extend(LOAD(rA + rB))
 * Used by: lhax, lwax (halfword/word algebraic indexed loads)
 *
 * @param ctx The builder context
 * @param cast_type The cast for sign extension (e.g., "int16_t", "int32_t")
 * @param load_macro The REX_LOAD_* macro to use
 */
```

## Source note 31, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L360)

```text
// MMIO Detection Helpers
```

## Source note 32, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L363)

```text
/**
 * Check if an upper-16-bit immediate value corresponds to a known MMIO range.
 *
 * Xbox 360 hardware register ranges:
 * - GPU MMIO: 0x7FC80000-0x7FCFFFFF (upper bits: 0x7FC8-0x7FCF)
 * - XMA/APU MMIO: 0x7FEA0000-0x7FEAFFFF (upper bits: 0x7FEA)
 *
 * @param imm The upper 16 bits loaded by lis/oris
 * @return true if the value matches a known MMIO base address range
 */
```

## Source note 33, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L378)

```text
// Branch Bounds-Checking Helper
```

## Source note 34, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L381)

```text
/**
 * Emit a conditional branch with bounds checking.
 *
 * If the target is within the current function, emits a goto.
 * If outside, emits a warning and a return statement.
 *
 * @param ctx The builder context
 * @param target Target address of the branch
 * @param condition Pre-formatted condition expression (e.g., "ctr.u32 != 0")
 * @param instr_name Instruction mnemonic for the warning message
 */
```

## Source note 35, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L404)

```text
// Vector EA Calculation Helpers
```

## Source note 36, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L407)

```text
/**
 * Emit aligned or unaligned vector effective address calculation to ea.
 *
 * Pattern: ea = (opt_rA + rB) [& ~align_mask]
 * Uses operands[1] as optional base register and operands[2] as index register.
 *
 * @param ctx The builder context
 * @param align_mask Alignment mask string (e.g., "0xF"), or nullptr for no alignment
 */
```

## Source note 37, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L429)

```text
/**
 * Emit unaligned vector effective address calculation to temp.
 *
 * Pattern: temp.u32 = opt_rA + rB
 * Uses operands[1] as optional base register and operands[2] as index register.
 *
 * @param ctx The builder context
 */
```

## Source note 38, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L445)

```text
// Trap Instruction Helper
```

## Source note 39, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/helpers.h#L448)

```text
/**
 * Emit a PPC trap instruction: if (<condition>) ppc_trap(ctx, base, 0);
 *
 * @param to       5-bit TO field
 * @param aSigned  First operand, signed (e.g., "ctx.r3.s32")
 * @param aUnsigned First operand, unsigned (e.g., "ctx.r3.u32")
 * @param bSigned  Second operand, signed (e.g., "ctx.r4.s32" or "-1")
 * @param bUnsigned Second operand, unsigned (e.g., "ctx.r4.u32" or "4294967295u")
 */
```
