# Edram: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/edram.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L19)

```text
// `wrap = false` can be used if it's known that the resulting tile indices
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L20)

```text
// can't exceed 11 bits, and the modulo operator doesn't need to be performed to
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L21)

```text
// access the data in the render targets that are located in both ends of the
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L22)

```text
// EDRAM at the same time.
```

## Source note 5, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L27)

```text
// Map the pixel and its sample index to canonical sample coordinates
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L28)

```text
// (xenia-canary #1163). Views with 1x/2x/4x samples of a single EDRAM
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L29)

```text
// allocation have the same physical samples, just arranged differently in
```

## Source note 8, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L30)

```text
// 4x4 sample blocks. This function, ownership transfer shaders, render target
```

## Source note 9, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L31)

```text
// dumping shaders, and the interlock output code use the following equations.
```

## Source note 10, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L33)

```text
// u and v as the sample coordinates in the single sampled view:
```

## Source note 11, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L34)

```text
// 4x: u = ((x & ~1) << 1) | (x & 1) | ((s & 1) << 1)
```

## Source note 12, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L35)

```text
//     v = ((y & ~1) << 1) | (y & 1) | (s & 2)
```

## Source note 13, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L36)

```text
// 2x: u = (x & ~2) | (s << 1)
```

## Source note 14, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L37)

```text
//     v = ((y & ~1) << 1) | (y & 1) | (x & 2)
```

## Source note 15, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L39)

```text
// The bit 0 of 4x sample index is horizontal, and bit 1 is vertical, and
```

## Source note 16, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L40)

```text
// 2x sample 0 is the top one. Some properties of the above equations used by
```

## Source note 17, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L41)

```text
// the layout's users include:
```

## Source note 18, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L42)

```text
// - The offsets of the other samples of a pixel from its sample 0 are
```

## Source note 19, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L43)

```text
//   constant, +2 sample columns for the horizontal (or the only 2x) sample
```

## Source note 20, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L44)

```text
//   bit and +2 sample rows for the vertical one.
```

## Source note 21, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L45)

```text
// - A 64bpp sample is two horizontally adjacent 32bpp sample columns, so a
```

## Source note 22, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L46)

```text
//   32bpp view of a 64bpp allocation has u = 2 * u_64bpp + half, and both
```

## Source note 23, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L47)

```text
//   halves decode to the same sample of two horizontally adjacent pixels in a
```

## Source note 24, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L48)

```text
//   view of any sample count.
```

## Source note 25, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L49)

```text
// - Horizontally adjacent pixels of a multisampled view have no constant
```

## Source note 26, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L50)

```text
//   address stride, the pixel and sample bits are interleaved.
```

## Source note 27, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L52)

```text
// Titles use the layout when purposedly aliasing memory, such as 5841125E
```

## Source note 28, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L53)

```text
// drawing half-res 4x particles over full-res scenes with swizzle shaders
```

## Source note 29, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L54)

```text
// designed around it and resolve downscaling relying on this sample grouping.
```

## Source note 30, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L56)

```text
// With resolution scaling, the rearrangement is carried out at guest pixel
```

## Source note 31, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L57)

```text
// granularity, while the host subpixel offset is carried along unchanged.
```

## Source note 32, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L72)

```text
// For now, while the actual storage of 64bpp render targets in comparison to
```

## Source note 33, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L73)

```text
// 32bpp is not known, storing 40x16 64bpp samples per tile for simplicity of
```

## Source note 34, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L74)

```text
// addressing in different scenarios.
```

## Source note 35, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/edram.xesli#L93)

```text
// EDRAM addressing is periodic (modulo the EDRAM size).
```
