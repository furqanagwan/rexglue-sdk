# Fault report test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/fault_report_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/fault_report_test.cpp#L39)

```text
// Unallocated guest virtual memory in a non-physical heap.
```

## Source note 2, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/fault_report_test.cpp#L42)

```text
// Stands in for a recompiled guest function that reads freed guest memory.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/fault_report_test.cpp#L50)

```text
// Runs in a child process: calls the faulting function, which kills it.
```

## Source note 4, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/fault_report_test.cpp#L61)

```text
// not reached
```

## Source note 5, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/fault_report_test.cpp#L84)

```text
// the read faulted
```
