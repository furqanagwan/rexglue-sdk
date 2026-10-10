/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Ported from has207/xenia-edge 0788c561e3
 *              (RG-GDK-032) for the ReXGlue runtime
 */

#include <rex/graphics/pipeline/shader/spirv_translator.h>
#include <cstdint>
#include <SPIRV/GLSL.std.450.h>
#include <rex/assert.h>
#include <rex/math.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/spirv_compatibility.h>
#include <rex/graphics/xenos_zpd_report.h>

namespace rex::graphics {

void SpirvShaderTranslator::FSI_LoadSampleMask() {
  assert_true(input_sample_mask_ != spv::NoResult);
  main_fsi_z_fail_sample_mask_ = const_uint_0_;
  main_fsi_stencil_fail_sample_mask_ = const_uint_0_;
  id_vector_temp_.clear();
  id_vector_temp_.push_back(const_int_0_);
  spv::Id input_sample_mask_value = builder_->createUnaryOp(
      spv::OpBitcast, type_uint_,
      builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassInput, input_sample_mask_, id_vector_temp_),
          spv::NoPrecision));

  if (FSI_GetMsaaSamples() != xenos::MsaaSamples::k2X) {
    main_fsi_sample_mask_ = input_sample_mask_value;
    return;
  }

  spv::Id const_uint_1 = builder_->makeUintConstant(1);
  if (native_2x_msaa_no_attachments_) {
    main_fsi_sample_mask_ = builder_->createBinOp(
        spv::OpShiftRightLogical, type_uint_,
        builder_->createUnaryOp(spv::OpBitReverse, type_uint_, input_sample_mask_value),
        builder_->makeUintConstant(32 - 2));
  } else {
    main_fsi_sample_mask_ = builder_->createQuadOp(
        spv::OpBitFieldInsert, type_uint_, input_sample_mask_value,
        builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, input_sample_mask_value,
                              builder_->makeUintConstant(3), const_uint_1),
        const_uint_1, builder_->makeUintConstant(32 - 1));
  }
}

void SpirvShaderTranslator::FSI_LoadEdramOffsets() {
  assert_true(input_fragment_coordinates_ != spv::NoResult);
  spv::Id const_uint_1 = builder_->makeUintConstant(1);
  spv::Id const_uint_2 = builder_->makeUintConstant(2);
  xenos::MsaaSamples msaa_samples = FSI_GetMsaaSamples();
  bool msaa_is_4x = msaa_samples >= xenos::MsaaSamples::k4X;
  bool msaa_is_2x_or_4x = msaa_samples >= xenos::MsaaSamples::k2X;
  const uint32_t resolution_scale[2] = {draw_resolution_scale_x_, draw_resolution_scale_y_};
  spv::Id guest_pixel[2], guest_subpixel[2];
  for (uint32_t i = 0; i < 2; ++i) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(int32_t(i)));
    spv::Id host_pixel = builder_->createUnaryOp(
        spv::OpConvertFToU, type_uint_,
        builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                        id_vector_temp_),
            spv::NoPrecision));
    if (resolution_scale[i] > 1) {
      spv::Id const_scale = builder_->makeUintConstant(resolution_scale[i]);
      guest_pixel[i] = builder_->createBinOp(spv::OpUDiv, type_uint_, host_pixel, const_scale);
      guest_subpixel[i] = builder_->createBinOp(spv::OpUMod, type_uint_, host_pixel, const_scale);
    } else {
      guest_pixel[i] = host_pixel;
      guest_subpixel[i] = spv::NoResult;
    }
  }

  auto expand_pixel_low_bit = [&](spv::Id pixel_x_or_y) {
    return builder_->createQuadOp(
        spv::OpBitFieldInsert, type_uint_,
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, pixel_x_or_y, const_uint_1),
        builder_->createBinOp(spv::OpShiftRightLogical, type_uint_, pixel_x_or_y, const_uint_1),
        const_uint_2, builder_->makeUintConstant(30));
  };

  spv::Id sample_u;
  if (msaa_is_4x) {
    sample_u = expand_pixel_low_bit(guest_pixel[0]);
  } else if (msaa_is_2x_or_4x) {
    sample_u = builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, guest_pixel[0],
                                     builder_->makeUintConstant(~uint32_t(2)));
  } else {
    sample_u = guest_pixel[0];
  }

  spv::Id sample_v;
  if (msaa_is_2x_or_4x) {
    sample_v = expand_pixel_low_bit(guest_pixel[1]);
    if (!msaa_is_4x) {
      sample_v = builder_->createBinOp(
          spv::OpBitwiseOr, type_uint_, sample_v,
          builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, guest_pixel[0], const_uint_2));
    }
  } else {
    sample_v = guest_pixel[1];
  }

  spv::Id sample_coordinates[2] = {sample_u, sample_v};
  for (uint32_t i = 0; i < 2; ++i) {
    if (resolution_scale[i] > 1) {
      sample_coordinates[i] = builder_->createBinOp(
          spv::OpIAdd, type_uint_,
          builder_->createBinOp(spv::OpIMul, type_uint_, sample_coordinates[i],
                                builder_->makeUintConstant(resolution_scale[i])),
          guest_subpixel[i]);
    }
  }

  uint32_t tile_width = xenos::kEdramTileWidthSamples * draw_resolution_scale_x_;
  spv::Id const_tile_half_width = builder_->makeUintConstant(tile_width >> 1);
  uint32_t tile_height = xenos::kEdramTileHeightSamples * draw_resolution_scale_y_;
  spv::Id const_tile_height = builder_->makeUintConstant(tile_height);
  spv::Id tile_half_index[2], tile_half_sample_coordinates[2];
  for (uint32_t i = 0; i < 2; ++i) {
    spv::Id sample_x_or_y = sample_coordinates[i];
    spv::Id tile_half_width_or_height = i ? const_tile_height : const_tile_half_width;
    tile_half_index[i] =
        builder_->createBinOp(spv::OpUDiv, type_uint_, sample_x_or_y, tile_half_width_or_height);
    tile_half_sample_coordinates[i] =
        builder_->createBinOp(spv::OpUMod, type_uint_, sample_x_or_y, tile_half_width_or_height);
  }

  spv::Id const_tile_width = builder_->makeUintConstant(tile_width);
  spv::Id row_offset_in_tile_at_32bpp = builder_->createBinOp(
      spv::OpIMul, type_uint_, tile_half_sample_coordinates[1], const_tile_width);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(
      builder_->makeIntConstant(kSystemConstantEdram32bppTilePitchDwordsScaled));
  spv::Id tile_row_offset_at_32bpp = builder_->createBinOp(
      spv::OpIMul, type_uint_,
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision),
      tile_half_index[1]);

  uint32_t tile_size = tile_width * tile_height;
  spv::Id const_tile_size = builder_->makeUintConstant(tile_size);

  spv::Id offset_in_first_tile_half_at_32bpp = builder_->createBinOp(
      spv::OpIAdd, type_uint_,
      builder_->createBinOp(
          spv::OpIAdd, type_uint_, tile_row_offset_at_32bpp,
          builder_->createBinOp(
              spv::OpIAdd, type_uint_,
              builder_->createBinOp(spv::OpIMul, type_uint_, const_tile_size,
                                    builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                                          tile_half_index[0], const_uint_1)),
              row_offset_in_tile_at_32bpp)),
      tile_half_sample_coordinates[0]);

  spv::Id is_second_tile_half = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, tile_half_index[0], const_uint_1),
      const_uint_0_);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramDepthBaseDwordsScaled));
  main_fsi_address_depth_ = builder_->createBinOp(
      spv::OpUMod, type_uint_,
      builder_->createBinOp(
          spv::OpIAdd, type_uint_,
          builder_->createLoad(
              builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                          id_vector_temp_),
              spv::NoPrecision),
          builder_->createBinOp(
              spv::OpIAdd, type_uint_, offset_in_first_tile_half_at_32bpp,
              builder_->createTriOp(spv::OpSelect, type_uint_, is_second_tile_half, const_uint_0_,
                                    const_tile_half_width))),
      builder_->makeUintConstant(tile_size * xenos::kEdramTileCount));

  if (current_shader().writes_color_targets()) {
    main_fsi_offset_32bpp_ =
        builder_->createBinOp(spv::OpIAdd, type_uint_, offset_in_first_tile_half_at_32bpp,
                              builder_->createTriOp(spv::OpSelect, type_uint_, is_second_tile_half,
                                                    const_tile_half_width, const_uint_0_));

    main_fsi_offset_64bpp_ = builder_->createBinOp(
        spv::OpIAdd, type_uint_,
        builder_->createBinOp(
            spv::OpIAdd, type_uint_,
            builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_, tile_row_offset_at_32bpp,
                                  const_uint_1),
            builder_->createBinOp(
                spv::OpIAdd, type_uint_,
                builder_->createBinOp(spv::OpIMul, type_uint_, const_tile_size, tile_half_index[0]),
                row_offset_in_tile_at_32bpp)),
        builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_, tile_half_sample_coordinates[0],
                              const_uint_1));
  }
}

