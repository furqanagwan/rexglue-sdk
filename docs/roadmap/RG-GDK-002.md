# Title

RG-GDK-002 — Pin and prove the April 2026 GDK PC toolchain

## Planning ID

RG-GDK-002

## Labels

gdk, windows, build, research, blocked

## Objective

Prove an exact April 2026 PC GDK/Windows SDK/Clang toolchain without altering PPC generation.

## Background

Current CMake enforces Clang >=18/C++23. Installed 260404 and VS Community do not prove a Microsoft-supported toolchain pairing; public announcement names VS 2026 Professional/Enterprise.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://learn.microsoft.com/en-us/gaming/gdk/docs/gdk-dev/whatsnew/release-notes?view=gdk-2604
- https://developer.microsoft.com/en-us/games/articles/2026/04/april-2026-microsoft-gdk-update/

Status and source assessment: Current CMake enforces Clang >=18/C++23. Installed 260404 and VS Community do not prove a Microsoft-supported toolchain pairing; public announcement names VS 2026 Professional/Enterprise. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Record exact 2604 update, redistributables, Windows SDK and supported VS edition.
- Build a minimal application linking the installed SDK/runtime with the chosen compiler; verify exception/CRT/plugin ABI.
- Add a GDK preset and documented setup only after the probe passes; keep standard Windows developer builds reproducible.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `CMakeLists.txt`
- `CMakePresets.json`
- `cmake/rexglueConfig.cmake.in`
- `.github/workflows/_build-platform.yaml`

## Tasks

- [ ] Record exact 2604 update, redistributables, Windows SDK and supported VS edition.
- [ ] Build a minimal application linking the installed SDK/runtime with the chosen compiler; verify exception/CRT/plugin ABI.
- [ ] Add a GDK preset and documented setup only after the probe passes; keep standard Windows developer builds reproducible.

## Dependencies

Depends on: RG-GDK-001

## Blocks

Blocks: RG-GDK-019
Blocks: RG-GDK-020
Blocks: RG-GDK-021
Blocks: RG-GDK-022

## Regression Risk

Compiler/CRT/plugin ABI mismatch may break guest callbacks, generated C++ or installed consumers even when SDK compilation succeeds. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Clean Debug/Release configure/build/install and external consumer compile.
- Negative missing/wrong GDK selection must fail with actionable diagnostics.
- Run PPC/ABI tests under the pinned toolchain.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Tool versions and redistributable provenance are pinned without copying SDK payloads.
- [ ] Clean-machine consumer build and tests pass using documented commands.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/2

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1).

Blocks: [RG-GDK-019 #19](https://github.com/furqanagwan/rexglue-sdk/issues/19), [RG-GDK-020 #20](https://github.com/furqanagwan/rexglue-sdk/issues/20), [RG-GDK-021 #21](https://github.com/furqanagwan/rexglue-sdk/issues/21), [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
