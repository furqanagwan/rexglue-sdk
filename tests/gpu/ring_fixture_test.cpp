/**
 * @file        ring_fixture_test.cpp
 * @brief       Primary ring read pointer publication and wrap (RG-GDK-011)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <chrono>
#include <cstdint>
#include <functional>
#include <thread>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"

namespace {

namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;

// A NOP packet of `dwords` dwords in total.
void AppendNop(std::vector<uint32_t>& burst, uint32_t dwords) {
  burst.push_back(xenos::MakePacketType3(xenos::PM4_NOP, uint16_t(dwords - 1)));
  burst.insert(burst.end(), dwords - 1, 0xDEADBEEF);
}

// WAIT_REG_MEM until the big-endian dword at `address` equals `value`.
void AppendWaitMemEqual(std::vector<uint32_t>& burst, uint32_t address, uint32_t value) {
  constexpr uint32_t kMemorySpace = 0x10;
  constexpr uint32_t kFunctionEqual = 0x3;
  burst.insert(burst.end(),
               {xenos::MakePacketType3(xenos::PM4_WAIT_REG_MEM, 5), kMemorySpace | kFunctionEqual,
                address | uint32_t(xenos::Endian::k8in32), value, 0xFFFFFFFF,
                // Poll interval; 0x100 per millisecond slept.
                0x100});
}

bool WaitFor(const std::function<bool()>& condition) {
  auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (!condition()) {
    if (std::chrono::steady_clock::now() > deadline) {
      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  return true;
}

}  // namespace

// has207/xenia-edge 29fcaeac3: the guest frees ring space by polling the read
// pointer write-back. Published only at the end of a burst, a burst that waits
// on the guest partway through never hands back the space it already consumed.
TEST_CASE("Read pointer write-back advances inside a burst blocked on the guest", "[gpu][ring]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  // RB_BLKSZ 2: every 4 quadwords, 8 dwords.
  uint32_t writeback = fixture->EnableReadPointerWriteBack(2);
  uint32_t start = fixture->write_index();
  uint32_t gate = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(gate, {0});

  std::vector<uint32_t> burst;
  for (uint32_t i = 0; i < 32; ++i) {
    AppendNop(burst, 10);
  }
  uint32_t wait_index = start + uint32_t(burst.size());
  AppendWaitMemEqual(burst, gate, 1);
  AppendNop(burst, 10);
  REQUIRE(fixture->Submit(burst));

  // While the command processor sits in the WAIT_REG_MEM, the guest must see
  // everything before it consumed, to within one RB_BLKSZ stride.
  bool published = WaitFor([&]() {
    uint32_t read_index = fixture->ReadDword(writeback);
    return read_index > start && read_index + 8 >= wait_index;
  });
  CHECK(published);
  INFO("write-back " << fixture->ReadDword(writeback) << ", wait at " << wait_index);
  CHECK(fixture->ReadDword(writeback) <= wait_index + 6);

  fixture->WriteDwords(gate, {1});
  REQUIRE(fixture->Flush());
  // The end of every burst publishes the exact position.
  CHECK(fixture->ReadDword(writeback) == fixture->write_index());
}

TEST_CASE("The ring wraps under bursts larger than the ring", "[gpu][ring]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  // The usual RB_BLKSZ 6: every 128 dwords.
  uint32_t writeback = fixture->EnableReadPointerWriteBack(6);
  uint32_t counter = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(counter, {0});

  // Bursts of 3/4 of the ring, each a run of NOPs ending in a MEM_WRITE of its
  // sequence number, five ring lengths in total. Each Submit waits on the
  // write-back for room and wraps the write pointer, as D3D does.
  uint32_t burst_dwords = fixture->ring_dwords() * 3 / 4;
  uint32_t burst_count = 5 * 4 / 3 + 1;
  for (uint32_t sequence = 1; sequence <= burst_count; ++sequence) {
    std::vector<uint32_t> burst;
    while (burst.size() + 16 + 3 < burst_dwords) {
      AppendNop(burst, 16);
    }
    auto write = GpuFixture::MemWrite(counter, {sequence}, xenos::Endian::k8in32);
    burst.insert(burst.end(), write.begin(), write.end());
    INFO("burst " << sequence);
    REQUIRE(fixture->Submit(burst));
  }
  REQUIRE(fixture->Flush());
  CHECK(fixture->ReadDword(counter) == burst_count);
  CHECK(fixture->ReadDword(writeback) == fixture->write_index());
}
