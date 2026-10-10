# Float24 round.ps: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/float24_round.ps.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_round.ps.hlsl#L10)

```text
// Input Z may be outside the viewport range (it's clamped after the shader).
```

## Source note 2, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_round.ps.hlsl#L11)

```text
// Assuming that 0...0.5 on the host corresponds to 0...1 on the guest, to
```

## Source note 3, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_round.ps.hlsl#L12)

```text
// allow for safe reinterpretation of any 24-bit value to and from float24
```

## Source note 4, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/float24_round.ps.hlsl#L13)

```text
// depth using depth output without unrestricted depth range.
```
