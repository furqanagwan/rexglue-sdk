# Spirv translator fetch: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_translator_fetch.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L30)

```text
// The implementation picks which pixels of the quad a coarse derivative uses.
```

## Source note 2, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L55)

```text
// If this is vfetch_full, the address may still be needed for vfetch_mini -
```

## Source note 3, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L56)

```text
// don't exit before calculating the address.
```

## Source note 4, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L58)

```text
// Nothing to load - just constant 0/1 writes, or the swizzle includes only
```

## Source note 5, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L59)

```text
// components that don't exist in the format (writing zero instead of them).
```

## Source note 6, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L60)

```text
// Unpacking assumes at least some word is needed.
```

## Source note 7, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L70)

```text
// Load the second fetch constant word up front - it holds the endianness
```

## Source note 8, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L71)

```text
// (bits 0:1) for the swap below and the buffer size in words (bits 2:25) used
```

## Source note 9, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L72)

```text
// for bound checking here.
```

## Source note 10, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L74)

```text
// The only element of the fetch constant buffer.
```

## Source note 11, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L76)

```text
// Vector index.
```

## Source note 12, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L78)

```text
// Component index.
```

## Source note 13, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L86)

```text
// Exclusive end of the fetch buffer in dwords (base + size). Words at or past
```

## Source note 14, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L87)

```text
// it read as 0, like the hardware clamping out-of-bounds lanes.
```

## Source note 15, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L90)

```text
// `base + index * stride` and the end bound loaded by vfetch_full.
```

## Source note 16, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L94)

```text
// Get the base address in dwords from the bits 2:31 of the first fetch
```

## Source note 17, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L95)

```text
// constant word.
```

## Source note 18, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L97)

```text
// The only element of the fetch constant buffer.
```

## Source note 19, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L99)

```text
// Vector index.
```

## Source note 20, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L101)

```text
// Component index.
```

## Source note 21, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L115)

```text
// address is the base now. The exclusive end is base + size (size in words
```

## Source note 22, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L116)

```text
// in bits 2:25 of the second word). Store it for the subsequent
```

## Source note 23, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L117)

```text
// vfetch_mini, which reuses this fetch constant.
```

## Source note 24, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L129)

```text
// Convert the index to an integer by flooring or by rounding to the
```

## Source note 25, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L130)

```text
// nearest (as floor(index + 0.5) because rounding to the nearest even
```

## Source note 26, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L131)

```text
// makes no sense for addressing, both 1.5 and 2.5 would be 2).
```

## Source note 27, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L148)

```text
// Store the address for the subsequent vfetch_mini.
```

## Source note 28, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L153)

```text
// The vfetch_full address has been loaded for the subsequent vfetch_mini,
```

## Source note 29, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L154)

```text
// but there's no data to load.
```

## Source note 30, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L159)

```text
// Load the needed words.
```

## Source note 31, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L168)

```text
// Add the word offset from the instruction (signed), plus the offset of the
```

## Source note 32, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L169)

```text
// word within the element.
```

## Source note 33, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L176)

```text
// Words at or past the end of the fetch buffer read as 0, matching the
```

## Source note 34, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L177)

```text
// hardware's bounds clamping. Games rely on this - e.g. an over-allocated
```

## Source note 35, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L178)

```text
// quad-list particle draw whose inactive vertices fetch 0 and collapse to a
```

## Source note 36, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L179)

```text
// degenerate (zero-area) primitive instead of exploding to garbage.
```

## Source note 37, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L188)

```text
// Copying from the array to id_vector_temp_ now, not in the loop above,
```

## Source note 38, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L189)

```text
// because of the LoadUint32FromSharedMemory call (potentially using
```

## Source note 39, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L190)

```text
// id_vector_temp_ internally).
```

## Source note 40, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L199)

```text
// Endian swap the words, getting the endianness from bits 0:1 of the second
```

## Source note 41, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L200)

```text
// fetch constant word (loaded above).
```

## Source note 42, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L207)

```text
// Convert the format.
```

## Source note 43, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L211)

```text
// If needed_words is not zero (checked in the beginning), this must not be
```

## Source note 44, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L212)

```text
// zero too. For simplicity, it's assumed that something will be unpacked
```

## Source note 45, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L213)

```text
// here.
```

## Source note 46, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L279)

```text
// If only one of two components is needed, extract it.
```

## Source note 47, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L290)

```text
// Bypassing the assertion in spv::Builder::createCompositeConstruct as
```

## Source note 48, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L291)

```text
// of November 5, 2020 - can construct vectors by concatenating vectors,
```

## Source note 49, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L292)

```text
// not just from individual scalars.
```

## Source note 50, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L321)

```text
// No need to clamp to -1 if signed - 1/(2^31-1) is rounded to
```

## Source note 51, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L322)

```text
// 1/(2^31) as float32.
```

## Source note 52, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L363)

```text
// Extract the components from the words as individual ints or uints.
```

## Source note 53, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L365)

```text
// Sign-extending extraction - in GLSL the sign-extending overload accepts
```

## Source note 54, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L366)

```text
// int.
```

## Source note 55, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L373)

```text
// Default is `words` itself if 1 word loaded.
```

## Source note 56, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L398)

```text
// Combine extracted components into a vector.
```

## Source note 57, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L411)

