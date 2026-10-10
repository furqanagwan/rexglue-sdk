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

void DxbcShaderTranslator::StartPixelShader_LoadROVParameters() {
  bool any_color_targets_written = current_shader().writes_color_targets() != 0;

  in_position_used_ |= 0b0011;
  a_.OpFToU(dxbc::Dest::R(system_temp_rov_params_, 0b0011), dxbc::Src::V1D(in_reg_ps_position_));

  {
    uint32_t scale_x = draw_resolution_scale_x_;
    uint32_t scale_y = draw_resolution_scale_y_;
    bool resolution_scaled = scale_x > 1 || scale_y > 1;
    uint32_t guest_pixel_temp = UINT32_MAX;
    if (resolution_scaled) {
      guest_pixel_temp = PushSystemTemp();
    }
    dxbc::Src guest_x(resolution_scaled ? dxbc::Src::R(guest_pixel_temp, dxbc::Src::kXXXX)
                                        : dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX));
    dxbc::Src guest_y(resolution_scaled ? dxbc::Src::R(guest_pixel_temp, dxbc::Src::kYYYY)
                                        : dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY));
    auto emit_guest_pixel_split = [&]() {
      if (!resolution_scaled) {
        return;
      }

      a_.OpUDiv(dxbc::Dest::R(guest_pixel_temp, 0b0011), dxbc::Dest::R(guest_pixel_temp, 0b1100),
                dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXYXY),
                dxbc::Src::LU(scale_x, scale_y, scale_x, scale_y));
    };
    auto emit_host_pixel_restore = [&]() {
      if (!resolution_scaled) {
        return;
      }
      a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b0011),
                dxbc::Src::R(system_temp_rov_params_), dxbc::Src::LU(scale_x, scale_y, 1, 1),
                dxbc::Src::R(guest_pixel_temp, 0b1110));
    };

    a_.OpIf(true,
            LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                               offsetof(SystemConstants, sample_count_log2), dxbc::Src::kXXXX));
    {
      emit_guest_pixel_split();

      a_.OpUShR(dxbc::Dest::R(system_temp_rov_params_, 0b0100), guest_x, dxbc::Src::LU(1));

      a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b1000), guest_x, dxbc::Src::LU(1));

      a_.OpBFI(dxbc::Dest::R(system_temp_rov_params_, 0b0001), dxbc::Src::LU(30), dxbc::Src::LU(2),
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ),
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW));

      a_.OpUShR(dxbc::Dest::R(system_temp_rov_params_, 0b0100), guest_y, dxbc::Src::LU(1));

      a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b1000), guest_y, dxbc::Src::LU(1));

      a_.OpBFI(dxbc::Dest::R(system_temp_rov_params_, 0b0010), dxbc::Src::LU(30), dxbc::Src::LU(2),
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ),
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW));
      emit_host_pixel_restore();
    }
    a_.OpElse();
    {
      a_.OpIf(true,
              LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                                 offsetof(SystemConstants, sample_count_log2), dxbc::Src::kYYYY));
      {
        emit_guest_pixel_split();

        a_.OpUShR(dxbc::Dest::R(system_temp_rov_params_, 0b0100), guest_x, dxbc::Src::LU(1));

        a_.OpBFI(dxbc::Dest::R(system_temp_rov_params_, 0b0100), dxbc::Src::LU(1), dxbc::Src::LU(1),
                 dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ), guest_y);

        a_.OpUShR(dxbc::Dest::R(system_temp_rov_params_, 0b1000), guest_y, dxbc::Src::LU(1));

        a_.OpBFI(dxbc::Dest::R(system_temp_rov_params_, 0b0010), dxbc::Src::LU(30),
                 dxbc::Src::LU(2), dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW),
                 dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ));

        a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b0001), guest_x,
                 dxbc::Src::LU(~uint32_t(2)));
        emit_host_pixel_restore();
      }
      a_.OpEndIf();
    }
    a_.OpEndIf();
    if (resolution_scaled) {
      PopSystemTemp();
    }
  }

  uint32_t tile_width = xenos::kEdramTileWidthSamples * draw_resolution_scale_x_;
  uint32_t tile_or_tile_half_width = tile_width >> uint32_t(any_color_targets_written);
  uint32_t tile_height = xenos::kEdramTileHeightSamples * draw_resolution_scale_y_;

  a_.OpUDiv(
      dxbc::Dest::R(system_temp_rov_params_, 0b1100),
      dxbc::Dest::R(system_temp_rov_params_, 0b0011),
      dxbc::Src::R(system_temp_rov_params_, 0b01000100),
      dxbc::Src::LU(tile_or_tile_half_width, tile_height, tile_or_tile_half_width, tile_height));

  a_.OpUMul(dxbc::Dest::Null(), dxbc::Dest::R(system_temp_rov_params_, 0b0010),
            dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), dxbc::Src::LU(tile_width));

  uint32_t tile_size = tile_width * tile_height;
  uint32_t tile_half_width = tile_width >> 1;
  if (any_color_targets_written) {
    uint32_t rov_address_temp = PushSystemTemp();

    a_.OpUMul(dxbc::Dest::Null(), dxbc::Dest::R(system_temp_rov_params_, 0b1000),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW),
              LoadSystemConstant(SystemConstants::Index::kEdram32bppTilePitchDwordsScaled,
                                 offsetof(SystemConstants, edram_32bpp_tile_pitch_dwords_scaled),
                                 dxbc::Src::kXXXX));

    a_.OpUShR(dxbc::Dest::R(rov_address_temp, 0b0001),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ), dxbc::Src::LU(1));

    a_.OpUMAd(dxbc::Dest::R(rov_address_temp, 0b0001),
              dxbc::Src::R(rov_address_temp, dxbc::Src::kXXXX), dxbc::Src::LU(tile_size),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY));

    a_.OpIAdd(dxbc::Dest::R(rov_address_temp, 0b0001),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW),
              dxbc::Src::R(rov_address_temp, dxbc::Src::kXXXX));

    a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ), dxbc::Src::LU(tile_size),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY));

    a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b1000),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW), dxbc::Src::LU(2),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY));

    a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b1000),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX), dxbc::Src::LU(2),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW));

    a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
             dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ), dxbc::Src::LU(1));

    a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b0100),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              dxbc::Src::LU(tile_half_width),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX));

    a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0100),
              dxbc::Src::R(rov_address_temp, dxbc::Src::kXXXX),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ));

    a_.OpMovC(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              dxbc::Src::LI(-int32_t(tile_half_width)), dxbc::Src::LI(int32_t(tile_half_width)));

    a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY));

    PopSystemTemp();
  } else {
    a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b0100),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ), dxbc::Src::LU(tile_size),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY));

    a_.OpUMAd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW),
              LoadSystemConstant(SystemConstants::Index::kEdram32bppTilePitchDwordsScaled,
                                 offsetof(SystemConstants, edram_32bpp_tile_pitch_dwords_scaled),
                                 dxbc::Src::kXXXX),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ));

    a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX));

    a_.OpUGE(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
             dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
             dxbc::Src::LU(tile_half_width));

    a_.OpMovC(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
              dxbc::Src::LI(-int32_t(tile_half_width)), dxbc::Src::LI(int32_t(tile_half_width)));

    a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX));
  }

  a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
            dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
            LoadSystemConstant(SystemConstants::Index::kEdramDepthBaseDwordsScaled,
                               offsetof(SystemConstants, edram_depth_base_dwords_scaled),
                               dxbc::Src::kXXXX));

  a_.OpUDiv(dxbc::Dest::Null(), dxbc::Dest::R(system_temp_rov_params_, 0b0010),
            dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
            dxbc::Src::LU(tile_size * xenos::kEdramTileCount));

  a_.OpIf(true, LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                                   offsetof(SystemConstants, sample_count_log2), dxbc::Src::kXXXX));
  { a_.OpMov(dxbc::Dest::R(system_temp_rov_params_, 0b0001), dxbc::Src::VCoverage()); }

  a_.OpElse();
  {
    a_.OpUBFE(dxbc::Dest::R(system_temp_rov_params_, 0b0001), dxbc::Src::LU(1), dxbc::Src::LU(3),
              dxbc::Src::VCoverage());

    a_.OpBFI(dxbc::Dest::R(system_temp_rov_params_, 0b0001), dxbc::Src::LU(31), dxbc::Src::LU(1),
             dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX), dxbc::Src::VCoverage());
  }

  a_.OpEndIf();
}

