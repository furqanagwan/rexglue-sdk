# Info: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/texture/info.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L23)

```text
// These formats are used for resampling textures / gamma control.
```

## Source note 2, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L115)

```text
// Uncompressed, and is also a ColorFormat.
```

## Source note 3, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L117)

```text
// Uncompressed, but resolve or memory export cannot be done to the format.
```

## Source note 4, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L129)

```text
// Bits of each stored component, 0 for none (and for non-fixed formats).
```

## Source note 5, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L131)

```text
// Fixed point: the host samples it normalized.
```

## Source note 6, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L146)

```text
// texel pitch
```

## Source note 7, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L147)

```text
// texel height
```

## Source note 8, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L148)

```text
// # of horizontal visible blocks
```

## Source note 9, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L149)

```text
// # of vertical visible blocks
```

## Source note 10, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L150)

```text
// # of horizontal pitch blocks
```

## Source note 11, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L151)

```text
// # of vertical pitch blocks
```

## Source note 12, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L174)

```text
// width in pixels
```

## Source note 13, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L175)

```text
// height in pixels
```

## Source note 14, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L176)

```text
// depth in layers
```

## Source note 15, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L177)

```text
// pitch in blocks
```

## Source note 16, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/info.h#L205)

```text
// Get the memory location of a mip. offset_x and offset_y are in blocks.
```
