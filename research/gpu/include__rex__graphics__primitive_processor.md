# Primitive processor: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/primitive_processor.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L35)

```text
// 128-bit SSSE3-level (SSE2+ for integer comparison, SSSE3 for pshufb) or AVX
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L36)

```text
// (256-bit AVX only got integer operations such as comparison in AVX2, which is
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L37)

```text
// above the minimum requirements of Xenia).
```

## Source note 4, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L47)

```text
// The idea behind this config variable is to force both indirection without
```

## Source note 5, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L48)

```text
// primitive reset and pre-masking / pre-swapping with primitive reset,
```

## Source note 6, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L49)

```text
// therefore this is supposed to be checked only by the host if it supports
```

## Source note 7, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L50)

```text
// indirection. It's pretty pointless to do only half of this on backends that
```

## Source note 8, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L51)

```text
// support full 32-bit indices unconditionally.
```

## Source note 9, line 56

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L56)

```text
// Normalizes primitive data in various ways for use with Direct3D 12 and Vulkan
```

## Source note 10, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L57)

```text
// (down to its minimum requirements plus the portability subset).
```

## Source note 11, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L59)

```text
// This solves various issues:
```

## Source note 12, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L60)

```text
// - Triangle fans not supported on Direct3D 10+ and the Vulkan portability
```

## Source note 13, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L61)

```text
//   subset.
```

## Source note 14, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L62)

```text
//   - Converts to triangle lists, both with and without primitive reset.
```

## Source note 15, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L63)

```text
// - Line loops are not supported on Direct3D 12 or Vulkan.
```

## Source note 16, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L64)

```text
//   - Converts to line strips.
```

## Source note 17, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L65)

```text
// - Quads not reproducible with line lists with adjacency without geometry
```

## Source note 18, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L66)

```text
//   shaders (some Vulkan implementations), as well as being hard to debug in
```

## Source note 19, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L67)

```text
//   PIX due to "catastrophic failures".
```

## Source note 20, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L68)

```text
//   - Converts to triangle lists.
```

## Source note 21, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L69)

```text
// - Vulkan requiring 0xFFFF primitive restart index for 16-bit indices and
```

## Source note 22, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L70)

```text
//   0xFFFFFFFF for 32-bit (Direct3D 12 slightly relaxes this, allowing 0xFFFF
```

## Source note 23, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L71)

```text
//   for 32-bit also, but it's of no use to Xenia since guest indices are
```

## Source note 24, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L72)

```text
//   big-endian usually. Also, only 24 lower bits of the vertex index being used
```

## Source note 25, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L73)

```text
//   on the guest (tested on an Adreno 200 phone with drawing, though not with
```

## Source note 26, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L74)

```text
//   primitive restart as OpenGL ES 2.0 doesn't expose it), so the upper 8 bits
```

## Source note 27, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L75)

```text
//   likely shouldn't have effect on primitive restart (guest reset index
```

## Source note 28, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L76)

```text
//   0xFFFFFF likely working for 0xFFFFFF, 0xFFFFFFFF, and 254 more indices),
```

## Source note 29, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L77)

```text
//   while Vulkan and Direct3D 12 require exactly 0xFFFFFFFF.
```

## Source note 30, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L78)

```text
//   - For 16-bit indices with guest reset index other than 0xFFFF (passing
```

## Source note 31, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L79)

```text
//     0xFFFF directly to the host is fine because it's the same irrespective of
```

## Source note 32, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L80)

```text
//     endianness), there are two possible solutions:
```

## Source note 33, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L81)

```text
//     - If the index buffer otherwise doesn't contain 0xFFFF otherwise (since
```

## Source note 34, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L82)

```text
//       it's a valid vertex index in this case), replacing the primitive reset
```

## Source note 35, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L83)

```text
//       index with 0xFFFF in the 16-bit buffer.
```

## Source note 36, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L84)

```text
//     - If the index buffer contains any usage of 0xFFFF as a real vertex
```

## Source note 37, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L85)

