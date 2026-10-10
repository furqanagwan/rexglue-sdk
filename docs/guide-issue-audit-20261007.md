# Guide issue audit and title rebuilds, 2026-10-07

GitHub issue states were checked directly on this date, including the native
transfers from ReXGlue to xbox-guide. Closed means the implementation issue was
closed; limitations in its body and comments still apply.

| Current issue | Original SDK issue | State | Implemented scope |
| --- | --- | --- | --- |
| [Guide #1](https://github.com/furqanagwan/xbox/issues/1) | #127 | Open | Main console-scene Guide epic; owner title/pad acceptance remains outstanding. |
| [Guide #2](https://github.com/furqanagwan/xbox/issues/2) | #132 | Closed | Console styling corrections, Mods and developer cheat-code pages. |
| [Guide #3](https://github.com/furqanagwan/xbox/issues/3) | #143 | Closed | Home/exit navigation, removed Media blade and gamerscore glyph. |
| [Guide #4](https://github.com/furqanagwan/xbox/issues/4) | #145 | Closed | Build-time marketplace add-on catalogue and Manage Game presentation. |
| [Guide #5](https://github.com/furqanagwan/xbox/issues/5) | #153 | Closed | Optional title-update downloads, version-specific executables and Active Downloads. |
| [Guide #6](https://github.com/furqanagwan/xbox/issues/6) | #161 | Closed | Console keyboard scene/state and guest keyboard UI integration. |
| [Guide #7](https://github.com/furqanagwan/xbox/issues/7) | #166 | Closed | BC emulator scenes, fonts, storage page and wider glyph coverage. |

SDK-owned UI dependencies also remain in their original repository:
[resolution/battery rendering #137](https://github.com/furqanagwan/rexglue-sdk/issues/137),
[controller/battery input #139](https://github.com/furqanagwan/rexglue-sdk/issues/139)
and [achievement enumeration #141](https://github.com/furqanagwan/rexglue-sdk/issues/141)
are closed. The broader guest
[content/profile/notification audit #17](https://github.com/furqanagwan/rexglue-sdk/issues/17)
is also closed; this does not establish real Xbox Live service integration.
[First-run sources #154](https://github.com/furqanagwan/rexglue-sdk/issues/154)
and [native title artwork #164](https://github.com/furqanagwan/rexglue-sdk/issues/164)
are open.

## Acceptance limits

Guide #5 records that projects with guest DLL modules cannot yet build update
executables. Its Quantum of Solace TU2 check verified download/install/handover,
but encountered a missing generated function at `0x821C1C20`; it did not prove
TU2 gameplay. Each version needs its own reviewed function and patch catalogue.
Guide #7 records resolution checks through 4K, but requires an 8K display for
its remaining screenshot gate and a title check of Manage Storage. SDK #139
records that the Raikiri dongle/cable battery protocol remains unknown.
Guide #7's [font PR #167](https://github.com/furqanagwan/rexglue-sdk/pull/167),
[emulator-tab PR #174](https://github.com/furqanagwan/rexglue-sdk/pull/174) and
[storage/glyph PR #196](https://github.com/furqanagwan/rexglue-sdk/pull/196)
were independently confirmed merged.

The new reusable message-box/download models are in
[Guide draft PR #8](https://github.com/furqanagwan/xbox/pull/8).
Their SDK integration is in
[SDK draft PR #214](https://github.com/furqanagwan/rexglue-sdk/pull/214).
Both were open and unmerged when checked; local builds include these changes.
[Extraction PR #211](https://github.com/furqanagwan/rexglue-sdk/pull/211),
[host-experience draft PR #212](https://github.com/furqanagwan/rexglue-sdk/pull/212)
and [source-selection draft PR #213](https://github.com/furqanagwan/rexglue-sdk/pull/213)
also remain open and unmerged. A rebuild on this branch includes their work;
a checkout of SDK main does not establish the same feature coverage.
No issue was closed as part of this audit.

## Fuzion Frenzy layering

Microsoft's [PC announcement](https://news.xbox.com/en-us/2026/07/22/xbox-backward-compatibility-on-pc/)
confirms the PC release and its host settings, but does not document its CPU
translation architecture. The independent, first-hand
[binary analysis at b3609bc](https://github.com/stocktaylor/Xbox-BC-for-PC-Research/blob/b3609bc2385860d17d9bc0f8f8eb8020ab84f434/TECHNICAL_FINDINGS.md)
reports XeFu inside a rehosted Xbox 360 compatibility environment and static
PowerPC-to-x64 translation of the compatibility modules. This is an analysis
finding, rather than an official Microsoft architectural statement.

Read-only checks of the installed package on this date corroborate the layers:
`SystemPartition/Compatibility/xefu.xex` (667,648 bytes) and `xefutitle.xex`
(12,288 bytes) have XEX2 headers. The installed `xefu_*.dll` and sampled
`xeo3_11149*.dll` have native AMD64 PE headers (`0x8664`); the latter contains
`xefutitle` references. Launch arguments include `fusion`. This installation
also includes `Emu.exe`, unlike the earlier research sample, so its absence
must not be assumed. Header checks alone do not prove every internal translation
detail or establish how original Xbox game instructions are executed.

Thus “Xbox 360 compatibility environment running the original Xbox layer” is
supported; “two generic CPU interpreters nested together” is not established.
Our 007/FIFA/NHL projects are Xbox 360 titles and continue to use static PPC
generation directly. They do not need XeFu. No Microsoft executable, DLL,
service identity or game content is copied into the SDK or published.

## Rebuild evidence

Rebuild inputs are SDK `34ab1402c5e0428679a8cc239747211a865f1549` and Guide
`db55a4d347c9edc74a17632fd7f71311ea1e7410`, Windows x64 / GDK 260404 Release.
The existing title executables and saves are preserved. Each title uses a new
local `recompiled-bc-20261007` sibling of its existing project, fresh generated
source fingerprints, BC Flash plus 17559 Guide resources, native icon artwork,
and `launch_menu=true` / `user_language=0` title defaults. NHL retains its ROV
default. Quantum of Solace retains its recorded shader cache and existing TU2
configuration; FIFA Street
retains both guest DLL modules. Private generated code and embedded assets stay
in ignored local folders. All five projects generated, configured and built
successfully;
compilation does not establish gameplay or controller compatibility.

From the Downloads directory, each output folder is the title folder below
followed by `recompiled-bc-20261007/out/build/release`:

| Title folder | Built executables / guest modules |
| --- | --- |
| `007/Quantum of Solace` | `quantumofsolace.exe`, `quantumofsolace_tu2.exe` |
| `007/Blood Stone` | `bloodstone.exe` |
| `007/Legends` | `legends.exe` |
| `FIFA Street/FIFA Street` | `fifastreet.exe`, `fifastreet_fifadllzf_xex.dll`, `fifastreet_footballcompengzf_xex.dll` |
| `NHL/Legacy Edition` | `nhllegacy.exe` |

Final artifact checks passed for all five projects / six executables:
Windows Shell extracts both large and small icons from each EXE; staged
`rexruntime.dll` and `rexgpu-xenos.dll` match the isolated SDK prefix by SHA-256;
Guide bundles and the expected source title IDs/checksums are present; original
and TU2 source identities agree; both FIFA Street guest DLLs are staged; launch
defaults are compiled in. Quantum of Solace's staged shader-cache files also
match the recorded source cache. All six old executable hashes remain unchanged,
and all three title repositories plus the Guide submodule have clean Git status.

Local records are `out/bc-title-rebuild-20261007/results.json` (all generation,
configuration and build exit codes zero), `artifacts.json` (EXE paths, sizes,
SHA-256 and icon checks), `inputs-and-baselines.json` and per-title logs.
The GDK SDK targeted suite passes 54 cases / 662 assertions with private skin
assets; the separately attempted Xbox Unity live download timed out (`12002`).
Docs links, roadmap validation and whitespace checks pass. No staged game
executable was launched and no save/profile was modified. Painted startup/
Guide checks, physical controller/drive tests, real TU2 gameplay and wider
GPU/vendor/full-playthrough validation remain unverified; prior title status
is unchanged. No existing registered Xbox app installation was replaced.

FIFA Street generation still reports branch target `0x82EB07E0` from
`0x82EB0884`, plus two `BaseHeap::Release failed because address is not a
region start` messages at tool teardown. All appear in the preserved original
`codegen_first.log` and `codegen_2.log` as well as this run. Generation exits
zero; these findings are retained rather than claimed fixed. Its existing
magenta-crowd limitation and NHL's RTV-path problem are not changed by this
Guide rebuild. NHL continues to opt into ROV.
NHL's generator also warns that function `0x8301F830` exceeds the 1 MiB
preferred output-file size (2,235,541 generated bytes in this run). Its original
codegen log reports the same function warning (2,258,405 bytes); no size limit
or generation setting was changed to hide it.
