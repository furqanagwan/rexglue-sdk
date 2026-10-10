# Dxbc translator fetch: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/dxbc_translator_fetch.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L44)

```text
// If this is vfetch_full, the address may still be needed for vfetch_mini -
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L45)

```text
// don't exit before calculating the address.
```

## Source note 3, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L47)

```text
// Nothing to load - just constant 0/1 writes, or the swizzle includes only
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L48)

```text
// components that don't exist in the format (writing zero instead of them).
```

## Source note 5, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L49)

```text
// Unpacking assumes at least some word is needed.
```

## Source note 6, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L54)

```text
// Create a 2-component dxbc::Src for the fetch constant (vf0 is in [0].xy of
```

## Source note 7, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L55)

```text
// the fetch constants array, vf1 is in [0].zw, vf2 is in [1].xy).
```

## Source note 8, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L64)

```text
// - Load the part of the byte address in the physical memory that is the same
```

## Source note 9, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L65)

```text
//   in vfetch_full and vfetch_mini to system_temp_grad_v_vfetch_address_.w
```

## Source note 10, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L66)

```text
//   (the index operand GPR must not be reloaded in vfetch_mini because it
```

## Source note 11, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L67)

```text
//   might have been overwritten previously, but that shouldn't have effect on
```

## Source note 12, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L68)

```text
//   vfetch_mini).
```

## Source note 13, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L74)

```text
// Convert the index to an integer by flooring or by rounding to the
```

## Source note 14, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L75)

```text
// nearest (as floor(index + 0.5) because rounding to the nearest even
```

## Source note 15, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L76)

```text
// makes no sense for addressing, both 1.5 and 2.5 would be 2).
```

## Source note 16, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L92)

```text
// Extract the byte address from the fetch constant to
```

## Source note 17, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L93)

```text
// system_temp_result_.w (which is not used yet).
```

## Source note 18, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L96)

```text
// Merge the index and the base address.
```

## Source note 19, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L101)

```text
// Fetching from the same location - extract the byte address of the
```

## Source note 20, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L102)

```text
// beginning of the buffer.
```

## Source note 21, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L108)

```text
// The vfetch_full address has been loaded for the subsequent vfetch_mini,
```

## Source note 22, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L109)

```text
// but there's no data to load.
```

## Source note 23, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L117)

```text
// - From now on, if any additional offset must be applied to the
```

## Source note 24, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L118)

```text
//   `base + index * stride` part of the address, it must be done by writing
```

## Source note 25, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L119)

```text
//   to system_temp_result_.w (address_temp_dest) instead of
```

## Source note 26, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L120)

```text
//   system_temp_grad_v_vfetch_address_.w (since it must stay the same for the
```

## Source note 27, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L121)

```text
//   vfetch_full and all its vfetch_mini invocations), and changing
```

## Source note 28, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L122)

```text
//   address_src to address_temp_src afterwards. system_temp_result_.w can be
```

## Source note 29, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L123)

```text
//   used for this purpose safely because it won't be overwritten until the
```

## Source note 30, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L124)

```text
//   last dword is loaded (after which the address won't be needed anymore).
```

## Source note 31, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L126)

```text
// Add the word offset from the instruction (signed), plus the offset of the
```

## Source note 32, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L127)

```text
// first needed word within the element.
```

## Source note 33, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L132)

```text
// Add the constant word offset.
```

## Source note 34, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L138)

```text
// - Load needed words to system_temp_result_, words 0, 1, 2, 3 to X, Y, Z, W
```

## Source note 35, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L139)

```text
//   respectively.
```

## Source note 36, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L141)

```text
// Loading the FXC way, Load4.xyw becomes Load2 and Load - would be a
```

## Source note 37, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L142)

```text
// compromise between AMD, where there are load_dwordx2/3/4, and Nvidia, where
```

## Source note 38, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L143)

```text
// a ByteAddressBuffer is more like an R32_UINT buffer.
```

## Source note 39, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L145)

```text
// Depending on whether the shared memory is bound as an SRV or as a UAV (if
```

## Source note 40, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L146)

```text
// memexport is used), fetch from the appropriate binding. Extract whether
```

## Source note 41, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L147)

```text
// shared memory is a UAV to system_temp_result_.x and check. In the `if`, put
```

## Source note 42, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L148)

```text
// the more likely case (SRV), in the `else`, the less likely one (UAV).
```

## Source note 43, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L174)

```text
// Go to the word in the buffer.
```

## Source note 44, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L180)

```text
// Can ld_raw either to the first multiple components, or to any scalar
```

## Source note 45, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L181)

```text
// component.
```

## Source note 46, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L185)

```text
// Read directly to system_temp_result_.
```

## Source note 47, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L188)

```text
// Read to the first components of a temporary register.
```

