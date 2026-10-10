# Codegen builder names

The 415 instruction builder functions use PascalCase (`BuildFres`) consistently
with the rest of the SDK. Issue
[#228](https://github.com/furqanagwan/rexglue-sdk/issues/228) changes identifiers
only, preserving dispatch keys, instruction logic and generated guest code.

The rename covers `src/codegen/builders.h`, the eight implementation files in
`src/codegen/builders/`, and `src/codegen/instruction_dispatch.cpp`. Every
`build_` token maps to `Build` followed by capitalized underscore-separated
parts. All 415 names are unique, none collide with existing identifiers, and
reversing the substitution reproduces the original source bytes.

## Generation comparison

Baseline: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, Windows x64, Clang
22.1.8, GDK 260404, Release `rexglue`. Both sides are freshly generated with
the same assembler binaries, source assembly, skip list and known-failure
list. SHA-256 comparisons show byte-identical output:

| Suite | Generated files | Cases |
| --- | --- | --- |
| Ordinary PPC instruction tests | 4 | 1,599 |
| Hardware-captured PPC corpus, 16 chunks | 35 | 169,459 |

The corpus retains its existing 917 skipped cases and eight expected failures;
the rename changes neither policy. Generated outputs and binaries remain
private under `out/audit-20261010/`.

Changed-line Clang-Tidy passes on all nine compiled implementation files. The
header has no compilation database entry and is checked through compilation.
Runtime validation on 2026-10-10:

- GDK Release: all 2,192 selected PPC tests pass, including 567 corpus groups.
- GDK Debug: 2,191 selected tests pass, plus the separately invoked
  `ppc_corpus.instr_mtmsrd` group passes in 0.06 seconds. This covers all 2,192
  selections, including all 567 corpus groups, with no untested group.
- Both configurations build `rexglue`, `ppc_tests` and `ppc_corpus_tests`.

The earlier slow Debug `mtmsrd` observation is not reproduced on this baseline.
The generated test runner already uses `PPCInterruptTestScope`; the rename
does not modify that scope or the runtime interrupt implementation. These are
PPC software checks, not a new title or GPU compatibility claim.
