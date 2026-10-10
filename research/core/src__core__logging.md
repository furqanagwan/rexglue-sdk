# Logging: core source notes

This record preserves technical and API notes moved from `src/core/logging.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L154)

```text
// Build sinks for a specific category (handles per-category sinks from config)
```

## Source note 2, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L159)

```text
// Replace default sinks entirely
```

## Source note 3, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L162)

```text
// Additive: default sinks + category-specific sinks
```

## Source note 4, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L171)

```text
// Resolve per-category level from config, or return default
```

## Source note 5, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L179)

```text
// Create a logger and register it
```

## Source note 6, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L203)

```text
// Create loggers for any categories already registered during static init
```

## Source note 7, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L209)

```text
// Set default logger to "core" if registered
```

## Source note 8, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L237)

```text
// The early msvc_sink stays: it is the persistent debug channel for GUI apps
```

## Source note 9, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L238)

```text
// and does not conflict with the stdout console sink.
```

## Source note 10, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L240)

```text
// Console sink (stdout, colored). Intended for console-subsystem processes.
```

## Source note 11, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L266)

```text
// Rebuild all loggers with new sinks
```

## Source note 12, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L277)

```text
// Set default logger to "core"
```

## Source note 13, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L330)

```text
// Check for duplicates
```

## Source note 14, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L384)

```text
// No lock: only safe to call from main thread or after init.
```

## Source note 15, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L507)

```text
// CLI Helpers
```

## Source note 16, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L538)

```text
// Build-type default
```

## Source note 17, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L541)

```text
// Environment variable
```

## Source note 18, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L550)

```text
// CLI global level overrides environment
```

## Source note 19, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/logging.cpp#L556)

```text
// Per-category CLI levels (string-keyed)
```
