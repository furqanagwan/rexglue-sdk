# Shared memory: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/shared_memory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L67)

```text
// As of October 8th, 2018, PIX doesn't support tiled buffers.
```

## Source note 2, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L149)

```text
// First free the buffer to detach it from the heaps.
```

## Source note 3, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L157)

```text
// If calling from the destructor, the SharedMemory destructor will call
```

## Source note 4, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L158)

```text
// ShutdownCommon.
```

## Source note 5, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L175)

```text
// ExecuteCommandLists is a full UAV barrier.
```

## Source note 6, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L189)

```text
// "UAV -> anything" transition commits the writes implicitly.
```

## Source note 7, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/shared_memory.cpp#L341)

```text
// namespace rex::graphics::d3d12
```
