# Primitive cache fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/primitive_cache_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/primitive_cache_fixture_test.cpp#L72)

```text
// Keep the same index address/key in this frame. A guest write collapses the
```

## Source note 2, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/primitive_cache_fixture_test.cpp#L73)

```text
// fan to degenerate triangles; stale conversion would still draw white.
```
