# Crt jump scanner: codegen source notes

This record preserves technical and API notes moved from `src/codegen/crt_jump_scanner.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L21)

```text
// Match the complete register save/restore layout, including the alternate
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L22)

```text
// longjmp path. Only address relocations are variable. No title IDs/addresses.
```

## Source note 3, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L26)

```text
// lis r4, hook@h
```

## Source note 4, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L27)

```text
// lwz r0, hook@l(r4)
```

## Source note 5, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L31)

```text
// stfd f14..31
```

## Source note 6, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L33)

```text
// std r13..31
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L36)

```text
// stvlx128 v64..127
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L51)

```text
// relative bl (AA=0, LK=1)
```

## Source note 9, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L53)

```text
// lfd f14..31
```

## Source note 10, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L55)

```text
// ld r13..31
```

## Source note 11, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L58)

```text
// lvx128 v64..127
```

## Source note 12, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L95)

```text
// Widen arithmetic before checking sizes; never read across a section.
```

## Source note 13, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L118)

```text
// The alternate (unwind-style) buffer path calls the kernel, not an
```

## Source note 14, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/crt_jump_scanner.cpp#L119)

```text
// ordinary function. Require that exact import rather than any branch.
```
