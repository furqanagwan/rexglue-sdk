

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

ID3D12PipelineState* D3D12RenderTargetCache::GetOrCreateDumpPipeline(DumpPipelineKey key) {
  auto pipeline_it = dump_pipelines_.find(key);
  if (pipeline_it != dump_pipelines_.end()) {
    return pipeline_it->second;
  }

  built_shader_.clear();

  constexpr uint32_t kBlobCount = 5;

  built_shader_.resize(sizeof(dxbc::ContainerHeader) / sizeof(uint32_t) + kBlobCount);
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

  enum Constant : uint32_t {
    kConstantOffsets,
    kConstantPitches,
    kConstantCount,
  };

  name_ptr = uint32_t((built_shader_.size() - rdef_position_dwords) * sizeof(uint32_t));
  uint32_t rdef_xe_edram_dump_offsets_name_ptr = name_ptr;
  name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_edram_dump_offsets");
  uint32_t rdef_xe_edram_dump_pitches_name_ptr = name_ptr;
  name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_edram_dump_pitches");

  uint32_t rdef_constants_position_dwords = uint32_t(built_shader_.size());
  uint32_t rdef_constants_ptr =
      uint32_t((rdef_constants_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
  built_shader_.resize(rdef_constants_position_dwords +
                       sizeof(dxbc::RdefVariable) / sizeof(uint32_t) * kConstantCount);
  {
    auto rdef_constants = reinterpret_cast<dxbc::RdefVariable*>(built_shader_.data() +
                                                                rdef_constants_position_dwords);

    dxbc::RdefVariable& rdef_constant_offsets = rdef_constants[kConstantOffsets];
    rdef_constant_offsets.name_ptr = rdef_xe_edram_dump_offsets_name_ptr;
    rdef_constant_offsets.size_bytes = sizeof(uint32_t);
    rdef_constant_offsets.flags = dxbc::kRdefVariableFlagUsed;
    rdef_constant_offsets.type_ptr = rdef_type_uint_ptr;
    rdef_constant_offsets.start_texture = UINT32_MAX;
    rdef_constant_offsets.start_sampler = UINT32_MAX;

    dxbc::RdefVariable& rdef_constant_pitches = rdef_constants[kConstantPitches];
    rdef_constant_pitches.name_ptr = rdef_xe_edram_dump_pitches_name_ptr;
    rdef_constant_pitches.size_bytes = sizeof(uint32_t);
    rdef_constant_pitches.flags = dxbc::kRdefVariableFlagUsed;
    rdef_constant_pitches.type_ptr = rdef_type_uint_ptr;
    rdef_constant_pitches.start_texture = UINT32_MAX;
    rdef_constant_pitches.start_sampler = UINT32_MAX;
  }

  uint32_t rdef_cbuffer_position_dwords = uint32_t(built_shader_.size());
  built_shader_.resize(rdef_cbuffer_position_dwords +
                       sizeof(dxbc::RdefCbuffer) / sizeof(uint32_t) * kDumpCbufferCount);
  {
    auto rdef_cbuffers =
        reinterpret_cast<dxbc::RdefCbuffer*>(built_shader_.data() + rdef_cbuffer_position_dwords);

    dxbc::RdefCbuffer& rdef_cbuffer_offsets = rdef_cbuffers[kDumpCbufferOffsets];
    rdef_cbuffer_offsets.name_ptr = rdef_xe_edram_dump_offsets_name_ptr;
    rdef_cbuffer_offsets.variable_count = 1;
    rdef_cbuffer_offsets.variables_ptr =
        uint32_t(rdef_constants_ptr + sizeof(dxbc::RdefVariable) * kConstantOffsets);
    rdef_cbuffer_offsets.size_vector_aligned_bytes = sizeof(uint32_t) * 4;

    dxbc::RdefCbuffer& rdef_cbuffer_pitches = rdef_cbuffers[kDumpCbufferPitches];
    rdef_cbuffer_pitches.name_ptr = rdef_xe_edram_dump_pitches_name_ptr;
    rdef_cbuffer_pitches.variable_count = 1;
    rdef_cbuffer_pitches.variables_ptr =
        uint32_t(rdef_constants_ptr + sizeof(dxbc::RdefVariable) * kConstantPitches);
    rdef_cbuffer_pitches.size_vector_aligned_bytes = sizeof(uint32_t) * 4;
  }

  uint32_t rdef_binding_count = 1 + key.is_depth + 1 + kDumpCbufferCount;

  name_ptr = uint32_t((built_shader_.size() - rdef_position_dwords) * sizeof(uint32_t));
  uint32_t rdef_xe_edram_dump_source_name_ptr = name_ptr;
  name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_edram_dump_source");
  uint32_t rdef_xe_edram_dump_stencil_name_ptr = name_ptr;
  if (key.is_depth) {
    name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_edram_dump_stencil");
  }
  uint32_t rdef_xe_edram_name_ptr = name_ptr;
  name_ptr += dxbc::AppendAlignedString(built_shader_, "xe_edram");

  uint32_t rdef_binding_position_dwords = uint32_t(built_shader_.size());
  built_shader_.resize(rdef_binding_position_dwords +
                       sizeof(dxbc::RdefInputBind) / sizeof(uint32_t) * rdef_binding_count);
  bool source_is_uint;
  if (key.is_depth) {
    source_is_uint = false;
  } else {
    GetColorOwnershipTransferDXGIFormat(key.GetColorFormat(), &source_is_uint);
  }
  dxbc::ResourceReturnType source_return_type =
      source_is_uint ? dxbc::ResourceReturnType::kUInt : dxbc::ResourceReturnType::kFloat;
  uint32_t source_component_count =
      key.is_depth ? 1 : xenos::GetColorRenderTargetFormatComponentCount(key.GetColorFormat());
  bool format_is_64bpp =
      !key.is_depth && xenos::IsColorRenderTargetFormat64bpp(key.GetColorFormat());
  {
    auto rdef_bindings =
        reinterpret_cast<dxbc::RdefInputBind*>(built_shader_.data() + rdef_binding_position_dwords);
    uint32_t rdef_binding_index = 0;

    dxbc::RdefInputBind& rdef_binding_source = rdef_bindings[rdef_binding_index++];
    rdef_binding_source.name_ptr = rdef_xe_edram_dump_source_name_ptr;
    rdef_binding_source.type = dxbc::RdefInputType::kTexture;
    rdef_binding_source.return_type = source_return_type;
    if (key.msaa_samples != xenos::MsaaSamples::k1X) {
      rdef_binding_source.dimension = dxbc::RdefDimension::kSRVTexture2DMS;

    } else {
      rdef_binding_source.dimension = dxbc::RdefDimension::kSRVTexture2D;
      rdef_binding_source.sample_count = UINT32_MAX;
    }
    rdef_binding_source.bind_count = 1;
    rdef_binding_source.flags = (source_component_count - 1)
                                << dxbc::kRdefInputFlagsComponentsShift;

    if (key.is_depth) {
      dxbc::RdefInputBind& rdef_binding_stencil = rdef_bindings[rdef_binding_index++];
      rdef_binding_stencil.name_ptr = rdef_xe_edram_dump_stencil_name_ptr;
      rdef_binding_stencil.type = dxbc::RdefInputType::kTexture;
      rdef_binding_stencil.return_type = dxbc::ResourceReturnType::kUInt;
      rdef_binding_stencil.dimension = rdef_binding_source.dimension;
      rdef_binding_stencil.sample_count = rdef_binding_source.sample_count;
      rdef_binding_stencil.bind_point = 1;
      rdef_binding_stencil.bind_count = 1;
      rdef_binding_stencil.flags = dxbc::kRdefInputFlags2Component;
      rdef_binding_stencil.id = 1;
    }

    dxbc::RdefInputBind& rdef_binding_edram = rdef_bindings[rdef_binding_index++];
    rdef_binding_edram.name_ptr = rdef_xe_edram_name_ptr;
    rdef_binding_edram.type = dxbc::RdefInputType::kUAVRWTyped;
    rdef_binding_edram.return_type = dxbc::ResourceReturnType::kUInt;
    rdef_binding_edram.dimension = dxbc::RdefDimension::kUAVBuffer;
    rdef_binding_edram.sample_count = UINT32_MAX;
    rdef_binding_edram.bind_count = 1;
    rdef_binding_edram.flags = format_is_64bpp ? dxbc::kRdefInputFlags2Component : 0;

    dxbc::RdefInputBind& rdef_binding_offsets = rdef_bindings[rdef_binding_index++];
    rdef_binding_offsets.name_ptr = rdef_xe_edram_dump_offsets_name_ptr;
    rdef_binding_offsets.type = dxbc::RdefInputType::kCbuffer;
    rdef_binding_offsets.bind_point = kDumpCbufferOffsets;
    rdef_binding_offsets.bind_count = 1;
    rdef_binding_offsets.flags = dxbc::kRdefInputFlagUserPacked;
    rdef_binding_offsets.id = kDumpCbufferOffsets;

    dxbc::RdefInputBind& rdef_binding_pitches = rdef_bindings[rdef_binding_index++];
    rdef_binding_pitches.name_ptr = rdef_xe_edram_dump_pitches_name_ptr;
    rdef_binding_pitches.type = dxbc::RdefInputType::kCbuffer;
    rdef_binding_pitches.bind_point = kDumpCbufferPitches;
    rdef_binding_pitches.bind_count = 1;
    rdef_binding_pitches.flags = dxbc::kRdefInputFlagUserPacked;
    rdef_binding_pitches.id = kDumpCbufferPitches;
  }

  {
    auto& rdef_header =
        *reinterpret_cast<dxbc::RdefHeader*>(built_shader_.data() + rdef_position_dwords);
    rdef_header.cbuffer_count = kDumpCbufferCount;
    rdef_header.cbuffers_ptr =
        uint32_t((rdef_cbuffer_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    rdef_header.input_bind_count = rdef_binding_count;
    rdef_header.input_binds_ptr =
        uint32_t((rdef_binding_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    rdef_header.shader_model = dxbc::RdefShaderModel::kComputeShader5_1;
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

  for (uint32_t i = 0; i < 2; ++i) {
    built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
    uint32_t signature_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
    built_shader_.resize(signature_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));
    {
      auto& signature =
          *reinterpret_cast<dxbc::Signature*>(built_shader_.data() + signature_position_dwords);

      signature.parameter_info_ptr = sizeof(dxbc::Signature);
    }
    {
      auto& blob_header =
          *reinterpret_cast<dxbc::BlobHeader*>(built_shader_.data() + blob_position_dwords);
      blob_header.fourcc = i ? dxbc::BlobHeader::FourCC::kOutputSignature
                             : dxbc::BlobHeader::FourCC::kInputSignature;
      blob_position_dwords = uint32_t(built_shader_.size());
      blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                               built_shader_[blob_offset_position_dwords++];
    }
  }

  built_shader_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t shex_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  built_shader_.resize(shex_position_dwords);

  built_shader_.push_back(dxbc::VersionToken(dxbc::ProgramType::kComputeShader, 5, 1));

  built_shader_.push_back(0);

  dxbc::Statistics stat;
  std::memset(&stat, 0, sizeof(dxbc::Statistics));
  dxbc::Assembler a(built_shader_, stat);

  a.OpDclGlobalFlags(dxbc::kGlobalFlagAllResourcesBound);
  a.OpDclConstantBuffer(
      dxbc::Src::CB(dxbc::Src::Dcl, kDumpCbufferOffsets, kDumpCbufferOffsets, kDumpCbufferOffsets),
      1);
  a.OpDclConstantBuffer(
      dxbc::Src::CB(dxbc::Src::Dcl, kDumpCbufferPitches, kDumpCbufferPitches, kDumpCbufferPitches),
      1);

  dxbc::ResourceDimension source_dimension = key.msaa_samples != xenos::MsaaSamples::k1X
                                                 ? dxbc::ResourceDimension::kTexture2DMS
                                                 : dxbc::ResourceDimension::kTexture2D;
  a.OpDclResource(
      source_dimension,
      dxbc::ResourceReturnTypeX4Token(source_is_uint ? dxbc::ResourceReturnType::kUInt
                                                     : dxbc::ResourceReturnType::kFloat),
      dxbc::Src::T(dxbc::Src::Dcl, 0, 0, 0));

  if (key.is_depth) {
    a.OpDclResource(source_dimension,
                    dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kUInt),
                    dxbc::Src::T(dxbc::Src::Dcl, 1, 1, 1));
  }

  a.OpDclUnorderedAccessViewTyped(dxbc::ResourceDimension::kBuffer, 0,
                                  dxbc::ResourceReturnTypeX4Token(dxbc::ResourceReturnType::kUInt),
                                  dxbc::Src::U(dxbc::Src::Dcl, 0, 0, 0));
  a.OpDclInput(dxbc::Dest::VThreadID(0b0011));

  stat.temp_register_count = 2;
  a.OpDclTemps(stat.temp_register_count);

  a.OpDclThreadGroup(40, 16, 1);

  uint32_t draw_resolution_scale_x = this->draw_resolution_scale_x();
  uint32_t draw_resolution_scale_y = this->draw_resolution_scale_y();

  uint32_t tile_width =
      (xenos::kEdramTileWidthSamples * draw_resolution_scale_x) >> uint32_t(format_is_64bpp);
  uint32_t tile_height = xenos::kEdramTileHeightSamples * draw_resolution_scale_y;

  a.OpUDiv(dxbc::Dest::R(0, 0b1100), dxbc::Dest::R(0, 0b0011), dxbc::Src::VThreadID(0b01000100),
           dxbc::Src::LU(tile_width, tile_height, tile_width, tile_height));

  a.OpUBFE(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(xenos::kEdramPitchTilesBits), dxbc::Src::LU(0),
           dxbc::Src::CB(kDumpCbufferPitches, kDumpCbufferPitches, 0, dxbc::Src::kXXXX));

  a.OpUMAd(dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kWWWW),
           dxbc::Src::R(1, dxbc::Src::kXXXX), dxbc::Src::R(0, dxbc::Src::kZZZZ));

  a.OpUBFE(dxbc::Dest::R(0, 0b0100), dxbc::Src::LU(xenos::kEdramBaseTilesBits + 1),
           dxbc::Src::LU(0),
           dxbc::Src::CB(kDumpCbufferOffsets, kDumpCbufferOffsets, 0, dxbc::Src::kXXXX));

  a.OpIAdd(dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kWWWW),
           dxbc::Src::R(0, dxbc::Src::kZZZZ));

  a.OpAnd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, dxbc::Src::kWWWW),
          dxbc::Src::LU(xenos::kEdramTileCount - 1));

  a.OpUMAd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, dxbc::Src::kZZZZ),
           dxbc::Src::LU(draw_resolution_scale_x * draw_resolution_scale_y *
                         (xenos::kEdramTileWidthSamples >> uint32_t(format_is_64bpp)) *
                         xenos::kEdramTileHeightSamples),
           dxbc::Src::R(0, dxbc::Src::kXXXX));

  a.OpUMAd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::LU(tile_width),
           dxbc::Src::R(0, dxbc::Src::kZZZZ));
  if (key.is_depth) {
    uint32_t tile_width_half = tile_width >> 1;

    a.OpUGE(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
            dxbc::Src::LU(tile_width_half));

    a.OpMovC(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
             dxbc::Src::LI(-int32_t(tile_width_half)), dxbc::Src::LI(int32_t(tile_width_half)));

    a.OpIAdd(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, dxbc::Src::kZZZZ),
             dxbc::Src::R(1, dxbc::Src::kXXXX));
  }

  a.OpUBFE(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(xenos::kEdramBaseTilesBits),
           dxbc::Src::LU(xenos::kEdramBaseTilesBits + 1),
           dxbc::Src::CB(kDumpCbufferOffsets, kDumpCbufferOffsets, 0, dxbc::Src::kXXXX));

  a.OpIAdd(dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kWWWW),
           -dxbc::Src::R(1, dxbc::Src::kXXXX));

  a.OpUBFE(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(xenos::kEdramPitchTilesBits),
           dxbc::Src::LU(xenos::kEdramPitchTilesBits),
           dxbc::Src::CB(kDumpCbufferPitches, kDumpCbufferPitches, 0, dxbc::Src::kXXXX));

  a.OpUDiv(dxbc::Dest::R(1, 0b0001), dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kWWWW),
           dxbc::Src::R(1, dxbc::Src::kXXXX));

  a.OpUMAd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kWWWW), dxbc::Src::LU(tile_width),
           dxbc::Src::R(0, dxbc::Src::kXXXX));

  a.OpUMAd(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(1, dxbc::Src::kXXXX),
           dxbc::Src::LU(xenos::kEdramTileHeightSamples * draw_resolution_scale_y),
           dxbc::Src::R(0, dxbc::Src::kYYYY));

  dxbc::Src source_address_src(dxbc::Src::R(0, 0b11000100));
  if (key.msaa_samples >= xenos::MsaaSamples::k2X) {
    uint32_t layout_scale_x = draw_resolution_scale_x;
    uint32_t layout_scale_y = draw_resolution_scale_y;
    bool layout_scaled = layout_scale_x > 1 || layout_scale_y > 1;
    if (layout_scaled) {
      a.OpUDiv(dxbc::Dest::R(0, 0b0011), dxbc::Dest::R(1, 0b0011), dxbc::Src::R(0),
               dxbc::Src::LU(layout_scale_x, layout_scale_y, 1, 1));
    }
    if (key.msaa_samples >= xenos::MsaaSamples::k4X) {
      a.OpUBFE(dxbc::Dest::R(0, 0b1000), dxbc::Src::LU(1), dxbc::Src::LU(1),
               dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpUBFE(dxbc::Dest::R(1, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1),
               dxbc::Src::R(0, dxbc::Src::kYYYY));

      a.OpBFI(dxbc::Dest::R(0, 0b1000), dxbc::Src::LU(1), dxbc::Src::LU(1),
              dxbc::Src::R(1, dxbc::Src::kZZZZ), dxbc::Src::R(0, dxbc::Src::kWWWW));

      a.OpUShR(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(0, dxbc::Src::kXXXX), dxbc::Src::LU(2));

      a.OpBFI(dxbc::Dest::R(0, 0b0001), dxbc::Src::LU(31), dxbc::Src::LU(1),
              dxbc::Src::R(1, dxbc::Src::kZZZZ), dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpUShR(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::LU(2));

      a.OpBFI(dxbc::Dest::R(0, 0b0010), dxbc::Src::LU(31), dxbc::Src::LU(1),
              dxbc::Src::R(1, dxbc::Src::kZZZZ), dxbc::Src::R(0, dxbc::Src::kYYYY));
    } else {
      a.OpUBFE(dxbc::Dest::R(0, 0b1000), dxbc::Src::LU(1), dxbc::Src::LU(1),
               dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpAnd(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::LU(2));

      a.OpAnd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
              dxbc::Src::LU(~uint32_t(2)));

      a.OpOr(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
             dxbc::Src::R(1, dxbc::Src::kZZZZ));

      a.OpAnd(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::LU(1));

      a.OpAnd(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY),
              dxbc::Src::LU(~uint32_t(3)));

      a.OpUShR(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY), dxbc::Src::LU(1));

      a.OpOr(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, dxbc::Src::kYYYY),
             dxbc::Src::R(1, dxbc::Src::kZZZZ));

      a.OpMovC(dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kWWWW),
               dxbc::Src::LU(draw_util::GetD3D10SampleIndexForGuest2xMSAA(1, msaa_2x_supported_)),
               dxbc::Src::LU(draw_util::GetD3D10SampleIndexForGuest2xMSAA(0, msaa_2x_supported_)));
    }
    if (layout_scaled) {
      a.OpUMAd(dxbc::Dest::R(0, 0b0011), dxbc::Src::R(0),
               dxbc::Src::LU(layout_scale_x, layout_scale_y, 1, 1), dxbc::Src::R(1));
    }

    a.OpLdMS(dxbc::Dest::R(1, (1 << source_component_count) - 1), source_address_src, 0b0011,
             dxbc::Src::T(0, 0), dxbc::Src::R(0, dxbc::Src::kWWWW));
    if (key.is_depth) {
      a.OpLdMS(dxbc::Dest::R(1, 0b0010), source_address_src, 0b0011, dxbc::Src::T(1, 1),
               dxbc::Src::R(0, dxbc::Src::kWWWW));
    }
  } else {
    a.OpMov(dxbc::Dest::R(0, 0b1000), dxbc::Src::LF(0.0f));

    a.OpLd(dxbc::Dest::R(1, (1 << source_component_count) - 1), source_address_src, 0b1011,
           dxbc::Src::T(0, 0));
    if (key.is_depth) {
      a.OpLd(dxbc::Dest::R(1, 0b0010), source_address_src, 0b1011, dxbc::Src::T(1, 1));
    }
  }

  if (key.is_depth) {
    switch (key.GetDepthFormat()) {
      case xenos::DepthRenderTargetFormat::kD24S8:

        a.OpMul(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX),
                dxbc::Src::LF(float(0xFFFFFF)));
        a.OpRoundNE(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX));
        a.OpFToU(dxbc::Dest::R(1, 0b0001), dxbc::Src::R(1, dxbc::Src::kXXXX));
        break;
      case xenos::DepthRenderTargetFormat::kD24FS8:

        DxbcShaderTranslator::PreClampedDepthTo20e4(
            a, 1, 0, 1, 0, 0, 0, !depth_float24_convert_in_pixel_shader() && depth_float24_round(),
            true);
        break;
    }

    a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(24), dxbc::Src::LU(8),
            dxbc::Src::R(1, dxbc::Src::kXXXX), dxbc::Src::R(1, dxbc::Src::kYYYY));
  } else {
    switch (key.GetColorFormat()) {
      case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA:

        assert_false(source_is_uint);
        for (uint32_t i = 0; i < 3; ++i) {
          DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(a, 1, i, 1, i, 0, 0, 0, 1);
        }
        a.OpMAd(dxbc::Dest::R(1), dxbc::Src::R(1), dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
        a.OpFToU(dxbc::Dest::R(1), dxbc::Src::R(1));
        for (uint32_t i = 1; i < 4; ++i) {
          a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(8), dxbc::Src::LU(i * 8),
                  dxbc::Src::R(1).Select(i), dxbc::Src::R(1, dxbc::Src::kXXXX));
        }
        break;
      case xenos::ColorRenderTargetFormat::k_8_8_8_8:
        if (!source_is_uint) {
          a.OpMAd(dxbc::Dest::R(1), dxbc::Src::R(1), dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
          a.OpFToU(dxbc::Dest::R(1), dxbc::Src::R(1));
        }
        for (uint32_t i = 1; i < 4; ++i) {
          a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(8), dxbc::Src::LU(i * 8),
                  dxbc::Src::R(1).Select(i), dxbc::Src::R(1, dxbc::Src::kXXXX));
        }
        break;
      case xenos::ColorRenderTargetFormat::k_2_10_10_10:
      case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10:
        if (!source_is_uint) {
          a.OpMAd(dxbc::Dest::R(1), dxbc::Src::R(1), dxbc::Src::LF(1023.0f, 1023.0f, 1023.0f, 3.0f),
                  dxbc::Src::LF(0.5f));
          a.OpFToU(dxbc::Dest::R(1), dxbc::Src::R(1));
        }
        for (uint32_t i = 1; i < 4; ++i) {
          a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(i == 3 ? 2 : 10), dxbc::Src::LU(i * 10),
                  dxbc::Src::R(1).Select(i), dxbc::Src::R(1, dxbc::Src::kXXXX));
        }
        break;
      case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
      case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16:

        DxbcShaderTranslator::UnclampedFloat32To7e3(a, 1, 0, 1, 0, 0, 0);
        for (uint32_t i = 1; i < 3; ++i) {
          DxbcShaderTranslator::UnclampedFloat32To7e3(a, 0, 0, 1, i, 0, 1);
          a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(10), dxbc::Src::LU(i * 10),
                  dxbc::Src::R(0, dxbc::Src::kXXXX), dxbc::Src::R(1, dxbc::Src::kXXXX));
        }

        a.OpMov(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW), true);
        a.OpMAd(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW), dxbc::Src::LF(3.0f),
                dxbc::Src::LF(0.5f));
        a.OpFToU(dxbc::Dest::R(1, 0b1000), dxbc::Src::R(1, dxbc::Src::kWWWW));
        a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(2), dxbc::Src::LU(30),
                dxbc::Src::R(1, dxbc::Src::kWWWW), dxbc::Src::R(1, dxbc::Src::kXXXX));
        break;
      case xenos::ColorRenderTargetFormat::k_16_16:
      case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
        assert_true(source_is_uint);
        a.OpBFI(dxbc::Dest::R(1, 0b0001), dxbc::Src::LU(16), dxbc::Src::LU(16),
                dxbc::Src::R(1, dxbc::Src::kYYYY), dxbc::Src::R(1, dxbc::Src::kXXXX));
        break;
      case xenos::ColorRenderTargetFormat::k_16_16_16_16:
      case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT:
        assert_true(source_is_uint);
        a.OpBFI(dxbc::Dest::R(1, 0b0011), dxbc::Src::LU(16), dxbc::Src::LU(16),
                dxbc::Src::R(1, 0b1101), dxbc::Src::R(1, 0b1000));
        break;
      case xenos::ColorRenderTargetFormat::k_32_FLOAT:
      case xenos::ColorRenderTargetFormat::k_32_32_FLOAT:
        assert_true(source_is_uint);

        break;
    }
  }

  a.OpStoreUAVTyped(dxbc::Dest::U(0, 0), dxbc::Src::R(0, dxbc::Src::kZZZZ), 1,
                    dxbc::Src::R(1, format_is_64bpp ? 0b0100 : dxbc::Src::kXXXX));

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
    container_header.blob_count = kBlobCount;
    CalculateDXBCChecksum(reinterpret_cast<unsigned char*>(built_shader_.data()),
                          static_cast<unsigned int>(built_shader_size_bytes),
                          reinterpret_cast<unsigned int*>(&container_header.hash));
  }

  ID3D12PipelineState* pipeline = ui::d3d12::util::CreateComputePipeline(
      command_processor_.GetD3D12Provider().GetDevice(), built_shader_.data(),
      built_shader_size_bytes,
      key.is_depth ? dump_root_signature_depth_ : dump_root_signature_color_);
  const char* format_name = key.is_depth
                                ? xenos::GetDepthRenderTargetFormatName(key.GetDepthFormat())
                                : xenos::GetColorRenderTargetFormatName(key.GetColorFormat());
  if (pipeline) {
    std::u16string pipeline_name = rex::string::to_utf16(
        fmt::format("RT Dump {} {}xMSAA", format_name, uint32_t(1) << uint32_t(key.msaa_samples)));
    pipeline->SetName(reinterpret_cast<LPCWSTR>(pipeline_name.c_str()));
  } else {
    REXGPU_ERROR(
        "D3D12RenderTargetCache: Failed to create a render target dumping "
        "pipeline for {}-sample render targets with format {}",
        uint32_t(1) << uint32_t(key.msaa_samples), format_name);
  }

  dump_pipelines_.emplace(key, pipeline);
  return pipeline;
}

