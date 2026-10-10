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

#pragma once

#include <cstddef>
#include <optional>
#include <cstring>
#include <string>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/format/dxbc.h>
#include <rex/graphics/format/ucode.h>
#include <rex/graphics/pipeline/shader/translator.h>
#include <rex/math.h>
#include <rex/string/buffer.h>
#include <rex/ui/graphics_provider.h>

namespace rex::graphics {

class DxbcShaderTranslator : public ShaderTranslator {
 public:
  DxbcShaderTranslator(ui::GraphicsProvider::GpuVendorID vendor_id, bool bindless_resources_used,
                       bool edram_rov_used, bool gamma_render_target_as_unorm8 = false,
                       bool msaa_2x_supported = true, uint32_t draw_resolution_scale_x = 1,
                       uint32_t draw_resolution_scale_y = 1, bool force_emit_source_map = false);
  ~DxbcShaderTranslator() override;

  union Modification {
    static constexpr uint32_t kVersion = 0x20261008;

    enum class DepthStencilMode : uint32_t {
      kNoModifiers,

      kEarlyHint,

      kFloat24Truncating,

      kFloat24Rounding,
    };

    uint64_t value;
    struct VertexShaderModification {
      uint32_t interpolator_mask : xenos::kMaxInterpolators;
      uint32_t user_clip_plane_count : 3;
      uint32_t user_clip_plane_cull : 1;

      uint32_t vertex_kill_and : 1;
      uint32_t output_point_size : 1;

      uint32_t dynamic_addressable_register_count : 8;

      uint32_t point_ps_ucp_mode : 2;

      Shader::HostVertexShaderType host_vertex_shader_type : Shader::kHostVertexShaderTypeBitCount;
    } vertex;
    struct PixelShaderModification {
      uint32_t interpolator_mask : xenos::kMaxInterpolators;
      uint32_t interpolators_centroid : xenos::kMaxInterpolators;

      uint32_t param_gen_enable : 1;
      uint32_t param_gen_interpolator : 4;

      uint32_t param_gen_point : 1;
      uint32_t dynamic_addressable_register_count : 8;

      DepthStencilMode depth_stencil_mode : 2;

      uint32_t zpd_total : 1;
    } pixel;

    explicit Modification(uint64_t modification_value = 0) : value(modification_value) {
      static_assert_size(*this, sizeof(value));
    }

    uint32_t GetVertexClipDistanceCount() const {
      return vertex.user_clip_plane_cull ? 0 : vertex.user_clip_plane_count;
    }
    uint32_t GetVertexCullDistanceCount() const {
      return (vertex.user_clip_plane_cull ? vertex.user_clip_plane_count : 0) +
             vertex.vertex_kill_and;
    }
  };

  enum class CbufferRegister {
    kSystemConstants,
    kFloatConstants,
    kBoolLoopConstants,
    kFetchConstants,
    kDescriptorIndices,
  };

  enum : uint32_t {
    kSysFlag_SharedMemoryIsUAV_Shift,
    kSysFlag_XYDividedByW_Shift,
    kSysFlag_ZDividedByW_Shift,
    kSysFlag_WNotReciprocal_Shift,
    kSysFlag_PrimitivePolygonal_Shift,
    kSysFlag_PrimitiveLine_Shift,
    kSysFlag_DepthFloat24_Shift,
    kSysFlag_AlphaPassIfLess_Shift,
    kSysFlag_AlphaPassIfEqual_Shift,
    kSysFlag_AlphaPassIfGreater_Shift,
    kSysFlag_ConvertColor0ToGamma_Shift,
    kSysFlag_ConvertColor1ToGamma_Shift,
    kSysFlag_ConvertColor2ToGamma_Shift,
    kSysFlag_ConvertColor3ToGamma_Shift,

    kSysFlag_ROVDepthStencil_Shift,
    kSysFlag_ROVDepthPassIfLess_Shift,
    kSysFlag_ROVDepthPassIfEqual_Shift,
    kSysFlag_ROVDepthPassIfGreater_Shift,

