# File: kernel source notes

This record preserves technical and API notes moved from `src/kernel/crt/file.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L254)

```text
// 0x00 dwFileAttributes
```

## Source note 2, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L256)

```text
// 0x04 ftCreationTime.Low
```

## Source note 3, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L257)

```text
// 0x08 ftCreationTime.High
```

## Source note 4, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L259)

```text
// 0x0C ftLastAccessTime.Low
```

## Source note 5, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L260)

```text
// 0x10 ftLastAccessTime.High
```

## Source note 6, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L262)

```text
// 0x14 ftLastWriteTime.Low
```

## Source note 7, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L263)

```text
// 0x18 ftLastWriteTime.High
```

## Source note 8, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L264)

```text
// 0x1C nFileSizeHigh
```

## Source note 9, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L265)

```text
// 0x20 nFileSizeLow
```

## Source note 10, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L266)

```text
// 0x24 dwReserved0, 0x28 dwReserved1 already zero
```

## Source note 11, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L268)

```text
// 0x2C cFileName[260]
```

## Source note 12, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L271)

```text
// 0x130 cAlternateFileName[14] already zero
```

## Source note 13, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L340)

```text
// Win32 MoveFileA fails if the destination already exists; callers wanting
```

## Source note 14, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L341)

```text
// overwrite semantics use MoveFileExA with MOVEFILE_REPLACE_EXISTING.
```

## Source note 15, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L382)

```text
// Fill WIN32_FILE_ATTRIBUTE_DATA (GetFileExInfoStandard = 0)
```

## Source note 16, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L386)

```text
// ftCreationTime.Low
```

## Source note 17, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L387)

```text
// ftCreationTime.High
```

## Source note 18, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L388)

```text
// ftLastAccessTime.Low
```

## Source note 19, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L389)

```text
// ftLastAccessTime.High
```

## Source note 20, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L390)

```text
// ftLastWriteTime.Low
```

## Source note 21, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L391)

```text
// ftLastWriteTime.High
```

## Source note 22, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L435)

```text
// VFS doesn't support modifying timestamps; report success.
```

## Source note 23, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L448)

```text
// FILETIME: { dwLowDateTime, dwHighDateTime }
```

## Source note 24, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L467)

```text
// Open source for reading
```

## Source note 25, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L478)

```text
// Open/create destination
```

## Source note 26, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L491)

```text
// Copy data in 64KB chunks
```

## Source note 27, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/crt/file.cpp#L601)

```text
// XAM exports -- same implementations, for games that import file I/O from xam.xex
```
