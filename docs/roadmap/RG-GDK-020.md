# Title

RG-GDK-020 — Implement GameInput while preserving guest device assignment

## Planning ID

RG-GDK-020

## Labels

input, windows, gdk, compatibility, blocked

## Objective

Add a native GameInput adapter with stable Xbox 360-facing semantics.

## Background

Local drivers include SDL/XInput/mouse-keyboard and device assignment tests. Canary #1230 illustrates subtype and whammy-neutral hazards.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1230
- https://learn.microsoft.com/en-us/xbox/gdk/docs/features/common/input/overviews/input-overview?view=gdk-2604

Status and source assessment: Local drivers include SDL/XInput/mouse-keyboard and device assignment tests. Canary #1230 illustrates subtype and whammy-neutral hazards. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Pin GameInput package/runtime deployment and implement existing driver interface.
- Preserve slots, packet numbers, rumble, deadzones, subtype and focus.
- Test XInput comparison path and mouse-keyboard merge before default switch.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/input/CMakeLists.txt`
- `src/input/input_system.cpp`
- `src/input/device_assignment.cpp`
- `src/input/state_merge.cpp`
- `tests/unit/input/input_assignment_test.cpp`

## Tasks

- [ ] Pin GameInput package/runtime deployment and implement existing driver interface.
- [ ] Preserve slots, packet numbers, rumble, deadzones, subtype and focus.
- [ ] Test XInput comparison path and mouse-keyboard merge before default switch.

## Dependencies

Depends on: RG-GDK-001
Depends on: RG-GDK-002

## Blocks

Blocks: RG-GDK-022
Blocks: RG-GDK-024

## Regression Risk

Device reassignment/subtype conversion can disconnect players, hold whammy input or leave rumble active after removal. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Four devices, disconnect/reconnect same/different device, slot persistence and no phantom input.
- Guitar neutral/whammy/subtype, rumble stop on removal and focus loss.
- Windows/GDK package with missing runtime diagnostic.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Existing assignment tests plus new host integration matrix pass.
- [ ] No dependency removal until all replaced input behavior has parity.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/20

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1), [RG-GDK-002 #2](https://github.com/furqanagwan/rexglue-sdk/issues/2).

Blocks: [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22), [RG-GDK-024 #24](https://github.com/furqanagwan/rexglue-sdk/issues/24).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
