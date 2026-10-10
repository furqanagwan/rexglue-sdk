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

#ifndef REX_GRAPHICS_PIPELINE_SHADER_SPIRV_SHADER_TRANSLATOR_H_
#define REX_GRAPHICS_PIPELINE_SHADER_SPIRV_SHADER_TRANSLATOR_H_

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <rex/platform.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/translator.h>
#include <rex/graphics/pipeline/shader/spirv_builder.h>
#include <rex/graphics/xenos.h>

namespace rex::graphics {

class SpirvShaderTranslator : public ShaderTranslator {
 public:
  union Modification {
    static constexpr uint32_t kVersion = 23;

    enum class DepthStencilMode : uint32_t {
      kNoModifiers,

      kEarlyHint,

      kFloat24Truncating,

      kFloat24Rounding,

      kPolygonOffset,
      kFloat24TruncatingPolygonOffset,
      kFloat24RoundingPolygonOffset,

    };

    struct {
      uint32_t interpolator_mask : xenos::kMaxInterpolators;

      uint32_t output_point_parameters : 1;

      uint32_t dynamic_addressable_register_count : 8;

      Shader::HostVertexShaderType host_vertex_shader_type : Shader::kHostVertexShaderTypeBitCount;

      uint32_t user_clip_plane_count : 3;

      uint32_t user_clip_plane_cull : 1;

      uint32_t vertex_kill_and : 1;

      xenos::TessellationMode tessellation_mode : 2;
    } vertex;
    struct PixelShaderModification {
      uint32_t interpolator_mask : xenos::kMaxInterpolators;
      uint32_t interpolators_centroid : xenos::kMaxInterpolators;

      uint32_t dynamic_addressable_register_count : 7;
      uint32_t param_gen_enable : 1;
      uint32_t param_gen_interpolator : 4;

      uint32_t param_gen_point : 1;

      DepthStencilMode depth_stencil_mode : 3;

      xenos::BlendFactor rt0_blend_rgb_factor_for_premult : 5;
      xenos::BlendFactor rt0_blend_a_factor_for_premult : 5;

      uint32_t color_targets_used : xenos::kMaxColorRenderTargets;

      uint32_t fsi_no_blending_or_zpd_total : 1;

      uint32_t resolution_scale_native : 1;

      static constexpr uint32_t kFsiBitCount = 18;
      static constexpr uint32_t kFsiRtFormatsShift = xenos::kMsaaSamplesBits;
      static_assert(kFsiRtFormatsShift +
                            xenos::kMaxColorRenderTargets * xenos::kColorRenderTargetFormatBits <=
                        kFsiBitCount,
                    "The FSI fields have to fit in the host render target bits");

      uint32_t fsi_bits() const {
        return uint32_t(depth_stencil_mode) | (uint32_t(rt0_blend_rgb_factor_for_premult) << 3) |
               (uint32_t(rt0_blend_a_factor_for_premult) << 8) | (color_targets_used << 13) |
               (resolution_scale_native << 17);
      }
      void set_fsi_bits(uint32_t bits) {
        assert_zero(bits >> kFsiBitCount);
        depth_stencil_mode = DepthStencilMode(bits & 0x7);
        rt0_blend_rgb_factor_for_premult = xenos::BlendFactor((bits >> 3) & 0x1F);
        rt0_blend_a_factor_for_premult = xenos::BlendFactor((bits >> 8) & 0x1F);
        color_targets_used = (bits >> 13) & 0xF;
        resolution_scale_native = (bits >> 17) & 1;

        assert_true(fsi_bits() == bits);
      }

      xenos::MsaaSamples fsi_msaa_samples() const {
        return xenos::MsaaSamples(fsi_bits() & ((uint32_t(1) << xenos::kMsaaSamplesBits) - 1));
      }
      void set_fsi_msaa_samples(xenos::MsaaSamples msaa_samples) {
        assert_true(msaa_samples <= xenos::MsaaSamples::k4X);
        constexpr uint32_t kMask = (uint32_t(1) << xenos::kMsaaSamplesBits) - 1;
        set_fsi_bits((fsi_bits() & ~kMask) | uint32_t(msaa_samples));
      }

      xenos::ColorRenderTargetFormat fsi_rt_format(uint32_t rt) const {
        assert_true(rt < xenos::kMaxColorRenderTargets);
        constexpr uint32_t kMask = (uint32_t(1) << xenos::kColorRenderTargetFormatBits) - 1;
        return xenos::ColorRenderTargetFormat(
            (fsi_bits() >> (kFsiRtFormatsShift + rt * xenos::kColorRenderTargetFormatBits)) &
            kMask);
      }
      bool fsi_no_blending() const { return fsi_no_blending_or_zpd_total != 0; }
      void set_fsi_no_blending(bool value) { fsi_no_blending_or_zpd_total = uint32_t(value); }
      bool zpd_total() const { return fsi_no_blending_or_zpd_total != 0; }
      void set_zpd_total(bool value) { fsi_no_blending_or_zpd_total = uint32_t(value); }

      void set_fsi_rt_format(uint32_t rt, xenos::ColorRenderTargetFormat format) {
        assert_true(rt < xenos::kMaxColorRenderTargets);
        assert_zero(uint32_t(format) >> xenos::kColorRenderTargetFormatBits);
        uint32_t shift = kFsiRtFormatsShift + rt * xenos::kColorRenderTargetFormatBits;
        uint32_t mask = ((uint32_t(1) << xenos::kColorRenderTargetFormatBits) - 1) << shift;
        set_fsi_bits((fsi_bits() & ~mask) | ((uint32_t(format) << shift) & mask));
      }
    } pixel;
    uint64_t value = 0;

