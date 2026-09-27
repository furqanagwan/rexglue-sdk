# Indirect PPC function discovery investigation

Issue: [RG-FIX-002](https://github.com/furqanagwan/rexglue-sdk/issues/32).
This is an investigation record, not a compatibility claim or an approved
scanner change.

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
