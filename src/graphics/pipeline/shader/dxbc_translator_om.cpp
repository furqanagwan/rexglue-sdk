/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <cstdint>

#include <rex/assert.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/xenos_zpd_report.h>
#include <rex/graphics/pipeline/texture/cache.h>
#include <rex/graphics/util/draw.h>
#include <rex/math.h>

namespace rex::graphics {
using namespace ucode;

void DxbcShaderTranslator::CompletePixelShader_WriteToRTVs() {
  uint32_t shader_writes_color_targets = current_shader().writes_color_targets();
  if (!shader_writes_color_targets) {
    return;
  }

  uint32_t gamma_temp = PushSystemTemp();
  for (uint32_t i = 0; i < 4; ++i) {
    if (!(shader_writes_color_targets & (1 << i))) {
      continue;
    }
    uint32_t system_temp_color = system_temps_color_[i];

    a_.OpMul(dxbc::Dest::R(system_temp_color), dxbc::Src::R(system_temp_color),
             LoadSystemConstant(SystemConstants::Index::kColorExpBias,
                                offsetof(SystemConstants, color_exp_bias) + sizeof(float) * i,
                                dxbc::Src::kXXXX));
    if (gamma_render_target_as_unorm8_) {
      a_.OpAnd(dxbc::Dest::R(gamma_temp, 0b0001), LoadFlagsSystemConstant(),
               dxbc::Src::LU(kSysFlag_ConvertColor0ToGamma << i));
      a_.OpIf(true, dxbc::Src::R(gamma_temp, dxbc::Src::kXXXX));

      a_.OpMov(dxbc::Dest::R(system_temp_color, 0b0111), dxbc::Src::R(system_temp_color), true);
      for (uint32_t j = 0; j < 3; ++j) {
        PreSaturatedLinearToPWLGamma(a_, system_temp_color, j, system_temp_color, j, gamma_temp, 0,
                                     gamma_temp, 1);
      }
      a_.OpEndIf();
    }

    a_.OpMov(dxbc::Dest::O(i), dxbc::Src::R(system_temp_color));
  }

  PopSystemTemp();
}

void DxbcShaderTranslator::CompletePixelShader_DSV_DepthTo24Bit() {
  bool shader_writes_depth = current_shader().writes_depth();

  if (!DSV_IsWritingFloat24Depth()) {
    if (shader_writes_depth) {
      a_.OpAnd(dxbc::Dest::R(system_temp_depth_stencil_, 0b0010), LoadFlagsSystemConstant(),
               dxbc::Src::LU(kSysFlag_DepthFloat24));
      a_.OpIf(true, dxbc::Src::R(system_temp_depth_stencil_, dxbc::Src::kYYYY));
      a_.OpMul(dxbc::Dest::R(system_temp_depth_stencil_, 0b0001),
               dxbc::Src::R(system_temp_depth_stencil_, dxbc::Src::kXXXX), dxbc::Src::LF(0.5f));
      a_.OpEndIf();

      a_.OpMov(dxbc::Dest::ODepth(), dxbc::Src::R(system_temp_depth_stencil_, dxbc::Src::kXXXX));
    }
    return;
  }

  uint32_t temp;
  if (shader_writes_depth) {
    temp = system_temp_depth_stencil_;
  } else {
    temp = PushSystemTemp();
    in_position_used_ |= 0b0100;
    a_.OpMul(dxbc::Dest::R(temp, 0b0001), dxbc::Src::V1D(in_reg_ps_position_, dxbc::Src::kZZZZ),
             dxbc::Src::LF(2.0f), true);
  }

  dxbc::Dest temp_x_dest(dxbc::Dest::R(temp, 0b0001));
  dxbc::Src temp_x_src(dxbc::Src::R(temp, dxbc::Src::kXXXX));
  dxbc::Dest temp_y_dest(dxbc::Dest::R(temp, 0b0010));
  dxbc::Src temp_y_src(dxbc::Src::R(temp, dxbc::Src::kYYYY));

  if (GetDxbcShaderModification().pixel.depth_stencil_mode ==
      Modification::DepthStencilMode::kFloat24Truncating) {
    dxbc::Dest truncate_dest(shader_writes_depth ? dxbc::Dest::ODepth() : dxbc::Dest::ODepthLE());

    a_.OpUGE(temp_y_dest, temp_x_src, dxbc::Src::LU(0x2E800000));
    a_.OpIf(true, temp_y_src);
    {
      a_.OpUBFE(temp_y_dest, dxbc::Src::LU(8), dxbc::Src::LU(23), temp_x_src);

      a_.OpIAdd(temp_y_dest, dxbc::Src::LI(116), -temp_y_src);

      a_.OpIMax(temp_y_dest, temp_y_src, dxbc::Src::LI(3));

      a_.OpBFI(temp_x_dest, temp_y_src, dxbc::Src::LU(0), dxbc::Src::LU(0), temp_x_src);

      a_.OpMul(truncate_dest, temp_x_src, dxbc::Src::LF(0.5f));
    }

    a_.OpElse();
    a_.OpMov(truncate_dest, dxbc::Src::LF(0.0f));

    a_.OpEndIf();
  } else {
    PreClampedDepthTo20e4(a_, temp, 0, temp, 0, temp, 1, true, false);
    Depth20e4To32(a_, dxbc::Dest::ODepth(), temp, 0, 0, temp, 0, temp, 1, true);
  }

  if (!shader_writes_depth) {
    PopSystemTemp();
  }
}

void DxbcShaderTranslator::CompletePixelShader_AlphaToMaskSample(
    bool initialize, uint32_t sample_index, float threshold_base, dxbc::Src threshold_offset,
    float threshold_offset_scale, uint32_t coverage_temp, uint32_t coverage_temp_component,
    uint32_t temp, uint32_t temp_component) {
  dxbc::Dest temp_dest(dxbc::Dest::R(temp, 1 << temp_component));
  dxbc::Src temp_src(dxbc::Src::R(temp).Select(temp_component));

  a_.OpMAd(temp_dest, threshold_offset, dxbc::Src::LF(-threshold_offset_scale),
           dxbc::Src::LF(threshold_base));

  a_.OpGE(temp_dest, dxbc::Src::R(system_temps_color_[0], dxbc::Src::kWWWW), temp_src);
  dxbc::Dest coverage_dest(dxbc::Dest::R(coverage_temp, 1 << coverage_temp_component));
  dxbc::Src coverage_src(dxbc::Src::R(coverage_temp).Select(coverage_temp_component));
  if (edram_rov_used_) {
    assert_true(coverage_temp != temp || coverage_temp_component != temp_component);

    a_.OpOr(temp_dest, temp_src, dxbc::Src::LU(~(uint32_t(0b00010001) << sample_index)));

    a_.OpAnd(coverage_dest, coverage_src, temp_src);
  } else {
    if (initialize) {
      assert_true(coverage_temp != temp || coverage_temp_component != temp_component);
      a_.OpAnd(coverage_dest, temp_src, dxbc::Src::LU(uint32_t(1) << sample_index));
    } else {
      a_.OpAnd(temp_dest, temp_src, dxbc::Src::LU(uint32_t(1) << sample_index));
      a_.OpOr(coverage_dest, coverage_src, temp_src);
    }
  }
}

void DxbcShaderTranslator::CompletePixelShader_AlphaToMask(uint32_t zpd_coverage_temp) {
  if (!current_shader().writes_color_target(0) || IsForceEarlyDepthStencilGlobalFlagEnabled()) {
    return;
  }

  if (!edram_rov_used_) {
    a_.OpMov(dxbc::Dest::OMask(), dxbc::Src::LU(UINT32_MAX));
  }

  dxbc::Src alpha_to_mask_constant_src(LoadSystemConstant(SystemConstants::Index::kAlphaToMask,
                                                          offsetof(SystemConstants, alpha_to_mask),
                                                          dxbc::Src::kXXXX));
  a_.OpIf(true, alpha_to_mask_constant_src);

  uint32_t temp = PushSystemTemp();
  dxbc::Dest temp_x_dest(dxbc::Dest::R(temp, 0b0001));
  dxbc::Src temp_x_src(dxbc::Src::R(temp, dxbc::Src::kXXXX));

  in_position_used_ |= 0b0011;
  a_.OpFToU(dxbc::Dest::R(temp, 0b0011), dxbc::Src::V1D(in_reg_ps_position_));
  a_.OpAnd(dxbc::Dest::R(temp, 0b0010), dxbc::Src::R(temp, dxbc::Src::kYYYY), dxbc::Src::LU(1));
  a_.OpBFI(temp_x_dest, dxbc::Src::LU(1), dxbc::Src::LU(1), temp_x_src,
           dxbc::Src::R(temp, dxbc::Src::kYYYY));
  a_.OpIShL(temp_x_dest, temp_x_src, dxbc::Src::LU(1));
  a_.OpUBFE(temp_x_dest, dxbc::Src::LU(2), temp_x_src, alpha_to_mask_constant_src);
  a_.OpUToF(temp_x_dest, temp_x_src);

  uint32_t coverage_temp = edram_rov_used_ ? system_temp_rov_params_ : temp;
  uint32_t coverage_temp_component = edram_rov_used_ ? 0 : 2;

  a_.OpIf(true, LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                                   offsetof(SystemConstants, sample_count_log2), dxbc::Src::kYYYY));
  {
    a_.OpIf(true,
            LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                               offsetof(SystemConstants, sample_count_log2), dxbc::Src::kXXXX));

