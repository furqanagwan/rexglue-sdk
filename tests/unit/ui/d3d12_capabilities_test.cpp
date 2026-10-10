// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <rex/ui/d3d12/d3d12_capabilities.h>

using rex::ui::d3d12::D3D12Capabilities;
using rex::ui::d3d12::DescribeD3D12Capabilities;
using rex::ui::d3d12::MeetsDirectX12Ultimate;
using rex::ui::d3d12::MissingDirectX12UltimateFeatures;

namespace {

D3D12Capabilities UltimateDevice() {
  D3D12Capabilities capabilities;
  capabilities.max_feature_level = D3D_FEATURE_LEVEL_12_2;
  capabilities.highest_shader_model = D3D_SHADER_MODEL_6_8;
  capabilities.raytracing_tier = D3D12_RAYTRACING_TIER_1_1;
  capabilities.variable_shading_rate_tier = D3D12_VARIABLE_SHADING_RATE_TIER_2;
  capabilities.mesh_shader_tier = D3D12_MESH_SHADER_TIER_1;
  capabilities.sampler_feedback_tier = D3D12_SAMPLER_FEEDBACK_TIER_0_9;
  return capabilities;
}

}

TEST_CASE("A device with every DirectX 12 Ultimate feature meets it", "[ui][d3d12]") {
  const auto capabilities = UltimateDevice();
  CHECK(MeetsDirectX12Ultimate(capabilities));
  CHECK(MissingDirectX12UltimateFeatures(capabilities).empty());
  CHECK(DescribeD3D12Capabilities(capabilities).starts_with("* DirectX 12 Ultimate: yes\n"));
}

TEST_CASE("A device missing one DirectX 12 Ultimate feature names it", "[ui][d3d12]") {
  auto capabilities = UltimateDevice();
  SECTION("Ray tracing 1.0") {
    capabilities.raytracing_tier = D3D12_RAYTRACING_TIER_1_0;
    CHECK(MissingDirectX12UltimateFeatures(capabilities) ==
          std::vector<std::string_view>{"ray tracing tier 1.1"});
  }
  SECTION("Variable-rate shading tier 1") {
    capabilities.variable_shading_rate_tier = D3D12_VARIABLE_SHADING_RATE_TIER_1;
    CHECK(MissingDirectX12UltimateFeatures(capabilities) ==
          std::vector<std::string_view>{"variable-rate shading tier 2"});
  }
  SECTION("No mesh shaders") {
    capabilities.mesh_shader_tier = D3D12_MESH_SHADER_TIER_NOT_SUPPORTED;
    CHECK(MissingDirectX12UltimateFeatures(capabilities) ==
          std::vector<std::string_view>{"mesh shaders tier 1"});
  }
  SECTION("No sampler feedback") {
    capabilities.sampler_feedback_tier = D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED;
    CHECK(MissingDirectX12UltimateFeatures(capabilities) ==
          std::vector<std::string_view>{"sampler feedback tier 0.9"});
  }
  SECTION("Shader model 6.4") {
    capabilities.highest_shader_model = D3D_SHADER_MODEL_6_4;
    CHECK(MissingDirectX12UltimateFeatures(capabilities) ==
          std::vector<std::string_view>{"shader model 6.5"});
  }
  CHECK_FALSE(MeetsDirectX12Ultimate(capabilities));
}

TEST_CASE("The capability report names tiers the way D3D12 does", "[ui][d3d12]") {
  auto capabilities = UltimateDevice();
  capabilities.sampler_feedback_tier = D3D12_SAMPLER_FEEDBACK_TIER_1_0;
  capabilities.enhanced_barriers = true;
  const auto text = DescribeD3D12Capabilities(capabilities);
  CHECK(text.find("* Ray tracing: tier 1.1\n") != std::string::npos);
  CHECK(text.find("* Variable-rate shading: tier 2\n") != std::string::npos);
  CHECK(text.find("* Mesh shaders: tier 1\n") != std::string::npos);
  CHECK(text.find("* Sampler feedback: tier 1\n") != std::string::npos);
  CHECK(text.find("* Enhanced barriers: yes\n") != std::string::npos);
  CHECK(text.find("* GPU upload heaps: no\n") != std::string::npos);
  CHECK(text.find("* Work graphs: not supported") != std::string::npos);
}

TEST_CASE("A feature level 11 device reports what it lacks", "[ui][d3d12]") {
  const D3D12Capabilities capabilities;
  CHECK(MissingDirectX12UltimateFeatures(capabilities).size() == 5);
  CHECK(DescribeD3D12Capabilities(capabilities)
            .starts_with("* DirectX 12 Ultimate: no (missing shader model 6.5, ray tracing tier "
                         "1.1, variable-rate shading tier 2, mesh shaders tier 1, sampler "
                         "feedback tier 0.9)\n"));
}