    explicit Modification(uint64_t modification_value = 0) : value(modification_value) {
      static_assert_size(*this, sizeof(value));
    }
  };

  enum : uint32_t {
    kSysFlag_VertexIndexLoad_Shift,
    kSysFlag_ComputeOrPrimitiveVertexIndexLoad_Shift,
    kSysFlag_ComputeOrPrimitiveVertexIndexLoad32Bit_Shift,
    kSysFlag_XYDividedByW_Shift,
    kSysFlag_ZDividedByW_Shift,
    kSysFlag_WNotReciprocal_Shift,
    kSysFlag_PrimitivePolygonal_Shift,
    kSysFlag_PrimitiveLine_Shift,
    kSysFlag_MsaaSamples_Shift,
    kSysFlag_DepthFloat24_Shift = kSysFlag_MsaaSamples_Shift + xenos::kMsaaSamplesBits,
    kSysFlag_AlphaPassIfLess_Shift,
    kSysFlag_AlphaPassIfEqual_Shift,
    kSysFlag_AlphaPassIfGreater_Shift,
    kSysFlag_ConvertColor0ToGamma_Shift,
    kSysFlag_ConvertColor1ToGamma_Shift,
    kSysFlag_ConvertColor2ToGamma_Shift,
    kSysFlag_ConvertColor3ToGamma_Shift,

    kSysFlag_FSIDepthStencil_Shift,
    kSysFlag_FSIDepthPassIfLess_Shift,
    kSysFlag_FSIDepthPassIfEqual_Shift,
    kSysFlag_FSIDepthPassIfGreater_Shift,

    kSysFlag_FSIDepthWrite_Shift,
    kSysFlag_FSIStencilTest_Shift,

    kSysFlag_FSIDepthStencilEarlyWrite_Shift,

    kSysFlag_Count,

    kSysFlag_VertexIndexLoad = 1u << kSysFlag_VertexIndexLoad_Shift,

    kSysFlag_ComputeOrPrimitiveVertexIndexLoad =
        1u << kSysFlag_ComputeOrPrimitiveVertexIndexLoad_Shift,
    kSysFlag_ComputeOrPrimitiveVertexIndexLoad32Bit =
        1u << kSysFlag_ComputeOrPrimitiveVertexIndexLoad32Bit_Shift,
    kSysFlag_XYDividedByW = 1u << kSysFlag_XYDividedByW_Shift,
    kSysFlag_ZDividedByW = 1u << kSysFlag_ZDividedByW_Shift,
    kSysFlag_WNotReciprocal = 1u << kSysFlag_WNotReciprocal_Shift,
    kSysFlag_PrimitivePolygonal = 1u << kSysFlag_PrimitivePolygonal_Shift,
    kSysFlag_PrimitiveLine = 1u << kSysFlag_PrimitiveLine_Shift,
    kSysFlag_DepthFloat24 = 1u << kSysFlag_DepthFloat24_Shift,
    kSysFlag_AlphaPassIfLess = 1u << kSysFlag_AlphaPassIfLess_Shift,
    kSysFlag_AlphaPassIfEqual = 1u << kSysFlag_AlphaPassIfEqual_Shift,
    kSysFlag_AlphaPassIfGreater = 1u << kSysFlag_AlphaPassIfGreater_Shift,
    kSysFlag_ConvertColor0ToGamma = 1u << kSysFlag_ConvertColor0ToGamma_Shift,
    kSysFlag_ConvertColor1ToGamma = 1u << kSysFlag_ConvertColor1ToGamma_Shift,
    kSysFlag_ConvertColor2ToGamma = 1u << kSysFlag_ConvertColor2ToGamma_Shift,
    kSysFlag_ConvertColor3ToGamma = 1u << kSysFlag_ConvertColor3ToGamma_Shift,
    kSysFlag_FSIDepthStencil = 1u << kSysFlag_FSIDepthStencil_Shift,
    kSysFlag_FSIDepthPassIfLess = 1u << kSysFlag_FSIDepthPassIfLess_Shift,
    kSysFlag_FSIDepthPassIfEqual = 1u << kSysFlag_FSIDepthPassIfEqual_Shift,
    kSysFlag_FSIDepthPassIfGreater = 1u << kSysFlag_FSIDepthPassIfGreater_Shift,
    kSysFlag_FSIDepthWrite = 1u << kSysFlag_FSIDepthWrite_Shift,
    kSysFlag_FSIStencilTest = 1u << kSysFlag_FSIStencilTest_Shift,
    kSysFlag_FSIDepthStencilEarlyWrite = 1u << kSysFlag_FSIDepthStencilEarlyWrite_Shift,
  };
  static_assert(kSysFlag_Count <= 32, "Too many flags in the system constants");

  struct SystemConstants {
    uint32_t flags;
    uint32_t vertex_index_load_address;
    uint32_t vertex_index_count;
    xenos::Endian vertex_index_endian;
    int32_t vertex_base_index;
    uint32_t padding_after_vertex_index[3];

    float ndc_scale[3];
    float point_vertex_diameter_min;

