# Disc image device: filesystem source notes

This record preserves technical and API notes moved from `include/rex/filesystem/devices/disc_image_device.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/disc_image_device.h#L31)

```text
// Reader injection for synthetic media and deterministic I/O failure tests.
```

## Source note 2, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/disc_image_device.h#L50)

```text
// Exact positioned read. Short reads and host errors are failures, never a
```

## Source note 3, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/disc_image_device.h#L51)

```text
// pointer into removable media. File handles remain serialized.
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/disc_image_device.h#L53)

```text
// Called only after a failed read; recovery is serialized across guest I/O.
```

## Source note 5, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/disc_image_device.h#L55)

```text
// Caller validates the source executable too. Directory layout must match
```

## Source note 6, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/disc_image_device.h#L56)

```text
// before retaining existing guest file entries and replacing the reader.
```
