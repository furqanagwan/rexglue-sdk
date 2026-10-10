# Content manager: system source notes

This record preserves technical and API notes moved from `src/system/xam/content_manager.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L57)

```text
/*allow_share_delete=*/
```

## Source note 2, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L104)

```text
// Package root path:
```

## Source note 3, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L105)

```text
// content_root/xuid/title_id/content_type/
```

## Source note 4, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L113)

```text
// DLCs are stored in common directory
```

## Source note 5, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L118)

```text
// Content path:
```

## Source note 6, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L119)

```text
// content_root/xuid/title_id/content_type/data_file_name/
```

## Source note 7, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L140)

```text
// Header root path:
```

## Source note 8, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L141)

```text
// content_root/xuid/title_id/Headers/content_type/filename.header
```

## Source note 9, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L155)

```text
// Search path:
```

## Source note 10, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L156)

```text
// content_root/xuid/title_id/type_name/*
```

## Source note 11, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L161)

```text
// Directories only.
```

## Source note 12, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L226)

```text
// Written whole or not at all, so a crash never leaves a torn header.
```

## Source note 13, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L246)

```text
// Guest writes go straight to host files; flushing makes them durable.
```

## Source note 14, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L258)

```text
// Content created before a crash may be missing its header; the package
```

## Source note 15, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L259)

```text
// is only listed with its metadata once the header exists.
```

## Source note 16, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L353)

```text
// The license_mask cvar grants extra licenses to every package, as it does
```

## Source note 17, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L354)

```text
// for XamContentGetLicenseMask (Edge aac25ad0c: any nonzero mask, not > 1).
```

## Source note 18, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L368)

```text
// Closing content commits it on the console. Make the writes durable before
```

## Source note 19, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L369)

```text
// the handles go, so a save closed without XamContentFlush still survives a
```

## Source note 20, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L370)

```text
// system crash (xenia-canary #1220). The package is closed either way; a
```

## Source note 21, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L371)

```text
// failed flush is reported.
```

## Source note 22, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L380)

```text
// Some games use different casing between Create and Close (e.g. "save" vs "SAVE")
```

## Source note 23, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L469)

```text
// Unmount phase: tolerant of not-mounted state
```

## Source note 24, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L480)

```text
// Delete phase: remove package directory and .header file
```

## Source note 25, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L507)

```text
// Per-game per-profile data location:
```

## Source note 26, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L508)

```text
// content_root/title_id/profile/user_name
```

## Source note 27, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L515)

```text
// Resolve kCurrentlyRunningTitleId so both sides compare actual title IDs.
```

## Source note 28, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L529)

```text
// Match on content_type + file_name + resolved title_id.
```

## Source note 29, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L530)

```text
// device_id is a virtual storage selector, not a content identifier.
```

## Source note 30, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L592)

```text
// Ensure parent directory exists
```

## Source note 31, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L608)

```text
// 4 MiB
```

## Source note 32, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L635)

```text
// Mount the STFS package as a virtual filesystem device
```

## Source note 33, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L641)

```text
// Derive install destination:
```

## Source note 34, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L642)

```text
// root_path_/0000000000000000/{title_id}/00000002/{filename}/
```

## Source note 35, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L652)

```text
// Read display name from STFS metadata
```

## Source note 36, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L662)

```text
// Create destination directory
```

## Source note 37, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L669)

```text
// Extract all files breadth-first
```

## Source note 38, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L692)

```text
// Compute license mask from STFS header licenses
```

## Source note 39, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xam/content_manager.cpp#L700)

```text
// Write .header file
```
