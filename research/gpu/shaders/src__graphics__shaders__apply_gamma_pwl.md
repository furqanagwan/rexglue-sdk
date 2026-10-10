# Apply gamma pwl: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/apply_gamma_pwl.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L13)

```text
// output = base + (multiplier * delta) / increment
```

## Source note 2, line 14

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L14)

```text
// https://developer.amd.com/wordpress/media/2012/10/RRG-216M56-03oOEM.pdf
```

## Source note 3, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L15)

```text
// The lower 6 bits of the base and the delta are 0 (though enforcing that in
```

## Source note 4, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L16)

```text
// the shader is not necessary).
```

## Source note 5, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L17)

```text
// The `(multiplier * delta) / increment` part may result in a nonzero value
```

## Source note 6, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L18)

```text
// in the lower 6 bits of the result, however, so doing `* (1.0f / 64.0f)`
```

## Source note 7, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L19)

```text
// instead of `>> 6` to preserve them (if the render target is 16bpc rather
```

## Source note 8, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L20)

```text
// than 10bpc, for instance).
```

## Source note 9, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L74)

```text
// UNORM conversion according to the Direct3D 10+ rules.
```

## Source note 10, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_pwl.xesli#L95)

```text
// Perceptual luma.
```
