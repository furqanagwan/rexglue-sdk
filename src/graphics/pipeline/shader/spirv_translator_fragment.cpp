

#include <rex/graphics/pipeline/shader/spirv_translator.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fmt/format.h>
#include <SPIRV/GLSL.std.450.h>
#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string/buffer.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/spirv_compatibility.h>
#include <rex/graphics/pipeline/shader/spirv.h>
#include <rex/graphics/xenos_zpd_report.h>

namespace rex::graphics {

void SpirvShaderTranslator::StartFragmentShaderBeforeMain() {
  Modification shader_modification = GetSpirvShaderModification();

  if (edram_fragment_shader_interlock_) {
    builder_->addExtension("SPV_EXT_fragment_shader_interlock");

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeRuntimeArray(type_uint_));

    builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride, sizeof(uint32_t));
    spv::Id type_edram = builder_->makeStructType(id_vector_temp_, "XeEdram");
    builder_->addMemberName(type_edram, 0, "edram");
    builder_->addMemberDecoration(type_edram, 0, spv::DecorationCoherent);
    builder_->addMemberDecoration(type_edram, 0, spv::DecorationRestrict);
    builder_->addMemberDecoration(type_edram, 0, spv::DecorationOffset, 0);
    builder_->addDecoration(type_edram, features_.spirv_version >= spv::Spv_1_3
                                            ? spv::DecorationBlock
                                            : spv::DecorationBufferBlock);
    buffer_edram_ = builder_->createVariable(spv::NoPrecision,
                                             features_.spirv_version >= spv::Spv_1_3
                                                 ? spv::StorageClassStorageBuffer
                                                 : spv::StorageClassUniform,
                                             type_edram, "xe_edram");
    builder_->addDecoration(buffer_edram_, spv::DecorationDescriptorSet,
                            int(kDescriptorSetSharedMemoryAndEdram));
    builder_->addDecoration(buffer_edram_, spv::DecorationBinding, 2);
    if (features_.spirv_version >= spv::Spv_1_4) {
      main_interface_.push_back(buffer_edram_);
    }
  }

  if (edram_fragment_shader_interlock_ || IsZpdTotal()) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeRuntimeArray(type_uint_));
    builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride, sizeof(uint32_t));
    spv::Id type_zpd_counter = builder_->makeStructType(id_vector_temp_, "XeZPDCounter");
    builder_->addMemberName(type_zpd_counter, 0, "counter");
    builder_->addMemberDecoration(type_zpd_counter, 0, spv::DecorationCoherent);
    builder_->addMemberDecoration(type_zpd_counter, 0, spv::DecorationRestrict);
    builder_->addMemberDecoration(type_zpd_counter, 0, spv::DecorationOffset, 0);
    builder_->addDecoration(type_zpd_counter, features_.spirv_version >= spv::Spv_1_3
                                                  ? spv::DecorationBlock
                                                  : spv::DecorationBufferBlock);
    buffer_zpd_counter_ = builder_->createVariable(spv::NoPrecision,
                                                   features_.spirv_version >= spv::Spv_1_3
                                                       ? spv::StorageClassStorageBuffer
                                                       : spv::StorageClassUniform,
                                                   type_zpd_counter, "xe_zpd_counter");
    builder_->addDecoration(buffer_zpd_counter_, spv::DecorationDescriptorSet,
                            int(kDescriptorSetSharedMemoryAndEdram));
    builder_->addDecoration(buffer_zpd_counter_, spv::DecorationBinding, 1);
    if (features_.spirv_version >= spv::Spv_1_4) {
      main_interface_.push_back(buffer_zpd_counter_);
    }
  }

  bool param_gen_needed =
      !is_depth_only_fragment_shader_ && GetPsParamGenInterpolator() != UINT32_MAX;

  if (!is_depth_only_fragment_shader_) {
    uint32_t input_location = 0;

    bool use_barycentric_interpolation = precise_interpolation_ &&
                                         features_.fragment_shader_barycentric &&
                                         !shader_modification.pixel.param_gen_point;
    if (use_barycentric_interpolation) {
      builder_->addExtension("SPV_KHR_fragment_shader_barycentric");
      builder_->addCapability(spv::CapabilityFragmentBarycentricKHR);

      input_barycentric_coord_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassInput,
                                                          type_float3_, "gl_BaryCoordKHR");
      builder_->addDecoration(input_barycentric_coord_, spv::DecorationBuiltIn,
                              static_cast<int>(spv::BuiltInBaryCoordKHR));
      main_interface_.push_back(input_barycentric_coord_);

      spv::Id type_float4_array_3 =
          builder_->makeArrayType(type_float4_, builder_->makeUintConstant(3), 0);
      uint32_t interpolators_remaining = GetModificationInterpolatorMask();
      uint32_t interpolator_index;
      while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
        interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
        spv::Id interpolator_per_vertex = builder_->createVariable(
            spv::NoPrecision, spv::StorageClassInput, type_float4_array_3,
            fmt::format("xe_in_interpolator_{}_per_vertex", interpolator_index).c_str());
        input_interpolators_per_vertex_[interpolator_index] = interpolator_per_vertex;
        builder_->addDecoration(interpolator_per_vertex, spv::DecorationLocation,
                                int(input_location));
        builder_->addDecoration(interpolator_per_vertex, spv::DecorationPerVertexKHR);

        main_interface_.push_back(interpolator_per_vertex);
        ++input_location;
      }
    } else {
      uint32_t interpolators_remaining = GetModificationInterpolatorMask();
      uint32_t interpolator_index;
      while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
        interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
        spv::Id interpolator = builder_->createVariable(
            spv::NoPrecision, spv::StorageClassInput, type_float4_,
            fmt::format("xe_in_interpolator_{}", interpolator_index).c_str());
        input_output_interpolators_[interpolator_index] = interpolator;
        builder_->addDecoration(interpolator, spv::DecorationLocation, int(input_location));
        if (shader_modification.pixel.interpolators_centroid &
            (UINT32_C(1) << interpolator_index)) {
          builder_->addDecoration(interpolator, spv::DecorationCentroid);
        }
        main_interface_.push_back(interpolator);
        ++input_location;
      }
    }

    if (shader_modification.pixel.param_gen_point) {
      if (param_gen_needed) {
        input_point_coordinates_ = builder_->createVariable(
            spv::NoPrecision, spv::StorageClassInput, type_float2_, "xe_in_point_coordinates");
        builder_->addDecoration(input_point_coordinates_, spv::DecorationLocation,
                                int(input_location));
        main_interface_.push_back(input_point_coordinates_);
      }
      ++input_location;
    }
  }

  bool need_frag_coord =
      edram_fragment_shader_interlock_ || param_gen_needed || IsSampleRate() ||
      DSV_IsApplyingPolygonOffset() || IsGuestPixelCenterFetchNeeded() ||
      (!edram_fragment_shader_interlock_ && !is_depth_only_fragment_shader_ &&
       current_shader().writes_color_target(0) && !IsExecutionModeEarlyFragmentTests());
  if (need_frag_coord) {
    input_fragment_coordinates_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassInput,
                                                           type_float4_, "gl_FragCoord");
    builder_->addDecoration(input_fragment_coordinates_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::FragCoord));
    if (IsSampleRate()) {
      builder_->addCapability(spv::CapabilitySampleRateShading);
      builder_->addDecoration(input_fragment_coordinates_, spv::DecorationSample);
    }
    main_interface_.push_back(input_fragment_coordinates_);
  }

  if (edram_fragment_shader_interlock_ || DSV_IsApplyingPolygonOffset() ||
      (param_gen_needed && !GetSpirvShaderModification().pixel.param_gen_point)) {
    input_front_facing_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassInput,
                                                   type_bool_, "gl_FrontFacing");
    builder_->addDecoration(input_front_facing_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::FrontFacing));
    main_interface_.push_back(input_front_facing_);
  }

  if (edram_fragment_shader_interlock_ || IsZpdTotal()) {
    builder_->addCapability(spv::CapabilitySampleRateShading);
    input_sample_mask_ = builder_->createVariable(
        spv::NoPrecision, spv::StorageClassInput,
        builder_->makeArrayType(type_int_, builder_->makeUintConstant(1), 0), "gl_SampleMaskIn");
    builder_->addDecoration(input_sample_mask_, spv::DecorationFlat);
    builder_->addDecoration(input_sample_mask_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::SampleMask));
    main_interface_.push_back(input_sample_mask_);
  }

  if (!is_depth_only_fragment_shader_) {
    if (!edram_fragment_shader_interlock_) {
      std::ranges::fill(output_fragment_data_, spv::NoResult);
      static const char* const kFragmentDataOutputNames[] = {
          "xe_out_fragment_data_0",
          "xe_out_fragment_data_1",
          "xe_out_fragment_data_2",
          "xe_out_fragment_data_3",
      };

      Modification shader_modification = GetHostRtShaderModification();
      uint32_t color_targets_remaining =
          current_shader().writes_color_targets() & shader_modification.pixel.color_targets_used;
      uint32_t color_target_index;
      while (rex::bit_scan_forward(color_targets_remaining, &color_target_index)) {
        color_targets_remaining &= ~(UINT32_C(1) << color_target_index);
        spv::Id output_fragment_data_rt =
            builder_->createVariable(spv::NoPrecision, spv::StorageClassOutput, type_float4_,
                                     kFragmentDataOutputNames[color_target_index]);
        output_fragment_data_[color_target_index] = output_fragment_data_rt;
        builder_->addDecoration(output_fragment_data_rt, spv::DecorationLocation,
                                int(color_target_index));

        builder_->addDecoration(output_fragment_data_rt, spv::DecorationInvariant);
        main_interface_.push_back(output_fragment_data_rt);
      }
    }
  }

  if (!edram_fragment_shader_interlock_ &&
      (current_shader().writes_depth() || DSV_IsWritingFloat24Depth() ||
       DSV_IsApplyingPolygonOffset())) {
    output_fragment_depth_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassOutput,
                                                      type_float_, "gl_FragDepth");
    builder_->addDecoration(output_fragment_depth_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::FragDepth));
    builder_->addDecoration(output_fragment_depth_, spv::DecorationInvariant);
    main_interface_.push_back(output_fragment_depth_);
  }

  output_fragment_sample_mask_ = spv::NoResult;
  if (!edram_fragment_shader_interlock_ && !is_depth_only_fragment_shader_) {
    spv::Id type_sample_mask_array =
        builder_->makeArrayType(type_int_, builder_->makeUintConstant(1), 0);
    output_fragment_sample_mask_ = builder_->createVariable(
        spv::NoPrecision, spv::StorageClassOutput, type_sample_mask_array, "gl_SampleMask");
    builder_->addDecoration(output_fragment_sample_mask_, spv::DecorationBuiltIn,
                            static_cast<int>(spv::BuiltIn::SampleMask));
    main_interface_.push_back(output_fragment_sample_mask_);
  }
}

