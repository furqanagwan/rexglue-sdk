# Game source test: system source notes

This record preserves technical and API notes moved from `tests/unit/system/game_source_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L18)

```text
// One optional header.
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L20)

```text
// XEX_HEADER_EXECUTION_INFO.
```

## Source note 3, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L28)

```text
// An unencrypted, uncompressed XEX whose image holds an XDBF resource named
```

## Source note 4, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L29)

```text
// by its title ID, with an English title string.
```

## Source note 5, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L38)

```text
// 'XSTR'
```

## Source note 6, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L45)

```text
// 'XDBF'
```

## Source note 7, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L51)

```text
// string table
```

## Source note 8, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L64)

```text
// security info
```

## Source note 9, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L66)

```text
// execution info
```

## Source note 10, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L70)

```text
// file format: not encrypted or compressed
```

## Source note 11, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L203)

```text
// Relative paths need the working directory's volume. Hosted Windows runners
```

## Source note 12, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L204)

```text
// may keep TEMP on C: and the CTest working directory on D:.
```

## Source note 13, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L283)

```text
// no resources
```

## Source note 14, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L291)

```text
// the title length's high byte
```

## Source note 15, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L328)

```text
// Builds generated before names were recorded keep the title ID alone.
```

## Source note 16, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L334)

```text
// Local only: REXGLUE_TITLE_XEX names a retail default.xex (encrypted and
```

## Source note 17, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/system/game_source_test.cpp#L335)

```text
// LZX-compressed, as discs ship) whose XDBF title should be read.
```
