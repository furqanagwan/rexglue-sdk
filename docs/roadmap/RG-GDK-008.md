# Title

RG-GDK-008 — Port texture layout and sub-32bpp resolve address corrections

## Planning ID

RG-GDK-008

## Labels

gpu, d3d12, compatibility, upstream-sync, blocked

## Objective

Correct guest texture and resolve addresses while retaining current renderer architecture.

## Background

Canary #1243 changes array/volume mips, linear 96bpp pitch and 3D bounds. #1240 handles 8/16bpp macro phases. Local texture utility retains old formulas.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1243
- https://github.com/xenia-canary/xenia-canary/pull/1240

Status and source assessment: Canary #1243 changes array/volume mips, linear 96bpp pitch and 3D bounds. #1240 handles 8/16bpp macro phases. Local texture utility retains old formulas. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Port independently testable layout corrections with full source provenance.
- Use checked range calculations and preserve array/volume distinctions.
- Keep texture-cache lifetime changes separate.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/graphics/pipeline/texture/util.cpp`
- `include/rex/graphics/pipeline/texture/util.h`
- `src/graphics/util/draw.cpp`

## Tasks

- [ ] Port independently testable layout corrections with full source provenance.
- [ ] Use checked range calculations and preserve array/volume distinctions.
- [ ] Keep texture-cache lifetime changes separate.

## Dependencies

Depends on: RG-GDK-006

## Blocks

Blocks: RG-GDK-009

## Regression Risk

New row/tile/mip formulas can overlap guest subresources or misplace resolve destinations across formats and scales. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Enumerate mip dimensions, packed mips, odd Z tile groups, 96bpp rows and array slices with CPU oracle.
- 8/16bpp resolve base phases, x=480 stripe and 4KB crossings.
- GPU upload/resolve/readback at native and scaled resolution with 1x/2x/4x MSAA.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] All expected ranges/bytes match independent fixtures and existing layout cases.
- [ ] Golden Axe Beast Rider/title 534307D5 cases recorded if locally available; no inferred title passes.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/8

Prerequisites: [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6).

Blocks: [RG-GDK-009 #9](https://github.com/furqanagwan/rexglue-sdk/issues/9).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
