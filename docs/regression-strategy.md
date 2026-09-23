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
| NVIDIA, modern and older compatible device | Edge #204 report was closed for tracker scope; Canary #1093 RTX 4070 Ti SUPER memexport report | Async pipeline lifetime, stock/created fighter geometry, stencil, readback, hybrid-adapter selection | RTX 5080 Laptop detected, driver 32.0.16.1714; not run |
| Intel Arc and non-Arc separately | Canary #608 non-Arc native stencil failure; local Intel fallback rules | Stencil export toggle/fallback, host-RT/ROV if supported, clears, bandwidth and unified memory | Intel Graphics detected, driver 32.0.101.6129; model class/caps not established; not run |
| WARP | Deterministic API validation and CI smoke only | Resource/state/descriptor checks where supported | Not run; cannot certify a vendor |

Run each selected GPU on ordinary Windows development deployment and intended
GDK title deployment. Record OS/driver/GDK versions rather than assuming newest
means correct. Run correctness at native scale first, then 2x resolution and
1x/2x/4x MSAA where guest fixtures support them. Test cold/warm caches and
foreground/minimize/resize/device removal. No optional feature should become an
implicit prerequisite without an explicit support policy change.

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
