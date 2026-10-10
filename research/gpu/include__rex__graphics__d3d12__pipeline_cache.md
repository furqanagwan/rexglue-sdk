# Pipeline cache: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/d3d12/pipeline_cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L64)

```text
// No ClearCache because it's undesirable with the persistent shader storage
```

## Source note 2, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L65)

```text
// (if the storage is reloaded, effectively nothing is cleared, while the call
```

## Source note 3, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L66)

```text
// takes a long time, and if it's not, there will be heavy stuttering for the
```

## Source note 4, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L67)

```text
// rest of the execution of the guest).
```

## Source note 5, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L75)

```text
// Blocks until the asynchronous pipeline creation queue is empty.
```

## Source note 6, line 77

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L77)

```text
// Creates the queued pipelines on this thread too, then waits for the rest:
```

## Source note 7, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L78)

```text
// for a draw that can't be skipped while its pipeline compiles.
```

## Source note 8, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L80)

```text
// Waits for one queued pipeline only, creating it on this thread unless a
```

## Source note 9, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L81)

```text
// creation thread already is.
```

## Source note 10, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L86)

```text
// Analyze shader microcode on the translator thread.
```

## Source note 11, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L89)

```text
// Retrieves the shader modification for the current state. The shader must
```

## Source note 12, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L90)

```text
// have microcode analyzed.
```

## Source note 13, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L98)

```text
// If draw_util::IsRasterizationPotentiallyDone is false, the pixel shader
```

## Source note 14, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L99)

```text
// MUST be made nullptr BEFORE calling this!
```

## Source note 15, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L110)

```text
// The SPIR-V -> DXIL guest shader path (RG-GDK-032), chosen with
```

## Source note 16, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L111)

```text
// gpu_shader_path=dxil when supported.
```

## Source note 17, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L115)

```text
// The draw needs something the path doesn't do yet: use DXBC.
```

## Source note 18, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L117)

```text
// Translation, DXIL conversion or pipeline creation failed.
```

## Source note 19, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L120)

```text
// Configures the draw's pipeline with xenia-edge's SPIR-V translator and
```

## Source note 20, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L121)

```text
// Mesa spirv_to_dxil; the shaders it returns give the draw's bindings.
```

## Source note 21, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L133)

```text
// Returns a pipeline with deferred creation by its handle. May return nullptr
```

## Source note 22, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L134)

```text
// if failed to create the pipeline.
```

## Source note 23, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L138)

```text
// Whether the pipeline is queued for asynchronous creation and not created
```

## Source note 24, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L139)

```text
// (or failed) yet.
```

## Source note 25, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L155)

```text
// Update PipelineDescription::kVersion if any of the Pipeline* enums are
```

## Source note 26, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L156)

```text
// changed!
```

## Source note 27, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L189)

```text
// Lines expanded to 1 guest pixel wide for resolution-scaled draws.
```

## Source note 28, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L197)

```text
// Special case, handled via disabling the pixel shader and depth / stencil.
```

## Source note 29, line 217

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L217)

```text
// Update PipelineDescription::kVersion if anything is changed!
```

## Source note 30, line 219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L219)

```text
// 1
```

## Source note 31, line 220

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L220)

```text
// 5
```

## Source note 32, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L221)

```text
// 9
```

## Source note 33, line 222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L222)

```text
// 13
```

## Source note 34, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L223)

```text
// 16
```

## Source note 35, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L224)

```text
// 20
```

## Source note 36, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L225)

```text
// 24
```

## Source note 37, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L226)

```text
// 27
```

## Source note 38, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L227)

```text
// 31
```

## Source note 39, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L233)

```text
// 0 if drawing without a pixel shader.
```

## Source note 40, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L240)

```text
// 2
```

## Source note 41, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L241)

```text
// PipelinePrimitiveTopologyType for a vertex shader.
```

## Source note 42, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L242)

```text
// xenos::TessellationMode for a domain shader.
```

## Source note 43, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L243)

```text
// 4
```

## Source note 44, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L244)

```text
// Zero for non-kVertex host_vertex_shader_type.
```

## Source note 45, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L245)

```text
// 7
```

## Source note 46, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L246)

```text
// 8
```

## Source note 47, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L247)

```text
// 10
```

## Source note 48, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L248)

```text
// 11
```

## Source note 49, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L249)

```text
// 12
```

## Source note 50, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L250)

```text
// 14
```

## Source note 51, line 251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L251)

```text
// 15
```

## Source note 52, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L252)

```text
// 18
```

## Source note 53, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L253)

```text
// 19
```

## Source note 54, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L254)

```text
// 20
```

## Source note 55, line 255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L255)

