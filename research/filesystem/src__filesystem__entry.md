# Entry: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/entry.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L55)

```text
// The size test is exact, not just a hint: the fold is ASCII-only, so any two
```

## Source note 2, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L56)

```text
// names it calls equal hold the same bytes per codepoint. It skips the UTF-8
```

## Source note 3, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L57)

```text
// decode for nearly every child, and a game directory can hold thousands.
```

## Source note 4, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L68)

```text
// Walk the path, one separator at a time.
```

## Source note 5, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L73)

```text
// Not found.
```

## Source note 6, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L99)

```text
// Already exists.
```

## Source note 7, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L139)

```text
// Store the string so split path string_views remain valid.
```

## Source note 8, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/entry.cpp#L143)

```text
// Drop root path (for example, "game:").
```
