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

REXCVAR_DEFINE_BOOL(spirv_disable_rounding_mode_rte, false, "GPU",
                    "Disable RoundingModeRTE capability in SPIR-V shaders. Enable this to "
                    "allow shader debugging in RenderDoc, which doesn't support this "
                    "capability.");

REXCVAR_DEFINE_STRING(shader_bisect_ps_hash, "", "GPU.Debug",
                      "Ucode hash (hex) of the pixel shader to bisect. Empty disables "
                      "the bisect entirely.");

REXCVAR_DEFINE_INT32(shader_bisect_instruction, -1, "GPU.Debug",
                     "Guest instruction of the bisected shader to snapshot a register "
                     "at, counted in translation order from 0. -1 disables.");

REXCVAR_DEFINE_INT32(shader_bisect_register, -1, "GPU.Debug",
                     "Guest register to write to color output 0 at the end of the "
                     "bisected shader, so an intermediate value can be read back. -1 "
                     "leaves the shader's own output alone.");

REXCVAR_DEFINE_INT32(shader_bisect_probe, 0, "GPU.Debug",
                     "What to write to color 0 for the bisected register, since an 8 "
                     "bit target hides the values that matter most.\n"
                     " 0: the register itself (default)\n"
                     " 1: 1.0 per component that is NaN\n"
                     " 2: 1.0 per component that is infinite\n"
                     " 3: 1.0 per component whose magnitude is at least 1");

REXCVAR_DEFINE_BOOL(shader_bisect_cut, false, "GPU.Debug",
                    "Stop emitting the bisected shader after "
                    "shader_bisect_instruction instead of only snapshotting the "
                    "register there. Cutting also drops the shader's own color and "
                    "depth exports, which changes what the render backend does with "
                    "the pixel.");

REXCVAR_DEFINE_BOOL(spirv_pixel_interlock_only, false, "GPU.Debug",
                    "Use PixelInterlockOrderedEXT even where the device offers sample "
                    "interlock, matching what the D3D12 backend always does. Sample "
                    "granularity asks for the shader to be invoked per sample, which "
                    "changes what every position-dependent value in it sees.");

REXCVAR_DEFINE_BOOL(spirv_disable_signed_zero_inf_nan_preserve, false, "GPU.Debug",
                    "Drop the SignedZeroInfNanPreserve capability from SPIR-V "
                    "shaders, which the D3D12 backend never requests. It governs what "
                    "reciprocal, logarithm and the min/max clamps do with infinities "
                    "and NaNs.");

REXCVAR_DEFINE_BOOL(spirv_fine_derivatives, false, "GPU.Debug",
                    "Compute texture LOD gradients and the guest's getGradients with "
                    "fine derivatives rather than coarse. Which pixels of the quad a "
                    "coarse derivative uses is left to the implementation, so the "
                    "same shader can pick a different LOD on different drivers.");

REXCVAR_DEFINE_BOOL(spirv_no_contraction_all, false, "GPU.Debug",
                    "Decorate every float arithmetic result with NoContraction, "
                    "removing the driver's freedom to fuse a multiply and add into "
                    "one rounding.");

namespace rex::graphics {

SpirvShaderTranslator::Features::Features(bool all)
    : spirv_version(all ? spv::Spv_1_5 : spv::Spv_1_0),
      max_storage_buffer_range(all ? UINT32_MAX : (128 * 1024 * 1024)),
      full_draw_index_uint32(all),
      vertex_pipeline_stores_and_atomics(all),
      fragment_stores_and_atomics(all),
      clip_distance(all),
      cull_distance(all),
      image_view_format_swizzle(all),
      signed_zero_inf_nan_preserve_float32(all),
      denorm_flush_to_zero_float32(all),
      rounding_mode_rte_float32(all),
      fragment_shader_sample_interlock(all),
      demote_to_helper_invocation(all),
      fragment_shader_barycentric(all) {}

uint64_t SpirvShaderTranslator::GetDefaultVertexShaderModification(
    uint32_t dynamic_addressable_register_count,
    Shader::HostVertexShaderType host_vertex_shader_type) const {
  Modification shader_modification;
  shader_modification.vertex.dynamic_addressable_register_count =
      dynamic_addressable_register_count;
  shader_modification.vertex.host_vertex_shader_type = host_vertex_shader_type;
  return shader_modification.value;
}

uint64_t SpirvShaderTranslator::GetDefaultPixelShaderModification(
    uint32_t dynamic_addressable_register_count) const {
  Modification shader_modification;
  shader_modification.pixel.dynamic_addressable_register_count = dynamic_addressable_register_count;
  return shader_modification.value;
}

std::vector<uint8_t> SpirvShaderTranslator::CreateDepthOnlyFragmentShader(
    Modification::DepthStencilMode depth_stencil_mode, bool zpd_total, bool viz_survey) {
  is_depth_only_fragment_shader_ = true;
  is_viz_survey_fragment_shader_ = viz_survey;

  Shader shader(xenos::ShaderType::kPixel, 0, nullptr, 0);
  string::StringBuffer instruction_disassembly_buffer;
  shader.AnalyzeUcode(instruction_disassembly_buffer);
  Modification modification(0);
  modification.pixel.depth_stencil_mode = depth_stencil_mode;
  modification.pixel.set_zpd_total(zpd_total);
  Shader::Translation& translation = *shader.GetOrCreateTranslation(modification.value);
  TranslateAnalyzedShader(translation);
  is_depth_only_fragment_shader_ = false;
  is_viz_survey_fragment_shader_ = false;
  return translation.translated_binary();
}

std::vector<uint8_t> SpirvShaderTranslator::CreateDepthOnlyFragmentShader(
    xenos::MsaaSamples fsi_msaa_samples, bool viz_survey) {
  Modification modification(0);
  modification.pixel.set_fsi_msaa_samples(fsi_msaa_samples);
  return CreateDepthOnlyFragmentShader(modification.pixel.depth_stencil_mode, false, viz_survey);
}

void SpirvShaderTranslator::Reset() {
  ShaderTranslator::Reset();

  builder_.reset();

  uniform_float_constants_ = spv::NoResult;

  input_vertex_index_ = spv::NoResult;

  input_control_point_index_ = spv::NoResult;
  input_tess_coord_ = spv::NoResult;

  input_point_coordinates_ = spv::NoResult;
  input_fragment_coordinates_ = spv::NoResult;
  input_front_facing_ = spv::NoResult;
  input_sample_mask_ = spv::NoResult;

  input_barycentric_coord_ = spv::NoResult;
  input_barycentric_coord_no_persp_ = spv::NoResult;
  std::ranges::fill(input_interpolators_per_vertex_, spv::NoResult);
  std::ranges::fill(input_output_interpolators_, spv::NoResult);
  std::ranges::fill(var_main_rect_list_guest_interpolators_, spv::NoResult);
  output_point_coordinates_ = spv::NoResult;
  output_point_size_ = spv::NoResult;

  sampler_bindings_.clear();
  texture_bindings_.clear();

  main_interface_.clear();
  bisect_instruction_index_ = 0;
  bisect_current_instruction_ = UINT32_MAX;
  bisect_snapshot_emitted_ = false;
  var_main_bisect_snapshot_ = spv::NoResult;
  var_main_registers_ = spv::NoResult;
  main_interpolators_unmodified_ = 0;
  var_main_interpolator_guest_center_deltas_.fill(spv::NoResult);
  var_main_memexport_address_ = spv::NoResult;
  for (size_t memexport_eM_index = 0; memexport_eM_index < rex::countof(var_main_memexport_data_);
       ++memexport_eM_index) {
    var_main_memexport_data_[memexport_eM_index] = spv::NoResult;
  }
  var_main_memexport_data_written_ = spv::NoResult;
  main_memexport_allowed_ = spv::NoResult;
  var_main_point_size_edge_flag_kill_vertex_ = spv::NoResult;
  main_vertex_rect_list_as_triangle_strip_ = false;
  var_main_rect_list_strip_vertex_ = spv::NoResult;
  var_main_rect_list_guest_vertex_indices_ = spv::NoResult;
  var_main_rect_list_guest_positions_ = spv::NoResult;
  main_rect_list_loop_vertex_index_ = spv::NoResult;
  main_rect_list_loop_vertex_index_next_ = spv::NoResult;
  var_main_kill_pixel_ = spv::NoResult;
  var_main_fsi_color_written_ = spv::NoResult;
  var_main_zpd_coverage_ = spv::NoResult;
  std::ranges::fill(output_fragment_data_, spv::NoResult);
  output_or_var_fragment_depth_ = spv::NoResult;
  output_fragment_depth_ = spv::NoResult;
  main_fbo_depth_unbiased_ = spv::NoResult;
  main_fbo_depth_derivatives_.fill(spv::NoResult);

  main_switch_op_.reset();
  main_switch_next_pc_phi_operands_.clear();
  main_rect_list_loop_header_ = nullptr;
  main_rect_list_loop_continue_ = nullptr;
  main_rect_list_loop_merge_ = nullptr;

  cf_exec_conditional_merge_ = nullptr;
  cf_instruction_predicate_merge_ = nullptr;
}

uint32_t SpirvShaderTranslator::GetModificationRegisterCount() const {
  Modification modification = GetSpirvShaderModification();
  return is_vertex_shader() ? modification.vertex.dynamic_addressable_register_count
                            : modification.pixel.dynamic_addressable_register_count;
}

bool SpirvShaderTranslator::BisectTargetsCurrentShader() const {
  if (REXCVAR_GET(shader_bisect_ps_hash).empty()) {
    return false;
  }
  uint64_t hash = std::strtoull(REXCVAR_GET(shader_bisect_ps_hash).c_str(), nullptr, 16);
  return hash && hash == current_shader().ucode_data_hash();
}

bool SpirvShaderTranslator::BisectSkipsInstruction() {
  if (!BisectTargetsCurrentShader()) {
    return false;
  }
  bisect_current_instruction_ = bisect_instruction_index_++;
  return REXCVAR_GET(shader_bisect_cut) && REXCVAR_GET(shader_bisect_instruction) >= 0 &&
         bisect_current_instruction_ > uint32_t(REXCVAR_GET(shader_bisect_instruction));
}

void SpirvShaderTranslator::BisectSnapshotAfterInstruction() {
  if (var_main_bisect_snapshot_ == spv::NoResult || REXCVAR_GET(shader_bisect_instruction) < 0 ||
      bisect_current_instruction_ != uint32_t(REXCVAR_GET(shader_bisect_instruction))) {
    return;
  }
  BisectStoreSnapshot();
}

void SpirvShaderTranslator::BisectStoreSnapshot() {
  EnsureBuildPointAvailable();
  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(REXCVAR_GET(shader_bisect_register)));
  builder_->createStore(
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassFunction,
                                                       var_main_registers_, id_vector_temp_),
                           spv::NoPrecision),
      var_main_bisect_snapshot_);
  bisect_snapshot_emitted_ = true;
}

