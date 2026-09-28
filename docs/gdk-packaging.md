# Gaming Runtime and PC packaging

A title built with the GDK preset owns the host Microsoft Gaming Runtime and
ships with a `MicrosoftGame.config` made from its own identity (RG-GDK-022).
This page covers the runtime lifecycle, generating the config, and building,
installing, launching and removing a title with the pinned April 2026 GDK
tools. The toolchain itself is in [GDK toolchain](gdk-toolchain.md).

Guest and host identity stay separate. Guest XAM profiles, saves and
achievements belong to the recompiled title's guest state and are never mapped
to a Windows, Microsoft account or Xbox services identity. The runtime is
initialized for the host process only; no SDK code calls Xbox services, and
`rexglue init gameconfig` writes no service IDs it was not given.

## Pinned tools

| Tool | Version | Location |
| --- | --- | --- |
| PC GDK | `260404` (April 2026) | `C:\Program Files (x86)\Microsoft GDK\260404` |
| `makepkg.exe`, `wdapp.exe` | shipped with 260404; `wdapp` reports build 10.0.26100.7897 | `C:\Program Files (x86)\Microsoft GDK\bin` |
| `GameConfigSchema.xsd` | shipped with 260404 | same `bin` directory |
| Gaming Services | 38.117.18001.0 on the validation machine | Microsoft Store |

Only `makepkg pack /pc` (MSIXVC) and loose registration are covered. MSIXVC2
(`makepkg2.exe`, `packageutil2.exe`) is a preview in this GDK and stays outside
the stable flow, as does ARM64 (RG-GDK-030).

## Runtime lifecycle

`rex::system::GamingRuntime` (`include/rex/system/gaming_runtime.h`) wraps
`XGameRuntimeInitialize` and `XGameRuntimeUninitialize`:

- **Off-thread, with a timeout.** On this machine the initialize call once stalled
  for more than 60 s ([GDK toolchain](gdk-toolchain.md)). The call runs on a worker
  thread and startup waits at most `gaming_runtime_timeout_ms` (default 10000).
  If the call returns after the title gave up, a success is balanced with an
  uninitialize, and no second call is made while one is still inside the
  runtime.
- **Classified errors.** The result is one of `ready`, `unavailable` (SDK built
  without the GDK), `missing` (`E_GAMERUNTIME_DLL_NOT_FOUND`, `..._MISSING_DEPENDENCY`,
  `ERROR_MOD_NOT_FOUND`), `version mismatch` (`E_GAMERUNTIME_VERSION_MISMATCH`),
  `config error` (`E_GAMERUNTIME_GAMECONFIG_BAD_FORMAT`, `..._OPTIONS_MISMATCH`,
  `..._OPTIONS_NOT_SUPPORTED`, the `E_GAMEPACKAGE_CONFIG_*` range, or a
  missing config file passed explicitly), `timed out` or `failed`. Each carries
  a message saying what to do.
- **Uninitialized last.** `ReXApp` releases the runtime after the guest
  runtime, so audio, input and GPU callbacks have stopped first. Its member is
  declared before the guest runtime, so the same order holds if `OnDestroy`
  never runs.

`ReXApp` starts the runtime right after logging, following the `gaming_runtime`
cvar (read at startup only):

| `gaming_runtime` | Behavior |
| --- | --- |
| `auto` (default) | Initialize in GDK builds; log a warning on failure and launch anyway. Silent in standard builds. |
| `required` | Launch only when the runtime is ready; otherwise log, show the message and exit. |
| `off` | Never initialize it. |

A title can override `OnGamingRuntimeInitialized(result, policy)` to decide
for itself (return `false` to stop the launch) and reach the runtime through
`gaming_runtime()`.

## Generate MicrosoftGame.config

```powershell
rexglue init gameconfig --output-dir gdk `
  --identity-name Studio.MyTitle --publisher "CN=Studio" `
  --display-name "My Title" --publisher-display-name "Studio" `
  --executable my_title.exe
