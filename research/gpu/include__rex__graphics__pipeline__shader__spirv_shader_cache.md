# Spirv shader cache: graphics source notes

This record preserves technical and API notes moved from `include/rex/graphics/pipeline/shader/spirv_shader_cache.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L25)

```text
// Modifications cross this interface as raw uint64_t (not
```

## Source note 2, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L26)

```text
// SpirvShaderTranslator::Modification) to keep glslang, pulled in by
```

## Source note 3, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L27)

```text
// spirv_shader_translator.h, out of backend headers that include this one.
```

## Source note 4, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L36)

```text
// Built-in geometry shader that expands a guest primitive type the host can't
```

## Source note 5, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L37)

```text
// draw directly. Values are part of the pipeline storage layout, so both
```

## Source note 6, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L38)

```text
// backends share this exact enum.
```

## Source note 7, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L44)

```text
// Lines expanded to 1 guest pixel wide for resolution-scaled draws.
```

## Source note 8, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L48)

```text
// Guest shader logic shared by the D3D12 (spirv_to_dxil) and Vulkan backends:
```

## Source note 9, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L49)

```text
// the SpirvShaderTranslator (built per backend via the Host seam), the
```

## Source note 10, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L50)

```text
// SpirvShaderTranslator::Modification derivation, ucode->SPIR-V translation,
```

## Source note 11, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L51)

```text
// and the built-in geometry shader key. The shader object cache stays
```

## Source note 12, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L52)

```text
// per-backend (their SpirvShader subclasses differ). This operates on
```

## Source note 13, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L53)

```text
// shaders/translations passed in. The host-specific tail (DXIL/VkPipeline
```

## Source note 14, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L54)

```text
// bytecode, pipeline state and storage) stays in each backend behind the Host
```

## Source note 15, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L55)

```text
// seam below.
```

## Source note 16, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L58)

```text
// Implemented by each backend to supply the host-specific pieces the shared
```

## Source note 17, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L59)

```text
// logic needs.
```

## Source note 18, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L64)

```text
// Builds a translator configured for this backend (Vulkan derives Features
```

## Source note 19, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L65)

```text
// from the device, D3D12 enables all and overrides a few). Called once for
```

## Source note 20, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L66)

```text
// the cache's main-thread translator and once per worker translator.
```

## Source note 21, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L69)

```text
// Depth float24 policy, which lives on the backend's RenderTargetCache
```

## Source note 22, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L70)

```text
// subclass (not the shared base, so it can't be read through the base ref).
```

## Source note 23, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L79)

```text
// Creates the main-thread translator. Call once after construction, on the
```

## Source note 24, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L80)

```text
// thread that will own draw-time translation. Returns false if the translator
```

## Source note 25, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L81)

```text
// could not be created.
```

## Source note 26, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L85)

```text
// The shared translator owned by this cache, for main-thread translation.
```

## Source note 27, line 87

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L87)

```text
// A fresh translator for a worker thread (the translator is not thread safe).
```

## Source note 28, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L90)

```text
// SPIR-V modification derivation (returns SpirvShaderTranslator::Modification
```

## Source note 29, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L91)

```text
// values as raw uint64_t to keep glslang out of backend headers). These read
```

## Source note 30, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L92)

```text
// the register file and render target cache policy. ps_param_gen_used only
```

## Source note 31, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L93)

```text
// affects kPointListAsTriangleStrip host vertex shaders (D3D12 passes false
```

## Source note 32, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L94)

```text
// since it expands points with the built-in geometry shader instead).
```

## Source note 33, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L104)

```text
// Ensures a Translation for the modification on the given (backend-owned)
```

## Source note 34, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L105)

```text
// shader exists WITHOUT translating to SPIR-V. Analyzes the ucode if needed.
```

## Source note 35, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L106)

```text
// Main/draw thread only. Returns the (possibly untranslated) Translation.
```

## Source note 36, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L108)

```text
// Translates a Translation to SPIR-V on the given translator (the main
```

## Source note 37, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L109)

```text
// thread's, or a worker's). use_try_claim coordinates concurrent translation
```

## Source note 38, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L110)

```text
// of the same Translation. Returns the valid Translation or nullptr. The
```

## Source note 39, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L111)

```text
// backend converts the SPIR-V to host bytecode afterward. Any thread.
```

## Source note 40, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L114)

```text
// Main-thread convenience: EnsureTranslation + TranslateSpirv on the shared
```

## Source note 41, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L115)

```text
// translator.
```

## Source note 42, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L118)

```text
// Built-in primitive-expansion geometry shader key (point/rect/quad). Derived
```

## Source note 43, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L119)

```text
// from SPIR-V modifications. Each backend builds the SPIR-V and converts it
```

## Source note 44, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L120)

```text
// to its own bytecode.
```

## Source note 45, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L126)

```text
// Raw enabled count (0-6). Vulkan keys on this too but always builds 6.
```

## Source note 46, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L142)

```text
// Returns false (no geometry shader) for kNone and for the *AsTriangleStrip
```

## Source note 47, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L143)

```text
// fallback host vertex shader types. Takes SPIR-V modification values.
```

## Source note 48, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L147)

```text
// Each backend selects the host tessellation vertex/hull shaders itself. That
```

## Source note 49, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L148)

```text
// selection references the generated vulkan_spirv blobs, whose generation
```

## Source note 50, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L149)

```text
// links xenia-gpu, and this base-library component cannot depend on xenia-gpu
```

## Source note 51, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/graphics/pipeline/shader/spirv_shader_cache.h#L150)

```text
// without a dependency cycle.
```
