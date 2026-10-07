# Xbox backward compatibility PC experience

This work covers the host experience as well as the in-game Guide. It does
not certify title compatibility. Fuzion Frenzy is an original Xbox title;
matching its PC host experience does not add original Xbox execution to this
static Xbox 360 SDK.
The [Guide issue audit and package-layer checks](guide-issue-audit-20261007.md)
record which implementation issues are closed and corroborate the installed
XeFu/Xbox 360 compatibility layers. The reference's native translation details
are research findings, not an official architectural specification.

## Reference and evidence

Microsoft describes resolution scaling, VSync, window modes, filtering,
anti-aliasing and language/audio controls in its
[July 2026 PC announcement](https://news.xbox.com/en-us/2026/07/22/xbox-backward-compatibility-on-pc/).
It also describes digital entitlements and Play Anywhere. Its announced
original Xbox achievements are future work, not evidence of an implemented
feature in this reference title.

Read-only inspection on 2026-10-06 of the installed Fuzion Frenzy package found
a separate EmuMenu launcher, launch arguments for graphics/audio behaviour,
MicrosoftGame.config, a native ICO, ShellVisuals, a shader cache and console
Flash files. The title menu data offers System, German, English, Spanish,
French and Italian via launch-time locale arguments. These are package
observations; no interactive gameplay, cloud synchronisation or online service
behaviour has been verified. Microsoft binaries, assets and service identities
are not incorporated into the SDK.

Reference metadata SHA-256: LaunchArguments.txt
`bdb7a45bf9b4916960a477ff84472b06996ea4a41ca0358df17a0867a13c639b`;
EmuMenu/Assets/TitleMenuData.json
`8881c5fbb09f9dcead7b9d7cd40f088374ae904247214083a221e3e8a8c2fef1`.
Private Flash-based tests subsequently passed for the reference's three-tab
scene layout/transitions and font conversion, as recorded below; this is not
interactive service/gameplay validation.

## Coverage and remaining gates

Issue states were checked on 2026-10-06. A closed implementation issue does not
prove parity with the installed reference or compatibility with every game.

| Experience | SDK/component behaviour and next gate |
| --- | --- |
| Pre-launch settings | Opt-in `launch_menu` now offers graphics, audio and language before runtime construction, with keyboard/mouse and physical-controller navigation. Interactive presentation and hardware checks remain. |
| Language | One resolver now supplies XGetLanguage, XConfig and XDBF title/achievement metadata. `user_language=0` follows Windows; explicit IDs 1–12 remain supported. Title language availability still depends on the game. |
| Native EXE art | `title-art` and the CMake icon helper now generate/embed multi-size title icons. [SDK #164](https://github.com/furqanagwan/rexglue-sdk/issues/164) stays open: existing title installations and Xbox app cached artwork have not been updated/verified. |
| Xbox library / packaging | Existing gameconfig and library-art tools produce package metadata and library tiles. Loose config and an EXE icon do not register a Store product. Own package registration and Xbox app presentation remain deployment gates. |
| First-run game source | Checked ISO/disc/folder selection, persisted sources, cancellable extraction and Retry/Leave Game recovery now exist in the SDK. [SDK #154](https://github.com/furqanagwan/rexglue-sdk/issues/154) remains open for interactive scene, physical-drive/title validation and friendly mismatch names; see [ADR-014](adr/ADR-014-game-source-and-media-recovery.md). |
| Original / title update launch | Existing separate static executables and update manifest preserve generated-code boundaries; see [title updates](title-updates.md). End-to-end original/TU switching needs representative-title evidence. |
| Guide / notifications / keyboard | Sources and issues belong to [xbox-guide](https://github.com/furqanagwan/xbox-guide). [Guide #1](https://github.com/furqanagwan/xbox-guide/issues/1) remains open for complete console scene support; closed fidelity work still has owner checks. Private assets are required for real scene tests. |
| Profiles / local achievements | Existing guest profiles, local achievement persistence and Guide presentation. These are local guest services; Xbox account linking and service achievements remain separate integration work. |
| Saves | Existing per-user Saved Games paths and preserving migration; see [data locations](data-locations.md). Cloud conflict, offline/reconnect, cancellation and account-switch gates require own service configuration and disposable save copies. |
| Sign-in / entitlements / cloud / online | No parity claim. Own Partner Center title registration, service configuration and test users are required. The installed game's identity cannot be reused. Guest multiplayer protocols also require title-specific research and tests; host sign-in alone does not implement Xbox 360 networking. |
| Input / handheld | Existing GameInput/XInput and mouse/keyboard guest input, assignment, Guide chord and battery UI. Launcher navigation now uses a temporary physical-controller reader and consumes held input before guest launch. Physical controller, touch UX and handheld hardware checks remain. |
| Graphics settings | Existing D3D12 scaling, filtering, VSync, FXAA and selective upscaling; supersampling was chosen over true MSAA boost in [ADR-012](adr/ADR-012-selective-upscaling-and-msaa-boost.md). Startup menu uses existing settings without adding shader changes. [SDK #182](https://github.com/furqanagwan/rexglue-sdk/issues/182) still blocks NHL visuals; AMD/Intel and title-specific fidelity remain unverified. |
| Audio / lifecycle | Existing XAudio2 master volume, mute and mute-on-minimise; menu exposes those controls. Reference suspend/constrained timing and output-device behaviour need interactive regression evidence. |
| Startup / shader stutter | Existing shipped shader cache and shader replacements. [SDK #120](https://github.com/furqanagwan/rexglue-sdk/issues/120) remains open for gameplay hitches. No arbitrary frame-rate unlock is promised. |
| Native ARM64 / storage | [SDK #45](https://github.com/furqanagwan/rexglue-sdk/issues/45), [#46](https://github.com/furqanagwan/rexglue-sdk/issues/46) and [#42](https://github.com/furqanagwan/rexglue-sdk/issues/42) remain host/deployment work, with hardware and representative-title gates. |

Local launch/settings/art and the source/I/O foundation are implemented, with
interactive and deployment gates still open. Preserve the runtime's per-user
save contract when integrating source selection with console scenes. Account/cloud work
needs a settled guest-to-host service design and an independently registered
title. Each integration must document failure, cancellation, offline behaviour
and account switching before claiming parity.
Microsoft documents the identity requirement in
[GDK title setup](https://learn.microsoft.com/en-us/xbox/gdk/docs/gdk-dev/get-started/get-started-home?view=gdk-2604)
and [Game Saves setup](https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/game-save/game-saves-developer-guide?view=gdk-2604).

## Launch settings

Run a rebuilt host with `--launch_menu=true`, or opt the title in through
`rexglue_configure_target(my_title CVAR_DEFAULTS "launch_menu=true")`.
The screen appears after host presentation and any title path wizard, before
guest runtime construction. Play continues the existing launch path; Exit
quits without starting guest execution. Closing the host also disposes the
dialog without invoking Play. Existing direct launch remains the default.

Graphics controls appear only when their GPU plugin flags are registered.
Render scale offers Match display or explicit 1–4 scaling on both axes;
explicit choices disable automatic display matching, including on later launches.
Title custom scales are shown as Custom.
These settings use the registry's validation and normal change callbacks.
Remember settings writes the existing per-title config. Unchecking it keeps
changes for this session; Exit does not write them. A save failure keeps the
menu open with a recovery message; session-only Play remains available. The existing F4 advanced
settings screen remains available during gameplay.

The launcher reads physical GameInput/XInput controllers without adding the
guest's synthetic keyboard or fallback controller. D-pad/left stick navigates,
A activates, B backs out and LB/RB changes tabs. Disconnect releases ImGui
navigation input. The temporary reader is disposed before guest setup; the
normal input system consumes held buttons and keystrokes before execution.
Physical controller navigation and the handoff still need a hardware check.

`user_language` defaults to English for existing projects. Use 0 for Windows
locale selection or IDs 1 English, 2 Japanese, 3 German, 4 French, 5 Spanish,
6 Italian, 7 Korean, 8 Traditional Chinese, 9 Portuguese, 10 Simplified Chinese,
11 Polish, 12 Russian. Unsupported Windows locales fall back to English;
Chinese script overrides region. XDBF metadata falls back to the title's own
available language; this does not manufacture translated game content.

## Game sources and media recovery

Regenerate a title's code to embed the original XEX title ID, full-file checksum
and guest-relative executable path. Title-update builds identify the original
source before applying their update. Older generated hosts retain folder
launching; they need regeneration for checked image selection.

A new host checks its configured source before constructing the guest. If
missing or mismatched, Choose game files offers an extracted folder, ISO or
optical drive. Check source verifies the XDVDFS structures and exact executable
identity. Remember source persists an absolute `game_source` path; an explicit
`--game_data_root` takes precedence. These choices preserve save/profile paths.

An image can run directly or use Extract to this PC. Copying runs in the
background, reports byte progress, supports cancellation between reads and
switches to a new local folder only after completion. Existing destinations
are never overwritten. Failure removes only the operation's owned staging
folder. Closing before launch cancels source checks/copying without starting
the guest.

Image reads use checked file I/O. Optical reads use sector-aligned unbuffered
I/O restricted to optical drive-letter devices. A missing game partition
explains the need for a compatible Kreon-style drive; no firmware operation or
alternate access method is attempted. Physical drive compatibility is pending.

A failed guest media read offers Retry or Leave Game. Retry checks the original
executable and directory layout before reconnecting existing handles. Leave
uses the Guide's window-close/termination path. Shutdown releases waiting I/O;
UI-thread reads return errors instead of waiting for their own dialog.

Both dialogs support physical-controller navigation, with disconnected/held
input released before guest handoff. Tests draw ImGui; physical pad behaviour
and painted presentation are still unverified. When private Guide assets finish loading, source and recovery choices use the
console's XuiMessageBox3 visual; while loading or without assets the controls
use the host fallback. Extraction progress uses the console Active Downloads
scene with nonblocking cancellation. Completed/cancelled/failed copy results
remain in the Guide's Active Downloads alongside title-update jobs. The source
file picker and validation controls stay host-native.

Friendly mismatch game names, original/TU title launches, painted scene/pad
interaction and real media-removal checks remain gates for [SDK #154](https://github.com/furqanagwan/rexglue-sdk/issues/154).

## Native title art

Use art you supply locally:

```powershell
rexglue title-art --image metadata/title.png --output gdk
```

This generates Title.ico (16/24/32/48/64/128/256) and the existing five
ShellVisuals PNG names/sizes. Images are scaled to cover and centred; provide
art with important content in the centre. Smaller ICO frames are straight-alpha
BGRA bitmaps with transparency masks; the 256 frame is PNG. Existing artwork
causes a failure before writing unless `--force` is specified.
MicrosoftGame.config and its identity are preserved.

`rexglue_configure_target` automatically embeds `gdk/Title.ico` when present at
configure time, for each original/TU host target. Alternatively:

```cmake
rexglue_configure_target(my_title ICON "${CMAKE_CURRENT_SOURCE_DIR}/art/title.ico")
```

The independently usable `rexglue_embed_title_icon(target path)` helper embeds
RT_ICON and RT_GROUP_ICON without replacing the linker's application manifest.
Generate art before configuring; reconfigure an existing project to add it.
Replacing the ICO then rebuilds resources through its dependency. Do not
embed the same icon through a second hand-authored resource file.

The native EXE icon serves Windows Shell. The runtime window uses XDBF art.
A registered GDK package uses ShellVisuals. Xbox app library artwork can be
cached: verify an installed package's registration and refresh/re-add its
library entry when validating changed art. A loose XML file does not prove
registration or service entitlement.

## Validation

Run targeted unit tests with `[language],[library_art],[cvar]`. They check all
explicit language IDs against the actual XAM entry and big-endian XConfig,
System resolution, unsupported locales, Chinese script precedence, ICO frame
dimensions/colour/alpha and configuration contracts.
Include `[launch_settings]` for the actual ImGui Play/Exit actions, Remember
persistence, failed-save recovery, controller activation/tab changes,
disconnect/deadzone handling and shutdown without completion. Include `[input]`
for the physical-only factory and existing input handoff contracts. These draw
the UI in a hidden-window context without submitting GPU frames.

`tests/consumer/launch_settings` is an installed-SDK consumer that builds and
links a complete host plus the GPU plugin. With a painting surface it records
whether the launcher draws before guest setup and then quits; it uses no game
data. Hidden-window GPU execution did not produce a painted frame locally, so
this consumer's end-to-end rendering check remains pending on an interactive
surface. The synthetic ImGui checks do not prove a GPU-rendered UX.

In an x64 VS developer shell:

```powershell
python scripts/test_title_art.py --rexglue out/win-amd64/Release/rexglue.exe --work-dir out/title-art-consumer
```

This uses synthetic artwork, verifies image dimensions/overwrite protection
and retained config, builds separate base/TU consumer EXEs, and checks native
icon resources, manifest and Shell extraction. It does not inspect or change
installed games. Interactive GUI/physical-controller checks, Xbox app registration/cache checks,
real-title language/render checks and online/cloud gates remain pending.
