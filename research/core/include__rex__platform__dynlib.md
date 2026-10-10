# Dynlib: core source notes

This record preserves technical and API notes moved from `include/rex/platform/dynlib.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/dynlib.h#L1)

```text
/**
 * @file        platform/dynlib.h
 * @brief       Platform-agnostic dynamic library loading
 */
```

## Source note 2, line 15

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/dynlib.h#L15)

```text
// Resolve symbols on first use. Maps to RTLD_LAZY on POSIX; the only mode on
```

## Source note 3, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/dynlib.h#L16)

```text
// Windows.
```

## Source note 4, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/dynlib.h#L18)

```text
// Resolve all symbols at load time. Load fails if any unresolved symbol
```

## Source note 5, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/platform/dynlib.h#L19)

```text
// exists. Maps to RTLD_NOW on POSIX; the only mode on Windows.
```
