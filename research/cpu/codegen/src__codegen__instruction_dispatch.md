# Instruction dispatch: codegen source notes

This record preserves technical and API notes moved from `src/codegen/instruction_dispatch.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L28)

```text
// Static dispatch table
```

## Source note 2, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L125)

```text
// Conditional Register
```

## Source note 3, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L149)

```text
// Control Flow
```

## Source note 4, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L183)

```text
// Floating Point
```

## Source note 5, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L220)

```text
// Memory - Load Immediate
```

## Source note 6, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L226)

```text
// Memory - Loads
```

## Source note 7, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L267)

```text
// Memory - Stores
```

## Source note 8, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L302)

```text
// Memory - Vector Loads
```

## Source note 9, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L324)

```text
// Memory - Vector Stores
```

## Source note 10, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L353)

```text
// Trap word immediate (all variants map to generic TWI)
```

## Source note 11, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L369)

```text
// Trap doubleword immediate (all variants map to generic TDI)
```

## Source note 12, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L385)

```text
// Trap word register (all variants map to generic TW)
```

## Source note 13, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L397)

```text
// Trap doubleword register (all variants map to generic TD)
```

## Source note 14, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L442)

```text
// Vector - Floating Point Arithmetic
```

## Source note 15, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L453)

```text
// Same as VMADDFP
```

## Source note 16, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L470)

```text
// Vector - Dot Products
```

## Source note 17, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L476)

```text
// Vector - Rounding
```

## Source note 18, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L488)

```text
// Vector - Integer Arithmetic
```

## Source note 19, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L525)

```text
// Vector - Average
```

## Source note 20, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L534)

```text
// Vector - Logical
```

## Source note 21, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L550)

```text
// Vector - Compare
```

## Source note 22, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L572)

```text
// Vector - Conversion
```

## Source note 23, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L584)

```text
// Vector - Merge
```

## Source note 24, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L596)

```text
// Vector - Permute
```

## Source note 25, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L604)

```text
// Vector - Shift
```

## Source note 26, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L632)

```text
// Vector - Splat
```

## Source note 27, line 644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L644)

```text
// Vector - Pack
```

## Source note 28, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L666)

```text
// Vector - Unpack
```

## Source note 29, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L682)

```text
// VUPKHSB128/VUPKLSB128 misidentification fixup (moved from recompiler.cpp).
```

## Source note 30, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L683)

```text
// Only fires when operands[2]==0x60; table entries for *128 variants
```

## Source note 31, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L684)

```text
// still serve the non-0x60 case.
```

## Source note 32, line 697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L697)

```text
// Emit trap code for unimplemented instruction - allows tests to be generated
```

## Source note 33, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/instruction_dispatch.cpp#L698)

```text
// and fail at runtime rather than skipping the entire function
```
