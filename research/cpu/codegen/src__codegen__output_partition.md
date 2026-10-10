# Output partition: codegen source notes

This record preserves technical and API notes moved from `src/codegen/output_partition.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_partition.cpp#L29)

```text
/// Bump when the sidecar layout changes.
```

## Source note 2, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_partition.cpp#L88)

```text
// Ordered so the sidecar is byte-stable across runs.
```

## Source note 3, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/output_partition.cpp#L143)

```text
// Rebuilt, not updated, so functions that disappeared leave the sidecar.
```