```text
// Convert to floating-point.
```

## Source note 58, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L414)

```text
// Normalize.
```

## Source note 59, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L420)

```text
// The signed case would result in 1.0 / 0.0 for 1-bit components, but
```

## Source note 60, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L421)

```text
// there are no Xenos formats with them.
```

## Source note 61, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L457)

```text
// Treat both -(2^(n-1)) and -(2^(n-1)-1) as -1. Using regular FMax,
```

## Source note 62, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L458)

```text
// not NMax, because the number is known not to be NaN.
```

## Source note 63, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L487)

```text
// Apply the exponent bias.
```

## Source note 64, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L494)

```text
// If any components not present in the format were requested, pad the
```

## Source note 65, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L495)

```text
// resulting vector with zeros.
```

## Source note 66, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L498)

```text
// Bypassing the assertion in spv::Builder::createCompositeConstruct as of
```

## Source note 67, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L499)

```text
// November 5, 2020 - can construct vectors by concatenating vectors, not
```

## Source note 68, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L500)

```text
// just from individual scalars.
```

## Source note 69, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L524)

```text
// Handle the instructions for setting the register LOD.
```

## Source note 70, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L545)

```text
// Handle instructions that store something.
```

## Source note 71, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L552)

```text
// Cube maps don't use the border.
```

## Source note 72, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L572)

```text
// Nothing to fetch, only constant 0/1 writes - simplify the rest of the
```

## Source note 73, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L573)

```text
// function so it doesn't have to handle this case.
```

## Source note 74, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L581)

```text
// Stores the needed components of the result.
```

## Source note 75, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L604)

```text
// Doesn't need the texture, handle separately.
```

## Source note 76, line 633

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L633)

```text
// kTextureFetch, kGetTextureComputedLod, kGetTextureWeights or
```

## Source note 77, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L634)

```text
// kGetTextureBorderColorFrac.
```

## Source note 78, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L636)

```text
// getBCF samples the texture twice, with a transparent black and an opaque
```

## Source note 79, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L637)

```text
// white border in place of the unsigned and the signed sample. The
```

## Source note 80, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L638)

```text
// difference is the share of the border.
```

## Source note 81, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L641)

```text
// Whether to use gradients (implicit or explicit) for LOD calculation.
```

## Source note 82, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L661)

```text
// Texel center snap instead of the epsilon (see CanSnapToTexelCenter).
```

## Source note 83, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L672)

```text
// While GL_ARB_texture_query_lod specifies the value for
```

## Source note 84, line 673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L673)

```text
// GL_NEAREST_MIPMAP_NEAREST and GL_LINEAR_MIPMAP_NEAREST minifying
```

## Source note 85, line 674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L674)

```text
// functions as rounded (unlike the `lod` instruction in Direct3D 10.1+,
```

## Source note 86, line 675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L675)

```text
// which is not defined for point sampling), the XNA assembler doesn't
```

## Source note 87, line 676

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L676)

```text
// accept MipFilter overrides for getCompTexLOD - probably should be
```

## Source note 88, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L677)

```text
// linear only, though not known exactly.
```

## Source note 89, line 679

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L679)

```text
// 4D5307F2 uses vertex displacement map textures for tessellated models
```

## Source note 90, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L680)

```text
// like the beehive tree with explicit LOD with point sampling (they store
```

## Source note 91, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L681)

```text
// values packed in two components), however, the fetch constant has
```

## Source note 92, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L682)

```text
// anisotropic filtering enabled. However, Direct3D 12 doesn't allow
```

## Source note 93, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L683)

```text
// mixing anisotropic and point filtering. Possibly anistropic filtering
```

## Source note 94, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L684)

```text
// should be disabled when explicit LOD is used - do this here.
```

## Source note 95, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L728)

```text
// Too many image or sampler bindings used.
```

## Source note 96, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L757)

```text
// Get offsets applied to the coordinates before sampling.
```

## Source note 97, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L760)

```text
// MSDN doesn't list offsets as getCompTexLOD parameters.
```

## Source note 98, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L762)

```text
// Add a small epsilon to the offset (1.5/4 the fixed-point texture
```

## Source note 99, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L763)

```text
// coordinate ULP with 8-bit subtexel precision - shouldn't significantly
```

## Source note 100, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L764)

```text
// effect the fixed-point conversion; 1/4 is also not enough with 3x
```

## Source note 101, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L765)

```text
// resolution scaling very noticeably on the weapon in 4D5307E6, at least
```

## Source note 102, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L766)

```text
// on the Direct3D 12 backend) to resolve ambiguity when fetching
```

## Source note 103, line 767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L767)

```text
// point-sampled textures between texels. This applies to both normalized
```

## Source note 104, line 768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L768)

```text
// (58410954 Xbox Live Arcade logo, coordinates interpolated between
```

## Source note 105, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L769)

```text
// vertices with half-pixel offset) and unnormalized (4D5307E6 lighting
```

## Source note 106, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L770)

```text
// G-buffer reading, ps_param_gen pixels) coordinates. On Nvidia Pascal,
```

## Source note 107, line 771

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L771)

```text
// without this adjustment, blockiness is visible in both cases. Possibly
```

## Source note 108, line 772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L772)

```text
// there is a better way, however, an attempt was made to error-correct
```

