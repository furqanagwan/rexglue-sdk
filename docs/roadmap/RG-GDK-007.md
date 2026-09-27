# Title

RG-GDK-007 — Decide the D3D12 shader architecture using a DXBC versus DXIL experiment

## Planning ID

RG-GDK-007

## Labels

architecture, gpu, d3d12, research, blocked

## Objective

Decide whether to retain DXBC long term or adopt a proven DXIL translation pipeline.

## Background

Edge c00e7aead removed DXBC in favor of SPIR-V→DXIL; ReXGlue still emits DXBC. Vulkan removal cannot dictate shader IR removal before this decision.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/commit/c00e7aead
- https://github.com/has207/xenia-edge/commit/6e9cb7e3f
- https://github.com/has207/xenia-edge/issues/198
- https://github.com/microsoft/DirectXShaderCompiler/blob/main/docs/DXIL.rst

Status and source assessment: Edge c00e7aead removed DXBC in favor of SPIR-V→DXIL; ReXGlue still emits DXBC. Vulkan removal cannot dictate shader IR removal before this decision. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Pin Edge compiler and dependency revisions, licensing and deployment implications.
- Prototype alternatives in an isolated branch without switching stable defaults.
- Compare float semantics, depth exports, memexport, ROV, transfer shaders and shader cache ABI.
- Write an ADR selecting the path and identifying retained/removed shader tools; keep DXBC initial ports until parity.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/pipeline/shader`
- `src/graphics/d3d12/pipeline_cache.cpp`
- `src/graphics/d3d12/render_target_cache.cpp`
- `thirdparty/CMakeLists.txt`

## Tasks

- [ ] Pin Edge compiler and dependency revisions, licensing and deployment implications.
- [ ] Prototype alternatives in an isolated branch without switching stable defaults.
- [ ] Compare float semantics, depth exports, memexport, ROV, transfer shaders and shader cache ABI.
- [ ] Write an ADR selecting the path and identifying retained/removed shader tools; keep DXBC initial ports until parity.

## Dependencies

Depends on: RG-GDK-006

## Blocks

Blocks: RG-GDK-009
Blocks: RG-GDK-010
Blocks: RG-GDK-011
Blocks: RG-GDK-012
Blocks: RG-GDK-023

## Regression Risk

Shader replacement can change NaN/Inf/rounding, interlock ordering, cache identities and support on older adapters. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Golden shader corpus with NaN/Inf/signed-zero/rcp/rsq and packed exports.
- RT transfer/float24 test from Edge #198; cold/warm cache and async compile.
- Correctness and paired frame-time comparison on all vendors.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] ADR contains measured results, rejected options, capability floor and staged rollback.
- [ ] No Vulkan runtime dependency is introduced by choosing an IR.

## Validation Commands

Current supported baseline commands (x64 VS developer shell; initialized submodules):

```powershell
cmake --preset win-amd64 -DREXGLUE_BUILD_TESTS=ON -DREXGLUE_USE_D3D12=ON -DREXGLUE_USE_VULKAN=OFF
cmake --build --preset win-amd64-debug
ctest --preset win-amd64-debug --output-on-failure
cmake --build --preset win-amd64-release
ctest --preset win-amd64-release --output-on-failure
python scripts/validate_roadmap.py
git diff --check
```

Run the issue-specific cases above and record exact new harness/test commands when implemented. No GPU/title/GDK harness command is claimed to exist yet. Research-only changes use document validation plus the stated experiment; do not report CTest as a hardware test.

## Documentation Changes

Update docs/upstream-tracking.md for adopted/rejected evidence and docs/regression-strategy.md for results. Update README/AGENTS when workflow or status changes; write/update an ADR for architecture. Keep private captures external and link artifact hashes.

## Agent Handoff Notes

Implementation may start after dependencies and the specific research gates below are complete. Read README.md, AGENTS.md, docs/investigation.md, docs/architecture-plan.md and this issue. Check git status and preserve existing work. Implement in the personal ReXGlue fork only. If an acceptance gate lacks hardware/material, record it as blocked and leave the issue open. Do not mark agent-ready until dependencies and relevant research are complete.

## Live GitHub dependency links

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/7

Prerequisites: [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6).

Blocks: [RG-GDK-009 #9](https://github.com/furqanagwan/rexglue-sdk/issues/9), [RG-GDK-010 #10](https://github.com/furqanagwan/rexglue-sdk/issues/10), [RG-GDK-011 #11](https://github.com/furqanagwan/rexglue-sdk/issues/11), [RG-GDK-012 #12](https://github.com/furqanagwan/rexglue-sdk/issues/12), [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
