# April 2026 PC GDK toolchain (RG-GDK-002)

The SDK can be built against the Microsoft GDK for PC as an **opt-in**. The standard `win-amd64` preset does not need, find or use a GDK, and nothing in this repository contains GDK headers, libraries or redistributables.

## Pinned toolchain

| Component | Pinned / observed | Provenance |
| --- | --- | --- |
| GDK (PC) | April 2026 Update 4, edition `260404` (`_GRDK_EDITION` in `windows/include/grdk.h`) | Microsoft GDK installer; `GameDKCoreLatest` environment variable |
| Gaming Runtime import library | `260404/windows/lib/x64/xgameruntime.lib` (1,201,048 bytes, 2026-09-01) | installed GDK |
| Gaming Runtime | `xgameruntime.dll` 10.0.26100.9441 (system) | Windows |
| Gaming Services | `Microsoft.GamingServices` 38.117.18001.0 | Microsoft Store; the GDK ships `windows/redist/GamingServices.appxbundle` and `InstallGamingServicesBundle.ps1` |
| Other GDK redistributables | `Microsoft.VCLibs.x64.14.00.appx`, `Microsoft.NET.Native.{Framework,Runtime}.2.2.appx` in `windows/redist` | installed GDK; not used by the SDK |
| Visual Studio | Community 2026 18.10.1 (developer shell, MSVC STL/CRT, linker) | Visual Studio installer |
| Compiler | Clang 22.1.8 (`clang`/`clang++`, `C:/Program Files/LLVM/bin`) | LLVM release installer, first on `PATH` in that shell |
| Windows SDK | 10.0.26100.0 | Visual Studio installer |
| CMake / generator | 4.4.3 (3.25 minimum) / Ninja Multi-Config | |

Microsoft's [April 2026 GDK announcement](https://developer.microsoft.com/en-us/games/articles/2026/04/april-2026-microsoft-gdk-update/) names Visual Studio 2026 **Professional and Enterprise**. The results below were produced with **Community**: they show technical compatibility on this machine, not a Microsoft-documented supported pairing.

`xgameruntime.lib` is an import library for the Gaming Runtime's C API, so it brings no C++ runtime, STL or exception model of its own into the link; the only CRT is the one the SDK already uses. The ABI checks below therefore target the SDK's own DLL boundaries (rexruntime and the GPU plugin) when built with the GDK.

## What the GDK build changes

* `REXGLUE_USE_GDK=ON` (the `win-amd64-gdk` preset) validates `REXGLUE_GDK_ROOT`, reads `_GRDK_EDITION` and requires it to equal `REXGLUE_GDK_EDITION` (`260404`). It then defines the imported target `rex::gdk`: GDK include directory, `xgameruntime.lib` and `REXGLUE_GDK_EDITION=<edition>`. `REXGLUE_GDK_ROOT` defaults to `$ENV{GameDKCoreLatest}`.
* `rex::runtime` links `rex::gdk` publicly. The SDK does not call any GDK API yet; GameInput, XAudio2, windowing and Gaming Runtime lifecycle work belongs to RG-GDK-019/020/021/022.
* Outputs go to `out/win-amd64-gdk/<Config>` so a GDK build never overwrites the standard build.
* The installed package config (`rexglueConfig.cmake`) re-resolves `rex::gdk` on the consumer's machine with the same edition check (`cmake/rexglue_gdk.cmake` is installed next to it). The SDK does not export a GDK path; a consumer may pass `-DREXGLUE_GDK_ROOT=...`.
* The GDK headers (`XGameRuntime.h`, via `XTaskQueue.h`) require `<windows.h>` to be included first; the public SDK headers do not include it, so code mixing the two includes it explicitly (see the unit test and consumer).
* A GDK build adds the `[gdk]` unit tests (`tests/unit/gdk/gdk_runtime_test.cpp`): the edition, `XGameRuntimeInitialize` in an unpackaged SDK process, and a C++ exception unwinding through rexruntime.

A missing or wrong GDK fails configuration with an actionable message:

* No edition selected (no `GameDKCoreLatest` and no `REXGLUE_GDK_ROOT`): asks for the April 2026 PC GDK or `-DREXGLUE_GDK_ROOT=...`.
* A directory without `windows/include/grdk.h`, `XGameRuntime.h` or `windows/lib/x64/xgameruntime.lib`: names the missing file.
* A different edition: `GDK edition mismatch: <root> is <found>, but 260404 is required`.

## Commands

From an x64 Visual Studio developer shell (`vcvars64.bat`) with initialized submodules:

