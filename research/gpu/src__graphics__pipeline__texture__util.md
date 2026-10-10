# Util: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/texture/util.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L74)

```text
// If level 0 is already the packed tail, D3D leaves mip_address at 0.
```

## Source note 2, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L75)

```text
// The rest of the tail is stored at the base address too.
```

## Source note 3, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L76)

```text
// Source: xenia-canary #1249 (ace153cb84704cea5634a056076585b570380a26).
```

## Source note 4, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L84)

```text
// Not taking mip_filter == kBaseMap into account for mip_max_level because
```

## Source note 5, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L85)

```text
// the mip filter may be overridden by shader fetch instructions.
```

## Source note 6, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L122)

```text
// Tile size is 32x32, and once textures go <=16 they are packed into a
```

## Source note 7, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L123)

```text
// single tile together. The math here is insane. Most sourced from
```

## Source note 8, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L124)

```text
// graph paper, looking at dds dumps and executable reverse engineering.
```

## Source note 9, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L125)

```text
//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
```

## Source note 10, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L126)

```text
// 0         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 11, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L127)

```text
// 1         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 12, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L128)

```text
// 2         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 13, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L129)

```text
// 3         +.4x4.+ +.....8x8.....+ +............16x16............+
```

## Source note 14, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L130)

```text
// 4 x               +.....8x8.....+ +............16x16............+
```

## Source note 15, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L131)

```text
// 5                 +.....8x8.....+ +............16x16............+
```

## Source note 16, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L132)

```text
// 6                 +.....8x8.....+ +............16x16............+
```

## Source note 17, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L133)

```text
// 7                 +.....8x8.....+ +............16x16............+
```

## Source note 18, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L134)

```text
// 8 2x2                             +............16x16............+
```

## Source note 19, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L135)

```text
// 9 2x2                             +............16x16............+
```

## Source note 20, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L136)

```text
// 0                                 +............16x16............+
```

## Source note 21, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L139)

```text
// The 2x2 and 1x1 squares are packed in their specific positions because
```

## Source note 22, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L140)

```text
// each square is the size of at least one block (which is 4x4 pixels max)
```

## Source note 23, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L142)

```text
// if (tile_aligned(w) > tile_aligned(h)) {
```

## Source note 24, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L143)

```text
//   // wider than tall, so packed horizontally
```

## Source note 25, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L144)

```text
// } else if (tile_aligned(w) < tile_aligned(h)) {
```

## Source note 26, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L145)

```text
//   // taller than wide, so packed vertically
```

## Source note 27, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L146)

```text
// } else {
```

## Source note 28, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L149)

```text
// It's important to use logical sizes here, as the input sizes will be
```

## Source note 29, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L150)

```text
// for the entire packed tile set, not the actual texture.
```

## Source note 30, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L151)

```text
// The minimum dimension is what matters most: if either width or height
```

## Source note 31, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L152)

```text
// is <= 16 this mode kicks in.
```

## Source note 32, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L158)

```text
// The shortest dimension is bigger than 16, not packed.
```

## Source note 33, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L167)

```text
// Find the block offset of the mip.
```

## Source note 34, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L170)

```text
// Wider than tall. Laid out vertically.
```

## Source note 35, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L174)

```text
// Taller than wide. Laid out horizontally.
```

## Source note 36, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L182)

```text
// Wider than tall. Laid out horizontally.
```

## Source note 37, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L187)

```text
// Taller than wide. Laid out vertically.
```

## Source note 38, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L193)

```text
// Pack 1x1 Z mipmaps along Z - not reached for 2D.
```

## Source note 39, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L221)

```text
// GetPackedMipOffset may result in packing along Y for `width > height`
```

## Source note 40, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L222)

```text
// textures.
```

## Source note 41, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L238)

```text
// For safety, for instance, with empty resolve regions (extents calculation
```

## Source note 42, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L239)

```text
// may overflow otherwise due to the assumption of at least one row, for
```

## Source note 43, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L240)

```text
// example, but an empty texture is empty anyway).
```

## Source note 44, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L245)

```text
// D3D's FindTextureSize aligns non-base 2D array levels to four slices.
```

## Source note 45, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L250)

```text
// For safety, clamp the maximum level.
```

## Source note 46, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L260)

```text
// Clear unused level layouts to zero strides/sizes.
```

## Source note 47, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L283)

```text
// The loop counter can mean two things depending on whether the packed mip
```

## Source note 48, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L284)

```text
// tail is stored as mip 0, because in this case, it would be ambiguous since
```

## Source note 49, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L285)

```text
// both the base and the mips would be on "level 0", but stored separately and
```

## Source note 50, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L286)

```text
// possibly with a different layout.
```

## Source note 51, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L289)

```text
// Packed mip tail is the level 0 - may need to load mip tails for the base,
```

## Source note 52, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L290)

```text
// the mips, or both.
```

## Source note 53, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L291)

```text
// Loop iteration 0 - base packed mip tail.
```

## Source note 54, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L292)

```text
// Loop iteration 1 - mips packed mip tail.
```

## Source note 55, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L295)

```text
// Packed mip tail is not the level 0.
```

## Source note 56, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L296)

```text
// Loop iteration is the actual level being loaded.
```

## Source note 57, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L305)

```text
// Calculate the strides.
```

## Source note 58, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L306)

```text
// Mips have row / depth slice strides calculated from a mip of a texture
```

## Source note 59, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L307)

```text
// whose base size is a power of two.
```

## Source note 60, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L308)

```text
// The base mip has tightly packed depth slices, and takes the row pitch
```

## Source note 61, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L309)

```text
// from the fetch constant.
```

## Source note 62, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L310)

```text
// For stride calculation purposes, mip dimensions are always aligned to
```

## Source note 63, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L311)

```text
// 32x32x4 blocks (or x1 for the missing dimensions), including for linear
```

## Source note 64, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L312)

```text
// textures.
```

## Source note 65, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L313)

```text
// Linear texture row blocks are aligned to max(256 / block size, 32).
```

## Source note 66, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L318)

```text
// Level 0 packed tails use power-of-two dimensions like the other mips.
```

## Source note 67, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L319)

```text
// Source: xenia-canary #1249 (81e3deaee2dbd5d3125f87da2194a61e418851ce).
```

## Source note 68, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L356)

```text
// Estimate the memory amount actually referenced by the texture, which may
```

## Source note 69, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L357)

```text
// be smaller (especially in the 1280x720 linear k_8_8_8_8 case in 4E4D083E,
```

## Source note 70, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L358)

```text
// for which memory exactly for 1280x720 is allocated, and aligning the
```

## Source note 71, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L359)

```text
// height to 32 would cause access of an unallocated page) or bigger than
```

## Source note 72, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L360)

```text
// the stride.
```

## Source note 73, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L362)

```text
// Calculate the portion of the mip tail actually used by the needed mips.
```

## Source note 74, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L363)

```text
// The actually used region may be significantly smaller than the full
```

## Source note 75, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L364)

```text
// 32x32-texel-aligned (and, for mips, calculated from the base dimensions
```

## Source note 76, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L365)

```text
// rounded to powers of two - 58410A7A has an 80x260 tiled texture with
```

## Source note 77, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L366)

```text
// packed mips at level 3 containing a mip ending at Y = 36, while
```

## Source note 78, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L367)

```text
// 260 >> 3 == 32, but 512 >> 3 == 64) tail. A 2x2 texture (for example,
```

## Source note 79, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L368)

```text
// in 494707D4, there's a 2x2 k_8_8_8_8 linear texture with packed mips),
```

## Source note 80, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L369)

```text
// for instance, would have its 2x2 base at (16, 0) and its 1x1 mip at
```

## Source note 81, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L370)

```text
// (8, 0) - and we need 2 or 1 rows in these cases, not 32 - the 32 rows
```

## Source note 82, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L371)

```text
// in a linear texture (with 256-byte pitch alignment) would span two 4 KB
```

## Source note 83, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L372)

```text
// pages rather than one.
```

## Source note 84, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L442)

```text
// https://github.com/gildor2/UModel/blob/de8fbd3bc922427ea056b7340202dcdcc19ccff5/Unreal/UnTexture.cpp#L489
```

## Source note 85, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L444)

```text
// Top bits of coordinates.
```

## Source note 86, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L446)

```text
// Lower bits of coordinates (result is 6-bit value).
```

## Source note 87, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L448)

```text
// Mix micro/macro + add few remaining x/y bits.
```

## Source note 88, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L450)

```text
// Mix bits again.
```

## Source note 89, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L457)

```text
// Reconstructed from disassembly of XGRAPHICS::TileVolume.
```

## Source note 90, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L483)

```text
// Get the origin of the 32x32 tile containing the last texel.
```

## Source note 91, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L489)

```text
// Independent addressing within 128x128 portions, but the extent is 0xA00
```

## Source note 92, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L490)

```text
// bytes from the 32x32 tile origin.
```

## Source note 93, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L494)

```text
// Independent addressing within 64x64 portions, but the extent is 0xC00
```

## Source note 94, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L495)

```text
// bytes from the 32x32 tile origin.
```

## Source note 95, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L510)

```text
// Find the highest block address within the last 32 row x 4 slice portion.
```

## Source note 96, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L511)

```text
// Addresses increase within aligned runs of 8 blocks walking x, where only
```

## Source note 97, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L512)

```text
// x[2:0] changes. Bank/pipe selection can place earlier runs at a higher
```

## Source note 98, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L513)

```text
// address, so check every run's last block.
```

## Source note 99, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L515)

```text
// For 1 byte per block, two 32x16x4 macro tiles share a page. The bank bit
```

## Source note 100, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L516)

```text
// can place blocks from the earlier macro tile after later ones, so include
```

## Source note 101, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L517)

```text
// both 32 row portion halves in the search.
```

## Source note 102, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L519)

```text
// When width exceeds the pitch, a block's (x, y) becomes
```

## Source note 103, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L520)

```text
// (x % pitch, y + 16 * (x / pitch)) so blocks from earlier rows can land in
```

## Source note 104, line 521

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L521)

```text
// the last portion. Check all rows in this case.
```

## Source note 105, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L522)

```text
// Source: xenia-canary #1249 (c332733afd14ed3aeb08b38d0cabffa58d1c8c2f); the
```

## Source note 106, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L523)

```text
// closed form it replaces reached 0x880 past the last block and a page more.
```

## Source note 107, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L548)

```text
// 0b00 or 0b01 for each component, whether it's constant 0/1.
```

## Source note 108, line 566

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L566)

```text
// If only constant components, choose according to the original format
```

## Source note 109, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L567)

```text
// (what would more likely be loaded if there were non-constant components).
```

## Source note 110, line 568

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L568)

```text
// If all components would be signed, use signed.
```

## Source note 111, line 569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L569)

```text
// Textures with only constant components must still be bound to shaders for
```

## Source note 112, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L570)

```text
// various queries (such as filtering weights) not involving the color data
```

## Source note 113, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L571)

```text
// itself.
```

## Source note 114, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L576)

```text
// If only signed and constant components, reading just from the signed host
```

## Source note 115, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L577)

```text
// view is enough.
```

## Source note 116, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L603)

```text
// Not applicable to cube textures.
```

## Source note 117, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L608)

```text
// Ported from xenia-canary (d119505289, 2ddc5ef737, 6a45452087, 0c843efb32,
```

## Source note 118, line 609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L609)

```text
// c3cd8617b1; RG-GDK-045). The host samples fixed formats normalized; this
```

## Source note 119, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L610)

```text
// packs, per output component after the guest swizzle, what the fetch shader
```

## Source note 120, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L611)

```text
// needs to give the guest its own result:
```

## Source note 121, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L612)

```text
// - num_format 1 (integer): the source component's width and sign, to scale
```

## Source note 122, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L613)

```text
//   the sample back to [0, 2^w - 1] (or the signed range);
```

## Source note 123, line 614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L614)

```text
// - num_format 0: rounding to 16 fractional bits (bit 24), and for point
```

## Source note 124, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L615)

```text
//   sampled 4 to 7 bit unsigned components, the width to rebuild the guest's
```

## Source note 125, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L616)

```text
//   n * (2^w + 1) / 2^(2w) conversion;
```

## Source note 126, line 617

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L617)

```text
// - bit 26 for a point sampled fetch constant, which snaps coordinates to
```

## Source note 127, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L618)

```text
//   the texel centre.
```

## Source note 128, line 636

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/texture/util.cpp#L636)

```text
// Swizzle components past the stored ones read the last stored one.
```