## Source note 109, line 773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L773)

```text
// division by adding the difference between original and re-denormalized
```

## Source note 110, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L774)

```text
// coordinates, but on Nvidia, `mul` (on Direct3D 12) and internal
```

## Source note 111, line 775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L775)

```text
// multiplication in texture sampling apparently round differently, so
```

## Source note 112, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L776)

```text
// `mul` gives a value that would be floored as expected, but the
```

## Source note 113, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L777)

```text
// left/upper pixel is still sampled instead.
```

## Source note 114, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L783)

```text
// For coordinate lerp factors. This needs to be done separately for
```

## Source note 115, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L784)

```text
// point mag/min filters, but they're currently not handled here
```

## Source note 116, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L785)

```text
// anyway.
```

## Source note 117, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L808)

```text
// Applying the rounding epsilon to cube maps too for potential game
```

## Source note 118, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L809)

```text
// passes processing cube map faces themselves.
```

## Source note 119, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L815)

```text
// The logic for ST weights is the same for all faces.
```

## Source note 120, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L830)

```text
// Fetch constant word usage:
```

## Source note 121, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L831)

```text
// - 2: Size (needed only once).
```

## Source note 122, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L832)

```text
// - 3: Exponent adjustment (needed only once).
```

## Source note 123, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L833)

```text
// - 4: Conditionally for 3D kTextureFetch: stacked texture filtering modes.
```

## Source note 124, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L834)

```text
//      Unconditionally LOD kTextureFetch: LOD and gradient exponent bias,
```

## Source note 125, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L835)

```text
//      result exponent bias.
```

## Source note 126, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L836)

```text
// - 5: Dimensionality (3D or 2D stacked - needed only once).
```

## Source note 127, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L838)

```text
// Load the texture size and whether it's 3D or stacked if needed.
```

## Source note 128, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L839)

```text
// 1D: X - width.
```

## Source note 129, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L840)

```text
// 2D, cube: X - width, Y - height (cube maps probably can be only square,
```

## Source note 130, line 841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L841)

```text
//           but for simplicity).
```

## Source note 131, line 842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L842)

```text
// 3D: X - width, Y - height, Z - depth.
```

## Source note 132, line 846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L846)

```text
// Size needed for denormalization for coordinate lerp factor.
```

## Source note 133, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L851)

```text
// Always need size for 1D textures to support wide 1D textures.
```

## Source note 134, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L864)

```text
// Size needed for normalization (or, for stacked texture layers,
```

## Source note 135, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L865)

```text
// denormalization) and for offsets.
```

## Source note 136, line 869

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L869)

```text
// Always need size for 1D textures to handle wide 1D textures
```

## Source note 137, line 870

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L870)

```text
// (> 8192 wide) which are mapped to 2D grids. The shader needs
```

## Source note 138, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L871)

```text
// the original width to compute the 2D coordinate remapping.
```

## Source note 139, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L875)

```text
// A promoted tfetch1D always needs the size - the interpretation is
```

## Source note 140, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L876)

```text
// selected at runtime, and the width feeds the wide 1D remap.
```

## Source note 141, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L883)

```text
// Stacked and 3D textures are fetched from different bindings - the
```

## Source note 142, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L884)

```text
// check is always needed.
```

## Source note 143, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L887)

```text
// Need to normalize all (if 3D).
```

## Source note 144, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L890)

```text
// Need to denormalize Z (if stacked).
```

## Source note 145, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L898)

```text
// The size is not needed for face ID offset.
```

## Source note 146, line 904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L904)

```text
// Stacked and 3D textures have different size packing - need to get
```

## Source note 147, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L905)

```text
// whether the texture is 3D unconditionally.
```

## Source note 148, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L910)

```text
// Get the data dimensionality from the bits 9:10 of the fetch constant
```

## Source note 149, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L911)

```text
// word 5.
```

## Source note 150, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L930)

```text
// For 1D textures, we need to save the original uint size before it gets
```

## Source note 151, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L931)

```text
// converted to float, so we can check if the texture is "wide" (> 8192).
```

## Source note 152, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L934)

```text
// Get the size from the fetch constant word 2.
```

## Source note 153, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L951)

```text
// Save the uint value for wide 1D texture detection later.
```

## Source note 154, line 971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L971)

```text
// tfetch1D promoted to 2D because of a 2-component source swizzle.
```

## Source note 155, line 972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L972)

```text
// The promotion is static (swizzle-only), so the fetch constant
```

## Source note 156, line 973

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L973)

```text
// may still be an actual 1D texture - select the size
```

## Source note 157, line 974

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L974)

```text
// interpretation by the runtime dimension (word 5, bits 9-10), and
```

## Source note 158, line 975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L975)

```text
// keep the 24-bit width for the wide 1D remap below, which
```

## Source note 159, line 976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L976)

```text
// performs its own runtime dimension check.
```

## Source note 160, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L997)

```text
// Height 1 (stored as 0) if actually 1D - the host texture is a
```

## Source note 161, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L998)

```text
// single row unless wide, and the wide remap overwrites Y.
```

## Source note 162, line 1049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1049)

```text
// HZB reducers in 555308B6 and 5553080B lock the sampler to one mip
```

## Source note 163, line 1050

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1050)

```text
// and address it with unnormalized coordinates. Those coordinates are
```