ID3D12PipelineState* D3D12RenderTargetCache::GetOrCreateDirectResolvePipeline(
    DirectResolvePipelineKey key) {
  auto pipeline_it = direct_resolve_pipelines_.find(key);
  if (pipeline_it != direct_resolve_pipelines_.end()) {
    return pipeline_it->second;
  }
  ID3D12PipelineState* pipeline = nullptr;

  size_t copy_shader_index = size_t(key.copy_shader);
  if (copy_shader_index < size_t(draw_util::ResolveCopyShaderIndex::kCount)) {
    pipeline = resolve_copy_pipelines_[copy_shader_index];
  }
  direct_resolve_pipelines_.emplace(key, pipeline);
  return pipeline;
}

bool D3D12RenderTargetCache::TryResolveCopyDirectly(const draw_util::ResolveInfo& resolve_info,
                                                    draw_util::ResolveCopyShaderIndex copy_shader,
                                                    bool draw_resolution_scaled) {
  ++direct_resolve_attempt_count_;
  (void)copy_shader;
  (void)draw_resolution_scaled;
  if (!direct_resolve_root_signature_color_ || !direct_resolve_root_signature_depth_) {
    return false;
  }

  uint32_t dump_base;
  uint32_t dump_row_length_used;
  uint32_t dump_rows;
  uint32_t dump_pitch;
  resolve_info.GetCopyEdramTileSpan(dump_base, dump_row_length_used, dump_rows, dump_pitch);
  GetResolveCopyDispatchesToDump(dump_base, dump_row_length_used, dump_rows, dump_pitch,
                                 dump_rectangles_, direct_resolve_dispatches_);
  if (direct_resolve_dispatches_.empty()) {
    return false;
  }

  for (const ResolveCopyDumpRectangle& rectangle : dump_rectangles_) {
    const auto* render_target = static_cast<const D3D12RenderTarget*>(rectangle.render_target);
    if (render_target == nullptr) {
      return false;
    }
    DumpPipelineKey dump_pipeline_key;
    dump_pipeline_key.msaa_samples = render_target->key().msaa_samples;
    dump_pipeline_key.resource_format = render_target->key().resource_format;
    dump_pipeline_key.is_depth = render_target->key().is_depth;
    if (!GetOrCreateDumpPipeline(dump_pipeline_key)) {
      return false;
    }
    DirectResolvePipelineKey direct_pipeline_key;
    direct_pipeline_key.dump_pipeline_key = dump_pipeline_key;
    direct_pipeline_key.copy_shader = copy_shader;
    direct_pipeline_key.draw_resolution_scaled = draw_resolution_scaled;
    if (!GetOrCreateDirectResolvePipeline(direct_pipeline_key)) {
      return false;
    }
  }

  return DumpRenderTargets(dump_base, dump_row_length_used, dump_rows, dump_pitch);
}

