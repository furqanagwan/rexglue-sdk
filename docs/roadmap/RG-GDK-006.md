# Title

RG-GDK-006 — Build D3D12 capability diagnostics and the three-vendor fixture harness

## Planning ID

RG-GDK-006

## Labels

gpu, directx, d3d12, amd, nvidia, intel, testing, blocked

## Objective

Make GPU behavior reproducible with capability logs, synthetic fixtures and failure captures.

## Background

Provider already queries ROV/sample/stencil features. Historical vendor defaults remain and Intel #608 warns native stencil is not uniformly usable.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/issues/608
- https://github.com/has207/xenia-edge/issues/204
- https://github.com/xenia-canary/xenia-canary/issues/1093
- https://learn.microsoft.com/en-us/windows/win32/direct3d12/hardware-feature-levels

Status and source assessment: Provider already queries ROV/sample/stencil features. Historical vendor defaults remain and Intel #608 warns native stencil is not uniformly usable. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Log adapter/driver/feature/shader/format capabilities and actual selected path.
- Add minimal standalone PM4/shader/readback fixture host respecting GPU plugin ABI.
- Add PIX markers and DRED failure capture; separate debug-layer correctness from perf runs.
- Inventory vendor exceptions with driver scope and retirement tests.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/ui/d3d12/d3d12_provider.cpp`
- `src/graphics/d3d12/render_target_cache.cpp`
- `tests/unit/CMakeLists.txt`
- `docs/regression-strategy.md`

## Tasks

- [ ] Log adapter/driver/feature/shader/format capabilities and actual selected path.
- [ ] Add minimal standalone PM4/shader/readback fixture host respecting GPU plugin ABI.
- [ ] Add PIX markers and DRED failure capture; separate debug-layer correctness from perf runs.
- [ ] Inventory vendor exceptions with driver scope and retirement tests.

## Dependencies

Depends on: RG-GDK-001

## Blocks

Blocks: RG-GDK-005
Blocks: RG-GDK-007
Blocks: RG-GDK-008
Blocks: RG-GDK-009
Blocks: RG-GDK-010
Blocks: RG-GDK-011
Blocks: RG-GDK-012

## Regression Risk

Capability defaults or diagnostics could select an unsupported path, perturb performance measurements or hide device-loss causes. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Unsupported capability selects tested fallback or clear error.
- Exercise device removal/resize/cache reuse and deterministic buffer readback.
- Run available AMD/NVIDIA/Intel matrix, with unavailable cases explicitly blocked.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] A fixture result can be independently reproduced from recorded metadata.
- [ ] No adapter is claimed supported from vendor name or FL11_0 device creation alone.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/6

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1).

Blocks: [RG-GDK-005 #5](https://github.com/furqanagwan/rexglue-sdk/issues/5), [RG-GDK-007 #7](https://github.com/furqanagwan/rexglue-sdk/issues/7), [RG-GDK-008 #8](https://github.com/furqanagwan/rexglue-sdk/issues/8), [RG-GDK-009 #9](https://github.com/furqanagwan/rexglue-sdk/issues/9), [RG-GDK-010 #10](https://github.com/furqanagwan/rexglue-sdk/issues/10), [RG-GDK-011 #11](https://github.com/furqanagwan/rexglue-sdk/issues/11), [RG-GDK-012 #12](https://github.com/furqanagwan/rexglue-sdk/issues/12).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
