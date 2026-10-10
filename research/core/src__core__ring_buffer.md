# Ring buffer: core source notes

This record preserves technical and API notes moved from `src/core/ring_buffer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/ring_buffer.cpp#L74)

```text
// Sanity check: Make sure we don't read over the write offset.
```

## Source note 2, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/ring_buffer.cpp#L104)

```text
// Sanity check: Make sure we don't write over the read offset.
```
