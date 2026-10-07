# Release evidence

What this fork supports, the evidence behind each claim, and what is still open
(RG-GDK-025). A configuration is listed as **supported** only when a linked run
on a recorded revision backs it. **Opt-in** means it works in the recorded runs
but is not the default. **Blocked** means it has not been run and why. Nothing
here claims results on hardware, titles or machines that were not used.

Recorded on 2026-09-27 at `main` `11644e2` or later on one development machine:
- Windows 11 Home 10.0.26340.
- VS 2026 Community 18.10.2 (MSVC 19.51.36260 libraries), LLVM Clang 22.1.8,
  CMake 4.4.3, Ninja, Windows SDK 10.0.26100.0.
- PC GDK 260404 and Gaming Services 38.117.18001.0.
- NVIDIA GeForce RTX 5080 Laptop GPU with driver 32.0.16.1714.

## Configurations

| Configuration | Status | Evidence | Limitations |
| --- | --- | --- | --- |
| SDK build and tests, `win-amd64` Debug/Release | Builds; Release suite passes; Debug has one known fixture failure | Historical fresh checkout below; current [Guide extraction checks](xbox-guide-extraction.md#validation-2026-10-06): Release 2,067 passed / 11 skipped, Debug 2,066 passed / 11 skipped / one failed | One machine; the Debug tessellation assertion also reproduces before extraction; private Guide asset cases skip |
| SDK build and tests, `win-amd64-gdk` Debug/Release | Supported (opt-in preset) | `ctest` 1,839/1,839 at `6223f54`; [GDK toolchain](gdk-toolchain.md) | VS Community only (Microsoft names Professional/Enterprise); GPU fixtures run serially |
| SDK install and external consumer | Supported | `tests/gdk_consumer` against the installed prefix ([GDK toolchain](gdk-toolchain.md)); Quantum of Solace built from `out/install/win-amd64` and `out/install/win-amd64-gdk` | — |
| Title project (`rexglue init`, `codegen`, build) | Supported for the title run | Quantum of Solace codegen, build and link against both installs ([baseline capture](baseline-capture.md)) | One title; other XEXs may need title-specific analysis |
| D3D12 rendering, NVIDIA | Supported for the recorded scenes | GPU fixtures (RG-GDK-006 to 012); Quantum of Solace 90 s scene pass | Scene pass, not visual accuracy against hardware |
| D3D12 rendering, AMD / Intel | Blocked | No hardware ([ADR-007](adr/ADR-007-local-gpu-validation-scope.md)); WARP runs are supplementary | Vendor-specific paths (sample layout, ROV) unverified |
| Input, window and audio: SDL3 | Removed (RG-GDK-033, 2026-09-28) | Old configs naming `sdl` start the native backend with a warning (`unit_tests [audio][xaudio2]`) | — |
| Input: XInput (default without the GDK) | Default | Quantum of Solace standard run with the ROG Raikiri (2026-09-28) | Subtypes from XInput; four pads not run |
| Input: GameInput (default in GDK builds) | Default | [GameInput](gameinput.md); Quantum of Solace native run after the PR #82 fix | No guide button; inbox runtime 0.2309 / redist 3.5.270 only |
| Window: Win32 (default) | Default | [Windowing](windowing.md); `gpu_tests [gpu][win32]`; Quantum of Solace native run | Multi-monitor DPI moves not run |
| Audio: XAudio2 (default) | Default | [Audio output](audio-output.md); `unit_tests [audio][xaudio2]`; Quantum of Solace native run | Physical device unplug not run; one HDMI endpoint |
| Gaming Runtime lifecycle (`gaming_runtime`) | Supported in GDK builds | [Gaming Runtime and PC packaging](gdk-packaging.md); Quantum of Solace native run logs "Gaming Runtime ready" | Missing or old Gaming Services tested with fakes only |
| `MicrosoftGame.config` and loose registration | Supported | `gdk.gameconfig_schema`; `gdk.smoke_registered` ([packaging](gdk-packaging.md)) | Registration as an application; elevated "as a game" not run |
| MSIXVC package, install, uninstall | Supported for the smoke title | `gdk.smoke_installed`; validator-clean Release package | Recompiled title not packaged; no Store submission |
| Saves and content | Supported in synthetic tests | `kernel_tests` ([content persistence](content-persistence.md)); saves survive package reinstall | Single profile; no power-loss test |
| PIX captures and host markers | Supported (NVIDIA) | PIX 2603.25; `gpu.pix_capture` (fixture capture, labeled events, debug-layer replay, no PIX imports) and `unit_tests [debug_markers]` ([PIX captures](baseline-capture.md#pix-for-windows-captures-rg-gdk-028)); Quantum of Solace frame 1800 captured with `d3d12_capture_frame`, labeled, debug-layer replay clean | Markers cover submissions, draws, resolves and swaps only; programmatic captures have no screenshot; AMD/Intel not run |
| ARM64 host | Blocked | No ARM64 MSVC libraries (RG-GDK-030/031) | — |
| DirectStorage | Not started | RG-GDK-029 | — |
| Fresh machine | Blocked | Only the development machine was available | The fresh-checkout run models a new clone, not a new PC |

## Guide extraction (2026-10-06)

For the source/issue split on 2026-10-06, the
[Guide extraction record](xbox-guide-extraction.md#validation-2026-10-06)
records the component pin, matching before/after Guide suites, full standard
Debug/Release builds and CTest, GDK Release Guide checks, an isolated Release
install and installed consumer, and standalone Windows CI without an SDK.
The existing Debug tessellation assertion remains open in the
[regression record](regression-strategy.md#debug-tessellation-fixture-2026-10-06).
Private Guide assets and an owner pad/title session were unavailable; no
current title compatibility claim is added. GDK testing still uses VS Community
and does not establish Microsoft's supported toolchain pairing.

## Fresh checkout (2026-09-27)

In a new x64 developer shell (`vcvars64.bat`) the README's commands were run
verbatim against `https://github.com/furqanagwan/rexglue-sdk.git` at `11644e2`,
into an empty `C:\rg025fresh`:

| Step | Command | Result |
| --- | --- | --- |
| Clone | `git clone --recurse-submodules …` | OK (`11644e2`, all submodules at their pins) |
| Submodules | `git submodule update --init --recursive` | OK (nothing left to fetch) |
| Configure | `cmake --preset win-amd64 -DREXGLUE_USE_D3D12=ON -DREXGLUE_USE_VULKAN=OFF -DREXGLUE_BUILD_TESTS=ON` | OK |
| Debug build | `cmake --build --preset win-amd64-debug` | OK, 1,433 build steps from scratch |
| Debug tests | `ctest --preset win-amd64-debug --output-on-failure` | 1,823/1,823 passed (118 s) |
| Release build | `cmake --build --preset win-amd64-release` | OK |
| Release tests | `ctest --preset win-amd64-release --output-on-failure` | 1,823/1,823 passed (91 s) |
| Install | `cmake --install out/build/win-amd64 --config Release` | OK, to `out/install/win-amd64` |

The run needed no step beyond the README. This proves the documented commands on
this machine; the machine already had Visual Studio, LLVM, CMake, Ninja and the
Windows SDK installed, so it is not a fresh-PC result.

## Default-switch gates for the native backends

**Decision, 2026-09-28:** the repository owner made the native backends the
defaults (GameInput in GDK builds and XInput otherwise, the Win32 window,
XAudio2) ahead of the remaining gates below, and decided that SDL is to be
removed. The gates stay as the record of what is and is not yet proven; the
status line below says which are open.

These were the gates for a native backend to become the default:

1. The backend's unit tests and fixtures pass in Debug and Release.
2. At least two recorded title soaks use it with no new fatal, error or
   missing-function log lines against the SDL run of the same scene, using
   `scripts/capture_baseline.py --run-for`.
3. **Input:** controlled input changes game state (007 #16), and connect,
   disconnect and reconnect work on real pads.
   **Window:** resize, minimize, restore, fullscreen and DPI change work in a
   title.
   **Audio:** device change and unplug work in a title.
4. The fallback still works: a missing runtime falls back to SDL with a logged
   diagnostic (GameInput already does).

SDL3 was removed by RG-GDK-033 (issue #97) on 2026-09-28, with every consumer in
the [SDL ownership map](windowing.md) replaced.

Status on 2026-09-27: gate 1 met for all three. Gate 2 has one title soak each
(Quantum of Solace native run). Gates 3 and 4 are partly met: GameInput falls
back to SDL; in-title device and window-state tests are not run.

## Rollback

Every native path is selected at startup and can be undone without a rebuild:

| Change | Roll back with |
| --- | --- |
| GameInput | `input_backend = "xinput"` |
| SDL3 removal (Win32 window, XAudio2, XInput) | None by configuration: revert the RG-GDK-033 PR |
| Gaming Runtime at startup | `gaming_runtime = "off"` |
| Real ZPD occlusion counts (RG-GDK-010) | `occlusion_query` cvar (see [regression strategy](regression-strategy.md)) |
| GDK build | Build the standard `win-amd64` preset; it needs no GDK |

Removals are not rolled back by configuration. Vulkan, Linux and macOS were
removed by RG-GDK-023 and RG-GDK-024; restoring them needs a revert of those
PRs and a new ADR.

## Continuous integration

- Pull requests run `Lint & Format Check`: clang-format, plus the script tests in
  `scripts/tests`, which include `check_docs.py` (links and paths in these
  handoff documents).
- The Windows build (`build-win-amd64.yaml`) runs only for `v*` tags and does not
  run CTest.
- The nightly workflow is manual-only. Its inherited schedule used a
  `development` branch this fork does not have and failed daily.
- Unit, PPC, GPU fixture, kernel and GDK tests therefore run on the development
  machine, as recorded in each issue. Adding CTest to CI would need a Windows
  runner with the bundled PPC toolchain and, for GDK tests, a GDK installation.
