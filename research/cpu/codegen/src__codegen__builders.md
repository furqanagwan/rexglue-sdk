# Builders: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L18)

```text
/**
 * Build C++ code for a PPC instruction using the dispatch table.
 *
 * @param id The PPC instruction ID (PPC_INST_*)
 * @param ctx The builder context
 * @return true if instruction was handled, false if unknown
 */
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L28)

```text
// Comparison Builders (CMP*, CMPL*)
```

## Source note 3, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L41)

```text
// Arithmetic Builders (ADD, SUB, MUL, DIV, NEG)
```

## Source note 4, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L99)

```text
// Logical Builders (AND, OR, XOR, shifts, rotates, bit manipulation)
```

## Source note 5, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L102)

```text
// AND operations
```

## Source note 6, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L108)

```text
// OR operations
```

## Source note 7, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L117)

```text
// XOR operations
```

## Source note 8, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L122)

```text
// Conditional Register operations
```

## Source note 9, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L132)

```text
// Equivalence (XNOR)
```

## Source note 10, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L135)

```text
// Count leading zeros
```

## Source note 11, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L139)

```text
// Sign extension
```

## Source note 12, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L144)

```text
// Clear operations
```

## Source note 13, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L147)

```text
// Rotate left double word
```

## Source note 14, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L157)

```text
// Rotate left word
```

## Source note 15, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L164)

```text
// Shift left
```

## Source note 16, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L168)

```text
// Shift right algebraic
```

## Source note 17, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L174)

```text
// Shift right logical
```

## Source note 18, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L179)

```text
// Control Flow Builders (branches, calls, returns)
```

## Source note 19, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L182)

```text
// Unconditional branch
```

## Source note 20, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L188)

```text
// Count register branch
```

## Source note 21, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L193)

```text
// Decrement counter and branch
```

## Source note 22, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L202)

```text
// Conditional branch (eq)
```

## Source note 23, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L208)

```text
// Conditional branch (lt)
```

## Source note 24, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L214)

```text
// Conditional branch (gt)
```

## Source note 25, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L220)

```text
// Conditional branch (so - summary overflow / unordered)
```

## Source note 26, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L227)

```text
// Floating Point Builders
```

## Source note 27, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L230)

```text
// Sign manipulation
```

## Source note 28, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L235)

```text
// Move and conversion
```

## Source note 29, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L264)

```text
// Fused multiply-add
```

## Source note 30, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L274)

```text
// Reciprocal and square root
```

## Source note 31, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L284)

```text
// Memory Builders (loads and stores)
```

## Source note 32, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L287)

```text
// Load immediate
```

## Source note 33, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L291)

```text
// Byte loads
```

## Source note 34, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L297)

```text
// Halfword loads
```

## Source note 35, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L308)

```text
// Word loads
```

## Source note 36, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L319)

```text
// Doubleword loads
```

## Source note 37, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L326)

```text
// Atomic load and reserve
```

## Source note 38, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L330)

```text
// Floating point loads
```

## Source note 39, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L340)

```text
// Byte stores
```

## Source note 40, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L346)

```text
// Halfword stores
```

## Source note 41, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L353)

```text
// Word stores
```

## Source note 42, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L361)

```text
// Atomic store conditional
```

## Source note 43, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L365)

```text
// Doubleword stores
```

## Source note 44, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L372)

```text
// Floating point stores
```

## Source note 45, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L383)

```text
// Vector loads
```

## Source note 46, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L390)

```text
// Vector stores
```

## Source note 47, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L399)

```text
// System Builders (NOP, SYNC, MF*, MT*, DC*, trap)
```

## Source note 48, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L402)

```text
// No-ops and sync
```

## Source note 49, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L413)

```text
// Trap instructions (generic builders - all specific variants map to these)
```

## Source note 50, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L414)

```text
// Trap word immediate
```

## Source note 51, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L415)

```text
// Trap doubleword immediate
```

## Source note 52, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L416)

```text
// Trap word register
```

## Source note 53, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L417)

```text
// Trap doubleword register
```

## Source note 54, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L419)

```text
// Cache operations
```

## Source note 55, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L429)

```text
// Move register
```

## Source note 56, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L432)

```text
// Move register field
```

## Source note 57, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L436)

```text
// Move from special registers
```

## Source note 58, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L447)

```text
// Move to special registers
```

## Source note 59, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L456)

```text
// Clear left double word immediate
```

## Source note 60, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L460)

```text
// Vector Builders (AltiVec/VMX instructions)
```

## Source note 61, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L463)

```text
// Vector floating point arithmetic
```

## Source note 62, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L478)

```text
// Vector dot products
```

## Source note 63, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L482)

```text
// Vector rounding
```

## Source note 64, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L488)

```text
// Vector integer arithmetic
```

## Source note 65, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L523)

```text
// Vector average
```

## Source note 66, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L530)

```text
// Vector logical
```

## Source note 67, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L539)

```text
// Vector compare
```

## Source note 68, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L554)

```text
// Vector conversion
```

## Source note 69, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L560)

```text
// Vector merge
```

## Source note 70, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L568)

```text
// Vector permute
```

## Source note 71, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L573)

```text
// Vector shift
```

## Source note 72, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L592)

```text
// Vector splat
```

## Source note 73, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L600)

```text
// Vector pack
```

## Source note 74, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders.h#L612)

```text
// Vector unpack
```
