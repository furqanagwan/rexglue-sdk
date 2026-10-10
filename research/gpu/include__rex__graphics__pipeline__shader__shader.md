# Shader: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/shader.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L32)

```text
// The structures here are used for both translation and disassembly.
```

## Source note 2, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L34)

```text
// Because disassembly uses them too, to make sure "assemble -> disassemble ->
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L35)

```text
// reassemble" round trip is always successful with the XNA assembler (as it is
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L36)

```text
// the accuracy benchmark for translation), only generalization - not
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L37)

```text
// optimization like nop skipping/replacement - must be done while converting
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L38)

```text
// microcode to these structures (in other words, parsed shader code should be
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L39)

```text
// enough to accurately reconstruct the microcode for any shader that could be
```

## Source note 8, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L40)

```text
// written by a human in assembly).
```

## Source note 9, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L42)

```text
// During the "parsed -> host" part of the translation, however, translators are
```

## Source note 10, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L43)

```text
// free to make any optimizations (as long as they don't affect the result, of
```

## Source note 11, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L44)

```text
// course) they find appropriate.
```

## Source note 12, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L47)

```text
// Result is not stored.
```

## Source note 13, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L49)

```text
// Result is stored to a temporary register indexed by storage_index [0-63].
```

## Source note 14, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L51)

```text
// Result is stored into a vertex shader interpolator export [0-15].
```

## Source note 15, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L53)

```text
// Result is stored to the position export (gl_Position).
```

## Source note 16, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L55)

```text
// Result is stored to the vertex shader misc export register, see
```

## Source note 17, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L56)

```text
// ucode::ExportRegister::kVSPointSizeEdgeFlagKillVertex for description of
```

## Source note 18, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L57)

```text
// components.
```

## Source note 19, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L59)

```text
// Result is stored as memexport destination address
```

## Source note 20, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L60)

```text
// (see xenos::xe_gpu_memexport_stream_t).
```

## Source note 21, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L62)

```text
// Result is stored to memexport destination data.
```

## Source note 22, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L64)

```text
// Result is stored to a color target export indexed by storage_index [0-3].
```

## Source note 23, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L66)

```text
// X of the result is stored to the depth export (gl_FragDepth).
```

## Source note 24, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L70)

```text
// Must be used only in translation to skip unused components, but not in
```

## Source note 25, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L71)

```text
// disassembly (because oPts.x000 will be assembled, but oPts.x00_ has both
```

## Source note 26, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L72)

```text
// skipped components and zeros, which cannot be encoded, and therefore it will
```

## Source note 27, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L73)

```text
// not).
```

## Source note 28, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L88)

```text
// The storage index is not dynamically addressed.
```

## Source note 29, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L90)

```text
// The storage index is addressed by a0.
```

## Source note 30, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L91)

```text
// Float constants only.
```

## Source note 31, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L93)

```text
// The storage index is addressed by aL.
```

## Source note 32, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L94)

```text
// Float constants and temporary registers only.
```

## Source note 33, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L98)

```text
// Describes the source value of a particular component.
```

## Source note 34, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L100)

```text
// Component receives the source X.
```

## Source note 35, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L102)

```text
// Component receives the source Y.
```

## Source note 36, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L104)

```text
// Component receives the source Z.
```

## Source note 37, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L106)

```text
// Component receives the source W.
```

## Source note 38, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L108)

```text
// Component receives constant 0.
```

## Source note 39, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L110)

```text
// Component receives constant 1.
```

## Source note 40, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L131)

```text
// Where the result is going.
```

## Source note 41, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L133)

```text
// Index into the storage_target, if it is indexed.
```

## Source note 42, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L135)

```text
// How the storage index is dynamically addressed, if it is.
```

## Source note 43, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L138)

```text
// True to clamp the result value to [0-1].
```

## Source note 44, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L140)

```text
// Defines whether each output component is written, though this is from the
```

## Source note 45, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L141)

```text
// original microcode, not taking into account whether such components
```

## Source note 46, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L142)

```text
// actually exist in the target.
```

## Source note 47, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L144)

```text
// Defines the source for each output component xyzw.
```

## Source note 48, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L147)

```text
// Returns the write mask containing only components actually present in the
```

## Source note 49, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L148)

```text
// target.
```

## Source note 50, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L153)

```text
// True if the components are in their 'standard' swizzle arrangement (xyzw).
```

## Source note 51, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L159)

```text
// Returns the components of the result, before swizzling, that won't be
```

## Source note 52, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L160)

```text
// discarded or replaced with a constant.
```

## Source note 53, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L172)

```text
// Returns which components of the used write mask are constant, and what
```

## Source note 54, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L173)

```text
// values they have.
```

## Source note 55, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L197)

```text
// Source is stored in a temporary register indexed by storage_index [0-63].
```

## Source note 56, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L199)

```text
// Source is stored in a float constant indexed by storage_index [0-255].
```

## Source note 57, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L201)

```text
// Source is stored in a vertex fetch constant indexed by storage_index
```

## Source note 58, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L202)

```text
// [0-95].
```

## Source note 59, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L204)

```text
// Source is stored in a texture fetch constant indexed by storage_index
```

## Source note 60, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L205)

```text
// [0-31].
```

## Source note 61, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L210)

```text
// Where the source comes from.
```

## Source note 62, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L212)

```text
// Index into the storage_target, if it is indexed.
```

## Source note 63, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L214)

```text
// How the storage index is dynamically addressed, if it is.
```

## Source note 64, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L217)

```text
// True to negate the operand value.
```

## Source note 65, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L219)

```text
// True to take the absolute value of the source (before any negation).
```

## Source note 66, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L221)

```text
// Number of components taken from the source operand.
```

## Source note 67, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L223)

```text
// Defines the source for each component xyzw (up to the given
```

## Source note 68, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L224)

```text
// component_count).
```

## Source note 69, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L227)

```text
// Returns the swizzle source for the component, replicating the rightmost
```

## Source note 70, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L228)

```text
// component if there are less than 4 components (similar to what the Xbox 360
```

## Source note 71, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L229)

```text
// shader compiler does as a general rule for unspecified components).
```

## Source note 72, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L233)

```text
// True if the components are in their 'standard' swizzle arrangement (xyzw).
```

## Source note 73, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L243)

```text
// Returns which components of two operands will always be bitwise equal
```

## Source note 74, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L244)

```text
// (disregarding component_count for simplicity of usage with GetComponent,
```

## Source note 75, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L245)

```text
// treating the rightmost component as replicated). This, strictly with all
```

## Source note 76, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L246)

```text
// conditions, must be used when emulating Shader Model 3 +-0 * x = +0
```

## Source note 77, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L247)

```text
// multiplication behavior with IEEE-compliant multiplication (because
```

## Source note 78, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L248)

```text
// -0 * |-0|, or -0 * +0, is -0, while the result must be +0).
```

## Source note 79, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L264)

```text
// Index into the ucode dword source.
```

## Source note 80, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L267)

```text
// Opcode for the instruction.
```

## Source note 81, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L269)

```text
// Friendly name of the instruction.
```

## Source note 82, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L272)

```text
// Instruction address where ALU/fetch instructions reside.
```

## Source note 83, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L274)

```text
// Number of instructions to execute.
```

## Source note 84, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L278)

```text
// Block is always executed.
```

## Source note 85, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L280)

```text
// Execution is conditional on the value of the boolean constant.
```

## Source note 86, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L282)

```text
// Execution is predicated.
```

## Source note 87, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L285)

```text
// Condition required to execute the instructions.
```

## Source note 88, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L287)

```text
// Constant index used as the conditional if kConditional.
```

## Source note 89, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L289)

```text
// Required condition value of the comparision (true or false).
```

## Source note 90, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L292)

```text
// Whether this exec ends the shader.
```

## Source note 91, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L294)

```text
// Whether the hardware doesn't have to wait for the predicate to be updated
```

## Source note 92, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L295)

```text
// after this exec.
```

## Source note 93, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L300)

```text
// Sequence bits, 2 per instruction, indicating whether ALU or fetch.
```

## Source note 94, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L303)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 95, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L308)

```text
// Index into the ucode dword source.
```

## Source note 96, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L311)

```text
// Integer constant register that holds the loop parameters.
```

## Source note 97, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L312)

```text
// 0:7 - uint8 loop count, 8:15 - uint8 start aL, 16:23 - int8 aL step.
```

## Source note 98, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L314)

```text
// Whether to reuse the current aL instead of reset it to loop start.
```

## Source note 99, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L317)

```text
// Target address to jump to when skipping the loop.
```

## Source note 100, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L320)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 101, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L325)

```text
// Index into the ucode dword source.
```

## Source note 102, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L328)

```text
// Break from the loop if the predicate matches the expected value.
```

## Source note 103, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L330)

```text
// Required condition value of the comparision (true or false).
```

## Source note 104, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L333)

```text
// Integer constant register that holds the loop parameters.
```

## Source note 105, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L334)

```text
// 0:7 - uint8 loop count, 8:15 - uint8 start aL, 16:23 - int8 aL step.
```

## Source note 106, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L337)

```text
// Target address of the start of the loop body.
```

## Source note 107, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L340)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 108, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L345)

```text
// Index into the ucode dword source.
```

## Source note 109, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L348)

```text
// Target address.
```

## Source note 110, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L352)

```text
// Call is always made.
```

## Source note 111, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L354)

```text
// Call is conditional on the value of the boolean constant.
```

## Source note 112, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L356)

```text
// Call is predicated.
```

## Source note 113, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L359)

```text
// Condition required to make the call.
```

## Source note 114, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L361)

```text
// Constant index used as the conditional if kConditional.
```

## Source note 115, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L363)

```text
// Required condition value of the comparision (true or false).
```

## Source note 116, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L366)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 117, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L371)

```text
// Index into the ucode dword source.
```

## Source note 118, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L374)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 119, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L379)

```text
// Index into the ucode dword source.
```

## Source note 120, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L382)

```text
// Target address.
```

## Source note 121, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L386)

```text
// Jump is always taken.
```

## Source note 122, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L388)

```text
// Jump is conditional on the value of the boolean constant.
```

## Source note 123, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L390)

```text
// Jump is predicated.
```

## Source note 124, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L393)

```text
// Condition required to make the jump.
```

## Source note 125, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L395)

```text
// Constant index used as the conditional if kConditional.
```

## Source note 126, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L397)

```text
// Required condition value of the comparision (true or false).
```

## Source note 127, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L400)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 128, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L405)

```text
// Index into the ucode dword source.
```

## Source note 129, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L408)

```text
// The type of resource being allocated.
```

## Source note 130, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L410)

```text
// Total count associated with the allocation.
```

## Source note 131, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L413)

```text
// True if this allocation is in a vertex shader.
```

## Source note 132, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L416)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 133, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L421)

```text
// Opcode for the instruction.
```

## Source note 134, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L423)

```text
// Friendly name of the instruction.
```

## Source note 135, line 426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L426)

```text
// True if the fetch is reusing a previous full fetch.
```

## Source note 136, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L427)

```text
// The previous fetch source and constant data will be populated.
```

## Source note 137, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L430)

```text
// True if the instruction is predicated on the specified
```

## Source note 138, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L431)

```text
// predicate_condition.
```

## Source note 139, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L433)

```text
// Expected predication condition value if predicated.
```

## Source note 140, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L436)

```text
// Describes how the instruction result is stored.
```

## Source note 141, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L437)

```text
// Note that if the result doesn't have any components to write the fetched
```

## Source note 142, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L438)

```text
// value to, the address calculation in vfetch_full must still be performed
```

## Source note 143, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L439)

```text
// because such a vfetch_full may be used to setup addressing for vfetch_mini
```

## Source note 144, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L440)

```text
// (wires in the color pass of 5454082B do vfetch_full to r2.000_, and then a
```

## Source note 145, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L441)

```text
// true vfetch_mini).
```

## Source note 146, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L444)

```text
// Number of source operands.
```

## Source note 147, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L446)

```text
// Describes each source operand.
```

## Source note 148, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L447)

```text
// Note that for vfetch_mini, which inherits the operands from vfetch_full,
```

## Source note 149, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L448)

```text
// the index operand register may been overwritten between the vfetch_full and
```

## Source note 150, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L449)

```text
// the vfetch_mini (happens in 4D530910 for wheels), but that should have no
```

## Source note 151, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L450)

```text
// effect on the index actually used for fetching. A copy of the index
```

## Source note 152, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L451)

```text
// therefore must be stored by vfetch_full (the base address, stride and
```

## Source note 153, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L452)

```text
// rounding may be pre-applied to it since they will be the same in the
```

## Source note 154, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L453)

```text
// vfetch_full and all its vfetch_mini instructions).
```

## Source note 155, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L459)

```text
// In dwords.
```

## Source note 156, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L461)

```text
// Prefetch count minus 1.
```

## Source note 157, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L469)

```text
// Attributes describing the fetch operation.
```

## Source note 158, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L472)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 159, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L477)

```text
// Opcode for the instruction.
```

## Source note 160, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L479)

```text
// Friendly name of the instruction.
```

## Source note 161, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L481)

```text
// Texture dimension for opcodes that have multiple dimension forms.
```

## Source note 162, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L484)

```text
// True if the instruction is predicated on the specified
```

## Source note 163, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L485)

```text
// predicate_condition.
```

## Source note 164, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L487)

```text
// Expected predication condition value if predicated.
```

## Source note 165, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L490)

```text
// True if the instruction has a result.
```

## Source note 166, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L492)

```text
// Describes how the instruction result is stored.
```

## Source note 167, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L495)

```text
// Number of source operands.
```

## Source note 168, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L497)

```text
// Describes each source operand.
```

## Source note 169, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L517)

```text
// Attributes describing the fetch operation.
```

## Source note 170, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L520)

```text
// Considering the operation, dimensions, filter overrides, and the result
```

## Source note 171, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L521)

```text
// components, returns which components of the result will have a value that
```

## Source note 172, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L522)

```text
// is not always zero.
```

## Source note 173, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L525)

```text
// Whether the fetch can return a single texel with no instruction override to
```

## Source note 174, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L526)

```text
// linear/anisotropic filtering.
```

## Source note 175, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L535)

```text
// Whether a tfetch snaps its coordinates to the texel center instead of
```

## Source note 176, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L536)

```text
// adding kTextureCoordEpsilon. Only point sampled 2D fetches with normalized
```

## Source note 177, line 537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L537)

```text
// coordinates snap; the fetch constant side is bit 26 of
```

## Source note 178, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L538)

```text
// texture_util::GetIntegerScaleBits. The epsilon is there so host rounding
```

## Source note 179, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L539)

```text
// picks the texel guest truncation would, but near an edge it can push the
```

## Source note 180, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L540)

```text
// sample into the next texel: texture seams in 425307EC's virtual texture
```

## Source note 181, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L541)

```text
// tables (xenia-canary c3cd8617b1).
```

## Source note 182, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L549)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 183, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L553)

```text
// Fixed point texture coordinate ULP (see ProcessTextureFetchInstruction).
```

## Source note 184, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L557)

```text
// Opcode for the vector part of the instruction.
```

## Source note 185, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L559)

```text
// Opcode for the scalar part of the instruction.
```

## Source note 186, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L561)

```text
// Friendly name of the vector instruction.
```

## Source note 187, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L563)

```text
// Friendly name of the scalar instruction.
```

## Source note 188, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L566)

```text
// True if the instruction is predicated on the specified
```

## Source note 189, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L567)

```text
// predicate_condition.
```

## Source note 190, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L569)

```text
// Expected predication condition value if predicated.
```

## Source note 191, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L572)

```text
// Describes how the vector operation result and, for exports, constant 0/1
```

## Source note 192, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L573)

```text
// are stored. For simplicity of translation and disassembly, treating
```

## Source note 193, line 574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L574)

```text
// constant 0/1 writes as a part of the vector operation - they need to be
```

## Source note 194, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L575)

```text
// expressed somehow in the disassembly anyway with a properly disassembled
```

## Source note 195, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L576)

```text
// instruction even if only constants are being exported. The XNA disassembler
```

## Source note 196, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L577)

```text
// falls back to displaying the whole vector operation, even if only constant
```

## Source note 197, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L578)

```text
// components are written, if the scalar operation is a nop or if the vector
```

## Source note 198, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L579)

```text
// operation changes a0, p0 or kills pixels (but if the scalar operation isn't
```

## Source note 199, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L580)

```text
// nop, it outputs the entire constant mask in the scalar operation
```

## Source note 200, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L581)

```text
// destination). Normally the XNA disassembler outputs the constant mask in
```

## Source note 201, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L582)

```text
// both vector and scalar operations, but that's not required by assembler, so
```

## Source note 202, line 583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L583)

```text
// it doesn't really matter whether it's specified in the vector operation, in
```

## Source note 203, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L584)

```text
// the scalar operation, or in both.
```

## Source note 204, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L586)

```text
// Describes how the scalar operation result is stored.
```

## Source note 205, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L588)

```text
// Both operations must be executed before any result is stored if vector and
```

## Source note 206, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L589)

```text
// scalar operations are paired. There are cases of vector result being used
```

## Source note 207, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L590)

```text
// as scalar operand or vice versa (the ring on Avalanche in 4D5307E6, for
```

## Source note 208, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L591)

```text
// example), in this case there must be no dependency between the two
```

## Source note 209, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L592)

```text
// operations.
```

## Source note 210, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L594)

```text
// Number of source operands of the vector operation.
```

## Source note 211, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L596)

```text
// Describes each source operand of the vector operation.
```

## Source note 212, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L598)

```text
// Number of source operands of the scalar operation.
```

## Source note 213, line 600

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L600)

```text
// Describes each source operand of the scalar operation.
```

## Source note 214, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L603)

```text
// Whether the vector part of the instruction is the same as if it was omitted
```

## Source note 215, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L604)

```text
// in the assembly (if compiled or assembled with the Xbox 360 shader
```

## Source note 216, line 605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L605)

```text
// compiler), and thus reassembling the shader with this instruction omitted
```

## Source note 217, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L606)

```text
// will result in the same microcode (since instructions with just an empty
```

## Source note 218, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L607)

```text
// write mask may have different values in other fields).
```

## Source note 219, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L608)

```text
// This is for disassembly! Translators should use the write masks and
```

## Source note 220, line 609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L609)

```text
// the changed state bits in the opcode info to skip operations, as this only
```

## Source note 221, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L610)

```text
// covers one very specific nop format!
```

## Source note 222, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L612)

```text
// Whether the scalar part of the instruction is the same as if it was omitted
```

## Source note 223, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L613)

```text
// in the assembly (if compiled or assembled with the Xbox 360 shader
```

## Source note 224, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L614)

```text
// compiler), and thus reassembling the shader with this instruction omitted
```

## Source note 225, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L615)

```text
// will result in the same microcode (since instructions with just an empty
```

## Source note 226, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L616)

```text
// write mask may have different values in other fields).
```

## Source note 227, line 619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L619)

```text
// For translation (not disassembly) - whether this instruction has totally no
```

## Source note 228, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L620)

```text
// effect.
```

## Source note 229, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L623)

```text
// If this is a "normal" eA write recognized by Xenia (MAD with a stream
```

## Source note 230, line 624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L624)

```text
// constant), returns the index of the stream float constant, otherwise
```

## Source note 231, line 625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L625)

```text
// returns UINT32_MAX.
```

## Source note 232, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L628)

```text
// Disassembles the instruction into ucode assembly text.
```

## Source note 233, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L651)

```text
// Returns whether the fetch is a full one, and the next parsed mini vertex
```

## Source note 234, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L652)

```text
// fetch should inherit most of its parameters.
```

## Source note 235, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L663)

```text
// Type of the vertex shader on the host - shader interface depends on in, so
```

## Source note 236, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L664)

```text
// it must be known at translation time. If values are changed, INVALIDATE
```

## Source note 237, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L665)

```text
// SHADER STORAGES (increase their version constexpr) where those are stored!
```

## Source note 238, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L666)

```text
// And check bit count where this is packed. This is : uint32_t for simplicity
```

## Source note 239, line 667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L667)

```text
// of packing in bit fields.
```

## Source note 240, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L680)

```text
// For implementation without unconditional support for memory writes from
```

## Source note 241, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L681)

```text
// vertex shaders, vertex shader converted to a compute shader doing only
```

## Source note 242, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L682)

```text
// memory export.
```

## Source note 243, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L685)

```text
// 4 host vertices for 1 guest vertex, for implementations without
```

## Source note 244, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L686)

```text
// unconditional geometry shader support.
```

## Source note 245, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L688)

```text
// 3 guest vertices processed by the host shader invocation to choose the
```

## Source note 246, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L689)

```text
// strip orientation, for implementations without unconditional geometry
```

## Source note 247, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L690)

```text
// shader support.
```

## Source note 248, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L693)

```text
// For packing HostVertexShaderType in bit fields.
```

## Source note 249, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L708)

```text
// Fetch instruction with all parameters.
```

## Source note 250, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L712)

```text
// Index within the vertex binding listing.
```

## Source note 251, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L714)

```text
// Fetch constant index [0-95].
```

## Source note 252, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L716)

```text
// Stride of the entire binding, in words.
```

## Source note 253, line 718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L718)

```text
// Packed attributes within the binding buffer.
```

## Source note 254, line 723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L723)

```text
// Index within the texture binding listing.
```

## Source note 255, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L725)

```text
// Fetch constant index [0-31].
```

## Source note 256, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L727)

```text
// Fetch instruction with all parameters.
```

## Source note 257, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L732)

```text
// Bitmap of all kConstantFloat registers read by the shader.
```

## Source note 258, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L733)

```text
// Any shader can only read up to 256 of the 512, and the base is dependent
```

## Source note 259, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L734)

```text
// on the shader type and SQ_VS/PS_CONST registers. Each bit corresponds to
```

## Source note 260, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L735)

```text
// a storage index from the type base.
```

## Source note 261, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L737)

```text
// Bitmap of all loop constants read by the shader.
```

## Source note 262, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L738)

```text
// Each bit corresponds to a storage index [0-31].
```

## Source note 263, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L740)

```text
// Bitmap of all bool constants read by the shader.
```

## Source note 264, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L741)

```text
// Each bit corresponds to a storage index [0-255].
```

## Source note 265, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L743)

```text
// Bitmap of all vertex fetch constants read by the shader.
```

## Source note 266, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L744)

```text
// Each bit corresponds to a storage index [0-95].
```

## Source note 267, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L747)

```text
// Total number of kConstantFloat registers read by the shader.
```

## Source note 268, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L750)

```text
// Whether kConstantFloat registers are indexed dynamically - in this case,
```

## Source note 269, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L751)

```text
// float_bitmap must be set to all 1, and tight packing must not be done.
```

## Source note 270, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L754)

```text
// Returns the index of the float4 constant as if all float4 constant
```

## Source note 271, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L755)

```text
// registers actually referenced were tightly packed in a buffer, or
```

## Source note 272, line 756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L756)

```text
// UINT32_MAX if not found.
```

## Source note 273, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L762)

```text
// Any can potentially be read - not packing.
```

## Source note 274, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L779)

```text
// Which eM elements have potentially (regardless of conditionals, loop
```

## Source note 275, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L780)

```text
// iteration counts, predication) been written earlier in the predecessor
```

## Source note 276, line 781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L781)

```text
// graph of the instruction since an `alloc export`.
```

## Source note 277, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L783)

```text
// For exec sequences, which eM elements are potentially (regardless of
```

## Source note 278, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L784)

```text
// predication) written by the instructions in the sequence. For other
```

## Source note 279, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L785)

```text
// control flow instructions, it's 0.
```

## Source note 280, line 795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L795)

```text
// Translator-specific modification bits.
```

## Source note 281, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L798)

```text
// True if the shader was translated and prepared without error.
```

## Source note 282, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L801)

```text
// True if the shader has already been translated and prepared. Pipeline
```

## Source note 283, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L802)

```text
// caches check this without a lock before translating (double-checked
```

## Source note 284, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L803)

```text
// against the translation lock), so it is acquire-paired with the release
```

## Source note 285, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L804)

```text
// in PublishTranslated: once this reads true, the validity, the errors, the
```

## Source note 286, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L805)

```text
// translated binary and the backend's preparation are all visible.
```

## Source note 287, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L808)

```text
// Publishes the translation to lock-free readers of is_translated. Called
```

## Source note 288, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L809)

```text
// once by the backend after ShaderTranslator::TranslateAnalyzedShader and
```

## Source note 289, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L810)

```text
// all of its own preparation, whether or not the translation is valid.
```

## Source note 290, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L813)

```text
// Errors that occurred during translation.
```

## Source note 291, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L816)

```text
// Translated shader binary (or text).
```

## Source note 292, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L819)

```text
// A title's replacement shader (ShaderReplacements) stands in for the
```

## Source note 293, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L820)

```text
// translated binary. The translation's bindings and interface stay, so the
```

## Source note 294, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L821)

```text
// replacement must keep them. Only before PublishTranslated.
```

## Source note 295, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L826)

```text
// Gets the translated shader binary as a string.
```

## Source note 296, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L827)

```text
// This is only valid if it is actually text.
```

## Source note 297, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L830)

```text
// Disassembly of the translated from the host graphics layer.
```

## Source note 298, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L831)

```text
// May be empty if the host does not support disassembly.
```

## Source note 299, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L834)

```text
// In case disassembly depends on the GPU backend, for setting it
```

## Source note 300, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L835)

```text
// externally.
```

## Source note 301, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L840)

```text
// For dumping after translation. Dumps the shader's translated code, and,
```

## Source note 302, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L841)

```text
// if available, translated disassembly, to files in the given directory
```

## Source note 303, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L842)

```text
// based on ucode hash. Returns {binary path, disassembly path if written}.
```

## Source note 304, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L850)

```text
// If there was some failure during preparation on the implementation side.
```

## Source note 305, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L867)

```text
// ucode_source_endian specifies the endianness of the ucode_dwords argument -
```

## Source note 306, line 868

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L868)

```text
// inside the Shader, the ucode will be stored with the native byte order.
```

## Source note 307, line 873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L873)

```text
// Whether the shader is identified as a vertex or pixel shader.
```

## Source note 308, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L876)

```text
// Microcode dwords in host endianness.
```

## Source note 309, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L883)

```text
// ucode_disasm_buffer is temporary storage for disassembly (provided
```

## Source note 310, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L884)

```text
// externally so it won't need to be reallocated for every shader).
```

## Source note 311, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L887)

```text
// The following parameters, until the translation, are valid if ucode
```

## Source note 312, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L888)

```text
// information has been gathered.
```

## Source note 313, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L890)

```text
// Microcode disassembly in D3D format.
```

## Source note 314, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L893)

```text
// All vertex bindings used in the shader.
```

## Source note 315, line 896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L896)

```text
// All texture bindings used in the shader.
```

## Source note 316, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L899)

```text
// Bitmaps of all constant registers accessed by the shader.
```

## Source note 317, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L902)

```text
// Information about memory export state at each control flow instruction. May
```

## Source note 318, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L903)

```text
// be empty if there are no eM# writes.
```

## Source note 319, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L913)

```text
// c# registers used as the addend in MAD operations to eA.
```

## Source note 320, line 918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L918)

```text
// Labels that jumps (explicit or from loops) can be done to.
```

## Source note 321, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L921)

```text
// Exclusive upper bound of the indexes of paired control flow instructions
```

## Source note 322, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L922)

```text
// (each corresponds to 3 dwords).
```

## Source note 323, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L925)

```text
// Whether the shader contains subroutine calls (cond_call).
```

## Source note 324, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L927)

```text
// Components of registers 0-15, 4 bits per register, that may be written
```

## Source note 325, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L928)

```text
// after the label in the program and then reach it by jumping back or
```

## Source note 326, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L929)

```text
// returning from a subroutine. Zero for labels only jumped to forward.
```

## Source note 327, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L935)

```text
// Registers 0-15 used with absolute addressing as coordinates of texture
```

## Source note 328, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L936)

```text
// fetches that may snap to texel centers (see CanSnapToTexelCenter).
```

## Source note 329, line 939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L939)

```text
// Upper bound of temporary registers addressed statically by the shader -
```

## Source note 330, line 940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L940)

```text
// highest static register address + 1, or 0 if no registers referenced this
```

## Source note 331, line 941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L941)

```text
// way. SQ_PROGRAM_CNTL is not always reliable - some draws (like single point
```

## Source note 332, line 942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L942)

```text
// draws with oPos = 0001 that are done by Xbox 360's Direct3D 9 sometimes;
```

## Source note 333, line 943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L943)

```text
// can be reproduced by launching the intro mission in 4D5307E6 from the
```

## Source note 334, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L944)

```text
// campaign lobby) that aren't supposed to cover any pixels use an invalid
```

## Source note 335, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L945)

```text
// (zero) SQ_PROGRAM_CNTL, but with an outdated pixel shader loaded, in this
```

## Source note 336, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L946)

```text
// case SQ_PROGRAM_CNTL may contain a number smaller than actually needed by
```

## Source note 337, line 947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L947)

```text
// the pixel shader - SQ_PROGRAM_CNTL should be used to go above this count if
```

## Source note 338, line 948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L948)

```text
// uses_register_dynamic_addressing is true.
```

## Source note 339, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L951)

```text
// Whether the shader addresses temporary registers dynamically, thus
```

## Source note 340, line 952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L952)

```text
// SQ_PROGRAM_CNTL should determine the number of registers to use, not only
```

## Source note 341, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L953)

```text
// register_static_address_bound.
```

## Source note 342, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L956)

```text
// For building shader modification bits (and also for normalization of them),
```

## Source note 343, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L957)

```text
// returns the amount of temporary registers that need to be allocated
```

## Source note 344, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L958)

```text
// explicitly - if not using register dynamic addressing, the shader
```

## Source note 345, line 959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L959)

```text
// translator will use register_static_address_bound directly.
```

## Source note 346, line 967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L967)

```text
// True if the current shader has any `kill` instructions.
```

## Source note 347, line 970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L970)

```text
// True if the shader has any texture-related instructions (any fetch
```

## Source note 348, line 971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L971)

```text
// instructions other than vertex fetch) writing any non-constant components.
```

## Source note 349, line 976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L976)

```text
// Whether each interpolator is written on any execution path.
```

## Source note 350, line 979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L979)

```text
// Whether the system vertex shader exports are written on any execution path.
```

## Source note 351, line 984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L984)

```text
// Returns the mask of the interpolators the pixel shader potentially requires
```

## Source note 352, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L985)

```text
// from the vertex shader, and also the PsParamGen destination register, or
```

## Source note 353, line 986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L986)

```text
// UINT32_MAX if it's not needed.
```

## Source note 354, line 991

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L991)

```text
// True if the shader overrides the pixel depth.
```

## Source note 355, line 994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L994)

```text
// Whether the shader can have early depth and stencil writing enabled, unless
```

## Source note 356, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L995)

```text
// alpha test or alpha to coverage is enabled.
```

## Source note 357, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1000)

```text
// Whether each color render target is written to on any execution path.
```

## Source note 358, line 1006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1006)

```text
// Host translations with the specified modification bits. Not thread-safe
```

## Source note 359, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1007)

```text
// with respect to translation creation/destruction.
```

## Source note 360, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1017)

```text
// For shader storage loading, to remove a modification in case of translation
```

## Source note 361, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1018)

```text
// failure. Not thread-safe.
```

## Source note 362, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1021)

```text
// An externally managed identifier of the shader storage the microcode of the
```

## Source note 363, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1022)

```text
// shader was last written to, or was loaded from, to only write the shader
```

## Source note 364, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1023)

```text
// microcode to the storage once. UINT32_MAX by default.
```

## Source note 365, line 1027

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1027)

```text
// Dumps the shader's microcode binary and, if analyzed, disassembly, to files
```

## Source note 366, line 1028

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1028)

```text
// in the given directory based on ucode hash. Returns the name of the written
```

## Source note 367, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1029)

```text
// file. Can be called at any time, doesn't require the shader to be
```

## Source note 368, line 1030

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1030)

```text
// translated. Returns {binary path, disassembly path if written}.
```

## Source note 369, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1043)

```text
// Whether info needed before translating has been gathered already - may be
```

## Source note 370, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1044)

```text
// needed to determine which modifications are actually needed and make sense
```

## Source note 371, line 1045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1045)

```text
// (for instance, there may be draws not covering anything and not allocating
```

## Source note 372, line 1046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1046)

```text
// any pixel shader registers in SQ_PROGRAM_CNTL, but still using the pixel
```

## Source note 373, line 1047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1047)

```text
// shader from the previous draw - in this case, every shader that happens to
```

## Source note 374, line 1048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1048)

```text
// be before such draw will need to be translated again with a different
```

## Source note 375, line 1049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1049)

```text
// dynamically addressed register count, which may cause compilation of
```

## Source note 376, line 1050

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1050)

```text
// different random pipelines across many random frames, thus causing
```

## Source note 377, line 1051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1051)

```text
// stuttering - normally host pipeline states are deterministically only
```

## Source note 378, line 1052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1052)

```text
// compiled when a new material appears in the game, and having the order of
```

## Source note 379, line 1053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1053)

```text
// draws also matter in such unpredictable way would break this rule; limit
```

## Source note 380, line 1054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1054)

```text
// the effect to shaders with dynamic register addressing only, which are
```

## Source note 381, line 1055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1055)

```text
// extremely rare; however care should be taken regarding depth format-related
```

## Source note 382, line 1056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1056)

```text
// translation modifications in this case), also some info needed for drawing
```

## Source note 383, line 1057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1057)

```text
// is collected during the ucode analysis.
```

## Source note 384, line 1066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1066)

```text
// Per control flow instruction index.
```

## Source note 385, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1080)

```text
// Memory export eM write info for each control flow instruction, if there are
```

## Source note 386, line 1081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1081)

```text
// any eM writes in the shader.
```

## Source note 387, line 1083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1083)

```text
// Which memexport elements (eM#) are written for any memexport in the shader.
```

## Source note 388, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1085)

```text
// ControlFlowMemExportInfo::eM_potentially_written_before equivalent for the
```

## Source note 389, line 1086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1086)

```text
// end of the shader, for the last memory export (or exports if the end has
```

## Source note 390, line 1087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1087)

```text
// multiple predecessor chains exporting to memory).
```

## Source note 391, line 1091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/shader.h#L1091)

```text
// Modification bits -> translation.
```
