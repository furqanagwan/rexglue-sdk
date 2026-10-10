# Util: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/texture/util.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L21)

```text
// This namespace replaces texture_extent and most of texture_info for
```

## Source note 2, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L22)

```text
// simplicity.
```

## Source note 3, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L24)

```text
// Extracts the size from the fetch constant, and also cleans up addresses and
```

## Source note 4, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L25)

```text
// mip range based on real presence of the base level and mips. Returns 6 faces
```

## Source note 5, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L26)

```text
// for cube textures.
```

## Source note 6, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L33)

```text
// Gets the number of the mipmap level where the packed mips are stored.
```

## Source note 7, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L39)

```text
// Gets the offset of the mipmap within the tail in blocks, or zeros (and
```

## Source note 8, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L40)

```text
// returns false) if the mip level is not packed. Width, height and depth are in
```

## Source note 9, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L41)

```text
// texels. For non-3D textures, set depth to 1.
```

## Source note 10, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L42)

```text
// The offset is always within the dimensions of the image rounded to 32.
```

## Source note 11, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L47)

```text
// Both tiled and linear textures, as it appears from Direct3D 9 texture
```

## Source note 12, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L48)

```text
// alignment disassembly (where the parameter indicating whether the texture is
```

## Source note 13, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L49)

```text
// tiled only has effect on aligning the width to max(256 / block size, 32)
```

## Source note 14, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L50)

```text
// rather than 32), are stored as tiles of 32x1x1 (for 1D), 32x32x1 (for 2D), or
```

## Source note 15, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L51)

```text
// 32x32x4 (for 3D) texels (or compression blocks for compressed textures) for
```

## Source note 16, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L52)

```text
// the purpose of calculation of the distance between subresources like array
```

## Source note 17, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L53)

```text
// slices, and between depth slices (especially for linear textures).
```

## Source note 18, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L55)

```text
// Textures have the base level (level 0) stored under their base_address, and
```

## Source note 19, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L56)

```text
// mip levels (starting from 1) stored under their mip_address. There are
```

## Source note 20, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L57)

```text
// differences in how texture data is stored under base_address and mip_address:
```

## Source note 21, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L58)

```text
// - The base level uses the row pitch (specified in texels divided by 32 - thus
```

## Source note 22, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L59)

```text
//   implies 32-block alignment for both uncompressed and compressed textures)
```

## Source note 23, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L60)

```text
//   stored in the fetch constant, and height aligned to 32 blocks for Z slice
```

## Source note 24, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L61)

```text
//   and array layer stride calculation purposes. The pitch can be different
```

## Source note 25, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L62)

```text
//   from the actual width - an example is 584109FF, using 1408 pitch for a
```

## Source note 26, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L63)

```text
//   1280x menu background).
```

## Source note 27, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L64)

```text
// - The mip levels use `max(next_pow2(width or height in texels) >> level, 1)`
```

## Source note 28, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L65)

```text
//   aligned to 32 blocks for the same purpose, likely disregarding the pitch
```

## Source note 29, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L66)

```text
//   from the fetch constant.
```

## Source note 30, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L68)

```text
// There is also mip tail packing if the fetch constant specifies that packed
```

## Source note 31, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L69)

```text
// mips are enabled, for both tiled and linear textures (545407E0 uses linear
```

## Source note 32, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L70)

```text
// DXT-compressed textures with packed mips very extensively for the game world
```

## Source note 33, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L71)

```text
// materials). In this case, mips with width or height of 16 or smaller are
```

## Source note 34, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L72)

```text
// stored not individually, but instead, in 32-texel (note: not 32-block - mip
```

## Source note 35, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L73)

```text
// tail calculations are done with texel units; but 32-block padding can only be
```

## Source note 36, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L74)

```text
// bigger than 32-texel padding for compressed textures) padding of the last
```

## Source note 37, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L75)

```text
// level before the packed one.
```