    CompletePixelShader_AlphaToMaskSample(true, 0, 0.75f, temp_x_src, 1.0f / 16.0f, coverage_temp,
                                          coverage_temp_component, temp, 1);
    CompletePixelShader_AlphaToMaskSample(false, 1, 0.25f, temp_x_src, 1.0f / 16.0f, coverage_temp,
                                          coverage_temp_component, temp, 1);
    CompletePixelShader_AlphaToMaskSample(false, 2, 0.5f, temp_x_src, 1.0f / 16.0f, coverage_temp,
                                          coverage_temp_component, temp, 1);
    CompletePixelShader_AlphaToMaskSample(false, 3, 1.0f, temp_x_src, 1.0f / 16.0f, coverage_temp,
                                          coverage_temp_component, temp, 1);

    a_.OpElse();
    CompletePixelShader_AlphaToMaskSample(true, (!edram_rov_used_ && msaa_2x_supported_) ? 1 : 0,
                                          0.5f, temp_x_src, 1.0f / 8.0f, coverage_temp,
                                          coverage_temp_component, temp, 1);
    CompletePixelShader_AlphaToMaskSample(false, edram_rov_used_ ? 1 : (msaa_2x_supported_ ? 0 : 3),
                                          1.0f, temp_x_src, 1.0f / 8.0f, coverage_temp,
                                          coverage_temp_component, temp, 1);

