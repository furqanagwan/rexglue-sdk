# Xenos draw: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/xenos_draw.hlsli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L61)

```text
// 1.0 added in the vertex shader to convert to Direct3D 11+, and clamped to
```

## Source note 2, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L62)

```text
// the factor range in the vertex shader.
```

## Source note 3, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L77)

```text
// Precise needed to preserve NaN - guest primitives may be converted to more
```

## Source note 4, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L78)

```text
// than 1 triangle, so need to kill them entirely manually in GS if any vertex
```

## Source note 5, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L79)

```text
// is NaN.
```

## Source note 6, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L87)

```text
// Guest primitives may be converted to more than 1 triangle, so need to kill
```

## Source note 7, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L88)

```text
// them entirely manually in GS - must kill if all guest primitive vertices
```

## Source note 8, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L89)

```text
// have negative cull distance.
```

## Source note 9, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/xenos_draw.hlsli#L93)

```text
// XENIA_GPU_D3D12_SHADERS_XENOS_DRAW_HLSLI_
```
