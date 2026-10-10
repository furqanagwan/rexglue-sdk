# Host depth store 1xmsaa.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/host_depth_store_1xmsaa.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_1xmsaa.cs.xesl#L29)

```text
// 1 thread = 8 samples (same as resolve granularity).
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_1xmsaa.cs.xesl#L33)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```
