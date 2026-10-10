# Discrete quad: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/discrete_quad.hlsli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L12)

```text
// 1.0 already added to the factor on the CPU, according to the images in
```

## Source note 2, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L13)

```text
// https://www.slideshare.net/blackdevilvikas/next-generation-graphics-programming-on-xbox-360
```

## Source note 3, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L14)

```text
// (fractional_even also requires a factor of at least 2.0).
```

## Source note 4, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L16)

```text
// Don't calculate any variables for SV_TessFactor outside of this loop, or
```

## Source note 5, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L17)

```text
// everything will be broken - FXC will add code to make it calculated only
```

## Source note 6, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L18)

```text
// once for all 4 fork instances, but doesn't do it properly.
```

## Source note 7, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L23)

```text
// Don't calculate any variables for SV_InsideTessFactor outside of this loop,
```

## Source note 8, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L24)

```text
// or everything will be broken - FXC will add code to make it calculated only
```

## Source note 9, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/discrete_quad.hlsli#L25)

```text
// once for all 2 fork instances, but doesn't do it properly.
```
