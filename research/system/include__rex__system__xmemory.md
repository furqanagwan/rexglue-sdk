# Xmemory: system source notes

This record preserves technical and API notes moved from `include/rex/system/xmemory.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L21)

```text
// PPCFunc type
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L31)

```text
/// Compensates for host allocation granularity coarser than 4KB on the 0xE0
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L32)

```text
/// physical heap. When the granularity exceeds 0x1000, the backing file maps the
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L33)

```text
/// 0xE0 heap at a 0x1000-byte offset that the mapping API rounds away (Windows
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L34)

```text
/// MapViewOfFileEx rounds down to 64KB), so guest
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L35)

```text
/// accesses must add it back. This must agree with Memory::MapViews, which only
```

## Source note 7, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L36)

```text
/// sets host_address_offset when allocation_granularity() > 0x1000:
```

## Source note 8, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L37)

```text
///   - Windows:        64KB granularity  -> offset
```

## Source note 9, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L46)

```text
/// Lightweight guest-to-host pointer translation using the memory base.
```

## Source note 10, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L47)

```text
/// For hooks and kernel code operating with the base pointer directly.
```

## Source note 11, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L48)

```text
/// Same raw arithmetic as recompiled code; no Memory* or heap lookup needed.
```

## Source note 12, line 84

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L84)

```text
// Equivalent to the Win32 MEMORY_BASIC_INFORMATION struct.
```

## Source note 13, line 86

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L86)

```text
// A pointer to the base address of the region of pages.
```

## Source note 14, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L88)

```text
// A pointer to the base address of a range of pages allocated by the
```

## Source note 15, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L89)

```text
// VirtualAlloc function. The page pointed to by the BaseAddress member is
```

## Source note 16, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L90)

```text
// contained within this allocation range.
```

## Source note 17, line 92

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L92)

```text
// The memory protection option when the region was initially allocated.
```

## Source note 18, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L94)

```text
// The size specified when the region was initially allocated, in bytes.
```

## Source note 19, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L96)

```text
// The size of the region beginning at the base address in which all pages
```

## Source note 20, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L97)

```text
// have identical attributes, in bytes.
```

## Source note 21, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L99)

```text
// The state of the pages in the region (commit/free/reserve).
```

## Source note 22, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L101)

```text
// The access protection of the pages in the region.
```

## Source note 23, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L105)

```text
// Describes a single page in the page table.
```

## Source note 24, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L109)

```text
// Base address of the allocated region in 4k pages.
```

## Source note 25, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L111)

```text
// Total number of pages in the allocated region in 4k pages.
```

## Source note 26, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L113)

```text
// Protection bits specified during region allocation.
```

## Source note 27, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L114)

```text
// Composed of bits from MemoryProtectFlag.
```

## Source note 28, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L116)

```text
// Current protection bits as of the last Protect.
```

## Source note 29, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L117)

```text
// Composed of bits from MemoryProtectFlag.
```

## Source note 30, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L119)

```text
// Allocation state of the page as a MemoryAllocationFlag bit mask.
```

## Source note 31, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L125)

```text
// Heap abstraction for page-based allocation.
```

## Source note 32, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L130)

```text
// Offset of the heap in relative to membase, without host_address_offset
```

## Source note 33, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L131)

```text
// adjustment.
```

## Source note 34, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L134)

```text
// Length of the heap range.
```

## Source note 35, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L137)

```text
// Size of each page within the heap range in bytes.
```

## Source note 36, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L140)

```text
// Type of specified heap
```

## Source note 37, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L143)

```text
// Offset added to the virtual addresses to convert them to host addresses
```

## Source note 38, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L144)

```text
// (not including membase).
```

## Source note 39, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L152)

```text
// Disposes and decommits all memory and clears the page table.
```

## Source note 40, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L155)

```text
// Dumps information about all allocations within the heap to the log.
```

## Source note 41, line 165

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L165)

```text
// Allocates pages with the given properties and allocation strategy.
```

