# Texture load: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L16)

```text
// 128 threads per group (the maximum wave size supported by DXIL and SPIR-V,
```

## Source note 2, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L17)

```text
// and the minimum required number of threads per group on Vulkan), laid out as
```

## Source note 3, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L18)

```text
// 4x32 (32 texels along Y per group - one guest tile) - starting with 64x32
```

## Source note 4, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L19)

```text
// blocks (2x1 guest tiles) per group for 8bpb / 16bpb, and smaller for larger
```

## Source note 5, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L20)

```text
// block sizes. Since the mip tail is packed in 32x / x32 storage, there's no
```

## Source note 6, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L21)

```text
// need for the Y group size smaller than 32 - 8x16, for instance, would result
```

## Source note 7, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L22)

```text
// in 128x16 blocks per group for 8bpb / 16bpb, and for a 32x32 mip tail, there
```

## Source note 8, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L23)

```text
// would be two groups rather than one, for a total of 128x32 blocks - 75% of
```

## Source note 9, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L24)

```text
// the work will be wasted rather than 50% with one 64x32-block group.
```

## Source note 10, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L31)

```text
// Base offset in bytes, resolution-scaled.
```

## Source note 11, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L33)

```text
// For tiled textures - row pitch in guest blocks, aligned to 32, unscaled.
```

## Source note 12, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L34)

```text
// For linear textures - row pitch in bytes.
```

## Source note 13, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L36)

```text
// For 3D textures only (ignored otherwise) - aligned to 32, unscaled.
```

## Source note 14, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L39)

```text
// - std140 vector boundary -
```

## Source note 15, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L41)

```text
// If this is a packed mip tail, this is aligned to tile dimensions.
```

## Source note 16, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L42)

```text
// Resolution-scaled.
```

## Source note 17, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L44)

```text
// Base offset in bytes.
```

## Source note 18, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L47)

```text
// - std140 vector boundary -
```

## Source note 19, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L74)

```text
// Only resolved textures can be resolution-scaled, and resolving is only
```

## Source note 20, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L75)

```text
// possible to a tiled destination.
```

## Source note 21, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L100)

```text
// bpb and bpb_log2 are separate because bpb may be not a power of 2 (like 96).
```

## Source note 22, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L105)

```text
// Only resolved textures can be resolution-scaled, and resolving is only
```

## Source note 23, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L106)

```text
// possible to a tiled destination.
```

## Source note 24, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L133)

```text
// Offset of the beginning of the odd R32G32/R32G32B32A32 load address from the
```

## Source note 25, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load.xesli#L134)

```text
// address of the even load, for power-of-two-sized textures.
```
