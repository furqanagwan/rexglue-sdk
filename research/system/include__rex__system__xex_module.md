# Xex module: system source notes

This record preserves technical and API notes moved from `include/rex/system/xex_module.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L75)

```text
// Calculate the new total size of the XEX image from its headers.
```

## Source note 2, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L79)

```text
// Byteswap the bitfield manually.
```

## Source note 3, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L107)

```text
// PE FileHeader TimeDateStamp (Unix epoch seconds) recorded by the linker.
```

## Source note 4, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L110)

```text
// Gets an optional header. Returns NULL if not found.
```

## Source note 5, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L111)

```text
// Special case: if key & 0xFF == 0x00, this function will return the value,
```

## Source note 6, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L112)

```text
// not a pointer! This assumes out_ptr points to uint32_t.
```

## Source note 7, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L116)

```text
// Ultra-cool templated version
```

## Source note 8, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L117)

```text
// Special case: if key & 0xFF == 0x00, this function will return the value,
```

## Source note 9, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L118)

```text
// not a pointer! This assumes out_ptr points to uint32_t.
```

## Source note 10, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L143)

```text
// Exception DataDirectory accessors (for PDATA table)
```

## Source note 11, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L144)

```text
// These return the correct PDATA location from the PE Optional Header,
```

## Source note 12, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L145)

```text
// which may differ from the .pdata section's VirtualAddress.
```

## Source note 13, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L152)

```text
// Binary introspection overrides
```

## Source note 14, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L208)

```text
// Holds the xex header
```

## Source note 15, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L209)

```text
// Holds XEXP patch data
```

## Source note 16, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L211)

```text
// pre-loaded import libraries for ease of use
```

## Source note 17, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L214)

```text
// XEX_HEADER_ALTERNATE_TITLE_IDS loaded into a safe std::vector
```

## Source note 18, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L220)

```text
// Loaded into memory?
```

## Source note 19, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L221)

```text
// PE/imports/symbols/etc all loaded?
```

## Source note 20, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L227)

```text
// Exception DataDirectory from PE Optional Header
```

## Source note 21, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L231)

```text
// PE FileHeader TimeDateStamp from the contained PE image.
```

## Source note 22, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xex_module.h#L239)

```text
// (removed orphan xe namespace)
```
