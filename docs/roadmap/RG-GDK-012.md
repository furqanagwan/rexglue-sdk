# Title

RG-GDK-012 — Validate scalar math and depth workarounds before adopting defaults

## Planning ID

RG-GDK-012

## Labels

gpu, d3d12, game-specific, research, regression, blocked

## Objective

Separate numerical corrections from title-motivated depth workarounds.

## Background

Canary #1190 replaces AC6 ground hack with approximation behavior; pending #1077 needs correctness research. Edge #160 fixes some decals but #278 reports Lost Odyssey regression.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1190
- https://github.com/xenia-canary/xenia-canary/pull/1031
- https://github.com/xenia-canary/xenia-canary/pull/1077
- https://github.com/has207/xenia-edge/pull/160
- https://github.com/has207/xenia-edge/issues/278

Status and source assessment: Canary #1190 replaces AC6 ground hack with approximation behavior; pending #1077 needs correctness research. Edge #160 fixes some decals but #278 reports Lost Odyssey regression. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Compare scalar approximation rounding and local existing behavior.
- Characterize Inf/NaN depth, depth clipping and shader bias for each path.
- Keep game-motivated offsets opt-in pending profile decision; document FH2 control case.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/pipeline/shader/dxbc_translator_alu.cpp`
- `src/graphics/pipeline/shader/dxbc_translator_fetch.cpp`
- `src/graphics/util/draw.cpp`
- `src/graphics/d3d12/render_target_cache.cpp`

## Tasks

- [ ] Compare scalar approximation rounding and local existing behavior.
- [ ] Characterize Inf/NaN depth, depth clipping and shader bias for each path.
- [ ] Keep game-motivated offsets opt-in pending profile decision; document FH2 control case.

## Dependencies

Depends on: RG-GDK-006
Depends on: RG-GDK-007

## Blocks

Blocks: RG-GDK-013
Blocks: RG-GDK-023

## Regression Risk

A math/depth change helping AC6 or Gears can regress Lost Odyssey, Forza Horizon 2 and unrelated shaders. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Numerical vectors for rcp/rsq/log/exp with boundary/exception values.
- Lost Odyssey RX 6600 reproduction and Gears/SCDA benefits plus FH2 negative control.
- No fixed-function plus shader double-bias.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] General math fixes have an independent semantic oracle.
- [ ] No experimental depth clamp/bias becomes a universal default without evidence.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/12

Prerequisites: [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6), [RG-GDK-007 #7](https://github.com/furqanagwan/rexglue-sdk/issues/7).

Blocks: [RG-GDK-013 #13](https://github.com/furqanagwan/rexglue-sdk/issues/13), [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
