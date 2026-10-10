# Seh: core source notes

This record preserves technical and API notes moved from `include/rex/platform/seh.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L24)

```text
/// Thread-local SEH state for capturing exception info.
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L30)

```text
/// Get the thread-local SEH state.
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L33)

```text
/// SEH filter function - captures exception info and determines whether to handle.
```

## Source note 4, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L34)

```text
/// Returns non-zero if the exception should be handled.
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L37)

```text
/// Re-raise the captured exception.
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L40)

```text
/// Initialize SEH signal handlers (POSIX only, no-op on Windows).
```

## Source note 7, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/seh.h#L43)

```text
/// Thread-local flag for POSIX: true when in SEH-protected code.
```
