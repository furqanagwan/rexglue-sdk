# Native rendering

ReXGlue runs a title's graphics by emulating the Xbox 360 GPU: the game's D3D
command stream (PM4 packets, Xenos shaders, EDRAM render targets) is translated
to D3D12 or Vulkan every frame. That is accurate but costs frame rate and can
show translation artifacts. A **native renderer** instead reads the game's own
scene data and draws it with host shaders written for the host GPU, the way the
Skate 3 recompilation does (twice the emulated frame rate at a quarter of the
GPU power).

A native renderer is always game-specific: it needs to know where the engine
keeps meshes, materials, cameras and lights. The SDK provides the parts every
game's renderer needs.

## What the SDK provides

| Piece | Header | Purpose |
| --- | --- | --- |
| Host render interface | `rex/graphics/native_rhi.h` | Buffers, textures, pipelines, binding layouts and a command recorder, implemented on D3D12 and Vulkan on top of the command processors. HLSL is compiled at runtime on D3D12; Vulkan takes prebuilt SPIR-V |
| Guest output hook | `rex/graphics/native_guest_renderer.h` | Register a renderer that draws the frame the presenter shows, or yields that frame back to emulation |
| Pass suppression | same | While the renderer draws, emulated draws and resolves of the passes it replaces are skipped and occlusion queries report the fake count. `SetNativeGuestOutputPassFilter` says which passes those are |
| Ultrawide output | same | `SetNativeGuestOutputWideAspect` sizes the output wider than the frontbuffer while the renderer serves frames |
| Guest texture addressing | `rex/graphics/pipeline/texture/util.h` | `GetTiledOffset2D`/`3D` locate blocks in tiled guest textures; the matching `GetTiledAddressUpperBound2D`/`3D` functions bound safe reads |
| Gameplay presence | `rex/kernel/guest_presence.h` | `GameplayContextValue` reports user 0's live gameplay context (`0x8001`), allowing a renderer to yield in frontends and loading screens |
| Programmatic performance capture | `rex/perf/counter.h` | `StartCapture` records a bounded scene sample to summary and per-frame CSV files; `IsCaptureRecording` prevents overlapping captures |
| Guest function hooks | generated code | Every recompiled function is a weak symbol with an `__imp__` original, so a game can replace one, capture the arguments and call through |
| Frame tools | cvars | `frame_stats_csv`, `gpu_trace_frame`, `gpu_skip_pixel_shaders`, and for
finding a game's own geometry `gpu_trace_shaders` (trace one shader program), `gpu_trace_constants`
(its transform chain) and `gpu_trace_vertex_buffers` (see recomp-framework CONTRIBUTING) |

Games that register nothing run exactly as before; none of this is active.

## How a game renderer fits together

```
guest render thread                          host GPU thread (swap)
-------------------                          ----------------------
engine submits a mesh ─┐                     presenter refresh
  hook: sub_XXXXXXXX   │ capture record ──►  TryRenderNativeGuestOutput
  (reads MeshContext,  │  (per frame queue)    ├─ renderer builds the scene
   calls __imp__ ...)  ┘                       │  from the captured records
                                               ├─ draws with nrhi::Cmd into
engine swaps ─────────────────────────────►    │  the guest output texture
                                               └─ returns true (or false to
                                                  let emulation show the frame)
```

1. **Find the submission points.** Use the frame trace to see which shader
   programs draw the scene: summarising it names them by draw count, and tracing
   one of them with `gpu_trace_constants` says which of its constants are the
   projection (never change), the camera (change per frame) and each object's
   own transform (change per draw). Then find the guest functions that submit
   those meshes (the Skate 3 renderer hooks the render-mesh and sorted draw-list
   functions). Menus, videos and loading screens can stay emulated: yield
   whenever the captured data is not a frame you can draw.
2. **Hook them.** Define the function with `REX_FUNC(sub_XXXXXXXX)` in the game
   project; the generated weak symbol is replaced at link time. Read what you
   need from guest memory (big-endian) and call `__imp__sub_XXXXXXXX` so the
   game keeps running normally.
3. **Register the renderer** at startup with
   `rex::graphics::SetNativeGuestOutputRenderer`. In the callback, create
   resources through `context.device`, record through `context.cmd` and draw
   into `context.guest_output` (it arrives in `ResourceState::kGuestOutput` and
   must be returned to it).
4. **Say which passes you replace** with `SetNativeGuestOutputPassFilter`.
   Passes whose results the game or your renderer reads back from guest memory
   (lightmap composition, render-to-texture UI) must keep running. The default
   suppresses only framebuffer-sized passes.
5. **Port the shaders.** Recreate the game's material shading in HLSL (the
   Xenos shader disassembly in the frame trace names the constants and
   textures each pass uses).

The smallest working renderer is recomp-framework's
`common/src/debug/native_render_probe.cpp`: it clears every frame to a colour.
Run a game with `--recomp_native_render_probe` to check the path works on a
machine.

## Measuring a pass

A native renderer's claim is that it costs less than emulating the GPU, so the
cost of each pass is worth having before any of it is written.

Mark each pass with `cmd.ProfileRegion(stage)`. A mark closes the previous
stage's span and opens its own, so the calls go at the start of each pass and
`ProfileStage::kTail` goes after the last one.

Run with `--frame_stats_csv=<file>`. Each row gains eleven `gpu_*_ms` columns
and a `gpu_frame` column saying which frame they belong to: readback waits for
the GPU to pass that submission, so the numbers arrive a few frames after the
CPU counters for the same frame and the two are not on the same row.

The probe renderer (`--recomp_native_render_probe` in the recomp framework)
marks its clear as `kMain`, which is how this path is checked on a machine
before a real renderer exists.

`d3d12_gpu_timestamp_buckets` and `vulkan_gpu_timestamp_buckets` turn the
collection off per backend. A device whose queue reports no timestamp support
logs that once and leaves the columns at zero.

## Status

- The interface and D3D12/Vulkan backends are ported from the Skate 3
  recompilation's SDK (github.com/mchughalex/rexglue-skate3), which runs a full
  game on them. Skate 3's surface-width pass selection became the per-game pass
  filter.
- GPU time per render stage (`nrhi::Cmd::ProfileRegion`) is measured: both
  command processors keep three frames of timestamp queries and report each
  stage's span in `frame_stats_csv`'s `gpu_*_ms` columns. Off unless that CSV
  is set, so an ordinary run pays nothing. See "Measuring a pass" below.
- No title in this organisation has a native renderer yet. The first target is
  a game whose emulated renderer is slow or shows artifacts.
