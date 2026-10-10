# Imgui dialog: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/imgui_dialog.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_dialog.h#L31)

```text
// Shows a simple message box containing a text message.
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_dialog.h#L32)

```text
// Callers can want for the dialog to close with Wait().
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_dialog.h#L33)

```text
// Dialogs retain themselves and will delete themselves when closed.
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_dialog.h#L37)

```text
// A fence to signal when the dialog is closed.
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/imgui_dialog.h#L48)

```text
// Closes the dialog and returns to any waiters.
```
