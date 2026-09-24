# ADR-002: Direct3D 12 only

Status: **Accepted policy/destination; implementation staged**. Date: 2026-09-23.

## Context

The fork must selectively modernize Xenia-derived compatibility while preserving static recompilation and controlling regressions. Current code does not yet implement all target policies. See [source investigation](../investigation.md).

## Decision

D3D12 is the only final host renderer; preserve Xenos/PM4/EDRAM above it.

## Consequences and rejected alternatives

Current Windows D3D12/DXBC is the initial baseline. Vulkan is not a supported final fallback. SPIR-V as compiler IR is decided in [ADR-008](ADR-008-shader-ir-dxbc-vs-dxil.md); no Vulkan runtime is implied. Removal follows validated parity.

A broad upstream transplant or deletion-first migration is rejected because source and issue history show title, vendor, lifetime and timing regressions.

## Validation and follow-up

RG-GDK-006 through RG-GDK-012, RG-GDK-023. See [architecture plan](../architecture-plan.md), [roadmap](../roadmap.md) and [regression strategy](../regression-strategy.md). Changes to this settled policy require a superseding ADR with evidence, not an undocumented agent assumption.