```text
//       index, converting the index buffer to 32-bit, and replacing the
```

## Source note 38, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L86)

```text
//       primitive reset index with 0xFFFFFFFF.
```

## Source note 39, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L87)

```text
//   - For 32-bit indices, there are two paths:
```

## Source note 40, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L88)

```text
//     - If the guest reset index is 0xFFFFFF, and the index buffer actually
```

## Source note 41, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L89)

```text
//       uses only 0xFFFFFFFF for reset, using it without changes.
```

## Source note 42, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L90)

```text
//     - If the guest uses something other than 0xFFFFFFFF for primitive reset,
```

## Source note 43, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L91)

```text
//       replacing elements with (index & 0xFFFFFF) == reset_index with
```

## Source note 44, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L92)

```text
//       0xFFFFFFFF.
```

## Source note 45, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L93)

```text
// - Some Vulkan implementations only support 24-bit indices. The guests usually
```

## Source note 46, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L94)

```text
//   pass big-endian vertices, so we need all 32 bits (as the least significant
```

## Source note 47, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L95)

```text
//   bits will be in 24...31) to perform the byte swapping. For this reason, we
```

## Source note 48, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L96)

```text
//   load 32-bit indices indirectly, doing non-indexed draws and fetching the
```

## Source note 49, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L97)

```text
//   indices from the shared memory. This, however, is not compatible with
```

## Source note 50, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L98)

```text
//   primitive restart.
```

## Source note 51, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L99)

```text
//   - Pre-swapping, masking to 24 bits, and converting the reset index to
```

## Source note 52, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L100)

```text
//     0xFFFFFFFF, resulting in an index buffer that can be used directly.
```

## Source note 53, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L105)

```text
// Auto-indexed on the host.
```

## Source note 54, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L107)

```text
// GPU DMA, from the shared memory.
```

## Source note 55, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L108)

```text
// For 32-bit, indirection is needed if the host only supports 24-bit
```

## Source note 56, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L109)

```text
// indices (even for non-endian-swapped, as the GPU should be ignoring the
```

## Source note 57, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L110)

```text
// upper 8 bits completely, rather than exhibiting undefined behavior.
```

## Source note 58, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L112)

```text
// Converted and stored in the primitive converter for the current draw
```

## Source note 59, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L113)

```text
// command. For 32-bit indices, if the host doesn't support all 32 bits,
```

## Source note 60, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L114)

```text
// this kind of an index buffer will always be pre-masked and pre-swapped.
```

## Source note 61, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L116)

```text
// Auto-indexed on the guest, but with an adapter index buffer on the host.
```

## Source note 62, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L118)

```text
// Adapter index buffer on the host for indirect loading of indices via DMA
```

## Source note 63, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L119)

```text
// (from the shared memory).
```

## Source note 64, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L126)

```text
// Includes whether tessellation is enabled (not kVertex) and the type of
```

## Source note 65, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L127)

```text
// tessellation.
```

## Source note 66, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L129)

```text
// Only used for non-kVertex host_vertex_shader_type. For kAdaptive, the
```

## Source note 67, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L130)

```text
// index buffer is always from the guest and fully 32-bit, and contains the
```

## Source note 68, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L131)

```text
// floating-point tessellation factors.
```

## Source note 69, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L141)

```text
// The reset index, if enabled, is always 0xFFFF for host_index_format
```

## Source note 70, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L142)

```text
// kInt16 and 0xFFFFFFFF for kInt32. Never enabled for "list" primitive
```

## Source note 71, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L143)

```text
// types, thus safe for direct usage on Vulkan.
```

## Source note 72, line 145

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L145)

```text
// Backend-specific handle for the index buffer valid for the current draw,
```

## Source note 73, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L146)

```text
// only valid for index_buffer_type kHostConverted, kHostBuiltinForAuto and
```

## Source note 74, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L147)

```text
// kHostBuiltinForDMA.
```

## Source note 75, line 159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L159)

```text
// Quad lists may be emulated as line lists with adjacency and a geometry
```

## Source note 76, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L160)

