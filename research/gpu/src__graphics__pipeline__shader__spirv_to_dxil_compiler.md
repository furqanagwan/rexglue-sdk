# Spirv to dxil compiler: graphics source notes

This record preserves technical and API notes moved from `src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L23)

```text
// Windows, wrl/client.h and the DXC validator interfaces (IDxcValidator,
```

## Source note 2, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L24)

```text
// IDxcVersionInfo) used to sign the converted DXIL.
```

## Source note 3, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L35)

```text
// Mesa C ABI. The header carries its own extern "C" guards.
```

## Source note 4, line 71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L71)

```text
// The guest sets 0..3 map to register spaces 0..3 in the Vulkan environment.
```

## Source note 5, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L72)

```text
// Park Dozen's runtime data and push constant CBVs in a high space so they
```

## Source note 6, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L73)

```text
// never collide. SpirvShaderTranslator emits no push constants and derives
```

## Source note 7, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L74)

```text
// vertex indices from its own constants, so these should stay unused.
```

## Source note 8, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L82)

```text
// No yz_flip. Unlike Dozen (which feeds Vulkan-convention NDC and flips
```

## Source note 9, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L83)

```text
// here), the command processor computes the host clip transform with D3D
```

## Source note 10, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L84)

```text
// conventions (origin_bottom_left) baked into ndc_scale/ndc_offset, so
```

## Source note 11, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L85)

```text
// gl_Position is already in D3D clip space and SV_Position is a direct copy.
```

## Source note 12, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L86)

```text
// Flipping would double-invert.
```

## Source note 13, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L88)

```text
// Strict IEEE float math, matching the DXC -Gis the HLSL path used.
```

## Source note 14, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L92)

```text
// SpirvShaderTranslator::kDescriptorSetCount.
```

## Source note 15, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L94)

```text
// Independently translated stages (the single-stage Translate path) must keep
```

## Source note 16, line 95

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L95)

```text
// their declared varyings so the packed VS-output and PS-input signatures
```

## Source note 17, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L96)

```text
// line up. Linked stages let them be pruned.
```

## Source note 18, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L98)

```text
// Producer clip count, for splitting clip/cull inputs of an isolated stage.
```

## Source note 19, line 103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L103)

```text
// The SPIR-V to DXIL conversion itself is thread safe: Mesa's glsl_type cache
```

## Source note 20, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L104)

```text
// (its only shared global) locks internally, so conversions run in parallel
```

## Source note 21, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L105)

```text
// across the main thread and the pipeline creation threads. Only the DXIL.dll
```

## Source note 22, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L106)

```text
// validator is a shared, non-thread-safe instance, so its creation and the
```

## Source note 23, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L107)

```text
// signing pass are serialized by this mutex.
```

## Source note 24, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L110)

```text
// DXC validator from DXIL.dll, created lazily and reused. Never destroyed: it
```

## Source note 25, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L111)

```text
// keeps DXIL.dll loaded for the process lifetime. Guarded by
```

## Source note 26, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L112)

```text
// dxil_validator_mutex. validator_version is what DXIL.dll stamps. It is passed
```

## Source note 27, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L113)

```text
// to spirv_to_dxil so the container header matches the signer.
```

## Source note 28, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L117)

```text
// Minimal IDxcBlob over a caller-owned buffer so the validator can sign in
```

## Source note 29, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L118)

```text
// place without copying. Not reference counted: it lives on the stack for the
```

## Source note 30, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L119)

```text
// Validate call, which does not retain it.
```

## Source note 31, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L134)

```text
// Returns DXIL.dll's DxcCreateInstance, or null. The provider preloads DXIL.dll
```

## Source note 32, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L135)

```text
// by full path during setup, so the plain-name load here resolves to that
```

## Source note 33, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L136)

```text
// module. The D3D12-directory path is a fallback if it has not been loaded yet.
```

## Source note 34, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L138)

```text
// The pinned dxil.dll deployed beside the Agility SDK first, so a different
```

## Source note 35, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L139)

```text
// one on the search path can't stand in for it (RG-GDK-032).
```

## Source note 36, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L152)

```text
// Maps the DXIL.dll validator version to the enum spirv_to_dxil stamps into the
```

## Source note 37, line 153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L153)

```text
// container, mirroring Mesa's dxil_validator. The validator rejects a container
```

## Source note 38, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L154)

```text
// tagged with a version it does not implement.
```

## Source note 39, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L173)

```text
// Lazily creates the DXIL.dll validator. dxil_validator_mutex must be held.
```

## Source note 40, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L196)

```text
// Briefly locks to ensure the validator exists and read its version (the only
```

## Source note 41, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L197)

```text
// validator access the conversion needs). Returns false if it cannot be
```

## Source note 42, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L198)

```text
// created. The conversion that follows runs unlocked.
```

## Source note 43, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L208)

```text
// Signs a DXIL container in place. spirv_to_dxil emits UNSIGNED DXIL (it only
```

## Source note 44, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L209)

```text
// records the validator version in the header). D3D12 rejects unsigned DXIL
```

## Source note 45, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L210)

```text
// with E_INVALIDARG, so the DXIL.dll validator must rewrite the container hash,
```

## Source note 46, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L211)

```text
// the same way DXC signs its own output.
```

## Source note 47, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L213)

```text
// The shared validator is not thread safe.
```

## Source note 48, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L253)

```text
// A single stage compiled on its own: keep unused varyings so its signature
```

## Source note 49, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L254)

```text
// matches the separately compiled neighbor stage.
```

## Source note 50, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L256)

```text
/*keep_io_vars=*/
```

## Source note 51, line 299

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L299)

```text
// Linking reconciles the inter-stage signatures, so dead varyings may be
```

## Source note 52, line 300

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L300)

```text
// pruned, and the clip/cull split comes from the linked producer.
```

## Source note 53, line 301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L301)

```text
/*keep_io_vars=*/
```

## Source note 54, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L302)

```text
/*input_clip_size=*/
```

## Source note 55, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/graphics/pipeline/shader/spirv_to_dxil_compiler.cpp#L319)

```text
// Copy out and free every Mesa object before signing.
```
