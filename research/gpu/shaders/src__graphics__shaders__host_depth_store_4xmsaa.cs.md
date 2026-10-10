# Host depth store 4xmsaa.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L29)

```text
// 1 thread = 8 samples (4x0.5 pixels, resolve granularity is 8 pixels).
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L33)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```

## Source note 3, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L43)

```text
// For simplicity, passing samples directly, not pixels, to
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L44)

```text
// XeEdramOffsetInts (xenia-canary #1238). Both backend transfer shader
```

## Source note 5, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L45)

```text
// readers expect:
```

## Source note 6, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L46)

```text
// 2 * x + horizontal sample and 2 * y + vertical sample
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_4xmsaa.cs.xesl#L53)

```text
// Render target horizontal sample in bit 0, vertical sample in bit 1.
```