## Source note 164, line 1051

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1051)

```text
// in the locked mip's grid, but the denominator below was always the
```

## Source note 165, line 1052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1052)

```text
// base level size, so each reduction after the first read garbage.
```

## Source note 166, line 1053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1053)

```text
// Limit this to 2D unnormalized fetches with a locked mip. This changes
```

## Source note 167, line 1054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1054)

```text
// only the denominator.
```

## Source note 168, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1062)

```text
// Word 4 has MipMinLevel in bits 2:5 and MipMaxLevel in bits 6:9.
```

## Source note 169, line 1088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1088)

```text
// Fetch constants store size minus 1 - add 1.
```

## Source note 170, line 1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1092)

```text
// max(size >> mip, 1) for non-pow2 textures. Scaling stays
```

## Source note 171, line 1093

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1093)

```text
// unchanged.
```

## Source note 172, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1103)

```text
// Convert the size to float for multiplication or division.
```

## Source note 173, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1110)

```text
// Check if this texture is from a resolution-scaled resolve operation.
```

## Source note 174, line 1111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1111)

```text
// This affects both size and offset calculations.
```

## Source note 175, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1115)

```text
// Load textures_resolved from system constants.
```

## Source note 176, line 1122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1122)

```text
// Check if this texture is resolved:
```

## Source note 177, line 1123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1123)

```text
// (textures_resolved >> fetch_constant_index) & 1
```

## Source note 178, line 1132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1132)

```text
// Scale the size for resolution-scaled textures.
```

## Source note 179, line 1133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1133)

```text
// When a texture is from a resolve operation (scaled), its actual host
```

## Source note 180, line 1134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1134)

```text
// dimensions are larger than the guest dimensions in the fetch constant.
```

## Source note 181, line 1135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1135)

```text
// The size must be scaled so that coordinate normalization and offset
```

## Source note 182, line 1136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1136)

```text
// calculations use the correct host dimensions.
```

## Source note 183, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1152)

```text
// Z size is not scaled (depth/layers don't change with resolution).
```

## Source note 184, line 1158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1158)

```text
// Load the needed original values of the coordinates operand.
```

## Source note 185, line 1181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1181)

```text
// How much the coordinates change from the host pixel to the guest pixel
```

## Source note 186, line 1182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1182)

```text
// center if they're an unmodified interpolant (see
```

## Source note 187, line 1183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1183)

```text
// StartFragmentShaderInMain), for picking the guest texel in point sampled
```

## Source note 188, line 1184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1184)

```text
// fetches.
```

## Source note 189, line 1223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1223)

```text
// Resolution scale doesn't need reverting for texture weights - weights are
```

## Source note 190, line 1224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1224)

```text
// calculated from fractional parts of coordinates which are
```

## Source note 191, line 1225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1225)

```text
// scale-independent.
```

## Source note 192, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1233)

```text
// Need unnormalized coordinates.
```

## Source note 193, line 1246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1246)

```text
// 0.5 has already been subtracted via offsets previously.
```

## Source note 194, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1252)

```text
// kTextureFetch, kGetTextureComputedLod or kGetTextureBorderColorFrac.
```

## Source note 195, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1256)

```text
// Normalize the XY coordinates, and apply the offset. When the texture
```

## Source note 196, line 1257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1257)

```text
// is resolution-scaled, size has already been scaled up to host texels
```

## Source note 197, line 1258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1258)

```text
// above so dividing the offset by it yields a 1-host-texel step.
```

## Source note 198, line 1266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1266)

```text
// Convert the guest-texel coord to host texels for resolution-
```

## Source note 199, line 1267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1267)

```text
// scaled textures, since size below is in host texels. Done before
```

## Source note 200, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1268)

```text
// the offset add so the offset stays at 1 host texel rather than
```

## Source note 201, line 1269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1269)

```text
// being multiplied with the coord.
```

## Source note 202, line 1296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1296)

```text
// Handle wide 1D textures (> 8192 wide) mapped to 2D grids.
```

## Source note 203, line 1299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1299)

```text
// Check if the fetch constant's actual dimension is k1D (word 5, bits
```

## Source note 204, line 1300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1300)

```text
// 9-10). If not, skip wide 1D handling as size bits differ per
```

## Source note 205, line 1301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1301)

```text
// dimension.
```

## Source note 206, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1319)

```text
// Check if wide (> 8192) - only valid if dimension is actually 1D.
```

## Source note 207, line 1327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1327)

```text
// Only apply remapping if actually 1D and wide.
```

## Source note 208, line 1332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1332)

```text
// original_width = width_minus_1 + 1
```

## Source note 209, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1341)

```text
// num_rows = min(ceil(original_width / row_width), row cap)
```

## Source note 210, line 1342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1342)

```text
// The cap matches the texture cache's materialized row cap for
```

## Source note 211, line 1343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1343)

```text
// index-space widths far larger than the real data.
```

## Source note 212, line 1362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1362)

```text
// row_index = floor(linear_x / row_width)
```

## Source note 213, line 1368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1368)

```text
// x_in_row = linear_x - row_index * row_width
```

## Source note 214, line 1374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1374)

```text
// coord_2d.x = x_in_row / row_width (normalized)
```

## Source note 215, line 1378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1378)

