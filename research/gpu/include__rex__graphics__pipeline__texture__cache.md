# Cache: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/texture/cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L31)

```text
// Manages host copies of guest textures, performing untiling, format and endian
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L32)

```text
// conversion of textures stored in the shared memory, and also handling
```

## Source note 3, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L33)

```text
// invalidation.
```

## Source note 4, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L35)

```text
// Mipmaps are treated the following way, according to the GPU hang message
```

## Source note 5, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L36)

```text
// found in game executables explaining the valid usage of BaseAddress when
```

## Source note 6, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L37)

```text
// streaming the largest LOD (it says games should not use 0 as the base address
```

## Source note 7, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L38)

```text
// when the largest LOD isn't loaded, but rather, either allocate a valid
```

## Source note 8, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L39)

```text
// address for it or make it the same as mip_address):
```

## Source note 9, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L40)

```text
// - If the texture has a base address, but no mip address, it's not mipmapped -
```

## Source note 10, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L41)

```text
//   the host texture has only the largest level too.
```

## Source note 11, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L42)

```text
// - If the texture has different non-zero base address and mip address, a host
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L43)

```text
//   texture with mip_max_level+1 mipmaps is created - mip_min_level is ignored
```

## Source note 13, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L44)

```text
//   and treated purely as sampler state because there are tfetch instructions
```

## Source note 14, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L45)

```text
//   working directly with LOD values - including fetching with an explicit LOD.
```

## Source note 15, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L46)

```text
//   However, the max level is not ignored because any mip count can be
```

## Source note 16, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L47)

```text
//   specified when creating a texture, and another texture may be placed after
```

## Source note 17, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L48)

```text
//   the last one.
```

## Source note 18, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L49)

```text
// - If the texture has a mip address, but the base address is 0 or the same as
```

## Source note 19, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L50)

```text
//   the mip address, a mipmapped texture is created, but min/max LOD is clamped
```

## Source note 20, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L51)

```text
//   to the lower bound of 1 - the game is expected to do that anyway until the
```

## Source note 21, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L52)

```text
//   largest LOD is loaded.
```

## Source note 22, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L56)

```text
// Hard limit, originating from the half-pixel offset filling hack in the
```

## Source note 23, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L57)

```text
// resolve shaders only filling up to 3 pixels, due to the bit counts used for
```

## Source note 24, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L58)

```text
// passing the scale to shaders, and because the full 490 MB EDRAM buffer is
```

## Source note 25, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L59)

```text
// within the minimum Direct3D 12 requirement of 128 * 2^20 texels in a single
```

## Source note 26, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L60)

```text
// buffer binding (counted as R32 for a byte address buffer).
```

## Source note 27, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L67)

```text
// Returns whether the actual scale is not smaller than the requested one.
```

## Source note 28, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L82)

```text
// A resolve that wrote this range at the guest's size (ADR-012): pages it
```

## Source note 29, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L83)

```text
// covers whole are no longer scaled, so textures there read the unscaled
```

## Source note 30, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L84)

```text
// data. A page it only partly covers keeps the scaled copy, which the
```

## Source note 31, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L85)

```text
// resolve also wrote.
```

## Source note 32, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L87)

```text
// Whether any page of the range holds a scaled resolve, so its data is the
```

## Source note 33, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L88)

```text
// scaled copy rather than shared memory.
```

## Source note 34, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L92)

```text
// Ensures the memory backing the range in the scaled resolve address space is
```

## Source note 35, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L93)

```text
// allocated and returns whether it is.
```

## Source note 36, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L94)

```text
/*start_unscaled*/
```

## Source note 37, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L95)

```text
/*length_unscaled*/
```

## Source note 38, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L96)

```text
/*length_scaled_alignment_log2*/
```

## Source note 39, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L122)

```text
// "ActiveTexture" means as of the latest RequestTextures call.
```

## Source note 40, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L147)

```text
// Dimensions minus 1 are stored similarly to how they're stored in fetch
```

## Source note 41, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L148)

```text
// constants so fewer bits can be used, while the maximum size (8192 for 2D)
```

## Source note 42, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L149)

```text
// can still be encoded (a 8192x sky texture is used in 4D530910).
```

## Source note 43, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L151)

```text
// Physical 4 KB page with the base mip level, disregarding A/C/E address
```

## Source note 44, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L152)

```text
// range prefix.
```

## Source note 45, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L153)

```text
// 17 total
```

## Source note 46, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L154)

```text
// 19
```

## Source note 47, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L155)

```text
// 32
```

## Source note 48, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L157)

```text
// 45
```

## Source note 49, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L158)

```text
// 46
```

