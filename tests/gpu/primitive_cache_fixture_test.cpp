// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <bit>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/cvar.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;

struct RestoreCvars {
  ~RestoreCvars() {
    for (const char* name : {"render_target_path_d3d12", "async_shader_compilation",
                             "readback_resolve", "primitive_processor_cache_min_indices"}) {
      rex::cvar::ResetToDefault(name);
    }
  }
};

void DrawFan(GpuFixture& fixture, uint32_t indices) {
  const uint32_t one = std::bit_cast<uint32_t>(1.0f);
  REQUIRE(fixture.Submit(
      GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_256_X, {one, one, one, one})));
  reg::VGT_DRAW_INITIATOR draw{};
  draw.prim_type = xenos::PrimitiveType::kTriangleFan;
  draw.source_select = xenos::SourceSelect::kDMA;
  draw.index_size = xenos::IndexFormat::kInt32;
  draw.num_indices = 4;
  reg::VGT_DMA_SIZE dma{};
  dma.num_words = 4;
  dma.swap_mode = xenos::Endian::k8in32;
  REQUIRE(fixture.Submit(
      {xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 3), draw.value, indices, dma.value}));
}
}

TEST_CASE("Guest writes replace a cached triangle fan on the GPU", "[gpu][primitive]") {
  RestoreCvars restore;
  const char* path = GENERATE("rtv", "rov");
  std::string error;
  auto fixture = GpuFixture::Create(&error, {{"render_target_path_d3d12", path},
                                             {"async_shader_compilation", "false"},
                                             {"primitive_processor_cache_min_indices", "0"}});
  if (!fixture) {
    SKIP(error);
  }
  if (std::string(path) == "rov" && (fixture->provider().IsAdapterSoftware() ||
                                     !fixture->provider().AreRasterizerOrderedViewsSupported())) {
    SKIP("hardware ROV unavailable");
  }
  INFO(fixture->Metadata());
  INFO(path);
  REQUIRE(rex::cvar::SetFlagByName("readback_resolve", "full"));
  constexpr uint32_t kSize = 32;
  const Surface surface{xenos::MsaaSamples::k1X, 64};
  const uint32_t indices = fixture->AllocPhysical(16);
  const uint32_t destination = fixture->AllocPhysical(kSize * kSize * 4);
  fixture->WriteDwords(indices, {0, 1, 3, 2});
  SetupDraw(*fixture, surface, kSize, kSize);
  DrawRect(*fixture, 0, 0, kSize, kSize, 0xFF0000FF);
  DrawFan(*fixture, indices);
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, destination);
  REQUIRE(fixture->Flush());
  CHECK(ReadTexel(*fixture, destination, 16, 16) == 0xFFFFFFFF);

  fixture->WriteDwordsAsGuest(indices, {0, 0, 0, 0});
  SetupDraw(*fixture, surface, kSize, kSize);
  DrawRect(*fixture, 0, 0, kSize, kSize, 0xFF0000FF);
  DrawFan(*fixture, indices);
  Resolve(*fixture, surface, kSize, kSize, xenos::CopySampleSelect::k0, destination);
  REQUIRE(fixture->Flush());
  CHECK(ReadTexel(*fixture, destination, 16, 16) == 0xFF0000FF);
}
