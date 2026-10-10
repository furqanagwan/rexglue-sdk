/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2018 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include "thirdparty/dxbc/DXBCChecksum.h"

#include <algorithm>
#include <atomic>
#include <cstring>
#include <memory>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/dxbc.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>
#include <rex/ui/graphics_provider.h>

REXCVAR_DEFINE_BOOL(dxbc_switch, true, "GPU/Shader", "Use switch statements in DXBC");

REXCVAR_DEFINE_BOOL(dxbc_source_map, false, "GPU/Shader", "Generate source maps for DXBC");

namespace rex::graphics {
using namespace ucode;

DxbcShaderTranslator::DxbcShaderTranslator(ui::GraphicsProvider::GpuVendorID vendor_id,
                                           bool bindless_resources_used, bool edram_rov_used,
                                           bool gamma_render_target_as_unorm8,
                                           bool msaa_2x_supported, uint32_t draw_resolution_scale_x,
                                           uint32_t draw_resolution_scale_y,
                                           bool force_emit_source_map)
    : a_(shader_code_, statistics_),
      ao_(shader_object_, statistics_),
      vendor_id_(vendor_id),
      bindless_resources_used_(bindless_resources_used),
      edram_rov_used_(edram_rov_used),
      zpd_full_counters_(REXCVAR_GET(occlusion_query_full_counters)),
      gamma_render_target_as_unorm8_(gamma_render_target_as_unorm8),
      msaa_2x_supported_(msaa_2x_supported),
      draw_resolution_scale_x_(draw_resolution_scale_x),
      draw_resolution_scale_y_(draw_resolution_scale_y),
      emit_source_map_(force_emit_source_map || REXCVAR_GET(dxbc_source_map)) {
  assert_not_zero(draw_resolution_scale_x);
  assert_not_zero(draw_resolution_scale_y);

  shader_code_.reserve(8192);
  shader_object_.reserve(16384);
}
DxbcShaderTranslator::~DxbcShaderTranslator() = default;

std::vector<uint8_t> DxbcShaderTranslator::CreateDepthOnlyPixelShader(
    bool zpd_total, Modification::DepthStencilMode depth_stencil_mode, bool viz_survey) {
  is_depth_only_pixel_shader_ = true;
  is_viz_survey_pixel_shader_ = viz_survey;

  Shader shader(xenos::ShaderType::kPixel, 0, nullptr, 0);
  shader.AnalyzeUcode(instruction_disassembly_buffer_);
  Modification modification(0);
  modification.pixel.zpd_total = uint32_t(zpd_total);
  modification.pixel.depth_stencil_mode = depth_stencil_mode;
  Shader::Translation& translation = *shader.GetOrCreateTranslation(modification.value);
  TranslateAnalyzedShader(translation);
  is_depth_only_pixel_shader_ = false;
  is_viz_survey_pixel_shader_ = false;
  return translation.translated_binary();
}

uint64_t DxbcShaderTranslator::GetDefaultVertexShaderModification(
    uint32_t dynamic_addressable_register_count,
    Shader::HostVertexShaderType host_vertex_shader_type) const {
  Modification shader_modification;
  shader_modification.vertex.dynamic_addressable_register_count =
      dynamic_addressable_register_count;
  shader_modification.vertex.host_vertex_shader_type = host_vertex_shader_type;
  shader_modification.vertex.interpolator_mask = (UINT32_C(1) << xenos::kMaxInterpolators) - 1;
  return shader_modification.value;
}

uint64_t DxbcShaderTranslator::GetDefaultPixelShaderModification(
    uint32_t dynamic_addressable_register_count) const {
  Modification shader_modification;
  shader_modification.pixel.dynamic_addressable_register_count = dynamic_addressable_register_count;
  shader_modification.pixel.interpolator_mask = (UINT32_C(1) << xenos::kMaxInterpolators) - 1;
  shader_modification.pixel.depth_stencil_mode = Modification::DepthStencilMode::kNoModifiers;
  return shader_modification.value;
}

void DxbcShaderTranslator::Reset() {
  ShaderTranslator::Reset();

  shader_code_.clear();

  cbuffer_count_ = 0;

  cbuffer_index_system_constants_ = cbuffer_count_++;
  cbuffer_index_float_constants_ = kBindingIndexUnallocated;
  cbuffer_index_bool_loop_constants_ = kBindingIndexUnallocated;
  cbuffer_index_fetch_constants_ = kBindingIndexUnallocated;
  cbuffer_index_descriptor_indices_ = kBindingIndexUnallocated;

  system_constants_used_ = 0;

  out_reg_vs_interpolators_ = UINT32_MAX;
  out_reg_vs_position_ = UINT32_MAX;
  out_reg_vs_clip_cull_distances_ = UINT32_MAX;
  out_reg_vs_point_size_ = UINT32_MAX;
  in_reg_ps_interpolators_ = UINT32_MAX;
  in_reg_ps_point_coordinates_ = UINT32_MAX;
  in_reg_ps_position_ = UINT32_MAX;
  in_reg_ps_front_face_sample_index_ = UINT32_MAX;

  in_domain_location_used_ = 0;
  in_control_point_index_used_ = false;
  in_position_used_ = 0;
  in_front_face_used_ = false;

  system_temp_count_current_ = 0;
  system_temp_count_max_ = 0;

  cf_exec_bool_constant_ = kCfExecBoolConstantNone;
  cf_exec_predicated_ = false;
  cf_instruction_predicate_if_open_ = false;
  cf_exec_predicate_written_ = false;

  srv_count_ = 0;
  srv_index_shared_memory_ = kBindingIndexUnallocated;
  srv_index_bindless_textures_2d_ = kBindingIndexUnallocated;
  srv_index_bindless_textures_3d_ = kBindingIndexUnallocated;
  srv_index_bindless_textures_cube_ = kBindingIndexUnallocated;

  texture_bindings_.clear();
  texture_bindings_for_bindful_srv_indices_.clear();

  uav_count_ = 0;
  uav_index_shared_memory_ = kBindingIndexUnallocated;
  uav_index_edram_ = kBindingIndexUnallocated;
  uav_index_zpd_counter_ = kBindingIndexUnallocated;

  sampler_bindings_.clear();

  std::memset(&shader_feature_info_, 0, sizeof(shader_feature_info_));
  std::memset(&statistics_, 0, sizeof(statistics_));
}

uint32_t DxbcShaderTranslator::GetModificationRegisterCount() const {
  Modification modification = GetDxbcShaderModification();
  return is_vertex_shader() ? modification.vertex.dynamic_addressable_register_count
                            : modification.pixel.dynamic_addressable_register_count;
}

bool DxbcShaderTranslator::UseSwitchForControlFlow() const {
  return REXCVAR_GET(dxbc_switch) && vendor_id_ != ui::GraphicsProvider::GpuVendorID::kIntel;
}

uint32_t DxbcShaderTranslator::PushSystemTemp(uint32_t zero_mask, uint32_t count) {
  uint32_t register_index = system_temp_count_current_;
  if (!is_depth_only_pixel_shader_ && !current_shader().uses_register_dynamic_addressing()) {
    register_index += register_count();
  }
  system_temp_count_current_ += count;
  system_temp_count_max_ = std::max(system_temp_count_max_, system_temp_count_current_);
  zero_mask &= 0b1111;
  if (zero_mask) {
    for (uint32_t i = 0; i < count; ++i) {
      a_.OpMov(dxbc::Dest::R(register_index + i, zero_mask), dxbc::Src::LU(0));
    }
  }
  return register_index;
}

void DxbcShaderTranslator::PopSystemTemp(uint32_t count) {
  assert_true(count <= system_temp_count_current_);
  system_temp_count_current_ -= std::min(count, system_temp_count_current_);
}

void DxbcShaderTranslator::PWLGammaToLinear(dxbc::Assembler& a, uint32_t target_temp,
                                            uint32_t target_temp_component, uint32_t source_temp,
                                            uint32_t source_temp_component,
                                            bool source_pre_saturated, uint32_t temp1,
                                            uint32_t temp1_component, uint32_t temp2,
                                            uint32_t temp2_component) {
  assert_true(temp1 != target_temp || temp1_component != target_temp_component);
  assert_true(temp1 != source_temp || temp1_component != source_temp_component);
  assert_true(temp2 != target_temp || temp2_component != target_temp_component);
  assert_true(temp2 != source_temp || temp2_component != source_temp_component);
  assert_true(temp1 != temp2 || temp1_component != temp2_component);
  dxbc::Dest target_dest(dxbc::Dest::R(target_temp, UINT32_C(1) << target_temp_component));
  dxbc::Src target_src(dxbc::Src::R(target_temp).Select(target_temp_component));
  dxbc::Src source_src(dxbc::Src::R(source_temp).Select(source_temp_component));
  dxbc::Dest temp1_dest(dxbc::Dest::R(temp1, UINT32_C(1) << temp1_component));
  dxbc::Src temp1_src(dxbc::Src::R(temp1).Select(temp1_component));
  dxbc::Dest temp2_dest(dxbc::Dest::R(temp2, UINT32_C(1) << temp2_component));
  dxbc::Src temp2_src(dxbc::Src::R(temp2).Select(temp2_component));

  a.OpGE(temp2_dest, source_src, dxbc::Src::LF(96.0f / 255.0f));
  a.OpIf(true, temp2_src);

  a.OpGE(temp2_dest, source_src, dxbc::Src::LF(192.0f / 255.0f));
  a.OpMovC(temp1_dest, temp2_src, dxbc::Src::LF(8.0f / 1024.0f), dxbc::Src::LF(4.0f / 1024.0f));
  a.OpMovC(temp2_dest, temp2_src, dxbc::Src::LF(-1024.0f), dxbc::Src::LF(-256.0f));
  a.OpElse();

  a.OpGE(temp2_dest, source_src, dxbc::Src::LF(64.0f / 255.0f));
  a.OpMovC(temp1_dest, temp2_src, dxbc::Src::LF(2.0f / 1024.0f), dxbc::Src::LF(1.0f / 1024.0f));
  a.OpMovC(temp2_dest, temp2_src, dxbc::Src::LF(-64.0f), dxbc::Src::LF(0.0f));
  a.OpEndIf();

  if (!source_pre_saturated) {
    a.OpMov(target_dest, source_src, true);
  }

  a.OpMul(target_dest, source_pre_saturated ? source_src : target_src,
          dxbc::Src::LF(255.0f * 1024.0f));
  a.OpMAd(target_dest, target_src, temp1_src, temp2_src);

  a.OpMul(temp1_dest, target_src, temp1_src);
  a.OpRoundZ(temp1_dest, temp1_src);
  a.OpAdd(target_dest, target_src, temp1_src);

  a.OpMul(target_dest, target_src, dxbc::Src::LF(1.0f / 1023.0f));
}

void DxbcShaderTranslator::PreSaturatedLinearToPWLGamma(
    dxbc::Assembler& a, uint32_t target_temp, uint32_t target_temp_component, uint32_t source_temp,
    uint32_t source_temp_component, uint32_t temp_or_target, uint32_t temp_or_target_component,
    uint32_t temp_non_target, uint32_t temp_non_target_component) {
  assert_true(target_temp != source_temp || target_temp_component != source_temp_component ||
              target_temp != temp_or_target || target_temp_component != temp_or_target_component);
  assert_true(temp_or_target != source_temp || temp_or_target_component != source_temp_component);
  assert_true(temp_non_target != target_temp || temp_non_target_component != target_temp_component);
  assert_true(temp_non_target != source_temp || temp_non_target_component != source_temp_component);
  assert_true(temp_or_target != temp_non_target ||
              temp_or_target_component != temp_non_target_component);
  dxbc::Dest target_dest(dxbc::Dest::R(target_temp, UINT32_C(1) << target_temp_component));
  dxbc::Src target_src(dxbc::Src::R(target_temp).Select(target_temp_component));
  dxbc::Src source_src(dxbc::Src::R(source_temp).Select(source_temp_component));
  dxbc::Dest temp_or_target_dest(
      dxbc::Dest::R(temp_or_target, UINT32_C(1) << temp_or_target_component));
  dxbc::Src temp_or_target_src(dxbc::Src::R(temp_or_target).Select(temp_or_target_component));
  dxbc::Dest temp_non_target_dest(
      dxbc::Dest::R(temp_non_target, UINT32_C(1) << temp_non_target_component));
  dxbc::Src temp_non_target_src(dxbc::Src::R(temp_non_target).Select(temp_non_target_component));

  a.OpGE(temp_non_target_dest, source_src, dxbc::Src::LF(128.0f / 1023.0f));
  a.OpIf(true, temp_non_target_src);

  a.OpGE(temp_non_target_dest, source_src, dxbc::Src::LF(512.0f / 1023.0f));
  a.OpMovC(temp_or_target_dest, temp_non_target_src, dxbc::Src::LF(1023.0f / 8.0f),
           dxbc::Src::LF(1023.0f / 4.0f));
  a.OpMovC(temp_non_target_dest, temp_non_target_src, dxbc::Src::LF(128.0f / 255.0f),
           dxbc::Src::LF(64.0f / 255.0f));
  a.OpElse();

  a.OpGE(temp_non_target_dest, source_src, dxbc::Src::LF(64.0f / 1023.0f));
  a.OpMovC(temp_or_target_dest, temp_non_target_src, dxbc::Src::LF(1023.0f / 2.0f),
           dxbc::Src::LF(1023.0f));
  a.OpMovC(temp_non_target_dest, temp_non_target_src, dxbc::Src::LF(32.0f / 255.0f),
           dxbc::Src::LF(0.0f));
  a.OpEndIf();

  a.OpMul(target_dest, source_src, temp_or_target_src);
  a.OpRoundZ(target_dest, target_src);
  a.OpMAd(target_dest, target_src, dxbc::Src::LF(1.0f / 255.0f), temp_non_target_src);
}

void DxbcShaderTranslator::RemapAndConvertVertexIndices(uint32_t dest_temp,
                                                        uint32_t dest_temp_components,
                                                        const dxbc::Src& src) {
  dxbc::Dest dest(dxbc::Dest::R(dest_temp, dest_temp_components));
  dxbc::Src dest_src(dxbc::Src::R(dest_temp));

  a_.OpIAdd(dest, src,
            LoadSystemConstant(SystemConstants::Index::kVertexIndexOffset,
                               offsetof(SystemConstants, vertex_index_offset), dxbc::Src::kXXXX));

  a_.OpAnd(dest, dest_src, dxbc::Src::LU(xenos::kVertexIndexMask));

  a_.OpUMax(dest, dest_src,
            LoadSystemConstant(SystemConstants::Index::kVertexIndexMinMax,
                               offsetof(SystemConstants, vertex_index_min), dxbc::Src::kXXXX));
  a_.OpUMin(dest, dest_src,
            LoadSystemConstant(SystemConstants::Index::kVertexIndexMinMax,
                               offsetof(SystemConstants, vertex_index_max), dxbc::Src::kXXXX));

  a_.OpUToF(dest, dest_src);
}

void DxbcShaderTranslator::StartVertexShader_LoadVertexIndex() {
  if (register_count() < 1) {
    return;
  }

  bool uses_register_dynamic_addressing = current_shader().uses_register_dynamic_addressing();

  uint32_t reg;
  if (uses_register_dynamic_addressing) {
    reg = PushSystemTemp();
  } else {
    reg = 0;
  }

  dxbc::Dest index_dest(dxbc::Dest::R(reg, 0b0001));
  dxbc::Src index_src(dxbc::Src::R(reg, dxbc::Src::kXXXX));

  a_.OpINE(
      index_dest, dxbc::Src::V1D(kInRegisterVSVertexIndex, dxbc::Src::kXXXX),
      LoadSystemConstant(SystemConstants::Index::kLineLoopClosingIndex,
                         offsetof(SystemConstants, line_loop_closing_index), dxbc::Src::kXXXX));

  a_.OpAnd(index_dest, dxbc::Src::V1D(kInRegisterVSVertexIndex, dxbc::Src::kXXXX), index_src);

  {
    dxbc::Src endian_src(LoadSystemConstant(SystemConstants::Index::kVertexIndexEndian,
                                            offsetof(SystemConstants, vertex_index_endian),
                                            dxbc::Src::kXXXX));
    dxbc::Dest swap_temp_dest(dxbc::Dest::R(reg, 0b0010));
    dxbc::Src swap_temp_src(dxbc::Src::R(reg, dxbc::Src::kYYYY));

    a_.OpSwitch(endian_src);
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian::k8in16)));
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian::k8in32)));

    a_.OpAnd(swap_temp_dest, index_src, dxbc::Src::LU(0x00FF00FF));

    a_.OpUShR(index_dest, index_src, dxbc::Src::LU(8));

    a_.OpAnd(index_dest, index_src, dxbc::Src::LU(0x00FF00FF));

    a_.OpUMAd(index_dest, swap_temp_src, dxbc::Src::LU(256), index_src);
    a_.OpBreak();
    a_.OpEndSwitch();

    a_.OpSwitch(endian_src);
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian::k8in32)));
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian::k16in32)));

    a_.OpUShR(swap_temp_dest, index_src, dxbc::Src::LU(16));

    a_.OpBFI(index_dest, dxbc::Src::LU(16), dxbc::Src::LU(16), index_src, swap_temp_src);
    a_.OpBreak();
    a_.OpEndSwitch();

    if (!uses_register_dynamic_addressing) {
      a_.OpMov(swap_temp_dest, dxbc::Src::LF(0.0f));
    }
  }

  RemapAndConvertVertexIndices(index_dest.index_1d_.index_, index_dest.write_mask_, index_src);

  if (uses_register_dynamic_addressing) {
    a_.OpMov(dxbc::Dest::X(0, 0, 0b0001), index_src);
    PopSystemTemp();
  }
}

