# Title

RG-GDK-022 — Integrate Gaming Runtime and per-title PC packaging

## Planning ID

RG-GDK-022

## Labels

gdk, windows, build, migration, blocked

## Objective

Provide a documented application-owned Gaming Runtime and MicrosoftGame.config deployment flow.

## Background

SDK has no established GDK integration. Guest XAM profiles are not host service identities. Packaging requires real title-project identity.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://learn.microsoft.com/en-us/gaming/gdk/docs/reference/system/xgameruntimeinit/xgameruntimeinit_members?view=gdk-2604
- https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/game-config/microsoftgameconfig-overview

Status and source assessment: SDK has no established GDK integration. Guest XAM profiles are not host service identities. Packaging requires real title-project identity. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Add title template initialize/uninitialize and error reporting for missing/mismatched runtime.
- Generate PC MicrosoftGame.config from supplied identity, with no invented service IDs.
- Document package/build/install/launch/uninstall using pinned supported tools.
- Keep MSIXVC2/ARM64 previews outside initial stable gate.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/rexglue/commands/init_command.cpp`
- `resources`
- `cmake/rexglue_install.cmake`
- `cmake/rexglueConfig.cmake.in`

## Tasks

- [ ] Add title template initialize/uninitialize and error reporting for missing/mismatched runtime.
- [ ] Generate PC MicrosoftGame.config from supplied identity, with no invented service IDs.
- [ ] Document package/build/install/launch/uninstall using pinned supported tools.
- [ ] Keep MSIXVC2/ARM64 previews outside initial stable gate.

## Dependencies

Depends on: RG-GDK-002
Depends on: RG-GDK-017
Depends on: RG-GDK-019
Depends on: RG-GDK-020
Depends on: RG-GDK-021

## Blocks

Blocks: RG-GDK-023
Blocks: RG-GDK-025

## Regression Risk

Runtime identity/lifecycle/packaging mistakes can prevent launch or break shutdown and saved-data access under GDK deployment. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Minimal static title app packaged and unpackaged launch; missing DLL/config/mismatched identity errors.
- Shutdown ordering with audio/input/GPU callbacks; saved-data persistence across reinstall policy.
- Clean machine/package dependency verification.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] Exact pinned GDK deployment commands and successful smoke artifacts are published.
- [ ] Guest compatibility state stays separate from optional host account/cloud services.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/22

Prerequisites: [RG-GDK-002 #2](https://github.com/furqanagwan/rexglue-sdk/issues/2), [RG-GDK-017 #17](https://github.com/furqanagwan/rexglue-sdk/issues/17), [RG-GDK-019 #19](https://github.com/furqanagwan/rexglue-sdk/issues/19), [RG-GDK-020 #20](https://github.com/furqanagwan/rexglue-sdk/issues/20), [RG-GDK-021 #21](https://github.com/furqanagwan/rexglue-sdk/issues/21).

Blocks: [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23), [RG-GDK-025 #25](https://github.com/furqanagwan/rexglue-sdk/issues/25).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