    a_.OpEndIf();
  }

  a_.OpElse();
  CompletePixelShader_AlphaToMaskSample(true, 0, 1.0f, temp_x_src, 1.0f / 4.0f, coverage_temp,
                                        coverage_temp_component, temp, 1);

  a_.OpEndIf();

  if (edram_rov_used_) {
    a_.OpAnd(temp_x_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
             dxbc::Src::LU(0b11111111));
    a_.OpRetC(false, temp_x_src);
  } else {
    dxbc::Src coverage_src(dxbc::Src::R(coverage_temp, coverage_temp_component));
    if (zpd_coverage_temp != UINT32_MAX) {
      a_.OpAnd(dxbc::Dest::R(zpd_coverage_temp, 0b0001),
               dxbc::Src::R(zpd_coverage_temp, dxbc::Src::kXXXX), coverage_src);
    }
    a_.OpDiscard(false, coverage_src);
    a_.OpMov(dxbc::Dest::OMask(), coverage_src);
  }

  PopSystemTemp();

  a_.OpEndIf();
}

void DxbcShaderTranslator::RTV_AddMSAASamplesToZPDTotal(dxbc::Src coverage_src) {
  if (uav_index_zpd_counter_ == kBindingIndexUnallocated) {
    uav_index_zpd_counter_ = uav_count_++;
  }

  uint32_t temp = PushSystemTemp();
  dxbc::Dest temp_x_dest(dxbc::Dest::R(temp, 0b0001));
  dxbc::Src temp_x_src(dxbc::Src::R(temp, dxbc::Src::kXXXX));
  dxbc::Dest temp_y_dest(dxbc::Dest::R(temp, 0b0010));
  dxbc::Src temp_y_src(dxbc::Src::R(temp, dxbc::Src::kYYYY));
  dxbc::Dest temp_z_dest(dxbc::Dest::R(temp, 0b0100));
  dxbc::Src temp_z_src(dxbc::Src::R(temp, dxbc::Src::kZZZZ));

  dxbc::Src counter_index_src(LoadSystemConstant(SystemConstants::Index::kZpdCounterIndex,
                                                 offsetof(SystemConstants, zpd_counter_index),
                                                 dxbc::Src::kXXXX));

  a_.OpINE(temp_z_dest, counter_index_src, dxbc::Src::LU(UINT32_MAX));
  a_.OpIf(true, temp_z_src);
  {
    a_.OpUMul(dxbc::Dest::Null(), temp_y_dest, counter_index_src,
              dxbc::Src::LU(XenosZPDReport::kCounterSizeBytes));
    a_.OpCountBits(temp_x_dest, coverage_src);

    if (IsSampleRate()) {
      a_.OpFirstBitLo(temp_z_dest, coverage_src);
      a_.OpIEq(temp_z_dest, dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kYYYY),
               temp_z_src);
      a_.OpAnd(temp_x_dest, temp_x_src, temp_z_src);
    }

    a_.OpIf(true, temp_x_src);
    {
      a_.OpAtomicIAdd(dxbc::Dest::U(uav_index_zpd_counter_, uint32_t(UAVRegister::kZpdCounter), 0),
                      temp_y_src, 0b0001, temp_x_src);
    }
    a_.OpEndIf();
  }
  a_.OpEndIf();

  PopSystemTemp();
}

