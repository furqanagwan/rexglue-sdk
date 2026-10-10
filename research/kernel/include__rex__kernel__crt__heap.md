# Heap: kernel source notes

This record preserves technical and API notes moved from `include/rex/kernel/crt/heap.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/crt/heap.h#L28)

```text
/// Mirrors O1HeapDiagnostics without requiring o1heap.h in consumer headers.
```

## Source note 2, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/crt/heap.h#L71)

```text
/// Initialize the global rexcrt heap. Called by Runtime::Setup() when enabled.
```

## Source note 3, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/kernel/crt/heap.h#L74)

```text
/// Access the global heap instance (valid after InitHeap).
```
