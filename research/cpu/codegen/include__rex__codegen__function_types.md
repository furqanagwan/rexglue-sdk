# Function types: codegen source notes

This record preserves technical and API notes moved from `include/rex/codegen/function_types.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L42)

```text
// Forward declarations
```

## Source note 2, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L48)

```text
/// Lightweight context passed to FunctionNode::emitCpp() and BuilderContext.
```

## Source note 3, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L49)

```text
/// Non-owning references -- caller must ensure lifetimes.
```

## Source note 4, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L50)

```text
/// An instruction word a switchable patch changes: codegen emits both
```

## Source note 5, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L51)

```text
/// versions, chosen at run time by the patch's flag.
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L55)

```text
///< Index into the title's switchable patch table
```

## Source note 7, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L59)

```text
/// A register a switchable patch sets before the instruction at its address.
```

## Source note 8, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L72)

```text
///< For "xstart" naming
```

## Source note 9, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L73)

```text
///< For import ordinal resolution (nullable)
```

## Source note 10, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L75)

```text
/// Every function name emitted as a call. The writer turns this into the
```

## Source note 11, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L76)

```text
/// per-file declaration header, so a missed name is a compile error.
```

## Source note 12, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L79)

```text
/// Instruction words switchable patches change, by guest address.
```

## Source note 13, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L90)

```text
// Authority Levels
```

## Source note 14, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L92)

```text
// Determines boundary mutability and merge eligibility.
```

## Source note 15, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L93)

```text
// Only GAP_FILL can be absorbed during vacancy merging.
```

## Source note 16, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L94)

```text
// All others represent immutable entry points.
```

## Source note 17, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L96)

```text
// Speculative - found in unclaimed gap, CAN be absorbed
```

## Source note 18, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L97)

```text
// Found via bl/bcl - immutable entry point
```

## Source note 19, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L98)

```text
// Found in vtable - immutable entry point
```

## Source note 20, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L99)

```text
// Save/restore helpers - fixed, overlaps allowed
```

## Source note 21, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L100)

```text
// From .pdata - entry fixed, can extend
```

## Source note 22, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L101)

```text
// User config - exact boundaries, immutable
```

## Source note 23, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L102)

```text
// Import thunk - external function, immutable
```

## Source note 24, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L106)

```text
// Target Classification (for code generation)
```

## Source note 25, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L109)

```text
// Target inside caller's function (PIC pattern)
```

## Source note 26, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L110)

```text
// Target is a function entry point
```

## Source note 27, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L111)

```text
// Target is an import
```

## Source note 28, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L112)

```text
// Target not recognized
```

## Source note 29, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L118)

```text
// Function State (3-state machine)
```

## Source note 30, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L121)

```text
// Entry point known, blocks/instructions not yet assigned
```

## Source note 31, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L122)

```text
// Blocks and instructions assigned, may have unresolved branches
```

## Source note 32, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L123)

```text
// All branches resolved, ready for code generation
```

## Source note 33, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L126)

```text
// Legacy aliases for compatibility during migration
```

## Source note 34, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L127)

```text
// Will be removed
```

## Source note 35, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L128)

```text
// Will be removed
```

## Source note 36, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L131)

```text
// Exception Handling - SEH (Structured Exception Handling)
```

## Source note 37, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L135)

```text
// [+0] Start of __try block
```

## Source note 38, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L136)

```text
// [+4] End of __try block
```

## Source note 39, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L137)

```text
// [+8] Handler function (__finally or __except body)
```

## Source note 40, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L138)

```text
// [+C] Filter expression (0 for __finally, address for __except)
```

## Source note 41, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L142)

```text
// e.g. __C_specific_handler thunk address
```

## Source note 42, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L143)

```text
// Pointer to scope table in .rdata
```

## Source note 43, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L145)

```text
// Stack frame size for r12 setup during unwind
```

## Source note 44, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L146)

```text
// __restgprlr_N address to call on unwind
```

## Source note 45, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L150)

```text
// Exception Handling - C++ EH (FuncInfo with magic 0x19930522)
```

## Source note 46, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L156)

```text
// Previous state (-1 = terminal)
```

## Source note 47, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L157)

```text
// Cleanup/destructor function address
```

## Source note 48, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L161)

```text
// Code address where state changes
```

## Source note 49, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L162)

```text
// State number at this IP
```

## Source note 50, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L166)

```text
// Catch type flags
```

## Source note 51, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L167)

```text
// Pointer to type descriptor (RTTI)
```

## Source note 52, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L168)

```text
// Displacement of catch object
```

## Source note 53, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L169)

```text
// Catch handler function address
```

## Source note 54, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L173)

```text
// Lowest state in try
```

## Source note 55, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L174)

```text
// Highest state in try
```

## Source note 56, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L175)

```text
// Highest state in catch
```

## Source note 57, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L180)

```text
// Frame handler function
```

## Source note 58, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L181)

```text
// Address of FuncInfo in .rdata
```

## Source note 59, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L182)

```text
// Number of unwind states
```

## Source note 60, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L189)

```text
// Combined Exception Info (variant of SEH or C++ EH)
```

## Source note 61, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L212)

```text
// Call Target - Resolved destination of a call/jump
```

## Source note 62, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L246)

```text
// Call Edge - A call site within a function
```

## Source note 63, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L250)

```text
// Address of the bl/b instruction
```

## Source note 64, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L251)

```text
// Resolved or unresolved target
```

## Source note 65, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L255)

```text
// Basic Block
```

## Source note 66, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L267)

```text
// Jump Table
```

## Source note 67, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L271)

```text
// Address of bctr instruction
```

## Source note 68, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L272)

```text
// Address of jump table data
```

## Source note 69, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L273)

```text
// Register holding switch index
```

## Source note 70, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L274)

```text
// Resolved case targets (internal labels)
```

## Source note 71, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L278)

```text
// Function Analysis (computed at seal time)
```

## Source note 72, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L282)

```text
// CSR requirements (denormal handling)
```

## Source note 73, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L285)

```text
// Special register usage
```

## Source note 74, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L291)

```text
// CSR state needed
```

## Source note 75, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L296)

```text
// Unresolved Jump - Internal jump awaiting resolution
```

## Source note 76, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L300)

```text
// Address of the branch instruction
```

## Source note 77, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L301)

```text
// Target address
```

## Source note 78, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L302)

```text
// true = bl (call), false = b (tail call)
```

## Source note 79, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L303)

```text
// true = bc/beq/bne/etc, false = b
```

## Source note 80, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L307)

```text
// Code Buffer - Holds executable code for a section
```

## Source note 81, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L309)

```text
// The graph owns code buffers so recompilation doesn't need module access.
```

## Source note 82, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/include/rex/codegen/function_types.h#L310)

```text
// Each buffer corresponds to one executable section.
```