    float ndc_offset[3];
    float point_vertex_diameter_max;

    float point_constant_diameter[2];

    float point_screen_diameter_to_ndc_radius[2];

    uint32_t texture_swizzled_signs[8];

    uint32_t texture_swizzles[16];

    uint32_t textures_resolved;

    float alpha_test_reference;

    uint32_t alpha_to_mask;

    uint32_t zpd_fsi_counter_index;

    uint32_t edram_32bpp_tile_pitch_dwords_scaled;
    uint32_t edram_depth_base_dwords_scaled;
    uint32_t padding_after_depth_info[2];

    float color_exp_bias[4];

    float edram_poly_offset_front_scale;
    float edram_poly_offset_back_scale;
    float edram_poly_offset_front_offset;
    float edram_poly_offset_back_offset;

    union {
      struct {
        uint32_t edram_stencil_front_reference_masks;
        uint32_t edram_stencil_front_func_ops;

        uint32_t edram_stencil_back_reference_masks;
        uint32_t edram_stencil_back_func_ops;
      };
      struct {
        uint32_t edram_stencil_front[2];
        uint32_t edram_stencil_back[2];
      };
    };

    uint32_t edram_rt_base_dwords_scaled[4];

    uint32_t padding_after_rt_base_dwords_scaled[4];

    uint32_t edram_rt_blend_factors_ops[4];

    uint32_t edram_rt_keep_mask[4][2];

    float edram_rt_clamp[4][4];

    float edram_blend_constant[4];

    float user_clip_planes[6][4];

    float tessellation_factor_range[2];
    float tessellation_padding0[2];
    uint32_t tessellation_vertex_index_endian;
    uint32_t tessellation_vertex_index_offset;
    uint32_t tessellation_vertex_index_min_max[2];

    uint32_t interpreter_ucode_base_dwords;
    uint32_t interpreter_cf_instr_count;
    uint32_t texture_integer_scale_pad[2];

    uint32_t texture_integer_scale_bits[32];
  };

  static_assert(offsetof(SystemConstants, tessellation_factor_range) == 512 &&
                    offsetof(SystemConstants, tessellation_vertex_index_endian) == 528 &&
                    offsetof(SystemConstants, tessellation_vertex_index_offset) == 532 &&
                    offsetof(SystemConstants, tessellation_vertex_index_min_max) == 536,
                "Keep xenos_draw.glsli tessellation offsets in sync with "
                "SystemConstants");

  enum ConstantBuffer : uint32_t {
    kConstantBufferSystem,
    kConstantBufferFloatVertex,
    kConstantBufferFloatPixel,
    kConstantBufferBoolLoop,
    kConstantBufferFetch,

    kConstantBufferCount,
  };

  enum DescriptorSet : uint32_t {

    kDescriptorSetSharedMemoryAndEdram,

    kDescriptorSetConstants,

    kDescriptorSetMutableLayoutsStart,

    kDescriptorSetTexturesVertex = kDescriptorSetMutableLayoutsStart,

    kDescriptorSetTexturesPixel,

    kDescriptorSetCount,
  };
  static_assert(kDescriptorSetCount <= 4,
                "The number of descriptor sets used by translated shaders must be within "
                "the minimum Vulkan maxBoundDescriptorSets requirement of 4, which is "
                "the limit on most GPUs used in Android devices - Arm Mali, Imagination "
                "PowerVR, Qualcomm Adreno 6xx and older, as well as on old PC Nvidia "
                "drivers");

  static constexpr uint32_t kSpirvMagicToolId = 26;

  struct Features {
    explicit Features(bool all = false);

    unsigned int spirv_version;

    uint32_t max_storage_buffer_range;

    bool full_draw_index_uint32;

    bool vertex_pipeline_stores_and_atomics;
    bool fragment_stores_and_atomics;

    bool clip_distance;
    bool cull_distance;

    bool image_view_format_swizzle;

    bool signed_zero_inf_nan_preserve_float32;
    bool denorm_flush_to_zero_float32;
    bool rounding_mode_rte_float32;

    bool fragment_shader_sample_interlock;

    bool demote_to_helper_invocation;

    bool fragment_shader_barycentric;

    bool allow_float_contraction = false;
  };

  SpirvShaderTranslator(const Features& features, bool native_2x_msaa_with_attachments,
                        bool native_2x_msaa_no_attachments, bool edram_fragment_shader_interlock,
                        bool precise_interpolation,

                        uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y)
      : features_(features),
        native_2x_msaa_with_attachments_(native_2x_msaa_with_attachments),
        native_2x_msaa_no_attachments_(native_2x_msaa_no_attachments),
        edram_fragment_shader_interlock_(edram_fragment_shader_interlock),
        precise_interpolation_(precise_interpolation),
        zpd_full_counters_(REXCVAR_GET(occlusion_query_full_counters)),
        draw_resolution_scale_x_(draw_resolution_scale_x),
        draw_resolution_scale_y_(draw_resolution_scale_y) {}

  uint64_t GetDefaultVertexShaderModification(
      uint32_t dynamic_addressable_register_count,
      Shader::HostVertexShaderType host_vertex_shader_type =
          Shader::HostVertexShaderType::kVertex) const override;
  uint64_t GetDefaultPixelShaderModification(
      uint32_t dynamic_addressable_register_count) const override;

  const Features& features() const { return features_; }

