# Shader replacements test: graphics source notes

This record preserves technical and API notes moved from `tests/unit/graphics/shader_replacements_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 1

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L1)

```text
/**
 * @file        shader_replacements_test.cpp
 * @brief       Replacement shaders matched by ucode hash, with fallback (RG-GDK-067)
 */
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L40)

```text
// Wrong length, unknown stage, wrong extension, no stage.
```

## Source note 3, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L62)

```text
// Another stage, path or hash: no replacement, so the translation stays.
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L67)

```text
// Only DXBC containers are taken.
```

## Source note 5, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L82)

```text
// not DXBC
```

## Source note 6, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L83)

```text
// bad name
```

## Source note 7, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/graphics/shader_replacements_test.cpp#L84)

```text
// source, not shipped
```
