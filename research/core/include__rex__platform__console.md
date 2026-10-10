# Console: core source notes

This record preserves technical and API notes moved from `include/rex/platform/console.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L17)

```text
// Returns true if the stream is attached to a terminal. False for nullptr or
```

## Source note 2, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L18)

```text
// any non-terminal stream (pipes, files, redirected output).
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L21)

```text
// Enables ANSI escape sequence interpretation on the stream. No-op on POSIX.
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L22)

```text
// Returns true if escapes are interpreted on return (including the case where
```

## Source note 5, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L23)

```text
// they already were); false only when the Windows console probe fails.
```

## Source note 6, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L26)

```text
// Switches the process console output to UTF-8. Process-wide on Windows; no
```

## Source note 7, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/console.h#L27)

```text
// per-stream component, hence the no-arg signature. No-op on POSIX.
```
