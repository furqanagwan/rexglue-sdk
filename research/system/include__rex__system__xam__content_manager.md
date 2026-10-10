# Content manager: system source notes

This record preserves technical and API notes moved from `include/rex/system/xam/content_manager.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L37)

```text
// If set in XCONTENT_AGGREGATE_DATA, will be substituted with the running
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L38)

```text
// titles ID
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L46)

```text
// this should be be<uint16_t>, but that stops copy constructor being
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L47)

```text
// generated...
```

## Source note 5, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L54)

```text
// Some games use this padding field as a null-terminator, as eg.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L55)

```text
// DLC packages usually fill the entire file_name_raw array
```

## Source note 7, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L56)

```text
// Not every game sets it to 0 though, so make sure any file_name_raw reads
```

## Source note 8, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L57)

```text
// only go up to 42 chars!
```

## Source note 9, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L61)

```text
// Package is located via device_id/content_type/file_name, so only need to
```

## Source note 10, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L62)

```text
// compare those
```

## Source note 11, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L78)

```text
// Some games (e.g. 584108A9) require multiple null-terminators for it to
```

## Source note 12, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L79)

```text
// read the string properly, blanking the array should take care of that
```

## Source note 13, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L90)

```text
// Some games rely on padding field acting as a null-terminator...
```

## Source note 14, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L97)

```text
// some titles store XUID here?
```

## Source note 15, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L112)

```text
// Package is located via device_id/title_id/content_type/file_name, so only
```

## Source note 16, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L113)

```text
// need to compare those
```

## Source note 17, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L134)

```text
// The user the package was opened for.
```

## Source note 18, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L165)

```text
// XamContentFlush: makes the open root's written files durable and ensures
```

## Source note 19, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L166)

```text
// its header exists. X_ERROR_FILE_NOT_FOUND if the root is not open.
```

## Source note 20, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L182)

```text
// The host folder of a package, open or not (the guide's Manage Storage).
```

## Source note 21, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L189)

```text
// Returns the host filesystem path for an open content package, or empty.
```

## Source note 22, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L192)

```text
// Installs an STFS content package from an arbitrary host path.
```

## Source note 23, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L193)

```text
// Extracts the package into root_path_/0000000000000000/{title_id}/00000002/{filename}/
```

## Source note 24, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xam/content_manager.h#L194)

```text
// and writes a .header file for XAM enumeration.
```