void DxbcShaderTranslator::CompletePixelShader() {
  uint32_t zpd_coverage_temp = UINT32_MAX;
  if (GetDxbcShaderModification().pixel.zpd_total) {
    zpd_coverage_temp = PushSystemTemp();
    a_.OpMov(dxbc::Dest::R(zpd_coverage_temp, 0b0001), dxbc::Src::VCoverage());
  }

  if (is_depth_only_pixel_shader_) {
    if (edram_rov_used_) {
      CompletePixelShader_WriteToROV();
    } else {
      if (zpd_coverage_temp != UINT32_MAX) {
        RTV_AddMSAASamplesToZPDTotal(dxbc::Src::R(zpd_coverage_temp, dxbc::Src::kXXXX));
      }
      CompletePixelShader_DSV_DepthTo24Bit();
    }
    if (zpd_coverage_temp != UINT32_MAX) {
      PopSystemTemp();
    }
    return;
  }

  if (current_shader().writes_color_target(0) && !IsForceEarlyDepthStencilGlobalFlagEnabled()) {
    if (edram_rov_used_) {
      uint32_t rt_0_written_temp = PushSystemTemp();
      a_.OpAnd(dxbc::Dest::R(rt_0_written_temp, 0b0001),
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX), dxbc::Src::LU(1 << 8));
      a_.OpIf(true, dxbc::Src::R(rt_0_written_temp, dxbc::Src::kXXXX));

      PopSystemTemp();
    }

    uint32_t alpha_test_temp = PushSystemTemp();
    dxbc::Dest alpha_test_mask_dest(dxbc::Dest::R(alpha_test_temp, 0b0001));
    dxbc::Src alpha_test_mask_src(dxbc::Src::R(alpha_test_temp, dxbc::Src::kXXXX));
    dxbc::Dest alpha_test_op_dest(dxbc::Dest::R(alpha_test_temp, 0b0010));
    dxbc::Src alpha_test_op_src(dxbc::Src::R(alpha_test_temp, dxbc::Src::kYYYY));
    dxbc::Dest alpha_test_fuzzy_diff_dest(dxbc::Dest::R(alpha_test_temp, 0b0100));
    dxbc::Src alpha_test_fuzzy_diff_src(dxbc::Src::R(alpha_test_temp, dxbc::Src::kZZZZ));

    a_.OpUBFE(alpha_test_mask_dest, dxbc::Src::LU(3), dxbc::Src::LU(kSysFlag_AlphaPassIfLess_Shift),
              LoadFlagsSystemConstant());

    a_.OpINE(alpha_test_op_dest, alpha_test_mask_src,
             dxbc::Src::LU(uint32_t(xenos::CompareFunction::kAlways)));

    a_.OpIf(true, alpha_test_op_src);
    {
      dxbc::Src alpha_src(dxbc::Src::R(system_temps_color_[0], dxbc::Src::kWWWW));
      dxbc::Src alpha_test_reference_src(
          LoadSystemConstant(SystemConstants::Index::kAlphaTestReference,
                             offsetof(SystemConstants, alpha_test_reference), dxbc::Src::kXXXX));

      dxbc::Src fuzzy_epsilon = dxbc::Src::LF(1e-3f);

      a_.OpIEq(alpha_test_op_dest, alpha_test_mask_src,
               dxbc::Src::LU(uint32_t(xenos::CompareFunction::kNotEqual)));
      a_.OpIf(true, alpha_test_op_src);
      {
        if (REXCVAR_GET(use_fuzzy_alpha_epsilon)) {
          a_.OpAdd(alpha_test_fuzzy_diff_dest, alpha_src, -alpha_test_reference_src);

          a_.OpLT(alpha_test_mask_dest, alpha_test_fuzzy_diff_src.Abs(), fuzzy_epsilon);
          a_.OpNot(alpha_test_mask_dest, alpha_test_mask_src);
        } else {
          a_.OpNE(alpha_test_mask_dest, alpha_src, alpha_test_reference_src);
        }
      }
      a_.OpElse();
      {
        if (REXCVAR_GET(use_fuzzy_alpha_epsilon)) {
          a_.OpAdd(alpha_test_fuzzy_diff_dest, alpha_src, -fuzzy_epsilon);
          a_.OpLT(alpha_test_op_dest, alpha_test_fuzzy_diff_src, alpha_test_reference_src);
          a_.OpOr(alpha_test_op_dest, alpha_test_op_src, dxbc::Src::LU(~uint32_t(1 << 0)));
          a_.OpAnd(alpha_test_mask_dest, alpha_test_mask_src, alpha_test_op_src);

          a_.OpAdd(alpha_test_fuzzy_diff_dest, alpha_src, -alpha_test_reference_src);
          a_.OpLT(alpha_test_op_dest, alpha_test_fuzzy_diff_src.Abs(), fuzzy_epsilon);
          a_.OpOr(alpha_test_op_dest, alpha_test_op_src, dxbc::Src::LU(~uint32_t(1 << 1)));
          a_.OpAnd(alpha_test_mask_dest, alpha_test_mask_src, alpha_test_op_src);

          a_.OpAdd(alpha_test_fuzzy_diff_dest, alpha_src, fuzzy_epsilon);
          a_.OpLT(alpha_test_op_dest, alpha_test_reference_src, alpha_test_fuzzy_diff_src);
          a_.OpOr(alpha_test_op_dest, alpha_test_op_src, dxbc::Src::LU(~uint32_t(1 << 2)));
          a_.OpAnd(alpha_test_mask_dest, alpha_test_mask_src, alpha_test_op_src);
        } else {
          a_.OpLT(alpha_test_op_dest, alpha_src, alpha_test_reference_src);
          a_.OpOr(alpha_test_op_dest, alpha_test_op_src, dxbc::Src::LU(~uint32_t(1 << 0)));
          a_.OpAnd(alpha_test_mask_dest, alpha_test_mask_src, alpha_test_op_src);

          a_.OpEq(alpha_test_op_dest, alpha_src, alpha_test_reference_src);
          a_.OpOr(alpha_test_op_dest, alpha_test_op_src, dxbc::Src::LU(~uint32_t(1 << 1)));
          a_.OpAnd(alpha_test_mask_dest, alpha_test_mask_src, alpha_test_op_src);

          a_.OpLT(alpha_test_op_dest, alpha_test_reference_src, alpha_src);
          a_.OpOr(alpha_test_op_dest, alpha_test_op_src, dxbc::Src::LU(~uint32_t(1 << 2)));
          a_.OpAnd(alpha_test_mask_dest, alpha_test_mask_src, alpha_test_op_src);
        }
      }

      a_.OpEndIf();

      if (edram_rov_used_) {
        a_.OpRetC(false, alpha_test_mask_src);
      } else {
        a_.OpDiscard(false, alpha_test_mask_src);
      }
    }

    a_.OpEndIf();

    PopSystemTemp();

    CompletePixelShader_AlphaToMask(zpd_coverage_temp);

    if (edram_rov_used_) {
      a_.OpEndIf();
    }
  }

  if (zpd_coverage_temp != UINT32_MAX) {
    RTV_AddMSAASamplesToZPDTotal(dxbc::Src::R(zpd_coverage_temp, dxbc::Src::kXXXX));
    PopSystemTemp();
  }

  if (edram_rov_used_) {
    CompletePixelShader_WriteToROV();
  } else {
    CompletePixelShader_WriteToRTVs();
    CompletePixelShader_DSV_DepthTo24Bit();
  }
}

