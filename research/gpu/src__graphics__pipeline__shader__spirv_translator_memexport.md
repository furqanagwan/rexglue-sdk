# Spirv translator memexport: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_translator_memexport.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L34)

```text
// Check if memory export is allowed in this guest shader invocation.
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L38)

```text
// For pixel shaders with resolution scaling, only allow memory export from
```

## Source note 3, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L39)

```text
// the center host pixel to avoid duplicate exports.
```

## Source note 4, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L44)

```text
// Check if we're at the center pixel (scale/2 for both X and Y).
```

## Source note 5, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L47)

```text
// Check X coordinate.
```

## Source note 6, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L66)

```text
// Check Y coordinate.
```

## Source note 7, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L85)

```text
// Combine with existing memexport_allowed condition.
```

## Source note 8, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L97)

```text
// If the pixel was killed (but the actual killing on the SPIR-V side has not
```

## Source note 9, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L98)

```text
// been performed yet because the device doesn't support demotion to helper
```

## Source note 10, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L99)

```text
// invocation that doesn't interfere with control flow), the current
```

## Source note 11, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L100)

```text
// invocation is not considered active anymore.
```

## Source note 12, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L109)

```text
// Check if the address with the correct sign and exponent was written, and
```

## Source note 13, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L110)

```text
// that the index doesn't overflow the mantissa bits. Z takes all 12 bits of
```

## Source note 14, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L111)

```text
// const_0x4b0 rather than the top 9, so the constants the shader accepts
```

## Source note 15, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L112)

```text
// match the ones draw_util::AddMemExportRanges derives ranges from.
```

## Source note 16, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L113)

```text
// all((eA_vector >> uvec4(30, 23, 20, 23)) == uvec4(0x1, 0x96, 0x4B0, 0x96))
```

## Source note 17, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L149)

```text
// Load the original eM.
```

## Source note 18, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L156)

```text
// Swap red and blue if needed.
```

## Source note 19, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L178)

```text
// Extract the numeric format.
```

## Source note 20, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L190)

```text
// Perform format packing.
```

## Source note 21, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L223)

```text
// The widths must be without holes (R, RG, RGB, RGBA), and expecting the
```

## Source note 22, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L224)

```text
// widths to add up to the size of the stored texel (8, 16 or 32 bits), as the
```

## Source note 23, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L225)

```text
// unused upper bits will contain junk from the sign extension of X if the
```

## Source note 24, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L226)

```text
// number is signed.
```

## Source note 25, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L234)

```text
// Only formats for which max + 0.5 can be represented exactly.
```

## Source note 26, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L242)

```text
// Extract the needed components.
```

## Source note 27, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L264)

```text
// Flush NaNs.
```

## Source note 28, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L267)

```text
// Convert to integers.
```

## Source note 29, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L271)

```text
// Signed.
```

## Source note 30, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L275)

```text
// Signed normalized.
```

## Source note 31, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L298)

```text
// All phi instructions must be in the beginning of the block.
```

## Source note 32, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L302)

```text
// Convert to signed integer, adding plus/minus 0.5 before truncating
```

## Source note 33, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L303)

```text
// according to the Direct3D format conversion rules.
```

## Source note 34, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L326)

```text
// Unsigned normalized.
```

## Source note 35, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L349)

```text
// All phi instructions must be in the beginning of the block.
```

## Source note 36, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L353)

```text
// Convert to unsigned integer, adding 0.5 before truncating according to
```

## Source note 37, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L354)

```text
// the Direct3D format conversion rules.
```

## Source note 38, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L369)

```text
// Pack into a 32-bit value, and pad to a 4-component vector for the phi.
```

## Source note 39, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L403)

```text
// Must be called at the end of the switch case segment for the correct phi
```

## Source note 40, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L404)

```text
// parent.
```

## Source note 41, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L412)

```text
// k_8, k_8_A, k_8_B
```

## Source note 42, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L419)

```text
// k_1_5_5_5
```

## Source note 43, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L423)

```text
// k_5_6_5
```

## Source note 44, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L427)

```text
// k_6_5_5
```

## Source note 45, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L431)

```text
// k_8_8_8_8, k_8_8_8_8_A, k_8_8_8_8_AS_16_16_16_16
```

## Source note 46, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L439)

```text
// k_2_10_10_10, k_2_10_10_10_AS_16_16_16_16
```

## Source note 47, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L445)

```text
// k_8_8
```

## Source note 48, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L449)

```text
// k_4_4_4_4
```

## Source note 49, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L453)

```text
// k_10_11_11, k_10_11_11_AS_16_16_16_16
```

## Source note 50, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L459)

```text
// k_11_11_10, k_11_11_10_AS_16_16_16_16
```

## Source note 51, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L465)

```text
// k_16
```

## Source note 52, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L469)

```text
// k_16_16
```

## Source note 53, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L473)

```text
// k_16_16_16_16
```

## Source note 54, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L476)

```text
// Flush NaNs.
```

## Source note 55, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L479)

```text
// Convert to integers.
```

## Source note 56, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L483)

```text
// Signed.
```

## Source note 57, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L487)

```text
// Signed normalized.
```

## Source note 58, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L503)

```text
// All phi instructions must be in the beginning of the block.
```

## Source note 59, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L508)

```text
// Convert to signed integer, adding plus/minus 0.5 before truncating
```

## Source note 60, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L509)

```text
// according to the Direct3D format conversion rules.
```

## Source note 61, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L527)

```text
// Unsigned.
```

## Source note 62, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L531)

```text
// Unsigned normalized.
```

## Source note 63, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L546)

```text
// All phi instructions must be in the beginning of the block.
```

## Source note 64, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L551)

```text
// Convert to unsigned integer, adding 0.5 before truncating according to
```

## Source note 65, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L552)

```text
// the Direct3D format conversion rules.
```

## Source note 66, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L567)

```text
// Pack into two 32-bit values, and pad to a 4-component vector for the phi.
```

## Source note 67, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L591)

```text
// Xbox 360 float16 uses extended range: exponent 31 is a large finite value,
```

## Source note 68, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L592)

```text
// not Inf/NaN. See PackFloat16x2ExtendedRange.
```

## Source note 69, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L594)

```text
// k_16_FLOAT
```

## Source note 70, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L614)

```text
// k_16_16_FLOAT
```

## Source note 71, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L634)

```text
// k_16_16_16_16_FLOAT
```

## Source note 72, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L659)

```text
// k_32_FLOAT
```

## Source note 73, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L670)

```text
// k_32_32_FLOAT
```

## Source note 74, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L681)

```text
// k_32_32_32_32_FLOAT
```

## Source note 75, line 694

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L694)

```text
// Select the result and the element size based on the format.
```

## Source note 76, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L695)

```text
// Phi must be the first instructions in a block.
```

## Source note 77, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L700)

```text
// Default case for an invalid format.
```

## Source note 78, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L714)

```text
// Default case for an invalid format (doesn't enter any element size
```

## Source note 79, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L715)

```text
// conditional, skipped).
```

## Source note 80, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L727)

```text
// Endian-swap.
```

## Source note 81, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L734)

```text
// Load the index of eM0 in the stream.
```

## Source note 82, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L740)

```text
// Check how many elements starting from eM0 are within the bounds of the
```

## Source note 83, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L741)

```text
// stream, and from the eM# that were written, exclude the out-of-bounds ones.
```

## Source note 84, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L742)

```text
// The index can't be negative, and the index and the count are limited to 23
```

## Source note 85, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L743)

```text
// bits, so it's safe to use 32-bit signed subtraction and clamping to get the
```

## Source note 86, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L744)

```text
// remaining eM# count.
```

## Source note 87, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L763)

```text
// Get the eM0 address in bytes.
```

## Source note 88, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L764)

```text
// Left-shift the stream base address by 2 to both convert it from dwords to
```

## Source note 89, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L765)

```text
// bytes and drop the upper bits.
```

## Source note 90, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L767)

```text
// Masked to physical - the guest may use a mirror window.
```

## Source note 91, line 779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L779)

```text
// Store based on the element size.
```

## Source note 92, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L802)

```text
// replace_shift = 8 * (element_address_bytes & 3)
```

## Source note 93, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L827)

```text
// replace_shift = 16 * (element_address_words & 1)
```

## Source note 94, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L899)

```text
// Close the conditionals for whether memory export is allowed in this
```

## Source note 95, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_memexport.cpp#L900)

```text
// invocation.
```
