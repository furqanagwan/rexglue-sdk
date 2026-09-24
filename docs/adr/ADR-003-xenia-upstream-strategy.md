# ADR-003: Selective upstream adaptation

Status: **Accepted policy/destination; implementation staged**. Date: 2026-09-23.

## Context

The fork must selectively modernize Xenia-derived compatibility while preserving static recompilation and controlling regressions. Current code does not yet implement all target policies. See [source investigation](../investigation.md).

## Decision

Treat Xenia, Canary, Edge and upstream ReXGlue as read-only evidence; port narrowly into the personal ReXGlue fork.

## Consequences and rejected alternatives

The personal Edge fork is for controlled research, not runtime coupling. Record exact source/PR/issue provenance, rejected proposals and follow-up regressions. Patch-equivalence and source comparison matter more than newer timestamps. Review monthly and before ports; no automatic merge.

A broad upstream transplant or deletion-first migration is rejected because source and issue history show title, vendor, lifetime and timing regressions.

## Validation and follow-up

RG-GDK-026. See [architecture plan](../architecture-plan.md), [roadmap](../roadmap.md) and [regression strategy](../regression-strategy.md). Changes to this settled policy require a superseding ADR with evidence, not an undocumented agent assumption.
