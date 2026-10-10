// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <rex/ui/d3d12/d3d12_api.h>

namespace rex::ui::d3d12 {

struct D3D12Capabilities {
  D3D_FEATURE_LEVEL max_feature_level = D3D_FEATURE_LEVEL_11_0;
  D3D_SHADER_MODEL highest_shader_model = D3D_SHADER_MODEL_5_1;
  D3D12_RAYTRACING_TIER raytracing_tier = D3D12_RAYTRACING_TIER_NOT_SUPPORTED;
  D3D12_VARIABLE_SHADING_RATE_TIER variable_shading_rate_tier =
      D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED;
  D3D12_MESH_SHADER_TIER mesh_shader_tier = D3D12_MESH_SHADER_TIER_NOT_SUPPORTED;
  D3D12_SAMPLER_FEEDBACK_TIER sampler_feedback_tier = D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED;
  bool enhanced_barriers = false;
  bool gpu_upload_heap = false;
  D3D12_WORK_GRAPHS_TIER work_graphs_tier = D3D12_WORK_GRAPHS_TIER_NOT_SUPPORTED;
};

D3D12Capabilities QueryD3D12Capabilities(ID3D12Device* device, D3D_FEATURE_LEVEL max_feature_level,
                                         D3D_SHADER_MODEL highest_shader_model);

std::vector<std::string_view> MissingDirectX12UltimateFeatures(
    const D3D12Capabilities& capabilities);

bool MeetsDirectX12Ultimate(const D3D12Capabilities& capabilities);

std::string DescribeD3D12Capabilities(const D3D12Capabilities& capabilities);

}