## Source note 48, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L191)

```text
// Copy to system_temp_result_.
```

## Source note 49, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L195)

```text
// Release load_temp.
```

## Source note 50, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L204)

```text
// - Endian swap the words.
```

## Source note 51, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L209)

```text
// Extract the endianness from the fetch constant.
```

## Source note 52, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L226)

```text
// 8-in-16 or one half of 8-in-32.
```

## Source note 53, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L230)

```text
// Temp = X0Z0.
```

## Source note 54, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L232)

```text
// Result = YZW0.
```

## Source note 55, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L234)

```text
// Result = Y0W0.
```

## Source note 56, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L236)

```text
// Result = YXWZ.
```

## Source note 57, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L241)

```text
// 16-in-32 or another half of 8-in-32.
```

## Source note 58, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L245)

```text
// Temp = ZW00.
```

## Source note 59, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L247)

```text
// Result = ZWXY.
```

## Source note 60, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L252)

```text
// Release endian_temp (if allocated) and swap_temp.
```

## Source note 61, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L256)

```text
// - Unpack the format.
```

## Source note 62, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L262)

```text
// If needed_words is not zero (checked in the beginning), this must not be
```

## Source note 63, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L263)

```text
// zero too. For simplicity, it's assumed that something will be unpacked
```

## Source note 64, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L264)

```text
// here.
```

## Source note 65, line 304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L304)

```text
// Not a packed integer format.
```

## Source note 66, line 308

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L308)

```text
// Handle packed integer formats.
```

## Source note 67, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L331)

```text
// Treat both -(2^(n-1)) and -(2^(n-1)-1) as -1.
```

## Source note 68, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L395)

```text
// No need to clamp to -1 if signed - 1/(2^31-1) is rounded to
```

## Source note 69, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L396)

```text
// 1/(2^31) as float32.
```

## Source note 70, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L414)

```text
// Already in the needed result components.
```

## Source note 71, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L417)

```text
// Packed integer or unknown format.
```

## Source note 72, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L423)

```text
// - Apply the exponent bias.
```

## Source note 73, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L430)

```text
// - Write zeros to components not present in the format.
```

## Source note 74, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L443)

```text
// 1D and 2D textures (including stacked ones) are treated as 2D arrays for
```

## Source note 75, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L444)

```text
// binding and coordinate simplicity.
```

## Source note 76, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L483)

```text
// Consistently 0 if not bindless as it may be used for hashing.
```

## Source note 77, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L496)

```text
// In Direct3D 12, anisotropic filtering implies linear filtering.
```

## Source note 78, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L520)

```text
// Consistently 0 if not bindless as it may be used for hashing.
```

## Source note 79, line 618

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L618)

```text
// Handle instructions for setting register LOD.
```

## Source note 80, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L652)

```text
// Handle instructions that store something.
```

## Source note 81, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L660)

```text
// Nothing to fetch, only constant 0/1 writes.
```

## Source note 82, line 666

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L666)

```text
// Handle before doing anything that actually needs the texture.
```

## Source note 83, line 690

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L690)

```text
// Handle instructions that need the coordinates, the fetch constant, the LOD
```

## Source note 84, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L691)

```text
// and possibly the SRV - kTextureFetch, kGetTextureBorderColorFrac,
```

## Source note 85, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L692)

```text
// kGetTextureComputedLod, kGetTextureWeights.
```

## Source note 86, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L700)

```text
// All host components contribute, even when the guest only writes X.
```

## Source note 87, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L716)

```text
// Whether to use gradients (implicit or explicit) for LOD calculation.
```

## Source note 88, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L728)

```text
// Texel center snap instead of the epsilon, see CanSnapToTexelCenter.
```

## Source note 89, line 731

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L731)

```text
// Get offsets applied to the coordinates before sampling.
```

## Source note 90, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L732)

```text
// `offsets` is used for float4 literal construction,
```

## Source note 91, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L735)

```text
// MSDN doesn't list offsets as getCompTexLOD parameters.
```

## Source note 92, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L737)

```text
// Add a small epsilon to the offset (1.5/4 the fixed-point texture
```

## Source note 93, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L738)

```text
// coordinate ULP - shouldn't significantly effect the fixed-point
```

## Source note 94, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L739)

```text
// conversion; 1/4 is also not enough with 3x resolution scaling very
```

## Source note 95, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L740)

```text
// noticeably on the weapon in 4D5307E6) to resolve ambiguity when fetching
```

## Source note 96, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L741)

```text
// point-sampled textures between texels. This applies to both normalized
```

## Source note 97, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L742)

```text
// (58410954 Xbox Live Arcade logo, coordinates interpolated between
```

## Source note 98, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L743)

```text
// vertices with half-pixel offset) and unnormalized (4D5307E6 lighting
```

