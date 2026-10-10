# Xenos: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/xenos.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L25)

```text
// enum types used in the GPU registers or the microcode must be : uint32_t or
```

## Source note 2, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L26)

```text
// : int32_t, as Visual C++ restarts bit field packing when a field requires
```

## Source note 3, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L27)

```text
// different alignment than the previous one, so only 32-bit types must be used
```

## Source note 4, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L28)

```text
// in bit fields (registers are 32-bit, and the microcode consists of triples of
```

## Source note 5, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L29)

```text
// 32-bit words).
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L38)

```text
// Only the lower 24 bits of the vertex index are used (tested on an Adreno 200
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L39)

```text
// phone using a GL_UNSIGNED_INT element array buffer with junk in the upper 8
```

## Source note 8, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L40)

```text
// bits that had no effect on drawing).
```

## Source note 9, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L59)

```text
// Starting with this primitive type, explicit major mode is assumed (in the
```

## Source note 10, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L60)

```text
// R6xx/R7xx registers, k2DCopyRectListV0 is 22, and implicit major mode is
```

## Source note 11, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L61)

```text
// only used for primitive types 0 through 21) - and tessellation patches use
```

## Source note 12, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L62)

```text
// the range that starts from k2DCopyRectListV0.
```

## Source note 13, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L74)

```text
// Tessellation patches when VGT_OUTPUT_PATH_CNTL::path_select is
```

## Source note 14, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L75)

```text
// VGTOutputPath::kTessellationEnable. The vertex shader receives the patch
```

## Source note 15, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L76)

```text
// index rather than control point indices.
```

## Source note 16, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L77)

```text
// With non-adaptive tessellation, VGT_DRAW_INITIATOR::num_indices is the
```

## Source note 17, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L78)

```text
// patch count (4D5307F1 draws single ground patches by passing 1 as the index
```

## Source note 18, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L79)

```text
// count). VGT_INDX_OFFSET is also applied to the patch index - 4D5307F1 uses
```

## Source note 19, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L80)

```text
// auto-indexed patches with a nonzero VGT_INDX_OFFSET, which contains the
```

## Source note 20, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L81)

```text
// base patch index there.
```

## Source note 21, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L82)

```text
// With adaptive tessellation, however, num_indices is the number of
```

## Source note 22, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L83)

```text
// tessellation factors in the "index buffer" reused for tessellation factors,
```

## Source note 23, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L84)

```text
// which is the patch count multiplied by the edge count (if num_indices is
```

## Source note 24, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L85)

```text
// multiplied further by 4 for quad patches for the ground in 4D5307F2, for
```

## Source note 25, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L86)

```text
// example, some incorrect patches are drawn, so Xenia shouldn't do that; also
```

## Source note 26, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L87)

```text
// 4D5307E6 draws water triangle patches with the number of indices that is 3
```

## Source note 27, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L88)

```text
// times the invocation count of the memexporting shader that calculates the
```

## Source note 28, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L89)

```text
// tessellation factors for a single patch for each "point").
```

## Source note 29, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L95)

```text
// For the texture fetch constant (not the tfetch instruction), stacked stored
```

## Source note 30, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L96)

```text
// as 2D.
```

## Source note 31, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L119)

```text
// TEX_FORMAT_COMP, known as GPUSIGN on the Xbox 360.
```

## Source note 32, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L122)

```text
// Two's complement texture data.
```

## Source note 33, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L124)

```text
// 2*color-1 - https://xboxforums.create.msdn.com/forums/t/107374.aspx
```

## Source note 34, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L126)

```text
// Linearized when sampled.
```

## Source note 35, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L133)

```text
// Only applicable to the mip filter - like OpenGL minification filters
```

## Source note 36, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L134)

```text
// GL_NEAREST / GL_LINEAR without MIPMAP_NEAREST / MIPMAP_LINEAR.
```

## Source note 37, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L150)

```text
// (0.0, 0.0, 0.0)
```

## Source note 38, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L153)

```text
// (1.0, 1.0, 1.0, 1.0)
```

## Source note 39, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L155)

```text
// Unknown precisely, but likely (0.5, 0.0, 0.5) for unsigned (Cr, Y, Cb)
```

## Source note 40, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L158)

```text
// Unknown precisely, but likely (0.0, 0.5, 0.5) for unsigned (Y, Cr, Cb)
```

## Source note 41, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L163)

```text
// For the tfetch instruction (not the fetch constant) and related instructions,
```

## Source note 42, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L164)

```text
// stacked accessed using tfetch3D.
```

## Source note 43, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L210)

```text
// Not very common, but used for some world draws in 545407E0.
```

## Source note 44, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L214)

```text
// SurfaceNumberX from yamato_enum.h.
```

## Source note 45, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L217)

```text
// Microsoft-style, scale factor (2^(n-1))-1.
```

## Source note 46, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L224)

```text
// The EDRAM is an opaque block of memory accessible by the RB (render backend)
```

## Source note 47, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L225)

```text
// pipeline stage of the GPU, which performs output-merger functionality (color
```

## Source note 48, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L226)

```text
// render target writing and blending, depth and stencil testing) and resolve
```

## Source note 49, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L227)

```text
// (copy) operations.
```

## Source note 50, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L229)

```text
// Data in the 10 MiB of EDRAM is laid out as 2048 tiles on 80x16 32bpp MSAA
```

## Source note 51, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L230)

```text
// samples. With 2x MSAA, one pixel consists of 1x2 samples, and with 4x, it
```

## Source note 52, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L231)

```text
// consists of 2x2 samples. Thus, for a 32bpp render target, one tile contains
```

## Source note 53, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L232)

```text
// 80x16 pixels without MSAA, samples of 80x8 pixels with 2x MSAA, or samples of
```

## Source note 54, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L233)

```text
// 40x8 pixels with 4x MSAA. The base is specified in tiles, the pitch is also
```

## Source note 55, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L234)

```text
// treated as tiles (so a 256x single-sampled surface will be stored in the
```

## Source note 56, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L235)

```text
// EDRAM as 320x).
```

## Source note 57, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L237)

```text
// XGSurfaceSize code in game executables calculates the size in tiles in the
```

## Source note 58, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L238)

```text
// following order:
```

## Source note 59, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L239)

```text
// 1) If MSAA is >=2x, multiply the height by 2.
```

## Source note 60, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L240)

```text
// 2) If MSAA is 4x, multiply the width by 2.
```

## Source note 61, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L241)

