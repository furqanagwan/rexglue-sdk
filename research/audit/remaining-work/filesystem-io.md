# Filesystem io: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/261).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/filesystem/devices/host_path_entry.cpp:62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/devices/host_path_entry.cpp#L62)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): pick correct response.
```

## Note 2: src/filesystem/devices/stfs_container_device.cpp:644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/devices/stfs_container_device.cpp#L644)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): optimize if flags.contiguous is set.
```

## Note 3: src/filesystem/entry.cpp:107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/entry.cpp#L107)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): resort? would break iteration?
```

## Note 4: src/filesystem/entry.cpp:160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/entry.cpp#L160)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): update timestamps.
```

## Note 5: src/filesystem/vfs_dump.cpp:42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/vfs_dump.cpp#L42)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Flags specifying the type of device.
```

## Note 6: src/filesystem/vfs_dump.cpp:118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/vfs_dump.cpp#L118)

Disposition: retired reminder. The upstream XE_DEFINE_CONSOLE_APP macro does not belong to the SDK CLI.

```text
// TODO: CONSOLE APP - XE_DEFINE_CONSOLE_APP("xenia-vfs-dump", rex::filesystem::vfs_dump_main,
//                       "[source] [dump_path]", "source", "dump_path");
```

## Note 7: src/filesystem/virtual_file_system.cpp:199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/filesystem/virtual_file_system.cpp#L199)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): should 'is_directory' remain as a bool or should it be
  // flipped to a generic FileAttributeFlags?
```

## Note 8: src/system/xfile.cpp:39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xfile.cpp#L39)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): signal that the file is closing?
```

## Note 9: src/system/xfile.cpp:219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/system/xfile.cpp#L219)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: not sure if this is meant to change depending on buffer address?
  // (only game seen using this always seems to use 4096-byte buffers)
```

## Note 10: include/rex/filesystem/devices/stfs_xbox.h:471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/filesystem/devices/stfs_xbox.h#L471)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: title/system updates contain more data after XContentMetadata, seems
  // to affect header.header_size
```

## Note 11: include/rex/filesystem/file.h:35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/filesystem/file.h#L35)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Parameters
```

## Note 12: include/rex/filesystem/file.h:45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/filesystem/file.h#L45)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Parameters
```

## Note 13: include/rex/system/xfile.h:140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/system/xfile.h#L140)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): create flags, open state, etc.
```
