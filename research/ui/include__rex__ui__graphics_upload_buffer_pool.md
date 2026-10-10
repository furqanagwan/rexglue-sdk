# Graphics upload buffer pool: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/graphics_upload_buffer_pool.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L23)

```text
// Submission index is the fence value or a value derived from it (if reclaiming
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L24)

```text
// less often than once per fence value, for instance).
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L28)

```text
// Taken from the Direct3D 12 MiniEngine sample (LinearAllocator
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L29)

```text
// kCpuAllocatorPageSize). Large enough for most cases.
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L38)

```text
// Should be called before submitting anything using this pool, unless the
```

## Source note 6, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L39)

```text
// implementation doesn't require explicit flushing.
```

## Source note 7, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L43)

```text
// Extended by the implementation.
```

## Source note 8, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L52)

```text
// Request to write data in a single piece, creating a new page if the current
```

## Source note 9, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L53)

```text
// one doesn't have enough free space.
```

## Source note 10, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L55)

```text
// Request to write data in multiple parts, filling the buffer entirely.
```

## Source note 11, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L63)

```text
// May be increased by the implementation on creation or on first allocation
```

## Source note 12, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L64)

```text
// to avoid wasting space if the real allocation turns out to be bigger than
```

## Source note 13, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L65)

```text
// the specified page size.
```

## Source note 14, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L68)

```text
// A list of buffers with free space, with the first buffer being the one
```

## Source note 15, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L69)

```text
// currently being filled.
```

## Source note 16, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L72)

```text
// A list of full buffers that can be reclaimed when the GPU doesn't use them
```

## Source note 17, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_upload_buffer_pool.h#L73)

```text
// anymore.
```