```text
// 3) 80x16-align width and height in samples.
```

## Source note 62, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L242)

```text
// 4) Multiply width*height in samples by 4 or 8 depending on the pixel format.
```

## Source note 63, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L243)

```text
// 5) Divide the byte size by 5120.
```

## Source note 64, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L244)

```text
// This means that when working with layout of surfaces in the EDRAM, it should
```

## Source note 65, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L245)

```text
// be assumed that a multisampled surface is the same as a single-sampled
```

## Source note 66, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L246)

```text
// surface with 2x height and (with 4x MSAA) width - however, format size
```

## Source note 67, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L247)

```text
// doesn't effect the dimensions, 64bpp surfaces take twice as many tiles as
```

## Source note 68, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L248)

```text
// 32bpp surfaces.
```

## Source note 69, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L250)

```text
// From this, it follows that the tile row pitch in tiles can be multiplied by
```

## Source note 70, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L251)

```text
// 64bpp too. In the formula for calculating the tile count:
```

## Source note 71, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L252)

```text
// (height rounded up to 16) * (width rounded up to 80) * (4 or 8) / 5120
```

## Source note 72, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L253)

```text
// the fraction can be reduced because the numerator is always divisible by
```

## Source note 73, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L254)

```text
// 5120 - it changes in 80 * 16 * 4 = 5120 increments - in tile increments -
```

## Source note 74, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L255)

```text
// resulting in:
```

## Source note 75, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L256)

```text
// (height in tiles) * (width in tiles) * (1 or 2)
```

## Source note 76, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L257)

```text
// Here we get only multiplication, which (disregarding the variable size) is
```

## Source note 77, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L258)

```text
// associative for integers, so:
```

## Source note 78, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L259)

```text
// ((height in tiles) * (width in tiles)) * (1 or 2)
```

## Source note 79, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L260)

```text
// is identical to:
```

## Source note 80, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L261)

```text
// (height in tiles) * ((width in tiles) * (1 or 2))
```

## Source note 81, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L263)

```text
// Depth surfaces are also stored as 32bpp tiles, however, as opposed to color
```

## Source note 82, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L264)

```text
// surfaces, 40x16-sample halves of each tile are swapped - game shaders (for
```

## Source note 83, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L265)

```text
// example, in 4D5307E6 main menu, 545407F2) perform this swapping when writing
```

## Source note 84, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L266)

```text
// specific depth/stencil values by drawing to a depth buffer's memory through a
```

## Source note 85, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L267)

```text
// color render target (to reupload a depth/stencil surface previously evicted
```

## Source note 86, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L268)

```text
// from the EDRAM to the main memory, for instance).
```

## Source note 87, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L270)

```text
// EDRAM addressing is circular - a render target may be backed by a EDRAM range
```

## Source note 88, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L271)

```text
// that extends beyond 2048 tiles, in which case, what would go to the tile 2048
```

## Source note 89, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L272)

```text
// will actually be in tile 0, tile 2049 will go to tile 1, and so on. 4D5307F1
```

## Source note 90, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L273)

```text
// heavily relies on this behavior for its depth buffer. Specifically, it's used
```

## Source note 91, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L274)

```text
// the following way:
```

## Source note 92, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L275)

```text
// - First, a depth-only 1120x720 2xMSAA pass is performed with the depth buffer
```

## Source note 93, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L276)

```text
//   in tiles [1008, 2268), or [1008, 2048) and [0, 220).
```

## Source note 94, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L277)

```text
// - Then, the depth buffer in [1008, 2268) is resolved into a texture, later
```

## Source note 95, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L278)

```text
//   used in screen-space effects.
```

## Source note 96, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L279)

```text
// - The upper 1120x576 bin is drawn into the color buffer in [0, 1008), using
```

## Source note 97, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L280)

```text
//   the [1008, 2016) portion of the previously populated depth buffer for early
```

## Source note 98, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L281)

```text
//   depth testing (there seems to be no true early Z on the Xenos, only early
```

## Source note 99, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L282)

```text
//   hi-Z, but still it possibly needs to be in sync with the per-sample depth
```

## Source note 100, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L283)

```text
//   buffer), and overwriting the tail of the previously filled depth buffer in
```

## Source note 101, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L284)

```text
//   [0, 220).
```

## Source note 102, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L285)

```text
// - The lower 1120x144 bin is drawn without the pregenerated depth buffer data.
```

## Source note 103, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L302)

```text
// 7e3 [0, 32) RGB, unorm alpha.
```

## Source note 104, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L303)

```text
// http://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/eg05-xenos-doggett.pdf
```

## Source note 105, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L305)

```text
// Fixed point -32...32.
```

## Source note 106, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L306)

```text
// http://www.students.science.uu.nl/~3220516/advancedgraphics/papers/inferred_lighting.pdf
```

## Source note 107, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L308)

```text
// Fixed point -32...32.
```

## Source note 108, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L313)

```text
// 16-bit fixed point at half speed, with full blending.
```

## Source note 109, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L314)

```text
// http://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/unc-xenos-doggett.pdf
```

## Source note 110, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L351)

```text
// Returns the version of the format with the same packing and meaning of values
```

## Source note 111, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L352)

```text
// stored in it, but without blending precision modifiers.
```

## Source note 112, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L366)

```text
// 20e4 [0, 2).
```

## Source note 113, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L375)

```text
// Converts Xenos floating-point 7e3 color value in bits 0:9 (not clamping) to
```

## Source note 114, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L376)

```text
// an IEEE-754 32-bit floating-point number.
```

## Source note 115, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L378)

```text
// Converts 24-bit unorm depth in the value (not clamping) to an IEEE-754 32-bit
```

## Source note 116, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L379)

```text
// floating-point number.
```

## Source note 117, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L380)

```text
// Converts an IEEE-754 32-bit floating-point number to Xenos floating-point
```

## Source note 118, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L381)

```text
// depth, rounding to the nearest even or towards zero.
```

## Source note 119, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L383)

```text
// Converts Xenos floating-point depth in bits 0:23 (not clamping) to an
```

## Source note 120, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L384)

```text
// IEEE-754 32-bit floating-point number.
```

## Source note 121, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L386)

```text
// Converts 24-bit unorm depth in the value (not clamping) to an IEEE-754 32-bit
```

## Source note 122, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L387)

```text
// floating-point number.
```

## Source note 123, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L389)

```text
// Not 1.0f / 16777215.0f as that gives an incorrect result (like for a very
```

