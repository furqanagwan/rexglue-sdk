# Macros: core source notes

This record preserves technical and API notes moved from `include/rex/logging/macros.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L16)

```text
/* Implementation macro - do not call directly. Uses raw pointer for zero
   ref-count overhead and gates on should_log() to skip format evaluation. */
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L32)

```text
/* --- Parameterized Macros (Primary API) --------------------------------- */
```

## Source note 3, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L43)

```text
/* --- Noisy Parameterized Macros (cvar-gated) ------------------------------ */
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L48)

```text
/* --- Per-Subsystem Alias Macros - Core Category -------------------------- */
```

## Source note 5, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L59)

```text
/* --- Per-Subsystem Alias Macros ------------------------------------------ */
```

## Source note 6, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L61)

```text
/** @{ CPU */
```

## Source note 7, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L70)

```text
/** @{ APU */
```

## Source note 8, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L79)

```text
/** @{ GPU */
```

## Source note 9, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L88)

```text
/** @{ Kernel */
```

## Source note 10, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L97)

```text
/** @{ System */
```

## Source note 11, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L106)

```text
/** @{ Filesystem */
```

## Source note 12, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L115)

```text
/* --- Noisy Aliases - Per-Subsystem ---------------------------------------- */
```

## Source note 13, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L132)

```text
/* --- Custom Category Definition ----------------------------------------- */
```

## Source note 14, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L134)

```text
/**
 * Define a custom log category with Meyers singleton, guaranteed to
 * initialize on first use regardless of static init order.
 *
 * Usage (in a header):
 *   REXLOG_DEFINE_CATEGORY(codegen)
 *   #define REXCODEGEN_TRACE(...) REXLOG_CAT_TRACE(::rex::log::codegen(), __VA_ARGS__)
 *   // ... etc for DEBUG, INFO, WARN, ERROR, CRITICAL
 *
 * Expands to an inline function rex::log::codegen() returning LogCategoryId.
 */
```

## Source note 15, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L153)

```text
// For dynamic parents (defined via REXLOG_DEFINE_CATEGORY)
```

## Source note 16, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/macros.h#L163)

```text
/* --- Built-in SDK Categories ---------------------------------------------- */
```
