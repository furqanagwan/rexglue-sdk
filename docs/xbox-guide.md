# Xbox guide

The Xbox 360 guide over a running title, built from the console's own scenes
([ADR-011](adr/ADR-011-xbox-guide-from-system-xui.md),
[RG-GDK-041](https://github.com/furqanagwan/rexglue-sdk/issues/127)).

Status: implemented in three parts: format layer, XUI runtime, guide. Checked
with Quantum of Solace (GDK Release, NVIDIA, 2026-09-30) through scripted
keyboard runs. An owner play session with a pad is still to do.

## Using it

- Open or close it with Back and Start together, with the Guide button where the
  input backend reports it (XInput with `--guide_button`, or the keyboard bind
  `keybind_guide`), or with Home (`bind_xbox_guide`). GameInput does not expose
  the Guide button, which Windows keeps for Game Bar.
- The system update is looked for in the `xbox_guide_system_update` cvar, then in
  `$SystemUpdate` beside the executable, then in
  `%LOCALAPPDATA%\ReXGlue\$SystemUpdate`. It loads in the background at startup;
  if none is found, the first open says so. `--xbox_guide=false` turns the guide
  off.
- Navigation: D-pad or left stick; LB/RB or left/right switch tabs; A selects;
  B goes back or closes; Y is Xbox Home. On the keyboard: arrows, Enter or Space,
  Escape or Backspace, Y, and Page Up/Down.

## What it does

It runs the console's own flow. The HUD backdrop plays `ClosedToHalf` and hosts
`GuideMain`, and the Home tab's blade comes in with `2Close`. Tabs change with
the `iToj` blade shuffles. Launching something plays `<tab>Open` with the
backdrop's `HalfToFull`. The Xbox Home and Turn Off prompts are the skin's
`XuiMessageBox3`, hosted in the backdrop's error frame (`HalfToError`). Button
focus, press and sounds come from the skin visuals' named frames.

- Games & Apps > Achievements opens `802_Achievements` as a grid of the title's
  achievements. Unlocked ones show their XDBF icon, others the console's
  unearned or secret image. The header shows the focused achievement; A opens
  `828_AchievDetails`. The button shows the gamerscore earned.
- Xbox Home (Y, or the Home tab) and Settings > Turn Off Console ask first. Yes
  closes the guide and ends the title through the window's normal close path.
- Everything else (Marketplace, My Games, media players, Live features) stays in
  the menu, disabled, as the console's disabled controls behave: they take focus,
  and pressing them plays the inactive sound.
- While it is open, the guest sees a neutral pad, XN_SYS_UI is true, and
  XamIsUIActive reports system UI, as for the Guide button on the console.
  Titles that pause for XN_SYS_UI pause.

On the console the Guide button never reaches the title. Back+Start does, so a
title may react to the Start press that completes the chord, for example by
opening its pause menu. The guide masks the buttons once it is open.

## Where the guide comes from

Dashboard 2.0.17559's system update (`$SystemUpdate`, as a USB update or console
dump) holds the package `su20076000_00000000` (PIRS/STFS). Its `$flash_*.xex`
files are unencrypted, LZX-compressed XEX2 images whose resources are XUIZ
packages:

| Package | Contents the guide uses |
| --- | --- |
| `hud/hud` | `GuideMain.xur`; the tab scenes `HomeTab*`, `GamesTab*`, `SettingsTab*`; `InfoMessage.xur`; `Strings.xus`; `BladeOpen.xma`, `BladeSwitch_1..4.xma`; battery and media icons |
| `huduiskin/skin` | `skin.xur`: the visuals controls name (`XuiButtonGuide`, `btn_Count_achiev`, `HUD_Bladedark`, `HUD_Bladegrey`, `legend_A/B/X/Y`, `Label_Head`, `XuiMessageBox2/3/4`...) |
| `huduiskin/xam` | `XamStrings.xus` (the Xbox Home confirmation, the achievement toast text) |
| `xam/xam` | `hudbkgnd.xur` (the backdrop's state machine), `HUD_open.xma`, `HUD_close.xma`, `Achievement.png` |
| `xam/skin` | blade nine-grid images, `btn_selectG.xma`, `btn_backG.xma` |
| `xam/shrdres` | button glyphs (`A-Button.png`...), `btn_Focus.xma`, `btn_Select.xma`, `btn_Back.xma`, `tab_Switch.xma`, achievement icons |
| `gamerprofile/gp` | `802_Achievements.xur`, `828_AchievDetails.xur` |

Scene paths are either relative to the scene's own package or use
`sharedres://`, which means `xam/shrdres`. Skin visuals name images that live
in `xam/skin`.

## XUR v8

All values are big-endian. A packed integer is one byte below `0xF0`, `0xFnnn`
in two bytes, or `0xFF` followed by 32 bits.

- Header: `XUIB`, version 8, flags, tool version (u16), file size, section
  count (u16). Then a count header of 12 packed totals, where the first is the
  object count. Then the section table: magic, offset and length per section.
- Pools: `STRN` (u32 length, u16 count, NUL-terminated UTF-8; index 0 is the
  empty string), `VECT`, `QUAT`, `FLOT`, `COLR` (ARGB), `CUST` (figure paths:
  length, box, point count, then anchor and two control points per point).
- `KEYP` holds packed keyframe values: literals for bool and integer types,
  pool indexes for the others. `KEYD` holds keyframes: packed frame, then a flag
  byte (0 linear, 1 none, 2 ease followed by signed ease-in, ease-out and scale
  bytes; 3, 0xA and 0xB carry extra data the runtime ignores), then the index of
  the first `KEYP` value. `NAME` holds named frames: name, frame, command (play,
  stop, go to, go to and play, go to and stop), and a target for the go-to
  commands.
- `DATA` is the element tree. Per element: the class name's string index, then
  a flag byte: 1 own properties, 8 shares an earlier element's properties
  (packed index), 2 has children, 4 has named frames and timelines. Properties
  start with a packed value count, then one packed mask per class, base class
  first, followed by that class's set values. Compound values (Fill, Gradient,
  Stroke) are written once and referenced by index after that. Indexed
  properties (gradient stops) carry a byte count. Timelines animate the owner's
  descendants. Each names its target by Id, then its properties as a class index
  into the target's chain (derived class first) and a property index per compound
  level, then its keyframe count and first `KEYD` index. A leaf element with
  flag 4 has no timeline count.

The schema (`src/ui/xui/schema.cpp`) lists only the classes the guide's scenes
use. Mask bits past a class's known properties are read as one packed value and
ignored, since every non-compound type except bool is one packed value (bool is
a byte, which reads the same). One finding: `AccountManagementNavButton` derives
from `GuideDashCommandNavButton`, which the Settings tab relies on.

## Inferred, not documented

These are unknowns kept deliberately. Revisit them if the runtime looks wrong
against the console.

- Timeline rate: 60 frames/s. A blade switch is 11 frames, about 183 ms. The
  reference recreation times it at about 155 ms. 30 frames/s would be twice
  as slow as the console feels.
- Ease: bytes are signed percentages. The guide's blades use in -100, out 100.
  The runtime's curve is a cubic Bezier fit, not XUI's own formula.
- Text style bits come from the skin's named label visuals (`...Right`,
  `...Center`, `...Ellipsis`, `...NoWrap`, `..._V`): 0x10 no wrap, 0x200 right,
  0x400 centre, 0x1000 vertical centre, 0x4000 ellipsis, 0x1 bold (button
  labels and legend letters have it, the header does not). 0x4, 0x100,
  0x4000000 and 0x8000000 are unknown and ignored. Message box bodies
  (`XuiEdit`) wrap.
