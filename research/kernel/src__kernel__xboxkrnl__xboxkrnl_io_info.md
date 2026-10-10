# Xboxkrnl io info: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_io_info.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L129)

```text
// Internal unique file pointer. Not sure why anyone would want this.
```

## Source note 3, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L154)

```text
// Files that are XCTD compressed begin with the magic 0x0FF512ED but we
```

## Source note 4, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L155)

```text
// shouldn't detect this that way. There's probably a flag somewhere
```

## Source note 5, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L156)

```text
// (attributes?) that defines if it's compressed or not.
```

## Source note 6, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L162)

```text
// Make sure we're working with up-to-date information, just in case the
```

## Source note 7, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L163)

```text
// file size has changed via something other than NtSetInfoFile
```

## Source note 8, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L164)

```text
// (eg. seems NtWriteFile might extend the file in some cases)
```

## Source note 9, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L179)

```text
// Requested by XMountUtilityDrive XAM-task
```

## Source note 10, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L181)

```text
// FILE_BYTE_ALIGNMENT?
```

## Source note 11, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L186)

```text
// Unsupported, for now.
```

## Source note 12, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L313)

```text
// Update the file entry information.
```

## Source note 13, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L322)

```text
// Update the files rex::filesystem::Entry information
```

## Source note 14, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L327)

```text
// Info contains IO Completion handle and completion key
```

## Source note 15, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L341)

```text
// Unsupported, for now.
```

## Source note 16, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L397)

```text
// set for FATX, but we don't do that currently
```

## Source note 17, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_io_info.cpp#L440)

```text
// Unsupported, for now.
```
