# Heap allocation test: core source notes

This record preserves technical and API notes moved from `tests/unit/memory/heap_allocation_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L24)

```text
// Helper to cast away const for heap operations
```

## Source note 2, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L32)

```text
// Size and Alignment Rounding Tests
```

## Source note 3, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L37)

```text
// v00000000, 4KB pages
```

## Source note 4, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L43)

```text
// Requested size
```

## Source note 5, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L50)

```text
// Query to verify actual allocated size
```

## Source note 6, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L53)

```text
// Rounded up from 100
```

## Source note 7, line 89

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L89)

```text
// 4 pages
```

## Source note 8, line 110

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L110)

```text
// 32-byte alignment requested
```

## Source note 9, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L115)

```text
// Address should be page-aligned (4096), not just 32-byte aligned
```

## Source note 10, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L124)

```text
// 64KB alignment
```

## Source note 11, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L136)

```text
// Allocation Direction Tests
```

## Source note 12, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L148)

```text
// bottom-up
```

## Source note 13, line 152

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L152)

```text
// First 64KB (0x10000) is reserved, allocations start at 0x10000 or later
```

## Source note 14, line 166

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L166)

```text
// Allocate bottom-up first
```

## Source note 15, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L171)

```text
// Allocate top-down
```

## Source note 16, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L175)

```text
// top-down
```

## Source note 17, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L178)

```text
// Top-down should be significantly higher
```

## Source note 18, line 180

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L180)

```text
// Top-down should be near top of heap (heap ends at ~0x40000000)
```

## Source note 19, line 188

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L188)

```text
// AllocFixed Tests
```

## Source note 20, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L196)

```text
// Choose an address that should be free
```

## Source note 21, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L205)

```text
// Verify allocation is at exact address
```

## Source note 22, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L209)

```text
// Should be allocated
```

## Source note 23, line 221

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L221)

```text
// First allocation: reserve only
```

## Source note 24, line 223

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L223)

```text
// Reserve only
```

## Source note 25, line 227

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L227)

```text
// Second reserve at same address should FAIL
```

## Source note 26, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L230)

```text
// Reserve only - should fail
```

## Source note 27, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L244)

```text
// First: reserve only
```

## Source note 28, line 250

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L250)

```text
// Second: commit on already-reserved region should SUCCEED
```

## Source note 29, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L253)

```text
// Commit only
```

## Source note 30, line 261

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L261)

```text
// Protection Tests
```

## Source note 31, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L272)

```text
// Initial: RW
```

## Source note 32, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L279)

```text
// New: Read only
```

## Source note 33, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L283)

```text
// Old protection should have been RW (3)
```

## Source note 34, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L286)

```text
// Query to verify new protection
```

## Source note 35, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L296)

```text
// QueryRegionInfo Tests
```

## Source note 36, line 306

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L306)

```text
// 4 pages
```

## Source note 37, line 323

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L323)

```text
// Third page
```

## Source note 38, line 327

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L327)

```text
// base_address is the queried address
```

## Source note 39, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L329)

```text
// allocation_size should still be full allocation
```

## Source note 40, line 331

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L331)

```text
// region_size is remaining size from query point
```

## Source note 41, line 332

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L332)

```text
// 2 pages left
```

## Source note 42, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L339)

```text
// Release Tests
```

## Source note 43, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L344)

```text
// Use a different region
```

## Source note 44, line 362

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L362)

```text
// Should be able to allocate at same address again
```

## Source note 45, line 373

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L373)

```text
// Heap Selection Tests (LookupHeap)
```

## Source note 46, line 382

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L382)

```text
// This is the 4KB page heap
```

## Source note 47, line 388

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L388)

```text
// This is the 64KB page heap
```

## Source note 48, line 403

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L403)

```text
// 64KB Page Heap Tests (v40000000)
```

## Source note 49, line 408

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L408)

```text
// v40000000 heap
```

## Source note 50, line 414

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L414)

```text
// Request only 4KB
```

## Source note 51, line 421

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L421)

```text
// Size should be rounded to 64KB page size
```

## Source note 52, line 424

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L424)

```text
// Address should be 64KB aligned
```

## Source note 53, line 432

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L432)

```text
// Decommit Tests
```

## Source note 54, line 446

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L446)

```text
// Verify initial state is committed
```

## Source note 55, line 456

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L456)

```text
// Verify commit flag is removed but reserve remains
```

## Source note 56, line 472

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L472)

```text
// 4 pages
```

## Source note 57, line 477

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L477)

```text
// Decommit only middle 2 pages
```

## Source note 58, line 481

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L481)

```text
// First page should still be committed
```

## Source note 59, line 486

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L486)

```text
// Middle page should be decommitted
```

## Source note 60, line 491

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L491)

```text
// Last page should still be committed
```

## Source note 61, line 500

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L500)

```text
// This pattern observed in real app: NtFreeVirtualMemory(MEM_DECOMMIT)
```

## Source note 62, line 501

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L501)

```text
// followed by NtAllocateVirtualMemory at same address
```

## Source note 63, line 503

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L503)

```text
// v40000000 heap, 64KB pages
```

## Source note 64, line 506

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L506)

```text
// Allocate on 64KB heap
```

## Source note 65, line 513

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L513)

```text
// Decommit (like NtFreeVirtualMemory with type=0x4000)
```

## Source note 66, line 517

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L517)

```text
// After decommit, state should be Reserve only (state=1)
```

## Source note 67, line 520

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L520)

```text
// Exactly 1
```

## Source note 68, line 522

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L522)

```text
// Recommit at same address (like NtAllocateVirtualMemory with type=0x60001000)
```

## Source note 69, line 525

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L525)

```text
// Commit only
```

## Source note 70, line 529

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L529)

```text
// State should now include commit again
```

## Source note 71, line 538

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L538)

```text
// Real app decommits same address multiple times in sequence
```

## Source note 72, line 540

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L540)

```text
// v40000000 heap
```

## Source note 73, line 549

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L549)

```text
// First decommit
```

## Source note 74, line 553

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L553)

```text
// Second decommit of same already-decommitted page should still succeed
```

## Source note 75, line 557

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L557)

```text
// Third decommit
```

## Source note 76, line 565

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L565)

```text
// On v40000000 heap, even small decommit requests affect whole 64KB page
```

## Source note 77, line 576

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L576)

```text
// Decommit with small size - should still affect the page
```

## Source note 78, line 577

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L577)

```text
// Request only 4KB
```

## Source note 79, line 580

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L580)

```text
// The 64KB page should still be affected (implementation detail:
```

## Source note 80, line 581

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L581)

```text
// size gets rounded to page_size internally via get_page_count)
```

## Source note 81, line 584

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L584)

```text
// State should show decommitted
```

## Source note 82, line 591

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L591)

```text
// Address Translation Tests
```

## Source note 83, line 597

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L597)

```text
// Allocate some memory first
```

## Source note 84, line 607

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L607)

```text
// Translate to host
```

## Source note 85, line 611

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L611)

```text
// Should be able to read/write
```

## Source note 86, line 630

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L630)

```text
// Guest -> Host -> Guest roundtrip
```

## Source note 87, line 642

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L642)

```text
// Physical addresses are masked with 0x1FFFFFFF (29 bits)
```

## Source note 88, line 643

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L643)

```text
// So 0xA0000000 and 0x00000000 should map to same physical offset
```

## Source note 89, line 647

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L647)

```text
// Both should resolve to same offset in physical memory
```

## Source note 90, line 648

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L648)

```text
// (0xA0001000 & 0x1FFFFFFF) == 0x00001000
```

## Source note 91, line 653

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L653)

```text
// Physical Heap Tests
```

## Source note 92, line 661

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L661)

```text
// vA0000000 heap: base=0xA0000000, 64KB pages
```

## Source note 93, line 668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L668)

```text
// Address should be in 0xA0000000-0xBFFFFFFF range
```

## Source note 94, line 672

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L672)

```text
// Should be 64KB aligned
```

## Source note 95, line 683

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L683)

```text
// vC0000000 heap: base=0xC0000000, 16MB pages
```

## Source note 96, line 684

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L684)

```text
// Note: First 16MB is pre-allocated for GPU writeback
```

## Source note 97, line 688

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L688)

```text
// 16MB
```

## Source note 98, line 693

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L693)

```text
// Address should be in 0xC0000000-0xDFFFFFFF range
```

## Source note 99, line 705

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L705)

```text
// vE0000000 heap: base=0xE0000000, 4KB pages
```

## Source note 100, line 712

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L712)

```text
// Address should be in 0xE0000000-0xFFCFFFFF range
```

## Source note 101, line 716

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L716)

```text
// Should be 4KB aligned
```

## Source note 102, line 728

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L728)

```text
// Should be v00000000 heap
```

## Source note 103, line 734

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L734)

```text
// Should be v40000000 heap
```

## Source note 104, line 740

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L740)

```text
// Should be vE0000000 heap
```

## Source note 105, line 746

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L746)

```text
// Should be vA0000000 heap
```

## Source note 106, line 752

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L752)

```text
// Should be vC0000000 heap
```

## Source note 107, line 757

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L757)

```text
// AllocRange Window Tests (RG-GDK-004, xenia-canary #1215)
```

## Source note 108, line 766

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L766)

```text
// Allocates in [low, high] and checks the result lies fully inside it.
```

## Source note 109, line 783

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L783)

```text
// Rounding 0x3E0F8000 up to 64 KB would place the top-down allocation at
```

## Source note 110, line 784

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L784)

```text
// 0x3E0F0000, ending above the ceiling.
```

## Source note 111, line 789

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L789)

```text
// A ceiling in the middle of a page excludes that page.
```

## Source note 112, line 799

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L799)

```text
// Previously the aligned-up ceiling let this land at 0x3E110000.
```

## Source note 113, line 804

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L804)

```text
// Allocations that are a multiple of the alignment land where they did.
```

## Source note 114, line 825

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L825)

```text
// Aligning 0xFFFFFFFF up used to wrap to zero and reject the range.
```

## Source note 115, line 835

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L835)

```text
// A full window isn't tested here: the search failing hits the debug
```

## Source note 116, line 836

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L836)

```text
// "Heap exhausted!" assertion.
```

## Source note 117, line 855

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L855)

```text
// xenia-canary #1215's case: the parent heap (4 KB pages) gets the physical
```

## Source note 118, line 856

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L856)

```text
// window 0x10000000-0x10FF8000, whose ceiling isn't 64 KB aligned.
```

## Source note 119, line 863

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L863)

```text
// The caller's alignment is a physical one, which is what the guest reads
```

## Source note 120, line 864

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L864)

```text
// back through MmGetPhysicalAddress. The vE0000000 heap sits 0x1000 below
```

## Source note 121, line 865

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L865)

```text
// its physical addresses, so its virtual addresses are aligned only to the
```

## Source note 122, line 866

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L866)

```text
// page. xenia-canary #1202 (rejected) and #1182 (open) aim to change this;
```

## Source note 123, line 867

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L867)

```text
// see docs/upstream-tracking.md.
```

## Source note 124, line 879

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L879)

```text
// Both host views reach the same memory.
```

## Source note 125, line 886

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/tests/unit/memory/heap_allocation_test.cpp#L886)

```text
// 4D5307F1's request (xenia-canary #1182): 0x280000 bytes at 32 KB alignment.
```
