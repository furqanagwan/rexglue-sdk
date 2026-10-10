# Shader fetch: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/268).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L64)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify the fetch constant type (that it's a vertex fetch,
  // not a texture fetch), here instead of dropping draws with invalid vertex
  // fetch constants on the CPU when proper bound checks are added - vfetch may
  // be conditional, so fetch constants may also be used conditionally.
```

## Note 2: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L146)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Bound checking is not done here, but haven't encountered
  // any games relying on out-of-bounds access. On Adreno 200 on Android (LG
  // P705), however, words (not full elements) out of glBufferData bounds
  // contain 0.
```

## Note 3: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L387)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): This converts from D3D10+ float16 with NaNs instead
        // of Xbox 360 float16 with extended range. However, haven't encountered
        // games relying on that yet.
```

## Note 4: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:667

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L667)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Currently disregarding the LOD completely in getWeights
  // because the needed code would be very complicated, while getWeights is
  // mostly used for things like PCF of shadow maps, that don't have mips. The
  // LOD would be needed for the mip lerp factor in W of the return value and to
  // choose the LOD where interpolation would take place for XYZ. That would
  // require either implementing the LOD calculation algorithm using the ALU
  // (since the `lod` instruction is limited to pixel shaders and can't be used
  // when there's control flow divergence, unlike explicit gradients), or
  // sampling a texture filled with LOD numbers (easier and more consistent -
  // unclamped LOD doesn't make sense for getWeights anyway). The same applies
  // to offsets.
```

## Note 5: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:755

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L755)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Offsets need to be applied at the LOD being fetched, not
  // at LOD 0. However, since offsets have granularity of 0.5, not 1, on the
  // Xbox 360, they can't be passed directly as AOffImmI to the `sample`
  // instruction (plus-minus 0.5 offsets are very common in games). But
  // offsetting at mip levels is a rare usage case, mostly offsets are used for
  // things like shadow maps and blur, where there are no mips.
```

## Note 6: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:817

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L817)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): If LOD calculation is added to getWeights, face
          // offset probably will need to be handled too (if the hardware
          // supports it at all, though MSDN lists OffsetZ in tfetchCube).
```

## Note 7: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:842

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L842)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Currently disregarding the LOD completely in getWeights.
    // However, if the LOD lerp factor and the LOD where filtering would happen
    // are ever calculated, all components of the size may be needed for ALU LOD
    // calculation with normalized coordinates (or, if a texture filled with LOD
    // indices is used, coordinates will need to be normalized as normally).
```

## Note 8: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:977

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L977)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Mip lerp factor needs to be calculated, and the
    // coordinate lerp factors should be calculated at the mip level texels
    // would be sampled from. That would require some way of calculating the LOD
    // that would be applicable to explicit gradients and vertex shaders. Also,
    // with point sampling, possibly lerp factors need to be 0. W  (mip lerp
    // factor) should have been masked out previously because it's not supported
    // currently.
```

## Note 9: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:986

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L986)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Filtering modes should possibly be taken into account,
    // but for simplicity, not doing that - from a high level point of view,
    // would be useless to get weights that will always be zero.
```

## Note 10: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1126)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Offsets need to be applied at the LOD being fetched.
```

## Note 11: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1205)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Offsets need to be applied at the LOD being fetched.
```

## Note 12: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1461)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Gradient exponent adjustment from the fetch
          // constant needs to be applied here, would require math involving
          // SV_Position parity, replacing coordinates for one pixel with 0
          // and for another with the adjusted gradient, but possibly not used
          // by any games.
```

## Note 13: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1589)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Gradient exponent adjustment is currently not done
          // in getCompTexLOD, so don't do it here too.
```

## Note 14: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1610)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Gradient exponent adjustment is currently not
            // done in getCompTexLOD, so don't do it here too.
```

## Note 15: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1620

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1620)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Are cube map register gradients unnormalized if
            // the coordinates themselves are unnormalized?
