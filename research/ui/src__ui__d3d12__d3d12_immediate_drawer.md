# D3d12 immediate drawer: ui source notes

This record preserves technical and API notes moved from `src/ui/d3d12/d3d12_immediate_drawer.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L26)

```text
// Generated with `xb buildshaders`.
```

## Source note 2, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L49)

```text
// Lifetime is not managed anymore, so don't keep the resource either.
```

## Source note 3, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L54)

```text
// Await GPU usage completion of all draws and texture uploads (which happen
```

## Source note 4, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L55)

```text
// before draws).
```

## Source note 5, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L61)

```text
// Texture resources and descriptors are owned and tracked by the immediate
```

## Source note 6, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L62)

```text
// drawer. Zombie texture objects are supported, but are meaningless.
```

## Source note 7, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L73)

```text
// Create the root signature.
```

## Source note 8, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L121)

```text
// Create the pipelines.
```

## Source note 9, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L169)

```text
// Create the samplers.
```

## Source note 10, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L182)

```text
// Nearest neighbor, clamp.
```

## Source note 11, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L193)

```text
// Bilinear, clamp.
```

## Source note 12, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L198)

```text
// Bilinear, repeat.
```

## Source note 13, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L205)

```text
// Nearest neighbor, repeat.
```

## Source note 14, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L211)

```text
// Create pools for draws.
```

## Source note 15, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L212)

```text
// A draw list's vertices go up in one request, so pages hold a large list:
```

## Source note 16, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L213)

```text
// 2 MiB (the default) is about 105,000 vertices, which the Xbox guide's
```

## Source note 17, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L214)

```text
// gradients can pass.
```

## Source note 18, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L219)

```text
// Reset the current state.
```

## Source note 19, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L249)

```text
// Create and fill the upload buffer.
```

## Source note 20, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L279)

```text
// Defer uploading and transition to the next draw.
```

## Source note 21, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L280)

```text
// While the upload has not been yet completed, keep a reference to the
```

## Source note 22, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L281)

```text
// resource because its lifetime is not tied to that of the
```

## Source note 23, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L282)

```text
// ImmediateTexture (and thus to context's submissions) now.
```

## Source note 24, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L311)

```text
// Manage by this immediate drawer if successfully created a resource.
```

## Source note 25, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L329)

```text
// Update the submission index to be used throughout the current immediate
```

## Source note 26, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L330)

```text
// drawer paint.
```

## Source note 27, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L334)

```text
// Release deleted textures.
```

## Source note 28, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L346)

```text
// Release upload buffers for completed texture uploads.
```

## Source note 29, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L356)

```text
// Make sure textures created before the current frame are uploaded, even if
```

## Source note 30, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L357)

```text
// nothing was drawn in the previous frames or nothing will be drawn in the
```

## Source note 31, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L358)

```text
// current or subsequent ones, as that would result in upload buffers kept
```

## Source note 32, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L359)

```text
// forever.
```

## Source note 33, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L365)

```text
// Begin drawing.
```

## Source note 34, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L404)

```text
// Bind the vertices.
```

## Source note 35, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L419)

```text
// Bind the indices.
```

## Source note 36, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L442)

```text
// Could be an error while obtaining the vertex and index buffers.
```

## Source note 37, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L450)

```text
// Set the scissor rectangle.
```

## Source note 38, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L453)

```text
// Nothing is visible (zero area is used as the default current_scissor_
```

## Source note 39, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L454)

```text
// value also).
```

## Source note 40, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L468)

```text
// Ensure texture data is available if any texture is loaded, upload all in a
```

## Source note 41, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L469)

```text
// batch, then transition all at once.
```

## Source note 42, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L472)

```text
// Bind the texture. If this is the first draw in a frame, the descriptor heap
```

## Source note 43, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L473)

```text
// index will be invalid initially, and the texture will be bound regardless
```

## Source note 44, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L474)

```text
// of what's in current_texture_.
```

## Source note 45, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L504)

```text
// No texture, solid color.
```

## Source note 46, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L525)

```text
// Bind the sampler. If the resource doesn't exist (solid color drawing), use
```

## Source note 47, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L526)

```text
// nearest-neighbor and clamp so fetching is simpler.
```

## Source note 48, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L536)

```text
// Set the primitive type and the pipeline for it.
```

## Source note 49, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L558)

```text
// Draw.
```

## Source note 50, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L577)

```text
// Leaving the presenter's submission timeline - await GPU usage completion of
```

## Source note 51, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L578)

```text
// all draws and texture uploads (which happen before draws) and reset
```

## Source note 52, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L579)

```text
// submission indices.
```

## Source note 53, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L597)

```text
// Remove from the texture list.
```

## Source note 54, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L605)

```text
// Queue for delayed release.
```

## Source note 55, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L615)

```text
// Called often - don't initialize anything.
```

## Source note 56, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L624)

```text
// Copy all at once, then transition all at once (not interleaving copying and
```

## Source note 57, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L625)

```text
// pipeline barriers).
```

## Source note 58, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/d3d12/d3d12_immediate_drawer.cpp#L658)

```text
// namespace rex::ui::d3d12
```
