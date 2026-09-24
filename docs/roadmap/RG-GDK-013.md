# Title

RG-GDK-013 — Design a narrow title compatibility profile mechanism

## Planning ID

RG-GDK-013

## Labels

architecture, game-specific, compatibility, research, blocked

## Objective

Decide whether an explicit title/module profile system is necessary and specify it before implementation.

## Background

Canary/Edge use title configs and hash-filtered patches. PR #844 shows global config contamination risk; runtime PPC patches do not modify generated C++.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/844
- https://github.com/has207/xenia-edge/pull/275
- https://github.com/has207/xenia-edge/pull/160

Status and source assessment: Canary/Edge use title configs and hash-filtered patches. PR #844 shows global config contamination risk; runtime PPC patches do not modify generated C++. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Inventory actual needed overrides from local reproductions; reject unnecessary database complexity.
- Specify title ID/module hash/version, provenance, scope, disable switch, conflict rules and effective logging.
- Separate pre-codegen guest patches from runtime behavior profiles.
- Produce schema/decision and negative test plan; do not implement runtime feature in this issue.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/codegen/manifest.cpp`
- `include/rex/codegen/manifest.h`
- `src/system/runtime.cpp`
- `src/core/cvar.cpp`
- `docs/adr/ADR-005-game-specific-compatibility-policy.md`

## Tasks

- [ ] Inventory actual needed overrides from local reproductions; reject unnecessary database complexity.
- [ ] Specify title ID/module hash/version, provenance, scope, disable switch, conflict rules and effective logging.
- [ ] Separate pre-codegen guest patches from runtime behavior profiles.
- [ ] Produce schema/decision and negative test plan; do not implement runtime feature in this issue.

## Dependencies

Depends on: RG-GDK-001
Depends on: RG-GDK-012

## Blocks

Blocks: RG-GDK-016

## Regression Risk

A profile can match the wrong executable version, leak into global defaults or patch guest bytes without regenerating native code. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Design examples cover unknown key/hash, conflict, title transition and global-config persistence.
- Demonstrate how each proposed rule can be disabled and removed.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Reviewed design says whether a database is needed and why.
- [ ] Each proposed behavior is traceable/testable and cannot silently change unrelated titles.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/13

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1), [RG-GDK-012 #12](https://github.com/furqanagwan/rexglue-sdk/issues/12).

Blocks: [RG-GDK-016 #16](https://github.com/furqanagwan/rexglue-sdk/issues/16).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
