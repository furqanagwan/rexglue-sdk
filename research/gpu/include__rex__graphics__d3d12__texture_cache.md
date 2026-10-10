# Texture cache: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/texture_cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L37)

```text
// Keys that can be stored for checking validity whether descriptors for host
```

## Source note 2, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L38)

```text
// shader bindings are up to date.
```

## Source note 3, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L45)

```text
// Sampler parameters that can be directly converted to a host sampler or used
```

## Source note 4, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L46)

```text
// for binding checking validity whether samplers are up to date.
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L50)

```text
// 3
```

## Source note 6, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L51)

```text
// 6
```

## Source note 7, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L52)

```text
// 9
```

## Source note 8, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L53)

```text
// 11
```

## Source note 9, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L54)

```text
// For anisotropic, these are true.
```

## Source note 10, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L55)

```text
// 12
```

## Source note 11, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L56)

```text
// 13
```

## Source note 12, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L57)

```text
// 14
```

## Source note 13, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L58)

```text
// 17
```

## Source note 14, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L59)

```text
// 21
```

## Source note 15, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L60)

```text
// 22
```

## Source note 16, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L61)

```text
// Maximum mip level is in the texture resource itself, but mip_base_map
```

## Source note 17, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L62)

```text
// can be used to limit fetching to mip_min_level.
```

## Source note 18, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L93)

```text
// Must be called within a submission - creates and untiles textures needed by
```

## Source note 19, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L94)

```text
// shaders and puts them in the SRV state. This may bind compute pipelines
```

## Source note 20, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L95)

```text
// (notifying the command processor about that), so this must be called before
```

## Source note 21, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L96)

```text
// binding the actual drawing pipeline.
```

## Source note 22, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L99)

```text
// Returns whether texture SRV keys stored externally are still valid for the
```

## Source note 23, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L100)

```text
// current bindings and host shader binding layout. Both keys and
```

## Source note 24, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L101)

```text
// host_shader_bindings must have host_shader_binding_count elements
```

## Source note 25, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L102)

```text
// (otherwise they are incompatible - like if this function returned false).
```

## Source note 26, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L106)

```text
// Exports the current binding data to texture SRV keys so they can be stored
```

## Source note 27, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L107)

```text
// for checking whether subsequent draw calls can keep using the same
```

## Source note 28, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L108)

```text
// bindings. Write host_shader_binding_count keys.
```

## Source note 29, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L119)

```text
// Returns whether the actual scale is not smaller than the requested one.
```

## Source note 30, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L122)

```text
// Ensures the tiles backing the range in the buffers are allocated.
```

## Source note 31, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L125)

```text
// Makes the specified range of up to 1-2 GB currently accessible on the GPU.
```

## Source note 32, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L126)

```text
// One draw call can access only at most one range - the same memory is
```

## Source note 33, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L127)

```text
// accessible through different buffers based on the range needed, so aliasing
```

## Source note 34, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L128)

```text
// barriers are required.
```

## Source note 35, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L131)

```text
// These functions create a view of the range specified in the last successful
```

## Source note 36, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L132)

```text
// MakeScaledResolveRangeCurrent call because that function must be called
```

## Source note 37, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L133)

```text
// before this.
```

## Source note 38, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L156)

```text
// Returns the ID3D12Resource of the front buffer texture (in
```

## Source note 39, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L157)

```text
// NON_PIXEL_SHADER_RESOURCE state), or nullptr in case of failure, and writes
```

## Source note 40, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L158)

```text
// the description of its SRV. May call LoadTextureData, so the same
```

## Source note 41, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L159)

```text
// restrictions (such as about descriptor heap change possibility) apply.
```

## Source note 42, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L175)

```text
// This binds pipelines, allocates descriptors, and copies!
```

## Source note 43, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L186)

```text
// Format info for the regular case.
```

## Source note 44, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L187)

```text
// DXGI format (typeless when different signedness or number representation
```

## Source note 45, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L188)

```text
// is used) for the texture resource.
```

## Source note 46, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L190)

```text
// DXGI format for unsigned normalized or unsigned/signed float SRV.
```

## Source note 47, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L192)

```text
// The regular load shader, used when special load shaders (like
```

## Source note 48, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L193)

```text
// signed-specific or decompressing) aren't needed.
```

## Source note 49, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L195)

```text
// DXGI format for signed normalized or unsigned/signed float SRV.
```

## Source note 50, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L197)

```text
// If the signed version needs a different bit representation on the host,
```

## Source note 51, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L198)

```text
// this is the load shader for the signed version. Otherwise the regular
```

## Source note 52, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L199)

```text
// load_shader will be used for the signed version, and a single copy will
```

## Source note 53, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L200)

```text
// be created if both unsigned and signed are used.
```

## Source note 54, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L203)

```text
// Do NOT add integer DXGI formats to this - they are not filterable, can
```

## Source note 55, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L204)

```text
// only be read with Load, not Sample! If any game is seen using num_format
```

## Source note 56, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L205)

```text
// 1 for fixed-point formats (for floating-point, it's normally set to 1
```

## Source note 57, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L206)

```text
// though), add a constant buffer containing multipliers for the
```

## Source note 58, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L207)

```text
// textures and multiplication to the tfetch implementation.
```

## Source note 59, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L209)

```text
// Whether the DXGI format, if not uncompressing the texture, consists of
```

## Source note 60, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L210)

```text
// blocks, thus copy regions must be aligned to block size (assuming it's
```

## Source note 61, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L211)

```text
// the same as the guest block size).
```

## Source note 62, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L213)

```text
// Uncompression info for when the regular host format for this texture is
```

## Source note 63, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L214)

```text
// block-compressed, but the size is not block-aligned, and thus such
```

## Source note 64, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L215)

```text
// texture cannot be created in Direct3D on PC and needs decompression,
```

## Source note 65, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L216)

```text
// however, such textures are common, for instance, in 4D5307E6. This only
```

## Source note 66, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L217)

```text
// supports unsigned normalized formats - let's hope GPUSIGN_SIGNED was not
```

## Source note 67, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L218)

```text
// used for DXN and DXT5A.
```

## Source note 68, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L222)

```text
// Mapping of Xenos swizzle components to DXGI format components.
```

## Source note 69, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L276)

```text
// For bindful - indices in the non-shader-visible descriptor cache for
```

## Source note 70, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L277)

```text
// copying to the shader-visible heap (much faster than recreating, which,
```

## Source note 71, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L278)

```text
// according to profiling, was often a bottleneck in many games).
```

## Source note 72, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L279)

```text
// For bindless - indices in the global shader-visible descriptor heap.
```

## Source note 73, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L310)

```text
// Descriptor indices of texture and texture_signed of the respective
```

## Source note 74, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L311)

```text
// TextureBinding returned from FindOrCreateTextureDescriptor.
```

## Source note 75, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L337)

```text
// After writing through a UAV.
```

## Source note 76, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L343)

```text
// After an aliasing barrier (which is even stronger than an UAV barrier).
```

## Source note 77, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L359)

```text
// Whether decompression is needed on the host (Direct3D only allows creation
```

## Source note 78, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L360)

```text
// of block-compressed textures with 4x4-aligned dimensions on PC).
```

## Source note 79, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L400)

```text
// Returns the index of an existing of a newly created non-shader-visible
```

## Source note 80, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L401)

```text
// cached (for bindful) or a shader-visible global (for bindless) descriptor,
```

## Source note 81, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L402)

```text
// or UINT32_MAX if failed to create.
```

## Source note 82, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L410)

```text
// Make sure any range up to 1 GB is accessible through 1 or 2 buffers.
```

## Source note 83, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L411)

```text
// 2x2 scale buffers - just one 2 GB buffer for all 2 GB.
```

## Source note 84, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L412)

```text
// 3x3 scale buffers - 4 buffers:
```

## Source note 85, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L413)

```text
//  +0.0 +0.5 +1.0 +1.5 +2.0 +2.5 +3.0 +3.5 +4.0 +4.5
```

## Source note 86, line 416

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L416)

```text
// Buffer N has an offset of N * 1 GB in the scaled resolve address space.
```

## Source note 87, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L417)

```text
// The logic is:
```

## Source note 88, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L418)

```text
// - 2 GB can be accessed through a [0 GB ... 2 GB) buffer - only need one.
```

## Source note 89, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L419)

```text
// - 2.1 GB needs [0 GB ... 2 GB) and [1 GB ... 2.1 GB) - two buffers.
```

## Source note 90, line 420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L420)

```text
// - 3 GB needs [0 GB ... 2 GB) and [1 GB ... 3 GB) - two buffers.
```

## Source note 91, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L421)

```text
// - 3.1 GB needs [0 GB ... 2 GB), [1 GB ... 3 GB) and [2 GB ... 3.1 GB) -
```

## Source note 92, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L422)

```text
//   three buffers.
```

## Source note 93, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L427)

```text
// Returns indices of two scaled resolve virtual buffers that the location in
```

## Source note 94, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L428)

```text
// memory may be accessible through. May be the same if it's a location near
```

## Source note 95, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L429)

```text
// the beginning or the end of the address represented only by one buffer.
```

## Source note 96, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L434)

```text
// In different cases for 3x3:
```

## Source note 97, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L435)

```text
//  +0.0 +0.5 +1.0 +1.5 +2.0 +2.5 +3.0 +3.5 +4.0 +4.5
```

## Source note 98, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L436)

```text
// |12________2________|1_________2________|
```

## Source note 99, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L437)

```text
//           |1_________2________|1_________12__|
```

## Source note 100, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L441)

```text
// The index is also the gigabyte offset of the buffer from the start of the
```

## Source note 101, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L442)

```text
// scaled physical memory address space.
```

## Source note 102, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L462)

```text
// Load pipelines for resolution-scaled resolve targets.
```

## Source note 103, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L467)

```text
// Indices of cached descriptors used by deleted textures, for reuse.
```

## Source note 104, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L477)

```text
// Contains null SRV descriptors of dimensions from NullSRVDescriptorIndex.
```

## Source note 105, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L478)

```text
// For copying, not shader-visible.
```

## Source note 106, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L484)

```text
// Unsupported texture formats used during this frame (for research and
```

## Source note 107, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L485)

```text
// testing).
```

## Source note 108, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L493)

```text
// The tiled buffer for resolved data with resolution scaling.
```

## Source note 109, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L494)

```text
// Because on Direct3D 12 (at least on Windows 10 2004) typed SRV or UAV
```

## Source note 110, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L495)

```text
// creation fails for offsets above 4 GB, a single tiled 4.5 GB buffer can't
```

## Source note 111, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L496)

```text
// be used for 3x3 resolution scaling.
```

## Source note 112, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L497)

```text
// Instead, "sliding window" buffers allowing to access a single range of up
```

## Source note 113, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L498)

```text
// to 1 GB (or up to 2 GB, depending on the low bits) at any moment are used.
```

## Source note 114, line 499

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L499)

```text
// Parts of 4.5 GB address space can be accessed through 2 GB buffers as:
```

## Source note 115, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L500)

```text
//  +0.0 +0.5 +1.0 +1.5 +2.0 +2.5 +3.0 +3.5 +4.0 +4.5
```

## Source note 116, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L501)

```text
// |___________________|___________________|      or
```

## Source note 117, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L503)

```text
// (2 GB is also the amount of scaled physical memory with 2x resolution
```

## Source note 118, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L504)

```text
// scale, and older Intel GPUs, while support tiled resources, only support 31
```

## Source note 119, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L505)

```text
// virtual address bits per resource).
```

## Source note 120, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L506)

```text
// Index is first gigabyte. Only including buffers containing over 1 GB
```

## Source note 121, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L507)

```text
// (because otherwise the data will be fully contained in another).
```

## Source note 122, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L508)

```text
// Size is calculated the same as in GetScaledResolveBufferCount.
```

## Source note 123, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L515)

```text
// Not very big heaps (16 MB) because they are needed pretty sparsely. One
```

## Source note 124, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L516)

```text
// 2x-scaled 1280x720x32bpp texture is slighly bigger than 14 MB.
```

## Source note 125, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L528)

```text
// Resident portions of the tiled buffer.
```

## Source note 126, line 530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L530)

```text
// Number of currently resident portions of the tiled buffer, for profiling.
```

## Source note 127, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L532)

```text
// Current scaled resolve state.
```

## Source note 128, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L533)

```text
// For aliasing barrier placement, last owning buffer index for each of 1 GB.
```

## Source note 129, line 539

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L539)

```text
// Range used in the last successful MakeScaledResolveRangeCurrent call.
```

## Source note 130, line 544

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/texture_cache.h#L544)

```text
// namespace rex::graphics::d3d12
```
