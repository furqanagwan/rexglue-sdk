# Disc image entry: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/devices/disc_image_entry.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_entry.cpp#L46)

```text
// Only allow reads.
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_entry.cpp#L53)

```text
// Preserve the mapping API for existing callers using an owned snapshot.
```

## Source note 3, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/devices/disc_image_entry.cpp#L54)

```text
// No memory pages are backed by a file on media that can disappear.
```
