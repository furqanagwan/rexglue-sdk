# Title

RG-GDK-023 — Remove Vulkan backend and obsolete graphics dependencies after parity

## Planning ID

RG-GDK-023

## Labels

cleanup, gpu, d3d12, migration, blocked

## Objective

Finish the D3D12-only host architecture after all replacement gates pass.

## Background

Vulkan is currently optional/off on Windows, present in graphics/UI/build/install trees. SPIR-V may be compiler IR depending on RG-GDK-007; distinguish it from Vulkan runtime.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/commit/c00e7aead
- https://github.com/rexglue/rexglue-sdk/blob/c94f5ebdcb3c9d1a460ca48e04f9758448f8d518/thirdparty/CMakeLists.txt

Status and source assessment: Vulkan is currently optional/off on Windows, present in graphics/UI/build/install trees. SPIR-V may be compiler IR depending on RG-GDK-007; distinguish it from Vulkan runtime. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Audit dependency/link/deploy graph against chosen shader architecture.
- Remove Vulkan backend selection/source/public exports and unused Vulkan-only libraries/assets.
- Update generated consumer templates, docs, install exports and CI; simplify only verified-dead abstractions.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `CMakeLists.txt`
- `src/graphics/CMakeLists.txt`
- `src/ui/CMakeLists.txt`
- `src/graphics/vulkan`
- `src/ui/vulkan`
- `include/rex/graphics/vulkan`
- `include/rex/ui/vulkan`
- `thirdparty/CMakeLists.txt`
- `.gitmodules`
- `cmake/rexglue_vulkan_stack.cmake`
- `cmake/rexglue_install.cmake`

## Tasks

- [ ] Audit dependency/link/deploy graph against chosen shader architecture.
- [ ] Remove Vulkan backend selection/source/public exports and unused Vulkan-only libraries/assets.
- [ ] Update generated consumer templates, docs, install exports and CI; simplify only verified-dead abstractions.

## Dependencies

Depends on: RG-GDK-007
Depends on: RG-GDK-009
Depends on: RG-GDK-010
Depends on: RG-GDK-011
Depends on: RG-GDK-012
Depends on: RG-GDK-022

## Blocks

Blocks: RG-GDK-024
Blocks: RG-GDK-025

## Regression Risk

Premature graphics dependency removal can break transfer shader generation, consumer installation or a previously working D3D12 path. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Clean build/install/external consumer without Vulkan SDK/loader.
- Audit import tables and package contents for Vulkan loader/backend dependencies.
- Full GPU regression/vendor suite before and after removal.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] D3D12 is the only selectable/rendering backend.
- [ ] No live Vulkan dependency remains; any retained SPIR-V tool has documented shader-only consumer.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/23

Prerequisites: [RG-GDK-007 #7](https://github.com/furqanagwan/rexglue-sdk/issues/7), [RG-GDK-009 #9](https://github.com/furqanagwan/rexglue-sdk/issues/9), [RG-GDK-010 #10](https://github.com/furqanagwan/rexglue-sdk/issues/10), [RG-GDK-011 #11](https://github.com/furqanagwan/rexglue-sdk/issues/11), [RG-GDK-012 #12](https://github.com/furqanagwan/rexglue-sdk/issues/12), [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22).

Blocks: [RG-GDK-024 #24](https://github.com/furqanagwan/rexglue-sdk/issues/24), [RG-GDK-025 #25](https://github.com/furqanagwan/rexglue-sdk/issues/25).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
