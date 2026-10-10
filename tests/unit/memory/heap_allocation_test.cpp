/**
 * @file        heap_allocation_test.cpp
 * @brief       Unit tests for memory heap allocation behavior
 *
 * These tests validate the BaseHeap allocation, protection, and query
 * operations based on observed runtime behavior.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/system/xmemory.h>

#include "test_memory.h"

namespace {

using rex::testing::GetTestMemory;

rex::memory::BaseHeap* MutableHeap(const rex::memory::BaseHeap* heap) {
  return const_cast<rex::memory::BaseHeap*>(heap);
}

}

TEST_CASE("Heap allocation rounds size up to page size", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  SECTION("Size smaller than page size rounds to page size") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        100, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);
    REQUIRE(addr != 0);

    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));
    CHECK(info.allocation_size == 4096);

    heap->Release(addr, nullptr);
  }

  SECTION("Size of 4 bytes rounds to 4096") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        4, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);

    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));
    CHECK(info.allocation_size == 4096);

    heap->Release(addr, nullptr);
  }

  SECTION("Size exactly page size stays unchanged") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);

    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));
    CHECK(info.allocation_size == 4096);

    heap->Release(addr, nullptr);
  }

  SECTION("Multi-page allocation") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        4096 * 4, 4096,
        rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);

    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));
    CHECK(info.allocation_size == 4096 * 4);

    heap->Release(addr, nullptr);
  }
}

TEST_CASE("Heap allocation rounds alignment up to page size", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  SECTION("Small alignment rounds to page size") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        4096, 32, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);

    CHECK((addr % 4096) == 0);

    heap->Release(addr, nullptr);
  }

  SECTION("Large alignment is respected") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        4096, 65536, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);

    CHECK((addr % 65536) == 0);

    heap->Release(addr, nullptr);
  }
}

TEST_CASE("Bottom-up allocation starts after reserved first 64KB", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  CHECK(addr >= 0x10000);

  heap->Release(addr, nullptr);
}

TEST_CASE("Top-down allocation returns high addresses", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t addr_bottom = 0;
  uint32_t addr_top = 0;

  heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr_bottom);

  heap->Alloc(4096, 4096,
              rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
              rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, true, &addr_top);

  CHECK(addr_top > addr_bottom);

  CHECK(addr_top > 0x1F000000);

  heap->Release(addr_bottom, nullptr);
  heap->Release(addr_top, nullptr);
}

TEST_CASE("AllocFixed allocates at exact address", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t target = 0x20000000;

  bool result =
      heap->AllocFixed(target, 4096, 4096,
                       rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  REQUIRE(result);

  rex::memory::HeapAllocationInfo info{};
  REQUIRE(heap->QueryRegionInfo(target, &info));
  CHECK(info.base_address == target);
  CHECK(info.state != 0);

  heap->Release(target, nullptr);
}

TEST_CASE("AllocFixed reserve-only fails on already-reserved region", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t target = 0x21000000;

  bool first = heap->AllocFixed(target, 4096, 4096, rex::memory::kMemoryAllocationReserve,
                                rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  REQUIRE(first);

  bool second =
      heap->AllocFixed(target, 4096, 4096, rex::memory::kMemoryAllocationReserve,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  CHECK_FALSE(second);

  heap->Release(target, nullptr);
}

TEST_CASE("AllocFixed commit on reserved region succeeds", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t target = 0x21100000;

  bool reserve =
      heap->AllocFixed(target, 4096, 4096, rex::memory::kMemoryAllocationReserve,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  REQUIRE(reserve);

  bool commit =
      heap->AllocFixed(target, 4096, 4096, rex::memory::kMemoryAllocationCommit,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  CHECK(commit);

  heap->Release(target, nullptr);
}

TEST_CASE("Protect changes page protection and returns old value", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  SECTION("Change to read-only") {
    uint32_t old_protect = 0;
    bool protect_result = heap->Protect(addr, 4096, rex::memory::kMemoryProtectRead, &old_protect);
    REQUIRE(protect_result);

    CHECK(old_protect == (rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite));

    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));
    CHECK(info.protect == rex::memory::kMemoryProtectRead);
  }

  heap->Release(addr, nullptr);
}

TEST_CASE("QueryRegionInfo returns correct allocation info", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096 * 4, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  SECTION("Query at allocation base") {
    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));

    CHECK(info.base_address == addr);
    CHECK(info.allocation_size == 4096 * 4);
    CHECK(info.region_size == 4096 * 4);
    CHECK(info.protect == (rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite));
    CHECK(info.state != 0);
  }

  SECTION("Query in middle of allocation") {
    uint32_t mid = addr + 4096 * 2;
    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(mid, &info));

    CHECK(info.base_address == mid);

    CHECK(info.allocation_size == 4096 * 4);

    CHECK(info.region_size == 4096 * 2);
  }

  heap->Release(addr, nullptr);
}

TEST_CASE("Release frees memory for reallocation", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x22000000));
  REQUIRE(heap != nullptr);

  uint32_t target = 0x22000000;

  bool alloc1 =
      heap->AllocFixed(target, 4096, 4096,
                       rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  REQUIRE(alloc1);

  uint32_t released_size = 0;
  bool release = heap->Release(target, &released_size);
  REQUIRE(release);
  CHECK(released_size == 4096);

  bool alloc2 =
      heap->AllocFixed(target, 4096, 4096,
                       rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  CHECK(alloc2);

  heap->Release(target, nullptr);
}

TEST_CASE("LookupHeap returns correct heap for address", "[memory][heap]") {
  auto& memory = GetTestMemory();

  SECTION("Address in v00000000 range") {
    auto* heap = memory.LookupHeap(0x10000000);
    REQUIRE(heap != nullptr);
  }

  SECTION("Address in v40000000 range") {
    auto* heap = memory.LookupHeap(0x50000000);
    REQUIRE(heap != nullptr);
  }

  SECTION("Address in v80000000 range (XEX)") {
    auto* heap = memory.LookupHeap(0x82000000);
    REQUIRE(heap != nullptr);
  }

  SECTION("Address in stack range returns nullptr") {
    auto* heap = memory.LookupHeap(0x7F000000);
    CHECK(heap == nullptr);
  }
}

TEST_CASE("64KB page heap rounds to 64KB boundaries", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x50000000));
  REQUIRE(heap != nullptr);

  SECTION("Small size rounds to 64KB") {
    uint32_t addr = 0;
    bool result = heap->Alloc(
        4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
        rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
    REQUIRE(result);

    rex::memory::HeapAllocationInfo info{};
    REQUIRE(heap->QueryRegionInfo(addr, &info));

    CHECK(info.allocation_size == 65536);

    CHECK((addr % 65536) == 0);

    heap->Release(addr, nullptr);
  }
}

TEST_CASE("Decommit removes commit flag but keeps reservation", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  rex::memory::HeapAllocationInfo info_before{};
  REQUIRE(heap->QueryRegionInfo(addr, &info_before));
  CHECK((info_before.state & rex::memory::kMemoryAllocationCommit) != 0);
  CHECK((info_before.state & rex::memory::kMemoryAllocationReserve) != 0);

  bool decommit = heap->Decommit(addr, 4096);
  REQUIRE(decommit);

  rex::memory::HeapAllocationInfo info_after{};
  REQUIRE(heap->QueryRegionInfo(addr, &info_after));
  CHECK((info_after.state & rex::memory::kMemoryAllocationCommit) == 0);
  CHECK((info_after.state & rex::memory::kMemoryAllocationReserve) != 0);

  heap->Release(addr, nullptr);
}

TEST_CASE("Decommit partial region", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096 * 4, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  bool decommit = heap->Decommit(addr + 4096, 4096 * 2);
  REQUIRE(decommit);

  rex::memory::HeapAllocationInfo info_first{};
  REQUIRE(heap->QueryRegionInfo(addr, &info_first));
  CHECK((info_first.state & rex::memory::kMemoryAllocationCommit) != 0);

  rex::memory::HeapAllocationInfo info_mid{};
  REQUIRE(heap->QueryRegionInfo(addr + 4096, &info_mid));
  CHECK((info_mid.state & rex::memory::kMemoryAllocationCommit) == 0);

  rex::memory::HeapAllocationInfo info_last{};
  REQUIRE(heap->QueryRegionInfo(addr + 4096 * 3, &info_last));
  CHECK((info_last.state & rex::memory::kMemoryAllocationCommit) != 0);

  heap->Release(addr, nullptr);
}

TEST_CASE("Decommit-recommit cycle on 64KB heap (real usage pattern)", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x50000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      65536, 65536, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  bool decommit = heap->Decommit(addr, 65536);
  REQUIRE(decommit);

  rex::memory::HeapAllocationInfo info{};
  REQUIRE(heap->QueryRegionInfo(addr, &info));
  CHECK(info.state == rex::memory::kMemoryAllocationReserve);

  bool recommit =
      heap->AllocFixed(addr, 65536, 65536, rex::memory::kMemoryAllocationCommit,
                       rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite);
  REQUIRE(recommit);

  rex::memory::HeapAllocationInfo info_after{};
  REQUIRE(heap->QueryRegionInfo(addr, &info_after));
  CHECK((info_after.state & rex::memory::kMemoryAllocationCommit) != 0);

  heap->Release(addr, nullptr);
}

TEST_CASE("Repeated decommit of same page succeeds (idempotent)", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x50000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      65536, 65536, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  bool decommit1 = heap->Decommit(addr, 65536);
  REQUIRE(decommit1);

  bool decommit2 = heap->Decommit(addr, 65536);
  CHECK(decommit2);

  bool decommit3 = heap->Decommit(addr, 65536);
  CHECK(decommit3);

  heap->Release(addr, nullptr);
}

TEST_CASE("Decommit on 64KB heap uses 64KB granularity", "[memory][heap]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0x50000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      65536, 65536, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  bool decommit = heap->Decommit(addr, 4096);
  REQUIRE(decommit);

  rex::memory::HeapAllocationInfo info{};
  REQUIRE(heap->QueryRegionInfo(addr, &info));

  CHECK((info.state & rex::memory::kMemoryAllocationCommit) == 0);

  heap->Release(addr, nullptr);
}

TEST_CASE("TranslateVirtual returns valid host pointer", "[memory][translation]") {
  auto& memory = GetTestMemory();

  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t guest_addr = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &guest_addr);
  REQUIRE(result);

  uint8_t* host_ptr = memory.TranslateVirtual(guest_addr);
  REQUIRE(host_ptr != nullptr);

  host_ptr[0] = 0xAB;
  CHECK(host_ptr[0] == 0xAB);

  heap->Release(guest_addr, nullptr);
}

TEST_CASE("HostToGuestVirtual roundtrip", "[memory][translation]") {
  auto& memory = GetTestMemory();

  auto* heap = MutableHeap(memory.LookupHeap(0x10000000));
  REQUIRE(heap != nullptr);

  uint32_t original_guest = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &original_guest);
  REQUIRE(result);

  uint8_t* host_ptr = memory.TranslateVirtual(original_guest);
  uint32_t back_to_guest = memory.HostToGuestVirtual(host_ptr);

  CHECK(back_to_guest == original_guest);

  heap->Release(original_guest, nullptr);
}

TEST_CASE("TranslatePhysical masks to 29 bits", "[memory][translation]") {
  auto& memory = GetTestMemory();

  uint8_t* ptr_low = memory.TranslatePhysical(0x00001000);
  uint8_t* ptr_high = memory.TranslatePhysical(0xA0001000);

  CHECK(ptr_low == ptr_high);
}

TEST_CASE("Physical heap vA0000000 (64KB pages, cached)", "[memory][physical]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0xA0000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  CHECK(addr >= 0xA0000000);
  CHECK(addr < 0xC0000000);

  CHECK((addr % 65536) == 0);

  heap->Release(addr, nullptr);
}

TEST_CASE("Physical heap vC0000000 (16MB pages, uncached)", "[memory][physical]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0xC0000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result =
      heap->Alloc(16 * 1024 * 1024, 16 * 1024 * 1024,
                  rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
                  rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  CHECK(addr >= 0xC0000000);
  CHECK(addr < 0xE0000000);

  heap->Release(addr, nullptr);
}

TEST_CASE("Physical heap vE0000000 (4KB pages, write-combine)", "[memory][physical]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0xE0000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = 0;
  bool result = heap->Alloc(
      4096, 4096, rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit,
      rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite, false, &addr);
  REQUIRE(result);

  CHECK(addr >= 0xE0000000);
  CHECK(addr < 0xFFD00000);

  CHECK((addr % 4096) == 0);

  heap->Release(addr, nullptr);
}

TEST_CASE("LookupHeapByType selects correct heap", "[memory][heap]") {
  auto& memory = GetTestMemory();

  SECTION("Virtual heap with 4KB pages") {
    auto* heap = memory.LookupHeapByType(false, 4096);
    REQUIRE(heap != nullptr);
  }

  SECTION("Virtual heap with 64KB pages") {
    auto* heap = memory.LookupHeapByType(false, 65536);
    REQUIRE(heap != nullptr);
  }

  SECTION("Physical heap with 4KB pages") {
    auto* heap = memory.LookupHeapByType(true, 4096);
    REQUIRE(heap != nullptr);
  }

  SECTION("Physical heap with 64KB pages") {
    auto* heap = memory.LookupHeapByType(true, 65536);
    REQUIRE(heap != nullptr);
  }

  SECTION("Physical heap with 16MB pages") {
    auto* heap = memory.LookupHeapByType(true, 16 * 1024 * 1024);
    REQUIRE(heap != nullptr);
  }
}

namespace {

constexpr uint32_t kReserveCommit =
    rex::memory::kMemoryAllocationReserve | rex::memory::kMemoryAllocationCommit;
constexpr uint32_t kReadWrite = rex::memory::kMemoryProtectRead | rex::memory::kMemoryProtectWrite;

uint32_t AllocInRange(rex::memory::BaseHeap* heap, uint32_t low, uint32_t high, uint32_t size,
                      uint32_t alignment, bool top_down) {
  uint32_t addr = 0;
  REQUIRE(
      heap->AllocRange(low, high, size, alignment, kReserveCommit, kReadWrite, top_down, &addr));
  CHECK(addr >= low);
  CHECK(uint64_t(addr) + size - 1 <= high);
  return addr;
}

}

TEST_CASE("AllocRange keeps allocations below an unaligned ceiling", "[memory][heap]") {
  auto* heap = MutableHeap(GetTestMemory().LookupHeap(0x3E000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = AllocInRange(heap, 0x3E000000, 0x3E0F8000, 0x10000, 0x10000, true);
  CHECK(addr == 0x3E0E0000);
  heap->Release(addr, nullptr);

  addr = AllocInRange(heap, 0x3E000000, 0x3E0F8800, 0x1000, 0x1000, true);
  CHECK(addr == 0x3E0F7000);
  heap->Release(addr, nullptr);
}

TEST_CASE("AllocRange uses the last page of an inclusive ceiling", "[memory][heap]") {
  auto* heap = MutableHeap(GetTestMemory().LookupHeap(0x3E100000));
  REQUIRE(heap != nullptr);

  uint32_t addr = AllocInRange(heap, 0x3E100000, 0x3E10FFFF, 0x1000, 0x1000, true);
  CHECK(addr == 0x3E10F000);
  heap->Release(addr, nullptr);

  addr = AllocInRange(heap, 0x3E100000, 0x3E13FFFF, 0x10000, 0x10000, true);
  CHECK(addr == 0x3E130000);
  heap->Release(addr, nullptr);
}

TEST_CASE("AllocRange fits a window exactly the size of the request", "[memory][heap]") {
  auto* heap = MutableHeap(GetTestMemory().LookupHeap(0x3E200000));
  REQUIRE(heap != nullptr);

  for (bool top_down : {true, false}) {
    uint32_t addr = AllocInRange(heap, 0x3E200000, 0x3E20FFFF, 0x10000, 0x10000, top_down);
    CHECK(addr == 0x3E200000);
    heap->Release(addr, nullptr);
  }
}

TEST_CASE("AllocRange accepts a UINT32_MAX ceiling", "[memory][heap]") {
  auto* heap = MutableHeap(GetTestMemory().LookupHeap(0x3E300000));
  REQUIRE(heap != nullptr);

  uint32_t addr = AllocInRange(heap, 0x3E300000, 0xFFFFFFFF, 0x1000, 0x10000, false);
  CHECK(addr == 0x3E300000);
  heap->Release(addr, nullptr);
}

TEST_CASE("AllocRange fails when the window is too small", "[memory][heap]") {
  auto* heap = MutableHeap(GetTestMemory().LookupHeap(0x3E400000));
  REQUIRE(heap != nullptr);
  uint32_t addr = 0;

  SECTION("Window one page smaller than the request") {
    CHECK_FALSE(heap->AllocRange(0x3E400000, 0x3E40EFFF, 0x10000, 0x1000, kReserveCommit,
                                 kReadWrite, true, &addr));
  }

  SECTION("Window inside a single page") {
    CHECK_FALSE(heap->AllocRange(0x3E400000, 0x3E400800, 0x1000, 0x1000, kReserveCommit, kReadWrite,
                                 true, &addr));
  }
}

TEST_CASE("Physical AllocRange keeps allocations inside the requested range",
          "[memory][physical]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0xB0000000));
  REQUIRE(heap != nullptr);

  uint32_t addr = AllocInRange(heap, 0xB0000000, 0xB0FF8000, 0x10000, 0x10000, true);
  CHECK(memory.GetPhysicalAddress(addr) % 0x10000 == 0);
  heap->Release(addr, nullptr);
}

TEST_CASE("Physical heap vE0000000 aligns the physical address", "[memory][physical]") {
  auto& memory = GetTestMemory();
  auto* heap = MutableHeap(memory.LookupHeap(0xF2000000));
  REQUIRE(heap != nullptr);

  for (uint32_t alignment : {0x1000u, 0x8000u, 0x10000u}) {
    for (bool top_down : {true, false}) {
      INFO("alignment " << alignment << " top_down " << top_down);
      uint32_t addr = AllocInRange(heap, 0xF2000000, 0xF2FFFFFF, 0x10000, alignment, top_down);
      uint32_t physical = memory.GetPhysicalAddress(addr);
      CHECK(physical == addr - 0xE0000000 + 0x1000);
      CHECK(physical % alignment == 0);

      *memory.TranslateVirtual<uint8_t*>(addr) = 0x5A;
      CHECK(*memory.TranslatePhysical<uint8_t*>(physical) == 0x5A);
      heap->Release(addr, nullptr);
    }
  }

  uint32_t addr = 0;
  REQUIRE(heap->Alloc(0x280000, 0x8000, kReserveCommit, kReadWrite, true, &addr));
  CHECK(memory.GetPhysicalAddress(addr) % 0x8000 == 0);
  heap->Release(addr, nullptr);
}