void SpirvShaderTranslator::BisectOverrideColorOutput() {
  if (var_main_bisect_snapshot_ == spv::NoResult ||
      output_or_var_fragment_data_[0] == spv::NoResult) {
    return;
  }
  EnsureBuildPointAvailable();

  if (!bisect_snapshot_emitted_) {
    BisectStoreSnapshot();
  }
  spv::Id value = builder_->createLoad(var_main_bisect_snapshot_, spv::NoPrecision);
  spv::Id classified = spv::NoResult;
  switch (REXCVAR_GET(shader_bisect_probe)) {
    case 1:
      classified = builder_->createUnaryOp(spv::OpIsNan, type_bool4_, value);
      break;
    case 2:
      classified = builder_->createUnaryOp(spv::OpIsInf, type_bool4_, value);
      break;
    case 3:
      classified =
          builder_->createBinOp(spv::OpFOrdGreaterThanEqual, type_bool4_,
                                builder_->createUnaryBuiltinCall(
                                    type_float4_, ext_inst_glsl_std_450_, GLSLstd450FAbs, value),
                                const_float4_1_);
      break;
    default:
      break;
  }
  if (classified != spv::NoResult) {
    value = builder_->createTriOp(spv::OpSelect, type_float4_, classified, const_float4_1_,
                                  const_float4_0_);
  }
  builder_->createStore(value, output_or_var_fragment_data_[0]);

  if (var_main_fsi_color_written_ != spv::NoResult) {
    builder_->createStore(
        builder_->createBinOp(spv::OpBitwiseOr, type_uint_,
                              builder_->createLoad(var_main_fsi_color_written_, spv::NoPrecision),
                              builder_->makeUintConstant(uint32_t(1))),
        var_main_fsi_color_written_);
  }
  REXGPU_INFO("shader_bisect: shader {:016X} {} instruction {} of {}, r{} to oC0",
              current_shader().ucode_data_hash(),
              REXCVAR_GET(shader_bisect_cut) ? "cut after" : "snapshot after",
              REXCVAR_GET(shader_bisect_instruction), bisect_instruction_index_,
              REXCVAR_GET(shader_bisect_register));
}