void DxbcShaderTranslator::StartVertexOrDomainShader() {
  bool uses_register_dynamic_addressing = current_shader().uses_register_dynamic_addressing();

  for (uint32_t i = 0; i < register_count(); ++i) {
    a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, i) : dxbc::Dest::R(i),
             dxbc::Src::LF(0.0f));
  }

  uint32_t interpolator_count = rex::bit_count(GetModificationInterpolatorMask());
  for (uint32_t i = 0; i < interpolator_count; ++i) {
    a_.OpMov(dxbc::Dest::O(out_reg_vs_interpolators_ + i), dxbc::Src::LF(0.0f));
  }

  Shader::HostVertexShaderType host_vertex_shader_type =
      GetDxbcShaderModification().vertex.host_vertex_shader_type;
  switch (host_vertex_shader_type) {
    case Shader::HostVertexShaderType::kVertex:
      StartVertexShader_LoadVertexIndex();
      break;

    case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
      if (register_count() >= 1) {
        in_domain_location_used_ |= 0b0111;
        a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 0, 0b0111)
                                                  : dxbc::Dest::R(0, 0b0111),
                 dxbc::Src::VDomain(0b000110));
        if (register_count() >= 2) {
          dxbc::Dest control_point_index_dest(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 1)
                                                                               : dxbc::Dest::R(1));
          in_control_point_index_used_ = true;
          for (uint32_t i = 0; i < 3; ++i) {
            a_.OpMov(control_point_index_dest.Mask(1 << i),
                     dxbc::Src::VICP(i, kInRegisterDSControlPointIndex, dxbc::Src::kXXXX));
          }
        }
      }
      break;

    case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
      if (register_count() >= 1) {
        in_domain_location_used_ |= 0b0111;
        a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 0, 0b0111)
                                                  : dxbc::Dest::R(0, 0b0111),
                 dxbc::Src::VDomain(0b000110));
        if (register_count() >= 2) {
          in_control_point_index_used_ = true;
          a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 1, 0b0001)
                                                    : dxbc::Dest::R(1, 0b0001),
                   dxbc::Src::VICP(0, kInRegisterDSControlPointIndex, dxbc::Src::kXXXX));

          a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 1, 0b0010)
                                                    : dxbc::Dest::R(1, 0b0010),
                   dxbc::Src::LF(0.0f));
        }
      }
      break;

    case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
      if (register_count() >= 1) {
        in_domain_location_used_ |= 0b0011;
        a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 0, 0b0011)
                                                  : dxbc::Dest::R(0, 0b0011),
                 dxbc::Src::VDomain());

        in_control_point_index_used_ = true;
        a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 0, 0b0100)
                                                  : dxbc::Dest::R(0, 0b0100),
                 dxbc::Src::VICP(0, kInRegisterDSControlPointIndex, dxbc::Src::kXXXX));
        if (register_count() >= 2) {
          dxbc::Dest r1_dest(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 1)
                                                              : dxbc::Dest::R(1));
          for (uint32_t i = 0; i < 3; ++i) {
            a_.OpMov(r1_dest.Mask(1 << i),
                     dxbc::Src::VICP(1 + i, kInRegisterDSControlPointIndex, dxbc::Src::kXXXX));
          }
        }
      }
      break;

    case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
      if (register_count() >= 1) {
        in_domain_location_used_ |= 0b0011;
        a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 0, 0b0110)
                                                  : dxbc::Dest::R(0, 0b0110),
                 dxbc::Src::VDomain(0b010000));

        in_control_point_index_used_ = true;
        a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 0, 0b0001)
                                                  : dxbc::Dest::R(0, 0b0001),
                 dxbc::Src::VICP(0, kInRegisterDSControlPointIndex, dxbc::Src::kXXXX));
        if (register_count() >= 2) {
          a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, 1, 0b0001)
                                                    : dxbc::Dest::R(1, 0b0001),
                   dxbc::Src::LF(0.0f));
        }
      }
      break;

    default:

      assert_unhandled_case(host_vertex_shader_type);
      EmitTranslationError("Unsupported host vertex shader type in StartVertexOrDomainShader");
      break;
  }
}

