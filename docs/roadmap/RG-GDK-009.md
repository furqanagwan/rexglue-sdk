# Title

RG-GDK-009 — Migrate canonical EDRAM with alias and MSAA follow-up fixes

## Planning ID

RG-GDK-009

## Labels

gpu, d3d12, amd, regression, migration, blocked

## Objective

Unify EDRAM layout and preserve color/depth/sample alias semantics as a tested migration.

## Background

Canary #1163 introduced a canonical model; #1238 explicitly repairs an AMD regression. #1222 preserves bits under color/depth aliases.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1163
- https://github.com/xenia-canary/xenia-canary/pull/1238
- https://github.com/xenia-canary/xenia-canary/pull/1222

Status and source assessment: Canary #1163 introduced a canonical model; #1238 explicitly repairs an AMD regression. #1222 preserves bits under color/depth aliases. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Map all layout consumers and generated transfer/dump/resolve shader artifacts.
- Port #1163 with #1238/#1222 behavior and the chosen shader architecture.
- Preserve existing PWL gamma/UNorm16 import and rollback path.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/pipeline/render_target/cache.cpp`
- `src/graphics/d3d12/render_target_cache.cpp`
- `src/graphics/d3d12/command_processor.cpp`
- `src/graphics/shaders`

## Tasks

- [ ] Map all layout consumers and generated transfer/dump/resolve shader artifacts.
- [ ] Port #1163 with #1238/#1222 behavior and the chosen shader architecture.
- [ ] Preserve existing PWL gamma/UNorm16 import and rollback path.

## Dependencies

Depends on: RG-GDK-006
Depends on: RG-GDK-007
Depends on: RG-GDK-008

## Blocks

Blocks: RG-GDK-010
Blocks: RG-GDK-011
Blocks: RG-GDK-023

## Regression Risk

Mixed EDRAM sample conventions can corrupt color/depth aliases and regress AMD MSAA depth copies. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Exact color/depth alias bits, 32/64bpp ownership transfers, clears and PWL gamma blend.
- 2x/4x host depth copy sample indices, scaled resolution and ROV/RTV parity.
- Title 4D5307F1 AMD and 4D530A26 occluded sprites; unrelated workloads.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] No mixed old/new EDRAM address convention remains.
- [ ] All vendor matrix cases pass including regression follow-ups; generated shaders reproducible.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/9

Prerequisites: [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6), [RG-GDK-007 #7](https://github.com/furqanagwan/rexglue-sdk/issues/7), [RG-GDK-008 #8](https://github.com/furqanagwan/rexglue-sdk/issues/8).

Blocks: [RG-GDK-010 #10](https://github.com/furqanagwan/rexglue-sdk/issues/10), [RG-GDK-011 #11](https://github.com/furqanagwan/rexglue-sdk/issues/11), [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
