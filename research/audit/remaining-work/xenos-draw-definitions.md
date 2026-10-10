# Xenos draw definitions: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/265).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/graphics_system.cpp:190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/graphics_system.cpp#L190)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: set_can_debugger_suspend not yet ported
  // vsync_worker_thread_->set_can_debugger_suspend(true);
```

## Note 2: src/graphics/graphics_system.cpp:224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/graphics_system.cpp#L224)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Somehow gain exclusive ownership of the Provider (may be
  // used by the command processor, the presenter, and possibly anything else,
  // it's considered free-threaded, except for lifetime management which will be
  // involved in this case) and reset it so a new host GPU API device is
  // created. Then ask the command processor to reset itself in its thread, and
  // ask the UI thread to reset the Presenter (the UI thread manages its
  // lifetime - but if there's no WindowedAppContext, either don't reset it as
  // in this case there's no user who needs uninterrupted gameplay, or somehow
  // protect it with a mutex so any thread can be considered a UI thread and
  // reset).
```

## Note 3: src/graphics/graphics_system.cpp:341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/graphics_system.cpp#L341)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Enable profiling once ported
  // SCOPE_profile_cpu_f("gpu");
```

## Note 4: src/graphics/graphics_system.cpp:349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/graphics_system.cpp#L349)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): we shouldn't need to do the dispatch here, but there's
  //     something wrong and the CP will block waiting for code that
  //     needs to be run in the interrupt.
```

## Note 5: src/graphics/primitive_processor.cpp:72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L72)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): More investigation of the cache threshold as cache lookups
// and insertions require global critical region locking, and insertions also
// require protecting pages. At 1024, the cache only made the performance worse
// (415607D4, 16-bit primitive reset index replacement).
// DEFINE_int32(
//     primitive_processor_cache_min_indices, 4096,
//     "Smallest number of guest indices to store in the cache to try reusing "
//     "later in the same frame if processing (such as primitive type conversion "
//     "or reset index replacement) is performed.\n"
//     "Setting this to a very high value may result in excessive CPU processing, "
//     "while a very low value may result in excessive locking and lookups.\n"
//     "Negative values disable caching.",
//     "GPU");
```

## Note 6: src/graphics/primitive_processor.cpp:224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L224)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): SIMD for faster initialization?
```

## Note 7: src/graphics/primitive_processor.cpp:227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L227)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the correct order.
                  // v0, v1, v2.
```

## Note 8: src/graphics/primitive_processor.cpp:301

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L301)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Conversion of patch strips / fans if found.
```

## Note 9: src/graphics/primitive_processor.cpp:355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L355)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support line patches.
```

## Note 10: src/graphics/primitive_processor.cpp:451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L451)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support immediate-indexed vertices.
```

## Note 11: src/graphics/primitive_processor.cpp:545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L545)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support immediate-indexed vertices.
```

## Note 12: src/graphics/primitive_processor.cpp:669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L669)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): 16-bit > 32-bit primitive type conversion for
          // Metal, where primitive reset is always enabled, if UINT16_MAX is
          // used as a real vertex index.
```

## Note 13: src/graphics/primitive_processor.cpp:913

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L913)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Shared memory request cache.
```

## Note 14: src/graphics/primitive_processor.cpp:986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L986)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Revisit this - maybe the early-out will be free if this
  // function is bandwidth-bound.
```

