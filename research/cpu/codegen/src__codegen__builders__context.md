# Context: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/context.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L25)

```text
/// eieio instruction encoding (big-endian). Used for MMIO detection:
```

## Source note 2, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L26)

```text
/// if the next instruction after a load/store is eieio, the access is MMIO.
```

## Source note 3, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L30)

```text
// Convenience Accessors
```

## Source note 4, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L42)

```text
// Register Accessors
```

## Source note 5, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L45)

```text
// Localizing a non-volatile assumes the function owns it across its whole body.
```

## Source note 6, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L46)

```text
// An SEH funclet does not: it inherits its owner's live registers through ctx.
```

## Source note 7, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L143)

```text
// Output Helpers
```

## Source note 8, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L146)

```text
// Template implementations in header, but we need explicit instantiations
```

## Source note 9, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L147)

```text
// for common format strings to avoid link errors in some cases
```

## Source note 10, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L150)

```text
// Code Generation Helpers
```

## Source note 11, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L166)

```text
// Search in calls (bl instructions)
```

## Source note 12, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L173)

```text
// Search in tail calls (b instructions to other functions)
```

## Source note 13, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L200)

```text
// setjmp must execute in this caller's frame. Restore ctx after native
```

## Source note 14, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L201)

```text
// unwinding; no modified automatic local is read on return.
```

## Source note 15, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L207)

```text
// Try to use pre-resolved call target from FunctionGraph
```

## Source note 16, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L213)

```text
// Handle save/restore helpers. Gated on the global setting, not this
```

## Source note 17, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L214)

```text
// function's: the helper bodies are emitted under it too, so once they
```

## Source note 18, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L215)

```text
// spill to locals they are no-ops that scribble zeros on the caller's
```

## Source note 19, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L216)

```text
// frame. A share_registers function still has to elide them.
```

## Source note 20, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L219)

```text
// print nothing - these are handled by local variable tracking
```

## Source note 21, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L223)

```text
// An SEH funclet runs on its owner's frame and reads whatever non-volatiles
```

## Source note 22, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L224)

```text
// the owner left live, so hand it the localized copies through ctx and take
```

## Source note 23, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L225)

```text
// them back afterwards. Only registers already localized here can be live at
```

## Source note 24, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L226)

```text
// this point, so that set is the whole live-in the funclet can see.
```

## Source note 25, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L250)

```text
// Try to resolve ordinal to actual function name
```

## Source note 26, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L277)

```text
// Unresolved target from graph
```

## Source note 27, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L284)

```text
// No pre-resolved target found - this is an error
```

## Source note 28, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L294)

```text
// Use classifyTarget for consistent branch classification
```

## Source note 29, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L295)

```text
// false = branch instruction (not a call), so own-base means loop back
```

## Source note 30, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L300)

```text
// Target is within this function - local goto
```

## Source note 31, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L307)

```text
// Conditional tail call to another function - check pre-resolved call target
```

## Source note 32, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L378)

```text
// Build call -- no ctx/base prefix, just register arguments resolved through accessors
```

## Source note 33, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L441)

```text
// Vector (SIMD) Code Generation Helpers
```

## Source note 34, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L455)

```text
// Replace {vA} placeholder in expression with actual register
```

## Source note 35, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L475)

```text
// Swapped: op(vB, vA) instead of op(vA, vB) - useful for andnot which has reversed operand
```

## Source note 36, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L504)

```text
// Memory (Load/Store) Code Generation Helpers
```

## Source note 37, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L509)

```text
// D-form: rD = LOAD(rA + D) where operands[0]=rD, operands[1]=D, operands[2]=rA
```

## Source note 38, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L510)

```text
// load_macro should be like "REX_LOAD_U8" - we replace REX_LOAD with REX_MM_LOAD for MMIO
```

## Source note 39, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L514)

```text
// Replace "REX_LOAD_" with "REX_MM_LOAD_"
```

## Source note 40, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L529)

```text
// X-form: rD = LOAD(rA + rB) where operands[0]=rD, operands[1]=rA, operands[2]=rB
```

## Source note 41, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L530)

```text
// load_macro should be like "REX_LOAD_U8" - we replace REX_LOAD with REX_MM_LOAD for MMIO
```

## Source note 42, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L534)

```text
// Replace "REX_LOAD_" with "REX_MM_LOAD_"
```

## Source note 43, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L549)

```text
// D-form: STORE(rA + D, rS) where operands[0]=rS, operands[1]=D, operands[2]=rA
```

## Source note 44, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L550)

```text
// store_macro should be like "REX_STORE_U8" - we replace REX_STORE with REX_MM_STORE for MMIO
```

## Source note 45, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L554)

```text
// Replace "REX_STORE_" with "REX_MM_STORE_"
```

## Source note 46, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L569)

```text
// X-form: STORE(rA + rB, rS) where operands[0]=rS, operands[1]=rA, operands[2]=rB
```

## Source note 47, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L570)

```text
// store_macro should be like "REX_STORE_U8" - we replace REX_STORE with REX_MM_STORE for MMIO
```

## Source note 48, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L573)

```text
// Use X-form specific check (operands[1] is base)
```

## Source note 49, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/context.cpp#L574)

```text
// Replace "REX_STORE_" with "REX_MM_STORE_"
```
