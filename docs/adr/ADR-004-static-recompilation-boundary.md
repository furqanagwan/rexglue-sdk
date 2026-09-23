# ADR-004: Static recompilation boundary

Status: **Accepted policy/destination; implementation staged**. Date: 2026-09-23.

## Context

The fork must selectively modernize Xenia-derived compatibility while preserving static recompilation and controlling regressions. Current code does not yet implement all target policies. See [source investigation](../investigation.md).

## Decision

Guest PPC CPU execution remains generated native C++ through registered function dispatch.

## Consequences and rejected alternatives

Do not adopt Xenia JIT/CPU backends, dynamic PPC fallback or JIT-dependent scheduler/exception machinery. Guest shader translation remains allowed. Patched guest CPU instructions require regeneration or explicit generated function overrides. Relaunched modules must already be compiled.

A broad upstream transplant or deletion-first migration is rejected because source and issue history show title, vendor, lifetime and timing regressions.

## Validation and follow-up

RG-GDK-003, RG-GDK-014 through RG-GDK-017. See [architecture plan](../architecture-plan.md), [roadmap](../roadmap.md) and [regression strategy](../regression-strategy.md). Changes to this settled policy require a superseding ADR with evidence, not an undocumented agent assumption.