## Note 15: src/graphics/primitive_processor.cpp:1234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/primitive_processor.cpp#L1234)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): SIMD quad conversion maybe - 2 vectors to 3 vectors (though
// multiple quads are rarely drawn anyway).
```

## Note 16: src/graphics/util/draw.cpp:251

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/util/draw.cpp#L251)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Overestimate or more properly round the viewport scissor
  // boundaries if this flooring causes gaps on the bottom / right side in real
  // games if any are found using fractional viewport coordinates. Viewport
  // scissoring is not an inherent result of the viewport scale / offset, these
  // are used merely for transformation of coordinates; rather, it's done by
  // intersecting the viewport and scissor rectangles in the guest driver and
  // writing the common portion to PA_SC_WINDOW_SCISSOR, so how the scissor is
  // computed for a fractional viewport is entirely up to the guest.
  //
  //   Even though Xbox 360 games are designed for Direct3D, with 0...W range of
  //   Z in clip space, the GPU also allows -W...W. Since Xenia is not targeting
  //   OpenGL (where it would be toggled via glClipControl - or, on ES, it would
  //   always be -W...W), this function always remaps it to 0...W, though
  //   numerically not precisely (0 is moved to 0.5, locking the exponent near
  //   what was the truly floating-point 0 originally). It is the guest
  //   viewport's responsibility (haven't checked, but it's logical) to remap
  //   from -1...1 in the NDC to glDepthRange within the 0...1 range. Also -Z
  //   pointing forward in OpenGL doesn't matter here (the -W...W clip space is
  //   symmetric).
  //
  // - Clipping is disabled:
  //
  //   The most common case of drawing without clipping in games is screen-space
  //   draws, most prominently clears, directly in render target coordinates.
  //
  //   In this particular case (though all the general case arithmetic still
  //   applies), the vertex shader returns a position in pixels, pre-divided by
  //   W (though this doesn't matter if W is 1).
  //
  //   Because clipping is disabled, this huge polygon with, for example,
  //   a (1280, 720, 0, 1) vertex, is not clipped to (-w, -w) ... (w, w), so the
  //   vertex becomes (1280, 720) in the NDC as well (even though in regular 3D
  //   draws with clipping, disregarding the guard band for simplicity, it can't
  //   be bigger than (1, 1) after clipping and the division by W).
  //
  //   For these draws, the viewport is also usually disabled (though, again, it
  //   doesn't have to be - an enabled viewport would likely still work as
  //   usual) by disabling PA_CL_VTE_CNTL::VPORT_X/Y/Z_SCALE/OFFSET_ENA - which
  //   equals to having a viewport scale of (1, 1, 1) and offset of (0, 0, 0).
  //   This results in the NDC being treated directly as pixel coordinates.
  //   Normally, with clipping, this would make only a tiny 1x1 area in the
  //   corner of the render target being possible to cover (and 3 unreachable
  //   pixels outside of the render target). The window offset is then applied,
  //   if needed, as well as the half-pixel offset.
  //
  //   It's also possible (though not verified) that without clipping, Z (as a
  //   result of, for instance, polygon offset, or explicit calculations in the
  //   vertex shader) may end up outside the viewport Z range. Direct3D 10
  //   requires clamping to the viewport Z bounds in all cases in the
  //   output-merger according to the Direct3D 11.3 functional specification. A
  //   different behavior is likely on the Xbox 360, however, because while
  //   Direct3D 10-compatible AMD GPUs such as the R600 have
  //   PA_SC_VPORT_ZMIN/ZMAX registers, the Adreno 200 doesn't seem to have any
  //   equivalents, neither in PA nor in RB. This probably also applies to
  //   shader depth output - possibly doesn't need to be clamped as well.
  //
  //   On the PC, we need to emulate disabled clipping by using a viewport at
  //   least as large as the scissor region within the render target, as well as
  //   the full viewport depth range (plus changing Z clipping to Z clamping on
  //   the host if possible), and rescale from the guest clip space to the host
  //   "no clip" clip space, as well as apply the viewport, the window offset,
  //   and the half-pixel offset, in the vertex shader. Ideally, the host
  //   viewport should have a power of 2 size - so scaling doesn't affect
  //   precision, and is merely an exponent bias.
  //
  // NDC XY point towards +XY on the render target - the viewport scale sign
  // handles the remapping from Direct3D 9 -Y towards +U to a generic
  // transformation from the NDC to pixel coordinates.
  //
  // TODO(Triang3l): Investigate the need for clamping of oDepth to 0...1 for
  // D24FS8 as well.
```

## Note 17: src/graphics/util/draw.cpp:320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/util/draw.cpp#L320)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate the need for clamping of oDepth to 0...1 for
  // D24FS8 as well.
```

## Note 18: src/graphics/util/draw.cpp:678

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/util/draw.cpp#L678)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Remove the unresearched format logging when it's known
    // how exactly these formats need to be handled (most importantly what
    // components need to be stored and in which order).
```

