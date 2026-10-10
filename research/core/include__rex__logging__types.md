# Types: core source notes

This record preserves technical and API notes moved from `include/rex/logging/types.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L27)

```text
/**
 * Lightweight handle identifying a log category.
 *
 * Internally a uint16_t index into the global category registry.
 * SDK built-in categories are registered via REXLOG_DEFINE_CATEGORY;
 * consumer categories are obtained at runtime via RegisterLogCategory().
 */
```

## Source note 2, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L40)

```text
/**
 * Entry in the global category registry.
 * Each registered category has a human-readable name and its own spdlog logger.
 */
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L45)

```text
/**< Category name (e.g. "core", "app.network") */
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L46)

```text
/**< Per-category spdlog logger instance */
```

## Source note 5, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L59)

```text
/**
 * Configuration for the logging system.
 *
 * Fill out and pass to InitLogging(). All fields have sensible defaults.
 * String-keyed maps (category_levels, category_sinks) resolve by name so
 * they work for categories that haven't been registered yet.
 */
```

## Source note 6, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L67)

```text
/** Global default log level applied to all categories unless overridden. */
```

## Source note 7, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L70)

```text
/** Whether to create a colored stdout sink. Intended for console-subsystem
   *  processes (CLI tools). Windowed apps should leave this false and rely on
   *  the platform debug sink created by InitLoggingEarly(). */
```

## Source note 8, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L77)

```text
/** spdlog pattern string for the stdout console sink. */
```

## Source note 9, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L80)

```text
/** spdlog pattern string for the file sink. */
```

## Source note 10, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L83)

```text
/** Messages at or above this level trigger an immediate flush. */
```

## Source note 11, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L86)

```text
/**
   * Per-category log level overrides.
   * Key is the category name (e.g. "core", "gpu", "app.network").
   * Categories not listed here use default_level.
   */
```

## Source note 12, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L93)

```text
/**
   * Extra sinks added to ALL loggers alongside the default console/file sinks.
   * Useful for ring-buffer capture sinks, network sinks, etc.
   */
```

## Source note 13, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L99)

```text
/**
   * Per-category extra sinks. Key is category name.
   * Each vector of sinks is added ONLY to the specified category's logger.
   */
```

## Source note 14, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/types.h#L105)

```text
/**
   * If true, per-category sinks in category_sinks REPLACE the default sinks
   * for that category rather than being added alongside them.
   * Default is false (additive).
   */
```