void DxbcShaderTranslator::StartPixelShader() {
  if (edram_rov_used_) {
    StartPixelShader_LoadROVParameters();

    if (ROV_IsDepthStencilEarly()) {
      ROV_DepthStencilTest();
    } else {
      if (!current_shader().writes_depth()) {
        assert_true(system_temp_depth_stencil_ != UINT32_MAX);
        dxbc::Src in_position_z(dxbc::Src::V1D(in_reg_ps_position_, dxbc::Src::kZZZZ));
        in_position_used_ |= 0b0100;
        a_.OpDerivRTXCoarse(dxbc::Dest::R(system_temp_depth_stencil_, 0b0001), in_position_z);
        a_.OpDerivRTYCoarse(dxbc::Dest::R(system_temp_depth_stencil_, 0b0010), in_position_z);
      }
    }
  }

  if (is_depth_only_pixel_shader_) {
    return;
  }

  bool uses_register_dynamic_addressing = current_shader().uses_register_dynamic_addressing();
  Modification shader_modification = GetDxbcShaderModification();

  uint32_t param_gen_interpolator =
      (shader_modification.pixel.param_gen_enable &&
       shader_modification.pixel.param_gen_interpolator < register_count())
          ? shader_modification.pixel.param_gen_interpolator
          : UINT32_MAX;

  uint32_t interpolator_mask = GetModificationInterpolatorMask();
  for (uint32_t i = 0; i < register_count(); ++i) {
    if (i == param_gen_interpolator) {
      continue;
    }
    a_.OpMov(uses_register_dynamic_addressing ? dxbc::Dest::X(0, i) : dxbc::Dest::R(i),
             (i < xenos::kMaxInterpolators && (interpolator_mask & (UINT32_C(1) << i)))
                 ? dxbc::Src::V1D(in_reg_ps_interpolators_ +
                                  rex::bit_count(interpolator_mask & ((UINT32_C(1) << i) - 1)))
                 : dxbc::Src::LF(0.0f));
  }

  if (param_gen_interpolator != UINT32_MAX) {
    uint32_t param_gen_temp =
        uses_register_dynamic_addressing ? PushSystemTemp() : param_gen_interpolator;

    in_position_used_ |= 0b0011;
    a_.OpRoundNI(dxbc::Dest::R(param_gen_temp, 0b0011), dxbc::Src::V1D(in_reg_ps_position_));
    uint32_t resolution_scaled_axes =
        uint32_t(draw_resolution_scale_x_ > 1) | (uint32_t(draw_resolution_scale_y_ > 1) << 1);
    if (resolution_scaled_axes) {
      a_.OpMul(dxbc::Dest::R(param_gen_temp, resolution_scaled_axes), dxbc::Src::R(param_gen_temp),
               dxbc::Src::LF(1.0f / draw_resolution_scale_x_, 1.0f / draw_resolution_scale_y_, 1.0f,
                             1.0f));
    }
    if (shader_modification.pixel.param_gen_point) {
      a_.OpMov(dxbc::Dest::R(param_gen_temp, 0b0001),
               dxbc::Src::R(param_gen_temp, dxbc::Src::kXXXX).Abs());
      a_.OpMov(dxbc::Dest::R(param_gen_temp, 0b0010),
               -(dxbc::Src::R(param_gen_temp, dxbc::Src::kYYYY).Abs()));

      assert_true(in_reg_ps_point_coordinates_ != UINT32_MAX);
      a_.OpMov(dxbc::Dest::R(param_gen_temp, 0b1100),
               dxbc::Src::V1D(in_reg_ps_point_coordinates_, 0b0100 << 4), true);
    } else {
      a_.OpMov(dxbc::Dest::R(param_gen_temp, 0b0011), dxbc::Src::R(param_gen_temp).Abs());

      a_.OpAnd(dxbc::Dest::R(param_gen_temp, 0b0100), LoadFlagsSystemConstant(),
               dxbc::Src::LU(kSysFlag_PrimitivePolygonal));
      a_.OpIf(true, dxbc::Src::R(param_gen_temp, dxbc::Src::kZZZZ));
      {
        in_front_face_used_ = true;
        a_.OpMovC(dxbc::Dest::R(param_gen_temp, 0b0001),
                  dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kXXXX),
                  dxbc::Src::R(param_gen_temp, dxbc::Src::kXXXX),
                  -dxbc::Src::R(param_gen_temp, dxbc::Src::kXXXX));
      }
      a_.OpEndIf();

      a_.OpUBFE(dxbc::Dest::R(param_gen_temp, 0b0100), dxbc::Src::LU(1),
                dxbc::Src::LU(kSysFlag_PrimitiveLine_Shift), LoadFlagsSystemConstant());
      a_.OpIShL(dxbc::Dest::R(param_gen_temp, 0b0100),
                dxbc::Src::R(param_gen_temp, dxbc::Src::kZZZZ), dxbc::Src::LU(31));
      a_.OpMov(dxbc::Dest::R(param_gen_temp, 0b1000), dxbc::Src::LF(0.0f));
    }

    if (uses_register_dynamic_addressing) {
      a_.OpMov(dxbc::Dest::X(0, param_gen_interpolator), dxbc::Src::R(param_gen_temp));

      PopSystemTemp();
    }
  }

  if (current_shader().memexport_eM_written()) {
    dxbc::Dest memexport_enabled_dest(
        dxbc::Dest::R(system_temp_memexport_enabled_and_eM_written_, 0b0001));
    dxbc::Src memexport_enabled_src(
        dxbc::Src::R(system_temp_memexport_enabled_and_eM_written_, dxbc::Src::kXXXX));
    uint32_t resolution_scaled_axes =
        uint32_t(draw_resolution_scale_x_ > 1) | (uint32_t(draw_resolution_scale_y_ > 1) << 1);
    if (resolution_scaled_axes) {
      uint32_t memexport_condition_temp = PushSystemTemp();

      in_position_used_ |= resolution_scaled_axes;
      a_.OpFToU(dxbc::Dest::R(memexport_condition_temp, resolution_scaled_axes),
                dxbc::Src::V1D(in_reg_ps_position_));
      a_.OpUDiv(dxbc::Dest::Null(), dxbc::Dest::R(memexport_condition_temp, resolution_scaled_axes),
                dxbc::Src::R(memexport_condition_temp),
                dxbc::Src::LU(draw_resolution_scale_x_, draw_resolution_scale_y_, 0, 0));
      a_.OpIEq(dxbc::Dest::R(memexport_condition_temp, resolution_scaled_axes),
               dxbc::Src::R(memexport_condition_temp),
               dxbc::Src::LU(draw_resolution_scale_x_ >> 1, draw_resolution_scale_y_ >> 1, 0, 0));
      for (uint32_t i = 0; i < 2; ++i) {
        if (!(resolution_scaled_axes & (1 << i))) {
          continue;
        }
        a_.OpAnd(memexport_enabled_dest, memexport_enabled_src,
                 dxbc::Src::R(memexport_condition_temp).Select(i));
      }

      PopSystemTemp();
    }

    if (IsSampleRate()) {
      uint32_t memexport_condition_temp = PushSystemTemp();
      a_.OpFirstBitLo(dxbc::Dest::R(memexport_condition_temp, 0b0001), dxbc::Src::VCoverage());
      a_.OpIEq(dxbc::Dest::R(memexport_condition_temp, 0b0001),
               dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kYYYY),
               dxbc::Src::R(memexport_condition_temp, dxbc::Src::kXXXX));
      a_.OpAnd(memexport_enabled_dest, memexport_enabled_src,
               dxbc::Src::R(memexport_condition_temp, dxbc::Src::kXXXX));

      PopSystemTemp();
    }
  }
}