## Source note 124, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L390)

```text
// common 0xC00000 which clears 2_10_10_10 to 0001). Division by 2^24 is just
```

## Source note 125, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L391)

```text
// an exponent shift though, thus exact.
```

## Source note 126, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L392)

```text
// Division by 16777215.0f behaves this way.
```

## Source note 127, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L396)

```text
// Scale for conversion of slope scales from PA_SU_POLY_OFFSET_FRONT/BACK_SCALE
```

## Source note 128, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L397)

```text
// units to those used when the slope is computed from the difference between
```

## Source note 129, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L398)

```text
// adjacent pixels, for conversion from the guest to common host APIs or to
```

## Source note 130, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L399)

```text
// calculation using max(|ddx(z)|, |ddy(z)|).
```

## Source note 131, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L400)

```text
// "slope computed in subpixels (1/12 or 1/16)" - R5xx Acceleration.
```

## Source note 132, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L401)

```text
// But the correct scale for conversion of the slope scale from subpixels to
```

## Source note 133, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L402)

```text
// pixels is likely 1/16 according to:
```

## Source note 134, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L403)

```text
// https://github.com/mesa3d/mesa/blob/54ad9b444c8e73da498211870e785239ad3ff1aa/src/gallium/drivers/radeonsi/si_state.c#L946
```

## Source note 135, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L417)

```text
// RB_SURFACE_INFO::surface_pitch width.
```

## Source note 136, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L419)

```text
// The part of RB_COLOR_INFO::color_base and RB_DEPTH_INFO::depth_base width
```

## Source note 137, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L420)

```text
// usable on the Xenos, which has periodic 11-bit EDRAM tile addressing.
```

## Source note 138, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L433)

```text
// log2_ceil of the maximum value of GetSurfacePitchTiles, assuming 16383 being
```

## Source note 139, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L434)

```text
// the maximum pitch in pixels (not sure about the validity of values above
```

## Source note 140, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L435)

```text
// 8192, but to avoid bounds checking).
```

## Source note 141, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L436)

```text
// log2_ceil of 16383, multiplied by 2 for 4x MSAA, rounded to 80 samples,
```

## Source note 142, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L437)

```text
// multiplied by 2 for 64bpp.
```

## Source note 143, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L442)

```text
// a2xx_sq_surfaceformat +
```

## Source note 144, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L443)

```text
// https://github.com/indirivacua/RAGE-Console-Texture-Editor/blob/master/Console.Xbox360.Graphics.pas
```

## Source note 145, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L453)

```text
// Possibly similar to k_8, but may be storing alpha instead of red when
```

## Source note 146, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L454)

```text
// resolving/memexporting, though not exactly known. From the point of view of
```

## Source note 147, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L455)

```text
// sampling, it should be treated the same as k_8 (given that textures have
```

## Source note 148, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L456)

```text
// the last - and single-component textures have the only - component
```

## Source note 149, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L457)

```text
// replicated into all the remaining ones before the swizzle).
```

## Source note 150, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L458)

```text
// Used as:
```

## Source note 151, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L459)

```text
// - Texture in 4B4E083C - text, starting from the "Loading..." and the "This
```

## Source note 152, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L460)

```text
//   game saves data automatically" messages. The swizzle in the fetch
```

## Source note 153, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L461)

```text
//   constant is 111W (suggesting that internally the only component may be
```

## Source note 154, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L462)

```text
//   the alpha one, not red).
```

## Source note 155, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L467)

```text
// Though it's unknown what exactly REP means, likely it's "repeating
```

## Source note 156, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L468)

```text
// fraction" (the term used for normalized fixed-point formats, UNORM in
```

## Source note 157, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L469)

```text
// particular for unsigned signedness - 0.0 to 1.0 range, like in
```

## Source note 158, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L470)

```text
// Direct3D 10+, unlike the 0.0 to 255.0 range for D3DFMT_R8G8_B8G8 and
```

## Source note 159, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L471)

```text
// D3DFMT_G8R8_G8B8 in Direct3D 9). 54540829 uses k_Y1_Cr_Y0_Cb_REP directly
```

## Source note 160, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L472)

```text
// as UNORM.
```

## Source note 161, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L474)

```text
// Used for videos in 54540829.
```

## Source note 162, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L477)

```text
// Likely same as k_8_8_8_8.
```

## Source note 163, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L478)

```text
// Used as:
```

## Source note 164, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L479)

```text
// - Memexport destination in 4D5308BC - multiple small draws when looking
```

## Source note 165, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L480)

```text
//   back at the door behind the player in the first room of gameplay.
```

## Source note 166, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L481)

```text
// - Memexport destination in 4D53085B and 4D530919 - in 4D53085B, in a frame
```

## Source note 167, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L482)

```text
//   between the intro video and the main menu, in a 8192-point draw.
```

## Source note 168, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L535)

```text
// Subset of a2xx_sq_surfaceformat - formats that RTs can be resolved to.
```

## Source note 169, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L565)

```text
// Resolve writes unsigned data for fixed-point formats (so k_16_16 and
```

## Source note 170, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L566)

```text
// k_16_16_16_16 render target formats, which are signed and also have a
```

## Source note 171, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L567)

```text
// different range, are not equivalent to the respective texture formats).
```

## Source note 172, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L572)

```text
// Shaders fetch data copied from k_8_8_8_8_GAMMA with TextureSign::kGamma.
```

## Source note 173, line 715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L715)

```text
// SRC1 added on Adreno.
```

## Source note 174, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L733)

```text
// VGT_DRAW_INITIATOR::DI_SRC_SEL_*
```

## Source note 175, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L740)

```text
// VGT_DRAW_INITIATOR::DI_MAJOR_MODE_*
```

## Source note 176, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L752)

```text
// Microsoft-style representation with two -1 representations (one is slightly
```

## Source note 177, line 753

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L753)

```text
// past -1 but clamped).
```

## Source note 178, line 755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L755)

```text
// OpenGL "alternate mapping" format lacking representation for zero.
```

## Source note 179, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L759)

```text
// Arbitrary filter is still present in the Code Aurora Forum release of the
```

## Source note 180, line 760

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L760)

```text
// Adreno 200 programming interface, but is deprecated according to the
```

## Source note 181, line 761

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L761)

```text
// IPR2015-00325 R400 Document Library Folder History:
```

## Source note 182, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L762)

```text
//   "Change 124923 on 2003/10/03 by jhoule@jhoule_doc_lt
```