  static constexpr uint32_t GetSharedMemoryStorageBufferCountLog2(
      uint32_t max_storage_buffer_range) {
    if (max_storage_buffer_range >= 512 * 1024 * 1024) {
      return 0;
    }
    if (max_storage_buffer_range >= 256 * 1024 * 1024) {
      return 1;
    }
    return 2;
  }
  uint32_t GetSharedMemoryStorageBufferCountLog2() const {
    return GetSharedMemoryStorageBufferCountLog2(features_.max_storage_buffer_range);
  }

  std::vector<uint8_t> CreateDepthOnlyFragmentShader(
      Modification::DepthStencilMode depth_stencil_mode =
          Modification::DepthStencilMode::kNoModifiers,
      bool zpd_total = false, bool viz_survey = false);

  std::vector<uint8_t> CreateDepthOnlyFragmentShader(xenos::MsaaSamples fsi_msaa_samples,
                                                     bool viz_survey = false);

  static spv::Id PreClampedFloat32To7e3(SpirvBuilder& builder, spv::Id f32_scalar,
                                        spv::Id ext_inst_glsl_std_450);

  static spv::Id UnclampedFloat32To7e3(SpirvBuilder& builder, spv::Id f32_scalar,
                                       spv::Id ext_inst_glsl_std_450);

  static spv::Id Float7e3To32(SpirvBuilder& builder, spv::Id f10_uint_scalar, uint32_t f10_shift,
                              bool result_as_uint, spv::Id ext_inst_glsl_std_450);

  static spv::Id PreClampedDepthTo20e4(SpirvBuilder& builder, spv::Id f32_scalar,
                                       bool round_to_nearest_even, bool remap_from_0_to_0_5,
                                       spv::Id ext_inst_glsl_std_450);

  static spv::Id Depth20e4To32(SpirvBuilder& builder, spv::Id f24_uint_scalar, uint32_t f24_shift,
                               bool remap_to_0_to_0_5, bool result_as_uint,
                               spv::Id ext_inst_glsl_std_450);

  static spv::Id PWLGammaToLinear(SpirvBuilder* builder_, spv::Id value, bool pre_saturated,
                                  spv::Id ext_inst_glsl_std_450);
  static spv::Id LinearToPWLGamma(SpirvBuilder* builder_, spv::Id value, bool pre_saturated,
                                  spv::Id ext_inst_glsl_std_450);

 protected:
  void Reset() override;

  uint32_t GetModificationRegisterCount() const override;

  void StartTranslation() override;

  std::vector<uint8_t> CompleteTranslation() override;

  void PostTranslation() override;

  void ProcessLabel(uint32_t cf_index) override;

  void ProcessExecInstructionBegin(const ParsedExecInstruction& instr) override;
  void ProcessExecInstructionEnd(const ParsedExecInstruction& instr) override;
  void ProcessLoopStartInstruction(const ParsedLoopStartInstruction& instr) override;
  void ProcessLoopEndInstruction(const ParsedLoopEndInstruction& instr) override;
  void ProcessJumpInstruction(const ParsedJumpInstruction& instr) override;
  void ProcessAllocInstruction(const ParsedAllocInstruction& instr, uint8_t export_eM) override;

  void ProcessVertexFetchInstruction(const ParsedVertexFetchInstruction& instr) override;
  void ProcessTextureFetchInstruction(const ParsedTextureFetchInstruction& instr) override;
  void ProcessAluInstruction(const ParsedAluInstruction& instr,
                             uint8_t memexport_eM_potentially_written_before) override;

 private:
  struct TextureBinding {
    uint32_t fetch_constant;

    xenos::FetchOpDimension dimension;
    bool is_signed;

    spv::Id variable;
  };

  struct SamplerBinding {
    uint32_t fetch_constant;
    xenos::TextureFilter mag_filter;
    xenos::TextureFilter min_filter;
    xenos::TextureFilter mip_filter;
    xenos::AnisoFilter aniso_filter;
    bool border_color_forced;
    xenos::BorderColor forced_border_color;

    spv::Id variable;
  };

  spv::Id SpirvSmearScalarResultOrConstant(spv::Id scalar, spv::Id vector_type);

  Modification GetSpirvShaderModification() const {
    return Modification(current_translation().modification());
  }

  bool IsSpirvVertexShader() const {
    return is_vertex_shader() && !Shader::IsHostVertexShaderTypeDomain(
                                     GetSpirvShaderModification().vertex.host_vertex_shader_type);
  }
  bool IsSpirvTessEvalShader() const {
    return is_vertex_shader() && Shader::IsHostVertexShaderTypeDomain(
                                     GetSpirvShaderModification().vertex.host_vertex_shader_type);
  }
  bool IsSpirvComputeShader() const {
    return is_vertex_shader() && GetSpirvShaderModification().vertex.host_vertex_shader_type ==
                                     Shader::HostVertexShaderType::kMemExportCompute;
  }
  bool IsSpirvRectListAsTriangleStrip() const {
    return IsSpirvVertexShader() && GetSpirvShaderModification().vertex.host_vertex_shader_type ==
                                        Shader::HostVertexShaderType::kRectangleListAsTriangleStrip;
  }

  Modification GetHostRtShaderModification() const {
    assert_false(edram_fragment_shader_interlock_);
    return GetSpirvShaderModification();
  }