    kSysFlag_ROVDepthWrite_Shift,
    kSysFlag_ROVStencilTest_Shift,

    kSysFlag_ROVDepthStencilEarlyWrite_Shift,

    kSysFlag_Count,

    kSysFlag_SharedMemoryIsUAV = 1u << kSysFlag_SharedMemoryIsUAV_Shift,
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
    kSysFlag_ROVDepthStencil = 1u << kSysFlag_ROVDepthStencil_Shift,
    kSysFlag_ROVDepthPassIfLess = 1u << kSysFlag_ROVDepthPassIfLess_Shift,
    kSysFlag_ROVDepthPassIfEqual = 1u << kSysFlag_ROVDepthPassIfEqual_Shift,
    kSysFlag_ROVDepthPassIfGreater = 1u << kSysFlag_ROVDepthPassIfGreater_Shift,
    kSysFlag_ROVDepthWrite = 1u << kSysFlag_ROVDepthWrite_Shift,
    kSysFlag_ROVStencilTest = 1u << kSysFlag_ROVStencilTest_Shift,
    kSysFlag_ROVDepthStencilEarlyWrite = 1u << kSysFlag_ROVDepthStencilEarlyWrite_Shift,
  };
  static_assert(kSysFlag_Count <= 32, "Too many flags in the system constants");

  struct SystemConstants {
    uint32_t flags;
    union {
      struct {
        float tessellation_factor_range_min;
        float tessellation_factor_range_max;
      };
      float tessellation_factor_range[2];
    };
    uint32_t line_loop_closing_index;

    xenos::Endian vertex_index_endian;
    uint32_t vertex_index_offset;
    union {
      struct {
        uint32_t vertex_index_min;
        uint32_t vertex_index_max;
      };
      uint32_t vertex_index_min_max[2];
    };

    float user_clip_planes[6][4];

    float ndc_scale[3];
    float point_vertex_diameter_min;

    float ndc_offset[3];
    float point_vertex_diameter_max;

    float point_constant_diameter[2];

    float point_screen_diameter_to_ndc_radius[2];

    uint32_t texture_swizzled_signs[8];

    uint32_t textures_resolution_scaled;

    uint32_t sample_count_log2[2];
    float alpha_test_reference;

    uint32_t alpha_to_mask;
    uint32_t edram_32bpp_tile_pitch_dwords_scaled;
    uint32_t edram_depth_base_dwords_scaled;

    uint32_t zpd_counter_index;

    float color_exp_bias[4];

    union {
      struct {
        float edram_poly_offset_front_scale;
        float edram_poly_offset_front_offset;
      };
      float edram_poly_offset_front[2];
    };
    union {
      struct {
        float edram_poly_offset_back_scale;
        float edram_poly_offset_back_offset;
      };
      float edram_poly_offset_back[2];
    };

    union {
      struct {
        uint32_t edram_stencil_front_reference;
        uint32_t edram_stencil_front_read_mask;
        uint32_t edram_stencil_front_write_mask;
        uint32_t edram_stencil_front_func_ops;

        uint32_t edram_stencil_back_reference;
        uint32_t edram_stencil_back_read_mask;
        uint32_t edram_stencil_back_write_mask;
        uint32_t edram_stencil_back_func_ops;
      };
      struct {
        uint32_t edram_stencil_front[4];
        uint32_t edram_stencil_back[4];
      };
      uint32_t edram_stencil[2][4];
    };

    uint32_t edram_rt_base_dwords_scaled[4];

    uint32_t edram_rt_format_flags[4];

    float edram_rt_clamp[4][4];

    uint32_t edram_rt_keep_mask[4][2];

    uint32_t edram_rt_blend_factors_ops[4];

    float edram_blend_constant[4];

    uint32_t texture_integer_scale_bits[32];

   private:
    friend class DxbcShaderTranslator;

    enum class Index : uint32_t {
      kFlags,
      kTessellationFactorRange,
      kLineLoopClosingIndex,

      kVertexIndexEndian,
      kVertexIndexOffset,
      kVertexIndexMinMax,

      kUserClipPlanes,

