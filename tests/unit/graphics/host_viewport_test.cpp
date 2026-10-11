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

void SetFloat(RegisterFile& regs, uint32_t index, float value) {
  std::memcpy(&regs[index], &value, sizeof(value));
}

draw_util::ViewportInfo TileViewport(int32_t window_x_offset) {
  RegisterFile regs;
  std::memset(regs.values, 0, sizeof(regs.values));
  reg::PA_CL_VTE_CNTL vte = {};
  vte.vport_x_scale_ena = 1;
  vte.vport_x_offset_ena = 1;
  vte.vport_y_scale_ena = 1;
  vte.vport_y_offset_ena = 1;
  regs[XE_GPU_REG_PA_CL_VTE_CNTL] = vte.value;
  SetFloat(regs, XE_GPU_REG_PA_CL_VPORT_XSCALE, 640.0f);
  SetFloat(regs, XE_GPU_REG_PA_CL_VPORT_XOFFSET, 640.0f);
  SetFloat(regs, XE_GPU_REG_PA_CL_VPORT_YSCALE, -360.0f);
  SetFloat(regs, XE_GPU_REG_PA_CL_VPORT_YOFFSET, 360.0f);
  reg::PA_SU_SC_MODE_CNTL mode = {};
  mode.vtx_window_offset_enable = 1;
  regs[XE_GPU_REG_PA_SU_SC_MODE_CNTL] = mode.value;
  reg::PA_SC_WINDOW_OFFSET window = {};
  window.window_x_offset = window_x_offset;
  regs[XE_GPU_REG_PA_SC_WINDOW_OFFSET] = window.value;
  reg::PA_SU_VTX_CNTL vtx = {};
  vtx.pix_center = xenos::PixelCenter::kOGLHalf;
  regs[XE_GPU_REG_PA_SU_VTX_CNTL] = vtx.value;

  draw_util::ViewportInfo info;
  draw_util::GetHostViewportInfo(regs, 1, 1, false, 8192, 8192, false, {}, false, false, false,
                                 info);
  return info;
}

}

TEST_CASE("A tile drawn at a negative window offset keeps the full viewport", "[graphics][draw]") {
  const auto left = TileViewport(0);
  const auto right = TileViewport(-608);

  CHECK(left.xy_offset[0] == 0);
  CHECK(left.xy_extent[0] == 1280);
  CHECK(right.xy_offset[0] == -608);
  CHECK(right.xy_extent[0] == 1280);
  CHECK(right.ndc_scale[0] == Approx(left.ndc_scale[0]));
  CHECK(right.ndc_offset[0] == Approx(left.ndc_offset[0]));
}
