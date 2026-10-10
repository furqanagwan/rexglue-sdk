# Phase register: codegen source notes

This record preserves technical and API notes moved from `src/codegen/phase_register.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L40)

```text
// PE Structures
```

## Source note 2, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L59)

```text
// Exception Info Parsing
```

## Source note 3, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L68)

```text
// Prolog info extracted from function prologue for SEH unwinding
```

## Source note 4, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L70)

```text
// From addi r31, r1, -N
```

## Source note 5, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L71)

```text
// From bl __savegprlr_N
```

## Source note 6, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L72)

```text
// True if frame size was successfully detected
```

## Source note 7, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L75)

```text
// Scan function prolog to extract frame size and save helper
```

## Source note 8, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L76)

```text
// Only called for functions with ExceptionFlag set
```

## Source note 9, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L92)

```text
// Use pdata prolog length - if 0, we can't safely scan
```

## Source note 10, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L103)

```text
// Check for addi r31, r1, -N (frame pointer setup)
```

## Source note 11, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L112)

```text
// Check for bl - save helper call
```

## Source note 12, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L118)

```text
// NOTE(tomc): info.valid may be false for handler functions that receive frame in r12
```

## Source note 13, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L119)

```text
// The caller should warn only if frameSize is actually needed (i.e., function has SEH scopes)
```

## Source note 14, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L148)

```text
// __finally has layout [2]=handler, [3]=0; __except has [2]=filter, [3]=handler
```

## Source note 15, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L165)

```text
// For __finally (filter=0), handler is a separate function
```

## Source note 16, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L166)

```text
// For __except (filter!=0), only filter is a separate function (handler is inline)
```

## Source note 17, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L168)

```text
// __finally handler
```

## Source note 18, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L171)

```text
// __except filter
```

## Source note 19, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L225)

```text
// Parse UnwindMap
```

## Source note 20, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L241)

```text
// Parse TryBlockMap
```

## Source note 21, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L276)

```text
// Parse IPtoStateMap
```

## Source note 22, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L354)

```text
// Helper Detection
```

## Source note 23, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L418)

```text
// Register Phase: imports, helpers, PDATA, config functions
```

## Source note 24, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L430)

```text
// Merge user hints into analysis state
```

## Source note 25, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L441)

```text
// Build chunksByParent from config.functions
```

## Source note 26, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L473)

```text
// Register imports
```

## Source note 27, line 534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L534)

```text
// Register save/restore helpers
```

## Source note 28, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L554)

```text
// VMX 64-127
```

## Source note 29, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L572)

```text
// Register CONFIG functions
```

## Source note 30, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L593)

```text
// Register PDATA functions
```

## Source note 31, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L635)

```text
// Scan prolog to get frame size for SEH unwinding
```

## Source note 32, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L649)

```text
// Populate SEH frame info for unwinding
```

## Source note 33, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L651)

```text
// Need non-const access to set frame info
```

## Source note 34, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L655)

```text
// Warn if we have SEH scopes but couldn't determine frame size
```

## Source note 35, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L661)

```text
// Compute restore helper from save helper
```

## Source note 36, line 662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L662)

```text
// Save helpers and restore helpers are at matching offsets from their base addresses
```

## Source note 37, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L682)

```text
// For __except (filter!=0), handler is inline code - add as label
```

## Source note 38, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L702)

```text
// Queue EH-discovered functions
```

## Source note 39, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_register.cpp#L721)

```text
// anonymous namespace
```
