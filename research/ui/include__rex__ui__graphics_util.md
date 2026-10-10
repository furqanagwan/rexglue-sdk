# Graphics util: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/graphics_util.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L18)

```text
// For estimating coverage extents from vertices. This may give results that are
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L19)

```text
// different than what the GPU will actually draw (this is the reference
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L20)

```text
// conversion with 1/2 ULP accuracy, but Direct3D 11 permits 0.6 ULP tolerance
```

## Source note 4, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L21)

```text
// in floating point to fixed point conversion), but is enough to tie-break
```

## Source note 5, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L22)

```text
// vertices at pixel centers (due to the half-pixel offset applied to integer
```

## Source note 6, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L23)

```text
// coordinates incorrectly, for instance) with some error tolerance near 0.5,
```

## Source note 7, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/graphics_util.h#L24)

```text
// for use with the top-left rasterization rule later.
```
