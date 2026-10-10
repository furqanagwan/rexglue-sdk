# D3d12 upload buffer pool: ui source notes

This record preserves technical and API notes moved from `src/ui/d3d12/d3d12_upload_buffer_pool.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_upload_buffer_pool.cpp#L19)

```text
// Align to D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT not to waste any space if
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_upload_buffer_pool.cpp#L20)

```text
// it's smaller (the size of the heap backing the buffer will be aligned to
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_upload_buffer_pool.cpp#L21)

```text
// D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT anyway).
```

## Source note 4, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_upload_buffer_pool.cpp#L92)

```text
// Unmapping will be done implicitly when the resource is destroyed.
```

## Source note 5, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_upload_buffer_pool.cpp#L101)

```text
// namespace rex::ui::d3d12
```