      kNDCScale,
      kPointVertexDiameterMin,

      kNDCOffset,
      kPointVertexDiameterMax,

      kPointConstantDiameter,
      kPointScreenDiameterToNDCRadius,

      kTextureSwizzledSigns,

      kTexturesResolutionScaled,
      kSampleCountLog2,
      kAlphaTestReference,

      kAlphaToMask,
      kEdram32bppTilePitchDwordsScaled,
      kEdramDepthBaseDwordsScaled,
      kZpdCounterIndex,

      kColorExpBias,

      kEdramPolyOffsetFront,
      kEdramPolyOffsetBack,

      kEdramStencil,

      kEdramRTBaseDwordsScaled,

      kEdramRTFormatFlags,

      kEdramRTClamp,

      kEdramRTKeepMask,

      kEdramRTBlendFactorsOps,

      kEdramBlendConstant,

      kTextureIntegerScaleBits,

      kCount,
    };
    static_assert(uint32_t(Index::kCount) <= 64,
                  "Too many system constants, can't use uint64_t for usage bits");
  };

  enum class SRVSpace {

    kMain,
    kBindlessTextures2DArray,
    kBindlessTextures3D,
    kBindlessTexturesCube,
  };

  enum class SRVMainRegister {
    kSharedMemory,
    kBindfulTexturesStart,
  };

  static constexpr uint32_t kMaxTextureBindingIndexBits = 8;
  static constexpr uint32_t kMaxTextureBindings = (1 << kMaxTextureBindingIndexBits) - 1;
  struct TextureBinding {
    uint32_t bindful_srv_index;

    uint32_t bindful_srv_rdef_name_ptr;
    uint32_t bindless_descriptor_index;
    uint32_t fetch_constant;

    xenos::FetchOpDimension dimension;
    bool is_signed;
    std::string bindful_name;
  };

  static constexpr uint32_t kMaxSamplerBindingIndexBits = 7;
  static constexpr uint32_t kMaxSamplerBindings = (1 << kMaxSamplerBindingIndexBits) - 1;
  struct SamplerBinding {
    uint32_t bindless_descriptor_index;
    uint32_t fetch_constant;
    xenos::TextureFilter mag_filter;
    xenos::TextureFilter min_filter;
    xenos::TextureFilter mip_filter;
    xenos::AnisoFilter aniso_filter;
    uint32_t border_color_forced;
    xenos::BorderColor forced_border_color;
    std::string bindful_name;
  };

  enum class UAVRegister {
    kSharedMemory,
    kEdram,
    kZpdCounter,
  };

  uint64_t GetDefaultVertexShaderModification(
      uint32_t dynamic_addressable_register_count,
      Shader::HostVertexShaderType host_vertex_shader_type =
          Shader::HostVertexShaderType::kVertex) const override;
  uint64_t GetDefaultPixelShaderModification(
      uint32_t dynamic_addressable_register_count) const override;

  std::vector<uint8_t> CreateDepthOnlyPixelShader(
      bool zpd_total = false,
      Modification::DepthStencilMode depth_stencil_mode =
          Modification::DepthStencilMode::kNoModifiers,
      bool viz_survey = false);

  static void PreClampedFloat32To7e3(dxbc::Assembler& a, uint32_t f10_temp,
                                     uint32_t f10_temp_component, uint32_t f32_temp,
                                     uint32_t f32_temp_component, uint32_t temp_temp,
                                     uint32_t temp_temp_component);

  static void UnclampedFloat32To7e3(dxbc::Assembler& a, uint32_t f10_temp,
                                    uint32_t f10_temp_component, uint32_t f32_temp,
                                    uint32_t f32_temp_component, uint32_t temp_temp,
                                    uint32_t temp_temp_component);

  static void Float7e3To32(dxbc::Assembler& a, const dxbc::Dest& f32, uint32_t f10_temp,
                           uint32_t f10_temp_component, uint32_t f10_shift, uint32_t temp1_temp,
                           uint32_t temp1_temp_component, uint32_t temp2_temp,
                           uint32_t temp2_temp_component);

