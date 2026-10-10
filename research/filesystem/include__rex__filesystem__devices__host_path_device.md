# Host path device: filesystem source notes

This record preserves technical and API notes moved from `include/rex/filesystem/devices/host_path_device.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/host_path_device.h#L33)

```text
// NOTE(tomc): When true, host file handles open with FILE_SHARE_DELETE so an open read
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/host_path_device.h#L34)

```text
// handle (e.g. a save-slot preview) does not block an overwrite's
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/host_path_device.h#L35)

```text
// delete+recreate. Opt-in per device: content/save devices set it; game-data
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/host_path_device.h#L36)

```text
// and read-only devices leave it off (see a5c3a963 ghost-file fix).
```
