# Title

RG-GDK-014 — Modernize guest object headers and kernel lifetime contracts

## Planning ID

RG-GDK-014

## Labels

xboxkrnl, compatibility, regression, research, blocked

## Objective

Align guest dispatcher objects with host state while preserving static runtime ownership.

## Background

Canary #1227 synchronizes headers; #1225 signature lifetime remains disputed. Local object_table tests exist and should anchor adaptation.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1227
- https://github.com/xenia-canary/xenia-canary/pull/1225
- https://github.com/xenia-canary/xenia-canary/issues/754

Status and source assessment: Canary #1227 synchronizes headers; #1225 signature lifetime remains disputed. Local object_table tests exist and should anchor adaptation. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Map header bytes, handles, native pointer signatures and reference ownership.
- Adapt confirmed header synchronization behavior; isolate pending signature proposal until root cause verified.
- Intersect missing export aggregate with actual compiled-title needs; no success-only stubs.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/system/xobject.cpp`
- `src/system/xevent.cpp`
- `src/system/xsemaphore.cpp`
- `src/system/xthread.cpp`
- `tests/unit/kernel/object_table_test.cpp`

## Tasks

- [ ] Map header bytes, handles, native pointer signatures and reference ownership.
- [ ] Adapt confirmed header synchronization behavior; isolate pending signature proposal until root cause verified.
- [ ] Intersect missing export aggregate with actual compiled-title needs; no success-only stubs.

## Dependencies

Depends on: RG-GDK-001

## Blocks

Blocks: RG-GDK-015
Blocks: RG-GDK-017
Blocks: RG-GDK-018

## Regression Risk

Incorrect header synchronization/handle reuse can close live files, lose wakeups or free objects still in use. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Handle reuse, object destruction/recreation at same guest address, manual/auto events and semaphore counts.
- Concurrent wait/signal/reset/pulse, invalid handles and teardown.
- Guitar Hero 5 DLC signature reproducer or synthetic equivalent.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Guest and host states agree under repeatable concurrency tests.
- [ ] Pending ownership semantics are resolved or remain blocked; no JIT teardown imported.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/14

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1).

Blocks: [RG-GDK-015 #15](https://github.com/furqanagwan/rexglue-sdk/issues/15), [RG-GDK-017 #17](https://github.com/furqanagwan/rexglue-sdk/issues/17), [RG-GDK-018 #18](https://github.com/furqanagwan/rexglue-sdk/issues/18).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
