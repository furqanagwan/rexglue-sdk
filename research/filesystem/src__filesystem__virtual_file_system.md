# Virtual file system: filesystem source notes

This record preserves technical and API notes moved from `src/filesystem/virtual_file_system.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L28)

```text
// Delete all devices.
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L29)

```text
// This will explode if anyone is still using data from them.
```

## Source note 3, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L96)

```text
// Found symlink!
```

## Source note 4, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L108)

```text
// Resolve relative paths
```

## Source note 5, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L111)

```text
// Resolve symlinks.
```

## Source note 6, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L118)

```text
// Find the device.
```

## Source note 7, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L124)

```text
// Supress logging the error for ShaderDumpxe:\CompareBackEnds as this is
```

## Source note 8, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L125)

```text
// not an actual problem nor something we care about.
```

## Source note 9, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L157)

```text
// Create all required directories recursively.
```

## Source note 10, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L189)

```text
// Can't delete root.
```

## Source note 11, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L199)

```text
// Cleanup access.
```

## Source note 12, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L210)

```text
// Lookup host device/parent path.
```

## Source note 13, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L211)

```text
// If no device or parent, fail.
```

## Source note 14, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L234)

```text
// If the cached entry does not exist on host anymore, invalidate it.
```

## Source note 15, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L247)

```text
// Check if exists (if we need it to), or that it doesn't (if it shouldn't).
```

## Source note 16, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L251)

```text
// Must exist.
```

## Source note 17, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L258)

```text
// Must not exist.
```

## Source note 18, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L265)

```text
// Either way, ok.
```

## Source note 19, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L269)

```text
// Verify permissions.
```

## Source note 20, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L274)

```text
// Match Xenia behavior: downgrade to read access instead of failing.
```

## Source note 21, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L281)

```text
// Remember that we are creating this new, instead of replacing.
```

## Source note 22, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L285)

```text
// May need to delete, if it exists.
```

## Source note 23, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L288)

```text
// Shouldn't be possible to hit this.
```

## Source note 24, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L302)

```text
// Normal open.
```

## Source note 25, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L318)

```text
// Create if needed (either new or as a replacement).
```

## Source note 26, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/filesystem/virtual_file_system.cpp#L325)

```text
// Open.
```