spv::Id SpirvShaderTranslator::FSI_AddSampleOffset(spv::Id sample_0_address, uint32_t sample_index,
                                                   spv::Id is_64bpp) {
  if (!sample_index) {
    return sample_0_address;
  }

  uint32_t tile_width = xenos::kEdramTileWidthSamples * draw_resolution_scale_x_;
  uint32_t sample_row_offset = 2 * draw_resolution_scale_y_ * tile_width * (sample_index >> 1);
  uint32_t sample_column_offset_32bpp = 2 * draw_resolution_scale_x_ * (sample_index & 1);
  spv::Id sample_offset;
  if ((sample_index & 1) && is_64bpp != spv::NoResult) {
    sample_offset = builder_->createTriOp(
        spv::OpSelect, type_int_, is_64bpp,
        builder_->makeIntConstant(int32_t(sample_row_offset + 2 * sample_column_offset_32bpp)),
        builder_->makeIntConstant(int32_t(sample_row_offset + sample_column_offset_32bpp)));
  } else {
    sample_offset =
        builder_->makeIntConstant(int32_t(sample_row_offset + sample_column_offset_32bpp));
  }
  return builder_->createBinOp(spv::OpIAdd, type_int_, sample_0_address, sample_offset);
}

void SpirvShaderTranslator::FSI_AddMSAASamplesToZPD(bool count_passed, bool count_failed) {
  assert_true(edram_fragment_shader_interlock_);
  assert_true(buffer_zpd_counter_ != spv::NoResult);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantZpdFsiCounterIndex));
  spv::Id counter_index =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision);
  SpirvBuilder::IfBuilder if_counter_open(
      builder_->createBinOp(spv::OpINotEqual, type_bool_, counter_index,
                            builder_->makeUintConstant(UINT32_MAX)),
      spv::SelectionControlDontFlattenMask, *builder_);

  spv::StorageClass storage_class = features_.spirv_version >= spv::Spv_1_3
                                        ? spv::StorageClassStorageBuffer
                                        : spv::StorageClassUniform;
  spv::Id const_scope_device =
      builder_->makeUintConstant(static_cast<unsigned int>(spv::ScopeDevice));
  spv::Id const_semantics_relaxed = const_uint_0_;

  spv::Id counter_base = builder_->createBinOp(spv::OpIMul, type_uint_, counter_index,
                                               builder_->makeUintConstant(XenosZPDReport::kCount));

  auto add_lane = [&](spv::Id sample_mask, uint32_t lane, bool flag) {
    spv::Id sample_count = builder_->createUnaryOp(spv::OpBitCount, type_uint_, sample_mask);
    SpirvBuilder::IfBuilder if_any_samples(
        builder_->createBinOp(spv::OpINotEqual, type_bool_, sample_count, const_uint_0_),
        spv::SelectionControlDontFlattenMask, *builder_);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(const_int_0_);
    id_vector_temp_.push_back(
        builder_->createUnaryOp(spv::OpBitcast, type_int_,
                                builder_->createBinOp(spv::OpIAdd, type_uint_, counter_base,
                                                      builder_->makeUintConstant(lane))));
    spv::Id counter_ptr =
        builder_->createAccessChain(storage_class, buffer_zpd_counter_, id_vector_temp_);
    if (flag) {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(counter_ptr);
      id_vector_temp_.push_back(const_scope_device);
      id_vector_temp_.push_back(const_semantics_relaxed);
      id_vector_temp_.push_back(builder_->makeUintConstant(1));
      builder_->createNoResultOp(spv::OpAtomicStore, id_vector_temp_);
    } else {
      builder_->createQuadOp(spv::OpAtomicIAdd, type_uint_, counter_ptr, const_scope_device,
                             const_semantics_relaxed, sample_count);
    }
    if_any_samples.makeEndIf();
  };

  if (count_passed) {
    add_lane(builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_fsi_sample_mask_,
                                   builder_->makeUintConstant((uint32_t(1) << 4) - 1)),
             XenosZPDReport::kZPass, is_viz_survey_fragment_shader_);
  }
  if (count_failed && !is_viz_survey_fragment_shader_) {
    add_lane(main_fsi_z_fail_sample_mask_, XenosZPDReport::kZFail, false);
    add_lane(main_fsi_stencil_fail_sample_mask_, XenosZPDReport::kStencilFail, false);
  }

  if_counter_open.makeEndIf();
}

