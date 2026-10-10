/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include "thirdparty/dxbc/DXBCChecksum.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <memory>
#include <string>
#include <tuple>
#include <utility>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/d3d12/command_processor.h>
#include <rex/graphics/d3d12/deferred_command_list.h>
#include <rex/graphics/d3d12/render_target_cache.h>
#include <rex/graphics/d3d12/texture_cache.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/format/dxbc.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/d3d12/d3d12_util.h>

REXCVAR_DEFINE_BOOL(native_stencil_value_output_d3d12_intel, false, "GPU/D3D12",
                    "Native stencil value output for Intel D3D12");

REXCVAR_DEFINE_STRING(render_target_path_d3d12, "", "GPU/D3D12",
                      "D3D12 render target implementation path")
    .lifecycle(rex::cvar::Lifecycle::kInitOnly);

REXCVAR_DEFINE_BOOL(native_stencil_value_output, true, "GPU", "Enable native stencil value output");

namespace rex::graphics::d3d12 {

namespace shaders {
#include "../shaders/bytecode/d3d12_5_1/clear_uint2_ps.h"
#include "../shaders/bytecode/d3d12_5_1/fullscreen_cw_vs.h"
#include "../shaders/bytecode/d3d12_5_1/host_depth_store_1xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/host_depth_store_2xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/host_depth_store_4xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/passthrough_position_xy_vs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_clear_32bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_clear_32bpp_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_clear_64bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_clear_64bpp_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_32bpp_1x2xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_32bpp_1x2xmsaa_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_32bpp_4xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_32bpp_4xmsaa_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_64bpp_1x2xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_64bpp_1x2xmsaa_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_64bpp_4xmsaa_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_fast_64bpp_4xmsaa_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_128bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_128bpp_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_16bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_16bpp_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_32bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_32bpp_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_64bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_64bpp_scaled_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_8bpp_cs.h"
#include "../shaders/bytecode/d3d12_5_1/resolve_full_8bpp_scaled_cs.h"
}

const D3D12RenderTargetCache::ResolveCopyShaderCode
    D3D12RenderTargetCache::kResolveCopyShaders[size_t(
        draw_util::ResolveCopyShaderIndex::kCount)] = {
        {shaders::resolve_fast_32bpp_1x2xmsaa_cs, sizeof(shaders::resolve_fast_32bpp_1x2xmsaa_cs),
         shaders::resolve_fast_32bpp_1x2xmsaa_scaled_cs,
         sizeof(shaders::resolve_fast_32bpp_1x2xmsaa_scaled_cs)},
        {shaders::resolve_fast_32bpp_4xmsaa_cs, sizeof(shaders::resolve_fast_32bpp_4xmsaa_cs),
         shaders::resolve_fast_32bpp_4xmsaa_scaled_cs,
         sizeof(shaders::resolve_fast_32bpp_4xmsaa_scaled_cs)},
        {shaders::resolve_fast_64bpp_1x2xmsaa_cs, sizeof(shaders::resolve_fast_64bpp_1x2xmsaa_cs),
         shaders::resolve_fast_64bpp_1x2xmsaa_scaled_cs,
         sizeof(shaders::resolve_fast_64bpp_1x2xmsaa_scaled_cs)},
        {shaders::resolve_fast_64bpp_4xmsaa_cs, sizeof(shaders::resolve_fast_64bpp_4xmsaa_cs),
         shaders::resolve_fast_64bpp_4xmsaa_scaled_cs,
         sizeof(shaders::resolve_fast_64bpp_4xmsaa_scaled_cs)},
        {shaders::resolve_full_8bpp_cs, sizeof(shaders::resolve_full_8bpp_cs),
         shaders::resolve_full_8bpp_scaled_cs, sizeof(shaders::resolve_full_8bpp_scaled_cs)},
        {shaders::resolve_full_16bpp_cs, sizeof(shaders::resolve_full_16bpp_cs),
         shaders::resolve_full_16bpp_scaled_cs, sizeof(shaders::resolve_full_16bpp_scaled_cs)},
        {shaders::resolve_full_32bpp_cs, sizeof(shaders::resolve_full_32bpp_cs),
         shaders::resolve_full_32bpp_scaled_cs, sizeof(shaders::resolve_full_32bpp_scaled_cs)},
        {shaders::resolve_full_64bpp_cs, sizeof(shaders::resolve_full_64bpp_cs),
         shaders::resolve_full_64bpp_scaled_cs, sizeof(shaders::resolve_full_64bpp_scaled_cs)},
        {shaders::resolve_full_128bpp_cs, sizeof(shaders::resolve_full_128bpp_cs),
         shaders::resolve_full_128bpp_scaled_cs, sizeof(shaders::resolve_full_128bpp_scaled_cs)},
};

const uint32_t D3D12RenderTargetCache::kTransferUsedRootParameters[size_t(
    TransferRootSignatureIndex::kCount)] = {

    kTransferUsedRootParameterColorSRVBit | kTransferUsedRootParameterAddressConstantBit,

    kTransferUsedRootParameterDepthSRVBit | kTransferUsedRootParameterAddressConstantBit,

    kTransferUsedRootParameterDepthSRVBit | kTransferUsedRootParameterStencilSRVBit |
        kTransferUsedRootParameterAddressConstantBit,

    kTransferUsedRootParameterStencilMaskConstantBit | kTransferUsedRootParameterColorSRVBit |
        kTransferUsedRootParameterAddressConstantBit,

    kTransferUsedRootParameterStencilMaskConstantBit | kTransferUsedRootParameterStencilSRVBit |
        kTransferUsedRootParameterAddressConstantBit,

    kTransferUsedRootParameterColorSRVBit | kTransferUsedRootParameterAddressConstantBit |
        kTransferUsedRootParameterHostDepthSRVBit |
        kTransferUsedRootParameterHostDepthAddressConstantBit,

    kTransferUsedRootParameterDepthSRVBit | kTransferUsedRootParameterAddressConstantBit |
        kTransferUsedRootParameterHostDepthSRVBit |
        kTransferUsedRootParameterHostDepthAddressConstantBit,

    kTransferUsedRootParameterDepthSRVBit | kTransferUsedRootParameterStencilSRVBit |
        kTransferUsedRootParameterAddressConstantBit | kTransferUsedRootParameterHostDepthSRVBit |
        kTransferUsedRootParameterHostDepthAddressConstantBit,
};

const D3D12RenderTargetCache::TransferModeInfo
    D3D12RenderTargetCache::kTransferModes[size_t(TransferMode::kCount)] = {

        {TransferOutput::kDepth, TransferRootSignatureIndex::kColor,
         TransferRootSignatureIndex::kColor},

        {TransferOutput::kColor, TransferRootSignatureIndex::kColor,
         TransferRootSignatureIndex::kColor},

        {TransferOutput::kDepth, TransferRootSignatureIndex::kDepth,
         TransferRootSignatureIndex::kDepthStencil},

        {TransferOutput::kColor, TransferRootSignatureIndex::kDepthStencil,
         TransferRootSignatureIndex::kDepthStencil},

        {TransferOutput::kStencilBit, TransferRootSignatureIndex::kColorToStencilBit,
         TransferRootSignatureIndex::kColorToStencilBit},

        {TransferOutput::kStencilBit, TransferRootSignatureIndex::kStencilToStencilBit,
         TransferRootSignatureIndex::kStencilToStencilBit},

        {TransferOutput::kDepth, TransferRootSignatureIndex::kColorAndHostDepth,
         TransferRootSignatureIndex::kColorAndHostDepth},

        {TransferOutput::kDepth, TransferRootSignatureIndex::kDepthAndHostDepth,
         TransferRootSignatureIndex::kDepthStencilAndHostDepth},
};

D3D12RenderTargetCache::~D3D12RenderTargetCache() {
  Shutdown(true);
}

bool D3D12RenderTargetCache::Initialize() {
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  ID3D12Device* device = provider.GetDevice();

  const char* path_reason = "render_target_path_d3d12";
  if (REXCVAR_GET(render_target_path_d3d12) == "rtv") {
    path_ = Path::kHostRenderTargets;
  } else if (REXCVAR_GET(render_target_path_d3d12) == "rov") {
    path_ = Path::kPixelShaderInterlock;
  } else {
    path_reason = "vendor default";

#if 1

    path_ = provider.GetAdapterVendorID() == ui::GraphicsProvider::GpuVendorID::kIntel
                ? Path::kPixelShaderInterlock
                : Path::kHostRenderTargets;
#else

    path_ = provider.GetAdapterVendorID() == ui::GraphicsProvider::GpuVendorID::kAMD
                ? Path::kHostRenderTargets
                : Path::kPixelShaderInterlock;
#endif
  }
  if (path_ == Path::kPixelShaderInterlock && !provider.AreRasterizerOrderedViewsSupported()) {
    path_ = Path::kHostRenderTargets;
    path_reason = "ROV unsupported, fallback";
  }
  REXGPU_INFO("D3D12 render target path: {} ({})",
              path_ == Path::kPixelShaderInterlock ? "ROV" : "host render targets", path_reason);

  uint32_t edram_buffer_size =
      xenos::kEdramSizeBytes * (draw_resolution_scale_x() * draw_resolution_scale_y());
  D3D12_RESOURCE_DESC edram_buffer_desc;
  ui::d3d12::util::FillBufferResourceDesc(edram_buffer_desc, edram_buffer_size,
                                          D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);

  edram_buffer_state_ = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;

  if (FAILED(device->CreateCommittedResource(
          &ui::d3d12::util::kHeapPropertiesDefault, D3D12_HEAP_FLAG_NONE, &edram_buffer_desc,
          edram_buffer_state_, nullptr, IID_PPV_ARGS(&edram_buffer_)))) {
    REXGPU_ERROR("D3D12RenderTargetCache: Failed to create the EDRAM buffer");
    Shutdown();
    return false;
  }
  edram_buffer_->SetName(L"EDRAM Buffer");
  edram_buffer_modification_status_ = EdramBufferModificationStatus::kUnmodified;

  D3D12_DESCRIPTOR_HEAP_DESC edram_buffer_descriptor_heap_desc;
  edram_buffer_descriptor_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  edram_buffer_descriptor_heap_desc.NumDescriptors = uint32_t(EdramBufferDescriptorIndex::kCount);
  edram_buffer_descriptor_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  edram_buffer_descriptor_heap_desc.NodeMask = 0;
  if (FAILED(device->CreateDescriptorHeap(&edram_buffer_descriptor_heap_desc,
                                          IID_PPV_ARGS(&edram_buffer_descriptor_heap_)))) {
    REXGPU_ERROR(
        "D3D12RenderTargetCache: Failed to create the descriptor heap for "
        "EDRAM buffer views");
    Shutdown();
    return false;
  }
  edram_buffer_descriptor_heap_start_ =
      edram_buffer_descriptor_heap_->GetCPUDescriptorHandleForHeapStart();
  ui::d3d12::util::CreateBufferRawSRV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kRawSRV)),
      edram_buffer_, edram_buffer_size);
  ui::d3d12::util::CreateBufferTypedSRV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kR32UintSRV)),
      edram_buffer_, DXGI_FORMAT_R32_UINT, edram_buffer_size >> 2);
  ui::d3d12::util::CreateBufferTypedSRV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kR32G32UintSRV)),
      edram_buffer_, DXGI_FORMAT_R32G32_UINT, edram_buffer_size >> 3);
  ui::d3d12::util::CreateBufferTypedSRV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kR32G32B32A32UintSRV)),
      edram_buffer_, DXGI_FORMAT_R32G32B32A32_UINT, edram_buffer_size >> 4);
  ui::d3d12::util::CreateBufferRawUAV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kRawUAV)),
      edram_buffer_, edram_buffer_size);
  ui::d3d12::util::CreateBufferTypedUAV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kR32UintUAV)),
      edram_buffer_, DXGI_FORMAT_R32_UINT, edram_buffer_size >> 2);
  ui::d3d12::util::CreateBufferTypedUAV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kR32G32UintUAV)),
      edram_buffer_, DXGI_FORMAT_R32G32_UINT, edram_buffer_size >> 3);
  ui::d3d12::util::CreateBufferTypedUAV(
      device,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kR32G32B32A32UintUAV)),
      edram_buffer_, DXGI_FORMAT_R32G32B32A32_UINT, edram_buffer_size >> 4);

  bool draw_resolution_scaled = IsDrawResolutionScaled();

  std::array<D3D12_ROOT_PARAMETER, 3> resolve_copy_root_parameters;

  resolve_copy_root_parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
  resolve_copy_root_parameters[0].Constants.ShaderRegister = 0;
  resolve_copy_root_parameters[0].Constants.RegisterSpace = 0;

  resolve_copy_root_parameters[0].Constants.Num32BitValues =
      (draw_resolution_scaled ? sizeof(draw_util::ResolveCopyShaderConstants::DestRelative)
                              : sizeof(draw_util::ResolveCopyShaderConstants)) /
      sizeof(uint32_t);
  resolve_copy_root_parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

  D3D12_DESCRIPTOR_RANGE resolve_copy_dest_range;
  resolve_copy_dest_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
  resolve_copy_dest_range.NumDescriptors = 1;
  resolve_copy_dest_range.BaseShaderRegister = 0;
  resolve_copy_dest_range.RegisterSpace = 0;
  resolve_copy_dest_range.OffsetInDescriptorsFromTableStart = 0;
  resolve_copy_root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  resolve_copy_root_parameters[1].DescriptorTable.NumDescriptorRanges = 1;
  resolve_copy_root_parameters[1].DescriptorTable.pDescriptorRanges = &resolve_copy_dest_range;
  resolve_copy_root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

  D3D12_DESCRIPTOR_RANGE resolve_copy_source_range;
  resolve_copy_source_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  resolve_copy_source_range.NumDescriptors = 1;
  resolve_copy_source_range.BaseShaderRegister = 0;
  resolve_copy_source_range.RegisterSpace = 0;
  resolve_copy_source_range.OffsetInDescriptorsFromTableStart = 0;
  resolve_copy_root_parameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  resolve_copy_root_parameters[2].DescriptorTable.NumDescriptorRanges = 1;
  resolve_copy_root_parameters[2].DescriptorTable.pDescriptorRanges = &resolve_copy_source_range;
  resolve_copy_root_parameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
  D3D12_ROOT_SIGNATURE_DESC resolve_copy_root_signature_desc;
  resolve_copy_root_signature_desc.NumParameters = UINT(resolve_copy_root_parameters.size());
  resolve_copy_root_signature_desc.pParameters = resolve_copy_root_parameters.data();
  resolve_copy_root_signature_desc.NumStaticSamplers = 0;
  resolve_copy_root_signature_desc.pStaticSamplers = nullptr;
  resolve_copy_root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
  resolve_copy_root_signature_ =
      ui::d3d12::util::CreateRootSignature(provider, resolve_copy_root_signature_desc);
  if (resolve_copy_root_signature_ == nullptr) {
    REXGPU_ERROR(
        "D3D12RenderTargetCache: Failed to create the resolve copy root "
        "signature");
    Shutdown();
    return false;
  }

  direct_resolve_root_signature_color_ = resolve_copy_root_signature_;
  direct_resolve_root_signature_depth_ = resolve_copy_root_signature_;
  direct_resolve_root_signature_color_->AddRef();
  direct_resolve_root_signature_depth_->AddRef();

  for (size_t i = 0; i < size_t(draw_util::ResolveCopyShaderIndex::kCount); ++i) {
    const draw_util::ResolveCopyShaderInfo& resolve_copy_shader_info =
        draw_util::resolve_copy_shader_info[i];
    const ResolveCopyShaderCode& resolve_copy_shader_code = kResolveCopyShaders[i];

    assert_true(resolve_copy_shader_code.unscaled && resolve_copy_shader_code.unscaled_size &&
                resolve_copy_shader_code.scaled && resolve_copy_shader_code.scaled_size);
    ID3D12PipelineState* resolve_copy_pipeline = ui::d3d12::util::CreateComputePipeline(
        device,
        draw_resolution_scaled ? resolve_copy_shader_code.scaled
                               : resolve_copy_shader_code.unscaled,
        draw_resolution_scaled ? resolve_copy_shader_code.scaled_size
                               : resolve_copy_shader_code.unscaled_size,
        resolve_copy_root_signature_);
    if (resolve_copy_pipeline == nullptr) {
      REXGPU_ERROR("D3D12RenderTargetCache: Failed to create {} resolve copy pipeline",
                   resolve_copy_shader_info.debug_name);
      Shutdown();
      return false;
    }
    std::u16string resolve_copy_pipeline_name =
        rex::string::to_utf16(resolve_copy_shader_info.debug_name);
    resolve_copy_pipeline->SetName(reinterpret_cast<LPCWSTR>(resolve_copy_pipeline_name.c_str()));
    resolve_copy_pipelines_[i] = resolve_copy_pipeline;
  }

  use_stencil_reference_output_ =
      REXCVAR_GET(native_stencil_value_output) &&
      provider.IsPSSpecifiedStencilReferenceSupported() &&
      (REXCVAR_GET(native_stencil_value_output_d3d12_intel) ||
       provider.GetAdapterVendorID() != ui::GraphicsProvider::GpuVendorID::kIntel);
  REXGPU_INFO("D3D12 pixel-shader stencil reference output: {}",
              use_stencil_reference_output_ ? "yes" : "no");

  if (path_ == Path::kHostRenderTargets) {
    gamma_render_target_as_unorm16_ = REXCVAR_GET(gamma_render_target_as_unorm16);

    depth_float24_round_ = REXCVAR_GET(depth_float24_round);
    depth_float24_convert_in_pixel_shader_ = REXCVAR_GET(depth_float24_convert_in_pixel_shader);

    if (REXCVAR_GET(native_2x_msaa)) {
      msaa_2x_supported_ = true;
      static const DXGI_FORMAT kRenderTargetDXGIFormats[] = {
          DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_SNORM,
          DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
          DXGI_FORMAT_R10G10B10A2_UNORM,  DXGI_FORMAT_R8G8B8A8_UNORM,
          DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_SNORM,
          DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_D24_UNORM_S8_UINT,

          DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R32G32_UINT,
          DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R32_UINT,
      };
      D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS multisample_quality_levels;
      multisample_quality_levels.SampleCount = 2;
      multisample_quality_levels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
      for (size_t i = 0; i < rex::countof(kRenderTargetDXGIFormats); ++i) {
        multisample_quality_levels.Format = kRenderTargetDXGIFormats[i];
        multisample_quality_levels.NumQualityLevels = 0;
        if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
                                               &multisample_quality_levels,
                                               sizeof(multisample_quality_levels))) ||
            !multisample_quality_levels.NumQualityLevels) {
          msaa_2x_supported_ = false;
          break;
        }
      }
    } else {
      msaa_2x_supported_ = false;
    }
    if (msaa_2x_supported_ && gamma_render_target_as_unorm16_) {
      D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS multisample_quality_levels;
      multisample_quality_levels.SampleCount = 2;
      multisample_quality_levels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
      multisample_quality_levels.Format = DXGI_FORMAT_R16G16B16A16_UNORM;
      multisample_quality_levels.NumQualityLevels = 0;
      if (FAILED(device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
                                             &multisample_quality_levels,
                                             sizeof(multisample_quality_levels))) ||
          !multisample_quality_levels.NumQualityLevels) {
        msaa_2x_supported_ = false;
      }
    }
    if (!msaa_2x_supported_) {
      REXGPU_WARN(
          "2x MSAA is not supported, emulated via top-left and bottom-right "
          "samples of 4x MSAA");
    }

    descriptor_pool_color_ = std::make_unique<ui::d3d12::D3D12CpuDescriptorPool>(
        provider, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 11);
    descriptor_pool_depth_ = std::make_unique<ui::d3d12::D3D12CpuDescriptorPool>(
        provider, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 11);
    descriptor_pool_srv_ = std::make_unique<ui::d3d12::D3D12CpuDescriptorPool>(
        provider, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 11);

    null_rtv_descriptor_ss_ = descriptor_pool_color_->AllocateDescriptor();
    null_rtv_descriptor_ms_ = descriptor_pool_color_->AllocateDescriptor();
    if (!null_rtv_descriptor_ss_ || !null_rtv_descriptor_ms_) {
      Shutdown();
      return false;
    }
    D3D12_RENDER_TARGET_VIEW_DESC null_rtv_desc;

    null_rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    null_rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
    null_rtv_desc.Texture2D.MipSlice = 0;
    null_rtv_desc.Texture2D.PlaneSlice = 0;
    device->CreateRenderTargetView(nullptr, &null_rtv_desc, null_rtv_descriptor_ss_.GetHandle());
    null_rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
    device->CreateRenderTargetView(nullptr, &null_rtv_desc, null_rtv_descriptor_ms_.GetHandle());

    D3D12_ROOT_PARAMETER
    host_depth_store_root_parameters[kHostDepthStoreRootParameterCount];

    D3D12_ROOT_PARAMETER& host_depth_store_root_constants =
        host_depth_store_root_parameters[kHostDepthStoreRootParameterConstants];
    host_depth_store_root_constants.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    host_depth_store_root_constants.Constants.ShaderRegister = 0;
    host_depth_store_root_constants.Constants.RegisterSpace = 0;
    host_depth_store_root_constants.Constants.Num32BitValues =
        sizeof(HostDepthStoreConstants) / sizeof(uint32_t);
    host_depth_store_root_constants.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    D3D12_DESCRIPTOR_RANGE host_depth_store_root_source_range;
    host_depth_store_root_source_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    host_depth_store_root_source_range.NumDescriptors = 1;
    host_depth_store_root_source_range.BaseShaderRegister = 0;
    host_depth_store_root_source_range.RegisterSpace = 0;
    host_depth_store_root_source_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_ROOT_PARAMETER& host_depth_store_root_source =
        host_depth_store_root_parameters[kHostDepthStoreRootParameterSource];
    host_depth_store_root_source.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    host_depth_store_root_source.DescriptorTable.NumDescriptorRanges = 1;
    host_depth_store_root_source.DescriptorTable.pDescriptorRanges =
        &host_depth_store_root_source_range;
    host_depth_store_root_source.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    D3D12_DESCRIPTOR_RANGE host_depth_store_root_dest_range;
    host_depth_store_root_dest_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    host_depth_store_root_dest_range.NumDescriptors = 1;
    host_depth_store_root_dest_range.BaseShaderRegister = 0;
    host_depth_store_root_dest_range.RegisterSpace = 0;
    host_depth_store_root_dest_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_ROOT_PARAMETER& host_depth_store_root_dest =
        host_depth_store_root_parameters[kHostDepthStoreRootParameterDest];
    host_depth_store_root_dest.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    host_depth_store_root_dest.DescriptorTable.NumDescriptorRanges = 1;
    host_depth_store_root_dest.DescriptorTable.pDescriptorRanges =
        &host_depth_store_root_dest_range;
    host_depth_store_root_dest.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    D3D12_ROOT_SIGNATURE_DESC host_depth_store_root_desc;
    host_depth_store_root_desc.NumParameters = UINT(rex::countof(host_depth_store_root_parameters));
    host_depth_store_root_desc.pParameters = host_depth_store_root_parameters;
    host_depth_store_root_desc.NumStaticSamplers = 0;
    host_depth_store_root_desc.pStaticSamplers = nullptr;
    host_depth_store_root_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
    host_depth_store_root_signature_ =
        ui::d3d12::util::CreateRootSignature(provider, host_depth_store_root_desc);
    if (!host_depth_store_root_signature_) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the host depth storing "
          "root signature");
      Shutdown();
      return false;
    }

    host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k1X)] =
        ui::d3d12::util::CreateComputePipeline(device, shaders::host_depth_store_1xmsaa_cs,
                                               sizeof(shaders::host_depth_store_1xmsaa_cs),
                                               host_depth_store_root_signature_);
    if (!host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k1X)]) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the 1-sample host depth "
          "storing pipeline");
      Shutdown();
      return false;
    }
    host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k1X)]->SetName(
        L"Host Depth Store 1xMSAA");

    host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k2X)] =
        ui::d3d12::util::CreateComputePipeline(device, shaders::host_depth_store_2xmsaa_cs,
                                               sizeof(shaders::host_depth_store_2xmsaa_cs),
                                               host_depth_store_root_signature_);
    if (!host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k2X)]) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the 2-sample host depth "
          "storing pipeline");
      Shutdown();
      return false;
    }
    host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k2X)]->SetName(
        L"Host Depth Store 2xMSAA");

    host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k4X)] =
        ui::d3d12::util::CreateComputePipeline(device, shaders::host_depth_store_4xmsaa_cs,
                                               sizeof(shaders::host_depth_store_4xmsaa_cs),
                                               host_depth_store_root_signature_);
    if (!host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k4X)]) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the 4-sample host depth "
          "storing pipeline");
      Shutdown();
      return false;
    }
    host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k4X)]->SetName(
        L"Host Depth Store 4xMSAA");

    transfer_vertex_buffer_pool_ = std::make_unique<ui::d3d12::D3D12UploadBufferPool>(
        provider, std::max(ui::d3d12::D3D12UploadBufferPool::kDefaultPageSize,
                           sizeof(float) * 2 * 6 * Transfer::kMaxCutoutBorderRectangles *
                               xenos::kEdramTileCount));

    D3D12_DESCRIPTOR_RANGE transfer_root_color_srv_range;
    transfer_root_color_srv_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    transfer_root_color_srv_range.NumDescriptors = 1;
    transfer_root_color_srv_range.BaseShaderRegister = kTransferSRVRegisterColor;
    transfer_root_color_srv_range.RegisterSpace = 0;
    transfer_root_color_srv_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_DESCRIPTOR_RANGE transfer_root_depth_srv_range;
    transfer_root_depth_srv_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    transfer_root_depth_srv_range.NumDescriptors = 1;
    transfer_root_depth_srv_range.BaseShaderRegister = kTransferSRVRegisterDepth;
    transfer_root_depth_srv_range.RegisterSpace = 0;
    transfer_root_depth_srv_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_DESCRIPTOR_RANGE transfer_root_stencil_srv_range;
    transfer_root_stencil_srv_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    transfer_root_stencil_srv_range.NumDescriptors = 1;
    transfer_root_stencil_srv_range.BaseShaderRegister = kTransferSRVRegisterStencil;
    transfer_root_stencil_srv_range.RegisterSpace = 0;
    transfer_root_stencil_srv_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_DESCRIPTOR_RANGE transfer_root_host_depth_srv_range;
    transfer_root_host_depth_srv_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    transfer_root_host_depth_srv_range.NumDescriptors = 1;
    transfer_root_host_depth_srv_range.BaseShaderRegister = kTransferSRVRegisterHostDepth;
    transfer_root_host_depth_srv_range.RegisterSpace = 0;
    transfer_root_host_depth_srv_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_ROOT_PARAMETER
    transfer_root_parameters[kTransferUsedRootParameterCount];
    D3D12_ROOT_SIGNATURE_DESC transfer_root_desc;
    transfer_root_desc.pParameters = transfer_root_parameters;
    transfer_root_desc.NumStaticSamplers = 0;
    transfer_root_desc.pStaticSamplers = nullptr;
    transfer_root_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    for (size_t i = 0; i < size_t(TransferRootSignatureIndex::kCount); ++i) {
      uint32_t transfer_root_mask = kTransferUsedRootParameters[i];

      if (transfer_root_mask & kTransferUsedRootParameterStencilMaskConstantBit) {
        D3D12_ROOT_PARAMETER& transfer_root_stencil_mask_constant =
            transfer_root_parameters[rex::bit_count(
                transfer_root_mask & (kTransferUsedRootParameterStencilMaskConstantBit - 1))];
        transfer_root_stencil_mask_constant.ParameterType =
            D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
        transfer_root_stencil_mask_constant.Constants.ShaderRegister =
            kTransferCBVRegisterStencilMask;
        transfer_root_stencil_mask_constant.Constants.RegisterSpace = 0;
        transfer_root_stencil_mask_constant.Constants.Num32BitValues = 1;
        transfer_root_stencil_mask_constant.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }

      if (transfer_root_mask & kTransferUsedRootParameterColorSRVBit) {
        D3D12_ROOT_PARAMETER& transfer_root_color_srv = transfer_root_parameters[rex::bit_count(
            transfer_root_mask & (kTransferUsedRootParameterColorSRVBit - 1))];
        transfer_root_color_srv.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        transfer_root_color_srv.DescriptorTable.NumDescriptorRanges = 1;
        transfer_root_color_srv.DescriptorTable.pDescriptorRanges = &transfer_root_color_srv_range;
        transfer_root_color_srv.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }

      if (transfer_root_mask & kTransferUsedRootParameterDepthSRVBit) {
        D3D12_ROOT_PARAMETER& transfer_root_depth_srv = transfer_root_parameters[rex::bit_count(
            transfer_root_mask & (kTransferUsedRootParameterDepthSRVBit - 1))];
        transfer_root_depth_srv.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        transfer_root_depth_srv.DescriptorTable.NumDescriptorRanges = 1;
        transfer_root_depth_srv.DescriptorTable.pDescriptorRanges = &transfer_root_depth_srv_range;
        transfer_root_depth_srv.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }

      if (transfer_root_mask & kTransferUsedRootParameterStencilSRVBit) {
        D3D12_ROOT_PARAMETER& transfer_root_stencil_srv = transfer_root_parameters[rex::bit_count(
            transfer_root_mask & (kTransferUsedRootParameterStencilSRVBit - 1))];
        transfer_root_stencil_srv.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        transfer_root_stencil_srv.DescriptorTable.NumDescriptorRanges = 1;
        transfer_root_stencil_srv.DescriptorTable.pDescriptorRanges =
            &transfer_root_stencil_srv_range;
        transfer_root_stencil_srv.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }

      if (transfer_root_mask & kTransferUsedRootParameterAddressConstantBit) {
        D3D12_ROOT_PARAMETER& transfer_root_address_constant =
            transfer_root_parameters[rex::bit_count(
                transfer_root_mask & (kTransferUsedRootParameterAddressConstantBit - 1))];
        transfer_root_address_constant.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
        transfer_root_address_constant.Constants.ShaderRegister = kTransferCBVRegisterAddress;
        transfer_root_address_constant.Constants.RegisterSpace = 0;
        transfer_root_address_constant.Constants.Num32BitValues =
            sizeof(TransferAddressConstant) / sizeof(uint32_t);
        transfer_root_address_constant.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }

      if (transfer_root_mask & kTransferUsedRootParameterHostDepthSRVBit) {
        D3D12_ROOT_PARAMETER& transfer_root_host_depth_srv =
            transfer_root_parameters[rex::bit_count(
                transfer_root_mask & (kTransferUsedRootParameterHostDepthSRVBit - 1))];
        transfer_root_host_depth_srv.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        transfer_root_host_depth_srv.DescriptorTable.NumDescriptorRanges = 1;
        transfer_root_host_depth_srv.DescriptorTable.pDescriptorRanges =
            &transfer_root_host_depth_srv_range;
        transfer_root_host_depth_srv.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }

      if (transfer_root_mask & kTransferUsedRootParameterHostDepthAddressConstantBit) {
        D3D12_ROOT_PARAMETER& transfer_root_host_address_constant =
            transfer_root_parameters[rex::bit_count(
                transfer_root_mask & (kTransferUsedRootParameterHostDepthAddressConstantBit - 1))];
        transfer_root_host_address_constant.ParameterType =
            D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
        transfer_root_host_address_constant.Constants.ShaderRegister =
            kTransferCBVRegisterHostDepthAddress;
        transfer_root_host_address_constant.Constants.RegisterSpace = 0;
        transfer_root_host_address_constant.Constants.Num32BitValues =
            sizeof(TransferAddressConstant) / sizeof(uint32_t);
        transfer_root_host_address_constant.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
      }
      transfer_root_desc.NumParameters = rex::bit_count(transfer_root_mask);
      assert_true(transfer_root_desc.NumParameters <= kTransferUsedRootParameterCount);
      transfer_root_signatures_[i] =
          ui::d3d12::util::CreateRootSignature(provider, transfer_root_desc);
      if (!transfer_root_signatures_[i]) {
        REXGPU_ERROR(
            "D3D12RenderTargetCache: Failed to create the render target "
            "ownership transfer root signature {:X}",
            transfer_root_mask);
        Shutdown();
        return false;
      }
    }

    D3D12_DESCRIPTOR_RANGE dump_root_source_range;
    dump_root_source_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    dump_root_source_range.NumDescriptors = 1;
    dump_root_source_range.BaseShaderRegister = 0;
    dump_root_source_range.RegisterSpace = 0;
    dump_root_source_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_DESCRIPTOR_RANGE dump_root_stencil_range;
    dump_root_stencil_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    dump_root_stencil_range.NumDescriptors = 1;
    dump_root_stencil_range.BaseShaderRegister = 1;
    dump_root_stencil_range.RegisterSpace = 0;
    dump_root_stencil_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_DESCRIPTOR_RANGE dump_root_edram_range;
    dump_root_edram_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    dump_root_edram_range.NumDescriptors = 1;
    dump_root_edram_range.BaseShaderRegister = 0;
    dump_root_edram_range.RegisterSpace = 0;
    dump_root_edram_range.OffsetInDescriptorsFromTableStart = 0;
    D3D12_ROOT_PARAMETER
    dump_root_color_parameters[kDumpRootParameterColorCount];
    D3D12_ROOT_PARAMETER
    dump_root_depth_parameters[kDumpRootParameterDepthCount];
    for (uint32_t i = 0; i < 2; ++i) {
      D3D12_ROOT_PARAMETER& dump_root_offsets =
          i ? dump_root_depth_parameters[kDumpRootParameterOffsets]
            : dump_root_color_parameters[kDumpRootParameterOffsets];
      dump_root_offsets.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
      dump_root_offsets.Constants.ShaderRegister = kDumpCbufferOffsets;
      dump_root_offsets.Constants.RegisterSpace = 0;
      dump_root_offsets.Constants.Num32BitValues = sizeof(DumpOffsets) / sizeof(uint32_t);
      dump_root_offsets.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

      D3D12_ROOT_PARAMETER& dump_root_source =
          i ? dump_root_depth_parameters[kDumpRootParameterSource]
            : dump_root_color_parameters[kDumpRootParameterSource];
      dump_root_source.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
      dump_root_source.DescriptorTable.NumDescriptorRanges = 1;
      dump_root_source.DescriptorTable.pDescriptorRanges = &dump_root_source_range;
      dump_root_source.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

      if (i) {
        D3D12_ROOT_PARAMETER& dump_root_stencil =
            dump_root_depth_parameters[kDumpRootParameterDepthStencil];
        dump_root_stencil.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
        dump_root_stencil.DescriptorTable.NumDescriptorRanges = 1;
        dump_root_stencil.DescriptorTable.pDescriptorRanges = &dump_root_stencil_range;
        dump_root_stencil.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
      }

      D3D12_ROOT_PARAMETER& dump_root_pitches =
          i ? dump_root_depth_parameters[kDumpRootParameterDepthPitches]
            : dump_root_color_parameters[kDumpRootParameterColorPitches];
      dump_root_pitches.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
      dump_root_pitches.Constants.ShaderRegister = kDumpCbufferPitches;
      dump_root_pitches.Constants.RegisterSpace = 0;
      dump_root_pitches.Constants.Num32BitValues = sizeof(DumpPitches) / sizeof(uint32_t);
      dump_root_pitches.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

      D3D12_ROOT_PARAMETER& dump_root_edram =
          i ? dump_root_depth_parameters[kDumpRootParameterDepthEdram]
            : dump_root_color_parameters[kDumpRootParameterColorEdram];
      dump_root_edram.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
      dump_root_edram.DescriptorTable.NumDescriptorRanges = 1;
      dump_root_edram.DescriptorTable.pDescriptorRanges = &dump_root_edram_range;
      dump_root_edram.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    }
    D3D12_ROOT_SIGNATURE_DESC dump_root_desc;
    dump_root_desc.NumParameters = UINT(rex::countof(dump_root_color_parameters));
    dump_root_desc.pParameters = dump_root_color_parameters;
    dump_root_desc.NumStaticSamplers = 0;
    dump_root_desc.pStaticSamplers = nullptr;
    dump_root_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
    dump_root_signature_color_ = ui::d3d12::util::CreateRootSignature(provider, dump_root_desc);
    if (!dump_root_signature_color_) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the color render target "
          "dumping root signature");
      Shutdown();
      return false;
    }
    dump_root_desc.NumParameters = UINT(rex::countof(dump_root_depth_parameters));
    dump_root_desc.pParameters = dump_root_depth_parameters;
    dump_root_signature_depth_ = ui::d3d12::util::CreateRootSignature(provider, dump_root_desc);
    if (!dump_root_signature_depth_) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the depth render target "
          "dumping root signature");
      Shutdown();
      return false;
    }

    D3D12_ROOT_PARAMETER uint32_rtv_clear_root_constants;
    uint32_rtv_clear_root_constants.ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    uint32_rtv_clear_root_constants.Constants.ShaderRegister = 0;
    uint32_rtv_clear_root_constants.Constants.RegisterSpace = 0;
    uint32_rtv_clear_root_constants.Constants.Num32BitValues = 2;
    uint32_rtv_clear_root_constants.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
    D3D12_ROOT_SIGNATURE_DESC uint32_rtv_clear_root_desc;
    uint32_rtv_clear_root_desc.NumParameters = 1;
    uint32_rtv_clear_root_desc.pParameters = &uint32_rtv_clear_root_constants;
    uint32_rtv_clear_root_desc.NumStaticSamplers = 0;
    uint32_rtv_clear_root_desc.pStaticSamplers = nullptr;
    uint32_rtv_clear_root_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
    uint32_rtv_clear_root_signature_ =
        ui::d3d12::util::CreateRootSignature(provider, uint32_rtv_clear_root_desc);
    if (!uint32_rtv_clear_root_signature_) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the k_32_FLOAT / "
          "k_32_32_FLOAT render target clearing root signature");
      Shutdown();
      return false;
    }
    D3D12_GRAPHICS_PIPELINE_STATE_DESC uint32_rtv_clear_pipeline_desc = {};
    uint32_rtv_clear_pipeline_desc.pRootSignature = uint32_rtv_clear_root_signature_;
    uint32_rtv_clear_pipeline_desc.VS.pShaderBytecode = shaders::fullscreen_cw_vs;
    uint32_rtv_clear_pipeline_desc.VS.BytecodeLength = sizeof(shaders::fullscreen_cw_vs);
    uint32_rtv_clear_pipeline_desc.PS.pShaderBytecode = shaders::clear_uint2_ps;
    uint32_rtv_clear_pipeline_desc.PS.BytecodeLength = sizeof(shaders::clear_uint2_ps);
    uint32_rtv_clear_pipeline_desc.BlendState.RenderTarget[0].RenderTargetWriteMask =
        D3D12_COLOR_WRITE_ENABLE_ALL;
    uint32_rtv_clear_pipeline_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    uint32_rtv_clear_pipeline_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
    uint32_rtv_clear_pipeline_desc.RasterizerState.DepthClipEnable = TRUE;
    uint32_rtv_clear_pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    uint32_rtv_clear_pipeline_desc.NumRenderTargets = 1;
    for (size_t i = 0; i < 2; ++i) {
      uint32_rtv_clear_pipeline_desc.RTVFormats[0] =
          GetColorOwnershipTransferDXGIFormat(i ? xenos::ColorRenderTargetFormat::k_32_32_FLOAT
                                                : xenos::ColorRenderTargetFormat::k_32_FLOAT);
      for (size_t j = size_t(xenos::MsaaSamples::k1X); j <= size_t(xenos::MsaaSamples::k4X); ++j) {
        if (xenos::MsaaSamples(j) == xenos::MsaaSamples::k2X && !msaa_2x_supported_) {
          uint32_rtv_clear_pipeline_desc.SampleMask = 0b1001;
          uint32_rtv_clear_pipeline_desc.SampleDesc.Count = 4;
        } else {
          uint32_rtv_clear_pipeline_desc.SampleMask = UINT_MAX;
          uint32_rtv_clear_pipeline_desc.SampleDesc.Count = 1 << j;
        }
        ID3D12PipelineState* uint32_rtv_clear_pipeline;
        if (FAILED(device->CreateGraphicsPipelineState(&uint32_rtv_clear_pipeline_desc,
                                                       IID_PPV_ARGS(&uint32_rtv_clear_pipeline)))) {
          REXGPU_ERROR(
              "D3D12RenderTargetCache: Failed to create the {} {}-sample "
              "render target clearing pipeline",
              i ? "k_32_32_FLOAT" : "k_32_FLOAT", uint32_t(1) << j);
          Shutdown();
          return false;
        }
        uint32_rtv_clear_pipelines_[i][j] = uint32_rtv_clear_pipeline;
        auto uint32_rtv_clear_pipeline_name = rex::string::to_utf16(fmt::format(
            "Resolve Clear {} {}xMSAA", i ? "k_32_32_FLOAT" : "k_32_FLOAT", uint32_t(1) << j));
        uint32_rtv_clear_pipeline->SetName(
            reinterpret_cast<LPCWSTR>(uint32_rtv_clear_pipeline_name.c_str()));
      }
    }

    built_shader_.reserve(1024);
  } else if (path_ == Path::kPixelShaderInterlock) {
    gamma_render_target_as_unorm16_ = false;

    depth_float24_round_ = true;
    depth_float24_convert_in_pixel_shader_ = true;

    msaa_2x_supported_ = false;

    std::array<D3D12_ROOT_PARAMETER, 2> resolve_rov_clear_root_parameters;

    resolve_rov_clear_root_parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
    resolve_rov_clear_root_parameters[0].Constants.ShaderRegister = 0;
    resolve_rov_clear_root_parameters[0].Constants.RegisterSpace = 0;

    resolve_rov_clear_root_parameters[0].Constants.Num32BitValues =
        sizeof(draw_util::ResolveClearShaderConstants) / sizeof(uint32_t);
    resolve_rov_clear_root_parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    D3D12_DESCRIPTOR_RANGE resolve_rov_clear_dest_range;
    resolve_rov_clear_dest_range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    resolve_rov_clear_dest_range.NumDescriptors = 1;
    resolve_rov_clear_dest_range.BaseShaderRegister = 0;
    resolve_rov_clear_dest_range.RegisterSpace = 0;
    resolve_rov_clear_dest_range.OffsetInDescriptorsFromTableStart = 0;
    resolve_rov_clear_root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    resolve_rov_clear_root_parameters[1].DescriptorTable.NumDescriptorRanges = 1;
    resolve_rov_clear_root_parameters[1].DescriptorTable.pDescriptorRanges =
        &resolve_rov_clear_dest_range;
    resolve_rov_clear_root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
    D3D12_ROOT_SIGNATURE_DESC resolve_rov_clear_root_signature_desc;
    resolve_rov_clear_root_signature_desc.NumParameters =
        UINT(resolve_rov_clear_root_parameters.size());
    resolve_rov_clear_root_signature_desc.pParameters = resolve_rov_clear_root_parameters.data();
    resolve_rov_clear_root_signature_desc.NumStaticSamplers = 0;
    resolve_rov_clear_root_signature_desc.pStaticSamplers = nullptr;
    resolve_rov_clear_root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
    resolve_rov_clear_root_signature_ =
        ui::d3d12::util::CreateRootSignature(provider, resolve_rov_clear_root_signature_desc);
    if (resolve_rov_clear_root_signature_ == nullptr) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the resolve EDRAM buffer "
          "clear root signature");
      Shutdown();
      return false;
    }

    resolve_rov_clear_32bpp_pipeline_ = ui::d3d12::util::CreateComputePipeline(
        device,
        draw_resolution_scaled ? shaders::resolve_clear_32bpp_scaled_cs
                               : shaders::resolve_clear_32bpp_cs,
        draw_resolution_scaled ? sizeof(shaders::resolve_clear_32bpp_scaled_cs)
                               : sizeof(shaders::resolve_clear_32bpp_cs),
        resolve_rov_clear_root_signature_);
    if (resolve_rov_clear_32bpp_pipeline_ == nullptr) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the 32bpp resolve EDRAM "
          "buffer clear pipeline");
      Shutdown();
      return false;
    }
    resolve_rov_clear_32bpp_pipeline_->SetName(L"Resolve Clear 32bpp");
    resolve_rov_clear_64bpp_pipeline_ = ui::d3d12::util::CreateComputePipeline(
        device,
        draw_resolution_scaled ? shaders::resolve_clear_64bpp_scaled_cs
                               : shaders::resolve_clear_64bpp_cs,
        draw_resolution_scaled ? sizeof(shaders::resolve_clear_64bpp_scaled_cs)
                               : sizeof(shaders::resolve_clear_64bpp_cs),
        resolve_rov_clear_root_signature_);
    if (resolve_rov_clear_64bpp_pipeline_ == nullptr) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create the 64bpp resolve EDRAM "
          "buffer clear pipeline");
      Shutdown();
      return false;
    }
    resolve_rov_clear_64bpp_pipeline_->SetName(L"Resolve Clear 64bpp");
  } else {
    assert_unhandled_case(path_);
    Shutdown();
    return false;
  }

  InitializeCommon();

  return true;
}

