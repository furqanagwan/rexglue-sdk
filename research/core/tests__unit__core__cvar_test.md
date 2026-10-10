# Cvar test: core source notes

This record preserves technical and API notes moved from `tests/unit/core/cvar_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L18)

```text
// Test cvars
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L31)

```text
// Command dispatch test fixtures.
```

## Source note 3, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L109)

```text
// This test specifically tests the string-based SetFlagByName API
```

## Source note 4, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L110)

```text
// which parses string representations into native types
```

## Source note 5, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L177)

```text
// Set initial values using REXCVAR_SET
```

## Source note 6, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L270)

```text
// A flag the command line did not mention still takes the config value
```

## Source note 7, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L378)

```text
// Registered: the title's default replaces the compiled-in one.
```

## Source note 8, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L383)

```text
// A user's choice wins; a title default after it changes nothing.
```

## Source note 9, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L387)

```text
// Unknown values and out-of-range ones are refused.
```

## Source note 10, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L391)

```text
// A runtime-loaded module's flag: applied as it registers, under the
```

## Source note 11, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L392)

```text
// config file.
```

## Source note 12, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L425)

```text
// Put the compiled-in default back for the tests after this one.
```

## Source note 13, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L442)

```text
// Reset to known value
```

## Source note 14, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L473)

```text
// Note: This test must run before FinalizeInit is called elsewhere,
```

## Source note 15, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L474)

```text
// or use testing utilities to reset state
```

## Source note 16, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L477)

```text
// Assuming not finalized yet in test context
```

## Source note 17, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L486)

```text
// Clear any existing pending flags
```

## Source note 18, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L524)

```text
// Reset to default
```

## Source note 19, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L559)

```text
// Back to default
```

## Source note 20, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L571)

```text
// Should contain modified flags
```

## Source note 21, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L575)

```text
// Should not contain flags at default
```

## Source note 22, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L583)

```text
// 1. Verify metadata is queryable
```

## Source note 23, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L589)

```text
// 2. Verify validation works (set to valid non-default value, then invalid)
```

## Source note 24, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L593)

```text
// 3. Verify change tracking (value 7 is different from default 5)
```

## Source note 25, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L596)

```text
// 4. Verify reset works
```

## Source note 26, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L602)

```text
// Additional test cvars for extended coverage
```

## Source note 27, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L649)

```text
// Too short (less than 3 chars)
```

## Source note 28, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L663)

```text
// Non-debug flag should have is_debug_only = false
```

## Source note 29, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L672)

```text
// Finalize to lock init-only flags
```

## Source note 30, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L686)

```text
// After scope, should be blocked again
```

## Source note 31, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L694)

```text
// Modify several flags
```

## Source note 32, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L713)

```text
// Modify flags in different categories
```

## Source note 33, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L714)

```text
// Category: Test
```

## Source note 34, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L715)

```text
// Category: TestCategory
```

## Source note 35, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L735)

```text
// Clean up any existing file
```

## Source note 36, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L744)

```text
// Verify file exists and contains expected content
```

## Source note 37, line 778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L778)

```text
// Note: This test modifies the environment, which may affect other tests
```

## Source note 38, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L779)

```text
// In practice, environment application happens once at startup
```

## Source note 39, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L782)

```text
// Set environment variable
```

## Source note 40, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L793)

```text
// Clean up
```

## Source note 41, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L821)

```text
// SaveConfig writes what the user chose: config-file and runtime values.
```

## Source note 42, line 822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L822)

```text
// Values for one run (command line, environment) never become permanent,
```

## Source note 43, line 823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/core/cvar_test.cpp#L823)

```text
// the leak Canary #844 describes for per-game configs (ADR-009).
```