void DxbcShaderTranslator::PreClampedFloat32To7e3(dxbc::Assembler& a, uint32_t f10_temp,
                                                  uint32_t f10_temp_component, uint32_t f32_temp,
                                                  uint32_t f32_temp_component, uint32_t temp_temp,
                                                  uint32_t temp_temp_component) {
  assert_true(temp_temp != f10_temp || temp_temp_component != f10_temp_component);
  assert_true(temp_temp != f32_temp || temp_temp_component != f32_temp_component);

  dxbc::Dest f10_dest(dxbc::Dest::R(f10_temp, 1 << f10_temp_component));
  dxbc::Src f10_src(dxbc::Src::R(f10_temp).Select(f10_temp_component));
  dxbc::Src f32_src(dxbc::Src::R(f32_temp).Select(f32_temp_component));
  dxbc::Dest temp_dest(dxbc::Dest::R(temp_temp, 1 << temp_temp_component));
  dxbc::Src temp_src(dxbc::Src::R(temp_temp).Select(temp_temp_component));

  a.OpULT(temp_dest, f32_src, dxbc::Src::LU(0x3E800000));

  a.OpIf(true, temp_src);
  {
    a.OpUShR(temp_dest, f32_src, dxbc::Src::LU(23));

    a.OpIAdd(temp_dest, dxbc::Src::LI(125), -temp_src);

    a.OpUMin(temp_dest, temp_src, dxbc::Src::LU(24));

    a.OpBFI(f10_dest, dxbc::Src::LU(9), dxbc::Src::LU(23), dxbc::Src::LU(1), f32_src);

    a.OpUShR(f10_dest, f10_src, temp_src);
  }

  a.OpElse();
  { a.OpIAdd(f10_dest, f32_src, dxbc::Src::LU(0xC2000000u)); }

  a.OpEndIf();

  a.OpUBFE(temp_dest, dxbc::Src::LU(1), dxbc::Src::LU(16), f10_src);

  a.OpIAdd(f10_dest, f10_src, dxbc::Src::LU(0x7FFF));

  a.OpIAdd(f10_dest, f10_src, temp_src);

  a.OpUBFE(f10_dest, dxbc::Src::LU(10), dxbc::Src::LU(16), f10_src);
}

