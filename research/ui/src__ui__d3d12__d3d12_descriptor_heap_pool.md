# D3d12 descriptor heap pool: ui source notes

This record preserves technical and API notes moved from `src/ui/d3d12/d3d12_descriptor_heap_pool.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L47)

```text
// Reclaim all submitted pages.
```

## Source note 2, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L57)

```text
// Mark all pages as never used yet in the new timeline.
```

## Source note 3, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L66)

```text
// Not checking current_page_used_ != 0 because asking for 0 descriptors
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L67)

```text
// returns a valid heap also - but actually the new heap will be different now
```

## Source note 5, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L68)

```text
// and the old one must be unbound since it doesn't exist anymore.
```

## Source note 6, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L95)

```text
// If the last full update happened on the current page, a partial update is
```

## Source note 7, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L96)

```text
// possible.
```

## Source note 8, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L99)

```text
// Go to the next page if there's not enough free space on the current one,
```

## Source note 9, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L100)

```text
// or because the previous page may be outdated. In this case, a full update
```

## Source note 10, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L101)

```text
// is necessary.
```

## Source note 11, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L103)

```text
// Close the page that was current.
```

## Source note 12, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L119)

```text
// Create the page if needed (may be the first call for the page).
```

## Source note 13, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_descriptor_heap_pool.cpp#L145)

```text
// namespace rex::ui::d3d12
```
