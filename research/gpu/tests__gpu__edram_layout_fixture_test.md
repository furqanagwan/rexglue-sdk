# Edram layout fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/edram_layout_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L33)

```text
// Draws one pixel at a time with its own constant color, so every pixel of the
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L34)

```text
// region (0, 0)-(width, height) holds a distinct value regardless of how the
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L35)

```text
// rasterizer treats the edges.
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L46)

```text
// A distinct 32bpp value per 1x pixel of a 16x16 region.
```

## Source note 5, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L55)

```text
// Canary #1163's canonical layout: the 1x pixel holding sample `s` of the
```

## Source note 6, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L56)

```text
// MSAA pixel (x, y) at the same EDRAM address (XeEdramOffsetBytes).
```

## Source note 7, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L66)

```text
// Canary #1163: MSAA samples of a pixel are spread over 4x4 blocks of the 1x
```

## Source note 8, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L67)

```text
// view of the same EDRAM, so a 1x target re-aliased as MSAA (and back) sees the
```

## Source note 9, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L68)

```text
// console's arrangement. 8x8-aligned clears can't show this; one draw per
```

## Source note 10, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L69)

```text
// pixel gives every 1x pixel a distinct value.
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L78)

```text
// Otherwise draws are dropped while their pipelines compile.
```

## Source note 12, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L89)

```text
// The MSAA alias of the same EDRAM rows: 2x halves the height, 4x also the
```

## Source note 13, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L90)

```text
// width (the pitch is in samples either way).
```

## Source note 14, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L139)

```text
// Otherwise draws are dropped while their pipelines compile.
```

## Source note 15, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L144)

```text
// Every sample of an MSAA pixel gets the pixel's color.
```

## Source note 16, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L185)

```text
// Canary #1222 (title 4D530A26): a color target aliasing the depth buffer's
```

## Source note 17, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L186)

```text
// EDRAM base that writes only the stencil byte (red of k_8_8_8_8 over D24S8)
```

## Source note 18, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L187)

```text
// must not disable a read-only depth test, and the depth bits must survive.
```

## Source note 19, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L197)

```text
// Depth tiles store their 40-sample halves swapped relative to color, so a
```

## Source note 20, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L198)

```text
// whole 80-sample tile row covers both the color and the depth bits.
```

## Source note 21, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L201)

```text
// Depth 0.5 everywhere, no color writes.
```

## Source note 22, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L213)

```text
// Red only, depth test less without writes: the left half (z 0.25) passes,
```

## Source note 23, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L214)

```text
// the right half (z 0.75) fails.
```

## Source note 24, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L252)

```text
// Canary #1238: when a float24 depth target is transferred back into after an
```

## Source note 25, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L253)

```text
// alias, the host depth store saves its float32 depth per sample in the layout
```

## Source note 26, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L254)

```text
// the transfer shader reads it with. A wrong layout loses the host precision,
```

## Source note 27, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L255)

```text
// so redrawing the same geometry with an equal depth test fails.
```

## Source note 28, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L269)

```text
// 80 samples, a whole tile row, for both halves of the depth tile.
```

## Source note 29, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L271)

```text
// A color target far from the depth one to record the equal test.
```

## Source note 30, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L285)

```text
// A color draw over the depth range makes the color target its owner. It
```

## Source note 31, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L286)

```text
// writes only the stencil byte, so the EDRAM depth bits still match the
```

## Source note 32, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L287)

```text
// host depth when the range goes back to the depth target.
```

## Source note 33, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L315)

```text
// Canary #1163: a 64bpp sample is two horizontally adjacent 32bpp sample
```

## Source note 34, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L316)

```text
// columns, u = 2 * u_64bpp + half, for any sample count of the 64bpp view.
```

## Source note 35, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/edram_layout_fixture_test.cpp#L329)

```text
// 40 64bpp samples (a tile row), 80 32bpp ones in the 1x alias.
```