## Source note 99, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L744)

```text
// G-buffer reading, ps_param_gen pixels) coordinates. On Nvidia Pascal,
```

## Source note 100, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L745)

```text
// without this adjustment, blockiness is visible in both cases. Possibly
```

## Source note 101, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L746)

```text
// there is a better way, however, an attempt was made to error-correct
```

## Source note 102, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L747)

```text
// division by adding the difference between original and re-denormalized
```

## Source note 103, line 748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L748)

```text
// coordinates, but on Nvidia, `mul` and internal multiplication in texture
```

## Source note 104, line 749

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L749)

```text
// sampling apparently round differently, so `mul` gives a value that would
```

## Source note 105, line 750

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L750)

```text
// be floored as expected, but the left/upper pixel is still sampled
```

## Source note 106, line 751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L751)

```text
// instead.
```

## Source note 107, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L757)

```text
// For coordinate lerp factors. This needs to be done separately for
```

## Source note 108, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L758)

```text
// point mag/min filters, but they're currently not handled here
```

## Source note 109, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L759)

```text
// anyway.
```

## Source note 110, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L782)

```text
// Applying the rounding epsilon to cube maps too for potential game
```

## Source note 111, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L783)

```text
// passes processing cube map faces themselves.
```

## Source note 112, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L789)

```text
// The logic for ST weights is the same for all faces.
```

## Source note 113, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L805)

```text
// Load the texture size if needed.
```

## Source note 114, line 806

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L806)

```text
// 1D: X - width.
```

## Source note 115, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L807)

```text
// 2D, cube: X - width, Y - height (cube maps probably can be only square, but
```

## Source note 116, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L808)

```text
//           for simplicity).
```

## Source note 117, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L809)

```text
// 3D: X - width, Y - height, Z - depth, W - 0 if stacked 2D, 1 if 3D.
```

## Source note 118, line 812

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L812)

```text
// Size needed for denormalization for coordinate lerp factor.
```

## Source note 119, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L817)

```text
// Always need size for 1D textures to support wide 1D textures.
```

## Source note 120, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L830)

```text
// Size needed for normalization (or, for stacked texture layers,
```

## Source note 121, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L831)

```text
// denormalization) and for offsets.
```

## Source note 122, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L843)

```text
// Stacked and 3D textures are fetched from different SRVs - the check
```

## Source note 123, line 844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L844)

```text
// is always needed.
```

## Source note 124, line 847

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L847)

```text
// Need to normalize all (if 3D).
```

## Source note 125, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L850)

```text
// Need to denormalize Z (if stacked).
```

## Source note 126, line 858

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L858)

```text
// The size is not needed for face ID offset.
```

## Source note 127, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L864)

```text
// Stacked and 3D textures have different size packing - need to get whether
```

## Source note 128, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L865)

```text
// the texture is 3D unconditionally.
```

## Source note 129, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L905)

```text
// tfetch3D is used for both stacked and 3D - first, check if 3D.
```

## Source note 130, line 912

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L912)

```text
// Even if depth isn't needed specifically for stacked or specifically
```

## Source note 131, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L913)

```text
// for 3D later, load both cases anyway to make sure the register is
```

## Source note 132, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L914)

```text
// always initialized.
```

## Source note 133, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L916)

```text
// Load the 3D texture size.
```

## Source note 134, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L921)

```text
// Load the 2D stacked texture size.
```

## Source note 135, line 930

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L930)

```text
// Fetch constants store size minus 1 - add 1.
```

## Source note 136, line 933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L933)

```text
// Convert the size to float for multiplication/division.
```

## Source note 137, line 946

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L946)

```text
// Need unnormalized coordinates.
```

## Source note 138, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L951)

```text
// If needed, apply the resolution scale to the width / height and the
```

## Source note 139, line 952

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L952)

```text
// unnormalized coordinates.
```

## Source note 140, line 963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L963)

```text
// Use system_temp_result_ as a temporary for conditionally
```

## Source note 141, line 964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L964)

```text
// resolution-scaled coordinates.
```

## Source note 142, line 968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L968)

```text
// Using system_temp_result_.w as a temporary for the flag indicating
```

## Source note 143, line 969

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L969)

```text
// whether the texture is resolution-scaled - not involved in coordinate
```

## Source note 144, line 970

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L970)

```text
// calculations.
```

## Source note 145, line 978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L978)

```text
// The texture is resolution-scaled - scale the coordinates and the size.
```

## Source note 146, line 993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L993)

```text
// Using system_temp_result_ as a temporary for coordinate denormalization
```

## Source note 147, line 994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L994)

```text
// and offsetting. May already contain the coordinates loaded if
```

## Source note 148, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L995)

```text
// resolution scaling was applied to the coordinates.
```

