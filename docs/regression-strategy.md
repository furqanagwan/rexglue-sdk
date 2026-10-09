# Compatibility baseline and regression strategy

## CTest configuration discovery (2026-10-07)

During PC host validation, a Release CTest run invoked Debug GPU executables
after a Debug build. Vendored Catch2's POST_BUILD discovery writes a shared
test file in this multi-configuration build. This made the known Debug
tessellation assertion appear to be a Release regression and invalidated
that run as Release evidence.

The SDK selects Catch2's existing PRE_TEST discovery mode. Each configuration
then receives its own discovered test file. Validation must inspect CTest's
`--show-only=json-v1` inventory as well as the test count: every SDK executable
argument, including nested PowerShell invocations, must match Debug or Release
as requested. The corrected full Release suite passes; the baseline Debug
tessellation fixture failure remains independently reproducible and open.
Current counts and limitations are in [release evidence](release-evidence.md).

## Current baseline

As of 2026-09-27 (RG-GDK-001 closed):
- **SDK:** `main` `6223f54`. CTest passes 1,823 tests on `win-amd64` and 1,839 on
  `win-amd64-gdk`, Debug and Release.
- **Title:** Quantum of Solace (`415607FF`) passes its boot and early-rendering
  scene with a 90 s soak, on SDL and on the GDK native backends. The runs, hashes
  and limitations are in [baseline capture](baseline-capture.md).
- **Other workloads:** each has an owner and a current result in the workload
  table below.
- **Vendors:** NVIDIA and WARP only (ADR-007).

### Investigation snapshot (historical)

No title execution, image comparison, audio capture, PIX capture or cross-vendor
run was performed for this investigation. **Working: unknown. Partially working:
unknown.** Upstream game reports are not local compatibility results. Local unit
and PPC tests exist but were not executed: configure requires initialized
submodules. ReXGlue source gaps and upstream risk reports are listed separately.

| Baseline field | Snapshot / status |
| --- | --- |
| SDK commit | `c94f5ebdcb3c9d1a460ca48e04f9758448f8d518` |
| Runtime architecture | AOT PPC C++ + registered dispatcher; D3D12/DXBC currently available |
| Working / partial titles | No validated inventory yet |
| Missing behavior observed in source | Fake ZPD/visible VIZ; five-argument NtOpenFile; no-op XamContentFlush |
| Graphics defect candidates | DXBC memexport rounding temp; old texture layout; not reproduced on hardware here |
| Crash / audio / input outcomes | No local run; upstream reports below are test candidates |
| GDK | `260404` install directory discovered; integration and packaging untested |
| Build | VS developer shell reaches submodule prerequisite failure; no binary built |

RG-GDK-001 creates the executable baseline workflow and records actual results.
Never overwrite the last good baseline when an import fails. Store run metadata
in version control; keep large captures and private game data in controlled
artifact storage, linked by hashes. Baseline adoption requires a maintainer
decision with explained differences, not an automatic “update expected output”.

## Required run record

Use a record with `status: not-run | pass | fail | blocked`, timestamp, SDK and
title-project commits, generated-code hash, compiler/SDK/GDK exact versions,
Windows build, CPU, RAM, adapter model/LUID/PCI vendor/device, driver, D3D12
capabilities, chosen RTV/ROV path, shader compiler/cache version, config and
active profiles, title ID/module hash/TU, scene/save/input sequence, resolution,
duration, result and artifacts. Hash screenshots, logs, PCM and captures.
Record baseline and candidate SHAs together. Mark WARP runs as WARP; they do not
substitute for AMD/NVIDIA/Intel hardware. Redact personal paths/account identifiers.

Synthetic fixtures are preferred for byte/layout/ABI behavior. Developers supply
their own legally obtained title data outside the repository; no XEX, disc image,
copyrighted shader corpus, save or restricted SDK content is distributed. A title
fixture manifest describes hashes and deterministic steps without containing
game data. Missing material is `blocked`, never `pass` or a silently skipped test.

## Representative workload suite

Titles below are regression workloads selected from reviewed upstream evidence.
Only Quantum of Solace is available and recompiled locally; every other title is
unavailable, so its gate runs as the synthetic fixture named in the result
column until the title can be supplied. Results are as of 2026-09-27
(RG-GDK-001).

