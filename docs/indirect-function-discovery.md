# Indirect PPC function discovery investigation

Issue: [RG-FIX-002](https://github.com/furqanagwan/rexglue-sdk/issues/32).
This records the diagnosis, rejected experiments and bounded discovery fix.
It is not a general indirect-call completeness or title compatibility claim.

## Observed gap

For the private Quantum of Solace XEX (title `415607FF`, media `06DD88A0`,
SHA-256 `a96f4f651cc0937e51aa2f81245b48ba08d71de1b8bef0e33bc2b2bca29caa42`),
several indirect calls reach aligned executable PPC entry points missing from
the generated function registry. Adding exact title configuration hints emits
their original instruction bodies and advances two repeat NVIDIA D3D12 runs
past each former fatal. Current title evidence is in the private `007` project
and [007 issue #6](https://github.com/furqanagwan/007/issues/6).

The codegen debug log reports `VTableScanner: found 0 Complete Object
Locators` for this XEX. The current `VTableScanner` only starts from RTTI COL
patterns in `.rdata`, so it contributes no function entries through that path
for this title. The separate `functionPointerScan` is disabled in
`src/codegen/analyze.cpp` because it produced too many false positives.
These facts do not yet establish how each missing pointer is stored.

## Private XEX probe, 2026-09-24

A temporary read-only probe over decoded non-executable sections found all
seven sampled missing targets as big-endian pointers in `.rdata`. Example:
`0x82462590` at `0x82096A18` is between pointers to registered code, and
`0x8211E798` occurs in five `.rdata` locations with registered code pointers
on both sides. `0x821C1C20` also occurs in `.data` as part of the known
jump table, so a generic executable-pointer scan would conflate different
structures. Raw pointer logs remain private with the title material.

An experimental rule after gap filling selected unknown executable addresses
in `.rdata` only when at least two of the four adjacent dwords were already
registered functions. Without title hints it proposed 49 unique entries and
included all seven sampled missing targets. Registering all 49 is **rejected**:
although codegen completed, it introduced unresolved conditional branches
from `0x8211E7AC`, `0x8211E7EC`, `0x824E16C8`, `0x824E16F0`, and
`0x824E1718`, plus an unresolved branch/function involving `0x825BC4D4`.
The experiment was local and fully reverted; no generated experimental title
binary was used for compatibility testing. Neighboring registered pointers
alone are not sufficient evidence of safe function boundaries.

## Required diagnosis before changing discovery

1. Trace an observed target from guest memory through its indirect call site
   and identify the source table or object. Record the containing XEX section,
   references, neighboring values, and decoded target instructions privately.
2. Check whether the table is an RTTI-free vtable, jump table, function-pointer
   array, or another structure. A run of executable addresses alone is not
   sufficient evidence: jump-table labels may be internal to one function.
3. Build synthetic positive and negative fixtures for the exact pattern.
   Compare function boundaries, registration sets, unresolved branches, and
   false positives before considering a default-on rule.
4. Rebuild Debug and Release SDK tests and rerun the pinned title scene twice.
   Record any next failure without claiming a successful boot.

Until then, exact title entry hints stay in the 007 repository. Do not enable
the broad pointer scan merely to move a title crash forward.

## Gap-fill diagnosis, 2026-09-28

The comparison uses SDK `d6ccced` and the same pinned XEX above, with **no
title function hints** in either analysis. The previous RTTI observation was
correct, but was not the immediate reason gap filling lost these entries.

One complete static pointer-storage trace is:

1. The `.rdata` dword at `0x82096A18` contains `0x82462590`, in big-endian
   guest format.
2. Code at `0x82465ABC` / `0x82465AD4` constructs `0x820969F8` and stores it
   at offset zero of the object at `0x82465AE4`. Code at `0x82462490` /
   `0x82462498` installs that same object table at `0x824624A0`.
   Thus the target occupies virtual-method slot `+0x20`; this is an object
   dispatch table, not merely an unexplained sequence of executable pointers.
   No RTTI Complete Object Locator is found by this SDK's scanner. This is a
   static storage trace, not a claim to have captured the live object/call site.
3. The original target has five instructions: three pointer loads through
   object offsets `0x1C`, `0x10`, `0x1C`, a floating-point load at `+0x3C`,
   and `blr`. It is an independent method, not a switch-table label.
4. Initial gap splitting registers `0x82462578..0x824625A4` as one segment.
   It splits on returns and already-known direct tail targets, but not on the
   preceding method's indirect `bctr` at `0x8246258C`. Block discovery correctly
   stops that method at `0x82462590`. The segment retains its larger provisional
   extent; the suffix containing the independent method is never reconsidered.

There is a second, distinct case at `0x821C1BF8`: it is a `li r3,constant;
blr` leaf inside the switch function `0x821C1B90`, also reached by an
unconditional direct tail branch at `0x824A287C`. Main's graph leaves that
branch unresolved, and emission reports both an unresolved branch and a
missing call target. A switch reference alone would not justify an entry;
the direct branch from another function does, for this self-contained leaf.

## Conservative rule

* Revisit only trailing bytes of **discovered GAP_FILL segments** whose
  decoded blocks end before their provisional extent. Keep the existing
  segmentation, entry ownership and exception-data checks. Skip a suffix
  targeted by the owner's unresolved branches, zero padding, and a standalone
  return-only suffix. Iterate with the existing discovery limit.
* Preserve normal absorbed-gap cleanup. A recovered function does not get
  permission to protect every local block as another entry.
* Once normal merge resolution converges, allow an aligned unconditional
  direct tail branch into another function's decoded `li r3,IMM; blr` block
  to establish a callable entry. Do not promote calls, conditional branches,
  addresses covered only by declared bounds, or arbitrary shared epilogues.
  The latter can depend on the caller's frame and localized registers.
* During emission use the actual owning function when classifying branches
  in overlapping blocks. A branch within its decoded blocks stays a local
  label; a `bl` to a registered entry remains a call.

The broad pointer scanner remains disabled. No title ID, address list, runtime
fallback or PPC JIT is introduced. Original title hints remain in 007.

## Rejected takeover behavior

The initial gap-leftover implementation added 62 entries and removed none on
the no-hints title. Its cleanup exemption also retained a synthetic ordinary
local return block as a callable function. Removing that exemption yields
60 additions and six removals: the removed entries are internal blocks of
newly recovered functions. Fourteen additions were unreferenced return-only
suffixes; these are excluded by the final conservative rule. Their lack of
references is diagnostic evidence, not a new pointer-scanning heuristic.

The initial shared-tail proposal also accepted arbitrary decoded bodies.
The final rule accepts only the constant-return leaf above; a synthetic
frame-reading shared epilogue must remain unresolved rather than acquire an
unsafe independent calling convention.

## Validation

`tests/unit/codegen/indirect_discovery_test.cpp` exercises the full analysis
pipeline on independently authored PPC fixtures, including a minimal valid
exception directory. Positives cover a newly known tail target, an indirect
tail dispatch followed by a leaf, and a shared constant-return leaf. Negatives
cover local return blocks, zero padding, loops, return-only suffixes, conditional
branches, calls, unaligned targets, gaps in declared bounds and frame-dependent
shared epilogues. Overlapping-owner branch classification is checked separately.

Private decoded sections, phase graph censuses and generated output comparisons
are retained under the ignored SDK build output (`out/rgfix002`). They are not
repository assets. Final build and title-run evidence is recorded below when
the regression gates complete.

### Pinned no-hints comparison

| Measurement | Main (`d6ccced`) | Candidate |
| --- | ---: | ---: |
| Registered mappings (including imports/helpers) | 21,800 | 21,840 |
| Added / removed entries | — | 46 / 6 |
| Unresolved graph branches | 1 | 0 |
| Unresolved emission diagnostics | 2 | 0 |
| Function pairs sharing decoded instruction bytes | 4,975 | 4,976 |

The only new overlapping pair is `0x821C1B90` / `0x821C1BF8`, the proven
shared leaf. All 46 additions have non-executable-section pointer references;
this corroborates the review but is not used to select entries. No false
boundary remains in the negative fixtures. The title comparison finds no
unexplained new overlap; it cannot prove every function boundary in the game.
The six removed entries are internal blocks of recovered methods:
`0x8211E7BC`, `0x8211E7FC`, `0x8233AE7C`, `0x824E16D4`, `0x824E16FC`,
`0x824E1724`.

Automatic discovery recovers all 13 non-switch methods from the title's 32
hints, plus the one directly referenced switch leaf without hints. The other
18 switch leaves remain intentionally unpromoted. For runtime validation the
private project retains **all 19 switch-leaf hints** and removes the 13 method
hints: partially hinting that switch changes the host's discovered blocks,
so the shared-leaf rule no longer applies to its unhinted case. Broadening
discovery just to bypass that boundary would defeat the conservative rule.
The tracked 007 configuration retains all 32 hints.
