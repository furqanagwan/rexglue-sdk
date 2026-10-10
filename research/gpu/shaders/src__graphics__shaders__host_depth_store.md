# Host depth store: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/host_depth_store.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store.xesli#L28)

```text
// The width divided by 8 minus 1 is stored.
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store.xesli#L36)

```text
// As host depth is needed for at most one transfer destination per update, base
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store.xesli#L37)

```text
// is not passed to the shader - (0, 0) of the render target is at 0 of the
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store.xesli#L38)

```text
// destination buffer.
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store.xesli#L48)

```text
// 40-sample columns are not swapped for addressing simplicity (because this is
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/host_depth_store.xesli#L49)

```text
// used for depth -> depth transfers, where swapping isn't needed).
```
