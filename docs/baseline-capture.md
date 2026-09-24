# Baseline capture workflow

## Current checkpoint (2026-09-24)

The baseline recorder, assessment and negative tests are in place. Windows x64
Debug and Release SDK builds pass; the latest full CTest runs discovered 1,675
tests per configuration, with four existing explicit BitStream skips. The
private Quantum of Solace title reaches changing early 3D views on the NVIDIA
D3D12 path. This is a **partial rendering observation**, not a gameplay, input,
audio, save/load, visual-accuracy or GDK deployment pass. The interactive route
is owned by [007 issue #16](https://github.com/furqanagwan/007/issues/16), and
the GDK build/deployment gates are [RG-GDK-002](https://github.com/furqanagwan/rexglue-sdk/issues/2)
and [RG-GDK-022](https://github.com/furqanagwan/rexglue-sdk/issues/22).
The 2026-09-23 failure sequence below is retained as historical evidence.

Implementation starts with RG-GDK-001. The first title is **007: Quantum of
Solace**. Keep its ISO, extracted modules, generated code, saves and captures
outside this repository. Work through boot, menus, a repeatable gameplay scene,
save/reload, audio/input and rendering before expanding to another title.
Synthetic unit/PPC tests and hardware validation remain required alongside it.

`scripts/capture_baseline.py` writes a new run directory containing `run.json`,
stdout/stderr logs and SHA-256 hashes. Existing directories are rejected.
Pass `--artifact path` for each screenshot, PIX capture or diagnostic log to copy
and hash it in the same run directory.
The manifest follows [baseline-run.schema.json](baseline-run.schema.json).
Use an explicit executable path and a finite timeout. Run from the title's
required working directory; the recorder records that directory.

```powershell
python scripts/capture_baseline.py --output C:/private/runs/qos-boot-001 --title QuantumOfSolace --material C:/private/qos/default.xex --metadata C:/private/qos/environment.json --artifact C:/private/qos/boot.png --timeout 120 -- C:/private/qos/QuantumOfSolace.exe
python scripts/assess_baseline.py --run C:/private/runs/qos-boot-001 --output C:/private/runs/qos-boot-001-review.json --status fail --reviewer maintainer --reason "Boot fails before the menu; see the hashed run artifacts"
python -m unittest discover -s scripts/tests -p 'test_*baseline.py'
```

The optional metadata file is a JSON object. Record compiler, Windows SDK, GDK
(or `not used`), build configuration, GPU model/driver, adapter selection,
RTV/ROV path, title/media/version IDs, scene, configuration hashes and owner.
Unmeasured values must remain `unknown` or `not-run`. The recorder fills the
standard fields with `unknown` when omitted. Metadata is embedded and hashed;
it cannot override the recorder's result or artifact fields.

An exit code of zero means only that the process completed. Compatibility stays
`not-run` until scene evidence is reviewed. Missing material/executable produces
`blocked`; a nonzero exit or timeout produces `fail`. Exit status 1 includes
blocked runs. Preserve the manifest and artifacts; write review findings in a
separate assessment referencing their hashes. Do not edit a failed run into a
pass. `assess_baseline.py` creates that separate record and checks the run and
artifact hashes. It refuses to mark a failed, timed-out or blocked run as pass.
An assessment output path must be new. The timeout controls the launched process, not a launcher-created process
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
* ISO SHA-256 `586870e30447704b9d029ea05136475cad7de55f444b9135163fce0fd393321e`.

The private project scaffold and code generation completed (175 output files).
Code generation reported an unresolved branch from `0x824A287C` to `0x821C1BF8`;
generated code emits `REX_FATAL` for this edge. The destination is also a local
label in another generated function, so function-boundary/shared-tail analysis
is needed before choosing a correction. Do not substitute a no-op.
The private project configured, compiled and linked against the installed
Release SDK. All 16,617 disc files were extracted to a private game root. An
isolated boot smoke run on 2026-09-23 exited after 2.69 seconds with Windows
exception `0xC000001D` (illegal instruction) before a game log or screenshot was
produced. Windows Event Log fault offset `0x01A30CEE` maps to a generated `ud2`
after a range check. The exact guest function and cause remain under
investigation; do not assume it is the unresolved branch above. Boot is
**failing**. Gameplay, saves, audio and rendering remain **not-run**.

Private evidence: `../007/Quantum of Solace/baseline/smoke-20260923/run.json`
and `smoke-20260923-assessment.json`. The assessment hashes the run manifest
(`eabc23a77529fc31b6b06c8a3db7e6f64a670f09b1869eef0f15fb121b9b0fc8`)
and records `fail`. The Windows Event Log record at 20:46:08 local time is saved
as `smoke-20260923-event.txt` (SHA-256
`e035af020480e51399b779ee5d723df9f527a802fffdbc0fd158f783f073bb91`).
The run used an isolated user data directory.
No GPU path was reached, so there is no meaningful D3D12 screenshot or PIX
capture from this scene. The executable and generated title sources are private.

The same title command was repeated with the same metadata, XEX, executable and
user data root. Both runs exited `0xC000001D` and had identical material,
executable, metadata and empty stdout/stderr hashes. Durations were 2.69s and
2.57s; timestamps/durations naturally vary and worktree status changed during
tool development. The second reviewed manifest SHA-256 is
`a209e63c111974e3efc25f6afe25a2065a2a9b1e9525dd6ae02575478f12c102`.
The recorder tests repeat a synthetic fixture and compare its stdout hashes.
The user confirms NVIDIA is the only available GPU test target. AMD and Intel
GPU coverage is untested and non-blocking by the user's explicit decision
([ADR-007](adr/ADR-007-local-gpu-validation-scope.md)).
Earlier adapter enumeration
does not establish usable Intel GPU test coverage. At this 2026-09-23 checkpoint,
NVIDIA rendering remained unvalidated.
April 2026 GDK deployment remains untested. RG-GDK-001 stays open until its
acceptance and evidence requirements are satisfied.

## SDK build and test evidence, 2026-09-23

Baseline configuration: x64 Visual Studio 2026 developer environment (`VSCMD_VER
18.0`), Clang 22.1.8, CMake 4.4.3, Windows SDK `10.0.26100.0`, D3D12 ON,
Vulkan OFF, tests ON, pinned submodules initialized. April 2026 GDK is installed
locally (`260404`) but not selected by this ordinary Windows preset; GDK build
or deployment is not claimed.

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
fix, full CTest runs on branch `RG-GDK-001` passed in both configurations:
1,667 executed successfully and four BitStream write tests remained skipped per
configuration. The skips are coverage gaps, not passes. These results establish
a build/test starting point, not a game, GPU or GDK compatibility baseline.
Raw logs are retained privately under `../007/Quantum of Solace/baseline/`.

## RG-FIX-001 jump-table regression, 2026-09-23

The first boot failure was traced to `sub_821C1B90`: `lwzx r8,r10,r9` uses
scaled `r10` as the index and `r9` as the table base, but code generation
selected `r9` as the switch index. The absolute table also has a zero entry at
slot 20 followed by valid entries through slot 38. The focused scanner fix
recognizes the alternate indexed-load operand and preserves bounded internal
zero gaps. A synthetic test covers both operand orders with and without a gap.
The regenerated private title now switches on guest `r3`, includes slot 26,
and no longer hits the prior `0xC000001D` trap.

Debug and Release SDK builds succeeded. Each full CTest run discovered 1,672
cases (214 unit, 1,458 PPC): 1,668 passed and the same four BitStream cases
were skipped. Two repeated title runs on the NVIDIA GeForce RTX 5080 Laptop
GPU (DXGI vendor `0x10DE`, device `0x2C19`) selected the D3D12 Xenos plugin
and both exited `0xC0000409`. Their title logs report the same next failure:
`[FATAL] Call to invalid or unregistered function at guest address 0x8211E798`.
Private run manifests are `rgfix-nvidia-boot-1/run.json` and
`rgfix-nvidia-boot-2/run.json`; title logs are `quantumofsolace_011.log` and
`quantumofsolace_012.log` under the private project build logs. The unchanged
XEX, executable and metadata hashes are recorded in those manifests. This is
still a failing boot; rendering, gameplay, saves and GDK deployment remain
unvalidated. The invalid guest call requires a separate investigation.

| Private artifact in `sdk-20260923` | SHA-256 |
| --- | --- |
| `rg001-build-debug.log` | `0c9c4cf15fc56c0897403fdcbbae7cf5b323d00ef1dc41371442814b7dabc313` |
| `rg001-build-release.log` | `9cc1a6c6f4c5f4d0c47b1fc3aa205b991f71457bd7a8ff80974357dfb343fd5c` |
| `rg001-ctest-debug-final.log` | `d32070d8afa06eda427c5196052d34174aeea9e12a9fe1c3e7278f3545a77ce1` |
| `rg001-ctest-release-final.log` | `077e2b433f211d37d076b17c5ff94b6f311c63fcf4f6720f76ae2908fe503d71` |

## NVIDIA D3D12 evidence after the initial boot failures

The 007 project remains the only selected game workload. Its owner is
`furqanagwan`; the private XEX hash and title/media IDs above are unchanged.
The SDK host/runtime and title configuration are tracked separately, so no
game payload or private screenshot is committed here. Two 45-second launch
runs after the relative-path fix reached their timeout without a fatal or
`scaleform` path failure. Their recorder statuses are `fail`/`timeout` by
design; a timeout is not a compatibility pass. These runs used an SDK worktree
with the relative-path fix before merge, so they are diagnostic rather than a
clean-revision last-good baseline.

| Private evidence under `../007/Quantum of Solace/` | SHA-256 | Finding |
| --- | --- | --- |
| `baseline/rgfix003-boot-3/run.json` | `f5b93058c5abab9aca547f41a7f4a1fd810daee00ff0bc2ddc4cff4679d7bc62` | Repeated 45-second boot capture |
| `baseline/rgfix003-boot-4/run.json` | `1af4ed78670a87b49b01e1c78e43f6e089aa54e53e1412cfa41821291c8c3c5b` | Repeated 45-second boot capture |
| `recompiled/out/build/win-amd64-release/logs/quantumofsolace_058.log` | `fbd9708aed5421a0783721245232fcd4e76f62373c97b9c8f8bdb96c79480a96` | Final diagnostic boot log |
| `baseline/rg007004-window-visual-1.png` | `c35de3155c9df028be5fcc8ea07731affe6c4aa8b1d122f35ef346b548667834` | Early 1280×720 D3D12 view |
| `baseline/rg007004-window-visual-5.png` | `ab0e88ecc9b4b858eb2dbbd57a4028a45f379c1b3afe1796803362daf04ee279` | A later view of the changing scene |
| `baseline/rg007005-window-1.png` | `b307d307e8add5c31ca2a326ad3acaa3dc8a16202155a44c37208dc0bc33fb7d` | Later mission-interface observation; input response inconclusive |

The window crops were taken during separate live observations and are not
claimed as artifacts of the timed recorder runs. [007's rendering record](https://github.com/furqanagwan/007/blob/main/docs/RG-007-004.md)
and [interactive checkpoint](https://github.com/furqanagwan/007/blob/RG-007-005/docs/RG-007-005.md)
contain the event sequence and limitations. The local adapter was NVIDIA RTX
5080 Laptop GPU, driver `32.0.16.1714`; the D3D12 Xenos plugin was selected.
RTV/ROV path and visual parity are not established. AMD and Intel GPU runs are
unavailable locally and non-blocking under ADR-007. A GDK-packaged run has not
occurred. No test here implies support for additional titles.

On 2026-09-24, following [RG-GDK-003's merged import fix](https://github.com/furqanagwan/rexglue-sdk/pull/48),
both full Windows x64 Debug and Release SDK builds passed. Each CTest run
discovered 217 unit and 1,458 PPC cases (1,675 total); all runnable cases
passed and four pre-existing BitStream tests were explicitly skipped. Six
baseline recorder/assessment Python tests passed. These are current SDK
build/test results, not a rerun of the private title on that exact revision.
