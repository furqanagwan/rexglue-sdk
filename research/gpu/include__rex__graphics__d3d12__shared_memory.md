# Shared memory: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/shared_memory.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L43)

```text
// RequestRange may transition the buffer to copy destination - call it before
```

## Source note 2, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L44)

```text
// UseForReading or UseForWriting.
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L46)

```text
// Makes the buffer usable for vertices, indices and texture untiling.
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L48)

```text
// Vertex fetch is also allowed in pixel shaders.
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L53)

```text
// Makes the buffer usable for texture tiling after a resolve.
```

## Source note 6, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L57)

```text
// Makes the buffer usable as a source for copy commands.
```

## Source note 7, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L59)

```text
// Must be called when doing draws/dispatches modifying data within the shared
```

## Source note 8, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L60)

```text
// memory buffer as a UAV, to make sure that when UseForWriting is called the
```

## Source note 9, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L61)

```text
// next time, a UAV barrier will be done, and subsequent overlapping UAV
```

## Source note 10, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L62)

```text
// writes and reads are ordered.
```

## Source note 11, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L71)

```text
// Due to the D3D12_REQ_BUFFER_RESOURCE_TEXEL_COUNT_2_TO_EXP limitation, the
```

## Source note 12, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L72)

```text
// smallest supported formats are 32-bit.
```

## Source note 13, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L87)

```text
// The 512 MB tiled buffer.
```

## Source note 14, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L95)

```text
// Non-shader-visible buffer descriptor heap for faster binding (via copying
```

## Source note 15, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L96)

```text
// rather than creation).
```

## Source note 16, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/shared_memory.h#L115)

```text
// namespace rex::graphics::d3d12
```
