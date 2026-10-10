# Config: codegen source notes

This record preserves technical and API notes moved from `src/codegen/config.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 13

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L13)

```text
// TOML config file loading
```

## Source note 2, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L33)

```text
/// Maximum nesting depth for include chains.
```

## Source note 3, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L36)

```text
/// Parse a hex address string (with or without "0x"/"0X" prefix).
```

## Source note 4, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L50)

```text
// Scalar merge helpers -- log overrides at debug level
```

## Source note 5, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L69)

```text
/// Overload for booleans where the "zero" state (false) is meaningful.
```

## Source note 6, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L70)

```text
/// Only skip the merge when the overlay explicitly did not set the key.
```

## Source note 7, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L82)

```text
// Apply a single parsed TOML table onto the config (merge semantics)
```

## Source note 8, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L86)

```text
// --- Scalars: last wins ---
```

## Source note 9, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L88)

```text
// String scalars (only override if present in this file)
```

## Source note 10, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L102)

```text
// Bool scalars
```

## Source note 11, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L124)

```text
// Integer scalars (only override if present)
```

## Source note 12, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L134)

```text
// --- [analysis] section scalars ---
```

## Source note 13, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L146)

```text
// exceptionHandlerFuncHints -- push_back then deduplicate at end
```

## Source note 14, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L156)

```text
// --- Keyed tables: additive, same key = last wins ---
```

## Source note 15, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L158)

```text
// [rexcrt]
```

## Source note 16, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L178)

```text
// [functions]
```

## Source note 17, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L225)

```text
// [[patch]] -- keyed by "name"; a later entry replaces the writes it lists
```

## Source note 18, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L226)

```text
// and the enabled flag it sets, so an override file can switch one on.
```

## Source note 19, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L302)

```text
// Canary spells the switch is_enabled; accept both, enabled wins.
```

## Source note 20, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L350)

```text
// [[cheat]] -- keyed by "name": the title's own cheat codes, for the guide.
```

## Source note 21, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L372)

```text
// [[dlc]] -- keyed by "id": the title's add-ons, for the guide.
```

## Source note 22, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L396)

```text
// [[title_update]] -- keyed by "version": the title's updates, for the guide.
```

## Source note 23, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L432)

```text
// --- Arrays of tables: deduplicated by primary key (address), last wins ---
```

## Source note 24, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L434)

```text
// [[invalid_instructions]] -- keyed by "data" address
```

## Source note 25, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L464)

```text
// [[switch_tables]] -- keyed by "address"
```

## Source note 26, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L518)

```text
// [[midasm_hook]] -- keyed by "address"
```

## Source note 27, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L581)

```text
// --- Sets: additive ---
```

## Source note 28, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L583)

```text
// indirect_calls -> knownIndirectCallHints (set)
```

## Source note 29, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L635)

```text
// Process includes first (depth-first), so this table's own values win.
```

## Source note 30, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L658)

```text
// Public API
```

## Source note 31, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L722)

```text
// Helper to check 4-byte alignment (PPC instructions are 4-byte aligned)
```

## Source note 32, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L730)

```text
// Check special address alignment
```

## Source note 33, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L742)

```text
// Check function address alignment
```

## Source note 34, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L750)

```text
// Check for duplicate function boundaries
```

## Source note 35, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L770)

```text
// Check for overlapping function boundaries (standalone functions only)
```

## Source note 36, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L790)

```text
// Validate rexcrt all-or-nothing groups -- originals are stripped so partial
```

## Source note 37, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L791)

```text
// sets would leave the game with missing CRT functions at runtime.
```

## Source note 38, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/config.cpp#L818)

```text
// Check required fields
```