void SpirvShaderTranslator::FBO_AddMSAASamplesToZPDTotal() {
  assert_false(edram_fragment_shader_interlock_);
  assert_true(buffer_zpd_counter_ != spv::NoResult);
  assert_true(var_main_zpd_coverage_ != spv::NoResult);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantZpdFsiCounterIndex));
  spv::Id counter_index =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision);
  SpirvBuilder::IfBuilder if_counter_open(
      builder_->createBinOp(spv::OpINotEqual, type_bool_, counter_index,
                            builder_->makeUintConstant(UINT32_MAX)),
      spv::SelectionControlDontFlattenMask, *builder_);

  spv::Id coverage = builder_->createLoad(var_main_zpd_coverage_, spv::NoPrecision);
  if (features_.demote_to_helper_invocation) {
    id_vector_temp_.clear();
    coverage = builder_->createTriOp(
        spv::OpSelect, type_uint_,
        builder_->createOp(spv::OpIsHelperInvocationEXT, type_bool_, id_vector_temp_),
        const_uint_0_, coverage);
  }
  spv::Id sample_count = builder_->createUnaryOp(spv::OpBitCount, type_uint_, coverage);
  SpirvBuilder::IfBuilder if_any_samples(
      builder_->createBinOp(spv::OpINotEqual, type_bool_, sample_count, const_uint_0_),
      spv::SelectionControlDontFlattenMask, *builder_);

  spv::Id counter_offset = builder_->createBinOp(
      spv::OpIMul, type_uint_, counter_index, builder_->makeUintConstant(XenosZPDReport::kCount));
  id_vector_temp_.clear();
  id_vector_temp_.push_back(const_int_0_);
  id_vector_temp_.push_back(builder_->createUnaryOp(spv::OpBitcast, type_int_, counter_offset));
  spv::StorageClass storage_class = features_.spirv_version >= spv::Spv_1_3
                                        ? spv::StorageClassStorageBuffer
                                        : spv::StorageClassUniform;
  spv::Id counter_ptr =
      builder_->createAccessChain(storage_class, buffer_zpd_counter_, id_vector_temp_);
  spv::Id const_scope_device =
      builder_->makeUintConstant(static_cast<unsigned int>(spv::ScopeDevice));
  spv::Id const_semantics_relaxed = const_uint_0_;
  builder_->createQuadOp(spv::OpAtomicIAdd, type_uint_, counter_ptr, const_scope_device,
                         const_semantics_relaxed, sample_count);

  if_any_samples.makeEndIf();
  if_counter_open.makeEndIf();
}

