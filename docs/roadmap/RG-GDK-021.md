# Title

RG-GDK-021 — Provide native Windows windowing and complete SDL consumer audit

## Planning ID

RG-GDK-021

## Labels

windows, migration, build, blocked

## Objective

Replace Windows SDL UI consumers where useful and make remaining dependencies explicit.

## Background

SDL owns window/event/dialog paths as well as audio/input. Windows-only cannot be implemented by removing SDL first.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/rexglue/rexglue-sdk/blob/c94f5ebdcb3c9d1a460ca48e04f9758448f8d518/src/ui/CMakeLists.txt

Status and source assessment: SDL owns window/event/dialog paths as well as audio/input. Windows-only cannot be implemented by removing SDL first. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Map every SDL consumer and define native Win32 message/window ownership.
- Implement window/focus/resize/DPI/fullscreen/dialog lifecycle preserving D3D12 HWND presenter.
- Retain any justified dependency until its native replacement is validated.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/ui/CMakeLists.txt`
- `src/ui/window_sdl.cpp`
- `src/ui/windowed_app_main_sdl.cpp`
- `src/ui/surface_win.cpp`
- `src/ui/d3d12/d3d12_presenter.cpp`
- `thirdparty/CMakeLists.txt`

## Tasks

- [ ] Map every SDL consumer and define native Win32 message/window ownership.
- [ ] Implement window/focus/resize/DPI/fullscreen/dialog lifecycle preserving D3D12 HWND presenter.
- [ ] Retain any justified dependency until its native replacement is validated.

## Dependencies

Depends on: RG-GDK-001
Depends on: RG-GDK-002

## Blocks

Blocks: RG-GDK-022
Blocks: RG-GDK-024

## Regression Risk

Native message-pump/window ownership changes can deadlock GPU shutdown or break focus, DPI and text input. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Resize/minimize/restore/DPI, multi-monitor move and clean close during GPU work.
- Keyboard/text/dialog input and title thread/UI handoff without deadlock.
- Installed external title app finds runtime/plugin DLLs.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] UI behavior and D3D12 presentation match baseline; all remaining SDL uses have named owners.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/21

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1), [RG-GDK-002 #2](https://github.com/furqanagwan/rexglue-sdk/issues/2).

Blocks: [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22), [RG-GDK-024 #24](https://github.com/furqanagwan/rexglue-sdk/issues/24).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
