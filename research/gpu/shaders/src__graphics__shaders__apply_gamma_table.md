# Apply gamma table: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/apply_gamma_table.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_table.xesli#L59)

```text
// UNORM conversion according to the Direct3D 10+ rules.
```

## Source note 2, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_table.xesli#L63)

```text
// The ramp has blue in bits 0:9, green in 10:19, red in 20:29 - BGR passed as
```

## Source note 3, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_table.xesli#L64)

```text
// an R10G10B10A2 buffer.
```

## Source note 4, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_table.xesli#L73)

```text
// Perceptual luma.
```

## Source note 5, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/apply_gamma_table.xesli#L77)

```text
// Perceptual luma.
```
