# PPC test corpus (RG-GDK-054)

The PowerPC instruction tests from has207/xenia-edge
`src/xenia/cpu/ppc/testing` at `b5cc59e854020f8406c0b3a96eff6a3d036a514b`
(2026-10-01): 578 `.s` files, 167,636 of the cases (`instr__gen_*.s`, labels
ending `_GEN`) captured on Xbox 360 hardware by xenia-project's `gen_tests`,
the rest written by hand. They are Xenia project files under its BSD licence
(`LICENSE` at the repository root carries the notice). Provenance is in
`docs/upstream-tracking.md`.

Configure with `-DREXGLUE_PPC_CORPUS=ON` to build `ppc_corpus_tests`; each
file is one CTest test, `ppc_corpus.<file stem>`, labelled `ppc_corpus`:

```powershell
cmake --preset win-amd64 -DREXGLUE_PPC_CORPUS=ON
cmake --build --preset win-amd64-release --target ppc_corpus_tests
ctest --preset win-amd64-release -L ppc_corpus
```

`rexglue recompile-tests --table` generates the cases as data, run from one
loop per file (`ppc_table_runner.h`), so the corpus compiles in a few minutes.
A failing case prints one line naming its first wrong register or byte.

| File | Contents |
| --- | --- |
| `skip.txt` | Edge's list of captures it judges self-inconsistent; left out. |
| `assembler_unsupported.txt` | Files the bundled binutils cannot assemble; left out. |
| `known_failures.txt` | Cases expected to fail, each with its cause (an issue, or a corpus error). |

A known failure that passes fails its file's test, so a fix must remove its
entries. To rebuild the list, run `ppc_corpus_tests` with
`PPC_CORPUS_FAILURES` set to a file path: every failing case is appended to it
as `<file stem>/<label> <first mismatch>`.