## Source note 38, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L77)

```text
// Note that the mip tail can be used both for the base level and mips (1...) if
```

## Source note 39, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L78)

```text
// the entire texture has width or height of 16 or smaller. Therefore, both the
```

## Source note 40, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L79)

```text
// base and the mips would be loaded from a mip tail that would be stored like
```

## Source note 41, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L80)

```text
// the level 0 of the texture. But, in this case, under base_address and
```

## Source note 42, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L81)

```text
// mip_address there are two separate mip tails, and the former likely uses the
```

## Source note 43, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L82)

```text
// pitch from the fetch constant and no power of two size rounding, while for
```

## Source note 44, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L83)

```text
// the latter the strides are likely calculated like for usual mips. The same
```

## Source note 45, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L84)

```text
// applies to 17...32 texture sizes, though in this case the base is not packed
```

## Source note 46, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L85)

```text
// tail, but the mips are still packed within an image that's stored like the
```

## Source note 47, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L86)

```text
// level 0 of the texture. So, "storage level 0" is an ambiguous concept - host
```

## Source note 48, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L87)

```text
// texture loading code should distinguish between "base level 0" and "mip tail
```

## Source note 49, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L88)

```text
// for the mips 1... stored like level 0" and load the actual host level 0 from
```

## Source note 50, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L89)

```text
// base_address, with all the base addressing properties, and host levels 1...
```

## Source note 51, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L90)

```text
// from mip_address, with all the mips addressing properties. The base level
```

## Source note 52, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L91)

```text
// being packed is evident from the function that tiles textures in game
```

## Source note 53, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L92)

```text
// disassembly, which only checks the flag whether the data is packed passed to
```

## Source note 54, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L93)

```text
// it, not the level, to see if it needs to calculate the offset in the mip
```

## Source note 55, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L94)

```text
// tail, and the offset calculation function doesn't have level == 0 checks in
```

## Source note 56, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L95)

```text
// it, only early-out if level < packed tail level (which can be 0). There are
```

## Source note 57, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L96)

```text
// examples of textures with packed base, for example, in the intro level of
```

## Source note 58, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L97)

```text
// 545407E0 (8x8 linear DXT1 - pairs of orange lights in the bottom of gambling
```

## Source note 59, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L98)

```text
// machines).
```

## Source note 60, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L100)

```text
// Linear texture rows are aligned to max(256 / block size, 32), for both the
```

## Source note 61, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L101)

```text
// base and the mips (for the base, Direct3D 9 writes the aligned pitch to the
```

## Source note 62, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L102)

```text
// fetch constant).
```

## Source note 63, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L104)

```text
// However, all the 32x32x4 padding, being just padding, is not necessarily
```

## Source note 64, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L105)

```text
// being actually accessed, especially for linear textures. 4E4D083E has a
```

## Source note 65, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L106)

```text
// 1280x720 k_8_8_8_8 linear texture, and allocates memory for exactly 1280x720,
```

## Source note 66, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L107)

```text
// so aligning the height to 32 to 1280x736 results in access violations. So,
```

## Source note 67, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L108)

```text
// while for stride calculations all the padding must be respected, for actual
```

## Source note 68, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L109)

```text
// memory loads it's better to avoid trying to access it when possible:
```

## Source note 69, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L110)

```text
// - If the pitch is bigger than the width, it's better to calculate the last
```

## Source note 70, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L111)

```text
//   row's length from the width rather than the pitch (this also possibly works
```

## Source note 71, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L112)

```text
//   in the other direction though - pitch < width is a weird situation, but
```

## Source note 72, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L113)

```text
//   probably legal, and may lead to reading data from beyond the calculated
```

## Source note 73, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L114)

```text
//   subresource stride).
```

## Source note 74, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L115)

```text
// - For linear textures (like that 1280x720 example from 4E4D083E), it's easy
```

## Source note 75, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L116)

```text
//   to calculate the exact memory extent that may be accessed knowing the
```