## Note 19: src/graphics/util/draw.cpp:815

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/util/draw.cpp#L815)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// D3D9 HACK: Vertices to use are always in vf0, and are written by the CPU.
```

## Note 20: src/graphics/util/draw_extent_estimator.cpp:92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/util/draw_extent_estimator.cpp#L92)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support immediate indices.
```

## Note 21: include/rex/graphics/format/dxbc.h:2094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/format/dxbc.h#L2094)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify if the instruction counts should be incremented
    // this way (haven't been able to obtain this from FXC because it generates
    // separate emit_stream and cut_stream, at least for Shader Model 5.1).
```

## Note 22: include/rex/graphics/format/ucode.h:579

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/format/ucode.h#L579)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find if gradients are unnormalized for cube maps if
  // coordinates are unnormalized. Since texldd doesn't perform any
  // transformation for gradients (unlike for the coordinates themselves),
  // gradients are probably in cube space, which is -MA...MA, and LOD
  // calculation involves gradients in this space, so probably gradients
  // shouldn't be unnormalized.
  //
  // Adreno has only been supporting seamless cube map sampling since 3xx, so
  // the Xenos likely doesn't support seamless sampling:
  // https://developer.qualcomm.com/qfile/28557/80-nu141-1_b_adreno_opengl_es_developer_guide.pdf
  //
  // Offsets are likely applied at the LOD at which the texture is sampled (not
  // sure if to the higher-quality or to both - though "right before sampling"
  // probably means to both - in Direct3D 10, it's recommended to only use
  // offsets at integer mip levels, otherwise "you may get results that do not
  // translate well to hardware".
```

## Note 23: include/rex/graphics/format/ucode.h:635

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/format/ucode.h#L635)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify whether it's coarse or fine (on Adreno 200, for
  // instance). This is using the texture unit, where the LOD is computed for
  // the whole quad (according to the Direct3D 11.3 specification), so likely
  // coarse; ddx / ddy from the Shader Model 4 era is also compiled by FXC to
  // deriv_rtx/rty_coarse when targeting Shader Model 5, and on TeraScale,
  // coarse / fine selection only appeared on Direct3D 11 GPUs.
```

## Note 24: include/rex/graphics/primitive_processor.h:133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/primitive_processor.h#L133)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): If important, split into the index count and the actual
    // index buffer size, using zeros for out-of-bounds indices.
```

## Note 25: include/rex/graphics/primitive_processor.h:450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/primitive_processor.h#L450)

Disposition: retired reminder. Metal is a retired host backend.

```text
// TODO(Triang3l): 16-bit > 32-bit primitive type conversion for Metal, where
  // primitive reset is always enabled, if UINT16_MAX is used as a real vertex
  // index.
```

## Note 26: include/rex/graphics/primitive_processor.h:550

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/primitive_processor.h#L550)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the correct order.
      // v0, v1, v2.
```

## Note 27: include/rex/graphics/registers.h:221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/registers.h#L221)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Research the order, as well as the sampling location, of
    // PsParamGen.zw, the behavior (whether they're extrapolated) when the
    // center of the pixel is not covered, on the real hardware.
    // * Sign bit of X - is front face (according to the disassembly of vFace
    //   and gl_FrontFacing usage), non-negative for front face, negative for
    //   back face (used with `rcpc` in shaders to take signedness of 0 into
    //   account in `cndge`).
    // * Sign bit of Y - is the primitive type a point (according to the
    //   IPR2015-00325 sequencer specification), negative for a point,
    //   non-negative for other primitive types.
    // * Sign bit of Z - is the primitive type a line (according to the
    //   IPR2015-00325 sequencer specification), negative for a line,
    //   non-negative for other primitive types.
```

