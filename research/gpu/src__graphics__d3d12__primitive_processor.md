# Primitive processor: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/primitive_processor.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/primitive_processor.cpp#L63)

```text
// No need to submit deferred barriers - builtin_index_buffer_ has never
```

## Source note 2, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/primitive_processor.cpp#L64)

```text
// been used yet, so it's in the initial state, and
```

## Source note 3, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/primitive_processor.cpp#L65)

```text
// builtin_index_buffer_upload_ is in an upload heap, so it's GENERIC_READ.
```

## Source note 4, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/primitive_processor.cpp#L130)

```text
// Successfully created the buffer and wrote the data to upload.
```

## Source note 5, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/primitive_processor.cpp#L134)

```text
// Schedule uploading in the first submission.
```

## Source note 6, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/primitive_processor.cpp#L161)

```text
// namespace rex::graphics::d3d12
```
