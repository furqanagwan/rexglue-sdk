# Spirv translator: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_translator.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L35)

```text
// If anything in this structure is changed in a way not compatible with
```

## Source note 2, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L36)

```text
// the previous layout, invalidate the pipeline storages by increasing this
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L37)

```text
// version number! Backends add it to their dated
```

## Source note 4, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L38)

```text
// PipelineDescription::kVersion, so bumping either one is enough. Only
```

## Source note 5, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L39)

```text
// ever raise it, a reverted layout change needs another bump.
```

## Source note 6, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L44)

```text
// Early fragment tests - enable if alpha test and alpha to coverage are
```

## Source note 7, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L45)

```text
// disabled; ignored if anything in the shader blocks early Z writing.
```

## Source note 8, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L47)

```text
// Converting the depth to the closest 32-bit float representable exactly
```

## Source note 9, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L48)

```text
// as a 20e4 float, truncating towards zero, so SV_DepthLessEqual-style
```

## Source note 10, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L49)

```text
// conservative depth output (ExecutionModeDepthLess) can still allow
```

## Source note 11, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L50)

```text
// coarse early Z culling. MSAA depth must be per-sample, so the shader
```

## Source note 12, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L51)

```text
// runs at sample frequency.
```

## Source note 13, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L52)

```text
// Fixed-function viewport depth bounds must be snapped to float24 too.
```

## Source note 14, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L54)

```text
// Similar to kFloat24Truncating, but rounding to the nearest even, so
```

## Source note 15, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L55)

```text
// plain ExecutionModeDepthReplacing is used rather than DepthLess.
```

## Source note 16, line 57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L57)

```text
// Host RT shader polygon offset for suspected coplanar redraws with tiny
```

## Source note 17, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L58)

```text
// biases. Writes the biased depth from the pixel shader and zeroes fixed
```

## Source note 18, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L59)

```text
// function depth bias to avoid host slope/quantization quirks. This path
```

## Source note 19, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L60)

```text
// is controlled by depth_bias_shader_offset.
```

## Source note 20, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L68)

```text
// uint32_t 0.
```

## Source note 21, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L69)

```text
// Interpolators written by the vertex shader and needed by the pixel
```

## Source note 22, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L70)

```text
// shader.
```

## Source note 23, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L72)

```text
// For HostVertexShaderType kPointListAsTriangleStrip, whether to output
```

## Source note 24, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L73)

```text
// the point coordinates.
```

## Source note 25, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L74)

```text
// For other HostVertexShaderTypes (though truly reachable only for
```

## Source note 26, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L75)

```text
// kVertex), whether to output the point size.
```

## Source note 27, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L77)

```text
// Dynamically indexable register count from SQ_PROGRAM_CNTL.
```

## Source note 28, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L79)

```text
// Pipeline stage and input configuration.
```

## Source note 29, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L81)

```text
// User clip plane count, number of clip planes enabled (0-6).
```

## Source note 30, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L83)

```text
// If user_clip_plane_count is non-zero, whether they should be cull
```

## Source note 31, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L84)

```text
// distances instead of clip distances.
```

## Source note 32, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L86)

```text
// Vertex kill (oPts.z) with the "and" operator - the primitive is culled
```

## Source note 33, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L87)

```text
// only when all of its vertices request the kill, emulated with an extra
```

## Source note 34, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L88)

```text
// cull distance written after the user clip plane cull distances. The
```

## Source note 35, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L89)

```text
// "or" operator sets the position to NaN instead and needs no bit here.
```

## Source note 36, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L91)

```text
// For domain shaders - the tessellation mode, selecting the tessellation
```

## Source note 37, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L92)

```text
// evaluation shader spacing (Direct3D 12 sets it in the hull shaders, but
```

## Source note 38, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L93)

```text
// in SPIR-V the spacing lives in the domain shader). Discrete uses equal
```

## Source note 39, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L94)

```text
// spacing, continuous and adaptive use fractional even.
```

## Source note 40, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L98)

```text
// uint32_t 0.
```

## Source note 41, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L99)

```text
// Interpolators written by the vertex shader and needed by the pixel
```

## Source note 42, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L100)

```text
// shader.
```

## Source note 43, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L103)

```text
// uint32_t 1.
```

## Source note 44, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L104)

```text
// Dynamically indexable register count from SQ_PROGRAM_CNTL. Max 64.
```

## Source note 45, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L108)

```text
// If param_gen_enable is set, this must be set for point primitives, and
```

## Source note 46, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L109)

```text
// must not be set for other primitive types - enables the point sprite
```

## Source note 47, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L110)

```text
// coordinates input, and also effects the flag bits in PsParamGen.
```

## Source note 48, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L112)

```text
// For host render targets - depth / stencil output mode. The FSI path
```

## Source note 49, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L113)

```text
// has no such state, so it aliases these bits as fsi_msaa_samples. The
```

## Source note 50, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L114)

```text
// two paths are mutually exclusive per device.
```

## Source note 51, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L116)

```text
// For host render targets with MIN/MAX blend op - the source blend factor
```

## Source note 52, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L117)

```text
// to pre-multiply the shader output by (since Vulkan/D3D12 MIN/MAX
```

## Source note 53, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L118)

```text
// ignores blend factors, but Xbox 360 applies them). kOne means no
```

## Source note 54, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L119)

```text
// pre-multiply. Only RT0 is supported for now.
```

## Source note 55, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L122)

```text
// For host render targets - which color render targets are actually
```

## Source note 56, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L123)

```text
// bound.
```

## Source note 57, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L125)

```text
// Shared bit, two meanings, one per render target path - a device is on
```

## Source note 58, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L126)

```text
// one path or the other, and neither reads the other's meaning.
```

## Source note 59, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L127)

```text
// FSI path - set when no render target the shader writes has blending
```

## Source note 60, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L128)

```text
// enabled, so the EDRAM ROP skips emitting the blending path entirely.
```

## Source note 61, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L129)

```text
// Host render target path - the draw is inside a hybrid occlusion query
```

## Source note 62, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L130)

```text
// (occlusion_query_full_counters), so count the coverage before the
```

## Source note 63, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L131)

```text
// depth/stencil test into the ZPD counter's Total lane.
```

## Source note 64, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L133)

```text
// PsParamGen and the memexport dedup must act like there's no resolution
```

## Source note 65, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L134)

```text
// scaling. Doesn't affect fetch offsets, those follow texture scale, not
```

## Source note 66, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L135)

```text
// from the draw. This is only set when the draw is native because of a
```

## Source note 67, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L136)

```text
// set scale threshold (FBO only).
```

## Source note 68, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L139)

```text
// The host render target path's fields, assembled into one value so
```

## Source note 69, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L140)

```text
// the FSI path can carve them up without its own uses colliding. Safe
```

## Source note 70, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L141)

```text
// because GetPixelShaderModification only writes the fields themselves
```

## Source note 71, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L142)

```text
// on the host path, and a device is on one path or the other.
```

## Source note 72, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L150)

```text
// The shifts assume the widths declared above. Nothing in C++ can
```

## Source note 73, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L151)

```text
// measure a bitfield, so set_fsi_bits round-trips as the guard.
```

## Source note 74, line 164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L164)

```text
// Catches a field having been narrowed under the shifts above.
```

## Source note 75, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L172)

```text
// The per-sample code is emitted for 1 << this many samples, and the
```

## Source note 76, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L173)

```text
// render target cache rejects the draw above 4x before this is read.
```

## Source note 77, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L179)

```text
// Only meaningful for render targets the shader writes, the rest stay
```

## Source note 78, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L180)

```text
// at zero.
```

## Source note 79, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L231)

```text
// 1 to write new depth to the depth buffer, 0 to keep the old one if the
```

## Source note 80, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L232)

```text
// depth test passes.
```

## Source note 81, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L235)

```text
// If the depth / stencil test has failed, but resulted in a stencil value
```

## Source note 82, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L236)

```text
// that is different than the one currently in the depth buffer, write it
```

## Source note 83, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L237)

```text
// anyway and don't run the rest of the shader (to check if the sample may
```

## Source note 84, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L238)

```text
// be discarded some way) - use when alpha test and alpha to coverage are
```

## Source note 85, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L239)

```text
// disabled. Ignored by the shader if not applicable to it (like if it has
```

## Source note 86, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L240)

```text
// kill instructions or writes the depth output).
```

## Source note 87, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L246)

```text
// For HostVertexShaderType kVertex, if fullDrawIndexUint32 is not
```

## Source note 88, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L247)

```text
// supported (ignored otherwise), whether to fetch the index manually
```

## Source note 89, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L248)

```text
// (32-bit only - 16-bit indices are always fetched via the Vulkan index
```

## Source note 90, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L249)

```text
// buffer).
```

## Source note 91, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L251)

```text
// For HostVertexShaderTypes kMemExportCompute, kPointListAsTriangleStrip,
```

## Source note 92, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L252)

```text
// kRectangleListAsTriangleStrip, whether the vertex index needs to be
```

## Source note 93, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L253)

```text
// loaded from the index buffer (rather than using autogenerated indices),
```

## Source note 94, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L254)

```text
// and whether it's 32-bit. This is separate from kSysFlag_VertexIndexLoad
```

## Source note 95, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L255)

```text
// because the same system constants may be used for the memexporting
```

## Source note 96, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L256)

```text
// compute shader and the vertex shader for the same draw, but
```

## Source note 97, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L257)

```text
// kSysFlag_VertexIndexLoad may be not needed.
```

## Source note 98, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L285)

```text
// IF SYSTEM CONSTANTS ARE CHANGED OR ADDED, THE FOLLOWING MUST BE UPDATED:
```

## Source note 99, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L286)

```text
// - SystemConstantIndex enum.
```

## Source note 100, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L287)

```text
// - Structure members in BeginTranslation.
```

## Source note 101, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L289)

```text
// Using the std140 layout - vec2 must be aligned to 8 bytes, vec3 and vec4 to
```

## Source note 102, line 290

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L290)

```text
// 16 bytes.
```

## Source note 103, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L306)

```text
// Diameter in guest screen coordinates > radius (0.5 * diameter) in the NDC
```

## Source note 104, line 307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L307)

```text
// for the host viewport.
```

## Source note 105, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L310)

```text
// Each byte contains post-swizzle TextureSign values for each of the needed
```

## Source note 106, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L311)

```text
// components of each of the 32 used texture fetch constants.
```

## Source note 107, line 314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L314)

```text
// If the imageViewFormatSwizzle portability subset is not supported, the
```

## Source note 108, line 315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L315)

```text
// component swizzle (taking both guest and host swizzles into account) to
```

## Source note 109, line 316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L316)

```text
// apply to the result directly in the shader code. In each uint32_t,
```

## Source note 110, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L317)

```text
// swizzles for 2 texture fetch constants (in bits 0:11 and 12:23).
```

## Source note 111, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L320)

```text
// Whether the contents of each texture in fetch constants comes from a
```

## Source note 112, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L321)

```text
// resolve operation (bit per texture, 32 textures max).
```

## Source note 113, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L325)

```text
// If alpha to mask is disabled, the entire alpha_to_mask value must be 0.
```

## Source note 114, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L326)

```text
// If alpha to mask is enabled, bits 0:7 are sample offsets, and bit 8 must
```

## Source note 115, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L327)

```text
// be 1.
```

## Source note 116, line 330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L330)

```text
// UINT32_MAX when the draw is outside an active ZPD segment, which is used
```

## Source note 117, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L331)

```text
// as a skip writing sentinel to the FSI counter buffer.
```

## Source note 118, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L361)

```text
// xenos_draw.glsli reads the tessellation fields below at fixed std140
```

## Source note 119, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L362)

```text
// offsets, so these bytes can't be reclaimed.
```

## Source note 120, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L365)

```text
// Render target blending options - RB_BLENDCONTROL, with only the relevant
```

## Source note 121, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L366)

```text
// options (factors and operations - AND 0x1FFF1FFF). If 0x00010001
```

## Source note 122, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L367)

```text
// (1 * src + 0 * dst), blending is disabled for the render target.
```

## Source note 123, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L370)

```text
// Format info - mask to apply to the old packed RT data, and to apply as
```

## Source note 124, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L371)

```text
// inverted to the new packed data, before storing (more or less the inverse
```

## Source note 125, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L372)

```text
// of the write mask packed like render target channels). This can be used
```

## Source note 126, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L373)

```text
// to bypass unpacking if blending is not used. If 0 and not blending,
```

## Source note 127, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L374)

```text
// reading the old data from the EDRAM buffer is not required.
```

## Source note 128, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L377)

```text
// Format info - values to clamp the color to before blending or storing.
```

## Source note 129, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L378)

```text
// Low color, low alpha, high color, high alpha.
```

## Source note 130, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L381)

```text
// The constant blend factor for the respective modes.
```

## Source note 131, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L384)

```text
// User clip planes. Also read by the GLSL tessellation helpers in
```

## Source note 132, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L385)

```text
// xenos_draw.glsli at fixed std140 offsets, guarded by the static_assert
```

## Source note 133, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L386)

```text
// below.
```

## Source note 134, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L388)

```text
// Tessellation factor range: [0] = min, [1] = max. 1.0 is added on the CPU
```

## Source note 135, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L389)

```text
// per Xbox 360 docs. fractional_even partitioning needs min >= 2.0.
```

## Source note 136, line 396

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L396)

```text
// Ucode interpreter VS placeholder. Guest VS ucode location in shared
```

## Source note 137, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L397)

```text
// memory as a dword address, and its control-flow instruction count. Zero
```

## Source note 138, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L398)

```text
// unless the interpreter is bound for this draw. Appended after the
```

## Source note 139, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L399)

```text
// tessellation tail so the static_assert offsets above are unaffected.
```

## Source note 140, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L400)

```text
// Read as std140 uint4 [34].xy by ucode_interpreter.vs.slang.
```

## Source note 141, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L405)

```text
// Packed fixed texture conversion (see GetIntegerScaleBits).
```

## Source note 142, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L406)

```text
// Every component occupies 6 bits in bits 0:23
```

## Source note 143, line 407

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L407)

```text
//   bits 0:3 = component_bits - 1
```

## Source note 144, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L408)

```text
//   bits 4:5 = xenos::TextureSign
```

## Source note 145, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L409)

```text
// bit 24 = normalized num_format
```

## Source note 146, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L410)

```text
// bit 26 = point sampled fetch constant
```

## Source note 147, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L411)

```text
// Zero means no conversion.
```

## Source note 148, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L412)

```text
// Appended at the very tail (std140 uint4 [35]) so it disturbs neither the
```

## Source note 149, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L413)

```text
// xenos_draw.glsli tessellation offsets nor the interpreter [34] slot.
```

## Source note 150, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L417)

```text
// xenos_draw.glsli reads these tessellation fields from the system constants
```

## Source note 151, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L418)

```text
// UBO at these fixed std140 offsets. Keep them in sync.
```

## Source note 152, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L436)

```text
// The minimum limit for maxPerStageDescriptorStorageBuffers is 4, and for
```

## Source note 153, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L437)

```text
// maxStorageBufferRange it's 128 MB. These are the values of those limits on
```

## Source note 154, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L438)

```text
// Arm Mali as of November 2020. Xenia needs 512 MB shared memory to be bound,
```

## Source note 155, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L439)

```text
// therefore SSBOs must only be used for shared memory - all other storage
```

## Source note 156, line 440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L440)

```text
// resources must be images or texel buffers.
```

## Source note 157, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L442)

```text
// According to the "Pipeline Layout Compatibility" section of the Vulkan
```

## Source note 158, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L444)

```text
// "Two pipeline layouts are defined to be "compatible for set N" if they
```

## Source note 159, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L445)

```text
//  were created with identically defined descriptor set layouts for sets
```

## Source note 160, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L446)

```text
//  zero through N, and if they were created with identical push constant
```

## Source note 161, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L447)

```text
//  ranges."
```

## Source note 162, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L448)

```text
// "Place the least frequently changing descriptor sets near the start of
```

## Source note 163, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L449)

```text
//  the pipeline layout, and place the descriptor sets representing the most
```

## Source note 164, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L450)

```text
//  frequently changing resources near the end. When pipelines are switched,
```

## Source note 165, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L451)

```text
//  only the descriptor set bindings that have been invalidated will need to
```

## Source note 166, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L452)

```text
//  be updated and the remainder of the descriptor set bindings will remain
```

## Source note 167, line 453

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L453)

```text
//  in place."
```

## Source note 168, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L454)

```text
// This is partially the reverse of the Direct3D 12's rule of placing the
```

## Source note 169, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L455)

```text
// most frequently changed descriptor sets in the beginning. Here all
```

## Source note 170, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L456)

```text
// descriptor sets with an immutable layout are placed first, in reverse
```

## Source note 171, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L457)

```text
// frequency of changing, and sets that may be different for different
```

## Source note 172, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L458)

```text
// pipeline states last.
```

## Source note 173, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L460)

```text
// Always the same descriptor set layouts for all pipeline layouts:
```

## Source note 174, line 462

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L462)

```text
// Never changed.
```

## Source note 175, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L464)

```text
// Changed in case of changes in the data.
```

## Source note 176, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L467)

```text
// Mutable part of the pipeline layout:
```

## Source note 177, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L470)

```text
// Rarely used at all, but may be changed at an unpredictable rate when
```

## Source note 178, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L471)

```text
// vertex textures are used (for example, for bones of an object, which may
```

## Source note 179, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L472)

```text
// consist of multiple draw commands with different materials).
```

## Source note 180, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L474)

```text
// Per-material textures.
```

## Source note 181, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L486)

```text
// "Xenia Emulator Microcode Translator".
```

## Source note 182, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L487)

```text
// https://github.com/KhronosGroup/SPIRV-Headers/blob/c43a43c7cc3af55910b9bec2a71e3e8a622443cf/include/spirv/spir-v.xml#L79
```

## Source note 183, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L523)

```text
// No defaults - a missing argument would shift the
```

## Source note 184, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L524)

```text
// ones after it and silently take a wrong scale.
```

## Source note 185, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L542)

```text
// Feature set the translator emits for, so host helper shaders (e.g. the
```

## Source note 186, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L543)

```text
// built-in geometry shader) can match the SPIR-V version and float controls.
```

## Source note 187, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L560)

```text
// Creates a special fragment shader without color outputs - this resets the
```

## Source note 188, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L561)

```text
// state of the translator.
```

## Source note 189, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L562)

```text
// Creates a synthetic depth-only fragment shader. When depth_stencil_mode is
```

## Source note 190, line 563

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L563)

```text
// a float24 mode, the shader reads gl_FragCoord.z, converts to float24, and
```

## Source note 191, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L564)

```text
// writes the result to gl_FragDepth - matching the substitute pixel shader
```

## Source note 192, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L565)

```text
// the DXBC backend uses when a guest draw has no pixel shader.
```

## Source note 193, line 570

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L570)

```text
// FSI variant - specialized for one guest sample count instead of a host
```

## Source note 194, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L571)

```text
// depth / stencil mode.
```

## Source note 195, line 575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L575)

```text
// Common functions useful not only for the translator, but also for EDRAM
```

## Source note 196, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L576)

```text
// emulation via conventional render targets.
```

## Source note 197, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L578)

```text
// Converts the color value externally clamped to [0, 31.875] to 7e3 floating
```

## Source note 198, line 579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L579)

```text
// point, with zeros in bits 10:31, rounding to the nearest even.
```

## Source note 199, line 582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L582)

```text
// Same as PreClampedFloat32To7e3, but clamps the input to [0, 31.875].
```

## Source note 200, line 585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L585)

```text
// Converts the 7e3 number in bits [f10_shift, f10_shift + 10) to a 32-bit
```

## Source note 201, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L586)

```text
// float.
```

## Source note 202, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L589)

```text
// Converts the depth value externally clamped to the representable [0, 2)
```

## Source note 203, line 590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L590)

```text
// range to 20e4 floating point, with zeros in bits 24:31, rounding to the
```

## Source note 204, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L591)

```text
// nearest even or towards zero. If remap_from_0_to_0_5 is true, it's assumed
```

## Source note 205, line 592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L592)

```text
// that 0...1 is pre-remapped to 0...0.5 in the input.
```

## Source note 206, line 596

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L596)

```text
// Converts the 20e4 number in bits [f24_shift, f24_shift + 24) to a 32-bit
```

## Source note 207, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L597)

```text
// float.
```

## Source note 208, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L601)

```text
// Piecewise-linear gamma conversions for k_8_8_8_8_GAMMA values stored as
```

## Source note 209, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L602)

```text
// linear UNORM16. Values may be scalars or vectors of up to 3 components.
```

## Source note 210, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L603)

```text
// Unless pre_saturated is true, inputs are clamped to [0, 1] (NaN to 0).
```

## Source note 211, line 637

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L637)

```text
// Stacked and 3D are separate TextureBindings.
```

## Source note 212, line 656

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L656)

```text
// Builder helpers.
```

## Source note 213, line 680

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L680)

```text
// The host render target path's fields of the pixel modification. The FSI
```

## Source note 214, line 681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L681)

```text
// path keeps the EDRAM ROP's specialization in those same bits, so reading
```

## Source note 215, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L682)

```text
// them there is a bug - assert rather than leave it to review.
```

## Source note 216, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L688)

```text
// The modification bit is shared with fsi_no_blending, so it only means
```

## Source note 217, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L689)

```text
// zpd_total on the host render target path.
```

## Source note 218, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L701)

```text
// Whether the current non-FSI pixel shader should convert the depth to 20e4.
```

## Source note 219, line 713

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L713)

```text
// Whether the current non-FSI pixel shader applies polygon offset via shader
```

## Source note 220, line 714

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L714)

```text
// depth output instead of fixed function bias.
```

## Source note 221, line 725

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L725)

```text
// Whether the shader runs at sample frequency - when converting depth to
```

## Source note 222, line 726

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L726)

```text
// float24 from the rasterizer's own depth (not guest oDepth), each sample
```

## Source note 223, line 727

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L727)

```text
// needs its own depth value for intersections to be antialiased.
```

## Source note 224, line 738

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L738)

```text
// Returns UINT32_MAX if PsParamGen doesn't need to be written.
```

## Source note 225, line 741

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L741)

```text
// Must be called before emitting any SPIR-V operations that must be in a
```

## Source note 226, line 742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L742)

```text
// block in translator callbacks to ensure that if the last instruction added
```

## Source note 227, line 743

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L743)

```text
// was something like OpBranch - in this case, an unreachable block is
```

## Source note 228, line 744

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L744)

```text
// created.
```

## Source note 229, line 758

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L758)

```text
// Writes gl_FragDepth for FBO shaders that need explicit depth: guest oDepth,
```

## Source note 230, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L759)

```text
// float24 conversion, or the host RT decal bias path.
```

## Source note 231, line 762

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L762)

```text
// Updates the current flow control condition (to be called in the beginning
```

## Source note 232, line 763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L763)

```text
// of exec and in jumps), closing the previous conditionals if needed.
```

## Source note 233, line 764

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L764)

```text
// However, if the condition is not different, the instruction-level predicate
```

## Source note 234, line 765

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L765)

```text
// conditional also won't be closed - this must be checked separately if
```

## Source note 235, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L766)

```text
// needed (for example, in jumps).
```

## Source note 236, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L769)

```text
// Opens or reopens the predicate check conditional for the instruction.
```

## Source note 237, line 770

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L770)

```text
// Should be called before processing a non-control-flow instruction.
```

## Source note 238, line 772

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L772)

```text
// Closes the instruction-level predicate conditional if it's open, useful if
```

## Source note 239, line 773

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L773)

```text
// a control flow instruction needs to do some code which needs to respect the
```

## Source note 240, line 774

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L774)

```text
// current exec conditional, but can't itself be predicated.
```

## Source note 241, line 776

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L776)

```text
// Closes conditionals opened by exec and instructions within them (but not by
```

## Source note 242, line 777

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L777)

```text
// labels) and updates the state accordingly.
```

## Source note 243, line 782

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L782)

```text
// Loads unswizzled operand without sign modifiers as float4.
```

## Source note 244, line 786

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L786)

```text
// Returns the requested components, with the operand's swizzle applied, in a
```

## Source note 245, line 787

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L787)

```text
// condensed form, but without negation / absolute value modifiers. The
```

## Source note 246, line 788

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L788)

```text
// storage is float4, no matter what the component count of original_operand
```

## Source note 247, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L789)

```text
// is (the storage will be either r# or c#, but the instruction may be
```

## Source note 248, line 790

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L790)

```text
// scalar).
```

## Source note 249, line 801

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L801)

```text
// If components are identical, the same Id will be written to both outputs.
```

## Source note 250, line 805

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L805)

```text
// Gets the absolute value of the loaded operand if it's not absolute already.
```

## Source note 251, line 807

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L807)

```text
// The type of the value must be a float vector consisting of
```

## Source note 252, line 808

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L808)

```text
// rex::bit_count(result.GetUsedResultComponents()) elements, or (to replicate
```

## Source note 253, line 809

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L809)

```text
// a scalar into all used components) float, or the value can be spv::NoResult
```

## Source note 254, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L810)

```text
// if there's no result to store (like constants only).
```

## Source note 255, line 813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L813)

```text
// For Shader Model 3 multiplication (+-0 or denormal * anything = +0),
```

## Source note 256, line 814

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L814)

```text
// replaces the value with +0 if the minimum of the two operands is 0. This
```

## Source note 257, line 815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L815)

```text
// must be called with absolute values of operands - use GetAbsoluteOperand!
```

## Source note 258, line 817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L817)

```text
// Reduces floating-point precision by truncating mantissa bits with rounding.
```

## Source note 259, line 818

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L818)

```text
// Used to match Xbox 360 Xenos GPU hardware approximation instructions
```

## Source note 260, line 819

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L819)

```text
// (RCP, RSQ, EXP, LOG, SQRT) that provide ~2^-21 relative error tolerance
```

## Source note 261, line 820

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L820)

```text
// instead of full IEEE-754 precision (equivalent to 21 vs 23 mantissa bits).
```

## Source note 262, line 822

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L822)

```text
// Pack/unpack two floats as Xbox 360 extended-range float16, where exponent
```

## Source note 263, line 823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L823)

```text
// 31 is a large finite value (up to +-131008), not Inf/NaN.
```

## Source note 264, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L826)

```text
// Conditionally discard the current fragment. Changes the build point.
```

## Source note 265, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L828)

```text
// Return type is a rex::bit_count(result.GetUsedResultComponents())-component
```

## Source note 266, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L829)

```text
// float vector or a single float, depending on whether it's a reduction
```

## Source note 267, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L830)

```text
// instruction (check getTypeId of the result), or returns spv::NoResult if
```

## Source note 268, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L831)

```text
// nothing to store.
```

## Source note 269, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L835)

```text
// Returns a float value to write to the previous scalar register and to the
```

## Source note 270, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L836)

```text
// destination. If the return value is ps itself (in the retain_prev case),
```

## Source note 271, line 837

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L837)

```text
// returns spv::NoResult (handled as a special case, so if it's retain_prev,
```

## Source note 272, line 838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L838)

```text
// but don't need to write to anywhere, no OpLoad(ps) will be done).
```

## Source note 273, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L843)

```text
// Perform endian swap of a uint scalar or vector.
```

## Source note 274, line 845

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L845)

```text
// Perform endian swap of a uint4 vector.
```

## Source note 275, line 849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L849)

```text
// If `replace_mask` is provided, the bits specified in the mask will be
```

## Source note 276, line 850

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L850)

```text
// replaced with those from the value via OpAtomicAnd/Or.
```

## Source note 277, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L851)

```text
// Bits of `value` not in `replace_mask` will be ignored.
```

## Source note 278, line 874

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L874)

```text
// `texture_parameters` need to be set up except for `sampler`, which will be
```

## Source note 279, line 875

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L875)

```text
// set internally, optionally doing linear interpolation between the an
```

## Source note 280, line 876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L876)

```text
// existing value and the new one (the result location may be the same as for
```

## Source note 281, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L877)

```text
// the first lerp endpoint, but not across signedness). getBCF samples one
```

## Source note 282, line 878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L878)

```text
// image in both slots, with its black and white border samplers.
```

## Source note 283, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L886)

```text
// `texture_parameters` need to be set up except for `sampler`, which will be
```

## Source note 284, line 887

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L887)

```text
// set internally.
```

## Source note 285, line 893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L893)

```text
// The guest sample count baked into the modification, so the MSAA dependent
```

## Source note 286, line 894

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L894)

```text
// code is emitted for that count alone rather than selected at runtime.
```

## Source note 287, line 899

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L899)

```text
// Set when nothing the shader writes blends, so the blending path can be
```

## Source note 288, line 900

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L900)

```text
// left out entirely.
```

## Source note 289, line 905

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L905)

```text
// Only call for render targets the shader writes.
```

## Source note 290, line 910

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L910)

```text
// Guest samples per pixel - how many of main_fsi_sample_mask_'s per-sample
```

## Source note 291, line 911

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L911)

```text
// bits and of the EDRAM ROP code are meaningful.
```

## Source note 292, line 913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L913)

```text
// Whether it's possible and worth skipping running the translated shader for
```

## Source note 293, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L914)

```text
// 2x2 quads.
```

## Source note 294, line 922

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L922)

```text
// The address must be a signed int. Whether the render target is 64bpp, if
```

## Source note 295, line 923

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L923)

```text
// present at all, must be a bool (if it's NoResult, 32bpp will be assumed).
```

## Source note 296, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L926)

```text
// Updates main_fsi_sample_mask_. Must be called outside non-uniform control
```

## Source note 297, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L927)

```text
// flow because of taking derivatives of the fragment depth.
```

## Source note 298, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L929)

```text
// Adds the selected depth/stencil outcomes to the active ZPD counter slot.
```

## Source note 299, line 931

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L931)

```text
// Adds the coverage before the depth/stencil test to the Total lane of the
```

## Source note 300, line 932

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L932)

```text
// active ZPD counter slot.
```

## Source note 301, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L935)

```text
// Alpha to coverage helper - tests one sample.
```

## Source note 302, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L936)

```text
// coverage_out is modified to include this sample if it passes.
```

## Source note 303, line 941

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L941)

```text
// Alpha to coverage main function.
```

## Source note 304, line 943

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L943)

```text
// Returns the first and the second 32 bits as two uints.
```

## Source note 305, line 944

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L944)

```text
// Both are specialized for the render target's format through the
```

## Source note 306, line 945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L945)

```text
// modification - only that format's path is emitted.
```

## Source note 307, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L950)

```text
// The bounds must have the same number of components as the color or alpha.
```

## Source note 308, line 960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L960)

```text
// If source_color_clamped, dest_color, constant_color_clamped are
```

## Source note 309, line 961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L961)

```text
// spv::NoResult, will blend the alpha. Otherwise, will blend the color.
```

## Source note 310, line 962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L962)

```text
// The result will be unclamped (color packing is supposed to clamp it).
```

## Source note 311, line 975

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L975)

```text
// Scale of the draw being translated. All position-dependent paths use
```

## Source note 312, line 976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L976)

```text
// these. Only fetch offset scaling uses draw_resolution_scale_x_/y_ directly.
```

## Source note 313, line 977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L977)

```text
// The scale threshold is host render target state - the FSI path has no
```

## Source note 314, line 978

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L978)

```text
// host targets and stores RT formats in that bit, so it always scales.
```

## Source note 315, line 989

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L989)

```text
// Whether point sampled fetches at an interpolated coordinate pick the guest
```

## Source note 316, line 990

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L990)

```text
// texel sampled at the guest pixel center, rather than at the host pixel.
```

## Source note 317, line 993

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L993)

```text
// For safety with different drivers (even though fragment shader interlock in
```

## Source note 318, line 994

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L994)

```text
// SPIR-V only has one control flow requirement - that both begin and end must
```

## Source note 319, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L995)

```text
// be dynamically executed exactly once in this order), adhering to the more
```

## Source note 320, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L996)

```text
// strict control flow limitations of OpenGL (GLSL) fragment shader interlock,
```

## Source note 321, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L997)

```text
// that begin and end are called only on the outermost level of the control
```

## Source note 322, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L998)

```text
// flow of the main function, and that there are no returns before either
```

## Source note 323, line 999

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L999)

```text
// (there's a single return from the shader).
```

## Source note 324, line 1001

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1001)

```text
// A device and cvar constant, not draw state.
```

## Source note 325, line 1003

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1003)

```text
// occlusion_query_full_counters - FSI shaders also count ZFail and
```

## Source note 326, line 1004

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1004)

```text
// StencilFail. Part of the pipeline storage key.
```

## Source note 327, line 1007

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1007)

```text
// Is currently writing the empty depth-only pixel shader, such as for depth
```

## Source note 328, line 1008

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1008)

```text
// and stencil testing with fragment shader interlock.
```

## Source note 329, line 1015

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1015)

```text
// For helper functions like operand loading, so they don't conflict with
```

## Source note 330, line 1016

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1016)

```text
// id_vector_temp_ usage in bigger callbacks.
```

## Source note 331, line 1032

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1032)

```text
// Index = component count - 1.
```

## Source note 332, line 1085

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1085)

```text
// vec2(0.0, 1.0), to arbitrarily VectorShuffle non-constant and constant
```

## Source note 333, line 1086

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1086)

```text
// components.
```

## Source note 334, line 1118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1118)

```text
// Accessed as float4[2], not float2[4], due to std140 array stride
```

## Source note 335, line 1119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1119)

```text
// alignment.
```

## Source note 336, line 1141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1141)

```text
// Not using combined images and samplers because
```

## Source note 337, line 1142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1142)

```text
// maxPerStageDescriptorSamplers is often lower than
```

## Source note 338, line 1143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1143)

```text
// maxPerStageDescriptorSampledImages, and for every fetch constant, there
```

## Source note 339, line 1144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1144)

```text
// are, for regular fetches, two bindings (unsigned and signed).
```

## Source note 340, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1148)

```text
// VS as VS only - int.
```

## Source note 341, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1150)

```text
// VS as TES only - per-control-point float array carrying the patch/control
```

## Source note 342, line 1151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1151)

```text
// point index computed by the host vertex and hull shaders.
```

## Source note 343, line 1153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1153)

```text
// VS as TES only - float3 (barycentric coordinates).
```

## Source note 344, line 1155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1155)

```text
// PS, only when needed - float2.
```

## Source note 345, line 1157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1157)

```text
// PS, only when needed - float4.
```

## Source note 346, line 1159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1159)

```text
// PS, only when needed - bool.
```

## Source note 347, line 1161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1161)

```text
// PS, only when needed - int[1].
```

## Source note 348, line 1164

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1164)

```text
// PS, barycentric coordinate inputs (when fragment_shader_barycentric is
```

## Source note 349, line 1165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1165)

```text
// enabled) - float3.
```

## Source note 350, line 1169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1169)

```text
// PS, per-vertex interpolator arrays for barycentric interpolation (when
```

## Source note 351, line 1170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1170)

```text
// fragment_shader_barycentric is enabled). Stores the array variable
```

## Source note 352, line 1171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1171)

```text
// (float4[3]) for each interpolator.
```

## Source note 353, line 1174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1174)

```text
// VS output or PS input, only the ones that are needed (spv::NoResult for the
```

## Source note 354, line 1175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1175)

```text
// unneeded interpolators), indexed by the guest interpolator index - float4.
```

## Source note 355, line 1176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1176)

```text
// The Qualcomm Adreno driver has strict requirements for stage linkage - as
```

## Source note 356, line 1177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1177)

```text
// Xenia uses separate variables, not an array (so the interpolation
```

## Source note 357, line 1178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1178)

```text
// qualifiers can be applied to each element separately), the interpolators
```

## Source note 358, line 1179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1179)

```text
// must also be separate variables in the other stage, including the geometry
```

## Source note 359, line 1180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1180)

```text
// shader (not just an array assuming that consecutive locations will be
```

## Source note 360, line 1181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1181)

```text
// linked as consecutive array elements, on Qualcomm, they won't be linked at
```

## Source note 361, line 1182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1182)

```text
// all).
```

## Source note 362, line 1185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1185)

```text
// VS, only for HostVertexShaderType::kPointListAsTriangleStrip when needed
```

## Source note 363, line 1186

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1186)

```text
// for the PS - float2.
```

## Source note 364, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1188)

```text
// VS, only when needed - float.
```

## Source note 365, line 1199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1199)

```text
// VS, only for HostVertexShaderType::kRectangleListAsTriangleStrip.
```

## Source note 366, line 1201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1201)

```text
// uint (lower 2 bits of the expanded host vertex index).
```

## Source note 367, line 1203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1203)

```text
// int3 (guest indices for the 3 rectangle vertices after base addition).
```

## Source note 368, line 1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1205)

```text
// float4[3] (guest clip-space positions for the 3 rectangle vertices).
```

## Source note 369, line 1207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1207)

```text
// For used interpolators only: float4[3].
```

## Source note 370, line 1210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1210)

```text
// Function-scoped variables for fragment color data.
```

## Source note 371, line 1211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1211)

```text
// Used by both FSI and FBO paths so that color values can be read back
```

## Source note 372, line 1212

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1212)

```text
// (e.g., for alpha test). For FBO, these are copied to output_fragment_data_
```

## Source note 373, line 1213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1213)

```text
// at the end of the shader.
```

## Source note 374, line 1216

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1216)

```text
// FBO only: Actual framebuffer color attachment outputs (Output storage).
```

## Source note 375, line 1217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1217)

```text
// These are write-only and populated at the end of the shader from
```

## Source note 376, line 1218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1218)

```text
// output_or_var_fragment_data_.
```

## Source note 377, line 1221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1221)

```text
// Function-scoped staging variable for guest oDepth writes. Used by both
```

## Source note 378, line 1222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1222)

```text
// FSI (which writes the value to the EDRAM buffer inside the interlock)
```

## Source note 379, line 1223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1223)

```text
// and FBO (copied to output_fragment_depth_ at the end of the shader,
```

## Source note 380, line 1224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1224)

```text
// remapping guest 0...1 to host 0...0.5 when the depth format is float24).
```

## Source note 381, line 1227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1227)

```text
// FBO only: actual gl_FragDepth Output.
```

## Source note 382, line 1228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1228)

```text
// Written at the end of the pixel shader from output_or_var_fragment_depth_.
```

## Source note 383, line 1230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1230)

```text
// Raster depth and derivatives captured early for the host RT decal path.
```

## Source note 384, line 1234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1234)

```text
// Fragment shader sample mask output (gl_SampleMask).
```

## Source note 385, line 1235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1235)

```text
// Only used for alpha-to-coverage in non-FSI mode.
```

## Source note 386, line 1236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1236)

```text
// For FSI mode, sample mask is handled via main_fsi_sample_mask_.
```

## Source note 387, line 1242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1242)

```text
// bool.
```

## Source note 388, line 1244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1244)

```text
// uint4.
```

## Source note 389, line 1246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1246)

```text
// int4.
```

## Source note 390, line 1248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1248)

```text
// int.
```

## Source note 391, line 1250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1250)

```text
// float.
```

## Source note 392, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1252)

```text
// `base + index * stride` in dwords from the last vfetch_full as it may be
```

## Source note 393, line 1253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1253)

```text
// needed by vfetch_mini - int.
```

## Source note 394, line 1255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1255)

```text
// Exclusive end (base + size) in dwords of the last vfetch_full's buffer, for
```

## Source note 395, line 1256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1256)

```text
// clamping out-of-bounds words to 0 in both it and its vfetch_mini - int.
```

## Source note 396, line 1258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1258)

```text
// float.
```

## Source note 397, line 1260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1260)

```text
// float3.
```

## Source note 398, line 1263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1263)

```text
// float4[register_count()].
```

## Source note 399, line 1265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1265)

```text
// Components of registers 0-15, 4 bits per register, that still hold the
```

## Source note 400, line 1266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1266)

```text
// interpolant they were initialized with.
```

## Source note 401, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1268)

```text
// float4 each, the interpolant at the guest pixel center minus at the host
```

## Source note 402, line 1269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1269)

```text
// pixel, for IsGuestPixelCenterFetchNeeded.
```

## Source note 403, line 1272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1272)

```text
// Guest instruction bisect, snapshotting a register to color 0.
```

## Source note 404, line 1281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1281)

```text
// float4 holding the watched register at the chosen instruction.
```

## Source note 405, line 1283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1283)

```text
// Memory export variables are created only when needed.
```

## Source note 406, line 1284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1284)

```text
// float4.
```

## Source note 407, line 1286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1286)

```text
// Each is float4.
```

## Source note 408, line 1288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1288)

```text
// Bit field of which eM# elements have been written so far by the invocation
```

## Source note 409, line 1289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1289)

```text
// since the last memory write - uint.
```

## Source note 410, line 1291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1291)

```text
// If memory export is disabled in certain invocations or (if emulating some
```

## Source note 411, line 1292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1292)

```text
// primitive types without a geometry shader) at specific guest vertex loop
```

## Source note 412, line 1293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1293)

```text
// iterations because the translated shader is executed multiple times for the
```

## Source note 413, line 1294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1294)

```text
// same guest vertex or pixel, this contains whether memory export is allowed
```

## Source note 414, line 1295

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1295)

```text
// in the current execution of the translated code.
```

## Source note 415, line 1296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1296)

```text
// bool.
```

## Source note 416, line 1298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1298)

```text
// VS only - float3 (special exports).
```

## Source note 417, line 1300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1300)

```text
// PS, only when needed - bool.
```

## Source note 418, line 1302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1302)

```text
// PS, when writing to color render targets - uint.
```

## Source note 419, line 1303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1303)

```text
// Whether color buffers have been written to, if not written on the taken
```

## Source note 420, line 1304

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1304)

```text
// execution path, don't export according to Direct3D 9 register documentation
```

## Source note 421, line 1305

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1305)

```text
// (some games rely on this behavior).
```

## Source note 422, line 1306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1306)

```text
// Used by both FSI and FBO paths for proper alpha test / alpha-to-coverage
```

## Source note 423, line 1307

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1307)

```text
// behavior.
```

## Source note 424, line 1309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1309)

```text
// Hybrid ZPD query coverage before the depth/stencil test, from
```

## Source note 425, line 1310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1310)

```text
// SampleMaskIn, narrowed by alpha to coverage.
```

## Source note 426, line 1312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1312)

```text
// Loaded by FSI_LoadSampleMask.
```

## Source note 427, line 1313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1313)

```text
// Can be modified on the outermost control flow level in the main function.
```

## Source note 428, line 1314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1314)

```text
// 0:3 - Per-sample coverage at the current stage of the shader's execution.
```

## Source note 429, line 1315

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1315)

```text
//       Affected by things like gl_SampleMaskIn, early or late depth /
```

## Source note 430, line 1316

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1316)

```text
//       stencil (always resets bits for failing, no matter if need to defer
```

## Source note 431, line 1317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1317)

```text
//       writing), alpha to coverage.
```

## Source note 432, line 1318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1318)

```text
// 4:7 - Depth write deferred mask - when early depth / stencil resulted in a
```

## Source note 433, line 1319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1319)

```text
//       different value for the sample (like different stencil if the test
```

## Source note 434, line 1320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1320)

```text
//       failed), but can't write it before running the shader because it's
```

## Source note 435, line 1321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1321)

```text
//       not known if the sample will be discarded by the shader, alphatest or
```

## Source note 436, line 1322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1322)

```text
//       AtoC.
```

## Source note 437, line 1323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1323)

```text
// Early depth / stencil rejection of the pixel is possible when both 0:3 and
```

## Source note 438, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1324)

```text
// 4:7 are zero.
```

## Source note 439, line 1326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1326)

```text
// Per-sample depth/stencil test failures from FSI_DepthStencilTest, zero
```

## Source note 440, line 1327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1327)

```text
// unless occlusion_query_full_counters is enabled. A sample is in at most one
```

## Source note 441, line 1328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1328)

```text
// of these, stencil failure taking precedence.
```

## Source note 442, line 1331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1331)

```text
// Loaded by FSI_LoadEdramOffsets.
```

## Source note 443, line 1332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1332)

```text
// Including the depth render target base.
```

## Source note 444, line 1334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1334)

```text
// Not including the render target base.
```

## Source note 445, line 1337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1337)

```text
// Loaded by FSI_DepthStencilTest for early depth / stencil, the depth /
```

## Source note 446, line 1338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1338)

```text
// stencil values to write at the end of the shader if the specified in
```

## Source note 447, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1339)

```text
// main_fsi_sample_mask_ and if the samples were not discarded later after the
```

## Source note 448, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1340)

```text
// early test.
```

## Source note 449, line 1347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1347)

```text
// VS only, for HostVertexShaderType::kRectangleListAsTriangleStrip.
```

## Source note 450, line 1351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1351)

```text
// int (0..2), OpPhi in main_rect_list_loop_header_.
```

## Source note 451, line 1353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1353)

```text
// int, produced in main_rect_list_loop_continue_ and consumed by the OpPhi in
```

## Source note 452, line 1354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1354)

```text
// main_rect_list_loop_header_.
```

## Source note 453, line 1361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1361)

```text
// If the exec bool constant / predicate conditional is open, block after it
```

## Source note 454, line 1362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1362)

```text
// (not added to the function yet).
```

## Source note 455, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1364)

```text
// If the instruction-level predicate conditional is open, block after it (not
```

## Source note 456, line 1365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1365)

```text
// added to the function yet).
```

## Source note 457, line 1367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1367)

```text
// When cf_exec_conditional_merge_ is not null:
```

## Source note 458, line 1368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1368)

```text
// If the current exec conditional is based on a bool constant: the number of
```

## Source note 459, line 1369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1369)

```text
// the bool constant.
```

## Source note 460, line 1370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1370)

```text
// If it's based on the predicate value: kCfExecBoolConstantPredicate.
```

## Source note 461, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1373)

```text
// When cf_exec_conditional_merge_ is not null, the expected bool constant or
```

## Source note 462, line 1374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1374)

```text
// predicate value for the current exec conditional.
```

## Source note 463, line 1376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1376)

```text
// When cf_instruction_predicate_merge_ is not null, the expected predicate
```

## Source note 464, line 1377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1377)

```text
// value for the current or the last instruction.
```

## Source note 465, line 1379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1379)

```text
// Whether there was a `setp` in the current exec before the current
```

## Source note 466, line 1380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1380)

```text
// instruction, thus instruction-level predicate value can be different than
```

## Source note 467, line 1381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1381)

```text
// the exec-level predicate value, and can't merge two execs with the same
```

## Source note 468, line 1382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_translator.h#L1382)

```text
// predicate condition anymore.
```