## Source note 42, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L166)

```text
// This can reserve and commit the pages as well as set protection modes.
```

## Source note 43, line 167

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L167)

```text
// This will fail if not enough contiguous pages can be found.
```

## Source note 44, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L171)

```text
// Allocates pages at the given address.
```

## Source note 45, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L172)

```text
// This can reserve and commit the pages as well as set protection modes.
```

## Source note 46, line 173

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L173)

```text
// This will fail if the pages are already allocated.
```

## Source note 47, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L177)

```text
// Allocates pages at an address within the given address range.
```

## Source note 48, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L178)

```text
// This can reserve and commit the pages as well as set protection modes.
```

## Source note 49, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L179)

```text
// This will fail if not enough contiguous pages can be found.
```

## Source note 50, line 184

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L184)

```text
// Allocates from the system portion of the heap (top of virtual heaps).
```

## Source note 51, line 185

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L185)

```text
// Physical heaps delegate to regular Alloc since there is no split.
```

## Source note 52, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L189)

```text
// Decommits pages in the given range.
```

## Source note 53, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L190)

```text
// Partial overlapping pages will also be decommitted.
```

## Source note 54, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L193)

```text
// Decommits and releases pages in the given range.
```

## Source note 55, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L194)

```text
// Partial overlapping pages will also be released.
```

## Source note 56, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L197)

```text
// Modifies the protection mode of pages within the given range.
```

## Source note 57, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L201)

```text
// Queries information about the given region of pages.
```

## Source note 58, line 204

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L204)

```text
// Queries the size of the region containing the given address.
```

## Source note 59, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L207)

```text
// Queries the base and size of a region containing the given address.
```

## Source note 60, line 210

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L210)

```text
// Queries the current protection mode of the region containing the given
```

## Source note 61, line 211

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L211)

```text
// address.
```

## Source note 62, line 214

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L214)

```text
// Queries the currently strictest readability and writability for the entire
```

## Source note 63, line 215

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L215)

```text
// range.
```

## Source note 64, line 226

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L226)

```text
// Callers must hold the global critical region - see
```

## Source note 65, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L227)

```text
// AcquireHostPageReconcileLock.
```

## Source note 66, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L230)

```text
// Acquires the global critical region for operations that will run the host
```

## Source note 67, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L231)

```text
// page reconcile pass, which reads watch state guarded by it.
```

## Source note 68, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L233)

```text
// It must be taken before heap_mutex_, not partway through: mutex.h requires
```

## Source note 69, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L234)

```text
// the global region to be acquired first and held longest, and
```

## Source note 70, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L235)

```text
// PhysicalHeap::Decommit/Release/Protect already call down into BaseHeap
```

## Source note 71, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L236)

```text
// with it held. Acquiring it inside SyncHostPageAccess instead would give
```

## Source note 72, line 237

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L237)

```text
// those paths heap_mutex_ -> global while PhysicalHeap has global ->
```

## Source note 73, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L238)

```text
// heap_mutex_, which deadlocks.
```

## Source note 74, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L240)

```text
// Returns an empty (unlocked) guard when guest pages are at least host page
```

## Source note 75, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L241)

```text
// sized, since no reconcile happens then and the lock would be pure cost.
```

## Source note 76, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L244)

```text
// Whether a host page is currently write-watched for guest invalidation.
```

## Source note 77, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L245)

```text
// SyncHostPageAccess must not restore write access to such a page: the watch
```

## Source note 78, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L246)

```text
// is recorded in a flag that EnableAccessCallbacks checks before re-applying
```

## Source note 79, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L247)

```text
// protection, so silently unprotecting here would disable the watch forever.
```

## Source note 80, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L248)

```text
// Only PhysicalHeap tracks this; every other heap has no watch state.
```

## Source note 81, line 268

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L268)

```text
// Normal heap allowing allocations from guest virtual address ranges.
```

## Source note 82, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L274)

```text
// Initializes the heap properties and allocates the page table.
```