void D3D12RenderTargetCache::Shutdown(bool from_destructor) {
  ui::d3d12::util::ReleaseAndNull(resolve_rov_clear_64bpp_pipeline_);
  ui::d3d12::util::ReleaseAndNull(resolve_rov_clear_32bpp_pipeline_);
  ui::d3d12::util::ReleaseAndNull(resolve_rov_clear_root_signature_);

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = size_t(xenos::MsaaSamples::k1X); j <= size_t(xenos::MsaaSamples::k4X); ++j) {
      ui::d3d12::util::ReleaseAndNull(uint32_rtv_clear_pipelines_[i][j]);
    }
  }
  ui::d3d12::util::ReleaseAndNull(uint32_rtv_clear_root_signature_);

  for (const auto& dump_pipeline_pair : dump_pipelines_) {
    if (dump_pipeline_pair.second) {
      dump_pipeline_pair.second->Release();
    }
  }
  dump_pipelines_.clear();
  for (const auto& direct_resolve_pipeline_pair : direct_resolve_pipelines_) {
    bool aliased_resolve_copy_pipeline = false;
    for (ID3D12PipelineState* resolve_copy_pipeline : resolve_copy_pipelines_) {
      if (direct_resolve_pipeline_pair.second == resolve_copy_pipeline) {
        aliased_resolve_copy_pipeline = true;
        break;
      }
    }
    if (direct_resolve_pipeline_pair.second && !aliased_resolve_copy_pipeline) {
      direct_resolve_pipeline_pair.second->Release();
    }
  }
  direct_resolve_pipelines_.clear();
  ui::d3d12::util::ReleaseAndNull(direct_resolve_root_signature_depth_);
  ui::d3d12::util::ReleaseAndNull(direct_resolve_root_signature_color_);
  ui::d3d12::util::ReleaseAndNull(dump_root_signature_depth_);
  ui::d3d12::util::ReleaseAndNull(dump_root_signature_color_);

  for (const auto& transfer_pipeline_array_pair : transfer_stencil_bit_pipelines_) {
    for (ID3D12PipelineState* transfer_pipeline : transfer_pipeline_array_pair.second) {
      if (transfer_pipeline) {
        transfer_pipeline->Release();
      }
    }
  }
  transfer_stencil_bit_pipelines_.clear();
  for (const auto& transfer_pipeline_pair : transfer_pipelines_) {
    if (transfer_pipeline_pair.second) {
      transfer_pipeline_pair.second->Release();
    }
  }
  transfer_pipelines_.clear();
  for (size_t i = 0; i < rex::countof(transfer_root_signatures_); ++i) {
    ui::d3d12::util::ReleaseAndNull(transfer_root_signatures_[i]);
  }

  transfer_vertex_buffer_pool_.reset();

  for (size_t i = 0; i < rex::countof(host_depth_store_pipelines_); ++i) {
    ui::d3d12::util::ReleaseAndNull(host_depth_store_pipelines_[i]);
  }
  ui::d3d12::util::ReleaseAndNull(host_depth_store_root_signature_);

  null_rtv_descriptor_ms_.Free();
  null_rtv_descriptor_ss_.Free();
  descriptor_pool_srv_.reset();
  descriptor_pool_depth_.reset();
  descriptor_pool_color_.reset();

  for (size_t i = 0; i < rex::countof(resolve_copy_pipelines_); ++i) {
    ui::d3d12::util::ReleaseAndNull(resolve_copy_pipelines_[i]);
  }
  ui::d3d12::util::ReleaseAndNull(resolve_copy_root_signature_);

  ui::d3d12::util::ReleaseAndNull(edram_buffer_descriptor_heap_);
  ui::d3d12::util::ReleaseAndNull(edram_buffer_);

  if (!from_destructor) {
    ShutdownCommon();
  }
}

