# Decoded binary: codegen source notes

This record preserves technical and API notes moved from `src/codegen/decoded_binary.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L28)

```text
// Instruction Range Iterator
```

## Source note 2, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L75)

```text
// Decoded Binary - Single-pass instruction decoder
```

## Source note 3, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L82)

```text
// Non-copyable, non-movable (holds reference to binary)
```

## Source note 4, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L88)

```text
/// Decode all executable sections (call once after construction)
```

## Source note 5, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L91)

```text
/// Get instruction at address (O(1) lookup)
```

## Source note 6, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L92)

```text
/// Returns nullptr if address not in any executable section
```

## Source note 7, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L96)

```text
/// Get range of instructions [start, end)
```

## Source note 8, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L97)

```text
/// Returns empty range if addresses not in same section
```

## Source note 9, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L100)

```text
/// Get raw data at address (for reading non-instruction data like jump tables)
```

## Source note 10, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L103)

```text
/// Read a value at address (with byte-swap for big-endian)
```

## Source note 11, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L107)

```text
/// Get all code regions (separated by null padding)
```

## Source note 12, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L110)

```text
/// Find code region containing address
```

## Source note 13, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L113)

```text
/// Check if branch from->to crosses a null boundary
```

## Source note 14, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L116)

```text
/// Check if address is in any code region
```

## Source note 15, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L119)

```text
/// Check if instruction at address is null/invalid
```

## Source note 16, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L122)

```text
/// Statistics
```

## Source note 17, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L131)

```text
// Copy of raw section data
```

## Source note 18, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L158)

```text
/// Compute code regions by finding null padding boundaries
```

## Source note 19, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L161)

```text
/// Find section containing address
```

## Source note 20, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L167)

```text
// Template Implementation
```

## Source note 21, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L179)

```text
// Byte-swap for big-endian PPC
```

## Source note 22, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L197)

```text
// Helper functions for branch analysis (using existing arch::ppc)
```

## Source note 23, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L200)

```text
/// Check if instruction is a branch
```

## Source note 24, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L205)

```text
/// Check if instruction is a call (branch with link)
```

## Source note 25, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L210)

```text
/// Check if instruction is a return (blr)
```

## Source note 26, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L215)

```text
/// Check if instruction is indirect branch (bcctr/bclr)
```

## Source note 27, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L220)

```text
/// Check if instruction is a terminator (unconditional branch, return, bctr)
```

## Source note 28, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L225)

```text
/// Check if instruction is conditional branch
```

## Source note 29, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L230)

```text
/// Check if instruction is lis (addis rD, 0, imm)
```

## Source note 30, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L235)

```text
/// Get branch target address (for direct branches)
```

## Source note 31, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/decoded_binary.h#L240)

```text
/// Check if instruction is null/invalid (null padding)
```
