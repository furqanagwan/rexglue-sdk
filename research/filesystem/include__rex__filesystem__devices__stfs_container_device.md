# Stfs container device: filesystem source notes

This record preserves technical and API notes moved from `include/rex/filesystem/devices/stfs_container_device.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_container_device.h#L28)

```text
// https://free60project.github.io/wiki/STFS.html
```

## Source note 2, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_container_device.h#L54)

```text
// Reads and validates the StfsHeader from an STFS package file without
```

## Source note 3, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_container_device.h#L55)

```text
// mounting the device. Returns nullptr if the file is missing, too small,
```

## Source note 4, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_container_device.h#L56)

```text
// or has an invalid magic.
```

## Source note 5, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_container_device.h#L142)

```text
// SVOD directory nodes already read, so a node that points back at an
```

## Source note 6, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_container_device.h#L143)

```text
// earlier one ends the walk instead of recursing forever.
```