## Source note 50, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L159)

```text
// 47
```

## Source note 51, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L160)

```text
// Physical 4 KB page with mip 1 and smaller.
```

## Source note 52, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L161)

```text
// 64
```

## Source note 53, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L163)

```text
// (Layers for stacked and 3D, 6 for cube, 1 for other dimensions) - 1.
```

## Source note 54, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L164)

```text
// 74
```

## Source note 55, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L165)

```text
// 83
```

## Source note 56, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L166)

```text
// 87
```

## Source note 57, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L167)

```text
// 93
```

## Source note 58, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L168)

```text
// 95
```

## Source note 59, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L169)

```text
// Whether this texture is signed and has a different host representation
```

## Source note 60, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L170)

```text
// than an unsigned view of the same guest texture.
```

## Source note 61, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L171)

```text
// 96
```

## Source note 62, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L173)

```text
// Whether this texture is a resolution-scaled resolve target.
```

## Source note 63, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L174)

```text
// 97
```

## Source note 64, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L175)

```text
// Least important in ==, so placed last.
```

## Source note 65, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L176)

```text
// 98
```

## Source note 66, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L185)

```text
// Zero everything, including the padding, for a stable hash.
```

## Source note 67, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L222)

```text
// For 3D-as-2D wrappers: the host texture is 2D, but guest memory tiling
```

## Source note 68, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L223)

```text
// may still need to be interpreted as 3D.
```

## Source note 69, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L245)

```text
// For LRU caching - updates the last usage frame and moves the texture to
```

## Source note 70, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L246)

```text
// the end of the usage queue. Must be called any time the texture is
```

## Source note 71, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L247)

```text
// referenced by any GPU work in the implementation to make sure it's not
```

## Source note 72, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L248)

```text
// destroyed while still in use.
```

## Source note 73, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L254)

```text
// If track_usage is false, the texture won't be added to the LRU list.
```

## Source note 74, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L278)

```text
// These are to be accessed within the global critical region to synchronize
```

## Source note 75, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L279)

```text
// with shared memory.
```

## Source note 76, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L280)

```text
// Whether the recent base level data needs reloading from the memory.
```

## Source note 77, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L282)

```text
// Whether the recent mip data needs reloading from the memory.
```

## Source note 78, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L285)

```text
// Watch handles for the memory ranges.
```

## Source note 79, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L290)

```text
// Rules of data access in load shaders:
```

## Source note 80, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L291)

```text
// - Source reading (from the shared memory or the scaled resolve buffer):
```

## Source note 81, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L292)

```text
//   - Guest data may be stored in a sparsely-allocated buffer, or, in
```

## Source note 82, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L293)

```text
//     Direct3D 12 terms, a tiled buffer. This means that some regions of the
```

## Source note 83, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L294)

```text
//     buffer may not be mapped. On tiled resources tier 1 hardware, accessing
```

## Source note 84, line 295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L295)

```text
//     unmapped tiles results in undefined behavior, including a GPU page
```

## Source note 85, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L296)

```text
//     fault and device removal. So, shaders must not try to access
```

## Source note 86, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L297)

```text
//     potentially unmapped regions (that are outside the texture memory
```

## Source note 87, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L298)

```text
//     extents calculated on the CPU, taking into account that Xenia can't
```

## Source note 88, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L299)

```text
//     overestimate texture sizes freely since it must not try to upload
```

## Source note 89, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L300)

```text
//     unallocated pages on the CPU).
```

## Source note 90, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L301)

```text
//   - Buffer tiles have 64 KB size on Direct3D 12. Vulkan has its own
```

## Source note 91, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L302)

```text
//     alignment requirements for sparse binding. But overall, we're
```

## Source note 92, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L303)

```text
//     allocating pretty large regions.
```

## Source note 93, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L304)

```text
//   - Resolution scaling disabled:
```

## Source note 94, line 305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L305)

```text
//     - Shared memory allocates regions of power of two sizes that map
```

## Source note 95, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L306)

```text
//       directly to the same portions of the 512 MB of the console's
```

## Source note 96, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L307)

```text
//       physical memory. So, a 64 KB-aligned host buffer region is also 64
```

## Source note 97, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L308)

```text
//       KB-aligned in the guest address space.
```

## Source note 98, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L309)

```text
//     - Tiled textures: 32x32x4-block tiles are always resident each as a
```

## Source note 99, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L310)

```text
//       whole. If the width is bigger than the pitch, the overflowing 32x32x4
```

## Source note 100, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L311)

```text
//       tiles are also loaded as entire tiles. We do not have separate
```

## Source note 101, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L312)

```text
//       shaders for 2D and 3D. So, for tiled textures, it's safe to consider
```