void DxbcShaderTranslator::ROV_DepthStencilTest() {
  uint32_t temp = PushSystemTemp();
  dxbc::Dest temp_x_dest(dxbc::Dest::R(temp, 0b0001));
  dxbc::Src temp_x_src(dxbc::Src::R(temp, dxbc::Src::kXXXX));
  dxbc::Dest temp_y_dest(dxbc::Dest::R(temp, 0b0010));
  dxbc::Src temp_y_src(dxbc::Src::R(temp, dxbc::Src::kYYYY));
  dxbc::Dest temp_z_dest(dxbc::Dest::R(temp, 0b0100));
  dxbc::Src temp_z_src(dxbc::Src::R(temp, dxbc::Src::kZZZZ));
  dxbc::Dest temp_w_dest(dxbc::Dest::R(temp, 0b1000));
  dxbc::Src temp_w_src(dxbc::Src::R(temp, dxbc::Src::kWWWW));

  a_.OpAnd(temp_x_dest, LoadFlagsSystemConstant(), dxbc::Src::LU(kSysFlag_ROVDepthStencil));

  a_.OpIf(true, temp_x_src);

  bool shader_writes_depth = current_shader().writes_depth();
  bool depth_stencil_early = ROV_IsDepthStencilEarly();

  dxbc::Src z_ddx_src(dxbc::Src::LF(0.0f)), z_ddy_src(dxbc::Src::LF(0.0f));

  if (shader_writes_depth) {
    ROV_DepthTo24Bit(system_temp_depth_stencil_, 0, system_temp_depth_stencil_, 0, temp, 0);
  } else {
    dxbc::Src in_position_z(dxbc::Src::V1D(in_reg_ps_position_, dxbc::Src::kZZZZ));

    if (depth_stencil_early) {
      z_ddx_src = dxbc::Src::R(temp, dxbc::Src::kXXXX);
      z_ddy_src = dxbc::Src::R(temp, dxbc::Src::kYYYY);

      in_position_used_ |= 0b0100;
      a_.OpDerivRTXCoarse(temp_x_dest, in_position_z);
      a_.OpDerivRTYCoarse(temp_y_dest, in_position_z);
    } else {
      assert_true(system_temp_depth_stencil_ != UINT32_MAX);
      z_ddx_src = dxbc::Src::R(system_temp_depth_stencil_, dxbc::Src::kXXXX);
      z_ddy_src = dxbc::Src::R(system_temp_depth_stencil_, dxbc::Src::kYYYY);
    }

    a_.OpMax(temp_z_dest, z_ddx_src.Abs(), z_ddy_src.Abs());

    in_front_face_used_ = true;
    a_.OpIf(true, dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kXXXX));

    a_.OpMAd(
        temp_z_dest, temp_z_src,
        LoadSystemConstant(SystemConstants::Index::kEdramPolyOffsetFront,
                           offsetof(SystemConstants, edram_poly_offset_front), dxbc::Src::kXXXX),
        LoadSystemConstant(SystemConstants::Index::kEdramPolyOffsetFront,
                           offsetof(SystemConstants, edram_poly_offset_front), dxbc::Src::kYYYY));
    a_.OpElse();

    a_.OpMAd(
        temp_z_dest, temp_z_src,
        LoadSystemConstant(SystemConstants::Index::kEdramPolyOffsetBack,
                           offsetof(SystemConstants, edram_poly_offset_back), dxbc::Src::kXXXX),
        LoadSystemConstant(SystemConstants::Index::kEdramPolyOffsetBack,
                           offsetof(SystemConstants, edram_poly_offset_back), dxbc::Src::kYYYY));
    a_.OpEndIf();

    in_position_used_ |= 0b0100;
    a_.OpAdd(temp_z_dest, temp_z_src, in_position_z);
  }

  for (uint32_t i = 0; i < 4; ++i) {
    dxbc::Dest sample_depth_stencil_dest(
        depth_stencil_early ? dxbc::Dest::R(system_temp_depth_stencil_, 1 << i) : temp_w_dest);
    dxbc::Src sample_depth_stencil_src(
        depth_stencil_early ? dxbc::Src::R(system_temp_depth_stencil_).Select(i) : temp_w_src);

    a_.OpAnd(temp_w_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
             dxbc::Src::LU(1 << i));

    a_.OpIf(true, temp_w_src);

    uint32_t sample_temp = PushSystemTemp();
    dxbc::Dest sample_temp_x_dest(dxbc::Dest::R(sample_temp, 0b0001));
    dxbc::Src sample_temp_x_src(dxbc::Src::R(sample_temp, dxbc::Src::kXXXX));
    dxbc::Dest sample_temp_y_dest(dxbc::Dest::R(sample_temp, 0b0010));
    dxbc::Src sample_temp_y_src(dxbc::Src::R(sample_temp, dxbc::Src::kYYYY));
    dxbc::Dest sample_temp_z_dest(dxbc::Dest::R(sample_temp, 0b0100));
    dxbc::Src sample_temp_z_src(dxbc::Src::R(sample_temp, dxbc::Src::kZZZZ));
    dxbc::Dest sample_temp_w_dest(dxbc::Dest::R(sample_temp, 0b1000));
    dxbc::Src sample_temp_w_src(dxbc::Src::R(sample_temp, dxbc::Src::kWWWW));

    if (shader_writes_depth) {
      assert_false(depth_stencil_early);
      a_.OpMov(sample_depth_stencil_dest,
               dxbc::Src::R(system_temp_depth_stencil_, dxbc::Src::kXXXX));
    } else {
      switch (i) {
        case 0:

          a_.OpMAd(sample_depth_stencil_dest, z_ddx_src,
                   dxbc::Src::LF(draw_util::kD3D10StandardSamplePositions4x[0][0] * (1.0f / 16.0f)),
                   temp_z_src);
          a_.OpMAd(sample_depth_stencil_dest, z_ddy_src,
                   dxbc::Src::LF(draw_util::kD3D10StandardSamplePositions4x[0][1] * (1.0f / 16.0f)),
                   sample_depth_stencil_src);

          a_.OpMovC(
              sample_depth_stencil_dest,
              LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                                 offsetof(SystemConstants, sample_count_log2), dxbc::Src::kYYYY),
              sample_depth_stencil_src, temp_z_src, true);
          break;
        case 1:

          a_.OpIf(true, LoadSystemConstant(SystemConstants::Index::kSampleCountLog2,
                                           offsetof(SystemConstants, sample_count_log2),
                                           dxbc::Src::kXXXX));

          a_.OpMAd(sample_depth_stencil_dest, z_ddx_src,
                   dxbc::Src::LF(draw_util::kD3D10StandardSamplePositions4x[1][0] * (1.0f / 16.0f)),
                   temp_z_src);
          a_.OpMAd(sample_depth_stencil_dest, z_ddy_src,
                   dxbc::Src::LF(draw_util::kD3D10StandardSamplePositions4x[1][1] * (1.0f / 16.0f)),
                   sample_depth_stencil_src, true);
          a_.OpElse();

          a_.OpMAd(sample_depth_stencil_dest, z_ddx_src,
                   dxbc::Src::LF(draw_util::kD3D10StandardSamplePositions4x[3][0] * (1.0f / 16.0f)),
                   temp_z_src);
          a_.OpMAd(sample_depth_stencil_dest, z_ddy_src,
                   dxbc::Src::LF(draw_util::kD3D10StandardSamplePositions4x[3][1] * (1.0f / 16.0f)),
                   sample_depth_stencil_src, true);
          a_.OpEndIf();
          break;
        default: {
          const int8_t* sample_position = draw_util::kD3D10StandardSamplePositions4x[i];
          a_.OpMAd(sample_depth_stencil_dest, z_ddx_src,
                   dxbc::Src::LF(sample_position[0] * (1.0f / 16.0f)), temp_z_src);
          a_.OpMAd(sample_depth_stencil_dest, z_ddy_src,
                   dxbc::Src::LF(sample_position[1] * (1.0f / 16.0f)), sample_depth_stencil_src,
                   true);
        } break;
      }

      ROV_DepthTo24Bit(sample_depth_stencil_src.index_1d_.index_,
                       sample_depth_stencil_src.swizzle_ & 3,
                       sample_depth_stencil_src.index_1d_.index_,
                       sample_depth_stencil_src.swizzle_ & 3, sample_temp, 0);
    }

    if (uav_index_edram_ == kBindingIndexUnallocated) {
      uav_index_edram_ = uav_count_++;
    }
    a_.OpLdUAVTyped(
        sample_temp_x_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), 1,
        dxbc::Src::U(uav_index_edram_, uint32_t(UAVRegister::kEdram), dxbc::Src::kXXXX));

    a_.OpUShR(sample_temp_y_dest, sample_temp_x_src, dxbc::Src::LU(8));

    a_.OpIAdd(sample_temp_z_dest, sample_depth_stencil_src, -sample_temp_y_src);

    a_.OpILT(sample_temp_w_dest, sample_temp_z_src, dxbc::Src::LI(0));

    a_.OpMovC(sample_temp_w_dest, sample_temp_w_src, dxbc::Src::LU(kSysFlag_ROVDepthPassIfLess),
              dxbc::Src::LU(kSysFlag_ROVDepthPassIfGreater));

    a_.OpMovC(sample_temp_z_dest, sample_temp_z_src, sample_temp_w_src,
              dxbc::Src::LU(kSysFlag_ROVDepthPassIfEqual));

    a_.OpAnd(sample_temp_z_dest, sample_temp_z_src, LoadFlagsSystemConstant());

    a_.OpIf(true, sample_temp_z_src);
    {
      a_.OpAnd(sample_temp_z_dest, LoadFlagsSystemConstant(),
               dxbc::Src::LU(kSysFlag_ROVDepthWrite));

      a_.OpMovC(sample_depth_stencil_dest, sample_temp_z_src, sample_depth_stencil_src,
                sample_temp_y_src);
    }

    a_.OpElse();
    {
      if (zpd_full_counters_) {
        a_.OpOr(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
                dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                dxbc::Src::LU(1 << (12 + i)));
      }

      a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
               dxbc::Src::LU(~uint32_t(1 << i)));
    }
    a_.OpEndIf();

    a_.OpBFI(sample_depth_stencil_dest, dxbc::Src::LU(24), dxbc::Src::LU(8),
             sample_depth_stencil_src, sample_temp_x_src);

    a_.OpAnd(sample_temp_y_dest, LoadFlagsSystemConstant(), dxbc::Src::LU(kSysFlag_ROVStencilTest));

    a_.OpIf(true, sample_temp_y_src);
    {
      in_front_face_used_ = true;
      a_.OpIf(true, dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kXXXX));
      for (uint32_t j = 0; j < 2; ++j) {
        if (j) {
          a_.OpElse();
        }
        dxbc::Src stencil_read_mask_src(
            LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                               j ? offsetof(SystemConstants, edram_stencil_back_read_mask)
                                 : offsetof(SystemConstants, edram_stencil_front_read_mask),
                               dxbc::Src::kXXXX));

        a_.OpAnd(sample_temp_y_dest,
                 LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                    j ? offsetof(SystemConstants, edram_stencil_back_reference)
                                      : offsetof(SystemConstants, edram_stencil_front_reference),
                                    dxbc::Src::kXXXX),
                 stencil_read_mask_src);

        a_.OpAnd(sample_temp_z_dest, sample_temp_x_src, stencil_read_mask_src);
      }

      a_.OpEndIf();

      a_.OpIAdd(sample_temp_y_dest, sample_temp_y_src, -sample_temp_z_src);

      a_.OpILT(sample_temp_z_dest, sample_temp_y_src, dxbc::Src::LI(0));

      a_.OpMovC(sample_temp_z_dest, sample_temp_z_src,
                dxbc::Src::LU(uint32_t(xenos::CompareFunction::kLess)),
                dxbc::Src::LU(uint32_t(xenos::CompareFunction::kGreater)));

      a_.OpMovC(sample_temp_y_dest, sample_temp_y_src, sample_temp_z_src,
                dxbc::Src::LU(uint32_t(xenos::CompareFunction::kEqual)));

      in_front_face_used_ = true;
      a_.OpMovC(sample_temp_z_dest,
                dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kXXXX),
                LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                   offsetof(SystemConstants, edram_stencil_front_func_ops),
                                   dxbc::Src::kXXXX),
                LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                   offsetof(SystemConstants, edram_stencil_back_func_ops),
                                   dxbc::Src::kXXXX));

      a_.OpAnd(sample_temp_y_dest, sample_temp_y_src, sample_temp_z_src);

      a_.OpIf(true, sample_temp_y_src);
      {
        a_.OpAnd(sample_temp_y_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                 dxbc::Src::LU(1 << i));

        a_.OpMovC(sample_temp_y_dest, sample_temp_y_src, dxbc::Src::LU(6), dxbc::Src::LU(9));

        a_.OpUBFE(sample_temp_y_dest, dxbc::Src::LU(3), sample_temp_y_src, sample_temp_z_src);
      }

      a_.OpElse();
      {
        a_.OpUBFE(sample_temp_y_dest, dxbc::Src::LU(3), dxbc::Src::LU(3), sample_temp_z_src);
        if (zpd_full_counters_) {
          a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
                   dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                   dxbc::Src::LU(~uint32_t(1 << (12 + i))));
          a_.OpOr(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
                  dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                  dxbc::Src::LU(1 << (16 + i)));
        }

        a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
                 dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                 dxbc::Src::LU(~uint32_t(1 << i)));
      }

      a_.OpEndIf();

      a_.OpSwitch(sample_temp_y_src);
      {
        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kZero)));
        a_.OpMov(sample_temp_y_dest, dxbc::Src::LU(0));
        a_.OpBreak();

        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kReplace)));
        in_front_face_used_ = true;
        a_.OpMovC(sample_temp_y_dest,
                  dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kXXXX),
                  LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                     offsetof(SystemConstants, edram_stencil_front_reference),
                                     dxbc::Src::kXXXX),
                  LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                     offsetof(SystemConstants, edram_stencil_back_reference),
                                     dxbc::Src::kXXXX));
        a_.OpBreak();

        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kIncrementClamp)));
        {
          a_.OpAnd(sample_temp_y_dest, sample_temp_x_src, dxbc::Src::LU(UINT8_MAX));

          a_.OpIAdd(sample_temp_y_dest, sample_temp_y_src, dxbc::Src::LI(1));

          a_.OpIMin(sample_temp_y_dest, sample_temp_y_src, dxbc::Src::LI(UINT8_MAX));
        }
        a_.OpBreak();

        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kDecrementClamp)));
        {
          a_.OpAnd(sample_temp_y_dest, sample_temp_x_src, dxbc::Src::LU(UINT8_MAX));

          a_.OpIAdd(sample_temp_y_dest, sample_temp_y_src, dxbc::Src::LI(-1));

          a_.OpIMax(sample_temp_y_dest, sample_temp_y_src, dxbc::Src::LI(0));
        }
        a_.OpBreak();

        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kInvert)));
        a_.OpNot(sample_temp_y_dest, sample_temp_x_src);
        a_.OpBreak();

        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kIncrementWrap)));
        a_.OpIAdd(sample_temp_y_dest, sample_temp_x_src, dxbc::Src::LI(1));
        a_.OpBreak();

        a_.OpCase(dxbc::Src::LU(uint32_t(xenos::StencilOp::kDecrementWrap)));
        a_.OpIAdd(sample_temp_y_dest, sample_temp_x_src, dxbc::Src::LI(-1));
        a_.OpBreak();

        a_.OpDefault();
        a_.OpMov(sample_temp_y_dest, sample_temp_x_src);
        a_.OpBreak();
      }

      a_.OpEndSwitch();

      in_front_face_used_ = true;
      a_.OpMovC(sample_temp_z_dest,
                dxbc::Src::V1D(in_reg_ps_front_face_sample_index_, dxbc::Src::kXXXX),
                LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                   offsetof(SystemConstants, edram_stencil_front_write_mask),
                                   dxbc::Src::kXXXX),
                LoadSystemConstant(SystemConstants::Index::kEdramStencil,
                                   offsetof(SystemConstants, edram_stencil_back_write_mask),
                                   dxbc::Src::kXXXX));

      a_.OpAnd(sample_temp_y_dest, sample_temp_y_src, sample_temp_z_src);

      a_.OpNot(sample_temp_z_dest, sample_temp_z_src);

      a_.OpAnd(sample_depth_stencil_dest, sample_depth_stencil_src, sample_temp_z_src);

      a_.OpOr(sample_depth_stencil_dest, sample_depth_stencil_src, sample_temp_y_src);
    }

    a_.OpEndIf();

    a_.OpAnd(sample_temp_y_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
             dxbc::Src::LU(1 << i));

    a_.OpIf(false, sample_temp_y_src);
    {
      a_.OpBFI(sample_depth_stencil_dest, dxbc::Src::LU(8), dxbc::Src::LU(0),
               sample_depth_stencil_src, sample_temp_x_src);
    }

    a_.OpEndIf();

    a_.OpINE(sample_temp_x_dest, sample_depth_stencil_src, sample_temp_x_src);
    if (depth_stencil_early && !current_shader().implicit_early_z_write_allowed()) {
      a_.OpBFI(dxbc::Dest::R(system_temp_rov_params_, 0b0001), dxbc::Src::LU(1),
               dxbc::Src::LU(4 + i), sample_temp_x_src,
               dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX));
    } else {
      a_.OpIf(true, sample_temp_x_src);
      {
        if (depth_stencil_early) {
          a_.OpAnd(sample_temp_x_dest, LoadFlagsSystemConstant(),
                   dxbc::Src::LU(kSysFlag_ROVDepthStencilEarlyWrite));

          a_.OpIf(true, sample_temp_x_src);
        }

        if (uav_index_edram_ == kBindingIndexUnallocated) {
          uav_index_edram_ = uav_count_++;
        }
        a_.OpStoreUAVTyped(dxbc::Dest::U(uav_index_edram_, uint32_t(UAVRegister::kEdram)),
                           dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), 1,
                           sample_depth_stencil_src);
        if (depth_stencil_early) {
          a_.OpElse();

          a_.OpOr(dxbc::Dest::R(system_temp_rov_params_, 0b0001),
                  dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                  dxbc::Src::LU(1 << (4 + i)));

          a_.OpEndIf();
        }
      }

      a_.OpEndIf();
    }

    PopSystemTemp();

    a_.OpEndIf();

    {
      uint32_t tile_width = xenos::kEdramTileWidthSamples * draw_resolution_scale_x_;
      int32_t sample_column_delta = int32_t(2 * draw_resolution_scale_x_);
      int32_t sample_row_delta = int32_t(2 * draw_resolution_scale_y_ * tile_width);
      int32_t sample_delta;
      if (!(i & 1)) {
        sample_delta = sample_column_delta;
      } else if (i == 1) {
        sample_delta = sample_row_delta - sample_column_delta;
      } else {
        sample_delta = -(sample_row_delta + sample_column_delta);
      }
      a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
                dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
                dxbc::Src::LI(sample_delta));
    }
  }

  if (ROV_IsDepthStencilEarly()) {
    if (zpd_full_counters_) {
      ROV_AddMSAASamplesToZPD(false, true);
    }

    a_.OpAnd(dxbc::Dest::R(temp, 0b0001), dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
             dxbc::Src::LU(0b11111111));

    a_.OpMovC(dxbc::Dest::R(temp, 0b0001), dxbc::Src::R(temp, dxbc::Src::kXXXX),
              dxbc::Src::LF(1.0f), dxbc::Src::LF(0.0f));

    a_.OpDerivRTXFine(dxbc::Dest::R(temp, 0b0010), dxbc::Src::R(temp, dxbc::Src::kXXXX));

    a_.OpMovC(dxbc::Dest::R(temp, 0b0001), dxbc::Src::R(temp, dxbc::Src::kYYYY),
              dxbc::Src::LF(1.0f), dxbc::Src::R(temp, dxbc::Src::kXXXX));

    a_.OpDerivRTYCoarse(dxbc::Dest::R(temp, 0b0010), dxbc::Src::R(temp, dxbc::Src::kXXXX));

    a_.OpMovC(dxbc::Dest::R(temp, 0b0001), dxbc::Src::R(temp, dxbc::Src::kYYYY),
              dxbc::Src::LF(1.0f), dxbc::Src::R(temp, dxbc::Src::kXXXX));

    a_.OpRetC(false, dxbc::Src::R(temp, dxbc::Src::kXXXX));
  }

  a_.OpEndIf();

  PopSystemTemp();
}