void DxbcShaderTranslator::UnclampedFloat32To7e3(dxbc::Assembler& a, uint32_t f10_temp,
                                                 uint32_t f10_temp_component, uint32_t f32_temp,
                                                 uint32_t f32_temp_component, uint32_t temp_temp,
                                                 uint32_t temp_temp_component) {
  a.OpMax(dxbc::Dest::R(f10_temp, 1 << f10_temp_component),
          dxbc::Src::R(f32_temp).Select(f32_temp_component), dxbc::Src::LF(0.0f));
  a.OpMin(dxbc::Dest::R(f10_temp, 1 << f10_temp_component),
          dxbc::Src::R(f10_temp).Select(f10_temp_component), dxbc::Src::LF(31.875f));
  PreClampedFloat32To7e3(a, f10_temp, f10_temp_component, f10_temp, f10_temp_component, temp_temp,
                         temp_temp_component);
}

void DxbcShaderTranslator::Float7e3To32(dxbc::Assembler& a, const dxbc::Dest& f32,
                                        uint32_t f10_temp, uint32_t f10_temp_component,
                                        uint32_t f10_shift, uint32_t temp1_temp,
                                        uint32_t temp1_temp_component, uint32_t temp2_temp,
                                        uint32_t temp2_temp_component) {
  assert_true(f10_shift <= (32 - 10));
  assert_true(temp1_temp != temp2_temp || temp1_temp_component != temp2_temp_component);

  dxbc::Dest exponent_dest(dxbc::Dest::R(temp1_temp, 1 << temp1_temp_component));
  dxbc::Src exponent_src(dxbc::Src::R(temp1_temp).Select(temp1_temp_component));
  dxbc::Dest mantissa_dest(dxbc::Dest::R(temp2_temp, 1 << temp2_temp_component));
  dxbc::Src mantissa_src(dxbc::Src::R(temp2_temp).Select(temp2_temp_component));

  if (!(f10_temp == temp1_temp && f10_temp_component == temp1_temp_component)) {
    a.OpUBFE(exponent_dest, dxbc::Src::LU(3), dxbc::Src::LU(f10_shift + 7),
             dxbc::Src::R(f10_temp).Select(f10_temp_component));
  }

  a.OpUBFE(mantissa_dest, dxbc::Src::LU(7), dxbc::Src::LU(f10_shift),
           dxbc::Src::R(f10_temp).Select(f10_temp_component));
  if (f10_temp == temp1_temp && f10_temp_component == temp1_temp_component) {
    a.OpUBFE(exponent_dest, dxbc::Src::LU(3), dxbc::Src::LU(f10_shift + 7),
             dxbc::Src::R(f10_temp).Select(f10_temp_component));
  }

  a.OpIf(false, exponent_src);
  {
    a.OpIf(true, mantissa_src);
    {
      a.OpFirstBitHi(exponent_dest, mantissa_src);

      a.OpIAdd(exponent_dest, exponent_src, dxbc::Src::LI(7 - 31));

      a.OpIShL(mantissa_dest, mantissa_src, exponent_src);

      a.OpIAdd(exponent_dest, dxbc::Src::LI(1), -exponent_src);
    }

    a.OpElse();
    { a.OpMov(exponent_dest, dxbc::Src::LI(-124)); }

    a.OpEndIf();
  }

  a.OpEndIf();

  a.OpIMAd(exponent_dest, exponent_src, dxbc::Src::LI(1 << 23), dxbc::Src::LI(124 << 23));

  a.OpBFI(f32, dxbc::Src::LU(7), dxbc::Src::LU(23 - 7), mantissa_src, exponent_src);
}

