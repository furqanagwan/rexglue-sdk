/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2025 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstdint>
#include <cstdlib>

#include <rex/assert.h>
#include <rex/graphics/xenos.h>

namespace rex::graphics {

enum Register {
#define XE_GPU_REGISTER(index, type, name) XE_GPU_REG_##name = index,
#include <rex/graphics/register_table.inc>
#undef XE_GPU_REGISTER
};

namespace reg {

union alignas(uint32_t) COHER_STATUS_HOST {
  uint32_t value;
  struct {
    uint32_t matching_contexts : 8;
    uint32_t rb_copy_dest_base_ena : 1;
    uint32_t dest_base_0_ena : 1;
    uint32_t dest_base_1_ena : 1;
    uint32_t dest_base_2_ena : 1;
    uint32_t dest_base_3_ena : 1;
    uint32_t dest_base_4_ena : 1;
    uint32_t dest_base_5_ena : 1;
    uint32_t dest_base_6_ena : 1;
    uint32_t dest_base_7_ena : 1;
    uint32_t _pad_17 : 7;
    uint32_t vc_action_ena : 1;
    uint32_t tc_action_ena : 1;
    uint32_t pglb_action_ena : 1;
    uint32_t _pad_27 : 4;
    uint32_t status : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_COHER_STATUS_HOST;
};
static_assert_size(COHER_STATUS_HOST, sizeof(uint32_t));

union alignas(uint32_t) WAIT_UNTIL {
  uint32_t value;
  struct {
    uint32_t _pad_0 : 1;
    uint32_t wait_re_vsync : 1;
    uint32_t wait_fe_vsync : 1;
    uint32_t wait_vsync : 1;
    uint32_t wait_dsply_id0 : 1;
    uint32_t wait_dsply_id1 : 1;
    uint32_t wait_dsply_id2 : 1;
    uint32_t _pad_7 : 3;
    uint32_t wait_cmdfifo : 1;
    uint32_t _pad_11 : 3;
    uint32_t wait_2d_idle : 1;
    uint32_t wait_3d_idle : 1;
    uint32_t wait_2d_idleclean : 1;
    uint32_t wait_3d_idleclean : 1;
    uint32_t _pad_18 : 2;
    uint32_t cmdfifo_entries : 4;
    uint32_t _pad_24 : 8;
  };
  static constexpr Register register_index = XE_GPU_REG_WAIT_UNTIL;
};
static_assert_size(WAIT_UNTIL, sizeof(uint32_t));

union alignas(uint32_t) SQ_PROGRAM_CNTL {
  uint32_t value;
  struct {
    uint32_t vs_num_reg : 6;
    uint32_t _pad_6 : 2;
    uint32_t ps_num_reg : 6;
    uint32_t _pad_14 : 2;
    uint32_t vs_resource : 1;
    uint32_t ps_resource : 1;
    uint32_t param_gen : 1;
    uint32_t gen_index_pix : 1;

    uint32_t vs_export_count : 4;
    xenos::VertexShaderExportMode vs_export_mode : 3;
    uint32_t ps_export_mode : 4;
    uint32_t gen_index_vtx : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_SQ_PROGRAM_CNTL;
};
static_assert_size(SQ_PROGRAM_CNTL, sizeof(uint32_t));

union alignas(uint32_t) SQ_CONTEXT_MISC {
  uint32_t value;
  struct {
    uint32_t inst_pred_optimize : 1;
    uint32_t sc_output_screen_xy : 1;
    xenos::SampleControl sc_sample_cntl : 2;
    uint32_t _pad_4 : 4;

    uint32_t param_gen_pos : 8;
    uint32_t perfcounter_ref : 1;
    uint32_t yield_optimize : 1;
    uint32_t tx_cache_sel : 1;
    uint32_t _pad_19 : 13;
  };
  static constexpr Register register_index = XE_GPU_REG_SQ_CONTEXT_MISC;
};
static_assert_size(SQ_CONTEXT_MISC, sizeof(uint32_t));

union alignas(uint32_t) SQ_INTERPOLATOR_CNTL {
  uint32_t value;
  struct {
    uint32_t param_shade : 16;

