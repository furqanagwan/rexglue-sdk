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