## Note 28: include/rex/graphics/registers.h:689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/registers.h#L689)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Redo these tests and possibly flip these vertically in
    // the comment and in the actual implementation. It appears that
    // gl_FragCoord.y is mirrored as opposed to the actual screen coordinates in
    // the rasterizer (see the SQ_CONTEXT_MISC::param_gen_pos comment here).
    // According to tests on an Adreno 200 device (LG Optimus L7), done by
    // drawing 0.5x0.5 rectangles in different corners of four pixels in a quad
    // to a multisampled GLSurfaceView, the coverage mask is the following for 4
    // samples:
    // 0.25)  [0.25, 0.5)  [0.5, 0.75)  [0.75, 1)   [1
    //  --        --           --          --       --
    // |  |      |  |         | #|        |##|     |##|
    // |  |      |# |         |# |        |# |     |##|
    //  --        --           --          --       --
    // (gl_FragCoord.y near 0 in the top, near 1 in the bottom here - D3D-like.)
    // For 2 samples, the top sample (closer to gl_FragCoord.y 0) is covered
    // when alpha is in [0.5, 1), the bottom sample is covered when the alpha is
    // [1. With these thresholds, however, in 5454082B, almost all distant trees
    // are transparent, this is asymmetric - fully transparent for a quarter of
    // the range (or even half of the range for 2x and almost the entire range
    // for 1x), but fully opaque only in one value.
    // Though, 2, 2, 2, 2 offset values are commonly used for undithered alpha
    // to coverage (in games such as 5454082B, and overall in AMD driver
    // implementations) - it appears that 2, 2, 2, 2 offsets are supposed to
    // make this symmetric.
    // Both 5454082B and RADV (which used AMDVLK as a reference) use 3, 1, 0, 2
    // offsets for dithered alpha to mask.
    // https://gitlab.freedesktop.org/nchery/mesa/commit/8a52e4cc4fad4f1c75acc0badd624778f9dfe202
    // It appears that the offsets lower the thresholds by (offset / 4 /
    // sample count). That's consistent with both 2, 2, 2, 2 making the test
    // symmetric and 0, 0, 0, 0 (forgetting to set the offset values) resulting
    // in what the official Adreno 200 driver for Android (which is pretty buggy
    // overall) produces.
    // According to Evergreen register reference:
    // - offset0 is for pixel (0, 0) in each quad.
    // - offset1 is for pixel (0, 1) in each quad.
    // - offset2 is for pixel (1, 0) in each quad.
    // - offset3 is for pixel (1, 1) in each quad.
```

## Note 29: include/rex/graphics/util/draw.h:82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/util/draw.h#L82)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate how kRectangleList should be treated - possibly
  // actually drawn as two polygons on the console, however, the current
  // geometry shader doesn't care about the winding order - allowing backface
  // culling for rectangles currently breaks 4D53082D.
```

## Note 30: include/rex/graphics/util/draw.h:558

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/util/draw.h#L558)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Check which 32-bit portion is in which register.
```

## Note 31: include/rex/graphics/xenos.h:63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L63)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify if this is also true for the Xenos.
```

## Note 32: include/rex/graphics/xenos.h:151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L151)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Is the alpha 0 or 1?
```

## Note 33: include/rex/graphics/xenos.h:156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L156)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Real hardware border color, and is the alpha 0 or 1?
```

## Note 34: include/rex/graphics/xenos.h:159

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L159)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Real hardware border color, and is the alpha 0 or 1?
```

## Note 35: include/rex/graphics/xenos.h:463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L463)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate how k_8_A and k_8_B work in resolves and
  // memexports, whether they store alpha/blue of the input or red.
```

## Note 36: include/rex/graphics/xenos.h:575

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L575)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate k_8_8_8_8_A.
```

## Note 37: include/rex/graphics/xenos.h:878

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L878)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify whether kDepthOnly means the pixel shader is ignored
  // completely even if it writes depth, exports to memory or kills pixels.
  // Hints suggesting that it should be completely ignored (which is desirable
  // on real hardware to avoid scheduling the pixel shader at all and waiting
  // for it especially since the Xbox 360 doesn't have early per-sample depth /
  // stencil, only early hi-Z / hi-stencil, and other registers possibly
  // toggling pixel shader execution are yet to be found):
  // - Most of depth pre-pass draws in 415607E6 use the kDepthOnly more with a
  //   `oC0 = tfetch2D(tf0, r0.xy) * r1` shader, some use `oC0 = r0` though.
  //   However, when alphatested surfaces are drawn, kColorDepth is explicitly
  //   used with the same shader performing the texture fetch.
  // - 5454082B has some kDepthOnly draws with alphatest enabled, but the shader
  //   is `oC0 = r0`, which makes no sense (alphatest based on an interpolant
  //   from the vertex shader) as no texture alpha cutout is involved.
  // - 5454082B also has kDepthOnly draws with pretty complex shaders clearly
  //   for use only in the color pass - even fetching and filtering a shadowmap.
  // For now, based on these, let's assume the pixel shader is never used with
  // kDepthOnly.
```

