# Asynchronous pipeline creation

With `async_shader_compilation` (on by default), new pipelines are created on
background threads (`d3d12_pipeline_creation_threads`, three quarters of the
cores, below-normal priority). A draw whose pipeline isn't ready yet is
skipped, unless it draws into a one-off or small target or uses memexport,
in which case it waits for its own pipeline only
(`tests/gpu/async_draw_fixture_test.cpp`).

## Frame end doesn't wait

`PipelineCache::EndSubmission` used to create every queued pipeline on the
command processor thread and wait for the creation threads at the end of
each submission. Because skipped draws never record a pipeline that isn't
ready, nothing in the command list needs them. With async compilation, it
now only wakes the creation threads. Without async compilation, draws record
pipelines that are still being created, so the wait stays.

Source: has207/xenia-edge `4366b05dae` ("[D3D12] async shader compilation
actually fully async", 2026-01-06). Its other hunk, `use_try_claim` for
Edge's placeholder pipelines, doesn't apply: ReXGlue has no placeholders.

Measured on Quantum of Solace, DXIL, cold shader cache, the same save,
180 s (2026-10-09):

| | Before | After |
| --- | --- | --- |
| Level-load frame | 25.5 s (24.9 s creating pipelines in draws) | 7.5 s (7.0 s in draws) |
| 5 s windows with a frame over 300 ms after the load | 16, up to 617 ms, spent in swap | none; longest frame 99 ms |
| Rendering | complete | complete, no missing geometry in the screenshots |

The hitches after the load were the frame-end wait (they show as "swap" in
the `Long frame` log line). What's left is the level-load frame: draws that
wait for their own pipeline, and SPIR-V translation, which still runs on the
draw thread for DXIL.

## What the level-load frame is made of

The `Long frame` log line splits pipeline time into DXIL setup (choosing
the modifications and translating to SPIR-V on the draw thread) and the
draws that waited for their own pipeline. QoS on DXIL, cold cache, same save,
with the frame-end change (2026-10-09):

| Frame | Pipelines | DXIL setup | Awaited |
| --- | --- | --- | --- |
| First level load, 7.6 s | 7.1 s | 0.4 s | 265 pipelines, 6.7 s |
| Next area, 5.0 s | 5.0 s | 0.1 s | 191 pipelines, 4.9 s |

So almost all of it is the deliberate waits: during a load every render
target is new, so every draw counts as "not drawn recently" and waits, at
about 25 ms a pipeline, one after another. SPIR-V translation is not the
problem. DXBC's level load was 6.3 s in the same batch, so this isn't
DXIL-specific.

These waits keep one-off renders correct, so they stay. They only happen
with a cold cache: the second launch restores the pipelines from storage
before play. For players, a release can ship a recorded cache
(`docs/shader-cache.md`), which removes the first-launch wait too.