  bool IsZpdTotal() const {
    return !edram_fragment_shader_interlock_ && GetSpirvShaderModification().pixel.zpd_total();
  }

  bool IsExecutionModeEarlyFragmentTests() const {
    return !edram_fragment_shader_interlock_ && is_pixel_shader() &&
           GetHostRtShaderModification().pixel.depth_stencil_mode ==
               Modification::DepthStencilMode::kEarlyHint &&
           !IsZpdTotal() && current_shader().implicit_early_z_write_allowed();
  }

  bool DSV_IsWritingFloat24Depth() const {
    if (edram_fragment_shader_interlock_) {
      return false;
    }
    Modification::DepthStencilMode depth_stencil_mode =
        GetHostRtShaderModification().pixel.depth_stencil_mode;
    return depth_stencil_mode == Modification::DepthStencilMode::kFloat24Truncating ||
           depth_stencil_mode == Modification::DepthStencilMode::kFloat24TruncatingPolygonOffset ||
           depth_stencil_mode == Modification::DepthStencilMode::kFloat24Rounding ||
           depth_stencil_mode == Modification::DepthStencilMode::kFloat24RoundingPolygonOffset;
  }

  bool DSV_IsApplyingPolygonOffset() const {
    if (edram_fragment_shader_interlock_) {
      return false;
    }
    Modification::DepthStencilMode depth_stencil_mode =
        GetHostRtShaderModification().pixel.depth_stencil_mode;
    return depth_stencil_mode == Modification::DepthStencilMode::kPolygonOffset ||
           depth_stencil_mode == Modification::DepthStencilMode::kFloat24TruncatingPolygonOffset ||
           depth_stencil_mode == Modification::DepthStencilMode::kFloat24RoundingPolygonOffset;
  }

  bool IsSampleRate() const {
    return is_pixel_shader() && DSV_IsWritingFloat24Depth() && !current_shader().writes_depth();
  }

  uint32_t GetModificationInterpolatorMask() const {
    Modification modification = GetSpirvShaderModification();
    return is_vertex_shader() ? modification.vertex.interpolator_mask
                              : modification.pixel.interpolator_mask;
  }

  uint32_t GetPsParamGenInterpolator() const;

  void EnsureBuildPointAvailable();

  void StartVertexOrTessEvalShaderBeforeMain();
  void StartVertexOrTessEvalShaderInMain();
  void CompleteVertexOrTessEvalShaderInMain();
  void ResetUcodeInvocationStateInMain();
  void ResetVertexShaderInvocationStateInMain();
  void WriteVertexIndexToRegister0(spv::Id vertex_index);

  void StartFragmentShaderBeforeMain();
  void StartFragmentShaderInMain();
  void CompleteFragmentShaderInMain();

  void CompleteFragmentShader_DSV_DepthTo24Bit();

  void UpdateExecConditionals(ParsedExecInstruction::Type type, uint32_t bool_constant_index,
                              bool condition);

  void UpdateInstructionPredication(bool predicated, bool condition);

  void CloseInstructionPredication();

  void CloseExecConditionals();

  spv::Id GetStorageAddressingIndex(InstructionStorageAddressingMode addressing_mode,
                                    uint32_t storage_index, bool is_float_constant = false);

  spv::Id LoadOperandStorage(const InstructionOperand& operand);
  spv::Id ApplyOperandModifiers(spv::Id operand_value, const InstructionOperand& original_operand,
                                bool invert_negate = false, bool force_absolute = false);

  spv::Id GetUnmodifiedOperandComponents(spv::Id operand_storage,
                                         const InstructionOperand& original_operand,
                                         uint32_t components);
  spv::Id GetOperandComponents(spv::Id operand_storage, const InstructionOperand& original_operand,
                               uint32_t components, bool invert_negate = false,
                               bool force_absolute = false) {
    return ApplyOperandModifiers(
        GetUnmodifiedOperandComponents(operand_storage, original_operand, components),
        original_operand, invert_negate, force_absolute);
  }

  void GetOperandScalarXY(spv::Id operand_storage, const InstructionOperand& original_operand,
                          spv::Id& a_out, spv::Id& b_out, bool invert_negate = false,
                          bool force_absolute = false);

  spv::Id GetAbsoluteOperand(spv::Id operand_storage, const InstructionOperand& original_operand);

  void StoreResult(const InstructionResult& result, spv::Id value);

  spv::Id ZeroIfAnyOperandIsZero(spv::Id value, spv::Id operand_0_abs, spv::Id operand_1_abs);

  spv::Id ReduceFloatPrecision(spv::Id value, uint32_t mantissa_bits);

  spv::Id PackFloat16x2ExtendedRange(spv::Id float2_value);
  spv::Id UnpackFloat16x2ExtendedRange(spv::Id packed_uint);

  void KillPixel(spv::Id condition, uint8_t memexport_eM_potentially_written_before);

  spv::Id ProcessVectorAluOperation(const ParsedAluInstruction& instr,
                                    uint8_t memexport_eM_potentially_written_before,
                                    bool& predicate_written);

  spv::Id ProcessScalarAluOperation(const ParsedAluInstruction& instr,
                                    uint8_t memexport_eM_potentially_written_before,
                                    bool& predicate_written);

  spv::Id EndianSwap32Uint(spv::Id value, spv::Id endian);

  spv::Id EndianSwap128Uint4(spv::Id value, spv::Id endian);