```powershell
cmake --preset win-amd64-gdk -DREXGLUE_BUILD_TESTS=ON
cmake --build --preset win-amd64-gdk-debug
ctest --preset win-amd64-gdk-debug --output-on-failure
cmake --build --preset win-amd64-gdk-release
ctest --preset win-amd64-gdk-release --output-on-failure
cmake --install out/build/win-amd64-gdk --config Release --prefix out/install/win-amd64-gdk
```

External consumer, configured only against the install tree. Build it in Release: the installed SDK is Release, and mixing a Debug consumer with Release rexruntime would mismatch `_ITERATOR_DEBUG_LEVEL`.

```powershell
cmake -S tests/gdk_consumer -B out/build/gdk-consumer -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_PREFIX_PATH="$PWD/out/install/win-amd64-gdk"
cmake --build out/build/gdk-consumer
ctest --test-dir out/build/gdk-consumer --output-on-failure
```

The consumer (`tests/gdk_consumer/main.cpp`) checks the edition matches the SDK's, initializes the Gaming Runtime, catches an exception thrown from a callback run inside rexruntime, loads the installed `rexgpu-xenos` plugin through the ABI handshake, and round-trips a plugin cvar through the runtime registry. That registry is shared by the executable, rexruntime and the plugin, so they share one CRT and heap.

Negative checks:

```powershell
cmake --preset win-amd64-gdk -B out/build/gdk-missing -DREXGLUE_GDK_ROOT=
cmake --preset win-amd64-gdk -B out/build/gdk-wrong -DREXGLUE_GDK_ROOT="C:/not-an-installed-gdk"
cmake --preset win-amd64-gdk -B out/build/gdk-edition -DREXGLUE_GDK_EDITION=251000
```

The standalone probe in `tools/gdk-toolchain-probe` stays as the minimal, SDK-independent check.

## Results, 2026-09-25

All from the development machine with the toolchain pinned above, on 2026-09-25:

* `win-amd64-gdk` configure reported `GDK: 260404`. Debug and Release built with no warnings from GDK headers: the imported target's include directory is a system include.
* `ctest --preset win-amd64-gdk-release`: 1731 of 1731 passed. These are the standard 1728 unit, PPC, GPU fixture and shader-reproducibility tests plus the three `[gdk]` tests. `XGameRuntimeInitialize` returned success in the unpackaged test process.
* `ctest --preset win-amd64-gdk-debug`: all unit, PPC and `[gdk]` tests passed. With `-j 8`, one GPU fixture test (`PM4 type-0 register write reads back through REG_TO_MEM`) failed after 5.5 s while other GPU fixtures shared the adapter. Serially, `ctest -L gpu --repeat until-fail:3` passed all 34 GPU tests three times. Run the GPU label serially.
* Installed Release to `out/install/win-amd64-gdk`. The installed `rexglueTargets.cmake` references only `rex::gdk`, and the config stores just the edition (`260404`). The external consumer configured against that prefix alone and printed `XGameRuntimeInitialize: 0x00000000` and five `PASS` lines (runtime, exception through rexruntime, plugin ABI handshake, plugin cvar registration, cvar round-trip).
* Negative checks: an empty `REXGLUE_GDK_ROOT`, `C:/not-an-installed-gdk` and `REXGLUE_GDK_EDITION=251000` each stopped configuration with the messages listed above. A consumer given `-DREXGLUE_GDK_ROOT=C:/nope` stopped with the same missing-file message from the installed `rexglue_gdk.cmake`.
* The standard `win-amd64` preset still configures with `GDK: OFF`, and its Debug and Release suites pass (1728 tests each).

## Limitations (RG-GDK-002 closed with these recorded)

* Visual Studio edition: only VS 2026 Community was used. Microsoft's announcement names Professional/Enterprise as supported. This is a support statement, not a technical difference: the editions ship the same MSVC libraries, Windows SDK and linker, and the build does not use VS itself (CMake, Ninja and LLVM Clang). Treat Community as working but not Microsoft-supported.
* Clean machine: every result above comes from the development machine, where the GDK and Gaming Services were installed interactively. The package config needs only an installed 260404 GDK on the consumer machine; this has not been run from a fresh Windows install.
* Packaged (MSIXVC or loose-file registered) title operation, Gaming Runtime lifecycle in a running title, and redistributable deployment to end users (RG-GDK-022).
* ARM64: the GDK ships `windows/lib/arm64`, but this machine has no ARM64 MSVC libraries (RG-GDK-030, #45).
