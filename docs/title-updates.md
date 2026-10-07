# Title updates

A title update changes a game's code: its package carries XEX delta patches
(`default.xexp`, and one per patched DLL) beside any data files it replaces.
A recompiled title's code is fixed when it's built, so a running build can't
take an update's code. Instead each title update a title supports is built as
its own executable, and the original stays as it was
([Guide #5](https://github.com/furqanagwan/xbox-guide/issues/5), transferred from SDK #153).

Mods and code patches are written against one executable's addresses, so each
version has its own config: a mod made for the original never reaches the
update.

## Building one (RG-GDK-057)

List the update in the project manifest, beside `[entrypoint]`:

```toml
[[title_update]]
version = 2                                  # the update's version
package = "../title_updates/TU_10LC1VV_000000S000000.00000000000G7"
out_directory_path = "generated/tu2"
includes = ["../quantumofsolace_tu2.toml"]   # this version's own settings
```

- `package` is the update's LIVE/CON package as downloaded, or a folder of its
  extracted files. Nothing from it is committed; keep it with the game files.
- `includes` replaces the entrypoint's: function entries, hooks, patches and
  mods carry addresses, which an update moves. Put settings that don't depend
  on addresses (cheat codes, add-ons) in a file both versions include.
- `rexglue codegen` generates the original, then each update. For an update it
  mounts the package at `update:` and loads the executable with that update's
  patch applied (`XexModule::ApplyPatch`), so analysis and the generated code
  see the updated executable. A package without the executable's patch is an
  error.
- The generated `rexglue.cmake` gives each update its own executable,
  `<target>_tu<version>` (for example `quantumofsolace_tu2.exe`), built from
  the same host sources with that version's generated code. Codegen's build
  rule tracks the package, so a different package regenerates the update.
- The executable records the version (`PPCImageInfo::title_update`), and the
  guide's Manage Game uses it for add-ons that need an update.
- Not yet: projects with DLL `[[modules]]`.

## Listing one for players

The title's config lists each update it had, for the guide's Title Updates (an
update is never required, and the first run never asks for one):

```toml
[[title_update]]
version = 2
media_id = "06DD88A0"                      # the disc it applies to
base_version = 7                           # the executable version it updates
content_id = "B59A1F29F4FB82AB35DC7AEC8975F83F620A8290"
size_kb = 2420                             # optional
date = "2012-06-18"                        # optional
changelog = "..."                          # optional: what it changes
```

`content_id` is the package's STFS content ID, which Xbox Unity lists as the
update's `hash`: the SHA-1 of the header from `0x344` up to the header size
rounded to 4 KB. That region holds the top hash table's hash, so it identifies
and checks the whole file. Xbox Unity has no changelogs; the title repository
writes them. Codegen compiles the list into `PPCImageInfo::title_updates`.

## Downloading and installing (`rex/ui/guide/title_update.h`)

- **Sources, in order:** Xbox Unity (`TitleUpdateInfo.php?titleid=` lists the
  title's updates per media ID; the one whose hash is the content ID gives the
  `TitleUpdate.php?tuid=` to download), then any URL templates in
  `title_update_sources` (`;`-separated, with `{title_id}`, `{media_id}`,
  `{version}`, `{content_id}`). A source that's down or doesn't list the update
  is skipped with its reason. A file on this PC is the last resort.
- **Checks:** a LIVE/CON/PIRS package of content type `0x000B0000`, for this
  title, this disc's media ID and base version, whose header hashes to its
  content ID and whose content ID is the listed one. A download that fails a
  check is discarded and the next source tried.
- **Where it goes:** `%LOCALAPPDATA%\<title>\title_updates\<version>\`, the
  package as downloaded (one per version). It's mounted at `update:` directly,
  without extracting.

## Running one

- **Choosing:** `title_update` (set from the guide, saved in the title's
  settings) is the update to run, 0 for the original. At startup each
  executable checks it: when that update is installed and its executable
  (`<original>_tu<version>.exe`) is beside the original, the original starts it
  and quits; turned off, the update build starts the original. Otherwise, or
  if the update is removed, the original runs: an update is never required.
  The started executable gets `--title_update_handoff`, so it never hands back.
- **Mounting:** an update build mounts its installed package at `update:` and
  applies the executable's patch at load, so the update's data sections match
  its code. `--update_data_root` (a package or folder) overrides the installed
  one for development; an update build that has neither, and no original
  beside it, stops with a message.
- XEX patches are applied only this way. An original build ignores a
  `default.xexp` lying beside `default.xex` (it logs that it did) instead of
  patching its data under the original code, as it did before.

## In the guide

Games & Apps > Title Updates lists each update (a page of its own, apart from
Manage Game's add-ons), and Active Downloads follows
the downloads ([Xbox guide](xbox-guide.md#what-it-does)). Turning an update
on or off saves `title_update`, asks first (the game restarts), ends the
title, and starts the executable again once it has shut down, without the
command line's `--title_update`; that start picks the executable. Each
version's config must carry the `[[title_update]]` entries, so the update
build's guide can turn it off again.

## Validation

- `unit_tests [title_update]`: manifest entries (own output and includes,
  version recorded, missing fields and repeated versions refused) and the
  generated CMake (a `<target>_tu2` executable, its sources produced by the
  codegen rule).
- Quantum of Solace, title update 2 (Xbox Unity TUID 22386, media `06DD88A0`,
  base version 7), GDK Release on 2026-10-01. Codegen built
  `generated/default` unchanged and `generated/tu2` from the patched
  executable (21,652 functions against the original's 21,670), and the build
  produced `quantumofsolace.exe` and `quantumofsolace_tu2.exe`. The update
  executable mounted the package, applied the patch ("base version 0.0.0.7,
  new version 0.0.2.7"), opened the game's files and started audio, then
  stopped at "Call to invalid or unregistered function at guest address
  0x821C1C20". That is one of the function entries `quantumofsolace.toml`
  adds for the original; the update's own config (in the title repository)
  needs its entries, as the original's did.
- `unit_tests [title_update]` (part 2): package header and content ID
  (damaged byte refused), the checks (other game, disc, base version,
  update, content type), Xbox Unity's listing (Quantum of Solace's real
  response; 007 Legends' empty one), `title_update_sources` templates,
  install and replace (a refused package leaves the installed one), sources
  tried in order with their reasons, and the launch choice (off, on but not
  installed or not built, on, turned off, handed over, removed).
- `unit_tests "[.network]"` (run by hand, reaches xboxunity.net): Quantum of
  Solace's title update 2 found by content ID, downloaded (2,478,080 bytes,
  with progress), checked and installed, 2026-10-01.
- Handover with real executables: with title update 2 installed and
  `--title_update=2`, `quantumofsolace.exe` logged "title update 2 is on",
  started `quantumofsolace_tu2.exe` and exited 0; the update build mounted the
  installed package by itself and applied the patch.
