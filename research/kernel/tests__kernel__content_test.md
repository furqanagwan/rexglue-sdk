# Content test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/content_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L61)

```text
// Some titles flush with other casing than they created with.
```

## Source note 2, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L100)

```text
// Created, but the process stopped before XamContentCreate wrote the header.
```

## Source note 3, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L122)

```text
// A torn header and a stray temporary from an earlier crash.
```

## Source note 4, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L136)

```text
// Runs in a child process: writes a save, flushes it and dies without any
```

## Source note 5, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L137)

```text
// cleanup, as a crash would.
```

## Source note 6, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L173)

```text
// died where the crash was injected
```

## Source note 7, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/content_test.cpp#L175)

```text
// "Restart": a fresh content manager over the same root.
```
