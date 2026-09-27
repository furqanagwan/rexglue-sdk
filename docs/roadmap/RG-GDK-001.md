# Title

RG-GDK-001 — Establish a reproducible Windows D3D12 compatibility baseline

## Planning ID

RG-GDK-001

## Labels

testing, build, documentation, agent-ready

## Objective

Create the baseline capture/run workflow and record real current results before subsystem replacement.

## Background

At c94f5ebdcb3c9d1a460ca48e04f9758448f8d518 there are unit/PPC tests but no verified game/vendor baseline. Plain shell misses CRT libraries; VS developer shell configure reaches uninitialized cli11. GPU trace capture was removed in 71782a3.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/issues/278
- https://github.com/xenia-canary/xenia-canary/issues/773
- https://github.com/xenia-canary/xenia-canary/pull/1218
- https://github.com/rexglue/rexglue-sdk/commit/71782a3

Status and source assessment: At c94f5ebdcb3c9d1a460ca48e04f9758448f8d518 there are unit/PPC tests but no verified game/vendor baseline. Plain shell misses CRT libraries; VS developer shell configure reaches uninitialized cli11. GPU trace capture was removed in 71782a3. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Initialize pinned submodules and record compiler/Windows SDK/GDK/build metadata; do not update pins to bypass errors.
- Add a run-record schema and capture helper with pass/fail/blocked/not-run, artifact hashes and explicit missing-material handling.
- Run Debug/Release unit and PPC tests with nonzero CTest discovery; record counts and failures.
- Select available legally supplied title projects and reproducible scenes; record working/partial/failing status and missing API/audio/input evidence.
- Capture current D3D12 screenshots/logs and available hardware results; publish a gap list for unavailable vendor/title runs.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `CMakePresets.json`
- `tests/CMakeLists.txt`
- `tests/unit/CMakeLists.txt`
- `tests/ppc/CMakeLists.txt`
- `cmake/ppc_test_pipeline.cmake`
- `scripts`
- `docs/regression-strategy.md`

## Tasks

- [ ] Initialize pinned submodules and record compiler/Windows SDK/GDK/build metadata; do not update pins to bypass errors.
- [ ] Add a run-record schema and capture helper with pass/fail/blocked/not-run, artifact hashes and explicit missing-material handling.
- [ ] Run Debug/Release unit and PPC tests with nonzero CTest discovery; record counts and failures.
- [ ] Select available legally supplied title projects and reproducible scenes; record working/partial/failing status and missing API/audio/input evidence.
- [ ] Capture current D3D12 screenshots/logs and available hardware results; publish a gap list for unavailable vendor/title runs.

## Dependencies

Depends on: none

## Blocks

Blocks: RG-GDK-002
Blocks: RG-GDK-003
Blocks: RG-GDK-004
Blocks: RG-GDK-005
Blocks: RG-GDK-006
Blocks: RG-GDK-013
Blocks: RG-GDK-014
Blocks: RG-GDK-015
Blocks: RG-GDK-018
Blocks: RG-GDK-020
Blocks: RG-GDK-021
Blocks: RG-GDK-026

## Regression Risk

The recorder could falsely classify skipped/failed runs as passing or overwrite the last-good artifact set. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Validate the helper against missing executable, failed run and missing private game material: none may produce pass.
- Repeat a synthetic fixture and available title scene twice with identical config; compare recorded IDs/hashes and explain nondeterminism.
- Run CTest in Debug and Release; preserve initial failures as baseline defects, not silently ignored successes.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] A versioned baseline manifest includes every required field and points to immutable artifacts.
- [ ] A fresh developer shell can follow documented commands through build and test, or exact external blockers are recorded and this issue stays open.
- [ ] Each representative workload is assigned a fixture/title owner and explicit current result; no unsupported compatibility claims.

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

Ready for baseline tooling implementation now: architecture is fixed, no prerequisites, files and negative tests are defined. Lack of private material blocks a run, not writing the recorder. Baseline capture is not a GPU support certification. Read README.md, AGENTS.md, docs/investigation.md, docs/architecture-plan.md and this issue. Check git status and preserve existing work. Implement in the personal ReXGlue fork only. If an acceptance gate lacks hardware/material, record it as blocked and leave the issue open. Do not mark agent-ready until dependencies and relevant research are complete.

## Live GitHub dependency links

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/1

Prerequisites: none.

Blocks: [RG-GDK-002 #2](https://github.com/furqanagwan/rexglue-sdk/issues/2), [RG-GDK-003 #3](https://github.com/furqanagwan/rexglue-sdk/issues/3), [RG-GDK-004 #4](https://github.com/furqanagwan/rexglue-sdk/issues/4), [RG-GDK-005 #5](https://github.com/furqanagwan/rexglue-sdk/issues/5), [RG-GDK-006 #6](https://github.com/furqanagwan/rexglue-sdk/issues/6), [RG-GDK-013 #13](https://github.com/furqanagwan/rexglue-sdk/issues/13), [RG-GDK-014 #14](https://github.com/furqanagwan/rexglue-sdk/issues/14), [RG-GDK-015 #15](https://github.com/furqanagwan/rexglue-sdk/issues/15), [RG-GDK-018 #18](https://github.com/furqanagwan/rexglue-sdk/issues/18), [RG-GDK-020 #20](https://github.com/furqanagwan/rexglue-sdk/issues/20), [RG-GDK-021 #21](https://github.com/furqanagwan/rexglue-sdk/issues/21), [RG-GDK-026 #26](https://github.com/furqanagwan/rexglue-sdk/issues/26).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
