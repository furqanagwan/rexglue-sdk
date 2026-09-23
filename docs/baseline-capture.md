# Baseline capture workflow

Implementation starts with RG-GDK-001. The first title is **007: Quantum of
Solace**. Keep its ISO, extracted modules, generated code, saves and captures
outside this repository. Work through boot, menus, a repeatable gameplay scene,
save/reload, audio/input and rendering before expanding to another title.
Synthetic unit/PPC tests and hardware validation remain required alongside it.

`scripts/capture_baseline.py` writes a new run directory containing `run.json`,
stdout/stderr logs and SHA-256 hashes. Existing directories are rejected.
The manifest follows [baseline-run.schema.json](baseline-run.schema.json).
Use an explicit executable path and a finite timeout. Run from the title's
required working directory; the recorder records that directory.

```powershell
python scripts/capture_baseline.py --output C:/private/runs/qos-boot-001 --title QuantumOfSolace --material C:/private/qos/default.xex --metadata C:/private/qos/environment.json --timeout 120 -- C:/private/qos/QuantumOfSolace.exe
python -m unittest discover -s scripts/tests -p test_capture_baseline.py
```

The optional metadata file is a JSON object. Record compiler, Windows SDK, GDK
(or `not used`), build configuration, GPU model/driver, adapter selection,
RTV/ROV path, title/media/version IDs, scene, configuration hashes and owner.
Unmeasured values must remain `unknown` or `not-run`. Metadata is embedded and
hashed; it cannot override the recorder's result or artifact fields.

An exit code of zero means only that the process completed. Compatibility stays
`not-run` until scene evidence is reviewed. Missing material/executable produces
`blocked`; a nonzero exit or timeout produces `fail`. Exit status 1 includes
blocked runs. Preserve the manifest and artifacts; write review findings in a
separate assessment referencing their hashes. Do not edit a failed run into a
pass. The timeout controls the launched process, not a launcher-created process
tree: invoke the title executable directly.

SDK revision and worktree status are recorded; dirty builds are diagnostic and
must be rerun from a committed revision before declaring a last-good baseline.
The recorder does not capture screenshots/PIX or certify GPU/GDK behavior.

## Quantum of Solace identity and outstanding gates

On 2026-09-23, the supplied ISO's root `default.xex` was inspected privately:

* Title ID `415607FF`; media ID `06DD88A0`.
* Raw XEX version/base version `00000007` / `00000007`.
* XEX size 7,000,064 bytes; SHA-256
  `a96f4f651cc0937e51aa2f81245b48ba08d71de1b8bef0e33bc2b2bca29caa42`.
* ISO size 7,835,492,352 bytes. No title update has been applied.

The private project scaffold and code generation completed (175 output files).
Code generation reported an unresolved branch from `0x824A287C` to `0x821C1BF8`;
generated code emits `REX_FATAL` for this edge. The destination is also a local
label in another generated function, so function-boundary/shared-tail analysis
is needed before choosing a correction. Do not substitute a no-op.
The private project configured, compiled and linked against the installed
Release SDK. Full assets and a
reproducible scene are still required for a game run.
Boot/gameplay/save/audio/rendering and AMD/NVIDIA/Intel results remain `not-run`.
The user confirms NVIDIA is the only available GPU test target. AMD and Intel
GPU coverage is untested and non-blocking under
[ADR-007](adr/ADR-007-local-gpu-validation-scope.md). Earlier adapter enumeration
does not establish usable Intel GPU test coverage. NVIDIA remains unvalidated.
April 2026 GDK deployment remains untested. RG-GDK-001 stays open until its
acceptance and evidence requirements are satisfied.

## SDK build and test evidence, 2026-09-23

Baseline configuration: x64 VS developer environment, Clang 22.1.8, CMake 4.4.3,
D3D12 ON, Vulkan OFF, tests ON, pinned submodules initialized. Ordinary Windows
builds only; GDK is not selected by this preset.

Three defects were observed and corrected while establishing the baseline:

1. libmspack's cabextract path contains symlinks checked out as text on this
   Windows setup. CMake now uses the canonical source/header directory at the
   same dependency revision.
2. `rex/hash.h` exposes xxHash but CMake kept the dependency private. Core and
   runtime now propagate that public dependency to SDK consumers.
3. The depfile test used invalid C++ string escapes for expected backslashes.
   Raw string literals now test the intended escaped output; production depfile
   behavior is unchanged.

Debug and Release builds and Release installation succeeded. Each initial full
CTest run discovered 1,671 cases (213 unit, 1,458 PPC): 1,666 passed, the depfile
test failed, and four BitStream write tests explicitly skipped. After the test
fix, the named depfile test passed in each configuration. The four skips remain
coverage gaps, not passes. These results establish a build/test starting point,
not a game, GPU or GDK compatibility baseline. Raw logs are retained privately.