## Source note 83, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L279)

```text
// A heap for ranges of memory that are mapped to physical ranges.
```

## Source note 84, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L280)

```text
// Physical ranges are used by the audio and graphics subsystems representing
```

## Source note 85, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L281)

```text
// hardware wired directly to memory in the console.
```

## Source note 86, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L283)

```text
// The physical heap and the behavior of sharing pages with virtual pages is
```

## Source note 87, line 284

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L284)

```text
// implemented by having a 'parent' heap that is used to perform allocation in
```

## Source note 88, line 285

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L285)

```text
// the guest virtual address space 1:1 with the physical address space.
```

## Source note 89, line 291

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L291)

```text
// Initializes the heap properties and allocates the page table.
```

## Source note 90, line 311

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L311)

```text
// Returns true if any page in the range was watched.
```

## Source note 91, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L321)

```text
// Allocation on these heaps delegates to parent_heap_, whose own reconcile
```

## Source note 92, line 322

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L322)

```text
// pass takes the global critical region. Acquire whenever this heap or its
```

## Source note 93, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L323)

```text
// parent will need it, so the ordering holds even for a heap whose own guest
```

## Source note 94, line 324

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L324)

```text
// pages are large enough to skip reconciling but whose parent's are not.
```

## Source note 95, line 333

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L333)

```text
// Whether writing to each page should result trigger invalidation
```

## Source note 96, line 334

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L334)

```text
// callbacks.
```

## Source note 97, line 337

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L337)

```text
// Protected by global_critical_region. Flags for each 64 system pages,
```

## Source note 98, line 338

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L338)

```text
// interleaved as blocks, so bit scan can be used to quickly extract ranges.
```

## Source note 99, line 342

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L342)

```text
// Models the entire guest memory system on the console.
```

## Source note 100, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L343)

```text
// This exposes interfaces to both virtual and physical memory and a TLB and
```

## Source note 101, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L344)

```text
// page table for allocation, mapping, and protection.
```

## Source note 102, line 346

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L346)

```text
// The memory is backed by a memory mapped file and is placed at a stable
```

## Source note 103, line 347

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L347)

```text
// fixed address in the host address space (like 0x100000000). This allows
```

## Source note 104, line 348

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L348)

```text
// efficient guest<->host address translations as well as easy sharing of the
```

## Source note 105, line 349

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L349)

```text
// memory across various subsystems.
```

## Source note 106, line 351

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L351)

```text
// The guest memory address space is split into several ranges that have varying
```

## Source note 107, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L352)

```text
// properties such as page sizes, caching strategies, protections, and
```

## Source note 108, line 353

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L353)

```text
// overlap with other ranges. Each range is represented by a BaseHeap of either
```

## Source note 109, line 354

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L354)

```text
// VirtualHeap or PhysicalHeap depending on type. Heaps model the page tables
```

## Source note 110, line 355

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L355)

```text
// and can handle reservation and committing of requested pages.
```

## Source note 111, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L361)

```text
// Initializes the memory system.
```

## Source note 112, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L362)

```text
// This may fail if the host address space could not be reserved or the
```

## Source note 113, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L363)

```text
// mapping to the file system fails.
```

## Source note 114, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L366)

```text
// Resets all memory to zero and resets all allocations.
```

## Source note 115, line 369

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L369)

```text
// Full file name and path of the memory-mapped file backing all memory.
```

## Source note 116, line 372

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L372)

```text
// Base address of virtual memory in the host address space.
```

## Source note 117, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L373)

```text
// This is often something like 0x100000000.
```

## Source note 118, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L376)

```text
// Translates a guest virtual address to a host address that can be accessed
```

## Source note 119, line 377

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L377)

```text
// as a normal pointer.
```

## Source note 120, line 378

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L378)

```text
// Note that the contents at the specified host address are big-endian.
```

## Source note 121, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L389)

```text
// Base address of physical memory in the host address space.
```

## Source note 122, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L390)

