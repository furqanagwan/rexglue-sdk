# Stfs xbox: filesystem source notes

This record preserves technical and API notes moved from `include/rex/filesystem/devices/stfs_xbox.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L27)

```text
// Import kernel content types for STFS structures
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L31)

```text
// Convert FAT timestamp to 100-nanosecond intervals since January 1, 1601 (UTC)
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L34)

```text
// 80 is the difference between 1980 (FAT) and 1900 (tm);
```

## Source note 4, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L40)

```text
// the value stored in 2-seconds intervals
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L48)

```text
// 11644473600LL is a difference between 1970 and 1601
```

## Source note 6, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L52)

```text
// Structs used for interchange between Xenia and actual Xbox360 kernel/XAM
```

## Source note 7, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L77)

```text
/* STFS structures */
```

## Source note 8, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L85)

```text
// if set, only uses a single backing-block
```

## Source note 9, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L86)

```text
// per hash table (no resiliency),
```

## Source note 10, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L87)

```text
// otherwise uses two
```

## Source note 11, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L88)

```text
// if set, uses secondary backing-block
```

## Source note 12, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L89)

```text
// for the highest-level hash table
```

## Source note 13, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L113)

```text
// unallocated but doesn't exist in package (needs to expand)?
```

## Source note 14, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L114)

```text
// unallocated but exists in package?
```

## Source note 15, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L159)

```text
// num L0 blocks covered by this table?
```

## Source note 16, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L207)

```text
/* SVOD structures */
```

## Source note 17, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L232)

```text
/* XContent structures */
```

## Source note 18, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L274)

```text
// metadata_version 2 adds 3 languages inside thumbnail/title_thumbnail space
```

## Source note 19, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L336)

```text
// no room for this lang, read from english slot..
```

## Source note 20, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L348)

```text
// Invalid language ID?
```

## Source note 21, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L361)

```text
// no room for this lang, read from english slot..
```

## Source note 22, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L373)

```text
// Invalid language ID?
```

## Source note 23, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L394)

```text
// no room for this lang, store in english slot..
```

## Source note 24, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L406)

```text
// Invalid language ID?
```

## Source note 25, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L420)

```text
// no room for this lang, store in english slot..
```

## Source note 26, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/filesystem/devices/stfs_xbox.h#L432)

```text
// Invalid language ID?
```