## Source note 183, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L764)

```text
//   Deprecated the ARBITRARY_FILTER fields from TFetch instr+const."
```

## Source note 184, line 778

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L778)

```text
// a2xx_sq_ps_vtx_mode
```

## Source note 185, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L786)

```text
// Vertex shader outputs are ignored (kill all primitives) - see
```

## Source note 186, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L787)

```text
// SX_MISC::MULTIPASS on R6xx/R7xx.
```

## Source note 187, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L799)

```text
// - msaa_samples is RB_SURFACE_INFO::msaa_samples.
```

## Source note 188, line 800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L800)

```text
// - sample_control is SQ_CONTEXT_MISC::sc_sample_cntl.
```

## Source note 189, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L801)

```text
// - interpolator_control_sampling_pattern is
```

## Source note 190, line 802

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L802)

```text
//   SQ_INTERPOLATOR_CNTL::sampling_pattern.
```

## Source note 191, line 803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L803)

```text
// Centroid interpolation can be tested in 5454082B. If the GPU host backend
```

## Source note 192, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L804)

```text
// implements guest MSAA properly, using host MSAA, with everything interpolated
```

## Source note 193, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L805)

```text
// at centers, the Monument Valley start screen background may have a few
```

## Source note 194, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L806)

```text
// distinctly bright pixels on the mesas/buttes, where extrapolation happens.
```

## Source note 195, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L807)

```text
// Interpolating certain values (ones that aren't used for gradient calculation,
```

## Source note 196, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L808)

```text
// not texture coordinates) at centroids fixes this issue.
```

## Source note 197, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L835)

```text
// Render triangles.
```

## Source note 198, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L836)

```text
// Send 2 sets of 3 polygons with the specified polygon type.
```

## Source note 199, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L837)

```text
// 4541096E uses 2 for triangles, which is "reserved" on R6xx and not defined
```

## Source note 200, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L838)

```text
// on Adreno 2xx, but polymode_front/back_ptype are 0 (points) in this case in
```

## Source note 201, line 839

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L839)

```text
// 4541096E, which should not be respected for non-kDualMode as the title
```

## Source note 202, line 840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L840)

```text
// wants to draw filled triangles.
```

## Source note 203, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L850)

```text
// Pixel center at vertex positions .0, like in Direct3D 9.
```

## Source note 204, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L851)

```text
// Commonly used in Xbox 360 games.
```

## Source note 205, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L853)

```text
// Pixel center at vertex positions .5, like in OpenGL.
```

## Source note 206, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L854)

```text
// Used in 415607E6.
```

## Source note 207, line 859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L859)

```text
// OpenGL.
```

## Source note 208, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L861)

```text
// Direct3D. Common in Xbox 360 games.
```

## Source note 209, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L871)

```text
// 1/256th was added in R600. On the Xbox 360, games normally use 1/16th.
```

## Source note 210, line 882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L882)

```text
// Xenos copies EDRAM contents to a tiled 2D or 3D texture (resolves - from
```

## Source note 211, line 883

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L883)

```text
// "MSAA resolve", but this name is also used for single-sampled copying) by
```

## Source note 212, line 884

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L884)

```text
// drawing primitives with the EDRAM mode EdramMode::kCopy. Pixels covered by
```

## Source note 213, line 885

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L885)

```text
// the drawn geometry are copied. It's likely that only rectangular regions can
```

## Source note 214, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L886)

```text
// be resolved.
```

## Source note 215, line 888

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L888)

```text
// Resolve operation can write color data in ColorFormat formats, with or
```

## Source note 216, line 889

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L889)

```text
// without MSAA color sample averaging, endian swap, red/blue swap, and exponent
```

## Source note 217, line 890

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L890)

```text
// bias. Depth resolving likely has a lot more restrictions, considering sample
```

## Source note 218, line 891

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L891)

```text
// averaging, red/blue swap and exponent bias would be pretty meaningless for it
```

## Source note 219, line 892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L892)

```text
// (also, Direct3D 9 specifies k_8_8_8_8 as RB_COPY_DEST_INFO::copy_dest_format
```

## Source note 220, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L893)

```text
// for depth, which is clearly not true - the right format would be k_24_8 or
```

## Source note 221, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L894)

```text
// k_24_8_FLOAT, so depth resolving likely doesn't support format conversion),
```

## Source note 222, line 895

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L895)

```text
// though endian swap is supported.
```

## Source note 223, line 897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L897)

```text
// In addition, a resolve draw may clear the region it copies (this feature is
```

## Source note 224, line 898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L898)

```text
// commonly used when going to the next tile with predicated tiling). While one
```

## Source note 225, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L899)

```text
// resolve draw call may copy just one color or depth buffer, it may clear both
```

## Source note 226, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L900)

```text
// color and depth at once (or just color or depth, or nothing) if copying a
```

## Source note 227, line 901

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L901)

```text
// color buffer (the color render target cleared is the same as the one copied -
```

## Source note 228, line 902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L902)

```text
// however, depth resolves have RB_COPY_CONTROL::copy_src_select 4, so they
```

## Source note 229, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L903)

```text
// can't clear color).
```

## Source note 230, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L905)

```text
// Direct3D 9 does resolving by drawing kRectangleList with 3 vertices with a
```

## Source note 231, line 906

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L906)

```text
// vertex shader that accepts k_32_32_FLOAT vertices with k8in32 endianness in
```

## Source note 232, line 907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L907)

```text
// SHADER_CONSTANT_FETCH_00_0, with the half-pixel offset, according to the
```

## Source note 233, line 908

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L908)

```text
// PA_SU_VTX_CNTL::pix_center setting, pre-applied to the vertices (for Direct3D
```

## Source note 234, line 909

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L909)

```text
// 9 pixel centers, 0.5 must be added to the vertex positions to get the
```

## Source note 235, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L910)

```text
// coordinates of the corners).
```

## Source note 236, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L912)

```text
// The rectangle is used for both the source render target and the destination
```

## Source note 237, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L913)

```text
// texture, according to how it's used in 4E4D07E9.
```

## Source note 238, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L915)

```text
// Direct3D 9 gives the rectangle in source render target coordinates (for
```

## Source note 239, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L916)

```text
// example, in 4D5307E6, the sniper rifle scope has a (128,64)->(448,256)
```

## Source note 240, line 917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L917)

```text
// rectangle). It doesn't adjust the EDRAM base pointer, otherwise (taking into
```

