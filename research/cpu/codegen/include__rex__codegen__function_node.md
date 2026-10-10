# Function node: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/function_node.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L19)

```text
// Function Node
```

## Source note 2, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L21)

```text
// Core object representing a function in the graph.
```

## Source note 3, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L22)

```text
// Manages its own state transitions and resolution.
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L25)

```text
// Graph manages all mutations
```

## Source note 5, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L31)

```text
// Read-only accessors - external code can inspect but not modify
```

## Source note 6, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L40)

```text
// Code access - cached pointer to instruction bytes
```

## Source note 7, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L44)

```text
// Authority and state
```

## Source note 8, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L48)

```text
// State queries
```

## Source note 9, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L53)

```text
// Legacy aliases (PENDING maps to kRegistered OR kDiscovered - not sealed)
```

## Source note 10, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L56)

```text
// Special type checks
```

## Source note 11, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L61)

```text
// State Machine - New 3-state model
```

## Source note 12, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L64)

```text
/// Can transition from kRegistered to kDiscovered?
```

## Source note 13, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L67)

```text
/// Transition kRegistered -> kDiscovered with blocks and instructions
```

## Source note 14, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L68)

```text
/// Precondition: canDiscover() returns true
```

## Source note 15, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L69)

```text
/// For non-imports: blocks must not be empty
```

## Source note 16, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L74)

```text
/// Transition kRegistered -> kDiscovered for import functions (no blocks)
```

## Source note 17, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L77)

```text
/// Can transition from kDiscovered to kSealed?
```

## Source note 18, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L78)

```text
/// Returns true if:
```

## Source note 19, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L79)

```text
/// - state == kDiscovered
```

## Source note 20, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L80)

```text
/// - imports: always OK (no blocks required)
```

## Source note 21, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L81)

```text
/// - non-imports: blocks not empty AND no unresolved branches
```

## Source note 22, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L84)

```text
/// Transition kDiscovered -> kSealed
```

## Source note 23, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L85)

```text
/// Computes FunctionAnalysis and sorts blocks
```

## Source note 24, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L88)

```text
/// Get analysis result (only valid after seal)
```

## Source note 25, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L92)

```text
// Code Emission (valid after seal)
```

## Source note 26, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L95)

```text
/// Emit C++ code for this function
```

## Source note 27, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L96)

```text
/// Requires: state() == kSealed
```

## Source note 28, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L97)

```text
/// For imports: emits REX_IMPORT macro
```

## Source note 29, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L98)

```text
/// For normal functions: emits REX_FUNC with blocks and instructions
```

## Source note 30, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L102)

```text
// Instruction access (valid after discover)
```

## Source note 31, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L105)

```text
/// Get owned instructions (pointers into DecodedBinary)
```

## Source note 32, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L112)

```text
// Check if address is within overall function bounds (ignores blocks)
```

## Source note 33, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L113)

```text
// Use this for branch target detection where address may be in a gap between blocks
```

## Source note 34, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L116)

```text
// Labels (internal branch targets within this function)
```

## Source note 35, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L120)

```text
// Resolved calls (bl instructions)
```

## Source note 36, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L123)

```text
// Resolved tail calls (b instructions to other functions)
```

## Source note 37, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L126)

```text
// Jump tables
```

## Source note 38, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L129)

```text
// Unresolved jumps (pending resolution)
```

## Source note 39, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L132)

```text
// Sealing state (legacy - use canSeal() with new semantics)
```

## Source note 40, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L138)

```text
// Exception info (SEH or C++ EH)
```

## Source note 41, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L144)

```text
// This is an SEH funclet: non-volatiles stay in ctx so it sees what its owner
```

## Source note 42, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L145)

```text
// left live, and callers sync their localized copies around the call.
```

## Source note 43, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L151)

```text
// Mutation methods - only FunctionGraph can call these
```

## Source note 44, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L158)

```text
// Block/label management
```

## Source note 45, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L162)

```text
// Call tracking
```

## Source note 46, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L168)

```text
// Resolution (reactive - called by graph on events)
```

## Source note 47, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L176)

```text
// Internal helper
```

## Source note 48, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L186)

```text
// Cached pointer to instruction bytes
```

## Source note 49, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L192)

```text
// Populated at discover()
```

## Source note 50, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L194)

```text
// Pointers into DecodedBinary
```

## Source note 51, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L195)

```text
// Branch targets within this function
```

## Source note 52, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_node.h#L205)

```text
// Computed at seal()
```
