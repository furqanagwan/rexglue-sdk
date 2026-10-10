# Shader translation: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/266).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/pipeline/shader/dxbc_translator.cpp:88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator.cpp#L88)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Handle in a nicer way (is_depth_only_pixel_shader_ is a
  // leftover from when a Shader object wasn't used during translation).
```

## Note 2: src/graphics/pipeline/shader/dxbc_translator.cpp:583

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator.cpp#L583)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support line and non-adaptive quad patches.
```

## Note 3: src/graphics/pipeline/shader/dxbc_translator.cpp:1228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator.cpp#L1228)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Avoid copy?
```

## Note 4: src/graphics/pipeline/shader/dxbc_translator.cpp:2767

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator.cpp#L2767)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support line patches.
```

## Note 5: src/graphics/pipeline/shader/dxbc_translator.cpp:3129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator.cpp#L3129)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support line patches.
```

## Note 6: src/graphics/pipeline/shader/interpreter.cpp:948

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/interpreter.cpp#L948)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the correct handling of the invalid swizzle 6.
```

## Note 7: src/graphics/pipeline/shader/interpreter.cpp:957

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/interpreter.cpp#L957)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Bit scan loops over components cause a link-time
  // optimization internal error in Visual Studio 2019, mainly in the format
  // unpacking. Using loops with up to 4 iterations here instead.
```

## Note 8: src/graphics/pipeline/shader/interpreter.cpp:976

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/interpreter.cpp#L976)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the default values for unused components.
```

## Note 9: src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp:182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L182)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Point parameters from the system uniform buffer.
```

## Note 10: src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp:388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L388)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): For points, handle ps_ucp_mode (transform the host clip
  // space to the guest one, calculate the distances to the user clip planes,
  // cull using the distance from the center for modes 0, 1 and 2, cull and clip
  // per-vertex for modes 2 and 3) - except for the vertex kill flag.
```

## Note 11: src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp:611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L611)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Handle ps_ucp_mode properly, clip expanded points if
        // needed.
```

## Note 12: src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp:876

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_builtin_geometry_shader.cpp#L876)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the correct decomposition of quads into triangles
      // on the real hardware.
```

## Note 13: src/graphics/pipeline/shader/spirv_translator.cpp:127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L127)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Handle in a nicer way (is_depth_only_fragment_shader_ is a
  // leftover from when a Shader object wasn't used during translation).
```

## Note 14: src/graphics/pipeline/shader/spirv_translator.cpp:313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L313)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Logger.
```

## Note 15: src/graphics/pipeline/shader/spirv_translator.cpp:719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L719)

Disposition: retired reminder. Metal mesh shaders are outside the D3D12-only destination.

```text
// TODO(has207): Replace this 3x-VS hack with a Metal mesh shader once
    // Xenia has a mesh-shader authoring path. SPIRV-Cross supports MSL mesh
    // shaders (ExecutionModelMeshEXT) but not geometry shaders, so rect/point
    // expansion could be expressed cleanly as SPIR-V mesh shaders and
    // translated the same way the rest of the pipeline is. Same applies to
    // kPointListAsTriangleStrip.
```

## Note 16: src/graphics/pipeline/shader/spirv_translator.cpp:1055

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L1055)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Avoid copy?
```

## Note 17: src/graphics/pipeline/shader/spirv_translator.cpp:2127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L2127)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Bounds checking.
```

## Note 18: src/graphics/pipeline/shader/spirv_translator.cpp:2158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L2158)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Close line loop primitive.
        // Load the unswapped index as uint for swapping, or for indirect
        // loading if needed.
```

## Note 19: src/graphics/pipeline/shader/spirv_translator.cpp:2178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L2178)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Bounds checking.
```

## Note 20: src/graphics/pipeline/shader/spirv_translator.cpp:2742

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L2742)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): For points, handle ps_ucp_mode (take the guest clip space
    // coordinates instead of the host ones, calculate the distances to the user
    // clip planes, cull using the distance from the center for modes 0, 1 and
    // 2, cull and clip per-vertex for modes 2 and 3) in clip and cull
    // distances.
```

## Note 21: src/graphics/pipeline/shader/spirv_translator.cpp:3020

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L3020)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): With sample shading (for depth format conversion) only
  // for the bottom-right sample (unlike in Direct3D, the sample mask input
  // doesn't include covered samples of the primitive that correspond to other
  // invocations, so use the sample that's the most friendly to the half-pixel
  // offset).
```

## Note 22: src/graphics/pipeline/shader/spirv_translator.cpp:3054

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L3054)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Promoted to SPIR-V 1.6 - don't add the extension there.
```

## Note 23: src/graphics/pipeline/shader/spirv_translator.cpp:3141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L3141)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Use GroupNonUniformQuad operations where supported.
      // If none of the pixels in the quad passed the depth / stencil test, the
      // value of (any samples covered ? 1.0f : 0.0f) for the current pixel will
      // be 0.0f, and since it will be 0.0f in other pixels too, the derivatives
      // will be zero as well.
```