## Source note 149, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1012)

```text
// 0.5 has already been subtracted via offsets previously.
```

## Source note 150, line 1018

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1018)

```text
// - Component signedness, for selecting the SRV, and if data is needed.
```

## Source note 151, line 1033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1033)

```text
// - Coordinates.
```

## Source note 152, line 1035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1035)

```text
// Will need a temporary in all cases:
```

## Source note 153, line 1036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1036)

```text
// - 1D, 2D array - need to be padded to 2D array coordinates.
```

## Source note 154, line 1037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1037)

```text
// - 3D - Z needs to be unnormalized for stacked and normalized for 3D.
```

## Source note 155, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1038)

```text
// - Cube - coordinates need to be transformed into the cube space.
```

## Source note 156, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1039)

```text
// Bindless sampler index will be loaded to W after loading the coordinates
```

## Source note 157, line 1040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1040)

```text
// (so W can be used as a temporary for coordinate loading).
```

## Source note 158, line 1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1043)

```text
// Need normalized coordinates (except for Z - keep it as is, will be
```

## Source note 159, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1044)

```text
// converted later according to whether the texture is 3D). For cube maps,
```

## Source note 160, line 1045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1045)

```text
// coordinates need to be transformed back into the cube space.
```

## Source note 161, line 1070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1070)

```text
// Some titles might provide non-finite stacked coordinates, like 584107FB's
```

## Source note 162, line 1071

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1071)

```text
// backdrop which doesn't render unless the offset path is clamped. For
```

## Source note 163, line 1072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1072)

```text
// safety, no-offset is clamped as well, with both preserving stacked
```

## Source note 164, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1073)

```text
// layer-center rules.
```

## Source note 165, line 1074

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1074)

```text
// Source: xenia-canary #1252 (04085efaafcfb8907749f200514c21433db2ebeb).
```

## Source note 166, line 1076

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1076)

```text
// Unnormalized coordinates - normalize XY, and if 3D, normalize Z.
```

## Source note 167, line 1080

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1080)

```text
// Apply the offsets to components to normalize where needed, or just
```

## Source note 168, line 1081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1081)

```text
// copy the components to coord_and_sampler_temp where not.
```

## Source note 169, line 1084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1084)

```text
// Using coord_and_sampler_temp.w as a temporary for the needed
```

## Source note 170, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1085)

```text
// resolution scale inverse - sampler not loaded yet.
```

## Source note 171, line 1114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1114)

```text
// Normalize if 3D or clamp to layer centers if stacked.
```

## Source note 172, line 1138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1138)

```text
// Don't normalize if stacked and clamp to layer centers.
```

## Source note 173, line 1158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1158)

```text
// Normalized coordinates - apply offsets to XY or copy them to
```

## Source note 174, line 1159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1159)

```text
// coord_and_sampler_temp, and if stacked, denormalize Z.
```

## Source note 175, line 1166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1166)

```text
// Using coord_and_sampler_temp.w as a temporary for the needed
```

## Source note 176, line 1167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1167)

```text
// resolution scale inverse - sampler not loaded yet.
```

## Source note 177, line 1190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1190)

```text
// 3D/stacked without offset is handled separately.
```

## Source note 178, line 1199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1199)

```text
// Denormalize and offset Z (re-apply the offset not to lose precision
```

## Source note 179, line 1200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1200)

```text
// as a result of division) if stacked.
```

## Source note 180, line 1218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1218)

```text
// Denormalize Z if stacked, and revert to normalized if 3D.
```

## Source note 181, line 1255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1255)

```text
// Transform from the major axis SC/TC plus 1 into cube coordinates.
```

## Source note 182, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1256)

```text
// Move SC/TC from 1...2 to -1...1.
```

## Source note 183, line 1259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1259)

```text
// Get the face index (floored, within 0...5) as an integer to
```

## Source note 184, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1260)

```text
// coord_and_sampler_temp.z.
```

## Source note 185, line 1272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1272)

```text
// Split the face index into axis and sign (0 - positive, 1 - negative)
```

## Source note 186, line 1273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1273)

```text
// to coord_and_sampler_temp.zw (sign in W so it won't be overwritten).
```

## Source note 187, line 1274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1274)

```text
// Fine to overwrite W at this point, the sampler index hasn't been
```

## Source note 188, line 1275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1275)

```text
// loaded yet.
```

## Source note 189, line 1279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1279)

```text
// Remap the axes in a way opposite to the ALU cube instruction.
```

## Source note 190, line 1283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1283)

```text
// X is the major axis.
```

## Source note 191, line 1284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1284)

```text
// Y = -TC (TC overwritten).
```

## Source note 192, line 1287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1287)

```text
// Z = neg ? SC : -SC.
```

## Source note 193, line 1292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1292)

