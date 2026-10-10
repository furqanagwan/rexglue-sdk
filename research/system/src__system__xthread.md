# Xthread: system source notes

This record preserves technical and API notes moved from `src/system/xthread.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L74)

```text
// top 8 bits = processor ID (or 0 for default)
```

## Source note 2, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L75)

```text
// bit 0 = 1 to create suspended
```

## Source note 3, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L79)

```text
// Adjust stack size - min of 16k.
```

## Source note 4, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L88)

```text
// The kernel does not take a reference. We must unregister in the dtor.
```

## Source note 5, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L98)

```text
// Unregister first to prevent lookups while deleting.
```

## Source note 6, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L143)

```text
// Unwind cleanly at this safe point. Does not return.
```

## Source note 7, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L181)

```text
// May be getting set before the thread is created.
```

## Source note 8, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L182)

```text
// One the thread is ready it will handle it.
```

## Source note 9, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L189)

```text
// NOTE: proc_mask is logical processors, not physical processors or cores.
```

## Source note 10, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L192)

```text
// is this reasonable?
```

## Source note 11, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L209)

```text
// Self-referencing pointers for wait timeout timer/block
```

## Source note 12, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L226)

```text
// Initialize APC lists (kernel + user mode)
```

## Source note 13, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L230)

```text
// Set process pointer - use guest_process if provided, else default to title process.
```

## Source note 14, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L237)

```text
// Set PRCB pointers (derived from this thread's PCR).
```

## Source note 15, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L242)

```text
// PPCContext for spinlock helpers (valid before thread runs; r13 set at construction).
```

## Source note 16, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L245)

```text
// Set per-thread process type and link into process thread list.
```

## Source note 17, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L262)

```text
// current_cpu is expected to be initialized externally via SetActiveCpu.
```

## Source note 18, line 266

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L266)

```text
// Initialize timer_list as self-referencing
```

## Source note 19, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L273)

```text
// Initialize unk_154 list as self-referencing
```

## Source note 20, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L286)

```text
// Guard page size * 2
```

## Source note 21, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L303)

```text
// Initialize the stack with junk
```

## Source note 22, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L306)

```text
// Setup the guard pages
```

## Source note 23, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L326)

```text
// Thread kernel object.
```

## Source note 24, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L332)

```text
// Allocate a stack.
```

## Source note 25, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L337)

```text
// Allocate thread scratch.
```

## Source note 26, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L338)

```text
// This is used by interrupts/APCs/etc so we can round-trip pointers through.
```

## Source note 27, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L342)

```text
// Allocate TLS block.
```

## Source note 28, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L343)

```text
// Games will specify a certain number of 4b slots that each thread will get.
```

## Source note 29, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L358)

```text
// Allocate both the slots and the extended data.
```

## Source note 30, line 359

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L359)

```text
// Some TLS is compiled with the binary (declspec(thread)) vars. The game
```

## Source note 31, line 360

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L360)

```text
// will directly access those through 0(r13).
```

## Source note 32, line 370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L370)

```text
// Zero all of TLS.
```

## Source note 33, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L373)

```text
// If game has extended data, copy in the default values.
```

## Source note 34, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L378)

```text
// Allocate thread state block from heap.
```

## Source note 35, line 379

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L379)

```text
// https://web.archive.org/web/20170704035330/https://www.microsoft.com/msj/archive/S2CE.aspx
```

## Source note 36, line 380

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L380)

```text
// This is set as r13 for user code and some special inlined Win32 calls
```

## Source note 37, line 381

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L381)

```text
// (like GetLastError/etc) will poke it directly.
```

## Source note 38, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L382)

```text
// We try to use it as our primary store of data just to keep things all
```

## Source note 39, line 383

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L383)

```text
// consistent.
```

## Source note 40, line 384

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L384)

```text
// 0x000: pointer to tls data
```

## Source note 41, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L385)

```text
// 0x100: pointer to TEB(?)
```

## Source note 42, line 386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L386)

```text
// 0x10C: Current CPU(?)
```

## Source note 43, line 387

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L387)

```text
// 0x150: if >0 then error states don't get set (DPC active bool?)
```

## Source note 44, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L389)

```text
// 0x14C: thread id
```

## Source note 45, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L390)

```text
// 0x160: last error
```

## Source note 46, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L391)

```text
// So, at offset 0x100 we have a 4b pointer to offset 200, then have the
```

## Source note 47, line 392

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L392)

```text
// structure.
```

## Source note 48, line 399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L399)

```text
// Create thread state - needed for interrupt callbacks and kernel exports
```

## Source note 49, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L408)

```text
// Initialize the KTHREAD object.
```

## Source note 50, line 425

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L425)

```text
// Always retain when starting - the thread owns itself until exited.
```

## Source note 51, line 429

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L429)

```text
// Allocate a big host stack.
```

## Source note 52, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L435)

```text
// Set thread ID override. This is used by logging.
```

## Source note 53, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L438)

```text
// Set name immediately, if we have one.
```

## Source note 54, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L444)

```text
// Execute user code.
```

## Source note 55, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L454)

```text
// Release the self-reference to the thread.
```

## Source note 56, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L463)

```text
// Set the thread name based on host ID (for easier debugging).
```

## Source note 57, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L472)

```text
// Assign the newly created thread to the logical processor, and also set up
```

## Source note 58, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L473)

```text
// the current CPU in KPCR and KTHREAD.
```

## Source note 59, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L477)

```text
// Start the thread now that we're all setup.
```

## Source note 60, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L485)

```text
// This may only be called on the thread itself.
```

## Source note 61, line 487

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L487)

```text
// Keep the object alive until Thread::Exit() transitions the host thread
```

## Source note 62, line 488

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L488)

```text
// into pthread_exit(). Otherwise ReleaseHandle() below may delete `this`
```

## Source note 63, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L489)

```text
// while this method is still running.
```

## Source note 64, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L492)

```text
// Mark as terminated before running down APCs.
```

## Source note 65, line 498

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L498)

```text
// Set exit code.
```

## Source note 66, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L503)

```text
// Unlink thread from process thread list.
```

## Source note 67, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L516)

```text
// The guest stack belongs to the thread's execution lifetime, not the handle
```

## Source note 68, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L517)

```text
// lifetime. Games can keep thread handles after exit; holding the stack until
```

## Source note 69, line 518

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L518)

```text
// object destruction leaks the reserved stack range and eventually makes
```

## Source note 70, line 519

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L519)

```text
// ExCreateThread fail even though the old threads are no longer running.
```

## Source note 71, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L522)

```text
// NOTE: unless PlatformExit fails, expect it to never return!
```

## Source note 72, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L529)

```text
// NOTE: this does not return!
```

## Source note 73, line 535

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L535)

```text
// Set exit code.
```

## Source note 74, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L542)

```text
// Same lifetime rule as Exit(): don't allow ReleaseHandle() to destroy
```

## Source note 75, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L543)

```text
// the thread object before Thread::Exit() reaches pthread_exit().
```

## Source note 76, line 561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L561)

```text
// Let the kernel know we are starting.
```

## Source note 77, line 564

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L564)

```text
// Dispatch any APCs that were queued before the thread was created first.
```

## Source note 78, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L572)

```text
// If a XapiThreadStartup value is present, we use that as a trampoline.
```

## Source note 79, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L573)

```text
// Otherwise, we are a raw thread.
```

## Source note 80, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L580)

```text
// Run user code.
```

## Source note 81, line 586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L586)

```text
// NOTE(tomc): JIT execution replaced with direct function calls
```

## Source note 82, line 587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L587)

```text
// In rexglue, guest code is compiled ahead of time and called directly.
```

## Source note 83, line 588

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L588)

```text
// The start_address points to a 32bit guest address, for which the function
```

## Source note 84, line 589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L589)

```text
// dispatcher maintains a lookup table to retrieve the host function pointer.
```

## Source note 85, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L607)

```text
// Pass arguments in r3, r4, ... per PPC calling convention
```

## Source note 86, line 627

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L627)

```text
// Convert this host thread to a fiber so SwitchTo works bidirectionally.
```

## Source note 87, line 628

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L628)

```text
// Required on Windows before any CreateFiber; provides the fallback handle
```

## Source note 88, line 629

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L629)

```text
// when another fiber switches back to the main execution context.
```

## Source note 89, line 632

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L632)

```text
// Execute the function
```

## Source note 90, line 638

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L638)

```text
// If we got here it means the execute completed without an exit being called.
```

## Source note 91, line 639

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L639)

```text
// Treat the return code as an implicit exit code (if desired).
```

## Source note 92, line 651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L651)

```text
// NOTE: intentionally not calling CheckApcs() here.
```

## Source note 93, line 652

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L652)

```text
// Delivering APCs here can cause them to fire in wrong contexts.
```

## Source note 94, line 669

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L669)

```text
// Match Edge/Canary behavior: callback is only a wakeup hint.
```

## Source note 95, line 670

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L670)

```text
// User APC execution happens on alertable wait return paths.
```

## Source note 96, line 686

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L686)

```text
/* user apc mode */
```

## Source note 97, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L688)

```text
// Important: use the caller PPC context when queuing to another thread.
```

## Source note 98, line 689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L689)

```text
// Using the target thread context here can corrupt APC lock/IRQL bookkeeping.
```

## Source note 99, line 701

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L701)

```text
// Match Edge/Canary behavior: callback is only a wakeup hint.
```

## Source note 100, line 702

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L702)

```text
// APCs are delivered via alertable wait handling.
```

## Source note 101, line 780

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L780)

```text
// Rundown both user (1) and kernel (0) APC lists.
```

## Source note 102, line 796

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L796)

```text
// No-op.
```

## Source note 103, line 826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L826)

```text
// Write priority to guest X_KTHREAD struct.
```

## Source note 104, line 852

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L852)

```text
// Prefer reading from guest KTHREAD (always available for guest threads,
```

## Source note 105, line 853

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L853)

```text
// kept in sync by SetActiveCpu). Avoids dependency on pcr_address_ which
```

## Source note 106, line 854

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L854)

```text
// may not be set yet if the thread is mid-creation.
```

## Source note 107, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L867)

```text
// May be called during thread creation - don't skip if current == new.
```

## Source note 108, line 871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L871)

```text
// Write to guest KTHREAD (always available for guest threads).
```

## Source note 109, line 877

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L877)

```text
// Write to PCR if allocated (may not be during early creation).
```

## Source note 110, line 937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L937)

```text
// Wrapped to 0 - treat as not suspended.
```

## Source note 111, line 955

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L955)

```text
// An absolute time that already passed: a zero delay, below.
```

## Source note 112, line 987

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L987)

```text
// Is this the main thread?
```

## Source note 113, line 995

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L995)

```text
// High address
```

## Source note 114, line 996

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L996)

```text
// Low address
```

## Source note 115, line 997

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L997)

```text
// Allocation address
```

## Source note 116, line 998

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L998)

```text
// Allocation size
```

## Source note 117, line 1000

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1000)

```text
// Context (invalid if not running)
```

## Source note 118, line 1019

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1019)

```text
// Save PPCContext to ThreadSavedState
```

## Source note 119, line 1024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1024)

```text
// GPRs - copy individually since PPCContext uses named registers
```

## Source note 120, line 1039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1039)

```text
// r14-r31: contiguous in PPCContext and state array
```

## Source note 121, line 1057

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1057)

```text
// f14-f31: contiguous in PPCContext and state array
```

## Source note 122, line 1060

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1060)

```text
// VRs (v0-v127)
```

## Source note 123, line 1075

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1075)

```text
// v14-v31: contiguous in PPCContext and state array
```

## Source note 124, line 1109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1109)

```text
// v64-v127: contiguous in PPCContext and state array
```

## Source note 125, line 1112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1112)

```text
// CR fields
```

## Source note 126, line 1122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1122)

```text
// Other state
```

## Source note 127, line 1132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1132)

```text
// Load ThreadSavedState into PPCContext
```

## Source note 128, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1152)

```text
// r14-r31: contiguous in PPCContext and state array
```

## Source note 129, line 1170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1170)

```text
// f14-f31: contiguous in PPCContext and state array
```

## Source note 130, line 1173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1173)

```text
// VRs (v0-v127)
```

## Source note 131, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1188)

```text
// v14-v31: contiguous in PPCContext and state array
```

## Source note 132, line 1222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1222)

```text
// v64-v127: contiguous in PPCContext and state array
```

## Source note 133, line 1225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1225)

```text
// CR fields
```

## Source note 134, line 1235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1235)

```text
// Other state
```

## Source note 135, line 1247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1247)

```text
// Host XThreads are expected to be recreated on their own.
```

## Source note 136, line 1270

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1270)

```text
// APCs now live in guest-memory typed lists
```

## Source note 137, line 1291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1291)

```text
// Kind-of a hack, but we need to set the kernel state outside of the object
```

## Source note 138, line 1292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1292)

```text
// constructor so it doesn't register a handle with the object table.
```

## Source note 139, line 1314

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1314)

```text
// state.apc_head is ignored - APCs live in guest-memory typed lists
```

## Source note 140, line 1324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1324)

```text
// Register now that we know our thread ID.
```

## Source note 141, line 1327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1327)

```text
// Create thread state
```

## Source note 142, line 1335

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1335)

```text
// Always retain when starting - the thread owns itself until exited.
```

## Source note 143, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1339)

```text
// Not done restoring yet.
```

## Source note 144, line 1342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1342)

```text
// Set thread ID override. This is used by logging.
```

## Source note 145, line 1346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1346)

```text
// Set name immediately, if we have one.
```

## Source note 146, line 1353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1353)

```text
// Acquire any mutants
```

## Source note 147, line 1361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1361)

```text
// Execute user code.
```

## Source note 148, line 1371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1371)

```text
// Release the self-reference to the thread.
```

## Source note 149, line 1376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1376)

```text
// NOTE(tomc): if this is kept and processor notification dispatch is implemented,
```

## Source note 150, line 1377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1377)

```text
//             this needs to send a signal to the processor that a thread was started
```

## Source note 151, line 1386

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1386)

```text
// NOTE(tomc): there was a start suspended check here before but I don't think we need it.
```

## Source note 152, line 1393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1393)

```text
// Let the kernel know we are starting.
```

## Source note 153, line 1398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xthread.cpp#L1398)

```text
// Exit.
```
