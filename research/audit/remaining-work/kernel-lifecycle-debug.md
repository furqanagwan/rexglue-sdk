# Kernel lifecycle debug: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/271).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/kernel/xboxkrnl/cert_monitor.cpp:31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/cert_monitor.cpp#L31)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Implement cert monitor callback if needed
```

## Note 2: src/kernel/xboxkrnl/debug_monitor.cpp:58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/debug_monitor.cpp#L58)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Implement PIX callback if needed
```

## Note 3: src/kernel/xboxkrnl/xboxkrnl_debug.cpp:45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L45)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): check record->number_parameters to make sure it's a
  // correct size.
```

## Note 4: src/kernel/xboxkrnl/xboxkrnl_debug.cpp:59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L59)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): cvar for thread name encoding for conversion, some games use
  // SJIS and there's no way to automatically know this.
```

## Note 5: src/kernel/xboxkrnl/xboxkrnl_debug.cpp:79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L79)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): unwinding required here?
```

## Note 6: src/kernel/xboxkrnl/xboxkrnl_debug.cpp:141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_debug.cpp#L141)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): unwinding.
  // This is going to suck.
```

## Note 7: src/kernel/xboxkrnl/xboxkrnl_error.cpp:37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_error.cpp#L37)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): replace these with named error codes
```

## Note 8: src/kernel/xboxkrnl/xboxkrnl_hal.cpp:31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_hal.cpp#L31)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvank): diediedie much more gracefully
  // Not sure how to blast back up the stack in LLVM without exceptions, though.
```

## Note 9: src/kernel/xboxkrnl/xboxkrnl_hid.cpp:25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_hid.cpp#L25)

Disposition: retained investigation; not yet reproduced or resolved.

```text
/* TODO(gibbed):
   * Games check for the following errors:
   *   0xC000009D - translated to 0x48F  - ERROR_DEVICE_NOT_CONNECTED
   *   0x103      - translated to 0x10D2 - ERROR_EMPTY
   * Other errors appear to be ignored?
   *
   * unk1 is 0
   * unk2 is a pointer to &unk3[2], possibly a 6-byte buffer
   * unk3 is a pointer to a 20-byte buffer
   */
```

## Note 10: src/kernel/xboxkrnl/xboxkrnl_misc.cpp:26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_misc.cpp#L26)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): can we do anything about exceptions?
```

## Note 11: src/kernel/xboxkrnl/xboxkrnl_module.cpp:52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L52)

Disposition: retired reminder. CPU-JIT PIX execution is outside ADR-004.

```text
// TODO: JIT - PIX commands require JIT processor->Execute
  // if (!REXCVAR_GET(kernel_pix)) {
  //   return false;
  // }
  // ...
```

## Note 12: src/kernel/xboxkrnl/xboxkrnl_module.cpp:84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L84)

Disposition: retired reminder. CPU-JIT trampoline generation is outside ADR-004.

```text
// TODO: JIT - GenerateTrampoline requires JIT
    // lpKeDebugMonitorData->callback_fn =
    //     GenerateTrampoline("KeDebugMonitorCallback", KeDebugMonitorCallback);
```

## Note 13: src/kernel/xboxkrnl/xboxkrnl_module.cpp:104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L104)

Disposition: retired reminder. CPU-JIT trampoline generation is outside ADR-004.

```text
// TODO: JIT - GenerateTrampoline requires JIT
    // lpKeCertMonitorData->callback_fn =
    //     GenerateTrampoline("KeCertMonitorCallback", KeCertMonitorCallback);
```

## Note 14: src/kernel/xboxkrnl/xboxkrnl_module.cpp:159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_module.cpp#L159)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): set this to the actual module name.
```

## Note 15: src/kernel/xboxkrnl/xboxkrnl_threading.cpp:593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L593)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): increment thread priority?
  // TODO(benvanik): wait?
```

## Note 16: src/kernel/xboxkrnl/xboxkrnl_threading.cpp:594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L594)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): wait?
```

## Note 17: src/kernel/xboxkrnl/xboxkrnl_video.cpp:385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_video.cpp#L385)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): what does this mean, I forget:
  // callbacks get 0, r3, r4
```