```text
// shader, but geometry shaders must be supported for this.
```

## Source note 77, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L167)

```text
// Submission must be open to call (may request the index buffer in the shared
```

## Source note 78, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L168)

```text
// memory).
```

## Source note 79, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L171)

```text
// Invalidates the cache within the range.
```

## Source note 80, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L176)

```text
// For host-side index buffer creation, the biggest possibly needed contiguous
```

## Source note 81, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L177)

```text
// allocation, in indices.
```

## Source note 82, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L178)

```text
// - No conversion: up to 0xFFFF vertices (as the vertex count in
```

## Source note 83, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L179)

```text
//   VGT_DRAW_INITIATOR is 16-bit).
```

## Source note 84, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L180)

```text
// - Triangle fans to lists: since the 3rd vertex, every guest vertex creates
```

## Source note 85, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L181)

```text
//   a triangle, thus the maximum is 3 * (UINT16_MAX - 2), or 0x2FFF7.
```

## Source note 86, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L182)

```text
//   Primitive reset can only slow down the amplification - the 3 vertices
```

## Source note 87, line 183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L183)

```text
//   after a reset add 1 host vertex each, not 3 each.
```

## Source note 88, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L184)

```text
// - Line loops to strips: adding 1 vertex if there are at least 2 vertices in
```

## Source note 89, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L185)

```text
//   the original primitive, either replacing the primitive reset index with
```

## Source note 90, line 186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L186)

```text
//   this new closing vertex, or in case of the final primitive, just adding a
```

## Source note 91, line 187

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L187)

```text
//   vertex - thus the absolute limit is UINT16_MAX + 1, or 0x10000.
```

## Source note 92, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L188)

```text
// - Quad lists to triangle lists: vertices are processed in groups of 4, each
```

## Source note 93, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L189)

```text
//   group converted to 6 vertices, so the limit is 1.5 * 0xFFFC, or 0x17FFA.
```

## Source note 94, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L190)

```text
// Thus, the maximum vertex count is defined by triangle fan to list
```

## Source note 95, line 191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L191)

```text
// conversion.
```

## Source note 96, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L192)

```text
// Also include padding for co-alignment of the source and the destination for
```

## Source note 97, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L193)

```text
// SIMD.
```

## Source note 98, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L201)

```text
// Call from the backend-specific initialization function.
```

## Source note 99, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L202)

```text
// - full_32bit_vertex_indices_supported:
```

## Source note 100, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L203)

```text
//   - If the backend supports 32-bit indices unconditionally, and doesn't
```

## Source note 101, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L204)

```text
//     generate indirection logic in vertex shaders, pass hard-coded `true`.
```

## Source note 102, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L205)

```text
//   - Otherwise:
```

## Source note 103, line 206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L206)

```text
//     - If the host doesn't support full 32-bit indices (but supports at
```

## Source note 104, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L207)

```text
//       least 24-bit indices), pass `false`.
```

## Source note 105, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L208)

```text
//     - If the host supports 32-bit indices, but the backend can handle both
```

## Source note 106, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L209)

```text
//       cases, pass `REXCVAR_GET(ignore_32bit_vertex_index_support)`, and
```

## Source note 107, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L210)

```text
//       afterwards, check `AreFull32BitVertexIndicesUsed()` externally to see
```

## Source note 108, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L211)

```text
//       if indirection may be needed.
```

## Source note 109, line 212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L212)

```text
//     - When full 32-bit indices are not supported, the host must be using
```

## Source note 110, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L213)

```text
//       auto-indexed draws for 32-bit indices of ProcessedIndexBufferType
```

## Source note 111, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L214)

```text
//       kGuestDMA, while fetching the index data manually from the shared
```

## Source note 112, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L215)

```text
//       memory buffer and endian-swapping it.
```

## Source note 113, line 216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L216)

```text
//     - Indirection, however, precludes primitive reset usage - so if
```

## Source note 114, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L217)

```text
//       primitive reset is needed, the primitive processor will pre-swap and
```