```text
// X = neg ? -1 : 1 (SC overwritten).
```

## Source note 194, line 1300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1300)

```text
// Y is the major axis.
```

## Source note 195, line 1301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1301)

```text
// X = SC (already there).
```

## Source note 196, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1302)

```text
// Z = neg ? -TC : TC.
```

## Source note 197, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1307)

```text
// Y = neg ? -1 : 1 (TC overwritten).
```

## Source note 198, line 1315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1315)

```text
// Z is the major axis.
```

## Source note 199, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1316)

```text
// X = neg ? -SC : SC (SC overwritten).
```

## Source note 200, line 1321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1321)

```text
// Y = -TC (TC overwritten).
```

## Source note 201, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1324)

```text
// Z = neg ? -1 : 1.
```

## Source note 202, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1340)

```text
// Because the `lod` instruction is not defined for point sampling, and
```

## Source note 203, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1341)

```text
// since the return value can be used with bias later, forcing linear mip
```

## Source note 204, line 1342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1342)

```text
// filtering (the XNA assembler also doesn't accept MipFilter overrides
```

## Source note 205, line 1343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1343)

```text
// for getCompTexLOD).
```

## Source note 206, line 1349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1349)

```text
// Load the sampler index to coord_and_sampler_temp.w and use relative
```

## Source note 207, line 1350

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1350)

```text
// sampler indexing.
```

## Source note 208, line 1363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1363)

```text
// Check which SRV needs to be accessed - signed or unsigned. If there is
```

## Source note 209, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1364)

```text
// at least one non-signed component, will be using the unsigned one.
```

## Source note 210, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1373)

```text
// Bindless path - select the SRV index between unsigned and signed to
```

## Source note 211, line 1374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1374)

```text
// query.
```

## Source note 212, line 1376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1376)

```text
// Check if 3D.
```

## Source note 213, line 1409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1409)

```text
// Always 3 coordinate components (1D and 2D are padded to 2D
```

## Source note 214, line 1410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1410)

```text
// arrays, 3D and cube have 3 coordinate dimensions). Not caring
```

## Source note 215, line 1411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1411)

```text
// about normalization of the array layer because it doesn't
```

## Source note 216, line 1412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1412)

```text
// participate in LOD calculation in Direct3D 12.
```

## Source note 217, line 1413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1413)

```text
// The `lod` instruction returns the unclamped LOD (probably need
```

## Source note 218, line 1414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1414)

```text
// unclamped so it can be biased back into the range later) in the Y
```

## Source note 219, line 1415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1415)

```text
// component, and the resource swizzle is the return value swizzle.
```

## Source note 220, line 1441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1441)

```text
// Close the 3D/stacked check.
```

## Source note 221, line 1445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1445)

```text
// Bindful path - conditionally query one of the SRVs.
```

## Source note 222, line 1452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1452)

```text
// Check if 3D.
```

## Source note 223, line 1475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1475)

```text
// Close the 3D/stacked check.
```

## Source note 224, line 1479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1479)

```text
// Close the signedness check.
```

## Source note 225, line 1482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1482)

```text
// Release is_unsigned_temp.
```

## Source note 226, line 1485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1485)

```text
// - Gradients or LOD to be passed to the sample_d/sample_l.
```

## Source note 227, line 1489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1489)

```text
// Will be allocated for both explicit and computed LOD.
```

## Source note 228, line 1491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1491)

```text
// Will be allocated for computed LOD only, and if not using basemap mip
```

## Source note 229, line 1492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1492)

```text
// filter.
```

## Source note 230, line 1497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1497)

```text
// Accumulate the explicit LOD sources (in D3D11.3 specification order:
```

## Source note 231, line 1498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1498)

```text
// specified LOD + sampler LOD bias + instruction LOD bias).
```

## Source note 232, line 1500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1500)

```text
// Fetch constant LOD bias * 32.
```

## Source note 233, line 1505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1505)

```text
// Divide the fetch constant LOD bias by 32, and add the register LOD
```

## Source note 234, line 1506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1506)

```text
// and the instruction LOD bias.
```

## Source note 235, line 1513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1513)

```text
// Divide the fetch constant LOD by 32, and add the instruction LOD
```

## Source note 236, line 1514

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1514)

```text
// bias.
```

## Source note 237, line 1538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1538)

```text
// Convert the bias to a gradient scale.
```

## Source note 238, line 1542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1542)

```text
// Extract gradient exponent biases from the fetch constant and merge
```

## Source note 239, line 1543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1543)

```text
// them with the LOD bias.
```

## Source note 240, line 1555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1555)

```text
// Obtain the gradients and apply biases to them.
```

## Source note 241, line 1557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1557)

```text
// Register gradients are already in the cube space for cube maps.
```

## Source note 242, line 1581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1581)