## Source note 102, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L313)

```text
//       that if any location within a 32x32-aligned portion is within the
```

## Source note 103, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L314)

```text
//       texture bounds, the entire 32x32 portion also can be read.
```

## Source note 104, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L315)

```text
//     - Linear textures: Pitch is aligned to 256 bytes. Row count, however,
```

## Source note 105, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L316)

```text
//       is not aligned to anything (unless the mip tail is being loaded). The
```

## Source note 106, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L317)

```text
//       overflowing last row in case `width > pitch`, however, is made
```

## Source note 107, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L318)

```text
//       resident up to the last texel in it. But row start alignment is 256,
```

## Source note 108, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L319)

```text
//       which is a power of two, and is smaller than the Direct3D 12 tile
```

## Source note 109, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L320)

```text
//       size of 64 KB. So, if any block within a 256-aligned region is within
```

## Source note 110, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L321)

```text
//       the texture bounds, without resolution scaling, reading from any
```

## Source note 111, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L322)

```text
//       location in that 256-aligned region is safe.
```

## Source note 112, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L323)

```text
//     - Since we use the same shaders for tiled and linear textures (as well
```

## Source note 113, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L324)

```text
//       as 1D textures), this means that without resolution scaling, it's
```

## Source note 114, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L325)

```text
//       safe to access a min(256 bytes, 32 blocks)-aligned portion along X,
```

## Source note 115, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L326)

```text
//       but only within the same row of blocks, with bounds checking only for
```

## Source note 116, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L327)

```text
//       such portion as a whole, but without additional bounds checking
```

## Source note 117, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L328)

```text
//       inside of it.
```

## Source note 118, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L329)

```text
//     - Therefore, it's recommended that shaders read power-of-two amounts of
```

## Source note 119, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L330)

```text
//       blocks (so there will naturally be some alignment to some power of
```

## Source note 120, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L331)

```text
//       two), and this way, each thread may read at most 16 16bpb blocks or
```

## Source note 121, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L332)

```text
//       at most 32 8bpb or smaller blocks with in a single `if (x < width)`
```

## Source note 122, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L333)

```text
//       for the whole aligned range of the same length.
```

## Source note 123, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L334)

```text
//   - Resolution scaling enabled:
```

## Source note 124, line 335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L335)

```text
//     - For simplicity, unlike in the shared memory, buffer tile boundaries
```

## Source note 125, line 336

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L336)

```text
//       are not aligned to powers of 2 the same way as guest addresses are.
```

## Source note 126, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L337)

```text
//       While for 2x2 resolution scaling it still happens to be the case
```

## Source note 127, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L338)

```text
//       because `host scaling unit address = guest scaling unit address << 2`
```

## Source note 128, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L339)

```text
//       (similarly for 2x1 and 1x2), for 3x or x3, it's not - a 64 KB host
```

## Source note 129, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L340)

```text
//       tile would represent 7281.777 guest bytes with 3x3 (disregarding that
```

## Source note 130, line 341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L341)

```text
//       sequences of texels that are adjacent in memory alongside the
```

## Source note 131, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L342)

```text
//       horizontal axis, not individual bytes, are scaled, but even in that
```

## Source note 132, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L343)

```text
//       case it's not scaling by 2^n still).
```

## Source note 133, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L344)

```text
//     - The above would affect the `width > pitch` case for linear textures,
```

## Source note 134, line 345

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L345)

```text
//       requiring overestimating the width in calculation of the range of the
```

## Source note 135, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L346)

```text
//       tiles to map, while not doing this overestimation on the guest memory
```

## Source note 136, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L347)

```text
//       extent calculation side (otherwise it may result in attempting to
```

## Source note 137, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L348)

```text
//       upload unallocated memory on the CPU). For example, let's take look
```

## Source note 138, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L349)

```text
//       at an extreme case of a 369x28 k_8 texture with a pitch of 256 bytes.
```

## Source note 139, line 350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L350)

```text
//       The last row, in guest memory, would be loaded from the [7168, 7281)
```

## Source note 140, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L351)

```text
//       range, or, with 3x3 resolution scaling, from bytes [64512, 65529).
```

## Source note 141, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L352)

```text
//       However, if we try to unconditionally load 2 pixels, like the texture
```

## Source note 142, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L353)

```text
//       is 370x28, we will be accessing the bytes [64512, 65538). But bytes
```

## Source note 143, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L354)

```text
//       65536 and 65537 will be in another 64 KB tile, which may be not
```

## Source note 144, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L355)

```text
//       mapped yet. However, none of this is an issue for one simple reason -
```

