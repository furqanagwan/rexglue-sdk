# Resolve fast 32bpp 1x2xmsaa: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli#L29)

```text
// 1 thread = 8 host pixels.
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli#L31)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli#L40)

```text
// With 1x MSAA the pixels are the canonical samples, thus the scanline is
```

## Source note 4, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli#L41)

```text
// contiguous and a single vectorized load suffices.
```

## Source note 5, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli#L49)

```text
// There's no fixed stride between horizontally adjacent pixels of a
```

## Source note 6, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_fast_32bpp_1x2xmsaa.xesli#L50)

```text
// multisampled source, load each pixel from its respective address.
```
