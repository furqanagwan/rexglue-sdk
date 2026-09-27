# Title

RG-GDK-024 — Retire Linux and macOS build, platform and distribution paths

## Planning ID

RG-GDK-024

## Labels

cleanup, windows, migration, build, blocked

## Objective

Make Windows the only supported host after native replacement parity.

## Background

Root CMake/presets/workflows include Linux/macOS and shared POSIX files; SDL and guest abstractions cannot be deleted indiscriminately.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/rexglue/rexglue-sdk/blob/c94f5ebdcb3c9d1a460ca48e04f9758448f8d518/CMakePresets.json

Status and source assessment: Root CMake/presets/workflows include Linux/macOS and shared POSIX files; SDL and guest abstractions cannot be deleted indiscriminately. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Remove Linux presets/workflows/platform sources and packaging once Windows equivalents pass.
- Remove Apple Objective-C/Metal-surface/MoltenVK/presets/workflows and install assets.
- Audit shared POSIX/SDL code consumers and exported headers; preserve guest abstractions.
- Add explicit unsupported-host configure diagnostic and update generated title templates.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `CMakeLists.txt`
- `CMakePresets.json`
- `src/core/CMakeLists.txt`
- `src/ui/CMakeLists.txt`
- `.github/workflows/_build-platform.yaml`
- `.github/workflows/nightly.yaml`
- `cmake/rexglue_install.cmake`
- `resources`

## Tasks

- [ ] Remove Linux presets/workflows/platform sources and packaging once Windows equivalents pass.
- [ ] Remove Apple Objective-C/Metal-surface/MoltenVK/presets/workflows and install assets.
- [ ] Audit shared POSIX/SDL code consumers and exported headers; preserve guest abstractions.
- [ ] Add explicit unsupported-host configure diagnostic and update generated title templates.

## Dependencies

Depends on: RG-GDK-019
Depends on: RG-GDK-020
Depends on: RG-GDK-021
Depends on: RG-GDK-023

## Blocks

Blocks: RG-GDK-025

## Regression Risk

Deleting shared host abstractions can break Windows Unicode paths, exception handling, audio, input or generated title projects. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Fresh Windows SDK build/install and external title project compile from generated template.
- No Linux/macOS CI/distribution artifacts remain; unsupported host rejected clearly.
- Full baseline regression after cleanup, including paths/Unicode/exceptions/window/audio/input.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Windows-only host policy reflected in source selection, templates, packaging and docs.
- [ ] No compatibility behavior removed merely because an abstraction was cross-platform.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/24

Prerequisites: [RG-GDK-019 #19](https://github.com/furqanagwan/rexglue-sdk/issues/19), [RG-GDK-020 #20](https://github.com/furqanagwan/rexglue-sdk/issues/20), [RG-GDK-021 #21](https://github.com/furqanagwan/rexglue-sdk/issues/21), [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23).

Blocks: [RG-GDK-025 #25](https://github.com/furqanagwan/rexglue-sdk/issues/25).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