```text
// 28
```

## Source note 56, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L256)

```text
// Hybrid occlusion query draw (RTV + in-shader Total counting). Selects
```

## Source note 57, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L257)

```text
// the counting depth-only pixel shader when there is no guest PS.
```

## Source note 58, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L258)

```text
// 29
```

## Source note 59, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L259)

```text
// Survey draw for VIZ conditional rendering (ROV + occlusion_query_viz).
```

## Source note 60, line 260

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L260)

```text
// Selects the depth-only pixel shader that marks the ZPass lane.
```

## Source note 61, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L261)

```text
// 30
```

## Source note 62, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L262)

```text
// SPIR-V -> DXIL guest shaders (RG-GDK-032): the modifications are
```

## Source note 63, line 263

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L263)

```text
// SpirvShaderTranslator ones. On the ROV path without a guest pixel
```

## Source note 64, line 264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L264)

```text
// shader, pixel_shader_modification holds the guest sample count.
```

## Source note 65, line 265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L265)

```text
// 31
```

## Source note 66, line 267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L267)

```text
// 8
```

## Source note 67, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L268)

```text
// 11
```

## Source note 68, line 269

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L269)

```text
// 14
```

## Source note 69, line 270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L270)

```text
// 17
```

## Source note 70, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L271)

```text
// 20
```

## Source note 71, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L272)

```text
// 23
```

## Source note 72, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L273)

```text
// 26
```

## Source note 73, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L274)

```text
// 29
```

## Source note 74, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L275)

```text
// 32
```

## Source note 75, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L292)

```text
// With description.dxil, the SPIR-V translations converted to DXIL when
```

## Source note 76, line 293

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L293)

```text
// the pipeline is created (on a creation thread with async compilation),
```

## Source note 77, line 294

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L294)

```text
// and the geometry shader's DXIL, used instead of the DXBC ones.
```

## Source note 78, line 313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L313)

```text
// PA_CL_CLIP_CNTL::ps_ucp_mode for point primitives.
```

## Source note 79, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L331)

```text
// Can be called from multiple threads.
```

## Source note 80, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L338)

```text
// If draw_util::IsRasterizationPotentiallyDone is false, the pixel shader
```

## Source note 81, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L339)

```text
// MUST be made nullptr BEFORE calling this! The shaders must be translated
```

## Source note 82, line 340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L340)

```text
// and valid unless for_placeholder is true.
```

## Source note 83, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L366)

```text
// Temporary storage for AnalyzeUcode calls on the processor thread.
```

## Source note 84, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L368)

```text
// Reusable shader translator for the processor thread.
```

## Source note 85, line 371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L371)

```text
// The title's replacement shaders, read once at startup (RG-GDK-067).
```

## Source note 86, line 375

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L375)

```text
// Command processor thread DXIL conversion/disassembly interfaces, if DXIL
```

## Source note 87, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L376)

```text
// disassembly is enabled.
```

## Source note 88, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L381)

```text
// Ucode hash -> shader.
```

## Source note 89, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L390)

```text
// Texture binding layouts of different shaders, for obtaining layout UIDs.
```

## Source note 90, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L392)

```text
// Map of texture binding layouts used by shaders, for obtaining UIDs. Keys
```

## Source note 91, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L393)

```text
// are XXH3 hashes of layouts, values need manual collision resolution using
```

## Source note 92, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L394)

```text
// layout_vector_offset:layout_length of texture_binding_layouts_.
```

## Source note 93, line 397

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L397)

```text
// Bindless sampler indices of different shaders, for obtaining layout UIDs.
```

## Source note 94, line 398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L398)

```text
// For bindful, sampler count is used as the UID instead.
```

## Source note 95, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L400)

```text
// Keys are XXH3 hashes of used bindless sampler indices.
```

## Source note 96, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L404)

```text
// Geometry shaders for Xenos primitive types not supported by Direct3D 12.
```

## Source note 97, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L408)

```text
// Empty depth-only pixel shader for writing to depth buffer via ROV when no
```

## Source note 98, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L409)

```text
// Xenos pixel shader provided.
```

## Source note 99, line 410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L410)

```text
// Also bound to RTV draws that write nothing so they stay rasterized for
```

## Source note 100, line 411

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L411)

```text
// occlusion queries.
```

## Source note 101, line 413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L413)

```text
// Depth-only pixel shaders that count coverage into the ZPD Total counter,
```

## Source note 102, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L414)

```text
// for hybrid occlusion query draws without a guest pixel shader.
```

## Source note 103, line 430

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L430)

```text
// Twin of a guest shader for the SPIR-V translator, by ucode hash.
```

## Source note 104, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L432)

