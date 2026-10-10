# Crt jump scanner test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/crt_jump_scanner_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/crt_jump_scanner_test.cpp#L24)

```text
// Synthetic CRT-shaped routines assembled from the documented register layout.
```

## Source note 2, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/crt_jump_scanner_test.cpp#L25)

```text
// Deliberately use different relocation values from every investigated title.
```

## Source note 3, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/crt_jump_scanner_test.cpp#L95)

```text
// Negative signed low-half relocation; points back inside this image.
```

## Source note 4, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/crt_jump_scanner_test.cpp#L98)

```text
// unmapped hook pointer must be rejected
```
