# Title

RG-GDK-019 — Add and validate a native XAudio2 PCM output driver

## Planning ID

RG-GDK-019

## Labels

audio, windows, gdk, migration, blocked

## Objective

Replace the Windows SDL audio sink only after XAudio2 output parity is demonstrated.

## Background

Current CMake always builds SDL output plus FFmpeg XMA. Host output replacement must not remove guest XMA state or callbacks.

## Architecture Context

Windows PC / April 2026 GDK / D3D12-only destination. Preserve static PPC-to-C++ compilation, registered guest function dispatch, guest ABI and GPU plugin boundary. Edge is a reference fork, not a runtime dependency. Current baseline: c94f5ebdcb3c9d1a460ca48e04f9758448f8d518.

## Upstream Evidence

- https://github.com/xenia-canary/xenia-canary/issues/600
- https://github.com/xenia-canary/xenia-canary/issues/739
- https://learn.microsoft.com/en-us/windows/win32/xaudio2/xaudio2-introduction

Status and source assessment: Current CMake always builds SDL output plus FFmpeg XMA. Host output replacement must not remove guest XMA state or callbacks. Review the live upstream status again before implementation; closed does not imply merged.

## Scope

- Implement XAudio2 driver behind existing interface with explicit queue and callback lifetime.
- Preserve PCM endian/channel/rate conversion and guest pacing.
- Handle no device, device replacement and shutdown; switch default only after baseline parity.

## Out of Scope

Unrelated subsystem replacement; CPU JIT; upstream repository mutations; unvalidated global title hacks; compatibility claims without runs. No game/SDK payload distribution.

## Relevant Files

- `src/audio/CMakeLists.txt`
- `src/audio/audio_system.cpp`
- `src/audio/sdl`
- `include/rex/audio`

## Tasks

- [ ] Implement XAudio2 driver behind existing interface with explicit queue and callback lifetime.
- [ ] Preserve PCM endian/channel/rate conversion and guest pacing.
- [ ] Handle no device, device replacement and shutdown; switch default only after baseline parity.

## Dependencies

Depends on: RG-GDK-002
Depends on: RG-GDK-018

## Blocks

Blocks: RG-GDK-022
Blocks: RG-GDK-024

## Regression Risk

Output replacement can swap channels, introduce underruns/drift or freeze a title when audio hardware disappears. Preserve the last-good baseline, use independently reversible changes and require the tests below before closing.

## Regression Tests

- Stereo/5.1 channel impulse mapping, clipping/rounding and queue underrun/latency.
- Disable/remove/reconnect audio device while title continues; repeated teardown.
- Windows and GDK deployment redistributable smoke.

## Vendor Validation

Not applicable to pure CPU logic; do not claim GPU compatibility.

## Acceptance Criteria

- [ ] Baseline PCM/channel and lifecycle gates pass; no title freeze when device is absent.
- [ ] SDL audio dependency removed only after all Windows audio consumers migrated.

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

This issue: https://github.com/furqanagwan/rexglue-sdk/issues/19

Prerequisites: [RG-GDK-002 #2](https://github.com/furqanagwan/rexglue-sdk/issues/2), [RG-GDK-018 #18](https://github.com/furqanagwan/rexglue-sdk/issues/18).

Blocks: [RG-GDK-022 #22](https://github.com/furqanagwan/rexglue-sdk/issues/22), [RG-GDK-024 #24](https://github.com/furqanagwan/rexglue-sdk/issues/24).

## Documentation handoff

The planning documents are on `docs/windows-gdk-modernization-roadmap` in this fork pending review. Read [README](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/README.md), [AGENTS](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/AGENTS.md), [investigation](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/investigation.md) and [roadmap/index](https://github.com/furqanagwan/rexglue-sdk/blob/docs/windows-gdk-modernization-roadmap/docs/roadmap.md). Do not assume the default branch already contains this documentation.
