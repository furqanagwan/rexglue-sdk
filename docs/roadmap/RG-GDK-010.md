# Title

RG-GDK-010 — Implement ZPD counters and track VIZ predication separately

## Planning ID

RG-GDK-010

## Labels

gpu, d3d12, compatibility, research, upstream-sync, blocked

## Objective

Replace fake occlusion results with validated query semantics, without treating pending VIZ code as settled.

## Background

Local EVENT_WRITE_ZPD emits fixed samples and VIZ returns visible. Canary #1218 supersedes earlier ZPD work; #1111 remains WIP and has ROV lifecycle questions.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1218
- https://github.com/xenia-canary/xenia-canary/pull/1111
- https://github.com/xenia-canary/xenia-canary/pull/1058
- https://github.com/has207/xenia-edge/pull/127
- https://github.com/has207/xenia-edge/pull/143
- https://github.com/has207/xenia-edge/pull/145

Status and source assessment: Local EVENT_WRITE_ZPD emits fixed samples and VIZ returns visible. Canary #1218 supersedes earlier ZPD work; #1111 remains WIP and has ROV lifecycle questions. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Implement report ABI, running counter differences, fences, FIFO retirement and reuse for ZPD.
- Use strict correctness path as oracle; document fast/readback interactions.
- Keep VIZ a separate sub-change gated on resolved #1111 semantics; exclude memexport/copy where required.
- Do not revive obsolete saturation tuning from Edge #143.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/command_processor.cpp`
- `include/rex/graphics/command_processor.h`
- `src/graphics/d3d12/command_processor.cpp`
- `src/graphics/d3d12/pipeline_cache.cpp`

## Tasks

- [ ] Implement report ABI, running counter differences, fences, FIFO retirement and reuse for ZPD.
- [ ] Use strict correctness path as oracle; document fast/readback interactions.
- [ ] Keep VIZ a separate sub-change gated on resolved #1111 semantics; exclude memexport/copy where required.
- [ ] Do not revive obsolete saturation tuning from Edge #143.

## Dependencies

Depends on: RG-GDK-006
Depends on: RG-GDK-007
Depends on: RG-GDK-009

## Blocks

Blocks: RG-GDK-023

## Regression Risk

Query reuse or retirement errors can leave guest reports unresolved, produce false visibility or force severe GPU stalls. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- BEGIN/END, wrap, zero draws, recycled IDs, split submissions, MSAA/resolution changes and guest memory reuse.
- Crackdown 2 flare control with full/fast resolve and query modes.
- VIZ occluded/visible surveys and predicate lifecycle only after research gate.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] ZPD no longer relies on unconditional fake counts for validated path.
- [ ] No guest hangs waiting for reports; VIZ adoption either proven or explicitly deferred/open.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/10

Prerequisites: [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6), [RG-GDK-007 #7](https://github.com/furqanagwan/rexglue-sdk/issues/7), [RG-GDK-009 #9](https://github.com/furqanagwan/rexglue-sdk/issues/9).

Blocks: [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
