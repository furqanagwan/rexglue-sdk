# Object header test: kernel source notes

This record preserves technical and API notes moved from `tests/kernel/object_header_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L40)

```text
// Polls: a zero timeout never blocks.
```

## Source note 2, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L62)

```text
// Guest memory holding a dispatch object the guest initialized inline, as the
```

## Source note 3, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L63)

```text
// XDK's inlined KeInitializeEvent/KeInitializeSemaphore do.
```

## Source note 4, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L89)

```text
// Before RG-GDK-014 Initialize dropped manual_reset and this reported 1.
```

## Source note 5, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L95)

```text
// A notification event stays signaled through waits.
```

## Source note 6, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L115)

```text
// KePulseEvent returns the previous state and leaves the event reset.
```

## Source note 7, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L136)

```text
// Over the limit: nothing changes.
```

## Source note 8, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L146)

```text
// Synchronization, not signaled.
```

## Source note 9, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L153)

```text
// The guest signals it in place, without calling the kernel.
```

## Source note 10, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L160)

```text
// And resets it in place after the kernel set it.
```

## Source note 11, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L189)

```text
// Past the limit the host keeps its count, and says so in the header.
```

## Source note 12, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L196)

```text
// Canary #1225's Guitar Hero 5 trace, synthetically: the guest dereferences
```

## Source note 13, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L197)

```text
// an object the kernel created over its memory, the object dies, its handle
```

## Source note 14, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L198)

```text
// goes to the next object, and the signature left in guest memory names that
```

## Source note 15, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L199)

```text
// unrelated object.
```

## Source note 16, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L211)

```text
// ObDereferenceObject on it: the last handle goes and the object dies.
```

## Source note 17, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L216)

```text
// The table reuses the lowest free slot, so the next object takes the
```

## Source note 18, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L217)

```text
// handle, like the thread in the Guitar Hero 5 trace.
```

## Source note 19, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L227)

```text
// Releasing the new event leaves the semaphore alone.
```

## Source note 20, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L242)

```text
// A semaphore at its limit is not released: the host call fails and the
```

## Source note 21, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L243)

```text
// header keeps the count.
```

## Source note 22, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L278)

```text
// And the host agrees: exactly that many waits succeed.
```

## Source note 23, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L308)

```text
// End signaled, so the waiters race the last Set too.
```

## Source note 24, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L322)

```text
// Quiescent: the guest header says what a wait finds. A waiter's callback
```

## Source note 25, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L323)

```text
// can run after a later Set, so it must read the host state, not assume a
```

## Source note 26, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/kernel/object_header_test.cpp#L324)

```text
// reset.
```