void SpirvShaderTranslator::StartFragmentShaderInMain() {
  var_main_zpd_coverage_ = spv::NoResult;
  if (IsZpdTotal()) {
    assert_true(input_sample_mask_ != spv::NoResult);
    if (features_.demote_to_helper_invocation) {
      builder_->addExtension("SPV_EXT_demote_to_helper_invocation");
      builder_->addCapability(spv::CapabilityDemoteToHelperInvocationEXT);
    }
    var_main_zpd_coverage_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction,
                                                      type_uint_, "xe_var_zpd_coverage");
    id_vector_temp_.clear();
    id_vector_temp_.push_back(const_int_0_);
    spv::Id sample_mask_element =
        builder_->createAccessChain(spv::StorageClassInput, input_sample_mask_, id_vector_temp_);
    builder_->createStore(
        builder_->createUnaryOp(spv::OpBitcast, type_uint_,
                                builder_->createLoad(sample_mask_element, spv::NoPrecision)),
        var_main_zpd_coverage_);
  }

  if (current_shader().kills_pixels()) {
    if (features_.demote_to_helper_invocation) {
      builder_->addExtension("SPV_EXT_demote_to_helper_invocation");
      builder_->addCapability(spv::CapabilityDemoteToHelperInvocationEXT);
    } else {
      var_main_kill_pixel_ =
          builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_bool_,
                                   "xe_var_kill_pixel", builder_->makeBoolConstant(false));
    }
  }

  std::ranges::fill(output_or_var_fragment_data_, spv::NoResult);
  var_main_fsi_color_written_ = spv::NoResult;
  uint32_t color_targets_written = current_shader().writes_color_targets();
  if (color_targets_written && !is_depth_only_fragment_shader_) {
    static const char* const kFragmentDataVariableNames[] = {
        "xe_var_fragment_data_0",
        "xe_var_fragment_data_1",
        "xe_var_fragment_data_2",
        "xe_var_fragment_data_3",
    };
    uint32_t color_targets_remaining = color_targets_written;
    uint32_t color_target_index;
    while (rex::bit_scan_forward(color_targets_remaining, &color_target_index)) {
      color_targets_remaining &= ~(UINT32_C(1) << color_target_index);
      output_or_var_fragment_data_[color_target_index] =
          builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float4_,
                                   kFragmentDataVariableNames[color_target_index], const_float4_0_);
    }

    var_main_fsi_color_written_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_uint_,
                                 "xe_var_color_written", const_uint_0_);
  }

  if (current_shader().writes_depth()) {
    output_or_var_fragment_depth_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float_,
                                 "xe_var_fragment_depth", const_float_0_);
  }

  if (DSV_IsApplyingPolygonOffset()) {
    assert_true(input_fragment_coordinates_ != spv::NoResult);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(2));
    main_fbo_depth_unbiased_ = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                    id_vector_temp_),
        spv::NoPrecision);
    builder_->addCapability(spv::CapabilityDerivativeControl);
    main_fbo_depth_derivatives_[0] =
        builder_->createUnaryOp(spv::OpDPdxCoarse, type_float_, main_fbo_depth_unbiased_);
    main_fbo_depth_derivatives_[1] =
        builder_->createUnaryOp(spv::OpDPdyCoarse, type_float_, main_fbo_depth_unbiased_);
  }

  if (edram_fragment_shader_interlock_ && FSI_IsDepthStencilEarly()) {
    FSI_LoadSampleMask();
    FSI_LoadEdramOffsets();
    builder_->createNoResultOp(spv::OpBeginInvocationInterlockEXT);
    FSI_DepthStencilTest(false);
    if (zpd_full_counters_) {
      FSI_AddMSAASamplesToZPD(false, true);
    }
    if (!is_depth_only_fragment_shader_) {
      spv::Id quad_needs_execution =
          builder_->createBinOp(spv::OpINotEqual, type_bool_, main_fsi_sample_mask_, const_uint_0_);

      builder_->addCapability(spv::CapabilityDerivativeControl);

      quad_needs_execution = builder_->createBinOp(
          spv::OpLogicalOr, type_bool_, quad_needs_execution,
          builder_->createBinOp(
              spv::OpFOrdNotEqual, type_bool_,
              builder_->createUnaryOp(
                  spv::OpDPdxFine, type_float_,
                  builder_->createTriOp(spv::OpSelect, type_float_, quad_needs_execution,
                                        const_float_1_, const_float_0_)),
              const_float_0_));

      quad_needs_execution = builder_->createBinOp(
          spv::OpLogicalOr, type_bool_, quad_needs_execution,
          builder_->createBinOp(
              spv::OpFOrdNotEqual, type_bool_,
              builder_->createUnaryOp(
                  spv::OpDPdyCoarse, type_float_,
                  builder_->createTriOp(spv::OpSelect, type_float_, quad_needs_execution,
                                        const_float_1_, const_float_0_)),
              const_float_0_));
      spv::Block& main_fsi_early_depth_stencil_execute_quad = builder_->makeNewBlock();
      main_fsi_early_depth_stencil_execute_quad_merge_ = &builder_->makeNewBlock();
      builder_->createSelectionMerge(main_fsi_early_depth_stencil_execute_quad_merge_,
                                     spv::SelectionControlDontFlattenMask);
      builder_->createConditionalBranch(quad_needs_execution,
                                        &main_fsi_early_depth_stencil_execute_quad,
                                        main_fsi_early_depth_stencil_execute_quad_merge_);
      builder_->setBuildPoint(&main_fsi_early_depth_stencil_execute_quad);
    }
  }

  if (is_depth_only_fragment_shader_) {
    return;
  }

  uint32_t param_gen_interpolator = GetPsParamGenInterpolator();

  uint32_t interpolator_mask = GetModificationInterpolatorMask();

  Modification shader_modification = GetSpirvShaderModification();
  bool use_barycentric_interpolation = precise_interpolation_ &&
                                       features_.fragment_shader_barycentric &&
                                       !shader_modification.pixel.param_gen_point;

  spv::Id bary_y_vec4 = spv::NoResult;
  spv::Id bary_z_vec4 = spv::NoResult;
  if (use_barycentric_interpolation && interpolator_mask) {
    spv::Id barycentric_coords = builder_->createLoad(input_barycentric_coord_, spv::NoPrecision);

    spv::Id bary_y = builder_->createCompositeExtract(barycentric_coords, type_float_, 1);
    spv::Id bary_z = builder_->createCompositeExtract(barycentric_coords, type_float_, 2);
    id_vector_temp_util_.clear();
    id_vector_temp_util_.push_back(bary_y);
    id_vector_temp_util_.push_back(bary_y);
    id_vector_temp_util_.push_back(bary_y);
    id_vector_temp_util_.push_back(bary_y);
    bary_y_vec4 = builder_->createCompositeConstruct(type_float4_, id_vector_temp_util_);
    id_vector_temp_util_.clear();
    id_vector_temp_util_.push_back(bary_z);
    id_vector_temp_util_.push_back(bary_z);
    id_vector_temp_util_.push_back(bary_z);
    id_vector_temp_util_.push_back(bary_z);
    bary_z_vec4 = builder_->createCompositeConstruct(type_float4_, id_vector_temp_util_);
  }

  spv::Id guest_pixel_center_offsets[2] = {};
  bool guest_pixel_center_fetch = IsGuestPixelCenterFetchNeeded();
  if (guest_pixel_center_fetch) {
    assert_true(input_fragment_coordinates_ != spv::NoResult);
    uint32_t pixel_scales[] = {GetCurrentDrawResolutionScaleX(), GetCurrentDrawResolutionScaleY()};
    for (uint32_t i = 0; i < 2; ++i) {
      if (pixel_scales[i] <= 1) {
        guest_pixel_center_offsets[i] = const_float_0_;
        continue;
      }
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));
      spv::Id host_position = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                      id_vector_temp_),
          spv::NoPrecision);
      spv::Id pixel_scale = builder_->makeFloatConstant(float(pixel_scales[i]));

      spv::Id guest_center = builder_->createNoContractionBinOp(
          spv::OpFMul, type_float_,
          builder_->createNoContractionBinOp(
              spv::OpFAdd, type_float_,
              builder_->createUnaryBuiltinCall(
                  type_float_, ext_inst_glsl_std_450_, GLSLstd450Floor,
                  builder_->createNoContractionBinOp(spv::OpFDiv, type_float_, host_position,
                                                     pixel_scale)),
              builder_->makeFloatConstant(0.5f)),
          pixel_scale);
      guest_pixel_center_offsets[i] =
          builder_->createNoContractionBinOp(spv::OpFSub, type_float_, guest_center, host_position);
    }
  }

  for (uint32_t i = 0; i < register_count(); ++i) {
    if (i == param_gen_interpolator) {
      continue;
    }
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(int(i)));

    spv::Id interpolated_value;
    if (i < xenos::kMaxInterpolators && (interpolator_mask & (UINT32_C(1) << i))) {
      if (use_barycentric_interpolation) {
        spv::Id per_vertex_array = input_interpolators_per_vertex_[i];

        id_vector_temp_util_.clear();
        id_vector_temp_util_.push_back(builder_->makeIntConstant(0));
        spv::Id v0 = builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassInput, per_vertex_array,
                                        id_vector_temp_util_),
            spv::NoPrecision);
        id_vector_temp_util_.clear();
        id_vector_temp_util_.push_back(builder_->makeIntConstant(1));
        spv::Id v1 = builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassInput, per_vertex_array,
                                        id_vector_temp_util_),
            spv::NoPrecision);
        id_vector_temp_util_.clear();
        id_vector_temp_util_.push_back(builder_->makeIntConstant(2));
        spv::Id v2 = builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassInput, per_vertex_array,
                                        id_vector_temp_util_),
            spv::NoPrecision);

        spv::Id d1 = builder_->createBinOp(spv::OpFSub, type_float4_, v1, v0);
        spv::Id d2 = builder_->createBinOp(spv::OpFSub, type_float4_, v2, v0);

        spv::Id term1 = builder_->createBinOp(spv::OpFMul, type_float4_, d1, bary_y_vec4);
        spv::Id term2 = builder_->createBinOp(spv::OpFMul, type_float4_, d2, bary_z_vec4);
        spv::Id sum_terms = builder_->createBinOp(spv::OpFAdd, type_float4_, term1, term2);
        interpolated_value = builder_->createBinOp(spv::OpFAdd, type_float4_, v0, sum_terms);
      } else {
        interpolated_value = builder_->createLoad(input_output_interpolators_[i], spv::NoPrecision);
      }
      if (guest_pixel_center_fetch &&
          (current_shader().point_fetch_coordinate_registers() & (UINT32_C(1) << i))) {
        spv::Id guest_center_delta = builder_->createNoContractionBinOp(
            spv::OpFAdd, type_float4_,
            builder_->createNoContractionBinOp(
                spv::OpVectorTimesScalar, type_float4_,
                builder_->createUnaryOp(spv::OpDPdx, type_float4_, interpolated_value),
                guest_pixel_center_offsets[0]),
            builder_->createNoContractionBinOp(
                spv::OpVectorTimesScalar, type_float4_,
                builder_->createUnaryOp(spv::OpDPdy, type_float4_, interpolated_value),
                guest_pixel_center_offsets[1]));
        var_main_interpolator_guest_center_deltas_[i] =
            builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float4_,
                                     "xe_var_interpolator_guest_center_delta");
        builder_->createStore(guest_center_delta, var_main_interpolator_guest_center_deltas_[i]);
        main_interpolators_unmodified_ |= UINT64_C(0b1111) << (i * 4);
      }
    } else {
      interpolated_value = const_float4_0_;
    }

    builder_->createStore(interpolated_value,
                          builder_->createAccessChain(spv::StorageClassFunction,
                                                      var_main_registers_, id_vector_temp_));
  }

  main_interpolators_unmodified_ &=
      ~current_shader().GetRegisterComponentsWrittenBeforeReentering(0);

  if (param_gen_interpolator != UINT32_MAX) {
    Modification modification = GetSpirvShaderModification();

    spv::Id const_sign_bit = builder_->makeUintConstant(UINT32_C(1) << 31);

    assert_true(input_fragment_coordinates_ != spv::NoResult);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(const_int_0_);
    spv::Id param_gen_x = builder_->createUnaryBuiltinCall(
        type_float_, ext_inst_glsl_std_450_, GLSLstd450FAbs,
        builder_->createUnaryBuiltinCall(
            type_float_, ext_inst_glsl_std_450_, GLSLstd450Floor,
            builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                            id_vector_temp_),
                spv::NoPrecision)));

    if (GetCurrentDrawResolutionScaleX() > 1) {
      param_gen_x = builder_->createBinOp(
          spv::OpFMul, type_float_, param_gen_x,
          builder_->makeFloatConstant(1.0f / float(GetCurrentDrawResolutionScaleX())));
    }
    if (!modification.pixel.param_gen_point) {
      assert_true(input_front_facing_ != spv::NoResult);
      param_gen_x = builder_->createTriOp(
          spv::OpSelect, type_float_,
          builder_->createBinOp(
              spv::OpLogicalOr, type_bool_,
              builder_->createBinOp(
                  spv::OpIEqual, type_bool_,
                  builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                                        builder_->makeUintConstant(kSysFlag_PrimitivePolygonal)),
                  const_uint_0_),
              builder_->createLoad(input_front_facing_, spv::NoPrecision)),
          param_gen_x,
          builder_->createUnaryOp(
              spv::OpBitcast, type_float_,
              builder_->createBinOp(
                  spv::OpBitwiseXor, type_uint_,
                  builder_->createUnaryOp(spv::OpBitcast, type_uint_, param_gen_x),
                  const_sign_bit)));
    }

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(1));
    spv::Id param_gen_y = builder_->createUnaryBuiltinCall(
        type_float_, ext_inst_glsl_std_450_, GLSLstd450FAbs,
        builder_->createUnaryBuiltinCall(
            type_float_, ext_inst_glsl_std_450_, GLSLstd450Floor,
            builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                            id_vector_temp_),
                spv::NoPrecision)));

    if (GetCurrentDrawResolutionScaleY() > 1) {
      param_gen_y = builder_->createBinOp(
          spv::OpFMul, type_float_, param_gen_y,
          builder_->makeFloatConstant(1.0f / float(GetCurrentDrawResolutionScaleY())));
    }
    if (modification.pixel.param_gen_point) {
      param_gen_y = builder_->createUnaryOp(
          spv::OpBitcast, type_float_,
          builder_->createBinOp(spv::OpBitwiseXor, type_uint_,
                                builder_->createUnaryOp(spv::OpBitcast, type_uint_, param_gen_y),
                                const_sign_bit));
    }

    spv::Id param_gen_z, param_gen_w;
    if (modification.pixel.param_gen_point) {
      assert_true(input_point_coordinates_ != spv::NoResult);

      spv::Id param_gen_point_coordinates = builder_->createTriBuiltinCall(
          type_float2_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
          builder_->createLoad(input_point_coordinates_, spv::NoPrecision), const_float2_0_,
          const_float2_1_);
      param_gen_z = builder_->createCompositeExtract(param_gen_point_coordinates, type_float_, 0);
      param_gen_w = builder_->createCompositeExtract(param_gen_point_coordinates, type_float_, 1);
    } else {
      param_gen_z = builder_->createUnaryOp(
          spv::OpBitcast, type_float_,
          builder_->createTriOp(
              spv::OpSelect, type_uint_,
              builder_->createBinOp(
                  spv::OpINotEqual, type_bool_,
                  builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                                        builder_->makeUintConstant(kSysFlag_PrimitiveLine)),
                  const_uint_0_),
              const_sign_bit, const_uint_0_));
      param_gen_w = const_float_0_;
    }

    id_vector_temp_.clear();
    id_vector_temp_.push_back(param_gen_x);
    id_vector_temp_.push_back(param_gen_y);
    id_vector_temp_.push_back(param_gen_z);
    id_vector_temp_.push_back(param_gen_w);
    spv::Id param_gen = builder_->createCompositeConstruct(type_float4_, id_vector_temp_);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(int(param_gen_interpolator)));
    builder_->createStore(
        param_gen, builder_->createAccessChain(spv::StorageClassFunction, var_main_registers_,
                                               id_vector_temp_));
  }
}

}
