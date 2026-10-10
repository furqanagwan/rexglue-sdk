# Discrete triangle: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/discrete_triangle.hlsli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L12)

```text
// Xenos creates a uniform grid for triangles, but this can't be reproduced
```

## Source note 2, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L13)

```text
// using the tessellator on the PC, so just use what has the closest level of
```

## Source note 3, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L14)

```text
// detail.
```

## Source note 4, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L15)

```text
// https://www.slideshare.net/blackdevilvikas/next-generation-graphics-programming-on-xbox-360
```

## Source note 5, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L17)

```text
// 1.0 already added to the factor on the CPU, according to the images in the
```

## Source note 6, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L18)

```text
// slides above.
```

## Source note 7, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L20)

```text
// Don't calculate any variables for SV_TessFactor outside of this loop, or
```

## Source note 8, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L21)

```text
// everything will be broken - FXC will add code to make it calculated only
```

## Source note 9, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_triangle.hlsli#L22)

```text
// once for all 3 fork instances, but doesn't do it properly.
```