  static void PreClampedDepthTo20e4(dxbc::Assembler& a, uint32_t f24_temp,
                                    uint32_t f24_temp_component, uint32_t f32_temp,
                                    uint32_t f32_temp_component, uint32_t temp_temp,
                                    uint32_t temp_temp_component, bool round_to_nearest_even,
                                    bool remap_from_0_to_0_5);

  static void Depth20e4To32(dxbc::Assembler& a, const dxbc::Dest& f32, uint32_t f24_temp,
                            uint32_t f24_temp_component, uint32_t f24_shift, uint32_t temp1_temp,
                            uint32_t temp1_temp_component, uint32_t temp2_temp,
                            uint32_t temp2_temp_component, bool remap_to_0_to_0_5);

  static void PWLGammaToLinear(dxbc::Assembler& a, uint32_t target_temp,
                               uint32_t target_temp_component, uint32_t source_temp,
                               uint32_t source_temp_component, bool source_pre_saturated,
                               uint32_t temp1, uint32_t temp1_component, uint32_t temp2,
                               uint32_t temp2_component);

  static void PreSaturatedLinearToPWLGamma(dxbc::Assembler& a, uint32_t target_temp,
                                           uint32_t target_temp_component, uint32_t source_temp,
                                           uint32_t source_temp_component, uint32_t temp_or_target,
                                           uint32_t temp_or_target_component,
                                           uint32_t temp_non_target,
                                           uint32_t temp_non_target_component);

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
  void EmitWide1DTextureCoordinates(const ParsedTextureFetchInstruction& instr,
                                    const dxbc::Src& coord_operand, float offset_x,
                                    uint32_t tfetch_index, uint32_t coord_temp,
                                    uint32_t width_minus_1_temp, bool promoted_1d);
  void ProcessAluInstruction(const ParsedAluInstruction& instr,
                             uint8_t memexport_eM_potentially_written_before) override;

 private:
  static constexpr uint32_t kInRegisterVSVertexIndex = 0;
  static constexpr uint32_t kInRegisterDSControlPointIndex = 0;

  void MarkSystemConstantUsed(SystemConstants::Index index) {
    system_constants_used_ |= uint64_t(1) << uint32_t(index);
  }

  dxbc::Src GetSystemConstantSrc(size_t offset, uint32_t swizzle) const {
    uint32_t first_component = uint32_t((offset >> 2) & 3);
    return dxbc::Src::CB(cbuffer_index_system_constants_,
                         uint32_t(CbufferRegister::kSystemConstants), uint32_t(offset >> 4),
                         std::min((swizzle & 3) + first_component, uint32_t(3)) |
                             std::min(((swizzle >> 2) & 3) + first_component, uint32_t(3)) << 2 |
                             std::min(((swizzle >> 4) & 3) + first_component, uint32_t(3)) << 4 |
                             std::min(((swizzle >> 6) & 3) + first_component, uint32_t(3)) << 6);
  }
  dxbc::Src LoadSystemConstant(SystemConstants::Index index, size_t offset, uint32_t swizzle) {
    MarkSystemConstantUsed(index);
    return GetSystemConstantSrc(offset, swizzle);
  }
  dxbc::Src LoadFlagsSystemConstant() {
    return LoadSystemConstant(SystemConstants::Index::kFlags, offsetof(SystemConstants, flags),
                              dxbc::Src::kXXXX);
  }

  Modification GetDxbcShaderModification() const {
    return Modification(current_translation().modification());
  }

  bool IsDxbcVertexShader() const {
    return is_vertex_shader() && !Shader::IsHostVertexShaderTypeDomain(
                                     GetDxbcShaderModification().vertex.host_vertex_shader_type);
  }
  bool IsDxbcDomainShader() const {
    return is_vertex_shader() && Shader::IsHostVertexShaderTypeDomain(
                                     GetDxbcShaderModification().vertex.host_vertex_shader_type);
  }