void SpirvShaderTranslator::StartTranslation() {
  builder_ = std::make_unique<SpirvBuilder>(features_.spirv_version, (kSpirvMagicToolId << 16) | 1,
                                            nullptr);
  builder_->SetAllowContraction(features_.allow_float_contraction);
  builder_->SetNoContractionAll(REXCVAR_GET(spirv_no_contraction_all));

  builder_->addCapability(IsSpirvTessEvalShader() ? spv::CapabilityTessellation
                                                  : spv::CapabilityShader);
  if (features_.spirv_version < spv::Spv_1_4) {
    if (features_.signed_zero_inf_nan_preserve_float32 || features_.denorm_flush_to_zero_float32 ||
        features_.rounding_mode_rte_float32) {
      builder_->addExtension("SPV_KHR_float_controls");
    }
  }
  ext_inst_glsl_std_450_ = builder_->import("GLSL.std.450");
  builder_->setMemoryModel(spv::AddressingModelLogical, spv::MemoryModelGLSL450);
  builder_->setSource(spv::SourceLanguageUnknown, 0);

  type_void_ = builder_->makeVoidType();
  type_bool_ = builder_->makeBoolType();
  type_bool2_ = builder_->makeVectorType(type_bool_, 2);
  type_bool3_ = builder_->makeVectorType(type_bool_, 3);
  type_bool4_ = builder_->makeVectorType(type_bool_, 4);
  type_int_ = builder_->makeIntType(32);
  type_int2_ = builder_->makeVectorType(type_int_, 2);
  type_int3_ = builder_->makeVectorType(type_int_, 3);
  type_int4_ = builder_->makeVectorType(type_int_, 4);
  type_uint_ = builder_->makeUintType(32);
  type_uint2_ = builder_->makeVectorType(type_uint_, 2);
  type_uint3_ = builder_->makeVectorType(type_uint_, 3);
  type_uint4_ = builder_->makeVectorType(type_uint_, 4);
  type_float_ = builder_->makeFloatType(32);
  type_float2_ = builder_->makeVectorType(type_float_, 2);
  type_float3_ = builder_->makeVectorType(type_float_, 3);
  type_float4_ = builder_->makeVectorType(type_float_, 4);

  const_int_0_ = builder_->makeIntConstant(0);
  id_vector_temp_.clear();
  for (uint32_t i = 0; i < 4; ++i) {
    id_vector_temp_.push_back(const_int_0_);
  }
  const_int4_0_ = builder_->makeCompositeConstant(type_int4_, id_vector_temp_);
  const_uint_0_ = builder_->makeUintConstant(0);
  id_vector_temp_.clear();
  for (uint32_t i = 0; i < 4; ++i) {
    id_vector_temp_.push_back(const_uint_0_);
  }
  const_uint4_0_ = builder_->makeCompositeConstant(type_uint4_, id_vector_temp_);
  const_float_0_ = builder_->makeFloatConstant(0.0f);
  id_vector_temp_.clear();
  id_vector_temp_.push_back(const_float_0_);
  for (uint32_t i = 1; i < 4; ++i) {
    id_vector_temp_.push_back(const_float_0_);
    const_float_vectors_0_[i] =
        builder_->makeCompositeConstant(type_float_vectors_[i], id_vector_temp_);
  }
  const_float_1_ = builder_->makeFloatConstant(1.0f);
  id_vector_temp_.clear();
  id_vector_temp_.push_back(const_float_1_);
  for (uint32_t i = 1; i < 4; ++i) {
    id_vector_temp_.push_back(const_float_1_);
    const_float_vectors_1_[i] =
        builder_->makeCompositeConstant(type_float_vectors_[i], id_vector_temp_);
  }
  id_vector_temp_.clear();
  id_vector_temp_.push_back(const_float_0_);
  id_vector_temp_.push_back(const_float_1_);
  const_float2_0_1_ = builder_->makeCompositeConstant(type_float2_, id_vector_temp_);

  struct SystemConstant {
    const char* name;
    size_t offset;
    spv::Id type;
  };
  spv::Id type_float4_array_4 =
      builder_->makeArrayType(type_float4_, builder_->makeUintConstant(4), sizeof(float) * 4);
  builder_->addDecoration(type_float4_array_4, spv::DecorationArrayStride, sizeof(float) * 4);
  spv::Id type_uint4_array_2 =
      builder_->makeArrayType(type_uint4_, builder_->makeUintConstant(2), sizeof(uint32_t) * 4);
  builder_->addDecoration(type_uint4_array_2, spv::DecorationArrayStride, sizeof(uint32_t) * 4);
  spv::Id type_uint4_array_4 =
      builder_->makeArrayType(type_uint4_, builder_->makeUintConstant(4), sizeof(uint32_t) * 4);
  builder_->addDecoration(type_uint4_array_4, spv::DecorationArrayStride, sizeof(uint32_t) * 4);
  spv::Id type_uint4_array_8 =
      builder_->makeArrayType(type_uint4_, builder_->makeUintConstant(8), sizeof(uint32_t) * 4);
  builder_->addDecoration(type_uint4_array_8, spv::DecorationArrayStride, sizeof(uint32_t) * 4);
  spv::Id type_float4_array_6 =
      builder_->makeArrayType(type_float4_, builder_->makeUintConstant(6), sizeof(float) * 4);
  builder_->addDecoration(type_float4_array_6, spv::DecorationArrayStride, sizeof(float) * 4);
  const SystemConstant system_constants[] = {
      {"flags", offsetof(SystemConstants, flags), type_uint_},
      {"vertex_index_load_address", offsetof(SystemConstants, vertex_index_load_address),
       type_uint_},
      {"vertex_index_count", offsetof(SystemConstants, vertex_index_count), type_uint_},
      {"vertex_index_endian", offsetof(SystemConstants, vertex_index_endian), type_uint_},
      {"vertex_base_index", offsetof(SystemConstants, vertex_base_index), type_int_},
      {"ndc_scale", offsetof(SystemConstants, ndc_scale), type_float3_},
      {"point_vertex_diameter_min", offsetof(SystemConstants, point_vertex_diameter_min),
       type_float_},
      {"ndc_offset", offsetof(SystemConstants, ndc_offset), type_float3_},
      {"point_vertex_diameter_max", offsetof(SystemConstants, point_vertex_diameter_max),
       type_float_},
      {"point_constant_diameter", offsetof(SystemConstants, point_constant_diameter), type_float2_},
      {"point_screen_diameter_to_ndc_radius",
       offsetof(SystemConstants, point_screen_diameter_to_ndc_radius), type_float2_},
      {"texture_swizzled_signs", offsetof(SystemConstants, texture_swizzled_signs),
       type_uint4_array_2},
      {"texture_swizzles", offsetof(SystemConstants, texture_swizzles), type_uint4_array_4},
      {"textures_resolved", offsetof(SystemConstants, textures_resolved), type_uint_},
      {"alpha_test_reference", offsetof(SystemConstants, alpha_test_reference), type_float_},
      {"alpha_to_mask", offsetof(SystemConstants, alpha_to_mask), type_uint_},
      {"zpd_fsi_counter_index", offsetof(SystemConstants, zpd_fsi_counter_index), type_uint_},
      {"edram_32bpp_tile_pitch_dwords_scaled",
       offsetof(SystemConstants, edram_32bpp_tile_pitch_dwords_scaled), type_uint_},
      {"edram_depth_base_dwords_scaled", offsetof(SystemConstants, edram_depth_base_dwords_scaled),
       type_uint_},
      {"color_exp_bias", offsetof(SystemConstants, color_exp_bias), type_float4_},
      {"edram_poly_offset_front_scale", offsetof(SystemConstants, edram_poly_offset_front_scale),
       type_float_},
      {"edram_poly_offset_back_scale", offsetof(SystemConstants, edram_poly_offset_back_scale),
       type_float_},
      {"edram_poly_offset_front_offset", offsetof(SystemConstants, edram_poly_offset_front_offset),
       type_float_},
      {"edram_poly_offset_back_offset", offsetof(SystemConstants, edram_poly_offset_back_offset),
       type_float_},
      {"edram_stencil_front", offsetof(SystemConstants, edram_stencil_front), type_uint2_},
      {"edram_stencil_back", offsetof(SystemConstants, edram_stencil_back), type_uint2_},
      {"edram_rt_base_dwords_scaled", offsetof(SystemConstants, edram_rt_base_dwords_scaled),
       type_uint4_},
      {"edram_rt_blend_factors_ops", offsetof(SystemConstants, edram_rt_blend_factors_ops),
       type_uint4_},
      {"edram_rt_keep_mask", offsetof(SystemConstants, edram_rt_keep_mask), type_uint4_array_2},
      {"edram_rt_clamp", offsetof(SystemConstants, edram_rt_clamp), type_float4_array_4},
      {"edram_blend_constant", offsetof(SystemConstants, edram_blend_constant), type_float4_},
      {"user_clip_planes", offsetof(SystemConstants, user_clip_planes), type_float4_array_6},
      {"tessellation_factor_range", offsetof(SystemConstants, tessellation_factor_range),
       type_float2_},
      {"tessellation_vertex_index_endian",
       offsetof(SystemConstants, tessellation_vertex_index_endian), type_uint_},
      {"tessellation_vertex_index_offset",
       offsetof(SystemConstants, tessellation_vertex_index_offset), type_uint_},
      {"tessellation_vertex_index_min_max",
       offsetof(SystemConstants, tessellation_vertex_index_min_max), type_uint2_},
      {"interpreter_ucode_base_dwords", offsetof(SystemConstants, interpreter_ucode_base_dwords),
       type_uint_},
      {"interpreter_cf_instr_count", offsetof(SystemConstants, interpreter_cf_instr_count),
       type_uint_},
      {"texture_integer_scale_bits", offsetof(SystemConstants, texture_integer_scale_bits),
       type_uint4_array_8},
  };
  id_vector_temp_.clear();
  id_vector_temp_.reserve(rex::countof(system_constants));
  for (size_t i = 0; i < rex::countof(system_constants); ++i) {
    id_vector_temp_.push_back(system_constants[i].type);
  }
  spv::Id type_system_constants = builder_->makeStructType(id_vector_temp_, "XeSystemConstants");
  for (size_t i = 0; i < rex::countof(system_constants); ++i) {
    const SystemConstant& system_constant = system_constants[i];
    builder_->addMemberName(type_system_constants, static_cast<unsigned int>(i),
                            system_constant.name);
    builder_->addMemberDecoration(type_system_constants, static_cast<unsigned int>(i),
                                  spv::DecorationOffset, int(system_constant.offset));
  }
  builder_->addDecoration(type_system_constants, spv::DecorationBlock);
  uniform_system_constants_ =
      builder_->createVariable(spv::NoPrecision, spv::StorageClassUniform, type_system_constants,
                               "xe_uniform_system_constants");
  builder_->addDecoration(uniform_system_constants_, spv::DecorationDescriptorSet,
                          int(kDescriptorSetConstants));
  builder_->addDecoration(uniform_system_constants_, spv::DecorationBinding,
                          int(kConstantBufferSystem));
  if (features_.spirv_version >= spv::Spv_1_4) {
    main_interface_.push_back(uniform_system_constants_);
  }

  bool memexport_used = IsMemoryExportUsed();

  if (!is_depth_only_fragment_shader_) {
    uint32_t float_constant_count = current_shader().constant_register_map().float_count;
    if (float_constant_count) {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeArrayType(
          type_float4_, builder_->makeUintConstant(float_constant_count), sizeof(float) * 4));

      builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride,
                              sizeof(float) * 4);
      spv::Id type_float_constants = builder_->makeStructType(id_vector_temp_, "XeFloatConstants");
      builder_->addMemberName(type_float_constants, 0, "float_constants");
      builder_->addMemberDecoration(type_float_constants, 0, spv::DecorationOffset, 0);
      builder_->addDecoration(type_float_constants, spv::DecorationBlock);
      uniform_float_constants_ =
          builder_->createVariable(spv::NoPrecision, spv::StorageClassUniform, type_float_constants,
                                   "xe_uniform_float_constants");
      builder_->addDecoration(uniform_float_constants_, spv::DecorationDescriptorSet,
                              int(kDescriptorSetConstants));
      builder_->addDecoration(
          uniform_float_constants_, spv::DecorationBinding,
          int(is_pixel_shader() ? kConstantBufferFloatPixel : kConstantBufferFloatVertex));
      if (features_.spirv_version >= spv::Spv_1_4) {
        main_interface_.push_back(uniform_float_constants_);
      }
    }

    id_vector_temp_.clear();

    id_vector_temp_.push_back(
        builder_->makeArrayType(type_uint4_, builder_->makeUintConstant(2), sizeof(uint32_t) * 4));
    builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride,
                            sizeof(uint32_t) * 4);

    id_vector_temp_.push_back(
        builder_->makeArrayType(type_uint4_, builder_->makeUintConstant(8), sizeof(uint32_t) * 4));
    builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride,
                            sizeof(uint32_t) * 4);
    spv::Id type_bool_loop_constants =
        builder_->makeStructType(id_vector_temp_, "XeBoolLoopConstants");
    builder_->addMemberName(type_bool_loop_constants, 0, "bool_constants");
    builder_->addMemberDecoration(type_bool_loop_constants, 0, spv::DecorationOffset, 0);
    builder_->addMemberName(type_bool_loop_constants, 1, "loop_constants");
    builder_->addMemberDecoration(type_bool_loop_constants, 1, spv::DecorationOffset,
                                  sizeof(uint32_t) * 8);
    builder_->addDecoration(type_bool_loop_constants, spv::DecorationBlock);
    uniform_bool_loop_constants_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassUniform,
                                 type_bool_loop_constants, "xe_uniform_bool_loop_constants");
    builder_->addDecoration(uniform_bool_loop_constants_, spv::DecorationDescriptorSet,
                            int(kDescriptorSetConstants));
    builder_->addDecoration(uniform_bool_loop_constants_, spv::DecorationBinding,
                            int(kConstantBufferBoolLoop));
    if (features_.spirv_version >= spv::Spv_1_4) {
      main_interface_.push_back(uniform_bool_loop_constants_);
    }

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeArrayType(
        type_uint4_, builder_->makeUintConstant(32 * 6 / 4), sizeof(uint32_t) * 4));
    builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride,
                            sizeof(uint32_t) * 4);
    spv::Id type_fetch_constants = builder_->makeStructType(id_vector_temp_, "XeFetchConstants");
    builder_->addMemberName(type_fetch_constants, 0, "fetch_constants");
    builder_->addMemberDecoration(type_fetch_constants, 0, spv::DecorationOffset, 0);
    builder_->addDecoration(type_fetch_constants, spv::DecorationBlock);
    uniform_fetch_constants_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassUniform, type_fetch_constants,
                                 "xe_uniform_fetch_constants");
    builder_->addDecoration(uniform_fetch_constants_, spv::DecorationDescriptorSet,
                            int(kDescriptorSetConstants));
    builder_->addDecoration(uniform_fetch_constants_, spv::DecorationBinding,
                            int(kConstantBufferFetch));
    if (features_.spirv_version >= spv::Spv_1_4) {
      main_interface_.push_back(uniform_fetch_constants_);
    }

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeRuntimeArray(type_uint_));

    builder_->addDecoration(id_vector_temp_.back(), spv::DecorationArrayStride, sizeof(uint32_t));
    spv::Id type_shared_memory = builder_->makeStructType(id_vector_temp_, "XeSharedMemory");
    builder_->addMemberName(type_shared_memory, 0, "shared_memory");
    builder_->addMemberDecoration(type_shared_memory, 0, spv::DecorationRestrict);
    if (!memexport_used) {
      builder_->addMemberDecoration(type_shared_memory, 0, spv::DecorationNonWritable);
    }
    builder_->addMemberDecoration(type_shared_memory, 0, spv::DecorationOffset, 0);
    builder_->addDecoration(type_shared_memory, features_.spirv_version >= spv::Spv_1_3
                                                    ? spv::DecorationBlock
                                                    : spv::DecorationBufferBlock);
    unsigned int shared_memory_binding_count = 1 << GetSharedMemoryStorageBufferCountLog2();
    if (shared_memory_binding_count > 1) {
      type_shared_memory = builder_->makeArrayType(
          type_shared_memory, builder_->makeUintConstant(shared_memory_binding_count), 0);
    }
    buffers_shared_memory_ = builder_->createVariable(spv::NoPrecision,
                                                      features_.spirv_version >= spv::Spv_1_3
                                                          ? spv::StorageClassStorageBuffer
                                                          : spv::StorageClassUniform,
                                                      type_shared_memory, "xe_shared_memory");
    builder_->addDecoration(buffers_shared_memory_, spv::DecorationDescriptorSet,
                            int(kDescriptorSetSharedMemoryAndEdram));
    builder_->addDecoration(buffers_shared_memory_, spv::DecorationBinding, 0);
    if (features_.spirv_version >= spv::Spv_1_4) {
      main_interface_.push_back(buffers_shared_memory_);
    }
  }

  if (is_vertex_shader()) {
    StartVertexOrTessEvalShaderBeforeMain();
  } else if (is_pixel_shader()) {
    StartFragmentShaderBeforeMain();
  }

  std::vector<spv::Id> main_param_types;
  std::vector<std::vector<spv::Decoration>> main_precisions;
  spv::Block* function_main_entry;
  function_main_ =
      builder_->makeFunctionEntry(spv::NoPrecision, type_void_, "main", main_param_types,
                                  main_precisions, &function_main_entry);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantFlags));
  main_system_constant_flags_ =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision);

  if (!is_depth_only_fragment_shader_) {
    var_main_predicate_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_bool_,
                                 "xe_var_predicate", builder_->makeBoolConstant(false));
    var_main_loop_count_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_uint4_,
                                 "xe_var_loop_count", const_uint4_0_);
    var_main_address_register_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_int_,
                                 "xe_var_address_register", const_int_0_);
    var_main_loop_address_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_int4_,
                                 "xe_var_loop_address", const_int4_0_);
    var_main_previous_scalar_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float_,
                                 "xe_var_previous_scalar", const_float_0_);
    var_main_vfetch_address_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_int_,
                                 "xe_var_vfetch_address", const_int_0_);
    var_main_vfetch_bound_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_int_,
                                 "xe_var_vfetch_bound", const_int_0_);
    var_main_tfetch_lod_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float_,
                                 "xe_var_tfetch_lod", const_float_0_);
    var_main_tfetch_gradients_h_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float3_,
                                 "xe_var_tfetch_gradients_h", const_float3_0_);
    var_main_tfetch_gradients_v_ =
        builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float3_,
                                 "xe_var_tfetch_gradients_v", const_float3_0_);
    if (register_count()) {
      spv::Id type_register_array =
          builder_->makeArrayType(type_float4_, builder_->makeUintConstant(register_count()), -1);
      var_main_registers_ = builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction,
                                                     type_register_array, "xe_var_registers");
      if (is_pixel_shader() && BisectTargetsCurrentShader() &&
          REXCVAR_GET(shader_bisect_register) >= 0 &&
          uint32_t(REXCVAR_GET(shader_bisect_register)) < register_count()) {
        var_main_bisect_snapshot_ =
            builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float4_,
                                     "xe_var_bisect_snapshot", const_float4_0_);
      }
    }
    if (memexport_used) {
      var_main_memexport_address_ =
          builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_float4_,
                                   "xe_var_memexport_address", const_float4_0_);
      uint8_t memexport_eM_remaining = current_shader().memexport_eM_written();
      uint32_t memexport_eM_index;
      while (rex::bit_scan_forward(memexport_eM_remaining, &memexport_eM_index)) {
        memexport_eM_remaining &= ~(uint8_t(1) << memexport_eM_index);
        var_main_memexport_data_[memexport_eM_index] = builder_->createVariable(
            spv::NoPrecision, spv::StorageClassFunction, type_float4_,
            fmt::format("xe_var_memexport_data_{}", memexport_eM_index).c_str(), const_float4_0_);
      }
      var_main_memexport_data_written_ =
          builder_->createVariable(spv::NoPrecision, spv::StorageClassFunction, type_uint_,
                                   "xe_var_memexport_data_written", const_uint_0_);
    }
  }

  if (is_vertex_shader()) {
    StartVertexOrTessEvalShaderInMain();
  } else if (is_pixel_shader()) {
    StartFragmentShaderInMain();
  }

  if (is_depth_only_fragment_shader_) {
    return;
  }

  if (main_vertex_rect_list_as_triangle_strip_) {
    assert_true(IsSpirvVertexShader());
    assert_true(var_main_rect_list_guest_vertex_indices_ != spv::NoResult);

    spv::Block& main_rect_list_loop_pre_header = *builder_->getBuildPoint();
    main_rect_list_loop_header_ = &builder_->makeNewBlock();
    spv::Block& main_rect_list_loop_body = builder_->makeNewBlock();
    main_rect_list_loop_continue_ = new spv::Block(builder_->getUniqueId(), *function_main_);
    main_rect_list_loop_merge_ = new spv::Block(builder_->getUniqueId(), *function_main_);
    builder_->createBranch(main_rect_list_loop_header_);

    builder_->setBuildPoint(main_rect_list_loop_header_);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(const_int_0_);
    id_vector_temp_.push_back(main_rect_list_loop_pre_header.getId());
    main_rect_list_loop_vertex_index_next_ = builder_->getUniqueId();
    id_vector_temp_.push_back(main_rect_list_loop_vertex_index_next_);
    id_vector_temp_.push_back(main_rect_list_loop_continue_->getId());
    main_rect_list_loop_vertex_index_ = builder_->createOp(spv::OpPhi, type_int_, id_vector_temp_);
    spv::Id main_rect_list_loop_condition =
        builder_->createBinOp(spv::OpSLessThan, type_bool_, main_rect_list_loop_vertex_index_,
                              builder_->makeIntConstant(3));
    uint_vector_temp_.clear();
    builder_->createLoopMerge(main_rect_list_loop_merge_, main_rect_list_loop_continue_,
                              spv::LoopControlDontUnrollMask, uint_vector_temp_);
    builder_->createConditionalBranch(main_rect_list_loop_condition, &main_rect_list_loop_body,
                                      main_rect_list_loop_merge_);

    builder_->setBuildPoint(&main_rect_list_loop_body);
    ResetUcodeInvocationStateInMain();
    ResetVertexShaderInvocationStateInMain();
    id_vector_temp_.clear();
    id_vector_temp_.push_back(main_rect_list_loop_vertex_index_);
    WriteVertexIndexToRegister0(builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassFunction,
                                    var_main_rect_list_guest_vertex_indices_, id_vector_temp_),
        spv::NoPrecision));
  }

  spv::Block& main_loop_pre_header = *builder_->getBuildPoint();
  main_loop_header_ = &builder_->makeNewBlock();
  spv::Block& main_loop_body = builder_->makeNewBlock();

  main_loop_continue_ = new spv::Block(builder_->getUniqueId(), *function_main_);
  main_loop_merge_ = new spv::Block(builder_->getUniqueId(), *function_main_);
  builder_->createBranch(main_loop_header_);

  bool has_main_switch = !current_shader().label_addresses().empty();

  builder_->setBuildPoint(main_loop_header_);
  spv::Id main_loop_pc_current = spv::NoResult;
  if (has_main_switch) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(const_int_0_);
    id_vector_temp_.push_back(main_loop_pre_header.getId());
    main_loop_pc_next_ = builder_->getUniqueId();
    id_vector_temp_.push_back(main_loop_pc_next_);
    id_vector_temp_.push_back(main_loop_continue_->getId());
    main_loop_pc_current = builder_->createOp(spv::OpPhi, type_int_, id_vector_temp_);
  }
  uint_vector_temp_.clear();
  builder_->createLoopMerge(main_loop_merge_, main_loop_continue_, spv::LoopControlDontUnrollMask,
                            uint_vector_temp_);
  builder_->createBranch(&main_loop_body);

  builder_->setBuildPoint(&main_loop_body);
  if (has_main_switch) {
    main_switch_header_ = builder_->getBuildPoint();
    main_switch_merge_ = new spv::Block(builder_->getUniqueId(), *function_main_);
    builder_->createSelectionMerge(main_switch_merge_, spv::SelectionControlDontFlattenMask);
    main_switch_op_ = std::make_unique<spv::Instruction>(spv::OpSwitch);
    main_switch_op_->addIdOperand(main_loop_pc_current);
    main_switch_op_->addIdOperand(main_switch_merge_->getId());

    main_switch_merge_->addPredecessor(main_switch_header_);

    spv::Block* main_switch_case_0_block = new spv::Block(builder_->getUniqueId(), *function_main_);
    main_switch_op_->addImmediateOperand(0);
    main_switch_op_->addIdOperand(main_switch_case_0_block->getId());

    main_switch_case_0_block->addPredecessor(main_switch_header_);
    function_main_->addBlock(main_switch_case_0_block);
    builder_->setBuildPoint(main_switch_case_0_block);
  }
}

