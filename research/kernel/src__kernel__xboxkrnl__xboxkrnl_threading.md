# Xboxkrnl threading: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_threading.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L46)

```text
// r13 + 0x100: pointer to thread local state
```

## Source note 3, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L47)

```text
// Thread local state:
```

## Source note 4, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L48)

```text
//   0x058: kernel time
```

## Source note 5, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L49)

```text
//   0x14C: thread id
```

## Source note 6, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L50)

```text
//   0x150: if >0 then error states don't get set
```

## Source note 7, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L51)

```text
//   0x160: last error
```

## Source note 8, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L54)

```text
// lwz       r11, 0x100(r13)
```

## Source note 9, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L55)

```text
// lwz       r3, 0x14C(r11)
```

## Source note 10, line 58

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L58)

```text
// lwz r11, 0x150(r13)
```

## Source note 11, line 59

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L59)

```text
// if (r11 == 0) {
```

## Source note 12, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L60)

```text
//   lwz r11, 0x100(r13)
```

## Source note 13, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L61)

```text
//   stw r3, 0x160(r11)
```

## Source note 14, line 65

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L65)

```text
// lwz r11, 0x150(r13)
```

## Source note 15, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L66)

```text
// if (r11 == 0) {
```

## Source note 16, line 67

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L67)

```text
//   lwz r11, 0x100(r13)
```

## Source note 17, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L68)

```text
//   stw r3, 0x160(r11)
```

## Source note 18, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L72)

```text
// r3 = RtlNtStatusToDosError(r3)
```

## Source note 19, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L73)

```text
// lwz r11, 0x150(r13)
```

## Source note 20, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L74)

```text
// if (r11 == 0) {
```

## Source note 21, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L75)

```text
//   lwz r11, 0x100(r13)
```

## Source note 22, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L76)

```text
//   stw r3, 0x160(r11)
```

## Source note 23, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L81)

```text
// If the name exists and its type matches, we can return that (ref+1)
```

## Source note 24, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L82)

```text
// with a success of NAME_EXISTS.
```

## Source note 25, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L83)

```text
// If the name exists and its type doesn't match, we do NAME_COLLISION.
```

## Source note 26, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L84)

```text
// Otherwise, we add like normal.
```

## Source note 27, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L96)

```text
// Found something! It's been retained, so return.
```

## Source note 28, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L99)

```text
// The caller will do as it likes.
```

## Source note 29, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L115)

```text
// http://jafile.com/uploads/scoop/main.cpp.txt
```

## Source note 30, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L117)

```text
// LPHANDLE Handle,
```

## Source note 31, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L118)

```text
// DWORD    StackSize,
```

## Source note 32, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L119)

```text
// LPDWORD  ThreadId,
```

## Source note 33, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L120)

```text
// LPVOID   XapiThreadStartup, ?? often 0
```

## Source note 34, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L121)

```text
// LPVOID   StartAddress,
```

## Source note 35, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L122)

```text
// LPVOID   StartContext,
```

## Source note 36, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L123)

```text
// DWORD    CreationFlags // 0x80?
```

## Source note 37, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L125)

```text
// Determine target process based on creation flags.
```

## Source note 38, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L132)

```text
// Inherit default stack size
```

## Source note 39, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L139)

```text
// Stack must be aligned to 16kb pages
```

## Source note 40, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L148)

```text
// Failed!
```

## Source note 41, line 174

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L174)

```text
// NOTE: this kills us right now. We won't return from it.
```

## Source note 42, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L274)

```text
// The Xbox 360, according to disassembly of KeSetAffinityThread, unlike
```

## Source note 43, line 275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L275)

```text
// Windows NT, stores the previous affinity via the pointer provided as an
```

## Source note 44, line 276

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L276)

```text
// argument, not in the return value - the return value is used for the
```

## Source note 45, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L277)

```text
// result.
```

## Source note 46, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L344)

```text
// One of X_PROCTYPE_?
```

## Source note 47, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L392)

```text
// https://msdn.microsoft.com/en-us/library/ms686801
```

## Source note 48, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L402)

```text
// https://msdn.microsoft.com/en-us/library/ms686804
```

## Source note 49, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L415)

```text
// https://msdn.microsoft.com/en-us/library/ms686812
```

## Source note 50, line 417

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L417)

```text
// xboxkrnl doesn't actually have an error branch - it always succeeds, even
```

## Source note 51, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L418)

```text
// if it overflows the TLS.
```

## Source note 52, line 427

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L427)

```text
// https://msdn.microsoft.com/en-us/library/ms686818
```

## Source note 53, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L431)

```text
// xboxkrnl doesn't actually have an error branch - it always succeeds, even
```

## Source note 54, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L432)

```text
// if it overflows the TLS.
```

## Source note 55, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L489)

```text
// Check for an existing timer with the same name.
```

## Source note 56, line 507

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L507)

```text
// obj_attributes may have a name inside of it, if != NULL.
```

## Source note 57, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L571)

```text
// https://msdn.microsoft.com/en-us/library/windows/hardware/ff552150(v=vs.85).aspx
```

## Source note 58, line 578

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L578)