void DxbcShaderTranslator::StartTranslation() {
  Modification shader_modification = GetDxbcShaderModification();
  uint32_t interpolator_register_mask = GetModificationInterpolatorMask();
  uint32_t interpolator_register_count = rex::bit_count(interpolator_register_mask);
  if (is_vertex_shader()) {
    uint32_t out_reg_index = 0;

    if (interpolator_register_count) {
      out_reg_vs_interpolators_ = out_reg_index;
      out_reg_index += interpolator_register_count;
    }

    out_reg_vs_position_ = out_reg_index;
    ++out_reg_index;

    uint32_t clip_and_cull_distance_count = shader_modification.GetVertexClipDistanceCount() +
                                            shader_modification.GetVertexCullDistanceCount();
    if (clip_and_cull_distance_count) {
      out_reg_vs_clip_cull_distances_ = out_reg_index;
      out_reg_index += (clip_and_cull_distance_count + 3) >> 2;
    }

    if (shader_modification.vertex.output_point_size) {
      out_reg_vs_point_size_ = out_reg_index;
      ++out_reg_index;
    }
  } else if (is_pixel_shader()) {
    uint32_t in_reg_index = 0;

    if (interpolator_register_count) {
      in_reg_ps_interpolators_ = in_reg_index;
      in_reg_index += interpolator_register_count;
    }

    if (shader_modification.pixel.param_gen_point) {
      in_reg_ps_point_coordinates_ = in_reg_index;
      ++in_reg_index;
    }

    in_reg_ps_position_ = in_reg_index;
    ++in_reg_index;

    in_reg_ps_front_face_sample_index_ = in_reg_index;
    ++in_reg_index;
  }

  if (is_vertex_shader()) {
    system_temp_position_ = PushSystemTemp(0b1111);
    system_temp_point_size_edge_flag_kill_vertex_ = PushSystemTemp(0b0100);

    a_.OpMov(dxbc::Dest::R(system_temp_point_size_edge_flag_kill_vertex_, 0b0001),
             dxbc::Src::LF(-1.0f));
  } else if (is_pixel_shader()) {
    if (edram_rov_used_) {
      system_temp_rov_params_ = PushSystemTemp();
    }
    if (IsDepthStencilSystemTempUsed()) {
      uint32_t depth_stencil_temp_zero_mask;
      if (current_shader().writes_depth()) {
        depth_stencil_temp_zero_mask = 0b0001;
      } else {
        assert_true(edram_rov_used_);
        if (ROV_IsDepthStencilEarly()) {
          depth_stencil_temp_zero_mask = 0b1111;
        } else {
          depth_stencil_temp_zero_mask = 0b0000;
        }
      }
      system_temp_depth_stencil_ = PushSystemTemp(depth_stencil_temp_zero_mask);
    }
    uint32_t shader_writes_color_targets = current_shader().writes_color_targets();
    for (uint32_t i = 0; i < 4; ++i) {
      if (shader_writes_color_targets & (1 << i)) {
        system_temps_color_[i] = PushSystemTemp(0b1111);
      }
    }
  }

  uint8_t memexport_eM_written = current_shader().memexport_eM_written();
  if (memexport_eM_written) {
    system_temp_memexport_enabled_and_eM_written_ = PushSystemTemp(0b0010);

    a_.OpIBFE(dxbc::Dest::R(system_temp_memexport_enabled_and_eM_written_, 0b0001),
              dxbc::Src::LU(1), dxbc::Src::LU(kSysFlag_SharedMemoryIsUAV_Shift),
              LoadFlagsSystemConstant());
    system_temp_memexport_address_ = PushSystemTemp(0b1111);
    uint8_t memexport_eM_remaining = memexport_eM_written;
    uint32_t memexport_eM_index;
    while (rex::bit_scan_forward(memexport_eM_remaining, &memexport_eM_index)) {
      memexport_eM_remaining &= ~(uint8_t(1) << memexport_eM_index);
      system_temps_memexport_data_[memexport_eM_index] = PushSystemTemp(0b1111);
    }
  }

  if (!is_depth_only_pixel_shader_) {
    system_temp_result_ = PushSystemTemp();
    system_temp_ps_pc_p0_a0_ = PushSystemTemp(0b1111);
    system_temp_aL_ = PushSystemTemp(0b1111);
    system_temp_loop_count_ = PushSystemTemp(0b1111);
    system_temp_grad_h_lod_ = PushSystemTemp(0b1111);
    system_temp_grad_v_vfetch_address_ = PushSystemTemp(0b1111);
  }

  if (is_vertex_shader()) {
    StartVertexOrDomainShader();
  } else if (is_pixel_shader()) {
    StartPixelShader();
  }

  if (is_depth_only_pixel_shader_) {
    return;
  }

  a_.OpLoop();

  if (UseSwitchForControlFlow()) {
    a_.OpSwitch(dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kYYYY));
    a_.OpCase(dxbc::Src::LU(0));
  } else {
    a_.OpIf(false, dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kYYYY));
  }
}

void DxbcShaderTranslator::CompleteVertexOrDomainShader() {
  uint32_t temp = PushSystemTemp();
  dxbc::Dest temp_x_dest(dxbc::Dest::R(temp, 0b0001));
  dxbc::Src temp_x_src(dxbc::Src::R(temp, dxbc::Src::kXXXX));

  dxbc::Src flags_src(LoadFlagsSystemConstant());

  a_.OpAnd(temp_x_dest, flags_src, dxbc::Src::LU(kSysFlag_WNotReciprocal));
  a_.OpIf(false, temp_x_src);
  a_.OpDiv(dxbc::Dest::R(system_temp_position_, 0b1000), dxbc::Src::LF(1.0f),
           dxbc::Src::R(system_temp_position_, dxbc::Src::kWWWW));
  a_.OpEndIf();

  a_.OpAnd(temp_x_dest, flags_src, dxbc::Src::LU(kSysFlag_XYDividedByW));
  a_.OpIf(true, temp_x_src);
  a_.OpMul(dxbc::Dest::R(system_temp_position_, 0b0011), dxbc::Src::R(system_temp_position_),
           dxbc::Src::R(system_temp_position_, dxbc::Src::kWWWW));
  a_.OpEndIf();

  a_.OpAnd(temp_x_dest, flags_src, dxbc::Src::LU(kSysFlag_ZDividedByW));
  a_.OpIf(true, temp_x_src);
  a_.OpMul(dxbc::Dest::R(system_temp_position_, 0b0100),
           dxbc::Src::R(system_temp_position_, dxbc::Src::kZZZZ),
           dxbc::Src::R(system_temp_position_, dxbc::Src::kWWWW));
  a_.OpEndIf();

  Modification shader_modification = GetDxbcShaderModification();
  uint32_t clip_distance_next_component = 0;
  uint32_t cull_distance_next_component = shader_modification.GetVertexClipDistanceCount();

  uint32_t& ucp_clip_cull_distance_next_component_ref =
      shader_modification.vertex.user_clip_plane_cull ? cull_distance_next_component
                                                      : clip_distance_next_component;
  for (uint32_t i = 0; i < shader_modification.vertex.user_clip_plane_count; ++i) {
    a_.OpDP4(dxbc::Dest::O(
                 out_reg_vs_clip_cull_distances_ + (ucp_clip_cull_distance_next_component_ref >> 2),
                 UINT32_C(1) << (ucp_clip_cull_distance_next_component_ref & 3)),
             dxbc::Src::R(system_temp_position_),
             LoadSystemConstant(SystemConstants::Index::kUserClipPlanes,
                                offsetof(SystemConstants, user_clip_planes) + sizeof(float) * 4 * i,
                                dxbc::Src::kXYZW));
    ++ucp_clip_cull_distance_next_component_ref;
  }

  a_.OpMul(dxbc::Dest::R(system_temp_position_, 0b0111), dxbc::Src::R(system_temp_position_),
           LoadSystemConstant(SystemConstants::Index::kNDCScale,
                              offsetof(SystemConstants, ndc_scale), 0b100100));

  a_.OpMAd(dxbc::Dest::R(system_temp_position_, 0b0111),
           LoadSystemConstant(SystemConstants::Index::kNDCOffset,
                              offsetof(SystemConstants, ndc_offset), 0b100100),
           dxbc::Src::R(system_temp_position_, dxbc::Src::kWWWW),
           dxbc::Src::R(system_temp_position_));

  bool shader_writes_vertex_kill =
      (current_shader().writes_point_size_edge_flag_kill_vertex() & 0b100) != 0;
  if (shader_writes_vertex_kill) {
    a_.OpAnd(temp_x_dest,
             dxbc::Src::R(system_temp_point_size_edge_flag_kill_vertex_, dxbc::Src::kZZZZ),
             dxbc::Src::LU(UINT32_C(0x7FFFFFFF)));
  }
  if (shader_modification.vertex.vertex_kill_and) {
    dxbc::Dest vertex_kill_dest(
        dxbc::Dest::O(out_reg_vs_clip_cull_distances_ + (cull_distance_next_component >> 2),
                      UINT32_C(1) << (cull_distance_next_component & 3)));
    if (shader_writes_vertex_kill) {
      a_.OpMovC(vertex_kill_dest, temp_x_src, dxbc::Src::LF(-1.0f), dxbc::Src::LF(0.0f));
    } else {
      a_.OpMov(vertex_kill_dest, dxbc::Src::LF(0.0f));
    }
    ++cull_distance_next_component;
  } else {
    if (shader_writes_vertex_kill) {
      a_.OpMovC(dxbc::Dest::R(system_temp_position_, 0b1000), temp_x_src,
                dxbc::Src::LF(std::nanf("")),
                dxbc::Src::R(system_temp_position_, dxbc::Src::kWWWW));
    }
  }

  a_.OpMov(dxbc::Dest::O(out_reg_vs_position_), dxbc::Src::R(system_temp_position_));

  if (out_reg_vs_point_size_ != UINT32_MAX) {
    a_.OpMov(dxbc::Dest::O(out_reg_vs_point_size_, 0b0001),
             dxbc::Src::R(system_temp_point_size_edge_flag_kill_vertex_, dxbc::Src::kXXXX));
  }

  PopSystemTemp();
}

