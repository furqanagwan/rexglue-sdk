# DXIL shader toolchain (RG-GDK-032 stage 1)

The opt-in build of what the future SPIR-V → DXIL guest shader path needs
([ADR-008](adr/ADR-008-shader-ir-dxbc-vs-dxil.md), epic
[#53](https://github.com/furqanagwan/rexglue-sdk/issues/53)). Stage 1 only
pins and builds the toolchain and proves it end to end; no guest shader uses
it yet, and DXBC stays the shipping path. The default build is unchanged:
nothing is downloaded or built unless `REXGLUE_SHADER_DXIL` is on.

## What it pins

| Component | Pin | Source | Why |
| --- | --- | --- | --- |
| Mesa `spirv_to_dxil` | has207/mesa `7a1fc756809f3bdc9771b54e6036b156389dfc85` | GitLab archive, SHA-256 checked | The commit xenia-edge `edge` pins (`0788c561e3`, 2026-10-03): Edge's fork with its barycentric, linking, `keep_io_vars` and FSI→ROV changes |
| D3D12 Agility SDK | 1.618.5 (`D3D12SDKVersion` 618) | NuGet `Microsoft.Direct3D.D3D12`, SHA-256 checked | Shader Model 6.6 on any supported Windows build, independent of the OS runtime |
| DXC | 1.8.2502.8 | NuGet `Microsoft.Direct3D.DXC`, SHA-256 checked | `dxil.dll` signs the DXIL `spirv_to_dxil` emits unsigned; D3D12 rejects unsigned DXIL |

The Agility SDK and DXC versions are the ones Microsoft's own PC backward
compatibility ships: Fuzion Frenzy's package (2608.3123.1.0, under
`C:\XboxGames\Fuzion Frenzy\Content`) carries `D3D12Core.dll` 1.618.5.0 and
`dxcompiler.dll` 1.8.2502.8 beside its GPU emulator (`VGPUDX12.dll`). The
April 2026 GDK (260404) itself ships no D3D12 runtime or shader compiler: on
PC the GDK uses the Windows SDK's D3D12 headers and the Agility SDK and DXC
from NuGet, so this pairing is the nearest first-party reference. Nothing of
Microsoft's is copied; the packages come from NuGet under their own licences.

## Building

Prerequisites, beyond the [GDK toolchain](gdk-toolchain.md): an x64 Visual
Studio developer shell (meson compiles Mesa with `cl`), ninja, and meson ≥ 1.4
with the Python `mako` module:

```powershell
python -m pip install --user "meson>=1.4" mako
cmake --preset win-amd64-gdk-dxil -DREXGLUE_BUILD_TESTS=ON
cmake --build --preset win-amd64-gdk-dxil-release
ctest --preset win-amd64-gdk-dxil-release -L dxil --output-on-failure
```

flex and bison are not needed: OpenGL, Vulkan and the Gallium drivers are off,
as in Edge's recipe. The first configure downloads about 60 MB into
`out/build/<preset>/_deps/shader_dxil`; Mesa builds out of tree in
`out/build/<preset>/mesa-spirv_to_dxil` (release, `/MD`, static archives only).
`REXGLUE_MESA_SOURCE_DIR` points the build at another Mesa checkout. Outputs go
to `out/win-amd64-gdk-dxil/<Config>`, so the DXIL build never overwrites the
plain GDK build.

## What a consumer gets

- `rex::spirv_to_dxil`: the static Mesa archives and the
  `spirv_to_dxil.h`/`dxil_versions.h` include directories.
- `REXGLUE_DXC_INCLUDE_DIR`: DXC's `dxcapi.h` for the validator interfaces.
- `rexglue_deploy_d3d12_redist(<target>)`: copies `D3D12Core.dll`,
  `d3d12SDKLayers.dll` and `dxil.dll` into `<exe dir>\D3D12\`. The executable
  must export `D3D12SDKVersion = 618` and `D3D12SDKPath = ".\\D3D12\\"`, as an
  Agility SDK title does.

## Tests

`tests/dxil/dxil_smoke_test.cpp` (`dxil_smoke_tests`, CTest label `dxil`):

- a hand-assembled SPIR-V compute shader goes through `spirv_to_dxil` at
  Shader Model 6.6 and is signed in place by the pinned `dxil.dll`
  (validator 1.8);
- D3D12 loads the Agility SDK's `D3D12Core.dll` from `.\D3D12\` (checked by
  path, not assumed), reports Shader Model 6.6, and creates a compute
  pipeline from the signed DXIL. Skips without a device or below SM 6.6.

Measured 2026-10-03 on NVIDIA (GDK 260404, Release): both pass.

## Not yet

Stages 2–6 of [#53](https://github.com/furqanagwan/rexglue-sdk/issues/53):
Edge's `SpirvShaderTranslator` and `spirv_to_dxil` compiler behind a runtime
selector, the host shaders, the render target cache, the parity gates and
only then a default switch. Titles don't export the Agility symbols yet; that
comes with the runtime selector. `dxcompiler.dll` (runtime HLSL, which
Microsoft's BC also ships) isn't deployed: nothing compiles HLSL at runtime.
