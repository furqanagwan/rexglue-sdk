# Function graph: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/function_graph.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L19)

```text
// Function Graph
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L21)

```text
// Container for all function nodes. Manages resolution notifications.
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L22)

```text
// Also handles vacancy checking for merge eligibility.
```

## Source note 4, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L24)

```text
// Vacancy Rules - A region is vacant if ALL are true:
```

## Source note 5, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L25)

```text
//   1. No null dword at the boundary
```

## Source note 6, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L26)

```text
//   2. No chunk claims the region
```

## Source note 7, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L27)

```text
//   3. Target does not fall within a protected function's range:
```

## Source note 8, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L28)

```text
//      - PDATA/CONFIG/HELPER: always protected (cannot merge into)
```

## Source note 9, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L29)

```text
//      - DISCOVERED with xrefs: CAN be merged (treated as potential internal label)
```

## Source note 10, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L36)

```text
// Code Buffer Management
```

## Source note 11, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L39)

```text
// Add a code buffer (copies executable section data into graph)
```

## Source note 12, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L42)

```text
// Translate guest address to host pointer (searches all code buffers)
```

## Source note 13, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L45)

```text
// Get all code buffers (for iteration/debugging)
```

## Source note 14, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L48)

```text
// Update all function code pointers (call after loading code buffers)
```

## Source note 15, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L52)

```text
// Function Management
```

## Source note 16, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L55)

```text
// Add a function to the graph.
```

## Source note 17, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L56)

```text
// Returns the new node, or existing node if already present (higher authority wins).
```

## Source note 18, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L57)

```text
// Notifies all PENDING functions to try resolution against the new entry.
```

## Source note 19, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L58)

```text
// hasXrefs: true if this is a known call target (bl target, etc.)
```

## Source note 20, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L62)

```text
// Add a named function to the graph (convenience overload)
```

## Source note 21, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L66)

```text
// Add a resolved import as a callable function with __imp__ name
```

## Source note 22, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L67)

```text
// Address is the thunk address that bl instructions target
```

## Source note 23, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L70)

```text
// Get function by entry point (O(1))
```

## Source note 24, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L74)

```text
// Remove function from graph (for cleanup of absorbed GAP_FILLs)
```

## Source note 25, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L77)

```text
// Get function containing address (O(log f) via sorted base index)
```

## Source note 26, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L81)

```text
// Check if address is a known entry point
```

## Source note 27, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L84)

```text
// Check if address is an import (FunctionNode with IMPORT authority)
```

## Source note 28, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L87)

```text
// Iterate all functions (includes imports with IMPORT authority)
```

## Source note 29, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L92)

```text
// Get all PENDING functions
```

## Source note 30, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L95)

```text
// Get all SEALED functions
```

## Source note 31, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L104)

```text
// Function Setup (called during Discover phase)
```

## Source note 32, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L107)

```text
// Set function name
```

## Source note 33, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L110)

```text
// Set exception handler flag
```

## Source note 34, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L113)

```text
// Set parsed exception info (SEH or C++ EH)
```

## Source note 35, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L116)

```text
// Add a block to a function
```

## Source note 36, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L119)

```text
// Add a label (internal branch target) to a function
```

## Source note 37, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L122)

```text
// Add a resolved call to a function
```

## Source note 38, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L125)

```text
// Add a resolved tail call to a function
```

## Source note 39, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L128)

```text
// Add a jump table to a function
```

## Source note 40, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L131)

```text
// Add an unresolved jump to a function
```

## Source note 41, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L132)

```text
// isCall: true for bl (call), false for b (tail call)
```

## Source note 42, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L137)

```text
// Resolution and Expansion (called during Merge phase)
```

## Source note 43, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L140)

```text
// Try to resolve all unresolved jumps for a function
```

## Source note 44, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L141)

```text
// Checks against known functions, imports, and internal labels
```

## Source note 45, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L142)

```text
// Returns number of jumps resolved
```

## Source note 46, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L145)

```text
// Absorb a region into a function (for vacancy expansion)
```

## Source note 47, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L148)

```text
// Seal a function if it can be sealed
```

## Source note 48, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L149)

```text
// Returns true if function was sealed
```

## Source note 49, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L152)

```text
// Seal all functions that can be sealed
```

## Source note 50, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L153)

```text
// Returns number of functions sealed
```

## Source note 51, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L156)

```text
// Seal all functions, throwing if any cannot be sealed
```

## Source note 52, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L157)

```text
// Use after discovery is complete to enforce all functions are ready
```

## Source note 53, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L161)

```text
// Vacancy Checking
```

## Source note 54, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L164)

```text
// Set the memory reader for null-dword checking
```

## Source note 55, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L167)

```text
// Register a chunk (address range claimed by config, blocks vacancy)
```

## Source note 56, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L170)

```text
// Check if a region is vacant for absorption
```

## Source note 57, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L171)

```text
// fromAddr: the address we're expanding from (to check for null boundary)
```

## Source note 58, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L172)

```text
// targetAddr: the start of the region we want to absorb
```

## Source note 59, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L175)

```text
// Check if target is a mergeable entry point (DISCOVERED with xrefs)
```

## Source note 60, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L178)

```text
// Flag every SEH funclet as register-sharing. Run after discovery, once
```

## Source note 61, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L179)

```text
// funclet extents are known. Returns the number flagged.
```

## Source note 62, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L183)

```text
// Target Classification (for code generation)
```

## Source note 63, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L186)

```text
// Classify a branch target for code generation.
```

## Source note 64, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L187)

```text
// target: address being branched to
```

## Source note 65, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L188)

```text
// callerAddr: address of the branch instruction
```

## Source note 66, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L189)

```text
// isCallInstruction: true for bl (expects return), false for b (no return)
```

## Source note 67, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L190)

```text
// Returns how the target should be treated during code generation.
```

## Source note 68, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L191)

```text
// caller: exact emitting function when blocks overlap with another entry.
```

## Source note 69, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L199)

```text
// sorted by base for O(log f) interval lookup
```

## Source note 70, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L200)

```text
// entry -> hasXrefs
```

## Source note 71, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L201)

```text
// base, size pairs
```

## Source note 72, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_graph.h#L204)

```text
// Notify all PENDING functions that a new function was added
```
