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
#include <atomic>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <deque>
#include <mutex>
#include <set>
#include <utility>
#include <vector>
#include <fmt/format.h>
#include <rex/assert.h>
#include <rex/chrono/clock.h>
#if REXGLUE_SHADER_DXIL
#include <rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h>
#include <rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h>
#include <rex/graphics/pipeline/shader/spirv_translator.h>
#endif
#include <rex/cvar.h>
#include <rex/dbg.h>
#include <rex/perf/counter.h>
#include <rex/filesystem.h>
#include <rex/graphics/d3d12/command_processor.h>
#include <rex/graphics/d3d12/pipeline_cache.h>
#include <rex/graphics/d3d12/render_target_cache.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/storage_seed.h>
#include <rex/graphics/format/dxbc.h>
#include <rex/graphics/pipeline_util.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/hash.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string.h>
#include <rex/string/buffer.h>
#include <rex/thread.h>
#include <rex/types.h>
#include <rex/ui/d3d12/d3d12_util.h>

namespace rex::graphics::d3d12 {

bool PipelineCache::GetGeometryShaderKey(
    PipelineGeometryShader geometry_shader_type,
    DxbcShaderTranslator::Modification vertex_shader_modification,
    DxbcShaderTranslator::Modification pixel_shader_modification, GeometryShaderKey& key_out) {
  if (geometry_shader_type == PipelineGeometryShader::kNone) {
    return false;
  }
  assert_true(vertex_shader_modification.vertex.interpolator_mask ==
              pixel_shader_modification.pixel.interpolator_mask);
  GeometryShaderKey key;
  key.type = geometry_shader_type;
  key.interpolator_count = rex::bit_count(vertex_shader_modification.vertex.interpolator_mask);
  key.user_clip_plane_count = vertex_shader_modification.vertex.user_clip_plane_count;
  key.user_clip_plane_cull = vertex_shader_modification.vertex.user_clip_plane_cull;
  key.has_vertex_kill_and = vertex_shader_modification.vertex.vertex_kill_and;
  key.has_point_size = vertex_shader_modification.vertex.output_point_size;
  key.has_point_coordinates = pixel_shader_modification.pixel.param_gen_point;
  key.point_ps_ucp_mode = vertex_shader_modification.vertex.point_ps_ucp_mode;
  key_out = key;
  return true;
}

void PipelineCache::CreateDxbcGeometryShader(GeometryShaderKey key,
                                             std::vector<uint32_t>& shader_out) {
  shader_out.clear();
  uint32_t point_clip_distance_count = key.user_clip_plane_cull ? 0 : key.user_clip_plane_count;
  uint32_t point_user_cull_distance_count =
      key.type == PipelineGeometryShader::kPointList && key.user_clip_plane_cull
          ? key.user_clip_plane_count
          : 0;
  bool point_recalculate_clip_distances = key.type == PipelineGeometryShader::kPointList &&
                                          point_clip_distance_count && key.point_ps_ucp_mode >= 2;
  bool point_recalculate_cull_distances = key.type == PipelineGeometryShader::kPointList &&
                                          point_user_cull_distance_count &&
                                          key.point_ps_ucp_mode >= 3;

  constexpr uint32_t kBlobCount = 5;

  shader_out.resize(sizeof(dxbc::ContainerHeader) / sizeof(uint32_t) + kBlobCount);
  uint32_t blob_offset_position_dwords = sizeof(dxbc::ContainerHeader) / sizeof(uint32_t);
  uint32_t blob_position_dwords = uint32_t(shader_out.size());
  constexpr uint32_t kBlobHeaderSizeDwords = sizeof(dxbc::BlobHeader) / sizeof(uint32_t);

  uint32_t name_ptr;

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t rdef_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;

  shader_out.resize(rdef_position_dwords + sizeof(dxbc::RdefHeader) / sizeof(uint32_t));

  dxbc::AppendAlignedString(shader_out, "Xenia");
  {
    auto& rdef_header =
        *reinterpret_cast<dxbc::RdefHeader*>(shader_out.data() + rdef_position_dwords);
    rdef_header.shader_model = dxbc::RdefShaderModel::kGeometryShader5_1;
    rdef_header.compile_flags =
        dxbc::kCompileFlagNoPreshader | dxbc::kCompileFlagPreferFlowControl |
        dxbc::kCompileFlagIeeeStrictness | dxbc::kCompileFlagAllResourcesBound;

    rdef_header.generator_name_ptr = sizeof(dxbc::RdefHeader);
    rdef_header.fourcc = dxbc::RdefHeader::FourCC::k5_1;
    rdef_header.InitializeSizes();
  }

  uint32_t system_cbuffer_size_vector_aligned_bytes = 0;

  if (key.type == PipelineGeometryShader::kPointList ||
      key.type == PipelineGeometryShader::kLineList) {
    name_ptr = uint32_t((shader_out.size() - rdef_position_dwords) * sizeof(uint32_t));
    uint32_t rdef_name_ptr_float2 = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "float2");

    uint32_t rdef_type_float2_position_dwords = uint32_t(shader_out.size());
    uint32_t rdef_type_float2_ptr =
        uint32_t((rdef_type_float2_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    shader_out.resize(rdef_type_float2_position_dwords + sizeof(dxbc::RdefType) / sizeof(uint32_t));
    {
      auto& rdef_type_float2 =
          *reinterpret_cast<dxbc::RdefType*>(shader_out.data() + rdef_type_float2_position_dwords);
      rdef_type_float2.variable_class = dxbc::RdefVariableClass::kVector;
      rdef_type_float2.variable_type = dxbc::RdefVariableType::kFloat;
      rdef_type_float2.row_count = 1;
      rdef_type_float2.column_count = 2;
      rdef_type_float2.name_ptr = rdef_name_ptr_float2;
    }

    enum PointConstant : uint32_t {
      kPointConstantConstantDiameter,
      kPointConstantScreenDiameterToNDCRadius,
      kPointConstantCount,
    };

    name_ptr = uint32_t((shader_out.size() - rdef_position_dwords) * sizeof(uint32_t));
    uint32_t rdef_name_ptr_xe_point_constant_diameter = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "xe_point_constant_diameter");
    uint32_t rdef_name_ptr_xe_point_screen_diameter_to_ndc_radius = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "xe_point_screen_diameter_to_ndc_radius");

    uint32_t rdef_constants_position_dwords = uint32_t(shader_out.size());
    uint32_t rdef_constants_ptr =
        uint32_t((rdef_constants_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    shader_out.resize(rdef_constants_position_dwords +
                      sizeof(dxbc::RdefVariable) / sizeof(uint32_t) * kPointConstantCount);
    {
      auto rdef_constants =
          reinterpret_cast<dxbc::RdefVariable*>(shader_out.data() + rdef_constants_position_dwords);

      static_assert(sizeof(DxbcShaderTranslator::SystemConstants ::point_constant_diameter) ==
                        sizeof(float) * 2,
                    "DxbcShaderTranslator point_constant_diameter system constant size "
                    "differs between the shader translator and geometry shader "
                    "generation");
      static_assert_size(DxbcShaderTranslator::SystemConstants::point_constant_diameter,
                         sizeof(float) * 2);
      dxbc::RdefVariable& rdef_constant_point_constant_diameter =
          rdef_constants[kPointConstantConstantDiameter];
      rdef_constant_point_constant_diameter.name_ptr = rdef_name_ptr_xe_point_constant_diameter;
      rdef_constant_point_constant_diameter.start_offset_bytes =
          offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter);
      rdef_constant_point_constant_diameter.size_bytes = sizeof(float) * 2;
      rdef_constant_point_constant_diameter.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_point_constant_diameter.type_ptr = rdef_type_float2_ptr;
      rdef_constant_point_constant_diameter.start_texture = UINT32_MAX;
      rdef_constant_point_constant_diameter.start_sampler = UINT32_MAX;

      static_assert(
          sizeof(DxbcShaderTranslator::SystemConstants ::point_screen_diameter_to_ndc_radius) ==
              sizeof(float) * 2,
          "DxbcShaderTranslator point_screen_diameter_to_ndc_radius system "
          "constant size differs between the shader translator and geometry "
          "shader generation");
      dxbc::RdefVariable& rdef_constant_point_screen_diameter_to_ndc_radius =
          rdef_constants[kPointConstantScreenDiameterToNDCRadius];
      rdef_constant_point_screen_diameter_to_ndc_radius.name_ptr =
          rdef_name_ptr_xe_point_screen_diameter_to_ndc_radius;
      rdef_constant_point_screen_diameter_to_ndc_radius.start_offset_bytes =
          offsetof(DxbcShaderTranslator::SystemConstants, point_screen_diameter_to_ndc_radius);
      rdef_constant_point_screen_diameter_to_ndc_radius.size_bytes = sizeof(float) * 2;
      rdef_constant_point_screen_diameter_to_ndc_radius.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_point_screen_diameter_to_ndc_radius.type_ptr = rdef_type_float2_ptr;
      rdef_constant_point_screen_diameter_to_ndc_radius.start_texture = UINT32_MAX;
      rdef_constant_point_screen_diameter_to_ndc_radius.start_sampler = UINT32_MAX;
    }

    name_ptr = uint32_t((shader_out.size() - rdef_position_dwords) * sizeof(uint32_t));
    uint32_t rdef_name_ptr_xe_system_cbuffer = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "xe_system_cbuffer");

    uint32_t rdef_cbuffer_position_dwords = uint32_t(shader_out.size());
    shader_out.resize(rdef_cbuffer_position_dwords + sizeof(dxbc::RdefCbuffer) / sizeof(uint32_t));
    {
      auto& rdef_cbuffer_system =
          *reinterpret_cast<dxbc::RdefCbuffer*>(shader_out.data() + rdef_cbuffer_position_dwords);
      rdef_cbuffer_system.name_ptr = rdef_name_ptr_xe_system_cbuffer;
      rdef_cbuffer_system.variable_count = kPointConstantCount;
      rdef_cbuffer_system.variables_ptr = rdef_constants_ptr;
      auto rdef_constants = reinterpret_cast<const dxbc::RdefVariable*>(
          shader_out.data() + rdef_constants_position_dwords);
      for (uint32_t i = 0; i < kPointConstantCount; ++i) {
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     rdef_constants[i].start_offset_bytes + rdef_constants[i].size_bytes);
      }
      if (point_recalculate_clip_distances || point_recalculate_cull_distances) {
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     uint32_t(offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) +
                              sizeof(float) * 3));
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     uint32_t(offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) +
                              sizeof(float) * 3));
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     uint32_t(offsetof(DxbcShaderTranslator::SystemConstants, user_clip_planes) +
                              sizeof(float) * 4 * 6));
      }
      system_cbuffer_size_vector_aligned_bytes =
          rex::align(system_cbuffer_size_vector_aligned_bytes, uint32_t(sizeof(uint32_t) * 4));
      rdef_cbuffer_system.size_vector_aligned_bytes = system_cbuffer_size_vector_aligned_bytes;
    }

    uint32_t rdef_binding_position_dwords = uint32_t(shader_out.size());
    shader_out.resize(rdef_binding_position_dwords +
                      sizeof(dxbc::RdefInputBind) / sizeof(uint32_t));
    {
      auto& rdef_binding_cbuffer_system =
          *reinterpret_cast<dxbc::RdefInputBind*>(shader_out.data() + rdef_binding_position_dwords);
      rdef_binding_cbuffer_system.name_ptr = rdef_name_ptr_xe_system_cbuffer;
      rdef_binding_cbuffer_system.type = dxbc::RdefInputType::kCbuffer;
      rdef_binding_cbuffer_system.bind_point =
          uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants);
      rdef_binding_cbuffer_system.bind_count = 1;
      rdef_binding_cbuffer_system.flags = dxbc::kRdefInputFlagUserPacked;
    }

    {
      auto& rdef_header =
          *reinterpret_cast<dxbc::RdefHeader*>(shader_out.data() + rdef_position_dwords);
      rdef_header.cbuffer_count = 1;
      rdef_header.cbuffers_ptr =
          uint32_t((rdef_cbuffer_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
      rdef_header.input_bind_count = 1;
      rdef_header.input_binds_ptr =
          uint32_t((rdef_binding_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    }
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kResourceDefinition;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  uint32_t input_clip_distance_count = key.user_clip_plane_cull ? 0 : key.user_clip_plane_count;
  uint32_t input_cull_distance_count =
      (key.user_clip_plane_cull ? key.user_clip_plane_count : 0) + key.has_vertex_kill_and;
  uint32_t input_clip_and_cull_distance_count =
      input_clip_distance_count + input_cull_distance_count;

  uint32_t isgn_parameter_count =
      key.interpolator_count + 1 + ((input_clip_and_cull_distance_count + 3) / 4) +
      uint32_t(input_cull_distance_count && (input_clip_distance_count & 3) != 0) +
      key.has_point_size;

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t isgn_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(isgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t) +
                    sizeof(dxbc::SignatureParameter) / sizeof(uint32_t) * isgn_parameter_count);

  name_ptr = uint32_t((shader_out.size() - isgn_position_dwords) * sizeof(uint32_t));
  uint32_t isgn_name_ptr_texcoord = name_ptr;
  if (key.interpolator_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "TEXCOORD");
  }
  uint32_t isgn_name_ptr_sv_position = name_ptr;
  name_ptr += dxbc::AppendAlignedString(shader_out, "SV_Position");
  uint32_t isgn_name_ptr_sv_clip_distance = name_ptr;
  if (input_clip_distance_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "SV_ClipDistance");
  }
  uint32_t isgn_name_ptr_sv_cull_distance = name_ptr;
  if (input_cull_distance_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "SV_CullDistance");
  }
  uint32_t isgn_name_ptr_xepsize = name_ptr;
  if (key.has_point_size) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "XEPSIZE");
  }

  uint32_t input_register_interpolators = UINT32_MAX;
  uint32_t input_register_position;
  uint32_t input_register_clip_and_cull_distances = UINT32_MAX;
  uint32_t input_register_point_size = UINT32_MAX;
  {
    auto& isgn_header =
        *reinterpret_cast<dxbc::Signature*>(shader_out.data() + isgn_position_dwords);
    isgn_header.parameter_count = isgn_parameter_count;
    isgn_header.parameter_info_ptr = sizeof(dxbc::Signature);

    auto isgn_parameters = reinterpret_cast<dxbc::SignatureParameter*>(
        shader_out.data() + isgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));
    uint32_t isgn_parameter_index = 0;
    uint32_t input_register_index = 0;

    if (key.interpolator_count) {
      input_register_interpolators = input_register_index;
      for (uint32_t i = 0; i < key.interpolator_count; ++i) {
        assert_true(isgn_parameter_index < isgn_parameter_count);
        dxbc::SignatureParameter& isgn_interpolator = isgn_parameters[isgn_parameter_index++];
        isgn_interpolator.semantic_name_ptr = isgn_name_ptr_texcoord;
        isgn_interpolator.semantic_index = i;
        isgn_interpolator.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        isgn_interpolator.register_index = input_register_index++;
        isgn_interpolator.mask = 0b1111;
        isgn_interpolator.always_reads_mask = 0b1111;
      }
    }

    input_register_position = input_register_index;
    assert_true(isgn_parameter_index < isgn_parameter_count);
    dxbc::SignatureParameter& isgn_sv_position = isgn_parameters[isgn_parameter_index++];
    isgn_sv_position.semantic_name_ptr = isgn_name_ptr_sv_position;
    isgn_sv_position.system_value = dxbc::Name::kPosition;
    isgn_sv_position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
    isgn_sv_position.register_index = input_register_index++;
    isgn_sv_position.mask = 0b1111;
    isgn_sv_position.always_reads_mask = 0b1111;

    if (input_clip_and_cull_distance_count) {
      input_register_clip_and_cull_distances = input_register_index;
      uint32_t isgn_cull_distance_semantic_index = 0;
      for (uint32_t i = 0; i < input_clip_and_cull_distance_count; i += 4) {
        if (i < input_clip_distance_count) {
          dxbc::SignatureParameter& isgn_sv_clip_distance = isgn_parameters[isgn_parameter_index++];
          isgn_sv_clip_distance.semantic_name_ptr = isgn_name_ptr_sv_clip_distance;
          isgn_sv_clip_distance.semantic_index = i / 4;
          isgn_sv_clip_distance.system_value = dxbc::Name::kClipDistance;
          isgn_sv_clip_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          isgn_sv_clip_distance.register_index = input_register_index;
          uint8_t isgn_sv_clip_distance_mask =
              (UINT8_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1;
          isgn_sv_clip_distance.mask = isgn_sv_clip_distance_mask;
          isgn_sv_clip_distance.always_reads_mask = isgn_sv_clip_distance_mask;
        }
        if (input_cull_distance_count && i + 4 > input_clip_distance_count) {
          dxbc::SignatureParameter& isgn_sv_cull_distance = isgn_parameters[isgn_parameter_index++];
          isgn_sv_cull_distance.semantic_name_ptr = isgn_name_ptr_sv_cull_distance;
          isgn_sv_cull_distance.semantic_index = isgn_cull_distance_semantic_index++;
          isgn_sv_cull_distance.system_value = dxbc::Name::kCullDistance;
          isgn_sv_cull_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          isgn_sv_cull_distance.register_index = input_register_index;
          uint8_t isgn_sv_cull_distance_mask =
              (UINT8_C(1) << std::min(input_clip_and_cull_distance_count - i, UINT32_C(4))) - 1;
          if (i < input_clip_distance_count) {
            isgn_sv_cull_distance_mask &= ~((UINT8_C(1) << (input_clip_distance_count - i)) - 1);
          }
          isgn_sv_cull_distance.mask = isgn_sv_cull_distance_mask;
          isgn_sv_cull_distance.always_reads_mask = isgn_sv_cull_distance_mask;
        }
        ++input_register_index;
      }
    }

    if (key.has_point_size) {
      input_register_point_size = input_register_index;
      assert_true(isgn_parameter_index < isgn_parameter_count);
      dxbc::SignatureParameter& isgn_point_size = isgn_parameters[isgn_parameter_index++];
      isgn_point_size.semantic_name_ptr = isgn_name_ptr_xepsize;
      isgn_point_size.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      isgn_point_size.register_index = input_register_index++;
      isgn_point_size.mask = 0b0001;
      isgn_point_size.always_reads_mask =
          key.type == PipelineGeometryShader::kPointList ? 0b0001 : 0;
    }

    assert_true(isgn_parameter_index == isgn_parameter_count);
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kInputSignature;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  uint32_t osgn_parameter_count = key.interpolator_count + key.has_point_coordinates + 1 +
                                  ((input_clip_distance_count + 3) / 4);

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t osgn_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(osgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t) +
                    sizeof(dxbc::SignatureParameterForGS) / sizeof(uint32_t) *
                        osgn_parameter_count);

  name_ptr = uint32_t((shader_out.size() - osgn_position_dwords) * sizeof(uint32_t));
  uint32_t osgn_name_ptr_texcoord = name_ptr;
  if (key.interpolator_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "TEXCOORD");
  }
  uint32_t osgn_name_ptr_xespritetexcoord = name_ptr;
  if (key.has_point_coordinates) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "XESPRITETEXCOORD");
  }
  uint32_t osgn_name_ptr_sv_position = name_ptr;
  name_ptr += dxbc::AppendAlignedString(shader_out, "SV_Position");
  uint32_t osgn_name_ptr_sv_clip_distance = name_ptr;
  if (input_clip_distance_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "SV_ClipDistance");
  }

  uint32_t output_register_interpolators = UINT32_MAX;
  uint32_t output_register_point_coordinates = UINT32_MAX;
  uint32_t output_register_position;
  uint32_t output_register_clip_distances = UINT32_MAX;
  {
    auto& osgn_header =
        *reinterpret_cast<dxbc::Signature*>(shader_out.data() + osgn_position_dwords);
    osgn_header.parameter_count = osgn_parameter_count;
    osgn_header.parameter_info_ptr = sizeof(dxbc::Signature);

    auto osgn_parameters = reinterpret_cast<dxbc::SignatureParameterForGS*>(
        shader_out.data() + osgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));
    uint32_t osgn_parameter_index = 0;
    uint32_t output_register_index = 0;

    if (key.interpolator_count) {
      output_register_interpolators = output_register_index;
      for (uint32_t i = 0; i < key.interpolator_count; ++i) {
        assert_true(osgn_parameter_index < osgn_parameter_count);
        dxbc::SignatureParameterForGS& osgn_interpolator = osgn_parameters[osgn_parameter_index++];
        osgn_interpolator.semantic_name_ptr = osgn_name_ptr_texcoord;
        osgn_interpolator.semantic_index = i;
        osgn_interpolator.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        osgn_interpolator.register_index = output_register_index++;
        osgn_interpolator.mask = 0b1111;
      }
    }

    if (key.has_point_coordinates) {
      output_register_point_coordinates = output_register_index;
      assert_true(osgn_parameter_index < osgn_parameter_count);
      dxbc::SignatureParameterForGS& osgn_point_coordinates =
          osgn_parameters[osgn_parameter_index++];
      osgn_point_coordinates.semantic_name_ptr = osgn_name_ptr_xespritetexcoord;
      osgn_point_coordinates.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      osgn_point_coordinates.register_index = output_register_index++;
      osgn_point_coordinates.mask = 0b0011;
      osgn_point_coordinates.never_writes_mask = 0b1100;
    }

    output_register_position = output_register_index;
    assert_true(osgn_parameter_index < osgn_parameter_count);
    dxbc::SignatureParameterForGS& osgn_sv_position = osgn_parameters[osgn_parameter_index++];
    osgn_sv_position.semantic_name_ptr = osgn_name_ptr_sv_position;
    osgn_sv_position.system_value = dxbc::Name::kPosition;
    osgn_sv_position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
    osgn_sv_position.register_index = output_register_index++;
    osgn_sv_position.mask = 0b1111;

    if (input_clip_distance_count) {
      output_register_clip_distances = output_register_index;
      for (uint32_t i = 0; i < input_clip_distance_count; i += 4) {
        dxbc::SignatureParameterForGS& osgn_sv_clip_distance =
            osgn_parameters[osgn_parameter_index++];
        osgn_sv_clip_distance.semantic_name_ptr = osgn_name_ptr_sv_clip_distance;
        osgn_sv_clip_distance.semantic_index = i / 4;
        osgn_sv_clip_distance.system_value = dxbc::Name::kClipDistance;
        osgn_sv_clip_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        osgn_sv_clip_distance.register_index = output_register_index++;
        uint8_t osgn_sv_clip_distance_mask =
            (UINT8_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1;
        osgn_sv_clip_distance.mask = osgn_sv_clip_distance_mask;
        osgn_sv_clip_distance.never_writes_mask = osgn_sv_clip_distance_mask ^ 0b1111;
      }
    }

    assert_true(osgn_parameter_index == osgn_parameter_count);
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kOutputSignatureForGS;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t shex_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(shex_position_dwords);

  shader_out.push_back(dxbc::VersionToken(dxbc::ProgramType::kGeometryShader, 5, 1));

  shader_out.push_back(0);

  dxbc::Statistics stat;
  std::memset(&stat, 0, sizeof(dxbc::Statistics));
  dxbc::Assembler a(shader_out, stat);

  a.OpDclGlobalFlags(dxbc::kGlobalFlagAllResourcesBound);

  if (system_cbuffer_size_vector_aligned_bytes) {
    a.OpDclConstantBuffer(
        dxbc::Src::CB(dxbc::Src::Dcl, 0,
                      uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                      uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants)),
        system_cbuffer_size_vector_aligned_bytes / (sizeof(uint32_t) * 4));
  }

  dxbc::Primitive input_primitive = dxbc::Primitive::kUndefined;
  uint32_t input_primitive_vertex_count = 0;
  dxbc::PrimitiveTopology output_primitive_topology = dxbc::PrimitiveTopology::kUndefined;
  uint32_t max_output_vertex_count = 0;
  switch (key.type) {
    case PipelineGeometryShader::kPointList:

      input_primitive = dxbc::Primitive::kPoint;
      input_primitive_vertex_count = 1;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    case PipelineGeometryShader::kRectangleList:

      input_primitive = dxbc::Primitive::kTriangle;
      input_primitive_vertex_count = 3;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    case PipelineGeometryShader::kQuadList:

      input_primitive = dxbc::Primitive::kLineWithAdjacency;
      input_primitive_vertex_count = 4;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    case PipelineGeometryShader::kLineList:

      input_primitive = dxbc::Primitive::kLine;
      input_primitive_vertex_count = 2;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    default:
      assert_unhandled_case(key.type);
  }

  assert_false(key.interpolator_count && input_register_interpolators == UINT32_MAX);
  for (uint32_t i = 0; i < key.interpolator_count; ++i) {
    a.OpDclInput(dxbc::Dest::V2D(input_primitive_vertex_count, input_register_interpolators + i));
  }
  a.OpDclInputSIV(dxbc::Dest::V2D(input_primitive_vertex_count, input_register_position),
                  dxbc::Name::kPosition);

  assert_false(input_clip_and_cull_distance_count &&
               input_register_clip_and_cull_distances == UINT32_MAX);
  for (uint32_t i = 0; i < input_clip_and_cull_distance_count; i += 4) {
    if (i < input_clip_distance_count) {
      a.OpDclInput(dxbc::Dest::V2D(
          input_primitive_vertex_count, input_register_clip_and_cull_distances + (i >> 2),
          (UINT32_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1));
    }
    if (input_cull_distance_count && i + 4 > input_clip_distance_count) {
      uint32_t cull_distance_mask =
          (UINT32_C(1) << std::min(input_clip_and_cull_distance_count - i, UINT32_C(4))) - 1;
      if (i < input_clip_distance_count) {
        cull_distance_mask &= ~((UINT32_C(1) << (input_clip_distance_count - i)) - 1);
      }
      a.OpDclInput(dxbc::Dest::V2D(input_primitive_vertex_count,
                                   input_register_clip_and_cull_distances + (i >> 2),
                                   cull_distance_mask));
    }
  }
  if (key.has_point_size && key.type == PipelineGeometryShader::kPointList) {
    assert_true(input_register_point_size != UINT32_MAX);
    a.OpDclInput(dxbc::Dest::V2D(input_primitive_vertex_count, input_register_point_size, 0b0001));
  }

  size_t dcl_temps_count_position_dwords = a.OpDclTemps(1);

  a.OpDclInputPrimitive(input_primitive);
  dxbc::Dest stream(dxbc::Dest::M(0));
  a.OpDclStream(stream);
  a.OpDclOutputTopology(output_primitive_topology);

  assert_false(key.interpolator_count && output_register_interpolators == UINT32_MAX);
  for (uint32_t i = 0; i < key.interpolator_count; ++i) {
    a.OpDclOutput(dxbc::Dest::O(output_register_interpolators + i));
  }
  if (key.has_point_coordinates) {
    assert_true(output_register_point_coordinates != UINT32_MAX);
    a.OpDclOutput(dxbc::Dest::O(output_register_point_coordinates, 0b0011));
  }
  a.OpDclOutputSIV(dxbc::Dest::O(output_register_position), dxbc::Name::kPosition);
  assert_false(input_clip_distance_count && output_register_clip_distances == UINT32_MAX);
  for (uint32_t i = 0; i < input_clip_distance_count; i += 4) {
    a.OpDclOutputSIV(
        dxbc::Dest::O(output_register_clip_distances + (i >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1),
        dxbc::Name::kClipDistance);
  }

  a.OpDclMaxOutputVertexCount(max_output_vertex_count);

  for (uint32_t i = 0; i < input_primitive_vertex_count; ++i) {
    a.OpNE(dxbc::Dest::R(0), dxbc::Src::V2D(i, input_register_position),
           dxbc::Src::V2D(i, input_register_position));
    a.OpOr(dxbc::Dest::R(0, 0b0011), dxbc::Src::R(0, 0b0100), dxbc::Src::R(0, 0b1110));
    a.OpOr(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
           dxbc::Src::R(0, dxbc::Src::kYYYY));
    a.OpRetC(true, dxbc::Src::R(0, dxbc::Src::kXXXX));
  }

  if (input_cull_distance_count) {
    uint32_t cull_distance_start =
        point_recalculate_cull_distances ? point_user_cull_distance_count : 0;
    for (uint32_t i = cull_distance_start; i < input_cull_distance_count; ++i) {
      uint32_t cull_distance_register =
          input_register_clip_and_cull_distances + ((input_clip_distance_count + i) >> 2);
      uint32_t cull_distance_component = (input_clip_distance_count + i) & 3;
      a.OpLT(dxbc::Dest::R(0, 0b0001),
             dxbc::Src::V2D(0, cull_distance_register).Select(cull_distance_component),
             dxbc::Src::LF(0.0f));
      for (uint32_t j = 1; j < input_primitive_vertex_count; ++j) {
        a.OpLT(dxbc::Dest::R(0, 0b0010),
               dxbc::Src::V2D(j, cull_distance_register).Select(cull_distance_component),
               dxbc::Src::LF(0.0f));
        a.OpAnd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
                dxbc::Src::R(0, dxbc::Src::kYYYY));
      }
      a.OpRetC(true, dxbc::Src::R(0, dxbc::Src::kXXXX));
    }
  }

  switch (key.type) {
    case PipelineGeometryShader::kPointList: {
      dxbc::Src point_size_src(dxbc::Src::CB(
          0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
          offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter) >> 4,
          ((offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter[0]) >> 2) & 3) |
              (((offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter[1]) >> 2) &
                3)
               << 2)));
      if (key.has_point_size) {
        a.OpGE(dxbc::Dest::R(0, 0b0001),
               dxbc::Src::V2D(0, input_register_point_size, dxbc::Src::kXXXX), dxbc::Src::LF(0.0f));
        a.OpMovC(dxbc::Dest::R(0, 0b0011), dxbc::Src::R(0, dxbc::Src::kXXXX),
                 dxbc::Src::V2D(0, input_register_point_size, dxbc::Src::kXXXX), point_size_src);
        point_size_src = dxbc::Src::R(0, 0b0100);
      }

      for (uint32_t i = 0; i < 2; ++i) {
        a.OpLT(dxbc::Dest::R(0, 0b0100), dxbc::Src::LF(0.0f), point_size_src.SelectFromSwizzled(i));
        a.OpRetC(false, dxbc::Src::R(0, dxbc::Src::kZZZZ));
      }

      a.OpMul(dxbc::Dest::R(0, 0b0011), point_size_src,
              dxbc::Src::CB(0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                            offsetof(DxbcShaderTranslator::SystemConstants,
                                     point_screen_diameter_to_ndc_radius) >>
                                4,
                            ((offsetof(DxbcShaderTranslator::SystemConstants,
                                       point_screen_diameter_to_ndc_radius[0]) >>
                              2) &
                             3) |
                                (((offsetof(DxbcShaderTranslator::SystemConstants,
                                            point_screen_diameter_to_ndc_radius[1]) >>
                                   2) &
                                  3)
                                 << 2)));
      point_size_src = dxbc::Src::R(0, 0b0100);
      a.OpMul(dxbc::Dest::R(0, 0b0011), point_size_src,
              dxbc::Src::V2D(0, input_register_position, dxbc::Src::kWWWW));
      dxbc::Src point_radius_x_src(point_size_src.SelectFromSwizzled(0));
      dxbc::Src point_radius_y_src(point_size_src.SelectFromSwizzled(1));

      if (point_recalculate_cull_distances) {
        stat.temp_register_count = std::max(UINT32_C(4), stat.temp_register_count);
        dxbc::Src ndc_scale_xy(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4,
            ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[0]) >> 2) & 3) |
                (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[1]) >> 2) & 3) << 2)));
        dxbc::Src ndc_scale_z(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4, dxbc::Src::kZZZZ));
        dxbc::Src ndc_offset_xy(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4,
            ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[0]) >> 2) & 3) |
                (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[1]) >> 2) & 3)
                 << 2)));
        dxbc::Src ndc_offset_z(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4, dxbc::Src::kZZZZ));
        for (uint32_t j = 0; j < point_user_cull_distance_count; ++j) {
          for (uint32_t i = 0; i < 4; ++i) {
            a.OpAdd(dxbc::Dest::R(2, 0b0001),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kXXXX),
                    (i & 1) ? point_radius_x_src : -point_radius_x_src);
            a.OpAdd(dxbc::Dest::R(2, 0b0010),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kYYYY),
                    (i >> 1) ? -point_radius_y_src : point_radius_y_src);
            a.OpMov(dxbc::Dest::R(2, 0b0100),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kZZZZ));
            a.OpMov(dxbc::Dest::R(2, 0b1000),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kWWWW));
            a.OpMAd(dxbc::Dest::R(2, 0b0011), -ndc_offset_xy, dxbc::Src::R(2, dxbc::Src::kWWWW),
                    dxbc::Src::R(2, 0b0011));
            a.OpDiv(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2, 0b0011), ndc_scale_xy);
            a.OpMAd(dxbc::Dest::R(2, 0b0100), -ndc_offset_z, dxbc::Src::R(2, dxbc::Src::kWWWW),
                    dxbc::Src::R(2, dxbc::Src::kZZZZ));
            a.OpDiv(dxbc::Dest::R(2, 0b0100), dxbc::Src::R(2, dxbc::Src::kZZZZ), ndc_scale_z);
            a.OpDP4(
                dxbc::Dest::R(2, 0b0001), dxbc::Src::R(2),
                dxbc::Src::CB(0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                              (offsetof(DxbcShaderTranslator::SystemConstants, user_clip_planes) +
                               sizeof(float) * 4 * j) >>
                                  4,
                              dxbc::Src::kXYZW));
            a.OpLT(dxbc::Dest::R(2, 0b0001), dxbc::Src::R(2, dxbc::Src::kXXXX),
                   dxbc::Src::LF(0.0f));
            if (i == 0) {
              a.OpMov(dxbc::Dest::R(3, 0b0001), dxbc::Src::R(2, dxbc::Src::kXXXX));
            } else {
              a.OpAnd(dxbc::Dest::R(3, 0b0001), dxbc::Src::R(3, dxbc::Src::kXXXX),
                      dxbc::Src::R(2, dxbc::Src::kXXXX));
            }
          }
          a.OpRetC(true, dxbc::Src::R(3, dxbc::Src::kXXXX));
        }
      }

      for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(0, input_register_interpolators + j));
        }

        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011),
                  dxbc::Src::LF(float(i & 1), float(i >> 1), 0.0f, 0.0f));
        }

        a.OpAdd(dxbc::Dest::R(0, 0b0100),
                dxbc::Src::V2D(0, input_register_position, dxbc::Src::kXXXX),
                (i & 1) ? point_radius_x_src : -point_radius_x_src);
        a.OpAdd(dxbc::Dest::R(0, 0b1000),
                dxbc::Src::V2D(0, input_register_position, dxbc::Src::kYYYY),
                (i >> 1) ? -point_radius_y_src : point_radius_y_src);
        a.OpMov(dxbc::Dest::O(output_register_position, 0b0011), dxbc::Src::R(0, 0b1110));
        a.OpMov(dxbc::Dest::O(output_register_position, 0b1100),
                dxbc::Src::V2D(0, input_register_position));
        if (point_recalculate_clip_distances) {
          dxbc::Src ndc_scale_xy(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4,
              ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[0]) >> 2) & 3) |
                  (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[1]) >> 2) & 3)
                   << 2)));
          dxbc::Src ndc_scale_z(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4, dxbc::Src::kZZZZ));
          dxbc::Src ndc_offset_xy(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4,
              ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[0]) >> 2) & 3) |
                  (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[1]) >> 2) & 3)
                   << 2)));
          dxbc::Src ndc_offset_z(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4, dxbc::Src::kZZZZ));
          a.OpMov(dxbc::Dest::R(1, 0b0011), dxbc::Src::R(0, 0b1110));
          a.OpMov(dxbc::Dest::R(1, 0b0100),
                  dxbc::Src::V2D(0, input_register_position, dxbc::Src::kZZZZ));
          a.OpMov(dxbc::Dest::R(1, 0b1000),
                  dxbc::Src::V2D(0, input_register_position, dxbc::Src::kWWWW));
          a.OpMAd(dxbc::Dest::R(1, 0b0011), -ndc_offset_xy, dxbc::Src::R(1, dxbc::Src::kWWWW),
                  dxbc::Src::R(1, 0b0100));
          a.OpDiv(dxbc::Dest::R(1, 0b0011), dxbc::Src::R(1, 0b0100), ndc_scale_xy);
          a.OpMAd(dxbc::Dest::R(1, 0b0100), -ndc_offset_z, dxbc::Src::R(1, dxbc::Src::kWWWW),
                  dxbc::Src::R(1, dxbc::Src::kZZZZ));
          a.OpDiv(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(1, dxbc::Src::kZZZZ), ndc_scale_z);
          for (uint32_t j = 0; j < input_clip_distance_count; ++j) {
            a.OpDP4(
                dxbc::Dest::O(output_register_clip_distances + (j >> 2), UINT32_C(1) << (j & 3)),
                dxbc::Src::R(1),
                dxbc::Src::CB(0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                              (offsetof(DxbcShaderTranslator::SystemConstants, user_clip_planes) +
                               sizeof(float) * 4 * j) >>
                                  4,
                              dxbc::Src::kXYZW));
          }
        } else {
          for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
            a.OpMov(dxbc::Dest::O(
                        output_register_clip_distances + (j >> 2),
                        (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                    dxbc::Src::V2D(0, input_register_clip_and_cull_distances + (j >> 2)));
          }
        }
        a.OpEmitStream(stream);
      }
      a.OpCutStream(stream);
    } break;

    case PipelineGeometryShader::kRectangleList: {
      a.OpAdd(dxbc::Dest::R(0, 0b0011), dxbc::Src::V2D(2, input_register_position, 0b0100),
              -dxbc::Src::V2D(1, input_register_position, 0b0100));
      a.OpDP2(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, 0b0100), dxbc::Src::R(0, 0b0100));

      a.OpAdd(dxbc::Dest::R(0, 0b0110), dxbc::Src::V2D(0, input_register_position, 0b0100 << 2),
              -dxbc::Src::V2D(2, input_register_position, 0b0100 << 2));
      a.OpDP2(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, 0b1001), dxbc::Src::R(0, 0b1001));

      a.OpAdd(dxbc::Dest::R(0, 0b1100), dxbc::Src::V2D(1, input_register_position, 0b0100 << 4),
              -dxbc::Src::V2D(0, input_register_position, 0b0100 << 4));
      a.OpDP2(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, 0b1110), dxbc::Src::R(0, 0b1110));

      a.OpLT(dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kYYYY),
             dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpLT(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kZZZZ),
             dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpAnd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kWWWW),
              dxbc::Src::R(0, dxbc::Src::kXXXX));
      a.OpIf(true, dxbc::Src::R(0, dxbc::Src::kXXXX));
      { a.OpMov(dxbc::Dest::R(0, 0b0111), dxbc::Src::LU(0, 1, 2, 0)); }
      a.OpElse();
      {
        a.OpLT(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kZZZZ),
               dxbc::Src::R(0, dxbc::Src::kYYYY));

        a.OpMovC(dxbc::Dest::R(0, 0b0111), dxbc::Src::R(0, dxbc::Src::kXXXX),
                 dxbc::Src::LU(1, 2, 0, 0), dxbc::Src::LU(2, 0, 1, 0));
      }
      a.OpEndIf();

      for (uint32_t i = 0; i < 3; ++i) {
        dxbc::Index input_vertex_index(0, i);
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(input_vertex_index, input_register_interpolators + j));
        }
        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
        }
        a.OpMov(dxbc::Dest::O(output_register_position),
                dxbc::Src::V2D(input_vertex_index, input_register_position));
        for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
          a.OpMov(dxbc::Dest::O(
                      output_register_clip_distances + (j >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                  dxbc::Src::V2D(input_vertex_index,
                                 input_register_clip_and_cull_distances + (j >> 2)));
        }
        a.OpEmitStream(stream);
      }

      stat.temp_register_count = std::max(UINT32_C(2), stat.temp_register_count);
      for (uint32_t j = 0; j < key.interpolator_count; ++j) {
        uint32_t input_register_interpolator = input_register_interpolators + j;
        a.OpAdd(dxbc::Dest::R(1), -dxbc::Src::V2D(dxbc::Index(0, 0), input_register_interpolator),
                dxbc::Src::V2D(dxbc::Index(0, 1), input_register_interpolator));
        a.OpAdd(dxbc::Dest::R(1), dxbc::Src::R(1),
                dxbc::Src::V2D(dxbc::Index(0, 2), input_register_interpolator));
        a.OpMov(dxbc::Dest::O(output_register_interpolators + j), dxbc::Src::R(1));
      }
      if (key.has_point_coordinates) {
        a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
      }
      a.OpAdd(dxbc::Dest::R(1), -dxbc::Src::V2D(dxbc::Index(0, 0), input_register_position),
              dxbc::Src::V2D(dxbc::Index(0, 1), input_register_position));
      a.OpAdd(dxbc::Dest::R(1), dxbc::Src::R(1),
              dxbc::Src::V2D(dxbc::Index(0, 2), input_register_position));
      a.OpMov(dxbc::Dest::O(output_register_position), dxbc::Src::R(1));
      for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
        uint32_t clip_distance_mask =
            (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1;
        uint32_t input_register_clip_distance = input_register_clip_and_cull_distances + (j >> 2);
        a.OpAdd(dxbc::Dest::R(1, clip_distance_mask),
                -dxbc::Src::V2D(dxbc::Index(0, 0), input_register_clip_distance),
                dxbc::Src::V2D(dxbc::Index(0, 1), input_register_clip_distance));
        a.OpAdd(dxbc::Dest::R(1, clip_distance_mask), dxbc::Src::R(1),
                dxbc::Src::V2D(dxbc::Index(0, 2), input_register_clip_distance));
        a.OpMov(dxbc::Dest::O(output_register_clip_distances + (j >> 2), clip_distance_mask),
                dxbc::Src::R(1));
      }
      a.OpEmitStream(stream);
      a.OpCutStream(stream);
    } break;

    case PipelineGeometryShader::kQuadList: {
      for (uint32_t i = 0; i < 4; ++i) {
        uint32_t input_vertex_index = i ^ (i >> 1);
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(input_vertex_index, input_register_interpolators + j));
        }
        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
        }
        a.OpMov(dxbc::Dest::O(output_register_position),
                dxbc::Src::V2D(input_vertex_index, input_register_position));
        for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
          a.OpMov(dxbc::Dest::O(
                      output_register_clip_distances + (j >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                  dxbc::Src::V2D(input_vertex_index,
                                 input_register_clip_and_cull_distances + (j >> 2)));
        }
        a.OpEmitStream(stream);
      }
      a.OpCutStream(stream);
    } break;

    case PipelineGeometryShader::kLineList: {
      stat.temp_register_count = std::max(UINT32_C(3), stat.temp_register_count);

      dxbc::Src half_pixel_ndc(dxbc::Src::CB(
          0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
          offsetof(DxbcShaderTranslator::SystemConstants, point_screen_diameter_to_ndc_radius) >> 4,
          ((offsetof(DxbcShaderTranslator::SystemConstants,
                     point_screen_diameter_to_ndc_radius[0]) >>
            2) &
           3) |
              (((offsetof(DxbcShaderTranslator::SystemConstants,
                          point_screen_diameter_to_ndc_radius[1]) >>
                 2) &
                3)
               << 2)));

      for (uint32_t i = 0; i < 2; ++i) {
        a.OpDiv(dxbc::Dest::R(1 + i, 0b0011), dxbc::Src::V2D(i, input_register_position),
                dxbc::Src::V2D(i, input_register_position, dxbc::Src::kWWWW));
        a.OpDiv(dxbc::Dest::R(1 + i, 0b0011), dxbc::Src::R(1 + i), half_pixel_ndc);
      }

      a.OpAdd(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2), -dxbc::Src::R(1));

      a.OpDP2(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(2), dxbc::Src::R(2));
      a.OpLT(dxbc::Dest::R(1, 0b1000), dxbc::Src::LF(0.0f), dxbc::Src::R(1, dxbc::Src::kZZZZ));
      a.OpRetC(false, dxbc::Src::R(1, dxbc::Src::kWWWW));
      a.OpRSq(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(1, dxbc::Src::kZZZZ));

      a.OpMul(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2).Swizzle(0b11100001),
              dxbc::Src::R(1, dxbc::Src::kZZZZ));
      a.OpMul(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2), half_pixel_ndc);
      a.OpMov(dxbc::Dest::R(2, 0b0001), -dxbc::Src::R(2, dxbc::Src::kXXXX));

      for (uint32_t i = 0; i < 4; ++i) {
        uint32_t vertex = i >> 1;
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(vertex, input_register_interpolators + j));
        }
        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
        }

        a.OpMAd(dxbc::Dest::R(0, 0b0011), (i & 1) ? dxbc::Src::R(2) : -dxbc::Src::R(2),
                dxbc::Src::V2D(vertex, input_register_position, dxbc::Src::kWWWW),
                dxbc::Src::V2D(vertex, input_register_position));
        a.OpMov(dxbc::Dest::O(output_register_position, 0b0011), dxbc::Src::R(0));
        a.OpMov(dxbc::Dest::O(output_register_position, 0b1100),
                dxbc::Src::V2D(vertex, input_register_position));
        for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
          a.OpMov(dxbc::Dest::O(
                      output_register_clip_distances + (j >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                  dxbc::Src::V2D(vertex, input_register_clip_and_cull_distances + (j >> 2)));
        }
        a.OpEmitStream(stream);
      }
      a.OpCutStream(stream);
    } break;

    default:
      assert_unhandled_case(key.type);
  }

  a.OpRet();

  shader_out[dcl_temps_count_position_dwords] = stat.temp_register_count;

  shader_out[shex_position_dwords + 1] = uint32_t(shader_out.size()) - shex_position_dwords;

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kShaderEx;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t stat_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(stat_position_dwords + sizeof(dxbc::Statistics) / sizeof(uint32_t));
  std::memcpy(shader_out.data() + stat_position_dwords, &stat, sizeof(dxbc::Statistics));

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kStatistics;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  uint32_t shader_size_bytes = uint32_t(shader_out.size() * sizeof(uint32_t));
  {
    auto& container_header = *reinterpret_cast<dxbc::ContainerHeader*>(shader_out.data());
    container_header.InitializeIdentification();
    container_header.size_bytes = shader_size_bytes;
    container_header.blob_count = kBlobCount;
    CalculateDXBCChecksum(reinterpret_cast<unsigned char*>(shader_out.data()),
                          static_cast<unsigned int>(shader_size_bytes),
                          reinterpret_cast<unsigned int*>(&container_header.hash));
  }
}

const std::vector<uint32_t>& PipelineCache::GetGeometryShader(GeometryShaderKey key) {
  auto it = geometry_shaders_.find(key);
  if (it != geometry_shaders_.end()) {
    return it->second;
  }
  std::vector<uint32_t> shader;
  CreateDxbcGeometryShader(key, shader);
  return geometry_shaders_.emplace(key, std::move(shader)).first->second;
}

}
