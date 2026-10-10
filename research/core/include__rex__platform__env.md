# Env: core source notes

This record preserves technical and API notes moved from `include/rex/platform/env.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L19)

```text
// Reads an environment variable. Returns std::nullopt when not set, or an
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L20)

```text
// optional containing UTF-8 bytes when set (an empty string is a distinct
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L21)

```text
// state from nullopt).
```

## Source note 4, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L24)

```text
// Sets an environment variable, overwriting any existing value. Value is
```

## Source note 5, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L25)

```text
// UTF-8. Returns true on success.
```

## Source note 6, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L28)

```text
// Removes an environment variable. Returns true if the variable was unset on
```

## Source note 7, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/env.h#L29)

```text
// return (success, or already not set).
```