  bool IsForceEarlyDepthStencilGlobalFlagEnabled() const {
    return is_pixel_shader() &&
           GetDxbcShaderModification().pixel.depth_stencil_mode ==
               Modification::DepthStencilMode::kEarlyHint &&
           !GetDxbcShaderModification().pixel.zpd_total && !edram_rov_used_ &&
           current_shader().implicit_early_z_write_allowed();
  }

  uint32_t GetModificationInterpolatorMask() const {
    Modification modification = GetDxbcShaderModification();
    return is_vertex_shader() ? modification.vertex.interpolator_mask
                              : modification.pixel.interpolator_mask;
  }

  bool UseSwitchForControlFlow() const;

  uint32_t PushSystemTemp(uint32_t zero_mask = 0, uint32_t count = 1);

  void PopSystemTemp(uint32_t count = 1);

  void ExportToMemory(uint8_t export_eM);

  bool IsSampleRate() const {
    assert_true(is_pixel_shader());
    return DSV_IsWritingFloat24Depth() && !current_shader().writes_depth();
  }
  bool IsDepthStencilSystemTempUsed() const {
    if (edram_rov_used_) {
      return true;
    }
    if (current_shader().writes_depth()) {
      return true;
    }
    return false;
  }

  bool DSV_IsWritingFloat24Depth() const {
    if (edram_rov_used_) {
      return false;
    }
    Modification::DepthStencilMode depth_stencil_mode =
        GetDxbcShaderModification().pixel.depth_stencil_mode;
    return depth_stencil_mode == Modification::DepthStencilMode::kFloat24Truncating ||
           depth_stencil_mode == Modification::DepthStencilMode::kFloat24Rounding;
  }

  bool ROV_IsDepthStencilEarly() const {
    assert_true(edram_rov_used_);
    return !is_depth_only_pixel_shader_ && !current_shader().writes_depth() &&
           !current_shader().memexport_eM_written();
  }

  void ROV_DepthTo24Bit(uint32_t d24_temp, uint32_t d24_temp_component, uint32_t d32_temp,
                        uint32_t d32_temp_component, uint32_t temp_temp,
                        uint32_t temp_temp_component);

  void ROV_DepthStencilTest();

  void ROV_AddMSAASamplesToZPD(bool count_passed, bool count_failed);

  void RTV_AddMSAASamplesToZPDTotal(dxbc::Src coverage_src);

  void ROV_UnpackColor(uint32_t rt_index, uint32_t packed_temp, uint32_t packed_temp_components,
                       uint32_t color_temp, uint32_t temp1, uint32_t temp1_component,
                       uint32_t temp2, uint32_t temp2_component);

  void ROV_PackPreClampedColor(uint32_t rt_index, uint32_t color_temp, uint32_t packed_temp,
                               uint32_t packed_temp_components, uint32_t temp1,
                               uint32_t temp1_component, uint32_t temp2, uint32_t temp2_component);

  void ROV_HandleColorBlendFactorCases(uint32_t src_temp, uint32_t dst_temp, uint32_t factor_temp);

  void ROV_HandleAlphaBlendFactorCases(uint32_t src_temp, uint32_t dst_temp, uint32_t factor_temp,
                                       uint32_t factor_component);

  void RemapAndConvertVertexIndices(uint32_t dest_temp, uint32_t dest_temp_components,
                                    const dxbc::Src& src);
  void StartVertexShader_LoadVertexIndex();
  void StartVertexOrDomainShader();
  void StartDomainShader();
  void StartPixelShader_LoadROVParameters();
  void StartPixelShader();

  void CompleteVertexOrDomainShader();

  void CompletePixelShader_AlphaToMaskSample(bool initialize, uint32_t sample_index,
                                             float threshold_base, dxbc::Src threshold_offset,
                                             float threshold_offset_scale, uint32_t coverage_temp,
                                             uint32_t coverage_temp_component, uint32_t temp,
                                             uint32_t temp_component);

  void CompletePixelShader_AlphaToMask(uint32_t zpd_coverage_temp = UINT32_MAX);
  void CompletePixelShader_WriteToRTVs();
  void CompletePixelShader_DSV_DepthTo24Bit();
  void CompletePixelShader_WriteToROV();
  void CompletePixelShader();

