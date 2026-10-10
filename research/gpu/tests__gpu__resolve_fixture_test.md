# Resolve fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/resolve_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L48)

```text
// Writes the resolve rectangle (x0, y0)-(x1, y1) for vertex fetch 0.
```

## Source note 2, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L61)

```text
// Direct3D 9 resolves by drawing a 3-vertex rectangle list with RB_MODECONTROL
```

## Source note 3, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L62)

```text
// in copy mode. The rectangle comes from vertex fetch constant 0.
```

## Source note 4, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L66)

```text
// The EDRAM pitch is in samples, two per pixel horizontally with 4x MSAA.
```

## Source note 5, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L132)

```text
// The clear happens after the copy, so the first resolve clears EDRAM and
```

## Source note 6, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L133)

```text
// the second one copies the cleared color out.
```

## Source note 7, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L149)

```text
// D3D advances RB_COPY_DEST_BASE by whole 32x32 macro tiles, which are 1 KB at
```

## Source note 8, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L150)

```text
// 8bpp and 2 KB at 16bpp, so the base can sit inside a 4 KB tiled subresource.
```

## Source note 9, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L151)

```text
// The texel at (x, y) then belongs at (x + 32 * phase, y) of the surface that
```

## Source note 10, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L152)

```text
// starts at the 4 KB boundary. Source: xenia-canary #1240.
```

## Source note 11, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L183)

```text
// Every byte of the allocation must be written exactly where the oracle
```

## Source note 12, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L184)

```text
// places the rectangle's texels, and nowhere else.
```

## Source note 13, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L211)

```text
// A uniform clear can't show texels read back from the wrong place, so this
```

## Source note 14, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L212)

```text
// resolves a 4x4 grid of 8x8 cells, each with its own color, into the same
```

## Source note 15, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L213)

```text
// destination. Each cell's texels must hold one value, distinct per cell, at
```

## Source note 16, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L214)

```text
// the addresses the tiling oracle gives. Run with draw_resolution_scale_* to
```

## Source note 17, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L215)

```text
// cover the scaled readback (#58).
```

## Source note 18, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L246)

```text
// Channels of 15 * (cell + 1) stay distinct even when packed to 5 bits.
```

## Source note 19, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L297)

```text
// Hidden: the backend treats device loss as fatal, so this case ends the
```

## Source note 20, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L298)

```text
// process. CTest runs it on its own and requires the fatal-error report.
```

## Source note 21, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/resolve_fixture_test.cpp#L313)

```text
// The resolve opens a submission, which checks the device first.
```