void DxbcShaderTranslator::ROV_UnpackColor(uint32_t rt_index, uint32_t packed_temp,
                                           uint32_t packed_temp_components, uint32_t color_temp,
                                           uint32_t temp1, uint32_t temp1_component, uint32_t temp2,
                                           uint32_t temp2_component) {
  assert_true(color_temp != packed_temp || packed_temp_components == 0);

  dxbc::Src packed_temp_low(dxbc::Src::R(packed_temp).Select(packed_temp_components));
  dxbc::Dest temp1_dest(dxbc::Dest::R(temp1, 1 << temp1_component));
  dxbc::Src temp1_src(dxbc::Src::R(temp1).Select(temp1_component));
  dxbc::Dest temp2_dest(dxbc::Dest::R(temp2, 1 << temp2_component));
  dxbc::Src temp2_src(dxbc::Src::R(temp2).Select(temp2_component));

  a_.OpMov(dxbc::Dest::R(color_temp, 0b1100), dxbc::Src::LF(0.0f, 0.0f, 0.0f, 1.0f));

  a_.OpSwitch(LoadSystemConstant(
      SystemConstants::Index::kEdramRTFormatFlags,
      offsetof(SystemConstants, edram_rt_format_flags) + sizeof(uint32_t) * rt_index,
      dxbc::Src::kXXXX));

  for (uint32_t i = 0; i < 2; ++i) {
    a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
        i ? xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA
          : xenos::ColorRenderTargetFormat::k_8_8_8_8)));

    a_.OpUBFE(dxbc::Dest::R(color_temp), dxbc::Src::LU(8), dxbc::Src::LU(0, 8, 16, 24),
              packed_temp_low);

    a_.OpUToF(dxbc::Dest::R(color_temp), dxbc::Src::R(color_temp));

    a_.OpMul(dxbc::Dest::R(color_temp), dxbc::Src::R(color_temp), dxbc::Src::LF(1.0f / 255.0f));
    if (i) {
      for (uint32_t j = 0; j < 3; ++j) {
        PWLGammaToLinear(a_, color_temp, j, color_temp, j, true, temp1, temp1_component, temp2,
                         temp2_component);
      }
    }
    a_.OpBreak();
  }

  a_.OpCase(dxbc::Src::LU(
      RenderTargetCache::AddPSIColorFormatFlags(xenos::ColorRenderTargetFormat::k_2_10_10_10)));
  a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
      xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10)));
  {
    a_.OpUBFE(dxbc::Dest::R(color_temp), dxbc::Src::LU(10, 10, 10, 2), dxbc::Src::LU(0, 10, 20, 30),
              packed_temp_low);

    a_.OpUToF(dxbc::Dest::R(color_temp), dxbc::Src::R(color_temp));

    a_.OpMul(dxbc::Dest::R(color_temp), dxbc::Src::R(color_temp),
             dxbc::Src::LF(1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 1023.0f, 1.0f / 3.0f));
  }
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
      xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT)));
  a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
      xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16)));
  {
    a_.OpUBFE(dxbc::Dest::R(color_temp, 0b1000), dxbc::Src::LU(2), dxbc::Src::LU(30),
              packed_temp_low);

    a_.OpUToF(dxbc::Dest::R(color_temp, 0b1000), dxbc::Src::R(color_temp, dxbc::Src::kWWWW));

    a_.OpMul(dxbc::Dest::R(color_temp, 0b1000), dxbc::Src::R(color_temp, dxbc::Src::kWWWW),
             dxbc::Src::LF(1.0f / 3.0f));

    for (int32_t i = 2; i >= 0; --i) {
      Float7e3To32(a_, dxbc::Dest::R(color_temp, 1 << i), packed_temp, packed_temp_components,
                   i * 10, color_temp, i, temp1, temp1_component);
    }
  }
  a_.OpBreak();

  for (uint32_t i = 0; i < 2; ++i) {
    a_.OpCase(dxbc::Src::LU(
        RenderTargetCache::AddPSIColorFormatFlags(i ? xenos::ColorRenderTargetFormat::k_16_16_16_16
                                                    : xenos::ColorRenderTargetFormat::k_16_16)));
    dxbc::Dest color_components_dest(dxbc::Dest::R(color_temp, i ? 0b1111 : 0b0011));

    a_.OpIBFE(color_components_dest, dxbc::Src::LU(16), dxbc::Src::LU(0, 16, 0, 16),
              dxbc::Src::R(packed_temp, 0b01010000 + packed_temp_components * 0b01010101));

    a_.OpIToF(color_components_dest, dxbc::Src::R(color_temp));

    a_.OpMul(color_components_dest, dxbc::Src::R(color_temp), dxbc::Src::LF(32.0f / 32767.0f));
    a_.OpBreak();
  }

  for (uint32_t i = 0; i < 2; ++i) {
    a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
        i ? xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT
          : xenos::ColorRenderTargetFormat::k_16_16_FLOAT)));
    dxbc::Dest color_components_dest(dxbc::Dest::R(color_temp, i ? 0b1111 : 0b0011));

    a_.OpUBFE(color_components_dest, dxbc::Src::LU(16), dxbc::Src::LU(0, 16, 0, 16),
              dxbc::Src::R(packed_temp, 0b01010000 + packed_temp_components * 0b01010101));

    a_.OpF16ToF32(color_components_dest, dxbc::Src::R(color_temp));
    a_.OpBreak();
  }

  if (packed_temp != color_temp) {
    a_.OpDefault();
    a_.OpMov(dxbc::Dest::R(color_temp, 0b0011),
             dxbc::Src::R(packed_temp, 0b0100 + packed_temp_components * 0b0101));
    a_.OpBreak();
  }

  a_.OpEndSwitch();
}

