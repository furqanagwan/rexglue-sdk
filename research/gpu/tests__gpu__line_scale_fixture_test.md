# Line scale fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/line_scale_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/line_scale_fixture_test.cpp#L50)

```text
// Draws a white horizontal line at guest y over black, resolves it at the
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/line_scale_fixture_test.cpp#L51)

```text
// guest's size (each texel the average of its host pixels) and returns the
```

## Source note 3, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/line_scale_fixture_test.cpp#L52)

```text
// red coverage summed down column 16, in 255ths of a guest pixel.
```

## Source note 4, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/line_scale_fixture_test.cpp#L112)

```text
// On a guest pixel's center and across a guest pixel boundary.
```

## Source note 5, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/line_scale_fixture_test.cpp#L123)

```text
// One guest pixel of white either way; a 1-host-pixel line at 2x gives half
```

## Source note 6, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/line_scale_fixture_test.cpp#L124)

```text
// (128).
```
