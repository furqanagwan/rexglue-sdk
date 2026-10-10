# Xsemaphore: system source notes

This record preserves technical and API notes moved from `src/system/xsemaphore.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L77)

```text
// SignalAndWait releases one count.
```

## Source note 2, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L98)

```text
// The header holds what this kernel last wrote, so a different count came
```

## Source note 3, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L99)

```text
// from the guest (an in-place KeInitializeSemaphore).
```

## Source note 4, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L102)

```text
// Over the limit the host keeps its count, and the header is corrected
```

## Source note 5, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L103)

```text
// to it below (Canary leaves the guest's value there).
```

## Source note 6, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L108)

```text
// Take back the counts the guest dropped, never blocking for one a waiter
```

## Source note 7, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L109)

```text
// has already claimed.
```

## Source note 8, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L127)

```text
// Get the free number of slots from the semaphore.
```

## Source note 9, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xsemaphore.cpp#L136)

```text
// Restore the semaphore back to its previous count.
```
