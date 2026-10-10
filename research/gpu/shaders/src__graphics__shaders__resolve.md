# Resolve: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/resolve.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L29)

```text
// xe::gpu::draw_util::ResolveEdramInfo.
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L31)

```text
// xe::gpu::draw_util::ResolveCoordinateInfo.
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L34)

```text
// Sanitized RB_COPY_DEST_INFO.
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L36)

```text
// xe::gpu::draw_util::ResolveCopyDestCoordinateInfo.
```

## Source note 5, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L64)

```text
// Always false for non-one-to-one resolve.
```

## Source note 6, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L183)

```text
// Offset of the beginning of the odd R32G32/R32G32B32A32 store address from
```

## Source note 7, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L184)

```text
// the address of the even store.
```

## Source note 8, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L215)

```text
// Int address of the first needed sample for non-averaging copies.
```

## Source note 9, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L216)

```text
// Horizontally adjacent pixels of a multisampled source don't have a fixed
```

## Source note 10, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L217)

```text
// address stride in the sample layout (see XeEdramOffsetInts), thus each
```

## Source note 11, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L218)

```text
// pixel computes its own address.
```

## Source note 12, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L233)

```text
// Int address for a given pixel and sample pair, per pixel for the same
```

## Source note 13, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L234)

```text
// reason as above.
```

## Source note 14, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L248)

```text
// Not using arrays for multi-pixel function arguments because indexable temps
```

## Source note 15, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L249)

```text
// are generated for them by FXC, that may be compiled unoptimally by the host
```

## Source note 16, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L250)

```text
// GPU driver.
```

## Source note 17, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L280)

```text
// Treat as 32_FLOAT.
```

## Source note 18, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L326)

```text
// Treat as 32_FLOAT.
```

## Source note 19, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L335)

```text
// L8 and A8 both use GPUTEXTUREFORMAT_8 (XGCopySurface, the software copy,
```

## Source note 20, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L336)

```text
// combines the source swizzle with the inverse destination one). Resolve
```

## Source note 21, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L337)

```text
// maps L8 to LOW_RED and A8 to LOW_BLUE, so for k_8 destinations the swap
```

## Source note 22, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L338)

```text
// selects alpha rather than blue; titles resolve opacity planes from the
```

## Source note 23, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L339)

```text
// alpha of 8_8_8_8_GAMMA targets this way (xenia-canary 2b3f0cb456).
```

## Source note 24, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L357)

```text
// 2-bit unsigned repeating fraction alpha, also with 7e3 RGB.
```

## Source note 25, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L376)

```text
// Missing alpha is 1.0 before MSAA averaging and exponent bias.
```

## Source note 26, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L400)

```text
// Treat as 32_FLOAT.
```

## Source note 27, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L427)

```text
// Treat as 32_32_FLOAT.
```

## Source note 28, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L456)

```text
// Treat as 32_32_FLOAT.
```

## Source note 29, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L465)

```text
// The caller selects the second dword for blue or alpha. Alpha is the high
```

## Source note 30, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L466)

```text
// half of it in the 16-bit component formats.
```

## Source note 31, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L499)

```text
// Treat as 32_32_FLOAT.
```

## Source note 32, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L501)

```text
// Missing alpha is 1.0 before MSAA averaging and exponent bias.
```

## Source note 33, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L568)

```text
// For blue or alpha from 64bpp, pre-add 1 to the addresses.
```

## Source note 34, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L627)

```text
// 8_8_8_8_GAMMA stores 10-bit linear color through the 8-bit PWL curve
```

## Source note 35, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L628)

```text
// (host sRGB isn't a substitute). Hardware resolve decodes it to linear
```

## Source note 36, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L629)

```text
// before MSAA averaging and format conversion, and every destination gets
```

## Source note 37, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L630)

```text
// the linear values: a title keeping the encoded bytes re-aliases the
```

## Source note 38, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L631)

```text
// surface as 8_8_8_8 before resolving. Averaging the encoded bytes left
```

## Source note 39, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L632)

```text
// titles overexposed (xenia-canary d119505289, 2ddc5ef737, fc48d37cdc).
```

## Source note 40, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L671)

```text
// RGB only: 8_8_8_8_GAMMA alpha is ordinary fixed data.
```

## Source note 41, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L681)

```text
// Samples averaged for kXenosCopySampleSelect_01/_23/_0123: the first
```

## Source note 42, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L682)

```text
// sample and first | 1 (the horizontal neighbor), then 2 and 3.
```

## Source note 43, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L870)

```text
// D3D maps A8 to k_8 with LOW_BLUE. k_8_A and k_8_B are still unknown,
```

## Source note 44, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L871)

```text
// so they keep the red/blue swap.
```

## Source note 45, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L875)

```text
// The second dword of each 64bpp pixel holds blue and alpha.
```

## Source note 46, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve.xesli#L879)

```text
// The PWL encoding only covers RGB.
```
