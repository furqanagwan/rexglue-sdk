# Control flow: codegen source notes

This record preserves technical and API notes moved from `src/codegen/builders/control_flow.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L24)

```text
// Unconditional Branch
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L30)

```text
// Use graph to classify the target - handles thunks that branch to nearby functions
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L31)

```text
// false = branch instruction (not a call), so own-base means loop back
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L36)

```text
// Target is within this function and not another function's entry point
```

## Source note 5, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L42)

```text
// Tail call to another function or import
```

## Source note 6, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L48)

```text
// Unknown target - fall back to range check
```

## Source note 7, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L64)

```text
// Always set LR (unless skipLr)
```

## Source note 8, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L68)

```text
// Use graph to classify the target
```

## Source note 9, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L69)

```text
// true = call instruction, so own-base means recursive call (not loop back)
```

## Source note 10, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L74)

```text
// PIC code pattern - bl to get PC into LR, treat as local jump
```

## Source note 11, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L75)

```text
// LR is already set above, now jump to the target
```

## Source note 12, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L82)

```text
// Call could change CSR state
```

## Source note 13, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L100)

```text
// BLRL: save return address, then branch-and-link to current LR
```

## Source note 14, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L110)

```text
// Count Register Branch
```

## Source note 15, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L114)

```text
// Check active jump table (set by emitCpp before dispatch), then auto-detected
```

## Source note 16, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L118)

```text
// Check auto-detected jump tables from function analysis
```

## Source note 17, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L134)

```text
// TODO(tomc): Figure out if this actually is triggered on real hardware and what would
```

## Source note 18, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L135)

```text
// happen?
```

## Source note 19, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L176)

```text
// No switch table - assume tail call via CTR
```

## Source note 20, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L177)

```text
// NOTE(tomc): If this is actually an unresolved switch table, the code after
```

## Source note 21, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L178)

```text
// will be unreachable. This is caught during analysis by discover_blocks.
```

## Source note 22, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L179)

```text
// The validation phase will report missing switch tables.
```

## Source note 23, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L190)

```text
// the call could change it
```

## Source note 24, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L203)

```text
// Decrement Counter and Branch
```

## Source note 25, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L263)

```text
// Conditional Branch (eq)
```

## Source note 26, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L287)

```text
// Conditional Branch (lt)
```

## Source note 27, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L311)

```text
// Conditional Branch (gt)
```

## Source note 28, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/builders/control_flow.cpp#L335)

```text
// Conditional Branch (so - summary overflow / unordered)
```
