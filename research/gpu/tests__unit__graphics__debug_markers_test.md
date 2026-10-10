# Debug markers test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/debug_markers_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L19)

```text
// Expected words follow PIXEncodeEventInfo and PIXCopyStringArgument in
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L20)

```text
// microsoft/PixEvents (see debug_markers.h); PIX decoding them is checked by
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L21)

```text
// scripts/pix_capture_fixture.ps1.
```

## Source note 4, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L27)

```text
// Four words: info, color, context, and "Resolve" with its terminator.
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L29)

```text
// Size 4, type 1 at bit 7, metadata 0xF3 (color, ANSI, on context) at bit 12.
```

## Source note 6, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L33)

```text
// "Resolve\0", low byte first.
```

## Source note 7, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L40)

```text
// A marker is type 2.
```

## Source note 8, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L41)

```text
// "Frame 12".
```

## Source note 9, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L50)

```text
// 255 characters: the last word holds seven and the terminator.
```

## Source note 10, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L69)

```text
// The submission ends inside both regions: both EndEvents go into the
```

## Source note 11, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L70)

```text
// command list being closed.
```

## Source note 12, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L73)

```text
// The scopes end later; their command list is gone, so nothing is recorded.
```

## Source note 13, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/debug_markers_test.cpp#L83)

```text
// A region opened in the next submission while the stale scope is alive.
```
