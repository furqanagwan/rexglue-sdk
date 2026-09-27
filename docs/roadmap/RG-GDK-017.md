# Title

RG-GDK-017 — Implement content persistence and audit XAM profiles, notifications and XEX transitions

## Planning ID

RG-GDK-017

## Labels

xam, compatibility, regression, upstream-sync, blocked

## Objective

Preserve guest content/profile state and correct missing flush/lookup behavior.

## Background

Local XamContentFlush only returns success. Canary #1216, pending #1226/#1109, profile reports and closed-unmerged #1135 expose distinct contracts.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1216
- https://github.com/xenia-canary/xenia-canary/pull/1226
- https://github.com/xenia-canary/xenia-canary/pull/1109
- https://github.com/xenia-canary/xenia-canary/pull/981
- https://github.com/xenia-canary/xenia-canary/issues/5
- https://github.com/xenia-canary/xenia-canary/issues/1220
- https://github.com/xenia-canary/xenia-canary/pull/1135

Status and source assessment: Local XamContentFlush only returns success. Canary #1216, pending #1226/#1109, profile reports and closed-unmerged #1135 expose distinct contracts. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Implement real flush for local package model, propagate errors and overlapped completion.
- Validate STFS extents and mixed-case path behavior with synthetic malformed containers.
- Audit concurrent profiles and crash persistence for multiple users.
- Specify notification masks/order and compiled module relaunch; no automatic GDK identity substitution.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/kernel/xam/xam_content.cpp`
- `src/system/xam/content_manager.cpp`
- `src/system/xam/user_profile.cpp`
- `src/kernel/xam/xam_notify.cpp`
- `src/system/xex_module.cpp`
- `src/filesystem/devices/stfs_container_device.cpp`

## Tasks

- [ ] Implement real flush for local package model, propagate errors and overlapped completion.
- [ ] Validate STFS extents and mixed-case path behavior with synthetic malformed containers.
- [ ] Audit concurrent profiles and crash persistence for multiple users.
- [ ] Specify notification masks/order and compiled module relaunch; no automatic GDK identity substitution.

## Dependencies

Depends on: RG-GDK-003
Depends on: RG-GDK-014
Depends on: RG-GDK-015

## Blocks

Blocks: RG-GDK-022

## Regression Risk

Flush/profile/content changes can lose saves, expose malformed package OOB reads or deliver notifications in the wrong order. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Flush failure/success, restart and injected crash using disposable save copies.
- Truncated/malformed package rejected without OOB reads; directory-backed payload and case collision tests.
- Two users, concurrent update/logout, listener filter/initial state and unknown precompiled module error.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Success reflects completed persistence contract; failures return correct guest status.
- [ ] No lost control save or title override leaking across launches.
- [ ] XMP initial state proposal adopted only with evidence, otherwise left as watch.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/17

Prerequisites: [RG-GDK-003 #3](https://github.com/furqanagwan/rexglue-sdk/issues/3), [RG-GDK-014 #14](https://github.com/furqanagwan/rexglue-sdk/issues/14), [RG-GDK-015 #15](https://github.com/furqanagwan/rexglue-sdk/issues/15).

Blocks: [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
