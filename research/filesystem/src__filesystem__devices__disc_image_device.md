# Disc image device: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/devices/disc_image_device.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_device.cpp#L59)

```text
// Another guest I/O thread may already have repaired this source.
```

## Source note 2, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_device.cpp#L89)

```text
// FileHandle's Windows implementation uses DWORD read lengths. Bounded
```

## Source note 3, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_device.cpp#L90)

```text
// chunks also prevent a single request from consuming enormous buffers.
```

## Source note 4, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_device.cpp#L120)

```text
// Preserve the existing supported game-partition offsets.
```

## Source note 5, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_device.cpp#L178)

```text
// Iterative in-order traversal preserves directory enumeration order without
```

## Source note 6, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_device.cpp#L179)

```text
// recursing down a malicious, unbalanced directory-entry tree.
```