```text
// coord_2d.y = (row_index + 0.5) / num_rows (normalized) - sample at
```

## Source note 216, line 1379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1379)

```text
// the center of the row, not its edge. At the edge, linear filtering
```

## Source note 217, line 1380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1380)

```text
// would blend 50/50 with the previous row (texels 8192 apart), and
```

## Source note 218, line 1381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1381)

```text
// even point sampling could pick the previous row when
```

## Source note 219, line 1382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1382)

```text
// (row_index / num_rows) * num_rows rounds to just below row_index.
```

## Source note 220, line 1399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1399)

```text
// Apply the offset, and normalize the Z coordinate for a 3D texture.
```

## Source note 221, line 1416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1416)

```text
// Denormalize the Z coordinate for a stacked texture, and apply the
```

## Source note 222, line 1417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1417)

```text
// offset.
```

## Source note 223, line 1429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1429)

```text
// 3D case.
```

## Source note 224, line 1442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1442)

```text
// Stacked case.
```

## Source note 225, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1452)

```text
// Clamp the layer index to a valid range so an Inf or NaN coordinate
```

## Source note 226, line 1453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1453)

```text
// does not select an undefined array layer.
```

## Source note 227, line 1459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1459)

```text
// Select one of the two.
```

## Source note 228, line 1474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1474)

```text
// Transform the cube coordinates from 2D to 3D.
```

## Source note 229, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1475)

```text
// Move SC/TC from 1...2 to -1...1.
```

## Source note 230, line 1485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1485)

```text
// Get the face index (floored, within 0...5 - OpConvertFToU is
```

## Source note 231, line 1486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1486)

```text
// undefined for out-of-range values, so clamping from both sides
```

## Source note 232, line 1487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1487)

```text
// manually).
```

## Source note 233, line 1498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1498)

```text
// Split the face index into the axis and the sign.
```

## Source note 234, line 1509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1509)

```text
// Remap the axes in a way opposite to the ALU cube instruction.
```

## Source note 235, line 1524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1524)

```text
// Make Z the default.
```

## Source note 236, line 1535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1535)

```text
// X is the major axis case.
```

## Source note 237, line 1541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1541)

```text
// Y is the major axis case.
```

## Source note 238, line 1547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1547)

```text
// Z is the major axis case.
```

## Source note 239, line 1553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1553)

```text
// Gather the coordinate components from the branches.
```

## Source note 240, line 1597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1597)

```text
// All 32 bits containing the values for 4 fetch constants (use
```

## Source note 241, line 1598

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1598)

```text
// OpBitFieldUExtract to get the signednesses for the specific components
```

## Source note 242, line 1599

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1599)

```text
// of this texture).
```

## Source note 243, line 1609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1609)

```text
// kGetTextureComputedLod.
```

## Source note 244, line 1611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1611)

```text
// Check if the signed binding is needs to be accessed rather than the
```

## Source note 245, line 1612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1612)

```text
// unsigned (if all signednesses are signed).
```

## Source note 246, line 1620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1620)

```text
// OpImageQueryLod doesn't need the array layer component.
```

## Source note 247, line 1621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1621)

```text
// So, 3 coordinate components for 3D cube, 2 in other cases (including
```

## Source note 248, line 1622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1622)

```text
// 1D, which are emulated as 2D arrays).
```

## Source note 249, line 1623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1623)

```text
// OpSampledImage must be in the same block as where its result is used.
```

## Source note 250, line 1625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1625)

```text
// Check if the texture is 3D or stacked.
```

## Source note 251, line 1631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1631)

```text
// 3D.
```

## Source note 252, line 1644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1644)

```text
// 2D stacked.
```

## Source note 253, line 1671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1671)

```text
// kTextureFetch or kGetTextureBorderColorFrac.
```

## Source note 254, line 1674

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1674)

```text
// Extract the signedness for each component of the swizzled result, and
```

## Source note 255, line 1675

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1675)

```text
// get which bindings (unsigned and signed) are needed.
```

## Source note 256, line 1684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1684)

```text
// Both border colors are always sampled.
```

## Source note 257, line 1717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1717)

```text
// Load the fetch constant word 3, needed for result exponent biasing.
```

## Source note 258, line 1718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1718)

```text
// exp_adjust is in word 3, bits 13:18 (6-bit signed).
```

## Source note 259, line 1732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1732)

```text
// Load the fetch constant word 4, needed unconditionally for LOD
```

## Source note 260, line 1733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1733)

```text
// biasing, and conditionally for stacked texture filtering.
```

## Source note 261, line 1747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1747)

```text
// Accumulate the explicit LOD (or LOD bias) sources (in D3D11.3
```

## Source note 262, line 1748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1748)

```text
// specification order: specified LOD + sampler LOD bias + instruction
```

## Source note 263, line 1749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1749)

```text
// LOD bias).
```

## Source note 264, line 1750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1750)

```text
// Fetch constant LOD (bits 12:21 of the word 4).
```

## Source note 265, line 1759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1759)

```text
// Register LOD.
```

## Source note 266, line 1765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1765)

```text
// Instruction LOD bias.
```

## Source note 267, line 1772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1772)

```text
// Cube and 3D auto-LOD without register gradients use implicit LOD +
```

## Source note 268, line 1773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1773)

```text
// bias. Explicit cube gradients pick the wrong mip on Vulkan, and
```