std::vector<uint8_t> SpirvShaderTranslator::CompleteTranslation() {
  if (!is_depth_only_fragment_shader_) {
    CloseExecConditionals();
    bool has_main_switch = !current_shader().label_addresses().empty();

    if (!builder_->getBuildPoint()->isTerminated()) {
      builder_->createBranch(has_main_switch ? main_switch_merge_ : main_loop_merge_);
    }
    if (has_main_switch) {
      builder_->setBuildPoint(main_switch_header_);
      builder_->getBuildPoint()->addInstruction(std::move(main_switch_op_));

      function_main_->addBlock(main_switch_merge_);
      builder_->setBuildPoint(main_switch_merge_);
      builder_->createBranch(main_loop_merge_);
    }

    function_main_->addBlock(main_loop_continue_);
    builder_->setBuildPoint(main_loop_continue_);
    if (has_main_switch) {
      if (main_switch_next_pc_phi_operands_.empty()) {
        main_switch_next_pc_phi_operands_.push_back(builder_->makeIntConstant(-1));
      }
      std::unique_ptr<spv::Instruction> main_loop_pc_next_op = std::make_unique<spv::Instruction>(
          main_loop_pc_next_, type_int_,
          main_switch_next_pc_phi_operands_.size() >= 2 ? spv::OpPhi : spv::OpCopyObject);
      for (spv::Id operand : main_switch_next_pc_phi_operands_) {
        main_loop_pc_next_op->addIdOperand(operand);
      }
      builder_->getBuildPoint()->addInstruction(std::move(main_loop_pc_next_op));
    }
    builder_->createBranch(main_loop_header_);

    function_main_->addBlock(main_loop_merge_);
    builder_->setBuildPoint(main_loop_merge_);
    if (main_vertex_rect_list_as_triangle_strip_) {
      assert_true(main_rect_list_loop_vertex_index_ != spv::NoResult);
      assert_true(var_main_rect_list_guest_positions_ != spv::NoResult);

      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(kOutputPerVertexMemberPosition));
      spv::Id position = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassOutput, output_per_vertex_, id_vector_temp_),
          spv::NoPrecision);
      id_vector_temp_.clear();
      id_vector_temp_.push_back(main_rect_list_loop_vertex_index_);
      builder_->createStore(position, builder_->createAccessChain(
                                          spv::StorageClassFunction,
                                          var_main_rect_list_guest_positions_, id_vector_temp_));

      uint32_t interpolators_remaining = GetModificationInterpolatorMask();
      uint32_t interpolator_index;
      while (rex::bit_scan_forward(interpolators_remaining, &interpolator_index)) {
        interpolators_remaining &= ~(UINT32_C(1) << interpolator_index);
        spv::Id rect_list_interpolators =
            var_main_rect_list_guest_interpolators_[interpolator_index];
        assert_true(rect_list_interpolators != spv::NoResult);
        spv::Id interpolator =
            builder_->createLoad(input_output_interpolators_[interpolator_index], spv::NoPrecision);
        id_vector_temp_.clear();
        id_vector_temp_.push_back(main_rect_list_loop_vertex_index_);
        builder_->createStore(
            interpolator, builder_->createAccessChain(spv::StorageClassFunction,
                                                      rect_list_interpolators, id_vector_temp_));
      }

      ExportToMemory(current_shader().memexport_eM_potentially_written_before_end());
      if (var_main_memexport_data_written_ != spv::NoResult) {
        builder_->createStore(const_uint_0_, var_main_memexport_data_written_);
      }

      builder_->createBranch(main_rect_list_loop_continue_);

      function_main_->addBlock(main_rect_list_loop_continue_);
      builder_->setBuildPoint(main_rect_list_loop_continue_);
      std::unique_ptr<spv::Instruction> main_rect_list_vertex_index_next_op =
          std::make_unique<spv::Instruction>(main_rect_list_loop_vertex_index_next_, type_int_,
                                             spv::OpIAdd);
      main_rect_list_vertex_index_next_op->addIdOperand(main_rect_list_loop_vertex_index_);
      main_rect_list_vertex_index_next_op->addIdOperand(builder_->makeIntConstant(1));
      builder_->getBuildPoint()->addInstruction(std::move(main_rect_list_vertex_index_next_op));
      builder_->createBranch(main_rect_list_loop_header_);

      function_main_->addBlock(main_rect_list_loop_merge_);
      builder_->setBuildPoint(main_rect_list_loop_merge_);
    }
  }

  if (!main_vertex_rect_list_as_triangle_strip_) {
    ExportToMemory(current_shader().memexport_eM_potentially_written_before_end());
  }

  if (is_vertex_shader()) {
    CompleteVertexOrTessEvalShaderInMain();
  } else if (is_pixel_shader()) {
    CompleteFragmentShaderInMain();
  }

  builder_->leaveFunction();

  spv::ExecutionModel execution_model;
  if (is_pixel_shader()) {
    execution_model = spv::ExecutionModelFragment;
    builder_->addExecutionMode(function_main_, spv::ExecutionModeOriginUpperLeft);
    if (IsExecutionModeEarlyFragmentTests()) {
      builder_->addExecutionMode(function_main_, spv::ExecutionModeEarlyFragmentTests);
    }

    if (!edram_fragment_shader_interlock_ &&
        (current_shader().writes_depth() || DSV_IsWritingFloat24Depth() ||
         DSV_IsApplyingPolygonOffset())) {
      builder_->addExecutionMode(function_main_, spv::ExecutionModeDepthReplacing);

      if (!current_shader().writes_depth() && !DSV_IsApplyingPolygonOffset() &&
          GetHostRtShaderModification().pixel.depth_stencil_mode ==
              Modification::DepthStencilMode::kFloat24Truncating) {
        builder_->addExecutionMode(function_main_, spv::ExecutionModeDepthLess);
      }
    }
    if (edram_fragment_shader_interlock_) {
      if (features_.fragment_shader_sample_interlock && !REXCVAR_GET(spirv_pixel_interlock_only)) {
        builder_->addCapability(spv::CapabilityFragmentShaderSampleInterlockEXT);
        builder_->addExecutionMode(function_main_, spv::ExecutionModeSampleInterlockOrderedEXT);
      } else {
        builder_->addCapability(spv::CapabilityFragmentShaderPixelInterlockEXT);
        builder_->addExecutionMode(function_main_, spv::ExecutionModePixelInterlockOrderedEXT);
      }
    }
  } else {
    assert_true(is_vertex_shader());
    if (IsSpirvTessEvalShader()) {
      execution_model = spv::ExecutionModelTessellationEvaluation;

      Modification shader_modification = GetSpirvShaderModification();
      Shader::HostVertexShaderType host_type = shader_modification.vertex.host_vertex_shader_type;

      switch (host_type) {
        case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
        case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
          builder_->addExecutionMode(function_main_, spv::ExecutionModeTriangles);
          break;
        case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
        case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
          builder_->addExecutionMode(function_main_, spv::ExecutionModeQuads);
          break;
        case Shader::HostVertexShaderType::kLineDomainCPIndexed:
        case Shader::HostVertexShaderType::kLineDomainPatchIndexed:
          builder_->addExecutionMode(function_main_, spv::ExecutionModeIsolines);
          break;
        default:
          assert_unhandled_case(host_type);
          break;
      }

      builder_->addExecutionMode(function_main_, shader_modification.vertex.tessellation_mode ==
                                                         xenos::TessellationMode::kDiscrete
                                                     ? spv::ExecutionModeSpacingEqual
                                                     : spv::ExecutionModeSpacingFractionalEven);

      builder_->addExecutionMode(function_main_, spv::ExecutionModeVertexOrderCw);
    } else {
      execution_model = spv::ExecutionModelVertex;
    }
  }
  if (features_.denorm_flush_to_zero_float32) {
    builder_->addCapability(spv::CapabilityDenormFlushToZero);
    builder_->addExecutionMode(function_main_, spv::ExecutionModeDenormFlushToZero, 32);
  }
  if (features_.signed_zero_inf_nan_preserve_float32 &&
      !REXCVAR_GET(spirv_disable_signed_zero_inf_nan_preserve)) {
    builder_->addCapability(spv::CapabilitySignedZeroInfNanPreserve);
    builder_->addExecutionMode(function_main_, spv::ExecutionModeSignedZeroInfNanPreserve, 32);
  }
  if (features_.rounding_mode_rte_float32 && !REXCVAR_GET(spirv_disable_rounding_mode_rte)) {
    builder_->addCapability(spv::CapabilityRoundingModeRTE);
    builder_->addExecutionMode(function_main_, spv::ExecutionModeRoundingModeRTE, 32);
  }
  spv::Instruction* entry_point = builder_->addEntryPoint(execution_model, function_main_, "main");
  for (spv::Id interface_id : main_interface_) {
    entry_point->addIdOperand(interface_id);
  }

  if (!is_depth_only_fragment_shader_) {
    size_t texture_binding_count = texture_bindings_.size();
    size_t sampler_binding_count = sampler_bindings_.size();
    for (size_t i = 0; i < sampler_binding_count; ++i) {
      builder_->addDecoration(sampler_bindings_[i].variable, spv::DecorationBinding,
                              int(texture_binding_count + i));
    }
  }

  std::vector<unsigned int> module_uints;
  builder_->dump(module_uints);

  std::vector<uint8_t> module_bytes;
  module_bytes.reserve(sizeof(unsigned int) * module_uints.size());
  module_bytes.insert(module_bytes.cend(), reinterpret_cast<const uint8_t*>(module_uints.data()),
                      reinterpret_cast<const uint8_t*>(module_uints.data()) +
                          sizeof(unsigned int) * module_uints.size());
  return module_bytes;
}

