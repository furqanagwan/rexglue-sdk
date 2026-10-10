# Spirv translator rb: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_translator_rb.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L29)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 2, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L30)

```text
// Assuming the value is already clamped to [0, 31.875].
```

## Source note 3, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L34)

```text
// Need the source as uint for bit operations.
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L43)

```text
// The denormal 7e3 case.
```

## Source note 5, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L44)

```text
// denormal_biased_f32 = (f32 & 0x7FFFFF) | 0x800000
```

## Source note 6, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L57)

```text
// denormal_biased_f32_shift_amount = min(125 - (f32 >> 23), 24)
```

## Source note 7, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L58)

```text
// Not allowing the shift to overflow as that's undefined in SPIR-V.
```

## Source note 8, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L74)

```text
// denormal_biased_f32 =
```

## Source note 9, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L75)

```text
//     ((f32 & 0x7FFFFF) | 0x800000) >> min(125 - (f32 >> 23), 24)
```

## Source note 10, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L79)

```text
// The normal 7e3 case.
```

## Source note 11, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L80)

```text
// Bias the exponent.
```

## Source note 12, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L81)

```text
// normal_biased_f32 = f32 - (124 << 23)
```

## Source note 13, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L85)

```text
// Select the needed conversion depending on whether the number is too small
```

## Source note 14, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L86)

```text
// to be represented as normalized 7e3.
```

## Source note 15, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L93)

```text
// Build the 7e3 number rounding to the nearest even.
```

## Source note 16, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L94)

```text
// ((biased_f32 + 0x7FFF + ((biased_f32 >> 16) & 1)) >> 16) & 0x3FF
```

## Source note 17, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L109)

```text
// Need the source as float for clamping.
```

## Source note 18, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L136)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 19, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L152)

```text
// The denormal nonzero 7e3 case.
```

## Source note 20, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L153)

```text
// denormal_mantissa_msb = findMSB(f10_mantissa)
```

## Source note 21, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L166)

```text
// denormal_f32_unbiased_exponent = 1 - (7 - findMSB(f10_mantissa))
```

## Source note 22, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L168)

```text
// denormal_f32_unbiased_exponent = findMSB(f10_mantissa) - 6
```

## Source note 23, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L171)

```text
// Normalize the mantissa.
```

## Source note 24, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L172)

```text
// denormal_f32_mantissa = f10_mantissa << (7 - findMSB(f10_mantissa))
```

## Source note 25, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L177)

```text
// If the 7e3 number is zero, make sure the float32 number is zero too.
```

## Source note 26, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L180)

```text
// Set the unbiased exponent to -124 for zero - 124 will be added later,
```

## Source note 27, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L181)

```text
// resulting in zero float32.
```

## Source note 28, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L188)

```text
// Select the needed conversion depending on whether the number is normal.
```

## Source note 29, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L197)

```text
// Bias the exponent and construct the build the float32 number.
```

## Source note 30, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L225)

```text
// CFloat24 from d3dref9.dll +
```

## Source note 31, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L226)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 32, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L227)

```text
// Assuming the value is already clamped to [0, 2) (in all places, the depth
```

## Source note 33, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L228)

```text
// is written with saturation).
```

## Source note 34, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L234)

```text
// Need the source as uint for bit operations.
```

## Source note 35, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L243)

```text
// The denormal 20e4 case.
```

## Source note 36, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L244)

```text
// denormal_biased_f32 = (f32 & 0x7FFFFF) | 0x800000
```

## Source note 37, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L257)

```text
// denormal_biased_f32_shift_amount = min(113 - (f32 >> 23), 24)
```

## Source note 38, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L258)

```text
// Not allowing the shift to overflow as that's undefined in SPIR-V.
```

## Source note 39, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L274)

```text
// denormal_biased_f32 =
```

## Source note 40, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L275)

```text
//     ((f32 & 0x7FFFFF) | 0x800000) >> min(113 - (f32 >> 23), 24)
```

## Source note 41, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L279)

```text
// The normal 20e4 case.
```

## Source note 42, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L280)

```text
// Bias the exponent.
```

## Source note 43, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L281)

```text
// normal_biased_f32 = f32 - (112 << 23)
```

## Source note 44, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L286)

```text
// Select the needed conversion depending on whether the number is too small
```

## Source note 45, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L287)

```text
// to be represented as normalized 20e4.
```

## Source note 46, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L294)

```text
// Build the 20e4 number rounding to the nearest even or towards zero.
```

## Source note 47, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L296)

```text
// biased_f32 += 3 + ((biased_f32 >> 3) & 1)
```

## Source note 48, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L310)

```text
// CFloat24 from d3dref9.dll +
```

## Source note 49, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L311)

```text
// https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexConvert.cpp
```

## Source note 50, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L329)

```text
// The denormal nonzero 20e4 case.
```

## Source note 51, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L330)

```text
// denormal_mantissa_msb = findMSB(f24_mantissa)
```

## Source note 52, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L343)

```text
// denormal_f32_unbiased_exponent = 1 - (20 - findMSB(f24_mantissa))
```

## Source note 53, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L345)

```text
// denormal_f32_unbiased_exponent = findMSB(f24_mantissa) - 19
```

## Source note 54, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L348)

```text
// Normalize the mantissa.
```

## Source note 55, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L349)

```text
// denormal_f32_mantissa = f24_mantissa << (20 - findMSB(f24_mantissa))
```

## Source note 56, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L354)

```text
// If the 20e4 number is zero, make sure the float32 number is zero too.
```

## Source note 57, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L357)

```text
// Set the unbiased exponent to -112 for zero - 112 will be added later,
```

## Source note 58, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L358)

```text
// resulting in zero float32.
```

## Source note 59, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L365)

```text
// Select the needed conversion depending on whether the number is normal.
```

## Source note 60, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L374)

```text
// Bias the exponent and construct the build the float32 number.
```

## Source note 61, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L401)

```text
// Baked into the FSI shader through the modification. Every loop bounded by
```

## Source note 62, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L402)

```text
// it below is on the FSI path.
```

## Source note 63, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L406)

```text
// Load the sample mask, which may be modified later by killing from
```

## Source note 64, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L407)

```text
// different sources.
```

## Source note 65, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L424)

```text
// Kill the pixel once the guest control flow and derivatives are not
```

## Source note 66, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L425)

```text
// needed anymore.
```

## Source note 67, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L432)

```text
// OpKill terminates the block.
```

## Source note 68, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L446)

```text
// Skip the alpha test and alpha to coverage if the render target 0 is not
```

## Source note 69, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L447)

```text
// written to dynamically. This check is used by both FSI and FBO paths.
```

## Source note 70, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L469)

```text
// More likely to write to the render target 0 than not.
```

## Source note 71, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L480)

```text
// Alpha test.
```

## Source note 72, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L485)

```text
// Check if the comparison function is not "always" - that should pass even
```

## Source note 73, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L486)

```text
// for NaN likely, unlike "less, equal or greater".
```

## Source note 74, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L505)

```text
// The comparison function is not "always" - perform the alpha test.
```

## Source note 75, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L506)

```text
// Handle "not equal" specially (specifically as "not equal" so it's true
```

## Source note 76, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L507)

```text
// for NaN, not "less or greater" which is false for NaN).
```

## Source note 77, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L515)

```text
// "Not equal" function.
```

## Source note 78, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L522)

```text
// Function other than "not equal".
```

## Source note 79, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L547)

```text
// Discard the pixel if the alpha test has failed.
```

## Source note 80, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L567)

```text
// OpKill terminates the block.
```

## Source note 81, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L575)

```text
// Alpha to coverage.
```

## Source note 82, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L579)

```text
// Close the render target 0 written check (used by both FSI and FBO).
```

## Source note 83, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L584)

```text
// The tests might have modified the sample mask via
```

## Source note 84, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L585)

```text
// fsi_sample_mask_in_rt_0_alpha_tests.
```

## Source note 85, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L593)

```text
// Demote path: the alpha test demotes instead of touching the mask, but
```

## Source note 86, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L594)

```text
// alpha to coverage still modified main_fsi_sample_mask_ inside the
```

## Source note 87, line 595

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L595)

```text
// written branch. Merge in the pre-branch mask
```

## Source note 88, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L596)

```text
// (fsi_sample_mask_in_rt_0_alpha_tests) on the not-written edge so the
```

## Source note 89, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L597)

```text
// value dominates the merge. Otherwise it is undefined there (invalid
```

## Source note 90, line 598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L598)

```text
// SPIR-V dominance and garbage coverage).
```

## Source note 91, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L622)

```text
// Don't do anything related to writing to the EDRAM if the pixel was
```

## Source note 92, line 623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L623)

```text
// killed.
```

## Source note 93, line 631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L631)

```text
// Check the condition before the OpSelectionMerge, which must be the
```

## Source note 94, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L632)

```text
// penultimate instruction in a block.
```

## Source note 95, line 646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L646)

```text
// Perform late depth / stencil writes for samples not discarded.
```

## Source note 96, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L658)

```text
// First SSBO structure element.
```

## Source note 97, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L669)

```text
// Only take the remaining coverage bits, not the late depth / stencil
```

## Source note 98, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L670)

```text
// write bits, into account in the check whether anything needs to be
```

## Source note 99, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L671)

```text
// done for the color targets.
```

## Source note 100, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L680)

```text
// Begin the critical section on the outermost control flow level so it's
```

## Source note 101, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L681)

```text
// entered exactly once on any control flow path as required by the SPIR-V
```

## Source note 102, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L682)

```text
// extension specification.
```

## Source note 103, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L684)

```text
// Do the depth / stencil test.
```

## Source note 104, line 685

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L685)

```text
// The sample mask might have been made narrower than the initially loaded
```

## Source note 105, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L686)

```text
// mask by various conditions that discard the whole pixel, as well as by
```

## Source note 106, line 687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L687)

```text
// alpha to coverage.
```

## Source note 107, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L690)

```text
// Only bits 0:3 of main_fsi_sample_mask_ are written by the late
```

## Source note 108, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L691)

```text
// depth / stencil test.
```

## Source note 109, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L700)

```text
// Skip all color operations if the pixel has failed the tests entirely.
```

## Source note 110, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L721)

```text
// Apply resolution scaling to EDRAM size.
```

## Source note 111, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L740)

```text
// Apply the exponent bias after the alpha test and alpha to coverage
```

## Source note 112, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L741)

```text
// because they need the unbiased alpha from the shader.
```

## Source note 113, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L753)

```text
// Write the color to the target in the EDRAM only it was written on the
```

## Source note 114, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L754)

```text
// shader's execution path, according to the Direct3D 9 rules that games
```

## Source note 115, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L755)

```text
// rely on.
```

## Source note 116, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L761)

```text
// More likely to write to the render target than not.
```

## Source note 117, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L765)

```text
// For accessing uint2 arrays of per-render-target data which are passed
```

## Source note 118, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L766)

```text
// as uint4 arrays due to std140 array element alignment.
```

## Source note 119, line 773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L773)

```text
// Load the mask of the bits of the destination color that should be
```

## Source note 120, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L774)

```text
// preserved (in 32-bit halves), which are 0, 0 if the color is fully
```

## Source note 121, line 775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L775)

```text
// overwritten, or UINT32_MAX, UINT32_MAX if writing to the target is
```

## Source note 122, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L776)

```text
// disabled completely.
```

## Source note 123, line 792

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L792)

```text
// Check if writing to the render target is not disabled completely.
```

## Source note 124, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L803)

```text
// Load the information about the render target.
```

## Source note 125, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L805)

```text
// Baked into the modification, so the pack and unpack trees collapse
```

## Source note 126, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L806)

```text
// to this format's path alone.
```

## Source note 127, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L816)

```text
// EDRAM addresses are wrapped on the Xenos (modulo the EDRAM size).
```

## Source note 128, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L831)

```text
// The overwrite path is emitted on its own when nothing blends, and
```

## Source note 129, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L832)

```text
// as the else branch otherwise.
```

## Source note 130, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L835)

```text
// Non-blending paths.
```

## Source note 131, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L837)

```text
// Pack the new color for all samples.
```

## Source note 132, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L840)

```text
// Check if need to load the original contents.
```

## Source note 133, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L850)

```text
// Loading and masking path.
```

## Source note 134, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L863)

```text
// First SSBO structure element.
```

## Source note 135, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L901)

```text
// Fully overwriting path.
```

## Source note 136, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L908)

```text
// First SSBO structure element.
```

## Source note 137, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L934)

```text
// Only this branch reads the blending parameters.
```

## Source note 138, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L944)

```text
// Check if blending (the blending is not 1 * source + 0 *
```

## Source note 139, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L945)

```text
// destination).
```

## Source note 140, line 952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L952)

```text
// Blending path.
```

## Source note 141, line 954

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L954)

```text
// Get various parameters used in blending.
```

## Source note 142, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1033)

```text
// Blend and mask each sample.
```

## Source note 143, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1041)

```text
// First SSBO structure element.
```

## Source note 144, line 1055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1055)

```text
// Load the destination color.
```

## Source note 145, line 1069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1069)

```text
// Blend the components.
```

## Source note 146, line 1081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1081)

```text
// Pack and store the result.
```

## Source note 147, line 1082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1082)

```text
// Bypass the `getNumTypeConstituents(typeId) ==
```

## Source note 148, line 1083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1083)

```text
// (int)constituents.size()` assertion in
```

## Source note 149, line 1084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1084)

```text
// createCompositeConstruct, OpCompositeConstruct can construct
```

## Source note 150, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1085)

```text
// vectors not only from scalars, but also from other vectors.
```

## Source note 151, line 1128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1128)

```text
// Convert to gamma space - this is incorrect, since it must be done
```

## Source note 152, line 1129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1129)

```text
// after blending on the Xbox 360, but this is just one of many blending
```

## Source note 153, line 1130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1130)

```text
// issues in the host render target path.
```

## Source note 154, line 1169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1169)

```text
// FBO path: Copy from Function-scoped variables to Output variables.
```

## Source note 155, line 1170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1170)

```text
// This is done at the end after alpha test/coverage so we can read the
```

## Source note 156, line 1171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1171)

```text
// color values during those operations.
```

## Source note 157, line 1187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1187)

```text
// For RT0, apply pre-multiply by source blend factor if needed for
```

## Source note 158, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1188)

```text
// MIN/MAX blend emulation (since Vulkan/D3D12 ignores blend factors
```

## Source note 159, line 1189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1189)

```text
// for MIN/MAX but Xbox 360 applies them).
```

## Source note 160, line 1192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1192)

```text
// Helper to extract RGB (xyz) from a float4.
```

## Source note 161, line 1202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1202)

```text
// Get blend factor values.
```

## Source note 162, line 1239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1239)

```text
// Load blend constant from system constants.
```

## Source note 163, line 1289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1289)

```text
// Unsupported factors - return 1 (no multiply).
```

## Source note 164, line 1294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1294)

```text
// Apply RGB pre-multiply.
```

## Source note 165, line 1299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1299)

```text
// Reconstruct float4 with new RGB and original alpha.
```

## Source note 166, line 1309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1309)

```text
// Apply alpha pre-multiply.
```

## Source note 167, line 1314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1314)

```text
// Replace alpha in color (extract RGB, reconstruct with new alpha).
```

## Source note 168, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1329)

```text
// Copies the staged depth to the FBO gl_FragDepth output.
```

## Source note 169, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1330)

```text
// No-op for FSI and when no host depth output was declared.
```

## Source note 170, line 1354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1354)

```text
// FSI manages its own depth via the EDRAM buffer - this hook is FBO-only.
```

## Source note 171, line 1355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1355)

```text
// Likewise, if no Output FragDepth was declared, there is nothing to write.
```

## Source note 172, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1364)

```text
// Source depth from guest oDepth, or from raster depth for float24 conversion
```

## Source note 173, line 1365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1365)

```text
// and the host RT decal path.
```

## Source note 174, line 1431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1431)

```text
// Legacy path: shader writes oDepth, but the modification is not in float24
```

## Source note 175, line 1432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1432)

```text
// mode (the host buffer may still be float24 if depth_float24_convert_in_
```

## Source note 176, line 1433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1433)

```text
// pixel_shader is off - check dynamically via the system flag).
```

## Source note 177, line 1447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1447)

```text
// Float24 mode: statically known float24 host buffer; perform the conversion.
```

## Source note 178, line 1451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1451)

```text
// Mantissa bit-truncation, then guest 0...1 -> host 0...0.5.
```

## Source note 179, line 1453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1453)

```text
// Representable as float24 (exponent >= -34): bit pattern >= 0x2E800000.
```

## Source note 180, line 1459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1459)

```text
// Biased exponent: 113+ at exp -14+; 93 at exp -34.
```

## Source note 181, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1463)

```text
// trunc_bits = max(116 - exponent, 3), in signed - drops 3 mantissa bits
```

## Source note 182, line 1464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1464)

```text
// at exp -14+ and 23 at exp -34. Must be signed: exponent > 116 (i.e.
```

## Source note 183, line 1465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1465)

```text
// values larger than ~2^-11) makes 116 - exponent negative; an unsigned
```

## Source note 184, line 1466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1466)

```text
// underflow would feed OpBitFieldInsert a Count > 32 (undefined).
```

## Source note 185, line 1484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1484)

```text
// Not representable - zero.
```

## Source note 186, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1489)

```text
// kFloat24Rounding: round-trip through 20e4 (round to nearest even), with
```

## Source note 187, line 1490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1490)

```text
// the 0...0.5 host remap baked in via remap_to_0_to_0_5 on Depth20e4To32.
```

## Source note 188, line 1505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1505)

```text
// On the Xbox 360, 2x MSAA doubles the storage height, 4x MSAA doubles the
```

## Source note 189, line 1506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1506)

```text
// storage width.
```

## Source note 190, line 1507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1507)

```text
// The guest 4x sample numbering is the Vulkan one, bit 0 horizontal and
```

## Source note 191, line 1508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1508)

```text
// bit 1 vertical, so 4x coverage passes through as is. Guest 2x puts
```

## Source note 192, line 1509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1509)

```text
// sample 0 at the top while Vulkan counts from the bottom, so the guest
```

## Source note 193, line 1510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1510)

```text
// samples map to Vulkan 1, 0 with native 2x MSAA and to 0, 3 with 2x
```

## Source note 194, line 1511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1511)

```text
// emulated as 4x.
```

## Source note 195, line 1525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1525)

```text
// 1x has the one sample, and at 4x the numbering matches - pass the
```

## Source note 196, line 1526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1526)

```text
// coverage through.
```

## Source note 197, line 1533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1533)

```text
// 1 and 0 to 0 and 1.
```

## Source note 198, line 1539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1539)

```text
// 0 and 3 to 0 and 1 - guest sample 1 comes from host sample 3
```

## Source note 199, line 1549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1549)

```text
// Convert the floating-point pixel coordinates to the canonical sample 0
```

## Source note 200, line 1550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1550)

```text
// coordinates, meaning the coordinates of the pixel's sample 0 in the
```

## Source note 201, line 1551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1551)

```text
// single sampled view of the EDRAM data. The layout is described in
```

## Source note 202, line 1552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1552)

```text
// XeEdramOffsetBytes (see edram.xesli). What matters here is that the offsets
```

## Source note 203, line 1553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1553)

```text
// of the other samples from sample 0 are constant, FSI_AddSampleOffset
```

## Source note 204, line 1554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1554)

```text
// adds them, and that with resolution scaling the rearrangement happens at
```

## Source note 205, line 1555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1555)

```text
// guest pixel granularity.
```

## Source note 206, line 1582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1582)

```text
// (((x or y) >> 1) << 2) | ((x or y) & 1), the sample 0 part of the
```

## Source note 207, line 1583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1583)

```text
// rearrangement shared by the 4x u and v and the 2x v.
```

## Source note 208, line 1591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1591)

```text
// u0 is ((x >> 1) << 2) | (x & 1) at 4x, x & ~2 at 2x and plain x at 1x.
```

## Source note 209, line 1601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1601)

```text
// v0 is ((y >> 1) << 2) | (y & 1) at 2x and 4x, with x bit 1 in bit 1 at
```

## Source note 210, line 1602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1602)

```text
// 2x only. At 1x it's plain y.
```

## Source note 211, line 1614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1614)

```text
// Restore the host pixel granularity.
```

## Source note 212, line 1626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1626)

```text
// Get 40 x 16 x resolution scale 32bpp half-tile or 40x16 64bpp tile index.
```

## Source note 213, line 1627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1627)

```text
// Working with 40x16-sample portions for 64bpp and for swapping for depth -
```

## Source note 214, line 1628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1628)

```text
// dividing by 40, not by 80.
```

## Source note 215, line 1629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1629)

```text
// Apply resolution scaling to tile dimensions.
```

## Source note 216, line 1644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1644)

```text
// Convert the Y sample 0 position within the half-tile or tile to the dword
```

## Source note 217, line 1645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1645)

```text
// offset of the row within a 80x16 32bpp tile or a 40x16 64bpp half-tile.
```

## Source note 218, line 1650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1650)

```text
// Multiply the Y tile position by the surface tile pitch in dwords at 32bpp
```

## Source note 219, line 1651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1651)

```text
// to get the address of the origin of the row of tiles within a 32bpp surface
```

## Source note 220, line 1652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1652)

```text
// in dwords (later it needs to be multiplied by 2 for 64bpp).
```

## Source note 221, line 1666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1666)

```text
// Get the dword offset of the sample 0 in the first half-tile in the tile
```

## Source note 222, line 1667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1667)

```text
// within a 32bpp surface.
```

## Source note 223, line 1680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1680)

```text
// Get whether the sample is in the second half-tile in a 32bpp surface.
```

## Source note 224, line 1686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1686)

```text
// Get the offset of the sample 0 within a depth / stencil surface, with
```

## Source note 225, line 1687

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1687)

```text
// samples 40...79 in the first half-tile, 0...39 in the second (flipped as
```

## Source note 226, line 1688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1688)

```text
// opposed to color). Then add the EDRAM base for depth / stencil, and wrap
```

## Source note 227, line 1689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1689)

```text
// addressing.
```

## Source note 228, line 1707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1707)

```text
// Get the offset of the sample 0 within a 32bpp surface, with samples
```

## Source note 229, line 1708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1708)

```text
// 0...39 in the first half-tile, 40...79 in the second.
```

## Source note 230, line 1714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1714)

```text
// Get the offset of the sample 0 within a 64bpp surface.
```

## Source note 231, line 1735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1735)

```text
// In the canonical layout, the horizontal (or the only 2x) sample bit is
```

## Source note 232, line 1736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1736)

```text
// +2 sample columns from sample 0, 2 dwords wide each for 64bpp, and the
```

## Source note 233, line 1737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1737)

```text
// vertical sample bit is +2 sample rows, all at the guest scale.
```

## Source note 234, line 1758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1758)

```text
// UINT32_MAX means no ZPD segment is currently open for this draw.
```

## Source note 235, line 1777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1777)

```text
// One slot holds every ZPD counter.
```

## Source note 236, line 1781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1781)

```text
// For VIZ, an atomic store of 1 replaces the atomic add since the survey's
```

## Source note 237, line 1782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1782)

```text
// ID consumer only cares about zero vs non-zero.
```

## Source note 238, line 1811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1811)

```text
// Only bits 0:3 are surviving coverage. 4:7 are deferred depth/stencil and
```

## Source note 239, line 1812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1812)

```text
// don't contribute to the counter.
```

## Source note 240, line 1841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1841)

```text
// Demoted fragments shouldn't be counted here.
```

## Source note 241, line 1855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1855)

```text
// Total is the slot's first counter.
```

## Source note 242, line 1883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1883)

```text
// Check if depth or stencil testing is needed.
```

## Source note 243, line 1895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1895)

```text
// Guest oDepth replaces the depth value FSI tests. It's not the raster depth
```

## Source note 244, line 1896

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1896)

```text
// plane, so don't take FragCoord for it.
```

## Source note 245, line 1904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1904)

```text
// Load the depth in the center of the pixel and calculate the derivatives
```

## Source note 246, line 1905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1905)

```text
// of the depth outside non-uniform control flow.
```

## Source note 247, line 1918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1918)

```text
// Skip everything if potentially discarded all the samples previously in the
```

## Source note 248, line 1919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1919)

```text
// shader.
```

## Source note 249, line 1936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L1936)

```text
// Load values involved in depth and stencil testing.
```

## Source note 250, line 2064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2064)

```text
// When the guest shader replaces depth, don't apply offset from the original
```

## Source note 251, line 2065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2065)

```text
// FragCoord.z plane. That would mix two different depth sources.
```

## Source note 252, line 2069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2069)

```text
// Get the maximum depth slope for the polygon offset.
```

## Source note 253, line 2070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2070)

```text
// https://docs.microsoft.com/en-us/windows/desktop/direct3d9/depth-bias
```

## Source note 254, line 2078

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2078)

```text
// Calculate the polygon offset.
```

## Source note 255, line 2083

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2083)

```text
// Apply the post-clip and post-viewport polygon offset to the fragment's
```

## Source note 256, line 2084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2084)

```text
// depth. Not clamping yet as this is at the center, which is not
```

## Source note 257, line 2085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2085)

```text
// necessarily covered and not necessarily inside the bounds - derivatives
```

## Source note 258, line 2086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2086)

```text
// scaled by sample locations will be added to this value, and it must be
```

## Source note 259, line 2087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2087)

```text
// linear.
```

## Source note 260, line 2092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2092)

```text
// Perform depth and stencil testing for each covered sample.
```

## Source note 261, line 2106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2106)

```text
// Load the original depth and stencil for the sample.
```

## Source note 262, line 2109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2109)

```text
// First SSBO structure element.
```

## Source note 263, line 2118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2118)

```text
// Calculate the new depth at the sample.
```

## Source note 264, line 2119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2119)

```text
// interpolateAtSample(gl_FragCoord) is not valid in GLSL because
```

## Source note 265, line 2120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2120)

```text
// gl_FragCoord is not an interpolator, calculating the depths at the
```

## Source note 266, line 2121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2121)

```text
// samples manually.
```

## Source note 267, line 2125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2125)

```text
// The center sample without MSAA, otherwise the top-left one - native
```

## Source note 268, line 2126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2126)

```text
// 2x sample 1 in Vulkan, 0 for 2x as 4x and for 4x.
```

## Source note 269, line 2140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2140)

```text
// For guest 2x this is the bottom sample, Vulkan 0 for native 2x and
```

## Source note 270, line 2141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2141)

```text
// Vulkan 3 for 2x as 4x.
```

## Source note 271, line 2142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2142)

```text
// For guest 4x this is the top-right sample since the horizontal
```

## Source note 272, line 2143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2143)

```text
// sample bit is bit 0, Vulkan 1.
```

## Source note 273, line 2154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2154)

```text
// Guest samples 2 and 3, bottom-left and bottom-right with the
```

## Source note 274, line 2155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2155)

```text
// vertical sample bit being bit 1, map to Vulkan samples 2 and 3.
```

## Source note 275, line 2175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2175)

```text
// Convert the new depth to 24-bit.
```

## Source note 276, line 2181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2181)

```text
// Round to the nearest even integer. This seems to be the correct
```

## Source note 277, line 2182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2182)

```text
// conversion, adding +0.5 and rounding towards zero results in red instead
```

## Source note 278, line 2183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2183)

```text
// of black in the 4D5307E6 clear shader.
```

## Source note 279, line 2191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2191)

```text
// Merge between the two formats.
```

## Source note 280, line 2195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2195)

```text
// Perform the depth test.
```

## Source note 281, line 2212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2212)

```text
// Perform the stencil test if enabled.
```

## Source note 282, line 2218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2218)

```text
// The read mask has zeros in the upper bits, applying it to the combined
```

## Source note 283, line 2219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2219)

```text
// stencil and depth will remove the depth part.
```

## Source note 284, line 2261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2261)

```text
// Make keep the default.
```

## Source note 285, line 2287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2287)

```text
// Keep - will use the old stencil in the phi.
```

## Source note 286, line 2290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2290)

```text
// Zero - will use the zero constant in the phi.
```

## Source note 287, line 2293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2293)

```text
// Replace - will use the stencil reference in the phi.
```

## Source note 288, line 2296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2296)

```text
// Increment and clamp.
```

## Source note 289, line 2307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2307)

```text
// Decrement and clamp.
```

## Source note 290, line 2317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2317)

```text
// Invert.
```

## Source note 291, line 2322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2322)

```text
// Increment and wrap.
```

## Source note 292, line 2323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2323)

```text
// The upper bits containing the old depth have no effect on the behavior.
```

## Source note 293, line 2328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2328)

```text
// Decrement and wrap.
```

## Source note 294, line 2329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2329)

```text
// The upper bits containing the old depth have no effect on the behavior.
```

## Source note 295, line 2334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2334)

```text
// Select the new stencil (with undefined data in bits starting from 8)
```

## Source note 296, line 2335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2335)

```text
// based on the stencil operation.
```

## Source note 297, line 2357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2357)

```text
// Merge the old depth / stencil (old depth kept from the old depth /
```

## Source note 298, line 2358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2358)

```text
// stencil so the separate old depth register is not needed anymore after
```

## Source note 299, line 2359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2359)

```text
// the depth test) and the new stencil based on the write mask.
```

## Source note 300, line 2368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2368)

```text
// Choose the result based on whether the stencil test was done.
```

## Source note 301, line 2369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2369)

```text
// All phi operations must be the first in the block.
```

## Source note 302, line 2375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2375)

```text
// Check whether the tests have passed, and exclude the bit from the
```

## Source note 303, line 2376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2376)

```text
// coverage if not.
```

## Source note 304, line 2382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2382)

```text
// Remember the failures for the ZFail and StencilFail counters. Stencil
```

## Source note 305, line 2383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2383)

```text
// failure takes precedence over depth failure.
```

## Source note 306, line 2403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2403)

```text
// Combine the new depth and the new stencil taking into account whether the
```

## Source note 307, line 2404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2404)

```text
// new depth should be written.
```

## Source note 308, line 2413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2413)

```text
// Write (or defer writing if the test is early, but may discard samples
```

## Source note 309, line 2414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2414)

```text
// later still) the new depth and stencil if they're different.
```

## Source note 310, line 2430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2430)

```text
// Always need to write late in this shader, as it may do something like
```

## Source note 311, line 2431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2431)

```text
// explicitly killing pixels.
```

## Source note 312, line 2463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2463)

```text
// Close the conditionals for whether depth / stencil testing is needed.
```

## Source note 313, line 2517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2517)

```text
// The Xbox 360 float16 has no NaN, map it to 0. Also keeps the overflow
```

## Source note 314, line 2518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2518)

```text
// detection below from misreading a NaN's exponent 31 as a finite extended
```

## Source note 315, line 2519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2519)

```text
// value, and FClamp's NaN result is undefined.
```

## Source note 316, line 2523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2523)

```text
// Standard conversion handles +-0..65504; larger magnitudes overflow to Inf
```

## Source note 317, line 2524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2524)

```text
// (exponent field 0x7C00). Re-encode the overflowed lanes using the extended
```

## Source note 318, line 2525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2525)

```text
// range: halve into the standard range, convert (exponent <= 30), then bump
```

## Source note 319, line 2526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2526)

```text
// the exponent by 1 into the exponent 31 slot the Xbox 360 treats as finite.
```

## Source note 320, line 2556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2556)

```text
// halved_packed has exponent <= 30 in both lanes, so adding 0x0400 per lane
```

## Source note 321, line 2557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2557)

```text
// bumps the exponent without ever carrying across lanes.
```

## Source note 322, line 2574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2574)

```text
// Inverse of PackFloat16x2ExtendedRange. Exponent 31 lanes are large finite
```

## Source note 323, line 2575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2575)

```text
// values, not Inf/NaN - decrement their exponent by 1 into the standard
```

## Source note 324, line 2576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2576)

```text
// range, unpack, then double to compensate.
```

## Source note 325, line 2591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2591)

```text
// Decrement the exponent only in overflowed lanes (0x0400 in the low lane,
```

## Source note 326, line 2592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2592)

```text
// 0x04000000 in the high one) so the subtraction never borrows across lanes.
```

## Source note 327, line 2670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2670)

```text
// Bypass the `getNumTypeConstituents(typeId) == (int)constituents.size()`
```

## Source note 328, line 2671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2671)

```text
// assertion in createCompositeConstruct, OpCompositeConstruct can
```

## Source note 329, line 2672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2672)

```text
// construct vectors not only from scalars, but also from other vectors.
```

## Source note 330, line 2728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2728)

```text
// RGB.
```

## Source note 331, line 2734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2734)

```text
// Alpha.
```

## Source note 332, line 2745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2745)

```text
// Pack.
```

## Source note 333, line 2769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2769)

```text
// NaN to 0, not to -32.
```

## Source note 334, line 2794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2794)

```text
// The high dword only exists on the 64bpp formats.
```

## Source note 335, line 2807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2807)

```text
// NaN is flushed to 0 inside PackFloat16x2ExtendedRange. The high dword
```

## Source note 336, line 2808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2808)

```text
// only exists on the 64bpp formats.
```

## Source note 337, line 2818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2818)

```text
// k_32_FLOAT, k_32_32_FLOAT and anything undefined.
```

## Source note 338, line 2821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2821)

```text
// The high dword only exists on the 64bpp formats.
```

## Source note 339, line 2942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2942)

```text
// k_32_FLOAT, k_32_32_FLOAT and anything undefined.
```

## Source note 340, line 2977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2977)

```text
// Flush NaN to 0 even for signed (NMax would flush it to the minimum
```

## Source note 341, line 2978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2978)

```text
// value).
```

## Source note 342, line 2997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2997)

```text
// If the factor is zero, don't use it in the multiplication at all, so that
```

## Source note 343, line 2998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2998)

```text
// infinity and NaN are not potentially involved in the multiplication.
```

## Source note 344, line 2999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L2999)

```text
// Calculate the condition before the selection merge, which must be the
```

## Source note 345, line 3000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3000)

```text
// penultimate instruction in the block.
```

## Source note 346, line 3006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3006)

```text
// Non-zero factor case.
```

## Source note 347, line 3033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3033)

```text
// Make one the default factor.
```

## Source note 348, line 3074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3074)

```text
// The result is the value itself.
```

## Source note 349, line 3077

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3077)

```text
// k[OneMinus]Src/Dest/ConstantColor/Alpha
```

## Source note 350, line 3096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3096)

```text
// kSrc/Dst/ConstantColor
```

## Source note 351, line 3104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3104)

```text
// kOneMinusSrc/Dst/ConstantColor
```

## Source note 352, line 3114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3114)

```text
// kSrc/Dst/ConstantAlpha
```

## Source note 353, line 3122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3122)

```text
// kOneMinusSrc/Dst/ConstantAlpha
```

## Source note 354, line 3146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3146)

```text
// Select the term for the non-zero factor.
```

## Source note 355, line 3170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3170)

```text
// Make the result zero if the factor is zero.
```

## Source note 356, line 3179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3179)

```text
// If the factor is zero, don't use it in the multiplication at all, so that
```

## Source note 357, line 3180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3180)

```text
// infinity and NaN are not potentially involved in the multiplication.
```

## Source note 358, line 3181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3181)

```text
// Calculate the condition before the selection merge, which must be the
```

## Source note 359, line 3182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3182)

```text
// penultimate instruction in the block.
```

## Source note 360, line 3188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3188)

```text
// Non-zero factor case.
```

## Source note 361, line 3207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3207)

```text
// Make one the default factor.
```

## Source note 362, line 3246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3246)

```text
// The result is the value itself.
```

## Source note 363, line 3249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3249)

```text
// k[OneMinus]Src/Dest/ConstantColor/Alpha
```

## Source note 364, line 3260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3260)

```text
// kSrc/Dst/ConstantColor/Alpha
```

## Source note 365, line 3268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3268)

```text
// kOneMinusSrc/Dst/ConstantColor/Alpha
```

## Source note 366, line 3292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3292)

```text
// Select the term for the non-zero factor.
```

## Source note 367, line 3312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3312)

```text
// Make the result zero if the factor is zero.
```

## Source note 368, line 3328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3328)

```text
// Apply blend factors to source and destination first.
```

## Source note 369, line 3329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3329)

```text
// Note: Unlike Vulkan's VK_BLEND_OP_MIN/MAX which ignore blend factors,
```

## Source note 370, line 3330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3330)

```text
// the Xbox 360 applies blend factors before the min/max operation.
```

## Source note 371, line 3331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3331)

```text
// So we apply factors unconditionally, then switch on the equation.
```

## Source note 372, line 3351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3351)

```text
// Now switch on the blend equation to combine the factored terms.
```

## Source note 373, line 3364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3364)

```text
// Make addition the default.
```

## Source note 374, line 3382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3382)

```text
// Addition case (default).
```

## Source note 375, line 3388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3388)

```text
// Subtraction case.
```

## Source note 376, line 3394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3394)

```text
// Reverse subtraction case.
```

## Source note 377, line 3400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3400)

```text
// Min case.
```

## Source note 378, line 3406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3406)

```text
// Max case.
```

## Source note 379, line 3412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3412)

```text
// Merge and create phi for the result.
```

## Source note 380, line 3435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3435)

```text
// Based on D3D12's CompletePixelShader_AlphaToMaskSample.
```

## Source note 381, line 3436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3436)

```text
// Calculates threshold and tests alpha against it.
```

## Source note 382, line 3437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3437)

```text
// threshold = threshold_base + threshold_offset * (-threshold_offset_scale)
```

## Source note 383, line 3447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3447)

```text
// Test: alpha >= threshold
```

## Source note 384, line 3448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3448)

```text
// Using OpFOrdGreaterThanEqual for proper NaN handling (NaN results in false)
```

## Source note 385, line 3453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3453)

```text
// FSI mode: Clear both coverage and deferred depth bits for failed samples.
```

## Source note 386, line 3454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3454)

```text
// This matches the D3D12 ROV implementation which uses ~(0b00010001 <<
```

## Source note 387, line 3455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3455)

```text
// sample_index). The test must affect not only the coverage bits (0-3), but
```

## Source note 388, line 3456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3456)

```text
// also the deferred depth/stencil write bits (4-7) since if a sample is
```

## Source note 389, line 3457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3457)

```text
// discarded by alpha to coverage, it must not be written at all.
```

## Source note 390, line 3459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3459)

```text
// Optimized: Pre-compute the clear mask constant
```

## Source note 391, line 3460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3460)

```text
// clear_mask = ~(0b00010001 << sample_index)
```

## Source note 392, line 3463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3463)

```text
// If test passes, keep all bits; if test fails, apply clear_mask
```

## Source note 393, line 3464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3464)

```text
// This avoids doing OpNot on every call by pre-computing the clear mask
```

## Source note 394, line 3469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3469)

```text
// Apply mask: coverage &= mask_to_apply
```

## Source note 395, line 3473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3473)

```text
// Non-FSI mode: Start with zero coverage, set bits for passed samples.
```

## Source note 396, line 3478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3478)

```text
// If sample passes, set its bit in coverage mask.
```

## Source note 397, line 3479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3479)

```text
// Create a mask with the sample bit set: (1 << sample_index)
```

## Source note 398, line 3482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3482)

```text
// coverage = select(sample_passes, coverage | sample_bit, coverage)
```

## Source note 399, line 3491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3491)

```text
// Based on D3D12's CompletePixelShader_AlphaToMask.
```

## Source note 400, line 3493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3493)

```text
// FSI mode implementation
```

## Source note 401, line 3495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3495)

```text
// Check if alpha to coverage can be done at all in this shader.
```

## Source note 402, line 3500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3500)

```text
// Check if we have the required variables
```

## Source note 403, line 3502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3502)

```text
// Sample mask not available
```

## Source note 404, line 3505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3505)

```text
// Fragment coordinates not available
```

## Source note 405, line 3508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3508)

```text
// RT0 not available
```

## Source note 406, line 3511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3511)

```text
// Load alpha_to_mask constant and check if enabled
```

## Source note 407, line 3522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3522)

```text
// Save the current block for PHI
```

## Source note 408, line 3526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3526)

```text
// Create blocks for control flow
```

## Source note 409, line 3530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3530)

```text
// Set up the conditional branch
```

## Source note 410, line 3534

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3534)

```text
// Alpha to coverage enabled path
```

## Source note 411, line 3537

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3537)

```text
// Start with the current sample mask (which includes both coverage bits 0-3
```

## Source note 412, line 3538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3538)

```text
// and deferred depth bits 4-7). Alpha to coverage will clear both the
```

## Source note 413, line 3539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3539)

```text
// coverage and deferred depth bits for samples that fail the alpha test.
```

## Source note 414, line 3540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3540)

```text
// This matches the D3D12 ROV implementation.
```

## Source note 415, line 3542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3542)

```text
// Extract dithering threshold offset from fragment position
```

## Source note 416, line 3551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3551)

```text
// Calculate dithering offset: (Y & 1) | ((X & 1) << 1)
```

## Source note 417, line 3561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3561)

```text
// Extract 2-bit offset from alpha_to_mask constant
```

## Source note 418, line 3571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3571)

```text
// Load alpha from RT0.w (oC0.w) once for all samples (optimization)
```

## Source note 419, line 3574

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3574)

```text
// W component
```

## Source note 420, line 3580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3580)

```text
// Only this shader's own samples and dithering thresholds are emitted.
```

## Source note 421, line 3598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3598)

```text
// Branch to main merge
```

## Source note 422, line 3602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3602)

```text
// Continue from merge block with PHI for the final mask
```

## Source note 423, line 3606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3606)

```text
// Coming from the enabled path
```

## Source note 424, line 3608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3608)

```text
// Coming from the disabled path
```

## Source note 425, line 3612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3612)

```text
// For FBO mode, ensure gl_SampleMask output was created
```

## Source note 426, line 3613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3613)

```text
// For depth-only shaders, we don't create gl_SampleMask, so skip
```

## Source note 427, line 3618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3618)

```text
// Initialize OMask to full coverage (in case alpha to mask is disabled).
```

## Source note 428, line 3619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3619)

```text
// gl_SampleMask is an array, so we need to access element [0].
```

## Source note 429, line 3624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3624)

```text
// All bits set
```

## Source note 430, line 3627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3627)

```text
// Load alpha_to_mask constant and check if enabled.
```

## Source note 431, line 3647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3647)

```text
// Extract dithering threshold offset from fragment position.
```

## Source note 432, line 3648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3648)

```text
// offset_index = (Y & 1) | ((X & 1) << 1)
```

## Source note 433, line 3649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3649)

```text
// offset = (alpha_to_mask >> (offset_index * 2)) & 0b11
```

## Source note 434, line 3652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3652)

```text
// Extract X and Y as floats first, then convert to uint
```

## Source note 435, line 3659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3659)

```text
// Y & 1
```

## Source note 436, line 3663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3663)

```text
// (X & 1) << 1
```

## Source note 437, line 3669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3669)

```text
// offset_index = y_bit | x_bit_shifted
```

## Source note 438, line 3672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3672)

```text
// bit_position = offset_index * 2
```

## Source note 439, line 3676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3676)

```text
// Extract 2-bit offset: (alpha_to_mask >> bit_position) & 0b11
```

## Source note 440, line 3682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3682)

```text
// Convert offset to float (0.0, 1.0, 2.0, 3.0)
```

## Source note 441, line 3686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3686)

```text
// Load alpha from RT0.w (oC0.w) once for all samples (optimization)
```

## Source note 442, line 3688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3688)

```text
// W component
```

## Source note 443, line 3694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3694)

```text
// Load MSAA sample count to determine which mode to use.
```

## Source note 444, line 3695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3695)

```text
// 0 = 1x, 1 = 2x, 2 = 4x
```

## Source note 445, line 3698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3698)

```text
// Check if MSAA is enabled (msaa_samples != 0)
```

## Source note 446, line 3710

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3710)

```text
// MSAA enabled - check if 4x or 2x
```

## Source note 447, line 3713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3713)

```text
// msaa_samples: 1 = 2x, 2 = 4x
```

## Source note 448, line 3724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3724)

```text
// 4x MSAA
```

## Source note 449, line 3733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3733)

```text
// 2x MSAA
```

## Source note 450, line 3736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3736)

```text
// FSI mode uses guest sample indices (0 and 1).
```

## Source note 451, line 3737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3737)

```text
// FBO mode sample mapping depends on whether native 2x MSAA is supported:
```

## Source note 452, line 3738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3738)

```text
// - Native 2x: host samples 1, 0 (reversed from guest order)
```

## Source note 453, line 3739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3739)

```text
// - 2x as 4x: host samples 0, 3
```

## Source note 454, line 3741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3741)

```text
// FSI: Use guest indices 0, 1.
```

## Source note 455, line 3745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3745)

```text
// FBO: Account for native 2x vs 2x-as-4x sample mapping. This epilogue only
```

## Source note 456, line 3746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3746)

```text
// runs when there is a color attachment (sample mask output), so the native
```

## Source note 457, line 3747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3747)

```text
// 2x decision must use the with-attachments capability, matching the host
```

## Source note 458, line 3748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3748)

```text
// pipeline's native-vs-emulated 2x choice.
```

## Source note 459, line 3750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3750)

```text
// Native 2x: D3D10.1+ standard - top is 1, bottom is 0.
```

## Source note 460, line 3754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3754)

```text
// 2x as 4x: Use samples 0 and 3.
```

## Source note 461, line 3762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3762)

```text
// Merge coverage from 4x and 2x MSAA paths using PHI.
```

## Source note 462, line 3772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3772)

```text
// MSAA disabled - single sample
```

## Source note 463, line 3779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3779)

```text
// Merge coverage from MSAA enabled and disabled paths using PHI.
```

## Source note 464, line 3788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3788)

```text
// Write coverage to gl_SampleMask and discard if zero (FBO mode only).
```

## Source note 465, line 3790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3790)

```text
// Write to gl_SampleMask[0].
```

## Source note 466, line 3798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3798)

```text
// Discard fragment if coverage is zero.
```

## Source note 467, line 3804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3804)

```text
// OpKill terminates the block, so makeEndIf with false to not branch.
```

## Source note 468, line 3812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3812)

```text
// Samples dropped by alpha-to-coverage never reach the depth/stencil test,
```

## Source note 469, line 3813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_rb.cpp#L3813)

```text
// so they shouldn't be included in the ZPD Total counter either.
```