```text
// This is often something like 0x200000000.
```

## Source note 123, line 393

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L393)

```text
// Translates a guest physical address to a host address that can be accessed
```

## Source note 124, line 394

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L394)

```text
// as a normal pointer.
```

## Source note 125, line 395

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L395)

```text
// Note that the contents at the specified host address are big-endian.
```

## Source note 126, line 401

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L401)

```text
// Translates a host address to a guest virtual address.
```

## Source note 127, line 402

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L402)

```text
// Note that the contents at the returned host address are big-endian.
```

## Source note 128, line 405

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L405)

```text
// Returns the guest physical address for the guest virtual address, or
```

## Source note 129, line 406

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L406)

```text
// UINT32_MAX if it can't be obtained.
```

## Source note 130, line 409

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L409)

```text
// Zeros out a range of memory at the given guest address.
```

## Source note 131, line 412

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L412)

```text
// Fills a range of guest memory with the given byte value.
```

## Source note 132, line 415

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L415)

```text
// Copies a non-overlapping range of guest memory (like a memcpy).
```

## Source note 133, line 418

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L418)

```text
// Searches the given range of guest memory for a run of dword values in
```

## Source note 134, line 419

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L419)

```text
// big-endian order.
```

## Source note 135, line 422

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L422)

```text
// Defines a memory-mapped IO (MMIO) virtual address range that when accessed
```

## Source note 136, line 423

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L423)

```text
// will trigger the specified read and write callbacks for dword read/writes.
```

## Source note 137, line 428

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L428)

```text
// Gets the defined MMIO range for the given virtual address, if any.
```

## Source note 138, line 431

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L431)

```text
// Physical memory access callbacks, two types of them.
```

## Source note 139, line 433

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L433)

```text
// This is simple per-system-page protection without reference counting or
```

## Source note 140, line 434

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L434)

```text
// stored ranges. Whenever a watched page is accessed, all callbacks for it
```

## Source note 141, line 435

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L435)

```text
// are triggered. Also the only way to remove callbacks is to trigger them
```

## Source note 142, line 436

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L436)

```text
// somehow. Since there are no references from pages to individual callbacks,
```

## Source note 143, line 437

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L437)

```text
// there's no way to disable only a specific callback for a page. Also
```

## Source note 144, line 438

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L438)

```text
// callbacks may be triggered spuriously, and handlers should properly ignore
```

## Source note 145, line 439

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L439)

```text
// pages they don't care about.
```

## Source note 146, line 441

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L441)

```text
// Once callbacks are triggered for a page, the page is not watched anymore
```

## Source note 147, line 442

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L442)

```text
// until requested again later. It is, however, unwatched only in one guest
```

## Source note 148, line 443

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L443)

```text
// view of physical memory (because different views may have different
```

## Source note 149, line 444

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L444)

```text
// protection for the same memory) - but it's rare when the same memory is
```

## Source note 150, line 445

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L445)

```text
// used with different guest page sizes, and it's okay to fire a callback more
```

## Source note 151, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L446)

```text
// than once.
```

## Source note 152, line 448

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L448)

```text
// Only accessing the guest virtual memory views of physical memory triggers
```

## Source note 153, line 449

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L449)

```text
// callbacks - data providers, for instance, must write to the host physical
```

## Source note 154, line 450

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L450)

```text
// heap directly, otherwise their threads may infinitely await themselves.
```

## Source note 155, line 452

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L452)

```text
// - Invalidation notifications:
```

## Source note 156, line 454

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L454)

```text
// Protecting from writing. One-shot callbacks for invalidation of various
```

## Source note 157, line 455

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L455)

```text
// kinds of physical memory caches (such as the GPU copy of the memory).
```

## Source note 158, line 457

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L457)

```text
// May be triggered for a single page (in case of a write access violation or
```

## Source note 159, line 458

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L458)

```text
// when need to synchronize data given by data providers) or for multiple
```

## Source note 160, line 459

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L459)

