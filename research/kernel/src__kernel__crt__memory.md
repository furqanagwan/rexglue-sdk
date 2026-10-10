# Memory: kernel source notes

This record preserves technical and API notes moved from `src/kernel/crt/memory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/memory.cpp#L17)

```text
// Standard memory operations
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/memory.cpp#L37)

```text
// Xbox/VMX-optimized variants (same semantics, native speed)
```

## Source note 3, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/memory.cpp#L57)

```text
// Secure variants (return errno_t)
```
