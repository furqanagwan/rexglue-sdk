# Guest memory: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/276).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/system/xmemory.cpp:29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L29)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): move xbox.h out
```

## Note 2: src/system/xmemory.cpp:634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L634)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): lightweight pool.
```

## Note 3: src/system/xmemory.cpp:651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L651)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): lightweight pool.
```

## Note 4: src/system/xmemory.cpp:1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1088)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(DrChat): write compressed with snappy.
```

## Note 5: src/system/xmemory.cpp:1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1143)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(DrChat): read compressed with snappy.
```

## Note 6: src/system/xmemory.cpp:1182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1182)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(DrChat): protect pages.
```

## Note 7: src/system/xmemory.cpp:1184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1184)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Remove access callbacks from pages if this is a physical
  // memory heap.
```

## Note 8: src/system/xmemory.cpp:1378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1378)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): optimized searching (free list buckets, bitmap, etc).
```

## Note 9: src/system/xmemory.cpp:1516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1516)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): find a way to actually decommit memory;
  //     mapped memory cannot be decommitted.
  /*BOOL result =
      VirtualFree(TranslateRelative(start_page_number << page_size_shift_),
                  page_count << page_size_shift_, MEM_DECOMMIT);
  if (!result) {
    PLOGW("BaseHeap::Decommit failed due to host VirtualFree failure");
    return false;
  }*/
```

## Note 10: src/system/xmemory.cpp:1563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1563)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): protect with NOACCESS?
  /*BOOL result = VirtualFree(
      TranslateRelative(base_page_number << page_size_shift_), 0, MEM_RELEASE);
  if (!result) {
    PLOGE("BaseHeap::Release failed due to host VirtualFree failure");
    return false;
  }*/
  // Instead, we just protect it, if we can.
```

## Note 11: src/system/xmemory.cpp:1574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1574)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): figure out why games are using memory after releasing
    // it. It's possible this is some virtual/physical stuff where the GPU
    // still can access it.
```

## Note 12: src/system/xmemory.cpp:1878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1878)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): don't leak parent memory.
```

## Note 13: src/system/xmemory.cpp:1899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1899)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): flag for ensure-not-committed?
```

## Note 14: src/system/xmemory.cpp:1911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1911)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): don't leak parent memory.
```

## Note 15: src/system/xmemory.cpp:1949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L1949)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): don't leak parent memory.
```

## Note 16: src/system/xmemory.cpp:2022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L2022)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Implement data providers.
```

## Note 17: src/system/xmemory.cpp:2098

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L2098)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Enable data providers.
```

## Note 18: src/system/xmemory.cpp:2102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L2102)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Check if data providers are already enabled.
          // If data providers are already enabled for the page, it has even
          // stricter protection.
```

## Note 19: src/system/xmemory.cpp:2132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmemory.cpp#L2132)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support read watches.
```

## Note 20: include/rex/system/xmemory.h:475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/xmemory.h#L475)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Implement data providers - more complicated because they
  // will need to be able to release the global lock.
```

## Note 21: include/rex/system/xmemory.h:500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/xmemory.h#L500)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Implement data providers - this is why locking depth of 1
  // will be required in the future.
```
