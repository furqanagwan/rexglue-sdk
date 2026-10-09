# Rust or C++?

**Conclusion: stay on C++23.** A move to Rust would cost years of rewriting
for a safety gain that is mostly unavailable here: the guest code works on
raw console memory and would be `unsafe` anyway. Get most of Rust's benefit
more cheaply, by fuzzing and sanitizing the C++ parts that read untrusted
files. Revisit only if a self-contained new component appears that has no
upstream C++ to follow.

## What the code is

| Part | Size (hand-written, measured 2026-10-09) | Nature |
| --- | --- | --- |
| Recompiled game code | Millions of generated lines per game | PowerPC translated to C++; every access is raw guest memory |
| Runtime: kernel, memory, threads | 46k lines | Emulates the console's kernel; pointer-heavy |
| Graphics: Xenos to Direct3D 12 | 87k lines | Shader translators, EDRAM, D3D12 COM |
| Audio, input, files, UI, Guide | 47k lines | XAudio2, GameInput, Win32, ImGui |
| Codegen tool and CLI | 29k lines | Reads XEX files, writes C++ |

## Where Rust would help

- **Parsing untrusted files.** Disc images, XEX, STFS packages, XDBF, XUI
  scenes and fonts come from the player's own files. Out-of-bounds reads
  there are exactly the bugs Rust prevents.
- **Thread safety.** The runtime runs many host threads (guest threads, GPU,
  audio, UI). Rust's `Send`/`Sync` rules catch data races at compile time.
  They would not have caught the achievement-popup freeze fixed in PR #223,
  which was Windows message re-entrancy, not a data race.
- **Tooling.** Cargo builds, tests and fuzzes with one command.

## Why it doesn't pay off here

1. **The core is unsafe by nature.** Generated game code reads and writes
   console memory by address, byte-swaps it and jumps through function tables.
   In Rust all of it would sit in `unsafe` blocks, which removes the guarantee
   that matters.
2. **Compile times.** A game is millions of generated lines. Clang already
   needs minutes; `rustc` is generally slower on huge generated functions.
   That's the slowest loop in the workflow.
3. **Upstream is C++.** Xenia, Canary and Edge are where most fixes come from
   (see `docs/upstream-tracking.md`). Today a port is a diff; in Rust every
   port becomes a translation and a fresh review, so we'd fall behind upstream.
4. **The platform is C++.** Direct3D 12, XAudio2, GameInput and the GDK's
   Gaming Runtime are C/C++ (COM) APIs. The `windows` crate covers Direct3D 12
   and XAudio2, but GameInput and the GDK have no official Rust bindings and
   Microsoft supports GDK development in C++.
5. **Dependencies are C/C++.** FFmpeg (XMA audio), Mesa (`spirv_to_dxil`),
   DXC, ImGui and the shader tooling would all stay C/C++ behind FFI.
6. **Cost.** About 210k hand-written lines, generator included: a
   multi-year rewrite with no new features, against an alpha that's still
   finding its feet.

## Getting the safety without switching

| Rust benefit | C++ equivalent here |
| --- | --- |
| Bounds-checked parsing | `std::span` readers that check every offset (the pattern in `src/system/xex_title_name.cpp`); libc++/MSVC hardened modes in Debug |
| Finding memory bugs | AddressSanitizer builds of the unit tests in CI (Clang supports it on Windows) |
| Hostile input | libFuzzer targets for XEX, ISO/XDVDFS, STFS, XDBF and XUI readers |
| Data races | Clang's thread-safety annotations on shared state; ThreadSanitizer is not available on Windows, so rely on annotations and review |
| Lints | `clang-tidy` in CI (bugprone, modernize, naming) |

## If Rust is ever used

Pick something self-contained with a small C API, such as the **updater**
(it downloads, verifies and swaps files, and touches no guest memory) or a
future **file-format parser** library. Build it as a static library through
`corrosion` in CMake, expose a C ABI, and fuzz it with `cargo fuzz`.
Don't put Rust inside the recompiled game or the GPU path.

## Follow-up work

- Add ASan and libFuzzer builds for the file parsers (issue to be filed).
- Add `clang-tidy` to CI (part of the [audit plan](../audit/2026-10-09-codebase-audit.md)).
