# Library art (RG-GDK-068)

`rexglue library-art` makes a title's Xbox PC library tiles in the style the
Xbox app shows Xbox 360 backward-compatible games in. The game's box art fills
the tile beside a white strip down its left side. The strip has the green
swooshes at its top, the XBOX 360 wordmark reading upwards and the orb at its
foot. Original Xbox games have their own black strip in the same place (as
seen in Fuzion Frenzy's PC package). The window and EXE icon are separate
(RG-GDK-060) and this command never touches them.

```powershell
rexglue library-art 415607FF --system-update "C:\path\to\$SystemUpdate" -o out\library-art
```

| Output | Size | Use |
| --- | --- | --- |
| `LibraryTile.png` | 1080 x 1080 | The Xbox app's own artwork choice for a game added by hand |
| `Square480x480Logo.png`, `Square150x150Logo.png`, `StoreLogo.png` (100), `Square44x44Logo.png` | as named | GDK `ShellVisuals` for a registered title |
| `SplashScreen.png` | 1920 x 1080 | GDK `ShellVisuals` splash: the title's key art |

- **Box art and splash.** With a title ID, the box art is the 360
  marketplace's `boxartlg.jpg` (219 x 300) and the splash its `background.jpg`
  (1280 x 720), both from `download.xbox.com`. The box art's top 13% is the
  console's banner (the orb, XBOX 360 and LIVE) and is cut off. `--cover` and
  `--background` take the builder's own images instead; a `--cover` is used
  whole, so it should have no banner. A larger cover gives a sharper tile: the
  marketplace's is scaled up by 1.8 for the 480 tile.
- **Wordmark and orb.** These come from the console system update that
  `--system-update` names (as for `guide-bundle`: a `$SystemUpdate` folder, its
  package or a BC Flash folder): the shapes of `splash_360.png` in XAM's shared
  resources, without its trade mark signs. They are coloured as the Store's
  tiles colour them: XBOX dark green, 360 grey, and the white orb with a green
  X, turned with the wordmark. Without a system update the strip has the
  swooshes only. Nothing of the Xbox's or the publisher's artwork ships with
  the SDK. Like the box art, the output belongs to the builder and is not
  committed (see the [title repository standard](title-repo-standard.md)).
- **Layout.** The tile is laid out on the Store's 1080 x 1080 tiles for Xbox 360
  games (Brütal Legend's was the reference):
  - the strip is 189 pixels wide;
  - the swooshes are twelve bands whose edges curve down to the right, fading
    to white by about 440 pixels down;
  - the wordmark is 415 pixels long, from 494 to 909 down;
  - the orb is 113 pixels across, centred 986 down.

  The tile is drawn at 1080 and scaled down to each size with high-quality
  cubic filtering (Windows Imaging Component).

## Validation (2026-10-02)

- `unit_tests [library_art]`:
  - PNG round trip;
  - box art banner cut and strip layout at 1080 and 150;
  - orb and wordmark taken from a synthetic splash: ™ left out, recoloured,
    and placed up the strip.
- Quantum of Solace (`415607FF`), Blood Stone (`4156081F`) and 007 Legends
  (`415608D8`) from the marketplace and the 17559 update. The tiles were
  compared side by side with Brütal Legend's Store tile at 480 x 480.
- Not yet tested: whether the Xbox app picks these up for a GDK-registered
  build (that registration is RG-GDK-060) and the app's artwork choice for a
  game added by hand.
