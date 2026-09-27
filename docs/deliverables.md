# Requested deliverables index

This index distinguishes delivered research/planning from implementation and
execution that remain roadmap work. Evidence is pinned to September 23, 2026.

| # | Deliverable | Artifact / status |
| --- | --- | --- |
| 1 | Executive technical summary | [Investigation](investigation.md#executive-assessment) |
| 2 | Repository ancestry | [Verified history and limits](investigation.md#repository-ancestry-and-divergence); exact original Xenia import unresolved |
| 3 | Fork divergence | [Pinned tips and counts](investigation.md#repository-ancestry-and-divergence) |
| 4 | Xenia/Canary/Edge comparison | [Applicability matrix](investigation.md#source-applicability-matrix) |
| 5 | Open Canary issues | [Review](upstream-review.md): all 96 indexed, review depth explicit |
| 6 | Open Canary PRs | [Review](upstream-review.md): all 60 indexed |
| 7 | Open Edge issues | [Review](upstream-review.md): all 27 indexed |
| 8 | Open Edge PRs | [Review](upstream-review.md): all 7 indexed |
| 9 | Recently closed/merged analysis | [Review](upstream-review.md): 42 selected items, including rejected PRs |
| 10 | Game-specific Edge inventory | [Scoped provenance](upstream-tracking.md), including rejected caps/silence and depth/scheduler hazards |
| 11 | Canary compatibility inventory | [Provenance](upstream-tracking.md), including already-present early XMA behavior in [investigation](investigation.md) |
| 12 | Regression inventory | [Upstream risks and local status](regression-strategy.md#regression-tracking-index) |
| 13 | Applicability matrix | [A–H matrix](investigation.md#source-applicability-matrix) |
| 14 | GPU/Xenos plan | [GPU sequence](architecture-plan.md#gpuxenos-sequence) |
| 15 | D3D12-only architecture | [Plan](architecture-plan.md) and [ADR-002](adr/ADR-002-direct3d12-only.md) |
| 16 | AMD assessment | [Vendor matrix](regression-strategy.md#gpu-vendor-assessment-and-matrix); untested locally |
| 17 | NVIDIA assessment | [Vendor matrix](regression-strategy.md#gpu-vendor-assessment-and-matrix); detected hardware is not a pass |
| 18 | Intel assessment | [Vendor matrix](regression-strategy.md#gpu-vendor-assessment-and-matrix); Arc/non-Arc distinction |
| 19 | GPU validation matrix | [Run requirements and matrix](regression-strategy.md); execution pending |
| 20 | XboxKrnl assessment | [Source matrix](investigation.md#source-applicability-matrix), issues #3/#14/#15 |
| 21 | XAM assessment | [Guest services](architecture-plan.md#guest-services-and-native-host-boundaries), issue #17 |
| 22 | Audio/XMA assessment | [Guest services](architecture-plan.md#guest-services-and-native-host-boundaries), issues #18/#19 |
| 23 | Input/GameInput assessment | [Guest services](architecture-plan.md#guest-services-and-native-host-boundaries), issue #20 |
| 24 | Windows migration | [Dependency map](architecture-plan.md#removal-dependency-map-and-build-migration) |
| 25 | Vulkan removal | [Dependency map](architecture-plan.md#removal-dependency-map-and-build-migration), issue #23 |
| 26 | Linux removal | [Dependency map](architecture-plan.md#removal-dependency-map-and-build-migration), issue #24 |
| 27 | macOS removal | [Dependency map](architecture-plan.md#removal-dependency-map-and-build-migration), issue #24 |
| 28 | GDK April 2026 matrix | [Official references and capability matrix](architecture-plan.md#april-2026-gdk-capability-matrix) |
| 29 | Build migration | [Build plan](architecture-plan.md#removal-dependency-map-and-build-migration), issues #2/#22/#24 |
| 30 | Detailed README specification | Delivered as the actual [README](../README.md), with current/target status separated |
| 31 | AGENTS.md | [Canonical handoff](../AGENTS.md) |
| 32 | ADR plan | Delivered as [six accepted policy ADRs](adr/README.md); shader/database choices remain research |
| 33 | Upstream tracking strategy | [Review process](upstream-tracking.md#review-process), issue #26 |
| 34 | Compatibility/regression strategy | [Baseline and test plan](regression-strategy.md) |
| 35 | Game-specific policy | [ADR-005](adr/ADR-005-game-specific-compatibility-policy.md); no runtime profile system implemented |
| 36 | Risk register | [Risks and controls](investigation.md#risk-register) |
| 37 | Sequential roadmap | [RG-GDK-001 through 026](roadmap.md) |
| 38 | Dependency graph | [Validated graph](roadmap.md#verified-dependency-graph) |
| 39 | Complete issue bodies | [Versioned bodies/index](roadmap/index.json) |
| 40 | Label plan | [Labels and actual applications](roadmap.md#label-plan) |
| 41 | Agent-ready list | [Queue](roadmap.md#agent-ready-queue-and-first-implementation): only #1 |
| 42 | Source/commit/PR/issue references | [Ledger](upstream-tracking.md), [snapshot](upstream-snapshot.json), official refs in [plan](architecture-plan.md) |
| 43 | Actual GitHub issue index | [Published #1–#26](roadmap.md#actual-issue-index) |
| 44 | Verified dependency graph | [Graph](roadmap.md#verified-dependency-graph), [live verification record](roadmap/github-verification.json) |
| 45 | Upstream→ReXGlue mapping | [Review](upstream-review.md), [compact ledger](upstream-tracking.md#compact-upstream-to-roadmap-index), [live issue index](roadmap.md) |
| 46 | Current regression index | [Index](regression-strategy.md#regression-tracking-index); no fabricated local regression tickets |
| 47 | Current agent-ready queue | [Baseline issue #1](https://github.com/furqanagwan/rexglue-sdk/issues/1) |
| 48 | First implementation recommendation | [#1 baseline](https://github.com/furqanagwan/rexglue-sdk/issues/1), then [#3 NtOpenFile](https://github.com/furqanagwan/rexglue-sdk/issues/3) after its gate |

Publication verification checks live titles, states, bodies, labels and linked
prerequisites. The dependency graph is an explicit issue-body/roadmap graph;
native GitHub blocking relationships were not configured. No runtime, title,
vendor or GDK deployment test is represented as passed by those document checks.
