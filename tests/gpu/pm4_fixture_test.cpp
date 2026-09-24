/**
 * @file        pm4_fixture_test.cpp
 * @brief       PM4 command processor fixtures through the GPU plugin (RG-GDK-006)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdio>

#include <catch2/catch_test_macros.hpp>

#include "gpu_fixture.h"

namespace {

using rex::graphics::xenos::Endian;
using rex::testing::GpuFixture;

constexpr uint32_t kScratchReg0 = 0x0578;

std::unique_ptr<GpuFixture> CreateFixture() {
  std::string error;
  auto fixture = GpuFixture::Create(&error);
  if (fixture) {
    std::printf("GPU fixture: %s\n", fixture->Metadata().c_str());
  } else {
    std::fprintf(stderr, "GPU fixture host unavailable: %s\n", error.c_str());
  }
  return fixture;
}

}  // namespace

TEST_CASE("PM4 MEM_WRITE stores dwords with the requested swap", "[gpu][pm4]") {
  auto fixture = CreateFixture();
  if (!fixture) {
    SKIP("GPU fixture host unavailable");
  }
  uint32_t dest = fixture->AllocPhysical(0x100);
  fixture->Submit(GpuFixture::MemWrite(dest, {0x11223344, 0xAABBCCDD}, Endian::k8in32));
  fixture->Submit(GpuFixture::MemWrite(dest + 8, {0x11223344}, Endian::kNone));
  REQUIRE(fixture->Flush());
  CHECK(fixture->ReadDword(dest) == 0x11223344);
  CHECK(fixture->ReadDword(dest + 4) == 0xAABBCCDD);
  // Without a swap the host-order store lands byte-reversed for the guest.
  CHECK(fixture->ReadDword(dest + 8) == 0x44332211);
}

TEST_CASE("PM4 type-0 register write reads back through REG_TO_MEM", "[gpu][pm4]") {
  auto fixture = CreateFixture();
  if (!fixture) {
    SKIP("GPU fixture host unavailable");
  }
  uint32_t dest = fixture->AllocPhysical(0x100);
  fixture->Submit(GpuFixture::SetRegisters(kScratchReg0, {0xC0FFEE01}));
  fixture->Submit(GpuFixture::RegToMem(kScratchReg0, dest, Endian::k8in32));
  REQUIRE(fixture->Flush());
  CHECK(fixture->ReadDword(dest) == 0xC0FFEE01);
}

TEST_CASE("PM4 INDIRECT_BUFFER executes the nested buffer in order", "[gpu][pm4]") {
  auto fixture = CreateFixture();
  if (!fixture) {
    SKIP("GPU fixture host unavailable");
  }
  uint32_t dest = fixture->AllocPhysical(0x100);
  uint32_t indirect = fixture->AllocPhysical(0x100);
  std::vector<uint32_t> nested = GpuFixture::MemWrite(dest, {1, 2}, Endian::k8in32);
  fixture->WriteDwords(indirect, nested);
  fixture->Submit(GpuFixture::IndirectBuffer(indirect, uint32_t(nested.size())));
  // Overwrites the nested buffer's second dword only if it ran first.
  fixture->Submit(GpuFixture::MemWrite(dest + 4, {3}, Endian::k8in32));
  REQUIRE(fixture->Flush());
  CHECK(fixture->ReadDword(dest) == 1);
  CHECK(fixture->ReadDword(dest + 4) == 3);
}

TEST_CASE("PM4 fences complete in submission order", "[gpu][pm4]") {
  auto fixture = CreateFixture();
  if (!fixture) {
    SKIP("GPU fixture host unavailable");
  }
  uint32_t dest = fixture->AllocPhysical(0x100);
  for (uint32_t i = 1; i <= 16; ++i) {
    fixture->Submit(GpuFixture::MemWrite(dest, {i}, Endian::k8in32));
    REQUIRE(fixture->Flush());
    CHECK(fixture->ReadDword(dest) == i);
  }
}