```text
/* SemaphoreObject */
```

## Source note 59, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L606)

```text
// Check for an existing semaphore with the same name.
```

## Source note 60, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L630)

```text
// obj_attributes may have a name inside of it, if != NULL.
```

## Source note 61, line 664

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L664)

```text
// Check for an existing timer with the same name.
```

## Source note 62, line 682

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L682)

```text
// obj_attributes may have a name inside of it, if != NULL.
```

## Source note 63, line 695

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L695)

```text
// This doesn't seem to be supported.
```

## Source note 64, line 696

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L696)

```text
// int32_t previous_count_ptr = SHIM_GET_ARG_32(2);
```

## Source note 65, line 698

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L698)

```text
// Whatever arg 1 is all games seem to set it to 0, so whether it's
```

## Source note 66, line 699

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L699)

```text
// abandon or wait we just say false. Which is good, cause they are
```

## Source note 67, line 700

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L700)

```text
// both ignored.
```

## Source note 68, line 719

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L719)

```text
// timer_type = NotificationTimer (0) or SynchronizationTimer (1)
```

## Source note 69, line 721

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L721)

```text
// Check for an existing timer with the same name.
```

## Source note 70, line 739

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L739)

```text
// obj_attributes may have a name inside of it, if != NULL.
```

## Source note 71, line 754

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L754)

```text
// Other fields are unmodified; they must carry through multiple calls.
```

## Source note 72, line 759

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L759)

```text
// Initialize wait list to point to itself (empty list).
```

## Source note 73, line 769

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L769)

```text
/*PTIMERAPCROUTINE*/
```

## Source note 74, line 810

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L810)

```text
// The only kind-of failure code (though this should never happen)
```

## Source note 75, line 827

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L827)

```text
// REXKRNL_IMPORT_TRACE("KeWaitForSingleObject", "obj={:#x} reason={} mode={} alertable={}
```

## Source note 76, line 828

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L828)

```text
// timeout={}",
```

## Source note 77, line 829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L829)

```text
// object_ptr.guest_address(), (uint32_t)wait_reason,
```

## Source note 78, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L830)

```text
//(uint32_t)processor_mode, (uint32_t)alertable,
```

## Source note 79, line 831

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L831)

```text
// timeout_ptr ? (int64_t)timeout : -1);
```

## Source note 80, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L834)

```text
// REXKRNL_IMPORT_RESULT("KeWaitForSingleObject", "{:#x}", result);
```

## Source note 81, line 933

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L933)

```text
// Guest-memory IRQL helpers - read/write current_irql directly from PCR.
```

## Source note 82, line 934

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L934)

```text
// Take PPCContext* explicitly so they work from any thread (including host threads
```

## Source note 83, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L935)

```text
// during InitializeGuestObject, dispatch thread creation, etc.).
```

## Source note 84, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L950)

```text
// Guest-memory spinlock helpers - store PCR address as owner (matching xenia).
```

## Source note 85, line 951

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L951)

```text
// PPCContext* provides r13 (PCR address) without needing XThread::GetCurrentThread().
```

## Source note 86, line 956

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L956)

```text
// self-deadlock detection
```

## Source note 87, line 972

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L972)

```text
// Guest-memory APC helpers
```

## Source note 88, line 1012

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1012)

```text
// Kernel-mode APCs without normal_routine go before those with one.
```

## Source note 89, line 1107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1107)

```text
/* user apc mode */
```

## Source note 90, line 1115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1115)

```text
// Match Edge/Canary behavior: callback is only a wakeup hint.
```

## Source note 91, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1116)

```text
// APC delivery happens via alertable wait handling.
```

## Source note 92, line 1155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1155)

```text
/* output? */
```

## Source note 93, line 1155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1155)

```text
/* 0x13 */
```

## Source note 94, line 1168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1168)

```text
// Lock dispatcher.
```

## Source note 95, line 1172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1172)

```text
// If already in a queue, abort.
```

## Source note 96, line 1177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1177)

```text
// Prep DPC.
```

## Source note 97, line 1201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1201)

```text
// https://github.com/Cxbx-Reloaded/Cxbx-Reloaded/blob/51e4dfcaacfdbd1a9692272931a436371492f72d/import/OpenXDK/include/xboxkrnl/xboxkrnl.h#L1372
```

## Source note 98, line 1203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1203)

```text
// 0x0
```

## Source note 99, line 1204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1204)

```text
// 0x4
```

## Source note 100, line 1205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1205)

```text
// 0x8
```

## Source note 101, line 1206

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1206)

```text
// 0xC
```

## Source note 102, line 1207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1207)

```text
// 0x10
```

## Source note 103, line 1208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1208)

```text
// 0x20
```

## Source note 104, line 1209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1209)

```text
// 0x34
```

## Source note 105, line 1218

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1218)

```text
// Create GuestPointers to struct members with correct guest addresses
```

## Source note 106, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1329)

```text
// NOTE: This function is very commonly inlined, and probably won't be called!
```

## Source note 107, line 1519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_threading.cpp#L1519)

```text
// REX_EXPORT_STUB(__imp__KeInitializeTimerEx); -- implemented below
```
