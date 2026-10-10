# Xam profile content: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/269).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/kernel/xam/xam_content.cpp:107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_content.cpp#L107)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): disc drive content
```

## Note 2: src/kernel/xam/xam_content.cpp:262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_content.cpp#L262)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): arguments assumed based on XamContentCreate.
```

## Note 3: src/kernel/xam/xam_content_device.cpp:28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_content_device.cpp#L28)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): real information.
//
// Until we expose real information about a HDD device, we
// claim there is 3GB free on a 4GB dummy HDD.
//
// There is a possibility that certain games are bugged in that
// they incorrectly only look at the lower 32-bits of free_bytes,
// when it is a 64-bit value. Which means any size above ~4GB
// will not be recognized properly.
```

## Note 4: src/kernel/xam/xam_info.cpp:79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_info.cpp#L79)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: format this depending on users locale?
```

## Note 5: src/kernel/xam/xam_info.cpp:88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_info.cpp#L88)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: format this depending on users locale?
```

## Note 6: src/kernel/xam/xam_locale.cpp:26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_locale.cpp#L26)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): put these forward decls in a header somewhere.
```

## Note 7: src/kernel/xam/xam_locale.cpp:189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_locale.cpp#L189)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): rework when XConfig is cleanly implemented.
```

## Note 8: src/kernel/xam/xam_task.cpp:47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_task.cpp#L47)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): figure out what this is for
```

## Note 9: src/kernel/xam/xam_user.cpp:161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L161)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): allow proper lookup of arbitrary XUIDs
```

## Note 10: src/kernel/xam/xam_user.cpp:164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L164)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): we assert here, but in case a title passes xuid_count > 1
    // until it's implemented for release builds...
```

## Note 11: src/kernel/xam/xam_user.cpp:233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L233)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): setting validity checking without needing a user profile
  // object.
```

## Note 12: src/kernel/xam/xam_user.cpp:248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L248)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): don't fail? most games don't even check!
```

## Note 13: src/kernel/xam/xam_user.cpp:422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L422)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): does this need the access arg on it?
```

## Note 14: src/kernel/xam/xam_user.cpp:495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L495)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): probably a FILETIME/LARGE_INTEGER, unknown currently
```

## Note 15: src/kernel/xam/xam_user.cpp:696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L696)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): unknown=0,2,3,9
```

## Note 16: src/kernel/xam/xam_user.cpp:726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_user.cpp#L726)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(PermaNull): Implement this properly,
  // For the time being returning 0xDEADF00D will prevent crashing.
```

## Note 17: src/kernel/xam/xam_video.cpp:26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xam/xam_video.cpp#L26)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): actually check to see if these are the same.
```

## Note 18: src/system/xam/content_manager.cpp:430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xam/content_manager.cpp#L430)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Gliniak): Get real error code for this case.
```

## Note 19: src/system/xam/content_manager.cpp:564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xam/content_manager.cpp#L564)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Gliniak): Cleanup this code to care only about handles
  // related to provided content
```

## Note 20: include/rex/system/xam/content_manager.h:39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/xam/content_manager.h#L39)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: check if actual x360 kernel/xam has a value similar to this
```

## Note 21: include/rex/system/xam/content_manager.h:214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/xam/content_manager.h#L214)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): remove use of global lock, it's bad here!
```

## Note 22: include/rex/system/xam/user_profile.h:40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/xam/user_profile.h#L40)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(sabretooth): not sure if this is a union, but it seems likely.
  // Haven't run into cases other than "binary data" yet.
```
