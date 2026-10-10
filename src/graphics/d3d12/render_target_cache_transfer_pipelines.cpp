

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

static void CanonicalizeSample(dxbc::Assembler& a, xenos::MsaaSamples msaa_samples,
                               dxbc::Src host_sample, bool msaa_2x_supported, uint32_t scale_x,
                               uint32_t scale_y, dxbc::Src& u_out, dxbc::Src& v_out,
                               bool& scaled_out) {
  bool scaled = scale_x > 1 || scale_y > 1;
  scaled_out = scaled;
  dxbc::Src guest_x(dxbc::Src::R(0, dxbc::Src::kXXXX));
  dxbc::Src guest_y(dxbc::Src::R(0, dxbc::Src::kYYYY));
  if (scaled) {
    a.OpUDiv(dxbc::Dest::R(1, 0b0011), dxbc::Dest::R(2, 0b0011), dxbc::Src::R(0, dxbc::Src::kXYXY),
             dxbc::Src::LU(scale_x, scale_y, scale_x, scale_y));
    guest_x = dxbc::Src::R(1, dxbc::Src::kXXXX);
    guest_y = dxbc::Src::R(1, dxbc::Src::kYYYY);
  }
  u_out = guest_x;
  v_out = guest_y;
  if (msaa_samples >= xenos::MsaaSamples::k4X) {
    a.OpBFI(dxbc::Dest::R(2, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1), host_sample, guest_x);

    a.OpUShR(dxbc::Dest::R(2, 0b1000), guest_x, dxbc::Src::LU(1));

    a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(30), dxbc::Src::LU(2),
            dxbc::Src::R(2, dxbc::Src::kWWWW), dxbc::Src::R(2, dxbc::Src::kZZZZ));

    a.OpUShR(dxbc::Dest::R(2, 0b0100), host_sample, dxbc::Src::LU(1));

    a.OpBFI(dxbc::Dest::R(2, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kZZZZ), guest_y);

    a.OpUShR(dxbc::Dest::R(2, 0b1000), guest_y, dxbc::Src::LU(1));

    a.OpBFI(dxbc::Dest::R(1, 0b0010), dxbc::Src::LU(30), dxbc::Src::LU(2),
            dxbc::Src::R(2, dxbc::Src::kWWWW), dxbc::Src::R(2, dxbc::Src::kZZZZ));
    u_out = dxbc::Src::R(1, dxbc::Src::kXXXX);
    v_out = dxbc::Src::R(1, dxbc::Src::kYYYY);
  } else if (msaa_samples == xenos::MsaaSamples::k2X) {
    if (msaa_2x_supported) {
      a.OpXOr(dxbc::Dest::R(2, 0b0100), host_sample, dxbc::Src::LU(1));
    } else {
      a.OpUShR(dxbc::Dest::R(2, 0b0100), host_sample, dxbc::Src::LU(1));
    }

    a.OpUShR(dxbc::Dest::R(2, 0b1000), guest_x, dxbc::Src::LU(1));

    a.OpBFI(dxbc::Dest::R(2, 0b1000), dxbc::Src::LU(1), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kWWWW), guest_y);

    a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(1), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kZZZZ), guest_x);

    a.OpUShR(dxbc::Dest::R(2, 0b0100), guest_y, dxbc::Src::LU(1));

    a.OpBFI(dxbc::Dest::R(1, 0b0010), dxbc::Src::LU(30), dxbc::Src::LU(2),
            dxbc::Src::R(2, dxbc::Src::kZZZZ), dxbc::Src::R(2, dxbc::Src::kWWWW));
    u_out = dxbc::Src::R(1, dxbc::Src::kXXXX);
    v_out = dxbc::Src::R(1, dxbc::Src::kYYYY);
  }
}

static void DecanonicalizeSample(dxbc::Assembler& a, xenos::MsaaSamples msaa_samples, dxbc::Src u,
                                 dxbc::Src v, bool scaled, bool msaa_2x_supported, uint32_t scale_x,
                                 uint32_t scale_y, dxbc::Src& x_out, dxbc::Src& y_out,
                                 dxbc::Src& sample_out) {
  x_out = u;
  y_out = v;
  if (msaa_samples >= xenos::MsaaSamples::k4X) {
    a.OpUBFE(dxbc::Dest::R(2, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1), u);

    a.OpAnd(dxbc::Dest::R(2, 0b1000), v, dxbc::Src::LU(2));

    a.OpOr(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(2, dxbc::Src::kZZZZ),
           dxbc::Src::R(2, dxbc::Src::kWWWW));
    sample_out = dxbc::Src::R(1, dxbc::Src::kZZZZ);

    a.OpUShR(dxbc::Dest::R(2, 0b0100), u, dxbc::Src::LU(2));

    a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(31), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kZZZZ), u);

    a.OpUShR(dxbc::Dest::R(2, 0b1000), v, dxbc::Src::LU(2));

    a.OpBFI(dxbc::Dest::R(1, 0b0010), dxbc::Src::LU(31), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kWWWW), v);
    x_out = dxbc::Src::R(1, dxbc::Src::kXXXX);
    y_out = dxbc::Src::R(1, dxbc::Src::kYYYY);
  } else if (msaa_samples == xenos::MsaaSamples::k2X) {
    a.OpUBFE(dxbc::Dest::R(2, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1), u);

    if (msaa_2x_supported) {
      a.OpXOr(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(2, dxbc::Src::kZZZZ), dxbc::Src::LU(1));
    } else {
      a.OpBFI(dxbc::Dest::R(1, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1),
              dxbc::Src::R(2, dxbc::Src::kZZZZ), dxbc::Src::R(2, dxbc::Src::kZZZZ));
    }
    sample_out = dxbc::Src::R(1, dxbc::Src::kZZZZ);

    a.OpUShR(dxbc::Dest::R(2, 0b1000), v, dxbc::Src::LU(1));

    a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(1), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kWWWW), u);

    a.OpUShR(dxbc::Dest::R(2, 0b1000), v, dxbc::Src::LU(2));

    a.OpBFI(dxbc::Dest::R(1, 0b0010), dxbc::Src::LU(31), dxbc::Src::LU(1),
            dxbc::Src::R(2, dxbc::Src::kWWWW), v);
    x_out = dxbc::Src::R(1, dxbc::Src::kXXXX);
    y_out = dxbc::Src::R(1, dxbc::Src::kYYYY);
  }
  if (scaled) {
    a.OpUMAd(dxbc::Dest::R(1, 0b0011), dxbc::Src::R(1), dxbc::Src::LU(scale_x, scale_y, 1, 1),
             dxbc::Src::R(2));
    x_out = dxbc::Src::R(1, dxbc::Src::kXXXX);
    y_out = dxbc::Src::R(1, dxbc::Src::kYYYY);
  }
}

