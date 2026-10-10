# Function dispatcher: system source notes

This record preserves technical and API notes moved from `include/rex/system/function_dispatcher.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L35)

```text
// Forward declarations
```

## Source note 2, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L39)

```text
/**
 * Narrow registration interface used by generated DLLs.
 */
```

## Source note 3, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L44)

```text
/**
   * Returns false (and logs) if guest_address is outside every registered
   * function-table range.
   */
```

## Source note 4, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L56)

```text
/**
   * Callback type for module registration functions.
   */
```

## Source note 5, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L71)

```text
/**
   * Executes guest code on a thread already running guest code, then restores
   * its full register state, matching the 360 kernel's trap-frame APC delivery.
   */
```

## Source note 6, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L78)

```text
// Shared thunk region size per module.
```

## Source note 7, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L79)

```text
// 64KB
```

## Source note 8, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L81)

```text
// rexglue function table management (per-module table at IMAGE_BASE + IMAGE_SIZE)
```

## Source note 9, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L82)

```text
// Set is_entrypoint=true exactly once for the host-loaded entrypoint so
```

## Source note 10, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L83)

```text
// AllocateThunk(caller_address=0) can route to its pool.
```

## Source note 11, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L84)

```text
/// `table_base` is where the dispatch table goes (PPCImageInfo
```

## Source note 12, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L85)

```text
/// function_table_base); 0 for image_base + image_size.
```

## Source note 13, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L91)

```text
/**
   * The guest address of the registered function whose host code most likely
   * contains `host_pc`: the one with the highest host entry at or below it.
   * Returns 0 when none is below it. Takes no lock (used from fault reports).
   */
```

## Source note 14, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L98)

```text
/**
   * caller_address must be inside a registered module, or 0 to mean "host-
   * initiated, route to the entrypoint pool".
   */
```

## Source note 15, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L104)

```text
/**
   * Returns the `code_base` of the module containing `guest_address`,
   * or 0 if no module covers that address.
   */
```

## Source note 16, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L110)

```text
/**
   * Register a module while recording guest addresses written via SetFunction.
   * `code_base` must equal the value previously passed to InitializeFunctionTable
   * for the same module.
   */
```

## Source note 17, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L117)

```text
/**
   * Unregister `module_id`: clears its function-table entries, releases its
   * thunk pool, and removes its per-module function table. Returns the
   * cleared thunk-pool range `[lo, hi)` for external cache invalidation, or
   * nullopt if the module was not registered.
   */
```

## Source note 18, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L145)

```text
// Host-side function lookup.
```

## Source note 19, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L148)

```text
// Per-module function table metadata.
```

## Source note 20, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L151)

```text
// code_base of the entrypoint module, or 0 if not yet registered.
```

## Source note 21, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L154)

```text
// Module recording for RegisterModule/UnregisterModule.
```

## Source note 22, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L163)

```text
// Recorded state per module, keyed by module_id.
```

## Source note 23, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L166)

```text
// Protects dispatcher metadata during module registration and callback dispatch.
```

## Source note 24, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L170)

```text
/// Adds `guest_address` to the indirect call trace at `path` (RG-GDK-066): a
```

## Source note 25, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L171)

```text
/// TOML file whose [functions] table the title's codegen config can include,
```

## Source note 26, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L172)

```text
/// so the next codegen registers every target a run found unregistered. The
```

## Source note 27, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/function_dispatcher.h#L173)

```text
/// file keeps what earlier runs recorded. False if it can't be written.
```
