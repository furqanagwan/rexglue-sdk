# Filesystem win: core source notes

This record preserves technical and API notes moved from `src/core/filesystem_win.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/filesystem_win.cpp#L47)

```text
// _wpgmptr is only set for wmain entry points; a plain main (Catch2)
```

## Source note 2, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/filesystem_win.cpp#L48)

```text
// leaves it null and the debug CRT asserts. Ask the loader instead.
```

## Source note 3, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/filesystem_win.cpp#L109)

```text
// Dumb, but OK.
```

## Source note 4, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/filesystem_win.cpp#L127)

```text
// Flush is necessary - if not flushing, stream position may be out of sync.
```

## Source note 5, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/filesystem_win.cpp#L236)

```text
// We assume we've already created the file in the caller.
```