  spv::Id LoadUint32FromSharedMemory(spv::Id address_dwords_int);

  void StoreUint32ToSharedMemory(spv::Id value, spv::Id address_dwords_int,
                                 spv::Id replace_mask = spv::NoResult);

  bool IsMemoryExportSupported() const {
    if (is_pixel_shader()) {
      return features_.fragment_stores_and_atomics;
    }
    return features_.vertex_pipeline_stores_and_atomics || IsSpirvComputeShader();
  }

  bool IsMemoryExportUsed() const {
    return current_shader().memexport_eM_written() && IsMemoryExportSupported();
  }

  void ExportToMemory(uint8_t export_eM);

  size_t FindOrAddTextureBinding(uint32_t fetch_constant, xenos::FetchOpDimension dimension,
                                 bool is_signed);
  size_t FindOrAddSamplerBinding(
      uint32_t fetch_constant, xenos::TextureFilter mag_filter, xenos::TextureFilter min_filter,
      xenos::TextureFilter mip_filter, xenos::AnisoFilter aniso_filter,
      std::optional<xenos::BorderColor> forced_border_color = std::nullopt);

  void SampleTexture(spv::Builder::TextureParameters& texture_parameters,
                     spv::ImageOperandsMask image_operands_mask, spv::Id image_unsigned,
                     spv::Id image_signed, spv::Id sampler_unsigned, spv::Id sampler_signed,
                     spv::Id is_any_unsigned, spv::Id is_any_signed, spv::Id& result_unsigned_out,
                     spv::Id& result_signed_out, spv::Id lerp_factor = spv::NoResult,
                     spv::Id lerp_first_unsigned = spv::NoResult,
                     spv::Id lerp_first_signed = spv::NoResult);

  spv::Id QueryTextureLod(spv::Builder::TextureParameters& texture_parameters,
                          spv::Id image_unsigned, spv::Id image_signed, spv::Id sampler,
                          spv::Id is_all_signed);

  spv::Id LoadMsaaSamplesFromFlags();

  xenos::MsaaSamples FSI_GetMsaaSamples() const {
    assert_true(edram_fragment_shader_interlock_);
    return GetSpirvShaderModification().pixel.fsi_msaa_samples();
  }

  bool FSI_GetNoBlending() const {
    assert_true(edram_fragment_shader_interlock_);
    return GetSpirvShaderModification().pixel.fsi_no_blending();
  }

  xenos::ColorRenderTargetFormat FSI_GetRtFormat(uint32_t rt) const {
    assert_true(edram_fragment_shader_interlock_);
    return GetSpirvShaderModification().pixel.fsi_rt_format(rt);
  }

  uint32_t FSI_GetSampleCount() const { return uint32_t(1) << uint32_t(FSI_GetMsaaSamples()); }

  bool FSI_IsDepthStencilEarly() const {
    assert_true(edram_fragment_shader_interlock_);
    return !is_depth_only_fragment_shader_ && !current_shader().writes_depth() &&
           !current_shader().memexport_eM_written();
  }
  void FSI_LoadSampleMask();
  void FSI_LoadEdramOffsets();

  spv::Id FSI_AddSampleOffset(spv::Id sample_0_address, uint32_t sample_index,
                              spv::Id is_64bpp = spv::NoResult);

  void FSI_DepthStencilTest(bool sample_mask_potentially_narrowed_previouly);

  void FSI_AddMSAASamplesToZPD(bool count_passed, bool count_failed);

  void FBO_AddMSAASamplesToZPDTotal();

  void FSI_AlphaToMaskSample(bool initialize, uint32_t sample_index, float threshold_base,
                             spv::Id threshold_offset, float threshold_offset_scale, spv::Id alpha,
                             spv::Id& coverage_out);

  void FSI_AlphaToMask();

  std::array<spv::Id, 2> FSI_ClampAndPackColor(spv::Id color_float4,
                                               xenos::ColorRenderTargetFormat format);
  std::array<spv::Id, 4> FSI_UnpackColor(std::array<spv::Id, 2> color_packed,
                                         xenos::ColorRenderTargetFormat format);

  spv::Id FSI_FlushNaNClampAndInBlending(spv::Id color_or_alpha, spv::Id is_fixed_point,
                                         spv::Id min_value, spv::Id max_value);
  spv::Id FSI_ApplyColorBlendFactor(spv::Id value, spv::Id is_fixed_point, spv::Id clamp_min_value,
                                    spv::Id clamp_max_value, spv::Id factor, spv::Id source_color,
                                    spv::Id source_alpha, spv::Id dest_color, spv::Id dest_alpha,
                                    spv::Id constant_color, spv::Id constant_alpha);
  spv::Id FSI_ApplyAlphaBlendFactor(spv::Id value, spv::Id is_fixed_point, spv::Id clamp_min_value,
                                    spv::Id clamp_max_value, spv::Id factor, spv::Id source_alpha,
                                    spv::Id dest_alpha, spv::Id constant_alpha);

  spv::Id FSI_BlendColorOrAlphaWithUnclampedResult(
      spv::Id is_fixed_point, spv::Id clamp_min_value, spv::Id clamp_max_value,
      spv::Id source_color_clamped, spv::Id source_alpha_clamped, spv::Id dest_color,
      spv::Id dest_alpha, spv::Id constant_color_clamped, spv::Id constant_alpha_clamped,
      spv::Id equation, spv::Id source_factor, spv::Id dest_factor);

