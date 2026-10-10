# Windowed app context win: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/windowed_app_context_win.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L23)

```text
// For per-monitor DPI awareness v1.
```

## Source note 2, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L39)

```text
// Added in Windows 10 1607, before per-monitor awareness v2 (1703). Make
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L40)

```text
// sure EnableNonClientDpiScaling is called in WM_NCCREATE so
```

## Source note 4, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L41)

```text
// AdjustWindowRectExForDpi matches the actual non-client area on 1607.
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L50)

```text
// Must call Initialize and check its result after creating to be able to
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L51)

```text
// perform pending function calls.
```

## Source note 7, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L66)

```text
// Windows 8.1 per-monitor DPI awareness version 1.
```

## Source note 8, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L70)

```text
// Windows 10 1607 per-monitor DPI awareness API, also used for per-monitor
```

## Source note 9, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/windowed_app_context_win.h#L71)

```text
// DPI awareness version 2 functionality added in Windows 10 1703.
```
