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

## Stage 2: the guest shader translator

xenia-edge's SPIR-V translator (`SpirvShaderTranslator`, its builder, built-in
geometry shaders, FSI system constants and `SpirvToDxilCompiler`, Edge
`0788c561e3`) is ported into `rex::graphics` under
`include/rex/graphics/pipeline/shader/spirv*.h` and
`src/graphics/pipeline/shader/spirv*.cpp`, compiled into the GPU plugin only
with `REXGLUE_SHADER_DXIL`. glslang (`a57276bf558f`, 16.0.0, Edge's pin)
provides the SPIR-V builder. The port is mechanical (namespaces, includes,
logging, cvars); Edge's Vulkan-only parts (`Features` from a Vulkan device, the
SPIR-V version probe and its two cvars) are dropped. `dxil.dll` is loaded from
the title's `D3D12\` folder first. The shared shader analysis gained what the
translator reads (also built for DXBC, which ignores it): registers written
before a label is re-entered, the subroutine return-point label, and the
registers used as snappable texture coordinates.

`tests/dxil/spirv_translator_test.cpp` (`spirv_translator_tests`) translates
the GPU fixture's hand-assembled vertex and pixel shaders, for the RTV and ROV
paths, with Edge's D3D12 translator configuration, through `spirv_to_dxil`
with bindless lowering; the pinned `dxil.dll` validates and signs all four.

## Stage 2: drawing with it

`gpu_shader_path=dxil` (GPU/D3D12, default `dxbc`, needs a restart) draws with
the translator in a `REXGLUE_SHADER_DXIL` build, on both render target paths.
It needs bindless resources, Shader Model 6.6 and a working `dxil.dll`;
otherwise the log says why and DXBC is used. Each draw then goes one of two
ways, so the paths mix freely within a frame:

