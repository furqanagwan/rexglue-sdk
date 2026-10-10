/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-canary 3d233a5b2 (PR #1218)
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include <rex/graphics/xenos.h>

namespace rex::graphics {

struct XenosZPDReport {
  enum Counter : uint32_t {
    kTotal,
    kZFail,
    kZPass,
    kStencilFail,
    kCount,
  };
  static constexpr uint32_t kCounterSizeBytes = kCount * sizeof(uint32_t);

  uint64_t z_fail = 0;
  uint64_t z_pass = 0;
  uint64_t stencil_fail = 0;
  uint64_t total() const { return z_fail + z_pass + stencil_fail; }

  bool operator==(const XenosZPDReport& other) const = default;

  XenosZPDReport& operator+=(const XenosZPDReport& other) {
    z_fail += other.z_fail;
    z_pass += other.z_pass;
    stencil_fail += other.stencil_fail;
    return *this;
  }

  static XenosZPDReport FromCounterSlot(const uint32_t* slot) {
    XenosZPDReport report;
    report.z_fail = slot[kZFail];
    report.z_pass = slot[kZPass];
    report.stencil_fail = slot[kStencilFail];
    return report;
  }

  static XenosZPDReport FromNativeQueryAndTotal(uint64_t passed, uint64_t coverage) {
    XenosZPDReport report;
    report.z_pass = passed;
    report.z_fail = std::max(coverage, passed) - passed;
    return report;
  }

  static XenosZPDReport FromNativeQuery(uint64_t passed) {
    XenosZPDReport report;
    report.z_pass = passed;
    return report;
  }

  XenosZPDReport Normalized(uint32_t scale_area) const {
    auto normalize = [scale_area](uint64_t count) {
      return scale_area <= 1 || !count
                 ? count
                 : std::max<uint64_t>(1, (count + (scale_area >> 1)) / scale_area);
    };
    XenosZPDReport report;
    report.z_fail = normalize(z_fail);
    report.z_pass = normalize(z_pass);
    report.stencil_fail = normalize(stencil_fail);
    return report;
  }

  void WriteTo(xenos::xe_gpu_depth_sample_counts* guest) const {
    auto lane_a = [](uint64_t count) { return uint32_t(count) - (uint32_t(count) >> 1); };
    auto lane_b = [](uint64_t count) { return uint32_t(count) >> 1; };
    guest->Total_A = lane_a(total());
    guest->Total_B = lane_b(total());
    guest->ZFail_A = lane_a(z_fail);
    guest->ZFail_B = lane_b(z_fail);
    xenos::xe_gpu_depth_sample_counts values;
    values.ZPass_A = lane_a(z_pass);
    values.ZPass_B = lane_b(z_pass);
    values.StencilFail_A = lane_a(stencil_fail);
    values.StencilFail_B = lane_b(stencil_fail);
    std::memcpy(&guest->ZPass_A, &values.ZPass_A,
                sizeof(values) - offsetof(xenos::xe_gpu_depth_sample_counts, ZPass_A));
  }
};

}
