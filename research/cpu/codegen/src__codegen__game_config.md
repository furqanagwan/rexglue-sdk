# Game config: codegen source notes

This record preserves technical and API notes moved from `src/codegen/game_config.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L22)

```text
// The ShellVisuals images and the sizes the GDK's config editor produces.
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L23)

```text
// makepkg pack refuses a config without SplashScreenImage.
```

## Source note 3, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L50)

```text
// ST_NonEmptyString: no leading or trailing whitespace.
```

## Source note 4, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L56)

```text
// ST_VersionQuad: four parts, each 0-65535 without leading zeros.
```

## Source note 5, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L76)

```text
// ST_Executable within ST_FileName: a relative path ending in .exe whose
```

## Source note 6, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L77)

```text
// parts neither start nor end with '.'.
```

## Source note 7, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L166)

```text
// One fixed-Huffman deflate block (RFC 1951 3.2.6) whose only back-references
```

## Source note 8, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L167)

```text
// are runs of the previous byte (distance 1). Enough for flat-color images.
```

## Source note 9, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L172)

```text
// BTYPE 01: fixed Huffman codes
```

## Source note 10, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L183)

```text
// distance code 0: distance 1
```

## Source note 11, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L189)

```text
// end of block
```

## Source note 12, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L207)

```text
// Huffman codes are sent most significant bit first.
```

## Source note 13, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L263)

```text
// ST_PackageName: ST_AsciiIdentifier ([-_. A-Za-z0-9] without '_' or ' '), 3-50.
```

## Source note 14, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L267)

```text
// ST_DistinguishedName, restricted to the common attribute keys.
```

## Source note 15, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L351)

```text
// Titles link the dynamic MSVC runtime (rexruntime and the title itself), so
```

## Source note 16, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L352)

```text
// a package must pull in the VC++ framework package (makepkg validator).
```

## Source note 17, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L368)

```text
// 8-bit RGBA: the Store validator wants 24 bpp plus alpha.
```

## Source note 18, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L372)

```text
// Each scanline uses the Sub filter: the first pixel is the color and the
```

## Source note 19, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/game_config.cpp#L373)

```text
// rest are zero differences, which compress to runs.
```
