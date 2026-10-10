// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/ui/d3d12/d3d12_capabilities.h>

#include <fmt/format.h>
#include <fmt/ranges.h>

namespace rex::ui::d3d12 {
namespace {

template <typename Options>
bool QueryOptions(ID3D12Device* device, D3D12_FEATURE feature, Options& options) {
  return SUCCEEDED(device->CheckFeatureSupport(feature, &options, sizeof(options)));
}

std::string TierName(uint32_t tier, uint32_t units_per_major) {
  if (!tier) {
    return "not supported";
  }
  return fmt::format("tier {:g}", double(tier) / units_per_major);
}

}

D3D12Capabilities QueryD3D12Capabilities(ID3D12Device* device, D3D_FEATURE_LEVEL max_feature_level,
                                         D3D_SHADER_MODEL highest_shader_model) {
  D3D12Capabilities capabilities;
  capabilities.max_feature_level = max_feature_level;
  capabilities.highest_shader_model = highest_shader_model;
  if (D3D12_FEATURE_DATA_D3D12_OPTIONS5 options5{};
      QueryOptions(device, D3D12_FEATURE_D3D12_OPTIONS5, options5)) {
    capabilities.raytracing_tier = options5.RaytracingTier;
  }
  if (D3D12_FEATURE_DATA_D3D12_OPTIONS6 options6{};
      QueryOptions(device, D3D12_FEATURE_D3D12_OPTIONS6, options6)) {
    capabilities.variable_shading_rate_tier = options6.VariableShadingRateTier;
  }
  if (D3D12_FEATURE_DATA_D3D12_OPTIONS7 options7{};
      QueryOptions(device, D3D12_FEATURE_D3D12_OPTIONS7, options7)) {
    capabilities.mesh_shader_tier = options7.MeshShaderTier;
    capabilities.sampler_feedback_tier = options7.SamplerFeedbackTier;
  }
  if (D3D12_FEATURE_DATA_D3D12_OPTIONS12 options12{};
      QueryOptions(device, D3D12_FEATURE_D3D12_OPTIONS12, options12)) {
    capabilities.enhanced_barriers = bool(options12.EnhancedBarriersSupported);
  }
  if (D3D12_FEATURE_DATA_D3D12_OPTIONS16 options16{};
      QueryOptions(device, D3D12_FEATURE_D3D12_OPTIONS16, options16)) {
    capabilities.gpu_upload_heap = bool(options16.GPUUploadHeapSupported);
  }
  if (D3D12_FEATURE_DATA_D3D12_OPTIONS21 options21{};
      QueryOptions(device, D3D12_FEATURE_D3D12_OPTIONS21, options21)) {
    capabilities.work_graphs_tier = options21.WorkGraphsTier;
  }
  return capabilities;
}

std::vector<std::string_view> MissingDirectX12UltimateFeatures(
    const D3D12Capabilities& capabilities) {
  std::vector<std::string_view> missing;
  if (capabilities.highest_shader_model < D3D_SHADER_MODEL_6_5) {
    missing.push_back("shader model 6.5");
  }
  if (capabilities.raytracing_tier < D3D12_RAYTRACING_TIER_1_1) {
    missing.push_back("ray tracing tier 1.1");
  }
  if (capabilities.variable_shading_rate_tier < D3D12_VARIABLE_SHADING_RATE_TIER_2) {
    missing.push_back("variable-rate shading tier 2");
  }
  if (capabilities.mesh_shader_tier < D3D12_MESH_SHADER_TIER_1) {
    missing.push_back("mesh shaders tier 1");
  }
  if (capabilities.sampler_feedback_tier < D3D12_SAMPLER_FEEDBACK_TIER_0_9) {
    missing.push_back("sampler feedback tier 0.9");
  }
  return missing;
}

bool MeetsDirectX12Ultimate(const D3D12Capabilities& capabilities) {
  return MissingDirectX12UltimateFeatures(capabilities).empty();
}

std::string DescribeD3D12Capabilities(const D3D12Capabilities& capabilities) {
  const auto missing = MissingDirectX12UltimateFeatures(capabilities);
  std::string ultimate = "yes";
  if (!missing.empty()) {
    ultimate = fmt::format("no (missing {})", fmt::join(missing, ", "));
  }
  return fmt::format(
      "* DirectX 12 Ultimate: {}\n"
      "* Ray tracing: {}\n"
      "* Variable-rate shading: {}\n"
      "* Mesh shaders: {}\n"
      "* Sampler feedback: {}\n"
      "* Enhanced barriers: {}\n"
      "* GPU upload heaps: {}\n"
      "* Work graphs: {}",
      ultimate, TierName(uint32_t(capabilities.raytracing_tier), 10),
      TierName(uint32_t(capabilities.variable_shading_rate_tier), 1),
      TierName(uint32_t(capabilities.mesh_shader_tier), 10),
      TierName(uint32_t(capabilities.sampler_feedback_tier), 100),
      capabilities.enhanced_barriers ? "yes" : "no", capabilities.gpu_upload_heap ? "yes" : "no",
      TierName(uint32_t(capabilities.work_graphs_tier), 10));
}

}