void SpirvShaderTranslator::PostTranslation() {
  Shader::Translation& translation = current_translation();
  if (!translation.is_valid()) {
    return;
  }
  SpirvShader* spirv_shader = dynamic_cast<SpirvShader*>(&translation.shader());
  if (spirv_shader &&
      !spirv_shader->bindings_setup_entered_.test_and_set(std::memory_order_relaxed)) {
    spirv_shader->texture_bindings_.clear();
    spirv_shader->texture_bindings_.reserve(texture_bindings_.size());
    for (const TextureBinding& translator_binding : texture_bindings_) {
      SpirvShader::TextureBinding& shader_binding = spirv_shader->texture_bindings_.emplace_back();

      std::memset(&shader_binding, 0, sizeof(shader_binding));
      shader_binding.fetch_constant = translator_binding.fetch_constant;
      shader_binding.dimension = translator_binding.dimension;
      shader_binding.is_signed = translator_binding.is_signed;
      spirv_shader->used_texture_mask_ |= UINT32_C(1) << translator_binding.fetch_constant;
    }
    spirv_shader->sampler_bindings_.clear();
    spirv_shader->sampler_bindings_.reserve(sampler_bindings_.size());
    for (const SamplerBinding& translator_binding : sampler_bindings_) {
      SpirvShader::SamplerBinding& shader_binding = spirv_shader->sampler_bindings_.emplace_back();
      shader_binding.fetch_constant = translator_binding.fetch_constant;
      shader_binding.mag_filter = translator_binding.mag_filter;
      shader_binding.min_filter = translator_binding.min_filter;
      shader_binding.mip_filter = translator_binding.mip_filter;
      shader_binding.aniso_filter = translator_binding.aniso_filter;
      shader_binding.border_color_forced = translator_binding.border_color_forced;
      shader_binding.forced_border_color = translator_binding.forced_border_color;
    }

    spirv_shader->bindings_ready_.store(true, std::memory_order_release);
  }
}

