# Heap: kernel source notes

This record preserves technical and API notes moved from `src/kernel/crt/heap.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L31)

```text
// Size header: prepended to every allocation so we can answer RtlSizeHeap
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L32)

```text
// without o1heap exposing per-allocation usable size.
```

## Source note 3, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L38)

```text
// padding to O1HEAP_ALIGNMENT
```

## Source note 4, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L54)

```text
// ReXHeap implementation
```

## Source note 5, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L144)

```text
// Pre-hook allocation outside our heap -- treat as fresh alloc.
```

## Source note 6, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L156)

```text
// Cross-segment fallback: allocate a fresh block, copy, then free old.
```

## Source note 7, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L203)

```text
// Allocate from the regular virtual heap (top-down) instead of the system
```

## Source note 8, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L204)

```text
// heap. The system heap range is shared with kernel bookkeeping allocations
```

## Source note 9, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L205)

```text
// (KernelState globals, thread PCR/TLS, module headers, etc.) and cannot
```

## Source note 10, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L206)

```text
// accommodate a large contiguous rexcrt segment alongside them.
```

## Source note 11, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/heap.cpp#L329)

```text
// Global instance + RTL hooks
```