void DxbcShaderTranslator::ROV_PackPreClampedColor(uint32_t rt_index, uint32_t color_temp,
                                                   uint32_t packed_temp,
                                                   uint32_t packed_temp_components, uint32_t temp1,
                                                   uint32_t temp1_component, uint32_t temp2,
                                                   uint32_t temp2_component) {
  assert_true(color_temp != packed_temp || packed_temp_components == 0);

  dxbc::Dest packed_dest_low(dxbc::Dest::R(packed_temp, 1 << packed_temp_components));
  dxbc::Src packed_src_low(dxbc::Src::R(packed_temp).Select(packed_temp_components));
  dxbc::Dest temp1_dest(dxbc::Dest::R(temp1, 1 << temp1_component));
  dxbc::Src temp1_src(dxbc::Src::R(temp1).Select(temp1_component));
  dxbc::Dest temp2_dest(dxbc::Dest::R(temp2, 1 << temp2_component));
  dxbc::Src temp2_src(dxbc::Src::R(temp2).Select(temp2_component));

  a_.OpMov(dxbc::Dest::R(packed_temp, 1 << (packed_temp_components + 1)), dxbc::Src::LU(0));

  a_.OpSwitch(LoadSystemConstant(
      SystemConstants::Index::kEdramRTFormatFlags,
      offsetof(SystemConstants, edram_rt_format_flags) + sizeof(uint32_t) * rt_index,
      dxbc::Src::kXXXX));

  for (uint32_t i = 0; i < 2; ++i) {
    a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
        i ? xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA
          : xenos::ColorRenderTargetFormat::k_8_8_8_8)));
    for (uint32_t j = 0; j < 4; ++j) {
      if (i && j < 3) {
        PreSaturatedLinearToPWLGamma(a_, temp1, temp1_component, color_temp, j, temp1,
                                     temp1_component, temp2, temp2_component);

        a_.OpMAd(temp1_dest, temp1_src, dxbc::Src::LF(255.0f), dxbc::Src::LF(0.5f));
      } else {
        a_.OpMAd(temp1_dest, dxbc::Src::R(color_temp).Select(j), dxbc::Src::LF(255.0f),
                 dxbc::Src::LF(0.5f));
      }

      a_.OpFToU(j ? temp1_dest : packed_dest_low, temp1_src);

      if (j) {
        a_.OpBFI(packed_dest_low, dxbc::Src::LU(8), dxbc::Src::LU(j * 8), temp1_src,
                 packed_src_low);
      }
    }
    a_.OpBreak();
  }

  a_.OpCase(dxbc::Src::LU(
      RenderTargetCache::AddPSIColorFormatFlags(xenos::ColorRenderTargetFormat::k_2_10_10_10)));
  a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
      xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10)));
  for (uint32_t i = 0; i < 4; ++i) {
    a_.OpMAd(temp1_dest, dxbc::Src::R(color_temp).Select(i), dxbc::Src::LF(i < 3 ? 1023.0f : 3.0f),
             dxbc::Src::LF(0.5f));
    a_.OpFToU(i ? temp1_dest : packed_dest_low, temp1_src);

    if (i) {
      a_.OpBFI(packed_dest_low, dxbc::Src::LU(i < 3 ? 10 : 2), dxbc::Src::LU(i * 10), temp1_src,
               packed_src_low);
    }
  }
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
      xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT)));
  a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
      xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16)));
  {
    PreClampedFloat32To7e3(a_, packed_temp, packed_temp_components, color_temp, 0, temp1,
                           temp1_component);
    for (uint32_t i = 1; i < 3; ++i) {
      PreClampedFloat32To7e3(a_, temp1, temp1_component, color_temp, i, temp2, temp2_component);
      a_.OpBFI(packed_dest_low, dxbc::Src::LU(10), dxbc::Src::LU(i * 10), temp1_src,
               packed_src_low);
    }

    a_.OpMAd(temp1_dest, dxbc::Src::R(color_temp, dxbc::Src::kWWWW), dxbc::Src::LF(3.0f),
             dxbc::Src::LF(0.5f));
    a_.OpFToU(temp1_dest, temp1_src);

    a_.OpBFI(packed_dest_low, dxbc::Src::LU(2), dxbc::Src::LU(30), temp1_src, packed_src_low);
  }
  a_.OpBreak();

  for (uint32_t i = 0; i < 2; ++i) {
    a_.OpCase(dxbc::Src::LU(
        RenderTargetCache::AddPSIColorFormatFlags(i ? xenos::ColorRenderTargetFormat::k_16_16_16_16
                                                    : xenos::ColorRenderTargetFormat::k_16_16)));
    for (uint32_t j = 0; j < (uint32_t(2) << i); ++j) {
      a_.OpGE(temp2_dest, dxbc::Src::R(color_temp).Select(j), dxbc::Src::LF(0.0f));
      a_.OpMovC(temp2_dest, temp2_src, dxbc::Src::LF(0.5f), dxbc::Src::LF(-0.5f));
      a_.OpMAd(temp1_dest, dxbc::Src::R(color_temp).Select(j), dxbc::Src::LF(32767.0f / 32.0f),
               temp2_src);
      dxbc::Dest packed_dest_half(
          dxbc::Dest::R(packed_temp, 1 << (packed_temp_components + (j >> 1))));

      a_.OpFToI((j & 1) ? temp1_dest : packed_dest_half, temp1_src);

      if (j & 1) {
        a_.OpBFI(packed_dest_half, dxbc::Src::LU(16), dxbc::Src::LU(16), temp1_src,
                 dxbc::Src::R(packed_temp).Select(packed_temp_components + (j >> 1)));
      }
    }
    a_.OpBreak();
  }

  for (uint32_t i = 0; i < 2; ++i) {
    a_.OpCase(dxbc::Src::LU(RenderTargetCache::AddPSIColorFormatFlags(
        i ? xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT
          : xenos::ColorRenderTargetFormat::k_16_16_FLOAT)));
    for (uint32_t j = 0; j < (uint32_t(2) << i); ++j) {
      dxbc::Dest packed_dest_half(
          dxbc::Dest::R(packed_temp, 1 << (packed_temp_components + (j >> 1))));

      a_.OpF32ToF16((j & 1) ? temp1_dest : packed_dest_half, dxbc::Src::R(color_temp).Select(j));

      if (j & 1) {
        a_.OpBFI(packed_dest_half, dxbc::Src::LU(16), dxbc::Src::LU(16), temp1_src,
                 dxbc::Src::R(packed_temp).Select(packed_temp_components + (j >> 1)));
      }
    }
    a_.OpBreak();
  }

  if (packed_temp != color_temp) {
    a_.OpDefault();
    a_.OpMov(dxbc::Dest::R(packed_temp, 0b11 << packed_temp_components),
             dxbc::Src::R(color_temp, 0b0100 << (packed_temp_components * 2)));
    a_.OpBreak();
  }

  a_.OpEndSwitch();
}

