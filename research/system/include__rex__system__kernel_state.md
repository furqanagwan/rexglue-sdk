# Kernel state: system source notes

This record preserves technical and API notes moved from `include/rex/system/kernel_state.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L48)

```text
// Kernel Import Trace Helpers
```

## Source note 2, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L50)

```text
// Use these macros for consistent logging of kernel import function calls.
```

## Source note 3, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L51)

```text
// Example usage:
```

## Source note 4, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L52)

```text
//   REXKRNL_IMPORT_TRACE("NtCreateFile", "path={} options={:#x}", path, opts);
```

## Source note 5, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L53)

```text
//   REXKRNL_IMPORT_RESULT("NtCreateFile", "{:#x}", result);
```

## Source note 6, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L54)

```text
//   REXKRNL_IMPORT_FAIL("NtCreateFile", "path='{}' -> {:#x}", path, result);
```

## Source note 7, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L66)

```text
// Kernel State Access Macros
```

## Source note 8, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L68)

```text
// Convenience macros for accessing the current thread's kernel state and
```

## Source note 9, line 69

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L69)

```text
// subsystems from kernel export (_entry) functions. These use the ThreadState
```

## Source note 10, line 70

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L70)

```text
// bound to the current thread via ThreadState::Bind().
```

## Source note 11, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L101)

```text
// (?), used by KeGetCurrentProcessType
```

## Source note 12, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L107)

```text
// 0x00
```

## Source note 13, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L108)

```text
// 0x04
```

## Source note 14, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L109)

```text
// 0x0C
```

## Source note 15, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L110)

```text
// 0x10
```

## Source note 16, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L111)

```text
// 0x14
```

## Source note 17, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L112)

```text
// 0x18
```

## Source note 18, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L113)

```text
// 0x19
```

## Source note 19, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L114)

```text
// 0x1A
```

## Source note 20, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L115)

```text
// 0x1B
```

## Source note 21, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L116)

```text
// 0x1C
```

## Source note 22, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L117)

```text
// 0x20
```

## Source note 23, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L118)

```text
// 0x24
```

## Source note 24, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L119)

```text
// 0x28
```

## Source note 25, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L120)

```text
// 0x2C
```

## Source note 26, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L121)

```text
// 0x2E
```

## Source note 27, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L122)

```text
// 0x2F
```

## Source note 28, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L123)

```text
// 0x30
```

## Source note 29, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L124)

```text
// 0x50
```

## Source note 30, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L125)

```text
// 0x54
```

## Source note 31, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L126)

```text
// 0x5C
```

## Source note 32, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L130)

```text
// Keep old name as alias for code that still references it
```

## Source note 33, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L141)

```text
// forward decl, defined in xevent.h
```

## Source note 34, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L160)

```text
// protects per-process TLS slot allocation bitmap
```

## Source note 35, line 161

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L161)

```text
// UsbdBootEnumerationDoneEvent uses X_DISPATCH_HEADER layout (0x10 bytes)
```

## Source note 36, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L174)

```text
/// Host-side metadata for a fiber managed by rexcrt hooks.
```

## Source note 37, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L176)

```text
///< Host OS fiber handle
```

## Source note 38, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L177)

```text
///< Unique identifier
```

## Source note 39, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L178)

```text
///< Guest fiber context buffer address
```

## Source note 40, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L179)

```text
///< Top of guest kernel stack (0 for thread fibers)
```

## Source note 41, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L180)

```text
///< Bottom of guest kernel stack (0 for thread fibers)
```

## Source note 42, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L181)

```text
///< true = ConvertThreadToFiber (don't free guest stack)
```

## Source note 43, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L197)

```text
/// The title update the running code was built for; 0 for the original.
```

## Source note 44, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L198)

```text
/// Only then are modules patched, from that update's update:\<name>p.
```

## Source note 45, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L208)

```text
// Access must be guarded by the global critical region.
```

## Source note 46, line 254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L254)

```text
// Recompiled module registry (populated by generated RegisterRecompiledModules)
```

## Source note 47, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L278)

```text
// Terminates a title: Unloads all modules, and kills all guest threads.
```

## Source note 48, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L279)

```text
// This DOES NOT RETURN if called from a guest thread!
```

## Source note 49, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L282)

```text
// Signaled while TerminateTitle runs, so sleeps nothing else can end (a
```

## Source note 50, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L283)

```text
// guest Sleep(INFINITE)) reach their termination point.
```

## Source note 51, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L296)

```text
/// Returns a fiber name for profiling
```

## Source note 52, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L337)

```text
// Returns the unlock FILETIME (100-ns intervals since 1601-01-01), or 0 if locked.
```

## Source note 53, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L368)

```text
// Must be guarded by the global critical region.
```

## Source note 54, line 374

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L374)

```text
// Protected by global_critical_region_.
```

## Source note 55, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L377)

```text
// Fiber name pool for profiling.
```

## Source note 56, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L378)

```text
// Never erased, Tracy references pointers async.
```

## Source note 57, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L386)

```text
// Paths in-flight in LoadUserModule. Guarded by the global critical region.
```

## Source note 58, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L391)

```text
// FreeLibrary deferred to teardown so guest threads still in unloaded code
```

## Source note 59, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L392)

```text
// don't return into freed pages. Drained at the end of ~KernelState.
```

## Source note 60, line 404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L404)

```text
// Must be guarded by the global critical region.
```

## Source note 61, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L412)

```text
// Global kernel state accessor (defined in kernel_state.cpp)
```

## Source note 62, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/kernel_state.h#L415)

```text
// Convenience accessor for kernel memory
```