```text
// Normalize Z of the gradients for fetching from the 3D texture.
```

## Source note 243, line 1593

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1593)

```text
// Coarse is according to the Direct3D 11.3 specification.
```

## Source note 244, line 1610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1610)

```text
// Pad the gradients to 2D because 1D textures are fetched as 2D
```

## Source note 245, line 1611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1611)

```text
// arrays.
```

## Source note 246, line 1619

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1619)

```text
// - Data.
```

## Source note 247, line 1621

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1621)

```text
// 4D5307F2 uses vertex displacement map textures for tessellated models
```

## Source note 248, line 1622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1622)

```text
// like the beehive tree with explicit LOD with point sampling (they store
```

## Source note 249, line 1623

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1623)

```text
// values packed in two components), however, the fetch constant has
```

## Source note 250, line 1624

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1624)

```text
// anisotropic filtering enabled. However, Direct3D 12 doesn't allow
```

## Source note 251, line 1625

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1625)

```text
// mixing anisotropic and point filtering. Possibly anistropic filtering
```

## Source note 252, line 1626

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1626)

```text
// should be disabled when explicit LOD is used - do this here.
```

## Source note 253, line 1644

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1644)

```text
// Load the sampler index to coord_and_sampler_temp.w and use relative
```

## Source note 254, line 1645

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1645)

```text
// sampler indexing.
```

## Source note 255, line 1661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1661)

```text
// A point sampled fetch constant takes the texel center (in host
```

## Source note 256, line 1662

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1662)

```text
// texels for a resolution scaled texture) instead of the epsilon. The
```

## Source note 257, line 1663

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1663)

```text
// result register is still free until the sample.
```

## Source note 258, line 1702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1702)

```text
// Break result register dependencies because textures will be sampled
```

## Source note 259, line 1703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1703)

```text
// conditionally, including the primary signs.
```

## Source note 260, line 1707

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1707)

```text
// Extract whether each component is signed.
```

## Source note 261, line 1712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1712)

```text
// Calculate the lerp factor between stacked texture layers if needed (or
```

## Source note 262, line 1713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1713)

```text
// 0 if point-sampled), and check which signedness SRVs need to be
```

## Source note 263, line 1714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1714)

```text
// sampled.
```

## Source note 264, line 1715

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1715)

```text
// As a result, if srv_selection_temp is allocated at all:
```

## Source note 265, line 1716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1716)

```text
// - srv_selection_temp.x - if multiple components, whether all components
```

## Source note 266, line 1717

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1717)

```text
//   are signed, wrapped by is_all_signed_src with a fallback for the
```

## Source note 267, line 1718

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1718)

```text
//   single component case. If false, the unsigned SRV needs to be
```

## Source note 268, line 1719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1719)

```text
//   sampled.
```

## Source note 269, line 1720

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1720)

```text
// - srv_selection_temp.y - if multiple components, whether any component
```

## Source note 270, line 1721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1721)

```text
//   is signed, wrapped by is_any_signed_src with a fallback for the
```

## Source note 271, line 1722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1722)

```text
//   single component case. If true, the signed SRV needs to be sampled.
```

## Source note 272, line 1723

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1723)

```text
// - srv_selection_temp.z - if stacked and not forced to be point-sampled,
```

## Source note 273, line 1724

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1724)

```text
//   the lerp factor between two layers, wrapped by layer_lerp_factor_src
```

## Source note 274, line 1725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1725)

```text
//   with l(0.0) fallback for the point sampling case.
```

## Source note 275, line 1726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1726)

```text
// - srv_selection_temp.w - first, scratch for calculations involving
```

## Source note 276, line 1727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1727)

```text
//   these, then, unsigned or signed SRV description index.
```

## Source note 277, line 1729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1729)

```text
// W is always needed for bindless.
```

## Source note 278, line 1747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1747)

```text
// Initialize to point sampling, and break register dependency for 3D.
```

## Source note 279, line 1751

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1751)

```text
// Check if minifying along layers (derivative > 1 along any axis).
```

## Source note 280, line 1756

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1756)

```text
// Denormalize the gradient if provided as normalized.
```

## Source note 281, line 1762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1762)

```text
// For NaN, considering that magnification is being done. Zero
```

## Source note 282, line 1763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1763)

```text
// srv_selection_temp.w means magnifying, non-zero means minifying.
```

## Source note 283, line 1768

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1768)

```text
// Write the magnification filter to srv_selection_temp.w. In the
```

## Source note 284, line 1769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1769)

```text
// "if" rather than "else" because this is more likely to happen if
```

## Source note 285, line 1770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1770)

```text
// the layer is constant.
```

## Source note 286, line 1779

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1779)

```text
// Write the minification filter to srv_selection_temp.w.
```

