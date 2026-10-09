# Releases and the updater

**Conclusion:**
- Publish the 007 games as GitHub releases of `furqanagwan/007`, versioned
  `0.1.0-alpha.1`, `0.1.0-alpha.2` and so on, with a `CHANGELOG.md`.
- Builds are made on the owner's PC, because building needs the game's files.
- Release builds leave out the built-in Guide assets.
- A small updater offers new versions and never installs one without asking.
  It keeps the previous version for rollback, and it never touches saves or
  settings.

## Versioning

[Semantic Versioning](https://semver.org) with pre-release labels:

| Version | Meaning |
| --- | --- |
| `0.1.0-alpha.1` | First public alpha |
| `0.1.0-alpha.N` | Fixes and progress during the alpha |
| `0.2.0-alpha.1` | A milestone, for example a game reaches Playable |
| `0.x.0-beta.1` | Feature-complete, still testing |
| `1.0.0` | All three games Playable |

- Git tag: `v0.1.0-alpha.1`.
- Release title: `007 Recompiled 0.1.0-alpha.1`.
- All three games share one version, and each release lists each game's
  status.
- Releases before `1.0.0` are marked **pre-release** on GitHub.

## What a release contains

One zip per game, plus a checksum file:

```text
007-QuantumOfSolace-0.1.0-alpha.1-win-x64.zip
007-BloodStone-0.1.0-alpha.1-win-x64.zip
007-Legends-0.1.0-alpha.1-win-x64.zip
SHA256SUMS.txt
```

Each zip holds the game executable, `rexruntime.dll`, `rexgpu-xenos.dll`,
the other required DLLs, `README.txt` and `version.txt`. Nothing else.

### What must stay out

- **Game files.** The player picks their own disc image or folder on first
  run (the Guide source picker).
- **Microsoft's Guide assets.** A title built with `REXGLUE_SYSTEM_UPDATE`
  embeds the console's Guide scenes, fonts and sounds in the executable.
  Release builds must leave it unset. Players who want the console Guide
  put their own `$SystemUpdate` (dashboard 2.0.17559) beside the executable or
  in `%LOCALAPPDATA%\ReXGlue\$SystemUpdate`; otherwise the SDK's own overlay is
  used. The release check script fails if a Guide bundle is present.
- **Saves, logs, caches and debug files (`.pdb`).**

### Open question for the owner

The executable contains the game's code, translated to C++ and compiled. That
is derived from the original game, unlike an emulator. Other recompilation
projects handle this differently: some ship builds, others ship only the tools
and have players build their own. Decide before the first public release;
everything below works either way.

## Changelog

`CHANGELOG.md` in the 007 repository, in
[Keep a Changelog](https://keepachangelog.com) form:

```markdown
## [0.1.0-alpha.1] - 2026-10-20

### Quantum of Solace
- Status: In-game.
- Fixed: picture froze when an achievement unlocked.

### All games
- Added: first-run disc image picker.

### Known issues
- ...
```

Each entry links its issue or PR. The release notes are this section,
pasted into the GitHub release.

## Making a release

In the 007 repository, a new script (Publish-Release.ps1, run as `Publish-Release.ps1 -Version 0.1.0-alpha.1`):

1. Check that the SDK checkout is a clean, tagged `main` commit, and that
   the 007 repository is clean on `main`.
2. Install the SDK to a fresh prefix, then regenerate and build each game in
   a clean folder **without** `REXGLUE_SYSTEM_UPDATE`.
3. Run each game once, fullscreen, for 90 seconds (the existing smoke check).
4. Zip each game, write `SHA256SUMS.txt`, and check that no Guide bundle,
   `.pdb`, `.iso` or `.xex` is inside.
5. `gh release create v0.1.0-alpha.1 --prerelease --notes-file <changelog section> <zips> SHA256SUMS.txt`.

GitHub Actions can't build releases, because codegen needs the game's
executable. CI keeps checking the repository itself.

## The updater

### Behavior

- On start, at most once a day, the game asks GitHub for the newest release:
  `GET https://api.github.com/repos/furqanagwan/007/releases`. Pre-releases
  count while the game is itself an alpha.
- If a newer version exists, the Guide shows a notification:
  "Update available: 0.1.0-alpha.2". Nothing downloads yet.
- Guide > Settings > System > **Update** shows the version, the changelog, and
  **Install** / **Not now** / **Skip this version**. It uses the Xbox 360
  Guide's update page look when the Guide assets are present, and the SDK
  overlay otherwise.
- **Install:**
  1. Download the zip to `%LOCALAPPDATA%\<name>\updates\<version>\`.
  2. Check its SHA-256 against `SHA256SUMS.txt`.
  3. Unpack it to a staging folder.
  4. Start `rexglue-updater.exe` and exit the game.
- **The helper:**
  1. Waits for the game to exit.
  2. Moves the current files to `previous\`.
  3. Moves the new files in.
  4. Restarts the game.
  5. On any failure, puts `previous\` back.
- **Rollback:** Guide > Settings > System > Update > **Use previous version**.
- **Off switch:** `check_for_updates = false` in the config, or a setting in
  the Guide.

### Why saves and settings are safe

They already live outside the install folder, as on Xbox PC games
([data locations](../../docs/data-locations.md)):

- Saves: `Saved Games\<name>`
- Settings, logs, caches: `%LOCALAPPDATA%\<name>`

The updater only replaces files in the install folder, and only the files
listed in the new zip.

### Where the code goes

- `rexglue-sdk`:
  - A new src/updater folder holds the release check, download, verification and
    staging, as a library with no guest dependencies.
  - A new tools/rexglue-updater folder holds the helper executable.
  - A Guide page for the update screen.
- Each title opts in with its release repository in its config:
  `update_repository = "furqanagwan/007"` and `update_asset = "007-QuantumOfSolace-*-win-x64.zip"`.
- Uses WinHTTP (already part of Windows), so there are no new dependencies.

### Risks

| Risk | Handling |
| --- | --- |
| A new alpha is broken | Never auto-install; keep `previous\`; one-click rollback |
| Corrupt or tampered download | SHA-256 from the release; HTTPS only; later, sign releases |
| Game still running during swap | The helper waits for the process to exit |
| GitHub rate limits (60 requests/hour unauthenticated) | One check a day, cached |
| Player is offline | Silent; check again next start |

## Tasks

1. 007: `CHANGELOG.md`, the Publish-Release.ps1 script, and a release check that
   rejects Guide bundles, `.pdb`, `.iso` and `.xex`.
2. Owner decision on shipping executables (see above), then publish
   `v0.1.0-alpha.1`.
3. SDK: updater library and tests (version comparison, checksum,
   staging, rollback).
4. SDK: `rexglue-updater.exe` helper.
5. SDK: Guide update page and notification.
6. 007: opt the three games in.
