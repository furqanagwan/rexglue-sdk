# April 2026 PC GDK toolchain probe

This isolated executable tests whether a selected x64 Windows compiler can compile C++23 against an **exact installed GDK edition** and link its `xgameruntime.lib`. It does not make the SDK or a game a GDK title. The SDK's own opt-in GDK build, which followed this probe, is documented in [docs/gdk-toolchain.md](../../docs/gdk-toolchain.md) ([RG-GDK-002](https://github.com/furqanagwan/rexglue-sdk/issues/2)).

From an x64 Visual Studio developer shell with CMake, Ninja and Clang available:

```powershell
cmake -S tools/gdk-toolchain-probe -B out/build/gdk-toolchain-probe -G Ninja -DCMAKE_CXX_COMPILER=clang-cl -DGDK_ROOT="C:/Program Files (x86)/Microsoft GDK/260404"
cmake --build out/build/gdk-toolchain-probe --verbose
out/build/gdk-toolchain-probe/rexglue_gdk_toolchain_probe.exe
```

The first two commands prove header, compiler, Windows SDK, CRT and import-library compatibility. The executable then attempts Gaming Runtime initialization and prints its HRESULT. A nonzero result is a deployment/runtime finding, not a failed compile/link probe. Run it unpackaged first and then in an appropriately configured PC title environment. Record the exact VS edition/version, Windows SDK, Clang, GDK edition, build output and initialization HRESULT. Do not copy GDK headers, libraries or redistributables into this repository.

Negative configure checks should fail with an actionable message:

```powershell
cmake -S tools/gdk-toolchain-probe -B out/build/gdk-toolchain-probe-missing -G Ninja -DCMAKE_CXX_COMPILER=clang-cl
cmake -S tools/gdk-toolchain-probe -B out/build/gdk-toolchain-probe-wrong -G Ninja -DCMAKE_CXX_COMPILER=clang-cl -DGDK_ROOT="C:/not-an-installed-gdk"
```

The [April 2026 GDK announcement](https://learn.microsoft.com/en-us/gaming/gdk/docs/gdk-dev/whatsnew/whats-new?view=gdk-2604) explicitly lists VS 2026 Professional and Enterprise support. A successful build using Community or Build Tools would demonstrate local technical compatibility only, not an officially documented supported pairing. The full SDK build, plugin ABI and external consumer remain separate RG-GDK-002 acceptance gates.

## Local result, 2026-09-24

| Component | Observed version |
| --- | --- |
| GDK PC edition | `260404`, `windows/include/XGameRuntime.h`, `windows/lib/x64/xgameruntime.lib` |
| Visual Studio developer shell | Community 2026 `18.10.1` |
| Compiler / build system | `clang-cl` 22.1.8 / CMake 4.4.3 / Ninja |
| Windows SDK | `10.0.26100.0` |

Debug and Release x64 builds compiled and linked. The unpackaged executable returned `XGameRuntimeInitialize: 0x00000000` in both configurations. Missing `GDK_ROOT` and an invalid edition each failed configure with the intended message when run from the same developer shell. The installed GDK headers emitted two Clang warnings: non-portable `GRDK.h` case and unsupported `#pragma section(..., discard)`; neither prevented this probe from compiling. These results do **not** establish Microsoft-supported VS Community pairing, SDK/plugin ABI parity, clean-machine redistributable deployment or packaged-title operation. RG-GDK-002 remains open.