void SpirvShaderTranslator::ProcessLabel(uint32_t cf_index) {
  if (cf_index == 0) {
    return;
  }

  main_interpolators_unmodified_ &=
      ~current_shader().GetRegisterComponentsWrittenBeforeReentering(cf_index);

  assert_false(current_shader().label_addresses().empty());

  CloseExecConditionals();

  spv::Function& function = builder_->getBuildPoint()->getParent();

  spv::Block* new_case = new spv::Block(builder_->getUniqueId(), function);
  main_switch_op_->addImmediateOperand(cf_index);
  main_switch_op_->addIdOperand(new_case->getId());

  new_case->addPredecessor(main_switch_header_);

  if (!builder_->getBuildPoint()->isTerminated()) {
    main_switch_next_pc_phi_operands_.push_back(builder_->makeIntConstant(int(cf_index)));
    main_switch_next_pc_phi_operands_.push_back(builder_->getBuildPoint()->getId());
    builder_->createBranch(main_loop_continue_);
  }
  function.addBlock(new_case);
  builder_->setBuildPoint(new_case);
}

void SpirvShaderTranslator::ProcessExecInstructionBegin(const ParsedExecInstruction& instr) {
  UpdateExecConditionals(instr.type, instr.bool_constant_index, instr.condition);
}

