# File read test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/file_read_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L46)

```text
// Clear of the other kernel tests' function tables.
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L51)

```text
// A buffer running past the end of the address space: the read fails with
```

## Source note 3, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L52)

```text
// STATUS_ACCESS_VIOLATION, not end of file.
```

## Source note 4, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L74)

```text
// The guest side: one NtReadFile with an APC, then delivery of the thread's
```

## Source note 5, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L75)

```text
// user APCs, as an alertable wait would.
```

## Source note 6, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L87)

```text
// As the alertable wait exports do after the wait.
```

## Source note 7, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L110)

```text
// Runs one read on a guest thread and reports what the caller saw.
```

## Source note 8, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L140)

```text
// A file of `bytes` in a fresh content root, opened as the guest would.
```

## Source note 9, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L171)

```text
/*synchronous=*/
```

## Source note 10, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L173)

```text
// The caller is told PENDING, so the APC is its only completion signal.
```

## Source note 11, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L182)

```text
/*synchronous=*/
```

## Source note 12, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L191)

```text
/*synchronous=*/
```

## Source note 13, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L205)

```text
/*synchronous=*/
```

## Source note 14, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/file_read_test.cpp#L210)

```text
// A notification event: the first wait does not consume the completion.
```