| Workload | Candidate title / upstream evidence | Repeatable gate | Owner | Current result |
| --- | --- | --- | --- | --- |
| Boot and early rendering smoke | Quantum of Solace `415607FF` (private, local) | Boot to early outdoor 3D views; 90 s soak; screenshots at 30 s and 85 s | 007 #16 (title), RG-GDK-001 | **Scene pass** 2026-09-27, standard (SDL) and GDK native (GameInput, Win32, XAudio2) builds; menus, controlled input, gameplay and saves not-run |
| Kernel import ABI and file IO | Dead Rising; Edge `887beea69` | Synthetic NtOpenFile import with distinct ShareAccess/OpenOptions; later boot/load/save | RG-GDK-014 | Synthetic: `kernel_tests [content]` pass; title not available (not-run) |
| Timing, waits and title termination | NFS Shift, Riddick; Edge #233/#234/#251, Canary #872/#1025 | Delay and timeout accuracy per interval, absolute times, APC delivery, termination of blocked threads under contention with a watchdog | RG-GDK-015 | Synthetic: `kernel_tests [timing]` and `[termination]` pass (both timer modes; wake paths mutation-checked); Quantum of Solace 90 s pass in both modes; titles not available |
| Dispatch headers and object reuse | Guitar Hero 5 DLC; Canary #1225/#1227 | Header mirrors host for events/semaphores, guest in-place writes, stale signature after handle reuse, concurrent wait/signal/reset/pulse | RG-GDK-014 | Synthetic: `kernel_tests [object_header]` pass (reproducer fails with the check removed); title not available |
| ZPD and lens flares | Crackdown 2; Canary #1218 | Occluded/unoccluded scene, strict vs fast/readback modes, query ID reuse/wrap and MSAA | RG-GDK-010, #64 | Fixture: `gpu_tests [zpd]` pass (NVIDIA, WARP); ROV counters `gpu_tests [zpd][rov]` pass (NVIDIA; WARP skips); RTV full counters open (#64); title not available |
| Scalar shader math | Ace Combat 6; Canary #1190 | rcp/rsq/log/exp edge values and ground rendering; unrelated shader controls | RG-GDK-012 | Fixture: `gpu_tests [alu]` pass (NVIDIA, WARP); title not available |
| EDRAM depth aliasing | title `4D530A26`; Canary #1222 | Color→depth→color bit preservation, occluded sprites, 1x/2x/4x sample readback | RG-GDK-009 | Fixture: EDRAM layout fixtures pass (NVIDIA, WARP); title not available |
| AMD sample layout | title `4D5307F1`; Canary #1238 | Canonical EDRAM before/after depth-copy fixtures, exact sample indices | RG-GDK-009 | Fixture pass on NVIDIA and WARP; AMD hardware unavailable (ADR-007) |
| Texture addressing | Golden Axe Beast Rider `534507E5`, `4E4D0855`; #1243 | Volume/array/mip packing and 96bpp pitch with independently computed byte ranges | RG-GDK-008 | Unit: `unit_tests [texture_layout]` pass; title not available |
| Sub-32bpp resolve | `534307D5`; #1240 | 8/16bpp offsets crossing 4KB and x=480 stripe; scaling and MSAA | RG-GDK-008 | Fixture: sub-32bpp resolve phase passes (NVIDIA, WARP); title not available |
| Memexport and memory pressure | UFC Undisputed 3 `5451087D`; #1093 | Stock and created fighters, packed signed exports, near-full heap, CPU readback | RG-GDK-011 | Fixture: `gpu_tests [memexport]` pass; #1093 clamp not adopted; title not available |
| Decal depth | Lost Odyssey `4D5307FA`; Edge #278 | Same camera/input, old clamp and proposed offset isolated, unrelated FH2 control | RG-GDK-012 | Not-run: no clamp or offset adopted; titles not available |
| Async IO timing | UEFA CL 2006–2007 `45410811`; Edge #275 / timing commits | Match load, physical allocation peak, sequential/random read deadlines and no global cap | RG-GDK-016 | Not-run (issue open) |
| Scheduler/exception stability | NFS Shift; Edge #233; Riddick in #234 | Repeated scene load under contention and watchdog; preserve static unwind/callbacks | RG-GDK-015 | Not-run (issue open); QoS 90 s soaks show no stalls |
| XMA loops | Tekken Tag 2, Koei titles; Edge `5dd1cdbbf`, #141 | Exact/one-bit-early loop start, multiple loops, PCM continuity and context progress | RG-GDK-018 | Unit: `unit_tests [xma]` pass on synthetic WMA Pro frames; titles not available |
| XMA decode failure | LEGO LOTR `5752081D`; Edge #235/#236 | Packet boundaries/error propagation; intro progress; no silent substitution masking failure | RG-GDK-018 | Unit pass (decode-failure count, no-progress guard); title not available |
| XMA multistream | DJ Hero 2; Canary #438 | Independent stream stems, channel ordering and simultaneous context consumption | RG-GDK-018 | Not-run: no multistream fixture |
| Audio lifecycle | 007 Legends `415608D8`, SCDA, Dark Souls; Edge #120/#113/#164 | Menus/scene transition/teardown, callback lifetime and device removal | RG-GDK-018, RG-GDK-019 | Unit: client lifetime and XAudio2 driver tests pass; QoS audio starts on SDL and XAudio2 |
| Content/profiles/notifications | Guitar Hero 5 DLC; #1225/#1226; Army of Two #1220; BO2 #1135 | Truncated package, object reuse, two-profile crash/restart persistence, listener masks | RG-GDK-017 | Synthetic: `kernel_tests` and STFS unit tests pass; two-profile case not-run (single profile) |
| Input | Guitar Hero subtype #1230; synthetic four-pad app | Connect/disconnect/reconnect, slot stability, whammy neutral, rumble, focus and mouse merge | RG-GDK-020 | Unit: input matrix passes; QoS pad connects on SDL and GameInput; four-pad and guitar hardware not-run |

Each baseline should include at least one workload from GPU, kernel, content,
audio, input and timing. A locally booting title is not automatically suitable
for testing all subsystems. Record the exact scene and stopping condition.

## GPU vendor assessment and matrix

All rows are **not run**. Hardware groups are a sampling strategy, not a promised
minimum GPU list. Choose concrete available models when executing RG-GDK-006.

| Vendor/sample | Evidence requiring attention | Required tests | Status |
| --- | --- | --- | --- |
| AMD, at least two supported driver/architecture combinations | Canary #1238 explicitly follows an AMD regression; local historical AMD ROV/shader condition | Host-RT/ROV, 2x/4x depth copy, resolves, memexport, device removal | Not run; no AMD detected locally |
| NVIDIA, modern and older compatible device | Edge #204 report was closed for tracker scope; Canary #1093 RTX 4070 Ti SUPER memexport report | Async pipeline lifetime, stock/created fighter geometry, stencil, readback, hybrid-adapter selection | RTX 5080 Laptop detected, driver 32.0.16.1714, FL 12_2, SM 6.8 (`gpu_tests`); fixtures not run |
| Intel Arc and non-Arc separately | Canary #608 non-Arc native stencil failure; local Intel fallback rules | Stencil export toggle/fallback, host-RT/ROV if supported, clears, bandwidth and unified memory | Intel Graphics detected, driver 32.0.101.6129; model class/caps not established; not run |
| WARP | Deterministic API validation and CI smoke only | Resource/state/descriptor checks where supported | Capability metadata smoke passes (`gpu_tests`, FL 12_1, SM 6.8, driver 10.0.26100.9502); cannot certify a vendor |

