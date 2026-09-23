# Title

RG-GDK-015 — Specify static-runtime timing, waits, teardown and exception behavior

## Planning ID

RG-GDK-015

## Labels

xboxkrnl, windows, regression, research, blocked

## Objective

Define safe timing and lifecycle changes without importing Edge guest scheduling.

## Background

Edge #234/#233 show scheduler regressions; #251 changes Sleep(0) with no x64 validation. Canary #1025 teardown and #872 timer behavior are relevant but architecture differs.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/issues/234
- https://github.com/has207/xenia-edge/issues/233
- https://github.com/has207/xenia-edge/pull/251
- https://github.com/xenia-canary/xenia-canary/pull/1025
- https://github.com/xenia-canary/xenia-canary/issues/872
- https://github.com/has207/xenia-edge/issues/268

Status and source assessment: Edge #234/#233 show scheduler regressions; #251 changes Sleep(0) with no x64 validation. Canary #1025 teardown and #872 timer behavior are relevant but architecture differs. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Document callback, APC, wait and generated-function lifetime/unwind contracts.
- Measure timer resolution and zero-time waits without adding global sleeps.
- Evaluate teardown fixes against registered modules; reject JIT stackpoint/safepoint machinery.
- Keep #251 watch gated on x64/local evidence.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/system/xthread.cpp`
- `src/system/function_dispatcher.cpp`
- `include/rex/system/xexception.h`
- `src/core/threading_win.cpp`
- `src/core/exception_handler_win.cpp`

## Tasks

- [ ] Document callback, APC, wait and generated-function lifetime/unwind contracts.
- [ ] Measure timer resolution and zero-time waits without adding global sleeps.
- [ ] Evaluate teardown fixes against registered modules; reject JIT stackpoint/safepoint machinery.
- [ ] Keep #251 watch gated on x64/local evidence.

## Dependencies

Depends on: RG-GDK-001
Depends on: RG-GDK-014

## Blocks

Blocks: RG-GDK-016
Blocks: RG-GDK-017
Blocks: RG-GDK-018

## Regression Risk

Wait/teardown/exception changes can hang compiled guest threads or invoke callbacks into unloaded modules. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Wait timeouts, alertable APC delivery, cancel/terminate, nested callbacks and unwind cleanup.
- Repeated module transition/shutdown under contention with watchdog.
- NFS Shift/Riddick scene loads if compiled fixtures available.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] No indefinite wait or callback into unloaded generated code in stress fixtures.
- [ ] Timer flags have measured effect matching documented contract; no scheduler transplant.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/15

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1), [RG-GDK-014 #14](https://github.com/furqanagwan/rexglue-sdk/issues/14).

Blocks: [RG-GDK-016 #16](https://github.com/furqanagwan/rexglue-sdk/issues/16), [RG-GDK-017 #17](https://github.com/furqanagwan/rexglue-sdk/issues/17), [RG-GDK-018 #18](https://github.com/furqanagwan/rexglue-sdk/issues/18).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