  void CompleteShaderCode();

  void EmitInstructionDisassembly();

  dxbc::Src LoadOperand(const InstructionOperand& operand, uint32_t needed_components,
                        bool& temp_pushed_out);

  void StoreResult(const InstructionResult& result, const dxbc::Src& src,
                   bool can_store_memexport_address = false);

  void UpdateExecConditionalsAndEmitDisassembly(ParsedExecInstruction::Type type,
                                                uint32_t bool_constant_index, bool condition);

  void CloseExecConditionals();

  void UpdateInstructionPredicationAndEmitDisassembly(bool predicated, bool condition);

  void CloseInstructionPredication();
  void JumpToLabel(uint32_t address);

  uint32_t FindOrAddTextureBinding(uint32_t fetch_constant, xenos::FetchOpDimension dimension,
                                   bool is_signed);
  uint32_t FindOrAddSamplerBinding(
      uint32_t fetch_constant, xenos::TextureFilter mag_filter, xenos::TextureFilter min_filter,
      xenos::TextureFilter mip_filter, xenos::AnisoFilter aniso_filter,
      std::optional<xenos::BorderColor> forced_border_color = std::nullopt);

  uint32_t GetBindlessResourceCount() const {
    return uint32_t(texture_bindings_.size() + sampler_bindings_.size());
  }

  dxbc::Src RequestTextureFetchConstantWordPair(uint32_t fetch_constant_index,
                                                uint32_t pair_index) {
    if (cbuffer_index_fetch_constants_ == kBindingIndexUnallocated) {
      cbuffer_index_fetch_constants_ = cbuffer_count_++;
    }
    uint32_t total_pair_index = fetch_constant_index * 3 + pair_index;
    return dxbc::Src::CB(cbuffer_index_fetch_constants_, uint32_t(CbufferRegister::kFetchConstants),
                         total_pair_index >> 1, (total_pair_index & 1) ? 0b10101110 : 0b00000100);
  }
  dxbc::Src RequestTextureFetchConstantWord(uint32_t fetch_constant_index, uint32_t word_index) {
    return RequestTextureFetchConstantWordPair(fetch_constant_index, word_index >> 1)
        .SelectFromSwizzled(word_index & 1);
  }

  void KillPixel(bool condition, const dxbc::Src& condition_src,
                 uint8_t memexport_eM_potentially_written_before);

  void ProcessVectorAluOperation(const ParsedAluInstruction& instr,
                                 uint8_t memexport_eM_potentially_written_before,
                                 uint32_t& result_swizzle, bool& predicate_written);

  void ReduceFloatPrecision(const dxbc::Dest& dest, const dxbc::Src& value, uint32_t mantissa_bits);

  void EmitScalarReciprocal(const dxbc::Dest& dest, const dxbc::Src& dest_src,
                            const dxbc::Src& operand, bool square_root);
  void ProcessScalarAluOperation(const ParsedAluInstruction& instr,
                                 uint8_t memexport_eM_potentially_written_before,
                                 bool& predicate_written);

  void WriteResourceDefinition();
  void WriteInputSignature();
  void WritePatchConstantSignature();
  void WriteOutputSignature();
  void WriteShaderCode();

  std::vector<uint32_t> shader_code_;

  std::vector<uint32_t> shader_object_;

  dxbc::ShaderFeatureInfo shader_feature_info_;

  dxbc::Statistics statistics_;

  dxbc::Assembler a_;

  dxbc::Assembler ao_;

  string::StringBuffer instruction_disassembly_buffer_;

  bool emit_source_map_;

  ui::GraphicsProvider::GpuVendorID vendor_id_;

  bool bindless_resources_used_;

  bool edram_rov_used_;

  bool zpd_full_counters_;

  bool gamma_render_target_as_unorm8_;

  bool msaa_2x_supported_;

  uint32_t draw_resolution_scale_x_;
  uint32_t draw_resolution_scale_y_;

  bool is_depth_only_pixel_shader_ = false;
  bool is_viz_survey_pixel_shader_ = false;