## Note 24: src/graphics/pipeline/shader/spirv_translator.cpp:3364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator.cpp#L3364)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): When SPIR-V 1.6 is used in Xenia, see if OpFNegate can be
    // used there, should be cheaper because it may be implemented as a hardware
    // instruction modifier, though it respects the rule for subnormal numbers -
    // see the actual hardware instructions in both OpBitwiseXor and OpFNegate
    // cases.
```

## Note 25: src/graphics/pipeline/shader/translator.cpp:709

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/translator.cpp#L709)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Remove when the old SPIR-V shader translator is deleted.
```

## Note 26: src/graphics/pipeline/shader/translator.cpp:763

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/translator.cpp#L763)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): location information.
```

## Note 27: src/graphics/pipeline/shader/translator.cpp:834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/translator.cpp#L834)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): return if (DoesControlFlowOpcodeEndShader(cf.opcode()))?
```

## Note 28: src/graphics/pipeline/shader/translator.cpp:1043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/translator.cpp#L1043)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the correct handling of the invalid swizzle 6.
```

## Note 29: src/graphics/pipeline/shader/translator.cpp:1219

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/translator.cpp#L1219)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Not caring about mag/min filters currently for
      // simplicity. It's very unlikely that this instruction is ever seriously
      // used to retrieve weights of zero though.
```

## Note 30: src/graphics/pipeline/shader/translator.cpp:1228

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/translator.cpp#L1228)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Is the depth lerp factor always 0 for cube maps?
```

## Note 31: src/graphics/shaders/apply_gamma_pwl.xesli:78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/shaders/apply_gamma_pwl.xesli#L78)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): If this is ever used for gamma other than 128 entries for a
  // 10bpc front buffer, handle the increment from DC_LUTA/B_CONTROL. Currently
  // assuming it's 2^3 = 8, or 1024 / 128.
```

## Note 32: src/graphics/shaders/pixel_formats.xesli:251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/shaders/pixel_formats.xesli#L251)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate 8_8_8_8_A.
```

## Note 33: src/graphics/shaders/pixel_formats.xesli:813

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/shaders/pixel_formats.xesli#L813)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate this better, 4D53085B is the only known game
  // that uses it (for lighting in certain places - one of easy to notice usages
  // is the T-shaped (or somewhat H-shaped) metal beams in the beginning of the
  // first mission), however the contents don't say anything about the channel
  // order.
```

## Note 34: src/graphics/shaders/pixel_formats.xesli:840

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/shaders/pixel_formats.xesli#L840)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate this better, 4D53085B is the only known game
  // that uses it (for lighting in certain places - one of easy to notice usages
  // is the T-shaped (or somewhat H-shaped) metal beams in the beginning of the
  // first mission), however the contents don't say anything about the channel
  // order.
```

## Note 35: src/graphics/shaders/resolve_full_8bpp.xesli:57

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/shaders/resolve_full_8bpp.xesli#L57)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate formats 8_A and 8_B.
```

## Note 36: include/rex/graphics/pipeline/shader/dxbc_translator.h:239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/shader/dxbc_translator.h#L239)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate replacement with an alpha-to-mask flag,
    // checking `(flags & (alpha test | alpha to mask)) == (always | disabled)`,
    // taking into account the potential relation with occlusion queries (but
    // should be safe at least temporarily).
```

## Note 37: include/rex/graphics/pipeline/shader/shader.h:997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/shader/shader.h#L997)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate what happens to memexport when the pixel
    // fails the depth/stencil test, but in Direct3D 11 UAV writes disable early
    // depth/stencil.
```

## Note 38: include/rex/graphics/pipeline/shader/spirv_translator.h:64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/shader/spirv_translator.h#L64)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Unorm24 (rounding) output mode.
```

## Note 39: include/rex/graphics/pipeline/shader/spirv_translator.h:241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/pipeline/shader/spirv_translator.h#L241)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate replacement with an alpha-to-mask flag,
    // checking `(flags & (alpha test | alpha to mask)) == (always | disabled)`,
    // taking into account the potential relation with occlusion queries (but
    // should be safe at least temporarily).
```
