# Host depth store 2xmsaa.cs: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L29)

```text
// 1 thread = 8 samples (8x0.5 pixels, resolve granularity is 8 pixels).
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L33)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L44)

```text
// For simplicity, passing samples directly, not pixels, to
```

## Source note 4, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L45)

```text
// XeEdramOffsetInts (xenia-canary #1238). Both backend transfer shader
```

## Source note 5, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L46)

```text
// readers expect:
```

## Source note 6, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L47)

```text
// x and 2 * y + sample
```

## Source note 7, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L54)

```text
// Top and bottom to Direct3D 10.1+ and Vulkan top 1 and bottom 0 (for 2x) or
```

## Source note 8, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store_2xmsaa.cs.xesl#L55)

```text
// top-left 0 and bottom-right 3 (for 4x).
```