```text
// The SPIR-V translation (draw thread), or nullptr.
```

## Source note 105, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L434)

```text
// Its converted and signed DXIL, or nullptr (failures are cached). Any thread.
```

## Source note 106, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L441)

```text
// A guest domain shader's SPIR-V linked with the host tessellation vertex and
```

## Source note 107, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L442)

```text
// hull shaders its modification selects, so spirv_to_dxil reconciles the
```

## Source note 108, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L443)

```text
// stage signatures; nullptr on failure (cached). Any thread.
```

## Source note 109, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L446)

```text
// Converts the pixel shaders below; false if any can't be made.
```

## Source note 110, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L448)

```text
// The DXIL pixel shader for a DXIL pipeline without a guest one, or nullptr
```

## Source note 111, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L449)

```text
// for none: as the DXBC helper pixel shaders, from the SPIR-V translator.
```

## Source note 112, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L452)

```text
// Writes a new DXIL pipeline and its guest shaders to the storage files.
```

## Source note 113, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L455)

```text
// Queues a stored DXIL pipeline for creation; false if it can't be made.
```

## Source note 114, line 466

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L466)

```text
// Host render targets: the empty pixel shader that keeps draws writing
```

## Source note 115, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L467)

```text
// nothing rasterized, and float24 depth conversion without a guest shader.
```

## Source note 116, line 474

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L474)

```text
// ROV: the EDRAM depth / stencil (or VIZ survey) pixel shaders by guest
```

## Source note 117, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L475)

```text
// xenos::MsaaSamples, which a DXIL pipeline without a guest pixel shader
```

## Source note 118, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L476)

```text
// carries in its pixel_shader_modification.
```

## Source note 119, line 484

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L484)

```text
// nullptr if creation has failed.
```

## Source note 120, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L491)

```text
// Queued for asynchronous creation, not created or failed yet.
```

## Source note 121, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L493)

```text
// Taken by whoever creates a queued pipeline: a creation thread, or the
```

## Source note 122, line 494

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L494)

```text
// command processor awaiting this one pipeline.
```

## Source note 123, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L504)

```text
// All previously generated pipelines identified by hash and the description.
```

## Source note 124, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L507)

```text
// Previously used pipeline. This matches our current state settings and
```

## Source note 125, line 508

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L508)

```text
// allows us to quickly(ish) reuse the pipeline if no registers have been
```

## Source note 126, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L509)

```text
// changed.
```

## Source note 127, line 512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L512)

```text
// Currently open shader storage path.
```

## Source note 128, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L516)

```text
// Shader storage output stream, for preload in the next emulator runs.
```

## Source note 129, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L518)

```text
// For only writing shaders to the currently open storage once, incremented
```

## Source note 130, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L519)

```text
// when switching the storage.
```

## Source note 131, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L523)

```text
// Pipeline storage output stream, for preload in the next emulator runs.
```

## Source note 132, line 527

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L527)

```text
// Thread for asynchronous writing to the storage streams.
```

## Source note 133, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L531)

```text
// Storage thread input is protected with storage_write_request_lock_, and the
```

## Source note 134, line 532

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L532)

```text
// thread is notified about its change via storage_write_request_cond_.
```

## Source note 135, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L540)

```text
// Pipeline creation threads.
```

## Source note 136, line 545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L545)

```text
// Protected with creation_request_lock_, notify_one creation_request_cond_
```

## Source note 137, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L546)

```text
// when set.
```

## Source note 138, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L549)

```text
// Number of threads that are currently creating a pipeline - incremented when
```

## Source note 139, line 550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L550)

```text
// a pipeline is dequeued (the completion event can't be triggered before this
```

## Source note 140, line 551

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L551)

```text
// is zero). Protected with creation_request_lock_.
```

## Source note 141, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L553)

```text
// Manual-reset event set when the last queued pipeline is created and there
```

## Source note 142, line 554

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L554)

```text
// are no more pipelines to create. This is triggered by the thread creating
```

## Source note 143, line 555

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L555)

```text
// the last pipeline.
```

## Source note 144, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L557)

```text
// Whether setting the event on completion is queued. Protected with
```

## Source note 145, line 558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L558)

```text
// creation_request_lock_, notify_one creation_request_cond_ when set.
```

## Source note 146, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L560)

```text
// Creation threads with this index or above need to be shut down as soon as
```

## Source note 147, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L561)

```text
// possible. Protected with creation_request_lock_, notify_all
```

## Source note 148, line 562

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L562)

```text
// creation_request_cond_ when set.
```

## Source note 149, line 567

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/d3d12/pipeline_cache.h#L567)

```text
// namespace rex::graphics::d3d12
```
