# Profile test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/profile_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L29)

```text
// Title-specific binary setting ids (XPROFILE_TITLE_SPECIFIC1-3).
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L33)

```text
// A setting that reports when it is destroyed.
```

## Source note 3, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L64)

```text
// Another thread writes the same setting while the reader still uses it.
```

## Source note 4, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L113)

```text
// A fresh profile (a relaunch) reads it back for the same title.
```

## Source note 5, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L130)

```text
// Loaded for another title (as after a title switch); the running title
```

## Source note 6, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L131)

```text
// has no saved copy.
```

## Source note 7, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L149)

```text
// No explicit flush: the header is still made durable on close.
```

## Source note 8, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/profile_test.cpp#L163)

```text
// The failure is reported and the package is still closed.
```
