// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstring>

#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>

using namespace rex::graphics;
using Catch::Approx;

namespace {

bool SamePosition(const int8_t* a, const int8_t* b) {
  return a[0] == b[0] && a[1] == b[1];
}

draw_util::ViewportInfo MsaaViewport(uint32_t scale, bool xenos_sample_positions) {
  RegisterFile regs;
  std::memset(regs.values, 0, sizeof(regs.values));
  reg::RB_SURFACE_INFO surface = {};
  surface.surface_pitch = 1280;
  surface.msaa_samples = xenos::MsaaSamples::k4X;
  regs[XE_GPU_REG_RB_SURFACE_INFO] = surface.value;
  reg::PA_CL_VTE_CNTL vte = {};
  vte.vport_x_scale_ena = 1;
  vte.vport_x_offset_ena = 1;
  vte.vport_y_scale_ena = 1;
  vte.vport_y_offset_ena = 1;
  regs[XE_GPU_REG_PA_CL_VTE_CNTL] = vte.value;
  auto set_float = [&regs](uint32_t index, float value) {
    std::memcpy(&regs[index], &value, sizeof(value));
  };
  set_float(XE_GPU_REG_PA_CL_VPORT_XSCALE, 640.0f);
  set_float(XE_GPU_REG_PA_CL_VPORT_XOFFSET, 640.375f);
  set_float(XE_GPU_REG_PA_CL_VPORT_YSCALE, -360.0f);
  set_float(XE_GPU_REG_PA_CL_VPORT_YOFFSET, 360.375f);
  reg::PA_SU_VTX_CNTL vtx = {};
  vtx.pix_center = xenos::PixelCenter::kOGLHalf;
  regs[XE_GPU_REG_PA_SU_VTX_CNTL] = vtx.value;
  draw_util::ViewportInfo info;
  draw_util::GetHostViewportInfo(regs, scale, scale, false, 8192, 8192, false, {}, false, false,
                                 false, info, false, xenos_sample_positions);
  return info;
}

}

TEST_CASE("Host samples get the Xenos sample positions in each host order",
          "[graphics][draw][msaa]") {
  int8_t positions[4][2];
  SECTION("4x host render targets keep the Xenos order") {
    REQUIRE(draw_util::GetHostSampleXenosPositions(xenos::MsaaSamples::k4X, true, false,
                                                   positions) == 4);
    for (uint32_t i = 0; i < 4; ++i) {
      CHECK(SamePosition(positions[i], draw_util::kXenosSamplePositions4x[i]));
    }
  }
  SECTION("4x with ROV swaps host samples 1 and 3") {
    REQUIRE(draw_util::GetHostSampleXenosPositions(xenos::MsaaSamples::k4X, true, true,
                                                   positions) == 4);
    CHECK(SamePosition(positions[1], draw_util::kXenosSamplePositions4x[3]));
    CHECK(SamePosition(positions[3], draw_util::kXenosSamplePositions4x[1]));
  }
  SECTION("Native 2x swaps the two samples") {
    REQUIRE(draw_util::GetHostSampleXenosPositions(xenos::MsaaSamples::k2X, true, false,
                                                   positions) == 2);
    CHECK(SamePosition(positions[0], draw_util::kXenosSamplePositions2x[1]));
    CHECK(SamePosition(positions[1], draw_util::kXenosSamplePositions2x[0]));
  }
  SECTION("2x drawn as 4x repeats the two samples") {
    REQUIRE(draw_util::GetHostSampleXenosPositions(xenos::MsaaSamples::k2X, false, false,
                                                   positions) == 4);
    CHECK(SamePosition(positions[0], draw_util::kXenosSamplePositions2x[0]));
    CHECK(SamePosition(positions[1], draw_util::kXenosSamplePositions2x[1]));
    CHECK(SamePosition(positions[2], draw_util::kXenosSamplePositions2x[0]));
    CHECK(SamePosition(positions[3], draw_util::kXenosSamplePositions2x[1]));
  }
}

TEST_CASE("A viewport offset onto a Xenos sample keeps that offset in host pixels when scaled",
          "[graphics][draw][msaa]") {
  CHECK(MsaaViewport(1, true).ndc_offset[0] == Approx(MsaaViewport(1, false).ndc_offset[0]));
  const auto host = MsaaViewport(2, false);
  const auto xenos = MsaaViewport(2, true);
  CHECK(xenos.ndc_offset[0] != Approx(host.ndc_offset[0]));
  CHECK(xenos.ndc_offset[1] != Approx(host.ndc_offset[1]));
  CHECK(xenos.ndc_scale[0] == Approx(host.ndc_scale[0]));
}
