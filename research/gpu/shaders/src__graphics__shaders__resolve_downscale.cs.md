# Resolve downscale.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/resolve_downscale.cs.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L10)

```text
// Downscales scaled resolve buffer data back to 1x resolution, for CPU readback
```

## Source note 2, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L11)

```text
// and for resolves written at the guest's size (ADR-012). One thread group
```

## Source note 3, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L12)

```text
// processes one 32x32 tile of the written extent; each thread produces output
```

## Source note 4, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L13)

```text
// dwords. Keeps the top-left host texel of each scale_x * scale_y block, or its
```

## Source note 5, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L14)

```text
// (scale/2, scale/2) center, or the average of all of them byte by byte (exact
```

## Source note 6, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L15)

```text
// for formats of 8-bit channels, whatever their endian swap), per
```

## Source note 7, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L16)

```text
// xe_downscale_mode.
```

## Source note 8, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L18)

```text
// The source is not a flat scale_x * scale_y expansion of each guest texel.
```

## Source note 9, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L19)

```text
// The resolve shaders in this repository are xenia-canary's from 0b2ffa314
```

## Source note 10, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L20)

```text
// (2025-08-20), which scale Nx1 units of horizontally consecutive guest blocks
```

## Source note 11, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L21)

```text
// (XeTextureScaledTiledOffset in that revision's texture_address.xesli):
```

## Source note 12, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L22)

```text
// - 1bpp and 2bpp - 8 blocks, 4bpp - 4, 8bpp - 2, 16bpp - 1.
```

## Source note 13, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L23)

```text
// A guest unit at guest address A occupies scale_x * scale_y host sub-units of
```

## Source note 14, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L24)

```text
// the same size at A * scale_x * scale_y, ordered column-major. This shader
```

## Source note 15, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L25)

```text
// reverses that per guest unit. Canary a635ac64f reads the group layout that
```

## Source note 16, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L26)

```text
// Canary introduced in 0f23f0568 instead, which doesn't match these shaders.
```

## Source note 17, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L28)

```text
// The source view starts at the written extent's scaled address, and the
```

## Source note 18, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L29)

```text
// extent is limited in dwords, so extents ending inside a tile are complete.
```

## Source note 19, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L32)

```text
// 1 to kMaxDrawResolutionScaleAlongAxis
```

## Source note 20, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L33)

```text
// 1 to kMaxDrawResolutionScaleAlongAxis
```

## Source note 21, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L34)

```text
// 0=8bit, 1=16bit, 2=32bit, 3=64bit
```

## Source note 22, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L35)

```text
// Number of 1x dwords to write; the last 32x32 tile may be partial.
```

## Source note 23, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L37)

```text
// 0: the (0, 0) host texel of each scaled block; 1: (scale/2, scale/2);
```

## Source note 24, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L38)

```text
// 2: the average of the block, per byte.
```

## Source note 25, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L45)

```text
// Scaled-buffer byte of the chosen host sample of the guest block at byte
```

## Source note 26, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L46)

```text
// offset rel_bytes from the start of the written extent.
```

## Source note 27, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L53)

```text
// Shift first, then mask: fxc compiles the mask-then-shift form into a ubfe
```

## Source note 28, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L54)

```text
// whose width wrongly includes the shift for non-zero pixel_size_log2.
```

## Source note 29, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L65)

```text
// 128 threads per group; a tile has 256..2048 output dwords depending on the
```

## Source note 30, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L66)

```text
// pixel size, so each thread strides over several of them.
```

## Source note 31, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L73)

```text
// Number of output dwords in a 1x tile (256, 512, 1024 or 2048).
```

## Source note 32, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L81)

```text
// Host sample to keep within each block: top-left, or center when requested.
```

## Source note 33, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L90)

```text
// Average: every output byte is the rounded mean of that byte of every
```

## Source note 34, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L91)

```text
// host texel of its block.
```

## Source note 35, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L125)

```text
// 32bpp: one texel per output dword. 64bpp: a texel's two dwords are
```

## Source note 36, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L126)

```text
// consecutive in its host sub-unit too.
```

## Source note 37, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_downscale.cs.hlsl#L133)

```text
// 8bpp/16bpp: consecutive texels packed into one output dword.
```