- Anchor bits: 1 left, 2 top, 4 right, 8 bottom, 0x10/0x20 centre, 0x40/0x80
  scale. They fit how the button visuals stretch.
- A Fill without FillType is solid; a Stroke without StrokeWidth draws
  nothing. The separators and focus tabs only look right that way.
- GuideMain's `<tab>Open`/`<tab>Close` frames take a tab's blade out and bring
  it in. The names read backwards until the keyframes are checked (Tab2's
  opacity falls in `2Open`).
- Fonts: the console's `.xtt` fonts are encrypted. Segoe UI stands in for
  Segoe Xbox, so the private-use gamerscore glyph in `btn_Count_achiev` has no
  equivalent.

## Validation

- `unit_tests [guide]`: the chord (once per press, held-at-start, Guide
  button), pad actions (buttons held at open ignored, direction repeat, stick,
  bumpers).
- `unit_tests [xui]` also covers the runtime: visuals and anchoring, frame 0 on
  build, eased playback and stop frames, sound cues, per-element compound
  animation, navigation over hidden controls, focus, path resolution; and
  `[ui_sound]` covers XMA file decoding. With `REXGLUE_SYSTEM_UPDATE`, `[local]` also
  plays GuideMain's `2To3` shuffle and decodes every guide sound (all audible).
- Quantum of Solace, 2026-09-30: opened with Home; Home tab, Games & Apps,
  Media; Achievements grid (50, 0 unlocked) and details; Xbox Home prompt with
  cancel and reopen through Y; close. No errors in the log.
- `unit_tests [xui]`: synthetic XUIZ, XUIS, XUR v8 (elements, shared and
  compound properties, gradient stops, timelines with compound paths, named
  frames, truncation, unknown classes, object count) and XEX2 resources (plain
  and basic compression, encrypted images refused).
- `unit_tests [local]` with `REXGLUE_SYSTEM_UPDATE` set to a `$SystemUpdate`
  folder: loads the package through the SDK's STFS device and LZX decoder, then
  decodes every non-Kinect scene in `hud/hud`, `huduiskin/skin`, `xam/xam` and
  `gamerprofile/gp` (2026-09-30: all pass on the 17559 package recorded in the
  [tracking ledger](upstream-tracking.md)). The Kinect scenes use ControlPack
  classes outside the schema.
