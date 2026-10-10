# Api: core source notes

This record preserves technical and API notes moved from `include/rex/logging/api.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L23)

```text
// Logging CVAR declarations (defined in logging.cpp)
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L32)

```text
/* =========================================================================
   Log Level Guidelines
   =========================================================================
   TRACE    - Per-instruction, per-iteration detail (massive output)
   DEBUG    - Development info, function entry/exit, intermediate state
   INFO     - Normal operational events, progress updates
   WARN     - Recoverable issues, fallback behaviors, unsupported features
   ERROR    - Serious problems affecting functionality
   CRITICAL - Fatal errors, memory corruption, unrecoverable state
   ========================================================================= */
```

## Source note 3, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L43)

```text
/**
 * Initialize the logging system with full configuration.
 *
 * Creates shared sinks and loggers for all built-in categories.
 * Safe to call multiple times; subsequent calls update levels only.
 *
 * @param config  Logging configuration.
 */
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L53)

```text
/**
 * Initialize logging with simple parameters (convenience overload).
 *
 * @param log_file  Path to log file, or empty for no file logging.
 * @param level     Default log level for all categories.
 */
```

## Source note 5, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L62)

```text
/**
 * As above, with nullptr meaning no file logging. Kept for callers of the
 * earlier `const char*` signature: a std::filesystem::path built from nullptr
 * is undefined behavior (it crashed the GPU test fixture).
 */
```

## Source note 6, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L69)

```text
/**
 * Early-phase logging initialization (before config is loaded).
 * Creates a platform debug sink (OutputDebugString on Windows, stdout elsewhere)
 * so log lines emitted before InitLogging() is called are captured.
 */
```

## Source note 7, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L76)

```text
/**
 * Flush all loggers and shut down the logging system.
 */
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L81)

```text
/**
 * Flush all loggers without tearing down the logging system.
 *
 * Use before a hard process exit (std::_Exit) when other threads may still be
 * logging: unlike ShutdownLogging it leaves the registry and sinks intact, so a
 * concurrent logger cannot hit freed state.
 */
```

## Source note 9, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L90)

```text
/**
 * Register a new log category at runtime.
 *
 * The returned handle can be used with REXLOG_CAT_* macros and all
 * category-accepting API functions. The category's logger is created
 * with the current default sinks and any matching entries from the
 * stored LogConfig::category_levels and LogConfig::category_sinks.
 *
 * Thread-safe but intended to be called during startup.
 *
 * @param name  Human-readable category name (e.g. "app.network").
 * @return      Handle for the new category.
 */
```

## Source note 10, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L108)

```text
/**
 * Look up a category by name.
 *
 * @param name  Category name to search for (case-sensitive).
 * @return      Category handle, or std::nullopt if not found.
 */
```

## Source note 11, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L116)

```text
/**
 * Get a read-only view of all registered categories.
 *
 * @return  Span over the registry entries in registration order.
 */
```

## Source note 12, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L123)

```text
/**
 * Get the raw logger pointer for a category (zero overhead).
 *
 * This is the fast path used by logging macros. Returns nullptr if
 * the category is not yet initialized.
 *
 * @param category  Category handle.
 * @return          Raw pointer to the spdlog logger (not owning).
 */
```

## Source note 13, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L134)

```text
/**
 * Get the shared logger pointer for a category.
 *
 * Prefer GetLoggerRaw() in hot paths. This overload is useful when
 * you need to hold the logger or manipulate its sinks.
 *
 * @param category  Category handle.
 * @return          Shared pointer to the spdlog logger.
 */
```

## Source note 14, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L145)

```text
/**
 * Get the default (Core) logger.
 *
 * @return  Shared pointer to the Core category logger.
 */
```

## Source note 15, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L152)

```text
/**
 * Set the log level for a specific category at runtime.
 *
 * @param category  Category handle.
 * @param level     New log level.
 */
```

## Source note 16, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L160)

```text
/**
 * Set the log level for all registered categories.
 *
 * @param level  New log level.
 */
```

## Source note 17, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L167)

```text
/**
 * Register a CVAR change callback for the "log_level" CVAR.
 * Call this after InitLogging() to enable runtime level changes.
 */
```

## Source note 18, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L173)

```text
/**
 * Add a sink to all current and future loggers.
 *
 * @param sink  Shared pointer to the spdlog sink.
 */
```

## Source note 19, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L180)

```text
/**
 * Add a sink to a specific category's logger only.
 *
 * @param category  Category handle.
 * @param sink      Shared pointer to the spdlog sink.
 */
```

## Source note 20, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L188)

```text
/**
 * Remove a sink from all loggers.
 *
 * @param sink  The sink to remove (matched by pointer identity).
 */
```

## Source note 21, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L195)

```text
/**
 * Remove a sink from a specific category's logger.
 *
 * @param category  Category handle.
 * @param sink      The sink to remove (matched by pointer identity).
 */
```

## Source note 22, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L203)

```text
/**
 * Replace the global console sink on every registered logger with `sink`.
 * Pass nullptr to remove the console sink without replacement.
 *
 * @param sink  New console sink, or nullptr to remove.
 */
```

## Source note 23, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L211)

```text
/**
 * Update the format pattern on the stdout console sink.
 *
 * @param pattern  spdlog pattern string.
 */
```

## Source note 24, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L218)

```text
/**
 * Update the format pattern on the file sink.
 *
 * @param pattern  spdlog pattern string.
 */
```

## Source note 25, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L225)

```text
/**
 * Parse a log level string to spdlog level enum.
 *
 * Accepts: "trace", "debug", "info", "warn"/"warning", "error"/"err",
 * "critical", "off". Case-insensitive.
 *
 * @param level_str  Level name string.
 * @return           Parsed level, or std::nullopt if invalid.
 */
```

## Source note 26, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L236)

```text
/**
 * Parse log level from string, returning a default on failure.
 *
 * @param level_str      Level name string.
 * @param default_level  Fallback level if parsing fails.
 * @return               Parsed level or default_level.
 */
```

## Source note 27, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L246)

```text
/**
 * Build a LogConfig from CLI arguments and environment variables.
 *
 * Precedence: CLI args > environment (REX_LOG_LEVEL) > build-type default.
 *
 * @param cli_level        Global level from CLI (empty string = not set).
 * @param category_levels  Per-category level overrides from CLI.
 * @return                 Populated LogConfig.
 */
```

## Source note 28, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/logging/api.h#L260)

```text
/**
 * Deletes whole runs of `<app_name>_NNN*.log` in `logs_dir`, oldest first,
 * until the files left fit in `budget_bytes`. InitLogging calls it before
 * opening a new run when LogConfig::dir_budget_bytes is set.
 */
```
