# Stfs container file: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/devices/stfs_container_file.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_file.cpp#L45)

```text
// Doesn't begin in this region. Skip it.
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_file.cpp#L55)

```text
// a block record in a data file that does not exist
```

## Source note 3, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_file.cpp#L65)

```text
// A block past the end of a truncated package: stop at what was read
```

## Source note 4, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/stfs_container_file.cpp#L66)

```text
// rather than place later blocks at the wrong offset.
```