Run each selected GPU on ordinary Windows development deployment and intended
GDK title deployment. Record OS/driver/GDK versions rather than assuming newest
means correct. Run correctness at native scale first, then 2x resolution and
1x/2x/4x MSAA where guest fixtures support them. Test cold/warm caches and
foreground/minimize/resize/device removal. No optional feature should become an
implicit prerequisite without an explicit support policy change.

### Capability record (RG-GDK-006)

Every GPU run records the provider's startup log lines, which name the adapter
index, vendor/device/subsystem/revision IDs, user-mode driver version, dedicated
memory, software flag, max feature level, highest shader model, debug-layer and
DRED state, the optional D3D12 features, and the render-target path the cache
actually selected with its reason (`render_target_path_d3d12`, vendor default or
ROV fallback) plus whether pixel-shader stencil reference output is used. A
result without those lines is not reproducible and does not count.

Debug-layer runs (`--d3d12_debug`) are correctness runs only. Performance runs
leave the debug layer off; use `--d3d12_dred` there to keep DRED breadcrumbs and
page-fault capture for device-removal diagnosis. DRED is still forced on with
the debug layer.

`gpu_tests` (CTest label `gpu`) creates real devices and runs the GPU fixtures:

```powershell
ctest --preset win-amd64-debug -L gpu -V
```

- **Capability metadata:** WARP and hardware devices report the values above.
  The hardware case skips when only a software adapter exists.
- **Fixture host (`tests/gpu/gpu_fixture.*`):** starts a `Runtime` with no
  title image, loads the `xenos` GPU plugin through the plugin ABI, places the
  primary ring buffer in guest physical memory and advances `CP_RB_WPTR`
  through the MMIO path, as a title does. `Flush()` waits for an
  `EVENT_WRITE_SHD` fence, so results read back afterwards are ordered after
  all submitted work. Each fixture prints the adapter metadata it ran on.
- **PM4 fixtures:** `MEM_WRITE` with and without endian swap, type-0 register
  writes read back with `REG_TO_MEM`, `INDIRECT_BUFFER` ordering, and fence
  ordering.
- **Resolve fixture:** an EDRAM color clear resolved through the resolve
  compute shaders into guest memory with `readback_resolve=full` at 1x, 2x
  and 4x MSAA; every texel must match the clear color.
- **Sub-32bpp resolve phase (RG-GDK-008):** k_8 and k_5_6_5 resolves to bases
  0, 1 or 3 macro tiles into a 4 KB subresource; every byte of the destination
  must match the `GetTiledOffset2D` oracle, with no stray writes.