## Source note 145, line 356

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L356)

```text
//       resolving is only possible to tiled textures, so linear textures will
```

## Source note 146, line 357

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L357)

```text
//       never be resolution-scaled.
```

## Source note 147, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L358)

```text
//     - Tiled textures have potentially referenced guest 32x32-block tiles
```

## Source note 148, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L359)

```text
//       loaded in their entirety. So, just like for unscaled textures, if any
```

## Source note 149, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L360)

```text
//       block within a tile is available, the entire tile is as well.
```

## Source note 150, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L361)

```text
// - Destination writing (to the linear buffer):
```

## Source note 151, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L362)

```text
//   - host_x_blocks_per_thread specifies how many pixels can be written
```

## Source note 152, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L363)

```text
//     without bounds checking within increments of that amount - the pitch of
```

## Source note 153, line 364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L364)

```text
//     the destination buffer is manually overaligned if needed.
```

## Source note 154, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L366)

```text
// In textures, resolution scaling is done for 8-byte portions of memory for
```

## Source note 155, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L367)

```text
// 8bpp textures, and for 16-byte portions for textures of higher bit depths
```

## Source note 156, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L368)

```text
// (these are the sizes of regions where contiguous texels in memory are also
```

## Source note 157, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L369)

```text
// contiguous in the texture along the horizontal axis, so 64-bit and 128-bit
```

## Source note 158, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L370)

```text
// loads / stores, for 8bpp and 16bpp+ respectively, can be used for untiling
```

## Source note 159, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L371)

```text
// regardless of the resolution scale).
```

## Source note 160, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L375)

```text
// Base offset in bytes, resolution-scaled.
```

## Source note 161, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L377)

```text
// For tiled textures - row pitch in blocks, aligned to 32, unscaled.
```

## Source note 162, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L378)

```text
// For linear textures - row pitch in bytes.
```

## Source note 163, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L380)

```text
// For 3D textures only (ignored otherwise) - aligned to 32, unscaled.
```

## Source note 164, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L383)

```text
// - std140 vector boundary -
```

## Source note 165, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L385)

```text
// If this is a packed mip tail, this is aligned to tile dimensions.
```

## Source note 166, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L386)

```text
// Resolution-scaled.
```

## Source note 167, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L388)

```text
// Base offset in bytes.
```

## Source note 168, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L391)

```text
// - std140 vector boundary -
```

## Source note 169, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L444)

```text
// Log2 of the sizes, in bytes, of the elements in the source (guest) and
```

## Source note 170, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L445)

```text
// the destination (host) buffer bindings accessed by the copying shader,
```

## Source note 171, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L446)

```text
// since the shader may copy multiple blocks per one invocation.
```

## Source note 172, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L449)

```text
// Number of bytes in a host resolution-scaled block (corresponding to a
```

## Source note 173, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L450)

```text
// guest block if not decompressing, or a host texel if decompressing)
```

## Source note 174, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L451)

```text
// written by the shader.
```

## Source note 175, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L453)

```text
// Log2 of the number of guest resolution-scaled blocks along the X axis
```

## Source note 176, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L454)

```text
// loaded by a single thread shader group.
```

## Source note 177, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L467)

```text
// Packed fixed texture conversion for the fetch shader, see
```

## Source note 178, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L468)

```text
// texture_util::GetIntegerScaleBits.
```

## Source note 179, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L470)

```text
// Destination swizzle merged with guest to host format swizzle.
```

## Source note 180, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L472)

```text
// Packed TextureSign values, 2 bit per each component, with guest-side
```

## Source note 181, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L473)

```text
// destination swizzle from the fetch constant applied to them.
```

## Source note 182, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L475)

```text
// Unsigned version of the texture (or signed if they have the same data).
```

## Source note 183, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L477)

```text
// Signed version of the texture if the data in the signed version is
```

## Source note 184, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L478)

```text
// different on the host.
```

## Source note 185, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L496)

```text
// May be called for purposes like clearing the cache, as well as in the
```

## Source note 186, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L497)

```text
// destructor of the implementation if textures, for instance, have references
```

## Source note 187, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L498)

```text
// to the implementation that are used in their destructor, and will become
```

## Source note 188, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L499)

```text
// invalid if the implementation is destroyed before the texture.
```

## Source note 189, line 502

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L502)

```text
// Whether the signed version of the texture has a different representation on
```

## Source note 190, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L503)

```text
// the host than its unsigned version (for example, if it's a fixed-point
```

## Source note 191, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L504)

```text
// texture emulated with a larger host pixel format).
```

## Source note 192, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L505)

```text
/*key*/
```

## Source note 193, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L506)

