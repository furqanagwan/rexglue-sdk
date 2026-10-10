# Adaptive triangle.hs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/adaptive_triangle.hs.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L13)

```text
// Factors for adaptive tessellation are taken from the index buffer.
```

## Source note 2, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L15)

```text
// 1.0 added to the factors according to the images in
```

## Source note 3, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L16)

```text
// https://www.slideshare.net/blackdevilvikas/next-generation-graphics-programming-on-xbox-360
```

## Source note 4, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L17)

```text
// (fractional_even also requires a factor of at least 2.0), to the min/max it
```

## Source note 5, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L18)

```text
// has already been added on the CPU.
```

## Source note 6, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L20)

```text
// Fork phase.
```

## Source note 7, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L21)

```text
// It appears that on the Xbox 360:
```

## Source note 8, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L22)

```text
// - [0] is the factor for the v0->v1 edge.
```

## Source note 9, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L23)

```text
// - [1] is the factor for the v1->v2 edge.
```

## Source note 10, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L24)

```text
// - [2] is the factor for the v2->v0 edge.
```

## Source note 11, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L25)

```text
// Where v0 is the U1V0W0 vertex, v1 is the U0V1W0 vertex, and v2 is the
```

## Source note 12, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L26)

```text
// U0V0W1 vertex.
```

## Source note 13, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L27)

```text
// The hint at the order was provided in the Code Listing 15 of:
```

## Source note 14, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L28)

```text
// http://www.uraldev.ru/files/download/21/Real-Time_Tessellation_on_GPU.pdf
```

## Source note 15, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L29)

```text
// In Direct3D 12:
```

## Source note 16, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L30)

```text
// - [0] is the factor for the U0 edge (v1->v2).
```

## Source note 17, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L31)

```text
// - [1] is the factor for the V0 edge (v2->v0),
```

## Source note 18, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L32)

```text
// - [2] is the factor for the W0 edge (v0->v1).
```

## Source note 19, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L33)

```text
// Direct3D 12 provides barycentrics as X for v0, Y for v1, Z for v2.
```

## Source note 20, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L34)

```text
// In Xenia's domain shaders, the barycentric coordinates are handled as:
```

## Source note 21, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L35)

```text
// 1) vDomain.xyz -> r0.zyx by Xenia.
```

## Source note 22, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L36)

```text
// 2) r0.zyx -> r0.zyx by the guest (because r1.y is set to 0 by Xenia, which
```

## Source note 23, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L37)

```text
//    apparently means identity swizzle to games).
```

## Source note 24, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L38)

```text
// 3) r0.z * v0 + r0.y * v1 + r0.x * v2 by the guest.
```

## Source note 25, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L39)

```text
// With this order, there are no cracks in 4D5307E6 water.
```

## Source note 26, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L44)

```text
// Join phase. vpc0, vpc1, vpc2 taken as inputs.
```

## Source note 27, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L60)

```text
// Only the lower 24 bits of the vertex index are used (tested on an Adreno
```

## Source note 28, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L61)

```text
// 200 phone). `((index & 0xFFFFFF) + offset) & 0xFFFFFF` is the same as
```

## Source note 29, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_triangle.hs.hlsl#L62)

```text
// `(index + offset) & 0xFFFFFF`.
```
