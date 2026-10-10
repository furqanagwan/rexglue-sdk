# Keybinds: ui source notes

This record preserves technical and API notes moved from `src/ui/keybinds.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/keybinds.cpp#L23)

```text
// Function keys
```

## Source note 2, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/keybinds.cpp#L86)

```text
// OEM / special
```

## Source note 3, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/keybinds.cpp#L141)

```text
// Mouse buttons
```

## Source note 4, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/keybinds.cpp#L161)

```text
/* ---- Bind registry ---- */
```

## Source note 5, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/keybinds.cpp#L176)

```text
/* Store the bind entry (owns the key string that the CVAR references). */
```

## Source note 6, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/ui/keybinds.cpp#L182)

```text
/* Capture a pointer to the entry's key string for the CVAR getter/setter.
     The entry is stable because g_binds is never compacted while binds are
     alive (UnregisterBind sets the callback to null rather than erasing). */
```
