# ADR-001: Windows PC and April 2026 GDK

Status: **Accepted policy/destination; implementation staged**. Date: 2026-09-23.

## Context

The fork must selectively modernize Xenia-derived compatibility while preserving static recompilation and controlling regressions. Current code does not yet implement all target policies. See [source investigation](../investigation.md).

## Decision

Windows PC is the sole host destination; public PC April 2026 GDK is the integration target. Initial validated configuration is to be x64; other CPU architectures need separate evidence.

## Consequences and rejected alternatives

Keep guest semantics separate from native services. Retain legacy host code only until replacement parity and cleanup gates pass. GDKX console deployment is outside this decision.

A broad upstream transplant or deletion-first migration is rejected because source and issue history show title, vendor, lifetime and timing regressions.

## Validation and follow-up

RG-GDK-002, RG-GDK-022, RG-GDK-024. See [architecture plan](../architecture-plan.md), [roadmap](../roadmap.md) and [regression strategy](../regression-strategy.md). Changes to this settled policy require a superseding ADR with evidence, not an undocumented agent assumption.