  enum class ShaderRdefTypeIndex {
    kFloat,
    kFloat2,
    kFloat3,
    kFloat4,
    kUint,
    kUint2,
    kUint4,

    kFloat4Array4,

    kFloat4Array6,

    kFloat4ConstantArray,

    kUint4Array2,

    kUint4Array8,

    kUint4Array48,

    kUint4DescriptorIndexArray,

    kCount,
    kUnknown = kCount
  };

  struct ShaderRdefType {
    const char* name;
    dxbc::RdefVariableClass variable_class;
    dxbc::RdefVariableType variable_type;
    uint16_t row_count;
    uint16_t column_count;
    uint16_t element_count;
    ShaderRdefTypeIndex array_element_type;
  };
  static const ShaderRdefType rdef_types_[size_t(ShaderRdefTypeIndex::kCount)];

  static constexpr uint32_t kBindingIndexUnallocated = UINT32_MAX;

  uint32_t cbuffer_count_;
  uint32_t cbuffer_index_system_constants_;
  uint32_t cbuffer_index_float_constants_;
  uint32_t cbuffer_index_bool_loop_constants_;
  uint32_t cbuffer_index_fetch_constants_;
  uint32_t cbuffer_index_descriptor_indices_;

  struct SystemConstantRdef {
    const char* name;
    ShaderRdefTypeIndex type;
    uint32_t size;
    uint32_t padding_after;
  };
  static const SystemConstantRdef system_constant_rdef_[size_t(SystemConstants::Index::kCount)];

  uint64_t system_constants_used_;

  uint32_t out_reg_vs_interpolators_;
  uint32_t out_reg_vs_position_;

  uint32_t out_reg_vs_clip_cull_distances_;
  uint32_t out_reg_vs_point_size_;
  uint32_t in_reg_ps_interpolators_;
  uint32_t in_reg_ps_point_coordinates_;
  uint32_t in_reg_ps_position_;

  uint32_t in_reg_ps_front_face_sample_index_;

  uint32_t in_domain_location_used_;

  bool in_control_point_index_used_;

  uint32_t in_position_used_;

  bool in_front_face_used_;

  uint32_t system_temp_count_current_;

  uint32_t system_temp_count_max_;

  uint32_t system_temp_position_;

  uint32_t system_temp_point_size_edge_flag_kill_vertex_;

  uint32_t system_temp_rov_params_;

  uint32_t system_temp_depth_stencil_;

  uint32_t system_temps_color_[4];

  uint32_t system_temp_memexport_enabled_and_eM_written_;

  uint32_t system_temp_memexport_address_;

  uint32_t system_temps_memexport_data_[ucode::kMaxMemExportElementCount];

  uint32_t system_temp_result_;

  uint32_t system_temp_ps_pc_p0_a0_;

  uint32_t system_temp_aL_;

  uint32_t system_temp_loop_count_;

  uint32_t system_temp_grad_h_lod_;

  uint32_t system_temp_grad_v_vfetch_address_;

  uint32_t cf_exec_bool_constant_;
  static constexpr uint32_t kCfExecBoolConstantNone = UINT32_MAX;

  bool cf_exec_bool_constant_condition_;

  bool cf_exec_predicated_;

  bool cf_exec_predicate_condition_;

  bool cf_instruction_predicate_if_open_;

  bool cf_instruction_predicate_condition_;

  bool cf_exec_predicate_written_;

  uint32_t srv_count_;
  uint32_t srv_index_shared_memory_;
  uint32_t srv_index_bindless_textures_2d_;
  uint32_t srv_index_bindless_textures_3d_;
  uint32_t srv_index_bindless_textures_cube_;

  std::vector<TextureBinding> texture_bindings_;
  std::unordered_map<uint32_t, uint32_t> texture_bindings_for_bindful_srv_indices_;

  uint32_t uav_count_;
  uint32_t uav_index_shared_memory_;
  uint32_t uav_index_edram_;
  uint32_t uav_index_zpd_counter_;

  std::vector<SamplerBinding> sampler_bindings_;
};

}