void DxbcShaderTranslator::PreClampedDepthTo20e4(dxbc::Assembler& a, uint32_t f24_temp,
                                                 uint32_t f24_temp_component, uint32_t f32_temp,
                                                 uint32_t f32_temp_component, uint32_t temp_temp,
                                                 uint32_t temp_temp_component,
                                                 bool round_to_nearest_even,
                                                 bool remap_from_0_to_0_5) {
  assert_true(temp_temp != f24_temp || temp_temp_component != f24_temp_component);
  assert_true(temp_temp != f32_temp || temp_temp_component != f32_temp_component);

  dxbc::Dest f24_dest(dxbc::Dest::R(f24_temp, 1 << f24_temp_component));
  dxbc::Src f24_src(dxbc::Src::R(f24_temp).Select(f24_temp_component));
  dxbc::Src f32_src(dxbc::Src::R(f32_temp).Select(f32_temp_component));
  dxbc::Dest temp_dest(dxbc::Dest::R(temp_temp, 1 << temp_temp_component));
  dxbc::Src temp_src(dxbc::Src::R(temp_temp).Select(temp_temp_component));

  uint32_t remap_bias = uint32_t(remap_from_0_to_0_5);

  a.OpULT(temp_dest, f32_src, dxbc::Src::LU(0x38800000 - (remap_bias << 23)));

  a.OpIf(true, temp_src);
  {
    a.OpUShR(temp_dest, f32_src, dxbc::Src::LU(23));

    a.OpIAdd(temp_dest, dxbc::Src::LI(113 - remap_bias), -temp_src);

    a.OpUMin(temp_dest, temp_src, dxbc::Src::LU(24));

    a.OpBFI(f24_dest, dxbc::Src::LU(9), dxbc::Src::LU(23), dxbc::Src::LU(1), f32_src);

    a.OpUShR(f24_dest, f24_src, temp_src);
  }

  a.OpElse();
  { a.OpIAdd(f24_dest, f32_src, dxbc::Src::LU(0xC8000000u + (remap_bias << 23))); }

  a.OpEndIf();

  if (round_to_nearest_even) {
    a.OpUBFE(temp_dest, dxbc::Src::LU(1), dxbc::Src::LU(3), f24_src);

    a.OpIAdd(f24_dest, f24_src, dxbc::Src::LU(3));

    a.OpIAdd(f24_dest, f24_src, temp_src);
  }

  a.OpUBFE(f24_dest, dxbc::Src::LU(24), dxbc::Src::LU(3), f24_src);
}

