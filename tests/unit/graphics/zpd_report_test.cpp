/**
 * @file        zpd_report_test.cpp
 * @brief       ZPD sample counter report layout and arithmetic (RG-GDK-010)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdint>
#include <cstring>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/xenos_zpd_report.h>

using rex::graphics::XenosZPDReport;
using rex::graphics::xenos::xe_gpu_depth_sample_counts;

namespace {

uint64_t Sum(uint32_t a, uint32_t b) {
  return uint64_t(a) + uint64_t(b);
}

}  // namespace

TEST_CASE("ZPD report splits each counter evenly across the A and B lanes", "[zpd]") {
  XenosZPDReport report;
  report.z_pass = 7;
  report.z_fail = 4;
  report.stencil_fail = 1;
  xe_gpu_depth_sample_counts guest;
  std::memset(&guest, 0xCD, sizeof(guest));
  report.WriteTo(&guest);

  // A gets the odd sample; D3D sums the two.
  CHECK(guest.ZPass_A == 4u);
  CHECK(guest.ZPass_B == 3u);
  CHECK(guest.ZFail_A == 2u);
  CHECK(guest.ZFail_B == 2u);
  CHECK(guest.StencilFail_A == 1u);
  CHECK(guest.StencilFail_B == 0u);
  CHECK(Sum(guest.Total_A, guest.Total_B) == 12u);
  // 425307EC masks each lane to 24 bits before summing, so neither lane may
  // carry the whole count.
  report = XenosZPDReport::FromNativeQuery(0x01000000);
  report.WriteTo(&guest);
  CHECK(guest.ZPass_A == 0x00800000u);
  CHECK(guest.ZPass_B == 0x00800000u);
}

TEST_CASE("ZPD report keeps the low 32 bits so END - BEGIN survives a wrap", "[zpd]") {
  // The hardware counters are 32-bit and free-running; D3D subtracts the BEGIN
  // snapshot from the END one, so a wrap in between still gives the delta.
  XenosZPDReport begin = XenosZPDReport::FromNativeQuery(0xFFFFFFF0ull);
  XenosZPDReport end = begin;
  end += XenosZPDReport::FromNativeQuery(0x30);
  xe_gpu_depth_sample_counts guest_begin, guest_end;
  begin.WriteTo(&guest_begin);
  end.WriteTo(&guest_end);
  uint32_t begin_sum = uint32_t(guest_begin.ZPass_A) + uint32_t(guest_begin.ZPass_B);
  uint32_t end_sum = uint32_t(guest_end.ZPass_A) + uint32_t(guest_end.ZPass_B);
  CHECK(uint32_t(end_sum - begin_sum) == 0x30u);
}

TEST_CASE("ZPD report normalizes host samples by the draw resolution scale", "[zpd]") {
  XenosZPDReport host = XenosZPDReport::FromNativeQuery(6 * 100);
  CHECK(host.Normalized(1).z_pass == 600u);
  CHECK(host.Normalized(6).z_pass == 100u);
  // Rounded to nearest.
  CHECK(XenosZPDReport::FromNativeQuery(9).Normalized(6).z_pass == 2u);
  CHECK(XenosZPDReport::FromNativeQuery(8).Normalized(6).z_pass == 1u);
  // A visible sliver never normalizes to occluded.
  CHECK(XenosZPDReport::FromNativeQuery(1).Normalized(9).z_pass == 1u);
  CHECK(XenosZPDReport::FromNativeQuery(0).Normalized(9).z_pass == 0u);
}

TEST_CASE("ZPD report writes the lanes D3D polls on last, in one copy", "[zpd]") {
  // GetData polls ZPass and QueryBatch Lock polls ZPass_A or StencilFail_B, so
  // they're the tail of the structure and written after Total and ZFail.
  CHECK(offsetof(xe_gpu_depth_sample_counts, ZPass_A) == 16u);
  CHECK(offsetof(xe_gpu_depth_sample_counts, StencilFail_B) == 28u);
  xe_gpu_depth_sample_counts guest;
  std::memset(&guest, 0xFF, sizeof(guest));
  XenosZPDReport().WriteTo(&guest);
  const uint32_t* words = reinterpret_cast<const uint32_t*>(&guest);
  for (uint32_t i = 0; i < 8; ++i) {
    CHECK(words[i] == 0u);
  }
}
