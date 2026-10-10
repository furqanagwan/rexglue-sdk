# Code patches: codegen source notes

This record preserves technical and API notes moved from `src/codegen/code_patches.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/code_patches.cpp#L23)

```text
// Check everything before writing anything.
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/code_patches.cpp#L24)

```text
// start -> end, owner
```

## Source note 3, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/code_patches.cpp#L78)

```text
// Branches, calls, returns, traps and system calls: switching one would change
```

## Source note 4, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/code_patches.cpp#L79)

```text
// control flow that analysis discovered from the original code.
```

## Source note 5, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/code_patches.cpp#L83)

```text
// twi, bc, sc, b/bl, bclr/bcctr and friends
```

## Source note 6, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/code_patches.cpp#L162)

```text
// A write of the bytes already there (QoS's be8 0x01) switches nothing.
```