void DxbcShaderTranslator::Depth20e4To32(dxbc::Assembler& a, const dxbc::Dest& f32,
                                         uint32_t f24_temp, uint32_t f24_temp_component,
                                         uint32_t f24_shift, uint32_t temp1_temp,
                                         uint32_t temp1_temp_component, uint32_t temp2_temp,
                                         uint32_t temp2_temp_component, bool remap_to_0_to_0_5) {
  assert_true(f24_shift <= (32 - 24));
  assert_true(temp1_temp != temp2_temp || temp1_temp_component != temp2_temp_component);

  dxbc::Dest exponent_dest(dxbc::Dest::R(temp1_temp, 1 << temp1_temp_component));
  dxbc::Src exponent_src(dxbc::Src::R(temp1_temp).Select(temp1_temp_component));
  dxbc::Dest mantissa_dest(dxbc::Dest::R(temp2_temp, 1 << temp2_temp_component));
  dxbc::Src mantissa_src(dxbc::Src::R(temp2_temp).Select(temp2_temp_component));

  uint32_t remap_bias = uint32_t(remap_to_0_to_0_5);

  if (!(f24_temp == temp1_temp && f24_temp_component == temp1_temp_component)) {
    a.OpUBFE(exponent_dest, dxbc::Src::LU(4), dxbc::Src::LU(f24_shift + 20),
             dxbc::Src::R(f24_temp).Select(f24_temp_component));
  }

  a.OpUBFE(mantissa_dest, dxbc::Src::LU(20), dxbc::Src::LU(f24_shift),
           dxbc::Src::R(f24_temp).Select(f24_temp_component));
  if (f24_temp == temp1_temp && f24_temp_component == temp1_temp_component) {
    a.OpUBFE(exponent_dest, dxbc::Src::LU(4), dxbc::Src::LU(f24_shift + 20),
             dxbc::Src::R(f24_temp).Select(f24_temp_component));
  }

  a.OpIf(false, exponent_src);
  {
    a.OpIf(true, mantissa_src);
    {
      a.OpFirstBitHi(exponent_dest, mantissa_src);

      a.OpIAdd(exponent_dest, exponent_src, dxbc::Src::LI(20 - 31));

      a.OpIShL(mantissa_dest, mantissa_src, exponent_src);

      a.OpIAdd(exponent_dest, dxbc::Src::LI(1), -exponent_src);
    }

    a.OpElse();
    { a.OpMov(exponent_dest, dxbc::Src::LI(-int32_t(112 - remap_bias))); }

    a.OpEndIf();
  }

  a.OpEndIf();

  a.OpIMAd(exponent_dest, exponent_src, dxbc::Src::LI(1 << 23),
           dxbc::Src::LI((112 - remap_bias) << 23));

  a.OpBFI(f32, dxbc::Src::LU(20), dxbc::Src::LU(23 - 20), mantissa_src, exponent_src);
}

}
