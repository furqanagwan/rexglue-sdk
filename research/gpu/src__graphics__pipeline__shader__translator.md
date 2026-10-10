# Translator: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/translator.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L29)

```text
// The Xbox 360 GPU is effectively an Adreno A200:
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L30)

```text
// https://github.com/freedreno/freedreno/wiki/A2XX-Shader-Instruction-Set-Architecture
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L32)

```text
// A lot of this information is derived from the freedreno drivers, AMD's
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L33)

```text
// documentation, publicly available Xbox presentations (from GDC/etc), and
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L34)

```text
// other reverse engineering.
```

## Source note 6, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L36)

```text
// Naming has been matched as closely as possible to the real thing by using the
```

## Source note 7, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L37)

```text
// publicly available XNA Game Studio shader assembler.
```

## Source note 8, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L38)

```text
// You can find a tool for exploring this under tools/shader-playground/,
```

## Source note 9, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L39)

```text
// allowing interative assembling/disassembling of shader code.
```

## Source note 10, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L41)

```text
// Though the 360's GPU is similar to the Adreno r200, the microcode format is
```

## Source note 11, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L42)

```text
// slightly different. Though this is a great guide it cannot be assumed it
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L43)

```text
// matches the 360 in all areas:
```

## Source note 13, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L44)

```text
// https://github.com/freedreno/freedreno/blob/master/util/disasm-a2xx.c
```

## Source note 14, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L46)

```text
// Lots of naming comes from the disassembly spit out by the XNA GS compiler
```

## Source note 15, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L47)

```text
// and dumps of d3dcompiler and games: https://pastebin.com/i4kAv7bB
```

## Source note 16, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L54)

```text
// Control flow instructions come paired in blocks of 3 dwords and all are
```

## Source note 17, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L55)

```text
// listed at the top of the ucode.
```

## Source note 18, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L56)

```text
// Each control flow instruction is executed sequentially until the final
```

## Source note 19, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L57)

```text
// ending instruction.
```

## Source note 20, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L58)

```text
// Gather the upper bound of the control flow instructions, and label
```

## Source note 21, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L59)

```text
// addresses, which are needed for disassembly.
```

## Source note 22, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L61)

```text
// Jumps back (source, target) for finding what may reenter a label.
```

## Source note 23, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L67)

```text
// Guess how long the control flow program is by scanning for the first
```

## Source note 24, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L68)

```text
// kExec-ish and instruction and using its address as the upper bound.
```

## Source note 25, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L69)

```text
// This is what freedreno does.
```

## Source note 26, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L77)

```text
// The instruction after the call is the subroutine return point, so
```

## Source note 27, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L78)

```text
// it must be a label that ret can jump back to.
```

## Source note 28, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L103)

```text
// Disassemble and gather information.
```

## Source note 29, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L201)

```text
// A label jumped back to may be reentered after anything within the span of
```

## Source note 30, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L202)

```text
// the jumps back overlapping it. With subroutines, anything may be executed
```

## Source note 31, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L203)

```text
// before returning to a label.
```

## Source note 32, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L247)

```text
// All potentially can be referenced.
```

## Source note 33, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L254)

```text
// Each bit indicates a vec4 (4 floats).
```

## Source note 34, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L260)

```text
// Gather potentially "dirty" memexport elements before each control flow
```

## Source note 35, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L261)

```text
// instruction. `alloc` (any, not only `export`) flushes the previous memory
```

## Source note 36, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L262)

```text
// export. On the guest GPU, yielding / serializing also terminates memory
```

## Source note 37, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L263)

```text
// exports, but for simplicity disregarding that, as that functionally does
```

## Source note 38, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L264)

```text
// nothing compared to flushing the previous memory export only at `alloc`
```

## Source note 39, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L265)

```text
// or even only specifically at `alloc export`, Microsoft's validator checks
```

## Source note 40, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L266)

```text
// if eM# aren't written after a `serialize`.
```

## Source note 41, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L276)

```text
// Until subroutine calls are handled accurately, assume that all eM#
```

## Source note 42, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L277)

```text
// have potentially been written by the subroutine for simplicity.
```

## Source note 43, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L284)

```text
// If the control flow instruction potentially results in any eM# being
```

## Source note 44, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L285)

```text
// written, mark those eM# as potentially written before each successor.
```

## Source note 45, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L296)

```text
// Already marked as written before this instruction (and thus
```

## Source note 46, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L297)

```text
// before all its successors too). Possibly this instruction is in a
```

## Source note 47, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L298)

```text
// loop, in this case an instruction may succeed itself.
```

## Source note 48, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L301)

```text
// The first instruction in the traversal is the writing instruction
```

## Source note 49, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L302)

```text
// itself, not its successor. However, if it has been visited by the
```

## Source note 50, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L303)

```text
// traversal twice, it's in a loop, so it succeeds itself, and thus
```

## Source note 51, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L304)

```text
// writes from it are potentially done before it too.
```

## Source note 52, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L318)

```text
// One successor: end.
```

## Source note 53, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L325)

```text
// Two successors: next, end.
```

## Source note 54, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L329)

```text
// Two successors: next, skip.
```

## Source note 55, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L333)

```text
// Two successors: next, repeat.
```

## Source note 56, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L337)

```text
// Two successors: next, target.
```

## Source note 57, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L341)

```text
// Currently treating all subroutine calls as potentially writing
```

## Source note 58, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L342)

```text
// all eM# for simplicity, so just exit the subroutine.
```

## Source note 59, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L346)

```text
// One or two successors: next if conditional, target.
```

## Source note 60, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L353)

```text
// Any `alloc` ends the previous export.
```

## Source note 61, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L373)

```text
// An empty shader can be created internally by shader translators as a dummy,
```

## Source note 62, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L374)

```text
// don't dump it.
```

## Source note 63, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L390)

```text
// Will be overwritten by PsParamGen.
```

## Source note 64, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L440)

```text
// Mini-fetches inherit the operands from full fetches.
```

## Source note 65, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L447)

```text
// Don't bother setting up a binding for an instruction that fetches nothing.
```

## Source note 66, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L448)

```text
// In case of vfetch_full, however, it may still be used to set up addressing
```

## Source note 67, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L449)

```text
// for the subsequent vfetch_mini, so operand information must still be
```

## Source note 68, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L450)

```text
// gathered.
```

## Source note 69, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L455)

```text
// Try to allocate an attribute on an existing binding.
```

## Source note 70, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L456)

```text
// If no binding for this fetch slot is found create it.
```

## Source note 71, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L461)

```text
// It may not hold that all strides are equal, but I hope it does.
```

## Source note 72, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L480)

```text
// Populate attribute.
```

## Source note 73, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L496)

```text
// Coordinates of fetches that may snap to texel centers, for translators
```

## Source note 74, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L497)

```text
// that keep them exact (xenia-edge).
```

## Source note 75, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L514)

```text
// Doesn't use bindings.
```

## Source note 76, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L517)

```text
// Continue.
```

## Source note 77, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L523)

```text
// Check and see if this fetch constant was previously used...
```

## Source note 78, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L532)

```text
// Assign a unique binding index.
```

## Source note 79, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L560)

```text
// Store used memexport constants because CPU code needs addresses and sizes.
```

## Source note 80, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L561)

```text
// eA is (hopefully) always written to using:
```

## Source note 81, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L562)

```text
// mad eA, r#, const0100, c#
```

## Source note 82, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L563)

```text
// (though there are some exceptions, shaders in 4D5307E6 for some reason set
```

## Source note 83, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L564)

```text
// eA to zeros, but the swizzle of the constant is not .xyzw in this case, and
```

## Source note 84, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L565)

```text
// they don't write to eM#).
```

## Source note 85, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L566)

```text
// Export is done to vector_dest of the ucode instruction for both vector and
```

## Source note 86, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L567)

```text
// scalar operations - no need to check separately.
```

## Source note 87, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L592)

```text
// Store used float constants before translating so the
```

## Source note 88, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L593)

```text
// translator can use tightly packed indices if not dynamically
```

## Source note 89, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L594)

```text
// indexed.
```

## Source note 90, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L614)

```text
// Fetch instructions can't export - don't need the current memexport count
```

## Source note 91, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L615)

```text
// operand.
```

## Source note 92, line 626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L626)

```text
// Registers 0-15 (4 components each) the control flow instruction writes.
```

## Source note 93, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L699)

```text
// An array of registers at the end of the r# space may be dynamically
```

## Source note 94, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L700)

```text
// addressable - ensure enough space, as specified in SQ_PROGRAM_CNTL, is
```

## Source note 95, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L701)

```text
// allocated.
```

## Source note 96, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L719)

```text
// Translate all instructions.
```

## Source note 97, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L750)

```text
// Not published here: the backend still prepares the translation (binding
```

## Source note 98, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L751)

```text
// layouts, disassembly) and calls PublishTranslated when it's done, so a
```

## Source note 99, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L752)

```text
// thread that sees is_translated() never reads a half-prepared translation
```

## Source note 100, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L753)

```text
// (has207/xenia-edge 462a1ac85, adapted).
```

## Source note 101, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L754)

```text
// In case is_valid_ is modified by PostTranslation, reload.
```

## Source note 102, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1040)

```text
// ucode::FetchDestinationSwizzle::k0 or the invalid swizzle 6.
```

## Source note 103, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1061)

```text
// Reuse previous vfetch_full if this is a mini.
```

## Source note 104, line 1212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1212)

```text
// Not checking if the MipFilter is basemap because XNA doesn't accept
```

## Source note 105, line 1213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1213)

```text
// MipFilter for getCompTexLOD.
```

## Source note 106, line 1276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1276)

```text
// Scalar `a` (W).
```

## Source note 107, line 1312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1312)

```text
// In case both vector and scalar operations are nop, still need to write
```

## Source note 108, line 1313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1313)

```text
// somewhere that it's an export, not mov r0._, r0 + retain_prev r0._.
```

## Source note 109, line 1314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1314)

```text
// Accurate round trip is possible only if the target is o0 or oC0, because
```

## Source note 110, line 1315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1315)

```text
// if the total write mask is empty, the XNA assembler forces the
```

## Source note 111, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1316)

```text
// destination to be o0/oC0, but this doesn't really matter in this case.
```

## Source note 112, line 1335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1335)

```text
// Both vector and scalar operation export to vector_dest.
```

## Source note 113, line 1372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1372)

```text
// Vector operation and constant 0/1 writes.
```

## Source note 114, line 1413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1413)

```text
// Scalar operation.
```

## Source note 115, line 1444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1444)

```text
// Constant and temporary register.
```

## Source note 116, line 1449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1449)

```text
// Left-hand constant operand (`a` - W swizzle).
```

## Source note 117, line 1468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1468)

```text
// Right-hand temporary register operand (`b` - X swizzle).
```

## Source note 118, line 1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1492)

```text
// For exports, if both are nop, the vector operation will be kept to state in
```

## Source note 119, line 1493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/translator.cpp#L1493)

```text
// the microcode that the destination in the microcode is an export.
```