## Source note 115, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L218)

```text
//       pre-mask the index buffer so there are only host-endian 0x00###### or
```

## Source note 116, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L219)

```text
//       0xFFFFFFFF values in it. In this case, a kHostConverted index buffer
```

## Source note 117, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L220)

```text
//       is returned from Process, and indirection is not needed (and
```

## Source note 118, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L221)

```text
//       impossible since the index buffer is not in the shared memory buffer
```

## Source note 119, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L222)

```text
//       anymore), though byte swap is still needed as 16-bit indices may also
```

## Source note 120, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L223)

```text
//       be kHostConverted, while they are completely unaffected by this. The
```

## Source note 121, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L224)

```text
//       same applies to primitive type conversion - if it happens for 32-bit
```

## Source note 122, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L225)

```text
//       guest indices, and kHostConverted is returned, they will be
```

## Source note 123, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L226)

```text
//       pre-swapped and pre-masked.
```

## Source note 124, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L227)

```text
// - triangle_fans_supported, line_loops_supported, quad_lists_supported:
```

## Source note 125, line 228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L228)

```text
//   - Pass true or false depending on whether the host actually supports
```

## Source note 126, line 229

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L229)

```text
//     those guest primitive types directly or through geometry shader
```

## Source note 127, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L230)

```text
//     emulation. Debug overriding will be resolved in the common code if
```

## Source note 128, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L231)

```text
//     needed.
```

## Source note 129, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L232)

```text
// - point_sprites_supported_without_vs_expansion,
```

## Source note 130, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L234)

```text
//   - Pass true or false depending on whether the host actually supports
```

## Source note 131, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L235)

```text
//     those guest primitive types directly or through geometry shader
```

## Source note 132, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L236)

```text
//     emulation. Overrides do not apply to these as hosts are not required to
```

## Source note 133, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L237)

```text
//     support the fallback paths since they require different vertex shader
```

## Source note 134, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L238)

```text
//     structure (for the fallback HostVertexShaderTypes).
```

## Source note 135, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L243)

```text
// If any primitive type conversion is needed for auto-indexed draws, called
```

## Source note 136, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L244)

```text
// from InitializeCommon (thus only once in the primitive processor's
```

## Source note 137, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L245)

```text
// lifetime) to set up the backend's index buffer containing indices for
```

## Source note 138, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L246)

```text
// primitive type remapping. The backend must allocate a 4-byte-aligned buffer
```

## Source note 139, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L247)

```text
// with `size_bytes` and call fill_callback for its mapping if creation has
```

## Source note 140, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L248)

```text
// been successful.
```

## Source note 141, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L251)

```text
// Call last in implementation-specific shutdown, also callable from the
```

## Source note 142, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L252)

```text
// destructor.
```

## Source note 143, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L255)

```text
// Call at boundaries of lifespans of converted data (between frames,
```

## Source note 144, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L256)

```text
// preferably in the end of a frame so between the swap and the next draw,
```

## Source note 145, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L257)

```text
// access violation handlers need to do less work).
```

## Source note 146, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L261)

```text
// For simplicity, just using the handles as byte offsets.
```

## Source note 147, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L265)

```text
// The destination allocation must have XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE
```

## Source note 148, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L266)

```text
// excess bytes.
```

## Source note 149, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L269)

```text
// Always moving the host pointer only forward into the allocation padding
```

## Source note 150, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L270)

```text
// space of XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE bytes. Without relying on
```

## Source note 151, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L271)

```text
// two's complement wrapping overflow behavior, the logic would look like:
```

## Source note 152, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L272)

```text
// uintptr_t host_subalignment =
```

## Source note 153, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L273)

```text
//     reinterpret_cast<uintptr_t>(host_index_ptr) &
```

## Source note 154, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L274)

```text
//     (XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE - 1);
```

## Source note 155, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L275)

```text
// uint32_t guest_subalignment = guest_index_base &
```

## Source note 156, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L276)

```text
//                               (XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE - 1);
```

## Source note 157, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L277)

