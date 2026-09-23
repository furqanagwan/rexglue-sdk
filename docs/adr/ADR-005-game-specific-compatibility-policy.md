# ADR-005: Explicit compatibility scope

Status: **Accepted policy/destination; implementation staged**. Date: 2026-09-23.

## Context

The fork must selectively modernize Xenia-derived compatibility while preserving static recompilation and controlling regressions. Current code does not yet implement all target policies. See [source investigation](../investigation.md).

## Decision

General correctness, title-specific, driver-specific and experimental behavior must be distinguished; title behavior cannot silently become global.

## Consequences and rejected alternatives

Any future profile mechanism must bind title/module version/hash, rationale, source provenance, test, owner, disable control and review/removal condition. No scattered unexplained title checks. Whether a runtime database is needed remains a design issue; this ADR does not implement it.

A broad upstream transplant or deletion-first migration is rejected because source and issue history show title, vendor, lifetime and timing regressions.

## Validation and follow-up

RG-GDK-012, RG-GDK-013, RG-GDK-016. See [architecture plan](../architecture-plan.md), [roadmap](../roadmap.md) and [regression strategy](../regression-strategy.md). Changes to this settled policy require a superseding ADR with evidence, not an undocumented agent assumption.