void DxbcShaderTranslator::CompleteShaderCode() {
  if (!is_depth_only_pixel_shader_) {
    CloseExecConditionals();

    if (UseSwitchForControlFlow()) {
      a_.OpBreak();
      a_.OpEndSwitch();
    } else {
      a_.OpEndIf();
    }

    a_.OpBreak();
    a_.OpEndLoop();

    PopSystemTemp(6);
  }

  uint8_t memexport_eM_written = current_shader().memexport_eM_written();
  if (memexport_eM_written) {
    ExportToMemory(current_shader().memexport_eM_potentially_written_before_end());

    PopSystemTemp(rex::bit_count(uint32_t(memexport_eM_written)) + 2);
  }

  if (is_vertex_shader()) {
    CompleteVertexOrDomainShader();
  } else if (is_pixel_shader()) {
    CompletePixelShader();
  }

  a_.OpRet();

  if (is_vertex_shader()) {
    PopSystemTemp(2);
  } else if (is_pixel_shader()) {
    uint32_t shader_writes_color_targets = current_shader().writes_color_targets();
    for (int32_t i = 3; i >= 0; --i) {
      if (shader_writes_color_targets & (1 << i)) {
        PopSystemTemp();
      }
    }
    if (IsDepthStencilSystemTempUsed()) {
      PopSystemTemp();
    }
    if (edram_rov_used_) {
      PopSystemTemp();
    }
  }
}

std::vector<uint8_t> DxbcShaderTranslator::CompleteTranslation() {
  CompleteShaderCode();

  shader_object_.clear();

  uint32_t blob_count = 6 + uint32_t(IsDxbcDomainShader());

  shader_object_.resize(sizeof(dxbc::ContainerHeader) / sizeof(uint32_t) + blob_count);

  uint32_t blob_offset_position_dwords = sizeof(dxbc::ContainerHeader) / sizeof(uint32_t);
  uint32_t blob_position_dwords = uint32_t(shader_object_.size());
  constexpr uint32_t kBlobHeaderSizeDwords = sizeof(dxbc::BlobHeader) / sizeof(uint32_t);

  shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords);
  WriteResourceDefinition();
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kResourceDefinition;
    blob_position_dwords = uint32_t(shader_object_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_object_[blob_offset_position_dwords++];
  }

  shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords);
  WriteInputSignature();
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kInputSignature;
    blob_position_dwords = uint32_t(shader_object_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_object_[blob_offset_position_dwords++];
  }

  if (IsDxbcDomainShader()) {
    shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
    shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords);
    WritePatchConstantSignature();
    {
      auto& blob_header =
          *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
      blob_header.fourcc = dxbc::BlobHeader::FourCC::kPatchConstantSignature;
      blob_position_dwords = uint32_t(shader_object_.size());
      blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                               shader_object_[blob_offset_position_dwords++];
    }
  }

  shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords);
  WriteOutputSignature();
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kOutputSignature;
    blob_position_dwords = uint32_t(shader_object_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_object_[blob_offset_position_dwords++];
  }

  shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords);
  WriteShaderCode();
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kShaderEx;
    blob_position_dwords = uint32_t(shader_object_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_object_[blob_offset_position_dwords++];
  }

  shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords +
                        sizeof(dxbc::ShaderFeatureInfo) / sizeof(uint32_t));
  std::memcpy(shader_object_.data() + blob_position_dwords + kBlobHeaderSizeDwords,
              &shader_feature_info_, sizeof(shader_feature_info_));
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kShaderFeatureInfo;
    blob_position_dwords = uint32_t(shader_object_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_object_[blob_offset_position_dwords++];
  }

  shader_object_[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  shader_object_.resize(blob_position_dwords + kBlobHeaderSizeDwords +
                        sizeof(dxbc::Statistics) / sizeof(uint32_t));
  std::memcpy(shader_object_.data() + blob_position_dwords + kBlobHeaderSizeDwords, &statistics_,
              sizeof(statistics_));
  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_object_.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kStatistics;
    blob_position_dwords = uint32_t(shader_object_.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_object_[blob_offset_position_dwords++];
  }

  uint32_t shader_object_size_bytes = uint32_t(shader_object_.size() * sizeof(uint32_t));
  {
    auto& container_header = *reinterpret_cast<dxbc::ContainerHeader*>(shader_object_.data());
    container_header.InitializeIdentification();
    container_header.size_bytes = shader_object_size_bytes;
    container_header.blob_count = blob_count;
    CalculateDXBCChecksum(reinterpret_cast<unsigned char*>(shader_object_.data()),
                          static_cast<unsigned int>(shader_object_size_bytes),
                          reinterpret_cast<unsigned int*>(&container_header.hash));
  }

  std::vector<uint8_t> shader_object_bytes;
  shader_object_bytes.resize(shader_object_size_bytes);
  std::memcpy(shader_object_bytes.data(), shader_object_.data(), shader_object_size_bytes);
  return shader_object_bytes;
}

void DxbcShaderTranslator::PostTranslation() {
  Shader::Translation& translation = current_translation();
  if (!translation.is_valid()) {
    return;
  }
  DxbcShader* dxbc_shader = dynamic_cast<DxbcShader*>(&translation.shader());
  if (dxbc_shader &&
      !dxbc_shader->bindings_setup_entered_.test_and_set(std::memory_order_relaxed)) {
    dxbc_shader->texture_bindings_.clear();
    dxbc_shader->texture_bindings_.reserve(texture_bindings_.size());
    dxbc_shader->used_texture_mask_ = 0;
    for (const TextureBinding& translator_binding : texture_bindings_) {
      DxbcShader::TextureBinding& shader_binding = dxbc_shader->texture_bindings_.emplace_back();

      std::memset(&shader_binding, 0, sizeof(shader_binding));
      shader_binding.bindless_descriptor_index = translator_binding.bindless_descriptor_index;
      shader_binding.fetch_constant = translator_binding.fetch_constant;
      shader_binding.dimension = translator_binding.dimension;
      shader_binding.is_signed = translator_binding.is_signed;
      dxbc_shader->used_texture_mask_ |= 1u << translator_binding.fetch_constant;
    }
    dxbc_shader->sampler_bindings_.clear();
    dxbc_shader->sampler_bindings_.reserve(sampler_bindings_.size());
    for (const SamplerBinding& translator_binding : sampler_bindings_) {
      DxbcShader::SamplerBinding& shader_binding = dxbc_shader->sampler_bindings_.emplace_back();
      shader_binding.bindless_descriptor_index = translator_binding.bindless_descriptor_index;
      shader_binding.fetch_constant = translator_binding.fetch_constant;
      shader_binding.mag_filter = translator_binding.mag_filter;
      shader_binding.min_filter = translator_binding.min_filter;
      shader_binding.mip_filter = translator_binding.mip_filter;
      shader_binding.aniso_filter = translator_binding.aniso_filter;
      shader_binding.border_color_forced = translator_binding.border_color_forced;
      shader_binding.forced_border_color = translator_binding.forced_border_color;
    }
  }
}

