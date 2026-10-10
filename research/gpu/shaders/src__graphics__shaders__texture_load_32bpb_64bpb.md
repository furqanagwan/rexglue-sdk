# Texture load 32bpb 64bpb: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_32bpb_64bpb.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_32bpb_64bpb.xesli#L26)

```text
// 1 thread = 8 packed 32-bit texels with the externally provided uint4 -> 2x
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_32bpb_64bpb.xesli#L27)

```text
// uint4 function (XE_TEXTURE_LOAD_32BPB_TO_64BPB) for converting to 64bpb -
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_32bpb_64bpb.xesli#L28)

```text
// useful for expansion of hendeca (10:11:11 or 11:11:10) to unorm16/snorm16.
```
