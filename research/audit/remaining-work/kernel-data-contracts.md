# Kernel data contracts: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/272).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/kernel/xboxkrnl/xboxkrnl_crypt.cpp:190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L190)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Size of this struct hasn't been confirmed yet.
```

## Note 2: src/kernel/xboxkrnl/xboxkrnl_crypt.cpp:477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L477)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify the order in keytabenc and everything in keytabdec.
```

## Note 3: src/kernel/xboxkrnl/xboxkrnl_crypt.cpp:578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_crypt.cpp#L578)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Array of keys we need
```

## Note 4: src/kernel/xboxkrnl/xboxkrnl_rtl.cpp:65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L65)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: This assumes as_array returns rex::be
```

## Note 5: src/kernel/xboxkrnl/xboxkrnl_rtl.cpp:249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L249)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): maybe use MultiByteToUnicode on Win32? would require
  // swapping.
```

## Note 6: src/kernel/xboxkrnl/xboxkrnl_rtl.cpp:269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L269)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): maybe use UnicodeToMultiByte on Win32?
```

## Note 7: src/kernel/xboxkrnl/xboxkrnl_rtl.cpp:558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L558)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we even need this?
```

## Note 8: src/kernel/xboxkrnl/xboxkrnl_rtl.cpp:563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L563)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we even need this?
```

## Note 9: src/kernel/xboxkrnl/xboxkrnl_rtl.cpp:568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_rtl.cpp#L568)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): do we even need this?
```

## Note 10: src/kernel/xboxkrnl/xboxkrnl_xconfig.cpp:34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_xconfig.cpp#L34)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): have real structs here that just get copied from.
  // https://free60project.github.io/wiki/XConfig.html
  // https://github.com/oukiar/freestyledash/blob/master/Freestyle/Tools/Generic/ExConfig.h
```

## Note 11: src/kernel/xboxkrnl/xboxkrnl_xconfig.cpp:61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/kernel/xboxkrnl/xboxkrnl_xconfig.cpp#L61)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): get this value.
```
