# ADR-007: NVIDIA local validation; other GPU coverage is non-blocking

Status: **Accepted**. Date: 2026-09-23.

## Context

The user explicitly confirmed NVIDIA as the primary local graphics target and
that AMD GPU availability must not prevent completion. The development machine
also exposes Intel integrated graphics; the synthetic getBCF fixtures were
subsequently run on that adapter, but it is not the owner's primary GPU and
those fixtures alone do not establish general Intel title compatibility.

## Decision

NVIDIA is the required local GPU validation target. AMD GPU testing is recorded
as unavailable and untested, with non-blocking follow-up coverage. The limited
Intel getBCF fixture result is recorded without generalizing it to title
compatibility. Implementation, issue completion and local delivery may proceed
without other vendor coverage. Do not claim compatibility on an untested path.

This supersedes mandatory AMD/Intel completion gates in ADR-006, AGENTS.md,
the regression strategy and existing roadmap issue bodies. Those original issue
bodies retain their publication hashes; apply this explicit policy override when
assessing their acceptance criteria.

## Consequences

Retain portable D3D12 behavior and existing vendor compatibility handling.
Required NVIDIA, unit/PPC, synthetic, title, save and applicable deployment tests
remain in scope. Missing AMD/Intel results alone cannot keep an issue open.
Failures on available hardware and missing required title evidence still must
be resolved. Future external vendor results can establish broader coverage.
