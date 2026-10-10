# Native resolve fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/native_resolve_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L35)

```text
// The foreground's right edge, in guest pixels: a quarter into a guest pixel
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L36)

```text
// whichever way the half-pixel convention shifts it, so at 2x the pixel's
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L37)

```text
// top-left host sample is covered and its center sample isn't.
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L40)

```text
// The fixtures' cvars outlive them: put back what these runs set, so later
```

## Source note 5, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L41)

```text
// tests in the process run at the default scale.
```

## Source note 6, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L52)

```text
// Draws the background over 32x32, then the foreground from the left up to
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L53)

```text
// kEdge, resolves 32x32 at 2x2 resolution scale with `list` as
```

## Source note 8, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L54)

```text
// resolution_scale_targets, and reads the texels back (row by row).
```

## Source note 9, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L68)

```text
// Otherwise draws are dropped while their pipelines compile.
```

## Source note 10, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L75)

```text
// The foreground's own geometry, ending inside a guest pixel.
```

## Source note 11, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L111)

```text
// Both render target paths resolve from the scaled EDRAM copy.
```

## Source note 12, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L117)

```text
// 32 wide is listed: the resolve stays scaled, read back from the top-left
```

## Source note 13, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L118)

```text
// host sample of each texel.
```

## Source note 14, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L122)

```text
// Not listed: written at the guest's size from each texel's center sample.
```

## Source note 15, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L133)

```text
// The edge pixel: covered at its top-left sample, not at its center.
```

## Source note 16, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L160)

```text
// none: every resolve at the guest's size.
```

## Source note 17, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L166)

```text
// The edge pixel has 2 of its 4 host samples covered: each byte is the mean
```

## Source note 18, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L167)

```text
// of two foreground and two background bytes. Everywhere else the block is
```

## Source note 19, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/native_resolve_fixture_test.cpp#L168)

```text
// uniform, so the average is the center sample.
```