## Source note 76, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L117)

```text
//   dimensions (unlike for tiled textures with complex addressing within
```

## Source note 77, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L118)

```text
//   32x32x4-block tiles), so there's no need to align them to 32x32x4 for
```

## Source note 78, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L119)

```text
//   memory extent calculation.
```

## Source note 79, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L120)

```text
//   - For the linear packed mip tail, the extent can be calculated as max of
```

## Source note 80, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L121)

```text
//     (block offsets + block extents) of all levels stored in it.
```

## Source note 81, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L123)

```text
// 1D textures are always linear and likely can't have packed mips (for `width >
```

## Source note 82, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L124)

```text
// height` textures, mip offset calculation may result in packing along Y).
```

## Source note 83, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L126)

```text
// Array slices are stored within levels (this is different than how Direct3D
```

## Source note 84, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L127)

```text
// 10+ builds subresource indices, for instance). Each array slice or level is
```

## Source note 85, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L128)

```text
// aligned to 4 KB (but this doesn't apply to 3D texture slices within one
```

## Source note 86, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L129)

```text
// level).
```

## Source note 87, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L133)

```text
// Distance between each row of blocks in bytes, including all the needed
```

## Source note 88, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L134)

```text
// power of two (for mips) and 256-byte (for linear textures) alignment.
```

## Source note 89, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L136)

```text
// Distance between Z slices in block rows, aligned to power of two for
```

## Source note 90, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L137)

```text
// mips, and to tile height.
```

## Source note 91, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L139)

```text
// Distance between each array slice within the level in bytes, aligned to
```

## Source note 92, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L140)

```text
// kTextureSubresourceAlignmentBytes. The distance to the next level is this
```

## Source note 93, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L141)

```text
// multiplied by the array slice count.
```

## Source note 94, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L144)

```text
// The exclusive upper bound of blocks needed at this level (this level for
```

## Source note 95, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L145)

```text
// non-packed levels, or all the packed levels for the packed mip tail).
```

## Source note 96, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L149)

```text
// Estimated amount of memory this level occupies. Not aligned to
```

## Source note 97, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L150)

```text
// kTextureSubresourceAlignmentBytes. For tiled textures, this will be
```

## Source note 98, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L151)

```text
// calculated for the extent rounded to 32x32x4 blocks (or 32x32x1 depending
```

## Source note 99, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L152)

```text
// on the dimensionality), but for linear textures, as well as for mips of
```

## Source note 100, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L153)

```text
// non-power-of-two tiled textures, this may be significantly (including
```

## Source note 101, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L154)

```text
// less 4 KB pages) smaller than the aligned size (like for 4E4D083E where
```

## Source note 102, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L155)

```text
// aligning the height of a 1280x720 linear texture results in access
```

## Source note 103, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L156)

```text
// violations). For the linear mip tail, this includes all the mip levels
```

## Source note 104, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L157)

```text
// stored in it. If the width is bigger than the pitch, this will also be
```

## Source note 105, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L158)

```text
// taken into account for the last row so all memory actually used by the
```

## Source note 106, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L159)

```text
// texture will be loaded, and may be bigger than the distance between array
```

## Source note 107, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L160)

```text
// slices or levels. The purpose of this parameter is to make the memory
```

## Source note 108, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L161)

```text
// amount that needs to be resident as close to the real amount as possible,
```

## Source note 109, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L162)

```text
// to make sure all the needed data will be read, but also, if possible,
```

## Source note 110, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L163)

```text
// unneeded memory pages won't be accessed (since that may trigger an access
```

## Source note 111, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L164)

```text
// violation on the CPU).
```

## Source note 112, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L166)

```text
// Including all array slices.
```

## Source note 113, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L171)

```text
// If mip_max_level specified at calculation time is at least 1, the stored
```

## Source note 114, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L172)

```text
// mips are min(1, packed_mip_level) through min(mip_max_level,
```

## Source note 115, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L173)

```text
// packed_mip_level).
```

## Source note 116, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L178)

```text
// UINT32_MAX if there's no packed mip tail.
```

## Source note 117, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L189)

```text
// Returns the total size of memory the texture uses starting from its base and
```

## Source note 118, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L190)

```text
// mip addresses, in bytes (both are optional).
```

## Source note 119, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L197)

```text
// Notes about tiled addresses:
```

## Source note 120, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L198)

```text
// - The tiled address calculation functions work for both positive and negative
```

## Source note 121, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L199)

```text
//   offsets, so they can be used to go both from the origin of the texture to a
```

## Source note 122, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L200)

```text
//   region inside it and back (as long as the coordinates are a multiple of the
```

## Source note 123, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L201)

```text
//   period of the tiled address function in each direction - depends on whether
```

## Source note 124, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L202)

```text
//   the texture is 2D or 3D, and on the number of bytes per block). This is, in
```

## Source note 125, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L203)

```text
//   particular, used by Direct3D 9 inside resolving to allow resolving with an
```

## Source note 126, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L204)

```text
//   offset in the texture, so the rectangle coordinates are relative to both
```

## Source note 127, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L205)

```text
//   the render target and the region (with the appropriate alignment) in the
```

## Source note 128, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L206)

```text
//   texture at the same time.
```

## Source note 129, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L207)

```text
// - 2D:
```

## Source note 130, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L208)

```text
//   - Origins of 32x32-block tiles grow monotonically as Y/32 (in blocks)
```

## Source note 131, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L209)

```text
//     increases, and in each tile row, as X/32 (in blocks) increases.
```

## Source note 132, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L210)

```text
//   - In each 32x32 tile, the block at (0, 0) within the tile has the address
```

## Source note 133, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L211)

```text
//     that matches the origin of the tile itself. This is not true for the
```

## Source note 134, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L212)

```text
//     block (31, 31), however - its address will be somewhere within the memory
```

## Source note 135, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L213)

```text
//     extent of the tile.
```

## Source note 136, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L214)

```text
//   - 1bpb:
```

## Source note 137, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L215)

```text
//     - The tiled address sequence repeats every 128 blocks along X or Y.
```

## Source note 138, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L216)

```text
//     - 32x32 tiles have their origins 0x200-bytes-aligned, and the addresses
```

## Source note 139, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L217)

```text
//       of the blocks within a 32x32 tile span 0xA00 bytes.
```

## Source note 140, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L218)

```text
//     - Note that 32x32x1bpb is 0x400 bytes, but addresses of blocks within a
```

## Source note 141, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L219)

```text
//       tile span the range of 0xA00 bytes - so 32x32 tiles are stored in
```

## Source note 142, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L220)

```text
//       memory ranges that may overlap (even across 128x128 - with the pitch of
```

## Source note 143, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L221)

```text
//       192 blocks, the tile at (96, 32)...(127, 63) spans 0x2200...0x2BFF,
```

## Source note 144, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L222)

```text
//       while the tile at (128, 32)...(159, 63) spans 0x2400...0x2DFF.
```

## Source note 145, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L223)

```text
//     - All blocks within a 32x32 tile are located in the same 4KB-aligned
```

## Source note 146, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L224)

```text
//       region.
```

## Source note 147, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L225)

```text
//   - 2bpb:
```

## Source note 148, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L226)

```text
//     - The approach to storage is conceptually similar to that of 1bpb, with
```

## Source note 149, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L227)

```text
//       some quantitative differences.
```

## Source note 150, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L228)

```text
//     - The tiled address sequence repeats every 64 blocks along X or Y.
```

## Source note 151, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L229)

```text
//     - 32x32 tiles have their origins 0x400-bytes-aligned, and the addresses
```

## Source note 152, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L230)

```text
//       of the blocks within a 32x32 tile span 0xC00 bytes.
```

## Source note 153, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L231)

```text
//   - 4bpb and larger:
```

## Source note 154, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L232)

```text
//     - 32x32 tiles (which themselves are 4 KB or larger in this case) are
```

## Source note 155, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L233)

```text
//       stored simply in a tile-row-major way, separately from each other in
```

## Source note 156, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L234)

```text
//       memory, with independent addressing within each tile.
```

## Source note 157, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L235)

```text
// - 3D:
```

## Source note 158, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L236)

```text
//   - Origins of 32x32x4-block tiles grow monotonically as Z/4 increases, and
```

## Source note 159, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L237)

```text
//     in each 4-slice portion, as Y/32 (in blocks) increases, and in each tile
```

## Source note 160, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L238)

```text
//     row, as X/32 (in blocks) increases.
```

## Source note 161, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L239)

```text
//   - Along Z, addressing repeats every 8 slices. Along Y, addressing repeats
```

## Source note 162, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L240)

```text
//     every 32 blocks regardless of the number of bytes per block.
```

## Source note 163, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L241)

```text
//   - 32-block-row x 4-slice portions are stored in disjoint 4KB-aligned ranges
```

## Source note 164, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L242)

```text
//     in memory (thus every 4 slices are also stored in disjoint ranges).
```

## Source note 165, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L243)

```text
//   - Addresses within a 32x32x4-block tile span widely throughout the X pitch,
```

## Source note 166, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L244)

```text
//     with a lot of overlap between 32x32x4 tiles with different X.
```

## Source note 167, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L245)

```text
//   - 1bpb:
```

## Source note 168, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L246)

```text
//     - The tiled address sequence repeats every 64 blocks along X.
```

## Source note 169, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L247)

```text
//     - Origins of 32x32x4-block tiles within 32-block-row x 4-slice portions:
```

## Source note 170, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L248)

```text
//       - X = 0, 64, 128...: (X / 64) * 0x1000
```

## Source note 171, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L249)

```text
//       - X = 32, 96, 160...: (X / 64) * 0x1000 + 0x400
```

## Source note 172, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L250)

```text
//       - Or: ((X >> 6) << 12) | (((X >> 5) & 1) << 10)
```

## Source note 173, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L251)

```text
//     - Span of the addresses within a 32x32x4-block tile:
```

## Source note 174, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L252)

```text
//       - Pitch = 32, 96, 160...: (Pitch / 64) * 0x1000 + 0x1000
```

## Source note 175, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L253)

```text
//       - Pitch = 64, 128, 192...: (Pitch / 64) * 0x1000 + 0xC00
```

## Source note 176, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L254)

```text
//     - Or: ((Pitch >> 6) << 12) + 0xC00 + (((Pitch >> 5) & 1) << 10)
```

## Source note 177, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L255)

```text
//     - Or: ((Pitch >> 6) << 12) + 0xC00 + ((Pitch & (1 << 5)) << (10 - 5))
```

## Source note 178, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L256)

```text
//   - 2bpb and larger:
```

## Source note 179, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L257)

```text
//     - The tiled address sequence repeats every 32 blocks along X.
```

## Source note 180, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L258)

```text
//     - Origins of 32x32x4-block tiles within 32-block-row x 4-slice portions:
```

## Source note 181, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L259)

```text
//       (X / 32) * 0x1000 * (BPB / 2)
```

## Source note 182, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L260)

```text
//     - Span of the addresses within a 32x32x4-block tile:
```

## Source note 183, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L261)

```text
//       ((Pitch / 32) * 0x1000 + 0x1000) * (BPB / 2)
```

## Source note 184, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L262)

```text
// - Addressing of blocks that are contiguous along X (for tiling/untiling of
```

## Source note 185, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L263)

```text
//   larger portions at once):
```

## Source note 186, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L264)

```text
//   - 1bpb - each 8 blocks are laid out sequentially, odd 8 blocks =
```

## Source note 187, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L265)

```text
//     even 8 blocks + 64 bytes (two R32G32_UINT tiled accesses for one
```

## Source note 188, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L266)

```text
//     R32G32B32A32_UINT linear access).
```

## Source note 189, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L267)

```text
//   - 2bpb, 4bpb, 8bpb, 16bpb - each 16 bytes contain blocks laid out
```

## Source note 190, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L268)

```text
//     sequentially (can tile/untile in R32G32B32A32_UINT portions).
```

## Source note 191, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L269)

```text
//   - 2bpb - odd 8 blocks = even 8 blocks + 64 bytes.
```

## Source note 192, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L270)

```text
//   - 4bpb - odd 4 blocks = even 4 blocks + 32 bytes.
```

## Source note 193, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L271)

```text
//   - 8bpb - odd 2 blocks = even 2 blocks + 32 bytes.
```

## Source note 194, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L272)

```text
//   - 16bpb - odd block = even block + 32 bytes.
```

## Source note 195, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L273)

```text
// - Resolve granularity for both offset and size is 8x8 pixels - see
```

## Source note 196, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L274)

```text
//   xenos::kResolveAlignmentPixels. So, multiple pixels can still be loaded and
```

## Source note 197, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L275)

```text
//   stored when resolving, taking the contiguous storage patterns described
```

## Source note 198, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L276)

```text
//   above into account.
```

## Source note 199, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L278)

```text
// bytes_per_block_log2 is log2_floor according to how Direct3D 9 calculates it,
```

## Source note 200, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L279)

```text
// but k_32_32_32 textures are never tiled anyway likely.
```

## Source note 201, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L284)

```text
// The tiled address grows monotonically between tiles with Z/4, then Y/32,
```

## Source note 202, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L285)

```text
// then X/32 blocks. Within 3D tiles, the bank swap in odd Z/4 groups makes
```

## Source note 203, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L286)

```text
// Y=8 the first stored row, not Y=0.
```

## Source note 204, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L305)

```text
// Supporting the right > pitch and bottom > height (in tiles) cases also, for
```

## Source note 205, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L306)

```text
// estimation how far addresses can actually go even potentially beyond the
```

## Source note 206, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L307)

```text
// subresource stride.
```

## Source note 207, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L313)

```text
// Returns four packed TextureSign values swizzled according to the swizzle in
```

## Source note 208, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L314)

```text
// the fetch constant, so the shader can apply TextureSigns after reading a
```

## Source note 209, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L315)

```text
// pre-swizzled texture. 0/1 elements are considered unsigned (and not biased),
```

## Source note 210, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L316)

```text
// however, if all non-constant components are signed, 0/1 are considered signed
```

## Source note 211, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L317)

```text
// too (because in backends, unsigned and signed textures may use separate host
```

## Source note 212, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L318)

```text
// textures with different formats, so just one is used for both signed and
```

## Source note 213, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L319)

```text
// constant components).
```

## Source note 214, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L325)

```text
// Make signed 00 - check if all are 01, 10 or 11.
```

## Source note 215, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L329)

```text
// Whether a shader binding gets the signed view. Unsigned bindings of a fully
```

## Source note 216, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L330)

```text
// signed texture, which getBCF samples, get it as there is no unsigned view.
```

## Source note 217, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L335)

```text
// Returns normalized clamp modes specified in the fetch constant based on the
```

## Source note 218, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L336)

```text
// texture data dimension in it.
```

## Source note 219, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L341)

```text
// How the fetch shader turns the host's normalized sample of a fixed format
```

## Source note 220, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L342)

```text
// back into what the guest reads: the integer value for num_format 1, and the
```

## Source note 221, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L343)

```text
// guest's rounding for num_format 0, plus the point sampled flag (layout in
```

## Source note 222, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/util.h#L344)

```text
// DxbcShaderTranslator::SystemConstants::texture_integer_scale_bits).
```
