# Title

RG-GDK-018 — Audit XMA packet/loop correctness and audio callback lifetime

## Planning ID

RG-GDK-018

## Labels

audio, compatibility, regression, upstream-sync, blocked

## Objective

Adapt proven later XMA fixes without losing existing ReXGlue decoder behavior.

## Background

ReXGlue already imported new Canary context in a0271ec/30e1c8a. Edge adds loop boundary and split-header fixes; rejected #236 and regressions #164/#120 demonstrate risk.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/has207/xenia-edge/commit/5dd1cdbbf548745a15714c158b15aad128530440
- https://github.com/has207/xenia-edge/commit/adf56b76c
- https://github.com/has207/xenia-edge/pull/236
- https://github.com/has207/xenia-edge/issues/164
- https://github.com/has207/xenia-edge/issues/120
- https://github.com/has207/xenia-edge/issues/113
- https://github.com/xenia-canary/xenia-canary/issues/1214
- https://github.com/xenia-canary/xenia-canary/issues/1036
- https://github.com/xenia-canary/xenia-canary/pull/748

Status and source assessment: ReXGlue already imported new Canary context in a0271ec/30e1c8a. Edge adds loop boundary and split-header fixes; rejected #236 and regressions #164/#120 demonstrate risk. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Diff local decode/consume/StoreContextMerged against selected commits and FFmpeg revision.
- Add packet/loop accounting fixes with author/SHA provenance.
- Audit callback unregister and driver destruction lifetime; local locks differ from Canary #1214.
- Do not emit silence merely to conceal decode errors or adopt scalar-only #748 as universal fix.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/audio/xma_context.cpp`
- `include/rex/audio/xma/context.h`
- `src/audio/xma_decoder.cpp`
- `src/audio/audio_system.cpp`
- `.gitmodules`

## Tasks

- [ ] Diff local decode/consume/StoreContextMerged against selected commits and FFmpeg revision.
- [ ] Add packet/loop accounting fixes with author/SHA provenance.
- [ ] Audit callback unregister and driver destruction lifetime; local locks differ from Canary #1214.
- [ ] Do not emit silence merely to conceal decode errors or adopt scalar-only #748 as universal fix.

## Dependencies

Depends on: RG-GDK-001
Depends on: RG-GDK-014
Depends on: RG-GDK-015

## Blocks

Blocks: RG-GDK-019

## Regression Risk

Packet/loop fixes or callback lifetime changes can mute streams, desynchronize cutscenes or deadlock multi-client teardown. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Split headers, frameless packets, loop_start one bit early/exact, output ring wrap and multistream channels.
- PCM sample/continuity tests and repeated register/process/unregister during teardown.
- Koei, Tekken Tag 2, LEGO LOTR, SCDA and 007 Legends workload results or explicit fixture gaps.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Decoder errors stay observable, progress is correct and no callback uses released guest/driver memory.
- [ ] Known upstream regression scenes are checked before declaring parity; FFmpeg pin documented.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/18

Prerequisites: [RG-GDK-001 #1](https://github.com/furqanagwan/rexglue-sdk/issues/1), [RG-GDK-014 #14](https://github.com/furqanagwan/rexglue-sdk/issues/14), [RG-GDK-015 #15](https://github.com/furqanagwan/rexglue-sdk/issues/15).

Blocks: [RG-GDK-019 #19](https://github.com/furqanagwan/rexglue-sdk/issues/19).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
