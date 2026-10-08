# Synced Edge GPU comparison, 2026-10-07

The owner's [fork](https://github.com/furqanagwan/xenia-edge/tree/edge) and
`has207/xenia-edge:edge` are identical at
`669b4266f5682e5169d42552fdf64f02880652a4` at this review. GitHub compare reports
zero ahead/behind commits. Syncing supplied upstream changes; it does not
establish fork-specific GPU improvements. Source history/diffs were read locally
from a filtered reference clone; no runtime dependency or upstream write was
created. The comparison base is `94de4f676` from the September 23 investigation;
later SDK ports and the DXIL source pin `0788c561e3` are checked separately.

## Changes relevant to this SDK

| Source | Local classification | Evidence / next action |
| --- | --- | --- |
| [`669b4266`](https://github.com/has207/xenia-edge/commit/669b4266f5682e5169d42552fdf64f02880652a4), `getBCF` | Missing; correctness port candidate | Both local fetch translators emit `getBCF is unimplemented`. Edge samples twice with forced black/white border samplers and returns the maximum component difference; cube returns zero. Requires sampler binding metadata and signed-view treatment, not only translator code. Test filter, mip/LOD, dimensions, scaling, signed formats and cube controls. |
| [`1b0e9d00`](https://github.com/has207/xenia-edge/commit/1b0e9d00ea33e6148c3429234e44e8c364edbd7d), primitive conversion invalidation | Missing at review; adapted in a separate follow-up | The pinned review base has the old end-vs-end comparison and caches invalidated in-flight results. `gpu-primitive-cache-invalidation` preserves the local mutex/callback contract and adds CPU regressions. See the tracking ledger and release evidence for its separate validation; no global/JIT locking is imported. |
| `bc9098de`, guest-pixel-center point sampling at resolution scale | Present in optional DXIL source; partial across shader paths | Local SPIR-V has `IsGuestPixelCenterFetchNeeded` and interpolant guest-center deltas from the October 3 source pin. DXBC has the earlier texel-center snap but not those named interpolant-delta mechanisms. Do not call the two fixes equivalent; compare scaled readbacks before a further DXBC port. |
| `7d0a45263`, scaled lines become one guest-pixel quads | Adapted | DXBC geometry-shader adaptation and RTV/ROV 1x/2x line fixtures are recorded in the tracking ledger. Optional DXIL carries the Edge source version. |
| `c3cd8617b`, point-fetch texel centers | Adapted | DXBC integer/center corrections are recorded under RG-GDK-045; the later `bc9098de` correction above is separate. |
| `04085efa`, stacked texture Inf/NaN layer clamps | Adapted | Local DXBC fetch fix and October 3 SPIR-V pin; no claim of tested compatibility for the upstream affected title. |
| `692cd59cf`, VIZ_QUERY | Adapted, opt-in | Local survey/predicate state, RTV/ROV fixture and fallback handling; `occlusion_query_viz` remains off by default. #65 needs acceptance review rather than another wholesale port. |
| `d8731edc`, volume resolve spacing; `ace153cb` / `81e3deae` / `c332733a`, texture layouts | Adapted | Local hand ports preserve older SDK interfaces; texture-layout unit fixtures are recorded. Volume-title behavior is not certified by a 2D fixture. |
| `de8e60601`, persistent async stand-in waits | Adapted | Local pipeline await path is already recorded. Remaining gameplay hitches (#120) need attribution; skipping draws globally is not an acceptable substitute. |
| `77f2cca80`, `935e03876`, `776dda2e3`; `16df25981`, `b83724656`, `34387b31f`, `1222c23f7`, `a7c39fa7d` | Deferred coupled redesign | Resolve read-watch, scaled extents, memexport pages and per-submission copyback dependencies differ from local `readback_resolve=fast`. Review as a bounded architecture change with coherency/readback tests; copying individual commits can lose ordering. |
| `3171a10a`, always-set Mesa pipeline bit removal | Not directly transferable | Edge retired DXBC; this SDK deliberately supports DXBC plus optional DXIL. Preserve distinct shader/cache keys until ADR-008's parity/retirement gates pass. |
| `4d15111d`, OG Xbox-specific shader cache keys | Outside current execution scope | This SDK statically executes Xbox 360 PPC titles; it has no XeFu original-Xbox execution backend. Presentation selection does not create one. |
| Metal/Vulkan changes in the same GPU history | Reference only | No matching supported local runtime backend. Do not reintroduce them to take a shared shader fix. |

The remaining October 6–7 updates primarily concern XeFu/OG Xbox launch/config,
kernel I/O, memory/trap frames, presenter teardown and XAM/UI behavior. They
cannot be treated as GPU upgrades or blindly mapped onto static PPC runtime
thread/I/O semantics. The latest `mcrfs` rounding-preservation correction is
already reviewed in PPC PR #162; that PR remains separate from SDK main.

## Is this implementation better?

There is no measured basis for a universal claim. The SDK has static PPC
execution, installed-consumer/plugin ABI checks and existing DXBC adaptations
that Edge's JIT/retired-DXBC code does not offer in the same form. Edge has
real GPU corrections missing locally and a different resolve coherency design.
Those are specific differences, not a performance or correctness ranking.

Existing [ADR-008 measurements](adr/ADR-008-shader-ir-dxbc-vs-dxil.md) and
[tracking ledger](upstream-tracking.md) identify what passed and what is still
unvalidated. Use synthetic readback and pinned 007 scenes to measure a proposed
adaptation. Source recency, compilation and matching function names alone do
not prove parity or superiority. New ports must include full source SHA,
motivation, comments/associated PR state when present, known follow-ups, local
locking/API adaptation and measurable regression tests in the ledger.
