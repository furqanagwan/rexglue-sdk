# Host path device: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/devices/host_path_device.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L38)

```text
// Create the path.
```

## Source note 2, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L60)

```text
// The filesystem will have stripped our prefix off already, so the path will
```

## Source note 3, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L61)

```text
// be in the form:
```

## Source note 4, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L62)

```text
// some\PATH.foo
```

## Source note 5, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L68)

```text
// Fallback to a lazy case-insensitive host lookup when an entry is missing
```

## Source note 6, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L69)

```text
// from the in-memory tree (for example because casing differs on Linux).
```

## Source note 7, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L78)

```text
// Stat the exact name first: enumerating a directory of hundreds of
```

## Source note 8, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L79)

```text
// archives costs milliseconds a walk. Only casing mismatch reaches
```

## Source note 9, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/host_path_device.cpp#L80)

```text
// the scan below.
```
