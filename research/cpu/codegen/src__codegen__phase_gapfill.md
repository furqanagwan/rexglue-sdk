# Phase gapfill: codegen source notes

This record preserves technical and API notes moved from `src/codegen/phase_gapfill.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L39)

```text
// GapFill to register uncovered code regions
```

## Source note 2, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L42)

```text
// Split a code region into function segments based on terminators (blr, tail calls).
```

## Source note 3, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L59)

```text
// Check for terminators
```

## Source note 4, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L65)

```text
// Don't split on tail recursion (branch to own segment start)
```

## Source note 5, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L83)

```text
// Handle remaining code after last terminator
```

## Source note 6, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L91)

```text
// Check if address looks like exception handler data (handler ptr + rdata ptr)
```

## Source note 7, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L100)

```text
// Exception handler data pattern:
```

## Source note 8, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L101)

```text
// [addr+0]: pointer to __C_specific_handler (entry point)
```

## Source note 9, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L102)

```text
// [addr+4]: pointer to scope table in .rdata
```

## Source note 10, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L106)

```text
// Check if first dword is a known entry point (like __C_specific_handler)
```

## Source note 11, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L111)

```text
// Check if second dword points to .rdata section
```

## Source note 12, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L129)

```text
// Registers a segment as a GAP_FILL function unless it starts at a known
```

## Source note 13, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L130)

```text
// entry, inside another function, or on exception data. Returns whether it
```

## Source note 14, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L131)

```text
// registered one.
```

## Source note 15, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L154)

```text
// Build set of known callables for tail call detection
```

## Source note 16, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L165)

```text
// Split region on terminators (blr, tail calls), then check each segment
```

## Source note 17, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L189)

```text
// Leftovers of gap segments (RG-FIX-002)
```

## Source note 18, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L192)

```text
// A gap segment ends at a blr or at a tail call to a function known when the
```

## Source note 19, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L193)

```text
// segment was cut. An indirect bctr or a tail call to a function found later
```

## Source note 20, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L194)

```text
// doesn't split it, so discovery can end the segment's function well before
```

## Source note 21, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L195)

```text
// the segment does: a thunk `addi r3,r3,-4; b sub_X` followed by the next
```

## Source note 22, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L196)

```text
// function. Those bytes were then claimed by no one and never looked at again
```

## Source note 23, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L197)

```text
// (RG-FIX-002).
```

## Source note 24, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L199)

```text
// The same happens when a segment starts at a function a call found earlier:
```

## Source note 25, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L200)

```text
// gap fill skips the whole segment, so the code after that function's body
```

## Source note 26, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L201)

```text
// (and after any functions following it back to back) was never looked at.
```

## Source note 27, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L202)

```text
// Blood Stone's thunk sub_8222D580 hid sub_8222D588, and 007 Legends'
```

## Source note 28, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L203)

```text
// sub_826D3EE0 and sub_826D3F08 hid sub_826D3F38, each reached only by a tail
```

## Source note 29, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L204)

```text
// branch from another function. A segment that starts inside a function
```

## Source note 30, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L205)

```text
// hides code the same way: 007 Legends' one-instruction thunk sub_82225D90,
```

## Source note 31, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L206)

```text
// called only through a pointer, follows a .pdata function ending there.
```

## Source note 32, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L208)

```text
// Follows the discovered bodies of the functions at or around the start of
```

## Source note 33, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L209)

```text
// `segment` back to back, adding them to `owners`. A .pdata or config
```

## Source note 34, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L210)

```text
// function owns its declared extent. Returns the first address none of them
```

## Source note 35, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L211)

```text
// covers.
```

## Source note 36, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L223)

```text
// Blocks past the segment don't count: a tail branch to a function not
```

## Source note 37, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L224)

```text
// yet known is followed as if it were the function's own code.
```

## Source note 38, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L244)

```text
// Addresses in executable sections that a non-executable section holds as an
```

## Source note 39, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L245)

```text
// aligned big-endian word: method tables and other function pointers.
```

## Source note 40, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L262)

```text
// Returns the gap functions registered in the leftovers of gap functions and
```

## Source note 41, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L263)

```text
// of `entrySegments`. A leftover is skipped when a function before it
```

## Source note 42, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L264)

```text
// branches into it (the code is that function's own, found later by Merge)
```

## Source note 43, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L265)

```text
// or when it starts with zero padding.
```

## Source note 44, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L309)

```text
// Compilers may leave an unreachable blr after a tail dispatch. Without
```

## Source note 45, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L310)

```text
// independent entry evidence, a return-only suffix is not a new function.
```

## Source note 46, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L311)

```text
// A pointer to it in data is such evidence: an empty method in a method
```

## Source note 47, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L312)

```text
// table (Blood Stone's sub_8218F208, after sub_8218F1F8's bctr).
```

## Source note 48, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L334)

```text
// Cleanup absorbed GAP_FILL functions
```

## Source note 49, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L351)

```text
// This GAP_FILL is inside another function's blocks
```

## Source note 50, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L353)

```text
// Absorbed by higher authority - remove
```

## Source note 51, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L357)

```text
// Both GAP_FILL, other has lower address - it survives
```

## Source note 52, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L373)

```text
// anonymous namespace
```

## Source note 53, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L381)

```text
// Discover blocks for gap-filled functions
```

## Source note 54, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L382)

```text
/*excludeGapFill=*/
```

## Source note 55, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L386)

```text
// Leftovers can hold more leftovers (a run of thunks), so repeat until
```

## Source note 56, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L387)

```text
// nothing new is found.
```

## Source note 57, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/phase_gapfill.cpp#L395)

```text
/*excludeGapFill=*/
```
