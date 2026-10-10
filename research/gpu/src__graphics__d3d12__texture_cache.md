# Texture cache: graphics source notes

This record preserves technical and API notes moved from `src/graphics/d3d12/texture_cache.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L37)

```text
// Generated with `xb buildshaders`.
```

## Source note 2, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L84)

```text
// k_1_REVERSE
```

## Source note 3, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L88)

```text
// k_1
```

## Source note 4, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L92)

```text
// k_8
```

## Source note 5, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L96)

```text
// k_1_5_5_5
```

## Source note 6, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L97)

```text
// Red and blue swapped in the load shader for simplicity.
```

## Source note 7, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L101)

```text
// k_5_6_5
```

## Source note 8, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L102)

```text
// Red and blue swapped in the load shader for simplicity.
```

## Source note 9, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L106)

```text
// k_6_5_5
```

## Source note 10, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L107)

```text
// On the host, green bits in blue, blue bits in green.
```

## Source note 11, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L111)

```text
// k_8_8_8_8
```

## Source note 12, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L115)

```text
// k_2_10_10_10
```

## Source note 13, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L119)

```text
// k_8_A
```

## Source note 14, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L123)

```text
// k_8_B
```

## Source note 15, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L127)

```text
// k_8_8
```

## Source note 16, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L131)

```text
// k_Cr_Y1_Cb_Y0_REP
```

## Source note 17, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L132)

```text
// Red and blue swapped in the load shader for simplicity.
```

## Source note 18, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L137)

```text
// k_Y1_Cr_Y0_Cb_REP
```

## Source note 19, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L138)

```text
// Red and blue swapped in the load shader for simplicity.
```

## Source note 20, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L143)

```text
// k_16_16_EDRAM
```

## Source note 21, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L144)

```text
// Not usable as a texture, also has -32...32 range.
```

## Source note 22, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L148)

```text
// k_8_8_8_8_A
```

## Source note 23, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L152)

```text
// k_4_4_4_4
```

## Source note 24, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L153)

```text
// Red and blue swapped in the load shader for simplicity.
```

## Source note 25, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L157)

```text
// k_10_11_11
```

## Source note 26, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L162)

```text
// k_11_11_10
```

## Source note 27, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L167)

```text
// k_DXT1
```

## Source note 28, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L171)

```text
// k_DXT2_3
```

## Source note 29, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L175)

```text
// k_DXT4_5
```

## Source note 30, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L179)

```text
// k_16_16_16_16_EDRAM
```

## Source note 31, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L180)

```text
// Not usable as a texture, also has -32...32 range.
```

## Source note 32, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L184)

```text
// R32_FLOAT for depth because shaders would require an additional SRV to
```

## Source note 33, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L185)

```text
// sample stencil, which we don't provide.
```

## Source note 34, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L186)

```text
// k_24_8
```

## Source note 35, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L190)

```text
// k_24_8_FLOAT
```

## Source note 36, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L194)

```text
// k_16
```

## Source note 37, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L198)

```text
// k_16_16
```

## Source note 38, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L202)

```text
// k_16_16_16_16
```

## Source note 39, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L206)

```text
// k_16_EXPAND
```

## Source note 40, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L210)

```text
// k_16_16_EXPAND
```

## Source note 41, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L214)

```text
// k_16_16_16_16_EXPAND
```

## Source note 42, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L218)

```text
// k_16_FLOAT
```

## Source note 43, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L222)

```text
// k_16_16_FLOAT
```

## Source note 44, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L226)

```text
// k_16_16_16_16_FLOAT
```

## Source note 45, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L230)

```text
// k_32
```

## Source note 46, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L234)

```text
// k_32_32
```

## Source note 47, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L238)

```text
// k_32_32_32_32
```

## Source note 48, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L242)

```text
// k_32_FLOAT
```

## Source note 49, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L246)

```text
// k_32_32_FLOAT
```

## Source note 50, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L250)

```text
// k_32_32_32_32_FLOAT
```

## Source note 51, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L254)

```text
// k_32_AS_8
```

## Source note 52, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L258)

```text
// k_32_AS_8_8
```

## Source note 53, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L262)

```text
// k_16_MPEG
```

## Source note 54, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L266)

```text
// k_16_16_MPEG
```

## Source note 55, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L270)

```text
// k_8_INTERLACED
```

## Source note 56, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L274)

```text
// k_32_AS_8_INTERLACED
```

## Source note 57, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L278)

```text
// k_32_AS_8_8_INTERLACED
```

## Source note 58, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L282)

```text
// k_16_INTERLACED
```

## Source note 59, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L286)

```text
// k_16_MPEG_INTERLACED
```

## Source note 60, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L290)

```text
// k_16_16_MPEG_INTERLACED
```

## Source note 61, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L298)

```text
// k_8_8_8_8_AS_16_16_16_16
```

## Source note 62, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L302)

```text
// k_DXT1_AS_16_16_16_16
```

## Source note 63, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L306)

```text
// k_DXT2_3_AS_16_16_16_16
```

## Source note 64, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L310)

```text
// k_DXT4_5_AS_16_16_16_16
```

## Source note 65, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L314)

```text
// k_2_10_10_10_AS_16_16_16_16
```

## Source note 66, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L318)

```text
// k_10_11_11_AS_16_16_16_16
```

## Source note 67, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L323)

```text
// k_11_11_10_AS_16_16_16_16
```

## Source note 68, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L328)

```text
// k_32_32_32_FLOAT
```

## Source note 69, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L332)

```text
// k_DXT3A
```

## Source note 70, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L333)

```text
// R8_UNORM has the same size as BC2, but doesn't have the 4x4 size
```

## Source note 71, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L334)

```text
// alignment requirement.
```

## Source note 72, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L338)

```text
// k_DXT5A
```

## Source note 73, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L342)

```text
// k_CTX1
```

## Source note 74, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L346)

```text
// k_DXT3A_AS_1_1_1_1
```

## Source note 75, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L350)

```text
// k_8_8_8_8_GAMMA_EDRAM
```

## Source note 76, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L351)

```text
// Not usable as a texture.
```

## Source note 77, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L355)

```text
// k_2_10_10_10_FLOAT_EDRAM
```

## Source note 78, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L356)

```text
// Not usable as a texture.
```

## Source note 79, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L373)

```text
// While the texture descriptor cache still exists (referenced by
```

## Source note 80, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L374)

```text
// ~D3D12Texture), destroy all textures.
```

## Source note 81, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L377)

```text
// First release the buffers to detach them from the heaps.
```

## Source note 82, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L391)

```text
// Buffers not used yet - no need aliasing barriers to change ownership of
```

## Source note 83, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L392)

```text
// gigabytes between even and odd buffers.
```

## Source note 84, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L404)

```text
// Create the loading root signature.
```

## Source note 85, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L406)

```text
// Parameter 0 is constants (changed multiple times when untiling).
```

## Source note 86, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L412)

```text
// Parameter 1 is the source (may be changed multiple times for the same
```

## Source note 87, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L413)

```text
// destination).
```

## Source note 88, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L424)

```text
// Parameter 2 is the destination.
```

## Source note 89, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L450)

```text
// Specify the load shader code.
```

## Source note 90, line 556

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L556)

```text
// Create the loading pipelines.
```

## Source note 91, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L592)

```text
// Create a heap with null SRV descriptors, since it's faster to copy a
```

## Source note 92, line 593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L593)

```text
// descriptor than to create an SRV, and null descriptors are used a lot (for
```

## Source note 93, line 594

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L594)

```text
// the signed version when only unsigned is used, for instance).
```

## Source note 94, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L647)

```text
// Clear texture descriptor cache.
```

## Source note 95, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L656)

```text
// ExecuteCommandLists is a full UAV and aliasing barrier.
```

## Source note 96, line 677

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L677)

```text
// Report used unsupported texture formats.
```

## Source note 97, line 703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L703)

```text
// Pre-create 3D-as-2D wrappers before draw setup. Wrapper loading may bind
```

## Source note 98, line 704

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L704)

```text
// compute pipelines and must happen in the texture request phase.
```

## Source note 99, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L727)

```text
// Transition the textures to the needed usage - always in
```

## Source note 100, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L728)

```text
// NON_PIXEL_SHADER_RESOURCE | PIXEL_SHADER_RESOURCE states because barriers
```

## Source note 101, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L729)

```text
// between read-only stages, if needed, are discouraged (also if these were
```

## Source note 102, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L730)

```text
// tracked separately, checks would be needed to make sure, if the same
```

## Source note 103, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L731)

```text
// texture is bound through different fetch constants to both VS and PS, it
```

## Source note 104, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L732)

```text
// would be in both states).
```

## Source note 105, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L743)

```text
// Will be referenced by the command list, so mark as used.
```

## Source note 106, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L816)

```text
// Not supporting signed compressed textures - hopefully DXN and DXT5A are
```

## Source note 107, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L817)

```text
// not used as signed.
```

## Source note 108, line 1009

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1009)

```text
/* kRepeat               */
```

## Source note 109, line 1010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1010)

```text
/* kMirroredRepeat       */
```

## Source note 110, line 1011

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1011)

```text
/* kClampToEdge          */
```

## Source note 111, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1012)

```text
/* kMirrorClampToEdge    */
```

## Source note 112, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1013)

```text
// No GL_CLAMP (clamp to half edge, half border) equivalent in Direct3D
```

## Source note 113, line 1014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1014)

```text
// 12, but there's no Direct3D 9 equivalent anyway, and too weird to be
```

## Source note 114, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1015)

```text
// suitable for intentional real usage.
```

## Source note 115, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1016)

```text
/* kClampToHalfway       */
```

## Source note 116, line 1017

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1017)

```text
// No mirror and clamp to border equivalents in Direct3D 12, but they
```

## Source note 117, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1018)

```text
// aren't there in Direct3D 9 either.
```

## Source note 118, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1019)

```text
/* kMirrorClampToHalfway */
```

## Source note 119, line 1020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1020)

```text
/* kClampToBorder        */
```

## Source note 120, line 1021

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1021)

```text
/* kMirrorClampToBorder  */
```

## Source note 121, line 1026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1026)

```text
// LOD biasing is performed in shaders.
```

## Source note 122, line 1058

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1058)

```text
// "It is undefined whether LOD clamping based on MinLOD and MaxLOD Sampler
```

## Source note 123, line 1059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1059)

```text
// states should happen before or after deciding if magnification is
```

## Source note 124, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1060)

```text
// occuring" - Direct3D 11.3 Functional Specification.
```

## Source note 125, line 1061

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1061)

```text
// Using the GL_NEAREST / GL_LINEAR minification filter emulation logic
```

## Source note 126, line 1062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1062)

```text
// described in the Vulkan VkSamplerCreateInfo specification, preserving
```

## Source note 127, line 1063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1063)

```text
// magnification vs. minification - point mip sampling (usable only without
```

## Source note 128, line 1064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1064)

```text
// anisotropic filtering on Direct3D 12) and MaxLOD 0.25. With anisotropic
```

## Source note 129, line 1065

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1065)

```text
// filtering, magnification vs. minification doesn't matter as the filter is
```

## Source note 130, line 1066

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1066)

```text
// always linear for both on Direct3D 12 - but linear filtering specifically
```

## Source note 131, line 1067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1067)

```text
// is what must not be done for kBaseMap, so setting MaxLOD to MinLOD.
```

## Source note 132, line 1074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1074)

```text
// Maximum mip level is in the texture resource itself.
```

## Source note 133, line 1090

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1090)

```text
// Limit to the virtual address space available for a resource.
```

## Source note 134, line 1098

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1098)

```text
// When reducing from a square size, prefer decreasing the horizontal
```

## Source note 135, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1099)

```text
// resolution as vertical resolution difference is visible more clearly in
```

## Source note 136, line 1100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1100)

```text
// perspective.
```

## Source note 137, line 1121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1121)

```text
// Exceeds the physical address space.
```

## Source note 138, line 1136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1136)

```text
// Ensure GPU virtual memory for buffers that may be used to access the range
```

## Source note 139, line 1137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1137)

```text
// is allocated - buffers are created. Always creating both buffers for all
```

## Source note 140, line 1138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1138)

```text
// addresses before creating the heaps so when creating a new buffer, it can
```

## Source note 141, line 1139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1139)

```text
// be safely assumed that no existing heaps should be mapped to it.
```

## Source note 142, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1150)

```text
// Buffer indices are gigabytes.
```

## Source note 143, line 1157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1157)

```text
// The first access will be a resolve.
```

## Source note 144, line 1232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1232)

```text
// If length is 0, the needed buffer can't be chosen because no buffer is
```

## Source note 145, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1233)

```text
// needed.
```

## Source note 146, line 1245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1245)

```text
// Get one or two buffers that can hold the whole range.
```

## Source note 147, line 1274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1274)

```text
// Too wide range requested - no buffer that contains both the start and the
```

## Source note 148, line 1275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1275)

```text
// end.
```

## Source note 149, line 1282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1282)

```text
// Choose the buffer that the range will be accessed through.
```

## Source note 150, line 1285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1285)

```text
// Prefer the buffer that is already used to make less aliasing barriers.
```

## Source note 151, line 1299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1299)

```text
// The range can be accessed only by one buffer.
```

## Source note 152, line 1303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1303)

```text
// Switch the current buffer for the range.
```

## Source note 153, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1319)

```text
// An aliasing barrier synchronizes and flushes everything.
```

## Source note 154, line 1381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1381)

```text
// The swap texture is likely to be used only for the presentation compute
```

## Source note 155, line 1382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1382)

```text
// shader, and not during emulation, where it'd be NON_PIXEL_SHADER_RESOURCE |
```

## Source note 156, line 1383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1383)

```text
// PIXEL_SHADER_RESOURCE.
```

## Source note 157, line 1397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1397)

```text
// Only texture->key, not the result of BindingInfoFromFetchConstant, contains
```

## Source note 158, line 1398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1398)

```text
// whether the texture is scaled.
```

## Source note 159, line 1439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1439)

```text
// UnalignedBlockTexturesSupported is for block-compressed textures with the
```

## Source note 160, line 1440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1440)

```text
// block size of 4x4, but not for 2x1 (4:2:2) subsampled formats.
```

## Source note 161, line 1471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1471)

```text
// Dense cache-line-aligned swizzle array avoids cache misses from accessing
```

## Source note 162, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1472)

```text
// the full HostFormat struct on every texture fetch.
```

## Source note 163, line 1487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1487)

```text
// 1D and 2D are emulated as 2D arrays.
```

## Source note 164, line 1504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1504)

```text
// 1D and 2D are emulated as 2D arrays.
```

## Source note 165, line 1526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1526)

```text
// 1D textures are treated as 2D for simplicity.
```

## Source note 166, line 1541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1541)

```text
// Untiling through a buffer instead of using unordered access because copying
```

## Source note 167, line 1542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1542)

```text
// is not done that often.
```

## Source note 168, line 1546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1546)

```text
// Assuming untiling will be the next operation.
```

## Source note 169, line 1565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1565)

```text
// Get the pipeline.
```

## Source note 170, line 1579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1579)

```text
// Get the guest layout.
```

## Source note 171, line 1603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1603)

```text
// The loop counter can mean two things depending on whether the packed mip
```

## Source note 172, line 1604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1604)

```text
// tail is stored as mip 0, because in this case, it would be ambiguous since
```

## Source note 173, line 1605

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1605)

```text
// both the base and the mips would be on "level 0", but stored in separate
```

## Source note 174, line 1606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1606)

```text
// places.
```

## Source note 175, line 1609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1609)

```text
// Packed mip tail is the level 0 - may need to load mip tails for the base,
```

## Source note 176, line 1610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1610)

```text
// the mips, or both.
```

## Source note 177, line 1611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1611)

```text
// Loop iteration 0 - base packed mip tail.
```

## Source note 178, line 1612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1612)

```text
// Loop iteration 1 - mips packed mip tail.
```

## Source note 179, line 1616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1616)

```text
// Packed mip tail is not the level 0.
```

## Source note 180, line 1617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1617)

```text
// Loop iteration is the actual level being loaded.
```

## Source note 181, line 1622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1622)

```text
// Get the host layout and the buffer.
```

## Source note 182, line 1630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1630)

```text
// Decompressing guest blocks.
```

## Source note 183, line 1636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1636)

```text
// Indexing is the same as for guest stored mips:
```

## Source note 184, line 1637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1637)

```text
// 1...min(level_last, level_packed) if level_packed is not 0, or only 0 if
```

## Source note 185, line 1638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1638)

```text
// level_packed == 0.
```

## Source note 186, line 1642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1642)

```text
// Using custom calculations instead of GetCopyableFootprints because
```

## Source note 187, line 1643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1643)

```text
// shaders may unconditionally copy multiple blocks along X per thread for
```

## Source note 188, line 1644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1644)

```text
// simplicity, to make sure all rows (also including the last one -
```

## Source note 189, line 1645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1645)

```text
// GetCopyableFootprints aligns row offsets, but not the total size) are
```

## Source note 190, line 1646

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1646)

```text
// properly padded to the number of blocks copied in an invocation without
```

## Source note 191, line 1647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1647)

```text
// implicit assumptions about D3D12_TEXTURE_DATA_PITCH_ALIGNMENT.
```

## Source note 192, line 1657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1657)

```text
// Loading the packed tail for the base or the mips - load the whole tail
```

## Source note 193, line 1658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1658)

```text
// to copy regions out of it.
```

## Source note 194, line 1695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1695)

```text
// Begin loading.
```

## Source note 195, line 1696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1696)

```text
// May use different buffers for scaled base and mips, and also addressability
```

## Source note 196, line 1697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1697)

```text
// of more than 128 * 2^20 (2^D3D12_REQ_BUFFER_RESOURCE_TEXEL_COUNT_2_TO_EXP)
```

## Source note 197, line 1698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1698)

```text
// texels is not mandatory - need two separate UAV descriptors for base and
```

## Source note 198, line 1699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1699)

```text
// mips.
```

## Source note 199, line 1700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1700)

```text
// Destination.
```

## Source note 200, line 1703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1703)

```text
// Source - base and mips, one or both.
```

## Source note 201, line 1706

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1706)

```text
// Source - shared memory.
```

## Source note 202, line 1720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1720)

```text
// Set up the destination descriptor.
```

## Source note 203, line 1729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1729)

```text
// Set up the unscaled source descriptor (scaled needs two descriptors that
```

## Source note 204, line 1730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1730)

```text
// depend on the buffer being current, so they will be set later - for mips,
```

## Source note 205, line 1731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1731)

```text
// after loading the base is done).
```

## Source note 206, line 1748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1748)

```text
// Submit the copy buffer population commands.
```

## Source note 207, line 1752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1752)

```text
// 3 bits for each.
```

## Source note 208, line 1760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1760)

```text
// The loop is slices within levels because the base and the levels may need
```

## Source note 209, line 1761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1761)

```text
// different portions of the scaled resolve virtual address space to be
```

## Source note 210, line 1762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1762)

```text
// available through buffers, and to create a descriptor, the buffer start
```

## Source note 211, line 1763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1763)

```text
// address is required - which may be different for base and mips.
```

## Source note 212, line 1772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1772)

```text
// Set up the base or mips source, also making it accessible if loading from
```

## Source note 213, line 1773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1773)

```text
// scaled resolve memory.
```

## Source note 214, line 1795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1795)

```text
// Offset already applied in the buffer because more than 512 MB can't be
```

## Source note 215, line 1796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1796)

```text
// directly addresses as R32 on some hardware (above
```

## Source note 216, line 1797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1797)

```text
// 2^D3D12_REQ_BUFFER_RESOURCE_TEXEL_COUNT_2_TO_EXP).
```

## Source note 217, line 1810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1810)

```text
// Shaders expect pitch in blocks for tiled textures.
```

## Source note 218, line 1821

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1821)

```text
// This is the packed mip tail, containing not only the specified level,
```

## Source note 219, line 1822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1822)

```text
// but also other levels at different offsets - load the entire needed
```

## Source note 220, line 1823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1823)

```text
// extents.
```

## Source note 221, line 1876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1876)

```text
// Update LRU caching because the texture will be used by the command list.
```

## Source note 222, line 1879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L1879)

```text
// Submit copying from the copy buffer to the host texture.
```

## Source note 223, line 2042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2042)

```text
// Try to find an existing descriptor.
```

## Source note 224, line 2052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2052)

```text
// Create a new bindless or cached descriptor if supported.
```

## Source note 225, line 2057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2057)

```text
// Not the version with the needed signedness.
```

## Source note 226, line 2062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2062)

```text
// Not supporting signed compressed textures - hopefully DXN and DXT5A are
```

## Source note 227, line 2063

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2063)

```text
// not used as signed.
```

## Source note 228, line 2137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2137)

```text
// Allocated + 1 (including the descriptor that is being added), rounded
```

## Source note 229, line 2138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2138)

```text
// up to kSRVDescriptorCachePageSize, (allocated + 1 + size - 1).
```

## Source note 230, line 2191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2191)

```text
// No GL_CLAMP (clamp to half edge, half border) equivalent in Direct3D 12,
```

## Source note 231, line 2192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2192)

```text
// but there's no Direct3D 9 equivalent anyway, and too weird to be suitable
```

## Source note 232, line 2193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2193)

```text
// for intentional real usage.
```

## Source note 233, line 2198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2198)

```text
// No Direct3D 12 equivalents.
```

## Source note 234, line 2204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/d3d12/texture_cache.cpp#L2204)

```text
// namespace rex::graphics::d3d12
```