```

The command writes `gdk/MicrosoftGame.config` and five flat-colored
placeholder images (`StoreLogo` 100×100, `Square150x150Logo`,
`Square44x44Logo`, `Square480x480Logo`, `SplashScreen` 1920×1080; 8-bit RGBA
in `--background-color`, default `#000000`). It never replaces an existing
image, so replace the placeholders with real art. To regenerate one, delete it
first. It refuses to replace a config that differs unless given `--force`.

- **Identity.** `--identity-name` (3–50 characters of `A–Z a–z 0–9 . -`) and
  `--publisher` (an X.500 name) are the package identity. For a Store
  build both must be the values from Partner Center.
- **Optional IDs.** `--package-version` (default `1.0.0.0`) and
  `--description` are optional. The Partner Center IDs are optional too:
  `--title-id` with `--msa-app-id` (both or neither), and `--store-id`. They are
  written only when given, and nothing is invented.
- **VC14 dependency.** The config always lists the `VC14` KnownDependency,
  because titles and `rexruntime.dll` link the dynamic MSVC runtime. `makepkg`'s
  validator requires it.
- **Checks.** Every value is checked against the rules of the GDK's
  `GameConfigSchema.xsd` before anything is written. The CTest
  `gdk.gameconfig_schema` validates real output against the installed schema.

A project made by `rexglue init` picks the directory up automatically:
`generated/rexglue.cmake` calls `rexglue_add_game_config(<target> DIRECTORY
gdk)` when `gdk/MicrosoftGame.config` exists. That copies the config and images
next to the built executable. The build output is then a loose PC layout.

An unpackaged run reads `MicrosoftGame.config` beside the executable: a
malformed one makes `XGameRuntimeInitialize` fail with `0x8924010B`.

## Build, register, package, install, launch, remove

Start in a GDK-configured project (`REXGLUE_USE_GDK`, see
[GDK toolchain](gdk-toolchain.md)) and set `$layout` to the Release output
directory that holds the title, its DLLs, the config and the images. Package
Release builds: Debug binaries depend on the debug CRT, which the validator
reports as non-retail dependencies.

```powershell
$gdk = "${env:ProgramFiles(x86)}\Microsoft GDK\bin"
cmake --build --preset <gdk release preset>

# Loose layout for development (needs Windows Developer Mode). Without admin
# rights the layout registers as an application, not a game install.
& "$gdk\wdapp.exe" register $layout
& "$gdk\wdapp.exe" launch "<PackageFamilyName>!Game"
& "$gdk\wdapp.exe" unregister <PackageFullName>

# MSIXVC package (makepkg does not need admin rights; nor did wdapp install here).
& "$gdk\makepkg.exe" genmap /f layout.xml /d $layout
& "$gdk\makepkg.exe" pack /f layout.xml /d $layout /pd out /pc
& "$gdk\wdapp.exe" install out\<PackageFullName>.msixvc
& "$gdk\wdapp.exe" launch "<PackageFamilyName>!Game"
& "$gdk\wdapp.exe" uninstall <PackageFullName>
```

`Get-AppxPackage -Name <identity name>` shows the package full name, family
name and install location. `wdapp register` and `wdapp install` also print the
AUMID (`<PackageFamilyName>!Game`, where `Game` is the executable `Id` the
config sets).

**Saves across reinstall.** `ReXApp` keeps user data under
`Saved Games\<title>` by default (`user_data_root`), outside the package and
outside MSIX file virtualization ([data locations](data-locations.md)).
Unregistering or uninstalling leaves saves in place, and a reinstall picks
them up. An installed package's own folder (`C:\Program Files\WindowsApps\...`)
is read-only.

## Smoke test

`tests/gdk_smoke` builds a minimal SDK title (`gdk_smoke_title`, a GUI program
using `GamingRuntime`) and `scripts/gdk_smoke.ps1` deploys it three ways:

| CTest | Runs by default | What it proves |
| --- | --- | --- |
| `gdk.smoke_unpackaged` | yes | Runtime ready with no package identity and a clean uninitialize. A missing `rexruntime.dll` (0xC0000135) or a foreign one (0xC0000139) stops the loader. A malformed config gives 0x8924010B and the title stops. |
| `gdk.smoke_registered` | with `REXGLUE_GDK_DEPLOY_SMOKE=1` | `wdapp register` → `launch` gives the registered package identity. After unregister and register again, the save counter goes 1 → 2. The package is gone afterwards. |
| `gdk.smoke_installed` | with `REXGLUE_GDK_DEPLOY_SMOKE=1` | `makepkg genmap` + `pack /pc` → `wdapp install` → `launch` gives package identity and GDK installation identity. After uninstall and install again, the save counter goes 1 → 2. The package is gone afterwards. |

Titles run with a system-only `PATH`, as on a clean machine. This matters: an
SDK installed elsewhere on `PATH` (here `C:\ReXGlue\bin`) supplied a
mismatched `rexruntime.dll` and turned "missing DLL" into "entry point not
found".

```powershell
$env:REXGLUE_GDK_DEPLOY_SMOKE = '1'
ctest --preset win-amd64-gdk-release -L gdk --output-on-failure
```

## Validation (2026-09-26)

These results are from the development machine: GDK 260404, Gaming Services
38.117.18001.0, Windows 11 26340, VS 2026 Community with MSVC 19.51.36260 and
Clang 22.1.8, Developer Mode on, not an administrator.

- **Unit tests.** `unit_tests [gaming_runtime]` uses fake runtime hooks for
  success and a single balanced uninitialize, a missing runtime, a version
  mismatch, the classification table, an explicit config path and a missing
  file, a stall (timeout, no second call, a late success balanced, a late
  failure left alone) and the policy. `[gdk][gaming_runtime]` uses the
  installed runtime: ready; a malformed explicit config (0x8924010B) and a
  missing one (0x80070003) are config errors; a generated config is accepted.
- **Generator.** `unit_tests [gameconfig]` covers the rendered XML, supplied
  IDs, escaping, 23 rejected identities, accepted variants and the images
  (decoded with stb_image: RGBA, uniform, compressed).
- **Schema.** `gdk.gameconfig_schema` validates minimal output and output with
  IDs against the installed `GameConfigSchema.xsd`, refuses a differing
  overwrite, and confirms the schema rejects a bad version.
- **Smoke.** `gdk.smoke_unpackaged`, `gdk.smoke_registered` and
  `gdk.smoke_installed` passed in Release. The Release MSIXVC,
  `ReXGlue.GdkSmoke_1.0.0.0_x64__q09xr73xf9vdy.msixvc` (13,017,088 bytes,
  SHA-256 `E03F5DD51D93468A0D42FA9A14ACA33899872EBD69FDF639646643BBDE60E735`),
  packed with no validator failures. makepkg generates a new content ID for
  each pack, so the hash identifies this run's artifact, not a reproducible
  build. The installed process had GDK installation identity (package
  identifier `747287482CD784C4A78227A286633417` on the first install). The
  registered one did not ("registered as an Application").

## Limitations

- **No title run.** No recompiled title has run with the runtime. `ReXApp`'s
  startup policy, message box and shutdown order are covered by unit tests
  of `GamingRuntime` and by the smoke title, not by a title with live audio,
  input and GPU threads.
- **No missing or old runtime.** Gaming Services was installed and current.
  Those results come from fake hooks, not from a machine without it or with
  an old version.
- **Registration as a game.** Registration without admin rights makes an
  application; registration as a game (`wdapp register` elevated) was not
  run.
- **Clean machine.** Everything ran on the development machine. The
  system-only `PATH` models a clean machine's DLL search, but the VC++
  framework package and Gaming Services were already installed.
- **Store submission.** Partner Center identity, `makepkg /l` encryption,
  submission validation and upload are not covered; no real service IDs were
  used.
- **Excluded.** MSIXVC2 and ARM64 are out of scope.
