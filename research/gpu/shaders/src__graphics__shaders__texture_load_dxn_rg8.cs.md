# Texture load dxn rg8.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_dxn_rg8.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxn_rg8.cs.xesl#L27)

```text
// 1 thread = 2 DXN blocks to 8x4 R8G8 texels.
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxn_rg8.cs.xesl#L46)

```text
// Odd block = even block + 32 guest bytes when tiled.
```