    uint32_t sampling_pattern : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_SQ_INTERPOLATOR_CNTL;
};
static_assert_size(SQ_INTERPOLATOR_CNTL, sizeof(uint32_t));

union alignas(uint32_t) SQ_VS_CONST {
  uint32_t value;
  struct {
    uint32_t base : 9;
    uint32_t _pad_9 : 3;

    uint32_t size : 9;
    uint32_t _pad_21 : 11;
  };
  static constexpr Register register_index = XE_GPU_REG_SQ_VS_CONST;
};
static_assert_size(SQ_VS_CONST, sizeof(uint32_t));

union alignas(uint32_t) SQ_PS_CONST {
  uint32_t value;
  struct {
    uint32_t base : 9;
    uint32_t _pad_9 : 3;

    uint32_t size : 9;
    uint32_t _pad_21 : 11;
  };
  static constexpr Register register_index = XE_GPU_REG_SQ_PS_CONST;
};
static_assert_size(SQ_PS_CONST, sizeof(uint32_t));

union alignas(uint32_t) VGT_DMA_SIZE {
  uint32_t value;
  struct {
    uint32_t num_words : 24;
    uint32_t _pad_24 : 6;
    xenos::Endian swap_mode : 2;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_DMA_SIZE;
};

union alignas(uint32_t) VGT_DRAW_INITIATOR {
  uint32_t value;

  struct {
    xenos::PrimitiveType prim_type : 6;
    xenos::SourceSelect source_select : 2;

    xenos::MajorMode major_mode : 2;
    uint32_t _pad_10 : 1;
    xenos::IndexFormat index_size : 1;
    uint32_t not_eop : 1;
    uint32_t _pad_13 : 3;
    uint32_t num_indices : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_DRAW_INITIATOR;
};
static_assert_size(VGT_DRAW_INITIATOR, sizeof(uint32_t));

union alignas(uint32_t) VGT_MULTI_PRIM_IB_RESET_INDX {
  uint32_t value;
  struct {
    uint32_t reset_indx : 24;
    uint32_t _pad_24 : 8;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_MULTI_PRIM_IB_RESET_INDX;
};
static_assert_size(VGT_MULTI_PRIM_IB_RESET_INDX, sizeof(uint32_t));

union alignas(uint32_t) VGT_INDX_OFFSET {
  uint32_t value;
  struct {
    uint32_t indx_offset : 24;
    uint32_t _pad_24 : 8;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_INDX_OFFSET;
};
static_assert_size(VGT_INDX_OFFSET, sizeof(uint32_t));

union alignas(uint32_t) VGT_MIN_VTX_INDX {
  uint32_t value;
  struct {
    uint32_t min_indx : 24;
    uint32_t _pad_24 : 8;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_MIN_VTX_INDX;
};
static_assert_size(VGT_MIN_VTX_INDX, sizeof(uint32_t));

union alignas(uint32_t) VGT_MAX_VTX_INDX {
  uint32_t value;
  struct {
    uint32_t max_indx : 24;
    uint32_t _pad_24 : 8;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_MAX_VTX_INDX;
};
static_assert_size(VGT_MAX_VTX_INDX, sizeof(uint32_t));

union alignas(uint32_t) VGT_OUTPUT_PATH_CNTL {
  uint32_t value;
  struct {
    xenos::VGTOutputPath path_select : 2;
    uint32_t _pad_2 : 30;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_OUTPUT_PATH_CNTL;
};
static_assert_size(VGT_OUTPUT_PATH_CNTL, sizeof(uint32_t));

union alignas(uint32_t) VGT_HOS_CNTL {
  uint32_t value;
  struct {
    xenos::TessellationMode tess_mode : 2;
    uint32_t _pad_2 : 30;
  };
  static constexpr Register register_index = XE_GPU_REG_VGT_HOS_CNTL;
};
static_assert_size(VGT_HOS_CNTL, sizeof(uint32_t));

union alignas(uint32_t) PA_SU_POINT_MINMAX {
  uint32_t value;
  struct {
    uint32_t min_size : 16;
    uint32_t max_size : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SU_POINT_MINMAX;
};
static_assert_size(PA_SU_POINT_MINMAX, sizeof(uint32_t));

union alignas(uint32_t) PA_SU_POINT_SIZE {
  uint32_t value;
  struct {
    uint32_t height : 16;
    uint32_t width : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SU_POINT_SIZE;
};
static_assert_size(PA_SU_POINT_SIZE, sizeof(uint32_t));

union alignas(uint32_t) PA_SU_SC_MODE_CNTL {
  uint32_t value;
  struct {
    uint32_t cull_front : 1;
    uint32_t cull_back : 1;