void SpirvShaderTranslator::ProcessExecInstructionEnd(const ParsedExecInstruction& instr) {
  if (instr.is_end) {
    CloseInstructionPredication();
    if (!builder_->getBuildPoint()->isTerminated()) {
      builder_->createBranch(current_shader().label_addresses().empty() ? main_loop_merge_
                                                                        : main_switch_merge_);
    }
  }
  UpdateExecConditionals(instr.type, instr.bool_constant_index, instr.condition);
}

void SpirvShaderTranslator::ProcessLoopStartInstruction(const ParsedLoopStartInstruction& instr) {
  CloseExecConditionals();

  EnsureBuildPointAvailable();

  id_vector_temp_.clear();

  id_vector_temp_.push_back(builder_->makeIntConstant(1));

  id_vector_temp_.push_back(builder_->makeIntConstant(int(instr.loop_constant_index >> 2)));

  id_vector_temp_.push_back(builder_->makeIntConstant(int(instr.loop_constant_index & 3)));

  spv::Id loop_constant = builder_->createLoad(
      builder_->createAccessChain(spv::StorageClassUniform, uniform_bool_loop_constants_,
                                  id_vector_temp_),
      spv::NoPrecision);

  spv::Id const_int_8 = builder_->makeIntConstant(8);

  spv::Id loop_count_stack_old = builder_->createLoad(var_main_loop_count_, spv::NoPrecision);
  spv::Id loop_count_new = builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, loop_constant,
                                                 const_int_0_, const_int_8);
  id_vector_temp_.clear();
  id_vector_temp_.push_back(loop_count_new);
  for (unsigned int i = 0; i < 3; ++i) {
    id_vector_temp_.push_back(
        builder_->createCompositeExtract(loop_count_stack_old, type_uint_, i));
  }
  builder_->createStore(builder_->createCompositeConstruct(type_uint4_, id_vector_temp_),
                        var_main_loop_count_);

  spv::Id address_relative_stack_old =
      builder_->createLoad(var_main_loop_address_, spv::NoPrecision);
  id_vector_temp_.clear();
  if (instr.is_repeat) {
    id_vector_temp_.emplace_back();
  } else {
    id_vector_temp_.push_back(
        builder_->createUnaryOp(spv::OpBitcast, type_int_,
                                builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_,
                                                      loop_constant, const_int_8, const_int_8)));
  }
  for (unsigned int i = 0; i < 3; ++i) {
    id_vector_temp_.push_back(
        builder_->createCompositeExtract(address_relative_stack_old, type_int_, i));
  }
  if (instr.is_repeat) {
    id_vector_temp_[0] = id_vector_temp_[1];
  }
  builder_->createStore(builder_->createCompositeConstruct(type_int4_, id_vector_temp_),
                        var_main_loop_address_);

  spv::Block& head_block = *builder_->getBuildPoint();
  spv::Id loop_count_zero =
      builder_->createBinOp(spv::OpIEqual, type_bool_, loop_count_new, const_uint_0_);
  spv::Block& skip_block = builder_->makeNewBlock();
  spv::Block& body_block = builder_->makeNewBlock();
  builder_->createSelectionMerge(&body_block, spv::SelectionControlMaskNone);
  {
    std::unique_ptr<spv::Instruction> branch_conditional_op =
        std::make_unique<spv::Instruction>(spv::OpBranchConditional);
    branch_conditional_op->addIdOperand(loop_count_zero);
    branch_conditional_op->addIdOperand(skip_block.getId());
    branch_conditional_op->addIdOperand(body_block.getId());

    branch_conditional_op->addImmediateOperand(1);
    branch_conditional_op->addImmediateOperand(2);
    head_block.addInstruction(std::move(branch_conditional_op));
  }
  skip_block.addPredecessor(&head_block);
  body_block.addPredecessor(&head_block);
  builder_->setBuildPoint(&skip_block);
  main_switch_next_pc_phi_operands_.push_back(
      builder_->makeIntConstant(int(instr.loop_skip_address)));
  main_switch_next_pc_phi_operands_.push_back(builder_->getBuildPoint()->getId());
  builder_->createBranch(main_loop_continue_);
  builder_->setBuildPoint(&body_block);
}

