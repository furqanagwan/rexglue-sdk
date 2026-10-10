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

void AppendNop(std::vector<uint32_t>& burst, uint32_t dwords) {
  burst.push_back(xenos::MakePacketType3(xenos::PM4_NOP, uint16_t(dwords - 1)));
  burst.insert(burst.end(), dwords - 1, 0xDEADBEEF);
}

void AppendWaitMemEqual(std::vector<uint32_t>& burst, uint32_t address, uint32_t value) {
  constexpr uint32_t kMemorySpace = 0x10;
  constexpr uint32_t kFunctionEqual = 0x3;
  burst.insert(burst.end(),
               {xenos::MakePacketType3(xenos::PM4_WAIT_REG_MEM, 5), kMemorySpace | kFunctionEqual,
                address | uint32_t(xenos::Endian::k8in32), value, 0xFFFFFFFF,

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

}

TEST_CASE("Read pointer write-back advances inside a burst blocked on the guest", "[gpu][ring]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }

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

  bool published = WaitFor([&]() {
    uint32_t read_index = fixture->ReadDword(writeback);
    return read_index > start && read_index + 8 >= wait_index;
  });
  CHECK(published);
  INFO("write-back " << fixture->ReadDword(writeback) << ", wait at " << wait_index);
  CHECK(fixture->ReadDword(writeback) <= wait_index + 6);

  fixture->WriteDwords(gate, {1});
  REQUIRE(fixture->Flush());

  CHECK(fixture->ReadDword(writeback) == fixture->write_index());
}

TEST_CASE("The ring wraps under bursts larger than the ring", "[gpu][ring]") {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }

  uint32_t writeback = fixture->EnableReadPointerWriteBack(6);
  uint32_t counter = fixture->AllocPhysical(0x1000);
  fixture->WriteDwords(counter, {0});

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
