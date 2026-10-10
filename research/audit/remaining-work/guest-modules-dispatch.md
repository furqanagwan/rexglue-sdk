# Guest modules dispatch: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/275).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/system/function_dispatcher.cpp:164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/function_dispatcher.cpp#L164)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: stack-arg path assumes 32-bit values; 64-bit and float args are wrong.
```

## Note 2: src/system/kernel_module.cpp:87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/kernel_module.cpp#L87)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Does this even work for kernel modules?
```

## Note 3: src/system/kernel_state.cpp:516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/kernel_state.cpp#L516)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): lookup module from caller address.
```

## Note 4: src/system/kernel_state.cpp:650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/kernel_state.cpp#L650)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): move someplace more appropriate (out of ctor, but around
  // here).
```

## Note 5: src/system/kernel_state.cpp:1077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/kernel_state.cpp#L1077)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): Do we need this?
  //             Xenia would iterate user_modules_ and call function_dispatcher()->Execute() for
  //             each Note that this would require reimplementation of guest thread management
```

## Note 6: src/system/kernel_state.cpp:1089

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/kernel_state.cpp#L1089)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): Do we need this? Same idea as OnThreadExecute
```

## Note 7: src/system/kernel_state.cpp:1182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/kernel_state.cpp#L1182)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): there are games that check 'length' of overlapped as
  // an indication of success. WTF?
  // Setting length to -1 when not success seems to be helping.
```

## Note 8: src/system/lzx.cpp:121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/lzx.cpp#L121)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): should this be set regardless if source window data is
      // available or not?
```

## Note 9: src/system/lzx.cpp:184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/lzx.cpp#L184)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: make this less ugly
```

## Note 10: src/system/user_module.cpp:55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/user_module.cpp#L55)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): make this code shared?
```

## Note 11: src/system/user_module.cpp:380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/user_module.cpp#L380)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Find a nicer way to represent that here.
```

## Note 12: src/system/user_module.cpp:400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/user_module.cpp#L400)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we need this?
```

## Note 13: src/system/xex_module.cpp:348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xex_module.cpp#L348)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: a way to do without a copy/alloc?
```

## Note 14: src/system/xex_module.cpp:373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xex_module.cpp#L373)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: should we use new_image_size here instead?
```

## Note 15: src/system/xex_module.cpp:650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xex_module.cpp#L650)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: a way to do without a copy/alloc?
```

## Note 16: src/system/xex_module.cpp:977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xex_module.cpp#L977)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: Don't know if 32 is the actual limit, but haven't seen more than
    // 2.
```

## Note 17: src/system/xmodule.cpp:94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xmodule.cpp#L94)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Find a way to call RestoreObject here before UserModule::Restore.
```

## Note 18: include/rex/system/util/xex2_info.h:162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/util/xex2_info.h#L162)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): figure out how stored.
  /*XEX_SYSTEM_ALLOW_NETWORK_READ_CANCEL            = 0x0,
  XEX_SYSTEM_UNINTERRUPTABLE_READS                = 0x0,
  XEX_SYSTEM_REQUIRE_FULL_EXPERIENCE              = 0x0,
  XEX_SYSTEM_GAME_VOICE_REQUIRED_UI               = 0x0,
  XEX_SYSTEM_CAMERA_ANGLE                         = 0x0,
  XEX_SYSTEM_SKELETAL_TRACKING_REQUIRED           = 0x0,
  XEX_SYSTEM_SKELETAL_TRACKING_SUPPORTED          = 0x0,*/
```
