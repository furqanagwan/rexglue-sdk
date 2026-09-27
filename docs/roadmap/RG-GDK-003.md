# Title

RG-GDK-003 — Correct NtOpenFile ShareAccess and OpenOptions argument mapping

## Planning ID

RG-GDK-003

## Labels

xboxkrnl, compatibility, testing, upstream-sync, blocked

## Objective

Restore the six-argument guest import ABI and forward ShareAccess to NtCreateFile.

## Background

Local NtOpenFile_entry at xboxkrnl_io.cpp:179 has five arguments. Edge 887beea69 inserts ShareAccess and reads OpenOptions from argument six; commit reports Dead Rising disc-error fix.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/commit/887beea6979fc1ee8580deb755d771c61e0039ad

Status and source assessment: Local NtOpenFile_entry at xboxkrnl_io.cpp:179 has five arguments. Edge 887beea69 inserts ShareAccess and reads OpenOptions from argument six; commit reports Dead Rising disc-error fix. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Adapt the typed signature to include ShareAccess before OpenOptions and forward both.
- Add a guest-register import fixture with deliberately distinct r7/r8 values.
- Preserve path, status and async/nonbuffered flags; retain source attribution.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/kernel/xboxkrnl/xboxkrnl_io.cpp`
- `tests/unit/ppc/import_function_test.cpp`
- `tests/unit/CMakeLists.txt`

## Tasks

- [ ] Adapt the typed signature to include ShareAccess before OpenOptions and forward both.
- [ ] Add a guest-register import fixture with deliberately distinct r7/r8 values.
- [ ] Preserve path, status and async/nonbuffered flags; retain source attribution.

## Dependencies

Depends on: RG-GDK-001

## Blocks

Blocks: RG-GDK-017

## Regression Risk

Changing argument positions can alter sharing/open flags and break previously tolerated IO; preserve guest error/overlapped behavior. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Use different ShareAccess/OpenOptions bit patterns to prove neither is shifted or ignored.
- Exercise success, missing path and invalid handle/status propagation; verify existing import_function tests.
- Run Dead Rising load sequence if a compiled lawful fixture exists; otherwise keep title result not-run.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Register-level regression fails on baseline and passes after fix.
- [ ] No changes to unrelated imports or dispatcher/JIT architecture.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/3

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1).

Blocks: [RG-GDK-017 #17](https://github.com/furqanagwan/rexglue-sdk/issues/17).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
