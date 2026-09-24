# Title

RG-GDK-016 — Investigate storage completion timing without per-title allocation caps

## Planning ID

RG-GDK-016

## Labels

compatibility, game-specific, research, xboxkrnl, blocked

## Objective

Reproduce timing-sensitive IO and design a bounded guest storage model if needed.

## Background

Edge #275 allocation cap was rejected; 5e9eae601 models per-device timing using its scheduler and e987fd7f5 refines sequential seeks.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/pull/275
- https://github.com/has207/xenia-edge/commit/5e9eae601b16757e49eeb83ab0f4d2945809f401
- https://github.com/has207/xenia-edge/commit/e987fd7f5
- https://github.com/microsoft/DirectStorage

Status and source assessment: Edge #275 allocation cap was rejected; 5e9eae601 models per-device timing using its scheduler and e987fd7f5 refines sequential seeks. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Reproduce UEFA allocation pressure with recorded read/completion timeline.
- Separate host IO acceleration from guest completion timing.
- Design per-device model compatible with static threads/async callbacks; no arbitrary global delay or title allocation cap.
- Assess DirectStorage only after semantics are stable.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/system/xfile.cpp`
- `src/filesystem/device.cpp`
- `src/kernel/xboxkrnl/xboxkrnl_io.cpp`

## Tasks

- [ ] Reproduce UEFA allocation pressure with recorded read/completion timeline.
- [ ] Separate host IO acceleration from guest completion timing.
- [ ] Design per-device model compatible with static threads/async callbacks; no arbitrary global delay or title allocation cap.
- [ ] Assess DirectStorage only after semantics are stable.

## Dependencies

Depends on: RG-GDK-004
Depends on: RG-GDK-013
Depends on: RG-GDK-015

## Blocks

Blocks: no initial implementation issue

## Regression Risk

Artificial IO delays can deadlock lock-held callers, reorder completion, stall unrelated titles or worsen memory pressure. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Sequential/random/synchronous/asynchronous reads; cancellation and lock-held caller behavior.
- Measure physical allocation peak and title progress with/without model, plus unrelated title control.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Root-cause evidence justifies model or explicitly rejects it.
- [ ] Any later implementation has bounded delays, deterministic fixtures and rollback; DirectStorage remains optional.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/16

Prerequisites: [RG-GDK-004 #4](https://github.com/furqanagwan/rexglue-sdk/issues/4), [RG-GDK-013 #13](https://github.com/furqanagwan/rexglue-sdk/issues/13), [RG-GDK-015 #15](https://github.com/furqanagwan/rexglue-sdk/issues/15).

Blocks: no initial implementation issue.

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
