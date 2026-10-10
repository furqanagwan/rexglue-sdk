# Pipeline util: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline_util.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L15)

```text
// Priority levels for async pipeline compilation.
```

## Source note 2, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L16)

```text
// Higher values are compiled sooner.
```

## Source note 3, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L17)

```text
// Writes to unbound RTs only.
```

## Source note 4, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L18)

```text
// Depth-only writes.
```

## Source note 5, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L19)

```text
// Writes to a visible RT.
```

## Source note 6, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L20)

```text
// Writes to RT0.
```

## Source note 7, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L22)

```text
// Converts normalized_color_mask to a 4-bit bitmask of bound RTs.
```

## Source note 8, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L23)

```text
// normalized_color_mask contains 4 bits per RT (RGBA).
```

## Source note 9, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline_util.h#L31)

```text
// Calculates async compilation priority from shader outputs.
```
