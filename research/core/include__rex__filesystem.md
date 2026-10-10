# Filesystem: core source notes

This record preserves technical and API notes moved from `include/rex/filesystem.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L34)

```text
// Get executable path.
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L37)

```text
// Get executable folder.
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L40)

```text
// Get user folder.
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L43)

```text
// Creates the parent folder of the specified path if needed.
```

## Source note 5, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L44)

```text
// This can be used to ensure the destination path for a new file exists before
```

## Source note 6, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L45)

```text
// attempting to create it.
```

## Source note 7, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L48)

```text
// Creates an empty file at the given path, overwriting if it exists.
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L51)

```text
// Replaces the file at `path` with `bytes` through a flushed sibling
```

## Source note 9, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L52)

```text
// `<path>.tmp` and a rename, so a crash leaves the old contents or the new,
```

## Source note 10, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L53)

```text
// never a torn file. Returns false if a step failed; the target is then
```

## Source note 11, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L54)

```text
// unchanged.
```

## Source note 12, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L57)

```text
// Opens the file at the given path with the specified mode.
```

## Source note 13, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L58)

```text
// This behaves like fopen and the returned handle can be used with stdio.
```

## Source note 14, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L61)

```text
// Wrapper for the 64-bit version of fseek, returns true on success.
```

## Source note 15, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L64)

```text
// Wrapper for the 64-bit version of ftell, returns a positive value on success.
```

## Source note 16, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L67)

```text
// Reduces the size of a stdio file opened for writing. The file pointer is
```

## Source note 17, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L68)

```text
// clamped. If this returns false, the size of the file and the file pointer are
```

## Source note 18, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L69)

```text
// undefined.
```

## Source note 19, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L73)

```text
// Implies kFileReadData.
```

## Source note 20, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L75)

```text
// Implies kFileWriteData.
```

## Source note 21, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L86)

```text
// Opens the file, failing if it doesn't exist.
```

## Source note 22, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L87)

```text
// The desired_access bitmask denotes the permissions on the file.
```

## Source note 23, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L96)

```text
// Reads the requested number of bytes from the file starting at the given
```

## Source note 24, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L97)

```text
// offset. The total number of bytes read is returned only if the complete
```

## Source note 25, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L98)

```text
// read succeeds.
```

## Source note 26, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L102)

```text
// Writes the given buffer to the file starting at the given offset.
```

## Source note 27, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L103)

```text
// The total number of bytes written is returned only if the complete
```

## Source note 28, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L104)

```text
// write succeeds.
```

## Source note 29, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L108)

```text
// Set length of the file in bytes.
```

## Source note 30, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L111)

```text
// Flushes any pending write buffers to the underlying filesystem.
```

## Source note 31, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem.h#L112)

```text
// Returns false if the host reports the flush failed.
```
