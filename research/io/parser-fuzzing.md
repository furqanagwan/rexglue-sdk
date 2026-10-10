# Parser fuzzing

Issue #234 added libFuzzer targets for the file parsers and an
AddressSanitizer (ASan) build. How to run them is in
[fuzzing](../../docs/fuzzing.md). This page records what the runs found and
the toolchain problems behind the build settings.

## Toolchain

LLVM Clang 22.1.8, Visual Studio 18 Community (MSVC 14.51), GDK 260404,
Windows 11. The `win-amd64-gdk-fuzz` preset, Release configuration.

| Problem | Cause | Setting |
| --- | --- | --- |
| Link error: `annotate_string` / `annotate_vector` mismatch | The MSVC STL turns on container annotations under ASan; libFuzzer was built without them | `_DISABLE_STRING_ANNOTATION`, `_DISABLE_VECTOR_ANNOTATION` |
| Link error: `RuntimeLibrary` MT_StaticRelease vs MD_DynamicRelease | LLVM ships `clang_rt.fuzzer-x86_64.lib` built with `/MT` | The fuzz build uses `CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded` |
| Programs exit with 0xC0000139 (entry point not found) | Visual Studio ships its own `clang_rt.asan_dynamic-x86_64.dll`, which comes first on a developer shell's `PATH` and does not match Clang 22 | Configure copies the compiler's DLL next to the built programs |
| Coverage of 4 edges on the XEX target | libFuzzer on Windows only reads coverage counters from the executable, not from `rexruntime.dll` | The fuzz build makes `rexruntime` a static library and skips the install rules |

## Bugs found

The first run, with only the synthetic seeds, crashed three of the four
targets within seconds. Each fix has a unit test built from the failing case.

| Parser | Failure | Fix | Test |
| --- | --- | --- | --- |
| XEX | `XexModule::Load` copied `header_size` bytes without checking them against the input; security info, page descriptors and optional headers were read at file-supplied offsets | `XexModule::IsHeaderWellFormed` checks every one against the header before the copy. The image readers check block, chunk and AES lengths against the input and the guest allocation, and a base address with no heap is refused | `tests/unit/system/parser_bounds_test.cpp` |
| XDBF | `GetStringTableEntry` read string lengths past the table; entry tables and blocks were never checked against the data | The entry table, each block and each string and achievement entry are bounded | `tests/unit/system/parser_bounds_test.cpp` |
| XDVDFS | A name that is not UTF-8 made `utf8_find_name_from_path` throw | Such a name marks the directory as damaged | `tests/unit/filesystem/disc_image_test.cpp` |
| STFS, SVOD | Same names as XDVDFS (found by reading, not by a crash) | Such a name refuses the package | `tests/unit/filesystem/stfs_container_test.cpp` |

`rex::string::utf8_is_valid` was added for the name checks.

## Recorded runs

2026-10-10, `win-amd64-gdk-fuzz` Release, after the fixes above. Each target
ran twice for 60 seconds; the second run started from the first run's corpus.
The table shows the second run. No run found a failure.

| Target | Edges | Features | Executions | Corpus |
| --- | ---: | ---: | ---: | ---: |
| `xex_fuzzer` | 429 | 616 | 918 | 59 |
| `xdbf_fuzzer` | 106 | 272 | 18,154,345 | 99 |
| `xdvdfs_fuzzer` | 388 | 616 | 1,002,233 | 58 |
| `stfs_fuzzer` | 446 | 613 | 523,378 | 15 |
| `xui_fuzzer` | 313 | 1,131 | 2,452,690 | 255 |

The first run of `xui_fuzzer` was in the Xbox repository's own fuzz build:
2,414,370 executions, 308 edges, no failures.

`xex_fuzzer` runs 14 to 36 inputs a second. Each input resets and maps the
guest heap, so it needs much longer runs than the others to go deep. The
image readers behind encrypted or compressed XEX files are mostly unreached:
a block must match its SHA-1 before it is decompressed.

## AddressSanitizer unit tests

`win-amd64-gdk-asan` Release, `ctest -L unit`: 607 tests. The first run had
14 audio tests exit with an access violation and no ASan report. ASan on
Windows commits shadow memory on demand from its own vectored exception
handler. The SDK's guest-memory handler was registered to run first, and it
is instrumented code, so the likely cause is a shadow fault inside it
faulting again until the stack ran out. No debugger was available to confirm
it. Under ASan the SDK handler now runs after the other handlers
(`src/core/exception_handler_win.cpp`), and the audio tests then passed.

One more test, `OpenExisting read-only handle reads`, failed only when cases
ran in parallel. Every CTest process named its temp file
`rexglue_filesystem_test_0.bin`; the name now includes the process ID.

## Limits

- 60 seconds per target is a smoke run, not a campaign. Longer runs belong
  before a release that changes a parser.
- `XexModule::LoadContinue` (PE headers, imports, exports) is not fuzzed; it
  reads guest memory that `Load` filled.
- LZX decompression is reached only through valid compressed blocks.
