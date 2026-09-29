# RG-FIX-006: CRT setjmp / longjmp

Issue: [#107](https://github.com/furqanagwan/rexglue-sdk/issues/107).
SDK baseline: `8e4b9f10c502a7696058b5522923701a11e7b27e`.
Investigation date: 2026-09-28. Design: [ADR-010](adr/ADR-010-static-nonlocal-jumps.md).

## Trigger and ownership

The user reports Quantum of Solace failed on save-and-exit. The investigation configured the
existing native jump overrides on the title branch `RG-007-007`, then searched
Blood Stone for the same CRT behavior. There is **no reported Blood Stone
setjmp/longjmp gameplay failure**. Its matching routines warrant shared SDK
recognition and regression testing, not a claim that a Blood Stone crash was
fixed. Title configs and interactive evidence belong in `furqanagwan/007`.

## Observed ABI

| Title | setjmp | longjmp | Evidence |
| --- | --- | --- | --- |
| Quantum of Solace | `0x825ABAE0` | `0x825AB7C0` | explicit hints; matching generated instruction trace |
| Blood Stone | `0x82B15EC0` | `0x82B16190` | Matching trace; unique automatic pair in private codegen |
| 007 Legends | `0x828AB380` | `0x828AB650` | Matching generated instruction trace |

The 179-word save routine stores f14-f31, r13-r31, v64-v127, LR, CR and SP,
and initializes the buffer's mode word. The 197-word restore routine normalizes
a zero return value and restores those registers. Its ordinary path calls a
small diagnostic-record helper; its alternate mode calls `RtlUnwind`. Full
layout matching varies only relocated hook-pointer immediates and relative
call operands. The common helper's two calls must resolve to the same executable
target and the unwind call must name the correct import.

Blood Stone has four direct setjmp callers; Legends has one. Each observed
caller contains one static setjmp site. Synthetic tests additionally exercise
multiple buffers in one caller and nested native frames. No game instructions,
executables, generated source or saves are distributed with these tests.

## Validation record

Local logs and private codegen output are under ignored `out/rgfix006`.
The synthetic detector corpus tests full patterns, mutated register operations,
every truncated prefix, non-executable data, invalid call forms/targets,
duplicate/partial matches, explicit overrides and unsafe localization settings.

Native helper tests check signed and zero returns, register restoration after
destructor side effects, nested-frame cleanup, independent snapshots, expiration
and thread isolation. PPC assembly fixtures compile through the production
emitter and execute the actual generated call sites.

Win-amd64 Debug and Release CTest each passed 1,929 tests (four existing
BitStream skips). Private codegen without jump hints recognized the pair in all
three titles: Quantum of Solace `0x825ABAE0`/`0x825AB7C0`, Legends
`0x828AB380`/`0x828AB650` and Blood Stone `0x82B15EC0`/`0x82B16190`. The GDK
Release SDK installed and Blood Stone's generated project built and linked.
Quantum of Solace's interactive save-and-exit check is tracked in the 007
repository.

Initial generated fixture
failures were unresolved synthetic helper calls; registering the reserved helper
symbols in the test graph fixed that test harness omission. The first scanner
probe correctly refused the pair until its relocation validation accounted for
the alternate branch's kernel import. Neither failure was a title regression.

AMD/Intel graphics are unavailable and remain untested, non-blocking per ADR-007.
This CPU/codegen change makes no new graphics compatibility claim. A front-end
run cannot close Quantum of Solace's save-and-exit validation.

## Provenance

This is original adaptation of the SDK's existing manual host-jump support,
inspected at the pinned baseline above. No upstream patch is copied. Private
title identities are recorded in the 007 repository's RG-007-006 evidence;
Quantum of Solace's identity is in [the prior discovery investigation](indirect-function-discovery.md).
The design retains a native static call stack and uses no PPC JIT machinery.

Read-only Edge reference: `12e3b4223dd4c2e41d57ea4b4477546affe4ce10`,
`src/xenia/kernel/xthread.cc` (native Windows reentry unwind) and
`src/xenia/cpu/xex_module.cc` (speculative function discovery). Classification
D/C: emulator-specific mechanisms requiring redesign, not portable fixes.
No corresponding upstream PR is adopted; its merge state and follow-up
regressions are therefore not used as evidence for this implementation.