void DxbcShaderTranslator::EmitInstructionDisassembly() {
  if (!emit_source_map_) {
    return;
  }
  const char* source = instruction_disassembly_buffer_.buffer();
  uint32_t length = uint32_t(instruction_disassembly_buffer_.length());

  while (length != 0 && source[0] == ' ') {
    ++source;
    --length;
  }
  while (length != 0 && source[length - 1] == '\n') {
    --length;
  }
  if (length == 0) {
    return;
  }
  char* dest =
      reinterpret_cast<char*>(a_.OpCustomData(dxbc::CustomDataClass::kComment, length + 1));
  std::memcpy(dest, source, length);
  dest[length] = '\0';
}

dxbc::Src DxbcShaderTranslator::LoadOperand(const InstructionOperand& operand,
                                            uint32_t needed_components, bool& temp_pushed_out) {
  temp_pushed_out = false;

  uint32_t first_needed_component;
  if (!rex::bit_scan_forward(needed_components, &first_needed_component)) {
    return dxbc::Src::LF(0.0f);
  }

  dxbc::Index index(operand.storage_index);
  switch (operand.storage_addressing_mode) {
    case InstructionStorageAddressingMode::kAbsolute:
      break;
    case InstructionStorageAddressingMode::kAddressRegisterRelative:
      index = dxbc::Index(system_temp_ps_pc_p0_a0_, 3, operand.storage_index);
      break;
    case InstructionStorageAddressingMode::kLoopRelative:
      index = dxbc::Index(system_temp_aL_, 0, operand.storage_index);
      break;
  }

  dxbc::Src src(dxbc::Src::LF(0.0f));
  switch (operand.storage_source) {
    case InstructionStorageSource::kRegister: {
      if (current_shader().uses_register_dynamic_addressing()) {
        uint32_t temp = PushSystemTemp();
        temp_pushed_out = true;
        uint32_t used_swizzle_components = 0;
        for (uint32_t i = 0; i < uint32_t(operand.component_count); ++i) {
          if (!(needed_components & (1 << i))) {
            continue;
          }
          SwizzleSource component = operand.GetComponent(i);
          assert_true(component >= SwizzleSource::kX && component <= SwizzleSource::kW);
          used_swizzle_components |= 1 << (uint32_t(component) - uint32_t(SwizzleSource::kX));
        }
        assert_not_zero(used_swizzle_components);
        a_.OpMov(dxbc::Dest::R(temp, used_swizzle_components), dxbc::Src::X(0, index));
        src = dxbc::Src::R(temp);
      } else {
        assert_true(operand.storage_addressing_mode == InstructionStorageAddressingMode::kAbsolute);
        src = dxbc::Src::R(index.index_);
      }
    } break;
    case InstructionStorageSource::kConstantFloat: {
      if (cbuffer_index_float_constants_ == kBindingIndexUnallocated) {
        cbuffer_index_float_constants_ = cbuffer_count_++;
      }
      const Shader::ConstantRegisterMap& constant_register_map =
          current_shader().constant_register_map();
      if (operand.storage_addressing_mode == InstructionStorageAddressingMode::kAbsolute) {
        uint32_t float_constant_index =
            constant_register_map.GetPackedFloatConstantIndex(operand.storage_index);
        assert_true(float_constant_index != UINT32_MAX);
        if (float_constant_index == UINT32_MAX) {
          return dxbc::Src::LF(0.0f);
        }
        index.index_ = float_constant_index;
      } else {
        assert_true(constant_register_map.float_dynamic_addressing);
      }
      src = dxbc::Src::CB(cbuffer_index_float_constants_,
                          uint32_t(CbufferRegister::kFloatConstants), index);
    } break;
    default:
      assert_unhandled_case(operand.storage_source);
      return dxbc::Src::LF(0.0f);
  }

  uint32_t swizzle = 0;
  for (uint32_t i = 0; i < 4; ++i) {
    SwizzleSource component =
        operand.GetComponent((needed_components & (1 << i)) ? i : first_needed_component);
    assert_true(component >= SwizzleSource::kX && component <= SwizzleSource::kW);
    swizzle |= (uint32_t(component) - uint32_t(SwizzleSource::kX)) << (i * 2);
  }
  src = src.Swizzle(swizzle);

  return src.WithModifiers(operand.is_absolute_value, operand.is_negated);
}

void DxbcShaderTranslator::StoreResult(const InstructionResult& result, const dxbc::Src& src,
                                       bool can_store_memexport_address) {
  uint32_t used_write_mask = result.GetUsedWriteMask();
  if (!used_write_mask) {
    return;
  }

  dxbc::Dest dest(dxbc::Dest::Null());
  bool is_clamped = result.is_clamped;
  switch (result.storage_target) {
    case InstructionStorageTarget::kNone:
      return;
    case InstructionStorageTarget::kRegister:
      if (current_shader().uses_register_dynamic_addressing()) {
        dxbc::Index register_index(result.storage_index);
        switch (result.storage_addressing_mode) {
          case InstructionStorageAddressingMode::kAbsolute:
            break;
          case InstructionStorageAddressingMode::kAddressRegisterRelative:
            register_index = dxbc::Index(system_temp_ps_pc_p0_a0_, 3, result.storage_index);
            break;
          case InstructionStorageAddressingMode::kLoopRelative:
            register_index = dxbc::Index(system_temp_aL_, 0, result.storage_index);
            break;
        }
        dest = dxbc::Dest::X(0, register_index);
      } else {
        assert_true(result.storage_addressing_mode == InstructionStorageAddressingMode::kAbsolute);
        dest = dxbc::Dest::R(result.storage_index);
      }
      break;
    case InstructionStorageTarget::kInterpolator: {
      uint32_t interpolator_mask = GetModificationInterpolatorMask();
      uint32_t interpolator_bit = UINT32_C(1) << result.storage_index;
      if (interpolator_mask & interpolator_bit) {
        dest = dxbc::Dest::O(out_reg_vs_interpolators_ +
                             rex::bit_count(interpolator_mask & (interpolator_bit - 1)));
      }
    } break;
    case InstructionStorageTarget::kPosition:
      dest = dxbc::Dest::R(system_temp_position_);
      break;
    case InstructionStorageTarget::kPointSizeEdgeFlagKillVertex:
      assert_zero(used_write_mask & 0b1000);
      dest = dxbc::Dest::R(system_temp_point_size_edge_flag_kill_vertex_);
      break;
    case InstructionStorageTarget::kExportAddress:
      if (!can_store_memexport_address) {
        return;
      }
      if (!current_shader().memexport_eM_written()) {
        return;
      }
      dest = dxbc::Dest::R(system_temp_memexport_address_);
      break;
    case InstructionStorageTarget::kExportData: {
      assert_not_zero(current_shader().memexport_eM_written() &
                      (uint8_t(1) << result.storage_index));
      dest = dxbc::Dest::R(system_temps_memexport_data_[result.storage_index]);

      assert_not_zero(used_write_mask);
      a_.OpOr(dxbc::Dest::R(system_temp_memexport_enabled_and_eM_written_, 0b0010),
              dxbc::Src::R(system_temp_memexport_enabled_and_eM_written_, dxbc::Src::kYYYY),
              dxbc::Src::LU(uint8_t(1) << result.storage_index));
    } break;
    case InstructionStorageTarget::kColor:
      assert_not_zero(used_write_mask);
      assert_true(current_shader().writes_color_target(result.storage_index));
      dest = dxbc::Dest::R(system_temps_color_[result.storage_index]);
      if (edram_rov_used_) {
        a_.OpOr(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
                dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                dxbc::Src::LU(uint32_t(1) << (8 + result.storage_index)));
      }
      break;
    case InstructionStorageTarget::kDepth:

      assert_true(used_write_mask == 0b0001);
      assert_true(current_shader().writes_depth());
      if (IsDepthStencilSystemTempUsed()) {
        dest = dxbc::Dest::R(system_temp_depth_stencil_);
      } else {
        dest = dxbc::Dest::ODepth();
      }

      is_clamped = true;
      break;
  }
  if (dest.type_ == dxbc::OperandType::kNull) {
    return;
  }

  uint32_t src_additional_swizzle = 0;
  uint32_t constant_mask = 0, constant_1_mask = 0;
  for (uint32_t i = 0; i < 4; ++i) {
    if (!(used_write_mask & (1 << i))) {
      continue;
    }
    SwizzleSource component = result.components[i];
    if (component >= SwizzleSource::kX && component <= SwizzleSource::kW) {
      src_additional_swizzle |= (uint32_t(component) - uint32_t(SwizzleSource::kX)) << (i * 2);
    } else {
      constant_mask |= 1 << i;
      if (component == SwizzleSource::k1) {
        constant_1_mask |= 1 << i;
      }
    }
  }
  if (used_write_mask != constant_mask) {
    a_.OpMov(dest.Mask(used_write_mask & ~constant_mask),
             src.SwizzleSwizzled(src_additional_swizzle), is_clamped);
  }
  if (constant_mask) {
    a_.OpMov(dest.Mask(constant_mask),
             dxbc::Src::LF(float(constant_1_mask & 1), float((constant_1_mask >> 1) & 1),
                           float((constant_1_mask >> 2) & 1), float((constant_1_mask >> 3) & 1)));
  }

  if (result.storage_target == InstructionStorageTarget::kPointSizeEdgeFlagKillVertex &&
      (used_write_mask & 0b0001)) {
    a_.OpIMax(
        dxbc::Dest::R(system_temp_point_size_edge_flag_kill_vertex_, 0b0001),
        LoadSystemConstant(SystemConstants::Index::kPointVertexDiameterMin,
                           offsetof(SystemConstants, point_vertex_diameter_min), dxbc::Src::kXXXX),
        dxbc::Src::R(system_temp_point_size_edge_flag_kill_vertex_, dxbc::Src::kXXXX));
    a_.OpIMin(
        dxbc::Dest::R(system_temp_point_size_edge_flag_kill_vertex_, 0b0001),
        LoadSystemConstant(SystemConstants::Index::kPointVertexDiameterMax,
                           offsetof(SystemConstants, point_vertex_diameter_max), dxbc::Src::kXXXX),
        dxbc::Src::R(system_temp_point_size_edge_flag_kill_vertex_, dxbc::Src::kXXXX));
  }
}