void DxbcShaderTranslator::ROV_HandleColorBlendFactorCases(uint32_t src_temp, uint32_t dst_temp,
                                                           uint32_t factor_temp) {
  dxbc::Dest factor_dest(dxbc::Dest::R(factor_temp, 0b0111));
  dxbc::Src one_src(dxbc::Src::LF(1.0f));

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOne)));
  a_.OpMov(factor_dest, one_src);
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kSrcColor)));
  if (factor_temp != src_temp) {
    a_.OpMov(factor_dest, dxbc::Src::R(src_temp));
  }
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusSrcColor)));
  a_.OpAdd(factor_dest, one_src, -dxbc::Src::R(src_temp));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kSrcAlpha)));
  a_.OpMov(factor_dest, dxbc::Src::R(src_temp, dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusSrcAlpha)));
  a_.OpAdd(factor_dest, one_src, -dxbc::Src::R(src_temp, dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kDstColor)));
  if (factor_temp != dst_temp) {
    a_.OpMov(factor_dest, dxbc::Src::R(dst_temp));
  }
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusDstColor)));
  a_.OpAdd(factor_dest, one_src, -dxbc::Src::R(dst_temp));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kDstAlpha)));
  a_.OpMov(factor_dest, dxbc::Src::R(dst_temp, dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusDstAlpha)));
  a_.OpAdd(factor_dest, one_src, -dxbc::Src::R(dst_temp, dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kConstantColor)));
  a_.OpMov(factor_dest,
           LoadSystemConstant(SystemConstants::Index::kEdramBlendConstant,
                              offsetof(SystemConstants, edram_blend_constant), dxbc::Src::kXYZW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusConstantColor)));
  a_.OpAdd(factor_dest, one_src,
           -LoadSystemConstant(SystemConstants::Index::kEdramBlendConstant,
                               offsetof(SystemConstants, edram_blend_constant), dxbc::Src::kXYZW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kConstantAlpha)));
  a_.OpMov(factor_dest,
           LoadSystemConstant(SystemConstants::Index::kEdramBlendConstant,
                              offsetof(SystemConstants, edram_blend_constant), dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusConstantAlpha)));
  a_.OpAdd(factor_dest, one_src,
           -LoadSystemConstant(SystemConstants::Index::kEdramBlendConstant,
                               offsetof(SystemConstants, edram_blend_constant), dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kSrcAlphaSaturate)));
  a_.OpAdd(dxbc::Dest::R(factor_temp, 0b0001), one_src, -dxbc::Src::R(dst_temp, dxbc::Src::kWWWW));
  a_.OpMin(factor_dest, dxbc::Src::R(src_temp, dxbc::Src::kWWWW),
           dxbc::Src::R(factor_temp, dxbc::Src::kXXXX));
  a_.OpBreak();

  a_.OpDefault();
  a_.OpMov(factor_dest, dxbc::Src::LF(0.0f));
  a_.OpBreak();
}