ID3D12PipelineState* const* D3D12RenderTargetCache::GetOrCreateTransferPipelines(
    TransferShaderKey key) {
  const TransferModeInfo& mode = kTransferModes[size_t(key.mode)];
  bool dest_is_stencil_bit = (mode.output == TransferOutput::kStencilBit);

  if (dest_is_stencil_bit) {
    auto pipelines_it = transfer_stencil_bit_pipelines_.find(key);
    if (pipelines_it != transfer_stencil_bit_pipelines_.end()) {
      return pipelines_it->second[0] ? pipelines_it->second.data() : nullptr;
    }
  } else {
    auto pipeline_it = transfer_pipelines_.find(key);
    if (pipeline_it != transfer_pipelines_.end()) {
      return pipeline_it->second ? &pipeline_it->second : nullptr;
    }
  }

  uint32_t rs = kTransferUsedRootParameters[size_t(use_stencil_reference_output_
                                                       ? mode.root_signature_with_stencil_ref
                                                       : mode.root_signature_no_stencil_ref)];

  bool dest_is_color = (mode.output == TransferOutput::kColor);

  xenos::ColorRenderTargetFormat dest_color_format =
      xenos::ColorRenderTargetFormat(key.dest_resource_format);
  xenos::DepthRenderTargetFormat dest_depth_format =
      xenos::DepthRenderTargetFormat(key.dest_resource_format);
  bool dest_is_64bpp = dest_is_color && xenos::IsColorRenderTargetFormat64bpp(dest_color_format);

  xenos::ColorRenderTargetFormat source_color_format =
      xenos::ColorRenderTargetFormat(key.source_resource_format);
  xenos::DepthRenderTargetFormat source_depth_format =
      xenos::DepthRenderTargetFormat(key.source_resource_format);

  bool source_is_color = (rs & kTransferUsedRootParameterColorSRVBit) != 0;
  bool source_is_64bpp;
  uint32_t source_color_format_component_count;
  uint32_t source_color_srv_component_mask;
  bool source_color_is_uint;
  if (source_is_color) {
    assert_zero(rs & kTransferUsedRootParameterDepthSRVBit);
    assert_zero(rs & kTransferUsedRootParameterStencilSRVBit);
    source_is_64bpp = xenos::IsColorRenderTargetFormat64bpp(source_color_format);
    source_color_format_component_count =
        xenos::GetColorRenderTargetFormatComponentCount(source_color_format);
    if (dest_is_stencil_bit) {
      if (source_is_64bpp && !dest_is_64bpp) {
        source_color_srv_component_mask = 0b1 | (0b1 << (source_color_format_component_count >> 1));
      } else {
        source_color_srv_component_mask = 0b1;
      }
    } else {
      source_color_srv_component_mask = (uint32_t(1) << source_color_format_component_count) - 1;
    }
    GetColorOwnershipTransferDXGIFormat(source_color_format, &source_color_is_uint);
  } else {
    source_is_64bpp = false;
    source_color_format_component_count = 0;
    source_color_srv_component_mask = 0;
    source_color_is_uint = false;
  }

  bool shader_uses_stencil_reference_output =
      mode.output == TransferOutput::kDepth && use_stencil_reference_output_;

  built_shader_.clear();

  uint32_t blob_count = 5 + uint32_t(shader_uses_stencil_reference_output);

  built_shader_.resize(sizeof(dxbc::ContainerHeader) / sizeof(uint32_t) + blob_count);
  uint32_t blob_offset_position_dwords = sizeof(dxbc::ContainerHeader) / sizeof(uint32_t);
  uint32_t blob_position_dwords = uint32_t(built_shader_.size());
  constexpr uint32_t kBlobHeaderSizeDwords = sizeof(dxbc::BlobHeader) / sizeof(uint32_t);

  uint32_t name_ptr;

  built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t rdef_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;

  built_shader_.resize(rdef_position_dwords + sizeof(dxbc::RdefHeader) / sizeof(uint32_t));

  dxbc::AppendAlignedString(built_shader_, "Xenia");

  name_ptr = uint32_t((built_shader_.size() - rdef_position_dwords) * sizeof(uint32_t));
  uint32_t rdef_dword_name_ptr = name_ptr;
  name_ptr += dxbc::AppendAlignedString(built_shader_, "dword");

  uint32_t rdef_type_uint_position_dwords = uint32_t(built_shader_.size());
  uint32_t rdef_type_uint_ptr =
      uint32_t((rdef_type_uint_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
  built_shader_.resize(rdef_type_uint_position_dwords + sizeof(dxbc::RdefType) / sizeof(uint32_t));
  {
    auto& rdef_type_uint =
        *reinterpret_cast<dxbc::RdefType*>(built_shader_.data() + rdef_type_uint_position_dwords);
    rdef_type_uint.variable_class = dxbc::RdefVariableClass::kScalar;
    rdef_type_uint.variable_type = dxbc::RdefVariableType::kUInt;
    rdef_type_uint.row_count = 1;
    rdef_type_uint.column_count = 1;
    rdef_type_uint.name_ptr = rdef_dword_name_ptr;
  }

  uint32_t rdef_constant_count = 0;
  uint32_t rdef_constant_index_stencil_mask =
      (rs & kTransferUsedRootParameterStencilMaskConstantBit) ? rdef_constant_count++ : UINT32_MAX;
  assert_false(dest_is_stencil_bit && rdef_constant_index_stencil_mask == UINT32_MAX);
  uint32_t rdef_constant_index_address =
      (rs & kTransferUsedRootParameterAddressConstantBit) ? rdef_constant_count++ : UINT32_MAX;
  assert_true(rdef_constant_index_address != UINT32_MAX);
  uint32_t rdef_constant_index_host_depth_address =
      (rs & kTransferUsedRootParameterHostDepthAddressConstantBit) ? rdef_constant_count++
                                                                   : UINT32_MAX;

  name_ptr = uint32_t((built_shader_.size() - rdef_position_dwords) * sizeof(uint32_t));
  uint32_t rdef_xe_transfer_stencil_mask_name_ptr = name_ptr;
  if (rdef_constant_index_stencil_mask != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_stencil_mask");
  }
  uint32_t rdef_xe_transfer_address_name_ptr = name_ptr;
  if (rdef_constant_index_address != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_address");
  }
  uint32_t rdef_xe_transfer_host_depth_address_name_ptr = name_ptr;
  if (rdef_constant_index_host_depth_address != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_host_depth_address");
  }

  uint32_t rdef_constants_position_dwords = uint32_t(built_shader_.size());
  uint32_t rdef_constants_ptr =
      uint32_t((rdef_constants_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
  built_shader_.resize(rdef_constants_position_dwords +
                       sizeof(dxbc::RdefVariable) / sizeof(uint32_t) * rdef_constant_count);
  {
    auto rdef_constants = reinterpret_cast<dxbc::RdefVariable*>(built_shader_.data() +
                                                                rdef_constants_position_dwords);

    if (rdef_constant_index_stencil_mask != UINT32_MAX) {
      dxbc::RdefVariable& rdef_constant_stencil_mask =
          rdef_constants[rdef_constant_index_stencil_mask];
      rdef_constant_stencil_mask.name_ptr = rdef_xe_transfer_stencil_mask_name_ptr;
      rdef_constant_stencil_mask.size_bytes = sizeof(uint32_t);
      rdef_constant_stencil_mask.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_stencil_mask.type_ptr = rdef_type_uint_ptr;
      rdef_constant_stencil_mask.start_texture = UINT32_MAX;
      rdef_constant_stencil_mask.start_sampler = UINT32_MAX;
    }

    if (rdef_constant_index_address != UINT32_MAX) {
      dxbc::RdefVariable& rdef_constant_address = rdef_constants[rdef_constant_index_address];
      rdef_constant_address.name_ptr = rdef_xe_transfer_address_name_ptr;
      rdef_constant_address.size_bytes = sizeof(uint32_t);
      rdef_constant_address.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_address.type_ptr = rdef_type_uint_ptr;
      rdef_constant_address.start_texture = UINT32_MAX;
      rdef_constant_address.start_sampler = UINT32_MAX;
    }

    if (rdef_constant_index_host_depth_address != UINT32_MAX) {
      dxbc::RdefVariable& rdef_constant_host_depth_address =
          rdef_constants[rdef_constant_index_host_depth_address];
      rdef_constant_host_depth_address.name_ptr = rdef_xe_transfer_host_depth_address_name_ptr;
      rdef_constant_host_depth_address.size_bytes = sizeof(uint32_t);
      rdef_constant_host_depth_address.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_host_depth_address.type_ptr = rdef_type_uint_ptr;
      rdef_constant_host_depth_address.start_texture = UINT32_MAX;
      rdef_constant_host_depth_address.start_sampler = UINT32_MAX;
    }
  }

  uint32_t rdef_cbuffer_count = 0;
  uint32_t cbuffer_index_stencil_mask =
      rdef_constant_index_stencil_mask != UINT32_MAX ? rdef_cbuffer_count++ : UINT32_MAX;
  uint32_t cbuffer_index_address =
      rdef_constant_index_address != UINT32_MAX ? rdef_cbuffer_count++ : UINT32_MAX;
  uint32_t cbuffer_index_host_depth_address =
      rdef_constant_index_host_depth_address != UINT32_MAX ? rdef_cbuffer_count++ : UINT32_MAX;
  uint32_t rdef_cbuffer_position_dwords = uint32_t(built_shader_.size());
  built_shader_.resize(rdef_cbuffer_position_dwords +
                       sizeof(dxbc::RdefCbuffer) / sizeof(uint32_t) * rdef_cbuffer_count);
  {
    auto rdef_cbuffers =
        reinterpret_cast<dxbc::RdefCbuffer*>(built_shader_.data() + rdef_cbuffer_position_dwords);

    if (cbuffer_index_stencil_mask != UINT32_MAX) {
      dxbc::RdefCbuffer& rdef_cbuffer_stencil_mask = rdef_cbuffers[cbuffer_index_stencil_mask];
      rdef_cbuffer_stencil_mask.name_ptr = rdef_xe_transfer_stencil_mask_name_ptr;
      rdef_cbuffer_stencil_mask.variable_count = 1;
      rdef_cbuffer_stencil_mask.variables_ptr = uint32_t(
          rdef_constants_ptr + sizeof(dxbc::RdefVariable) * rdef_constant_index_stencil_mask);
      rdef_cbuffer_stencil_mask.size_vector_aligned_bytes = sizeof(uint32_t) * 4;
    }

    if (cbuffer_index_address != UINT32_MAX) {
      dxbc::RdefCbuffer& rdef_cbuffer_address = rdef_cbuffers[cbuffer_index_address];
      rdef_cbuffer_address.name_ptr = rdef_xe_transfer_address_name_ptr;
      rdef_cbuffer_address.variable_count = 1;
      rdef_cbuffer_address.variables_ptr =
          uint32_t(rdef_constants_ptr + sizeof(dxbc::RdefVariable) * rdef_constant_index_address);
      rdef_cbuffer_address.size_vector_aligned_bytes = sizeof(uint32_t) * 4;
    }

    if (cbuffer_index_host_depth_address != UINT32_MAX) {
      dxbc::RdefCbuffer& rdef_cbuffer_host_depth_address =
          rdef_cbuffers[cbuffer_index_host_depth_address];
      rdef_cbuffer_host_depth_address.name_ptr = rdef_xe_transfer_host_depth_address_name_ptr;
      rdef_cbuffer_host_depth_address.variable_count = 1;
      rdef_cbuffer_host_depth_address.variables_ptr = uint32_t(
          rdef_constants_ptr + sizeof(dxbc::RdefVariable) * rdef_constant_index_host_depth_address);
      rdef_cbuffer_host_depth_address.size_vector_aligned_bytes = sizeof(uint32_t) * 4;
    }
  }

  uint32_t rdef_srv_count = 0;
  uint32_t srv_index_color =
      (rs & kTransferUsedRootParameterColorSRVBit) ? rdef_srv_count++ : UINT32_MAX;
  uint32_t srv_index_depth =
      (rs & kTransferUsedRootParameterDepthSRVBit) ? rdef_srv_count++ : UINT32_MAX;
  uint32_t srv_index_stencil =
      (rs & kTransferUsedRootParameterStencilSRVBit) ? rdef_srv_count++ : UINT32_MAX;
  uint32_t srv_index_host_depth =
      (rs & kTransferUsedRootParameterHostDepthSRVBit) ? rdef_srv_count++ : UINT32_MAX;
  uint32_t rdef_binding_count = rdef_srv_count + rdef_cbuffer_count;

  name_ptr = uint32_t((built_shader_.size() - rdef_position_dwords) * sizeof(uint32_t));
  uint32_t rdef_xe_transfer_color_name_ptr = name_ptr;
  if (srv_index_color != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_color");
  }
  uint32_t rdef_xe_transfer_depth_name_ptr = name_ptr;
  if (srv_index_depth != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_depth");
  }
  uint32_t rdef_xe_transfer_stencil_name_ptr = name_ptr;
  if (srv_index_stencil != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_stencil");
  }
  uint32_t rdef_xe_transfer_host_depth_name_ptr = name_ptr;
  if (srv_index_host_depth != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_transfer_host_depth");
  }

  uint32_t rdef_binding_position_dwords = uint32_t(built_shader_.size());
  built_shader_.resize(rdef_binding_position_dwords +
                       sizeof(dxbc::RdefInputBind) / sizeof(uint32_t) * rdef_binding_count);
  {
    auto rdef_bindings =
        reinterpret_cast<dxbc::RdefInputBind*>(built_shader_.data() + rdef_binding_position_dwords);
    uint32_t rdef_binding_index = 0;

    if (srv_index_color != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_color = rdef_bindings[rdef_binding_index++];
      rdef_binding_color.name_ptr = rdef_xe_transfer_color_name_ptr;
      rdef_binding_color.type = dxbc::RdefInputType::kTexture;
      rdef_binding_color.return_type =
          source_color_is_uint ? dxbc::ResourceReturnType::kUInt : dxbc::ResourceReturnType::kFloat;
      if (key.source_msaa_samples != xenos::MsaaSamples::k1X) {
        rdef_binding_color.dimension = dxbc::RdefDimension::kSRVTexture2DMS;
      } else {
        rdef_binding_color.dimension = dxbc::RdefDimension::kSRVTexture2D;
        rdef_binding_color.sample_count = UINT32_MAX;
      }
      rdef_binding_color.bind_point = kTransferSRVRegisterColor;
      rdef_binding_color.bind_count = 1;
      assert_not_zero(source_color_srv_component_mask);
      rdef_binding_color.flags = (32 - rex::lzcnt(source_color_srv_component_mask) - 1)
                                 << dxbc::kRdefInputFlagsComponentsShift;
      rdef_binding_color.id = srv_index_color;
    }

    if (srv_index_depth != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_depth = rdef_bindings[rdef_binding_index++];
      rdef_binding_depth.name_ptr = rdef_xe_transfer_depth_name_ptr;
      rdef_binding_depth.type = dxbc::RdefInputType::kTexture;
      rdef_binding_depth.return_type = dxbc::ResourceReturnType::kFloat;
      if (key.source_msaa_samples != xenos::MsaaSamples::k1X) {
        rdef_binding_depth.dimension = dxbc::RdefDimension::kSRVTexture2DMS;
      } else {
        rdef_binding_depth.dimension = dxbc::RdefDimension::kSRVTexture2D;
        rdef_binding_depth.sample_count = UINT32_MAX;
      }
      rdef_binding_depth.bind_point = kTransferSRVRegisterDepth;
      rdef_binding_depth.bind_count = 1;
      rdef_binding_depth.id = srv_index_depth;
    }

    if (srv_index_stencil != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_stencil = rdef_bindings[rdef_binding_index++];
      rdef_binding_stencil.name_ptr = rdef_xe_transfer_stencil_name_ptr;
      rdef_binding_stencil.type = dxbc::RdefInputType::kTexture;
      rdef_binding_stencil.return_type = dxbc::ResourceReturnType::kUInt;
      if (key.source_msaa_samples != xenos::MsaaSamples::k1X) {
        rdef_binding_stencil.dimension = dxbc::RdefDimension::kSRVTexture2DMS;
      } else {
        rdef_binding_stencil.dimension = dxbc::RdefDimension::kSRVTexture2D;
        rdef_binding_stencil.sample_count = UINT32_MAX;
      }
      rdef_binding_stencil.bind_point = kTransferSRVRegisterStencil;
      rdef_binding_stencil.bind_count = 1;
      rdef_binding_stencil.flags = dxbc::kRdefInputFlags2Component;
      rdef_binding_stencil.id = srv_index_stencil;
    }

    if (srv_index_host_depth != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_host_depth = rdef_bindings[rdef_binding_index++];
      rdef_binding_host_depth.name_ptr = rdef_xe_transfer_host_depth_name_ptr;
      rdef_binding_host_depth.type = dxbc::RdefInputType::kTexture;
      if (key.host_depth_source_is_copy) {
        rdef_binding_host_depth.return_type = dxbc::ResourceReturnType::kUInt;
        rdef_binding_host_depth.dimension = dxbc::RdefDimension::kSRVBuffer;
        rdef_binding_host_depth.sample_count = UINT32_MAX;
      } else {
        rdef_binding_host_depth.return_type = dxbc::ResourceReturnType::kFloat;
        if (key.host_depth_source_msaa_samples != xenos::MsaaSamples::k1X) {
          rdef_binding_host_depth.dimension = dxbc::RdefDimension::kSRVTexture2DMS;
        } else {
          rdef_binding_host_depth.dimension = dxbc::RdefDimension::kSRVTexture2D;
          rdef_binding_host_depth.sample_count = UINT32_MAX;
        }
      }
      rdef_binding_host_depth.bind_point = kTransferSRVRegisterHostDepth;
      rdef_binding_host_depth.bind_count = 1;
      rdef_binding_host_depth.id = srv_index_host_depth;
    }

    if (cbuffer_index_stencil_mask != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_stencil_mask = rdef_bindings[rdef_binding_index++];
      rdef_binding_stencil_mask.name_ptr = rdef_xe_transfer_stencil_mask_name_ptr;
      rdef_binding_stencil_mask.type = dxbc::RdefInputType::kCbuffer;
      rdef_binding_stencil_mask.bind_point = kTransferCBVRegisterStencilMask;
      rdef_binding_stencil_mask.bind_count = 1;
      rdef_binding_stencil_mask.flags = dxbc::kRdefInputFlagUserPacked;
      rdef_binding_stencil_mask.id = cbuffer_index_stencil_mask;
    }

    if (cbuffer_index_address != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_address = rdef_bindings[rdef_binding_index++];
      rdef_binding_address.name_ptr = rdef_xe_transfer_address_name_ptr;
      rdef_binding_address.type = dxbc::RdefInputType::kCbuffer;
      rdef_binding_address.bind_point = kTransferCBVRegisterAddress;
      rdef_binding_address.bind_count = 1;
      rdef_binding_address.flags = dxbc::kRdefInputFlagUserPacked;
      rdef_binding_address.id = cbuffer_index_address;
    }

    if (cbuffer_index_host_depth_address != UINT32_MAX) {
      dxbc::RdefInputBind& rdef_binding_host_depth_address = rdef_bindings[rdef_binding_index++];
      rdef_binding_host_depth_address.name_ptr = rdef_xe_transfer_host_depth_address_name_ptr;
      rdef_binding_host_depth_address.type = dxbc::RdefInputType::kCbuffer;
      rdef_binding_host_depth_address.bind_point = kTransferCBVRegisterHostDepthAddress;
      rdef_binding_host_depth_address.bind_count = 1;
      rdef_binding_host_depth_address.flags = dxbc::kRdefInputFlagUserPacked;
      rdef_binding_host_depth_address.id = cbuffer_index_host_depth_address;
    }
  }

  {
    auto& rdef_header =
        *reinterpret_cast<dxbc::RdefHeader*>(built_shader_.data() + rdef_position_dwords);
    rdef_header.cbuffer_count = rdef_cbuffer_count;
    rdef_header.cbuffers_ptr =
        uint32_t((rdef_cbuffer_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    rdef_header.input_bind_count = rdef_binding_count;
    rdef_header.input_binds_ptr =
        uint32_t((rdef_binding_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    rdef_header.shader_model = dxbc::RdefShaderModel::kPixelShader5_1;
    rdef_header.compile_flags =
        dxbc::kCompileFlagNoPreshader | dxbc::kCompileFlagPreferFlowControl |
        dxbc::kCompileFlagIeeeStrictness | dxbc::kCompileFlagAllResourcesBound;

    rdef_header.generator_name_ptr = sizeof(dxbc::RdefHeader);
    rdef_header.fourcc = dxbc::RdefHeader::FourCC::k5_1;
    rdef_header.InitializeSizes();
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kResourceDefinition;
    blob_position_dwords = uint32_t(built_shader_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             built_shader_[blob_offset_position_dwords++];
  }

  enum InputRegister : uint32_t {
    kInputRegisterPosition,
    kInputRegisterSampleIndex,
    kInputRegisterCount,
  };

  uint32_t isgn_parameter_count = 1 + uint32_t(key.dest_msaa_samples != xenos::MsaaSamples::k1X);

  built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t isgn_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  built_shader_.resize(isgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t) +
                       sizeof(dxbc::SignatureParameter) / sizeof(uint32_t) * isgn_parameter_count);

  name_ptr = uint32_t((built_shader_.size() - isgn_position_dwords) * sizeof(uint32_t));
  uint32_t isgn_sv_position_name_ptr = name_ptr;
  name_ptr += dxbc::AppendAlignedString(built_shader_, "SV_Position");
  uint32_t isgn_sv_sample_index_name_ptr = name_ptr;
  if (key.dest_msaa_samples != xenos::MsaaSamples::k1X) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "SV_SampleIndex");
  }

  {
    auto& isgn_header =
        *reinterpret_cast<dxbc::Signature*>(built_shader_.data() + isgn_position_dwords);
    isgn_header.parameter_count = isgn_parameter_count;
    isgn_header.parameter_info_ptr = sizeof(dxbc::Signature);

    auto isgn_parameters = reinterpret_cast<dxbc::SignatureParameter*>(
        built_shader_.data() + isgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));
    uint32_t isgn_parameter_index = 0;

    dxbc::SignatureParameter& isgn_sv_position = isgn_parameters[isgn_parameter_index++];
    isgn_sv_position.semantic_name_ptr = isgn_sv_position_name_ptr;
    isgn_sv_position.system_value = dxbc::Name::kPosition;
    isgn_sv_position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
    isgn_sv_position.register_index = kInputRegisterPosition;
    isgn_sv_position.mask = 0b1111;
    isgn_sv_position.always_reads_mask = 0b0011;

    if (key.dest_msaa_samples != xenos::MsaaSamples::k1X) {
      dxbc::SignatureParameter& isgn_sv_sample_index = isgn_parameters[isgn_parameter_index++];
      isgn_sv_sample_index.semantic_name_ptr = isgn_sv_sample_index_name_ptr;
      isgn_sv_sample_index.system_value = dxbc::Name::kSampleIndex;
      isgn_sv_sample_index.component_type = dxbc::SignatureRegisterComponentType::kUInt32;
      isgn_sv_sample_index.register_index = kInputRegisterSampleIndex;
      isgn_sv_sample_index.mask = 0b0001;
      isgn_sv_sample_index.always_reads_mask = 0b0001;
    }
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kInputSignature;
    blob_position_dwords = uint32_t(built_shader_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             built_shader_[blob_offset_position_dwords++];
  }

  uint32_t osgn_parameter_count = 0;
  uint32_t osgn_parameter_index_sv_target =
      mode.output == TransferOutput::kColor ? osgn_parameter_count++ : UINT32_MAX;
  uint32_t osgn_parameter_index_sv_depth =
      mode.output == TransferOutput::kDepth ? osgn_parameter_count++ : UINT32_MAX;
  uint32_t osgn_parameter_index_sv_stencil_ref =
      shader_uses_stencil_reference_output ? osgn_parameter_count++ : UINT32_MAX;

  built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t osgn_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  built_shader_.resize(osgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t) +
                       sizeof(dxbc::SignatureParameter) / sizeof(uint32_t) * osgn_parameter_count);

  name_ptr = uint32_t((built_shader_.size() - osgn_position_dwords) * sizeof(uint32_t));
  uint32_t osgn_sv_target_name_ptr = name_ptr;
  if (osgn_parameter_index_sv_target != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "SV_Target");
  }
  uint32_t osgn_sv_depth_name_ptr = name_ptr;
  if (osgn_parameter_index_sv_depth != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "SV_Depth");
  }
  uint32_t osgn_sv_stencil_ref_name_ptr = name_ptr;
  if (osgn_parameter_index_sv_stencil_ref != UINT32_MAX) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "SV_StencilRef");
  }

  bool dest_color_is_uint;
  if (mode.output == TransferOutput::kColor) {
    GetColorOwnershipTransferDXGIFormat(dest_color_format, &dest_color_is_uint);
  } else {
    dest_color_is_uint = false;
  }

  {
    auto& osgn_header =
        *reinterpret_cast<dxbc::Signature*>(built_shader_.data() + osgn_position_dwords);
    osgn_header.parameter_count = osgn_parameter_count;
    osgn_header.parameter_info_ptr = sizeof(dxbc::Signature);

    auto osgn_parameters = reinterpret_cast<dxbc::SignatureParameter*>(
        built_shader_.data() + osgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));

    if (osgn_parameter_index_sv_target != UINT32_MAX) {
      dxbc::SignatureParameter& osgn_sv_target = osgn_parameters[osgn_parameter_index_sv_target];
      osgn_sv_target.semantic_name_ptr = osgn_sv_target_name_ptr;
      osgn_sv_target.component_type = dest_color_is_uint
                                          ? dxbc::SignatureRegisterComponentType::kUInt32
                                          : dxbc::SignatureRegisterComponentType::kFloat32;
      osgn_sv_target.register_index = 0;
      osgn_sv_target.mask = 0b1111;
    }

    if (osgn_parameter_index_sv_depth != UINT32_MAX) {
      dxbc::SignatureParameter& osgn_sv_depth = osgn_parameters[osgn_parameter_index_sv_depth];
      osgn_sv_depth.semantic_name_ptr = osgn_sv_depth_name_ptr;
      osgn_sv_depth.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      osgn_sv_depth.register_index = UINT32_MAX;
      osgn_sv_depth.mask = 0b0001;
      osgn_sv_depth.never_writes_mask = 0b1110;
    }

    if (osgn_parameter_index_sv_stencil_ref != UINT32_MAX) {
      dxbc::SignatureParameter& osgn_sv_stencil_ref =
          osgn_parameters[osgn_parameter_index_sv_stencil_ref];
      osgn_sv_stencil_ref.semantic_name_ptr = osgn_sv_stencil_ref_name_ptr;

      osgn_sv_stencil_ref.component_type = dxbc::SignatureRegisterComponentType::kUInt32;
      osgn_sv_stencil_ref.register_index = UINT32_MAX;
      osgn_sv_stencil_ref.mask = 0b0001;
      osgn_sv_stencil_ref.never_writes_mask = 0b1110;
    }
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kOutputSignature;
    blob_position_dwords = uint32_t(built_shader_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             built_shader_[blob_offset_position_dwords++];
  }

  built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t shex_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  built_shader_.resize(shex_position_dwords);

  built_shader_.push_back(dxbc::VersionToken(dxbc::ProgramType::kPixelShader, 5, 1));

  built_shader_.push_back(0);

  dxbc::Statistics stat;
  std::memset(&stat, 0, sizeof(dxbc::Statistics));
  dxbc::Assembler a(built_shader_, stat);

  a.OpDclGlobalFlags(dxbc::kGlobalFlagAllResourcesBound);
  if (cbuffer_index_stencil_mask != UINT32_MAX) {
    a.OpDclConstantBuffer(
        dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_stencil_mask, kTransferCBVRegisterStencilMask,
                      kTransferCBVRegisterStencilMask),
        1);
  }
  if (cbuffer_index_address != UINT32_MAX) {
    a.OpDclConstantBuffer(dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_address,
                                        kTransferCBVRegisterAddress, kTransferCBVRegisterAddress),
                          1);
  }
  if (cbuffer_index_host_depth_address != UINT32_MAX) {
    a.OpDclConstantBuffer(
        dxbc::Src::CB(dxbc::Src::Dcl, cbuffer_index_host_depth_address,
                      kTransferCBVRegisterHostDepthAddress, kTransferCBVRegisterHostDepthAddress),
        1);
  }
  if (srv_index_color != UINT32_MAX) {
    a.OpDclResource(
        key.source_msaa_samples != xenos::MsaaSamples::k1X ? dxbc::ResourceDimension::kTexture2DMS
                                                           : dxbc::ResourceDimension::kTexture2D,
        dxbc::ResourceReturnTypeX4Token(source_color_is_uint ? dxbc::ResourceReturnType::kUInt
                                                             : dxbc::ResourceReturnType::kFloat),
        dxbc::Src::T(dxbc::Src::Dcl, srv_index_color, kTransferSRVRegisterColor,
                     kTransferSRVRegisterColor));
  }
  if (srv_index_depth != UINT32_MAX) {
    a.OpDclResource(key.source_msaa_samples != xenos::MsaaSamples::k1X
                        ? dxbc::ResourceDimension::kTexture2DMS
                        : dxbc::ResourceDimension::kTexture2D,
                    dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kFloat),
                    dxbc::Src::T(dxbc::Src::Dcl, srv_index_depth, kTransferSRVRegisterDepth,
                                 kTransferSRVRegisterDepth));
  }
  if (srv_index_stencil != UINT32_MAX) {
    a.OpDclResource(key.source_msaa_samples != xenos::MsaaSamples::k1X
                        ? dxbc::ResourceDimension::kTexture2DMS
                        : dxbc::ResourceDimension::kTexture2D,
                    dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kUInt),
                    dxbc::Src::T(dxbc::Src::Dcl, srv_index_stencil, kTransferSRVRegisterStencil,
                                 kTransferSRVRegisterStencil));
  }
  if (srv_index_host_depth != UINT32_MAX) {
    a.OpDclResource(key.host_depth_source_is_copy
                        ? dxbc::ResourceDimension::kBuffer
                        : (key.host_depth_source_msaa_samples != xenos::MsaaSamples::k1X
                               ? dxbc::ResourceDimension::kTexture2DMS
                               : dxbc::ResourceDimension::kTexture2D),
                    dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kFloat),
                    dxbc::Src::T(dxbc::Src::Dcl, srv_index_host_depth,
                                 kTransferSRVRegisterHostDepth, kTransferSRVRegisterHostDepth));
  }
  a.OpDclInputPSSIV(dxbc::InterpolationMode::kLinearNoPerspective,
                    dxbc::Dest::V1D(kInputRegisterPosition, 0b0011), dxbc::Name::kPosition);
  if (key.dest_msaa_samples != xenos::MsaaSamples::k1X) {
    a.OpDclInputPSSGV(dxbc::Dest::V1D(kInputRegisterSampleIndex, 0b0001), dxbc::Name::kSampleIndex);
  }
  if (osgn_parameter_index_sv_target != UINT32_MAX) {
    a.OpDclOutput(dxbc::Dest::O(0));
  }
  if (osgn_parameter_index_sv_depth != UINT32_MAX) {
    a.OpDclOutput(dxbc::Dest::ODepth());
  }
  if (osgn_parameter_index_sv_stencil_ref != UINT32_MAX) {
    a.OpDclOutput(dxbc::Dest::OStencilRef());
  }

  a.OpDclTemps(3);

  uint32_t draw_resolution_scale_x = this->draw_resolution_scale_x();
  uint32_t draw_resolution_scale_y = this->draw_resolution_scale_y();

  uint32_t tile_width_samples = xenos::kEdramTileWidthSamples * draw_resolution_scale_x;
  uint32_t tile_height_samples = xenos::kEdramTileHeightSamples * draw_resolution_scale_y;

  a.OpFToU(dxbc::Dest::R(0, 0b0011), dxbc::Src::V1D(kInputRegisterPosition));
  uint32_t dest_tile_width_pixels =
      tile_width_samples >>
      (uint32_t(dest_is_64bpp) + uint32_t(key.dest_msaa_samples >= xenos::MsaaSamples::k4X));
  uint32_t dest_tile_height_pixels =
      tile_height_samples >> uint32_t(key.dest_msaa_samples >= xenos::MsaaSamples::k2X);

  a.OpUDiv(dxbc::Dest::R(0, 0b1100), dxbc::Dest::R(0, 0b0011), dxbc::Src::R(0, 0b01000100),
           dxbc::Src::LU(dest_tile_width_pixels, dest_tile_height_pixels, dest_tile_width_pixels,
                         dest_tile_height_pixels));

  a.OpUBFE(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(xenos::kEdramPitchTilesBits), dxbc::Src::LU(0),
           dxbc::Src::CB(cbuffer_index_address, kTransferCBVRegisterAddress, 0, dxbc::Src::kXXXX));

  a.OpUMAd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(1, dxbc::Src::kXXXX),
           dxbc::Src::R(0, dxbc::Src::kWWWW), dxbc::Src::R(0, dxbc::Src::kZZZZ));

  dxbc::Src dest_sample(dxbc::Src::V1D(kInputRegisterSampleIndex, dxbc::Src::kXXXX));
  dxbc::Src source_sample(dest_sample);
  uint32_t source_tile_pixel_x_reg = 0;
  uint32_t source_tile_pixel_y_reg = 0;

  if (key.source_msaa_samples != key.dest_msaa_samples || source_is_64bpp != dest_is_64bpp) {
    dxbc::Src canonical_u(dxbc::Src::R(0, dxbc::Src::kXXXX));
    dxbc::Src canonical_v(dxbc::Src::R(0, dxbc::Src::kYYYY));
    bool canonical_scaled;
    CanonicalizeSample(a, key.dest_msaa_samples, dest_sample, msaa_2x_supported_,
                       draw_resolution_scale_x, draw_resolution_scale_y, canonical_u, canonical_v,
                       canonical_scaled);
    if (dest_is_64bpp && !source_is_64bpp) {
      a.OpIShL(dxbc::Dest::R(1, 0b0001), canonical_u, dxbc::Src::LU(1));
      canonical_u = dxbc::Src::R(1, dxbc::Src::kXXXX);
    } else if (!dest_is_64bpp && source_is_64bpp) {
      a.OpAnd(dxbc::Dest::R(0, 0b1000), canonical_u, dxbc::Src::LU(1));
      a.OpUShR(dxbc::Dest::R(1, 0b0001), canonical_u, dxbc::Src::LU(1));
      canonical_u = dxbc::Src::R(1, dxbc::Src::kXXXX);
    }
    dxbc::Src source_pixel_x(canonical_u);
    dxbc::Src source_pixel_y(canonical_v);
    DecanonicalizeSample(a, key.source_msaa_samples, canonical_u, canonical_v, canonical_scaled,
                         msaa_2x_supported_, draw_resolution_scale_x, draw_resolution_scale_y,
                         source_pixel_x, source_pixel_y, source_sample);

    source_tile_pixel_x_reg = 1;
    source_tile_pixel_y_reg =
        (key.source_msaa_samples == xenos::MsaaSamples::k1X &&
         key.dest_msaa_samples == xenos::MsaaSamples::k1X && !canonical_scaled)
            ? 0
            : 1;
  }

  uint32_t source_pixel_width_dwords_log2 =
      uint32_t(key.source_msaa_samples >= xenos::MsaaSamples::k4X) + uint32_t(source_is_64bpp);

  if (source_is_color != dest_is_color) {
    uint32_t source_32bpp_tile_half_pixels =
        tile_width_samples >> (1 + source_pixel_width_dwords_log2);
    a.OpULT(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(source_tile_pixel_x_reg, dxbc::Src::kXXXX),
            dxbc::Src::LU(source_32bpp_tile_half_pixels));
    a.OpMovC(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
             dxbc::Src::LI(int32_t(source_32bpp_tile_half_pixels)),
             dxbc::Src::LI(-int32_t(source_32bpp_tile_half_pixels)));
    a.OpIAdd(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(source_tile_pixel_x_reg, dxbc::Src::kXXXX),
             dxbc::Src::R(1, dxbc::Src::kWWWW));
    source_tile_pixel_x_reg = 1;
  }

  a.OpIBFE(dxbc::Dest::R(1, 0b1000), dxbc::Src::LU(xenos::kEdramBaseTilesBits + 1),
           dxbc::Src::LU(xenos::kEdramPitchTilesBits * 2),
           dxbc::Src::CB(cbuffer_index_address, kTransferCBVRegisterAddress, 0, dxbc::Src::kXXXX));

  a.OpIAdd(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(0, dxbc::Src::kZZZZ),
           dxbc::Src::R(1, dxbc::Src::kWWWW));

  a.OpAnd(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
          dxbc::Src::LU(xenos::kEdramTileCount - 1));

  a.OpUBFE(dxbc::Dest::R(2, 0b0001), dxbc::Src::LU(xenos::kEdramPitchTilesBits),
           dxbc::Src::LU(xenos::kEdramPitchTilesBits),
           dxbc::Src::CB(cbuffer_index_address, kTransferCBVRegisterAddress, 0, dxbc::Src::kXXXX));

  a.OpUDiv(dxbc::Dest::R(1, 0b1000), dxbc::Dest::R(2, 0b0001), dxbc::Src::R(1, dxbc::Src::kWWWW),
           dxbc::Src::R(2, dxbc::Src::kXXXX));

  a.OpUMAd(
      dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(tile_width_samples >> source_pixel_width_dwords_log2),
      dxbc::Src::R(2, dxbc::Src::kXXXX), dxbc::Src::R(source_tile_pixel_x_reg, dxbc::Src::kXXXX));

  a.OpUMAd(dxbc::Dest::R(1, 0b0010),
           dxbc::Src::LU(tile_height_samples >>
                         uint32_t(key.source_msaa_samples >= xenos::MsaaSamples::k2X)),
           dxbc::Src::R(1, dxbc::Src::kWWWW),
           dxbc::Src::R(source_tile_pixel_y_reg, dxbc::Src::kYYYY));

  bool source_load_is_two_dwords = !source_is_64bpp && dest_is_64bpp;
  if (key.source_msaa_samples != xenos::MsaaSamples::k1X) {
    for (uint32_t i = 0; i <= uint32_t(source_load_is_two_dwords); ++i) {
      uint32_t source_load_register = source_load_is_two_dwords ? i : 1;
      if (srv_index_depth != UINT32_MAX) {
        a.OpLdMS(dxbc::Dest::R(source_load_register, 0b1000), dxbc::Src::R(1), 0b0011,
                 dxbc::Src::T(srv_index_depth, kTransferSRVRegisterDepth, dxbc::Src::kXXXX),
                 source_sample);
      }
      if (srv_index_stencil != UINT32_MAX) {
        a.OpLdMS(dxbc::Dest::R(source_load_register, 0b0001), dxbc::Src::R(1), 0b0011,
                 dxbc::Src::T(srv_index_stencil, kTransferSRVRegisterStencil, dxbc::Src::kYYYY),
                 source_sample);
      } else if (srv_index_color != UINT32_MAX) {
        a.OpLdMS(dxbc::Dest::R(source_load_register, source_color_srv_component_mask),
                 dxbc::Src::R(1), 0b0011, dxbc::Src::T(srv_index_color, kTransferSRVRegisterColor),
                 source_sample);
      }
      if (source_load_is_two_dwords && !i) {
        a.OpIAdd(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
                 dxbc::Src::LU(draw_resolution_scale_x));
      }
    }
  } else {
    a.OpMov(dxbc::Dest::R(1, 0b0100), dxbc::Src::LU(0));
    dxbc::Src source_coordinates(dxbc::Src::R(1, 0b10000100));
    for (uint32_t i = 0; i <= uint32_t(source_load_is_two_dwords); ++i) {
      uint32_t source_load_register = source_load_is_two_dwords ? i : 1;
      if (srv_index_depth != UINT32_MAX) {
        a.OpLd(dxbc::Dest::R(source_load_register, 0b1000), source_coordinates, 0b1011,
               dxbc::Src::T(srv_index_depth, kTransferSRVRegisterDepth, dxbc::Src::kXXXX));
      }
      if (srv_index_stencil != UINT32_MAX) {
        a.OpLd(dxbc::Dest::R(source_load_register, 0b0001), source_coordinates, 0b1011,
               dxbc::Src::T(srv_index_stencil, kTransferSRVRegisterStencil, dxbc::Src::kYYYY));
      } else if (srv_index_color != UINT32_MAX) {
        a.OpLd(dxbc::Dest::R(source_load_register, source_color_srv_component_mask),
               source_coordinates, 0b1011,
               dxbc::Src::T(srv_index_color, kTransferSRVRegisterColor));
      }
      if (source_load_is_two_dwords && !i) {
        a.OpIAdd(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
                 dxbc::Src::LU(draw_resolution_scale_x));
      }
    }
  }

  if (source_is_64bpp && !dest_is_64bpp) {
    uint32_t source_color_half_component_count = source_color_format_component_count >> 1;
    if (dest_is_stencil_bit) {
      a.OpMovC(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(0, dxbc::Src::kWWWW),
               dxbc::Src::R(1).Select(source_color_half_component_count),
               dxbc::Src::R(1, dxbc::Src::kXXXX));
    } else {
      uint32_t color_high_dword_swizzle =
          (source_color_half_component_count * 0b01010101) &
          ~((uint32_t(1) << (source_color_half_component_count * 2)) - 1);
      for (uint32_t i = 0; i < source_color_half_component_count; ++i) {
        color_high_dword_swizzle |= (source_color_half_component_count + i) << (i * 2);
      }
      a.OpMovC(dxbc::Dest::R(1, (1 << source_color_half_component_count) - 1),
               dxbc::Src::R(0, dxbc::Src::kWWWW), dxbc::Src::R(1, color_high_dword_swizzle),
               dxbc::Src::R(1));
    }
  }

  if (osgn_parameter_index_sv_stencil_ref != UINT32_MAX && srv_index_stencil != UINT32_MAX) {
    assert_true(mode.output == TransferOutput::kDepth);
    a.OpMov(dxbc::Dest::OStencilRef(), dxbc::Src::R(1, dxbc::Src::kXXXX));
  }

  if (dest_is_64bpp) {
    bool color_packed_in_r0x_and_r1x = false;
    if (source_is_color) {
      switch (source_color_format) {
        case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
          for (uint32_t i = 0; i < 2; ++i) {
            for (uint32_t j = 0; j < 3; ++j) {
              DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(a, i, j, i, j, 2, 0, 2, 1);
            }
          }
        }
          [[fallthrough]];
        case xenos::ColorRenderTargetFormat::k_8_8_8_8: {
          color_packed_in_r0x_and_r1x = true;
          for (uint32_t i = 0; i < 2; ++i) {
            a.OpMAd(dxbc::Dest::R(i), dxbc::Src::R(i), dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(i), dxbc::Src::R(i));
            for (uint32_t j = 1; j < 4; ++j) {
              a.OpBFI(dxbc::Dest::R(i, 0b0001), dxbc::Src::LU(8), dxbc::Src::LU(j * 8),
                      dxbc::Src::R(i).Select(j), dxbc::Src::R(i, dxbc::Src::kXXXX));
            }
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_2_10_10_10:
        case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
          color_packed_in_r0x_and_r1x = true;
          for (uint32_t i = 0; i < 2; ++i) {
            a.OpMAd(dxbc::Dest::R(i), dxbc::Src::R(i),
                    dxbc::Src::LF(1023.0f, 1023.0f, 1023.0f, 3.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(i), dxbc::Src::R(i));
            for (uint32_t j = 1; j < 4; ++j) {
              a.OpBFI(dxbc::Dest::R(i, 0b0001), dxbc::Src::LU(j == 3 ? 2 : 10),
                      dxbc::Src::LU(j * 10), dxbc::Src::R(i).Select(j),
                      dxbc::Src::R(i, dxbc::Src::kXXXX));
            }
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
        case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
          color_packed_in_r0x_and_r1x = true;
          for (uint32_t i = 0; i < 2; ++i) {
            for (uint32_t j = 0; j < 3; ++j) {
              DxbcShaderTranslator::UnclampedFloat32To7e3(a, i, j, i, j, 2, 0);
              if (j) {
                a.OpBFI(dxbc::Dest::R(i, 0b0001), dxbc::Src::LU(10), dxbc::Src::LU(j * 10),
                        dxbc::Src::R(i).Select(j), dxbc::Src::R(i, dxbc::Src::kXXXX));
              }
            }

            a.OpMov(dxbc::Dest::R(i, 0b1000), dxbc::Src::R(i, dxbc::Src::kWWWW), true);
            a.OpMAd(dxbc::Dest::R(i, 0b1000), dxbc::Src::R(i, dxbc::Src::kWWWW),
                    dxbc::Src::LF(3.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(i, 0b1000), dxbc::Src::R(i, dxbc::Src::kWWWW));
            a.OpBFI(dxbc::Dest::R(i, 0b0001), dxbc::Src::LU(2), dxbc::Src::LU(30),
                    dxbc::Src::R(i, dxbc::Src::kWWWW), dxbc::Src::R(i, dxbc::Src::kXXXX));
          }
        } break;

        case xenos::ColorRenderTargetFormat::k_16_16:
        case xenos::ColorRenderTargetFormat::k_16_16_FLOAT: {
          if (dest_color_format == xenos::ColorRenderTargetFormat::k_32_32_FLOAT) {
            for (uint32_t i = 0; i < 2; ++i) {
              a.OpBFI(dxbc::Dest::O(0, 1 << i), dxbc::Src::LU(16), dxbc::Src::LU(16),
                      dxbc::Src::R(i, dxbc::Src::kYYYY), dxbc::Src::R(i, dxbc::Src::kXXXX));
            }
          } else {
            a.OpMov(dxbc::Dest::O(0, 0b0011), dxbc::Src::R(0));
            a.OpMov(dxbc::Dest::O(0, 0b1100), dxbc::Src::R(1, 0b0100 << 4));
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_16_16_16_16:
        case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT: {
          if (dest_color_format == xenos::ColorRenderTargetFormat::k_32_32_FLOAT) {
            a.OpBFI(dxbc::Dest::O(0, 0b0011), dxbc::Src::LU(16), dxbc::Src::LU(16),
                    dxbc::Src::R(1, 0b1101), dxbc::Src::R(1, 0b1000));
          } else {
            a.OpMov(dxbc::Dest::O(0), dxbc::Src::R(1));
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_32_FLOAT: {
          color_packed_in_r0x_and_r1x = true;
        } break;
        case xenos::ColorRenderTargetFormat::k_32_32_FLOAT: {
          if (dest_color_format == xenos::ColorRenderTargetFormat::k_32_32_FLOAT) {
            a.OpMov(dxbc::Dest::O(0, 0b0011), dxbc::Src::R(1));
          } else {
            a.OpUBFE(dxbc::Dest::O(0), dxbc::Src::LU(16), dxbc::Src::LU(0, 16, 0, 16),
                     dxbc::Src::R(1, 0b01010000));
          }
        } break;
      }
    } else {
      assert_not_zero(rs & kTransferUsedRootParameterDepthSRVBit);
      color_packed_in_r0x_and_r1x = true;
      for (uint32_t i = 0; i < 2; ++i) {
        switch (source_depth_format) {
          case xenos::DepthRenderTargetFormat::kD24S8: {
            a.OpMul(dxbc::Dest::R(i, 0b1000), dxbc::Src::R(i, dxbc::Src::kWWWW),
                    dxbc::Src::LF(float(0xFFFFFF)));
            a.OpRoundNE(dxbc::Dest::R(i, 0b1000), dxbc::Src::R(i, dxbc::Src::kWWWW));
            a.OpFToU(dxbc::Dest::R(i, 0b1000), dxbc::Src::R(i, dxbc::Src::kWWWW));
          } break;
          case xenos::DepthRenderTargetFormat::kD24FS8: {
            DxbcShaderTranslator::PreClampedDepthTo20e4(
                a, i, 3, i, 3, 1, 1,
                !depth_float24_convert_in_pixel_shader() && depth_float24_round(), true);
          } break;
        }

        a.OpBFI(dxbc::Dest::R(i, 0b0001), dxbc::Src::LU(24), dxbc::Src::LU(8),
                dxbc::Src::R(i, dxbc::Src::kWWWW), dxbc::Src::R(i, dxbc::Src::kXXXX));
      }
    }
    if (color_packed_in_r0x_and_r1x) {
      if (dest_color_format == xenos::ColorRenderTargetFormat::k_32_32_FLOAT) {
        a.OpMov(dxbc::Dest::O(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX));
        a.OpMov(dxbc::Dest::O(0, 0b0010), dxbc::Src::R(1, dxbc::Src::kXXXX));
      } else {
        for (uint32_t i = 0; i < 2; ++i) {
          a.OpUBFE(dxbc::Dest::O(0, 0b11 << (i * 2)), dxbc::Src::LU(16),
                   dxbc::Src::LU(0, 16, 0, 16), dxbc::Src::R(i, dxbc::Src::kXXXX));
        }
      }
    }
  } else {
    bool color_packed_in_r1x = false;
    bool depth_loaded_in_guest_format = false;
    if (source_is_color) {
      switch (source_color_format) {
        case xenos::ColorRenderTargetFormat::k_8_8_8_8:
        case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
          if (dest_is_stencil_bit) {
            if (source_color_format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA) {
              DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(a, 1, 0, 1, 0, 2, 0, 2, 1);
            }
            a.OpMAd(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
                    dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX));
          } else if (dest_is_color &&
                     (dest_color_format == xenos::ColorRenderTargetFormat::k_8_8_8_8 ||
                      dest_color_format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA)) {
            if (source_color_format != dest_color_format) {
              if (dest_color_format != xenos::ColorRenderTargetFormat::k_8_8_8_8) {
                for (uint32_t i = 0; i < 3; ++i) {
                  DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(a, 1, i, 1, i, 2, 0, 2, 1);
                }
              } else {
                for (uint32_t i = 0; i < 3; ++i) {
                  DxbcShaderTranslator::PWLGammaToLinear(a, 1, i, 1, i, true, 2, 0, 2, 1);
                }
              }
            }

            a.OpMov(dxbc::Dest::O(0), dxbc::Src::R(1));
          } else if (mode.output == TransferOutput::kDepth) {
            if (source_color_format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA) {
              for (uint32_t i = osgn_parameter_index_sv_stencil_ref != UINT32_MAX ? 0 : 1; i < 3;
                   ++i) {
                DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(a, 1, i, 1, i, 2, 0, 2, 1);
              }
            }

            a.OpMAd(dxbc::Dest::R(
                        1, osgn_parameter_index_sv_stencil_ref != UINT32_MAX ? 0b1111 : 0b1110),
                    dxbc::Src::R(1), dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(1, 0b1110), dxbc::Src::R(1));
            if (osgn_parameter_index_sv_stencil_ref != UINT32_MAX) {
              a.OpFToU(dxbc::Dest::OStencilRef(), dxbc::Src::R(1, dxbc::Src::kXXXX));
            }

            a.OpBFI(dxbc::Dest::R(1, 0b0010), dxbc::Src::LU(8), dxbc::Src::LU(8),
                    dxbc::Src::R(1, dxbc::Src::kZZZZ), dxbc::Src::R(1, dxbc::Src::kYYYY));

            a.OpBFI(dxbc::Dest::R(1, 0b1000), dxbc::Src::LU(8), dxbc::Src::LU(16),
                    dxbc::Src::R(1, dxbc::Src::kWWWW), dxbc::Src::R(1, dxbc::Src::kYYYY));
          } else {
            if (source_color_format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA) {
              for (uint32_t i = 0; i < 3; ++i) {
                DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(a, 1, i, 1, i, 2, 0, 2, 1);
              }
            }
            color_packed_in_r1x = true;
            a.OpMAd(dxbc::Dest::R(1), dxbc::Src::R(1), dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(1), dxbc::Src::R(1));
            for (uint32_t i = 1; i < 4; ++i) {
              a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(8), dxbc::Src::LU(i * 8),
                      dxbc::Src::R(1).Select(i), dxbc::Src::R(1, dxbc::Src::kXXXX));
            }
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_2_10_10_10:
        case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
          if (dest_is_stencil_bit) {
            a.OpMAd(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
                    dxbc::Src::LF(1023.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX));
          } else if (dest_is_color &&
                     (dest_color_format == xenos::ColorRenderTargetFormat::k_2_10_10_10 ||
                      dest_color_format ==
                          xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10)) {
            a.OpMov(dxbc::Dest::O(0), dxbc::Src::R(1));
          } else {
            color_packed_in_r1x = true;
            a.OpMAd(dxbc::Dest::R(1), dxbc::Src::R(1),
                    dxbc::Src::LF(1023.0f, 1023.0f, 1023.0f, 3.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(1), dxbc::Src::R(1));
            for (uint32_t i = 1; i < 4; ++i) {
              a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(i == 3 ? 2 : 10),
                      dxbc::Src::LU(i * 10), dxbc::Src::R(1).Select(i),
                      dxbc::Src::R(1, dxbc::Src::kXXXX));
            }
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
        case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
          if (dest_is_stencil_bit) {
            DxbcShaderTranslator::UnclampedFloat32To7e3(a, 1, 0, 1, 0, 2, 0);
          } else if (dest_is_color &&
                     (dest_color_format == xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT ||
                      dest_color_format ==
                          xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16)) {
            a.OpMov(dxbc::Dest::O(0), dxbc::Src::R(1));
          } else {
            color_packed_in_r1x = true;

            for (uint32_t i = 0; i < 3; ++i) {
              DxbcShaderTranslator::UnclampedFloat32To7e3(a, 1, i, 1, i, 2, 0);
              if (i) {
                a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(10), dxbc::Src::LU(i * 10),
                        dxbc::Src::R(1).Select(i), dxbc::Src::R(1, dxbc::Src::kXXXX));
              }
            }

            a.OpMov(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW), true);
            a.OpMAd(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
                    dxbc::Src::LF(3.0f), dxbc::Src::LF(0.5f));
            a.OpFToU(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW));
            a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(2), dxbc::Src::LU(30),
                    dxbc::Src::R(1, dxbc::Src::kWWWW), dxbc::Src::R(1, dxbc::Src::kXXXX));
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_16_16:
        case xenos::ColorRenderTargetFormat::k_16_16_16_16:
        case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
        case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT: {
          if (dest_is_stencil_bit) {
          } else if (dest_is_color &&
                     (dest_color_format == xenos::ColorRenderTargetFormat::k_16_16 ||
                      dest_color_format == xenos::ColorRenderTargetFormat::k_16_16_FLOAT)) {
            a.OpMov(dxbc::Dest::O(0, 0b0011), dxbc::Src::R(1));
          } else {
            color_packed_in_r1x = true;
            a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(16), dxbc::Src::LU(16),
                    dxbc::Src::R(1, dxbc::Src::kYYYY), dxbc::Src::R(1, dxbc::Src::kXXXX));
          }
        } break;
        case xenos::ColorRenderTargetFormat::k_32_FLOAT:
        case xenos::ColorRenderTargetFormat::k_32_32_FLOAT: {
          color_packed_in_r1x = true;
        } break;
      }
    } else if (rs & kTransferUsedRootParameterDepthSRVBit) {
      if (dest_is_color || dest_depth_format != source_depth_format) {
        depth_loaded_in_guest_format = true;
        switch (source_depth_format) {
          case xenos::DepthRenderTargetFormat::kD24S8: {
            a.OpMul(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
                    dxbc::Src::LF(float(0xFFFFFF)));
            a.OpRoundNE(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW));
            a.OpFToU(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW));
          } break;
          case xenos::DepthRenderTargetFormat::kD24FS8: {
            DxbcShaderTranslator::PreClampedDepthTo20e4(
                a, 1, 3, 1, 3, 1, 1,
                !depth_float24_convert_in_pixel_shader() && depth_float24_round(), true);
          } break;
        }
        if (dest_is_color) {
          color_packed_in_r1x = true;
          a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(24), dxbc::Src::LU(8),
                  dxbc::Src::R(1, dxbc::Src::kWWWW), dxbc::Src::R(1, dxbc::Src::kXXXX));
        }
      }
    }
    switch (mode.output) {
      case TransferOutput::kColor:

        if (color_packed_in_r1x) {
          switch (dest_color_format) {
            case xenos::ColorRenderTargetFormat::k_8_8_8_8: {
              a.OpUBFE(dxbc::Dest::R(1), dxbc::Src::LU(8), dxbc::Src::LU(0, 8, 16, 24),
                       dxbc::Src::R(1, dxbc::Src::kXXXX));
              a.OpUToF(dxbc::Dest::R(1), dxbc::Src::R(1));
              a.OpMul(dxbc::Dest::O(0), dxbc::Src::R(1), dxbc::Src::LF(1.0f / 255.0f));
            } break;
            case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
              a.OpUBFE(dxbc::Dest::R(1), dxbc::Src::LU(8), dxbc::Src::LU(0, 8, 16, 24),
                       dxbc::Src::R(1, dxbc::Src::kXXXX));
              a.OpUToF(dxbc::Dest::R(1), dxbc::Src::R(1));
              a.OpMul(dxbc::Dest::R(1, 0b0111), dxbc::Src::R(1), dxbc::Src::LF(1.0f / 255.0f));
              a.OpMul(dxbc::Dest::O(0, 0b1000), dxbc::Src::R(1), dxbc::Src::LF(1.0f / 255.0f));
              for (uint32_t i = 0; i < 3; ++i) {
                DxbcShaderTranslator::PWLGammaToLinear(a, 1, i, 1, i, true, 0, 0, 0, 1);
              }
              a.OpMov(dxbc::Dest::O(0, 0b0111), dxbc::Src::R(1));
            } break;
            case xenos::ColorRenderTargetFormat::k_2_10_10_10:
            case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
              a.OpUBFE(dxbc::Dest::R(1), dxbc::Src::LU(10, 10, 10, 2), dxbc::Src::LU(0, 10, 20, 30),
                       dxbc::Src::R(1, dxbc::Src::kXXXX));
              a.OpUToF(dxbc::Dest::R(1), dxbc::Src::R(1));
              a.OpMul(dxbc::Dest::O(0), dxbc::Src::R(1),
                      dxbc::Src::LF(1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 3.0f));
            } break;
            case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
            case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
              for (uint32_t i = 0; i < 3; ++i) {
                DxbcShaderTranslator::Float7e3To32(a, dxbc::Dest::O(0, 1 << i), 1, 0, i * 10, 1, 1,
                                                   1, 2);
              }

              a.OpUBFE(dxbc::Dest::R(1, 0b1000), dxbc::Src::LU(2), dxbc::Src::LU(30),
                       dxbc::Src::R(1, dxbc::Src::kXXXX));
              a.OpUToF(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW));
              a.OpMul(dxbc::Dest::O(0, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
                      dxbc::Src::LF(1.0f / 3.0f));
            } break;
            case xenos::ColorRenderTargetFormat::k_16_16:
            case xenos::ColorRenderTargetFormat::k_16_16_FLOAT: {
              a.OpUBFE(dxbc::Dest::O(0, 0b0011), dxbc::Src::LU(16), dxbc::Src::LU(0, 16, 0, 0),
                       dxbc::Src::R(1, dxbc::Src::kXXXX));
            } break;
            case xenos::ColorRenderTargetFormat::k_32_FLOAT: {
              a.OpMov(dxbc::Dest::O(0, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX));
            } break;
            default:

              assert_unhandled_case(dest_color_format);
          }
        }
        break;
      case TransferOutput::kDepth:
        if (source_is_color || depth_loaded_in_guest_format) {
          if (color_packed_in_r1x) {
            a.OpUBFE(dxbc::Dest::R(1, 0b1000), dxbc::Src::LU(24), dxbc::Src::LU(8),
                     dxbc::Src::R(1, dxbc::Src::kXXXX));
            if (osgn_parameter_index_sv_stencil_ref != UINT32_MAX) {
              a.OpUBFE(dxbc::Dest::OStencilRef(), dxbc::Src::LU(8), dxbc::Src::LU(0),
                       dxbc::Src::R(1, dxbc::Src::kXXXX));
            }
          }

          if (rs & kTransferUsedRootParameterHostDepthSRVBit) {
            if (key.host_depth_source_is_copy) {
              assert_true(key.host_depth_source_msaa_samples == xenos::MsaaSamples::k1X);
              if (key.dest_msaa_samples >= xenos::MsaaSamples::k2X) {
                if (key.dest_msaa_samples >= xenos::MsaaSamples::k4X) {
                  a.OpBFI(dxbc::Dest::R(0, 0b0001), dxbc::Src::LU(31), dxbc::Src::LU(1),
                          dxbc::Src::R(0, dxbc::Src::kXXXX), dest_sample);
                }

                if (key.dest_msaa_samples == xenos::MsaaSamples::k2X && msaa_2x_supported_) {
                  a.OpBFI(dxbc::Dest::R(0, 0b0010), dxbc::Src::LU(31), dxbc::Src::LU(1),
                          dxbc::Src::R(0, dxbc::Src::kYYYY), dest_sample);
                  a.OpXOr(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY),
                          dxbc::Src::LU(1));
                } else {
                  a.OpUShR(dxbc::Dest::R(0, 0b1000), dest_sample, dxbc::Src::LU(1));
                  a.OpBFI(dxbc::Dest::R(0, 0b0010), dxbc::Src::LU(31), dxbc::Src::LU(1),
                          dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::R(0, dxbc::Src::kWWWW));
                }
              }

              a.OpUMAd(dxbc::Dest::R(0, 0b0001), dxbc::Src::LU(tile_width_samples),
                       dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::R(0, dxbc::Src::kXXXX));
              a.OpUMAd(dxbc::Dest::R(0, 0b0001),
                       dxbc::Src::LU(tile_width_samples * tile_height_samples),
                       dxbc::Src::R(0, dxbc::Src::kZZZZ), dxbc::Src::R(0, dxbc::Src::kXXXX));

              a.OpLd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX), 0b0001,
                     dxbc::Src::T(srv_index_host_depth, kTransferSRVRegisterHostDepth,
                                  dxbc::Src::kXXXX));
            } else {
              a.OpIBFE(dxbc::Dest::R(0, 0b1000), dxbc::Src::LU(xenos::kEdramBaseTilesBits + 1),
                       dxbc::Src::LU(xenos::kEdramPitchTilesBits * 2),
                       dxbc::Src::CB(cbuffer_index_host_depth_address,
                                     kTransferCBVRegisterHostDepthAddress, 0, dxbc::Src::kXXXX));

              a.OpIAdd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, dxbc::Src::kZZZZ),
                       dxbc::Src::R(0, dxbc::Src::kWWWW));

              a.OpAnd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, dxbc::Src::kZZZZ),
                      dxbc::Src::LU(xenos::kEdramTileCount - 1));

              dxbc::Src host_depth_source_sample(dest_sample);
              if (key.host_depth_source_msaa_samples != key.dest_msaa_samples) {
                dxbc::Src host_depth_u(dxbc::Src::R(0, dxbc::Src::kXXXX));
                dxbc::Src host_depth_v(dxbc::Src::R(0, dxbc::Src::kYYYY));
                bool host_depth_scaled;
                CanonicalizeSample(a, key.dest_msaa_samples, dest_sample, msaa_2x_supported_,
                                   draw_resolution_scale_x, draw_resolution_scale_y, host_depth_u,
                                   host_depth_v, host_depth_scaled);
                dxbc::Src host_depth_x(host_depth_u);
                dxbc::Src host_depth_y(host_depth_v);
                DecanonicalizeSample(a, key.host_depth_source_msaa_samples, host_depth_u,
                                     host_depth_v, host_depth_scaled, msaa_2x_supported_,
                                     draw_resolution_scale_x, draw_resolution_scale_y, host_depth_x,
                                     host_depth_y, host_depth_source_sample);

                a.OpMov(dxbc::Dest::R(0, 0b0011), dxbc::Src::R(1));
              }

              a.OpUBFE(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(xenos::kEdramPitchTilesBits),
                       dxbc::Src::LU(xenos::kEdramPitchTilesBits),
                       dxbc::Src::CB(cbuffer_index_host_depth_address,
                                     kTransferCBVRegisterHostDepthAddress, 0, dxbc::Src::kXXXX));

              a.OpUDiv(dxbc::Dest::R(0, 0b0100), dxbc::Dest::R(1, 0b0001),
                       dxbc::Src::R(0, dxbc::Src::kZZZZ), dxbc::Src::R(1, dxbc::Src::kXXXX));

              a.OpUMAd(
                  dxbc::Dest::R(0, 0b0001),
                  dxbc::Src::LU(tile_width_samples >> uint32_t(key.host_depth_source_msaa_samples >=
                                                               xenos::MsaaSamples::k4X)),
                  dxbc::Src::R(1, dxbc::Src::kXXXX), dxbc::Src::R(0, dxbc::Src::kXXXX));

              a.OpUMAd(dxbc::Dest::R(0, 0b0010),
                       dxbc::Src::LU(
                           tile_height_samples >>
                           uint32_t(key.host_depth_source_msaa_samples >= xenos::MsaaSamples::k2X)),
                       dxbc::Src::R(0, dxbc::Src::kZZZZ), dxbc::Src::R(0, dxbc::Src::kYYYY));

              if (key.host_depth_source_msaa_samples != xenos::MsaaSamples::k1X) {
                a.OpLdMS(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0), 0b0011,
                         dxbc::Src::T(srv_index_host_depth, kTransferSRVRegisterHostDepth,
                                      dxbc::Src::kXXXX),
                         host_depth_source_sample);
              } else {
                a.OpMov(dxbc::Dest::R(0, 0b0100), dxbc::Src::LU(0));
                a.OpLd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, 0b10000100), 0b1011,
                       dxbc::Src::T(srv_index_host_depth, kTransferSRVRegisterHostDepth,
                                    dxbc::Src::kXXXX));
              }
            }

            switch (dest_depth_format) {
              case xenos::DepthRenderTargetFormat::kD24S8: {
                a.OpMul(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kXXXX),
                        dxbc::Src::LF(float(0xFFFFFF)));
                a.OpRoundNE(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY));
                a.OpFToU(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY));
              } break;
              case xenos::DepthRenderTargetFormat::kD24FS8: {
                DxbcShaderTranslator::PreClampedDepthTo20e4(
                    a, 0, 1, 0, 0, 0, 2,
                    !depth_float24_convert_in_pixel_shader() && depth_float24_round(), true);
              } break;
            }
            a.OpIEq(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY),
                    dxbc::Src::R(1, dxbc::Src::kWWWW));
            a.OpIf(true, dxbc::Src::R(0, dxbc::Src::kYYYY));

            a.OpMov(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(0, dxbc::Src::kXXXX));
            a.OpElse();
          }

          switch (dest_depth_format) {
            case xenos::DepthRenderTargetFormat::kD24S8: {
              a.OpUShR(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(1, dxbc::Src::kWWWW),
                       dxbc::Src::LU(23));
              a.OpIAdd(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
                       dxbc::Src::R(0, dxbc::Src::kXXXX));
              a.OpUToF(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW));
              a.OpMul(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW),
                      dxbc::Src::LF(1.0f / float(1 << 24)));
            } break;
            case xenos::DepthRenderTargetFormat::kD24FS8: {
              DxbcShaderTranslator::Depth20e4To32(a, dxbc::Dest::R(1, 0b1000), 1, 3, 0, 1, 3, 0, 0,
                                                  true);
            } break;
          }

          if (rs & kTransferUsedRootParameterHostDepthSRVBit) {
            a.OpEndIf();
          }
        }
        a.OpMov(dxbc::Dest::ODepth(), dxbc::Src::R(1, dxbc::Src::kWWWW));
        break;
      case TransferOutput::kStencilBit:

        assert_true(cbuffer_index_stencil_mask != UINT32_MAX);
        a.OpAnd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
                dxbc::Src::CB(cbuffer_index_stencil_mask, kTransferCBVRegisterStencilMask, 0,
                              dxbc::Src::kXXXX));
        a.OpDiscard(false, dxbc::Src::R(0, dxbc::Src::kXXXX));
        break;
    }
  }

  if (dest_is_color) {
    uint32_t dest_color_component_count =
        xenos::GetColorRenderTargetFormatComponentCount(dest_color_format);
    uint32_t dest_color_unwritten_mask = 0b1111 & ~uint32_t((1 << dest_color_component_count) - 1);
    if (dest_color_component_count < 4) {
      a.OpMov(dxbc::Dest::O(0, dest_color_unwritten_mask), dxbc::Src::LU(0));
    }
  }

  a.OpRet();

  built_shader_[shex_position_dwords + 1] = uint32_t(built_shader_.size()) - shex_position_dwords;

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kShaderEx;
    blob_position_dwords = uint32_t(built_shader_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             built_shader_[blob_offset_position_dwords++];
  }

  if (shader_uses_stencil_reference_output) {
    built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
    uint32_t sfi0_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
    built_shader_.resize(sfi0_position_dwords + sizeof(dxbc::ShaderFeatureInfo) / sizeof(uint32_t));
    auto& shader_feature_info =
        *reinterpret_cast<dxbc::ShaderFeatureInfo*>(built_shader_.data() + sfi0_position_dwords);
    shader_feature_info.feature_flags[0] |= dxbc::kShaderFeature0_StencilRef;
    {
      auto& blob_header =
          *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
      blob_header.fourcc = dxbc::BlobHeader::FourCC::kShaderFeatureInfo;
      blob_position_dwords = uint32_t(built_shader_.size());
      blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                               built_shader_[blob_offset_position_dwords++];
    }
  }

  built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t stat_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  built_shader_.resize(stat_position_dwords + sizeof(dxbc::Statistics) / sizeof(uint32_t));
  std::memcpy(built_shader_.data() + stat_position_dwords, &stat, sizeof(dxbc::Statistics));
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kStatistics;
    blob_position_dwords = uint32_t(built_shader_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             built_shader_[blob_offset_position_dwords++];
  }

  uint32_t built_shader_size_bytes = uint32_t(built_shader_.size() * sizeof(uint32_t));
  {
    auto& container_header = *reinterpret_cast<dxbc::ContainerHeader*>(built_shader_.data());
    container_header.InitializeIdentification();
    container_header.size_bytes = built_shader_size_bytes;
    container_header.blob_count = blob_count;
    CalculateDXBCChecksum(reinterpret_cast<unsigned char*>(built_shader_.data()),
                          static_cast<unsigned int>(built_shader_size_bytes),
                          reinterpret_cast<unsigned int*>(&container_header.hash));
  }

  ID3D12PipelineState* const* pipelines;
  ID3D12Device* device = command_processor_.GetD3D12Provider().GetDevice();
  D3D12_INPUT_ELEMENT_DESC pipeline_input_element_desc;
  pipeline_input_element_desc.SemanticName = "POSITION";
  pipeline_input_element_desc.SemanticIndex = 0;
  pipeline_input_element_desc.Format = DXGI_FORMAT_R32G32_FLOAT;
  pipeline_input_element_desc.InputSlot = 0;
  pipeline_input_element_desc.AlignedByteOffset = 0;
  pipeline_input_element_desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
  pipeline_input_element_desc.InstanceDataStepRate = 0;
  D3D12_GRAPHICS_PIPELINE_STATE_DESC pipeline_desc = {};
  pipeline_desc.pRootSignature = transfer_root_signatures_[size_t(
      use_stencil_reference_output_ ? mode.root_signature_with_stencil_ref
                                    : mode.root_signature_no_stencil_ref)];
  pipeline_desc.VS.pShaderBytecode = shaders::passthrough_position_xy_vs;
  pipeline_desc.VS.BytecodeLength = sizeof(shaders::passthrough_position_xy_vs);
  pipeline_desc.PS.pShaderBytecode = built_shader_.data();
  pipeline_desc.PS.BytecodeLength = built_shader_size_bytes;
  if (key.dest_msaa_samples == xenos::MsaaSamples::k2X && !msaa_2x_supported_) {
    pipeline_desc.SampleMask = 0b1001;
    pipeline_desc.SampleDesc.Count = 4;
  } else {
    pipeline_desc.SampleMask = UINT_MAX;
    pipeline_desc.SampleDesc.Count = UINT(1) << UINT(key.dest_msaa_samples);
  }
  pipeline_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
  pipeline_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
  pipeline_desc.RasterizerState.DepthClipEnable = TRUE;
  pipeline_desc.InputLayout.pInputElementDescs = &pipeline_input_element_desc;
  pipeline_desc.InputLayout.NumElements = 1;
  pipeline_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
  if (dest_is_stencil_bit) {
    pipeline_desc.DepthStencilState.StencilEnable = TRUE;
    pipeline_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
    pipeline_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
    pipeline_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_REPLACE;
    pipeline_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    pipeline_desc.DepthStencilState.BackFace = pipeline_desc.DepthStencilState.FrontFace;
    pipeline_desc.DSVFormat = GetDepthDSVDXGIFormat(dest_depth_format);

    std::array<ID3D12PipelineState*, 8>& stencil_bit_pipelines =
        transfer_stencil_bit_pipelines_
            .emplace(std::piecewise_construct, std::make_tuple(key), std::make_tuple())
            .first->second;
    bool stencil_pipelines_created = true;
    for (uint32_t i = 0; i < 8; ++i) {
      pipeline_desc.DepthStencilState.StencilWriteMask = UINT8(1) << i;
      if (SUCCEEDED(device->CreateGraphicsPipelineState(&pipeline_desc,
                                                        IID_PPV_ARGS(&stencil_bit_pipelines[i])))) {
        continue;
      }
      stencil_pipelines_created = false;
      for (uint32_t j = 0; j < i; ++j) {
        stencil_bit_pipelines[j]->Release();
        stencil_bit_pipelines[j] = nullptr;
      }
      break;
    }
    pipelines = stencil_pipelines_created ? stencil_bit_pipelines.data() : nullptr;
  } else {
    if (dest_is_color) {
      pipeline_desc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
      pipeline_desc.NumRenderTargets = 1;
      pipeline_desc.RTVFormats[0] = GetColorOwnershipTransferDXGIFormat(dest_color_format);
    } else {
      pipeline_desc.DepthStencilState.DepthEnable = TRUE;
      pipeline_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
      pipeline_desc.DepthStencilState.DepthFunc = REXCVAR_GET(depth_transfer_not_equal_test)
                                                      ? D3D12_COMPARISON_FUNC_NOT_EQUAL
                                                      : D3D12_COMPARISON_FUNC_ALWAYS;
      if (use_stencil_reference_output_) {
        pipeline_desc.DepthStencilState.StencilEnable = TRUE;
        pipeline_desc.DepthStencilState.StencilWriteMask = UINT8_MAX;
        pipeline_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
        pipeline_desc.DepthStencilState.FrontFace.StencilDepthFailOp =
            REXCVAR_GET(depth_transfer_not_equal_test) ? D3D12_STENCIL_OP_REPLACE
                                                       : D3D12_STENCIL_OP_KEEP;
        pipeline_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_REPLACE;

        pipeline_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;
        pipeline_desc.DepthStencilState.BackFace = pipeline_desc.DepthStencilState.FrontFace;
      }
      pipeline_desc.DSVFormat = GetDepthDSVDXGIFormat(dest_depth_format);
    }
    ID3D12PipelineState* pipeline;
    if (FAILED(device->CreateGraphicsPipelineState(&pipeline_desc, IID_PPV_ARGS(&pipeline)))) {
      pipeline = nullptr;
    }

    ID3D12PipelineState*& inserted_pipeline =
        transfer_pipelines_.emplace(key, pipeline).first->second;
    pipelines = inserted_pipeline ? &inserted_pipeline : nullptr;
  }

  if (!pipelines) {
    const char* source_format_name =
        (rs & kTransferUsedRootParameterColorSRVBit)
            ? xenos::GetColorRenderTargetFormatName(source_color_format)
            : xenos::GetDepthRenderTargetFormatName(source_depth_format);
    const char* dest_format_name = mode.output == TransferOutput::kColor
                                       ? xenos::GetColorRenderTargetFormatName(dest_color_format)
                                       : xenos::GetDepthRenderTargetFormatName(dest_depth_format);
    if (srv_index_host_depth != UINT32_MAX) {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create a render target ownership "
          "transfer pipeline for {}-sample {} + {}-sample host depth{} -> "
          "{}-sample {} for mode {}",
          uint32_t(1) << uint32_t(key.source_msaa_samples), source_format_name,
          uint32_t(1) << uint32_t(key.host_depth_source_msaa_samples),
          key.host_depth_source_is_copy ? " copy" : "",
          uint32_t(1) << uint32_t(key.dest_msaa_samples), dest_format_name, uint32_t(key.mode));
    } else {
      REXGPU_ERROR(
          "D3D12RenderTargetCache: Failed to create a render target ownership "
          "transfer pipeline for {}-sample {} -> {}-sample {} for mode {}",
          uint32_t(1) << uint32_t(key.source_msaa_samples), source_format_name,
          uint32_t(1) << uint32_t(key.dest_msaa_samples), dest_format_name, uint32_t(key.mode));
    }
  }
  return pipelines;
}

}
