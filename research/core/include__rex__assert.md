# Assert: core source notes

This record preserves technical and API notes moved from `include/rex/assert.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L29)

```text
// References expr in an unevaluated short-circuit so -Wunused doesn't fire.
```

## Source note 2, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L43)

```text
/// Assert failure handler that logs the message before aborting
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L44)

```text
/// @param file     Source file (__FILE__)
```

## Source note 4, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L45)

```text
/// @param line     Line number (__LINE__)
```

## Source note 5, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L46)

```text
/// @param expr     Expression that failed (stringified)
```

## Source note 6, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L47)

```text
/// @param message  User-provided message explaining the failure
```

## Source note 7, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L114)

```text
/// Marks code as unreachable. Invokes undefined behavior if reached.
```

## Source note 8, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L115)

```text
/// Use in switch default cases and after exhaustive if-else chains.
```

## Source note 9, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L118)

```text
// Fatal error that terminates the program with a message
```

## Source note 10, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/assert.h#L120)

```text
// Print to stderr and terminate
```
