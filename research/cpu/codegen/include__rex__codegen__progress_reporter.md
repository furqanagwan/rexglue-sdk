# Progress reporter: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/progress_reporter.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L21)

```text
/** Identifying fields from a loaded XEX, surfaced before recompilation work starts. */
```

## Source note 2, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L23)

```text
///< Display name (filename of the input XEX).
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L24)

```text
///< xex2_opt_execution_info.title_id
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L25)

```text
///< xex2_opt_execution_info.media_id
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L26)

```text
///< xex2_version.major (4 bits)
```

## Source note 6, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L27)

```text
///< xex2_version.minor (4 bits)
```

## Source note 7, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L28)

```text
///< xex2_version.build (16 bits)
```

## Source note 8, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L29)

```text
///< xex2_version.qfe   (8 bits)
```

## Source note 9, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L30)

```text
///< IMAGE_FILE_HEADER.TimeDateStamp (Unix epoch seconds)
```

## Source note 10, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L33)

```text
/**
 * Optional progress callback invoked by the codegen pipeline at module
 * and phase boundaries. CLI consumers implement this to drive a progress
 * view; library-internal callers (tests, headless callers) can pass
 * nullptr to opt out.
 *
 * All methods are called from the thread that drove the pipeline; no
 * cross-thread synchronization is implied.
 */
```

## Source note 11, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L46)

```text
/** Identifying info for an input binary, emitted right after each XEX is loaded. */
```

## Source note 12, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L49)

```text
/** A new module's analysis+write cycle is starting. `index` is 0-based. */
```

## Source note 13, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L52)

```text
/** A named phase within the current module is starting. */
```

## Source note 14, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L55)

```text
/** The current module finished successfully. */
```

## Source note 15, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L58)

```text
/** Project-level (non-module) emit phase started, e.g. "module_registry". */
```

## Source note 16, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/progress_reporter.h#L61)

```text
/** Project-level emit phase finished. */
```
