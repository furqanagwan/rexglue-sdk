# Cvar: core source notes

This record preserves technical and API notes moved from `src/core/cvar.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L36)

```text
// Set once cvar::Init has parsed the command line; later registrations are
```

## Source note 2, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L37)

```text
// from runtime-loaded modules and drain pending values.
```

## Source note 3, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L40)

```text
// Recursive: FlagRegistrar chain methods re-enter; change callbacks invoked
```

## Source note 4, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L41)

```text
// from SetFlagByName must not mutate the registry.
```

## Source note 5, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L47)

```text
// Flag registry - use functions to avoid static init order issues
```

## Source note 6, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L58)

```text
// Values that arrived before their cvar was registered; runtime-loaded
```

## Source note 7, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L59)

```text
// modules register cvars long after Init/LoadConfig.
```

## Source note 8, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L71)

```text
// Convert flag name to environment variable: gpu_vsync -> REX_GPU_VSYNC
```

## Source note 9, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L84)

```text
// Records the value SaveConfig writes for a registered flag.
```

## Source note 10, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L97)

```text
// Unvalidated apply, for the command line and environment paths.
```

## Source note 11, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L106)

```text
// Recursively apply TOML values
```

## Source note 12, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L140)

```text
// Still the file's value: saving must keep it.
```

## Source note 13, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L152)

```text
// todo(tomc): move restart manager to Runtime
```

## Source note 14, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L158)

```text
// Callback storage for change notifications
```

## Source note 15, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L175)

```text
// Range validation for numeric types
```

## Source note 16, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L179)

```text
// These types don't have numeric range constraints
```

## Source note 17, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L184)

```text
// Integer types
```

## Source note 18, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L202)

```text
// Allowed values validation
```

## Source note 19, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L217)

```text
// Custom validator
```

## Source note 20, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L251)

```text
// Late registration: replay pending values in ascending priority.
```

## Source note 21, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L372)

```text
// A runtime-loaded module's flag (the GPU plugin's): applied when it
```

## Source note 22, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L373)

```text
// registers, under its config and command-line values.
```

## Source note 23, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L379)

```text
// a higher source already chose
```

## Source note 24, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L405)

```text
// Copy the callback out from under the lock; GetFlagInfo pointers are
```

## Source note 25, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L406)

```text
// invalidated by registry mutation and a command may touch the registry.
```

## Source note 26, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L471)

```text
// Pointer is invalidated by any subsequent registry call.
```

## Source note 27, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L588)

```text
// Config-file and runtime values only. A value from the defaults, the
```

## Source note 28, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L589)

```text
// environment or the command line (or a title profile, ADR-009) belongs to
```

## Source note 29, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L590)

```text
// this run, and saving it would make it permanent (Canary #844).
```

## Source note 30, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L601)

```text
// Config keys for cvars that never registered this run (a plugin that
```

## Source note 31, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L602)

```text
// wasn't loaded) stay in the file. Their type is unknown: booleans and
```

## Source note 32, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L603)

```text
// numbers are written bare, anything else quoted.
```

## Source note 33, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L671)

```text
// Stash unrecognized --options for cvars that register later. Supported
```

## Source note 34, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L672)

```text
// forms: --name=value, --name (true), --no-name (false); a separated
```

## Source note 35, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L673)

```text
// "--name value" pair is ambiguous with a positional, so never consumed.
```

## Source note 36, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/cvar.cpp#L761)

```text
// The per-user settings folder may not exist yet.
```
