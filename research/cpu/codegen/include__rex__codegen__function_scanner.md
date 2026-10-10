# Function scanner: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/function_scanner.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L23)

```text
// For FunctionAuthority, TargetKind
```

## Source note 2, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L29)

```text
// Forward declarations
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L34)

```text
// FunctionAuthority is defined in function_graph.h
```

## Source note 4, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L37)

```text
// Block-Based Discovery Types
```

## Source note 5, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L40)

```text
/**
 * Basic block discovered during recursive block discovery.
 * Used as temporary scanner state during discovery when function extent is unknown.
 * Converted to FunctionNode::Block when added to the graph.
 *
 * projectedSize: Size limit for conditional branch fall-through.
 * When a conditional branch is taken, the fall-through block gets a projectedSize
 * equal to the distance to the branch target. This prevents the fall-through from
 * consuming unrelated code beyond the branch target.
 */
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L51)

```text
// Start address
```

## Source note 7, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L52)

```text
// End address (exclusive, points after last instruction)
```

## Source note 8, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L53)

```text
// Ends with blr/bctr/unconditional branch
```

## Source note 9, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L55)

```text
// Size limit (-1 = unlimited), set on conditional branch fall-through
```

## Source note 10, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L56)

```text
// Branch targets (for CFG building)
```

## Source note 11, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L59)

```text
/**
 * Result of block-based function discovery.
 * Contains all blocks reachable from entry point.
 */
```

## Source note 12, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L64)

```text
// Function entry point
```

## Source note 13, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L65)

```text
// All discovered blocks
```

## Source note 14, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L66)

```text
// From pdata (0 if unknown)
```

## Source note 15, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L67)

```text
// Detected jump tables
```

## Source note 16, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L68)

```text
// bl targets outside this function
```

## Source note 17, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L69)

```text
// Unconditional branches to other functions
```

## Source note 18, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L73)

```text
// Function Scanner
```

## Source note 19, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L76)

```text
/**
 * PowerPC function scanner
 *
 * Implements heuristics for function boundary detection:
 * - Linear sweep from entry point
 * - Furthest branch target tracking
 * - Return/indirect branch detection
 * - Prologue/epilogue pattern matching
 *
 * Uses BinaryView for binary introspection.
 */
```

## Source note 20, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L91)

```text
/**
   * Detect jump table pattern at bctr instruction
   * @param bctr_address Address of the bctr instruction
   * @return JumpTable on success, nullopt if no jump table detected
   */
```

## Source note 21, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L98)

```text
/**
   * Discover all reachable blocks from entry point.
   * Uses recursive block discovery with pending stack.
   * @param entry_point Function entry point address
   * @param pdata_size Optional size from .pdata (0 if unknown)
   * @return FunctionBlocks containing all discovered blocks
   */
```

## Source note 22, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L107)

```text
// Address translation via Module's Memory
```

## Source note 23, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L111)

```text
// Check if address is in an executable section
```

## Source note 24, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L114)

```text
// Set known switch table addresses (from config) to skip auto-detection
```

## Source note 25, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L119)

```text
// Set discontinuous function chunks (chunk_addr -> FunctionConfig with parent set)
```

## Source note 26, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L122)

```text
// Set bl targets that need resolution (for Fix 4: shared helper promotion)
```

## Source note 27, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L125)

```text
// Get collected bl targets from discovery
```

## Source note 28, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L146)

```text
// Set code regions for boundary checking (prevents cross-region merges)
```

## Source note 29, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L149)

```text
// Find which code region contains the given address (nullptr if not found)
```

## Source note 30, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L152)

```text
/**
   * Check if a branch from currentAddr to targetAddr stays within the same
   * code region OR targets a configured chunk of the current function.
   * Used to determine if a branch is internal or a tail call.
   *
   * @param currentAddr Address of the branch instruction
   * @param targetAddr Branch target address
   * @param functionEntry Entry point of the current function being discovered
   * @return true if the branch should be treated as internal
   */
```

## Source note 31, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L164)

```text
// Check if an address is within a chunk belonging to the given function
```

## Source note 32, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L178)

```text
// Find chunk parent for an address (returns 0 if not in any chunk)
```

## Source note 33, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L180)

```text
// First check exact chunk start matches
```

## Source note 34, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L185)

```text
// Then check if address is within any chunk range
```

## Source note 35, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L205)

```text
// Helper methods for function boundary detection
```

## Source note 36, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L212)

```text
// Block Discovery Result
```

## Source note 37, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L216)

```text
// Address of branch instruction
```

## Source note 38, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L217)

```text
// Target address
```

## Source note 39, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L218)

```text
// true = bl (call), false = b (tail/jump)
```

## Source note 40, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L219)

```text
// true = bc/beq/etc, false = unconditional
```

## Source note 41, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L228)

```text
// Collected instruction pointers (for FunctionNode ownership)
```

## Source note 42, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L231)

```text
// External references found during discovery
```

## Source note 43, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L232)

```text
// bl to unknown targets
```

## Source note 44, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L233)

```text
// b to external targets
```

## Source note 45, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L237)

```text
// Block Discovery Function
```

## Source note 46, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L240)

```text
/**
 * Discover all blocks belonging to a function starting at entryPoint.
 *
 * Algorithm:
 * - Worklist-based block discovery
 * - Linear sweep until terminator (blr, bctr, unconditional b)
 * - Follow both paths for conditional branches
 * - Detect jump tables at bctr instructions
 * - Stop at code region boundaries (null padding)
 *
 * @param decoded The decoded binary (single-pass decoded instructions)
 * @param entryPoint Starting address of the function
 * @param containingRegion Code region containing the entry point
 * @param knownFunctions Set of known function entry points (to detect tail calls)
 * @return BlockDiscoveryResult containing blocks, branches, and jump tables
 */
```

## Source note 47, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L262)

```text
// Jump Table Detection
```

## Source note 48, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_scanner.h#L265)

```text
/**
 * Detect jump table at a bctr instruction.
 *
 * Patterns detected:
 * - ABSOLUTE: lwzx loads full 32-bit addresses
 * - COMPUTED: lbzx + rlwinm (byte offset with shift)
 * - BYTEOFFSET: lbzx + add (byte offset direct)
 * - SHORTOFFSET: lhzx + add (16-bit offset)
 *
 * @param decoded The decoded binary
 * @param bctrAddr Address of the bctr instruction
 * @param containingRegion Code region for validation
 * @return JumpTable if detected, empty optional otherwise
 */
```