## Source note 241, line 918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L918)

```text
// account that 4x MSAA is used for the scope) it would have been
```

## Source note 242, line 919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L919)

```text
// (8,0)->(328,192), but it's not. However, it adjusts the destination texture
```

## Source note 243, line 920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L920)

```text
// address so (0,0) relative to the destination address is (0,0) relative to
```

## Source note 244, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L921)

```text
// the render target (if resolving a part of a render target to the top-left
```

## Source note 245, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L922)

```text
// corner of a texture, Direct3D 9 actually moves the destination pointer before
```

## Source note 246, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L923)

```text
// the start of the texture, with tiled offset internally calculated for a
```

## Source note 247, line 924

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L924)

```text
// negative offset). When copying, the pointer needs to be adjusted to the first
```

## Source note 248, line 925

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L925)

```text
// 32x32 tile that will actually be modified, by adding the value of
```

## Source note 249, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L926)

```text
// XGAddress2D/3DTiledOffset called for left/top & ~31.
```

## Source note 250, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L928)

```text
// RB_COPY_DEST_PITCH's purpose appears to be not clamping or something like
```

## Source note 251, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L929)

```text
// that, but just specifying pitch for going between rows, and height used by
```

## Source note 252, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L930)

```text
// 3D texture copies. copy_dest_pitch is rounded to 32 by Direct3D 9,
```

## Source note 253, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L931)

```text
// copy_dest_height is not. In the 4D5307E6 sniper rifle scope example,
```

## Source note 254, line 932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L932)

```text
// copy_dest_pitch is 320, and copy_dest_height is 192 - the same as the resolve
```

## Source note 255, line 933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L933)

```text
// rectangle size (resolving from a 320x192 portion of the surface at 128,64 to
```

## Source note 256, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L934)

```text
// the whole texture, at 0,0). The bottom of the destination level is at 256
```

## Source note 257, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L935)

```text
// relative to RB_COPY_DEST_BASE, but this runtime writes level_height - dest_y,
```

## Source note 258, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L936)

```text
// giving 192 without including the source rectangle's top. Adreno doesn't have
```

## Source note 259, line 937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L937)

```text
// copy_dest_height at all (as well as RB_COPY_DEST_INFO::copy_dest_slice),
```

## Source note 260, line 938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L938)

```text
// suggesting that these fields are only needed for 3D texture copies.
```

## Source note 261, line 940

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L940)

```text
// copy_dest_height can also be adjusted for source_top, so it shouldn't be used
```

## Source note 262, line 941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L941)

```text
// to determine volume slice spacing. Volume resolves separately write
```

## Source note 263, line 942

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L942)

```text
// destination pitch * level height to RB_COPY_SURFACE_SLICE without either
```

## Source note 264, line 943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L943)

```text
// adjustment. Later D3D runtimes (4D530A26, 555308B6) add source_top, which
```

## Source note 265, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L944)

```text
// would make the same sniper scope example 256 (xenia-canary #1248).
```

## Source note 266, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L946)

```text
// Window scissor must also be applied - in the jigsaw puzzle in 58410955, there
```

## Source note 267, line 947

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L947)

```text
// are 1280x720 resolve rectangles, but only the scissored 1280x256 needs to be
```

## Source note 268, line 948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L948)

```text
// copied, otherwise it overflows even beyond the EDRAM, and the depth buffer is
```

## Source note 269, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L949)

```text
// visible on the screen. It also ensures the coordinates are not negative (in
```

## Source note 270, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L950)

```text
// 565507D9, for example, the right tile is resolved with vertices
```

## Source note 271, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L951)

```text
// (-640,0)->(640,720), however, the destination texture pointer is adjusted
```

## Source note 272, line 952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L952)

```text
// properly to the right half of the texture, and the source render target has a
```

## Source note 273, line 953

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L953)

```text
// pitch of 800).
```

## Source note 274, line 955

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L955)

```text
// Granularity of offset and size in resolve operations is 8x8 pixels
```

## Source note 275, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L956)

```text
// (GPU_RESOLVE_ALIGNMENT - for example, 4D5307E6 resolves a 24x16 region for a
```

## Source note 276, line 957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L957)

```text
// 18x10 texture, 8x8 region for a 1x1 texture).
```

## Source note 277, line 958

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L958)

```text
// https://github.com/jmfauvel/CSGO-SDK/blob/master/game/client/view.cpp#L944
```

## Source note 278, line 959

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L959)

```text
// https://github.com/stanriders/hl2-asw-port/blob/master/src/game/client/vgui_int.cpp#L901
```

## Source note 279, line 963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L963)

```text
// Same as RB_SURFACE_INFO::surface_pitch, RB_COPY_DEST_PITCH::copy_dest_pitch
```

## Source note 280, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L964)

```text
// and RB_COPY_DEST_PITCH::copy_dest_height.
```

## Source note 281, line 975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L975)

```text
// a2xx_rb_copy_sample_select
```

## Source note 282, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1016)

```text
// No swap.
```

## Source note 283, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1019)

```text
// Swap bytes in half words.
```

## Source note 284, line 1031

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1031)

```text
// No swap.
```

## Source note 285, line 1034

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1034)

```text
// Swap bytes in half words.
```

## Source note 286, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1037)

```text
// Swap bytes.
```

## Source note 287, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1038)

```text
// NOTE: we are likely doing two swaps here. Wasteful. Oh well.
```

## Source note 288, line 1041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1041)

```text
// Swap half words.
```

## Source note 289, line 1064

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1064)

```text
// XE_GPU_REG_SHADER_CONSTANT_LOOP_*
```

## Source note 290, line 1068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1068)

```text
// +0
```

## Source note 291, line 1069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1069)

```text
// Address (aL) start and step.
```

## Source note 292, line 1070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1070)

```text
// The resulting aL is `iterator * step + start`, 10-bit, and has the real
```

## Source note 293, line 1071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1071)

```text
// range of [-256, 256], according to the IPR2015-00325 sequencer
```

## Source note 294, line 1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1072)

```text
// specification.
```

## Source note 295, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1073)

```text
// +8
```

## Source note 296, line 1074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1074)

```text
// +16
```

## Source note 297, line 1075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1075)

```text
// +24
```

## Source note 298, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1080)

```text
// SQ_TEX_VTX_INVALID/VALID_TEXTURE/BUFFER
```

## Source note 299, line 1091

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1091)

```text
// XE_GPU_REG_SHADER_CONSTANT_FETCH_*
```