  Features features_;
  bool native_2x_msaa_with_attachments_;
  bool native_2x_msaa_no_attachments_;
  uint32_t draw_resolution_scale_x_;
  uint32_t draw_resolution_scale_y_;

  bool IsCurrentDrawScaleNative() const {
    return !edram_fragment_shader_interlock_ && is_pixel_shader() &&
           GetHostRtShaderModification().pixel.resolution_scale_native;
  }
  uint32_t GetCurrentDrawResolutionScaleX() const {
    return IsCurrentDrawScaleNative() ? 1 : draw_resolution_scale_x_;
  }
  uint32_t GetCurrentDrawResolutionScaleY() const {
    return IsCurrentDrawScaleNative() ? 1 : draw_resolution_scale_y_;
  }

  bool IsGuestPixelCenterFetchNeeded() const;

  bool edram_fragment_shader_interlock_;

  bool precise_interpolation_;

  bool zpd_full_counters_;

  bool is_depth_only_fragment_shader_ = false;
  bool is_viz_survey_fragment_shader_ = false;

  std::unique_ptr<SpirvBuilder> builder_;

  std::vector<spv::Id> id_vector_temp_;

  std::vector<spv::Id> id_vector_temp_util_;
  std::vector<unsigned int> uint_vector_temp_;
  std::vector<unsigned int> uint_vector_temp_util_;

  spv::Id ext_inst_glsl_std_450_;

  spv::Id type_void_;

  union {
    struct {
      spv::Id type_bool_;
      spv::Id type_bool2_;
      spv::Id type_bool3_;
      spv::Id type_bool4_;
    };

    spv::Id type_bool_vectors_[4];
  };
  union {
    struct {
      spv::Id type_int_;
      spv::Id type_int2_;
      spv::Id type_int3_;
      spv::Id type_int4_;
    };
    spv::Id type_int_vectors_[4];
  };
  union {
    struct {
      spv::Id type_uint_;
      spv::Id type_uint2_;
      spv::Id type_uint3_;
      spv::Id type_uint4_;
    };
    spv::Id type_uint_vectors_[4];
  };
  union {
    struct {
      spv::Id type_float_;
      spv::Id type_float2_;
      spv::Id type_float3_;
      spv::Id type_float4_;
    };
    spv::Id type_float_vectors_[4];
  };

  spv::Id const_int_0_;
  spv::Id const_int4_0_;
  spv::Id const_uint_0_;
  spv::Id const_uint4_0_;
  union {
    struct {
      spv::Id const_float_0_;
      spv::Id const_float2_0_;
      spv::Id const_float3_0_;
      spv::Id const_float4_0_;
    };
    spv::Id const_float_vectors_0_[4];
  };
  union {
    struct {
      spv::Id const_float_1_;
      spv::Id const_float2_1_;
      spv::Id const_float3_1_;
      spv::Id const_float4_1_;
    };
    spv::Id const_float_vectors_1_[4];
  };

  spv::Id const_float2_0_1_;

  enum SystemConstantIndex : unsigned int {
    kSystemConstantFlags,
    kSystemConstantVertexIndexLoadAddress,
    kSystemConstantVertexIndexCount,
    kSystemConstantVertexIndexEndian,
    kSystemConstantVertexBaseIndex,
    kSystemConstantNdcScale,
    kSystemConstantPointVertexDiameterMin,
    kSystemConstantNdcOffset,
    kSystemConstantPointVertexDiameterMax,
    kSystemConstantPointConstantDiameter,
    kSystemConstantPointScreenDiameterToNdcRadius,
    kSystemConstantTextureSwizzledSigns,
    kSystemConstantTextureSwizzles,
    kSystemConstantTexturesResolved,
    kSystemConstantAlphaTestReference,
    kSystemConstantAlphaToMask,
    kSystemConstantZpdFsiCounterIndex,
    kSystemConstantEdram32bppTilePitchDwordsScaled,
    kSystemConstantEdramDepthBaseDwordsScaled,
    kSystemConstantColorExpBias,
    kSystemConstantEdramPolyOffsetFrontScale,
    kSystemConstantEdramPolyOffsetBackScale,
    kSystemConstantEdramPolyOffsetFrontOffset,
    kSystemConstantEdramPolyOffsetBackOffset,
    kSystemConstantEdramStencilFront,
    kSystemConstantEdramStencilBack,
    kSystemConstantEdramRTBaseDwordsScaled,
    kSystemConstantEdramRTBlendFactorsOps,

    kSystemConstantEdramRTKeepMask,
    kSystemConstantEdramRTClamp,
    kSystemConstantEdramBlendConstant,
    kSystemConstantUserClipPlanes,
    kSystemConstantTessellationFactorRange,
    kSystemConstantTessellationVertexIndexEndian,
    kSystemConstantTessellationVertexIndexOffset,
    kSystemConstantTessellationVertexIndexMinMax,
    kSystemConstantInterpreterUcodeBaseDwords,
    kSystemConstantInterpreterCfInstrCount,
    kSystemConstantTextureIntegerScaleBits,
  };
  spv::Id uniform_system_constants_;
  spv::Id uniform_float_constants_;
  spv::Id uniform_bool_loop_constants_;
  spv::Id uniform_fetch_constants_;

