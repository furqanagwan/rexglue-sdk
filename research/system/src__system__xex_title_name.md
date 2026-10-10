# Xex title name: system source notes

This record preserves technical and API notes moved from `src/system/xex_title_name.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 2

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L2)

```text
// The display name in a game executable's XDBF resource, for naming the game
```

## Source note 2, line 3

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L3)

```text
// a mismatched source holds. The bytes are whatever file the player chose, so
```

## Source note 3, line 4

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L4)

```text
// every offset is bounds-checked; the runtime's XEX loader and XDBF reader
```

## Source note 4, line 5

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L5)

```text
// trust a title already loaded and are not used here.
```

## Source note 5, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L16)

```text
// xex_module.cpp: AES-128-CBC with a zero IV, as XEX2 images use.
```

## Source note 6, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L23)

```text
// The XEX2 retail and development kit keys (public, as in xex_module.cpp).
```

## Source note 7, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L56)

```text
// An optional header's value (key ending 00 or 01) or offset (otherwise).
```

## Source note 8, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L72)

```text
// The loaded image, as XexModule::ReadImage lays it out.
```

## Source note 9, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L92)

```text
// basic: data blocks, each followed by zeros
```

## Source note 10, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L107)

```text
// normal (LZX); delta patches carry no resources
```

## Source note 11, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L109)

```text
// Blocks: a 4-byte size and 20-byte hash for the next block, then 2-byte
```

## Source note 12, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L110)

```text
// sized chunks of LZX data ending with a zero size.
```

## Source note 13, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L140)

```text
// The title string (0x8000) in the XDBF's default language, else English.
```

## Source note 14, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L143)

```text
// 'XDBF'
```

## Source note 15, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L158)

```text
// 'XSTC'
```

## Source note 16, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L162)

```text
// 'XSTR'
```

## Source note 17, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xex_title_name.cpp#L204)

```text
// Retail images first; a wrong key decodes to bytes without an XDBF.
```