## Source note 300, line 1098

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1098)

```text
// +0
```

## Source note 301, line 1099

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1099)

```text
// +2 address in dwords
```

## Source note 302, line 1101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1101)

```text
// +0
```

## Source note 303, line 1102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1102)

```text
// +2 size in words
```

## Source note 304, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1103)

```text
// +26
```

## Source note 305, line 1108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1108)

```text
// Byte alignment of texture subresources in memory - of each mip and stack
```

## Source note 306, line 1109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1109)

```text
// slice / cube face (and of textures themselves), this number of bits is also
```

## Source note 307, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1110)

```text
// omitted from base_address and mip_address.
```

## Source note 308, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1114)

```text
// Texture fetch constant size field widths.
```

## Source note 309, line 1117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1117)

```text
// Emulation cap on rows materialized for wide (> 8192) 1D textures mapped to
```

## Source note 310, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1118)

```text
// 2D (xenia-edge). Must match between the texture cache and the translators.
```

## Source note 311, line 1134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1134)

```text
// 3D tiled texture slices 0:3 and 4:7 are stored separately in memory, in
```

## Source note 312, line 1135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1135)

```text
// non-overlapping ranges, but addressing in 4:7 is different than in 0:3.
```

## Source note 313, line 1139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1139)

```text
// Texture tile address function periods:
```

## Source note 314, line 1140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1140)

```text
// - 2D 1bpb: 128x128
```

## Source note 315, line 1141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1141)

```text
// - 2D 2bpb: 64x64
```

## Source note 316, line 1142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1142)

```text
// - 2D 4bpb+: 32x32
```

## Source note 317, line 1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1143)

```text
// - 3D 1bpb: 64x32x8
```

## Source note 318, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1144)

```text
// - 3D 2bpb+: 32x32x8
```

## Source note 319, line 1154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1154)

```text
// Row pitch alignment of non-tiled textures.
```

## Source note 320, line 1158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1158)

```text
// XE_GPU_REG_SHADER_CONSTANT_FETCH_*
```

## Source note 321, line 1169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1169)

```text
// +0 dword_0
```

## Source note 322, line 1170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1170)

```text
// The signedness applies to the data components (before the swizzle, which
```

## Source note 323, line 1171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1171)

```text
// is the destination selection).
```

## Source note 324, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1172)

```text
// Signed repeating fraction formats always use the kZeroClampMinusOne mode,
```

## Source note 325, line 1173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1173)

```text
// according to the IPR2015-00325 R400 Document Library Folder History:
```

## Source note 326, line 1174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1174)

```text
//   "Change 133990 on 2003/11/25 by jhoule@jhoule_doc_lt
```

## Source note 327, line 1175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1175)

```text
//   v1.80 - Indicated that NO_ZERO srf mode is unsupported for Xenos (will
```

## Source note 328, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1176)

```text
//   currently only work in the VC path)"
```

## Source note 329, line 1177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1177)

```text
// +2
```

## Source note 330, line 1178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1178)

```text
// +4
```

## Source note 331, line 1179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1179)

```text
// +6
```

## Source note 332, line 1180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1180)

```text
// +8
```

## Source note 333, line 1181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1181)

```text
// +10
```

## Source note 334, line 1182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1182)

```text
// +13
```

## Source note 335, line 1183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1183)

```text
// +16
```

## Source note 336, line 1184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1184)

```text
// +19
```

## Source note 337, line 1185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1185)

```text
// Base row pitch in pixels (not blocks) >> 5. For linear textures, this is
```

## Source note 338, line 1186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1186)

```text
// provided by Direct3D 9 in a way that every row of blocks ends up aligned
```

## Source note 339, line 1187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1187)

```text
// to kTextureLinearRowAlignmentBytes (the GPU requires 256-byte alignment
```

## Source note 340, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1188)

```text
// of linear texture block rows for all textures).
```

## Source note 341, line 1189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1189)

