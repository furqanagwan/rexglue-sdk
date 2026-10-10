# Keybinds: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/keybinds.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/keybinds.h#L39)

```text
/**
 * Parse a human-readable key name to a VirtualKey enum value.
 * @param name  Key name string (e.g. "F3", "Backtick", "A", "Escape").
 * @return      Matching VirtualKey, or VirtualKey::kNone if unrecognized.
 */
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/keybinds.h#L46)

```text
/**
 * Convert a VirtualKey to its human-readable string name.
 * @param vk  VirtualKey to convert.
 * @return    Key name string (e.g. "F3", "LMB"), or empty if unrecognized.
 */
```

## Source note 3, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/keybinds.h#L53)

```text
/**
 * Register a named keybind with a default key and callback.
 *
 * Creates a string CVAR named @p name in the "Keybinds" category so the
 * binding is visible in the settings overlay and persisted to config.
 *
 * @param name         CVAR name for this bind (e.g. "bind_console").
 * @param default_key  Default key name (e.g. "Backtick", "F3").
 * @param description  Human-readable description for the settings UI.
 * @param callback     Function to invoke when the bound key is pressed.
 */
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/keybinds.h#L67)

```text
/**
 * Remove a previously registered keybind.
 * @param name  The CVAR name used when registering the bind.
 */
```

## Source note 5, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/keybinds.h#L73)

```text
/**
 * Process a key-down event against all registered binds.
 *
 * Looks up each bind's current key from its CVAR, parses it, and compares
 * against the event's virtual key. If a match is found, the bind's callback
 * is invoked and the event is marked as handled.
 *
 * @param e  The key event to process.
 * @return   True if a bind matched and the event was consumed.
 */
```
