# Phase discover: codegen source notes

This record preserves technical and API notes moved from `src/codegen/phase_discover.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L39)

```text
// Discover Phase: iterative function block discovery
```

## Source note 2, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L52)

```text
// Skip if already discovered
```

## Source note 3, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L58)

```text
// Imports don't need block discovery
```

## Source note 4, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L66)

```text
// Lookup pdataSize for exception handler boundary
```

## Source note 5, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L69)

```text
// For CONFIG functions: use only the explicitly declared size (if any)
```

## Source note 6, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L70)

```text
// If no size specified (size=0), let discovery find natural boundaries via region
```

## Source note 7, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L71)

```text
// Don't inherit PDATA sizes for CONFIG functions - they're user hints for entry points
```

## Source note 8, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L73)

```text
// 0 if not specified, which is correct
```

## Source note 9, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L76)

```text
// For non-CONFIG functions, use PDATA size if available
```

## Source note 10, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L84)

```text
// Find the code region containing this function
```

## Source note 11, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L97)

```text
// Pass pdataSize so forward branches within function extent are correctly identified
```

## Source note 12, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L106)

```text
// snooper the function with the discovered blocks and instructions
```

## Source note 13, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L110)

```text
// Add jump tables (targets become labels in the function)
```

## Source note 14, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L115)

```text
// Register external call targets as new functions (bl only, not b)
```

## Source note 15, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L125)

```text
// Add unresolved branches for later resolution
```

## Source note 16, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L131)

```text
// Scan exception handler regions for branches not in discovered blocks
```

## Source note 17, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L146)

```text
// Skip if already discovered by normal control flow
```

## Source note 18, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L150)

```text
// Skip if marked invalid
```

## Source note 19, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L174)

```text
// Skip internal jumps within pdata region
```

## Source note 20, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L181)

```text
// Register call targets as new functions
```

## Source note 21, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L199)

```text
// Iterative discovery
```

## Source note 22, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L224)

```text
// VTable scanning
```

## Source note 23, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L248)

```text
// Continue discovery for vtable functions
```

## Source note 24, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L271)

```text
// Function Pointer Scan: find lis/addi pairs loading code addresses
```

## Source note 25, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L272)

```text
// TODO(tomc): THIS IS WIP AND PROB A BAD IDEA LOL LETS SEE
```

## Source note 26, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L289)

```text
// Build set of existing functions to avoid duplicates
```

## Source note 27, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L295)

```text
// Track lis values: register -> (high_value, lis_address)
```

## Source note 28, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L296)

```text
// We scan linearly and track the most recent lis for each register
```

## Source note 29, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L297)

```text
// PPC has exactly 32 GPRs, so a fixed-size array is more efficient than a map
```

## Source note 30, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L304)

```text
// Reset tracking at region boundaries
```

## Source note 31, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L311)

```text
// Track lis rD, IMM
```

## Source note 32, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L320)

```text
// Check for addi rD, rA, IMM where rA was set by lis
```

## Source note 33, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L324)

```text
// li pseudo-op, not addi
```

## Source note 34, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L331)

```text
// Sign-extended add
```

## Source note 35, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L333)

```text
// PPC instructions are 4-byte aligned
```

## Source note 36, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L337)

```text
// Check if this address is in a code region
```

## Source note 37, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L342)

```text
// Skip if already a known function
```

## Source note 38, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L346)

```text
// Skip if it's an internal address (within same function's likely range)
```

## Source note 39, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L347)

```text
// Heuristic: if target is very close to current address, probably internal label
```

## Source note 40, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L350)

```text
// Could be local label, skip for now
```

## Source note 41, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L354)

```text
// Register as function with DISCOVERED authority and hasXrefs=true
```

## Source note 42, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L363)

```text
// Also check ori rD, rA, IMM (alternative to addi for unsigned)
```

## Source note 43, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L371)

```text
// Unsigned OR
```

## Source note 44, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L373)

```text
// PPC instructions are 4-byte aligned
```

## Source note 45, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L396)

```text
// Clear lis tracking if register is overwritten by other instruction
```

## Source note 46, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L397)

```text
// (Simplified: we clear on any write to the register)
```

## Source note 47, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L398)

```text
// This is conservative - could miss some patterns but avoids false positives
```

## Source note 48, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L405)

```text
// anonymous namespace
```

## Source note 49, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_discover.cpp#L407)

```text
/// Discover blocks for all pending functions (shared helper, declared in phase_helpers.h).
```