## Source note 269, line 1774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1774)

```text
// explicit 3D gradients of a coordinate that is constant across the
```

## Source note 270, line 1775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1775)

```text
// quad make NVIDIA return a different texel in one lane of the quad.
```

## Source note 271, line 1776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1776)

```text
// 1D and 2D keep explicit gradients.
```

## Source note 272, line 1782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1782)

```text
// The per-axis gradient exponent biases can't be applied to the
```

## Source note 273, line 1783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1783)

```text
// host's implicit gradients, so we approximate them by adding the
```

## Source note 274, line 1784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1784)

```text
// greater of the two to the LOD bias. Scaling both gradients by 2^n
```

## Source note 275, line 1785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1785)

```text
// shifts the computed LOD by n, so this is exact whenever both biases
```

## Source note 276, line 1786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1786)

```text
// are equal, and biases a blurrier mip rather than a shimmering one.
```

## Source note 277, line 1799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1799)

```text
// Calculate the gradients for sampling the texture if needed.
```

## Source note 278, line 1800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1800)

```text
// 2D vectors for k1D (because 1D images are emulated as 2D arrays),
```

## Source note 279, line 1801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1801)

```text
// k2D.
```

## Source note 280, line 1802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1802)

```text
// 3D vectors for k3DOrStacked, kCube.
```

## Source note 281, line 1805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1805)

```text
// Per-axis gradient exponent biases (LodBiasH/V) from word 4: h in
```

## Source note 282, line 1806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1806)

```text
// bits 22:26, v in bits 27:31. Applied here in the sample path like
```

## Source note 283, line 1807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1807)

```text
// the fetch-constant LOD bias (getCompTexLOD returns the raw queried
```

## Source note 284, line 1808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1808)

```text
// LOD, so neither bias is folded into it). Zero (the common case) is
```

## Source note 285, line 1809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1809)

```text
// a no-op.
```

## Source note 286, line 1830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1830)

```text
// Always use automatic gradient computation for 1D textures.
```

## Source note 287, line 1831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1831)

```text
// For wide 1D textures, coordinates have been remapped to 2D, and
```

## Source note 288, line 1832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1832)

```text
// register gradients would be in 1D space without accounting for
```

## Source note 289, line 1833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1833)

```text
// the 2D mapping. For normal 1D textures, coordinates[1] is
```

## Source note 290, line 1834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1834)

```text
// always 0, so auto gradients give the same result as register
```

## Source note 291, line 1835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1835)

```text
// gradients (Y gradient will be 0).
```

## Source note 292, line 1837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1837)

```text
// For wide 1D textures, coordinates[0] and coordinates[1]
```

## Source note 293, line 1838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1838)

```text
// have been remapped. Compute gradients from both.
```

## Source note 294, line 1841

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1841)

```text
// For wide 1D textures, also compute Y gradients.
```

## Source note 295, line 1842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1842)

```text
// coordinates[1] is non-zero only for wide 1D.
```

## Source note 296, line 1853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1853)

```text
// 1D textures are sampled as 2D arrays - need 2-component
```

## Source note 297, line 1854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1854)

```text
// gradients.
```

## Source note 298, line 1875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1875)

```text
// Normalize the gradients.
```

## Source note 299, line 1912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1912)

```text
// Normalize the gradients.
```

## Source note 300, line 1945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1945)

```text
// Only register gradients reach here (auto-LOD uses implicit LOD
```

## Source note 301, line 1946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1946)

```text
// + bias, handled at the gradient block guard above). Register
```

## Source note 302, line 1947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1947)

```text
// gradients are already in the cube space for cube maps.
```

## Source note 303, line 1969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1969)

```text
// Point sampled fetch constant uses the texel center in host texels
```

## Source note 304, line 1970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1970)

```text
// for a resolution scaled texture (the size already is) instead of
```

## Source note 305, line 1971

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1971)

```text
// the epsilon. Branching as the snapping is only needed for point
```

## Source note 306, line 1972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1972)

```text
// sampled fetch constants and is uniform.
```

## Source note 307, line 1986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1986)

```text
// Stay within the host texels of the guest texel that the guest
```

## Source note 308, line 1987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1987)

```text
// pixel center samples, keeping the host texel of this host
```

## Source note 309, line 1988

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1988)

```text
// pixel within it for detail if the texture is
```

## Source note 310, line 1989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1989)

```text
// resolution-scaled.
```

## Source note 311, line 1997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1997)

```text
// The host texel at the guest pixel center, rounded like the one
```

## Source note 312, line 1998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1998)

```text
// of this host pixel so they agree when the delta is 0.
```

## Source note 313, line 2005

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2005)

```text
// The offset was applied in host texels, while the guest
```

## Source note 314, line 2006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2006)

```text
// steps by guest texels.
```

## Source note 315, line 2054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2054)

```text
// Sample the texture.
```

## Source note 316, line 2066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2066)

```text
// 3D (3 coordinate components, 3 gradient components, single fetch)
```

## Source note 317, line 2067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2067)

```text
// or 2D stacked (2 coordinate components + 1 array layer coordinate
```

## Source note 318, line 2068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2068)

```text
// component, 2 gradient components, two fetches if the Z axis is
```

## Source note 319, line 2069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2069)

