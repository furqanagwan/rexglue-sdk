# Windowed app context win: ui source notes

This record preserves technical and API notes moved from `src/ui/windowed_app_context_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L33)

```text
// Logging possibly not initialized in this function yet.
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L37)

```text
// Xenia expected per-monitor v2 from the application manifest. Titles built
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L38)

```text
// with the SDK carry no such manifest, so opt in before any window exists;
```

## Source note 4, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L39)

```text
// this fails harmlessly if the process awareness is already set.
```

## Source note 5, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L49)

```text
// Obtain function pointers that may be used for windows if available.
```

## Source note 6, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L71)

```text
// Create the message-only window for executing pending functions - using a
```

## Source note 7, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L72)

```text
// window instead of executing them between iterations so non-main message
```

## Source note 8, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L73)

```text
// loops, such as Windows modals, can execute pending functions too.
```

## Source note 9, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L104)

```text
// Send WM_QUIT to whichever loop happens to process it - may be the loop of a
```

## Source note 10, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L105)

```text
// built-in modal window, which is unaware of HasQuitFromUIThread, don't let
```

## Source note 11, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L106)

```text
// it delay quitting indefinitely.
```

## Source note 12, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L113)

```text
// The HasQuitFromUIThread check is not absolutely required, but for
```

## Source note 13, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L114)

```text
// additional safety in case WM_QUIT is not received for any reason.
```

## Source note 14, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L118)

```text
// WM_QUIT (0, with the PostQuitMessage result in wParam) or an error
```

## Source note 15, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L119)

```text
// (-1). WM_QUIT may come from elsewhere than PlatformQuitFromUIThread,
```

## Source note 16, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L120)

```text
// so quit the context to finish everything including pending functions.
```

## Source note 17, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L134)

```text
// Need the window for the entire context's lifetime, don't allow anything
```

## Source note 18, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L135)

```text
// to close it.
```

## Source note 19, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L148)

```text
// The message-only window owned by the context is being destroyed,
```

## Source note 20, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L149)

```text
// thus the context won't be able to execute pending functions
```

## Source note 21, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_context_win.cpp#L150)

```text
// anymore - can't continue functioning normally.
```
