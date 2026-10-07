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
| SDK build and tests, `win-amd64` Debug/Release | Builds; Release suite passes; Debug has one known fixture failure | Historical fresh checkout below; current [console source checks](#console-source-scenes-2026-10-07): Release 2,098 passed / 13 skipped; Debug baseline failure recorded below | One machine; the Debug tessellation assertion also reproduces before extraction; private Guide asset cases skip |
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

## PC host experience (2026-10-07)

Revision: topic branch `pc-backcompat-experience`, based on `248d6c3`, Guide
submodule `3d5ea575a0f6a6ceb9f0c39c097d5c06c59b72aa`. The runs below test the
changes included in this commit; the logged environment now has VS Community
18.10.3, with the same Clang, Windows SDK, GDK and NVIDIA device recorded above.
See [coverage and remaining gates](pc-backward-compatibility.md).

- Standard Release: full build and CTest, 2,087 discovered, 2,076 passed,
  11 skipped, zero failures (170.89 s). Includes shader reproducibility and
  1,473 generated PPC cases. Logs: `out/bc-release-final-build.log` and
  `out/bc-release-final-ctest.log`.
- Standard Debug: full build and CTest, 2,087 discovered, 2,075 passed,
  11 skipped and the one baseline tessellation assertion (200.76 s). All 512
  unit cases pass or skip; the failure is in the GPU fixture. Logs:
  `out/bc-debug-final-build.log` and `out/bc-debug-final-ctest.log`.
- CTest inventories: Debug and Release each discover 2,087 tests; all 2,085
  SDK executable arguments per configuration, including nested PowerShell
  commands, match the requested configuration. This validates the
  [discovery fix](regression-strategy.md#ctest-configuration-discovery-2026-10-07).
  Logs: `out/bc-final-test-configuration-check.log` and corresponding
  `out/bc-*-final-discovery.json`.
- GDK Release: runtime/unit target build and the combined
  `[launch_settings],[language],[library_art],[cvar],[input],[gdk]` filter passed
  89 cases / 765 assertions. Log: `out/bc-gdk-final-targeted.log`. This is
  targeted evidence, not a new full GDK or service compatibility claim.
- Private reference Flash: three-tab backward-compatibility Guide and font
  conversion tests passed 2 cases / 28 assertions each in standard Debug,
  standard Release and GDK Release. The tests read the locally installed
  Fuzion Frenzy Flash directory; no assets were copied or redistributed.
  Logs: `out/bc-reference-guide-tests.log`,
  `out/bc-reference-guide-debug-tests.log`,
  `out/bc-reference-guide-gdk-tests.log`.
- Isolated Release install `out/bc-install`: the installed launcher consumer
  builds and links with the shipped ReXApp source and GPU plugin. Native art
  checks pass against the installed CMake helper for separate base/TU EXEs:
  RT_ICON, RT_GROUP_ICON, retained manifest, large/small Shell extraction,
  five PNG dimensions, collision protection and preserved config identity.
  Logs: `out/bc-final-consumer.log`, `out/bc-final-installed-art.log`.
  The isolated CMake user-package registry entry was removed afterwards.

The launcher unit cases draw ImGui without submitting GPU frames. A hidden
consumer window did not paint; interactive rendered launch/Play flow, physical
controller navigation/handoff, real-title settings and Xbox app registration
remain pending. Existing 007/NHL installations were not changed. Account,
cloud and service achievements require independent title/service registration
and failure/offline/account-switch validation. No whole-experience parity,
original Xbox execution or additional vendor support is claimed.

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

## Checked game sources (2026-10-07)

Revision: topic `pc-game-source`, based on `799a5ea`, with the Guide pin above.
[ADR-014](adr/ADR-014-game-source-and-media-recovery.md) records the source and
media recovery contract. Same development machine as the PC host checks.

- Standard Release full build/CTest: 2,109 discovered, 2,098 passed,
  11 skipped, zero failures (176.51 s), including 534 unit and 1,473 PPC cases.
  Logs: `out/source-release-final-build.log`,
  `out/source-release-final-ctest.log`.
- Debug targeted source/disc/codegen/launch UI: 36 cases / 499 assertions pass.
  Log: `out/source-debug-final-tests.log`.
- Standard Debug full build/CTest: 2,109 discovered, 2,097 passed, 11 skipped
  and the single pre-existing GPU tessellation fixture failure (212.15 s).
  All 534 unit cases pass or skip. Logs: `out/source-debug-final-build.log`,
  `out/source-debug-final-ctest.log`.
- GDK Release runtime/unit build and source/disc/codegen/launch/GDK filter:
  50 cases / 575 assertions pass. Logs: `out/source-gdk-final-build.log`,
  `out/source-gdk-final-tests.log`. This is targeted GDK evidence.
- Final review added entrypoint path validation and rechecked Release:
  36 cases / 511 assertions pass in both standard Debug and Release
  (`out/source-debug-reviewed-tests.log`, `out/source-release-reviewed-tests.log`).
  Final GDK Release review passes 50 cases / 587 assertions
  (`out/source-gdk-reviewed-tests.log`). The installed ReXApp consumer
  also compiles the entrypoint override check
  and the shared controller adapter (`out/source-consumer.log`).
- Isolated Release installation and external launcher consumer build/link
  pass. Native art regression passes against the installed CMake helper
  (`out/source-install.log`, `out/source-installed-art.log`). The isolated
  CMake package registry entry was removed; existing title installs are intact.

Synthetic tests cover sector-aligned reads, actual image truncation on open
handles, malformed directories, source identity, game:/d: mounting, atomic
extraction, cancellation, concurrent same-media recovery, UI-thread reads and
shutdown. Dialog tests draw ImGui without GPU frames; controller events are
injected. Physical pad/optical media, substituted-drive removal, original/TU
real-title launch and rendered interactive presentation remain unverified.
Console XuiMessageBox3, Active Downloads and friendly mismatch names remain
open. Issue #154 is not closed and whole-experience parity is not claimed.

## Console source scenes (2026-10-07)

Revision: topic `pc-guide-source-scenes`, based on `98f006b`; Guide
`db55a4d` ([component PR #8](https://github.com/furqanagwan/xbox-guide/pull/8)).
The SDK supplies file picking/I/O, resources and immutable copy-history
snapshots. Guide-owned message-box and activity models remain usable through
the standalone scene target without SDK runtime dependencies.

- Standalone Guide Debug/Release build and CTest pass: one CTest entry runs
  five synthetic cases / 48 assertions. Logs:
  `out/message-box-core-{debug,release}-{build,tests}.log`.
- Standard Release final full build/CTest: 2,111 discovered, 2,098 passed,
  13 skipped, zero failures (179.00 s). Logs:
  `out/source-scenes-final-release-build.log`,
  `out/source-scenes-final-release-ctest.log`.
- Standard Debug final full build/CTest: 2,111 discovered, 2,097 passed,
  13 skipped and the one baseline GPU tessellation assertion (205.93 s).
  All 536 unit cases pass or skip. Logs:
  `out/source-scenes-final-debug-build.log`,
  `out/source-scenes-final-debug-ctest.log`.
- Final private/source/disc/launch/TU checks: standard Debug 41 cases /
  582 assertions, standard Release 41 cases / 583 assertions, GDK Release
  55 cases / 659 assertions, all passing. Logs:
  `out/source-scenes-private-{debug,release,gdk}-tests.log`.
  These use the locally installed Fuzion Frenzy Flash directory, including
  the three source choices, recovery default focus/controller A activation,
  native Disc/Retry selection and Active Downloads template. A synthetic ISO
  also exercises UI extraction, local-folder handoff and completed-copy history.
- Isolated installed consumer compiles and links the updated ReXApp host
  adapter (`out/source-scenes-install.log`, `out/source-scenes-consumer.log`).
  Installed headers include the neutral scene APIs; the isolated CMake package
  registry entry is removed afterwards.

Two additional private cases account for the skipped-count increase from 11
to 13 in asset-free full CTest. Private checks pass separately. UI tests draw
ImGui without GPU frames and inject controller state; painted/physical pad
validation remains open. Images/optical media removal, friendly mismatch
names and real original/TU title launches remain #154 gates. Media dialogs
pair guest input blocking with XAM system-UI state/notifications and release
it on action or shutdown; that host lifecycle needs a real-title check.
No whole PC parity, service entitlement or original Xbox execution is claimed.

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
