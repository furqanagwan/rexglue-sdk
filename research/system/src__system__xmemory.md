# Xmemory: system source notes

This record preserves technical and API notes moved from `src/system/xmemory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L45)

```text
/**
 * Memory map:
 * 0x00000000 - 0x3FFFFFFF (1024mb) - virtual 4k pages
 * 0x40000000 - 0x7FFFFFFF (1024mb) - virtual 64k pages
 * 0x80000000 - 0x8BFFFFFF ( 192mb) - xex 64k pages
 * 0x8C000000 - 0x8FFFFFFF (  64mb) - xex 64k pages (encrypted)
 * 0x90000000 - 0x9FFFFFFF ( 256mb) - xex 4k pages
 * 0xA0000000 - 0xBFFFFFFF ( 512mb) - physical 64k pages
 * 0xC0000000 - 0xDFFFFFFF          - physical 16mb pages
 * 0xE0000000 - 0xFFFFFFFF          - physical 4k pages
 *
 * We use the host OS to create an entire addressable range for this. That way
 * we don't have to emulate a TLB. It'd be really cool to pass through page
 * sizes or use madvice to let the OS know what to expect.
 *
 * We create our own heap of committed memory that lives at
 * memory_HEAP_LOW to memory_HEAP_HIGH - all normal user allocations
 * come from there. Since the Xbox has no paging, we know that the size of
 * this heap will never need to be larger than ~512MB (realistically, smaller
 * than that). We place it far away from the XEX data and keep the memory
 * around it uncommitted so that we have some warning if things go astray.
 *
 * For XEX/GPU/etc data we allow placement allocations (base_address != 0) and
 * commit the requested memory as needed. This bypasses the standard heap, but
 * XEXs should never be overwriting anything so that's fine. We can also query
 * for previous commits and assert that we really isn't committing twice.
 *
 * GPU memory is mapped onto the lower 512mb of the virtual 4k range (0).
 * So 0xA0000000 = 0x00000000. A more sophisticated allocator could handle
 * this.
 */
