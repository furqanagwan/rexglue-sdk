# ADR-006: Regression-controlled migration

Status: **Accepted policy/destination; implementation staged**. Date: 2026-09-23.

## Context

The fork must selectively modernize Xenia-derived compatibility while preserving static recompilation and controlling regressions. Current code does not yet implement all target policies. See [source investigation](../investigation.md).

## Decision

Compatibility evidence, not compilation, gates subsystem migration and release.

## Consequences and rejected alternatives

Establish last-good baselines, synthetic and representative-title tests, relevant AMD/NVIDIA/Intel evidence, ordinary Windows/GDK deployment checks and rollback. Missing hardware/material is blocked. Do not distribute game data or restricted SDK content. Closed upstream reports do not prove a local fix.

A broad upstream transplant or deletion-first migration is rejected because source and issue history show title, vendor, lifetime and timing regressions.

## Validation and follow-up

RG-GDK-001, RG-GDK-006, RG-GDK-025. See [architecture plan](../architecture-plan.md), [roadmap](../roadmap.md) and [regression strategy](../regression-strategy.md). Changes to this settled policy require a superseding ADR with evidence, not an undocumented agent assumption.
