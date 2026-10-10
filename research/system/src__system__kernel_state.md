# Kernel state: system source notes

This record preserves technical and API notes moved from `src/system/kernel_state.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L52)

```text
// This is a global object initialized with the XboxkrnlModule.
```

## Source note 2, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L53)

```text
// It references the current kernel state object that all kernel methods should
```

## Source note 3, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L54)

```text
// be using to stash their variables.
```

## Source note 4, line 85

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L85)

```text
// Allocate KernelGuestGlobals early so xboxkrnl module can wire exports.
```

## Source note 5, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L90)

```text
// Initialize object type pool tags
```

## Source note 6, line 102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L102)

```text
// Initialize UsbdBootEnumerationDoneEvent as a signaled manual-reset event
```

## Source note 7, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L107)

```text
// Initialize OddObj self-referencing pointer
```

## Source note 8, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L115)

```text
// Initialize process structs
```

## Source note 9, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L122)

```text
// Title process needs minimal initialization here so threads created before
```

## Source note 10, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L123)

```text
// SetExecutableModule() (e.g. XMA decoder) can link into its thread_list.
```

## Source note 11, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L124)

```text
// SetExecutableModule() will re-initialize it fully with XEX header values.
```

## Source note 12, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L150)

```text
// Initialize TLS bitmap - mark used slots with 1s in HIGH bits (matching xenia).
```

## Source note 13, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L151)

```text
// Xenia formula: bitmap[count_div32] = -1 << (32 - ((num_slots + 3) & 0x1C))
```

## Source note 14, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L168)

```text
// Stop the dispatch thread before touching the object table
```

## Source note 15, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L175)

```text
// Unload through UnloadUserModule so the recompiled-DLL teardown runs.
```

## Source note 16, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L176)

```text
// call_entry=false because guest DllMain is unsafe at shutdown.
```

## Source note 17, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L179)

```text
/*call_entry=*/
```

## Source note 18, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L189)

```text
// Unregister all notify listeners.
```

## Source note 19, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L192)

```text
// Safe to reset now: Runtime::Shutdown() has already stopped graphics,
```

## Source note 20, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L193)

```text
// audio, and input before destroying KernelState.
```

## Source note 21, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L196)

```text
// Destroy any host fibers that were not explicitly cleaned up.
```

## Source note 22, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L221)

```text
// Drain last: FreeLibrary runs the DLL's host static dtors.
```

## Source note 23, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L230)

```text
// No title loaded yet (or a tool/test runtime without an image).
```

## Source note 24, line 312

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L312)

```text
// Set up the unlock save path and restore persisted state.
```

## Source note 25, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L467)

```text
// Already loaded.
```

## Source note 26, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L489)

```text
// Executing module isn't a kernel module.
```

## Source note 27, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L492)

```text
// NOTE: no global lock required as the kernel module list is static.
```

## Source note 28, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L515)

```text
// NULL name = self.
```

## Source note 29, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L519)

```text
// Some games request this, for some reason. wtf.
```

## Source note 30, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L523)

```text
// Search kernel modules under lock
```

## Source note 31, line 533

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L533)

```text
// Resolve path WITHOUT lock
```

## Source note 32, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L540)

```text
// Search user modules under lock
```

## Source note 33, line 560

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L560)

```text
// Create a thread to run in.
```

## Source note 34, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L561)

```text
// We start suspended so the caller can inspect/attach before resume.
```

## Source note 35, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L565)

```text
// We know this is the 'main thread'.
```

## Source note 36, line 601

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L601)

```text
// Update title process fields from the executable module.
```

## Source note 37, line 602

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L602)

```text
// Do NOT call InitializeProcess() again - it was already called in the
```

## Source note 38, line 603

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L603)

```text
// constructor, and threads (XMA decoder, dispatch) may already be linked
```

## Source note 39, line 604

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L604)

```text
// into the thread_list. Reinitializing would orphan them.
```

## Source note 40, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L611)

```text
// Read default stack size from XEX header, align to 4KB, clamp to min 16KB.
```

## Source note 41, line 622

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L622)

```text
// Update title process TLS info from the executable module.
```

## Source note 42, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L632)

```text
// Setup the kernel's XexExecutableModuleHandle field.
```

## Source note 43, line 634

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L634)

```text
/* XexExecutableModuleHandle */
```

## Source note 44, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L641)

```text
// Setup the kernel's ExLoadedImageName field
```

## Source note 45, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L643)

```text
/* ExLoadedImageName */
```

## Source note 46, line 649

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L649)

```text
// Spin up deferred dispatch worker.
```

## Source note 47, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L670)

```text
// Throws out of fn leave the originating overlapped uncompleted and
```

## Source note 48, line 671

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L671)

```text
// the waiting guest thread stuck; fail visibly rather than swallow.
```

## Source note 49, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L702)

```text
// Some games try to load relative to launch module, others specify full path.
```

## Source note 50, line 711

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L711)

```text
// loading_paths_ serializes concurrent loaders of the same path; we
```

## Source note 51, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L712)

```text
// can't hold the global lock across LoadFromFile or DllMain ATTACH.
```

## Source note 52, line 747

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L747)

```text
// Wire recompiled code (if any) before publishing to user_modules_, so a
```

## Source note 53, line 748

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L748)

```text
// failure in this block leaves no half-loaded entry behind.
```

## Source note 54, line 793

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L793)

```text
/*is_entrypoint=*/
```

## Source note 55, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L826)

```text
/* DLL_PROCESS_ATTACH */
```

## Source note 56, line 832

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L832)

```text
// call_entry=false: the guest already declined ATTACH, so don't run DETACH.
```

## Source note 57, line 833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L833)

```text
/*call_entry=*/
```

## Source note 58, line 843

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L843)

```text
// Run guest DllMain DETACH outside the global lock to avoid deadlock with
```

## Source note 59, line 844

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L844)

```text
// subsystem mutexes acquired from inside the guest callback.
```

## Source note 60, line 851

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L851)

```text
/* DLL_PROCESS_DETACH */
```

## Source note 61, line 926

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L926)

```text
// A module loaded by a bare name is joined to the executable's own path,
```

## Source note 62, line 927

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L927)

```text
// the game partition's device path (\Device\Harddisk0\Partition1\...),
```

## Source note 63, line 928

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L928)

```text
// which keeps its device in the key; registered paths are relative to the
```

## Source note 64, line 929

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L929)

```text
// game root, so they match as the key's trailing segments.
```

## Source note 65, line 949

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L949)

```text
// ReleaseMutant reads the current thread; skip on non-kernel threads
```

## Source note 66, line 950

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L950)

```text
// (host UI shutdown), where GetCurrentThread asserts.
```

## Source note 67, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L997)

```text
// Guest threads poll this flag in the kernel wait primitives
```

## Source note 68, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L998)

```text
// (XThread::CheckTitleTermination) and self-exit.
```

## Source note 69, line 1002

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1002)

```text
// Retained so a thread that wakes and exits below can't be freed mid-drain.
```

## Source note 70, line 1013

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1013)

```text
// Wake blocked waiters: signal objects (non-alertable waiters) and a bare user
```

## Source note 71, line 1014

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1014)

```text
// callback per target (alertable waits/delays).
```

## Source note 72, line 1022

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1022)

```text
// Stragglers are deliberately left running, never force-killed: TerminateThread
```

## Source note 73, line 1023

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1023)

```text
// orphans whatever host lock the thread holds (CRT heap, mutexes) and deadlocks
```

## Source note 74, line 1024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1024)

```text
// teardown. Window close hard-exits and lets the OS reap them.
```

## Source note 75, line 1026

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1026)

```text
// Drop guest threads from the map.
```

## Source note 76, line 1038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1038)

```text
// Drop refs before the self-terminate below (which does not return) so they
```

## Source note 77, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1039)

```text
// aren't leaked; reset the flag for relaunch.
```

## Source note 78, line 1044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1044)

```text
// Self-terminate if called from a guest thread (e.g. XamLoaderTerminateTitle).
```

## Source note 79, line 1058

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1058)

```text
// Thread count is now managed via thread-process linking in
```

## Source note 80, line 1059

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1059)

```text
// XThread::InitializeGuestObject and XThread::Exit.
```

## Source note 81, line 1073

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1073)

```text
// Must be called on executing thread.
```

## Source note 82, line 1082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1082)

```text
// Must be called on executing thread.
```

## Source note 83, line 1102

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1102)

```text
// Games seem to expect a few notifications on startup, only for the first
```

## Source note 84, line 1103

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1103)

```text
// listener.
```

## Source note 85, line 1104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1104)

```text
// https://cs.rin.ru/forum/viewtopic.php?f=38&t=60668&hilit=resident+evil+5&start=375
```

## Source note 86, line 1107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1107)

```text
// XN_SYS_UI (on, off)
```

## Source note 87, line 1110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1110)

```text
// XN_SYS_SIGNINCHANGED x2
```

## Source note 88, line 1113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1113)

```text
// XN_SYS_INPUTDEVICESCHANGED x2
```

## Source note 89, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1116)

```text
// XN_SYS_INPUTDEVICECONFIGCHANGED x2
```

## Source note 90, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1152)

```text
// Result last, so a caller polling it for completion reads a valid length.
```

## Source note 91, line 1169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1169)

```text
// Queue APC on the thread that requested the overlapped operation.
```

## Source note 92, line 1280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1280)

```text
// Save the object table
```

## Source note 93, line 1283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1283)

```text
// Legacy save-state field (global TLS bitmap) no longer used.
```

## Source note 94, line 1286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1286)

```text
// We save XThreads absolutely first, as they will execute code upon save
```

## Source note 95, line 1287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1287)

```text
// (which could modify the kernel state)
```

## Source note 96, line 1296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1296)

```text
// Don't save host threads. They can be reconstructed on startup.
```

## Source note 97, line 1309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1309)

```text
// Save all other objects
```

## Source note 98, line 1320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1320)

```text
// Don't save host objects or save XThreads again
```

## Source note 99, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1330)

```text
// Revert backwards and overwrite if a save failed.
```

## Source note 100, line 1341

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1341)

```text
// Check the magic value.
```

## Source note 101, line 1346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1346)

```text
// Restore the object table
```

## Source note 102, line 1349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1349)

```text
// Global TLS bitmap field is kept for old save-state compatibility.
```

## Source note 103, line 1360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1360)

```text
// Can't continue the restore or we risk misalignment.
```

## Source note 104, line 1373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/kernel_state.cpp#L1373)

```text
// Can't continue the restore or we risk misalignment.
```
