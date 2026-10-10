# Vfs dump: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/vfs_dump.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/vfs_dump.cpp#L48)

```text
// Run through all the files, breadth-first style.
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/vfs_dump.cpp#L53)

```text
// Allocate a buffer when needed.
```

## Source note 3, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/vfs_dump.cpp#L87)

```text
// Can't map the file into memory. Read it into a temporary buffer.
```

## Source note 4, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/vfs_dump.cpp#L89)

```text
// Resize the buffer.
```

## Source note 5, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/vfs_dump.cpp#L94)

```text
// Allocate a buffer rounded up to the nearest 512MB.
```