```

## Source note 2, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L82)

```text
// rex::FatalError(
```

## Source note 3, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L83)

```text
//     "Hard crash: the memory system crashed while dumping a crash dump.");
```

## Source note 4, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L101)

```text
// Uninstall the MMIO handler, as we won't be able to service more requests.
```

## Source note 5, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L117)

```text
// Unmap all views and close mapping.
```

## Source note 6, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L132)

```text
// Create main page file-backed mapping. This is all reserved but
```

## Source note 7, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L133)

```text
// uncommitted (so it shouldn't expand page file).
```

## Source note 8, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L134)

```text
// Round up to allocation granularity to accommodate platforms with large pages.
```

## Source note 9, line 146

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L146)

```text
// Attempt to create our views. This may fail at the first address
```

## Source note 10, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L147)

```text
// we pick, so try a few times.
```

## Source note 11, line 168

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L168)

```text
// Prepare virtual heaps.
```

## Source note 12, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L178)

```text
// Prepare physical heaps.
```

## Source note 13, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L188)

```text
// Protect the first and last 64kb of memory.
```

## Source note 14, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L197)

```text
// GPU writeback.
```

## Source note 15, line 198

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L198)

```text
// 0xC... is physical, 0x7F... is virtual. We may need to overlay these.
```

## Source note 16, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L203)

```text
// Pre-commit the physical memory range so the GPU can access it
```

## Source note 17, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L204)

```text
// without page faults. Reference: xenia-canary 5f5be0668.
```

## Source note 18, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L209)

```text
// Install MMIO handler for physical address translation and MMIO ranges
```

## Source note 19, line 225

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L225)

```text
// Allocate region at start of XEX range. Title 544307D5 explicitly
```

## Source note 20, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L226)

```text
// accesses 0x8000001C and expects a specific constant value.
```

## Source note 21, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L227)

```text
// Reference: xenia-canary 78f97f8ff.
```

## Source note 22, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L244)

```text
// (1024mb) - virtual 4k pages
```

## Source note 23, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L250)

```text
// (1024mb) - virtual 64k pages (cont)
```

## Source note 24, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L256)

```text
//   (16mb) - GPU writeback + 15mb of XPS?
```

## Source note 25, line 262

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L262)

```text
//  (256mb) - xex 64k pages
```

## Source note 26, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L268)

```text
//  (256mb) - xex 4k pages
```

## Source note 27, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L274)

```text
//  (512mb) - physical 64k pages
```

## Source note 28, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L280)

```text
//          - physical 16mb pages
```

## Source note 29, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L286)

```text
//          - physical 4k pages
```

## Source note 30, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L292)

```text
//          - physical raw
```

## Source note 31, line 302

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L302)

```text
// 0xE0000000 4 KB offset is emulated via host_address_offset and on the CPU
```

## Source note 32, line 303

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L303)

```text
// side if system allocation granularity is bigger than 4 KB.
```

## Source note 33, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L311)

```text
// Failed, so bail and try again.
```

## Source note 34, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L445)

```text
// AllocFixed rejects requests that don't cover whole host pages, so that a
```

## Source note 35, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L446)

```text
// guest heap can never widen an mprotect over a neighbouring guest page that
```

## Source note 36, line 447

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L447)

```text
// shares the host page. An MMIO window has no such neighbours - it owns its
```

## Source note 37, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L448)

```text
// entire range - so rounding out to host page bounds is safe here, and it is
```

## Source note 38, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L449)

```text
// required because callers describe these windows with mask-style sizes such
```

## Source note 39, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L450)

```text
// as 0xFFFF, which is one byte short of 64 KB and therefore never a multiple
```

## Source note 40, line 451

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L451)

```text
// of the 16 KB host page on Apple Silicon.
```

## Source note 41, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L463)

```text
// The MMIO registration keeps the caller's original size - only the host
```

## Source note 42, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L464)

```text
// reservation is rounded.
```

## Source note 43, line 475

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L475)

```text
// Access via physical_membase_ is special, when need to bypass everything
```

## Source note 44, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L476)

```text
// (for instance, for a data provider to actually write the data) so only
```

## Source note 45, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L477)

```text
// triggering callbacks on virtual memory regions.
```

## Source note 46, line 492

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L492)

```text
// Access violation callbacks from the guest are triggered when the global
```

## Source note 47, line 493

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L493)

```text
// critical region mutex is locked once.
```

## Source note 48, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L495)

```text
// Will be rounded to physical page boundaries internally, so just pass 1 as
```

## Source note 49, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L496)

```text
// the length - guranteed not to cross page boundaries also.
```

## Source note 50, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L503)

```text
// Recovery path for stale host protection state in physical memory:
```

## Source note 51, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L504)

```text
// if guest metadata says the page is writable but host protection is still
```

## Source note 52, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L505)

```text
// read-only / no-access, restore write access and resume execution.
```

## Source note 53, line 515

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L515)

```text
// If write-watch left current protect stale, trust committed allocation
```

## Source note 54, line 516

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L516)

```text
// metadata first for this alias.
```

## Source note 55, line 524

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L524)

```text
// Alias-aware fallback: consult canonical 0x00000000 physical heap
```

## Source note 56, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L525)

```text
// metadata when this alias has stale tracking.
```

## Source note 57, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L657)

```text
// Heap array is fixed after init; page counts are approximate statistics.
```

## Source note 58, line 722

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L722)

```text
// Recompiled Code Function Table
```

## Source note 59, line 830

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L830)

```text
// Guest memory cannot be executable - this should never happen :)
```

## Source note 60, line 834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L834)

```text
// Guest memory cannot be executable - this should never happen :)
```

## Source note 61, line 859

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L859)

```text
// The global critical region guards the watch flags read below and must
```

## Source note 62, line 860

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L860)

```text
// already be held by the caller (AcquireHostPageReconcileLock), acquired
```

## Source note 63, line 861

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L861)

```text
// ahead of heap_mutex_ so this never inverts against PhysicalHeap.
```

## Source note 64, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L863)

```text
// Multiple guest pages may share one host page. Keep the guest page table as
```

## Source note 65, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L864)

```text
// the source of truth, then grant the host page the union of the access needed
```

## Source note 66, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L865)

```text
// by its committed guest pages. This can't enforce stricter access for one
```

## Source note 67, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L866)

```text
// guest page while a neighbor needs broader access, but it keeps neighboring
```

## Source note 68, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L867)

```text
// committed pages usable and allows guest protection metadata to stay exact.
```

## Source note 69, line 903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L903)

```text
// Physical aliases are intentionally left accessible after release unless
```

## Source note 70, line 904

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L904)

```text
// protect_on_release is enabled because GPU users may still reference them.
```

## Source note 71, line 914

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L914)

```text
// The guest page table is not the whole truth: a physical heap page may
```

## Source note 72, line 915

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L915)

```text
// also be write-watched for GPU invalidation. EnableAccessCallbacks records
```

## Source note 73, line 916

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L916)

```text
// that in notify_on_invalidation and skips any page whose bit is already
```

## Source note 74, line 917

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L917)

```text
// set, so handing write access back here would stop the watch firing
```

## Source note 75, line 918

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L918)

```text
// permanently. One host page covers several guest pages, so an unrelated
```

## Source note 76, line 919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L919)

```text
// operation on a neighbour reaches this code constantly - clamp instead.
```

## Source note 77, line 920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L920)

```text
// Leaving the page read-only can only cause a spurious invalidation, which
```

## Source note 78, line 921

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L921)

```text
// is safe; restoring write access loses invalidations, which is not.
```

## Source note 79, line 935

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L935)

```text
// Coalesce neighbouring host pages that resolve to the same access into one
```

## Source note 80, line 936

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L936)

```text
// Protect call. A bulk commit spans thousands of host pages and almost always
```

## Source note 81, line 937

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L937)

```text
// wants a single uniform access for all of them, so protecting page by page
```

## Source note 82, line 938

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L938)

```text
// would cost thousands of syscalls where one suffices.
```

## Source note 83, line 984

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L984)

```text
// Walk table and release all regions.
```

## Source note 84, line 1082

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1082)

```text
// Unallocated.
```

## Source note 85, line 1108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1108)

```text
// Restore doesn't take heap_mutex_, but SyncHostPageAccess below still needs
```

## Source note 86, line 1109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1109)

```text
// the global critical region held by its caller.
```

## Source note 87, line 1116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1116)

```text
// Unallocated.
```

## Source note 88, line 1134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1134)

```text
// Commit the memory if it isn't already. We do not need to reserve any
```

## Source note 89, line 1135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1135)

```text
// memory, as the mapping has already taken care of that.
```

## Source note 90, line 1138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1138)

```text
// Read into memory with R/W protection, then restore the saved
```

## Source note 91, line 1139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1139)

```text
// protection.
```

## Source note 92, line 1147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1147)

```text
// Guest pages are smaller than host pages, so a per-guest-page commit is
```

## Source note 93, line 1148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1148)

```text
// rejected and a per-guest-page protect is misaligned - either way the
```

## Source note 94, line 1149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1149)

```text
// target would never become writable and the read below would fault or be
```

## Source note 95, line 1150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1150)

```text
// silently lost. Make the containing host page writable once instead;
```

## Source note 96, line 1151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1151)

```text
// guest pages are visited in ascending order, so one commit covers the
```

## Source note 97, line 1152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1152)

```text
// whole run that shares a host page. Real protections are reconciled from
```

## Source note 98, line 1153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1153)

```text
// the restored page table after the loop.
```

## Source note 99, line 1188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1188)

```text
// Reserve address space at the top for thread stacks.
```

## Source note 100, line 1189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1189)

```text
// 0x3XXXXXXX is for system threads, 0x7XXXXXXX is for title threads.
```

## Source note 101, line 1230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1230)

```text
// Fixed allocations can only be guaranteed page-aligned. If callers provide
```

## Source note 102, line 1231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1231)

```text
// a stricter alignment for an already-fixed address, fall back to page size.
```

## Source note 103, line 1247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1247)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 104, line 1248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1248)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 105, line 1252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1252)

```text
// - If we are reserving the entire range requested must not be already
```

## Source note 106, line 1253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1253)

```text
//   reserved.
```

## Source note 107, line 1254

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1254)

```text
// - If we are committing it's ok for pages within the range to already be
```

## Source note 108, line 1255

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1255)

```text
//   committed.
```

## Source note 109, line 1259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1259)

```text
// Already reserved.
```

## Source note 110, line 1267

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1267)

```text
// Attempting a commit-only op on an unreserved page.
```

## Source note 111, line 1268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1268)

```text
// This may be OK.
```

## Source note 112, line 1275

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1275)

```text
// Allocate from host.
```

## Source note 113, line 1277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1277)

```text
// Reserve is not needed, as we are mapped already.
```

## Source note 114, line 1291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1291)

```text
// Set page state.
```

## Source note 115, line 1298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1298)

```text
// Region is based on reservation.
```

## Source note 116, line 1328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1328)

```text
// high_address is the last byte the allocation may use. Don't round it up
```

## Source note 117, line 1329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1329)

```text
// to the alignment (xenia-canary #1215): a ceiling that isn't a multiple of
```

## Source note 118, line 1330

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1330)

```text
// it would let the search place the allocation above it, and aligning a
```

## Source note 119, line 1331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1331)

```text
// high_address near UINT32_MAX wraps to zero.
```

## Source note 120, line 1337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1337)

```text
// The search below treats high_page_number as the last usable page, so it
```

## Source note 121, line 1338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1338)

```text
// is the last page that ends at or below high_address. For a window ending
```

## Source note 122, line 1339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1339)

```text
// one byte below an alignment boundary, the common case, allocations whose
```

## Source note 123, line 1340

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1340)

```text
// size is a multiple of the alignment land where they did before.
```

## Source note 124, line 1364

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1364)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 125, line 1365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1365)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 126, line 1369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1369)

```text
// Find a free page range.
```

## Source note 127, line 1370

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1370)

```text
// The base page must match the requested alignment, so we first scan for
```

## Source note 128, line 1371

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1371)

```text
// a free aligned page and only then check for continuous free pages.
```

## Source note 129, line 1382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1382)

```text
// Base page not free, skip to next usable page.
```

## Source note 130, line 1385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1385)

```text
// Check requested range to ensure free.
```

## Source note 131, line 1394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1394)

```text
// At least one page in the range is used, skip to next.
```

## Source note 132, line 1395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1395)

```text
// We know we'll be starting at least before this page.
```

## Source note 133, line 1398

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1398)

```text
// Not enough space left to fit entire page range. Breaks outer
```

## Source note 134, line 1399

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1399)

```text
// loop.
```

## Source note 135, line 1404

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1404)

```text
// cancel out loop logic
```

## Source note 136, line 1410

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1410)

```text
// Found our place.
```

## Source note 137, line 1413

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1413)

```text
// Retry.
```

## Source note 138, line 1420

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1420)

```text
// Base page not free, skip to next usable page.
```

## Source note 139, line 1423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1423)

```text
// Check requested range to ensure free.
```

## Source note 140, line 1431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1431)

```text
// At least one page in the range is used, skip to next.
```

## Source note 141, line 1432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1432)

```text
// We know we'll be starting at least after this page.
```

## Source note 142, line 1435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1435)

```text
// cancel out loop logic
```

## Source note 143, line 1440

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1440)

```text
// Found our place.
```

## Source note 144, line 1443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1443)

```text
// Retry.
```

## Source note 145, line 1448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1448)

```text
// Out of memory.
```

## Source note 146, line 1454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1454)

```text
// Allocate from host.
```

## Source note 147, line 1456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1456)

```text
// Reserve is not needed, as we are mapped already.
```

## Source note 148, line 1470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1470)

```text
// Set page state.
```

## Source note 149, line 1504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1504)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 150, line 1505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1505)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 151, line 1509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1509)

```text
// Release from host.
```

## Source note 152, line 1511

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1511)

```text
// Perform table change.
```

## Source note 153, line 1525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1525)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 154, line 1526

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1526)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 155, line 1530

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1530)

```text
// Given address must be a region base address.
```

## Source note 156, line 1547

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1547)

```text
// Release from host not needed as mapping reserves the range for us.
```

## Source note 157, line 1561

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1561)

```text
// Perform table change.
```

## Source note 158, line 1582

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1582)

```text
// From the VirtualProtect MSDN page:
```

## Source note 159, line 1584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1584)

```text
// "The region of affected pages includes all pages containing one or more
```

## Source note 160, line 1585

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1585)

```text
//  bytes in the range from the lpAddress parameter to (lpAddress+dwSize).
```

## Source note 161, line 1586

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1586)

```text
//  This means that a 2-byte range straddling a page boundary causes the
```

## Source note 162, line 1587

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1587)

```text
//  protection attributes of both pages to be changed."
```

## Source note 163, line 1589

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1589)

```text
// "The access protection value can be set only on committed pages. If the
```

## Source note 164, line 1590

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1590)

```text
//  state of any page in the specified region is not committed, the function
```

## Source note 165, line 1591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1591)

```text
//  fails and returns without modifying the access protection of any pages in
```

## Source note 166, line 1592

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1592)

```text
//  the specified region."
```

## Source note 167, line 1609

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1609)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 168, line 1610

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1610)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 169, line 1614

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1614)

```text
// Ensure all pages are in the same reserved region and all are committed.
```

## Source note 170, line 1630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1630)

```text
// Change host protection directly when guest pages are at least as large as
```

## Source note 171, line 1631

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1631)

```text
// host pages. Smaller guest pages are reconciled after the page table update.
```

## Source note 172, line 1651

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1651)

```text
// Perform table change.
```

## Source note 173, line 1681

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1681)

```text
// Committed/reserved region.
```

## Source note 174, line 1688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1688)

```text
// Scan forward and report the size of the region matching the initial
```

## Source note 175, line 1689

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1689)

```text
// base address's attributes.
```

## Source note 176, line 1697

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1697)

```text
// Different region or different properties within the region; done.
```

## Source note 177, line 1703

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1703)

```text
// Free region.
```

## Source note 178, line 1708

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1708)

```text
// First non-free page; done with region.
```

## Source note 179, line 1825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1825)

```text
// Default top-down. Since parent heap is bottom-up this prevents
```

## Source note 180, line 1826

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1826)

```text
// collisions.
```

## Source note 181, line 1829

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1829)

```text
// Adjust alignment size our page size differs from the parent.
```

## Source note 182, line 1833

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1833)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 183, line 1834

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1834)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 184, line 1838

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1838)

```text
// Allocate from parent heap (gets our physical address in 0-512mb).
```

## Source note 185, line 1848

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1848)

```text
// Given the address we've reserved in the parent heap, pin that here.
```

## Source note 186, line 1849

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1849)

```text
// Shouldn't be possible for it to be allocated already.
```

## Source note 187, line 1862

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1862)

```text
// Adjust alignment size our page size differs from the parent.
```

## Source note 188, line 1866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1866)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 189, line 1867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1867)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 190, line 1871

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1871)

```text
// Allocate from parent heap (gets our physical address in 0-512mb).
```

## Source note 191, line 1872

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1872)

```text
// NOTE: this can potentially overwrite heap contents if there are already
```

## Source note 192, line 1873

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1873)

```text
// committed pages in the requested physical range.
```

## Source note 193, line 1881

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1881)

```text
// Given the address we've reserved in the parent heap, pin that here.
```

## Source note 194, line 1882

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1882)

```text
// Shouldn't be possible for it to be allocated already.
```

## Source note 195, line 1898

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1898)

```text
// Adjust alignment size our page size differs from the parent.
```

## Source note 196, line 1902

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1902)

```text
// Global critical region before heap_mutex_ - see
```

## Source note 197, line 1903

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1903)

```text
// AcquireHostPageReconcileLock for why the order matters.
```

## Source note 198, line 1907

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1907)

```text
// Allocate from parent heap (gets our physical address in 0-512mb).
```

## Source note 199, line 1919

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1919)

```text
// Given the address we've reserved in the parent heap, pin that here.
```

## Source note 200, line 1920

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1920)

```text
// Shouldn't be possible for it to be allocated already.
```

## Source note 201, line 1945

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1945)

```text
// Not caring about the contents anymore.
```

## Source note 202, line 1960

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1960)

```text
// Must invalidate here because the range being released may be reused in
```

## Source note 203, line 1961

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1961)

```text
// another mapping of physical memory - but callback flags are set in each
```

## Source note 204, line 1962

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1962)

```text
// heap separately (https://github.com/xenia-project/xenia/issues/1559 -
```

## Source note 205, line 1963

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1963)

```text
// dynamic vertices in 4D5307F2 start screen and menu allocated in 0xA0000000
```

## Source note 206, line 1964

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1964)

```text
// at addresses that overlap intro video textures in 0xE0000000, with the
```

## Source note 207, line 1965

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1965)

```text
// state of the allocator as of February 24th, 2020). If memory is invalidated
```

## Source note 208, line 1966

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1966)

```text
// in Alloc instead, Alloc won't be aware of callbacks enabled in other heaps,
```

## Source note 209, line 1967

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1967)

```text
// thus callback handlers will keep considering this range valid forever.
```

## Source note 210, line 1980

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1980)

```text
// Only invalidate if making writable again, for simplicity - not when simply
```

## Source note 211, line 1981

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L1981)

```text
// marking some range as immutable, for instance.
```

## Source note 212, line 2024

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2024)

```text
// Update callback flags for system pages and make their protection stricter
```

## Source note 213, line 2025

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2025)

```text
// if needed.
```

## Source note 214, line 2033

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2033)

```text
// Check if need to enable callbacks for the page and raise its protection.
```

## Source note 215, line 2035

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2035)

```text
// If enabling invalidation notifications:
```

## Source note 216, line 2036

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2036)

```text
// - Page writable and not watched for changes yet - protect and enable
```

## Source note 217, line 2037

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2037)

```text
//   invalidation notifications.
```

## Source note 218, line 2038

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2038)

```text
// - Page seen as writable by the guest, but only needs data providers -
```

## Source note 219, line 2039

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2039)

```text
//   just set the bits to enable invalidation notifications (already has
```

## Source note 220, line 2040

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2040)

```text
//   even stricter protection than needed).
```

## Source note 221, line 2041

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2041)

```text
// - Page not writable as requested by the game - don't do anything (need
```

## Source note 222, line 2042

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2042)

```text
//   real access violations here).
```

## Source note 223, line 2043

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2043)

```text
// If enabling data providers:
```

## Source note 224, line 2044

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2044)

```text
// - Page accessible (either read/write or read-only) and didn't need data
```

## Source note 225, line 2045

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2045)

```text
//   providers initially - protect and enable data providers.
```

## Source note 226, line 2046

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2046)

```text
// - Otherwise - do nothing.
```

## Source note 227, line 2048

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2048)

```text
// It's safe not to await data provider completion here before protecting as
```

## Source note 228, line 2049

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2049)

```text
// this never makes protection lighter, so it can't interfere with page
```

## Source note 229, line 2050

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2050)

```text
// faults that await data providers.
```

## Source note 230, line 2052

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2052)

```text
// Enabling data providers doesn't need to be deferred - providers will be
```

## Source note 231, line 2053

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2053)

```text
// polled for the last time without releasing the lock.
```

## Source note 232, line 2067

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2067)

```text
// Don't do anything with inaccessible pages - don't protect, don't enable
```

## Source note 233, line 2068

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2068)

```text
// callbacks - because real access violations are needed there. And don't
```

## Source note 234, line 2069

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2069)

```text
// enable invalidation notifications for read-only pages for the same
```

## Source note 235, line 2070

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2070)

```text
// reason.
```

## Source note 236, line 2131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2131)

```text
// Check if watching any page, whether need to call the callback at all.
```

## Source note 237, line 2150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2150)

```text
// Trigger callbacks.
```

## Source note 238, line 2152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2152)

```text
// If not doing anything with protection, no point in unwatching excess
```

## Source note 239, line 2153

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2153)

```text
// pages.
```

## Source note 240, line 2179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2179)

```text
// Always unwatch at least the requested pages.
```

## Source note 241, line 2182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2182)

```text
// Don't unprotect too much if not caring much about the region (limit to
```

## Source note 242, line 2183

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2183)

```text
// 4 MB - somewhat random, but max 1024 iterations of the page loop).
```

## Source note 243, line 2188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2188)

```text
// Convert to heap-relative addresses.
```

## Source note 244, line 2191

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2191)

```text
// Clamp to the heap upper bound.
```

## Source note 245, line 2194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2194)

```text
// Convert to system pages and update the range.
```

## Source note 246, line 2204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2204)

```text
// Unprotect ranges that need unprotection.
```

## Source note 247, line 2209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2209)

```text
// Check if need to allow writing to this page.
```

## Source note 248, line 2240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2240)

```text
// Mark pages as not write-watched.
```

## Source note 249, line 2264

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2264)

```text
// Indices match EnableAccessCallbacks: both count host pages from
```

## Source note 250, line 2265

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/system/xmemory.cpp#L2265)

```text
// membase_ + heap_base_, including host_address_offset().
```
