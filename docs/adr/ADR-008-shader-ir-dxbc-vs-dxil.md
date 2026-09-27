# ADR-008: Guest shader IR — keep DXBC now, adopt Edge's DXIL path staged

Status: **Accepted direction; DXIL adoption staged under [RG-GDK-032](https://github.com/furqanagwan/rexglue-sdk/issues/53)**. Date: 2026-09-24. Resolves [RG-GDK-007](https://github.com/furqanagwan/rexglue-sdk/issues/7).

## Context

ReXGlue's D3D12 backend translates Xenos microcode straight to DXBC (SM 5.1). The two upstreams ReXGlue borrows GPU fixes from have split:

| | xenia-canary (`canary_experimental`) | xenia-edge (`94de4f676`, 2026-09-23) |
| --- | --- | --- |
| Guest shader path | Xenos → DXBC (maintained; `dxbc_shader_translator.cc` present) | Xenos → SPIR-V (`SpirvShaderTranslator`, glslang SpvBuilder) → Mesa `spirv_to_dxil` → DXIL |
| DXBC | Kept | Retired in `c00e7aead` (translator, `dxbc.h` and DXBC transfer shaders deleted; D3D12 render-target cache −3000 lines) |
| Shader compiler DLLs | FXC-era bytecode, no runtime compiler | `dxcompiler.dll` dropped (`6e9cb7e3f`); `dxil.dll` validator required to sign output |
| Host/utility shaders | Prebuilt DXBC bytecode | Slang → DXIL (`xe_shader_rules_slang`) |
| Minimum shader model | 5.1 | 6.6 (`spirv_to_dxil` `shader_model_max = SHADER_MODEL_6_6`; provider rejects < 6.6) |
| Extra build tools | None | Mesa built out of tree with meson ≥ 1.4, ninja and Python `mako` under an MSVC environment; glslang, SPIRV-Tools/Headers, Slang |
| Maturity | Long-lived | 15 commits to `spirv_to_dxil_compiler.cc` / `gpu/d3d12` between 2026-08-26 and 2026-09-23 |

Since #51 ([RG-GDK-023](https://github.com/furqanagwan/rexglue-sdk/issues/23)), ReXGlue has no Vulkan backend and no SPIR-V translator. Its old translator was older than Edge's and tied to the removed Vulkan device.

## Decision

1. **DXBC stays the shipping guest-shader path for now.** Canary still maintains DXBC, so its GPU fixes (#5, [RG-GDK-008](https://github.com/furqanagwan/rexglue-sdk/issues/8) to [RG-GDK-012](https://github.com/furqanagwan/rexglue-sdk/issues/12)) remain direct ports and continue on the DXBC path.
2. **DXIL through Edge's SPIR-V → Mesa `spirv_to_dxil` pipeline is the long-term target.** It is ported as a unit, as an opt-in second path behind a build option and a runtime selector. The staging, gates and rollback are in [RG-GDK-032](https://github.com/furqanagwan/rexglue-sdk/issues/53).
3. **DXBC is retired only by a superseding ADR,** after the parity gates below pass on the opt-in path.
4. SPIR-V, glslang, SPIRV-Tools and Slang may return **only as shader-compilation tools**. No Vulkan loader, device or presenter is reintroduced (ADR-002).

## Rejected alternatives

- **DXBC only, permanently.** This cuts ReXGlue off from Edge's GPU accuracy work, which the fork exists to adopt, and leaves it on SM 5.1.
- **Switch to DXIL now.** There are no parity measurements, the Edge pipeline is less than a month old and still changing, it needs SM 6.6, and it adds a meson/Mesa build plus `dxil.dll` redistribution. The render-target cache rewrite would also collide with in-flight EDRAM work ([RG-GDK-009](https://github.com/furqanagwan/rexglue-sdk/issues/9)).
- **Revive ReXGlue's removed SPIR-V translator.** It is older than Edge's and would need Edge's fixes re-applied by hand. Edge's current translator is the better base.
- **HLSL/DXC generation.** Edge itself removed `dxcompiler.dll`; there is no upstream to borrow from.

## Capability floor and rollback

- DXBC path: SM 5.1 (current).
- DXIL path: SM 6.6, D3D12 Agility SDK as pinned by RG-GDK-002, and `dxil.dll` shipped beside the title. Hardware below SM 6.6 falls back to DXBC.
- Rollback: a runtime selector returns to DXBC per run. The build option removes the DXIL path entirely. Stages land as separate PRs, and no PR both adds a path and switches the default.

## Measured results

The measurements RG-GDK-007 asked for (paired correctness and frame time, cold/warm cache, golden corpus) need the opt-in path to exist. They are therefore the acceptance gate of RG-GDK-032 stage 5 and must be recorded here before any default switch.

| Measurement | DXBC | DXIL | Status |
| --- | --- | --- | --- |
| Golden corpus: NaN/Inf/signed zero, rcp/rsq, packed and signed memexport, depth export, ROV, float24 transfer (Edge #198) | — | — | Not run; needs [RG-GDK-006](https://github.com/furqanagwan/rexglue-sdk/issues/6) harness |
| Cold/warm shader cache time, async compile | — | — | Not run |
| Paired frame time on pinned title scenes (NVIDIA) | — | — | Not run |
| AMD / Intel | — | — | Untested, non-blocking (ADR-007) |

## Follow-up

Before stage 1 of RG-GDK-032, verify and record the licence and redistribution terms for Mesa, Slang and `dxil.dll` at the pinned revisions.
