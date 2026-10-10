# Shared memory: graphics source notes

This record preserves technical and API notes moved from `src/graphics/shared_memory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L53)

```text
// No watches now, so no references to the pools accessible by guest threads -
```

## Source note 2, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L54)

```text
// safe not to enter the global critical region.
```

## Source note 3, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L103)

```text
// Pages that are valid only because the CPU uploaded them lose their valid
```

## Source note 4, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L104)

```text
// bit here, so the next frame re-reads them from guest memory.
```

## Source note 5, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L109)

```text
// Keeping GPU-written data, so "invalidated by GPU".
```

## Source note 6, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L111)

```text
// No watches now, so no references to the pools accessible by guest threads -
```

## Source note 7, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L112)

```text
// safe not to enter the global critical region.
```

## Source note 8, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L171)

```text
// Allocate the range.
```

## Source note 9, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L189)

```text
// Allocate and link the nodes.
```

## Source note 10, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L234)

```text
// Fire global watches.
```

## Source note 11, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L240)

```text
// Fire per-range watches.
```

## Source note 12, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L245)

```text
// Store the next node now since when the callback is triggered, the links
```

## Source note 13, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L246)

```text
// will be broken.
```

## Source note 14, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L266)

```text
// Trigger modification callbacks so, for instance, resolved data is loaded to
```

## Source note 15, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L267)

```text
// the texture.
```

## Source note 16, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L270)

```text
// Mark the range as valid (so pages are not reuploaded until modified by the
```

## Source note 17, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L271)

```text
// CPU) and watch it so the CPU can reuse it and this will be caught.
```

## Source note 18, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L345)

```text
// Some texture or buffer is empty, for example - safe to draw in this case.
```

## Source note 19, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L416)

```text
// Consider pages in the block outside the requested range valid.
```

## Source note 20, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L429)

```text
// Check if need to open a new range.
```

## Source note 21, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L435)

```text
// Check if need to close the range.
```

## Source note 22, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L436)

```text
// Ignore the valid pages before the beginning of the range.
```

## Source note 23, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L445)

```text
// In the next iteration within this block, consider this range
```

## Source note 24, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L446)

```text
// valid since it has been queued for upload.
```

## Source note 25, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L498)

```text
// Check if a somewhat wider range (up to 256 KB with 4 KB pages) can be
```

## Source note 26, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L499)

```text
// invalidated - if no GPU-written data nearby that was not intended to be
```

## Source note 27, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L500)

```text
// invalidated since it's not in sync with CPU memory and can't be
```

## Source note 28, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L501)

```text
// reuploaded. It's a lot cheaper to upload some excess data than to catch
```

## Source note 29, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L502)

```text
// access violations - with 4 KB callbacks, 58410824 (being a
```

## Source note 30, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L503)

```text
// software-rendered game) runs at 4 FPS on Intel Core i7-3770, with 64 KB,
```

## Source note 31, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L504)

```text
// the CPU game code takes 3 ms to run per frame, but with 256 KB, it's
```

## Source note 32, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/shared_memory.cpp#L505)

```text
// 0.7 ms.
```
