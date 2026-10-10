# Texture load dxt3a.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_dxt3a.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3a.cs.xesl#L27)

```text
// 1 thread = 4 DXT3A blocks to 16x4 R8 texels (no need to convert to DXT3
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3a.cs.xesl#L28)

```text
// because the overhead is the same, 2x, but the size must be 4-aligned on
```

## Source note 3, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3a.cs.xesl#L29)

```text
// Direct3D 12).
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3a.cs.xesl#L48)

```text
// Odd 2 blocks = even 2 blocks + 32 bytes when tiled.
```