void SpirvShaderTranslator::ProcessLoopEndInstruction(const ParsedLoopEndInstruction& instr) {
  CloseExecConditionals();

  EnsureBuildPointAvailable();

  spv::Id loop_count_stack_old = builder_->createLoad(var_main_loop_count_, spv::NoPrecision);
  spv::Id loop_count =
      builder_->createBinOp(spv::OpISub, type_uint_,
                            builder_->createCompositeExtract(loop_count_stack_old, type_uint_, 0),
                            builder_->makeUintConstant(1));
  spv::Id address_relative_stack_old =
      builder_->createLoad(var_main_loop_address_, spv::NoPrecision);

  bool break_is_true = instr.is_predicated_break && instr.predicate_condition;
  spv::Id condition = builder_->createBinOp(break_is_true ? spv::OpIEqual : spv::OpINotEqual,
                                            type_bool_, loop_count, const_uint_0_);
  if (instr.is_predicated_break) {
    condition = builder_->createBinOp(
        instr.predicate_condition ? spv::OpLogicalOr : spv::OpLogicalAnd, type_bool_, condition,
        builder_->createLoad(var_main_predicate_, spv::NoPrecision));
  }

  spv::Block& body_block = *builder_->getBuildPoint();
  spv::Block& continue_block = builder_->makeNewBlock();
  spv::Block& break_block = builder_->makeNewBlock();
  builder_->createSelectionMerge(&break_block, spv::SelectionControlMaskNone);
  {
    std::unique_ptr<spv::Instruction> branch_conditional_op =
        std::make_unique<spv::Instruction>(spv::OpBranchConditional);
    branch_conditional_op->addIdOperand(condition);

    if (break_is_true) {
      branch_conditional_op->addIdOperand(break_block.getId());
      branch_conditional_op->addIdOperand(continue_block.getId());
      branch_conditional_op->addImmediateOperand(1);
      branch_conditional_op->addImmediateOperand(2);
    } else {
      branch_conditional_op->addIdOperand(continue_block.getId());
      branch_conditional_op->addIdOperand(break_block.getId());
      branch_conditional_op->addImmediateOperand(2);
      branch_conditional_op->addImmediateOperand(1);
    }
    body_block.addInstruction(std::move(branch_conditional_op));
  }
  continue_block.addPredecessor(&body_block);
  break_block.addPredecessor(&body_block);

  builder_->setBuildPoint(&continue_block);

  builder_->createStore(
      builder_->createCompositeInsert(loop_count, loop_count_stack_old, type_uint4_, 0),
      var_main_loop_count_);

  id_vector_temp_.clear();

  id_vector_temp_.push_back(builder_->makeIntConstant(1));

  id_vector_temp_.push_back(builder_->makeIntConstant(int(instr.loop_constant_index >> 2)));

  id_vector_temp_.push_back(builder_->makeIntConstant(int(instr.loop_constant_index & 3)));
  spv::Id loop_constant = builder_->createLoad(
      builder_->createAccessChain(spv::StorageClassUniform, uniform_bool_loop_constants_,
                                  id_vector_temp_),
      spv::NoPrecision);
  spv::Id address_relative_old =
      builder_->createCompositeExtract(address_relative_stack_old, type_int_, 0);
  builder_->createStore(
      builder_->createCompositeInsert(
          builder_->createBinOp(
              spv::OpIAdd, type_int_, address_relative_old,
              builder_->createTriOp(
                  spv::OpBitFieldSExtract, type_int_,
                  builder_->createUnaryOp(spv::OpBitcast, type_int_, loop_constant),
                  builder_->makeIntConstant(16), builder_->makeIntConstant(8))),
          address_relative_stack_old, type_int4_, 0),
      var_main_loop_address_);

  main_switch_next_pc_phi_operands_.push_back(
      builder_->makeIntConstant(int(instr.loop_body_address)));
  main_switch_next_pc_phi_operands_.push_back(builder_->getBuildPoint()->getId());
  builder_->createBranch(main_loop_continue_);

  builder_->setBuildPoint(&break_block);

  id_vector_temp_.clear();
  for (unsigned int i = 1; i < 4; ++i) {
    id_vector_temp_.push_back(
        builder_->createCompositeExtract(loop_count_stack_old, type_uint_, i));
  }
  id_vector_temp_.push_back(const_uint_0_);
  builder_->createStore(builder_->createCompositeConstruct(type_uint4_, id_vector_temp_),
                        var_main_loop_count_);
  id_vector_temp_.clear();
  for (unsigned int i = 1; i < 4; ++i) {
    id_vector_temp_.push_back(
        builder_->createCompositeExtract(address_relative_stack_old, type_int_, i));
  }
  id_vector_temp_.push_back(const_int_0_);
  builder_->createStore(builder_->createCompositeConstruct(type_int4_, id_vector_temp_),
                        var_main_loop_address_);
}

void SpirvShaderTranslator::ProcessJumpInstruction(const ParsedJumpInstruction& instr) {
  ParsedExecInstruction::Type type;
  if (instr.type == ParsedJumpInstruction::Type::kConditional) {
    type = ParsedExecInstruction::Type::kConditional;
  } else if (instr.type == ParsedJumpInstruction::Type::kPredicated) {
    type = ParsedExecInstruction::Type::kPredicated;
  } else {
    type = ParsedExecInstruction::Type::kUnconditional;
  }
  UpdateExecConditionals(type, instr.bool_constant_index, instr.condition);

  CloseInstructionPredication();

  if (builder_->getBuildPoint()->isTerminated()) {
    return;
  }
  main_switch_next_pc_phi_operands_.push_back(builder_->makeIntConstant(int(instr.target_address)));
  main_switch_next_pc_phi_operands_.push_back(builder_->getBuildPoint()->getId());
  builder_->createBranch(main_loop_continue_);
}

void SpirvShaderTranslator::ProcessAllocInstruction(const ParsedAllocInstruction& instr,
                                                    uint8_t export_eM) {
  bool start_memexport =
      instr.type == ucode::AllocType::kMemory && current_shader().memexport_eM_written();
  if (export_eM || start_memexport) {
    CloseExecConditionals();
  }

  if (export_eM) {
    ExportToMemory(export_eM);

    builder_->createStore(const_uint_0_, var_main_memexport_data_written_);

    uint8_t export_eM_remaining = export_eM;
    uint32_t eM_index;
    while (rex::bit_scan_forward(export_eM_remaining, &eM_index)) {
      export_eM_remaining &= ~(uint8_t(1) << eM_index);
      builder_->createStore(const_float4_0_, var_main_memexport_data_[eM_index]);
    }
  }

  if (start_memexport) {
    builder_->createStore(const_float4_0_, var_main_memexport_address_);
  }
}

spv::Id SpirvShaderTranslator::SpirvSmearScalarResultOrConstant(spv::Id scalar,
                                                                spv::Id vector_type) {
  bool is_constant = builder_->isConstant(scalar);
  bool is_spec_constant = builder_->isSpecConstant(scalar);
  if (!is_constant && !is_spec_constant) {
    return builder_->smearScalar(spv::NoPrecision, scalar, vector_type);
  }
  assert_true(builder_->getTypeClass(builder_->getTypeId(scalar)) ==
              builder_->getTypeClass(builder_->getScalarTypeId(vector_type)));
  if (!builder_->isVectorType(vector_type)) {
    assert_true(builder_->isScalarType(vector_type));
    return scalar;
  }
  int num_components = builder_->getNumTypeComponents(vector_type);
  id_vector_temp_util_.clear();
  for (int i = 0; i < num_components; ++i) {
    id_vector_temp_util_.push_back(scalar);
  }
  return builder_->makeCompositeConstant(vector_type, id_vector_temp_util_, is_spec_constant);
}

uint32_t SpirvShaderTranslator::GetPsParamGenInterpolator() const {
  assert_true(is_pixel_shader());
  Modification modification = GetSpirvShaderModification();

  return (modification.pixel.param_gen_enable &&
          modification.pixel.param_gen_interpolator < register_count())
             ? modification.pixel.param_gen_interpolator
             : UINT32_MAX;
}

void SpirvShaderTranslator::EnsureBuildPointAvailable() {
  if (!builder_->getBuildPoint()->isTerminated()) {
    return;
  }
  spv::Block& new_block = builder_->makeNewBlock();
  new_block.setUnreachable();
  builder_->setBuildPoint(&new_block);
}

void SpirvShaderTranslator::ResetUcodeInvocationStateInMain() {
  if (is_depth_only_fragment_shader_) {
    return;
  }

  builder_->createStore(builder_->makeBoolConstant(false), var_main_predicate_);
  builder_->createStore(const_uint4_0_, var_main_loop_count_);
  builder_->createStore(const_int_0_, var_main_address_register_);
  builder_->createStore(const_int4_0_, var_main_loop_address_);
  builder_->createStore(const_float_0_, var_main_previous_scalar_);
  builder_->createStore(const_int_0_, var_main_vfetch_address_);
  builder_->createStore(const_int_0_, var_main_vfetch_bound_);
  builder_->createStore(const_float_0_, var_main_tfetch_lod_);
  builder_->createStore(const_float3_0_, var_main_tfetch_gradients_h_);
  builder_->createStore(const_float3_0_, var_main_tfetch_gradients_v_);

  if (var_main_memexport_address_ != spv::NoResult) {
    builder_->createStore(const_float4_0_, var_main_memexport_address_);
  }
  if (var_main_memexport_data_written_ != spv::NoResult) {
    builder_->createStore(const_uint_0_, var_main_memexport_data_written_);
  }
  for (spv::Id& memexport_data : var_main_memexport_data_) {
    if (memexport_data != spv::NoResult) {
      builder_->createStore(const_float4_0_, memexport_data);
    }
  }
}
}
