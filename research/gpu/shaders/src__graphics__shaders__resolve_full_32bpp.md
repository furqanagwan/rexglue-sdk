# Resolve full 32bpp: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/resolve_full_32bpp.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_32bpp.xesli#L30)

```text
// 1 thread = 4 host pixels.
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_32bpp.xesli#L31)

```text
// 1 pixel per thread is 160% as slow on Nvidia Pascal, 8 pixels per thread is
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_32bpp.xesli#L32)

```text
// 115% as slow.
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_32bpp.xesli#L35)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```
