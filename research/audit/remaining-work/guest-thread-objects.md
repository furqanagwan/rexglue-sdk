# Guest thread objects: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/274).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/system/entry_table.cpp:33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/entry_table.cpp#L33)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): wait if needed?
```

## Note 2: src/system/entry_table.cpp:42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/entry_table.cpp#L42)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): replace with a map with wait-free for find.
  // https://github.com/facebook/folly/blob/master/folly/AtomicHashMap.h
```

## Note 3: src/system/entry_table.cpp:55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/entry_table.cpp#L55)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): sleep for less time?
```

## Note 4: src/system/util/object_table.cpp:173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/util/object_table.cpp#L173)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: Return a status code telling the caller it wasn't released
  // (but not a failure code)
```

## Note 5: src/system/xmutant.cpp:46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmutant.cpp#L46)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): abandoning.
```

## Note 6: src/system/xobject.cpp:20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L20)

Disposition: retired reminder. Unused JIT-only include; static dispatch replaces the CPU JIT.

```text
// #include <rex/kernel/xboxkrnl/private.h>  // TODO: JIT only
```

## Note 7: src/system/xobject.cpp:50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L50)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Assert kernel_state != nullptr in this constructor.
```

## Note 8: src/system/xobject.cpp:57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L57)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: these are being asserted true... find out why
  // assert_true(handles_.empty());
  // assert_zero(pointer_ref_count_);
```

## Note 9: src/system/xobject.cpp:93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L93)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: Return true when handle is actually released.
```

## Note 10: src/system/xobject.cpp:400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L400)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: This assumes the object has a dispatch header (some don't!)
```

## Note 11: src/system/xobject.cpp:430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L430)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: assert if the type of the object != as_type
```

## Note 12: src/system/xobject.cpp:490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xobject.cpp#L490)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: This assumes the object contains a dispatch header (some don't!)
```

## Note 13: src/system/xsymboliclink.cpp:28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xsymboliclink.cpp#L28)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): kernel_state_->RegisterSymbolicLink(this);
```

## Note 14: src/system/xthread.cpp:109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L109)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): platform kill
```

## Note 15: src/system/xthread.cpp:194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L194)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Does the following apply here?
    // https://docs.microsoft.com/en-us/windows/win32/dxtecharts/coding-for-multiple-cores
    // "On Xbox 360, you must explicitly assign software threads to a particular
    //  hardware thread by using XSetThreadProcessor. Otherwise, all child
    //  threads will stay on the same hardware thread as the parent."
```

## Note 16: src/system/xthread.cpp:465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L465)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): translate error?
```

## Note 17: src/system/xthread.cpp:483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L483)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we need thread notifications (related to processor thread management)?
```

## Note 18: src/system/xthread.cpp:505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L505)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): dispatch events? waiters? etc?
```

## Note 19: src/system/xthread.cpp:526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L526)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we need thread notifications (related to processor thread management)?
```

## Note 20: src/system/xthread.cpp:547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L547)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): inform the profiler that this thread is exiting.
```

## Note 21: src/system/xthread.cpp:554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L554)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we need thread notifications (related to processor thread management)?
```

## Note 22: src/system/xthread.cpp:1271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L1271)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we need rexglue-compatible thread serialization?
    //             ideally any previous use for this (multi-dvds) are reworked in recomp to be
    //             single xex
```

## Note 23: src/system/xthread.cpp:1383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xthread.cpp#L1383)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we need this? threads would need different restoration approach
      //             see XThread::Save
```

## Note 24: include/rex/system/entry_table.h:48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/entry_table.h#L48)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): replace with a better data structure.
```
