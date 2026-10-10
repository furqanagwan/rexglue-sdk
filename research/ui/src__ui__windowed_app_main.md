# Windowed app main: ui source notes

This record preserves technical and API notes moved from `src/ui/windowed_app_main.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_main.cpp#L41)

```text
// Runs the app on an initialized context.
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_main.cpp#L46)

```text
// Match remaining positional args to the app's expected options.
```

## Source note 3, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_main.cpp#L64)

```text
// Guest vblanks, GPU waits and guest sleeps all rely on millisecond sleeps.
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_main.cpp#L67)

```text
// Apartment-threaded COM for shell dialogs.
```

## Source note 5, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/windowed_app_main.cpp#L85)

```text
// Convert wide argv from CommandLineToArgvW to UTF-8 for cvar::Init.
```
