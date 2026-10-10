# Entry: filesystem source notes

This record preserves technical and API notes moved from `include/rex/filesystem/entry.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L36)

```text
// Matches https://source.winehq.org/source/include/winternl.h#1591.
```

## Source note 2, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L47)

```text
// If exist replace, else create.
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L49)

```text
// If exist open, else error.
```

## Source note 4, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L51)

```text
// If exist error, else create.
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L53)

```text
// If exist open, else create.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L55)

```text
// If exist open and overwrite, else error.
```

## Source note 7, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L57)

```text
// If exist open and overwrite, else create.
```

## Source note 8, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L61)

```text
// Reuse rex::filesystem definition.
```

## Source note 9, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L106)

```text
/// Walks @p path component-by-component starting from this entry.
```

## Source note 10, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L107)

```text
/// Returns this entry when @p path is empty (i.e. zero path components),
```

## Source note 11, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L108)

```text
/// nullptr if any intermediate component does not exist.
```

## Source note 12, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L122)

```text
// If successful, out_file points to a new file. When finished, call
```

## Source note 13, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/entry.h#L123)

```text
// file->Destroy()
```
