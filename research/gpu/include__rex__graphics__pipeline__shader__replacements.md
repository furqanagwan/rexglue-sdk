# Replacements: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/replacements.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L26)

```text
/// Replacement DXBC for translated guest shaders, keyed by the guest ucode hash
```

## Source note 2, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L27)

```text
/// and host stage, optionally narrowed to one translator modification. A file
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L28)

```text
/// is named `<HASH>[_<MODIFICATION>].<stage>.dxbc`, both in 16 hex digits as
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L29)

```text
/// `dump_shaders` writes them, with stage `vs`, `ps_rtv` or `ps_rov` (pixel
```

## Source note 5, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L30)

```text
/// shaders differ between the two render target paths).
```

## Source note 6, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L41)

```text
/// Parses a replacement file name; false for anything else.
```

## Source note 7, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L44)

```text
/// Adds every well-named DXBC file in `folder`; others are skipped with a
```

## Source note 8, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L45)

```text
/// warning. Returns the number added.
```

## Source note 9, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L48)

```text
/// Adds one replacement. False (and nothing added) unless `dxbc` is a DXBC
```

## Source note 10, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L49)

```text
/// container.
```

## Source note 11, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L52)

```text
/// The replacement for a translation: the one for its exact modification,
```

## Source note 12, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L53)

```text
/// else the one for any modification, else nullptr (translate as usual).
```

## Source note 13, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/replacements.h#L60)

```text
// Modification UINT64_MAX with has_modification false is "any".
```
