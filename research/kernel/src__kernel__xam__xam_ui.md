# Xam ui: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xam/xam_ui.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L47)

```text
// Holds guest input for as long as a dialog is on screen, so the title does
```

## Source note 2, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L48)

```text
// not act on the presses driving it - including the one that dismisses it.
```

## Source note 3, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L97)

```text
// Broadcast XN_SYS_UI = true
```

## Source note 4, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L115)

```text
// dialog should be deleted at this point!
```

## Source note 5, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L120)

```text
// Broadcast XN_SYS_UI = false
```

## Source note 6, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L139)

```text
// Broadcast XN_SYS_UI = true
```

## Source note 7, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L158)

```text
// dialog should be deleted at this point!
```

## Source note 8, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L163)

```text
// Broadcast XN_SYS_UI = false
```

## Source note 9, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L182)

```text
// Broadcast XN_SYS_UI = true
```

## Source note 10, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L188)

```text
// Broadcast XN_SYS_UI = false
```

## Source note 11, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L205)

```text
// Broadcast XN_SYS_UI = true
```

## Source note 12, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L210)

```text
// Broadcast XN_SYS_UI = false
```

## Source note 13, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L286)

```text
// https://www.se7ensins.com/forums/threads/working-xshowmessageboxui.844116/
```

## Source note 14, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L317)

```text
// Auto-pick the focused button.
```

## Source note 15, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L326)

```text
// config.pszMainIcon = nullptr;
```

## Source note 16, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L329)

```text
// config.pszMainIcon = TD_ERROR_ICON;
```

## Source note 17, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L332)

```text
// config.pszMainIcon = TD_WARNING_ICON;
```

## Source note 18, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L335)

```text
// config.pszMainIcon = TD_INFORMATION_ICON;
```

## Source note 19, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L349)

```text
// Fallback to headless if no drawer available
```

## Source note 20, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L438)

```text
// https://www.se7ensins.com/forums/threads/release-how-to-use-xshowkeyboardui-release.906568/
```

## Source note 21, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L451)

```text
// Console: shows the keyboard a title gets from XamShowKeyboardUI, with a
```

## Source note 22, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L452)

```text
// sample prompt, and logs what was typed.
```

## Source note 23, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L469)

```text
// After a second, so the console can be closed first.
```

## Source note 24, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L510)

```text
// Redirect default_text back into the buffer.
```

## Source note 25, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L527)

```text
// Zero the output buffer.
```

## Source note 26, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L538)

```text
// Read and convert title/description/default_text from guest memory as utf16 to utf8 strings
```

## Source note 27, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L558)

```text
// The console's own keyboard (RG-GDK-059); the ImGui dialog when it
```

## Source note 28, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L559)

```text
// cannot be shown (no keyboard scenes built in).
```

## Source note 29, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L585)

```text
// Fallback: the ImGui dialog, its result read as it closes.
```

## Source note 30, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L632)

```text
// +1 for null terminator, just in case
```

## Source note 31, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L638)

```text
// Fallback to headless
```

## Source note 32, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L662)

```text
// NOTE: 0x00000001 is our dummy device ID from xam_content.cc
```

## Source note 33, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L683)

```text
// No UI available - log prominently and pause to let user see the error
```

## Source note 34, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xam/xam_ui.cpp#L690)

```text
// This is death, and should never return.
```