void DxbcShaderTranslator::UpdateExecConditionalsAndEmitDisassembly(
    ParsedExecInstruction::Type type, uint32_t bool_constant_index, bool condition) {
  bool merge = false;
  if (type == ParsedExecInstruction::Type::kConditional) {
    if (cf_exec_bool_constant_ == bool_constant_index &&
        cf_exec_bool_constant_condition_ == condition) {
      merge = true;
    }
  } else if (type == ParsedExecInstruction::Type::kPredicated) {
    if (!cf_exec_predicate_written_ && cf_exec_predicated_ &&
        cf_exec_predicate_condition_ == condition) {
      merge = true;
    }
  } else {
    if (cf_exec_bool_constant_ == kCfExecBoolConstantNone && !cf_exec_predicated_) {
      merge = true;
    }
  }

  if (merge) {
    EmitInstructionDisassembly();
    return;
  }

  CloseExecConditionals();

  EmitInstructionDisassembly();

  if (type == ParsedExecInstruction::Type::kConditional) {
    uint32_t bool_constant_test_temp = PushSystemTemp();

    if (cbuffer_index_bool_loop_constants_ == kBindingIndexUnallocated) {
      cbuffer_index_bool_loop_constants_ = cbuffer_count_++;
    }
    a_.OpAnd(dxbc::Dest::R(bool_constant_test_temp, 0b0001),
             dxbc::Src::CB(cbuffer_index_bool_loop_constants_,
                           uint32_t(CbufferRegister::kBoolLoopConstants), bool_constant_index >> 7)
                 .Select((bool_constant_index >> 5) & 3),
             dxbc::Src::LU(uint32_t(1) << (bool_constant_index & 31)));

    a_.OpIf(condition, dxbc::Src::R(bool_constant_test_temp, dxbc::Src::kXXXX));

    PopSystemTemp();
    cf_exec_bool_constant_ = bool_constant_index;
    cf_exec_bool_constant_condition_ = condition;
  } else if (type == ParsedExecInstruction::Type::kPredicated) {
    a_.OpIf(condition, dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kZZZZ));
    cf_exec_predicated_ = true;
    cf_exec_predicate_condition_ = condition;
  }
}

void DxbcShaderTranslator::CloseExecConditionals() {
  CloseInstructionPredication();

  if (cf_exec_bool_constant_ != kCfExecBoolConstantNone || cf_exec_predicated_) {
    a_.OpEndIf();
    cf_exec_bool_constant_ = kCfExecBoolConstantNone;
    cf_exec_predicated_ = false;
  }

  cf_exec_predicate_written_ = false;
}

void DxbcShaderTranslator::UpdateInstructionPredicationAndEmitDisassembly(bool predicated,
                                                                          bool condition) {
  if (!predicated) {
    CloseInstructionPredication();
    EmitInstructionDisassembly();
    return;
  }

  if (cf_instruction_predicate_if_open_) {
    if (cf_instruction_predicate_condition_ == condition) {
      EmitInstructionDisassembly();
      return;
    }
    CloseInstructionPredication();
  }

  EmitInstructionDisassembly();

  if (!cf_exec_predicate_written_ && cf_exec_predicated_ &&
      cf_exec_predicate_condition_ == condition) {
    return;
  }

  a_.OpIf(condition, dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kZZZZ));
  cf_instruction_predicate_if_open_ = true;
  cf_instruction_predicate_condition_ = condition;
}

void DxbcShaderTranslator::CloseInstructionPredication() {
  if (cf_instruction_predicate_if_open_) {
    a_.OpEndIf();
    cf_instruction_predicate_if_open_ = false;
  }
}

void DxbcShaderTranslator::JumpToLabel(uint32_t address) {
  a_.OpMov(dxbc::Dest::R(system_temp_ps_pc_p0_a0_, 0b0010), dxbc::Src::LU(address));
  a_.OpContinue();
}

void DxbcShaderTranslator::ProcessLabel(uint32_t cf_index) {
  if (cf_index == 0) {
    return;
  }

  CloseExecConditionals();
  if (UseSwitchForControlFlow()) {
    JumpToLabel(cf_index);

    a_.OpBreak();

    a_.OpCase(dxbc::Src::LU(cf_index));
  } else {
    a_.OpEndIf();

    uint32_t test_temp = PushSystemTemp();
    a_.OpUGE(dxbc::Dest::R(test_temp, 0b0001), dxbc::Src::LU(cf_index),
             dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kYYYY));
    a_.OpIf(true, dxbc::Src::R(test_temp, dxbc::Src::kXXXX));

    PopSystemTemp();
  }
}

void DxbcShaderTranslator::ProcessExecInstructionBegin(const ParsedExecInstruction& instr) {
  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
  }
  UpdateExecConditionalsAndEmitDisassembly(instr.type, instr.bool_constant_index, instr.condition);
}

void DxbcShaderTranslator::ProcessExecInstructionEnd(const ParsedExecInstruction& instr) {
  if (instr.is_end) {
    CloseInstructionPredication();
    if (UseSwitchForControlFlow()) {
      a_.OpMov(dxbc::Dest::R(system_temp_ps_pc_p0_a0_, 0b0010), dxbc::Src::LU(UINT32_MAX));

      a_.OpContinue();
    } else {
      a_.OpBreak();
    }
  }
}

void DxbcShaderTranslator::ProcessLoopStartInstruction(const ParsedLoopStartInstruction& instr) {
  CloseExecConditionals();

  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
    EmitInstructionDisassembly();
  }

  if (cbuffer_index_bool_loop_constants_ == kBindingIndexUnallocated) {
    cbuffer_index_bool_loop_constants_ = cbuffer_count_++;
  }
  dxbc::Src loop_constant_src(dxbc::Src::CB(cbuffer_index_bool_loop_constants_,
                                            uint32_t(CbufferRegister::kBoolLoopConstants),
                                            2 + (instr.loop_constant_index >> 2))
                                  .Select(instr.loop_constant_index & 3));

  {
    uint32_t loop_count_temp = PushSystemTemp();
    a_.OpAnd(dxbc::Dest::R(loop_count_temp, 0b0001), loop_constant_src, dxbc::Src::LU(UINT8_MAX));

    a_.OpIf(false, dxbc::Src::R(loop_count_temp, dxbc::Src::kXXXX));
    JumpToLabel(instr.loop_skip_address);
    a_.OpEndIf();

    a_.OpMov(dxbc::Dest::R(system_temp_loop_count_, 0b1110),
             dxbc::Src::R(system_temp_loop_count_, 0b10010000));
    a_.OpMov(dxbc::Dest::R(system_temp_loop_count_, 0b0001),
             dxbc::Src::R(loop_count_temp, dxbc::Src::kXXXX));

    PopSystemTemp();
  }

  a_.OpMov(dxbc::Dest::R(system_temp_aL_, instr.is_repeat ? 0b1111 : 0b1110),
           dxbc::Src::R(system_temp_aL_, 0b10010000));
  if (!instr.is_repeat) {
    a_.OpUBFE(dxbc::Dest::R(system_temp_aL_, 0b0001), dxbc::Src::LU(8), dxbc::Src::LU(8),
              loop_constant_src);
  }
}

