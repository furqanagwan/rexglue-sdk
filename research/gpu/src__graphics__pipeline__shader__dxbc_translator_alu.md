# Dxbc translator alu: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/dxbc_translator_alu.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L27)

```text
// Perform outstanding memory exports before the invocation becomes inactive
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L28)

```text
// and UAV writes are disabled.
```

## Source note 3, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L30)

```text
// Discard the pixel, but continue execution if other lanes in the quad need
```

## Source note 4, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L31)

```text
// this lane for derivatives. The driver may also perform early exiting
```

## Source note 5, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L32)

```text
// internally if all lanes are discarded if deemed beneficial.
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L35)

```text
// Even though discarding disables all subsequent UAV/ROV writes, also skip
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L36)

```text
// as much of the Render Backend emulation logic as possible by setting the
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L37)

```text
// coverage and the mask of the written render targets to zero.
```

## Source note 9, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L55)

```text
// Load operands.
```

## Source note 10, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L56)

```text
// A small shortcut, operands of cube are the same, but swizzled.
```

## Source note 11, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L68)

```text
// .zzxy - don't need duplicated Z.
```

## Source note 12, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L80)

```text
// Don't return without PopSystemTemp(operand_temps) from now on!
```

## Source note 13, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L89)

```text
// Not using DXBC mad to prevent fused multiply-add (mul followed by add
```

## Source note 14, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L90)

```text
// may be optimized into non-fused mad by the driver in the identical
```

## Source note 15, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L91)

```text
// operands case also).
```

## Source note 16, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L97)

```text
// Shader Model 3: +-0 or denormal * anything = +0.
```

## Source note 17, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L101)

```text
// min isn't required to flush denormals, eq is.
```

## Source note 18, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L104)

```text
// Not replacing true `0 + term` with movc of the term because +0 + -0
```

## Source note 19, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L105)

```text
// should result in +0, not -0.
```

## Source note 20, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L109)

```text
// Release is_zero_temp.
```

## Source note 21, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L119)

```text
// max is commonly used as mov.
```

## Source note 22, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L125)

```text
// Shader Model 3 NaN behavior (a op b ? a : b, not fmax/fmin).
```

## Source note 23, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L198)

```text
// Shader Model 3: +-0 or denormal * anything = +0 (also not replacing
```

## Source note 24, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L199)

```text
// true `0 + term` with movc of the term because +0 + -0 should result
```

## Source note 25, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L200)

```text
// in +0, not -0).
```

## Source note 26, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L211)

```text
// Not using DXBC dp# to avoid fused multiply-add, PC GPUs are scalar
```

## Source note 27, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L212)

```text
// as of 2020 anyway, and not using mad for the same reason (mul
```

## Source note 28, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L213)

```text
// followed by add may be optimized into non-fused mad by the driver
```

## Source note 29, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L214)

```text
// in the identical operands case also).
```

## Source note 30, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L228)

```text
// operands[0] is .z_xy.
```

## Source note 31, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L229)

```text
// Result is T coordinate, S coordinate, 2 * major axis, face ID.
```

## Source note 32, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L234)

```text
// result.xy = bool2(abs(z) >= abs(x), abs(z) >= abs(y))
```

## Source note 33, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L237)

```text
// result.x = abs(z) >= abs(x) && abs(z) >= abs(y)
```

## Source note 34, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L247)

```text
// Z is the major axis.
```

## Source note 35, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L248)

```text
// z < 0 needed for SC and ID, but the last to use is ID.
```

## Source note 36, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L271)

```text
// result.x = abs(y) >= abs(x)
```

## Source note 37, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L275)

```text
// Y is the major axis.
```

## Source note 38, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L276)

```text
// y < 0 needed for TC and ID, but the last to use is ID.
```

## Source note 39, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L299)

```text
// X is the major axis.
```

## Source note 40, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L300)

```text
// x < 0 needed for SC and ID, but the last to use is ID.
```

## Source note 41, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L328)

```text
// Find max of all different components of the first operand.
```

## Source note 42, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L360)

```text
// result.xy = src0.xw == 0.0 (x only if needed).
```

## Source note 43, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L363)

```text
// result.zw = src1.xw == 0.0 (z only if needed).
```

## Source note 44, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L366)

```text
// p0 = src0.w == 0.0 && src1.w == 0.0
```

## Source note 45, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L371)

```text
// result = (src0.x == 0.0 && src1.x == 0.0) ? 0.0 : src0.x + 1.0
```

## Source note 46, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L375)

```text
// If the condition is true, 1 will be added to make it 0.
```

## Source note 47, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L386)

```text
// result.xy = src0.xw == 0.0 (x only if needed).
```

## Source note 48, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L389)

```text
// result.zw = src1.xw != 0.0 (z only if needed).
```

## Source note 49, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L392)

```text
// p0 = src0.w == 0.0 && src1.w != 0.0
```

## Source note 50, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L397)

```text
// result = (src0.x == 0.0 && src1.x != 0.0) ? 0.0 : src0.x + 1.0
```

## Source note 51, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L401)

```text
// If the condition is true, 1 will be added to make it 0.
```

## Source note 52, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L412)

```text
// result.xy = src0.xw == 0.0 (x only if needed).
```

## Source note 53, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L415)

```text
// result.zw = src1.xw > 0.0 (z only if needed).
```

## Source note 54, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L418)

```text
// p0 = src0.w == 0.0 && src1.w > 0.0
```

## Source note 55, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L423)

```text
// result = (src0.x == 0.0 && src1.x > 0.0) ? 0.0 : src0.x + 1.0
```

## Source note 56, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L427)

```text
// If the condition is true, 1 will be added to make it 0.
```

## Source note 57, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L438)

