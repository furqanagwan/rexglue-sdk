# Resolve full 128bpp: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/resolve_full_128bpp.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L29)

```text
// 1 thread = 2 host pixels.
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L32)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L46)

```text
// Inside the half-pixel offset filling columns, pixel_0 now contains the
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L47)

```text
// pixel to stretch, pixel_1 contains the pixel after it. However, this means
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L48)

```text
// that the pixel offset is not aligned to 2 anymore. If 1 is the pixel to
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L49)

```text
// stretch, the two pixels will be 1 and 2 for pixel_index.x == 0. If 3 is,
```

## Source note 7, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L50)

```text
// they will be 3 and 4 for pixel_index.x == 0 and 2. However, in the former
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L51)

```text
// case, they should be 1 and 1, and in the latter, 3 and 3.
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_128bpp.xesli#L56)

```text
// Only 32_32_32_32_FLOAT color format is 128bpp.
```
