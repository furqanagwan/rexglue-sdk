# Texture load dxt3aas1111: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_dxt3aas1111.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3aas1111.xesli#L26)

```text
// 1 thread = 4 DXT3A-as-1111 blocks to 16x4 16bpp texels passed through an
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3aas1111.xesli#L27)

```text
// externally provided
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3aas1111.xesli#L28)

```text
// `uint4 XE_TEXTURE_LOAD_DXT3A_AS_1_1_1_1_TO_16BPP(uint2 halfblocks)`
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3aas1111.xesli#L29)

```text
// conversion function.
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_dxt3aas1111.xesli#L48)

```text
// Odd 2 blocks = even 2 blocks + 32 bytes when tiled.
```
