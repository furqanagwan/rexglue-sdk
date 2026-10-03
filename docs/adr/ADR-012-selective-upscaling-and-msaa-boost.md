# ADR-012: Selective render target upscaling and MSAA boost

Date: 2026-10-03. Status: **accepted design, phases 1 and 2 implemented**
([RG-GDK-062 #168](https://github.com/furqanagwan/rexglue-sdk/issues/168),
[RG-GDK-063 #169](https://github.com/furqanagwan/rexglue-sdk/issues/169)).
Later phases need their own issues before code.

## Context

Microsoft's PC backward compatibility package for a title carries launch
arguments its GPU emulator (`VGPUDX12.dll`) reads, observed in the installed
files (nothing of theirs is used):

- `scalingResolutions=720x0 844x0 1280x0 0x240 0x480 0x256` (Fuzion Frenzy):
  only render targets whose width or height is on the list (`0` = any) are
  upscaled; everything else stays at the console's size. Symbols name the
  machinery: `DX12EdramManager::ComputeUpscalingMap`, `ScalingResolution`,
  `HostUpscaledMemory::ComputeUpscalingMaxAgeImmunity`, and a separate
  `AdjustUvForBilinearFilteringWhenUpscaling` for atlases.
- `aaBoostOn` with `aaBoostTargetMsaa=1`: the title's 1x render targets get a
  higher host sample count, with per-level resolve shaders.

ReXGlue scales every render target by `draw_resolution_scale_x/y`. Upscaling
a shadow map, a bloom chain or a UI atlas is what breaks post effects and
edges in some titles; Microsoft's list keeps those native.

How the scale is built in today (SDK `3cc9353`):

| Part | Scale |
| --- | --- |
| DXBC translator | A constructor constant: pixel position (`ps_param_gen`), the ROV EDRAM addressing (tile size, sample deltas, EDRAM size), point snapping and texture coordinate handling for scaled textures |
| Render target cache | Every host render target and every ownership transfer at one scale |
| Resolve | Writes the scaled copy of guest memory; the texture cache marks those pages (`scaled_resolve_pages_`) |
| Texture cache | Already mixed: a texture is scaled only if its pages were written by a scaled resolve (`TextureKey::scaled_resolve`, `textures_resolution_scaled` per fetch constant at run time) |
| MSAA | Host sample count equals the guest's (`native_2x_msaa` only emulates the guest's own 2x) |

So the texture side already handles native and scaled memory in one frame;
the render target side assumes one scale everywhere, and the ROV path bakes it
into every pixel shader's EDRAM addressing.

## Decision

### 1. A per-title list of scaled render target sizes

`resolution_scale_targets` (GPU cvar, a title default by name until the
ADR-009 fix catalog exists) holds Microsoft's syntax: space-separated
`WxH`, `0` meaning any. A size matches an entry when every non-zero dimension
of the entry is equal (`720x0` matches width 720, `0x240` height 240,
`1280x720` both). The size is the resolved rectangle's: what the game copies
out of the render target, and what its shaders later read. Empty list:
everything scaled, as now.

### Revision, phase 2 (2026-10-03): native resolves first

What a game reads of a render target is its resolve. Phase 2 therefore keeps
every render target scaled while it is drawn, and writes a resolve whose size
the list doesn't name at the guest's size: after the usual scaled copy, the
resolve downscale shader (already used for resolve readback) keeps the
center host sample of each guest texel and writes it to shared memory, and
the texture cache clears the scaled mark of the pages the resolve covers
whole (`MarkRangeAsNativeResolved`). Shaders sampling those textures then
read guest-size data, which is where upscaled shadow maps, bloom chains and
atlases go wrong. This works on both render target paths, needs no new
render target key, translation or transfer, and is used only for resolves
that cover their whole 2D destination of up to 64bpp (otherwise the resolve
stays scaled and a warning is logged once). Rendering unlisted targets still
costs the scaled resolution; sections 2 and 3 below (render-time per-target
scale on the RTV path) remain the design if that cost or a title's rendering
itself needs it.

### 2. RTV path only (render-time scale)

The ROV path addresses one EDRAM buffer whose layout is the scale; mixing
scales there means two EDRAM layouts and every ROV shader branching on both.
Render-time per-target scale is therefore RTV-only; native resolves (the
revision above) work on both paths.

### 3. Scale becomes per render target on the RTV path

- `RenderTargetKey` gains a scaled bit; host render targets of either kind
  coexist in the cache.
- Translated pixel shaders get the scale from the modification bits (one
  translation per scale actually used), not the translator constant, for the
  RTV-relevant uses (pixel position, texture coordinates). The translator
  constant stays for ROV.
- Ownership transfers between a scaled and a native key of the same EDRAM
  range resample: native to scaled replicates each sample over the scale's
  footprint; scaled to native takes the footprint's top-left sample (the
  guest-pixel centre convention the resolve already uses). Same-scale
  transfers are unchanged.
- A resolve from a native render target writes unscaled memory and clears the
  scaled-resolve pages it covers; from a scaled one, as now. The texture cache
  needs no new state.
- Viewport, scissor and depth bias scale per draw from the bound key's bit.

### 4. Bilinear UV clamp for upscaled atlases: a separate fix

Sampling an upscaled atlas bilinearly bleeds across sub-image edges the
console never reached. A clamp of each fetch to the half-texel border of the
sub-image needs the sub-image bounds, which the guest doesn't state. It is a
separate, opt-in fix (`AdjustUv...` in Microsoft's naming), designed when a
title shows the bleeding.

### 5. MSAA boost (#169): host samples above the guest's for 1x targets

`msaa_boost` (2 or 4; title default by name): on the RTV path, a guest 1x
color/depth target pair is created with that host sample count.

- The key keeps the guest's 1x (EDRAM addressing, aliasing, resolve rules all
  guest-side); the host resource records the boosted count.
- Resolves of a boosted target average its host samples into the guest's one
  sample (a `kAverage`-style resolve), then continue as a 1x resolve.
- A transfer from a boosted target to any other key, or to a guest-MSAA alias,
  first reduces it to 1x the same way; a transfer into a boosted target
  replicates. EDRAM aliasing therefore costs a resolve pass and is logged.
- Not applied: the ROV path; guest 2x/4x targets (already multisampled);
  formats without D3D12 multisample support (checked per format with
  `CheckFeatureSupport`, falling back to 1x); depth reads by `memexport` or
  EDRAM-as-texture tricks see 1x data after the reduction.

## Phases

1. **Matcher and diagnostics** (this ADR's commit): `resolution_scale_targets`
   parsing and matching (`ScalingResolutionList`), unit tested; with
   `log_resolution_scale_targets`, each resolved size is logged once with
   whether the list keeps it scaled, so a title's list can be built from a
   run.
2. **Native resolves** (#168, done): see the revision above;
   `tests/gpu/native_resolve_fixture_test.cpp` resolves a draw whose edge
   falls inside a guest pixel on both paths, listed and not. Render-time
   per-key scale (sections 2 and 3) only if a title needs it.
3. **MSAA boost** (#169): resource sample count, averaging resolve, transfer
   reduction; fixture tests at 2x and 4x boost.
4. **Atlas UV clamp**, if a title needs it.

Each phase is gated by the gpu suite, QoS and a second title at scale 2 and 3
with and without the list (screenshots), and NVIDIA; AMD and Intel recorded
when available (ADR-007).

## Consequences

- ROV titles keep global scaling.
- Each scale in use doubles the pixel shader translations it touches (two
  modifications), bounded by the titles' lists; the pipeline storage records
  them as today.
- Mixed scales cost resampling transfers where a game aliases the same EDRAM
  at both sizes; the log reports them.