  spv::Id buffers_shared_memory_;
  spv::Id buffer_edram_;
  spv::Id buffer_zpd_counter_;

  std::vector<TextureBinding> texture_bindings_;
  std::vector<SamplerBinding> sampler_bindings_;

  spv::Id input_vertex_index_;

  spv::Id input_control_point_index_;

  spv::Id input_tess_coord_;

  spv::Id input_point_coordinates_;

  spv::Id input_fragment_coordinates_;

  spv::Id input_front_facing_;

  spv::Id input_sample_mask_;

  spv::Id input_barycentric_coord_;
  spv::Id input_barycentric_coord_no_persp_;

  std::array<spv::Id, xenos::kMaxInterpolators> input_interpolators_per_vertex_;

  std::array<spv::Id, xenos::kMaxInterpolators> input_output_interpolators_;

  spv::Id output_point_coordinates_;

  spv::Id output_point_size_;

  enum OutputPerVertexMember : unsigned int {
    kOutputPerVertexMemberPosition,
    kOutputPerVertexMemberCount,
  };
  spv::Id output_per_vertex_;
  unsigned int output_per_vertex_clip_distance_member_index_ = 0;
  unsigned int output_per_vertex_cull_distance_member_index_ = 0;

  bool main_vertex_rect_list_as_triangle_strip_ = false;

  spv::Id var_main_rect_list_strip_vertex_;

  spv::Id var_main_rect_list_guest_vertex_indices_;

  spv::Id var_main_rect_list_guest_positions_;

  std::array<spv::Id, xenos::kMaxInterpolators> var_main_rect_list_guest_interpolators_;

  std::array<spv::Id, xenos::kMaxColorRenderTargets> output_or_var_fragment_data_;

  std::array<spv::Id, xenos::kMaxColorRenderTargets> output_fragment_data_;

  spv::Id output_or_var_fragment_depth_;

  spv::Id output_fragment_depth_;

  spv::Id main_fbo_depth_unbiased_;
  std::array<spv::Id, 2> main_fbo_depth_derivatives_;

  spv::Id output_fragment_sample_mask_;

  std::vector<spv::Id> main_interface_;
  spv::Function* function_main_;
  spv::Id main_system_constant_flags_;

  spv::Id var_main_predicate_;

  spv::Id var_main_loop_count_;

  spv::Id var_main_loop_address_;

  spv::Id var_main_address_register_;

  spv::Id var_main_previous_scalar_;

  spv::Id var_main_vfetch_address_;

  spv::Id var_main_vfetch_bound_;

  spv::Id var_main_tfetch_lod_;

  spv::Id var_main_tfetch_gradients_h_;
  spv::Id var_main_tfetch_gradients_v_;

  spv::Id var_main_registers_;

  uint64_t main_interpolators_unmodified_;

  std::array<spv::Id, xenos::kMaxInterpolators> var_main_interpolator_guest_center_deltas_;

  bool BisectTargetsCurrentShader() const;
  bool BisectSkipsInstruction();
  void BisectSnapshotAfterInstruction();
  void BisectStoreSnapshot();
  void BisectOverrideColorOutput();
  uint32_t bisect_instruction_index_;
  uint32_t bisect_current_instruction_;
  bool bisect_snapshot_emitted_;

  spv::Id var_main_bisect_snapshot_;

  spv::Id var_main_memexport_address_;

  spv::Id var_main_memexport_data_[ucode::kMaxMemExportElementCount];

  spv::Id var_main_memexport_data_written_;

  spv::Id main_memexport_allowed_;

  spv::Id var_main_point_size_edge_flag_kill_vertex_;

  spv::Id var_main_kill_pixel_;

  spv::Id var_main_fsi_color_written_;

  spv::Id var_main_zpd_coverage_;

  spv::Id main_fsi_sample_mask_;

  spv::Id main_fsi_z_fail_sample_mask_;
  spv::Id main_fsi_stencil_fail_sample_mask_;

  spv::Id main_fsi_address_depth_;

  spv::Id main_fsi_offset_32bpp_;
  spv::Id main_fsi_offset_64bpp_;

  std::array<spv::Id, 4> main_fsi_late_write_depth_stencil_;
  spv::Block* main_fsi_early_depth_stencil_execute_quad_merge_;
  spv::Block* main_loop_header_;
  spv::Block* main_loop_continue_;
  spv::Block* main_loop_merge_;
  spv::Id main_loop_pc_next_;

  spv::Block* main_rect_list_loop_header_;
  spv::Block* main_rect_list_loop_continue_;
  spv::Block* main_rect_list_loop_merge_;

  spv::Id main_rect_list_loop_vertex_index_;

  spv::Id main_rect_list_loop_vertex_index_next_;
  spv::Block* main_switch_header_;
  std::unique_ptr<spv::Instruction> main_switch_op_;
  spv::Block* main_switch_merge_;
  std::vector<spv::Id> main_switch_next_pc_phi_operands_;

  spv::Block* cf_exec_conditional_merge_;

  spv::Block* cf_instruction_predicate_merge_;

  uint32_t cf_exec_bool_constant_or_predicate_;
  static constexpr uint32_t kCfExecBoolConstantPredicate = UINT32_MAX;

  bool cf_exec_condition_;

  bool cf_instruction_predicate_condition_;

  bool cf_exec_predicate_written_;
};

}

#endif
