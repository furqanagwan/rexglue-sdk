# Xbox guide

The Xbox 360 guide over a running title, built from the console's own scenes
([ADR-011](adr/ADR-011-xbox-guide-from-system-xui.md),
[RG-GDK-041](https://github.com/furqanagwan/rexglue-sdk/issues/127)).

Status: the format layer is in (part 1). The XUI runtime (part 2) and the guide
itself (part 3) are in progress.

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
  `...Center`, `...Ellipsis`, `...NoWrap`): 0x10 no wrap, 0x200 right,
  0x400 centre, 0x4000 ellipsis, 0x100 probably vertical centre. 0x1, 0x1000,
  0x4000000 and 0x8000000 are unknown.
- Fonts: the console's `.xtt` fonts are encrypted. Segoe UI stands in for
  Segoe Xbox, so the private-use gamerscore glyph in `btn_Count_achiev` has no
  equivalent.

## Validation

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
