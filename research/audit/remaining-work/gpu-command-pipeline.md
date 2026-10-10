# Gpu command pipeline: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/262).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/command_processor.cpp:313

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L313)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME: We're supposed to process the WAIT_UNTIL register at this point,
    // but no games seem to actually use it.
```

## Note 2: src/graphics/command_processor.cpp:512

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L512)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Should this increase beyond 7 bits for PWL?
          // Direct3D 9 explicitly sets rw_index to 0x80 after writing the last
          // PWL entry. However, the DC_LUT_RW_INDEX documentation says that for
          // PWL, the bit 7 is ignored.
```

## Note 3: src/graphics/command_processor.cpp:545

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L545)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Should this reset the component write index? If this
        // increase is assumed to behave like a full DC_LUT_RW_INDEX write, it
        // probably should. Currently this also calls WriteRegister for
        // DC_LUT_RW_INDEX, which resets gamma_ramp_rw_component_ as well.
```

## Note 4: src/graphics/command_processor.cpp:671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L671)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): notify resource cache of base->size and type.
```

## Note 5: src/graphics/command_processor.cpp:1092

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L1092)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): only swap frontbuffer ptr.
```

## Note 6: src/graphics/command_processor.cpp:1439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L1439)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Remove IndexBufferInfo and replace handling of all this
  // with PrimitiveProcessor when the old Vulkan renderer is removed.
```

## Note 7: src/graphics/command_processor.cpp:1481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/command_processor.cpp#L1481)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): VGT_IMMED_DATA.
```

## Note 8: src/graphics/d3d12/command_processor.cpp:2244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/command_processor.cpp#L2244)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Choose between the table and PWL based on
        // DC_LUTA_CONTROL, support both for all formats (and also different
        // increments for PWL).
```

## Note 9: src/graphics/d3d12/command_processor.cpp:2823

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/command_processor.cpp#L2823)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): With ROV, pass the disabled render target mask for safety.
```

## Note 10: src/graphics/d3d12/command_processor.cpp:2927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/command_processor.cpp#L2927)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Support all primitive types.
```

## Note 11: src/graphics/d3d12/command_processor.cpp:3094

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/command_processor.cpp#L3094)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find some PM4 command that can be used for indication of
    // when memexports should be awaited?
```

## Note 12: src/graphics/d3d12/command_processor.cpp:3746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/command_processor.cpp#L3746)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): If failed to await (completed submission < awaited frame
  // submission), do something like dropping the draw command that wanted to
  // open the frame.
```

## Note 13: src/graphics/d3d12/pipeline_cache.cpp:431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L431)

Disposition: retired reminder. Vulkan is a retired host backend.

```text
// TODO(Triang3l): On Vulkan, skip pipelines requiring unsupported
        // device features (to keep the cache files mostly shareable across
        // devices).
        // Mark the shader modifications as needed for translation; DXIL
        // pipelines are translated to SPIR-V when they're created below.
```

## Note 14: src/graphics/d3d12/pipeline_cache.cpp:686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L686)

Disposition: retired reminder. Vulkan is a retired host backend.

```text
// TODO(Triang3l): On Vulkan, skip pipelines requiring unsupported device
      // features (to keep the cache files mostly shareable across devices).
      // Skip already known pipelines - those have already been enqueued.
```

## Note 15: src/graphics/d3d12/pipeline_cache.cpp:1784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L1784)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Investigate interaction of OMSetRenderTargets with
    // non-null depth and DSVFormat DXGI_FORMAT_UNKNOWN in the same case.
```

## Note 16: src/graphics/d3d12/pipeline_cache.cpp:1826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L1826)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Use ForcedSampleCount or some other fallback for
      // sample counting when needed, though with 2x it will be as incorrect as
      // with 1x / 4x anyway; or bind a dummy depth / stencil buffer if really
      // needed.
```

## Note 17: src/graphics/d3d12/pipeline_cache.cpp:1832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L1832)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): 4x MSAA fallback when 2x isn't supported.
```

## Note 18: src/graphics/d3d12/pipeline_cache.cpp:2836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L2836)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Find the correct decomposition of quads into triangles
      // on the real hardware.
```

## Note 19: src/graphics/d3d12/pipeline_cache.cpp:3309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L3309)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): 4x MSAA fallback when 2x isn't supported without ROV.
```

## Note 20: src/graphics/d3d12/pipeline_cache.cpp:3418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/pipeline_cache.cpp#L3418)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): When it happens to be that a combination of parameters
  // (no host pixel shader and depth / stencil without ROV) would disable
  // rasterization when it's still needed (for occlusion query sample counting),
  // ensure rasterization happens (by binding an empty pixel shader, or maybe
  // via ForcedSampleCount when not using 2x MSAA - its requirements for
  // OMSetRenderTargets need some investigation though).
```

## Note 21: src/graphics/d3d12/shared_memory.cpp:68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/d3d12/shared_memory.cpp#L68)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Re-enable tiled resources with PIX once fixed.
```

## Note 22: include/rex/graphics/d3d12/command_processor.h:632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/graphics/d3d12/command_processor.h#L632)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Investigate the issue with the sampler 2047 on Nvidia.
```
