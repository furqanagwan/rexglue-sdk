# Title

RG-GDK-004 — Fix heap range ceilings and audit physical alignment semantics

## Planning ID

RG-GDK-004

## Labels

compatibility, testing, upstream-sync, research, blocked

## Objective

Keep allocations inside guest-requested windows and define physical versus host alignment.

## Background

Local BaseHeap::AllocRange rounds high_address up. Canary #1215 corrects this; Rejected (closed unmerged) #1202 and pending #1182 address different alignment rules and cannot be combined by title alone.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/pull/1215
- https://github.com/xenia-canary/xenia-canary/pull/1202
- https://github.com/xenia-canary/xenia-canary/pull/1182
- https://github.com/xenia-canary/xenia-canary/pull/1180

Status and source assessment: Local BaseHeap::AllocRange rounds high_address up. Canary #1215 corrects this; Rejected (closed unmerged) #1202 and pending #1182 address different alignment rules and cannot be combined by title alone. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Port #1215 ceiling logic with local page arithmetic/overflow review.
- Evaluate #1202 and #1182 against local host_address_offset and MmGetPhysicalAddress; document adopted/rejected semantics.
- Avoid importing XPS #1180 or changing all heap mapping rules in the same patch.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/system/xmemory.cpp`
- `include/rex/system/xmemory.h`
- `tests/unit/memory/heap_allocation_test.cpp`

## Tasks

- [ ] Port #1215 ceiling logic with local page arithmetic/overflow review.
- [ ] Evaluate #1202 and #1182 against local host_address_offset and MmGetPhysicalAddress; document adopted/rejected semantics.
- [ ] Avoid importing XPS #1180 or changing all heap mapping rules in the same patch.

## Dependencies

Depends on: RG-GDK-001

## Blocks

Blocks: RG-GDK-011
Blocks: RG-GDK-016

## Regression Risk

Range arithmetic or alignment changes may overlap allocations, escape the requested ceiling or corrupt aliased physical heaps. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Review explicitly warns that AllocFixed has different semantics; use Far Cry 3 or an equivalent physical-heap workload as a regression control for any alignment changes.
- Exact-fit range, unaligned ceiling, UINT32_MAX edge, top-down/bottom-up and exhaustion tests.
- Physical aliases E0000000 and other page-size heaps with 4K/32K/64K alignment; verify both physical and translated host addresses.
- Existing allocation/free/protect regressions and GPU memexport pressure control.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Every returned allocation lies fully inside the requested window without overflow.
- [ ] Pending alignment proposal is explicitly accepted with evidence or remains a watch; no untested global alignment relaxation.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/4

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1).

Blocks: [RG-GDK-011 #11](https://github.com/furqanagwan/rexglue-sdk/issues/11), [RG-GDK-016 #16](https://github.com/furqanagwan/rexglue-sdk/issues/16).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