```text
// uintptr_t host_index_address_aligned = host_index_address;
```

## Source note 158, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L278)

```text
// if (guest_subalignment >= host_subalignment) {
```

## Source note 159, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L279)

```text
//   return guest_subalignment - host_subalignment;
```

## Source note 160, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L281)

```text
// return XE_GPU_PRIMITIVE_PROCESSOR_SIMD_SIZE -
```

## Source note 161, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L282)

```text
//        (host_subalignment - guest_subalignment);
```

## Source note 162, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L290)

```text
// Requests a buffer to write the new transformed indices to. The lifetime of
```

## Source note 163, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L291)

```text
// the returned buffer must be that of the current frame. Returns the mapping
```

## Source note 164, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L292)

```text
// of the buffer to write to, or nullptr in case of failure, in addition to,
```

## Source note 165, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L293)

```text
// if successful, a handle that can be used by the backend's command processor
```

## Source note 166, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L294)

```text
// to access the backend-specific data for binding the buffer.
```

## Source note 167, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L302)

```text
// SSSE3 or AVX.
```

## Source note 168, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L320)

```text
// NEON.
```

## Source note 169, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L370)

```text
// For use when the reset index is not 0xFFFF, and 0xFFFF is also used as a
```

## Source note 170, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L371)

```text
// valid index - keeps 0xFFFF as a real index and replaces the reset index
```

## Source note 171, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L372)

```text
// with 0xFFFFFFFF instead.
```

## Source note 172, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L375)

```text
// The reset index and the low 24 bits mask are taken explicitly because this
```

## Source note 173, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L376)

```text
// function may be used two ways:
```

## Source note 174, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L377)

```text
// - Passthrough - when the vertex shader swaps the indices (when 32-bit
```

## Source note 175, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L378)

```text
//   indices are supported on the host), in this case HostSwap is kNone, but
```

## Source note 176, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L379)

```text
//   the reset index and the guest low bits mask can be swapped according to
```

## Source note 177, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L380)

```text
//   the guest endian.
```

## Source note 178, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L381)

```text
// - Swapping for the host - when only 24 bits of an index are supported on
```

## Source note 179, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L382)

```text
//   the host. In this case, masking and comparison are done before applying
```

## Source note 180, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L383)

```text
//   HostSwap, but according to HostSwap, if needed, the data is swapped from
```

## Source note 181, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L384)

```text
//   the PowerPC's big endianness to the host GPU little endianness that we
```

## Source note 182, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L385)

```text
//   assume, which matches the Xenos's little endianness.
```

## Source note 183, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L390)

```text
// The Xbox 360's GPU only uses the low 24 bits of the index - masking.
```

## Source note 184, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L409)

```text
// REX_ARCH_AMD64
```

## Source note 185, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L412)

```text
// Comparison produces 0 or 0xFFFF on AVX and Neon - we need 0xFFFF as
```

## Source note 186, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L413)

```text
// the result for the primitive reset indices, so the result is
```

## Source note 187, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L414)

```text
// `index | (index == reset_index)`.
```

## Source note 188, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L473)

```text
// 4 vertices per strip, and primitive restarts between strips.
```

## Source note 189, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L477)

```text
// Triangle fan test cases:
```

## Source note 190, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L478)

```text
// - 4D5307E6 - main menu - game logo, developer logo, backgrounds of the menu
```

## Source note 191, line 479

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L479)

```text
//   item list (the whole menu and individual items) - no index buffer.
```

## Source note 192, line 480

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L480)

```text
// - 4E4D87E6 - terrain - with an index buffer and primitive reset (note that
```

## Source note 193, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L481)

```text
//   there, vfetch indices are computed in the vertex shader, involving
```

## Source note 194, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L482)

```text
//   floating-point reciprocal, so this case is very sensitive to rounding,
```

## Source note 195, line 483

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L483)

```text
//   and incorrect geometry may occur not because of vertex grouping issues,
```

## Source note 196, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L484)

```text
//   but also due to the behavior of the vertex shader).
```

