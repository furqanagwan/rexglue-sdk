# Memory win: core source notes

This record preserves technical and API notes moved from `src/core/memory_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory_win.cpp#L64)

```text
// Strip the page guard flag for now...
```

## Source note 2, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory_win.cpp#L88)

```text
// To test FromApp functions on desktop, undefine
```

## Source note 3, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory_win.cpp#L89)

```text
// REX_BASE_MEMORY_WIN_USE_DESKTOP_FUNCTIONS and link to WindowsApp.lib.
```

## Source note 4, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory_win.cpp#L222)

```text
// VirtualAlloc2FromApp and MapViewOfFile3FromApp were added in 10.0.17134.0.
```

## Source note 5, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/memory_win.cpp#L223)

```text
// https://docs.microsoft.com/en-us/uwp/win32-and-com/win32-apis
```
