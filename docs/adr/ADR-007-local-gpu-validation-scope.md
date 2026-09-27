# ADR-007: NVIDIA local validation; other GPU coverage is non-blocking

Status: **Accepted**. Date: 2026-09-23.

## Context

The user explicitly confirmed that only NVIDIA graphics can be tested and that
AMD/Intel GPU availability must not prevent completion. The machine's Intel CPU
does not provide Intel graphics validation. Earlier adapter enumeration is not
evidence that Intel GPU testing is available to the user.

## Decision

NVIDIA is the required local GPU validation target. AMD and Intel GPU testing is
recorded as unavailable and untested, with non-blocking follow-up coverage.
Implementation, issue completion and local delivery may proceed without it.
Do not claim compatibility on an untested vendor.

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
