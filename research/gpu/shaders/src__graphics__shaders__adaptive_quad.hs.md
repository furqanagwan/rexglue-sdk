# Adaptive quad.hs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/adaptive_quad.hs.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L13)

```text
// 1.0 added to the factors according to the images in
```

## Source note 2, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L14)

```text
// https://www.slideshare.net/blackdevilvikas/next-generation-graphics-programming-on-xbox-360
```

## Source note 3, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L15)

```text
// (fractional_even also requires a factor of at least 2.0), to the min/max it
```

## Source note 4, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L16)

```text
// has already been added on the CPU.
```

## Source note 5, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L18)

```text
// Direct3D 12 (goes in a direction along the perimeter):
```

## Source note 6, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L19)

```text
// [0] - between U0V1 and U0V0.
```

## Source note 7, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L20)

```text
// [1] - between U0V0 and U1V0.
```

## Source note 8, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L21)

```text
// [2] - between U1V0 and U1V1.
```

## Source note 9, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L22)

```text
// [3] - between U1V1 and U0V1.
```

## Source note 10, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L23)

```text
// Xbox 360 factors go along the perimeter too according to the example of
```

## Source note 11, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L24)

```text
// edge factors in Next Generation Graphics Programming on Xbox 360.
```

## Source note 12, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L25)

```text
// However, if v0->v1... that seems to be working for triangle patches applies
```

## Source note 13, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L26)

```text
// here too, with the swizzle Xenia uses in domain shaders:
```

## Source note 14, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L27)

```text
// [0] - between U0V0 and U1V0.
```

## Source note 15, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L28)

```text
// [1] - between U1V0 and U1V1.
```

## Source note 16, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L29)

```text
// [2] - between U1V1 and U0V1.
```

## Source note 17, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L30)

```text
// [3] - between U0V1 and U0V0.
```

## Source note 18, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L35)

```text
// On the Xbox 360, according to the presentation, the inside factor is the
```

## Source note 19, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L36)

```text
// minimum of the factors of the edges along the axis.
```

## Source note 20, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L37)

```text
// Direct3D 12:
```

## Source note 21, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L38)

```text
// [0] - along U.
```

## Source note 22, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L39)

```text
// [1] - along V.
```

## Source note 23, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L55)

```text
// Only the lower 24 bits of the vertex index are used (tested on an Adreno
```

## Source note 24, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L56)

```text
// 200 phone). `((index & 0xFFFFFF) + offset) & 0xFFFFFF` is the same as
```

## Source note 25, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/adaptive_quad.hs.hlsl#L57)

```text
// `(index + offset) & 0xFFFFFF`.
```
