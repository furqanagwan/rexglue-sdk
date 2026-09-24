# Title

RG-GDK-011 — Audit GPU synchronization, async pipelines and memexport readback

## Planning ID

RG-GDK-011

## Labels

gpu, d3d12, regression, compatibility, blocked

## Objective

Preserve GPU/CPU visibility and pipeline lifetime under load and memory pressure.

## Background

UFC3 #1093 differentiates stock/created fighters and backend behavior. Edge has publication-order and placeholder lifetime fixes; PM4 ring cadence alternatives need comparison.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/issues/1093
- https://github.com/xenia-canary/xenia-canary/pull/1195
- https://github.com/has207/xenia-edge/commit/29fcaeac3
- https://github.com/has207/xenia-edge/commit/462a1ac85
- https://github.com/has207/xenia-edge/commit/fe84ec77e

Status and source assessment: UFC3 #1093 differentiates stock/created fighters and backend behavior. Edge has publication-order and placeholder lifetime fixes; PM4 ring cadence alternatives need comparison. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Trace barriers/fences/descriptors and guest memory ownership end to end.
- Review Edge shader validity publication and placeholder pinning against local async implementation.
- Assess RB_BLKSZ pointer publication versus rejected fixed-packet proposal.
- Never globally allow invalid upload ranges to hide guest memory faults.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/shared_memory.cpp`
- `src/graphics/d3d12/shared_memory.cpp`
- `src/graphics/d3d12/command_processor.cpp`
- `src/graphics/d3d12/pipeline_cache.cpp`
- `src/graphics/command_processor.cpp`

## Tasks

- [ ] Trace barriers/fences/descriptors and guest memory ownership end to end.
- [ ] Review Edge shader validity publication and placeholder pinning against local async implementation.
- [ ] Assess RB_BLKSZ pointer publication versus rejected fixed-packet proposal.
- [ ] Never globally allow invalid upload ranges to hide guest memory faults.

## Dependencies

Depends on: RG-GDK-004
Depends on: RG-GDK-006
Depends on: RG-GDK-007
Depends on: RG-GDK-009

## Blocks

Blocks: RG-GDK-023

## Regression Risk

Missing barriers/publication fences or premature pipeline reclamation can cause stale memexport data, corruption and device removal. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Near-full heap, failed stream ranges, GPU write then CPU read then GPU reuse.
- Concurrent first-use/cache-hit shader compilation with teardown/device removal.
- Ring wrap and polling progress under large bursts.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] No use-after-free, stale shader validity or unresolved ownership hazard in stress runs.
- [ ] UFC3 and async pipeline cases recorded per vendor, with actual unavailable fixtures blocked.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/11

Prerequisites: [RG-GDK-004 #4](https://github.com/furqanagwan/rexglue-sdk/issues/4), [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6), [RG-GDK-007 #7](https://github.com/furqanagwan/rexglue-sdk/issues/7), [RG-GDK-009 #9](https://github.com/furqanagwan/rexglue-sdk/issues/9).

Blocks: [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
