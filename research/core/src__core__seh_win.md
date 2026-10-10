# Seh win: core source notes

This record preserves technical and API notes moved from `src/core/seh_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/seh_win.cpp#L47)

```text
// For access violations, include the extra info (read/write flag and address)
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/seh_win.cpp#L53)

```text
// RaiseException doesn't return, but compiler may not know that
```

## Source note 3, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/seh_win.cpp#L62)

```text
// Native SEH needs no signal handler setup, but mark as initialized
```
