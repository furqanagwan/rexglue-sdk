# Texture layout test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/texture_layout_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L33)

```text
// Expected offsets follow D3D's FindTextureSize: a mip level of an N-slice 2D
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L34)

```text
// array is padded to align(N, 4) slices, and a 3D mip's slice count comes from
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L35)

```text
// the level's own depth, not the base depth. Source: xenia-canary #1243.
```

## Source note 4, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L39)

```text
// Level 1 and 2 are both one 32x32 k_8_8_8_8 tile (4 KB) per slice.
```

## Source note 5, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L45)

```text
// A single slice isn't an array and a cube keeps its six faces.
```

## Source note 6, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L56)

```text
// Level 1 is 32x32x8, level 2 is 16x16x4 padded to 32x32x4.
```

## Source note 7, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L65)

```text
// 96bpp: 256 / 12 < 32, so a 32 texel row is 32 * 12 bytes, not 512.
```

## Source note 8, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L70)

```text
// 8bpp and 32bpp still pad to 256 bytes, 128bpp to 32 blocks.
```

## Source note 9, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L82)

```text
// 32x32x256: level 6 is 1x1x4 in the packed tail. D3D places it at
```

## Source note 10, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L83)

```text
// Z = (log2(depth) - level) * 4 = 8.
```

## Source note 11, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L90)

```text
// Independent oracle: every texel's address comes from the per-texel tiling
```

## Source note 12, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L91)

```text
// function, and the bounds must contain all of them.
```

## Source note 13, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L105)

```text
// 2D.
```

## Source note 14, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L123)

```text
// 3D, including the odd Z/4 groups.
```

## Source note 15, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L140)

```text
// For a whole 32x32x4 tile the lower bound is also tight.
```

## Source note 16, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L163)

```text
// xenia-canary #1249: when level 0 is the packed tail, D3D leaves the mip
```

## Source note 17, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L164)

```text
// address 0 and keeps the rest of the tail at the base address.
```

## Source note 18, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L180)

```text
// A base level above the tail with no mips still has none.
```

## Source note 19, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L191)

```text
// 8x8x9 k_8_8_8_8: one 32x32 tile (4 KB) per slice; the tail's depth is
```

## Source note 20, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L192)

```text
// next_pow2(9) = 16, not 9 rounded to 12.
```

## Source note 21, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L202)

```text
// xenia-canary #1249: the 3D upper bound is the last block's end exactly,
```

## Source note 22, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/texture_layout_test.cpp#L203)

```text
// where the closed form it replaced reached up to a page further.
```
