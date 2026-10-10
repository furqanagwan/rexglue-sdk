# Tessellation adaptive.vs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/tessellation_adaptive.vs.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 6

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L6)

```text
// The Xbox 360's GPU accepts the float32 tessellation factors for edges
```

## Source note 2, line 7

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L7)

```text
// through a special kind of an index buffer.
```

## Source note 3, line 8

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L8)

```text
// While 4D5307F2 sets the factors to 0 for frustum-culled (quad) patches, in
```

## Source note 4, line 9

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L9)

```text
// 4D5307E6 only allowing patches with factors above 0 makes distant
```

## Source note 5, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L10)

```text
// (triangle) patches disappear - it appears that there are no special values
```

## Source note 6, line 11

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L11)

```text
// for culled patches on the Xbox 360 (unlike zero, negative and NaN on
```

## Source note 7, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_adaptive.vs.hlsl#L12)

```text
// Direct3D 11).
```