```text
// Mips are always stored with padding to the `max(next_pow2(base width or
```

## Source note 342, line 1190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1190)

```text
// height) >> level, 1)` or a 32x32x4 tile (whichever is larger), so this
```

## Source note 343, line 1191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1191)

```text
// pitch is irrelevant to them (but the 256-byte alignment requirement still
```

## Source note 344, line 1192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1192)

```text
// applies to linear textures).
```

## Source note 345, line 1193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1193)

```text
// Examples of pitch > aligned width:
```

## Source note 346, line 1194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1194)

```text
// - 584109FF (loading screen and menu backgrounds, 1408 for a 1280x linear
```

## Source note 347, line 1195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1195)

```text
//   k_DXT4_5 texture, which corresponds to 22 * 256 bytes rather than
```

## Source note 348, line 1196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1196)

```text
//   20 * 256 for just 1280x).
```

## Source note 349, line 1197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1197)

```text
// +22
```

## Source note 350, line 1198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1198)

```text
// +31
```

## Source note 351, line 1200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1200)

```text
// +0 dword_1
```

## Source note 352, line 1201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1201)

```text
// +6
```

## Source note 353, line 1202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1202)

```text
// +8
```

## Source note 354, line 1203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1203)

```text
// +10
```

## Source note 355, line 1204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1204)

```text
// +11 d3d/opengl
```

## Source note 356, line 1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1205)

```text
// +12 base address >> 12
```

## Source note 357, line 1207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1207)

```text
// Size is stored with 1 subtracted from each component.
```

## Source note 358, line 1208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1208)

```text
// dword_2
```

## Source note 359, line 1216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1216)

```text
// Should be 0 for k2D and 5 for kCube if not stacked, but not very
```

## Source note 360, line 1217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1217)

```text
// meaningful in this case, likely should be ignored for non-stacked.
```

## Source note 361, line 1227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1227)

```text
// +0 dword_3 frac/int
```

## Source note 362, line 1228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1228)

```text
// xyzw, 3b each (XE_GPU_TEXTURE_SWIZZLE)
```

## Source note 363, line 1229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1229)

```text
// +1
```

## Source note 364, line 1230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1230)

```text
// +13
```

## Source note 365, line 1231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1231)

```text
// +19
```

## Source note 366, line 1232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1232)

```text
// +21
```

## Source note 367, line 1233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1233)

```text
// +23
```

## Source note 368, line 1234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1234)

```text
// +25
```

## Source note 369, line 1235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1235)

```text
// +28
```

## Source note 370, line 1236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1236)

```text
// +31
```

## Source note 371, line 1238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1238)

```text
// +0 dword_4
```

## Source note 372, line 1239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1239)

```text
// +1
```

## Source note 373, line 1240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1240)

```text
// +2
```

## Source note 374, line 1241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1241)

```text
// +6
```

## Source note 375, line 1242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1242)

```text
// +10
```

## Source note 376, line 1243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1243)

```text
// +11
```

## Source note 377, line 1244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1244)

```text
// 5 fractional bits (A2XX_SQ_TEX_4_LOD_BIAS).
```

## Source note 378, line 1245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1245)

```text
// +12
```

## Source note 379, line 1246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1246)

```text
// Also known as LodBiasH/V in sys2gmem.
```

## Source note 380, line 1247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1247)

```text
// +22
```

## Source note 381, line 1248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1248)

```text
// +27
```

## Source note 382, line 1250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1250)

```text
// +0 dword_5
```

## Source note 383, line 1251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1251)

```text
// +2
```

## Source note 384, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1252)

```text
// Also known as TriJuice.
```

## Source note 385, line 1253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1253)

```text
// +3
```

## Source note 386, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1254)

```text
// +5
```

## Source note 387, line 1255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1255)

```text
// +9
```

## Source note 388, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1256)

```text
// +11
```

## Source note 389, line 1257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1257)

```text
// +12 mip address >> 12
```

## Source note 390, line 1262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1262)

```text
// XE_GPU_REG_SHADER_CONSTANT_FETCH_*
```

## Source note 391, line 1292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1292)

```text
// Shader memory export (memexport) allows for writing of arbitrary formatted
```

## Source note 392, line 1293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1293)

```text
// data with random access / scatter capabilities. It provides functionality
```

## Source note 393, line 1294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1294)

```text
// largely similar to resolving - format packing, supporting arbitrary color
```

## Source note 394, line 1295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1295)

```text
// formats, from sub-dword ones such as k_8 in 58410B86, to 128-bit ones, with
```

## Source note 395, line 1296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1296)

```text
// endian swap similar to how it's performed in resolves (up to 128-bit);
```

## Source note 396, line 1297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1297)

```text
// specifying the number format, swapping red and blue channels - though with no
```

## Source note 397, line 1298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1298)

```text
// exponent biasing. Unlike resolving, however, instead of writing to tiled
```

## Source note 398, line 1299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1299)

```text
// textures, it exports the data to up to 5 elements (the eM# shader registers,
```

## Source note 399, line 1300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1300)

```text
// each corresponding to `base address + element size * (offset + 0...4)`) in a
```

## Source note 400, line 1301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1301)

```text
// stream defined by a stream constant and an offset in elements written to eA -
```

## Source note 401, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1302)

```text
// a shader, however, can write to multiple streams with different or the same
```

## Source note 402, line 1303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1303)

```text
// stream constants, by performing `alloc export` multiple times. It's used
```

## Source note 403, line 1304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1304)

```text
// mostly in vertex shaders (most commonly in improvised "compute shaders" done
```

## Source note 404, line 1305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1305)

```text
// by executing a vertex shader for a number of point-type primitives covering
```

## Source note 405, line 1306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1306)

```text
// nothing), though usage in pixel shaders is also possible - an example is
```

## Source note 406, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1307)

```text
// provided in the "Advanced Screenspace Antialiasing" presentation by Arne
```

## Source note 407, line 1308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1308)

```text
// Schober.
```

## Source note 408, line 1309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1309)

```text
// https://ubm-twvideo01.s3.amazonaws.com/o1/vault/gdceurope2010/slides/A_Schober_Advanced_Screenspace_Antialiasing.pdf
```

## Source note 409, line 1311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1311)

```text
// Unlike fetch constants, which are passed via special registers, a memory
```

## Source note 410, line 1312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1312)

```text
// export stream is configured by writing the stream constant and the offset to
```

## Source note 411, line 1313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1313)

```text
// a shader export register (eA) allocated by the shader - similar to more
```

## Source note 412, line 1314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1314)

```text
// conventional exports like oPos, o#, oC#. Therefore, in general, it's not
```

## Source note 413, line 1315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1315)

```text
// possible to know what its value will be without running the shader. For
```

## Source note 414, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1316)

```text
// emulation, this means that the memory range referenced by an export - that
```

## Source note 415, line 1317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1317)

```text
// needs to be validated - requires running the shader on the CPU in general.
```

## Source note 416, line 1318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1318)

```text
// Thankfully, however, the usual way of setting up eA is by executing:
```

## Source note 417, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1319)

```text
// `mad eA, r#, const0100, c#`
```

## Source note 418, line 1320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1320)

```text
// where c# is the stream float4 constant from the float constant registers, and
```

## Source note 419, line 1321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1321)

```text
// const0100 is a literal (0.0f, 1.0f, 0.0f, 0.0f) constant, also from the float
```

## Source note 420, line 1322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1322)

```text
// constant registers, used for placing the element index (r#) in the correct
```

## Source note 421, line 1323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1323)

```text
// component of eA. This allows for easy gathering of memexport stream
```

## Source note 422, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1324)

```text
// constants, which contain both the base address and the size of the
```

## Source note 423, line 1325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1325)

```text
// destination buffer for bounds checking, from the shader code and the float
```

## Source note 424, line 1326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1326)

```text
// constant registers, as long as the guest uses this instruction pattern to
```

## Source note 425, line 1327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1327)

```text
// write to eA.
```

## Source note 426, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1329)

```text
// The Xenos doesn't have an integer ALU, and denormals are treated as zero and
```

## Source note 427, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1330)

```text
// are flushed. However, eA contains integers and bit fields. A stream constant
```

## Source note 428, line 1331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1331)

```text
// is thus structured in a way that allows for packing integers in normalized
```

## Source note 429, line 1332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1332)

```text
// floating-point numbers.
```

## Source note 430, line 1334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1334)

```text
// X contains the base address of the stream in dwords as integer bits in the
```

## Source note 431, line 1335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1335)

```text
// lower 30 bits, and bits 0b01 in the top. The 0b01 bits make the exponent
```

## Source note 432, line 1336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1336)

```text
// nonzero, so the number is considered normalized, and therefore isn't flushed
```

## Source note 433, line 1337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1337)

```text
// to zero. With only 512 MB of the physical memory on the Xbox 360, the
```

## Source note 434, line 1338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1338)

```text
// exponent can't become 0b11111111, so X also won't be NaN for any valid Xbox
```

## Source note 435, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1339)

```text
// 360 physical address (though in general the GPU supports 32-bit addresses,
```

## Source note 436, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1340)

```text
// but this is originally an Xbox 360-specific feature, that was later, however,
```

## Source note 437, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1341)

```text
// likely reused for GL_QCOM_writeonly_rendering).
```

## Source note 438, line 1352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1352)

```text
// +0 dword_0 physical address >> 2
```

## Source note 439, line 1353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1353)

```text
// +30
```

## Source note 440, line 1355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1355)

```text
// +0 dword_1
```

## Source note 441, line 1357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1357)

```text
// +0 dword_2
```

## Source note 442, line 1358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1358)

```text
// +3
```

## Source note 443, line 1359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1359)

```text
// +8
```

## Source note 444, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1360)

```text
// +14
```

## Source note 445, line 1361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1361)

```text
// +16
```

## Source note 446, line 1362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1362)

```text
// +19
```

## Source note 447, line 1363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1363)

```text
// +20
```

## Source note 448, line 1365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1365)

```text
// +0 dword_3
```

## Source note 449, line 1366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1366)

```text
// +23
```

## Source note 450, line 1372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1372)

```text
// This is little endian as it is swapped in D3D code.
```

## Source note 451, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1373)

```text
// Corresponding A and B values are summed up by D3D.
```

## Source note 452, line 1374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1374)

```text
// Occlusion there is calculated by substracting begin from end struct.
```

## Source note 453, line 1386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1386)

```text
// Enum of event values used for VGT_EVENT_INITIATOR
```

## Source note 454, line 1414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1414)

```text
// Opcodes (IT_OPCODE) for Type-3 commands in the ringbuffer.
```

## Source note 455, line 1415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1415)

```text
// https://github.com/freedreno/amd-gpu/blob/master/include/api/gsl_pm4types.h
```

## Source note 456, line 1416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1416)

```text
// Not sure if all of these are used.
```

## Source note 457, line 1419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1419)

```text
// initialize CP's micro-engine
```

## Source note 458, line 1421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1421)

```text
// skip N 32-bit words to get to the next packet
```

## Source note 459, line 1423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1423)

```text
// indirect buffer dispatch.  prefetch parser uses this packet type to determine whether to pre-fetch the IB
```

## Source note 460, line 1424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1424)

```text
// indirect buffer dispatch.  same as IB, but init is pipelined
```

## Source note 461, line 1426

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1426)

```text
// wait for the IDLE state of the engine
```

## Source note 462, line 1427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1427)

```text
// wait until a register or memory location is a specific value
```

## Source note 463, line 1428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1428)

```text
// wait until a register location is equal to a specific value
```

## Source note 464, line 1429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1429)

```text
// wait until a register location is >= a specific value
```

## Source note 465, line 1430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1430)

```text
// wait until a read completes
```

## Source note 466, line 1431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1431)

```text
// wait until all base/size writes from an IB_PFD packet have completed
```

## Source note 467, line 1433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1433)

```text
// register read/modify/write
```

## Source note 468, line 1434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1434)

```text
// reads register in chip and writes to memory
```

## Source note 469, line 1435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1435)

```text
// write N 32-bit words to memory
```

## Source note 470, line 1436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1436)

```text
// write CP_PROG_COUNTER value to memory
```

## Source note 471, line 1437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1437)

```text
// conditional execution of a sequence of packets
```

## Source note 472, line 1438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1438)

```text
// conditional write to memory or register
```

## Source note 473, line 1440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1440)

```text
// generate an event that creates a write to memory when completed
```

## Source note 474, line 1441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1441)

```text
// generate a VS|PS_done event
```

## Source note 475, line 1442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1442)

```text
// generate a cache flush done event
```

## Source note 476, line 1443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1443)

```text
// generate a screen extent event
```

## Source note 477, line 1444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1444)

```text
// generate a z_pass done event
```

## Source note 478, line 1446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1446)

```text
// initiate fetch of index buffer and draw
```

## Source note 479, line 1447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1447)

```text
// draw using supplied indices in packet
```

## Source note 480, line 1448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1448)

```text
// initiate fetch of index buffer and binIDs and draw
```

## Source note 481, line 1449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1449)

```text
// initiate fetch of bin IDs and draw using supplied indices
```

## Source note 482, line 1451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1451)

```text
// begin/end initiator for viz query extent processing
```

## Source note 483, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1452)

```text
// fetch state sub-blocks and initiate shader code DMAs
```

## Source note 484, line 1453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1453)

```text
// load constant into chip and to memory
```

## Source note 485, line 1456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1456)

```text
// load constants from memory
```

## Source note 486, line 1457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1457)

```text
// load sequencer instruction memory (pointer-based)
```

## Source note 487, line 1458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1458)

```text
// load sequencer instruction memory (code embedded in packet)
```

## Source note 488, line 1459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1459)

```text
// load constants from a location in memory
```

## Source note 489, line 1460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1460)

```text
// selective invalidation of state pointers
```

## Source note 490, line 1462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1462)

```text
// dynamically changes shader instruction memory partition
```

## Source note 491, line 1463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1463)

```text
// program an offset that will added to the BIN_BASE value of the 3D_DRAW_INDX_BIN packet
```

## Source note 492, line 1464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1464)

```text
// sets the 64-bit BIN_MASK register in the PFP
```

## Source note 493, line 1465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1465)

```text
// sets the 64-bit BIN_SELECT register in the PFP
```

## Source note 494, line 1467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1467)

```text
// updates the current context, if needed
```

## Source note 495, line 1468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1468)

```text
// generate interrupt from the command stream
```

## Source note 496, line 1470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1470)

```text
// Xenia only: VdSwap uses this to trigger a swap.
```

## Source note 497, line 1472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1472)

```text
// copy sequencer instruction memory to system memory
```

## Source note 498, line 1474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1474)

```text
// Tiled rendering:
```

## Source note 499, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1475)

```text
// https://www.google.com/patents/US20060055701
```

## Source note 500, line 1484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1484)

```text
// ttcccccc cccccccc oiiiiiii iiiiiiii
```

## Source note 501, line 1491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1491)

```text
// tt?????? ??222222 22222111 11111111
```

## Source note 502, line 1498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1498)

```text
// tt?????? ???????? ???????? ????????
```

## Source note 503, line 1503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/xenos.h#L1503)

```text
// ttcccccc cccccccc ?ooooooo ???????p
```