## Note 38: include/rex/graphics/xenos.h:1361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L1361)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify whether GL_QCOM_writeonly_rendering is actually
// memexport on the Adreno 2xx using GL_OES_get_program_binary - it's also
// interesting to see how alphatest interacts with it, whether it's still true
// fixed-function alphatest, as it's claimed to be supported as usual by the
// extension specification.
//
// Y of eA contains the offset in elements - this is what shaders are supposed
// to calculate from something like the vertex index. Again, it's specified as
// an integer in the low bits, not as a truly floating-point number. For this
// purpose, stream constants contain the value 2^23 - when a whole
// floating-point number smaller than 2^23 is added as floating-point to 2^23,
// its integer representation becomes the mantissa bits of a number with an
// exponent of 23. Via multiply-add, `offset * 1.0f + exp2f(23)` is written here
// by the shader, allowing for element offsets of up to 2^23 - 1.
//
// Z is a bit field with the information about the formatting of the data. It's
// also packed as a normalized floating-point number, but in a cleaner way than
// X because not as many bits are required - just like Y, it has an exponent of
// 23 (possibly to let shaders build these values manually using floating-point
// multiply-add like integer shift-or, and finally to add 2^23, though that's
// not a case easy to handle in emulation, unlike prebuilt stream constants).
//
// W contains the number of elements in the stream. It's also packed with the
// full 23 exponent just like Y and Z, there's no way to index more than 2^23
// elements using packing via addition to 2^23, so this field also doesn't need
// more bits than that.
//
// According to the sequencer specification from IPR2015-00325 (where memexport
// is called "pass thru export"):
// - Pass thru exports can occur anywhere in the shader program.
// - There can be any number of pass thru exports.
// - The address register is not kept across clause boundaries, so it must be
//   refreshed after any Serialize (or yield), allocate instruction or resource
//   change.
// - The write to eM# may be predicated if the export is not needed.
// - Exports are dropped if:
//   - The index is above the maximum.
//   - The index sign bit is 1.
//   - The exponent of the index is not 23.
// The requirement that eM4 must be written if any eM# other than eM0 is also
// written doesn't apply to the final Xenos, it's likely an outdated note in the
// specification considering that it's very preliminary.
//
// According to Microsoft's shader validator:
// - eA can be written only by `mad`.
// - A single eM# can be written by any number of instruction, including with
//   write masking.
// - eA must be written before eM#.
// - Any alloc instruction or a `serialize` terminates the current memory
//   export. This doesn't apply to `exec Yield=true`, however, and it's not
//   clear if that's an oversight or if that's not considered a yield that
//   terminates the export.
//
// From the emulation perspective, this means that:
// - Alloc instructions (`alloc export` mandatorily, other allocs optionally),
//   and optionally `serialize` instructions within `exec`, should be treated as
//   the locations where the currently open export should be flushed to the
//   memory. It should be taken into account that an export may be in looping
//   control flow, and in this case it must be performed at every iteration.
// - Whether each eM# was written to must be tracked at shader execution time,
//   as predication can disable the export of an element.
//
// TODO(Triang3l): Investigate how memory export interacts with pixel killing.
// Given that eM# writes disabled by predication don't cause an export, it's
// possible that killed invocations are treated as inactive (invalid in Xenos
// terms) overall, and thus new memory exports from them shouldn't be done, but
// that's not verified. However, given that on Direct3D 11+, OpenGL and Vulkan
// hosts, discarding disables subsequent storage resource writes, on the host,
// it would be natural to perform all outstanding memory exports before
// discarding if the kill condition passes.
//
// Memory exports can be performed to any ColorFormat, including 8bpp and 16bpp
// ones. Hosts, however, may have the memory bound as a 32bpp buffer (for
// instance, due to the minimum resource view size limitation on Direct3D 11).
// In this case, bytes and shorts aren't addressable directly. However, taking
// into account that memory accesses are coherent within one shader invocation
// on Direct3D 11+, OpenGL and Vulkan and thus are done in order relatively to
// each other, it should be possible to implement them by clearing the bits via
// an atomic AND, and writing the new value using an atomic OR. This will, of
// course, make the entire write operation non-atomic, and in case of a race
// between writes to the same location, the final result may not even be just a
// value from one of the invocations, but rather, it can be OR of the values
// from any invocations involved. However, on the Xenos, there doesn't seem to
// be any possibility of meaningfully accessing the same location from multiple
// invocations if any of them is writing, memory exports are out-of-order, so
// such an implementation shouldn't be causing issues in reality. Atomic
// compare-exchange, however, should not be used for this purpose, as it may
// result in an infinite loop if different invocations want to write different
// values to the same memory location.
//
// Examples of setup in titles (Z from MSB to LSB):
//
// 4D5307E6 particles (different VS invocation counts, like 1, 2, 4):
// There is a passthrough shader - useful for verification as it simply writes
// directly what it reads via vfetch of various formats. Another shader (with
// different c# numbers, but same formats) does complicated math to process the
// particles.
// c152:           Z = 010010110000|0|111|00|100110|00000|010, count = 35840
//   8in32, 32_32_32_32_FLOAT, float, RGBA - from 32_32_32_32_FLOAT vfetch
// c154, 162:      Z = 010010110000|0|111|00|100000|00000|001, count = 71680
//   8in16, 16_16_16_16_FLOAT, float, RGBA - from 16_16_16_16_FLOAT vfetch
// c156, 158, 160: Z = 010010110000|0|000|00|011010|00000|001, count = 71680
//   8in16, 16_16_16_16, unorm, RGBA - from 16_16_16_16 unorm vfetch
// c164:           Z = 010010110000|0|111|00|011111|00000|001, count = 143360
//   8in16, 16_16_FLOAT, float, RGBA - from 16_16_FLOAT vfetch
// c166:           Z = 010010110000|0|000|00|011001|00000|001, count = 143360
//   8in16, 16_16, unorm, RGBA - from 16_16 unorm vfetch
// c168:           Z = 010010110000|0|001|00|000111|00000|010, count = 143360
//   8in32, 2_10_10_10, snorm, RGBA - from 2_10_10_10 snorm vfetch
// c170, c172:     Z = 010010110000|1|000|00|000110|00000|010, count = 143360
//   8in32, 8_8_8_8, unorm, BGRA - from 8_8_8_8 unorm vfetch with .zyxw swizzle
//
// 4D5307E6 water simulation (2048 VS invocations):
// c130: Z = 010010110000|0|111|00|100110|00000|010, count = 16384
//   8in32, 32_32_32_32_FLOAT, float, RGBA
//   The shader has 5 memexports of this kind and 6 32_32_32_32_FLOAT vfetches.
//
// 4D5307E6 water tessellation factors (1 VS invocation per triangle patch):
// c130: Z = 010010110000|0|111|11|100100|11111|010, count = patch count * 3
//   8in32, 32_FLOAT, float, RGBA
//
// 41560817 texture memory copying (64 bytes per invocation, two eA, eight eM#):
// c0: Z = 010010110000|0|010|11|011010|00011|001
//   8in16, 16_16_16_16, uint, RGBA - from 16_16_16_16 uint vfetch
//   (16_16_16_16 is the largest color format without special values)
//
// 58410B86 hierarchical depth buffer occlusion culling with the result read on
// the CPU (15000 VS invocations in the main menu):
// c8: Z = 010010110000|0|010|00|000010|00000|000, count = invocation count
//   No endian swap, 8, uint, RGBA
```

## Note 39: include/rex/graphics/xenos.h:1423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/xenos.h#L1423)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate how memory export interacts with pixel killing.
// Given that eM# writes disabled by predication don't cause an export, it's
// possible that killed invocations are treated as inactive (invalid in Xenos
// terms) overall, and thus new memory exports from them shouldn't be done, but
// that's not verified. However, given that on Direct3D 11+, OpenGL and Vulkan
// hosts, discarding disables subsequent storage resource writes, on the host,
// it would be natural to perform all outstanding memory exports before
// discarding if the kill condition passes.
//
// Memory exports can be performed to any ColorFormat, including 8bpp and 16bpp
// ones. Hosts, however, may have the memory bound as a 32bpp buffer (for
// instance, due to the minimum resource view size limitation on Direct3D 11).
// In this case, bytes and shorts aren't addressable directly. However, taking
// into account that memory accesses are coherent within one shader invocation
// on Direct3D 11+, OpenGL and Vulkan and thus are done in order relatively to
// each other, it should be possible to implement them by clearing the bits via
// an atomic AND, and writing the new value using an atomic OR. This will, of
// course, make the entire write operation non-atomic, and in case of a race
// between writes to the same location, the final result may not even be just a
// value from one of the invocations, but rather, it can be OR of the values
// from any invocations involved. However, on the Xenos, there doesn't seem to
// be any possibility of meaningfully accessing the same location from multiple
// invocations if any of them is writing, memory exports are out-of-order, so
// such an implementation shouldn't be causing issues in reality. Atomic
// compare-exchange, however, should not be used for this purpose, as it may
// result in an infinite loop if different invocations want to write different
// values to the same memory location.
//
// Examples of setup in titles (Z from MSB to LSB):
//
// 4D5307E6 particles (different VS invocation counts, like 1, 2, 4):
// There is a passthrough shader - useful for verification as it simply writes
// directly what it reads via vfetch of various formats. Another shader (with
// different c# numbers, but same formats) does complicated math to process the
// particles.
// c152:           Z = 010010110000|0|111|00|100110|00000|010, count = 35840
//   8in32, 32_32_32_32_FLOAT, float, RGBA - from 32_32_32_32_FLOAT vfetch
// c154, 162:      Z = 010010110000|0|111|00|100000|00000|001, count = 71680
//   8in16, 16_16_16_16_FLOAT, float, RGBA - from 16_16_16_16_FLOAT vfetch
// c156, 158, 160: Z = 010010110000|0|000|00|011010|00000|001, count = 71680
//   8in16, 16_16_16_16, unorm, RGBA - from 16_16_16_16 unorm vfetch
// c164:           Z = 010010110000|0|111|00|011111|00000|001, count = 143360
//   8in16, 16_16_FLOAT, float, RGBA - from 16_16_FLOAT vfetch
// c166:           Z = 010010110000|0|000|00|011001|00000|001, count = 143360
//   8in16, 16_16, unorm, RGBA - from 16_16 unorm vfetch
// c168:           Z = 010010110000|0|001|00|000111|00000|010, count = 143360
//   8in32, 2_10_10_10, snorm, RGBA - from 2_10_10_10 snorm vfetch
// c170, c172:     Z = 010010110000|1|000|00|000110|00000|010, count = 143360
//   8in32, 8_8_8_8, unorm, BGRA - from 8_8_8_8 unorm vfetch with .zyxw swizzle
//
// 4D5307E6 water simulation (2048 VS invocations):
// c130: Z = 010010110000|0|111|00|100110|00000|010, count = 16384
//   8in32, 32_32_32_32_FLOAT, float, RGBA
//   The shader has 5 memexports of this kind and 6 32_32_32_32_FLOAT vfetches.
//
// 4D5307E6 water tessellation factors (1 VS invocation per triangle patch):
// c130: Z = 010010110000|0|111|11|100100|11111|010, count = patch count * 3
//   8in32, 32_FLOAT, float, RGBA
//
// 41560817 texture memory copying (64 bytes per invocation, two eA, eight eM#):
// c0: Z = 010010110000|0|010|11|011010|00011|001
//   8in16, 16_16_16_16, uint, RGBA - from 16_16_16_16 uint vfetch
//   (16_16_16_16 is the largest color format without special values)
//
// 58410B86 hierarchical depth buffer occlusion culling with the result read on
// the CPU (15000 VS invocations in the main menu):
// c8: Z = 010010110000|0|010|00|000010|00000|000, count = invocation count
//   No endian swap, 8, uint, RGBA
```
