# Zpd query pool: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/zpd_query_pool.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L23)

```text
// namespace rex::ui::d3d12
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L29)

```text
// D3D12 occlusion query pool for ZPD reports. Queries live in ID3D12QueryHeap,
```

## Source note 3, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L30)

```text
// results are copied to a persistent readback buffer via ResolveQueryData.
```

## Source note 4, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L32)

```text
// D3D12 requires BeginQuery and EndQuery to be recorded in the same command
```

## Source note 5, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L33)

```text
// list, so segments split at EndSubmission.
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L35)

```text
// FlushResolveBatch coalesces pending indices into contiguous ranges to cut
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L36)

```text
// down on ResolveQueryData call count.
```

## Source note 8, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L38)

```text
// ROV queries (RG-GDK-010a) don't use D3D12 occlusion queries: the ROV pixel
```

## Source note 9, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L39)

```text
// shaders add their depth/stencil outcomes to a counter slot of four uint32
```

## Source note 10, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L40)

```text
// lanes (XenosZPDReport::Counter) with UAV atomics. ClearCounter zeroes the
```

## Source note 11, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L41)

```text
// slot when the query opens; a counter resolve copies it to a readback buffer.
```

## Source note 12, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L49)

```text
// `with_counter` also creates the ROV counter slots.
```

## Source note 13, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L70)

```text
// A raw UAV of the counter slots, or a null raw UAV without them.
```

## Source note 14, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L79)

```text
// `counter`: resolve the query's counter slot instead of its occlusion query.
```

## Source note 15, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L81)

```text
// Zeroes the slot, then leaves the buffer ready for the shaders' atomics.
```

## Source note 16, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L88)

```text
// VIZ predicates (xenia-canary #1111): SetPredication reads a buffer, so a
```

## Source note 17, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L89)

```text
// survey's count is staged into `dest` at `dest_offset` (8 bytes, the
```

## Source note 18, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L90)

```text
// destination in COPY_DEST). The occlusion query's sample count, after
```

## Source note 19, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L94)

```text
// The ROV counter slot's ZPass lane (the low dword only; the high one stays
```

## Source note 20, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L95)

```text
// as the destination has it):
```

## Source note 21, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L100)

```text
// A hybrid query resolves both the native query and the counter slot.
```

## Source note 22, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L109)

```text
// Buffers decay to COMMON when a submission finishes, so the tracked state
```

## Source note 23, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L110)

```text
// starts over for each submission.
```

## Source note 24, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L116)

```text
// Persistently mapped. Results readable once the fence signals.
```

## Source note 25, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L121)

```text
// One zeroed slot, the source of ClearCounter's copy. (The deferred command
```

## Source note 26, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L122)

```text
// list has no WriteBufferImmediate.)
```

## Source note 27, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L132)

```text
// Bumped on each acquire so stale readbacks from a recycled slot get dropped.
```

## Source note 28, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L137)

```text
// Reusable scratch for coalesced contiguous ranges during flush.
```

## Source note 29, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/zpd_query_pool.h#L141)

```text
// namespace rex::graphics::d3d12
```
