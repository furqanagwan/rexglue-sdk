# Xbox guide

The Xbox 360 guide over a running title, built from the console's own scenes
([ADR-011](adr/ADR-011-xbox-guide-from-system-xui.md),
[RG-GDK-041](https://github.com/furqanagwan/rexglue-sdk/issues/127)).

Status: implemented in three parts: format layer, XUI runtime, guide. Checked
with Quantum of Solace (GDK Release, NVIDIA, 2026-09-30) through scripted
keyboard runs. An owner play session with a pad is still to do.

## Using it

- Open or close it with View and Menu together (Back and Start on an Xbox 360
  pad), as Xbox Series backward compatibility opens the 360 guide, or with Home
  (`bind_xbox_guide`). The Xbox button is deliberately not a trigger: on PC it
  opens Game Bar, and the guide leaves it to Windows.
- The guide is built into the title, so players need nothing for it and it
  works offline. Whoever builds the title sets `REXGLUE_SYSTEM_UPDATE` (a CMake
  cache variable, or the environment variable of that name) to their own
  console's `$SystemUpdate` folder once, as they supply the game itself.
  `rexglue_configure_target`, which every title calls, then runs
  `rexglue guide-bundle` to take the four modules the guide reads (`hud`,
  `huduiskin`, `xam`, `gamerprofile`, about 2.7 MB) and embeds them in the
  executable with `.incbin`. Nothing from the update ships with the SDK. Note that
  a title built this way carries those console files; anyone passing the
  executable on passes them on.
- A build without `REXGLUE_SYSTEM_UPDATE` logs "Xbox guide not built in" and,
  at run time, falls back to the `xbox_guide_system_update` cvar, `$SystemUpdate`
  beside the executable, then `%LOCALAPPDATA%\ReXGlue\$SystemUpdate`. Naming
  the cvar also overrides the built-in guide. `--xbox_guide=false` turns the
  guide off.
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
- Xbox Home (Y, or the Home tab) asks first. Yes closes the guide and ends the
  title through the window's normal close path.
- Games & Apps > Manage Game lists the title's downloadable content: what is
  installed, and the content packages (STFS, content type 2, this title's ID)
  in the `DLC` folder beside the executable or picked with "Add Content from This
  PC" (the Windows file picker). Installed content is ticked; A on a package
  that is not installed installs it with `ContentManager::InstallContent`, in
  the background. The page is the `OptionsNotifications` scene; a game may need
  a restart to see new content.
- Settings > Preferences, Patches and Cheats open settings pages built from
  the console's own Options scenes (see [Settings pages](#settings-pages)).
- Entries a recompiled title has no use for are taken out and the list closed
  up: Settings > Family Settings, Account Management, Kinect Tuner and Turn Off
  Console, and the whole Media tab (tab changes pass over it). The code is kept
  and commented or listed (`kRemovedEntries`, `kRemovedTab` in
  `xbox_guide.cpp`), so each can be put back.
- Everything else (Marketplace, My Games, media players, Live features) stays in
  the menu, disabled, as the console's disabled controls behave: they take focus,
  and pressing them plays the inactive sound.
- While it is open, the guest sees a neutral pad, XN_SYS_UI is true, and
  XamIsUIActive reports system UI, as for the Guide button on the console.
  Titles that pause for XN_SYS_UI pause.

On the console the Guide button never reaches the title. View+Menu does, so a
title may react to the Menu (Start) press that completes the chord, for example by
opening its pause menu. The guide masks the buttons once it is open.

## Achievement notifications

Unlocks play XAM's own popup, `xam/xam notify.xur` with the skin's
`scr_Notification` visual. The Xbox sphere bursts in, the ring of light flashes
green, the bar slides out with the trophy, and `NotifyPopup.xma` plays. The text
is XAM's "Achievement unlocked\n%sG - %s". The popup sits at the bottom centre of
the HUD space, one unlock at a time. The popup's TransTo ends in a go-to that can
hold it, so it leaves with TransFrom after 4 s, which is the console's timing as
remembered, not measured. Without a system update, the SDK's own toast shows the
unlock. The console command `achievement_notify [id]` shows an achievement's
popup without unlocking it.

## Settings pages

Each page is one of the dashboard's Options scenes, hosted like Achievements
(`HalfToFull`, the blade goes out; B comes back with `FullToHalf`). Unused
controls are hidden and the rest moved up; new entries are copies of the
scene's own controls (`guide_layout.h`: `RemoveEntry`, `AddEntry`). Every change
is saved to the title's config file straight away.

| Page | Scene | Controls | Setting |
| --- | --- | --- | --- |
| Preferences | `Options` | Notifications, Volume (the Voice entry), Vibration, Resolution (a copy of Vibration). Online Status, Family Timer and Word Registration are removed. | |
| Notifications | `OptionsNotifications` | Show Notifications; Play Sound (disabled while Show is off) | `notifications_show`, `notifications_sound`: the unlock popup and its sound |
| Volume | `OptionsVoice` | Game Volume slider, steps of 10, left and right; voice, Kinect and output hidden | `audio_volume`, applied live |
| Vibration | `OptionsController` | Enable Vibration | `vibration`, applied live |
| Resolution | `OptionsVoice`'s output radio list, one button added | Match Display (the display's p), 1280 x 720, 2560 x 1440, 3840 x 2160 | `resolution_match_display`, `resolution_scale`; next launch |
| Patches, Cheats | `OptionsNotifications` checkboxes, one copy per patch | The title's switchable code patches of that category | `code_patch_states`, applied live |

- **Resolution.** With `resolution_match_display` (the default) the title draws
  at the display's resolution: at startup `resolution_scale` is set from the
  window's monitor, the title's 720p times 1, 2 or 3 (2160p gives 3, 1440p and
  1080p give 2). It is set as a one-run value, so a config file's
  `resolution_scale` is kept, and `--resolution_scale` on the command line
  still wins. The draw scale needs a restart, so a choice made in the guide
  applies at the next launch; the page says so.
- **Patches and Cheats** list the title's
  [switchable code patches](code-patches.md#switchable-patches) by their
  `category`. Turning one on or off takes effect at once and is kept in
  `code_patch_states`. A title with none shows the page's "No cheats are
  available for this game."
- **4K.** The guide's figures, gradients and text are drawn at the display's
  resolution; the fonts are baked for the display's height (120 px at 2160p),
  so text and notifications are sharp at 4K. The console's images (PNG) and the
  title's achievement icons (64 x 64) have no higher-resolution source and are
  scaled up with linear filtering.

## Menu inventory

All entries are from the 17559 scenes, in the order they appear. "Works" means
the guide acts on it; everything else is shown disabled, as on the console.

| Tab | Entry | Opens on the console | Here |
| --- | --- | --- | --- |
| Games & Apps | Achievements | `802_Achievements` grid, then `828_AchievDetails` | Works |
| | Manage Game (added) | | Works: install DLC from this PC |
| | Awards | `837_AvatarAwards` (avatar awards) | Disabled |
| | Recent | `QuickLaunch`: Games & Apps, Downloads, All tabs | Disabled |
| | My Games | dashboard (dash command 23) | Disabled |
| | Active Downloads | download queue | Disabled |
| | Redeem Code | code entry | Disabled |
| | Activity Feed (hidden in 17559) | | Hidden |
| Home | Xbox Home | quit prompt, then the dashboard | Works: prompt, then ends the title |
| | Connect to Xbox Live (offline) or Friends, Party, Messages, Beacons & Activity, Chat (on Live) | Live features | Disabled (offline set shown) |
| | Disc in Tray | title name; ejects | Shows the title, disabled |
| Media | System Video Player, System Music Player, Picture Viewer, Windows Media Center | dashboard apps (dash 39, 6, 44, 8); mini player below | Removed (the tab) |
| Settings | Profile | gamer profile | Disabled |
| | Preferences | `Options`: Word Registration, Family Timer (`OptionsPlayTimer`, Add More Time), Vibration (`OptionsController`), Voice (`OptionsVoice`: volumes, output), Notifications (`OptionsNotifications`), Online Status (`OptionsOnline`) | Works: [settings pages](#settings-pages) |
| | System Settings | dashboard (dash 47) | Disabled |
| | Patches, Cheats (added) | | Works: switchable code patches |
| | Family Settings, Account Management | dashboard (dash 20, 10) | Removed |
| | Kinect Tuner | Kinect troubleshooter | Removed |
| | Turn Off Console | turn-off prompt | Removed |
| Y button | Xbox Home | as above | Works |

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
- Radial fills: the brush is the box's inscribed ellipse, moved against the
  fill's Translation (box units, turned by the fill Rotation) and sized by its
  Scale. That is what puts the notification's ring-of-light arcs round the logo
  and the bar's rounded end in place; the opposite sign draws them outside.
  3D rotations are drawn flat (a half turn about X or Y mirrors).
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
- Quantum of Solace, 2026-09-30, 3840 x 2160 display: drew at 2160p
  (`resolution_scale` 3 from the display); Settings tab reached over the removed
  Media tab; Preferences, Notifications (both toggles, Play Sound disabled with
  Show off), Volume (100 to 70, saved), Vibration, Resolution (1280 x 720
  chosen, saved); Patches listed "Unlock FPS" on and turned it off; Cheats
  showed none. Settings were saved to a throwaway config beside the exe.
- `unit_tests [xui]`, `[guide]`: `Seek`, `RemoveEntry`/`AddEntry` (list closed
  up, navigation relinked), saved patch states by name.
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