- **DXIL**: `PipelineCache::ConfigurePipelineDxil` keeps a SPIR-V twin of
  each guest shader, derives xenia-edge's SPIR-V modifications
  (`GuestSpirvShaderCache`), translates and converts them (cached per
  modification, failures too), builds the built-in point / rectangle / quad /
  line geometry shaders as DXIL, and creates the pipeline with the fixed
  root signature from the DXBC path's fixed-function state (a `dxil`
  description bit keeps the two apart). `D3D12CommandProcessor::UpdateBindingsDxil`
  (xenia-edge's `UpdateBindingsMesa`) fills the system constants in the
  translator's layout, uploads the float, bool/loop, fetch and runtime-data
  constant buffers (its own, invalidated with the DXBC ones on register
  writes), binds shared memory (an SRV + UAV pair for memexport), the ZPD
  counter and EDRAM UAVs, and writes per-stage {texture, sampler} heap index
  buffers for the bindless lowering.
  - **Tessellation**: the guest shader is the domain shader. Its SPIR-V is
    linked by `spirv_to_dxil_link` with the host tessellation vertex and hull
    shaders its modification selects (discrete, continuous, adaptive; triangle
    and quad domains), so Mesa reconciles the stage signatures. Those host
    shaders are xenia-edge's GLSL (`src/graphics/shaders/spirv`), compiled at
    build time by the pinned glslang as Edge does (Vulkan 1.0, SPIR-V 1.0);
    nothing generated is checked in. The draw fills the tessellation factor
    range and index constants they read.
  - **ROV** (`render_target_path_d3d12=rov`): the translator runs the EDRAM
    render backend in the pixel shader (fragment shader interlock, which
    Edge's Mesa fork lowers to rasterizer-ordered views), the draw fills its
    EDRAM constants (`WriteFragmentShaderInterlockSystemConstants`) and counts
    samples into the active occlusion query's counter slot as the DXBC ROV
    shaders do.
  - **No guest pixel shader**: DXIL helper pixel shaders from the translator
    stand in for the DXBC ones (a pipeline can't mix DXBC and DXIL): the
    empty shader that keeps draws writing nothing rasterized, float24 depth
    conversion, and on ROV the EDRAM depth-only and VIZ survey shaders per
    guest sample count (carried in the description's pixel shader
    modification, since 2x is drawn as 4x).
- **DXBC**, as before, for hybrid occlusion query counting and shaders a
  title replaces (replacements are DXBC). A shader that fails to translate or
  convert, or a failing pipeline, also falls back, logged.
  `gpu_shader_path_dxil_strict` fails such draws instead (testing).

With `async_shader_compilation`, DXIL pipelines go to the creation threads
like DXBC ones: the draw thread only translates to SPIR-V (for the draw's
bindings), and Mesa's conversion and the pipeline state are made on the
creation thread. A draw that has to wait (a one-off, small or memexport
target) now waits for its own pipeline only, creating it itself if no thread
has started it, instead of for the whole queue; this applies to DXBC too.
DXIL pipelines go to the pipeline storage like DXBC ones, with their guest
shaders in the shader storage (DXIL draws may never translate them to DXBC);
at the next launch they're translated to SPIR-V and queued, converted and
created on the creation threads before play. The storage keeps both kinds; a
DXBC run skips the DXIL entries. Pipeline creation failures now log the debug layer's
reasons when `d3d12_debug` is on.

Parity: CTest `gpu.dxil_parity` runs the whole GPU fixture suite with
`gpu_shader_path=dxil` and strict mode. Measured 2026-10-04 on NVIDIA: all
52 cases pass, with 226 DXIL pipelines and none failing (the ROV cases run on
DXBC). That covers clears, resolves (including gamma, 4x MSAA and native
resolves at 2x), depth tests, memexport, ALU behaviour, ring and PM4
handling, point / line expansion at 2x, invalid fetch constants and VIZ
consumers; it is not yet a title-scene comparison.

With tessellation, ROV and the helper pixel shaders (2026-10-04, NVIDIA): the
suite, now 53 cases with `tessellation_fixture_test` (a hand-assembled domain
shader placing a quad patch, discrete and continuous, on both render target
paths), passes in strict mode, and so do the ROV occlusion query and VIZ
cases on DXIL. The log shows each linked tessellation conversion, and the
dumped SPIR-V shows the ROV pixel shaders built with their FSI
modifications. The default build's 58 GPU tests pass too.

## Titles

With an SDK built with `REXGLUE_SHADER_DXIL`, `rexglue_configure_target`
compiles `d3d12_agility.cpp` into the title (the `D3D12SDKVersion` and
`D3D12SDKPath` exports) and copies `D3D12Core.dll`, `d3d12SDKLayers.dll` and
`dxil.dll` into `<exe>\D3D12\`, the layout of Microsoft's backward
compatibility packages; the installed SDK carries them in
`share/rexglue/d3d12`. Every D3D12 device the title makes then uses Agility
SDK 1.618.5, whichever shader path it draws with. When D3D12 rejects a device,
the log now has each adapter's result (`0x887E0003` is an Agility setup the
runtime rejects).

First title run, 2026-10-04 (Quantum of Solace, GDK Release, NVIDIA,
3840x2160, `gpu_shader_path=dxil`): the in-engine intro renders correctly,
250 DXIL pipelines, none failing, no errors. Translation, conversion and
pipeline creation on the draw thread stall it: one 21.7 s frame and 23 fps
while new shaders keep coming, against 60 fps on DXBC.

After the asynchronous creation, the single-pipeline waits and publishing
SPIR-V translations (they were retranslated on every draw: 136,028
translations in 40 s, now 304), the same run has 309 conversions (median
12 ms), the menus at 60 fps and the intro at 25-45 fps with one 5 s frame
while about 200 new pipelines are awaited from a cold start.

Played twice on a fresh cache with the pipeline storage, 2.5 minutes each
(2026-10-04): the cold run created 713 DXIL pipelines and awaited 211, with a
16.5 s and a 3.8 s frame; the warm run restored them at startup, awaited
none, and its longest frame was 385 ms. Its remaining 200-330 ms frames are
all in swap, the GPU finishing the frame. A DXBC run played through the
same section (2026-10-04) was no faster: 38-52 fps with 66 frames over
150 ms in swap (up to 780 ms), against 41-60 fps and 51 for warm DXIL, so
those long frames are not DXIL-specific.

Paired run, 2026-10-09 (Quantum of Solace, GDK Release, NVIDIA RTX 5080
Laptop, one build of SDK `99158cb` plus file-read statistics, cold shader cache
both times, 90 s from launch with no input, only `gpu_shader_path` differs):

| | DXBC | DXIL |
| --- | --- | --- |
| Errors or failed pipelines | none | none |
| Longest frame | 2.6 s (level load) | 21.5 s (level load, pipelines created cold) |
| 5-second windows with a frame over 300 ms | 1 (417 ms) | 5 (up to 750 ms), in the first 40 s of play |
| Frame rate once loaded | about 50–60 fps | about 50–60 fps |

Screenshots every 4 s show correct rendering on both paths. No input means
the two runs reach different points of the level at the same time stamp, so
this is not a frame-exact comparison. The cold-cache stall is the known one
above; a warm cache removes it.

## Not yet

The rest of [#53](https://github.com/furqanagwan/rexglue-sdk/issues/53):
hybrid occlusion counting on DXIL, a tessellating title and a ROV title
scene on the DXIL path (only fixtures so far), and the wide 1D texture
mapping `kTexture1DWideMaxRows` belongs to. Edge's shared parsing fixes (1D
fetches with XY coordinates, and the second component of scalar operands
beside three-source vector ops) are in on both paths; see
[shader operand components](../research/gpu/shader-operand-components.md).
Then stages 3–6: the
host shaders, the render target cache, title-scene parity and only then a
default switch. `dxcompiler.dll` (runtime HLSL, which Microsoft's BC also
ships) isn't deployed: nothing compiles HLSL at runtime.
