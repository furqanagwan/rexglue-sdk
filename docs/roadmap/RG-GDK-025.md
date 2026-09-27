# Title

RG-GDK-025 — Complete release documentation and enforce migration acceptance gates

## Planning ID

RG-GDK-025

## Labels

documentation, testing, architecture, blocked

## Objective

Publish accurate build/deployment/support docs and a release evidence manifest.

## Background

The planning README distinguishes destination from current implementation. It must be revised as milestones actually pass.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/furqanagwan/rexglue-sdk

Status and source assessment: The planning README distinguishes destination from current implementation. It must be revised as milestones actually pass. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Update requirements/build/run/GDK/troubleshooting/support tables from executed commands.
- Publish vendor/compatibility results with exact versions and limitations.
- Verify clean agent handoff using README, AGENTS and assigned issue only.
- Ensure all architecture ADRs and provenance/regression indices reflect shipped code.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `README.md`
- `AGENTS.md`
- `CONTRIBUTING.md`
- `docs`
- `.github/workflows`

## Tasks

- [ ] Update requirements/build/run/GDK/troubleshooting/support tables from executed commands.
- [ ] Publish vendor/compatibility results with exact versions and limitations.
- [ ] Verify clean agent handoff using README, AGENTS and assigned issue only.
- [ ] Ensure all architecture ADRs and provenance/regression indices reflect shipped code.

## Dependencies

Depends on: RG-GDK-022
Depends on: RG-GDK-023
Depends on: RG-GDK-024

## Blocks

Blocks: no initial implementation issue

## Regression Risk

Stale commands or unsupported claims can produce unreproducible releases and incorrect agent handoffs. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Fresh checkout developer follows documented setup and builds/tests/runs sample.
- Roadmap/dependency/link validation and no untested support claims.
- Release reviewer checks all major migration regression evidence and rollback notes.

## Vendor Validation

AMD, NVIDIA and Intel: run the affected fixture on real hardware, record model/driver/capabilities and RTV/ROV path. Separate Intel Arc/non-Arc. Unavailable hardware stays blocked; WARP is supplementary. Compare ordinary Windows and intended GDK deployment when available.

## Acceptance Criteria

- [ ] Every supported configuration has linked actual evidence.
- [ ] No unresolved required gate is hidden by issue closure or release wording.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/25

Prerequisites: [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22), [RG-GDK-023 #23](https://github.com/furqanagwan/rexglue-sdk/issues/23), [RG-GDK-024 #24](https://github.com/furqanagwan/rexglue-sdk/issues/24).

Blocks: no initial implementation issue.

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
