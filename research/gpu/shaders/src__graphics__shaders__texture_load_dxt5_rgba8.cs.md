# Texture load dxt5 rgba8.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_dxt5_rgba8.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt5_rgba8.cs.xesl#L27)

```text
// 1 thread = 2 DXT5 blocks to 8x4 R8G8B8A8 texels.
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt5_rgba8.cs.xesl#L47)

```text
// Odd block = even block + 32 guest bytes when tiled.
```

## Source note 3, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt5_rgba8.cs.xesl#L54)

```text
// Sort the color indices so they can be used as weights for the second
```

## Source note 4, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt5_rgba8.cs.xesl#L55)

```text
// endpoint.
```
