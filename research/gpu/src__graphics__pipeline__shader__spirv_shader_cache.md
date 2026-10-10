# Spirv shader cache: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_shader_cache.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L62)

```text
// Tessellation mode selects the domain shader spacing.
```

## Source note 2, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L67)

```text
// User clip planes.
```

## Source note 3, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L74)

```text
// Vertex kill via the kill flag (oPts.z). The "and" operator (kill only when
```

## Source note 4, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L75)

```text
// all vertices of the primitive request it) is emulated with a cull distance.
```

## Source note 5, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L76)

```text
// The "or" operator sets the position to NaN in the translator.
```

## Source note 6, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L80)

```text
// For kPointListAsTriangleStrip the bit means output coordinates (only the
```

## Source note 7, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L81)

```text
// Vulkan fallback uses that host type). Otherwise it means output point size.
```

## Source note 8, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L122)

```text
// Depth/stencil mode, blend pre-multiply and the color target mask are host
```

## Source note 9, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L123)

```text
// render target path state, left at their defaults on the FSI path.
```

## Source note 10, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L125)

```text
// ReXGlue has no per-draw native scale threshold (xenia-edge's
```

## Source note 11, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L126)

```text
// draw_resolution_scale_threshold): every draw takes the target's scale.
```

## Source note 12, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L142)

```text
// kEarlyHint triggers a GPU fault on nvidia (Alan Wake gameplay), so
```

## Source note 13, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L143)

```text
// use the safe alternative.
```

## Source note 14, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L148)

```text
// MIN/MAX blend ignores fixed-function factors on the host, but the Xbox
```

## Source note 15, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L149)

```text
// 360 applies them. When the destination factor is ONE we pre-multiply the
```

## Source note 16, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L150)

```text
// shader output by the source factor. Only RT0 is supported for now.
```

## Source note 17, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L176)

```text
// The FSI shader runs the EDRAM ROP itself, so specialize it for the
```

## Source note 18, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L177)

```text
// sample count. No new pipeline permutations, they already vary by it.
```

## Source note 19, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L179)

```text
// Per render target, the format that drives the pack and unpack trees
```

## Source note 20, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L180)

```text
// and whether it blends. Unlike the sample count these add pipeline
```

## Source note 21, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L181)

```text
// permutations - the FSI render pass has no attachments to vary by - so
```

## Source note 22, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L182)

```text
// skip render targets the draw masks off, which the shader skips anyway.
```

## Source note 23, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L190)

```text
// The shader treats 1 * source + 0 * destination as no blending.
```

## Source note 24, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L196)

```text
// With no blending anywhere, the whole blending path can be left out.
```

## Source note 25, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L217)

```text
// ReXGlue translates on one thread per shader here; claiming a translation
```

## Source note 26, line 218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L218)

```text
// across threads (xenia-edge TryClaimTranslation) isn't needed.
```

## Source note 27, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L222)

```text
// ReXGlue's ShaderTranslator leaves publishing to the backend (the DXBC
```

## Source note 28, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L223)

```text
// path publishes after its replacement step); without it every draw
```

## Source note 29, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L224)

```text
// would translate again. Failures are published too, so they stay.
```

## Source note 30, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L234)

```text
/*use_try_claim=*/
```

## Source note 31, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L246)

```text
// The *AsTriangleStrip host vertex shader types are the fallback for when
```

## Source note 32, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L247)

```text
// geometry shaders are unsupported. There geometry_shader_type is kNone and
```

## Source note 33, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L248)

```text
// this is not called. output_point_parameters means coordinates, not size,
```

## Source note 34, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_shader_cache.cpp#L249)

```text
// for those, so reject them.
```
