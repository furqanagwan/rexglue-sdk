# Phase merge: codegen source notes

This record preserves technical and API notes moved from `src/codegen/phase_merge.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L31)

```text
// Entries reached by a tail branch into another function (RG-FIX-002)
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L34)

```text
// A direct tail branch proves that a shared constant-return leaf is also an
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L35)

```text
// entry. Restrict this to `li r3,N; blr`: an arbitrary shared epilogue may
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L36)

```text
// depend on the caller's frame or localized registers and cannot safely be
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L37)

```text
// emitted as an independent function. Jump-table references alone do not
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L38)

```text
// establish an entry. Returns how many entries were added.
```

## Source note 7, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L48)

```text
// Exception-region scanning may not retain the conditional flag. Verify
```

## Source note 8, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L49)

```text
// the source opcode too: only a direct b with LK=0 proves this tail entry.
```

## Source note 9, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L67)

```text
// addi r3,r0,IMM is the li pseudo-instruction; the immediate is unrestricted.
```

## Source note 10, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L91)

```text
// Merge to resolve jumps then seal functions
```

## Source note 11, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L131)

```text
// Only once nothing else resolves: register the entries that other
```

## Source note 12, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L132)

```text
// functions branch into, then resolve against them.
```

## Source note 13, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_merge.cpp#L155)

```text
// anonymous namespace
```
