# Title updates

A title update changes a game's code: its package carries XEX delta patches
(`default.xexp`, and one per patched DLL) beside any data files it replaces.
A recompiled title's code is fixed when it's built, so a running build can't
take an update's code. Instead each title update a title supports is built as
its own executable, and the original stays as it was
([#153](https://github.com/furqanagwan/rexglue-sdk/issues/153)).

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

## Running one

A title update executable needs its update: pass the package or folder with
`--update_data_root`. It mounts it at `update:` and applies the executable's
patch at load, so the update's data sections match its code. Without the
update it stops with a message.

XEX patches are applied only this way. An original build ignores a
`default.xexp` lying beside `default.xex` (it logs that it did) instead of
patching its data under the original code, as it did before.

Choosing between the two executables, downloading an update from Xbox Unity
and installing it are the next parts of #153.

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
