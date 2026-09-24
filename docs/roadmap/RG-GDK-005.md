# Title

RG-GDK-005 — Repair signed DXBC memexport rounding

## Planning ID

RG-GDK-005

## Labels

gpu, d3d12, regression, upstream-sync, blocked

## Objective

Fix both rounding-bias temporary destinations and validate exported guest bytes.

## Background

Canary #1127 writes bias to round_bias_temp. Both faulty local sequences remain at dxbc_translator_memexport.cpp:188 and :401.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1127

Status and source assessment: Canary #1127 writes bias to round_bias_temp. Both faulty local sequences remain at dxbc_translator_memexport.cpp:188 and :401. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Adapt the two destination corrections without shader architecture changes.
- Create signed normalized/packed export fixtures with positive, negative, half-step and saturation values.
- Record original author/SHA and reported title cases.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/pipeline/shader/dxbc_translator_memexport.cpp`
- `tests/unit/CMakeLists.txt`

## Tasks

- [ ] Adapt the two destination corrections without shader architecture changes.
- [ ] Create signed normalized/packed export fixtures with positive, negative, half-step and saturation values.
- [ ] Record original author/SHA and reported title cases.

## Dependencies

Depends on: RG-GDK-001
Depends on: RG-GDK-006

## Blocks

Blocks: no initial implementation issue

## Regression Risk

Signed packed exports could change rounding/saturation or write wrong guest bytes, corrupting GPU-skinned geometry. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Shader disassembly shows bias temp initialized before use.
- GPU readback matches independently calculated packed bytes; include both affected branches.
- Control unsigned/float export paths and CPU-visible memexport synchronization.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] Baseline reproduces the wrong signed result; candidate produces expected bytes.
- [ ] Affected GPU matrix passes without unrelated DXBC output changes.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/5

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1), [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6).

Blocks: no initial implementation issue.

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