```

## Note 16: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:1652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L1652)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Gradient exponent adjustment is currently not
            // done in getCompTexLOD, so don't do it here too.
```

## Note 17: src/graphics/pipeline/shader/dxbc_translator_fetch.cpp:2258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/dxbc_translator_fetch.cpp#L2258)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(boma): Guest clamping needs to be verified on real hardware.
```

## Note 18: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L107)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Verify the fetch constant type (that it's a vertex fetch,
    // not a texture fetch) here instead of dropping draws with invalid vertex
    // fetch constants on the CPU when proper bound checks are added - vfetch
    // may be conditional, so fetch constants may also be used conditionally.
    // Mask to physical, in dwords - the guest may use a mirror window.
```

## Note 19: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L268)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): This converts from GLSL float16 with NaNs instead of
      // Xbox 360 float16 with extended range. However, haven't encountered
      // games relying on that yet.
```

## Note 20: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:569

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L569)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Currently disregarding the LOD completely in
      // getWeights because the needed code would be very complicated, while
      // getWeights is mostly used for things like PCF of shadow maps, that
      // don't have mips. The LOD would be needed for the mip lerp factor in W
      // of the return value and to choose the LOD where interpolation would
      // take place for XYZ. That would require either implementing the LOD
      // calculation algorithm using the ALU (since the `lod` instruction is
      // limited to pixel shaders and can't be used when there's control flow
      // divergence, unlike explicit gradients), or sampling a texture filled
      // with LOD numbers (easier and more consistent - unclamped LOD doesn't
      // make sense for getWeights anyway). The same applies to offsets.
```

## Note 21: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:775

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L775)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Offsets need to be applied at the LOD being fetched, not
    // at LOD 0. However, since offsets have granularity of 0.5, not 1, on the
    // Xenos, they can't be passed directly as ConstOffset to the image sample
    // instruction (plus-minus 0.5 offsets are very common in games). But
    // offsetting at mip levels is a rare usage case, mostly offsets are used
    // for things like shadow maps and blur, where there are no mips.
```

## Note 22: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L838)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): If LOD calculation is added to getWeights, face
            // offset probably will need to be handled too (if the hardware
            // supports it at all, though MSDN lists OffsetZ in tfetchCube).
```

## Note 23: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L871)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Currently disregarding the LOD completely in
      // getWeights. However, if the LOD lerp factor and the LOD where filtering
      // would happen are ever calculated, all components of the size may be
      // needed for ALU LOD calculation with normalized coordinates (or, if a
      // texture filled with LOD indices is used, coordinates will need to be
      // normalized as normally).
```

## Note 24: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:1184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1184)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Mip lerp factor needs to be calculated, and the
    // coordinate lerp factors should be calculated at the mip level texels
    // would be sampled from. That would require some way of calculating the
    // LOD that would be applicable to explicit gradients and vertex shaders.
    // Also, with point sampling, possibly lerp factors need to be 0. W (mip
    // lerp factor) should have been masked out previously because it's not
    // supported currently.
```

## Note 25: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:1264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1264)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// FIXME(Triang3l): Filtering modes should possibly be taken into account,
      // but for simplicity, not doing that - from a high level point of view,
      // would be useless to get weights that will always be zero.
```

## Note 26: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:1987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L1987)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Are cube map register gradients unnormalized
              // if the coordinates themselves are unnormalized?
```

## Note 27: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:2683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2683)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(boma): Guest clamping needs to be verified on real hardware.
```

## Note 28: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:2832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2832)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Limit the total count to that actually supported by the
  // implementation.
```

## Note 29: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:2880

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2880)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Limit to what's actually supported by the implementation.
```

## Note 30: src/graphics/pipeline/shader/spirv_translator_fetch.cpp:2893

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/graphics/pipeline/shader/spirv_translator_fetch.cpp#L2893)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Triang3l): Limit the total count to that actually supported by the
  // implementation.
```