void D3D12RenderTargetCache::CompletedSubmissionUpdated() {
  if (transfer_vertex_buffer_pool_) {
    transfer_vertex_buffer_pool_->Reclaim(command_processor_.GetCompletedSubmission());
  }
}

void D3D12RenderTargetCache::BeginSubmission() {
  InvalidateCommandListRenderTargets();

  if (edram_buffer_modification_status_ != EdramBufferModificationStatus::kUnmodified) {
    assert_true(edram_buffer_state_ == D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
    edram_buffer_modification_status_ = EdramBufferModificationStatus::kUnmodified;
    PixelShaderInterlockFullEdramBarrierPlaced();
  }
}

bool D3D12RenderTargetCache::Update(bool is_rasterization_done,
                                    reg::RB_DEPTHCONTROL normalized_depth_control,
                                    uint32_t normalized_color_mask, const Shader& vertex_shader) {
  if (!RenderTargetCache::Update(is_rasterization_done, normalized_depth_control,
                                 normalized_color_mask, vertex_shader)) {
    return false;
  }
  switch (GetPath()) {
    case Path::kHostRenderTargets: {
      RenderTarget* const* depth_and_color_render_targets =
          last_update_accumulated_render_targets();
      PerformTransfersAndResolveClears(1 + xenos::kMaxColorRenderTargets,
                                       depth_and_color_render_targets, last_update_transfers());
      SetCommandListRenderTargets(depth_and_color_render_targets);
    } break;
    case Path::kPixelShaderInterlock: {
      TransitionEdramBuffer(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

      CommitEdramBufferUAVWrites(EdramBufferModificationStatus::kAsUAV);

      MarkEdramBufferModified(EdramBufferModificationStatus::kAsROV);
    } break;
    default:
      assert_unhandled_case(GetPath());
      return false;
  }
  return true;
}

void D3D12RenderTargetCache::WriteEdramRawSRVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle) {
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  ID3D12Device* device = provider.GetDevice();
  device->CopyDescriptorsSimple(
      1, handle,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kRawSRV)),
      D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void D3D12RenderTargetCache::WriteEdramRawUAVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle) {
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  ID3D12Device* device = provider.GetDevice();
  device->CopyDescriptorsSimple(
      1, handle,
      provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                    uint32_t(EdramBufferDescriptorIndex::kRawUAV)),
      D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void D3D12RenderTargetCache::WriteEdramUintPow2SRVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle,
                                                             uint32_t element_size_bytes_pow2) {
  EdramBufferDescriptorIndex descriptor_index;
  switch (element_size_bytes_pow2) {
    case 2:
      descriptor_index = EdramBufferDescriptorIndex::kR32UintSRV;
      break;
    case 3:
      descriptor_index = EdramBufferDescriptorIndex::kR32G32UintSRV;
      break;
    case 4:
      descriptor_index = EdramBufferDescriptorIndex::kR32G32B32A32UintSRV;
      break;
    default:
      assert_unhandled_case(element_size_bytes_pow2);
      return;
  }
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  ID3D12Device* device = provider.GetDevice();
  device->CopyDescriptorsSimple(1, handle,
                                provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                                              uint32_t(descriptor_index)),
                                D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void D3D12RenderTargetCache::WriteEdramUintPow2UAVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle,
                                                             uint32_t element_size_bytes_pow2) {
  EdramBufferDescriptorIndex descriptor_index;
  switch (element_size_bytes_pow2) {
    case 2:
      descriptor_index = EdramBufferDescriptorIndex::kR32UintUAV;
      break;
    case 3:
      descriptor_index = EdramBufferDescriptorIndex::kR32G32UintUAV;
      break;
    case 4:
      descriptor_index = EdramBufferDescriptorIndex::kR32G32B32A32UintUAV;
      break;
    default:
      assert_unhandled_case(element_size_bytes_pow2);
      return;
  }
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  ID3D12Device* device = provider.GetDevice();
  device->CopyDescriptorsSimple(1, handle,
                                provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                                              uint32_t(descriptor_index)),
                                D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

bool D3D12RenderTargetCache::Resolve(const memory::Memory& memory, D3D12SharedMemory& shared_memory,
                                     D3D12TextureCache& texture_cache,
                                     uint32_t& written_address_out, uint32_t& written_length_out,
                                     reg::RB_COPY_DEST_INFO* copy_dest_info_out) {
  written_address_out = 0;
  written_length_out = 0;

  bool draw_resolution_scaled = IsDrawResolutionScaled();

  draw_util::ResolveInfo resolve_info;
  bool fixed_16_truncated_to_minus_1_to_1 = IsFixed16TruncatedToMinus1To1();
  if (!draw_util::GetResolveInfo(register_file(), memory, draw_resolution_scale_x(),
                                 draw_resolution_scale_y(), fixed_16_truncated_to_minus_1_to_1,
                                 fixed_16_truncated_to_minus_1_to_1, resolve_info)) {
    return false;
  }
  if (copy_dest_info_out) {
    *copy_dest_info_out = resolve_info.copy_dest_info;
  }

  if (!resolve_info.coordinate_info.width_div_8 || !resolve_info.height_div_8) {
    return true;
  }

  DeferredCommandList& command_list = command_processor_.GetDeferredCommandList();

  bool copied = false;
  if (resolve_info.copy_dest_extent_length) {
    draw_util::ResolveCopyShaderConstants copy_shader_constants;
    uint32_t copy_group_count_x, copy_group_count_y;
    draw_util::ResolveCopyShaderIndex copy_shader =
        resolve_info.GetCopyShader(draw_resolution_scale_x(), draw_resolution_scale_y(),
                                   copy_shader_constants, copy_group_count_x, copy_group_count_y);
    assert_true(copy_group_count_x && copy_group_count_y);
    if (copy_shader != draw_util::ResolveCopyShaderIndex::kUnknown) {
      const draw_util::ResolveCopyShaderInfo& copy_shader_info =
          draw_util::resolve_copy_shader_info[size_t(copy_shader)];
      bool direct_resolved = false;

      const bool resolve_native = IsResolveNative(resolve_info);
      if (GetPath() == Path::kHostRenderTargets) {
        if (REXCVAR_GET(direct_host_resolve) && !resolve_native) {
          direct_resolved =
              TryResolveCopyDirectly(resolve_info, copy_shader, draw_resolution_scaled);
          if (direct_resolved) {
            ++direct_resolve_success_count_;
          } else {
            ++direct_resolve_fallback_count_;
          }
        }
        if (!direct_resolved) {
          uint32_t dump_base;
          uint32_t dump_row_length_used;
          uint32_t dump_rows;
          uint32_t dump_pitch;
          resolve_info.GetCopyEdramTileSpan(dump_base, dump_row_length_used, dump_rows, dump_pitch);
          if (!DumpRenderTargets(dump_base, dump_row_length_used, dump_rows, dump_pitch)) {
            REXGPU_ERROR("D3D12RenderTargetCache: Failed to dump host render targets for resolve");
            return false;
          }
        }
      }

      bool copy_dest_committed;
      if (draw_resolution_scaled) {
        copy_dest_committed =
            texture_cache.EnsureScaledResolveMemoryCommitted(
                resolve_info.copy_dest_extent_start, resolve_info.copy_dest_extent_length) &&
            texture_cache.MakeScaledResolveRangeCurrent(resolve_info.copy_dest_base,
                                                        resolve_info.copy_dest_extent_start -
                                                            resolve_info.copy_dest_base +
                                                            resolve_info.copy_dest_extent_length);
      } else {
        copy_dest_committed = shared_memory.RequestRange(resolve_info.copy_dest_extent_start,
                                                         resolve_info.copy_dest_extent_length);
      }
      if (copy_dest_committed) {
        ui::d3d12::util::DescriptorCpuGpuHandlePair descriptor_dest;
        ui::d3d12::util::DescriptorCpuGpuHandlePair descriptor_source;
        ui::d3d12::util::DescriptorCpuGpuHandlePair descriptors[2];
        if (command_processor_.RequestOneUseSingleViewDescriptors(
                bindless_resources_used_ ? uint32_t(draw_resolution_scaled) : 2, descriptors)) {
          if (bindless_resources_used_) {
            if (draw_resolution_scaled) {
              descriptor_dest = descriptors[0];
            } else {
              descriptor_dest = command_processor_.GetSharedMemoryUintPow2BindlessUAVHandlePair(
                  copy_shader_info.dest_bpe_log2);
            }
            if (copy_shader_info.source_is_raw) {
              descriptor_source = command_processor_.GetSystemBindlessViewHandlePair(
                  D3D12CommandProcessor::SystemBindlessView::kEdramRawSRV);
            } else {
              descriptor_source = command_processor_.GetEdramUintPow2BindlessSRVHandlePair(
                  copy_shader_info.source_bpe_log2);
            }
          } else {
            descriptor_dest = descriptors[0];
            if (!draw_resolution_scaled) {
              shared_memory.WriteUintPow2UAVDescriptor(descriptor_dest.first,
                                                       copy_shader_info.dest_bpe_log2);
            }
            descriptor_source = descriptors[1];
            if (copy_shader_info.source_is_raw) {
              WriteEdramRawSRVDescriptor(descriptor_source.first);
            } else {
              WriteEdramUintPow2SRVDescriptor(descriptor_source.first,
                                              copy_shader_info.source_bpe_log2);
            }
          }
          if (draw_resolution_scaled) {
            texture_cache.CreateCurrentScaledResolveRangeUintPow2UAV(
                descriptor_dest.first, copy_shader_info.dest_bpe_log2);
            texture_cache.TransitionCurrentScaledResolveRange(
                D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
          } else {
            shared_memory.UseForWriting();
          }
          TransitionEdramBuffer(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);

          command_list.D3DSetComputeRootSignature(resolve_copy_root_signature_);
          command_list.D3DSetComputeRootDescriptorTable(2, descriptor_source.second);
          command_list.D3DSetComputeRootDescriptorTable(1, descriptor_dest.second);
          if (draw_resolution_scaled) {
            command_list.D3DSetComputeRoot32BitConstants(
                0, sizeof(copy_shader_constants.dest_relative) / sizeof(uint32_t),
                &copy_shader_constants.dest_relative, 0);
          } else {
            command_list.D3DSetComputeRoot32BitConstants(
                0, sizeof(copy_shader_constants) / sizeof(uint32_t), &copy_shader_constants, 0);
          }
          command_processor_.SetExternalPipeline(resolve_copy_pipelines_[size_t(copy_shader)]);
          command_processor_.SubmitBarriers();
          command_list.D3DDispatch(copy_group_count_x, copy_group_count_y, 1);

          if (draw_resolution_scaled) {
            texture_cache.MarkCurrentScaledResolveRangeUAVWritesCommitNeeded();
          } else {
            shared_memory.MarkUAVWritesCommitNeeded();
          }

          texture_cache.MarkRangeAsResolved(resolve_info.copy_dest_extent_start,
                                            resolve_info.copy_dest_extent_length);

          if (resolve_native && shared_memory.RequestRange(resolve_info.copy_dest_extent_start,
                                                           resolve_info.copy_dest_extent_length)) {
            shared_memory.UseForWriting();
            if (command_processor_.DispatchResolveDownscale(
                    resolve_info.copy_dest_extent_start, resolve_info.copy_dest_extent_length,
                    draw_util::GetResolveDownscalePixelSizeLog2(resolve_info.copy_dest_info),
                    IsNativeResolveAveraged(resolve_info)
                        ? D3D12CommandProcessor::ResolveDownscaleMode::kAverage
                        : D3D12CommandProcessor::ResolveDownscaleMode::kCenter,
                    shared_memory.GetBuffer(), resolve_info.copy_dest_extent_start)) {
              shared_memory.MarkUAVWritesCommitNeeded();
              texture_cache.MarkRangeAsNativeResolved(resolve_info.copy_dest_extent_start,
                                                      resolve_info.copy_dest_extent_length);
            }
          }
          written_address_out = resolve_info.copy_dest_extent_start;
          written_length_out = resolve_info.copy_dest_extent_length;
          copied = true;
        }
      } else {
        REXGPU_ERROR(
            "D3D12RenderTargetCache: Failed to obtain the resolve destination "
            "memory region");
      }
    }
  } else {
    copied = true;
  }

  bool cleared = false;
  bool clear_depth = resolve_info.IsClearingDepth();
  bool clear_color = resolve_info.IsClearingColor();
  if (clear_depth || clear_color) {
    switch (GetPath()) {
      case Path::kHostRenderTargets: {
        Transfer::Rectangle clear_rectangle;
        RenderTarget* clear_render_targets[2];

        if (PrepareHostRenderTargetsResolveClear(resolve_info, clear_rectangle,
                                                 clear_render_targets[0], clear_transfers_[0],
                                                 clear_render_targets[1], clear_transfers_[1])) {
          uint64_t clear_values[2];
          clear_values[0] = resolve_info.rb_depth_clear;
          clear_values[1] =
              resolve_info.rb_color_clear | (uint64_t(resolve_info.rb_color_clear_lo) << 32);
          PerformTransfersAndResolveClears(2, clear_render_targets, clear_transfers_, clear_values,
                                           &clear_rectangle);
        }
        cleared = true;
      } break;
      case Path::kPixelShaderInterlock: {
        ui::d3d12::util::DescriptorCpuGpuHandlePair descriptor_edram;
        bool descriptor_edram_obtained;
        if (bindless_resources_used_) {
          descriptor_edram = command_processor_.GetSystemBindlessViewHandlePair(
              D3D12CommandProcessor::SystemBindlessView ::kEdramR32G32B32A32UintUAV);
          descriptor_edram_obtained = true;
        } else {
          descriptor_edram_obtained =
              command_processor_.RequestOneUseSingleViewDescriptors(1, &descriptor_edram);
          if (descriptor_edram_obtained) {
            WriteEdramUintPow2UAVDescriptor(descriptor_edram.first, 4);
          }
        }
        if (descriptor_edram_obtained) {
          TransitionEdramBuffer(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

          CommitEdramBufferUAVWrites();
          command_list.D3DSetComputeRootSignature(resolve_rov_clear_root_signature_);
          command_list.D3DSetComputeRootDescriptorTable(1, descriptor_edram.second);
          std::pair<uint32_t, uint32_t> clear_group_count = resolve_info.GetClearShaderGroupCount(
              draw_resolution_scale_x(), draw_resolution_scale_y());
          assert_true(clear_group_count.first && clear_group_count.second);
          if (clear_depth) {
            draw_util::ResolveClearShaderConstants depth_clear_constants;
            resolve_info.GetDepthClearShaderConstants(depth_clear_constants);
            command_list.D3DSetComputeRoot32BitConstants(
                0, sizeof(depth_clear_constants) / sizeof(uint32_t), &depth_clear_constants, 0);
            command_processor_.SetExternalPipeline(resolve_rov_clear_32bpp_pipeline_);
            command_processor_.SubmitBarriers();
            command_list.D3DDispatch(clear_group_count.first, clear_group_count.second, 1);
          }
          if (clear_color) {
            draw_util::ResolveClearShaderConstants color_clear_constants;
            resolve_info.GetColorClearShaderConstants(color_clear_constants);
            if (clear_depth) {
              command_list.D3DSetComputeRoot32BitConstants(
                  0, sizeof(color_clear_constants.rt_specific) / sizeof(uint32_t),
                  &color_clear_constants.rt_specific,
                  offsetof(draw_util::ResolveClearShaderConstants, rt_specific) / sizeof(uint32_t));
            } else {
              command_list.D3DSetComputeRoot32BitConstants(
                  0, sizeof(color_clear_constants) / sizeof(uint32_t), &color_clear_constants, 0);
            }
            command_processor_.SetExternalPipeline(resolve_info.color_edram_info.format_is_64bpp
                                                       ? resolve_rov_clear_64bpp_pipeline_
                                                       : resolve_rov_clear_32bpp_pipeline_);
            command_processor_.SubmitBarriers();
            command_list.D3DDispatch(clear_group_count.first, clear_group_count.second, 1);
          }
          MarkEdramBufferModified();
          cleared = true;
        }
      } break;
      default:
        assert_unhandled_case(GetPath());
    }
  } else {
    cleared = true;
  }

  return copied && cleared;
}

DXGI_FORMAT D3D12RenderTargetCache::GetColorResourceDXGIFormat(
    xenos::ColorRenderTargetFormat format) const {
  switch (format) {
    case xenos::ColorRenderTargetFormat::k_8_8_8_8:
      return DXGI_FORMAT_R8G8B8A8_UNORM;
    case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA:
      return gamma_render_target_as_unorm16_ ? DXGI_FORMAT_R16G16B16A16_UNORM
                                             : DXGI_FORMAT_R8G8B8A8_UNORM;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10:
      return DXGI_FORMAT_R10G10B10A2_UNORM;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16:
      return DXGI_FORMAT_R16G16B16A16_FLOAT;

    case xenos::ColorRenderTargetFormat::k_16_16:
      return DXGI_FORMAT_R16G16_TYPELESS;
    case xenos::ColorRenderTargetFormat::k_16_16_16_16:
      return DXGI_FORMAT_R16G16B16A16_TYPELESS;

    case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
      return DXGI_FORMAT_R16G16_TYPELESS;
    case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT:
      return DXGI_FORMAT_R16G16B16A16_TYPELESS;

    case xenos::ColorRenderTargetFormat::k_32_FLOAT:
      return DXGI_FORMAT_R32_TYPELESS;
    case xenos::ColorRenderTargetFormat::k_32_32_FLOAT:
      return DXGI_FORMAT_R32G32_TYPELESS;
    default:
      assert_unhandled_case(format);
      return DXGI_FORMAT_UNKNOWN;
  }
}

DXGI_FORMAT D3D12RenderTargetCache::GetColorDrawDXGIFormat(
    xenos::ColorRenderTargetFormat format) const {
  switch (format) {
    case xenos::ColorRenderTargetFormat::k_16_16:
      return DXGI_FORMAT_R16G16_SNORM;
    case xenos::ColorRenderTargetFormat::k_16_16_16_16:
      return DXGI_FORMAT_R16G16B16A16_SNORM;
    case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
      return DXGI_FORMAT_R16G16_FLOAT;
    case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT:
      return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case xenos::ColorRenderTargetFormat::k_32_FLOAT:
      return DXGI_FORMAT_R32_FLOAT;
    case xenos::ColorRenderTargetFormat::k_32_32_FLOAT:
      return DXGI_FORMAT_R32G32_FLOAT;
    default:
      return GetColorResourceDXGIFormat(format);
  }
}

DXGI_FORMAT D3D12RenderTargetCache::GetColorOwnershipTransferDXGIFormat(
    xenos::ColorRenderTargetFormat format, bool* is_integer_out) const {
  if (is_integer_out) {
    *is_integer_out = true;
  }
  switch (format) {
    case xenos::ColorRenderTargetFormat::k_16_16:
    case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
      return DXGI_FORMAT_R16G16_UINT;
    case xenos::ColorRenderTargetFormat::k_16_16_16_16:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT:
      return DXGI_FORMAT_R16G16B16A16_UINT;
    case xenos::ColorRenderTargetFormat::k_32_FLOAT:
      return DXGI_FORMAT_R32_UINT;
    case xenos::ColorRenderTargetFormat::k_32_32_FLOAT:
      return DXGI_FORMAT_R32G32_UINT;
    default:
      if (is_integer_out) {
        *is_integer_out = false;
      }
      return GetColorDrawDXGIFormat(format);
  }
}

DXGI_FORMAT D3D12RenderTargetCache::GetDepthResourceDXGIFormat(
    xenos::DepthRenderTargetFormat format) {
  switch (format) {
    case xenos::DepthRenderTargetFormat::kD24S8:
      return DXGI_FORMAT_R24G8_TYPELESS;
    case xenos::DepthRenderTargetFormat::kD24FS8:
      return DXGI_FORMAT_R32G8X24_TYPELESS;
    default:
      assert_unhandled_case(format);
      return DXGI_FORMAT_UNKNOWN;
  }
}

DXGI_FORMAT D3D12RenderTargetCache::GetDepthDSVDXGIFormat(xenos::DepthRenderTargetFormat format) {
  switch (format) {
    case xenos::DepthRenderTargetFormat::kD24S8:
      return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case xenos::DepthRenderTargetFormat::kD24FS8:
      return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    default:
      assert_unhandled_case(format);
      return DXGI_FORMAT_UNKNOWN;
  }
}

DXGI_FORMAT D3D12RenderTargetCache::GetDepthSRVDepthDXGIFormat(
    xenos::DepthRenderTargetFormat format) {
  switch (format) {
    case xenos::DepthRenderTargetFormat::kD24S8:
      return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    case xenos::DepthRenderTargetFormat::kD24FS8:
      return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
    default:
      assert_unhandled_case(format);
      return DXGI_FORMAT_UNKNOWN;
  }
}

DXGI_FORMAT D3D12RenderTargetCache::GetDepthSRVStencilDXGIFormat(
    xenos::DepthRenderTargetFormat format) {
  switch (format) {
    case xenos::DepthRenderTargetFormat::kD24S8:
      return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
    case xenos::DepthRenderTargetFormat::kD24FS8:
      return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
    default:
      assert_unhandled_case(format);
      return DXGI_FORMAT_UNKNOWN;
  }
}

RenderTargetCache::RenderTarget* D3D12RenderTargetCache::CreateRenderTarget(RenderTargetKey key) {
  ID3D12Device* device = command_processor_.GetD3D12Provider().GetDevice();

  D3D12_RESOURCE_DESC resource_desc;
  resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Alignment = 0;
  resource_desc.Width = key.GetWidth() * draw_resolution_scale_x();
  resource_desc.Height =
      GetRenderTargetHeight(key.pitch_tiles_at_32bpp, key.msaa_samples) * draw_resolution_scale_y();
  resource_desc.DepthOrArraySize = 1;
  resource_desc.MipLevels = 1;
  if (key.is_depth) {
    resource_desc.Format = GetDepthResourceDXGIFormat(key.GetDepthFormat());
  } else {
    resource_desc.Format = GetColorResourceDXGIFormat(key.GetColorFormat());
  }
  assert_true(resource_desc.Format != DXGI_FORMAT_UNKNOWN);
  if (resource_desc.Format == DXGI_FORMAT_UNKNOWN) {
    REXGPU_ERROR("D3D12RenderTargetCache: Unknown {} render target format {}",
                 key.is_depth ? "depth" : "color", uint32_t(key.resource_format));
    return nullptr;
  }
  if (key.msaa_samples == xenos::MsaaSamples::k2X && !msaa_2x_supported()) {
    resource_desc.SampleDesc.Count = 4;
  } else {
    resource_desc.SampleDesc.Count = UINT(1) << UINT(key.msaa_samples);
  }
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags = key.is_depth ? D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
                                     : D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

  D3D12_RESOURCE_STATES resource_state =
      key.is_depth ? D3D12_RESOURCE_STATE_DEPTH_WRITE : D3D12_RESOURCE_STATE_RENDER_TARGET;
  D3D12_CLEAR_VALUE optimized_clear_value;
  if (key.is_depth) {
    optimized_clear_value.Format = GetDepthDSVDXGIFormat(key.GetDepthFormat());

    optimized_clear_value.DepthStencil.Depth =
        key.GetDepthFormat() == xenos::DepthRenderTargetFormat::kD24S8 ? 1.0f : 0.0f;
    optimized_clear_value.DepthStencil.Stencil = 0;
  } else {
    optimized_clear_value.Format = GetColorDrawDXGIFormat(key.GetColorFormat());
    optimized_clear_value.Color[0] = 0.0f;
    optimized_clear_value.Color[1] = 0.0f;
    optimized_clear_value.Color[2] = 0.0f;
    optimized_clear_value.Color[3] = 0.0f;
  }

  Microsoft::WRL::ComPtr<ID3D12Resource> resource;
  if (FAILED(device->CreateCommittedResource(&ui::d3d12::util::kHeapPropertiesDefault,
                                             D3D12_HEAP_FLAG_NONE, &resource_desc, resource_state,
                                             &optimized_clear_value, IID_PPV_ARGS(&resource)))) {
    return nullptr;
  }
  {
    std::u16string resource_name = rex::string::to_utf16(key.GetDebugName());
    resource->SetName(reinterpret_cast<LPCWSTR>(resource_name.c_str()));
  }

  ui::d3d12::D3D12CpuDescriptorPool& descriptor_pool =
      key.is_depth ? *descriptor_pool_depth_ : *descriptor_pool_color_;
  ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_draw =
      descriptor_pool.AllocateDescriptor();
  ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_srv =
      descriptor_pool_srv_->AllocateDescriptor();
  if (!descriptor_draw.IsValid() || !descriptor_srv.IsValid()) {
    return nullptr;
  }
  D3D12_CPU_DESCRIPTOR_HANDLE descriptor_draw_handle = descriptor_draw.GetHandle();
  ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_load_separate;
  ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_srv_stencil;
  D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc;
  srv_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  if (resource_desc.SampleDesc.Count > 1) {
    srv_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
  } else {
    srv_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MostDetailedMip = 0;
    srv_desc.Texture2D.MipLevels = 1;
    srv_desc.Texture2D.PlaneSlice = 0;
    srv_desc.Texture2D.ResourceMinLODClamp = 0.0f;
  }
  if (key.is_depth) {
    descriptor_srv_stencil = descriptor_pool_srv_->AllocateDescriptor();
    if (!descriptor_srv_stencil.IsValid()) {
      return nullptr;
    }
    D3D12_DEPTH_STENCIL_VIEW_DESC dsv_desc;
    dsv_desc.Format = optimized_clear_value.Format;
    dsv_desc.Flags = D3D12_DSV_FLAG_NONE;
    D3D12_SHADER_RESOURCE_VIEW_DESC stencil_srv_desc;
    stencil_srv_desc.Format = GetDepthSRVStencilDXGIFormat(key.GetDepthFormat());
    stencil_srv_desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    if (resource_desc.SampleDesc.Count > 1) {
      dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;
      stencil_srv_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
    } else {
      dsv_desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
      dsv_desc.Texture2D.MipSlice = 0;
      stencil_srv_desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
      stencil_srv_desc.Texture2D.MostDetailedMip = 0;
      stencil_srv_desc.Texture2D.MipLevels = 1;
      stencil_srv_desc.Texture2D.PlaneSlice = 1;
      stencil_srv_desc.Texture2D.ResourceMinLODClamp = 0.0f;
    }
    device->CreateDepthStencilView(resource.Get(), &dsv_desc, descriptor_draw_handle);
    device->CreateShaderResourceView(resource.Get(), &stencil_srv_desc,
                                     descriptor_srv_stencil.GetHandle());

    srv_desc.Format = GetDepthSRVDepthDXGIFormat(key.GetDepthFormat());
  } else {
    D3D12_RENDER_TARGET_VIEW_DESC rtv_desc;
    rtv_desc.Format = optimized_clear_value.Format;
    if (resource_desc.SampleDesc.Count > 1) {
      rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
    } else {
      rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
      rtv_desc.Texture2D.MipSlice = 0;
      rtv_desc.Texture2D.PlaneSlice = 0;
    }
    device->CreateRenderTargetView(resource.Get(), &rtv_desc, descriptor_draw_handle);

    DXGI_FORMAT load_format = GetColorOwnershipTransferDXGIFormat(key.GetColorFormat());
    if (rtv_desc.Format != load_format) {
      descriptor_load_separate = descriptor_pool.AllocateDescriptor();
      if (!descriptor_load_separate.IsValid()) {
        return nullptr;
      }
      rtv_desc.Format = load_format;
      device->CreateRenderTargetView(resource.Get(), &rtv_desc,
                                     descriptor_load_separate.GetHandle());
    }

    srv_desc.Format = load_format;
  }
  device->CreateShaderResourceView(resource.Get(), &srv_desc, descriptor_srv.GetHandle());

  return new D3D12RenderTarget(key, resource.Get(), std::move(descriptor_draw),
                               std::move(descriptor_load_separate), std::move(descriptor_srv),
                               std::move(descriptor_srv_stencil), resource_state);
}

bool D3D12RenderTargetCache::IsHostDepthEncodingDifferent(
    xenos::DepthRenderTargetFormat format) const {
  if (format == xenos::DepthRenderTargetFormat::kD24FS8) {
    return !depth_float24_convert_in_pixel_shader_;
  }
  return false;
}

bool D3D12RenderTargetCache::IsGammaFormatHostStorageSeparate() const {
  return gamma_render_target_as_unorm16_;
}

void D3D12RenderTargetCache::RequestPixelShaderInterlockBarrier() {
  CommitEdramBufferUAVWrites();
}

void D3D12RenderTargetCache::TransitionEdramBuffer(D3D12_RESOURCE_STATES new_state) {
  if (command_processor_.PushTransitionBarrier(edram_buffer_, edram_buffer_state_, new_state)) {
    edram_buffer_modification_status_ = EdramBufferModificationStatus::kUnmodified;
  }
  edram_buffer_state_ = new_state;
}

void D3D12RenderTargetCache::MarkEdramBufferModified(
    EdramBufferModificationStatus modification_status) {
  assert_true(modification_status != EdramBufferModificationStatus::kUnmodified);
  assert_true(edram_buffer_state_ == D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
  if (edram_buffer_state_ != D3D12_RESOURCE_STATE_UNORDERED_ACCESS) {
    return;
  }

  edram_buffer_modification_status_ =
      std::max(edram_buffer_modification_status_, modification_status);
}

void D3D12RenderTargetCache::CommitEdramBufferUAVWrites(
    EdramBufferModificationStatus commit_status) {
  assert_true(commit_status != EdramBufferModificationStatus::kUnmodified);
  if (edram_buffer_modification_status_ < commit_status) {
    return;
  }
  assert_true(edram_buffer_state_ == D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
  if (edram_buffer_state_ == D3D12_RESOURCE_STATE_UNORDERED_ACCESS) {
    command_processor_.PushUAVBarrier(edram_buffer_);
  }
  edram_buffer_modification_status_ = EdramBufferModificationStatus::kUnmodified;
  PixelShaderInterlockFullEdramBarrierPlaced();
}
}