- **Resolve readback positions (#58):** a 4x4 grid of 8x8 cells, each
  resolved with its own clear color, to k_8, k_5_6_5 and k_8_8_8_8; every
  texel must hold its cell's value at the oracle address. A uniform clear can't
  show texels read back from the wrong place. `gpu.resolve_readback_scaled_3x2`
  reruns all resolve fixtures at `draw_resolution_scale` 3x2.
- **EDRAM sample layout (RG-GDK-009, `[edram]`):** guest draws through
  hand-assembled microcode (one scissored constant-color draw per pixel, so
  every pixel is distinct) followed by resolves of the same EDRAM through
  another view: 1x re-aliased as 2x/4x per sample and 2x/4x re-aliased as 1x
  must follow Canary #1163's canonical layout; a k_32_32_FLOAT target at 1x and
  4x re-aliased as 32bpp must put each 64bpp half at `u = 2 * u_64bpp + half`;
  a color target writing only the stencil byte over D24S8 at the same base
  must keep a read-only depth test and the depth bits (Canary #1222); a 2x/4x
  D24FS8 depth target restored after such an alias must keep its float32 host
  depth, checked by redrawing with an equal depth test (Canary #1238).
- **Device removal:** `gpu.device_removal_is_reported` removes the device with
  `ID3D12Device5::RemoveDevice` and requires the backend's fatal
  "Graphics device lost" report after the `DEVICE_REMOVED` reason is logged.
  Device loss is fatal by design today (`GraphicsSystem::OnHostGpuLossFromAnyThread`);
  device re-creation is not implemented.

Fixture environment variables:

| Variable | Effect |
| --- | --- |
| `REXGLUE_GPU_FIXTURE_ADAPTER` | DXGI adapter like `d3d12_adapter`; `-2` runs the fixtures on WARP |
| `REXGLUE_GPU_FIXTURE_CVARS` | `name=value;...` cvars applied before the GPU starts, e.g. `render_target_path_d3d12=rov` |
| `REXGLUE_GPU_FIXTURE_LOG` | Log file for diagnosing a failing fixture |

Debug CRT assertions in `gpu_tests` go to stderr, so an unattended run fails
instead of blocking on a dialog.

Recorded fixture results (2026-09-24, debug and release):

| Adapter | Driver | RT path | PM4 | Resolve | Device removal |
| --- | --- | --- | --- | --- | --- |
| NVIDIA RTX 5080 Laptop (0x10DE), FL 12_2, SM 6.8 | 32.0.16.1714 | host RT and ROV | Pass | Pass (0x11223344, 4096/4096 texels) | Pass |
| WARP (0x1414), FL 12_1, SM 6.8 | 10.0.26100.9502 | host RT and ROV | Pass | Pass (4096/4096 texels) | Not run |

RG-GDK-008 resolve fixtures (2026-09-24, debug): NVIDIA and WARP, host RT
and ROV, pass at native resolution for every MSAA and phase case. Texture
layout is covered by the `[texture_layout]` CPU unit tests; no fixture uploads
a guest texture through a draw yet.

Scaled readback ([#58](https://github.com/furqanagwan/rexglue-sdk/issues/58),
2026-09-24, debug): all resolve fixtures pass on NVIDIA at scales 2x2, 3x3,
3x2, 1x3 and 4x4 (host RT), at 3x3 on ROV and with
`readback_resolve_half_pixel_offset`, and on WARP at 3x2 (host RT) and 2x2
(ROV). Before the fix, 8bpp/16bpp readback lost half the texels at 2x and every
format came back misplaced at non-power-of-two scales.

RG-GDK-009 EDRAM layout fixtures (2026-09-24, release; debug and release
CTest 1697/1697): all `[gpu]` fixtures pass on NVIDIA with host RT and ROV at
native resolution, host RT at 3x2 and ROV at 2x2, and on WARP with host RT.
Before the port the layout fixtures fail on NVIDIA with both paths (192 of
192 2x samples and 224 of 256 4x samples off the canonical layout, 192 pixels
in the 2x/4x-as-1x direction); without the #1222 change 640 of 640
depth-failing pixels are written; without the #1238 change 486 of 512 2x
pixels fail the equal depth test. The 4x half of #1238 changes nothing in this
repository: its shaders address the store in 16-byte units, which drop the
misplaced sample bit (Canary's byte-addressed shader didn't). On WARP, ROV
draws never complete, so the `[edram]` fixtures run on WARP only with host
render targets. Titles 4D5307F1 and 4D530A26 and a PWL gamma blend fixture
are not run (no title content, no gamma draw fixture yet).

RG-GDK-025 release documentation (2026-09-27): `docs/release-evidence.md` lists
every configuration as supported, opt-in or blocked, with the evidence for each,
the default-switch gates for the native backends, rollback cvars and CI coverage.
The README's build commands were run verbatim from a fresh clone in a new
developer shell: 1,823/1,823 tests in Debug and in Release, and the install
succeeded. `scripts/check_docs.py` (in CI through `scripts/tests`) checks that
every link and repository path in README, AGENTS, CONTRIBUTING and docs
resolves. It found stale Vulkan and removed paths in the removal map, which are
now fixed. Also fixed: `rexglue init` projects now stage the GPU plugin, the ADR
statuses record what shipped, and the nightly workflow (failing daily on a
missing `development` branch) is manual-only. Not run: a fresh PC, AMD and
Intel.

GameInput startup crash (2026-09-27, found after RG-GDK-020 closed): a GDK
build of Quantum of Solace with `input_backend = "gameinput"` crashed within
seconds (0xC0000005 in `InputSystem::AttachWindow`). `RegisterGuideButtonCallback`
on the installed runtime (inbox GameInput.dll 0.2309, GameInputRedist 3.5.270)
wrote its token (2) over the driver's vtable pointer. The registration is
removed and the guide button is not reported through GameInput. New
`unit_tests [gdk][gameinput]` cases drive ReXApp's path (default input system,
then `AttachWindow`) and check the vtable after `Setup`; both failed before the
fix. The unit tests had missed it because they called the concrete driver
directly, so the compiler devirtualized the calls. Quantum of Solace then ran
90 s with GameInput, the Win32 window, XAudio2 and the Gaming Runtime.

RG-GDK-022 Gaming Runtime and packaging (2026-09-26): `rex::system::GamingRuntime`
initializes the runtime off-thread with a timeout (the recorded 60 s stall),
classifies missing, version, config and timeout failures, and uninitializes
after the guest runtime; `ReXApp` applies `gaming_runtime = auto|required|off`.
`rexglue init gameconfig` writes a schema-valid PC `MicrosoftGame.config` from
supplied identity only. `unit_tests [gaming_runtime],[gameconfig]` (fakes plus
the installed runtime: malformed 0x8924010B, missing 0x80070003, generated
config accepted), `gdk.gameconfig_schema` (installed XSD) and the
`tests/gdk_smoke` title: unpackaged (missing and mismatched `rexruntime.dll`,
malformed config), `wdapp register` and a validator-clean `makepkg pack /pc`
MSIXVC via `wdapp install`, each launched with package identity and removed,
with saves under Documents surviving redeploy. Not run: a recompiled title, a
machine without or with an old Gaming Services, elevated game registration, a
clean machine, Store submission. Details: `docs/gdk-packaging.md`.

RG-GDK-017 part 4, notifications and launches (2026-09-26): closed notify
listeners are unregistered (they were kept alive and fed forever), max_version is
clamped instead of asserted, and `XamLoaderLaunchTitle` logs whether a title went
to the dashboard, relaunched itself or asked for a module that was not compiled.
`kernel_tests [notify],[launch]`; the closed-listener case fails with the
unregister removed. XMP initial state (Canary #1135) left on watch. RG-GDK-017
closed with the single-profile and relaunch limitations recorded.

RG-GDK-017 part 3, close and profiles (2026-09-26): `XamContentClose` flushes
before releasing; profile settings are shared and locked, so a reader keeps a
setting another thread replaces (was a use-after-free); title-specific settings
save durably and no longer leak into a title without a saved copy.
`kernel_tests [profile]` plus the close case in `[content]`; the leak and close
cases fail when their fixes are disabled. Not run: two signed-in users (no
multi-user profile model), a system crash, titles.

RG-GDK-017 part 2, STFS bounds (2026-09-26): the STFS/SVOD reader refuses or
partially reads damaged packages instead of dereferencing null hash lookups,
indexing past its entry list, recursing through SVOD cycles or asserting.
`unit_tests [stfs],[svod]` (13 synthetic packages, incl. Canary #1226's
content_size mount check); 7 fail on the previous reader (Release build, to
avoid its Debug asserts). Not run: real damaged packages or titles.

RG-GDK-017 part 1, content flush (2026-09-26): `XamContentFlush` flushes the
root's open files and restores a missing header, `NtFlushBuffersFile` flushes,
and content headers are written through a flushed temporary and a rename.
`kernel_tests [content]` (new executable on an image-less Runtime) covers
flush success under either root casing, an unknown root, a failing file flush,
header restore, torn-header replacement, and a child process killed after
flushing whose save is listed and read back after restart. The failing-flush
case fails with error propagation disabled. Not run: power loss, titles.
Parts 2-4 are open; see `docs/content-persistence.md`.

RG-GDK-019 XAudio2 output (2026-09-26): `audio_backend = "xaudio2"`, opt-in
then and the default since 2026-09-28. `unit_tests [audio][conversion]` checks per-channel impulse
placement for 5.1 and the stereo fold, weights, gain and clamping.
`unit_tests [audio][xaudio2]` runs on the real XAudio2 and default endpoint
(NVIDIA HDMI audio here): paced playback with one release per frame, clock
pacing with no device, simulated critical error and silent-stall recovery,
late device arrival, slot overflow, 25 teardown cycles, two clients, and the
cvar-selected system serving a registered guest client. The loss and stall
paths fail their tests when disabled. Not run: titles, a physical unplug and
reconnect, 44.1 kHz-only endpoints, surround endpoints by ear. See
`docs/audio-output.md`.

RG-GDK-018 XMA and audio callback lifetime (2026-09-25): Edge packet/loop
fixes (`adf56b76c`, `5dd1cdbbf`, `9d8210b32`, `052365bc0`, `ade7e610b`), Canary
output invalidation (`7e98ae6de`, `09dbe2cd3`, `505697f98`) and the per-client
callback lifetime (`8aa50e0e0` with `b0a1ea5f8`, Canary #1214) ported.
`unit_tests [audio][xma]` decodes synthesized silent XMA streams through the real
FFmpeg decoder: split headers (XMA1 and XMA2), frameless skip chains, loop_start
one bit early and exact, single-frame and failing loops, ring wrap, stereo,
consume-only drain, starved input, and counted (not silenced) decode failures.
`[audio][lifetime]` covers unregister during an in-flight callback, re-entrant
submit, self-unregister and 300 register/dispatch/unregister cycles. Each fix
fails its test when disabled. Not run: Koei, Tekken Tag 2, LEGO LOTR, SCDA and
007 Legends (no recompiled fixtures here); FFmpeg pin unchanged. See
`docs/xma-audit.md`.

RG-GDK-021 native Win32 window (2026-09-25): `ui_backend = "win32"`, opt-in
then and the default since 2026-09-28. `unit_tests [ui][win32]` covers creation, DPI-scaled size,
resize, minimize and restore, fullscreen round trip, close veto versus
programmatic close, key and gated character input, and cross-thread UI
calls. `gpu_tests [gpu][win32]` presents D3D12 frames through the Win32 window
on WARP and NVIDIA across resize, minimize and restore, and closes with the
presenter attached. SDL consumers and owners are in `docs/windowing.md`. Not
run: titles, multi-monitor DPI moves, and AMD or Intel presentation.

RG-GDK-020 GameInput (2026-09-25): `input_backend = "gameinput"` (GDK
builds), opt-in then and the default since 2026-09-28. `unit_tests [input][gameinput]` covers the
guest-facing matrix through `GamepadDevices`: four pads, unplug, same or
different pad reconnecting, no phantom input, packet numbers, unfocused pad,
rumble hold, focus stop and resume, no rumble after reconnect, and keystroke
release. `[keystroke]` covers the synthesizer now shared with SDL, and
`[gdk][gameinput]` the mapping and setup against the installed runtime (one
pad enumerated and read). Not run: a four-pad hardware matrix, hot-plug,
hardware rumble, guitars (Canary #1230 open) and a machine without GameInput.

RG-GDK-002 GDK toolchain (2026-09-25): the opt-in `win-amd64-gdk` preset
(edition 260404, VS 2026 Community 18.10.1, Clang 22.1.8, Windows SDK
10.0.26100.0) passes 1731/1731 in Release and all unit/PPC/`[gdk]` tests in
Debug; GPU fixtures pass serially (one contention failure under `-j 8`). The
installed package builds and runs the external consumer in
`tests/gdk_consumer` (Gaming Runtime init 0x00000000, exception through
rexruntime, plugin ABI handshake and shared cvar registry). Missing, invalid and
wrong-edition GDK selections fail configure with actionable messages. The
standard `win-amd64` preset is unchanged. Not established: Microsoft-supported
VS edition (Professional/Enterprise), a clean machine, packaged-title operation
and ARM64. Details: `docs/gdk-toolchain.md`.

RG-GDK-012 scalar math and depth (2026-09-25): `gpu_tests [alu]` is the
semantic oracle for the scalar approximations: EXP, LOG, LOGC, RCP, RCPC, RCPF,
RSQ, RSQC, RSQF and SQRT on 27 inputs (signed zeros, infinities, NaN,
negatives, finite values across the exponent range) through translated vertex
shaders, checked bit-exactly against the documented special cases and within
2^-20 of double precision otherwise. It passes on NVIDIA and WARP with
`gpu_scalar_approximation_rounding` off (default) and on. The 21-bit rounding
from xenia-canary #1190 stays opt-in because its precision and midpoint are
unconfirmed on hardware. Depth bias is fixed-function on RTV and in-shader on
ROV, never both; no Inf depth clamp (#1077) or RTV shader offset (Edge #160,
regression #278) is adopted. Not run: AC6 4E4D07D1, Lost Odyssey on RX 6600,
Gears/SCDA benefits and the Forza Horizon 2 control (no title content), AMD and
Intel.

RG-GDK-011 part 2 (2026-09-25): `gpu_tests [memexport]` and
`[async-pipeline]` pass on NVIDIA (0x10DE, driver 32.0.16.1714) and WARP.
Ownership traced end to end for memexport: `RequestRange` before the draw
(ranges past the 512 MB end fail and drop only that draw), `RangeWrittenByGpu`
after it (pages valid and write-watched on the vA/vC/vE guest views), full
readback into guest memory, and a guest-view CPU write invalidating the pages
so the next draw re-uploads them (a hand-assembled `eA`/`eM0` vertex shader
exports, the CPU reads it back, overwrites it through the guest view and the
next draw fetches it as vertices). Writes through the physical host view
bypass the watches by design; the fixture's `WriteDwordsAsGuest` models guest
writes. A stream whose index count runs 1 MB past its 4 KB allocation (the
5451087D shape) keeps the head written and the command processor running; the
xenia-canary #1093 clamp is not adopted. The async stress translates unseen
pixel shaders on creation threads while PS-less draws translate the shared
vertex shader on the processor thread, then tears down with creation queued;
it is stress coverage, not a deterministic reproduction of the publication
race. Not run: UFC3 (no title content), AMD/Intel, device removal during
creation.

RG-GDK-011 part 1 (2026-09-24): `gpu_tests [ring]` passes on NVIDIA and
WARP. The read pointer write-back reaches a WAIT_REG_MEM blocked on the guest
to within one RB_BLKSZ stride (this case fails with mid-burst publication
disabled), and bursts totalling five ring lengths wrap with the fixture
waiting on the write-back for space. The shader translation publication order
fix has no deterministic test yet. Not run: memexport near-full heap and
failed stream ranges, async compile stress with teardown/device removal, UFC3
(no title content), AMD/Intel.

RG-GDK-010 ZPD occlusion queries (2026-09-24): `unit_tests [zpd]` and
`gpu_tests [zpd]` pass on NVIDIA (0x10DE, driver 32.0.16.1714) at 1x and at
3x2 draw resolution scale (`gpu.zpd_scaled_3x2`), and on WARP. Strict mode is
the oracle: BEGIN/END, QueryBatch with empty intervals, depth-rejected samples,
segments split across submissions, reused report memory with recycled host
query slots, a PS-less draw without writes (0 samples without the empty-PS
binding, on NVIDIA and WARP), 4x MSAA (host samples) and fast/fake modes. Not
run: AMD/Intel, VIZ (#65) and Crackdown 2 flares with the resolve readback
modes (no title content).

RG-GDK-010a ROV occlusion counters (2026-09-28): with
`render_target_path_d3d12 = "rov"` (Intel's default path) the pixel shaders
count samples into a per-query counter slot instead of reporting fake counts.
`occlusion_query_full_counters` (default off) adds ZFail and StencilFail on ROV.
`gpu_tests [zpd][rov]` on NVIDIA covers BEGIN/END, depth-rejected draws, depth
and stencil failures with full counters (a sample failing both counts once, as
StencilFail), slot reuse (32 queries) and 4x MSAA. WARP skips, as its ROV draws
don't complete. Mutations: restoring the fake fallback fails all five tests,
skipping the slot clear fails the reuse test, and dropping stencil precedence
fails the full-counter test. Not run: Intel and AMD ROV hardware.

RG-GDK-010a RTV hybrid Total (2026-09-29): with host render targets and
`occlusion_query_full_counters`, queries around depth or stencil tested draws
without depth writes take ZPass from the D3D12 query and Total from the pixel
shaders; the rejected rest is ZFail (host render targets cannot separate
StencilFail). `gpu_tests [zpd][hybrid]` on NVIDIA covers depth- and
stencil-rejected draws, a draw without a guest pixel shader (the counting
depth-only shader), a depth-writing draw sharing an interval with a hybrid one
(segment split), slot reuse (16 queries) and 4x MSAA. Mutations: dropping the
Total-counting segment split fails all five, and skipping the slot clear fails
the reuse test. The first run also caught the root signature being built
before hybrid support was known. Default settings are unchanged: the counter
UAV is only bound when full counters are on. Not run: Intel and AMD.

RG-GDK-004 heap ranges (2026-09-24, debug and release CTest): the AllocRange
window cases in `unit_tests [memory]` pass; six of seven fail before the
change (allocations ending above an unaligned or inclusive ceiling, a
`UINT32_MAX` ceiling rejected, a too-small window reaching the search). The
vE0000000 case records physical alignment for 4K/32K/64K requests and the
4D5307F1 request size from xenia-canary #1182. No physical-heap title (Far
Cry 3 or equivalent) was run.

AMD and Intel are untested and non-blocking (ADR-007). The `[edram]` fixtures
draw through guest shader translation; RG-GDK-010 to RG-GDK-012 add fixtures
for the paths they change.

### D3D12 vendor exceptions

Vendor-name branches in the D3D12 backend. None is driver-scoped yet; each needs
a fixture that shows the failure on the named driver before it is kept, narrowed
by driver version or retired.

| Location | Vendor | Behaviour | Origin and driver evidence | Override | Retirement test |
| --- | --- | --- | --- | --- | --- |
| `D3D12RenderTargetCache::Initialize` (`render_target_cache.cpp`) | Intel | Default render-target path is ROV instead of host render targets | "always" stencil comparison broken on UHD Graphics 630, driver 27.20.0100.9316 (April 2021) | `render_target_path_d3d12=rtv` | D3D9-style clear fixture with "always" stencil on current Intel Arc and non-Arc drivers |
| `D3D12RenderTargetCache::Initialize` (disabled `#else`) | AMD | Would force host render targets | AMD shader compiler crashes with the ROV output merger (March 2021) | n/a (dead code) | ROV draw fixture on current AMD drivers; delete the branch if it passes |
| `D3D12RenderTargetCache::Initialize` (`use_stencil_reference_output_`) | Intel | Pixel-shader stencil reference output off unless opted in | Canary #608: native stencil output fails on non-Arc Intel (Iris Xe) | `native_stencil_value_output_d3d12_intel=true` | Stencil export fixture, Arc and non-Arc separately |
| `DxbcShaderTranslator::UseSwitchForControlFlow` (`dxbc_translator.cpp`) | Intel | DXBC control flow uses `if` chains instead of `switch` | Crash on Intel HD Graphics 4000 (no driver recorded) | `dxbc_switch` (only disables further) | Shader control-flow fixture with `switch` on current Intel drivers |

## Comparison and release gates

For deterministic buffers use exact bytes/hashes; shader math cases need explicit
expected values, ULP bounds and NaN rules. Screenshots use a fixed frame and an
approved pixel-difference tolerance/mask recorded before the candidate run.
Audio tests check PCM samples, channel mapping, drift and underrun counts.
Performance runs exclude diagnostic layers, use at least five paired runs with
the same scene/cache state, and report median/p95 frame time and variability.
A reproducible >5% median or >10% p95 worsening triggers review, not automatic
acceptance or a claim of statistical significance. Record hardware noise.

Major ports need: unit/PPC pass; targeted synthetic failures fixed; previously
working representative scenes remain working; no new unexplained image/audio
differences, hangs or device removal; relevant vendor/deployment matrix complete;
and a tested rollback. Run save tests on disposable copies. A build-only pass
cannot close a compatibility migration. When hardware is unavailable, keep that
gate blocked and the issue open.

## PPC test corpus (RG-GDK-054)

Besides ReXGlue's own `tests/ppc` suite (1,473 cases, default CTest),
`tests/ppc/corpus` carries xenia-edge's 578 instruction test files, most of
them captured on Xbox 360 hardware ([README](../tests/ppc/corpus/README.md)).
It is opt-in (`-DREXGLUE_PPC_CORPUS=ON`), one CTest test per file, labelled
`ppc_corpus`; run it for any codegen, PPC builder or FPSCR change.

`tests/ppc/corpus/known_failures.txt` lists each case expected to fail with
its cause. A new failure or a known failure that passes fails the file's test,
so the list always matches the run; a fix removes its entries in the same
change. Measured 2026-10-02 (GDK Release, `main` 8aaf14e plus RG-GDK-055):
567 files, 169,459 cases run (917 skipped by Edge's `skip.txt`, 11 files the
bundled assembler can't assemble), 3,381 known failures. RG-GDK-055 (#151)
cleared the 27,585 floating-point failures RG-GDK-054 started with, and
RG-GDK-072 (#185) the 40 other wrong results (2026-10-03), leaving 3,341.

| Cause | Cases |
| --- | --- |
| #149 missing instructions, and `mfmsr` | 3,333 |
| Corpus errors: hand-written cases expecting a non-IEEE result (`faddx_3`, `fcmpu_1`, ...) | 8 |

Each case starts from a reset FPSCR (round to nearest, no flush) and a zeroed
test data window, as Edge's runner does; without that, rounding modes and
memory left by earlier cases changed later results.

RG-GDK-053's 2026-10-07 candidate removes the remaining 3,333 #149 entries.
The original pinned corpus/skip list is retained; eight hand-written corpus
errors still fail as expected. There are 567 CTest file entries, of which 563
contain active cases (four files are wholly skipped by the source skip list).
The generator emits 169,459 cases and reports 917 skipped. A direct corpus run
therefore executes 563 Catch2 groups, not 567 active groups.

MSR cases also need independent interrupt state: raw writes can finish with
EE disabled. The generated test scope releases its owned critical-region
nesting on case exit, including exceptions. This cleanup is confined to tests;
title code must balance its real interrupt disable/restore transitions. The
ordinary suite additionally tests nested MSR writes, repeated enables and
`mfmsr` values in each state. See [the follow-up provenance](upstream-tracking.md#rg-gdk-053-main-integration-and-corpus-follow-up-2026-10-07).

## Regression tracking index

These are **upstream-reported risks**, not newly proven ReXGlue regressions.
Mapped issues are prevention/research work. Create a separate ReXGlue regression
bug only after local evidence identifies an actual failure relative to a baseline.

| Upstream reference | Category / known range | ReXGlue tracking |
| --- | --- | --- |
| [Edge #278](https://github.com/has207/xenia-edge/issues/278) | Rendering/vendor; Lost Odyssey, comparison 7d5dcea…b988808 | RG-GDK-012 |
| [Canary #1238](https://github.com/xenia-canary/xenia-canary/pull/1238) | Vendor/rendering; AMD after canonical EDRAM | RG-GDK-009 |
| [Canary #1093](https://github.com/xenia-canary/xenia-canary/issues/1093) | Rendering/memory; UFC3, exact first-bad unknown | RG-GDK-011 |
| [Edge #233](https://github.com/has207/xenia-edge/issues/233) | Stability/compatibility; ccd4443 good, 34357e2 bad | RG-GDK-015 |
| [Edge #234](https://github.com/has207/xenia-edge/issues/234) | Scheduler hangs/performance, title-dependent | RG-GDK-015 |
| [Edge #164](https://github.com/has207/xenia-edge/issues/164) | Audio/stability; report after 8aa50e0 | RG-GDK-018 |
| [Edge #120](https://github.com/has207/xenia-edge/issues/120) | Audio; 007 Legends report after c3d1d3d, reporter later confirms fix | RG-GDK-018 |
| [Edge #113](https://github.com/has207/xenia-edge/issues/113) | Audio/compatibility; SCDA after 5376439 | RG-GDK-018 |
| [Canary #1036](https://github.com/xenia-canary/xenia-canary/issues/1036) | Audio/functional; Koei voice-line hangs | RG-GDK-018 |
| [Canary #608](https://github.com/xenia-canary/xenia-canary/issues/608) | Intel rendering; first-bad unknown | RG-GDK-006 |
| [Canary #872](https://github.com/xenia-canary/xenia-canary/issues/872) | Timing/performance; flag ignored in reported build 78d700a | RG-GDK-015 |
| [Canary #1220](https://github.com/xenia-canary/xenia-canary/issues/1220) | Functional/save persistence after crash; first-bad unknown | RG-GDK-017 |

Use the regression issue template with category (functional, rendering,
performance, stability, compatibility, vendor, GDK or build), last-good/first-bad
SHAs or `unknown`, title/module hash, subsystem, vendor matrix, reproduction,
logs/images/PIX as appropriate, upstream links, suspect change, workaround and
acceptance test. Label `regression` plus subsystem/vendor labels. Triage at each
port/release and during the monthly upstream review.

## Debug tessellation fixture, 2026-10-06

Found while validating the [Guide extraction](xbox-guide-extraction.md).
Standard Windows x64 Debug, Clang 22.1.8, VS 2026 Community, NVIDIA on the
development machine. `gpu.A tessellated quad patch covers the domain the shader maps`
fails at `src/graphics/pipeline/shader/dxbc_translator.cpp:551`, asserting
`register_count() >= 2` for the patch-indexed quad domain shader. Release
passes this fixture with assertions disabled; that does not validate the Debug
contract. No game assets are involved.

Reproduction: build Debug and run `gpu_tests.exe "[tessellation]"`, or the full
Debug CTest preset. Full extracted-suite result: 2,078 discovered, 2,066 passed,
11 skipped, one failed. The Guide-specific Debug suite passes 51 cases with
six private-asset cases skipped.

The same assertion independently reproduces after archiving and freshly
building pre-extraction SDK commit `d1a87b4ef0a09c7a7813ab2a2b27976de01de203`
with the standard preset's `-march=x86-64-v2` flags and original dependency
pins. This establishes an existing fixture/translator failure, rather than a
new Guide extraction regression. First bad and last good Debug revisions are
unknown. No assertion or GPU behavior was changed to hide it.

Local logs: `out/guide-ctest-debug.log`, `out/guide-original-debug-build.log`
and `out/guide-original-debug-tessellation.log`. Follow-up must reconcile the
fixture's domain shader register use with the translator's two-register
contract and pass the same test in Debug and Release. It stays unresolved;
the Guide extraction does not close or claim to fix it.

## Initial Windows D3D12 baseline results (RG-GDK-001)

This file records issue [RG-GDK-001](https://github.com/furqanagwan/rexglue-sdk/issues/1)
on the implementation branch rooted at `main`. The broader modernization roadmap
is being reviewed separately. [Baseline capture](baseline-capture.md) describes
the recorder, private run and exact limitations.

The first representative title is 007: Quantum of Solace (`415607FF`, media
`06DD88A0`). It compiles to a native executable, but initial boot fails before
a game log or screenshot. This is a **failing title result**, not a working or
partially working result. Gameplay, saves, audio, input and graphics have not
been assessed. No other title is selected until this one has a reproducible
boot scene. Synthetic unit and PPC tests remain part of every baseline.

| Workload | Owner | Current result | Evidence / next step |
| --- | --- | --- | --- |
| SDK unit and PPC tests | SDK maintainers | Debug/Release results in baseline capture | Preserve test logs and four explicit skips |
| Quantum of Solace boot | Furqan Agwan / SDK maintainers | Failing, `0xC000001D` | Private run manifest; locate generated `ud2` cause |
| Quantum of Solace gameplay/save/audio/input | Furqan Agwan / SDK maintainers | Not run | Requires boot and controlled repeatable scene |
| D3D12 NVIDIA | Furqan Agwan / SDK maintainers | Not run | Requires a scene reaching GPU initialization; record adapter/path/driver, log and screenshot |
| AMD and Intel GPU | External future coverage | Untested, non-blocking | User has no usable test access; do not claim compatibility |
| April 2026 GDK deployment | SDK maintainers | Not run | The ordinary Windows preset is not GDK validation |

For future changes, preserve the first result, rerun the same scene and compare
module/generated-code hashes, config, selected GPU path, logs and images. Use
disposable saves for failure tests. A compile pass cannot upgrade a title or
vendor result. Missing hardware results are marked untested; per the user's
[documented decision](adr/ADR-007-local-gpu-validation-scope.md), AMD and Intel
GPU coverage does not block local completion.

The known generated branch from `0x824A287C` to `0x821C1BF8` emits `REX_FATAL`.
The observed boot crash is an illegal instruction at a different generated code
offset; its cause is still unknown. Keep these as separate investigation items.

## Game-source and removable-media regression gates (2026-10-07)

[ADR-014](adr/ADR-014-game-source-and-media-recovery.md) replaces mapped image
pages with checked reads. Synthetic disc tests reject malformed headers,
cycles, unsafe names and out-of-range payloads; alignment fakes enforce sector
and buffer requirements. Actual image truncation exercises failure on an
already-open handle. Concurrent recovery keeps existing entry pointers,
rejects changed layouts and never blocks a UI-thread read on its own dialog.
Cancellation releases waiting workers, including during retry validation.

Game-source tests cover executable fingerprints, custom guest paths, original
inputs for TU builds, extraction completion/cancellation/read failure,
existing destination preservation and game:/d: runtime mounts. ImGui tests
cover validation-before-launch, persistence, mismatch rejection, Leave Game,
shutdown without launch, and controller disconnect/disposal. Leave Game uses
the same window-close path as the Guide; UI-only tests do not prove title
termination or painted GPU presentation.

Before closing #154, run each real first-run choice, source-original/TU
launches, image removal on a substituted/removable drive and physical optical
media removal/reinsert with the same and a different disc. Preserve saves and
use disposable copies for failure injection. Painted XuiMessageBox3/Active
Downloads and physical pad checks remain open. Results and the existing Debug
GPU assertion are recorded in [release evidence](release-evidence.md).

The scene adapter additionally tests the private reference's native choice
controls and Active Downloads template, safe initial Leave focus, controller
A activation without a prior directional input, extraction completion history
and local-folder handoff. Invisible ImGui hit targets must explicitly opt in
to navigation. Controller activation must make the navigation cursor visible;
otherwise ImGui ignores the first A press. Both gaps were caught and fixed
before publication. A temporary fixture collision during concurrent SDK test
processes was resolved with per-process source/disc fixture paths; final full
Debug and Release suites run sequentially. This is a test-fixture correction,
not a title compatibility claim.

The recovery fallback additionally tests first controller A on the initial
Leave Game choice, so absent Guide assets preserve the same safe default.