```text
// result.xy = src0.xw == 0.0 (x only if needed).
```

## Source note 58, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L441)

```text
// result.zw = src1.xw >= 0.0 (z only if needed).
```

## Source note 59, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L444)

```text
// p0 = src0.w == 0.0 && src1.w >= 0.0
```

## Source note 60, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L449)

```text
// result = (src0.x == 0.0 && src1.x >= 0.0) ? 0.0 : src0.x + 1.0
```

## Source note 61, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L453)

```text
// If the condition is true, 1 will be added to make it 0.
```

## Source note 62, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L531)

```text
// Shader Model 3: +-0 or denormal * anything = +0.
```

## Source note 63, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L535)

```text
// min isn't required to flush denormals, eq is.
```

## Source note 64, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L568)

```text
// Shader Model 3 NaN behavior (a >= b ? a : b, not fmax).
```

## Source note 65, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L593)

```text
// Round to nearest, with halfway values away from zero. The actual midpoint
```

## Source note 66, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L594)

```text
// behavior isn't known, this is the one 4E4D07D1 needs. Signed zero stays
```

## Source note 67, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L595)

```text
// signed. Denormals still follow the host float controls.
```

## Source note 68, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L604)

```text
// x keeps the original, y is truncated, z is rounded, and w is scratch.
```

## Source note 69, line 619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L619)

```text
// Don't let this rounding turn a finite host result into infinity.
```

## Source note 70, line 620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L620)

```text
// Keep the truncated value when it would.
```

## Source note 71, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L629)

```text
// Keep Inf and NaN exactly as the host instruction gave them. This only
```

## Source note 72, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L630)

```text
// reduces finite results and shouldn't make a nonfinite value look finite.
```

## Source note 73, line 665

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L665)

```text
// Load operands.
```

## Source note 74, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L675)

```text
// Don't return without PopSystemTemp(operand_temps) from now on!
```

## Source note 75, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L692)

```text
// Shader Model 3: +-0 or denormal * anything = +0.
```

## Source note 76, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L695)

```text
// min isn't required to flush denormals, eq is.
```

## Source note 77, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L700)

```text
// Release is_zero_temp.
```

## Source note 78, line 708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L708)

```text
// Check if need to select the src0.a * ps case.
```

## Source note 79, line 709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L709)

```text
// ps != -FLT_MAX.
```

## Source note 80, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L711)

```text
// isfinite(ps), or |ps| <= FLT_MAX, or -|ps| >= -FLT_MAX, since
```

## Source note 81, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L712)

```text
// -FLT_MAX is already loaded to an SGPR, this is also false if it's
```

## Source note 82, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L713)

```text
// NaN.
```

## Source note 83, line 717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L717)

```text
// isfinite(src0.b).
```

## Source note 84, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L721)

```text
// src0.b > 0 (need !(src0.b <= 0), but src0.b has already been checked
```

## Source note 85, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L722)

```text
// for NaN).
```

## Source note 86, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L728)

```text
// Shader Model 3: +-0 or denormal * anything = +0.
```

## Source note 87, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L730)

```text
// min isn't required to flush denormals, eq is.
```

## Source note 88, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L740)

```text
// Release test_temp.
```

## Source note 89, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L746)

```text
// max is commonly used as mov.
```

## Source note 90, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L750)

```text
// Shader Model 3 NaN behavior (a op b ? a : b, not fmax/fmin).
```

## Source note 91, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L798)

```text
// Release is_neg_infinity_temp.
```

## Source note 92, line 812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L812)

```text
// If +-Infinity (0x7F800000 or 0xFF800000), add -1 (0xFFFFFFFF) to turn
```

## Source note 93, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L813)

```text
// into +-FLT_MAX (0x7F7FFFFF or 0xFF7FFFFF).
```

## Source note 94, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L815)

```text
// Release is_infinity_temp.
```

## Source note 95, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L825)

```text
// Keep the sign bit if infinity.
```

## Source note 96, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L830)

```text
// Release is_not_infinity_temp.
```

## Source note 97, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L860)

```text
// Shader Model 3 NaN behavior (a >= b ? a : b, not fmax).
```

## Source note 98, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L899)

```text
// Calculate ps as if src0.a != 1.0 (the false predicate value case).
```

## Source note 99, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L902)

```text
// Set the predicate to src0.a == 1.0, and, if it's true, zero ps.
```

## Source note 100, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L922)

```text
// Just copying src0.a to ps (since it's set to 0 if it's 0) could work,
```

## Source note 101, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L923)

```text
// but flush denormals and zero sign just for safety.
```

## Source note 102, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L964)

```text
// DXBC mad isn't guaranteed to stay fused, so recover the product
```

## Source note 103, line 965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L965)

```text
// error with a Veltkamp split and Dekker error sum instead.
```

## Source note 104, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L968)

```text
// x/y: high/low part of a, z/w: high/low part of b.
```

## Source note 105, line 983

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L983)

```text
// x = error accumulator, y = scratch.
```

## Source note 106, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1000)

```text
// Opposite signs mean the product rounded away from zero.
```

## Source note 107, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1001)

```text
// Move it one representable float back toward zero.
```

## Source note 108, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1012)

```text
// Shader Model 3: +-0 or denormal * anything = +0.
```

## Source note 109, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1015)

```text
// min isn't required to flush denormals, eq is.
```

## Source note 110, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1020)

```text
// Release is_zero_temp.
```

## Source note 111, line 1052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1052)

```text
// Don't even disassemble or update predication.
```

## Source note 112, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1062)

```text
// Whether the instruction has changed the predicate, and it needs to be
```

## Source note 113, line 1063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_alu.cpp#L1063)

```text
// checked again later.
```