    uint32_t face : 1;

    xenos::PolygonModeEnable poly_mode : 2;
    xenos::PolygonType polymode_front_ptype : 3;
    xenos::PolygonType polymode_back_ptype : 3;
    uint32_t poly_offset_front_enable : 1;
    uint32_t poly_offset_back_enable : 1;
    uint32_t poly_offset_para_enable : 1;
    uint32_t _pad_14 : 1;
    uint32_t msaa_enable : 1;
    uint32_t vtx_window_offset_enable : 1;

    uint32_t _pad_17 : 2;
    uint32_t provoking_vtx_last : 1;
    uint32_t persp_corr_dis : 1;
    uint32_t multi_prim_ib_ena : 1;
    uint32_t _pad_22 : 1;
    uint32_t quad_order_enable : 1;
    uint32_t sc_one_quad_per_clock : 1;

    uint32_t _pad_25 : 7;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SU_SC_MODE_CNTL;
};
static_assert_size(PA_SU_SC_MODE_CNTL, sizeof(uint32_t));

union alignas(uint32_t) PA_SU_VTX_CNTL {
  uint32_t value;
  struct {
    xenos::PixelCenter pix_center : 1;
    xenos::VertexRounding round_mode : 2;
    xenos::VertexQuantization quant_mode : 3;
    uint32_t _pad_6 : 26;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SU_VTX_CNTL;
};
static_assert_size(PA_SU_VTX_CNTL, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_MPASS_PS_CNTL {
  uint32_t value;
  struct {
    uint32_t mpass_pix_vec_per_pass : 20;
    uint32_t _pad_20 : 11;
    uint32_t mpass_ps_ena : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_MPASS_PS_CNTL;
};
static_assert_size(PA_SC_MPASS_PS_CNTL, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_VIZ_QUERY {
  uint32_t value;
  struct {
    uint32_t viz_query_ena : 1;
    uint32_t viz_query_id : 6;

    uint32_t kill_pix_post_hi_z : 1;

    uint32_t kill_pix_post_detail_mask : 1;
    uint32_t _pad_9 : 23;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_VIZ_QUERY;
};
static_assert_size(PA_SC_VIZ_QUERY, sizeof(uint32_t));

union alignas(uint32_t) PA_CL_CLIP_CNTL {
  uint32_t value;
  struct {
    uint32_t ucp_ena_0 : 1;
    uint32_t ucp_ena_1 : 1;
    uint32_t ucp_ena_2 : 1;
    uint32_t ucp_ena_3 : 1;
    uint32_t ucp_ena_4 : 1;
    uint32_t ucp_ena_5 : 1;
    uint32_t _pad_6 : 8;
    uint32_t ps_ucp_mode : 2;
    uint32_t clip_disable : 1;
    uint32_t ucp_cull_only_ena : 1;
    uint32_t boundary_edge_flag_ena : 1;
    uint32_t dx_clip_space_def : 1;
    uint32_t dis_clip_err_detect : 1;
    uint32_t vtx_kill_or : 1;
    uint32_t xy_nan_retain : 1;
    uint32_t z_nan_retain : 1;
    uint32_t w_nan_retain : 1;
    uint32_t _pad_25 : 7;
  };
  struct {
    uint32_t ucp_ena : 6;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_CL_CLIP_CNTL;
};
static_assert_size(PA_CL_CLIP_CNTL, sizeof(uint32_t));

union alignas(uint32_t) PA_CL_VTE_CNTL {
  uint32_t value;
  struct {
    uint32_t vport_x_scale_ena : 1;
    uint32_t vport_x_offset_ena : 1;
    uint32_t vport_y_scale_ena : 1;
    uint32_t vport_y_offset_ena : 1;
    uint32_t vport_z_scale_ena : 1;
    uint32_t vport_z_offset_ena : 1;
    uint32_t _pad_6 : 2;
    uint32_t vtx_xy_fmt : 1;
    uint32_t vtx_z_fmt : 1;
    uint32_t vtx_w0_fmt : 1;
    uint32_t perfcounter_ref : 1;
    uint32_t _pad_12 : 20;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_CL_VTE_CNTL;
};
static_assert_size(PA_CL_VTE_CNTL, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_SCREEN_SCISSOR_TL {
  uint32_t value;
  struct {
    int32_t tl_x : 15;
    uint32_t _pad_15 : 1;
    int32_t tl_y : 15;
    uint32_t _pad_31 : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_SCREEN_SCISSOR_TL;
};
static_assert_size(PA_SC_SCREEN_SCISSOR_TL, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_SCREEN_SCISSOR_BR {
  uint32_t value;
  struct {
    int32_t br_x : 15;
    uint32_t _pad_15 : 1;
    int32_t br_y : 15;
    uint32_t _pad_31 : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_SCREEN_SCISSOR_BR;
};
static_assert_size(PA_SC_SCREEN_SCISSOR_BR, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_WINDOW_OFFSET {
  uint32_t value;
  struct {
    int32_t window_x_offset : 15;
    uint32_t _pad_15 : 1;
    int32_t window_y_offset : 15;
    uint32_t _pad_31 : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_WINDOW_OFFSET;
};
static_assert_size(PA_SC_WINDOW_OFFSET, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_WINDOW_SCISSOR_TL {
  uint32_t value;
  struct {
    uint32_t tl_x : 14;
    uint32_t _pad_14 : 2;
    uint32_t tl_y : 14;
    uint32_t _pad_30 : 1;
    uint32_t window_offset_disable : 1;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_WINDOW_SCISSOR_TL;
};
static_assert_size(PA_SC_WINDOW_SCISSOR_TL, sizeof(uint32_t));

union alignas(uint32_t) PA_SC_WINDOW_SCISSOR_BR {
  uint32_t value;
  struct {
    uint32_t br_x : 14;
    uint32_t _pad_14 : 2;
    uint32_t br_y : 14;
    uint32_t _pad_30 : 2;
  };
  static constexpr Register register_index = XE_GPU_REG_PA_SC_WINDOW_SCISSOR_BR;
};
static_assert_size(PA_SC_WINDOW_SCISSOR_BR, sizeof(uint32_t));

union alignas(uint32_t) RB_MODECONTROL {
  uint32_t value;
  struct {
    xenos::EdramMode edram_mode : 3;
    uint32_t _pad_3 : 29;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_MODECONTROL;
};
static_assert_size(RB_MODECONTROL, sizeof(uint32_t));

union alignas(uint32_t) RB_SURFACE_INFO {
  uint32_t value;
  struct {
    uint32_t surface_pitch : 14;
    uint32_t _pad_14 : 2;
    xenos::MsaaSamples msaa_samples : 2;
    uint32_t hiz_pitch : 14;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_SURFACE_INFO;
};
static_assert_size(RB_SURFACE_INFO, sizeof(uint32_t));

union alignas(uint32_t) RB_COLORCONTROL {
  uint32_t value;
  struct {
    xenos::CompareFunction alpha_func : 3;
    uint32_t alpha_test_enable : 1;
    uint32_t alpha_to_mask_enable : 1;

    uint32_t _pad_5 : 19;

    uint32_t alpha_to_mask_offset0 : 2;
    uint32_t alpha_to_mask_offset1 : 2;
    uint32_t alpha_to_mask_offset2 : 2;
    uint32_t alpha_to_mask_offset3 : 2;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_COLORCONTROL;
};
static_assert_size(RB_COLORCONTROL, sizeof(uint32_t));

union alignas(uint32_t) RB_COLOR_INFO {
  uint32_t value;
  struct {
    uint32_t color_base : 11;
    uint32_t color_base_bit_11 : 1;
    uint32_t _pad_12 : 4;
    xenos::ColorRenderTargetFormat color_format : 4;
    int32_t color_exp_bias : 6;
    uint32_t _pad_26 : 6;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_COLOR_INFO;

  static const Register rt_register_indices[4];
};
static_assert_size(RB_COLOR_INFO, sizeof(uint32_t));

union alignas(uint32_t) RB_COLOR_MASK {
  uint32_t value;
  struct {
    uint32_t write_red0 : 1;
    uint32_t write_green0 : 1;
    uint32_t write_blue0 : 1;
    uint32_t write_alpha0 : 1;
    uint32_t write_red1 : 1;
    uint32_t write_green1 : 1;
    uint32_t write_blue1 : 1;
    uint32_t write_alpha1 : 1;
    uint32_t write_red2 : 1;
    uint32_t write_green2 : 1;
    uint32_t write_blue2 : 1;
    uint32_t write_alpha2 : 1;
    uint32_t write_red3 : 1;
    uint32_t write_green3 : 1;
    uint32_t write_blue3 : 1;
    uint32_t write_alpha3 : 1;
    uint32_t _pad_16 : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_COLOR_MASK;
};
static_assert_size(RB_COLOR_MASK, sizeof(uint32_t));

union alignas(uint32_t) RB_BLENDCONTROL {
  uint32_t value;
  struct {
    xenos::BlendFactor color_srcblend : 5;
    xenos::BlendOp color_comb_fcn : 3;
    xenos::BlendFactor color_destblend : 5;
    uint32_t _pad_13 : 3;
    xenos::BlendFactor alpha_srcblend : 5;
    xenos::BlendOp alpha_comb_fcn : 3;
    xenos::BlendFactor alpha_destblend : 5;

    uint32_t _pad_29 : 3;
  };

  static constexpr Register register_index = XE_GPU_REG_RB_BLENDCONTROL0;
  static const Register rt_register_indices[4];
};
static_assert_size(RB_BLENDCONTROL, sizeof(uint32_t));

union alignas(uint32_t) RB_DEPTHCONTROL {
  uint32_t value;
  struct {
    uint32_t stencil_enable : 1;
    uint32_t z_enable : 1;
    uint32_t z_write_enable : 1;

    uint32_t _pad_3 : 1;
    xenos::CompareFunction zfunc : 3;
    uint32_t backface_enable : 1;
    xenos::CompareFunction stencilfunc : 3;
    xenos::StencilOp stencilfail : 3;
    xenos::StencilOp stencilzpass : 3;
    xenos::StencilOp stencilzfail : 3;
    xenos::CompareFunction stencilfunc_bf : 3;
    xenos::StencilOp stencilfail_bf : 3;
    xenos::StencilOp stencilzpass_bf : 3;
    xenos::StencilOp stencilzfail_bf : 3;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_DEPTHCONTROL;
};
static_assert_size(RB_DEPTHCONTROL, sizeof(uint32_t));

union alignas(uint32_t) RB_HIZCONTROL {
  uint32_t value;
  struct {
    uint32_t hiz_write_enable : 1;
    uint32_t hiz_enable : 1;
    uint32_t _pad_2 : 30;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_HIZCONTROL;
};
static_assert_size(RB_HIZCONTROL, sizeof(uint32_t));

union alignas(uint32_t) RB_STENCILREFMASK {
  uint32_t value;
  struct {
    uint32_t stencilref : 8;
    uint32_t stencilmask : 8;
    uint32_t stencilwritemask : 8;
    uint32_t _pad_24 : 8;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_STENCILREFMASK;
};
static_assert_size(RB_STENCILREFMASK, sizeof(uint32_t));

union alignas(uint32_t) RB_DEPTH_INFO {
  uint32_t value;
  struct {
    uint32_t depth_base : 11;
    uint32_t depth_base_bit_11 : 1;
    uint32_t _pad_12 : 4;
    xenos::DepthRenderTargetFormat depth_format : 1;
    uint32_t _pad_17 : 15;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_DEPTH_INFO;
};
static_assert_size(RB_DEPTH_INFO, sizeof(uint32_t));

union alignas(uint32_t) RB_COPY_CONTROL {
  uint32_t value;
  struct {
    uint32_t copy_src_select : 3;
    uint32_t _pad_3 : 1;
    xenos::CopySampleSelect copy_sample_select : 3;
    uint32_t _pad_7 : 1;
    uint32_t color_clear_enable : 1;
    uint32_t depth_clear_enable : 1;
    uint32_t _pad_10 : 10;
    xenos::CopyCommand copy_command : 2;
    uint32_t _pad_22 : 10;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_COPY_CONTROL;
};
static_assert_size(RB_COPY_CONTROL, sizeof(uint32_t));

union alignas(uint32_t) RB_COPY_DEST_INFO {
  uint32_t value;
  struct {
    xenos::Endian128 copy_dest_endian : 3;
    uint32_t copy_dest_array : 1;
    uint32_t copy_dest_slice : 3;
    xenos::ColorFormat copy_dest_format : 6;
    xenos::SurfaceNumberFormat copy_dest_number : 3;
    int32_t copy_dest_exp_bias : 6;
    uint32_t _pad_22 : 2;
    uint32_t copy_dest_swap : 1;
    uint32_t _pad_25 : 7;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_COPY_DEST_INFO;
};
static_assert_size(RB_COPY_DEST_INFO, sizeof(uint32_t));

union alignas(uint32_t) RB_COPY_DEST_PITCH {
  uint32_t value;
  struct {
    uint32_t copy_dest_pitch : 14;
    uint32_t _pad_14 : 2;
    uint32_t copy_dest_height : 14;
    uint32_t _pad_30 : 2;
  };
  static constexpr Register register_index = XE_GPU_REG_RB_COPY_DEST_PITCH;
};
static_assert_size(RB_COPY_DEST_PITCH, sizeof(uint32_t));

union alignas(uint32_t) DC_LUT_RW_INDEX {
  uint32_t value;
  struct {
    uint32_t rw_index : 8;
    uint32_t _pad_8 : 24;
  };
  static constexpr Register register_index = XE_GPU_REG_DC_LUT_RW_INDEX;
};
static_assert_size(DC_LUT_RW_INDEX, sizeof(uint32_t));

union alignas(uint32_t) DC_LUT_SEQ_COLOR {
  uint32_t value;
  struct {
    uint32_t seq_color : 16;
    uint32_t _pad_16 : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_DC_LUT_SEQ_COLOR;
};
static_assert_size(DC_LUT_SEQ_COLOR, sizeof(uint32_t));

union alignas(uint32_t) DC_LUT_PWL_DATA {
  uint32_t value;
  struct {
    uint32_t base : 16;
    uint32_t delta : 16;
  };
  static constexpr Register register_index = XE_GPU_REG_DC_LUT_PWL_DATA;
};
static_assert_size(DC_LUT_PWL_DATA, sizeof(uint32_t));

union alignas(uint32_t) DC_LUT_30_COLOR {
  uint32_t value;
  struct {
    uint32_t color_10_blue : 10;
    uint32_t color_10_green : 10;
    uint32_t color_10_red : 10;
    uint32_t _pad_30 : 2;
  };
  static constexpr Register register_index = XE_GPU_REG_DC_LUT_30_COLOR;
};
static_assert_size(DC_LUT_30_COLOR, sizeof(uint32_t));

}

}
