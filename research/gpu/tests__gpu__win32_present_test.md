# Win32 present test: graphics source notes

This record preserves technical and API notes moved from `tests/gpu/win32_present_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L33)

```text
// UI drawers run only for frames that are presented, so this records every
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L34)

```text
// presented frame's render target size.
```

## Source note 3, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L42)

```text
// Pumps the UI thread's messages until `done` or the timeout.
```

## Source note 4, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L71)

```text
// WARP, then the hardware adapter
```

## Source note 5, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L93)

```text
// First frame at the window's size.
```

## Source note 6, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L98)

```text
// Resize: the swap chain follows the client area.
```

## Source note 7, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L110)

```text
// Minimize and restore keep presenting afterwards.
```

## Source note 8, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L120)

```text
// Close with the presenter still attached, while frames are being requested:
```

## Source note 9, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/gpu/win32_present_test.cpp#L121)

```text
// the window detaches the surface, and the presenter outlives it cleanly.
```