## Source note 287, line 1787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1787)

```text
// Close the magnification check.
```

## Source note 288, line 1789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1789)

```text
// Check if the filter is linear.
```

## Source note 289, line 1793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1793)

```text
// Both overridden, one (magnification) is linear, another
```

## Source note 290, line 1794

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1794)

```text
// (minification) is not - handle linear filtering if magnifying.
```

## Source note 291, line 1799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1799)

```text
// Both overridden, one (minification) is linear, another
```

## Source note 292, line 1800

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1800)

```text
// (magnification) is not - handle linear filtering if minifying.
```

## Source note 293, line 1803

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1803)

```text
// For linear filtering, subtract 0.5 from the coordinates and store
```

## Source note 294, line 1804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1804)

```text
// the lerp factor. Flooring will be done later.
```

## Source note 295, line 1809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1809)

```text
// Close the linear check.
```

## Source note 296, line 1811

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1811)

```text
// Close the stacked check.
```

## Source note 297, line 1814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1814)

```text
// No gradients, or using the same filter overrides for magnifying and
```

## Source note 298, line 1815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1815)

```text
// minifying. Assume always magnifying if no gradients (LOD 0, always
```

## Source note 299, line 1816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1816)

```text
// <= 0). LOD is within 2D layers, not between them (unlike in 3D
```

## Source note 300, line 1817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1817)

```text
// textures, which have mips with depth reduced).
```

## Source note 301, line 1823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1823)

```text
// Initialize to point sampling, and break register dependency for
```

## Source note 302, line 1824

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1824)

```text
// 3D.
```

## Source note 303, line 1829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1829)

```text
// Extract the magnification filtering mode from the fetch
```

## Source note 304, line 1830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1830)

```text
// constant.
```

## Source note 305, line 1833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1833)

```text
// Check if it's linear.
```

## Source note 306, line 1836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1836)

```text
// For linear filtering, subtract 0.5 from the coordinates and store
```

## Source note 307, line 1837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1837)

```text
// the lerp factor. Flooring will be done later.
```

## Source note 308, line 1843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1843)

```text
// Close the fetch constant linear filtering mode check.
```

## Source note 309, line 1846

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1846)

```text
// Close the stacked check.
```

## Source note 310, line 1851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1851)

```text
// Check if any component is not signed, and if any component is signed.
```

## Source note 311, line 1857

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1857)

```text
// Multiple components fetched - need to merge.
```

## Source note 312, line 1872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1872)

```text
// For the first component, both sources must both be two is_signed
```

## Source note 313, line 1873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1873)

```text
// components, to initialize.
```

## Source note 314, line 1892

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1892)

```text
// Sample the texture - choose between 3D and stacked, and then sample
```

## Source note 315, line 1893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1893)

```text
// unsigned and signed SRVs and choose between them.
```

## Source note 316, line 1897

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1897)

```text
// The first fetch attempt will be for the 3D SRV.
```

## Source note 317, line 1903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1903)

```text
// i == 0 - 1D/2D/3D/cube.
```

## Source note 318, line 1904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1904)

```text
// i == 1 - 2D stacked.
```

## Source note 319, line 1913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1913)

```text
// Floor the array layer (Direct3D 12 does rounding to nearest even
```

## Source note 320, line 1914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1914)

```text
// for the layer index, but on the Xbox 360, addressing is similar to
```

## Source note 321, line 1915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1915)

```text
// that of 3D textures). This is needed for both point and linear
```

## Source note 322, line 1916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1916)

```text
// filtering (with linear, 0.5 was subtracted previously).
```

## Source note 323, line 1963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1963)

```text
// Check if the lerp factor is not zero (or NaN).
```

## Source note 324, line 1966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1966)

```text
// If the lerp factor is not zero, sample the next layer.
```

## Source note 325, line 1968

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1968)

```text
// Go to the next layer.
```

## Source note 326, line 1972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1972)

```text
// Always 3 coordinate components (1D and 2D are padded to 2D arrays,
```

## Source note 327, line 1973

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1973)

```text
// 3D and cube have 3 coordinate dimensions).
```

## Source note 328, line 1976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1976)

```text
// Sample the unsigned texture, or the black-border view.
```

## Source note 329, line 1979

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1979)

```text
// Load the unsigned texture descriptor index.
```

## Source note 330, line 2006

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2006)

```text
// Sample the signed texture, or the same view with a white border.
```

## Source note 331, line 2010

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2010)

```text
// Load the signed texture descriptor index.
```

## Source note 332, line 2042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2042)

```text
// Release signed_temp.
```

## Source note 333, line 2048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2048)

```text
// Interpolate between the two layers.
```

## Source note 334, line 2054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2054)

```text
// Close the linear filtering check.
```

## Source note 335, line 2056

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2056)

