# Kernel io memory: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/273).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/kernel/xboxkrnl/xboxkrnl_io.cpp:68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L68)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): validate path components individually
```

## Note 2: src/kernel/xboxkrnl/xboxkrnl_io.cpp:282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L282)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): async.
```

## Note 3: src/kernel/xboxkrnl/xboxkrnl_io.cpp:374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L374)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): async.
```

## Note 4: src/kernel/xboxkrnl/xboxkrnl_io.cpp:376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L376)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: On Windows it might be worth trying to use Win32 ReadFileScatter
      // here instead of handling it ourselves
```

## Note 5: src/kernel/xboxkrnl/xboxkrnl_io.cpp:428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io.cpp#L428)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): async path.
```

## Note 6: src/kernel/xboxkrnl/xboxkrnl_io_info.cpp:37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L37)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): validate path components individually.
```

## Note 7: src/kernel/xboxkrnl/xboxkrnl_io_info.cpp:91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L91)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): structures to get the size of.
```

## Note 8: src/kernel/xboxkrnl/xboxkrnl_io_info.cpp:131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L131)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): use pointer to fs::entry?
```

## Note 9: src/kernel/xboxkrnl/xboxkrnl_io_info.cpp:217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L217)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): structures to get the size of.
```

## Note 10: src/kernel/xboxkrnl/xboxkrnl_io_info.cpp:411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L411)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): sanity check, XCTD userland code seems to require this.
```

## Note 11: src/kernel/xboxkrnl/xboxkrnl_memory.cpp:231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L231)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: I think it's valid for NtProtectVirtualMemory to span regions, but
  // as of now our implementation will fail in this case. Need to verify.
```

## Note 12: src/kernel/xboxkrnl/xboxkrnl_memory.cpp:533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L533)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): FIXME
```

## Note 13: src/kernel/xboxkrnl/xboxkrnl_memory.cpp:637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L637)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO
```