void DxbcShaderTranslator::ROV_HandleAlphaBlendFactorCases(uint32_t src_temp, uint32_t dst_temp,
                                                           uint32_t factor_temp,
                                                           uint32_t factor_component) {
  dxbc::Dest factor_dest(dxbc::Dest::R(factor_temp, 1 << factor_component));
  dxbc::Src one_src(dxbc::Src::LF(1.0f));

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOne)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kSrcAlphaSaturate)));
  a_.OpMov(factor_dest, one_src);
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kSrcColor)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kSrcAlpha)));
  if (factor_temp != src_temp || factor_component != 3) {
    a_.OpMov(factor_dest, dxbc::Src::R(src_temp, dxbc::Src::kWWWW));
  }
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusSrcColor)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusSrcAlpha)));
  a_.OpAdd(factor_dest, one_src, -dxbc::Src::R(src_temp, dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kDstColor)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kDstAlpha)));
  if (factor_temp != dst_temp || factor_component != 3) {
    a_.OpMov(factor_dest, dxbc::Src::R(dst_temp, dxbc::Src::kWWWW));
  }
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusDstColor)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusDstAlpha)));
  a_.OpAdd(factor_dest, one_src, -dxbc::Src::R(dst_temp, dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kConstantColor)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kConstantAlpha)));
  a_.OpMov(factor_dest,
           LoadSystemConstant(SystemConstants::Index::kEdramBlendConstant,
                              offsetof(SystemConstants, edram_blend_constant), dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusConstantColor)));
  a_.OpCase(dxbc::Src::LU(uint32_t(xenos::BlendFactor::kOneMinusConstantAlpha)));
  a_.OpAdd(factor_dest, one_src,
           -LoadSystemConstant(SystemConstants::Index::kEdramBlendConstant,
                               offsetof(SystemConstants, edram_blend_constant), dxbc::Src::kWWWW));
  a_.OpBreak();

  a_.OpDefault();
  a_.OpMov(factor_dest, dxbc::Src::LF(0.0f));
  a_.OpBreak();
}

void DxbcShaderTranslator::ROV_AddMSAASamplesToZPD(bool count_passed, bool count_failed) {
  if (!count_passed && !count_failed) {
    return;
  }
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

  a_.OpINE(temp_x_dest, counter_index_src, dxbc::Src::LU(UINT32_MAX));
  a_.OpIf(true, temp_x_src);
  {
    a_.OpUMul(dxbc::Dest::Null(), temp_y_dest, counter_index_src,
              dxbc::Src::LU(XenosZPDReport::kCounterSizeBytes));
    auto add_lane = [&](uint32_t sample_bits, uint32_t lane) {
      a_.OpAnd(temp_x_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
               dxbc::Src::LU(sample_bits));
      a_.OpCountBits(temp_x_dest, temp_x_src);
      a_.OpIf(true, temp_x_src);
      {
        a_.OpIAdd(temp_z_dest, temp_y_src, dxbc::Src::LU(lane * sizeof(uint32_t)));
        a_.OpAtomicIAdd(
            dxbc::Dest::U(uav_index_zpd_counter_, uint32_t(UAVRegister::kZpdCounter), 0),
            temp_z_src, 0b0001, temp_x_src);
      }
      a_.OpEndIf();
    };
    if (is_viz_survey_pixel_shader_) {
      if (count_passed) {
        a_.OpAnd(temp_x_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
                 dxbc::Src::LU(0b1111));
        a_.OpIf(true, temp_x_src);
        {
          a_.OpIAdd(temp_z_dest, temp_y_src,
                    dxbc::Src::LU(XenosZPDReport::kZPass * sizeof(uint32_t)));
          a_.OpStoreRaw(
              dxbc::Dest::U(uav_index_zpd_counter_, uint32_t(UAVRegister::kZpdCounter), 0b0001),
              temp_z_src, dxbc::Src::LU(1));
        }
        a_.OpEndIf();
      }
    } else {
      if (count_passed) {
        add_lane(0b1111, XenosZPDReport::kZPass);
      }
      if (count_failed) {
        add_lane(0b1111 << 12, XenosZPDReport::kZFail);
        add_lane(0b1111 << 16, XenosZPDReport::kStencilFail);
      }
    }
  }
  a_.OpEndIf();

  PopSystemTemp();
}

