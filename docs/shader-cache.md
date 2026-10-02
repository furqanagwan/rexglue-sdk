# Shipped shader cache (RG-GDK-064)

The first time a game draws with a new shader or render state, the GPU
emulation translates the shader and creates a Direct3D 12 pipeline for it. That
work happens mid-frame and shows as a hitch. The pipeline cache already
records each title's shaders and pipeline descriptions under the cache root
(`<cache>\shaders\shareable\<title ID>.xsh` and
`<title ID>.rtv.d3d12.xpso`, or `.rov` on the ROV path). On the next start it
translates and creates all of them before the game runs. A player's first run
starts with nothing recorded.

Microsoft's PC backward compatibility ships a ready-made shader cache with each
game (`XeO3_ShaderCache\<title ID>\*.pak`) and preloads it. A rexglue title
can do the same:

1. Play the title (ideally through its levels) and take its two files from
   `<cache>\shaders\shareable` (by default `%LOCALAPPDATA%\<name>\cache`; see
   [data locations](data-locations.md)).
2. Put them in the title project's `shader_cache` folder, or name a folder with
   `rexglue_configure_target(<target> SHADER_CACHE <dir>)`. The build copies
   them to `shader_cache\` beside the executable.
3. At startup, before the pipeline cache opens its files, each shipped file
   seeds the player's (`SeedStorageFile`):
   - a player without the file, or with one from another SDK version, gets the
     shipped copy;
   - otherwise the shipped records the player lacks are appended after the
     player's valid records.

   Records are identified and validated by their XXH3 hashes, as the pipeline
   cache reads them, and the file is rewritten beside and then moved into
   place. The log says how many records were added.

- **Versions.** The files' headers carry the shader translator's version. A
  shipped file from another SDK version is ignored ("from another SDK
  version"); record new files after an SDK update. The ROV and RTV paths keep
  separate pipeline files, so ship both if both were recorded.
- **Not in the repository.** The files hold the game's shaders. Like the game
  and the guide, they go in builds and releases, never in a repository; the
  title repository's allowlist `.gitignore` keeps `shader_cache` local.
- `--shader_cache_shipped=<dir>` points at another folder of shipped files (an
  empty folder turns the seeding off).

## Validation (2026-10-02)

- `unit_tests [shader_cache]` covers:
  - a player without a file;
  - appending only the missing records after the player's, with a cut-off tail
    dropped;
  - a shipped file from another version ignored;
  - a player's file from another version replaced;
  - pipeline records stopping at a damaged one.
- Quantum of Solace with the owner's recorded cache (713 pipelines, 629
  shaders) and a fresh profile: the log shows both files seeded, the shaders
  translated in 25 ms and the 713 pipelines created in 48 ms, all before the
  first frame.
- Boot and menus with frame stats on held 60 fps with or without the cache.
  The one long frame at boot is the game waiting on the GPU (WAIT_REG_MEM),
  not pipeline creation; the worst menu frame was 18.8 ms with the cache and
  20.7 ms without, within noise. The cache's gain is in gameplay, where new
  effects first appear (#120); that has not been measured.
