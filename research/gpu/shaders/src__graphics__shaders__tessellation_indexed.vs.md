# Tessellation indexed.vs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/tessellation_indexed.vs.hlsl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 6

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_indexed.vs.hlsl#L6)

```text
// Only the lower 24 bits of the vertex index are used (tested on an Adreno
```

## Source note 2, line 7

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_indexed.vs.hlsl#L7)

```text
// 200 phone). `((index & 0xFFFFFF) + offset) & 0xFFFFFF` is the same as
```

## Source note 3, line 8

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/tessellation_indexed.vs.hlsl#L8)

```text
// `(index + offset) & 0xFFFFFF`.
```