void DxbcShaderTranslator::CompletePixelShader_WriteToROV() {
  uint32_t temp = PushSystemTemp();
  dxbc::Dest temp_x_dest(dxbc::Dest::R(temp, 0b0001));
  dxbc::Src temp_x_src(dxbc::Src::R(temp, dxbc::Src::kXXXX));
  dxbc::Dest temp_y_dest(dxbc::Dest::R(temp, 0b0010));
  dxbc::Src temp_y_src(dxbc::Src::R(temp, dxbc::Src::kYYYY));
  dxbc::Dest temp_z_dest(dxbc::Dest::R(temp, 0b0100));
  dxbc::Src temp_z_src(dxbc::Src::R(temp, dxbc::Src::kZZZZ));
  dxbc::Dest temp_w_dest(dxbc::Dest::R(temp, 0b1000));
  dxbc::Src temp_w_src(dxbc::Src::R(temp, dxbc::Src::kWWWW));

  uint32_t tile_width = xenos::kEdramTileWidthSamples * draw_resolution_scale_x_;

  if (ROV_IsDepthStencilEarly()) {
    for (uint32_t i = 0; i < 4; ++i) {
      a_.OpAnd(temp_x_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
               dxbc::Src::LU(1 << (4 + i)));

      a_.OpIf(true, temp_x_src);
      {
        if (uav_index_edram_ == kBindingIndexUnallocated) {
          uav_index_edram_ = uav_count_++;
        }
        a_.OpStoreUAVTyped(dxbc::Dest::U(uav_index_edram_, uint32_t(UAVRegister::kEdram)),
                           dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), 1,
                           dxbc::Src::R(system_temp_depth_stencil_).Select(i));
      }

      a_.OpEndIf();

      if (i < 3) {
        int32_t sample_column_delta = int32_t(2 * draw_resolution_scale_x_);
        int32_t sample_row_delta = int32_t(2 * draw_resolution_scale_y_ * tile_width);
        a_.OpIAdd(
            dxbc::Dest::R(system_temp_rov_params_, 0b0010),
            dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
            dxbc::Src::LI((i & 1) ? sample_row_delta - sample_column_delta : sample_column_delta));
      }
    }
  } else {
    ROV_DepthStencilTest();
  }

  ROV_AddMSAASamplesToZPD(true, zpd_full_counters_ && !ROV_IsDepthStencilEarly());

  if (!is_depth_only_pixel_shader_) {
    a_.OpAnd(temp_x_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
             dxbc::Src::LU(0b1111));

    a_.OpRetC(false, temp_x_src);
  }

  uint32_t shader_writes_color_targets = current_shader().writes_color_targets();
  uint32_t edram_size_32bpp_samples = (xenos::kEdramTileHeightSamples * draw_resolution_scale_y_) *
                                      tile_width * xenos::kEdramTileCount;
  for (uint32_t i = 0; i < 4; ++i) {
    if (!(shader_writes_color_targets & (1 << i))) {
      continue;
    }

    dxbc::Src keep_mask_src(LoadSystemConstant(
        SystemConstants::Index::kEdramRTKeepMask,
        offsetof(SystemConstants, edram_rt_keep_mask) + sizeof(uint32_t) * 2 * i, 0b0100));

    a_.OpAnd(temp_x_dest, keep_mask_src.SelectFromSwizzled(0), keep_mask_src.SelectFromSwizzled(1));

    a_.OpNot(temp_x_dest, temp_x_src);

    a_.OpMovC(temp_x_dest, temp_x_src, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
              dxbc::Src::LU(0));

    a_.OpAnd(temp_x_dest, temp_x_src, dxbc::Src::LU(1 << (8 + i)));

    a_.OpIf(true, temp_x_src);

    a_.OpMul(dxbc::Dest::R(system_temps_color_[i]), dxbc::Src::R(system_temps_color_[i]),
             LoadSystemConstant(SystemConstants::Index::kColorExpBias,
                                offsetof(SystemConstants, color_exp_bias) + sizeof(float) * i,
                                dxbc::Src::kXXXX));

    dxbc::Src rt_format_flags_src(LoadSystemConstant(
        SystemConstants::Index::kEdramRTFormatFlags,
        offsetof(SystemConstants, edram_rt_format_flags) + sizeof(uint32_t) * i, dxbc::Src::kXXXX));

    a_.OpAnd(dxbc::Dest::R(system_temp_rov_params_, 0b0010), rt_format_flags_src,
             dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_64bpp));

    a_.OpMovC(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kWWWW),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kZZZZ));

    a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              LoadSystemConstant(
                  SystemConstants::Index::kEdramRTBaseDwordsScaled,
                  offsetof(SystemConstants, edram_rt_base_dwords_scaled) + sizeof(uint32_t) * i,
                  dxbc::Src::kXXXX));

    a_.OpUDiv(dxbc::Dest::Null(), dxbc::Dest::R(system_temp_rov_params_, 0b0010),
              dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
              dxbc::Src::LU(edram_size_32bpp_samples));

    dxbc::Src rt_blend_factors_ops_src(LoadSystemConstant(
        SystemConstants::Index::kEdramRTBlendFactorsOps,
        offsetof(SystemConstants, edram_rt_blend_factors_ops) + sizeof(uint32_t) * i,
        dxbc::Src::kXXXX));
    dxbc::Src rt_clamp_vec_src(LoadSystemConstant(
        SystemConstants::Index::kEdramRTClamp,
        offsetof(SystemConstants, edram_rt_clamp) + sizeof(float) * 4 * i, dxbc::Src::kXYZW));

    a_.OpIEq(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(0x00010001));

    a_.OpIf(true, temp_x_src);
    {
      a_.OpMax(dxbc::Dest::R(system_temps_color_[i]), dxbc::Src::R(system_temps_color_[i]),
               rt_clamp_vec_src.Swizzle(0b01000000));
      a_.OpMin(dxbc::Dest::R(system_temps_color_[i]), dxbc::Src::R(system_temps_color_[i]),
               rt_clamp_vec_src.Swizzle(0b11101010));

      ROV_PackPreClampedColor(i, system_temps_color_[i], temp, 0, temp, 2, temp, 3);
    }

    a_.OpElse();
    {
      a_.OpAnd(temp_x_dest, rt_format_flags_src,
               dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_FixedPointColor));

      a_.OpIf(true, temp_x_src);
      {
        a_.OpMax(dxbc::Dest::R(system_temps_color_[i], 0b0111),
                 dxbc::Src::R(system_temps_color_[i]), rt_clamp_vec_src.Select(0));
        a_.OpMin(dxbc::Dest::R(system_temps_color_[i], 0b0111),
                 dxbc::Src::R(system_temps_color_[i]), rt_clamp_vec_src.Select(2));
      }

      a_.OpEndIf();

      a_.OpAnd(temp_x_dest, rt_format_flags_src,
               dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_FixedPointAlpha));

      a_.OpIf(true, temp_x_src);
      {
        a_.OpMax(dxbc::Dest::R(system_temps_color_[i], 0b1000),
                 dxbc::Src::R(system_temps_color_[i], dxbc::Src::kWWWW),
                 rt_clamp_vec_src.Select(1));
        a_.OpMin(dxbc::Dest::R(system_temps_color_[i], 0b1000),
                 dxbc::Src::R(system_temps_color_[i], dxbc::Src::kWWWW),
                 rt_clamp_vec_src.Select(3));
      }

      a_.OpEndIf();

      a_.OpMov(dxbc::Dest::R(temp, 0b0011), dxbc::Src::LU(0));
    }
    a_.OpEndIf();

    for (uint32_t j = 0; j < 4; ++j) {
      a_.OpAnd(temp_z_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kXXXX),
               dxbc::Src::LU(1 << j));

      a_.OpIf(true, temp_z_src);

      a_.OpOr(temp_z_dest, keep_mask_src.SelectFromSwizzled(0),
              keep_mask_src.SelectFromSwizzled(1));

      a_.OpMovC(temp_z_dest, temp_z_src, dxbc::Src::LU(0), rt_blend_factors_ops_src);

      a_.OpINE(temp_z_dest, temp_z_src, dxbc::Src::LU(0x00010001));

      a_.OpIf(true, temp_z_src);
      {
        if (uav_index_edram_ == kBindingIndexUnallocated) {
          uav_index_edram_ = uav_count_++;
        }
        a_.OpLdUAVTyped(
            temp_z_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), 1,
            dxbc::Src::U(uav_index_edram_, uint32_t(UAVRegister::kEdram), dxbc::Src::kXXXX));

        a_.OpAnd(temp_w_dest, rt_format_flags_src,
                 dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_64bpp));

        a_.OpIf(true, temp_w_src);
        {
          a_.OpIAdd(temp_w_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
                    dxbc::Src::LU(1));

          if (uav_index_edram_ == kBindingIndexUnallocated) {
            uav_index_edram_ = uav_count_++;
          }
          a_.OpLdUAVTyped(
              temp_w_dest, temp_w_src, 1,
              dxbc::Src::U(uav_index_edram_, uint32_t(UAVRegister::kEdram), dxbc::Src::kXXXX));
        }

        a_.OpElse();
        { a_.OpMov(temp_w_dest, dxbc::Src::LU(0)); }

        a_.OpEndIf();

        uint32_t color_temp = PushSystemTemp();
        dxbc::Dest color_temp_rgb_dest(dxbc::Dest::R(color_temp, 0b0111));
        dxbc::Dest color_temp_a_dest(dxbc::Dest::R(color_temp, 0b1000));
        dxbc::Src color_temp_src(dxbc::Src::R(color_temp));
        dxbc::Src color_temp_a_src(dxbc::Src::R(color_temp, dxbc::Src::kWWWW));

        a_.OpINE(dxbc::Dest::R(color_temp, 0b0001), rt_blend_factors_ops_src,
                 dxbc::Src::LU(0x00010001));

        a_.OpIf(true, dxbc::Src::R(color_temp, dxbc::Src::kXXXX));
        {
          ROV_UnpackColor(i, temp, 2, color_temp, temp, 0, temp, 1);

          a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << (5 + 1)));

          a_.OpIf(false, temp_x_src);
          {
            uint32_t blend_src_temp = PushSystemTemp();
            dxbc::Dest blend_src_temp_rgb_dest(dxbc::Dest::R(blend_src_temp, 0b0111));
            dxbc::Src blend_src_temp_src(dxbc::Src::R(blend_src_temp));

            a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU((1 << 5) - 1));

            a_.OpIf(true, temp_x_src);
            {
              a_.OpSwitch(temp_x_src);

              ROV_HandleColorBlendFactorCases(system_temps_color_[i], color_temp, blend_src_temp);

              a_.OpEndSwitch();

              a_.OpAnd(temp_x_dest, rt_format_flags_src,
                       dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_FixedPointColor));

              a_.OpIf(true, temp_x_src);
              {
                a_.OpMax(blend_src_temp_rgb_dest, blend_src_temp_src, rt_clamp_vec_src.Select(0));
                a_.OpMin(blend_src_temp_rgb_dest, blend_src_temp_src, rt_clamp_vec_src.Select(2));
              }

              a_.OpEndIf();

              a_.OpMul(blend_src_temp_rgb_dest, dxbc::Src::R(system_temps_color_[i]),
                       blend_src_temp_src);

              a_.OpIf(true, temp_x_src);
              {
                a_.OpMax(blend_src_temp_rgb_dest, blend_src_temp_src, rt_clamp_vec_src.Select(0));
                a_.OpMin(blend_src_temp_rgb_dest, blend_src_temp_src, rt_clamp_vec_src.Select(2));
              }

              a_.OpEndIf();

              a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << (5 + 2)));

              a_.OpMovC(blend_src_temp_rgb_dest, temp_x_src, -blend_src_temp_src,
                        blend_src_temp_src);
            }

            a_.OpElse();
            { a_.OpMov(blend_src_temp_rgb_dest, dxbc::Src::LF(0.0f)); }

            a_.OpEndIf();

            a_.OpUBFE(temp_x_dest, dxbc::Src::LU(5), dxbc::Src::LU(8), rt_blend_factors_ops_src);

            a_.OpIf(true, temp_x_src);
            {
              uint32_t blend_dest_factor_temp = PushSystemTemp();
              dxbc::Src blend_dest_factor_temp_src(dxbc::Src::R(blend_dest_factor_temp));

              a_.OpSwitch(temp_x_src);

              ROV_HandleColorBlendFactorCases(system_temps_color_[i], color_temp,
                                              blend_dest_factor_temp);

              a_.OpEndSwitch();

              a_.OpAnd(temp_x_dest, rt_format_flags_src,
                       dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_FixedPointColor));

              a_.OpIf(true, temp_x_src);
              {
                a_.OpMax(dxbc::Dest::R(blend_dest_factor_temp, 0b0111), blend_dest_factor_temp_src,
                         rt_clamp_vec_src.Select(0));
                a_.OpMin(dxbc::Dest::R(blend_dest_factor_temp, 0b0111), blend_dest_factor_temp_src,
                         rt_clamp_vec_src.Select(2));
              }

              a_.OpEndIf();

              a_.OpMul(color_temp_rgb_dest, color_temp_src, blend_dest_factor_temp_src);

              PopSystemTemp();

              a_.OpIf(true, temp_x_src);
              {
                a_.OpMax(color_temp_rgb_dest, color_temp_src, rt_clamp_vec_src.Select(0));
                a_.OpMin(color_temp_rgb_dest, color_temp_src, rt_clamp_vec_src.Select(2));
              }

              a_.OpEndIf();

              a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << 5));

              a_.OpMovC(temp_x_dest, temp_x_src, dxbc::Src::LF(-1.0f), dxbc::Src::LF(1.0f));

              a_.OpMAd(color_temp_rgb_dest, color_temp_src, temp_x_src, blend_src_temp_src);
            }

            a_.OpElse();
            { a_.OpMov(color_temp_rgb_dest, blend_src_temp_src); }

            a_.OpEndIf();

            PopSystemTemp();

            a_.OpMax(color_temp_rgb_dest, color_temp_src, rt_clamp_vec_src.Select(0));
            a_.OpMin(color_temp_rgb_dest, color_temp_src, rt_clamp_vec_src.Select(2));
          }

          a_.OpElse();
          {
            a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << 5));

            a_.OpIf(true, temp_x_src);
            { a_.OpMax(color_temp_rgb_dest, dxbc::Src::R(system_temps_color_[i]), color_temp_src); }

            a_.OpElse();
            { a_.OpMin(color_temp_rgb_dest, dxbc::Src::R(system_temps_color_[i]), color_temp_src); }

            a_.OpEndIf();
          }

          a_.OpEndIf();

          a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << (21 + 1)));

          a_.OpIf(false, temp_x_src);
          {
            a_.OpUBFE(temp_x_dest, dxbc::Src::LU(5), dxbc::Src::LU(16), rt_blend_factors_ops_src);

            a_.OpIf(true, temp_x_src);
            {
              a_.OpSwitch(temp_x_src);

              ROV_HandleAlphaBlendFactorCases(system_temps_color_[i], color_temp, temp, 0);

              a_.OpEndSwitch();

              a_.OpAnd(temp_y_dest, rt_format_flags_src,
                       dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_FixedPointAlpha));

              a_.OpIf(true, temp_y_src);
              {
                a_.OpMax(temp_x_dest, temp_x_src, rt_clamp_vec_src.Select(1));
                a_.OpMin(temp_x_dest, temp_x_src, rt_clamp_vec_src.Select(3));
              }

              a_.OpEndIf();

              a_.OpMul(temp_x_dest, dxbc::Src::R(system_temps_color_[i], dxbc::Src::kWWWW),
                       temp_x_src);

              a_.OpIf(true, temp_y_src);
              {
                a_.OpMax(temp_x_dest, temp_x_src, rt_clamp_vec_src.Select(1));
                a_.OpMin(temp_x_dest, temp_x_src, rt_clamp_vec_src.Select(3));
              }

              a_.OpEndIf();

              a_.OpAnd(temp_y_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << (21 + 2)));

              a_.OpMovC(temp_x_dest, temp_y_src, -temp_x_src, temp_x_src);
            }

            a_.OpElse();
            { a_.OpMov(temp_x_dest, dxbc::Src::LF(0.0f)); }

            a_.OpEndIf();

            a_.OpUBFE(temp_y_dest, dxbc::Src::LU(5), dxbc::Src::LU(24), rt_blend_factors_ops_src);

            a_.OpIf(true, temp_y_src);
            {
              a_.OpSwitch(temp_y_src);

              ROV_HandleAlphaBlendFactorCases(system_temps_color_[i], color_temp, temp, 1);

              a_.OpEndSwitch();

              uint32_t alpha_is_fixed_temp = PushSystemTemp();
              a_.OpAnd(dxbc::Dest::R(alpha_is_fixed_temp, 0b0001), rt_format_flags_src,
                       dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_FixedPointAlpha));

              a_.OpIf(true, dxbc::Src::R(alpha_is_fixed_temp, dxbc::Src::kXXXX));
              {
                a_.OpMax(temp_y_dest, temp_y_src, rt_clamp_vec_src.Select(1));
                a_.OpMin(temp_y_dest, temp_y_src, rt_clamp_vec_src.Select(3));
              }

              a_.OpEndIf();

              a_.OpMul(color_temp_a_dest, color_temp_a_src, temp_y_src);

              a_.OpIf(true, dxbc::Src::R(alpha_is_fixed_temp, dxbc::Src::kXXXX));

              PopSystemTemp();
              {
                a_.OpMax(color_temp_a_dest, color_temp_a_src, rt_clamp_vec_src.Select(1));
                a_.OpMin(color_temp_a_dest, color_temp_a_src, rt_clamp_vec_src.Select(3));
              }

              a_.OpEndIf();

              a_.OpAnd(temp_y_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << 21));

              a_.OpMovC(temp_y_dest, temp_y_src, dxbc::Src::LF(-1.0f), dxbc::Src::LF(1.0f));

              a_.OpMAd(color_temp_a_dest, color_temp_a_src, temp_y_src, temp_x_src);
            }

            a_.OpElse();
            { a_.OpMov(color_temp_a_dest, temp_x_src); }

            a_.OpEndIf();

            a_.OpMax(color_temp_a_dest, color_temp_a_src, rt_clamp_vec_src.Select(1));
            a_.OpMin(color_temp_a_dest, color_temp_a_src, rt_clamp_vec_src.Select(3));
          }

          a_.OpElse();
          {
            a_.OpAnd(temp_x_dest, rt_blend_factors_ops_src, dxbc::Src::LU(1 << 21));

            a_.OpIf(true, temp_x_src);
            {
              a_.OpMax(color_temp_a_dest, dxbc::Src::R(system_temps_color_[i], dxbc::Src::kWWWW),
                       color_temp_a_src);
            }

            a_.OpElse();
            {
              a_.OpMin(color_temp_a_dest, dxbc::Src::R(system_temps_color_[i], dxbc::Src::kWWWW),
                       color_temp_a_src);
            }

            a_.OpEndIf();
          }

          a_.OpEndIf();

          uint32_t color_pack_temp = PushSystemTemp();
          ROV_PackPreClampedColor(i, color_temp, temp, 0, color_pack_temp, 0, color_pack_temp, 1);

          PopSystemTemp();
        }

        a_.OpEndIf();

        a_.OpAnd(dxbc::Dest::R(temp, 0b1100), dxbc::Src::R(temp),
                 keep_mask_src.SwizzleSwizzled(0b0100 << 4));

        a_.OpNot(dxbc::Dest::R(color_temp, 0b0011), keep_mask_src);

        PopSystemTemp();

        a_.OpAnd(dxbc::Dest::R(temp, 0b0011), dxbc::Src::R(temp), dxbc::Src::R(color_temp));

        a_.OpOr(dxbc::Dest::R(temp, 0b0011), dxbc::Src::R(temp), dxbc::Src::R(temp, 0b1110));
      }

      a_.OpEndIf();

      if (uav_index_edram_ == kBindingIndexUnallocated) {
        uav_index_edram_ = uav_count_++;
      }
      a_.OpStoreUAVTyped(dxbc::Dest::U(uav_index_edram_, uint32_t(UAVRegister::kEdram)),
                         dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), 1, temp_x_src);

      a_.OpAnd(temp_z_dest, rt_format_flags_src,
               dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_64bpp));

      a_.OpIf(true, temp_z_src);
      {
        a_.OpIAdd(temp_z_dest, dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY),
                  dxbc::Src::LU(1));

        if (uav_index_edram_ == kBindingIndexUnallocated) {
          uav_index_edram_ = uav_count_++;
        }
        a_.OpStoreUAVTyped(dxbc::Dest::U(uav_index_edram_, uint32_t(UAVRegister::kEdram)),
                           temp_z_src, 1, temp_y_src);
      }

      a_.OpEndIf();

      a_.OpEndIf();

      if (j < 3) {
        int32_t sample_row_delta = int32_t(2 * draw_resolution_scale_y_ * tile_width);
        int32_t sample_column_delta_32bpp = int32_t(2 * draw_resolution_scale_x_);
        int32_t sample_column_delta_64bpp = 2 * sample_column_delta_32bpp;

        a_.OpAnd(temp_z_dest, rt_format_flags_src,
                 dxbc::Src::LU(RenderTargetCache::kPSIColorFormatFlag_64bpp));

        a_.OpMovC(temp_z_dest, temp_z_src,
                  dxbc::Src::LI((j & 1) ? sample_row_delta - sample_column_delta_64bpp
                                        : sample_column_delta_64bpp),
                  dxbc::Src::LI((j & 1) ? sample_row_delta - sample_column_delta_32bpp
                                        : sample_column_delta_32bpp));

        a_.OpIAdd(dxbc::Dest::R(system_temp_rov_params_, 0b0010),
                  dxbc::Src::R(system_temp_rov_params_, dxbc::Src::kYYYY), temp_z_src);
      }
    }

    a_.OpEndIf();
  }

  PopSystemTemp();
}

