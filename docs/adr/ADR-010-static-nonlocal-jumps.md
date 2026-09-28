# ADR-010: CRT non-local jumps in static code

Date: 2026-09-28. Status: implementation under validation in
[RG-FIX-006](https://github.com/furqanagwan/rexglue-sdk/issues/107).

## Context

Quantum of Solace's save-and-exit error path calls its CRT longjmp. Ordinary
PPC register restoration cannot unwind recompiled C++ calls. The existing
explicit `setjmp_address` / `longjmp_address` overrides already substitute
native jumps, but use one automatic context snapshot per caller and retain
thread-local buffers after their native frame returns.

## Decision

Recognize only the complete verified CRT register-save and restore layouts in
executable sections. Match relocation instructions and mapped targets, including
the alternate path's `xboxkrnl@327` (`RtlUnwind`) import. Apply only a unique
pair consistent with explicit hints. This is a shared ABI rule, not a title
profile or address list. Incomplete, changed and ambiguous candidates do not
enable substitutions.

Keep native setjmp at its generated direct call site, as a controlling
expression. Each native caller owns heap-backed snapshots keyed by guest buffer
address. The pointer to that state stays unchanged across the jump. Native
longjmp performs the Windows unwind, then the resumed caller restores guest
context and the signed return value (zero becomes one). Restoring after the
unwind prevents skipped frame destructors from corrupting the restored context.
Frame destruction unregisters its buffers without erasing a newer registration
of the same address. Registrations are thread-local.

Reject register-localization settings when jump substitutions are active.
Localized C++ automatic registers are not covered by context restoration.
An indirect or tail-called setjmp fails explicitly. Direct and indirect longjmp
use the same helper. A missing/expired/foreign-thread buffer fails explicitly.
The recognized setjmp routine's optional hook must remain null; a runtime guard
rejects an active hook instead of silently bypassing it.

## Limits and alternatives

This supports ordinary direct CRT setjmp/non-local-return paths. It does not
implement arbitrary guest jmp_buf memory inspection/copying, unwind-style buffers
created by other routines, guest `RtlUnwind`, cross-thread jumps, stack switching,
or jumps across host Windows callbacks. Copying the complete PPCContext retains
the existing explicit override's behavior; this is not an emulation of every
guest buffer byte. Native ARM64 execution is untested.

The implementation relies on Windows native unwinding, rather than portable ISO
C++ longjmp semantics. See Microsoft's [longjmp requirements](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/longjmp?view=msvc-170)
and [C++ unwind restrictions](https://learn.microsoft.com/en-us/cpp/cpp/using-setjmp-longjmp?view=msvc-170).
Tests must exercise optimized and unoptimized builds, real generated PPC calls,
skipped-frame destructors, multiple buffers, expiration, and thread isolation.
No broader compiler/platform guarantee follows from one toolchain's results.

Edge's JIT return-site recovery and thread reentry are separate mechanisms; none
is imported. Restoring that machinery would violate ADR-004. Merely finding the
CRT does not prove a title exercised it: keep recognition, boot and gameplay
evidence separate in the [investigation record](../crt-nonlocal-jumps.md).
