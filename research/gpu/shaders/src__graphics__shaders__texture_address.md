# Texture address: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_address.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L16)

```text
// https://github.com/gildor2/UModel/blob/de8fbd3bc922427ea056b7340202dcdcc19ccff5/Unreal/UnTexture.cpp#L489
```

## Source note 2, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L17)

```text
// Top bits of coordinates.
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L20)

```text
// Lower bits of coordinates (result is 6-bit value).
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L22)

```text
// Mix micro/macro + add few remaining x/y bits.
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L24)

```text
// Mix bits again.
```

## Source note 6, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L25)

```text
// Upper bits (offset bits [*-9]).
```

## Source note 7, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L26)

```text
// Next 1 bit.
```

## Source note 8, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L27)

```text
// Next 3 bits (offset bits [8-6]).
```

## Source note 9, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L28)

```text
// Next 2 bits.
```

## Source note 10, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L29)

```text
// Lower 6 bits (offset bits [5-0]).
```

## Source note 11, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L34)

```text
// Reconstructed from disassembly of XGRAPHICS::TileVolume.
```

## Source note 12, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L54)

```text
// Log2 of the number of blocks always laid out consecutively in memory along
```

## Source note 13, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L55)

```text
// the horizontal axis.
```

## Source note 14, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L57)

```text
// 1bpb and 2bpb - 8.
```

## Source note 15, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L58)

```text
// 4bpb - 4.
```

## Source note 16, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L59)

```text
// 8bpb - 2.
```

## Source note 17, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L60)

```text
// 16bpb - 1.
```

## Source note 18, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L64)

```text
// Odd sequences of consecutive blocks along the horizontal axis are placed at a
```

## Source note 19, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L65)

```text
// fixed offset in memory from the preceding even ones. Returns the distance
```

## Source note 20, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L66)

```text
// between the beginnings of the even and its corresponding odd sequences.
```

## Source note 21, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L71)

```text
// For shaders to be able to copy multiple horizontally adjacent pixels in the
```

## Source note 22, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L72)

```text
// same way regardless of the resolution scale chosen, scaling is done at Nx1
```

## Source note 23, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L73)

```text
// granularity where N matches the number of pixels that are consecutive with
```

## Source note 24, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L74)

```text
// guest tiling, rather than within individual guest pixels:
```

## Source note 25, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L75)

```text
// - 1bpp - 8x1 host pixels (can copy via R32G32_UINT)
```

## Source note 26, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L76)

```text
// - 2bpp - 8x1 host pixels (can copy via R32G32B32A32_UINT)
```

## Source note 27, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L77)

```text
// - 4bpp - 4x1 host pixels
```

## Source note 28, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L78)

```text
// - 8bpp - 2x1 host pixels
```

## Source note 29, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L79)

```text
// - 16bpp - 1x1 host pixels
```

## Source note 30, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L80)

```text
// For better access locality, because compute shaders in Xenia usually have 2D
```

## Source note 31, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L81)

```text
// thread groups, host Nx1 sub-units are scaled within guest Nx1 units in a
```

## Source note 32, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L82)

```text
// column-major way.
```

## Source note 33, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L83)

```text
// So, for example, in a 2bpp texture with 2x2 resolution scale, 16 guest bytes,
```

## Source note 34, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L84)

```text
// or 64 host bytes, contain:
```

## Source note 35, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L85)

```text
// - 16 host bytes - 8x1 top-left portion
```

## Source note 36, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L86)

```text
// - 16 host bytes - 8x1 bottom-left portion
```

## Source note 37, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L87)

```text
// - 16 host bytes - 8x1 top-right portion
```

## Source note 38, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L88)

```text
// - 16 host bytes - 8x1 bottom-right portion
```

## Source note 39, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L89)

```text
// This function is used only for non-negative positions within a texture, so
```

## Source note 40, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L90)

```text
// for simplicity, especially of the division involved, assuming everything is
```

## Source note 41, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L91)

```text
// unsigned.
```

## Source note 42, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L96)

```text
// Global host X coordinate in host Nx1 sub-units.
```

## Source note 43, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L98)

```text
// Global guest XY coordinate in guest Nx1 units.
```

## Source note 44, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L100)

```text
// Global guest XYZ coordinate of the beginning of the Nx1 unit.
```

## Source note 45, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L103)

```text
// Global guest linear address of the beginning of Nx1 unit in bytes.
```

## Source note 46, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L114)

```text
// Unit-local host XY index of the host Nx1 sub-unit.
```

## Source note 47, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L115)

```text
// Also see XeTextureScaledRightSubUnitOffsetInConsecutivePair for common
```

## Source note 48, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L116)

```text
// subexpression elimination information as this remainder calculation is done
```

## Source note 49, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L117)

```text
// there too.
```

## Source note 50, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L120)

```text
// - Guest global unit address.
```

## Source note 51, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L121)

```text
// - Host unit-local sub-unit index.
```

## Source note 52, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L122)

```text
// - Host pixel within a sub-unit (if the offset is requested at a smaller
```

## Source note 53, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L123)

```text
//   granularity than a whole sub-unit).
```

## Source note 54, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L130)

```text
// Offset of the beginning of next host sub-unit along the horizontal axis
```

## Source note 55, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L131)

```text
// within a pair of guest units.
```

## Source note 56, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L132)

```text
// x must be a multiple of 1 << (XeTextureTiledConsecutiveBlocksLog2 + 1) - to
```

## Source note 57, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L133)

```text
// go from one pair of consecutive blocks to another, full tiled offset
```

## Source note 58, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L134)

```text
// recalculation is required.
```

## Source note 59, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L143)

```text
// While % can be used here to take the modulo, for better common
```

## Source note 60, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L144)

```text
// subexpression elimination between this function and
```

## Source note 61, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L145)

```text
// XeTextureScaledTiledOffset when both are used, taking the remainder the
```

## Source note 62, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L146)

```text
// same way.
```

## Source note 63, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L150)

```text
// The next host sub-unit is in the other, odd guest unit.
```

## Source note 64, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L154)

```text
// The next host sub-unit is in the same guest unit.
```

## Source note 65, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_address.xesli#L160)

```text
// The layout of sub-units within one unit is column-major.
```