void DxbcShaderTranslator::ROV_DepthTo24Bit(uint32_t d24_temp, uint32_t d24_temp_component,
                                            uint32_t d32_temp, uint32_t d32_temp_component,
                                            uint32_t temp_temp, uint32_t temp_temp_component) {
  assert_true(temp_temp != d32_temp || temp_temp_component != d32_temp_component);

  a_.OpAnd(dxbc::Dest::R(temp_temp, 1 << temp_temp_component), LoadFlagsSystemConstant(),
           dxbc::Src::LU(kSysFlag_DepthFloat24));

  a_.OpIf(true, dxbc::Src::R(temp_temp).Select(temp_temp_component));
  {
    PreClampedDepthTo20e4(a_, d24_temp, d24_temp_component, d32_temp, d32_temp_component, temp_temp,
                          temp_temp_component, true, false);
  }
  a_.OpElse();
  {
    dxbc::Dest d24_dest(dxbc::Dest::R(d24_temp, 1 << d24_temp_component));
    dxbc::Src d24_src(dxbc::Src::R(d24_temp).Select(d24_temp_component));
    a_.OpMul(d24_dest, dxbc::Src::R(d32_temp).Select(d32_temp_component),
             dxbc::Src::LF(float(0xFFFFFF)));

    a_.OpRoundNE(d24_dest, d24_src);

    a_.OpFToU(d24_dest, d24_src);
  }
  a_.OpEndIf();
}

}
