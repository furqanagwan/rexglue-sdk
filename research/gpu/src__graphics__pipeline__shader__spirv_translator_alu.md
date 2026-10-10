# Spirv translator alu: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_translator_alu.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L44)

```text
// Implements round-to-nearest with ties rounding away from zero.
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L45)

```text
// Special values (INF, NaN, signed zeros) are preserved.
```

## Source note 3, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L46)

```text
// Denormals may be flushed to zero, closer approximating Xbox 360
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L47)

```text
// hardware behavior.
```

## Source note 5, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L52)

```text
// Convert float to uint bits
```

## Source note 6, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L55)

```text
// Calculate the number of bits to truncate
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L58)

```text
// Create a mask that keeps the sign, exponent, and desired mantissa bits
```

## Source note 8, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L62)

```text
// Truncate to get the base value
```

## Source note 9, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L66)

```text
// Extract the discarded low bits to determine if we should round up
```

## Source note 10, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L70)

```text
// Round up if discarded bits >= round_bit (round half up)
```

## Source note 11, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L74)

```text
// Add one ULP at the truncated precision level
```

## Source note 12, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L78)

```text
// Check if rounding caused exponent overflow (finite -> infinity)
```

## Source note 13, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L79)

```text
// This can happen when rounding up near FLT_MAX
```

## Source note 14, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L85)

```text
// If original was finite (exp != 0xFF) but rounded became inf (exp == 0xFF),
```

## Source note 15, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L86)

```text
// saturate by not rounding up
```

## Source note 16, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L94)

```text
// If rounding would cause overflow, use truncated value instead
```

## Source note 17, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L98)

```text
// Select between truncated and rounded-up value
```

## Source note 18, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L102)

```text
// Inf and NaN pass through, rounding them can produce a signed zero or an
```

## Source note 19, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L103)

```text
// infinity.
```

## Source note 20, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L107)

```text
// Convert back to float
```

## Source note 21, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L115)

```text
// Perform outstanding memory exports before the invocation becomes inactive
```

## Source note 22, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L116)

```text
// and storage writes are disabled.
```

## Source note 23, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L134)

```text
// Don't even disassemble or update predication.
```

## Source note 24, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L141)

```text
// Floating-point arithmetic operations (addition, subtraction, negation,
```

## Source note 25, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L142)

```text
// multiplication, division, modulo - see isArithmeticOperation in
```

## Source note 26, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L143)

```text
// propagateNoContraction of glslang; though for some reason it's not applied
```

## Source note 27, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L144)

```text
// to SPIR-V OpDot, at least in the February 16, 2020 version installed on
```

## Source note 28, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L145)

```text
// http://shader-playground.timjones.io/) must have the NoContraction
```

## Source note 29, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L146)

```text
// decoration to prevent reordering to make sure floating-point calculations
```

## Source note 30, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L147)

```text
// are optimized predictably and exactly the same in different shaders to
```

## Source note 31, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L148)

```text
// allow for multipass rendering (in addition to the Invariant decoration on
```

## Source note 32, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L149)

```text
// outputs).
```

## Source note 33, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L151)

```text
// Whether the instruction has changed the predicate, and it needs to be
```

## Source note 34, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L152)

```text
// checked again later.
```

## Source note 35, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L164)

```text
// Special retain_prev case - load ps only if needed and don't store the
```

## Source note 36, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L165)

```text
// same value back to ps.
```

## Source note 37, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L195)

```text
// Load operand storage without swizzle and sign modifiers.
```

## Source note 38, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L196)

```text
// A small shortcut, operands of cube are the same, but swizzled.
```

## Source note 39, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L211)

```text
// In case the paired scalar instruction (if processed first) terminates the
```

## Source note 40, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L212)

```text
// block.
```

## Source note 41, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L215)

```text
// Lookup table for variants of instructions with similar structure.
```

## Source note 42, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L232)

```text
// kDp4
```

## Source note 43, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L233)

```text
// kDp3
```

## Source note 44, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L234)

```text
// kDp2Add
```

## Source note 45, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L236)

```text
// kMax4
```

## Source note 46, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L271)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 47, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L276)

```text
// Extract the different components, if not all are different.
```

## Source note 48, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L305)

```text
// Check if the different components in any of the operands are zero,
```

## Source note 49, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L306)

```text
// even if the other is NaN - if min(|a|, |b|) is 0.
```

## Source note 50, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L316)

```text
// Replace with +0.
```

## Source note 51, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L320)

```text
// Insert the different components back to the result.
```

## Source note 52, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L348)

```text
// Not replacing true `0 + term` with conditional selection of the term
```

## Source note 53, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L349)

```text
// because +0 + -0 should result in +0, not -0.
```

## Source note 54, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L367)

```text
// a0 = (int)clamp(floor(src0.w + 0.5), -256.0, 255.0)
```

## Source note 55, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L389)

```text
// maxa returning nothing - can't load src1.
```

## Source note 56, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L392)

```text
// max is commonly used as mov.
```

## Source note 57, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L399)

```text
// operand_0 and operand_1 have different lengths though if src0.w is
```

## Source note 58, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L400)

```text
// forced without W being in the write mask for maxa purposes -
```

## Source note 59, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L401)

```text
// shuffle/extract the needed part if src0.w is only needed for setting
```

## Source note 60, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L402)

```text
// a0.
```

## Source note 61, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L403)

```text
// This is only needed for cases without mixed identical and different
```

## Source note 62, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L404)

```text
// components - the mixed case uses CompositeExtract, which works fine.
```

## Source note 63, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L406)

```text
// Need all but the last (W) element of operand_0 as a vector.
```

## Source note 64, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L415)

```text
// Need the non-W component as scalar.
```

## Source note 65, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L422)

```text
// All components are identical - mov (with the correct length in case
```

## Source note 66, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L423)

```text
// of maxa). Don't access operand_1 at all in this case (operand_0 is
```

## Source note 67, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L424)

```text
// already accessed for W in case of maxa).
```

## Source note 68, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L431)

```text
// Shader Model 3 NaN behavior (a op b ? a : b, not SPIR-V FMax/FMin which
```

## Source note 69, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L432)

```text
// are undefined for NaN or NMax/NMin which return the non-NaN operand).
```

## Source note 70, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L435)

```text
// All components are different - max/min of the scalars or the entire
```

## Source note 71, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L436)

```text
// vectors (with the correct length in case of maxa).
```

## Source note 72, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L445)

```text
// Mixed identical and different components.
```

## Source note 73, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L450)

```text
// Composite extraction of operand_0[i] works fine even it's maxa with
```

## Source note 74, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L451)

```text
// src0.w forced without W being in the write mask - src0.w would be the
```

## Source note 75, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L452)

```text
// last, so all indices before it are still valid. Don't extract twice
```

## Source note 76, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L453)

```text
// if already extracted though.
```

## Source note 77, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L515)

```text
// Not using OpDot for predictable optimization (especially addition
```

## Source note 78, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L516)

```text
// order) and NoContraction (which, for some reason, isn't placed on dot
```

## Source note 79, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L517)

```text
// in glslang as of the February 16, 2020 version).
```

## Source note 80, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L543)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 81, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L563)

```text
// operands[0] is .z_xy.
```

## Source note 82, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L564)

```text
// Result is T coordinate, S coordinate, 2 * major axis, face ID.
```

## Source note 83, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L565)

```text
// Skipping the second component of the operand, so 120, not 230.
```

## Source note 84, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L568)

```text
// Remapped from ZXY (Z_XY without the skipped component) to XYZ.
```

## Source note 85, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L598)

```text
// Check if the major axis is Z (abs(z) >= abs(x) && abs(z) >= abs(y)).
```

## Source note 86, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L607)

```text
// The major axis is Z.
```

## Source note 87, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L608)

```text
// tc = -y
```

## Source note 88, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L610)

```text
// ma/2 = z
```

## Source note 89, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L616)

```text
// sc = z < 0.0 ? -x : x
```

## Source note 90, line 621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L621)

```text
// id = z < 0.0 ? 5.0 : 4.0
```

## Source note 91, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L632)

```text
// The major axis is not Z - create an inner conditional to check if the
```

## Source note 92, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L633)

```text
// major axis is Y (abs(y) >= abs(x)).
```

## Source note 93, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L639)

```text
// The major axis is Y.
```

## Source note 94, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L640)

```text
// sc = x
```

## Source note 95, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L642)

```text
// ma/2 = y
```

## Source note 96, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L648)

```text
// tc = y < 0.0 ? -z : z
```

## Source note 97, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L651)

```text
// id = y < 0.0 ? 3.0 : 2.0
```

## Source note 98, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L660)

```text
// The major axis is X.
```

## Source note 99, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L661)

```text
// tc = -y
```

## Source note 100, line 663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L663)

```text
// ma/2 = x
```

## Source note 101, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L669)

```text
// sc = x < 0.0 ? z : -z
```

## Source note 102, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L674)

```text
// id = x < 0.0 ? 1.0 : 0.0
```

## Source note 103, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L682)

```text
// The major axis is Y or X - choose the options of the result from Y
```

## Source note 104, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L683)

```text
// and X.
```

## Source note 105, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L693)

```text
// Choose the result options from Z and YX cases.
```

## Source note 106, line 703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L703)

```text
// Multiply the major axis by 2.
```

## Source note 107, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L709)

```text
// Only one component - not composite.
```

## Source note 108, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L717)

```text
// Find max of all different components of the first operand.
```

## Source note 109, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L746)

```text
// X is only needed for the result, W is needed for the predicate.
```

## Source note 110, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L759)

```text
// p0 = src0.w == 0.0 && src1.w op 0.0
```

## Source note 111, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L770)

```text
// result = (src0.x == 0.0 && src1.x op 0.0) ? 0.0 : src0.x + 1.0
```

## Source note 112, line 772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L772)

```text
// result = ((src0.x == 0.0 && src1.x op 0.0) ? -1.0 : src0.x) + 1.0
```

## Source note 113, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L799)

```text
// Kills write their destination: 1.0 when the kill condition is true,
```

## Source note 114, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L800)

```text
// 0.0 otherwise (ucode.h). KillPixel demotes, so execution continues.
```

## Source note 115, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L808)

```text
// result.yz is needed: [0] = y, [1] = z.
```

## Source note 116, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L809)

```text
// resuly.y is needed: scalar = y.
```

## Source note 117, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L810)

```text
// resuly.z is needed: scalar = z.
```

## Source note 118, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L815)

```text
// result.yw is needed: [0] = y, [1] = w.
```

## Source note 119, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L816)

```text
// resuly.y is needed: scalar = y.
```

## Source note 120, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L817)

```text
// resuly.w is needed: scalar = w.
```

## Source note 121, line 821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L821)

```text
// y = src0.y * src1.y
```

## Source note 122, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L834)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 123, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L842)

```text
// x = 1.0
```

## Source note 124, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L846)

```text
// y = src0.y * src1.y
```

## Source note 125, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L850)

```text
// z = src0.z
```

## Source note 126, line 857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L857)

```text
// w = src1.w
```

## Source note 127, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L865)

```text
// Only one component - not composite.
```

## Source note 128, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L888)

```text
// In case the paired vector instruction (if processed first) terminates the
```

## Source note 129, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L889)

```text
// block.
```

## Source note 130, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L892)

```text
// Lookup table for variants of instructions with similar structure.
```

## Source note 131, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L898)

```text
// kMulsPrev2
```

## Source note 132, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L936)

```text
// kMulsc0
```

## Source note 133, line 937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L937)

```text
// kMulsc1
```

## Source note 134, line 938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L938)

```text
// kAddsc0
```

## Source note 135, line 939

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L939)

```text
// kAddsc1
```

## Source note 136, line 940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L940)

```text
// kSubsc0
```

## Source note 137, line 941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L941)

```text
// kSubsc1
```

## Source note 138, line 967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L967)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 139, line 977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L977)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 140, line 983

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L983)

```text
// Check if need to select the src0.a * ps case.
```

## Source note 141, line 984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L984)

```text
// Selection merge must be the penultimate instruction in the block, check
```

## Source note 142, line 985

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L985)

```text
// the condition before it.
```

## Source note 143, line 987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L987)

```text
// ps != -FLT_MAX.
```

## Source note 144, line 991

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L991)

```text
// isfinite(ps), or |ps| <= FLT_MAX, or -|ps| >= -FLT_MAX, since -FLT_MAX
```

## Source note 145, line 992

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L992)

```text
// is already loaded to an SGPR, this is also false if it's NaN.
```

## Source note 146, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1001)

```text
// isfinite(src0.b), or -|src0.b| >= -FLT_MAX for the same reason.
```

## Source note 147, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1015)

```text
// src0.b > 0 (need !(src0.b <= 0), but src0.b has already been checked
```

## Source note 148, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1016)

```text
// for NaN).
```

## Source note 149, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1023)

```text
// Multiplication case.
```

## Source note 150, line 1029

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1029)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 151, line 1034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1034)

```text
// Merge - choose between the product and -FLT_MAX.
```

## Source note 152, line 1046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1046)

```text
// Scalar maxas/maxasf clamp a0 to [0, 255] (non-negative), unlike the
```

## Source note 153, line 1047

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1047)

```text
// vector maxa which allows [-256, 255].
```

## Source note 154, line 1048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1048)

```text
// maxas: a0 = (int)clamp(floor(src0.a + 0.5), 0.0, 255.0)
```

## Source note 155, line 1049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1049)

```text
// maxasf: a0 = (int)clamp(floor(src0.a), 0.0, 255.0)
```

## Source note 156, line 1068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1068)

```text
// max is commonly used as mov.
```

## Source note 157, line 1071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1071)

```text
// Shader Model 3 NaN behavior (a op b ? a : b, not SPIR-V FMax/FMin which
```

## Source note 158, line 1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1072)

```text
// are undefined for NaN or NMax/NMin which return the non-NaN operand).
```

## Source note 159, line 1156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1156)

```text
// Can't create -0.0f with makeFloatConstant due to float comparison
```

## Source note 160, line 1157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1157)

```text
// internally, cast to bit pattern.
```

## Source note 161, line 1194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1194)

```text
// Can't create -0.0f with makeFloatConstant due to float comparison
```

## Source note 162, line 1195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1195)

```text
// internally, cast to bit pattern.
```

## Source note 163, line 1263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1263)

```text
// Kills write ps: 1.0 when the kill condition is true, 0.0 otherwise
```

## Source note 164, line 1264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1264)

```text
// (ucode.h). KillPixel demotes, so execution continues.
```

## Source note 165, line 1279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1279)

```text
// Fma isn't guaranteed to be fused (spirv_to_dxil splits 32-bit Fma
```

## Source note 166, line 1280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1280)

```text
// into a multiply and an add), so recover the product error with a
```

## Source note 167, line 1281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1281)

```text
// Veltkamp split and Dekker error sum instead.
```

## Source note 168, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1311)

```text
// Opposite signs mean the product rounded away from zero.
```

## Source note 169, line 1321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1321)

```text
// Shader Model 3: +0 or denormal * anything = +-0.
```

## Source note 170, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1339)

```text
// Special case in ProcessAluInstruction - loading ps only if writing to
```

## Source note 171, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_alu.cpp#L1340)

```text
// anywhere.
```
