# Texture load 32bpb: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/texture_load_32bpb.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_32bpb.xesli#L26)

```text
// 1 thread = 8 blocks passed through an externally provided
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/texture_load_32bpb.xesli#L27)

```text
// uint4 transformation function (XE_TEXTURE_LOAD_32BPB_TRANSFORM).
```