void SpirvShaderTranslator::FSI_DepthStencilTest(bool sample_mask_potentially_narrowed_previouly) {
  uint32_t sample_count = FSI_GetSampleCount();
  bool is_early = FSI_IsDepthStencilEarly();
  bool implicit_early_z_write_allowed = current_shader().implicit_early_z_write_allowed();
  spv::Id const_uint_1 = builder_->makeUintConstant(1);
  spv::Id const_uint_8 = builder_->makeUintConstant(8);

  spv::Id depth_stencil_enabled = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_FSIDepthStencil)),
      const_uint_0_);
  SpirvBuilder::IfBuilder if_depth_stencil_enabled(depth_stencil_enabled,
                                                   spv::SelectionControlDontFlattenMask, *builder_);

  spv::Id center_depth32_unbiased;
  std::array<spv::Id, 2> depth_dxy;

  if (current_shader().writes_depth()) {
    assert_false(is_early);
    assert_true(output_or_var_fragment_depth_ != spv::NoResult);
    center_depth32_unbiased = builder_->createLoad(output_or_var_fragment_depth_, spv::NoPrecision);
    depth_dxy[0] = const_float_0_;
    depth_dxy[1] = const_float_0_;
  } else {
    assert_true(input_fragment_coordinates_ != spv::NoResult);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(2));
    center_depth32_unbiased = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                    id_vector_temp_),
        spv::NoPrecision);
    builder_->addCapability(spv::CapabilityDerivativeControl);
    depth_dxy[0] = builder_->createUnaryOp(spv::OpDPdxCoarse, type_float_, center_depth32_unbiased);
    depth_dxy[1] = builder_->createUnaryOp(spv::OpDPdyCoarse, type_float_, center_depth32_unbiased);
  }

  spv::Block* block_any_sample_covered_head = nullptr;
  spv::Block* block_any_sample_covered = nullptr;
  spv::Block* block_any_sample_covered_merge = nullptr;
  if (sample_mask_potentially_narrowed_previouly) {
    spv::Id any_sample_covered =
        builder_->createBinOp(spv::OpINotEqual, type_bool_, main_fsi_sample_mask_, const_uint_0_);
    block_any_sample_covered_head = builder_->getBuildPoint();
    block_any_sample_covered = &builder_->makeNewBlock();
    block_any_sample_covered_merge = &builder_->makeNewBlock();
    builder_->createSelectionMerge(block_any_sample_covered_merge,
                                   spv::SelectionControlDontFlattenMask);
    builder_->createConditionalBranch(any_sample_covered, block_any_sample_covered,
                                      block_any_sample_covered_merge);
    builder_->setBuildPoint(block_any_sample_covered);
  }

  xenos::MsaaSamples msaa_samples = FSI_GetMsaaSamples();
  bool msaa_is_2x_4x = msaa_samples >= xenos::MsaaSamples::k2X;
  bool msaa_is_4x = msaa_samples >= xenos::MsaaSamples::k4X;
  spv::Id depth_is_float24 = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_DepthFloat24)),
      const_uint_0_);
  spv::Id depth_pass_if_less = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_FSIDepthPassIfLess)),
      const_uint_0_);
  spv::Id depth_pass_if_equal = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_FSIDepthPassIfEqual)),
      const_uint_0_);
  spv::Id depth_pass_if_greater = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_FSIDepthPassIfGreater)),
      const_uint_0_);
  spv::Id depth_write = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_FSIDepthWrite)),
      const_uint_0_);
  spv::Id stencil_enabled = builder_->createBinOp(
      spv::OpINotEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                            builder_->makeUintConstant(kSysFlag_FSIStencilTest)),
      const_uint_0_);
  spv::Id early_write =
      (is_early && implicit_early_z_write_allowed)
          ? builder_->createBinOp(
                spv::OpINotEqual, type_bool_,
                builder_->createBinOp(
                    spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                    builder_->makeUintConstant(kSysFlag_FSIDepthStencilEarlyWrite)),
                const_uint_0_)
          : spv::NoResult;
  spv::Id not_early_write =
      (is_early && implicit_early_z_write_allowed)
          ? builder_->createUnaryOp(spv::OpLogicalNot, type_bool_, early_write)
          : spv::NoResult;
  assert_true(input_front_facing_ != spv::NoResult);
  spv::Id front_facing = builder_->createLoad(input_front_facing_, spv::NoPrecision);
  spv::Id poly_offset_scale, poly_offset_offset, stencil_parameters;
  {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramPolyOffsetFrontScale));
    spv::Id poly_offset_front_scale = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramPolyOffsetBackScale));
    spv::Id poly_offset_back_scale = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    poly_offset_scale = builder_->createTriOp(spv::OpSelect, type_float_, front_facing,
                                              poly_offset_front_scale, poly_offset_back_scale);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramPolyOffsetFrontOffset));
    spv::Id poly_offset_front_offset = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramPolyOffsetBackOffset));
    spv::Id poly_offset_back_offset = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    poly_offset_offset = builder_->createTriOp(spv::OpSelect, type_float_, front_facing,
                                               poly_offset_front_offset, poly_offset_back_offset);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramStencilFront));
    spv::Id stencil_parameters_front = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramStencilBack));
    spv::Id stencil_parameters_back = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    stencil_parameters =
        builder_->createTriOp(spv::OpSelect, type_uint2_,
                              builder_->smearScalar(spv::NoPrecision, front_facing, type_bool2_),
                              stencil_parameters_front, stencil_parameters_back);
  }
  spv::Id stencil_reference_masks =
      builder_->createCompositeExtract(stencil_parameters, type_uint_, 0);
  spv::Id stencil_reference = builder_->createTriOp(
      spv::OpBitFieldUExtract, type_uint_, stencil_reference_masks, const_uint_0_, const_uint_8);
  spv::Id stencil_read_mask = builder_->createTriOp(
      spv::OpBitFieldUExtract, type_uint_, stencil_reference_masks, const_uint_8, const_uint_8);
  spv::Id stencil_reference_read_masked =
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, stencil_reference, stencil_read_mask);
  spv::Id stencil_write_mask =
      builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, stencil_reference_masks,
                            builder_->makeUintConstant(16), const_uint_8);
  spv::Id stencil_write_keep_mask =
      builder_->createUnaryOp(spv::OpNot, type_uint_, stencil_write_mask);
  spv::Id stencil_func_ops = builder_->createCompositeExtract(stencil_parameters, type_uint_, 1);
  spv::Id stencil_pass_if_less =
      builder_->createBinOp(spv::OpINotEqual, type_bool_,
                            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, stencil_func_ops,
                                                  builder_->makeUintConstant(uint32_t(1) << 0)),
                            const_uint_0_);
  spv::Id stencil_pass_if_equal =
      builder_->createBinOp(spv::OpINotEqual, type_bool_,
                            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, stencil_func_ops,
                                                  builder_->makeUintConstant(uint32_t(1) << 1)),
                            const_uint_0_);
  spv::Id stencil_pass_if_greater =
      builder_->createBinOp(spv::OpINotEqual, type_bool_,
                            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, stencil_func_ops,
                                                  builder_->makeUintConstant(uint32_t(1) << 2)),
                            const_uint_0_);

  spv::Id center_depth32_biased;

  if (current_shader().writes_depth()) {
    center_depth32_biased = center_depth32_unbiased;
  } else {
    std::array<spv::Id, 2> depth_dxy_abs;
    for (uint32_t i = 0; i < 2; ++i) {
      depth_dxy_abs[i] = builder_->createUnaryBuiltinCall(type_float_, ext_inst_glsl_std_450_,
                                                          GLSLstd450FAbs, depth_dxy[i]);
    }
    spv::Id depth_max_slope = builder_->createBinBuiltinCall(
        type_float_, ext_inst_glsl_std_450_, GLSLstd450FMax, depth_dxy_abs[0], depth_dxy_abs[1]);

    spv::Id slope_scaled_poly_offset = builder_->createNoContractionBinOp(
        spv::OpFMul, type_float_, poly_offset_scale, depth_max_slope);
    spv::Id poly_offset = builder_->createNoContractionBinOp(
        spv::OpFAdd, type_float_, slope_scaled_poly_offset, poly_offset_offset);

    center_depth32_biased = builder_->createNoContractionBinOp(
        spv::OpFAdd, type_float_, center_depth32_unbiased, poly_offset);
  }

  spv::Id new_sample_mask = main_fsi_sample_mask_;
  spv::Id z_fail_sample_mask = const_uint_0_;
  spv::Id stencil_fail_sample_mask = const_uint_0_;
  std::array<spv::Id, 4> late_write_depth_stencil{};
  for (uint32_t i = 0; i < sample_count; ++i) {
    spv::Id sample_covered =
        builder_->createBinOp(spv::OpINotEqual, type_bool_,
                              builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, new_sample_mask,
                                                    builder_->makeUintConstant(uint32_t(1) << i)),
                              const_uint_0_);
    SpirvBuilder::IfBuilder if_sample_covered(sample_covered, spv::SelectionControlDontFlattenMask,
                                              *builder_);

    spv::Id sample_address = FSI_AddSampleOffset(main_fsi_address_depth_, i);
    id_vector_temp_.clear();

    id_vector_temp_.push_back(const_int_0_);
    id_vector_temp_.push_back(sample_address);
    spv::Id sample_access_chain = builder_->createAccessChain(
        features_.spirv_version >= spv::Spv_1_3 ? spv::StorageClassStorageBuffer
                                                : spv::StorageClassUniform,
        buffer_edram_, id_vector_temp_);
    spv::Id old_depth_stencil = builder_->createLoad(sample_access_chain, spv::NoPrecision);

    std::array<spv::Id, 2> sample_location;
    switch (i) {
      case 0: {
        if (!msaa_is_2x_4x) {
          sample_location.fill(const_float_0_);
        } else {
          const int8_t* sample_location_int = (!msaa_is_4x && native_2x_msaa_no_attachments_)
                                                  ? draw_util::kD3D10StandardSamplePositions2x[1]
                                                  : draw_util::kD3D10StandardSamplePositions4x[0];
          for (uint32_t j = 0; j < 2; ++j) {
            sample_location[j] =
                builder_->makeFloatConstant(sample_location_int[j] * (1.0f / 16.0f));
          }
        }
      } break;
      case 1: {
        const int8_t* sample_location_int =
            msaa_is_4x
                ? draw_util::kD3D10StandardSamplePositions4x[1]
                : (native_2x_msaa_no_attachments_ ? draw_util::kD3D10StandardSamplePositions2x[0]
                                                  : draw_util::kD3D10StandardSamplePositions4x[3]);
        for (uint32_t j = 0; j < 2; ++j) {
          sample_location[j] = builder_->makeFloatConstant(sample_location_int[j] * (1.0f / 16.0f));
        }
      } break;
      default: {
        const int8_t* sample_location_int = draw_util::kD3D10StandardSamplePositions4x[i];
        for (uint32_t j = 0; j < 2; ++j) {
          sample_location[j] = builder_->makeFloatConstant(sample_location_int[j] * (1.0f / 16.0f));
        }
      } break;
    }
    std::array<spv::Id, 2> sample_depth_dxy;
    for (uint32_t j = 0; j < 2; ++j) {
      sample_depth_dxy[j] = builder_->createNoContractionBinOp(spv::OpFMul, type_float_,
                                                               sample_location[j], depth_dxy[j]);
    }
    spv::Id sample_depth32 = builder_->createTriBuiltinCall(
        type_float_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
        builder_->createNoContractionBinOp(
            spv::OpFAdd, type_float_, center_depth32_biased,
            builder_->createNoContractionBinOp(spv::OpFAdd, type_float_, sample_depth_dxy[0],
                                               sample_depth_dxy[1])),
        const_float_0_, const_float_1_);

    SpirvBuilder::IfBuilder depth_format_if(depth_is_float24, spv::SelectionControlDontFlattenMask,
                                            *builder_);
    spv::Id sample_depth_float24 = SpirvShaderTranslator::PreClampedDepthTo20e4(
        *builder_, sample_depth32, true, false, ext_inst_glsl_std_450_);
    depth_format_if.makeBeginElse();

    spv::Id sample_depth_unorm24 = builder_->createUnaryOp(
        spv::OpConvertFToU, type_uint_,
        builder_->createUnaryBuiltinCall(
            type_float_, ext_inst_glsl_std_450_, GLSLstd450RoundEven,
            builder_->createNoContractionBinOp(spv::OpFMul, type_float_, sample_depth32,
                                               builder_->makeFloatConstant(float(0xFFFFFF)))));
    depth_format_if.makeEndIf();

    spv::Id sample_depth24 =
        depth_format_if.createMergePhi(sample_depth_float24, sample_depth_unorm24);

    spv::Id old_depth = builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                              old_depth_stencil, const_uint_8);
    spv::Id depth_passed = builder_->createBinOp(
        spv::OpLogicalAnd, type_bool_, depth_pass_if_less,
        builder_->createBinOp(spv::OpULessThan, type_bool_, sample_depth24, old_depth));
    depth_passed = builder_->createBinOp(
        spv::OpLogicalOr, type_bool_, depth_passed,
        builder_->createBinOp(
            spv::OpLogicalAnd, type_bool_, depth_pass_if_equal,
            builder_->createBinOp(spv::OpIEqual, type_bool_, sample_depth24, old_depth)));
    depth_passed = builder_->createBinOp(
        spv::OpLogicalOr, type_bool_, depth_passed,
        builder_->createBinOp(
            spv::OpLogicalAnd, type_bool_, depth_pass_if_greater,
            builder_->createBinOp(spv::OpUGreaterThan, type_bool_, sample_depth24, old_depth)));

    SpirvBuilder::IfBuilder stencil_if(stencil_enabled, spv::SelectionControlDontFlattenMask,
                                       *builder_);
    spv::Id stencil_passed_if_enabled;
    spv::Id new_stencil_and_old_depth_if_stencil_enabled;
    {
      spv::Id old_stencil_read_masked = builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                                                              old_depth_stencil, stencil_read_mask);
      stencil_passed_if_enabled = builder_->createBinOp(
          spv::OpLogicalAnd, type_bool_, stencil_pass_if_less,
          builder_->createBinOp(spv::OpULessThan, type_bool_, stencil_reference_read_masked,
                                old_stencil_read_masked));
      stencil_passed_if_enabled = builder_->createBinOp(
          spv::OpLogicalOr, type_bool_, stencil_passed_if_enabled,
          builder_->createBinOp(
              spv::OpLogicalAnd, type_bool_, stencil_pass_if_equal,
              builder_->createBinOp(spv::OpIEqual, type_bool_, stencil_reference_read_masked,
                                    old_stencil_read_masked)));
      stencil_passed_if_enabled = builder_->createBinOp(
          spv::OpLogicalOr, type_bool_, stencil_passed_if_enabled,
          builder_->createBinOp(
              spv::OpLogicalAnd, type_bool_, stencil_pass_if_greater,
              builder_->createBinOp(spv::OpUGreaterThan, type_bool_, stencil_reference_read_masked,
                                    old_stencil_read_masked)));
      spv::Id stencil_op = builder_->createTriOp(
          spv::OpBitFieldUExtract, type_uint_, stencil_func_ops,
          builder_->createTriOp(
              spv::OpSelect, type_uint_, stencil_passed_if_enabled,
              builder_->createTriOp(spv::OpSelect, type_uint_, depth_passed,
                                    builder_->makeUintConstant(6), builder_->makeUintConstant(9)),
              builder_->makeUintConstant(3)),
          builder_->makeUintConstant(3));
      spv::Block& block_stencil_op_head = *builder_->getBuildPoint();
      spv::Block& block_stencil_op_keep = builder_->makeNewBlock();
      spv::Block& block_stencil_op_zero = builder_->makeNewBlock();
      spv::Block& block_stencil_op_replace = builder_->makeNewBlock();
      spv::Block& block_stencil_op_increment_clamp = builder_->makeNewBlock();
      spv::Block& block_stencil_op_decrement_clamp = builder_->makeNewBlock();
      spv::Block& block_stencil_op_invert = builder_->makeNewBlock();
      spv::Block& block_stencil_op_increment_wrap = builder_->makeNewBlock();
      spv::Block& block_stencil_op_decrement_wrap = builder_->makeNewBlock();
      spv::Block& block_stencil_op_merge = builder_->makeNewBlock();
      builder_->createSelectionMerge(&block_stencil_op_merge, spv::SelectionControlDontFlattenMask);
      {
        std::unique_ptr<spv::Instruction> stencil_op_switch_op =
            std::make_unique<spv::Instruction>(spv::OpSwitch);
        stencil_op_switch_op->addIdOperand(stencil_op);

        stencil_op_switch_op->addIdOperand(block_stencil_op_keep.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kZero));
        stencil_op_switch_op->addIdOperand(block_stencil_op_zero.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kReplace));
        stencil_op_switch_op->addIdOperand(block_stencil_op_replace.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kIncrementClamp));
        stencil_op_switch_op->addIdOperand(block_stencil_op_increment_clamp.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kDecrementClamp));
        stencil_op_switch_op->addIdOperand(block_stencil_op_decrement_clamp.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kInvert));
        stencil_op_switch_op->addIdOperand(block_stencil_op_invert.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kIncrementWrap));
        stencil_op_switch_op->addIdOperand(block_stencil_op_increment_wrap.getId());
        stencil_op_switch_op->addImmediateOperand(int32_t(xenos::StencilOp::kDecrementWrap));
        stencil_op_switch_op->addIdOperand(block_stencil_op_decrement_wrap.getId());
        builder_->getBuildPoint()->addInstruction(std::move(stencil_op_switch_op));
      }
      block_stencil_op_keep.addPredecessor(&block_stencil_op_head);
      block_stencil_op_zero.addPredecessor(&block_stencil_op_head);
      block_stencil_op_replace.addPredecessor(&block_stencil_op_head);
      block_stencil_op_increment_clamp.addPredecessor(&block_stencil_op_head);
      block_stencil_op_decrement_clamp.addPredecessor(&block_stencil_op_head);
      block_stencil_op_invert.addPredecessor(&block_stencil_op_head);
      block_stencil_op_increment_wrap.addPredecessor(&block_stencil_op_head);
      block_stencil_op_decrement_wrap.addPredecessor(&block_stencil_op_head);

      builder_->setBuildPoint(&block_stencil_op_keep);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_zero);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_replace);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_increment_clamp);
      spv::Id new_stencil_in_low_bits_increment_clamp = builder_->createBinOp(
          spv::OpIAdd, type_uint_,
          builder_->createBinBuiltinCall(
              type_uint_, ext_inst_glsl_std_450_, GLSLstd450UMin,
              builder_->makeUintConstant(UINT8_MAX - 1),
              builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, old_depth_stencil,
                                    builder_->makeUintConstant(UINT8_MAX))),
          const_uint_1);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_decrement_clamp);
      spv::Id new_stencil_in_low_bits_decrement_clamp = builder_->createBinOp(
          spv::OpISub, type_uint_,
          builder_->createBinBuiltinCall(
              type_uint_, ext_inst_glsl_std_450_, GLSLstd450UMax, const_uint_1,
              builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, old_depth_stencil,
                                    builder_->makeUintConstant(UINT8_MAX))),
          const_uint_1);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_invert);
      spv::Id new_stencil_in_low_bits_invert =
          builder_->createUnaryOp(spv::OpNot, type_uint_, old_depth_stencil);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_increment_wrap);
      spv::Id new_stencil_in_low_bits_increment_wrap =
          builder_->createBinOp(spv::OpIAdd, type_uint_, old_depth_stencil, const_uint_1);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_decrement_wrap);
      spv::Id new_stencil_in_low_bits_decrement_wrap =
          builder_->createBinOp(spv::OpISub, type_uint_, old_depth_stencil, const_uint_1);
      builder_->createBranch(&block_stencil_op_merge);

      builder_->setBuildPoint(&block_stencil_op_merge);
      id_vector_temp_.clear();
      id_vector_temp_.reserve(2 * 8);
      id_vector_temp_.push_back(old_depth_stencil);
      id_vector_temp_.push_back(block_stencil_op_keep.getId());
      id_vector_temp_.push_back(const_uint_0_);
      id_vector_temp_.push_back(block_stencil_op_zero.getId());
      id_vector_temp_.push_back(stencil_reference);
      id_vector_temp_.push_back(block_stencil_op_replace.getId());
      id_vector_temp_.push_back(new_stencil_in_low_bits_increment_clamp);
      id_vector_temp_.push_back(block_stencil_op_increment_clamp.getId());
      id_vector_temp_.push_back(new_stencil_in_low_bits_decrement_clamp);
      id_vector_temp_.push_back(block_stencil_op_decrement_clamp.getId());
      id_vector_temp_.push_back(new_stencil_in_low_bits_invert);
      id_vector_temp_.push_back(block_stencil_op_invert.getId());
      id_vector_temp_.push_back(new_stencil_in_low_bits_increment_wrap);
      id_vector_temp_.push_back(block_stencil_op_increment_wrap.getId());
      id_vector_temp_.push_back(new_stencil_in_low_bits_decrement_wrap);
      id_vector_temp_.push_back(block_stencil_op_decrement_wrap.getId());
      spv::Id new_stencil_in_low_bits_if_enabled =
          builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);

      new_stencil_and_old_depth_if_stencil_enabled = builder_->createBinOp(
          spv::OpBitwiseOr, type_uint_,
          builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, old_depth_stencil,
                                stencil_write_keep_mask),
          builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, new_stencil_in_low_bits_if_enabled,
                                stencil_write_mask));
    }
    stencil_if.makeEndIf();

    spv::Id stencil_passed =
        stencil_if.createMergePhi(stencil_passed_if_enabled, builder_->makeBoolConstant(true));
    spv::Id new_stencil_and_old_depth =
        stencil_if.createMergePhi(new_stencil_and_old_depth_if_stencil_enabled, old_depth_stencil);

    spv::Id depth_stencil_passed =
        builder_->createBinOp(spv::OpLogicalAnd, type_bool_, depth_passed, stencil_passed);
    spv::Id z_fail_sample_mask_after_sample = z_fail_sample_mask;
    spv::Id stencil_fail_sample_mask_after_sample = stencil_fail_sample_mask;
    if (zpd_full_counters_) {
      spv::Id sample_bit = builder_->makeUintConstant(uint32_t(1) << i);
      z_fail_sample_mask_after_sample = builder_->createTriOp(
          spv::OpSelect, type_uint_,
          builder_->createBinOp(
              spv::OpLogicalAnd, type_bool_, stencil_passed,
              builder_->createUnaryOp(spv::OpLogicalNot, type_bool_, depth_passed)),
          builder_->createBinOp(spv::OpBitwiseOr, type_uint_, z_fail_sample_mask, sample_bit),
          z_fail_sample_mask);
      stencil_fail_sample_mask_after_sample = builder_->createTriOp(
          spv::OpSelect, type_uint_,
          builder_->createUnaryOp(spv::OpLogicalNot, type_bool_, stencil_passed),
          builder_->createBinOp(spv::OpBitwiseOr, type_uint_, stencil_fail_sample_mask, sample_bit),
          stencil_fail_sample_mask);
    }
    spv::Id new_sample_mask_after_sample = builder_->createTriOp(
        spv::OpSelect, type_uint_, depth_stencil_passed, new_sample_mask,
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, new_sample_mask,
                              builder_->makeUintConstant(~(uint32_t(1) << i))));

    spv::Id new_stencil_and_unconditional_new_depth =
        builder_->createQuadOp(spv::OpBitFieldInsert, type_uint_, new_stencil_and_old_depth,
                               sample_depth24, const_uint_8, builder_->makeUintConstant(24));
    spv::Id new_depth_stencil = builder_->createTriOp(
        spv::OpSelect, type_uint_,
        builder_->createBinOp(spv::OpLogicalAnd, type_bool_, depth_stencil_passed, depth_write),
        new_stencil_and_unconditional_new_depth, new_stencil_and_old_depth);

    spv::Id new_depth_stencil_different =
        builder_->createBinOp(spv::OpINotEqual, type_bool_, new_depth_stencil, old_depth_stencil);
    spv::Id new_depth_stencil_write_condition = spv::NoResult;
    if (is_early) {
      if (implicit_early_z_write_allowed) {
        new_sample_mask_after_sample = builder_->createTriOp(
            spv::OpSelect, type_uint_,
            builder_->createBinOp(spv::OpLogicalAnd, type_bool_, new_depth_stencil_different,
                                  not_early_write),
            builder_->createBinOp(spv::OpBitwiseOr, type_uint_, new_sample_mask_after_sample,
                                  builder_->makeUintConstant(uint32_t(1) << (4 + i))),
            new_sample_mask_after_sample);
        new_depth_stencil_write_condition = builder_->createBinOp(
            spv::OpLogicalAnd, type_bool_, new_depth_stencil_different, early_write);
      } else {
        new_sample_mask_after_sample = builder_->createTriOp(
            spv::OpSelect, type_uint_, new_depth_stencil_different,
            builder_->createBinOp(spv::OpBitwiseOr, type_uint_, new_sample_mask_after_sample,
                                  builder_->makeUintConstant(uint32_t(1) << (4 + i))),
            new_sample_mask_after_sample);
      }
    } else {
      new_depth_stencil_write_condition = new_depth_stencil_different;
    }
    if (new_depth_stencil_write_condition != spv::NoResult) {
      SpirvBuilder::IfBuilder new_depth_stencil_write_if(
          new_depth_stencil_write_condition, spv::SelectionControlDontFlattenMask, *builder_);
      builder_->createStore(new_depth_stencil, sample_access_chain);
      new_depth_stencil_write_if.makeEndIf();
    }

    if_sample_covered.makeEndIf();
    new_sample_mask =
        if_sample_covered.createMergePhi(new_sample_mask_after_sample, new_sample_mask);
    if (zpd_full_counters_) {
      z_fail_sample_mask =
          if_sample_covered.createMergePhi(z_fail_sample_mask_after_sample, z_fail_sample_mask);
      stencil_fail_sample_mask = if_sample_covered.createMergePhi(
          stencil_fail_sample_mask_after_sample, stencil_fail_sample_mask);
    }
    if (is_early) {
      late_write_depth_stencil[i] =
          if_sample_covered.createMergePhi(new_depth_stencil, const_uint_0_);
    }
  }

  if (block_any_sample_covered_merge) {
    builder_->createBranch(block_any_sample_covered_merge);
    spv::Block& block_any_sample_covered_end = *builder_->getBuildPoint();
    builder_->setBuildPoint(block_any_sample_covered_merge);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(new_sample_mask);
    id_vector_temp_.push_back(block_any_sample_covered_end.getId());
    id_vector_temp_.push_back(main_fsi_sample_mask_);
    id_vector_temp_.push_back(block_any_sample_covered_head->getId());
    new_sample_mask = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
    if (zpd_full_counters_) {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(z_fail_sample_mask);
      id_vector_temp_.push_back(block_any_sample_covered_end.getId());
      id_vector_temp_.push_back(const_uint_0_);
      id_vector_temp_.push_back(block_any_sample_covered_head->getId());
      z_fail_sample_mask = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
      id_vector_temp_.clear();
      id_vector_temp_.push_back(stencil_fail_sample_mask);
      id_vector_temp_.push_back(block_any_sample_covered_end.getId());
      id_vector_temp_.push_back(const_uint_0_);
      id_vector_temp_.push_back(block_any_sample_covered_head->getId());
      stencil_fail_sample_mask = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
    }
    if (is_early) {
      for (uint32_t i = 0; i < sample_count; ++i) {
        id_vector_temp_.clear();
        id_vector_temp_.push_back(late_write_depth_stencil[i]);
        id_vector_temp_.push_back(block_any_sample_covered_end.getId());
        id_vector_temp_.push_back(const_uint_0_);
        id_vector_temp_.push_back(block_any_sample_covered_head->getId());
        late_write_depth_stencil[i] = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
      }
    }
  }
  if_depth_stencil_enabled.makeEndIf();
  main_fsi_sample_mask_ =
      if_depth_stencil_enabled.createMergePhi(new_sample_mask, main_fsi_sample_mask_);
  if (zpd_full_counters_) {
    main_fsi_z_fail_sample_mask_ =
        if_depth_stencil_enabled.createMergePhi(z_fail_sample_mask, const_uint_0_);
    main_fsi_stencil_fail_sample_mask_ =
        if_depth_stencil_enabled.createMergePhi(stencil_fail_sample_mask, const_uint_0_);
  }
  if (is_early) {
    for (uint32_t i = 0; i < sample_count; ++i) {
      main_fsi_late_write_depth_stencil_[i] =
          if_depth_stencil_enabled.createMergePhi(late_write_depth_stencil[i], const_uint_0_);
    }
  }
}

}
