# Zpd query pool: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/zpd_query_pool.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L41)

```text
// Not D3D12_HEAP_FLAG_CREATE_NOT_ZEROED: this one must start zeroed.
```

## Source note 2, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L158)

```text
// CPU never writes to this READBACK buffer - empty written range.
```

## Source note 3, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L190)

```text
// Bump the generation. Any in-flight readbacks for the slot's previous
```

## Source note 4, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L191)

```text
// occupants are ignored.
```

## Source note 5, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L201)

```text
// Bump generation so a second release with the same generation is rejected.
```

## Source note 6, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L261)

```text
// The transition also orders the reset after the atomics of the query that
```

## Source note 7, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L262)

```text
// last owned this slot.
```

## Source note 8, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L267)

```text
// And the atomics of this query after the reset.
```

## Source note 9, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L283)

```text
// Out of UNORDERED_ACCESS orders the copy after the pixel shaders' atomics.
```

## Source note 10, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L300)

```text
// Sorts the indices and coalesces contiguous runs into resolve_batch_ranges_.
```

## Source note 11, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L339)

```text
// State is per resource, so the whole buffer goes to COPY_SOURCE for the
```

## Source note 12, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L340)

```text
// copies and back to UNORDERED_ACCESS for draws still counting.
```

## Source note 13, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/zpd_query_pool.cpp#L372)

```text
// namespace rex::graphics::d3d12
```