```text
// Parameters like whether the texture is tiled and its dimensions are checked
```

## Source note 194, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L507)

```text
// externally, the implementation should take only format-related parameters
```

## Source note 195, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L508)

```text
// such as the format itself and the signedness into account.
```

## Source note 196, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L509)

```text
/*key*/
```

## Source note 197, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L510)

```text
// For formats with less than 4 components, implementations normally should
```

## Source note 198, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L511)

```text
// replicate the last component into the non-existent ones, similar to what is
```

## Source note 199, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L512)

```text
// done for unused components of operands in shaders by Microsoft's Xbox 360
```

## Source note 200, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L513)

```text
// shader compiler (.xxxx, .xyyy, .xyzz, .xyzw).
```

## Source note 201, line 514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L514)

```text
// For DXT3A and DXT5A, RRRR swizzle is specified in:
```

## Source note 202, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L515)

```text
// http://fileadmin.cs.lth.se/cs/Personal/Michael_Doggett/talks/unc-xenos-doggett.pdf
```

## Source note 203, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L516)

```text
// 4D5307E6 also expects replicated components in k_8 sprites.
```

## Source note 204, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L517)

```text
// DXN is read as RG in 4D5307E6, but as RA in 415607E6.
```

## Source note 205, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L524)

```text
// The texture must be created exactly with this key (if the implementation
```

## Source note 206, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L525)

```text
// supports the texture with this key, otherwise, or in case of a runtime
```

## Source note 207, line 526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L526)

```text
// failure, it should return nullptr), modifying it is not allowed.
```

## Source note 208, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L529)

```text
// Returns nullptr not only if the key is not supported, but also if couldn't
```

## Source note 209, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L530)

```text
// create the texture - if it's nullptr, occasionally a recreation attempt
```

## Source note 210, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L531)

```text
// should be made.
```

## Source note 211, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L539)

```text
// Writes the texture data (for base, mips or both - but not neither) from the
```

## Source note 212, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L540)

```text
// shared memory or the scaled resolve memory. The shared memory management is
```

## Source note 213, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L541)

```text
// done outside this function, the implementation just needs to load the data
```

## Source note 214, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L542)

```text
// into the texture object.
```

## Source note 215, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L546)

```text
// Converts a texture fetch constant to a texture key, normalizing and
```

## Source note 216, line 547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L547)

```text
// validating the values, or creating an invalid key, and also gets the
```

## Source note 217, line 548

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L548)

```text
// post-guest-swizzle signedness.
```

## Source note 218, line 552

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L552)

```text
// Makes all texture bindings invalid. Also requesting textures after calling
```

## Source note 219, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L553)

```text
// this will cause another attempt to create a texture or to untile it if
```

## Source note 220, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L554)

```text
// there was an error.
```

## Source note 221, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L561)

```text
// Called when something in a texture binding is changed for the
```

## Source note 222, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L562)

```text
// implementation to update the internal dependencies of the binding.
```

## Source note 223, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L563)

```text
/*fetch_constant_mask*/
```

## Source note 224, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L582)

```text
// Shared memory callback for texture data invalidation.
```

## Source note 225, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L586)

```text
// Checks if there are any pages that contain scaled resolve data within the
```

## Source note 226, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L587)

```text
// range.
```

## Source note 227, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L589)

```text
// Global shared memory invalidation callback for invalidating scaled resolved
```

## Source note 228, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L590)

```text
// texture data.
```

## Source note 229, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L606)

```text
// Bit vector storing whether each 4 KB physical memory page contains scaled
```

## Source note 230, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L607)

```text
// resolve data. uint32_t rather than uint64_t because parts of it can be sent
```

## Source note 231, line 608

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L608)

```text
// to shaders.
```

## Source note 232, line 610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L610)

```text
// Second level of the bit vector for faster rejection of non-scaled textures.
```

## Source note 233, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L611)

```text
// >> 12 for 4 KB pages, >> 5 for uint32_t level 1 bits, >> 6 for uint64_t
```

## Source note 234, line 612

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L612)

```text
// level 2 bits.
```

## Source note 235, line 615

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L615)

```text
// Global watch for scaled resolve data invalidation.
```

## Source note 236, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L628)

```text
// Whether a texture has become outdated (a memory watch has been triggered),
```

## Source note 237, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L629)

```text
// so need to recheck if textures aren't outdated, disregarding whether fetch
```

## Source note 238, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L630)

```text
// constants have been changed.
```

## Source note 239, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L634)

```text
// Bit vector with bits reset on fetch constant writes to avoid parsing fetch
```

## Source note 240, line 635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/texture/cache.h#L635)

```text
// constants again and again.
```
