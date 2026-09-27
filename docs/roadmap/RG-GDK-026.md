# Title

RG-GDK-026 — Maintain Canary and Edge upstream watches and regression provenance

## Planning ID

RG-GDK-026

## Labels

upstream-sync, research, regression, blocked

## Objective

Establish a repeatable monthly and pre-port review process without automatic code merging.

## Background

Current snapshot indexes all open items; selected pending/rejected work must be rechecked. Edge/Canary regularly backport each other, so SHA-only uniqueness is insufficient.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/issues/773
- https://github.com/has207/xenia-edge/issues/234
- https://github.com/xenia-canary/xenia-canary/pull/1111
- https://github.com/xenia-canary/xenia-canary/pull/1225
- https://github.com/xenia-canary/xenia-canary/pull/1077
- https://github.com/has207/xenia-edge/pull/251

Status and source assessment: Current snapshot indexes all open items; selected pending/rejected work must be rechecked. Edge/Canary regularly backport each other, so SHA-only uniqueness is insufficient. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Assign maintainer and record next review date; fetch refs and compare patch equivalence.
- Review new/updated commits, PRs, issues and relevant closed items for target subsystems and vendors.
- Update existing mapped issue rather than duplicate every upstream report.
- Record provenance, rejected ideas, unblock events and regression-test obligations; never auto-merge.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `docs/upstream-tracking.md`
- `docs/upstream-review.md`
- `docs/upstream-snapshot.json`
- `docs/roadmap.md`

## Tasks

- [ ] Assign maintainer and record next review date; fetch refs and compare patch equivalence.
- [ ] Review new/updated commits, PRs, issues and relevant closed items for target subsystems and vendors.
- [ ] Update existing mapped issue rather than duplicate every upstream report.
- [ ] Record provenance, rejected ideas, unblock events and regression-test obligations; never auto-merge.

## Dependencies

Depends on: RG-GDK-001

## Blocks

Blocks: no initial implementation issue

## Regression Risk

Stale status or duplicate/cherry-picked evidence can promote rejected code or miss a regression follow-up. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Trial review detects a pending→merged, rejected and regression-follow-up example.
- Verify every accepted port has source SHA, scope, adaptation and tests; unknown stays unknown.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Owner/cadence/query procedure and first completed review snapshot are documented.
- [ ] Watch entries only unblock on settled semantics plus local repro/test evidence; upstream merge alone is insufficient.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/26

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1).

Blocks: no initial implementation issue.

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
