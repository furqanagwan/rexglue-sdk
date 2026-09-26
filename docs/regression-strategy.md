# Compatibility baseline and regression strategy

## Current baseline

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

Titles below are **proposed regression workloads**, selected from reviewed
upstream evidence; availability, static recompilation readiness and local results
are unverified. Use synthetic fixtures immediately when a title cannot yet run.

| Workload | Candidate title / upstream evidence | Repeatable gate |
| --- | --- | --- |
| Kernel import ABI and file IO | Dead Rising; Edge `887beea69` | Synthetic NtOpenFile import with distinct ShareAccess/OpenOptions; later boot/load/save |
| ZPD and lens flares | Crackdown 2; Canary #1218 | Occluded/unoccluded scene, strict vs fast/readback modes, query ID reuse/wrap and MSAA |
| Scalar shader math | Ace Combat 6; Canary #1190 | rcp/rsq/log/exp edge values and ground rendering; unrelated shader controls |
| EDRAM depth aliasing | title `4D530A26`; Canary #1222 | Color→depth→color bit preservation, occluded sprites, 1x/2x/4x sample readback |
| AMD sample layout | title `4D5307F1`; Canary #1238 | Canonical EDRAM before/after depth-copy fixtures, exact sample indices |
| Texture addressing | Golden Axe Beast Rider `534507E5`, `4E4D0855`; #1243 | Volume/array/mip packing and 96bpp pitch with independently computed byte ranges |
| Sub-32bpp resolve | `534307D5`; #1240 | 8/16bpp offsets crossing 4KB and x=480 stripe; scaling and MSAA |
| Memexport and memory pressure | UFC Undisputed 3 `5451087D`; #1093 | Stock and created fighters, packed signed exports, near-full heap, CPU readback |
| Decal depth | Lost Odyssey `4D5307FA`; Edge #278 | Same camera/input, old clamp and proposed offset isolated, unrelated FH2 control |
| Async IO timing | UEFA CL 2006–2007 `45410811`; Edge #275 / timing commits | Match load, physical allocation peak, sequential/random read deadlines and no global cap |
| Scheduler/exception stability | NFS Shift; Edge #233; Riddick in #234 | Repeated scene load under contention and watchdog; preserve static unwind/callbacks |
| XMA loops | Tekken Tag 2, Koei titles; Edge `5dd1cdbbf`, #141 | Exact/one-bit-early loop start, multiple loops, PCM continuity and context progress |
| XMA decode failure | LEGO LOTR `5752081D`; Edge #235/#236 | Packet boundaries/error propagation; intro progress; no silent substitution masking failure |
| XMA multistream | DJ Hero 2; Canary #438 | Independent stream stems, channel ordering and simultaneous context consumption |
| Audio lifecycle | 007 Legends `415608D8`, SCDA, Dark Souls; Edge #120/#113/#164 | Menus/scene transition/teardown, callback lifetime and device removal |
| Content/profiles/notifications | Guitar Hero 5 DLC; #1225/#1226; Army of Two #1220; BO2 #1135 | Truncated package, object reuse, two-profile crash/restart persistence, listener masks |
| Input | Guitar Hero subtype #1230; synthetic four-pad app | Connect/disconnect/reconnect, slot stability, whammy neutral, rumble, focus and mouse merge |

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

RG-GDK-019 XAudio2 output (2026-09-26): opt-in `audio_backend = "xaudio2"`
(SDL stays default). `unit_tests [audio][conversion]` checks per-channel impulse
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

RG-GDK-021 native Win32 window (2026-09-25): opt-in `ui_backend = "win32"`
(SDL stays default). `unit_tests [ui][win32]` covers creation, DPI-scaled size,
resize, minimize and restore, fullscreen round trip, close veto versus
programmatic close, key and gated character input, and cross-thread UI
calls. `gpu_tests [gpu][win32]` presents D3D12 frames through the Win32 window
on WARP and NVIDIA across resize, minimize and restore, and closes with the
presenter attached. SDL consumers and owners are in `docs/windowing.md`. Not
run: titles, multi-monitor DPI moves, and AMD or Intel presentation.

RG-GDK-020 GameInput (2026-09-25): opt-in `input_backend = "gameinput"`
(GDK builds; SDL stays default). `unit_tests [input][gameinput]` covers the
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
run: the ROV path (falls back to fake results; #64), AMD/Intel, VIZ (#65) and
Crackdown 2 flares with the resolve readback modes (no title content).

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
