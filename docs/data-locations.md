# Where a title keeps its files

A recompiled title keeps its files where an Xbox PC game (a PC game built with
the GDK) does, so it behaves like one when installed to `C:\XboxGames` or run
from a build folder. `ReXApp::SetupEnvironment` picks the defaults; a
command-line flag or `OnConfigurePaths` overrides any of them.

| What | Default | Override |
| --- | --- | --- |
| Game files (`game:`) | `<exe>\game`, else the executable's own folder, whichever holds `default.xex` | `--game_data_root` (extracted folder or XDVDFS ISO) |
| Saves, profiles, achievements | `%USERPROFILE%\Saved Games\<name>` | `--user_data_root` |
| Shader and other caches | `%LOCALAPPDATA%\<name>\cache` (seeded from a [shipped shader cache](shader-cache.md) beside the executable) | `--cache_root` |
| The console's cache partitions (`cache:`, `cache0:`, `cache1:`; `mount_cache`) | `<cache>\partitions` | `--cache_root` |
| Logs | `%LOCALAPPDATA%\<name>\logs` | `--log_dir`, or `--log_file` for one file |
| Settings (`<name>.toml`) | `<exe>\<name>.toml` if it exists, else `%LOCALAPPDATA%\<name>\<name>.toml` | none |

`<name>` is the project name given to `ReXApp` (for example
`quantumofsolace`), not the title's display name: it is known before the XEX
loads and never changes.

An ISO supplied with `--game_data_root` is mounted read-only. The image must
contain a root `default.xex` with an XEX2 signature and its content fingerprint
must match the entry XEX used to generate the executable. Regenerate a title
with this SDK to embed that fingerprint. Title-update builds still require an
extracted folder; ISO selection, optical drives and first-run setup are tracked
in [RG-GDK-058](https://github.com/furqanagwan/rexglue-sdk/issues/154).

With `--user_data_root` and no `--cache_root`, the cache stays in
`<user data>\cache`, as it always has. Existing scripts that pass their own
user data folder see no change except where logs go.

## Why these folders

Microsoft's GDK guidance for PC titles
([PC developer FAQ](https://learn.microsoft.com/gaming/gdk/docs/gdk-dev/pc-dev/gr-pc-faq?view=gdk-2604),
[Game Saves walkthroughs](https://learn.microsoft.com/gaming/gdk/docs/features/common/game-save/game-saves-walkthroughs-and-samples?view=gdk-2604)):

- **Saves.** A title that doesn't use the GDK's Game Saves APIs should save to
  the Saved Games known folder (`FOLDERID_SavedGames`). The GDK FAQ says:
  "Don't save game data under the user's Documents folder": OneDrive syncs
  Documents and can corrupt saves; it does not sync Saved Games by default.
  Cloud saves (`XGameSaveFiles`) need a Partner Center title (SCID), which
  recompiled titles don't have.
- **Install.** An MSIXVC package installs as flat files to
  `C:\XboxGames\<Game>\Content`, where everything except the executable is
  readable and writable
  ([Flat File Install](https://learn.microsoft.com/gaming/gdk/docs/features/common/packaging/packaging-flatfileinstall?view=gdk-2604)).
  Game files found beside the executable therefore need no flags.
- **Caches, logs, settings.** They belong to one user on one machine, so they
  go to local app data. In a packaged install, Windows may keep app data writes
  inside the package's own storage; that is fine for data the title can rebuild,
  and it is removed with the package. Saves in Saved Games are not affected and
  survive uninstalling.

## Moving saves out of Documents

Earlier builds kept user data in `Documents\<name>`. At startup, when no
`--user_data_root` is given, the old folder exists and the new one does not,
`MoveLegacyUserData` moves it once:

1. Its `cache` folder moves to the new cache location (unless one is already
   there). The cache is never copied.
2. The rest is renamed to `Saved Games\<name>`. When a rename is impossible
   (for example Documents redirected to OneDrive on another drive), it is
   copied and the old folder is left in place for the user to delete.
3. A failed copy is removed, so the next start tries again. The log says what
   happened.

After the move the old folder is never read again, even if it reappears.

## Tests

`unit_tests [data_locations]`: defaults, known folders on this machine, game
files beside the executable, the move with its cache, nothing to move, an
existing cache kept, and the copy fallback when a rename fails.
`unit_tests [log]` covers `--log_dir`. The GDK smoke test
(`scripts/gdk_smoke.ps1`) checks that saves in Saved Games survive removing and
redeploying a registered or installed package.