```text
// pages (like when memory is released, or explicitly to trigger callbacks
```

## Source note 161, line 460

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L460)

```text
// when host-side code can't rely on regular access violations, like when
```

## Source note 162, line 461

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L461)

```text
// accessing a file).
```

## Source note 163, line 463

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L463)

```text
// Since granularity of callbacks is one single page, an invalidation
```

## Source note 164, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L464)

```text
// notification handler must invalidate the all the data stored in the touched
```

## Source note 165, line 465

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L465)

```text
// pages.
```

## Source note 166, line 467

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L467)

```text
// Because large ranges (like whole framebuffers) may be written to and
```

## Source note 167, line 468

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L468)

```text
// exceptions are expensive, it's better to unprotect multiple pages as a
```

## Source note 168, line 469

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L469)

```text
// result of a write access violation, so the shortest common range returned
```

## Source note 169, line 470

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L470)

```text
// by all the invalidation callbacks (clamped to a sane range and also not to
```

## Source note 170, line 471

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L471)

```text
// touch pages with provider callbacks) is unprotected.
```

## Source note 171, line 473

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L473)

```text
// - Data providers:
```

## Source note 172, line 476

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L476)

```text
// Returns start and length of the smallest physical memory region surrounding
```

## Source note 173, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L477)

```text
// the watched region that can be safely unwatched, if it doesn't matter,
```

## Source note 174, line 478

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L478)

```text
// return (0, UINT32_MAX).
```

## Source note 175, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L481)

```text
// Returns a handle for unregistering or for skipping one notification handler
```

## Source note 176, line 482

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L482)

```text
// while triggering data providers.
```

## Source note 177, line 485

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L485)

```text
// Unregisters a physical memory invalidation callback previously added with
```

## Source note 178, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L486)

```text
// RegisterPhysicalMemoryInvalidationCallback.
```

## Source note 179, line 489

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L489)

```text
// Enables physical memory access callbacks for the specified memory range,
```

## Source note 180, line 490

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L490)

```text
// snapped to system page boundaries.
```

## Source note 181, line 495

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L495)

```text
// Forces triggering of watch callbacks for a virtual address range if pages
```

## Source note 182, line 496

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L496)

```text
// are watched there and unwatching them. Returns whether any page was
```

## Source note 183, line 497

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L497)

```text
// watched. Must be called with global critical region locking depth of 1.
```

## Source note 184, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L503)

```text
// Allocates virtual memory from the 'system' heap.
```

## Source note 185, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L504)

```text
// System memory is kept separate from game memory but is still accessible
```

## Source note 186, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L505)

```text
// using normal guest virtual addresses. Kernel structures and other internal
```

## Source note 187, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L506)

```text
// 'system' allocations should come from this heap when possible.
```

## Source note 188, line 510

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L510)

```text
// Frees memory allocated with SystemHeapAlloc.
```

## Source note 189, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L513)

```text
// Gets the heap for the address space containing the given address.
```

## Source note 190, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L520)

```text
// Gets the heap with the given properties.
```

## Source note 191, line 523

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L523)

```text
// Aggregates page statistics across the given heaps.
```

## Source note 192, line 528

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L528)

```text
// Gets the physical base heap.
```

## Source note 193, line 531

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L531)

```text
// Dumps a map of all allocated memory to the log.
```

## Source note 194, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L538)

```text
// Recompiled Code Function Table API
```

## Source note 195, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L540)

```text
// Per-module function dispatch table at `table_base` (the module's
```

## Source note 196, line 541

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L541)

```text
// function_table_base, normally IMAGE_BASE + IMAGE_SIZE), indexed by
```

## Source note 197, line 542

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L542)

```text
// (guest_addr - code_base) * 2. Internally locked: callers may invoke from
```

## Source note 198, line 543

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L543)

```text
// any thread.
```

## Source note 199, line 546

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/xmemory.h#L546)

```text
// Returns false if guest_address is outside every registered module range.
```