```text
// linear-filtered).
```

## Source note 320, line 2076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2076)

```text
// 3D.
```

## Source note 321, line 2094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2094)

```text
// 2D stacked.
```

## Source note 322, line 2096

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2096)

```text
// Extract 2D gradients for stacked textures which are 2D arrays.
```

## Source note 323, line 2105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2105)

```text
// Check if linear filtering is needed.
```

## Source note 324, line 2118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2118)

```text
// Check if minifying along layers (derivative > 1 along any
```

## Source note 325, line 2119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2119)

```text
// axis).
```

## Source note 326, line 2125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2125)

```text
// Denormalize the gradient if provided as normalized.
```

## Source note 327, line 2130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2130)

```text
// For NaN, considering that magnification is being done.
```

## Source note 328, line 2134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2134)

```text
// Choose what filter is actually used, the minification or the
```

## Source note 329, line 2135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2135)

```text
// magnification one.
```

## Source note 330, line 2158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2158)

```text
// No gradients, or using the same filter overrides for magnifying
```

## Source note 331, line 2159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2159)

```text
// and minifying. Assume always magnifying if no gradients (LOD 0,
```

## Source note 332, line 2160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2160)

```text
// always <= 0). LOD is within 2D layers, not between them (unlike
```

## Source note 333, line 2161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2161)

```text
// in 3D textures, which have mips with depth reduced), so it
```

## Source note 334, line 2162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2162)

```text
// shouldn't have effect on filtering between layers.
```

## Source note 335, line 2172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2172)

```text
// Linear filtering may be needed either based on a dynamic
```

## Source note 336, line 2173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2173)

```text
// condition (the filtering mode is taken from the fetch constant,
```

## Source note 337, line 2174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2174)

```text
// or it's different for magnification and minification), or on a
```

## Source note 338, line 2175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2175)

```text
// static one (with gradients - specified in the instruction for
```

## Source note 339, line 2176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2176)

```text
// both magnification and minification as linear, without
```

## Source note 340, line 2177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2177)

```text
// gradients - specified for magnification as linear).
```

## Source note 341, line 2178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2178)

```text
// If the filter is linear, subtract 0.5 from the Z coordinate of
```

## Source note 342, line 2179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2179)

```text
// the first layer in filtering because 0.5 is in the middle of it.
```

## Source note 343, line 2190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2190)

```text
// Sample the first layer, needed regardless of whether filtering is
```

## Source note 344, line 2191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2191)

```text
// needed.
```

## Source note 345, line 2192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2192)

```text
// Floor the array layer (Vulkan does rounding to nearest or + 0.5
```

## Source note 346, line 2193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2193)

```text
// and floor even for the layer index, but on the Xenos, addressing
```

## Source note 347, line 2194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2194)

```text
// is similar to that of 3D textures). This is needed for both point
```

## Source note 348, line 2195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2195)

```text
// and linear filtering (with linear, 0.5 was subtracted
```

## Source note 349, line 2196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2196)

```text
// previously).
```

## Source note 350, line 2209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2209)

```text
// Sample the second layer if linear filtering is potentially needed
```

## Source note 351, line 2210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2210)

```text
// (conditionally or unconditionally, depending on whether the
```

## Source note 352, line 2211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2211)

```text
// filter needs to be chosen at runtime), and filter.
```

## Source note 353, line 2244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2244)

```text
// Get the actual build point after the SampleTexture call for
```

## Source note 354, line 2245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2245)

```text
// phi.
```

## Source note 355, line 2300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2300)

```text
// The samples differ by the border share in components with texture
```

## Source note 356, line 2301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2301)

```text
// data and not at all in constant ones.
```

## Source note 357, line 2321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2321)

```text
// Swizzle the result components manually if needed, to `result`.
```

## Source note 358, line 2322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2322)

```text
// Because the same host format component may be replicated into
```

## Source note 359, line 2323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2323)

```text
// multiple guest components (such as for formats with less than 4
```

## Source note 360, line 2324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2324)

```text
// components), yet the signedness is per-guest-component, it's not
```

## Source note 361, line 2325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2325)

```text
// possible to apply the signedness to host components before swizzling,
```

## Source note 362, line 2326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2326)

```text
// so doing it during (for unsigned vs. signed) and after (for biased
```

## Source note 363, line 2327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2327)

```text
// and gamma) swizzling.
```

## Source note 364, line 2333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2333)

```text
// All 32 bits containing the values (24 bits) for 2 fetch constants.
```

## Source note 365, line 2351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2351)

```text
// Bit 2 - X/Y/Z/W or 0/1.
```

## Source note 366, line 2361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2361)

```text
// Constant values.
```

## Source note 367, line 2362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2362)

```text
// Bit 0 - 0 or 1.
```

## Source note 368, line 2369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2369)

```text
// Fetched components.
```

## Source note 369, line 2370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2370)

```text
// Select whether the result is signed or unsigned (or biased or
```

## Source note 370, line 2371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2371)

```text
// gamma-corrected) based on the post-swizzle signedness.
```

## Source note 371, line 2377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2377)

```text
// Bit 0 - X or Y, Z or W, 0 or 1.
```

## Source note 372, line 2386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2386)

```text
// Bit 1 - X/Y or Z/W.
```

## Source note 373, line 2396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2396)

