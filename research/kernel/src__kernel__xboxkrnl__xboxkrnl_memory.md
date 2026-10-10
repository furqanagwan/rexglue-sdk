# Xboxkrnl memory: kernel source notes

This record preserves technical and API notes moved from `src/kernel/xboxkrnl/xboxkrnl_memory.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 12

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L12)

```text
// Disable warnings about unused parameters for kernel functions
```

## Source note 2, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L72)

```text
// _Inout_  PVOID *BaseAddress,
```

## Source note 3, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L73)

```text
// _Inout_  PSIZE_T RegionSize,
```

## Source note 4, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L74)

```text
// _In_     ULONG AllocationType,
```

## Source note 5, line 75

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L75)

```text
// _In_     ULONG Protect
```

## Source note 6, line 76

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L76)

```text
// _In_     BOOLEAN DebugMemory
```

## Source note 7, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L81)

```text
// Set to TRUE when allocation is from devkit memory area.
```

## Source note 8, line 82

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L82)

```text
// assert_true(debug_memory == 0);
```

## Source note 9, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L83)

```text
// just warn tf am i gunna do about it
```

## Source note 10, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L88)

```text
// This allocates memory from the kernel heap, which is initialized on startup
```

## Source note 11, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L89)

```text
// and shared by both the kernel implementation and user code.
```

## Source note 12, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L90)

```text
// The xe_memory_ref object is used to actually get the memory, and although
```

## Source note 13, line 91

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L91)

```text
// it's simple today we could extend it to do better things in the future.
```

## Source note 14, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L93)

```text
// Must request a size.
```

## Source note 15, line 97

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L97)

```text
// Check allocation type.
```

## Source note 16, line 101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L101)

```text
// If MEM_RESET is set only MEM_RESET can be set.
```

## Source note 17, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L105)

```text
// Don't allow games to set execute bits.
```

## Source note 18, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L113)

```text
// ignore specified page size when base address is specified.
```

## Source note 19, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L120)

```text
// Adjust size.
```

## Source note 20, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L127)

```text
// Round the base address down to the nearest page boundary.
```

## Source note 21, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L129)

```text
// For some reason, some games pass in negative sizes.
```

## Source note 22, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L132)

```text
// Use 64KB allocation granularity when no base address is specified,
```

## Source note 23, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L133)

```text
// matching Xbox 360 behavior. With a base address, use the heap's page size.
```

## Source note 24, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L136)

```text
// Allocate.
```

## Source note 25, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L160)

```text
// Specified the wrong page size for the wrong heap.
```

## Source note 26, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L175)

```text
// Failed - assume no memory available.
```

## Source note 27, line 179

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L179)

```text
// Zero memory, if needed.
```

## Source note 28, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L194)

```text
// Stash back.
```

## Source note 29, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L195)

```text
// Maybe set X_STATUS_ALREADY_COMMITTED if MEM_COMMIT?
```

## Source note 30, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L205)

```text
// Set to TRUE when this memory refers to devkit memory area.
```

## Source note 31, line 208

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L208)

```text
// Must request a size.
```

## Source note 32, line 213

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L213)

```text
// Don't allow games to set execute bits.
```

## Source note 33, line 224

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L224)

```text
// Adjust the base downwards to the nearest page boundary.
```

## Source note 34, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L235)

```text
// Write back output variables.
```

## Source note 35, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L253)

```text
// X_MEM_DECOMMIT | X_MEM_RELEASE
```

## Source note 36, line 256

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L256)

```text
// _Inout_  PVOID *BaseAddress,
```

## Source note 37, line 257

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L257)

```text
// _Inout_  PSIZE_T RegionSize,
```

## Source note 38, line 258

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L258)

```text
// _In_     ULONG FreeType
```

## Source note 39, line 259

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L259)

```text
// _In_     BOOLEAN DebugMemory
```

## Source note 40, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L261)

```text
// Set to TRUE when freeing external devkit memory.
```

## Source note 41, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L274)

```text
// If zero, we may need to query size (free whole region).
```

## Source note 42, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L325)

```text
// https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-memory_basic_information
```

## Source note 43, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L326)

```text
// State: ... This member can be one of the following values: MEM_COMMIT,
```

## Source note 44, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L327)

```text
// MEM_FREE, MEM_RESERVE.
```

## Source note 45, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L328)

```text
// State queried by Beautiful Katamari before displaying the loading screen.
```

## Source note 46, line 352

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L352)

```text
// Check protection bits.
```

## Source note 47, line 358

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L358)

```text
// Either may be OR'ed into protect_bits:
```

## Source note 48, line 361

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L361)

```text
// We could use this to detect what's likely GPU-synchronized memory
```

## Source note 49, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L362)

```text
// and let the GPU know we're messing with it (or even allocate from
```

## Source note 50, line 363

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L363)

```text
// the GPU). At least the D3D command buffer is X_PAGE_WRITECOMBINE.
```

## Source note 51, line 365

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L365)

```text
// Calculate page size.
```

## Source note 52, line 366

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L366)

```text
// Default            = 4KB
```

## Source note 53, line 367

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L367)

```text
// X_MEM_LARGE_PAGES  = 64KB
```

## Source note 54, line 368

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L368)

```text
// X_MEM_16MB_PAGES   = 16MB
```

## Source note 55, line 376

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L376)

```text
// Round up the region size and alignment to the next page.
```

## Source note 56, line 385

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L385)

```text
// min_addr_range/max_addr_range are bounds in physical memory, not virtual.
```

## Source note 57, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L388)

```text
// NOTE: xenia-canary has a per-title workaround (ignore_offset_for_ranged_allocations cvar)
```

## Source note 58, line 389

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L389)

```text
// for title 545108B4 where min_addr_range comparison fails due to 0x1000 offset.
```

## Source note 59, line 390

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L390)

```text
// If needed, set heap_physical_address_offset = 0 when min_addr_range && max_addr_range.
```

## Source note 60, line 391

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L391)

```text
// Reference: xenia-canary 81aaf98e0.
```

## Source note 61, line 400

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L400)

```text
// Failed - assume no memory available.
```

## Source note 62, line 464

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L464)

```text
// https://code.google.com/p/vdash/source/browse/trunk/vdash/include/kernel.h
```

## Source note 63, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L500)

```text
// Zero out the struct.
```

## Source note 64, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L503)

```text
// Set the constants the game is likely asking for.
```

## Source note 65, line 504

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L504)

```text
// These numbers are mostly guessed. If the game is just checking for
```

## Source note 66, line 505

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L505)

```text
// memory, this should satisfy it. If it's actually verifying things
```

## Source note 67, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L506)

```text
// this won't work :/
```

## Source note 68, line 509

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L509)

```text
// 512mb / 4kb pages
```

## Source note 69, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L557)

```text
// https://msdn.microsoft.com/en-us/library/windows/hardware/ff554547(v=vs.85).aspx
```

## Source note 70, line 559

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L559)

```text
// base_address = result of MmAllocatePhysicalMemory.
```

## Source note 71, line 571

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L571)

```text
// I've only seen this used to map XMA audio contexts.
```

## Source note 72, line 572

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L572)

```text
// The code seems fine with taking the src address, so this just returns that.
```

## Source note 73, line 573

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L573)

```text
// If others start using it there could be problems.
```

## Source note 74, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L597)

```text
// magic marker
```

## Source note 75, line 606

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L606)

```text
// 'None'
```

## Source note 76, line 613

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L613)

```text
// Page-aligned: large allocation with no pool header.
```

## Source note 77, line 616

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L616)

```text
// Small allocation: subtract pool header to get real alloc base.
```

## Source note 78, line 641

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L641)

```text
// Unknown argument.
```

## Source note 79, line 657

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/kernel/xboxkrnl/xboxkrnl_memory.cpp#L657)

```text
// Release the stack (where stack_end is the low address)
```
