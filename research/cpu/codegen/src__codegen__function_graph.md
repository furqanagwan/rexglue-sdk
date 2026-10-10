# Function graph: codegen source notes

This record preserves technical and API notes moved from `src/codegen/function_graph.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L70)

```text
// Generate default name
```

## Source note 2, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L75)

```text
// All functions start kRegistered - waiting for discover() to assign blocks.
```

## Source note 3, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L76)

```text
// Authority prevents merging via vacancy checks, not via initial state.
```

## Source note 4, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L80)

```text
// State Machine Methods
```

## Source note 5, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L88)

```text
// Non-imports must have blocks
```

## Source note 6, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L97)

```text
// Update size based on blocks
```

## Source note 7, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L115)

```text
// blocks_ and instructions_ remain empty for imports
```

## Source note 8, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L124)

```text
// Imports can seal without blocks
```

## Source note 9, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L126)

```text
// Non-imports must have blocks
```

## Source note 10, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L128)

```text
// All branches must be resolved
```

## Source note 11, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L141)

```text
// Extend size if block extends past current end
```

## Source note 12, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L149)

```text
// First check overall bounds
```

## Source note 13, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L154)

```text
// If no blocks defined, use linear range
```

## Source note 14, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L159)

```text
// Check individual blocks
```

## Source note 15, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L166)

```text
// For CONFIG and PDATA functions, trust the declared size even if blocks don't cover it
```

## Source note 16, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L167)

```text
// This handles out-of-line switch cases where compiler places code after epilogue
```

## Source note 17, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L169)

```text
// Already passed bounds check above
```

## Source note 18, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L188)

```text
// All jump table targets become labels
```

## Source note 19, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L214)

```text
// Check each unresolved jump
```

## Source note 20, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L217)

```text
// Target matches new function's entry point -> external call/tail call
```

## Source note 21, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L222)

```text
// Add as tail call (unconditional branch to another function)
```

## Source note 22, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L246)

```text
// Add as tail call to import
```

## Source note 23, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L260)

```text
// Check if target is within our blocks
```

## Source note 24, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L265)

```text
// It's internal - add as label
```

## Source note 25, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L273)

```text
// Add as a new block
```

## Source note 26, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L283)

```text
// Sort blocks by address for correct emission order
```

## Source note 27, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L287)

```text
// Merge overlapping blocks - can happen when multiple paths reach the same code
```

## Source note 28, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L288)

```text
// (e.g., jump table targets and unconditional branches both targeting an epilogue)
```

## Source note 29, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L298)

```text
// Check for overlap or adjacency
```

## Source note 30, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L300)

```text
// Extend last block to cover both
```

## Source note 31, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L319)

```text
// Compute function analysis
```

## Source note 32, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L330)

```text
// FunctionNode - C++ Code Emission
```

## Source note 33, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L335)

```text
// Helper: append formatted text to a raw string (matches Recompiler::println pattern)
```

## Source note 34, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L350)

```text
// Disassemble reads guest-order (big-endian) words from memory.
```

## Source note 35, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L363)

```text
// --- Empty stub for functions with no blocks ---
```

## Source note 36, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L383)

```text
// --- Check for SEH exception info ---
```

## Source note 37, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L392)

```text
// --- First pass: collect labels from all blocks ---
```

## Source note 38, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L412)

```text
// Labels from config switch tables
```

## Source note 39, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L419)

```text
// Labels and extern declarations from mid-asm hooks
```

## Source note 40, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L471)

```text
// Collect labels from auto-detected jump tables
```

## Source note 41, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L478)

```text
// --- Function name ---
```

## Source note 42, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L488)

```text
// Function signature with weak/alias pattern
```

## Source note 43, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L492)

```text
// Taking setjmp's address cannot preserve its native caller's continuation.
```

## Source note 44, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L493)

```text
// Fail explicitly instead of emitting an ordinary returning PPC substitute.
```

## Source note 45, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L505)

```text
// --- Second pass: emit instruction code ---
```

## Source note 46, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L511)

```text
// Local map for late-detected jump tables (can't mutate const config)
```

## Source note 47, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L531)

```text
// Only emit each label once
```

## Source note 48, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L537)

```text
// Look up switch table for this address
```

## Source note 49, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L549)

```text
// A switchable patch's register sets run before this instruction.
```

## Source note 50, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L568)

```text
// A switchable patch's word: both versions, chosen by its flag.
```

## Source note 51, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L596)

```text
// Either version may have run: forget what is known of the CSR.
```

## Source note 52, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L611)

```text
// Late jump table detection for bctr
```

## Source note 53, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L612)

```text
// Discovery already resolved this branch's table. A second scan may
```

## Source note 54, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L613)

```text
// infer a different index register from the same PPC address setup;
```

## Source note 55, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L614)

```text
// keep the graph's validated table as the source of truth.
```

## Source note 56, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L653)

```text
// Emit comment with instruction disassembly
```

## Source note 57, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L656)

```text
// Check for mid-asm hook BEFORE instruction
```

## Source note 58, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L661)

```text
// Dispatch instruction to builder
```

## Source note 59, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L675)

```text
// Check for mid-asm hook AFTER instruction
```

## Source note 60, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L686)

```text
// --- Close function body (or SEH try block) ---
```

## Source note 61, line 720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L720)

```text
// --- Emit local variable declarations, then body ---
```

## Source note 62, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L759)

```text
// If SEH, emit SEH_TRY and indent body
```

## Source note 63, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L781)

```text
// CodeBuffer buffer;
```

## Source note 64, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L782)

```text
// buffer.baseAddress = baseAddress;
```

## Source note 65, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L783)

```text
// buffer.data.assign(data, data + size);
```

## Source note 66, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L784)

```text
// codeBuffers_.push_back(std::move(buffer));
```

## Source note 67, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L785)

```text
// REXCODEGEN_DEBUG("FunctionGraph: added code buffer 0x{:08X}-0x{:08X} ({} bytes)",
```

## Source note 68, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L786)

```text
//                 baseAddress, baseAddress + static_cast<uint32_t>(size), size);
```

## Source note 69, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L792)

```text
// for (const auto& buffer : codeBuffers_) {
```

## Source note 70, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L793)

```text
//     if (buffer.contains(addr)) {
```

## Source note 71, line 794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L794)

```text
//         return buffer.translate(addr);
```

## Source note 72, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L797)

```text
// return nullptr;
```

## Source note 73, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L801)

```text
// size_t updated = 0;
```

## Source note 74, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L802)

```text
// for (auto& [base, node] : functions_) {
```

## Source note 75, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L803)

```text
//     const uint8_t* code = translateCode(base);
```

## Source note 76, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L804)

```text
//     if (code) {
```

## Source note 77, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L805)

```text
//         node->setCode(code);
```

## Source note 78, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L806)

```text
//         updated++;
```

## Source note 79, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L807)

```text
//     } else {
```

## Source note 80, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L808)

```text
//         REXCODEGEN_WARN("FunctionGraph: no code buffer for function 0x{:08X}", base);
```

## Source note 81, line 811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L811)

```text
// REXCODEGEN_DEBUG("FunctionGraph: updated code pointers for {} functions", updated);
```

## Source note 82, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L815)

```text
// FunctionGraph - Function Management
```

## Source note 83, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L820)

```text
// Check for existing function at this address
```

## Source note 84, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L825)

```text
// Higher authority wins
```

## Source note 85, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L833)

```text
// Replace with higher authority
```

## Source note 86, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L838)

```text
// Create new node
```

## Source note 87, line 844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L844)

```text
// Track xrefs for merge eligibility
```

## Source note 88, line 847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L847)

```text
// Notify all PENDING functions
```

## Source note 89, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L863)

```text
// Add as function with IMPORT authority
```

## Source note 90, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L887)

```text
// Clean up xref tracking
```

## Source note 91, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L892)

```text
// O(log f) lookup via sorted base index: find last function with base <= addr
```

## Source note 92, line 962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L962)

```text
// Function Setup (called during Discover phase)
```

## Source note 93, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1019)

```text
// Try immediate resolution against existing functions/imports
```

## Source note 94, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1021)

```text
// Target is a known function - resolve as call or tail call
```

## Source note 95, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1033)

```text
// Target is an import - resolve as call or tail call to import
```

## Source note 96, line 1046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1046)

```text
// Not resolvable yet - add as unresolved
```

## Source note 97, line 1053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1053)

```text
// Resolution and Expansion (called during Merge phase)
```

## Source note 98, line 1063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1063)

```text
// Get copy of unresolved jumps (list will be modified)
```

## Source note 99, line 1070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1070)

```text
// Try internal label first
```

## Source note 100, line 1078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1078)

```text
// Try function entry
```

## Source note 101, line 1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1092)

```text
// Try import
```

## Source note 102, line 1193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1193)

```text
// Vacancy Checking
```

## Source note 103, line 1202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1202)

```text
// Rule 1: Check for null dword at boundary
```

## Source note 104, line 1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1205)

```text
// Check for null at target (typical inter-function padding)
```

## Source note 105, line 1215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1215)

```text
// Rule 2: Check if any chunk claims the target region
```

## Source note 106, line 1224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1224)

```text
// Rule 3: Check if target falls within any function's range
```

## Source note 107, line 1227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1227)

```text
// Target is within a function - check if it's mergeable
```

## Source note 108, line 1229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1229)

```text
// GAP_FILL can be absorbed
```

## Source note 109, line 1231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1231)

```text
// Don't block, it's mergeable
```

## Source note 110, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1233)

```text
// Protected function - blocks vacancy
```

## Source note 111, line 1240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1240)

```text
// green light for vacancy
```

## Source note 112, line 1245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1245)

```text
// MSVC compiles __finally / __except bodies as funclets that run on the
```

## Source note 113, line 1246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1246)

```text
// owner's frame with its non-volatiles still live, and reaches an inline one
```

## Source note 114, line 1247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1247)

```text
// by bl from the middle of the owner. Localizing the funclet's copies hands it
```

## Source note 115, line 1248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1248)

```text
// a zero. The scope table names each funclet, which is the only reliable way
```

## Source note 116, line 1249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1249)

```text
// to tell one from a real function: every prologue reads its non-volatiles in
```

## Source note 117, line 1250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1250)

```text
// order to spill them, so "reads before writes" cannot distinguish them. C++
```

## Source note 118, line 1251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1251)

```text
// EH cleanup and catch funclets run the same way, so they are claimed too. The
```

## Source note 119, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1252)

```text
// owner stays localized and syncs across the call site instead, so it keeps
```

## Source note 120, line 1253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1253)

```text
// its isolation from its own callers.
```

## Source note 121, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1254)

```text
// funclet [base, end)
```

## Source note 122, line 1306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1306)

```text
// A funclet compiled with both an unwind entry and an inline bl entry lands in
```

## Source note 123, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1307)

```text
// the graph as two nodes sharing one tail. The scope table names only the
```

## Source note 124, line 1308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1308)

```text
// first, so sweep the extent for the rest.
```

## Source note 125, line 1321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1321)

```text
// Only entry points can be mergeable
```

## Source note 126, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1324)

```text
// Not an entry point
```

## Source note 127, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1329)

```text
// Only GAP_FILL authority can be absorbed
```

## Source note 128, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1330)

```text
// All other authorities represent immutable entry points
```

## Source note 129, line 1336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1336)

```text
// Address lookup alone is ambiguous when a shared block also has its own entry.
```

## Source note 130, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1339)

```text
// Case 1: Target is an import - always a call/tail-call
```

## Source note 131, line 1344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1344)

```text
// Case 2: Target is the caller's own entry point
```

## Source note 132, line 1346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1346)

```text
// bl to own base = recursive call (Function)
```

## Source note 133, line 1347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1347)

```text
// b to own base = loop back to start (InternalLabel)
```

## Source note 134, line 1351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1351)

```text
// Case 3a: a branch (not a call) into the caller's own blocks stays local,
```

## Source note 135, line 1352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1352)

```text
// even when another function also starts there. Discovery made it part of
```

## Source note 136, line 1353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1353)

```text
// this body, so no tail call was recorded for it: a null check that returns
```

## Source note 137, line 1354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1354)

```text
// 0 and otherwise falls into the virtual-call thunk after it, where the
```

## Source note 138, line 1355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1355)

```text
// thunk is also its own entry (RG-FIX-002).
```

## Source note 139, line 1362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1362)

```text
// Case 3: Target is a DIFFERENT function's entry point - this is a call/tail-call
```

## Source note 140, line 1363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1363)

```text
// This handles cases where a small thunk function branches to another function
```

## Source note 141, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1364)

```text
// whose entry point happens to fall within the thunk's address range
```

## Source note 142, line 1369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1369)

```text
// Case 4: Target is inside caller's function -> InternalLabel
```

## Source note 143, line 1370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1370)

```text
// For bl, this would be a rare PIC code pattern
```

## Source note 144, line 1375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/function_graph.cpp#L1375)

```text
// Case 5: Unknown target
```
