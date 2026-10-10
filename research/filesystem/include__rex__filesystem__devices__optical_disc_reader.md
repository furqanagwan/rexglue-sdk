# Optical disc reader: filesystem source notes

This record preserves technical and API notes moved from `include/rex/filesystem/devices/optical_disc_reader.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 6

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/optical_disc_reader.h#L6)

```text
// Only explicit drive-letter optical paths (\\.\D:), never physical disks.
```

## Source note 2, line 9

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/optical_disc_reader.h#L9)

```text
// The underlying reader requires sector-aligned offsets, lengths and buffers.
```

## Source note 3, line 10

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/optical_disc_reader.h#L10)

```text
// Injection lets synthetic tests enforce the same contract as unbuffered I/O.
```