```text
// Release the allocated layer_value_temp.
```

## Source note 336, line 2062

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2062)

```text
// Close the stacked/3D check.
```

## Source note 337, line 2069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2069)

```text
// Release is_signed_temp.
```

## Source note 338, line 2072

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2072)

```text
// Release grad_h_lod_temp and grad_v_temp.
```

## Source note 339, line 2081

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2081)

```text
// Release coord_and_sampler_temp.
```

## Source note 340, line 2084

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2084)

```text
// Apply the bias and gamma correction (gamma is after filtering here,
```

## Source note 341, line 2085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2085)

```text
// likely should be before, but it's outside Xenia's control for host
```

## Source note 342, line 2086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2086)

```text
// sampler filtering).
```

## Source note 343, line 2087

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2087)

```text
// Signs, gamma and num_format, from xenia-canary at 6260a87b85 (d119505289,
```

## Source note 344, line 2088

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2088)

```text
// 2ddc5ef737, 6a45452087, 0c843efb32, c3cd8617b1; RG-GDK-045).
```

## Source note 345, line 2104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2104)

```text
// Decode as signed offset binary: (n - 2^(w - 1)) / (2^(w - 1) - 1)
```

## Source note 346, line 2105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2105)

```text
// This maps 128 to zero for 8 bit components, avoiding the 1/255
```

## Source note 347, line 2106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2106)

```text
// bias of 2 * u - 1. Leave the result unclamped until num_format is
```

## Source note 348, line 2107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2107)

```text
// applied, and keep 2 * u - 1 when the width is unknown or 1 bit.
```

## Source note 349, line 2111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2111)

```text
// Y = 2^(w - 1).
```

## Source note 350, line 2116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2116)

```text
// Z = u * (2^w - 1) - 2^(w - 1).
```

## Source note 351, line 2123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2123)

```text
// Y = 2^(w - 1) - 1, Z = Z / Y.
```

## Source note 352, line 2133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2133)

```text
// Release biased_temp.
```

## Source note 353, line 2139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2139)

```text
// Convert from piecewise linear.
```

## Source note 354, line 2142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2142)

```text
// Release gamma_temp.
```

## Source note 355, line 2147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2147)

```text
// Apply num_format after signs/gamma.
```

## Source note 356, line 2155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2155)

```text
// Uniform early out. Zero means leave the sample alone. Bit 26 is the
```

## Source note 357, line 2156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2156)

```text
// coordinate snap, not a scale.
```

## Source note 358, line 2164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2164)

```text
// Reconstruct point sampled 4 to 7 bit unsigned components
```

## Source note 359, line 2165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2165)

```text
// using the guest conversion (see GetIntegerScaleBits).
```

## Source note 360, line 2169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2169)

```text
// 2^w per component.
```

## Source note 361, line 2174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2174)

```text
// The texel n from the host's n / (2^w - 1).
```

## Source note 362, line 2179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2179)

```text
// n * (2^w + 1) / 2^(2w).
```

## Source note 363, line 2184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2184)

```text
// Apply only where the packed component field is 1 to 15
```

## Source note 364, line 2185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2185)

```text
// (unsigned with a nonzero width field).
```

## Source note 365, line 2194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2194)

```text
// Only round unsigned normalized components to 16 fractional bits.
```

## Source note 366, line 2202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2202)

```text
// Clamp normalized unsigned-biased components to -1. Post-filtering
```

## Source note 367, line 2203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2203)

```text
// clamping can put mixtures with a stored value of 0 up to one component
```

## Source note 368, line 2204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2204)

```text
// code below the result of clamping each texel before.
```

## Source note 369, line 2212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2212)

```text
// Restore integer values with 2^w - 1 for unsigned components
```

## Source note 370, line 2213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2213)

```text
// and 2^(w - 1) - 1 for signed and unsigned-biased.
```

## Source note 371, line 2217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2217)

```text
// All ones for signed (1) and biased (2), taking one off the shift.
```

## Source note 372, line 2226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2226)

```text
// For 1 bit unsigned-biased components, use a scale of 0.5 and
```

## Source note 373, line 2227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2227)

```text
// an offset of -0.5 to recover -1 and 0.
```

## Source note 374, line 2234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2234)

```text
// Host decode precision varies since NVIDIA bit replication turns 1/31
```

## Source note 375, line 2235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2235)

```text
// into 8/255, giving a scaled value of 0.9725. Point sampling gives the
```

## Source note 376, line 2236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2236)

```text
// guest an integer texel value, while filtering keeps the fractional
```

## Source note 377, line 2237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2237)

```text
// result.
```

## Source note 378, line 2262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2262)

```text
// Apply the result exponent bias.
```

## Source note 379, line 2271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2271)

```text
// Release exp_adjust_temp.
```