## Source note 197, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L485)

```text
// Triangle fans as triangle lists.
```

## Source note 198, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L486)

```text
// Ordered as (v1, v2, v0), (v2, v3, v0) in Direct3D.
```

## Source note 199, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L487)

```text
// https://docs.microsoft.com/en-us/windows/desktop/direct3d9/triangle-fans
```

## Source note 200, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L495)

```text
// To match GetTriangleFanListIndexCount.
```

## Source note 201, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L510)

```text
// Even if 2 vertices are supplied, two lines are still drawn between them.
```

## Source note 202, line 511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L511)

```text
// https://www.khronos.org/opengl/wiki/Primitive
```

## Source note 203, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L512)

```text
// "You get n lines for n input vertices"
```

## Source note 204, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L513)

```text
// "If the user only specifies 1 vertex, the drawing command is ignored"
```

## Source note 205, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L520)

```text
// To match GetLineLoopStripIndexCount.
```

## Source note 206, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L535)

```text
// Quad list test cases:
```

## Source note 207, line 536

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L536)

```text
// - 4D5307E6 - main menu - flying dust on the road - no index buffer.
```

## Source note 208, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L550)

```text
// v0, v2, v3.
```

## Source note 209, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L557)

```text
// Pre-gathering the ranges allows for usage of the same functions for
```

## Source note 210, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L558)

```text
// conversion with and without reset. In addition, this increases safety in
```

## Source note 211, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L559)

```text
// weird cases - there won't be mismatch between the pre-calculation of the
```

## Source note 212, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L560)

```text
// post-conversion index count and the actual conversion if the game for some
```

## Source note 213, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L561)

```text
// reason modifies the index buffer between the two and adds or removes reset
```

## Source note 214, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L562)

```text
// indices in it.
```

## Source note 215, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L630)

```text
// Byte offsets used, for simplicity, directly as handles.
```

## Source note 216, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L637)

```text
// Caching for reuse of converted indices within a frame.
```

## Source note 217, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L639)

```text
// 256 KB as the largest possible guest index buffer - 0xFFFF 32-bit indices -
```

## Source note 218, line 640

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L640)

```text
// is slightly smaller than 256 KB, thus cache entries need store links within
```

## Source note 219, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L641)

```text
// at most 2 buckets.
```

## Source note 220, line 650

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L650)

```text
// 32 total
```

## Source note 221, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L651)

```text
// 48
```

## Source note 222, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L652)

```text
// 49
```

## Source note 223, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L653)

```text
// 52
```

## Source note 224, line 654

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L654)

```text
// 53
```

## Source note 225, line 655

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L655)

```text
// kNone if not changing the type (like only processing the reset index).
```

## Source note 226, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L656)

```text
// 59
```

## Source note 227, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L657)

```text
// If set, entry is for forced 32-bit guest DMA to host-endian 24-bit
```

## Source note 228, line 658

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L658)

```text
// index conversion used by non-kVertex host vertex shader types on
```

## Source note 229, line 659

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L659)

```text
// backends not supporting full 32-bit index fetch in this path.
```

## Source note 230, line 660

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L660)

```text
// 60
```

## Source note 231, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L668)

```text
// Clear unused bits, then set each field explicitly, not via the
```

## Source note 232, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L669)

```text
// initializer list (which causes `uint64_t key = 0;` to be ignored, and
```

## Source note 233, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L670)

```text
// also can't contain initializers for aliasing union members).
```

## Source note 234, line 691

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L691)

```text
// Subset of ConversionResult that can be reused for different primitive types
```

## Source note 235, line 692

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L692)

```text
// if the same result is used irrespective of one (like when only processing
```

## Source note 236, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L693)

```text
// the reset index).
```

## Source note 237, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L725)

```text
// A cache transaction performs a few operations in a RAII-like way (so
```

## Source note 238, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L726)

```text
// processing may return an error for any reason, and won't have to clean up
```

## Source note 239, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L727)

```text
// cache_currently_processing_base_ / size_bytes_ explicitly):
```

