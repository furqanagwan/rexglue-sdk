# Output stamp: codegen source notes

This record preserves technical and API notes moved from `src/codegen/output_stamp.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_stamp.cpp#L26)

```text
/// Bump when the stamp layout changes.
```

## Source note 2, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_stamp.cpp#L82)

```text
// Content, not mtime: survives a checkout, a copy, or a bare touch.
```

## Source note 3, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_stamp.cpp#L88)

```text
// Weaker than content, but a constant here would report a locked input
```

## Source note 4, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_stamp.cpp#L89)

```text
// as unchanged and skip the module forever.
```
