// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <cstring>

#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>

using namespace rex::graphics;

namespace {

uint32_t PackXY(uint32_t x, uint32_t y) {
  return x | (y << 16);
}

struct TileRegisters {
  RegisterFile regs;

  explicit TileRegisters(int32_t window_x_offset, int32_t window_y_offset) {
    std::memset(regs.values, 0, sizeof(regs.values));
    reg::RB_SURFACE_INFO surface = {};
    surface.surface_pitch = 1280;
    regs[XE_GPU_REG_RB_SURFACE_INFO] = surface.value;
    reg::PA_SU_SC_MODE_CNTL mode = {};
    mode.vtx_window_offset_enable = 1;
    regs[XE_GPU_REG_PA_SU_SC_MODE_CNTL] = mode.value;
    reg::PA_SC_WINDOW_OFFSET window = {};
    window.window_x_offset = window_x_offset;
    window.window_y_offset = window_y_offset;
    regs[XE_GPU_REG_PA_SC_WINDOW_OFFSET] = window.value;
    regs[XE_GPU_REG_PA_SC_WINDOW_SCISSOR_TL] = PackXY(0, 352);
    regs[XE_GPU_REG_PA_SC_WINDOW_SCISSOR_BR] = PackXY(1280, 720);
    regs[XE_GPU_REG_PA_SC_SCREEN_SCISSOR_TL] = PackXY(0, 0);
    regs[XE_GPU_REG_PA_SC_SCREEN_SCISSOR_BR] = PackXY(1280, 720);
  }

  int32_t OffsetTiles(bool host_render_targets, bool& kept_in_viewport) const {
    reg::RB_DEPTHCONTROL depth = {};
    depth.z_enable = 1;
    return draw_util::GetWindowOffsetTiles(regs, depth, 0, host_render_targets, kept_in_viewport);
  }
};

}

TEST_CASE("A window offset moves an EDRAM base by whole tiles and wraps", "[graphics][draw]") {
  CHECK(draw_util::AddWindowOffsetToEdramBase(400, -352, false) == 48);
  CHECK(draw_util::AddWindowOffsetToEdramBase(100, -352, false) == 2048 + 100 - 352);
  CHECK(draw_util::AddWindowOffsetToEdramBase(800, -352, true) == 96);
  CHECK(draw_util::AddWindowOffsetToEdramBase(400, 0, true) == 400);
}

TEST_CASE("A whole-tile upward window offset goes into the EDRAM base", "[graphics][draw]") {
  REQUIRE(rex::cvar::SetFlagByName("window_offset_in_edram", "true"));
  bool kept_in_viewport = true;
  CHECK(TileRegisters(0, -352).OffsetTiles(true, kept_in_viewport) == -352);
  CHECK_FALSE(kept_in_viewport);
}

TEST_CASE("Window offsets that EDRAM bases can't express stay in the viewport",
          "[graphics][draw]") {
  REQUIRE(rex::cvar::SetFlagByName("window_offset_in_edram", "true"));
  bool kept_in_viewport = false;
  SECTION("Sideways with host render targets") {
    CHECK(TileRegisters(-640, -352).OffsetTiles(true, kept_in_viewport) == 0);
    CHECK(kept_in_viewport);
  }
  SECTION("Not a whole tile") {
    CHECK(TileRegisters(0, -360).OffsetTiles(true, kept_in_viewport) == 0);
    CHECK(kept_in_viewport);
  }
  SECTION("Positive") {
    CHECK(TileRegisters(0, 352).OffsetTiles(true, kept_in_viewport) == 0);
    CHECK_FALSE(kept_in_viewport);
  }
  SECTION("Turned off") {
    REQUIRE(rex::cvar::SetFlagByName("window_offset_in_edram", "false"));
    CHECK(TileRegisters(0, -352).OffsetTiles(true, kept_in_viewport) == 0);
    CHECK_FALSE(kept_in_viewport);
    REQUIRE(rex::cvar::SetFlagByName("window_offset_in_edram", "true"));
  }
}

TEST_CASE("With the offset in EDRAM the scissor stays in the tile's own space",
          "[graphics][draw]") {
  TileRegisters tile(0, -352);
  draw_util::Scissor in_viewport;
  draw_util::GetScissor(tile.regs, in_viewport, true, false);
  draw_util::Scissor in_edram;
  draw_util::GetScissor(tile.regs, in_edram, true, true);
  CHECK(in_viewport.offset[1] == 0);
  CHECK(in_viewport.extent[1] == 368);
  CHECK(in_edram.offset[1] == 352);
  CHECK(in_edram.extent[1] == 368);
}