void DxbcShaderTranslator::ProcessLoopEndInstruction(const ParsedLoopEndInstruction& instr) {
  CloseExecConditionals();

  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
    EmitInstructionDisassembly();
  }

  a_.OpIAdd(dxbc::Dest::R(system_temp_loop_count_, 0b0001),
            dxbc::Src::R(system_temp_loop_count_, dxbc::Src::kXXXX), dxbc::Src::LI(-1));

  if (instr.is_predicated_break) {
    uint32_t break_case_temp = PushSystemTemp();
    if (instr.predicate_condition) {
      a_.OpMovC(dxbc::Dest::R(break_case_temp, 0b0001),
                dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kZZZZ), dxbc::Src::LU(0),
                dxbc::Src::R(system_temp_loop_count_, dxbc::Src::kXXXX));
    } else {
      a_.OpMovC(dxbc::Dest::R(break_case_temp, 0b0001),
                dxbc::Src::R(system_temp_ps_pc_p0_a0_, dxbc::Src::kZZZZ),
                dxbc::Src::R(system_temp_loop_count_, dxbc::Src::kXXXX), dxbc::Src::LU(0));
    }
    a_.OpIf(false, dxbc::Src::R(break_case_temp, dxbc::Src::kXXXX));

    PopSystemTemp();
  } else {
    a_.OpIf(false, dxbc::Src::R(system_temp_loop_count_, dxbc::Src::kXXXX));
  }
  {
    a_.OpMov(dxbc::Dest::R(system_temp_loop_count_, 0b0111),
             dxbc::Src::R(system_temp_loop_count_, 0b111001));
    a_.OpMov(dxbc::Dest::R(system_temp_loop_count_, 0b1000), dxbc::Src::LU(0));
    a_.OpMov(dxbc::Dest::R(system_temp_aL_, 0b0111), dxbc::Src::R(system_temp_aL_, 0b111001));
    a_.OpMov(dxbc::Dest::R(system_temp_aL_, 0b1000), dxbc::Src::LI(0));
  }
  a_.OpElse();
  {
    uint32_t aL_add_temp = PushSystemTemp();

    if (cbuffer_index_bool_loop_constants_ == kBindingIndexUnallocated) {
      cbuffer_index_bool_loop_constants_ = cbuffer_count_++;
    }
    a_.OpIBFE(dxbc::Dest::R(aL_add_temp, 0b0001), dxbc::Src::LU(8), dxbc::Src::LU(16),
              dxbc::Src::CB(cbuffer_index_bool_loop_constants_,
                            uint32_t(CbufferRegister::kBoolLoopConstants),
                            2 + (instr.loop_constant_index >> 2))
                  .Select(instr.loop_constant_index & 3));

    a_.OpIAdd(dxbc::Dest::R(system_temp_aL_, 0b0001),
              dxbc::Src::R(system_temp_aL_, dxbc::Src::kXXXX),
              dxbc::Src::R(aL_add_temp, dxbc::Src::kXXXX));

    PopSystemTemp();

    JumpToLabel(instr.loop_body_address);
  }
  a_.OpEndIf();
}

void DxbcShaderTranslator::ProcessJumpInstruction(const ParsedJumpInstruction& instr) {
  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
  }

  ParsedExecInstruction::Type type;
  if (instr.type == ParsedJumpInstruction::Type::kConditional) {
    type = ParsedExecInstruction::Type::kConditional;
  } else if (instr.type == ParsedJumpInstruction::Type::kPredicated) {
    type = ParsedExecInstruction::Type::kPredicated;
  } else {
    type = ParsedExecInstruction::Type::kUnconditional;
  }
  UpdateExecConditionalsAndEmitDisassembly(type, instr.bool_constant_index, instr.condition);

  CloseInstructionPredication();

  JumpToLabel(instr.target_address);
}

void DxbcShaderTranslator::ProcessAllocInstruction(const ParsedAllocInstruction& instr,
                                                   uint8_t export_eM) {
  bool start_memexport =
      instr.type == AllocType::kMemory && current_shader().memexport_eM_written();
  if (export_eM || start_memexport) {
    CloseExecConditionals();
  }

  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
    EmitInstructionDisassembly();
  }

  if (export_eM) {
    ExportToMemory(export_eM);

    a_.OpMov(dxbc::Dest::R(system_temp_memexport_enabled_and_eM_written_, 0b0010),
             dxbc::Src::LU(0));

    uint8_t export_eM_remaining = export_eM;
    uint32_t eM_index;
    while (rex::bit_scan_forward(export_eM_remaining, &eM_index)) {
      export_eM_remaining &= ~(uint8_t(1) << eM_index);
      a_.OpMov(dxbc::Dest::R(system_temps_memexport_data_[eM_index]), dxbc::Src::LF(0.0f));
    }
  }

  if (start_memexport) {
    a_.OpMov(dxbc::Dest::R(system_temp_memexport_address_), dxbc::Src::LU(0));
  }
}

const DxbcShaderTranslator::ShaderRdefType
    DxbcShaderTranslator::rdef_types_[size_t(DxbcShaderTranslator::ShaderRdefTypeIndex::kCount)] = {

        {"float", dxbc::RdefVariableClass::kScalar, dxbc::RdefVariableType::kFloat, 1, 1, 0,
         ShaderRdefTypeIndex::kUnknown},

        {"float2", dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kFloat, 1, 2, 0,
         ShaderRdefTypeIndex::kUnknown},

        {"float3", dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kFloat, 1, 3, 0,
         ShaderRdefTypeIndex::kUnknown},

        {"float4", dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kFloat, 1, 4, 0,
         ShaderRdefTypeIndex::kUnknown},

        {"dword", dxbc::RdefVariableClass::kScalar, dxbc::RdefVariableType::kUInt, 1, 1, 0,
         ShaderRdefTypeIndex::kUnknown},

        {"uint2", dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kUInt, 1, 2, 0,
         ShaderRdefTypeIndex::kUnknown},

        {"uint4", dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kUInt, 1, 4, 0,
         ShaderRdefTypeIndex::kUnknown},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kFloat, 1, 4, 4,
         ShaderRdefTypeIndex::kFloat4},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kFloat, 1, 4, 6,
         ShaderRdefTypeIndex::kFloat4},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kFloat, 1, 4, 0,
         ShaderRdefTypeIndex::kFloat4},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kUInt, 1, 4, 2,
         ShaderRdefTypeIndex::kUint4},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kUInt, 1, 4, 8,
         ShaderRdefTypeIndex::kUint4},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kUInt, 1, 4, 48,
         ShaderRdefTypeIndex::kUint4},

        {nullptr, dxbc::RdefVariableClass::kVector, dxbc::RdefVariableType::kUInt, 1, 4, 0,
         ShaderRdefTypeIndex::kUint4},
};

const DxbcShaderTranslator::SystemConstantRdef DxbcShaderTranslator::system_constant_rdef_[size_t(
    DxbcShaderTranslator::SystemConstants::Index::kCount)] = {
    {"xe_flags", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},
    {"xe_tessellation_factor_range", ShaderRdefTypeIndex::kFloat2, sizeof(float) * 2},
    {"xe_line_loop_closing_index", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},

    {"xe_vertex_index_endian", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},
    {"xe_vertex_index_offset", ShaderRdefTypeIndex::kUint, sizeof(int32_t)},
    {"xe_vertex_index_min_max", ShaderRdefTypeIndex::kUint2, sizeof(uint32_t) * 2},

    {"xe_user_clip_planes", ShaderRdefTypeIndex::kFloat4Array6, sizeof(float) * 4 * 6},

    {"xe_ndc_scale", ShaderRdefTypeIndex::kFloat3, sizeof(float) * 3},
    {"xe_point_vertex_diameter_min", ShaderRdefTypeIndex::kFloat, sizeof(float)},

    {"xe_ndc_offset", ShaderRdefTypeIndex::kFloat3, sizeof(float) * 3},
    {"xe_point_vertex_diameter_max", ShaderRdefTypeIndex::kFloat, sizeof(float)},

    {"xe_point_constant_diameter", ShaderRdefTypeIndex::kFloat2, sizeof(float) * 2},
    {"xe_point_screen_diameter_to_ndc_radius", ShaderRdefTypeIndex::kFloat2, sizeof(float) * 2},

    {"xe_texture_swizzled_signs", ShaderRdefTypeIndex::kUint4Array2, sizeof(uint32_t) * 4 * 2},

    {"xe_textures_resolution_scaled", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},
    {"xe_sample_count_log2", ShaderRdefTypeIndex::kUint2, sizeof(uint32_t) * 2},
    {"xe_alpha_test_reference", ShaderRdefTypeIndex::kFloat, sizeof(float)},

    {"xe_alpha_to_mask", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},
    {"xe_edram_32bpp_tile_pitch_dwords_scaled", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},
    {"xe_edram_depth_base_dwords_scaled", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},
    {"xe_zpd_counter_index", ShaderRdefTypeIndex::kUint, sizeof(uint32_t)},

    {"xe_color_exp_bias", ShaderRdefTypeIndex::kFloat4, sizeof(float) * 4},

    {"xe_edram_poly_offset_front", ShaderRdefTypeIndex::kFloat2, sizeof(float) * 2},
    {"xe_edram_poly_offset_back", ShaderRdefTypeIndex::kFloat2, sizeof(float) * 2},

    {"xe_edram_stencil", ShaderRdefTypeIndex::kUint4Array2, sizeof(uint32_t) * 4 * 2},

    {"xe_edram_rt_base_dwords_scaled", ShaderRdefTypeIndex::kUint4, sizeof(uint32_t) * 4},

    {"xe_edram_rt_format_flags", ShaderRdefTypeIndex::kUint4, sizeof(uint32_t) * 4},

    {"xe_edram_rt_clamp", ShaderRdefTypeIndex::kFloat4Array4, sizeof(float) * 4 * 4},

    {"xe_edram_rt_keep_mask", ShaderRdefTypeIndex::kUint4Array2, sizeof(uint32_t) * 4 * 2},

    {"xe_edram_rt_blend_factors_ops", ShaderRdefTypeIndex::kUint4, sizeof(uint32_t) * 4},

    {"xe_edram_blend_constant", ShaderRdefTypeIndex::kFloat4, sizeof(float) * 4},

    {"xe_texture_integer_scale_bits", ShaderRdefTypeIndex::kUint4Array8, sizeof(uint32_t) * 32},
};

}
