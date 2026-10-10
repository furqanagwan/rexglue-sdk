# Resolve full 8bpp: shaders source notes

This record preserves technical and API notes moved from `src/graphics/shaders/resolve_full_8bpp.xesli`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `f0f7199`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_8bpp.xesli#L30)

```text
// 1 thread = 8 host pixels.
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_8bpp.xesli#L32)

```text
// Group height can't cross resolve granularity, Y overflow check not needed.
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/f0f7199/src/graphics/shaders/resolve_full_8bpp.xesli#L56)

```text
// Convert to R8.
```
