# Game config: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/game_config.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L27)

```text
// Identity: Name (3-50 of A-Z a-z 0-9 . -) and Publisher (an X.500 name,
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L28)

```text
// e.g. "CN=Example"). For a Store build both must equal Partner Center's.
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L32)

```text
// ShellVisuals.
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L37)

```text
// The title executable, relative to the package root.
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L39)

```text
// Xbox services identity, both or neither (from Partner Center).
```

## Source note 6, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L42)

```text
// Microsoft Store product ID (12 characters).
```

## Source note 7, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L46)

```text
// A ShellVisuals image the config names, with the size GDK tools expect.
```

## Source note 8, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L56)

```text
// Checks every field; the error names the first bad one.
```

## Source note 9, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L59)

```text
// The MicrosoftGame.config text (UTF-8 XML), or the validation error.
```

## Source note 10, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L62)

```text
// A single-color PNG, used for placeholder ShellVisuals images until the
```

## Source note 11, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/game_config.h#L63)

```text
// title supplies its own art.
```
