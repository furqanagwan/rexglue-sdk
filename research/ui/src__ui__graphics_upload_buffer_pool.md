# Graphics upload buffer pool: ui source notes

This record preserves technical and API notes moved from `src/ui/graphics_upload_buffer_pool.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L45)

```text
// Reclaim all submitted pages.
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L55)

```text
// Mark all pages as never used yet in the new timeline.
```

## Source note 3, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L64)

```text
// Called from the destructor - must not call virtual functions here.
```

## Source note 4, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L107)

```text
// Start a new page if can't fit all the bytes or don't have an open page.
```

## Source note 5, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L109)

```text
// Close the page that was current.
```

## Source note 6, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L124)

```text
// Create a new page if none available.
```

## Source note 7, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L127)

```text
// Failed to create.
```

## Source note 8, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L133)

```text
// After CreatePageImplementation (more specifically, the first successful
```

## Source note 9, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/graphics_upload_buffer_pool.cpp#L134)

```text
// call), page_size_ may grow - but this doesn't matter here.
```
