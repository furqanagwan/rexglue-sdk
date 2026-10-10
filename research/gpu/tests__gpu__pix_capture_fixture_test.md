# Pix capture fixture test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/pix_capture_fixture_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L27)

```text
// Draws a kSize square of kColor and resolves it, calling `begin` and `end`
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L28)

```text
// around the submitted work. Returns the resolved texel at the center.
```

## Source note 3, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L31)

```text
// A readback resolve waits for its submission, so the draw and the resolve
```

## Source note 4, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L32)

```text
// have both executed when it returns.
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L34)

```text
// Otherwise the draw is dropped while its pipeline compiles.
```

## Source note 6, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L52)

```text
// Hidden: it only captures when PIX launched the process, which
```

## Source note 7, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L53)

```text
// scripts/pix_capture_fixture.ps1 does. The capture holds a draw and a
```

## Source note 8, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L54)

```text
// resolve; the script checks the saved capture's event list for the "Draw",
```

## Source note 9, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L55)

```text
// "Resolve" and queue "Frame, submission" labels. Nothing enables
```

## Source note 10, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L56)

```text
// gpu_debug_markers here, so the labels also prove PIX is detected.
```

## Source note 11, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L63)

```text
// The DXGI graphics analysis interface only exists under a capture tool.
```

## Source note 12, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/pix_capture_fixture_test.cpp#L69)

```text
// The captured work did what it says, so a replay can be compared with it.
```
