# Module: kernel source notes

This record preserves technical and API notes moved from `include/rex/kernel/xam/module.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L32)

```text
/// Counts host system UI (the Xbox guide) as on screen for XamIsUIActive,
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L33)

```text
/// as XAM's own dialogs are counted.
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L37)

```text
/// A title's request for text (XamShowKeyboardUI).
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L40)

```text
// VKBD_* modes, as the title passed them
```

## Source note 5, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L42)

```text
// characters, without the terminator
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L44)

```text
/// Shows a keyboard on the UI thread and returns it (a dialog that deletes
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L45)

```text
/// itself once closed), calling `done` with the text, or nothing when
```

## Source note 8, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L46)

```text
/// cancelled, before it closes; null when it cannot show one.
```

## Source note 9, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L50)

```text
/// The console's own keyboard (RG-GDK-059), which XamShowKeyboardUI uses
```

## Source note 10, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L51)

```text
/// ahead of the SDK's ImGui dialog. Empty to unset.
```

## Source note 11, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/xam/module.h#L65)

```text
// Full path to next xex
```
