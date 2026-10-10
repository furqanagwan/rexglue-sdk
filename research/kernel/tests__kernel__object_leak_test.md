# Object leak test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/object_leak_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_leak_test.cpp#L38)

```text
// Slack for handles other threads may open meanwhile.
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_leak_test.cpp#L53)

```text
// The first creation may open handles that stay (thread pools, caches).
```

## Source note 3, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_leak_test.cpp#L69)

```text
// Exports reach the kernel state; it must exist.
```

## Source note 4, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_leak_test.cpp#L84)

```text
// Before 0c7b01a it set the status and carried on with a null port.
```
