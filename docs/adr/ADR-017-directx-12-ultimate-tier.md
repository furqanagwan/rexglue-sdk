# ADR-017: DirectX 12 Ultimate is an optional tier, detected and used per feature

Date: 2026-10-10. Status: accepted owner direction. Implemented so far: the
capability report. Each feature adoption below is its own issue under
[the DirectX 12 Ultimate epic](https://github.com/furqanagwan/rexglue-sdk/issues/305).

## Context

The owner asked for foundations for native rendering on DirectX 12 Ultimate,
keeping the GDK in mind.

DirectX 12 Ultimate is feature level 12_2. It means all five of:
- shader model 6.5;
- DirectX Raytracing (DXR) tier 1.1;
- variable-rate shading (VRS) tier 2;
- mesh shaders tier 1;
- sampler feedback tier 0.9.

Newer D3D12 features sit beside it. These include enhanced barriers, GPU
upload heaps (resizable BAR) and work graphs. Xbox Series X|S and current PC
GPUs support Ultimate; many PCs the games could run on do not.

What ReXGlue needs today:

| Path | Needs |
| --- | --- |
| Emulated Xenos path, DXBC (ADR-008) | Feature level 11_0 and shader model 5.1 |
| DXIL path (#53) | Shader model 6.6, Agility SDK 1.618.5 shipped with the title |
| Native renderers ([research](../native-renderers.md)) | Not designed yet |

The D3D12 host code already lives behind `D3D12Provider`. The provider queries
and logs device features when the device is created.

## Decision

1. **Ultimate is an optional tier, never a requirement.** A title still
   launches on everything it supports today. Each Ultimate or newer feature
   is used only when the device reports it. The path it replaces stays as
   the fallback, and a setting can turn the feature off for comparison.
2. **One capability query per device.** `QueryD3D12Capabilities`
   (`include/rex/ui/d3d12/d3d12_capabilities.h`) reads the ray tracing, VRS,
   mesh shader, sampler feedback, enhanced barrier, GPU upload heap and work
   graph support once. `D3D12Provider::GetCapabilities()` exposes it. The
   device log says whether the device meets DirectX 12 Ultimate and, if not,
   what it lacks. Code tests this struct, not the raw D3D12 options.
3. **Features that need shader model 6.5 or newer go on the DXIL path.** This
   covers mesh and amplification shaders, ray tracing shaders and sampler
   feedback in shaders. The DXBC translator gets no new shader-model work
   (ADR-008).
4. **Each adoption is its own issue with its own gate:**
   - GPU fixture parity with the feature on and off;
   - no D3D12 debug-layer errors;
   - a paired Quantum of Solace frame-time run;
   - NVIDIA required; AMD and Intel recorded but non-blocking (ADR-007).

   A default is changed only by a separate PR after the gate passes.
5. **GDK.** PC builds take D3D12 from Windows, or from the Agility SDK the
   title ships, pinned by ADR-008. Feature queries use the Windows SDK
   10.0.26100 headers that the pinned GDK 260404 builds with. Host D3D12 code
   stays behind `D3D12Provider` and the GPU plugin boundary, so a console
   D3D12 provider could be added later without touching guest code. No
   console D3D12 code is written until console hardware and its SDK are
   available (ADR-016).

## Where each feature could help

| Feature | Use in ReXGlue | Path | Order |
| --- | --- | --- | --- |
| Capability report | Know what each player's device can do; logs and fault reports | Both | Done with this ADR |
| Enhanced barriers | Finer resource transitions in the render target cache, shared memory and texture cache | Both (host side) | 1 |
| GPU upload heaps | Write guest-memory uploads straight to GPU-visible memory instead of an upload buffer and a copy | Both (host side) | 2 |
| Mesh shaders | Expand Xenos points, rectangles, quads and lines without geometry shaders (`PipelineGeometryShader`) | DXIL | 3, after #53 stage 4 |
| Variable-rate shading | Opt-in coarser shading in upscaled render targets (ADR-012). It changes the image, so it never becomes a default | Both | 4 |
| Sampler feedback | Texture streaming for native renderers | Native renderers | After the native renderer ADR |
| Ray tracing | Optional effects in native renderers; none in emulation | Native renderers | After the native renderer ADR |
| Work graphs | No use found; reported only | — | — |

## Rejected alternatives

- **Require feature level 12_2.** This would drop GPUs that run the games well
  today. It would gain nothing for the emulated path, which draws what the
  Xbox 360 drew.
- **Add Ultimate features to the DXBC translator.** DXBC stops at shader model
  5.1, so mesh, ray tracing and feedback shaders cannot be expressed in it.
- **Write console D3D12 code now.** There is no hardware or SDK access to test
  it. That breaks the regression policy (ADR-006).
- **Adopt work graphs.** Nothing in the emulator or the native renderer plan
  needs GPU-driven work scheduling yet.

## Consequences

- Every feature has two paths until its fallback is retired by a later ADR.
- The capability log is the evidence for what a player's device supports. It
  is not evidence that a feature works; that needs the gate in decision 4.
- Native renderers keep their own decision record. This ADR only fixes the
  capability layer they build on.