```text
// Select between the constants and the fetched components.
```

## Source note 374, line 2402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2402)

```text
// Apply the signednesses to all the needed components. If swizzling is
```

## Source note 375, line 2403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2403)

```text
// done in the shader rather than via the image view, unsigned or signed
```

## Source note 376, line 2404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2404)

```text
// source has already been selected into `result` - only need to bias or
```

## Source note 377, line 2405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2405)

```text
// to gamma-correct.
```

## Source note 378, line 2429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2429)

```text
// Make unsigned (do nothing, take the unsigned component in the
```

## Source note 379, line 2430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2430)

```text
// phi) the default, and also, if unsigned or signed has already
```

## Source note 380, line 2431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2431)

```text
// been selected in swizzling, make signed the default to since
```

## Source note 381, line 2432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2432)

```text
// it, just like unsigned, doesn't need any transformations.
```

## Source note 382, line 2450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2450)

```text
// Signed.
```

## Source note 383, line 2458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2458)

```text
// Unsigned biased.
```

## Source note 384, line 2460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2460)

```text
// Decode as signed offset binary: (n - 2^(w - 1)) / (2^(w - 1) - 1)
```

## Source note 385, line 2461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2461)

```text
// This maps 128 to zero for 8 bit components, avoiding the 1/255
```

## Source note 386, line 2462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2462)

```text
// bias of 2 * u - 1. Leave the result unclamped until num_format is
```

## Source note 387, line 2463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2463)

```text
// applied, and keep 2 * u - 1 when the width is unknown or 1 bit.
```

## Source note 388, line 2497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2497)

```text
// Gamma.
```

## Source note 389, line 2501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2501)

```text
// Get the current build point for the phi operation not to assume
```

## Source note 390, line 2502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2502)

```text
// that it will be the same as before PWLGammaToLinear.
```

## Source note 391, line 2505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2505)

```text
// Merge.
```

## Source note 392, line 2526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2526)

```text
// Apply num_format after signs/gamma.
```

## Source note 393, line 2532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2532)

```text
// Uniform early out. Zero means leave the sample alone.
```

## Source note 394, line 2533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2533)

```text
// Bit 26 is the coordinate snap, not a scale.
```

## Source note 395, line 2552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2552)

```text
// Reconstruct point sampled 4 to 7 bit unsigned components
```

## Source note 396, line 2553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2553)

```text
// using the guest conversion (see GetIntegerScaleBits).
```

## Source note 397, line 2584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2584)

```text
// The texel n from the host's n / (2^w - 1).
```

## Source note 398, line 2591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2591)

```text
// n * (2^w + 1) / 2^(2w), where the packed component field
```

## Source note 399, line 2592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2592)

```text
// is 1 to 15 (unsigned with a nonzero width field).
```

## Source note 400, line 2615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2615)

```text
// Only round unsigned normalized components to 16 fractional bits.
```

## Source note 401, line 2640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2640)

```text
// Clamp normalized unsigned-biased components to -1. Post-filtering
```

## Source note 402, line 2641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2641)

```text
// clamping can put mixtures with a stored value of 0 up to one
```

## Source note 403, line 2642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2642)

```text
// component code below the result of clamping each texel before.
```

## Source note 404, line 2672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2672)

```text
// Restore integer values with 2^w - 1 for unsigned components
```

## Source note 405, line 2673

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2673)

```text
// and 2^(w - 1) - 1 for signed and unsigned-biased.
```

## Source note 406, line 2681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2681)

```text
// Signed (1) and biased (2) take one off the shift.
```

## Source note 407, line 2702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2702)

```text
// For 1 bit unsigned-biased components, use a scale of 0.5 and
```

## Source note 408, line 2703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2703)

```text
// an offset of -0.5 to recover -1 and 0.
```

## Source note 409, line 2722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2722)

```text
// Host decode precision varies since NVIDIA bit replication turns
```

## Source note 410, line 2723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2723)

```text
// 1/31 into 8/255, giving a scaled value of 0.9725. Point
```

## Source note 411, line 2724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2724)

```text
// sampling gives the guest an integer texel value, while
```

## Source note 412, line 2725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2725)

```text
// filtering keeps the fractional result.
```

## Source note 413, line 2743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2743)

```text
// Keep the original result when the scale branch is skipped.
```

## Source note 414, line 2755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2755)

```text
// Apply the exponent bias from the bits 13:18 of the fetch constant
```

## Source note 415, line 2756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2756)

```text
// word 3.
```

## Source note 416, line 2780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2780)

```text
// 1D and 2D textures (including stacked ones) are treated as 2D arrays for
```

## Source note 417, line 2781

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2781)

```text
// binding and coordinate simplicity.
```

## Source note 418, line 2883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2883)

```text
// The binding indices will be specified later after all textures are added as
```

## Source note 419, line 2884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2884)

```text
// samplers are located after images in the descriptor set.
```

## Source note 420, line 2905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2905)

```text
// OpSampledImage must be in the same block as where its result is used.
```

## Source note 421, line 2926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2926)

```text
// This may overwrite the first lerp endpoint for the sign (such usage of
```

## Source note 422, line 2927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2927)

```text
// this function is allowed).
```

## Source note 423, line 2936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2936)

```text
// OpSampledImage must be in the same block as where its result is used.
```