## Source note 240, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L728)

```text
// - Transaction initialization:
```

## Source note 241, line 729

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L729)

```text
//   - Lookup of previously processed indices in the cache.
```

## Source note 242, line 730

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L730)

```text
//   - If not found, beginning to add a new entry that is going to be
```

## Source note 243, line 732

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L732)

```text
//     - Marking the range as currently being processed, for slightly safer
```

## Source note 244, line 733

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L733)

```text
//       race condition handling if one happens - if invalidation happens
```

## Source note 245, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L734)

```text
//       during the transaction (but outside a global critical region lock,
```

## Source note 246, line 735

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L735)

```text
//       since processing may take a long time), the new cache entry won't be
```

## Source note 247, line 736

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L736)

```text
//       stored as it will already be invalid at the time of the completion of
```

## Source note 248, line 737

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L737)

```text
//       the transaction.
```

## Source note 249, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L738)

```text
//     - Enabling an access callback for the range.
```

## Source note 250, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L739)

```text
// - Setting the new result after processing (if not found in the cache
```

## Source note 251, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L740)

```text
//   previously).
```

## Source note 252, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L741)

```text
// - Transaction completion:
```

## Source note 253, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L742)

```text
//   - If the range wasn't invalidated during the transaction, storing the new
```

## Source note 254, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L743)

```text
//     entry in the cache.
```

## Source note 255, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L744)

```text
// If an entry was found in the cache (GetFoundResult results non-null), it
```

## Source note 256, line 745

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L745)

```text
// MUST be used instead of processing - this class doesn't provide the
```

## Source note 257, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L746)

```text
// possibility replace existing entries.
```

## Source note 258, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L754)

```text
// Replacement of an existing entry is not allowed.
```

## Source note 259, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L763)

```text
// If key_.count == 0, this transaction shouldn't do anything - for empty
```

## Source note 260, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L764)

```text
// ranges it's pointless, and it's unsafe to get the end pointer without
```

## Source note 261, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L765)

```text
// special logic, and count == 0 is also used as a special indicator for
```

## Source note 262, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L766)

```text
// vertex count below the cache usage threshold.
```

## Source note 263, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L782)

```text
// Modified by both the processor and the invalidation callback.
```

## Source note 264, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L784)

```text
// The conversion is performed while the lock is released since it may take a
```

## Source note 265, line 785

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L785)

```text
// long time.
```

## Source note 266, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L786)

```text
// If during the conversion the region currently being converted is
```

## Source note 267, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L787)

```text
// invalidated, the current entry will not be added to the cache.
```

## Source note 268, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L788)

```text
// Modified by the processor, read by the invalidation callback.
```

## Source note 269, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L790)

```text
// 0 if no new conversion is in progress, or a write invalidated it.
```

## Source note 270, line 791

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L791)

```text
// Modified by both the processor and invalidation callback under cache_mutex_.
```

## Source note 271, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L793)

```text
// Modified by both the processor and the invalidation callback.
```

## Source note 272, line 795

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L795)

```text
// Modified by both the processor and the invalidation callback.
```

## Source note 273, line 797

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L797)

```text
// For even faster handling of memory invalidation - whether any bit is set in
```

## Source note 274, line 798

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L798)

```text
// each cache_buckets_non_empty_l1_.
```

## Source note 275, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L799)

```text
// Modified by both the processor and the invalidation callback.
```

## Source note 276, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L801)

```text
// Must be called in a global critical region.
```

## Source note 277, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L814)

```text
// cache_buckets_non_empty_l1_ (along with cache_buckets_non_empty_l2_, which
```

## Source note 278, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L815)

```text
// must be kept in sync) used for indication whether each entry is non-empty,
```

## Source note 279, line 816

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L816)

```text
// for faster clearing (there's no special index here for an empty entry).
```

## Source note 280, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L817)

```text
// Huge, so it's the last in the class.
```

## Source note 281, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/primitive_processor.h#L818)

```text
// Modified by both the processor and the invalidation callback.
```