bool D3D12RenderTargetCache::DumpRenderTargets(uint32_t dump_base, uint32_t dump_row_length_used,
                                               uint32_t dump_rows, uint32_t dump_pitch) {
  assert_true(GetPath() == Path::kHostRenderTargets);

  GetResolveCopyRectanglesToDump(dump_base, dump_row_length_used, dump_rows, dump_pitch,
                                 dump_rectangles_);
  if (dump_rectangles_.empty()) {
    return true;
  }

  for (const ResolveCopyDumpRectangle& rectangle : dump_rectangles_) {
    auto& d3d12_rt = *static_cast<D3D12RenderTarget*>(rectangle.render_target);
    d3d12_rt.SetTemporarySortIndex(UINT32_MAX);
    d3d12_rt.SetTemporarySRVDescriptorIndex(UINT32_MAX);
    d3d12_rt.SetTemporarySRVDescriptorIndexStencil(UINT32_MAX);
  }

  TransitionEdramBuffer(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
  dump_invocations_.clear();
  dump_invocations_.reserve(dump_rectangles_.size());
  current_temporary_descriptors_cpu_.clear();
  bool any_sources_32bpp_64bpp[2] = {};
  uint32_t rt_sort_index = 0;
  for (const ResolveCopyDumpRectangle& rectangle : dump_rectangles_) {
    auto& d3d12_rt = *static_cast<D3D12RenderTarget*>(rectangle.render_target);
    command_processor_.PushTransitionBarrier(
        d3d12_rt.resource(),
        d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE),
        D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
    if (d3d12_rt.temporary_sort_index() == UINT32_MAX) {
      d3d12_rt.SetTemporarySortIndex(rt_sort_index++);
    }
    if (d3d12_rt.temporary_srv_descriptor_index() == UINT32_MAX) {
      d3d12_rt.SetTemporarySRVDescriptorIndex(uint32_t(current_temporary_descriptors_cpu_.size()));
      current_temporary_descriptors_cpu_.push_back(d3d12_rt.descriptor_srv().GetHandle());
    }
    RenderTargetKey rt_key = d3d12_rt.key();
    if (rt_key.is_depth && d3d12_rt.temporary_srv_descriptor_index_stencil() == UINT32_MAX) {
      d3d12_rt.SetTemporarySRVDescriptorIndexStencil(
          uint32_t(current_temporary_descriptors_cpu_.size()));
      current_temporary_descriptors_cpu_.push_back(d3d12_rt.descriptor_srv_stencil().GetHandle());
    }
    any_sources_32bpp_64bpp[size_t(rt_key.Is64bpp())] = true;
    DumpPipelineKey pipeline_key;
    pipeline_key.msaa_samples = rt_key.msaa_samples;
    pipeline_key.resource_format = rt_key.resource_format;
    pipeline_key.is_depth = rt_key.is_depth;
    dump_invocations_.emplace_back(rectangle, pipeline_key);
  }

  size_t edram_uav_indices[2] = {SIZE_MAX, SIZE_MAX};
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  if (!bindless_resources_used_) {
    if (any_sources_32bpp_64bpp[0]) {
      edram_uav_indices[0] = current_temporary_descriptors_cpu_.size();
      current_temporary_descriptors_cpu_.push_back(provider.OffsetViewDescriptor(
          edram_buffer_descriptor_heap_start_, uint32_t(EdramBufferDescriptorIndex::kR32UintUAV)));
    }
    if (any_sources_32bpp_64bpp[1]) {
      edram_uav_indices[1] = current_temporary_descriptors_cpu_.size();
      current_temporary_descriptors_cpu_.push_back(
          provider.OffsetViewDescriptor(edram_buffer_descriptor_heap_start_,
                                        uint32_t(EdramBufferDescriptorIndex::kR32G32UintUAV)));
    }
  }

  ID3D12Device* device = provider.GetDevice();
  uint32_t descriptor_count = uint32_t(current_temporary_descriptors_cpu_.size());
  current_temporary_descriptors_gpu_.resize(descriptor_count);
  if (!command_processor_.RequestOneUseSingleViewDescriptors(
          descriptor_count, current_temporary_descriptors_gpu_.data())) {
    return false;
  }
  for (uint32_t i = 0; i < descriptor_count; ++i) {
    device->CopyDescriptorsSimple(1, current_temporary_descriptors_gpu_[i].first,
                                  current_temporary_descriptors_cpu_[i],
                                  D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  }

  std::sort(dump_invocations_.begin(), dump_invocations_.end());

  DeferredCommandList& command_list = command_processor_.GetDeferredCommandList();
  ID3D12RootSignature* last_root_signature = nullptr;
  uint32_t root_parameters_set = 0;
  uint32_t last_descriptor_index_source = UINT32_MAX;
  uint32_t last_descriptor_index_stencil = UINT32_MAX;
  bool last_edram_uav_is_64bpp = false;
  DumpOffsets last_offsets;
  DumpPitches last_pitches;
  bool all_pipelines_available = true;
  for (const DumpInvocation& invocation : dump_invocations_) {
    const ResolveCopyDumpRectangle& rectangle = invocation.rectangle;
    auto& d3d12_rt = *static_cast<D3D12RenderTarget*>(rectangle.render_target);
    RenderTargetKey rt_key = d3d12_rt.key();
    DumpPipelineKey pipeline_key = invocation.pipeline_key;
    ID3D12PipelineState* pipeline = GetOrCreateDumpPipeline(pipeline_key);
    if (!pipeline) {
      all_pipelines_available = false;
      continue;
    }
    command_processor_.SetExternalPipeline(pipeline);

    ID3D12RootSignature* root_signature =
        pipeline_key.is_depth ? dump_root_signature_depth_ : dump_root_signature_color_;
    if (last_root_signature != root_signature) {
      last_root_signature = root_signature;
      command_list.D3DSetComputeRootSignature(root_signature);
      root_parameters_set = 0;
    }

    DumpRootParameter root_parameter_edram =
        pipeline_key.is_depth ? kDumpRootParameterDepthEdram : kDumpRootParameterColorEdram;
    uint32_t root_parameter_edram_bit = uint32_t(1) << root_parameter_edram;
    bool format_is_64bpp = rt_key.Is64bpp();
    if (last_edram_uav_is_64bpp != format_is_64bpp) {
      last_edram_uav_is_64bpp = format_is_64bpp;
      root_parameters_set &= ~root_parameter_edram_bit;
    }
    if (!(root_parameters_set & root_parameter_edram_bit)) {
      D3D12_GPU_DESCRIPTOR_HANDLE descriptor_handle_edram;
      if (bindless_resources_used_) {
        descriptor_handle_edram =
            command_processor_
                .GetEdramUintPow2BindlessUAVHandlePair(2 + uint32_t(last_edram_uav_is_64bpp))
                .second;
      } else {
        assert_true(edram_uav_indices[size_t(last_edram_uav_is_64bpp)] != SIZE_MAX);
        descriptor_handle_edram =
            current_temporary_descriptors_gpu_[edram_uav_indices[size_t(last_edram_uav_is_64bpp)]]
                .second;
      }
      command_list.D3DSetComputeRootDescriptorTable(root_parameter_edram, descriptor_handle_edram);
      root_parameters_set |= root_parameter_edram_bit;
    }

    DumpRootParameter root_parameter_pitches =
        pipeline_key.is_depth ? kDumpRootParameterDepthPitches : kDumpRootParameterColorPitches;
    uint32_t root_parameter_pitches_bit = uint32_t(1) << root_parameter_pitches;
    DumpPitches pitches;
    pitches.dest_pitch = dump_pitch;
    pitches.source_pitch = rt_key.GetPitchTiles();
    if (last_pitches != pitches) {
      last_pitches = pitches;
      root_parameters_set &= ~root_parameter_pitches_bit;
    }
    if (!(root_parameters_set & root_parameter_pitches_bit)) {
      command_list.D3DSetComputeRoot32BitConstants(
          root_parameter_pitches, sizeof(last_pitches) / sizeof(uint32_t), &last_pitches, 0);
      root_parameters_set |= root_parameter_pitches_bit;
    }

    if (pipeline_key.is_depth) {
      constexpr uint32_t kDumpRootParameterDepthStencilBit = uint32_t(1)
                                                             << kDumpRootParameterDepthStencil;
      uint32_t descriptor_index_stencil = d3d12_rt.temporary_srv_descriptor_index_stencil();
      assert_true(descriptor_index_stencil != UINT32_MAX);
      if (last_descriptor_index_stencil != descriptor_index_stencil) {
        last_descriptor_index_stencil = descriptor_index_stencil;
        root_parameters_set &= ~kDumpRootParameterDepthStencilBit;
      }
      if (!(root_parameters_set & kDumpRootParameterDepthStencilBit)) {
        command_list.D3DSetComputeRootDescriptorTable(
            kDumpRootParameterDepthStencil,
            current_temporary_descriptors_gpu_[last_descriptor_index_stencil].second);
        root_parameters_set |= kDumpRootParameterDepthStencilBit;
      }
    }

    constexpr uint32_t kDumpRootParameterSourceBit = uint32_t(1) << kDumpRootParameterSource;
    uint32_t descriptor_index_source = d3d12_rt.temporary_srv_descriptor_index();
    assert_true(descriptor_index_source != UINT32_MAX);
    if (last_descriptor_index_source != descriptor_index_source) {
      last_descriptor_index_source = descriptor_index_source;
      root_parameters_set &= ~kDumpRootParameterSourceBit;
    }
    if (!(root_parameters_set & kDumpRootParameterSourceBit)) {
      command_list.D3DSetComputeRootDescriptorTable(
          kDumpRootParameterSource,
          current_temporary_descriptors_gpu_[last_descriptor_index_source].second);
      root_parameters_set |= kDumpRootParameterSourceBit;
    }

    constexpr uint32_t kDumpRootParameterOffsetsBit = uint32_t(1) << kDumpRootParameterOffsets;
    DumpOffsets offsets;
    offsets.source_base_tiles = rt_key.base_tiles;
    ResolveCopyDumpRectangle::Dispatch dispatches[ResolveCopyDumpRectangle::kMaxDispatches];
    uint32_t dispatch_count = rectangle.GetDispatches(dump_pitch, dump_row_length_used, dispatches);
    for (uint32_t i = 0; i < dispatch_count; ++i) {
      const ResolveCopyDumpRectangle::Dispatch& dispatch = dispatches[i];
      offsets.dispatch_first_tile = dump_base + dispatch.offset;
      if (last_offsets != offsets) {
        last_offsets = offsets;
        root_parameters_set &= ~kDumpRootParameterOffsetsBit;
      }
      if (!(root_parameters_set & kDumpRootParameterOffsetsBit)) {
        command_list.D3DSetComputeRoot32BitConstants(
            kDumpRootParameterOffsets, sizeof(last_offsets) / sizeof(uint32_t), &last_offsets, 0);
        root_parameters_set |= kDumpRootParameterOffsetsBit;
      }
      command_processor_.SubmitBarriers();

      command_list.D3DDispatch((dispatch.width_tiles * draw_resolution_scale_x())
                                   << uint32_t(!format_is_64bpp),
                               dispatch.height_tiles * draw_resolution_scale_y(), 1);
    }
    MarkEdramBufferModified();
  }
  return all_pipelines_available;
}

}
