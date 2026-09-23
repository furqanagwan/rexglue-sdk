# Canonical development instructions

Read `README.md`, `docs/investigation.md`, relevant ADRs and the assigned issue.
This file is the handoff for Codex, Claude, Gemini, other agents and humans;
no previous chat context is required.

## Mission and non-negotiable architecture

Modernize `furqanagwan/rexglue-sdk` into a Windows PC / April 2026 GDK /
D3D12-only static Xbox 360 recompilation SDK. Current legacy platforms/backends
remain only until the documented replacement and regression gates are met.
`furqanagwan/xenia-edge` is a controlled reference/experiment fork, never a runtime
dependency. Upstream Xenia, Canary, Edge and ReXGlue are read-only references.

Do not reintroduce Vulkan, Linux or macOS as supported targets; restore Xenia's
PPC JIT; copy upstream subsystems blindly; make game-specific hacks global;
remove compatibility behavior just to compile; ignore upstream regression
history; claim untested compatibility; or close issues without required tests.
Do not delete current legacy code before its removal issue's gates are met.
GPU shader translation is allowed and is distinct from CPU JIT. SPIR-V IR use
requires a shader architecture decision and does not imply a Vulkan backend.

## Repository map

* `src/codegen`, `include/rex/codegen`, `include/rex/ppc`: static generation/ABI.
* `src/system`: runtime, function dispatcher, XEX, memory, guest objects/threads.
* `src/kernel`: XboxKrnl/XAM typed exports; preserve guest signatures and status.
* `src/graphics`, `include/rex/graphics`: Xenos/PM4, shaders, textures, EDRAM,
  D3D12 plugin. `src/ui/d3d12` owns host device/presentation.
* `src/audio`, `src/input`, `src/filesystem`, `src/core`: guest services/host adapters.
* `src/rexglue`, `resources`: CLI and generated project templates.
* `tests/unit`, `tests/ppc`: Catch2 unit and generated PPC instruction tests.
* `cmake`, `thirdparty`, `.github/workflows`: dependencies, exports and builds.
* `docs/roadmap`: exact GitHub issue bodies/index; `docs/upstream-tracking.md`:
  provenance; `docs/regression-strategy.md`: validation contract.

## Build and test

Use an x64 Visual Studio developer shell with LLVM Clang ≥18, CMake ≥3.25,
Ninja, Windows SDK and initialized submodules. `win-amd64` is a CPU architecture.

```powershell
git submodule update --init --recursive
cmake --preset win-amd64 -DREXGLUE_USE_D3D12=ON -DREXGLUE_USE_VULKAN=OFF -DREXGLUE_BUILD_TESTS=ON
cmake --build --preset win-amd64-debug
ctest --preset win-amd64-debug --output-on-failure
cmake --build --preset win-amd64-release
ctest --preset win-amd64-release --output-on-failure
cmake --install out/build/win-amd64 --config Release
```

PPC tests require bundled `tools/binutils/powerpc-none-elf-{as,ld,nm}.exe` and
their runtime DLLs. Confirm CTest discovers actual tests; zero tests is not a pass.
No GDK-specific preset exists yet; do not invent one. Follow the assigned
toolchain issue before documenting a GDK build as supported. For planning/docs
changes run `python scripts/validate_roadmap.py` and `git diff --check`.

## Conventions and Git workflow

Follow `.clang-format` (Google-derived, two spaces, 100 columns), `.editorconfig`
and local namespace/typed-import conventions. Keep guest endian, pointer width,
structure packing and return codes explicit. Prefer narrow adapters over leaking
host APIs into guest interfaces. Preserve notices and third-party licenses.

Check status and preserve user edits before work. Use a focused topic branch in
the implementation fork for implementation; never create upstream branches,
issues or PRs. Do not force-push or rewrite unrelated work. Keep migrations
bisectable and avoid mixing a code port with removal of unrelated backends.
Issue publication is permitted when the task requests it; no extra approval is
implied by this document. Otherwise follow the user's scope.

## Porting, regression and compatibility policy

Pin source SHA and PR head/merge state; read the diff, motivation, comments and
follow-up regressions. A closed PR may be rejected. Compare existing behavior
before calling something missing. Record source repo, commit, PR/issues, date,
title scope, classification A–H, known regressions, adaptation and tests in
`docs/upstream-tracking.md`. Unknown data stays unknown.

Classify correctness, compatibility, title-specific, driver-specific,
experimental and regression fixes separately. Do not import JIT safepoints,
thread teardown or exception machinery into static code without a separate
design. CPU byte patches require regeneration or explicit generated overrides.
Follow ADR-005 for title profiles; do not scatter unexplained title-ID branches.

Establish a last-good baseline before major changes. Run relevant unit/PPC,
synthetic and representative-title tests plus AMD/NVIDIA/Intel gates for GPU
changes. Preserve saves; use disposable copies for failure injection. Record
missing hardware/test content as blocked. Do not distribute game/SDK material.
Update README when user-visible workflow/status changes, ADRs for architecture,
tracking ledger for ports and regression records for failures.

## Definition of done and agent-ready

An issue is done only when acceptance criteria, required tests, vendor/deployment
gates and docs are complete, limitations are recorded, and upstream provenance
and regression checks are linked. A build alone never proves compatibility.
`agent-ready` additionally requires settled architecture, completed dependencies,
reviewed relevant upstream items, identified files, bounded regression risk and
measurable tests. Remove that label if evidence or dependencies invalidate it.
The initial ready queue is RG-GDK-001; no runtime migration is claimed ready
before its baseline/research gates. Report precise blockers and leave work open.
