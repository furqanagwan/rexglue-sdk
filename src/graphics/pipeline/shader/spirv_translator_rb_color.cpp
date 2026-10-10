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

spv::Id SpirvShaderTranslator::PackFloat16x2ExtendedRange(spv::Id float2_value) {
  float2_value = builder_->createTriOp(
      spv::OpSelect, type_float2_, builder_->createUnaryOp(spv::OpIsNan, type_bool2_, float2_value),
      const_float2_0_, float2_value);

  spv::Id standard = builder_->createUnaryBuiltinCall(type_uint_, ext_inst_glsl_std_450_,
                                                      GLSLstd450PackHalf2x16, float2_value);
  spv::Id const_0x7C00 = builder_->makeUintConstant(0x7C00);
  spv::Id lower_overflow = builder_->createBinOp(
      spv::OpIEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, standard, const_0x7C00), const_0x7C00);
  spv::Id upper_overflow = builder_->createBinOp(
      spv::OpIEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                            builder_->createBinOp(spv::OpShiftRightLogical, type_uint_, standard,
                                                  builder_->makeUintConstant(16)),
                            const_0x7C00),
      const_0x7C00);
  id_vector_temp_.clear();
  id_vector_temp_.resize(2, builder_->makeFloatConstant(-131008.0f));
  spv::Id const_neg_131008 = builder_->makeCompositeConstant(type_float2_, id_vector_temp_);
  id_vector_temp_.clear();
  id_vector_temp_.resize(2, builder_->makeFloatConstant(131008.0f));
  spv::Id const_131008 = builder_->makeCompositeConstant(type_float2_, id_vector_temp_);
  spv::Id clamped =
      builder_->createTriBuiltinCall(type_float2_, ext_inst_glsl_std_450_, GLSLstd450FClamp,
                                     float2_value, const_neg_131008, const_131008);
  id_vector_temp_.clear();
  id_vector_temp_.resize(2, builder_->makeFloatConstant(0.5f));
  spv::Id halved =
      builder_->createBinOp(spv::OpFMul, type_float2_, clamped,
                            builder_->makeCompositeConstant(type_float2_, id_vector_temp_));
  spv::Id halved_packed = builder_->createUnaryBuiltinCall(type_uint_, ext_inst_glsl_std_450_,
                                                           GLSLstd450PackHalf2x16, halved);

  spv::Id extended = builder_->createBinOp(spv::OpIAdd, type_uint_, halved_packed,
                                           builder_->makeUintConstant(0x04000400));
  spv::Id const_0xFFFF = builder_->makeUintConstant(0xFFFF);
  spv::Id const_0xFFFF0000 = builder_->makeUintConstant(0xFFFF0000);
  spv::Id result_lower = builder_->createTriOp(
      spv::OpSelect, type_uint_, lower_overflow,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, extended, const_0xFFFF),
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, standard, const_0xFFFF));
  spv::Id result_upper = builder_->createTriOp(
      spv::OpSelect, type_uint_, upper_overflow,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, extended, const_0xFFFF0000),
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, standard, const_0xFFFF0000));
  return builder_->createBinOp(spv::OpBitwiseOr, type_uint_, result_lower, result_upper);
}

spv::Id SpirvShaderTranslator::UnpackFloat16x2ExtendedRange(spv::Id packed_uint) {
  spv::Id const_0x7C00 = builder_->makeUintConstant(0x7C00);
  spv::Id lower_overflow = builder_->createBinOp(
      spv::OpIEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, packed_uint, const_0x7C00),
      const_0x7C00);
  spv::Id upper_overflow = builder_->createBinOp(
      spv::OpIEqual, type_bool_,
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                            builder_->createBinOp(spv::OpShiftRightLogical, type_uint_, packed_uint,
                                                  builder_->makeUintConstant(16)),
                            const_0x7C00),
      const_0x7C00);
  spv::Id standard = builder_->createUnaryBuiltinCall(type_float2_, ext_inst_glsl_std_450_,
                                                      GLSLstd450UnpackHalf2x16, packed_uint);

  spv::Id sub_lower = builder_->createTriOp(spv::OpSelect, type_uint_, lower_overflow,
                                            builder_->makeUintConstant(0x0400), const_uint_0_);
  spv::Id sub_upper = builder_->createTriOp(spv::OpSelect, type_uint_, upper_overflow,
                                            builder_->makeUintConstant(0x04000000), const_uint_0_);
  spv::Id reduced = builder_->createBinOp(
      spv::OpISub, type_uint_, packed_uint,
      builder_->createBinOp(spv::OpBitwiseOr, type_uint_, sub_lower, sub_upper));
  spv::Id reduced_unpacked = builder_->createUnaryBuiltinCall(type_float2_, ext_inst_glsl_std_450_,
                                                              GLSLstd450UnpackHalf2x16, reduced);
  id_vector_temp_.clear();
  id_vector_temp_.resize(2, builder_->makeFloatConstant(2.0f));
  spv::Id extended =
      builder_->createBinOp(spv::OpFMul, type_float2_, reduced_unpacked,
                            builder_->makeCompositeConstant(type_float2_, id_vector_temp_));
  spv::Id result_x =
      builder_->createTriOp(spv::OpSelect, type_float_, lower_overflow,
                            builder_->createCompositeExtract(extended, type_float_, 0),
                            builder_->createCompositeExtract(standard, type_float_, 0));
  spv::Id result_y =
      builder_->createTriOp(spv::OpSelect, type_float_, upper_overflow,
                            builder_->createCompositeExtract(extended, type_float_, 1),
                            builder_->createCompositeExtract(standard, type_float_, 1));
  id_vector_temp_.clear();
  id_vector_temp_.push_back(result_x);
  id_vector_temp_.push_back(result_y);
  return builder_->createCompositeConstruct(type_float2_, id_vector_temp_);
}

std::array<spv::Id, 2> SpirvShaderTranslator::FSI_ClampAndPackColor(
    spv::Id color_float4, xenos::ColorRenderTargetFormat format) {
  bool rt_format_is_64bpp = (RenderTargetCache::AddPSIColorFormatFlags(format) &
                             RenderTargetCache::kPSIColorFormatFlag_64bpp) != 0;
  spv::Id unorm_round_offset_float = builder_->makeFloatConstant(0.5f);
  id_vector_temp_.clear();
  id_vector_temp_.resize(4, unorm_round_offset_float);
  spv::Id unorm_round_offset_float4 =
      builder_->makeCompositeConstant(type_float4_, id_vector_temp_);

  std::array<spv::Id, 2> packed{const_uint_0_, const_uint_0_};
  switch (format) {
    case xenos::ColorRenderTargetFormat::k_8_8_8_8: {
      spv::Id packed_8_8_8_8;
      spv::Id color_scaled = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, type_float4_,
          builder_->createTriBuiltinCall(type_float4_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
                                         color_float4, const_float4_0_, const_float4_1_),
          builder_->makeFloatConstant(255.0f));
      spv::Id color_offset = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float4_, color_scaled, unorm_round_offset_float4);
      spv::Id color_uint4 = builder_->createUnaryOp(spv::OpConvertFToU, type_uint4_, color_offset);
      packed_8_8_8_8 = builder_->createCompositeExtract(color_uint4, type_uint_, 0);
      spv::Id component_width = builder_->makeUintConstant(8);
      for (uint32_t i = 1; i < 4; ++i) {
        packed_8_8_8_8 =
            builder_->createQuadOp(spv::OpBitFieldInsert, type_uint_, packed_8_8_8_8,
                                   builder_->createCompositeExtract(color_uint4, type_uint_, i),
                                   builder_->makeUintConstant(8 * i), component_width);
      }
      packed[0] = packed_8_8_8_8;
    } break;
    case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
      spv::Id packed_8_8_8_8_gamma;
      uint_vector_temp_.clear();
      uint_vector_temp_.push_back(0);
      uint_vector_temp_.push_back(1);
      uint_vector_temp_.push_back(2);
      spv::Id color_rgb = builder_->createRvalueSwizzle(spv::NoPrecision, type_float3_,
                                                        color_float4, uint_vector_temp_);
      spv::Id rgb_gamma = SpirvShaderTranslator::LinearToPWLGamma(
          builder_.get(),
          builder_->createRvalueSwizzle(spv::NoPrecision, type_float3_, color_float4,
                                        uint_vector_temp_),
          false, ext_inst_glsl_std_450_);
      spv::Id alpha_clamped = builder_->createTriBuiltinCall(
          type_float_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
          builder_->createCompositeExtract(color_float4, type_float_, 3), const_float_0_,
          const_float_1_);

      spv::Id color_gamma;
      {
        std::unique_ptr<spv::Instruction> color_gamma_composite_construct_op =
            std::make_unique<spv::Instruction>(builder_->getUniqueId(), type_float4_,
                                               spv::OpCompositeConstruct);
        color_gamma_composite_construct_op->addIdOperand(rgb_gamma);
        color_gamma_composite_construct_op->addIdOperand(alpha_clamped);
        color_gamma = color_gamma_composite_construct_op->getResultId();
        builder_->getBuildPoint()->addInstruction(std::move(color_gamma_composite_construct_op));
      }
      spv::Id color_scaled = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, type_float4_, color_gamma, builder_->makeFloatConstant(255.0f));
      spv::Id color_offset = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float4_, color_scaled, unorm_round_offset_float4);
      spv::Id color_uint4 = builder_->createUnaryOp(spv::OpConvertFToU, type_uint4_, color_offset);
      packed_8_8_8_8_gamma = builder_->createCompositeExtract(color_uint4, type_uint_, 0);
      spv::Id component_width = builder_->makeUintConstant(8);
      for (uint32_t i = 1; i < 4; ++i) {
        packed_8_8_8_8_gamma =
            builder_->createQuadOp(spv::OpBitFieldInsert, type_uint_, packed_8_8_8_8_gamma,
                                   builder_->createCompositeExtract(color_uint4, type_uint_, i),
                                   builder_->makeUintConstant(8 * i), component_width);
      }
      packed[0] = packed_8_8_8_8_gamma;
    } break;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
      spv::Id packed_2_10_10_10;
      spv::Id color_clamped =
          builder_->createTriBuiltinCall(type_float4_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
                                         color_float4, const_float4_0_, const_float4_1_);
      id_vector_temp_.clear();
      id_vector_temp_.resize(3, builder_->makeFloatConstant(1023.0f));
      id_vector_temp_.push_back(builder_->makeFloatConstant(3.0f));
      spv::Id color_scaled = builder_->createNoContractionBinOp(
          spv::OpFMul, type_float4_, color_clamped,
          builder_->makeCompositeConstant(type_float4_, id_vector_temp_));
      spv::Id color_offset = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float4_, color_scaled, unorm_round_offset_float4);
      spv::Id color_uint4 = builder_->createUnaryOp(spv::OpConvertFToU, type_uint4_, color_offset);
      packed_2_10_10_10 = builder_->createCompositeExtract(color_uint4, type_uint_, 0);
      spv::Id rgb_width = builder_->makeUintConstant(10);
      spv::Id alpha_width = builder_->makeUintConstant(2);
      for (uint32_t i = 1; i < 4; ++i) {
        packed_2_10_10_10 = builder_->createQuadOp(
            spv::OpBitFieldInsert, type_uint_, packed_2_10_10_10,
            builder_->createCompositeExtract(color_uint4, type_uint_, i),
            builder_->makeUintConstant(10 * i), i == 3 ? alpha_width : rgb_width);
      }
      packed[0] = packed_2_10_10_10;
    } break;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
      spv::Id packed_2_10_10_10_float;
      std::array<spv::Id, 4> color_components;

      for (uint32_t i = 0; i < 3; ++i) {
        color_components[i] = UnclampedFloat32To7e3(
            *builder_, builder_->createCompositeExtract(color_float4, type_float_, i),
            ext_inst_glsl_std_450_);
      }

      spv::Id alpha_scaled = builder_->createNoContractionBinOp(
          spv::OpFMul, type_float_,
          builder_->createTriBuiltinCall(
              type_float_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
              builder_->createCompositeExtract(color_float4, type_float_, 3), const_float_0_,
              const_float_1_),
          builder_->makeFloatConstant(3.0f));
      spv::Id alpha_offset = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float_, alpha_scaled, unorm_round_offset_float);
      color_components[3] = builder_->createUnaryOp(spv::OpConvertFToU, type_uint_, alpha_offset);

      packed_2_10_10_10_float = color_components[0];
      spv::Id rgb_width = builder_->makeUintConstant(10);
      for (uint32_t i = 1; i < 3; ++i) {
        packed_2_10_10_10_float = builder_->createQuadOp(
            spv::OpBitFieldInsert, type_uint_, packed_2_10_10_10_float, color_components[i],
            builder_->makeUintConstant(10 * i), rgb_width);
      }
      packed_2_10_10_10_float = builder_->createQuadOp(
          spv::OpBitFieldInsert, type_uint_, packed_2_10_10_10_float, color_components[3],
          builder_->makeUintConstant(30), builder_->makeUintConstant(2));
      packed[0] = packed_2_10_10_10_float;
    } break;
    case xenos::ColorRenderTargetFormat::k_16_16:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16: {
      std::array<spv::Id, 2> packed_16{const_uint_0_, const_uint_0_};
      id_vector_temp_.clear();
      id_vector_temp_.resize(4, builder_->makeFloatConstant(-32.0f));
      spv::Id const_float4_minus_32 =
          builder_->makeCompositeConstant(type_float4_, id_vector_temp_);
      id_vector_temp_.clear();
      id_vector_temp_.resize(4, builder_->makeFloatConstant(32.0f));
      spv::Id const_float4_32 = builder_->makeCompositeConstant(type_float4_, id_vector_temp_);
      id_vector_temp_.clear();

      spv::Id color_scaled = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, type_float4_,
          builder_->createTriBuiltinCall(
              type_float4_, ext_inst_glsl_std_450_, GLSLstd450FClamp,
              builder_->createTriOp(
                  spv::OpSelect, type_float4_,
                  builder_->createUnaryOp(spv::OpIsNan, type_bool4_, color_float4), const_float4_0_,
                  color_float4),
              const_float4_minus_32, const_float4_32),
          builder_->makeFloatConstant(32767.0f / 32.0f));
      id_vector_temp_.clear();
      id_vector_temp_.resize(4, builder_->makeFloatConstant(-0.5f));
      spv::Id unorm_round_offset_negative_float4 =
          builder_->makeCompositeConstant(type_float4_, id_vector_temp_);
      spv::Id color_offset = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float4_, color_scaled,
          builder_->createTriOp(spv::OpSelect, type_float4_,
                                builder_->createBinOp(spv::OpFOrdLessThan, type_bool4_,
                                                      color_scaled, const_float4_0_),
                                unorm_round_offset_negative_float4, unorm_round_offset_float4));
      spv::Id color_uint4 = builder_->createUnaryOp(
          spv::OpBitcast, type_uint4_,
          builder_->createUnaryOp(spv::OpConvertFToS, type_int4_, color_offset));
      spv::Id component_offset_width = builder_->makeUintConstant(16);

      for (uint32_t i = 0; i < (rt_format_is_64bpp ? 2u : 1u); ++i) {
        packed_16[i] = builder_->createQuadOp(
            spv::OpBitFieldInsert, type_uint_,
            builder_->createCompositeExtract(color_uint4, type_uint_, 2 * i),
            builder_->createCompositeExtract(color_uint4, type_uint_, 2 * i + 1),
            component_offset_width, component_offset_width);
      }
      packed = packed_16;
    } break;
    case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT: {
      std::array<spv::Id, 2> packed_16_float{const_uint_0_, const_uint_0_};

      for (uint32_t i = 0; i < (rt_format_is_64bpp ? 2u : 1u); ++i) {
        uint_vector_temp_.clear();
        uint_vector_temp_.push_back(2 * i);
        uint_vector_temp_.push_back(2 * i + 1);
        packed_16_float[i] = PackFloat16x2ExtendedRange(builder_->createRvalueSwizzle(
            spv::NoPrecision, type_float2_, color_float4, uint_vector_temp_));
      }
      packed = packed_16_float;
    } break;

    default: {
      std::array<spv::Id, 2> packed_32_float{const_uint_0_, const_uint_0_};

      for (uint32_t i = 0; i < (rt_format_is_64bpp ? 2u : 1u); ++i) {
        packed_32_float[i] =
            builder_->createUnaryOp(spv::OpBitcast, type_uint_,
                                    builder_->createCompositeExtract(color_float4, type_float_, i));
      }
      packed = packed_32_float;
    } break;
  }
  return packed;
}

std::array<spv::Id, 4> SpirvShaderTranslator::FSI_UnpackColor(
    std::array<spv::Id, 2> color_packed, xenos::ColorRenderTargetFormat format) {
  std::array<spv::Id, 4> unpacked{const_float_0_, const_float_0_, const_float_0_, const_float_1_};
  switch (format) {
    case xenos::ColorRenderTargetFormat::k_8_8_8_8:
    case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
      const uint32_t i = format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA ? 1 : 0;
      std::array<std::array<spv::Id, 4>, 2> unpacked_8_8_8_8_and_gamma;
      spv::Id component_width = builder_->makeUintConstant(8);
      spv::Id component_scale = builder_->makeFloatConstant(1.0f / 255.0f);
      for (uint32_t j = 0; j < 4; ++j) {
        spv::Id component = builder_->createNoContractionBinOp(
            spv::OpFMul, type_float_,
            builder_->createUnaryOp(
                spv::OpConvertUToF, type_float_,
                builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, color_packed[0],
                                      builder_->makeUintConstant(8 * j), component_width)),
            component_scale);
        if (i && j <= 2) {
          component = SpirvShaderTranslator::PWLGammaToLinear(builder_.get(), component, true,
                                                              ext_inst_glsl_std_450_);
        }
        unpacked_8_8_8_8_and_gamma[i][j] = component;
      }
      unpacked = unpacked_8_8_8_8_and_gamma[i];
    } break;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
      std::array<spv::Id, 4> unpacked_2_10_10_10;
      spv::Id rgb_width = builder_->makeUintConstant(10);
      spv::Id alpha_width = builder_->makeUintConstant(2);
      spv::Id rgb_scale = builder_->makeFloatConstant(1.0f / 1023.0f);
      spv::Id alpha_scale = builder_->makeFloatConstant(1.0f / 3.0f);
      for (uint32_t i = 0; i < 4; ++i) {
        unpacked_2_10_10_10[i] = builder_->createNoContractionBinOp(
            spv::OpFMul, type_float_,
            builder_->createUnaryOp(
                spv::OpConvertUToF, type_float_,
                builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, color_packed[0],
                                      builder_->makeUintConstant(10 * i),
                                      i == 3 ? alpha_width : rgb_width)),
            i == 3 ? alpha_scale : rgb_scale);
      }
      unpacked = unpacked_2_10_10_10;
    } break;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
      std::array<spv::Id, 4> unpacked_2_10_10_10_float;
      spv::Id rgb_width = builder_->makeUintConstant(10);
      for (uint32_t i = 0; i < 3; ++i) {
        unpacked_2_10_10_10_float[i] =
            Float7e3To32(*builder_,
                         builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, color_packed[0],
                                               builder_->makeUintConstant(10 * i), rgb_width),
                         0, false, ext_inst_glsl_std_450_);
      }
      unpacked_2_10_10_10_float[3] = builder_->createNoContractionBinOp(
          spv::OpFMul, type_float_,
          builder_->createUnaryOp(
              spv::OpConvertUToF, type_float_,
              builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, color_packed[0],
                                    builder_->makeUintConstant(30), builder_->makeUintConstant(2))),
          builder_->makeFloatConstant(1.0f / 3.0f));
      unpacked = unpacked_2_10_10_10_float;
    } break;
    case xenos::ColorRenderTargetFormat::k_16_16:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16: {
      const uint32_t i = format == xenos::ColorRenderTargetFormat::k_16_16_16_16 ? 1 : 0;
      std::array<std::array<spv::Id, 4>, 2> unpacked_16;
      unpacked_16[0][2] = const_float_0_;
      unpacked_16[0][3] = const_float_1_;
      spv::Id component_width = builder_->makeUintConstant(16);
      spv::Id component_scale = builder_->makeFloatConstant(32.0f / 32767.0f);
      spv::Id component_min = builder_->makeFloatConstant(-1.0f);
      std::array<spv::Id, 2> color_packed_signed;
      for (uint32_t j = 0; j <= i; ++j) {
        color_packed_signed[j] =
            builder_->createUnaryOp(spv::OpBitcast, type_int_, color_packed[j]);
      }
      for (uint32_t j = 0; j < uint32_t(i ? 4 : 2); ++j) {
        spv::Id component = builder_->createNoContractionBinOp(
            spv::OpFMul, type_float_,
            builder_->createUnaryOp(
                spv::OpConvertSToF, type_float_,
                builder_->createTriOp(spv::OpBitFieldSExtract, type_int_,
                                      color_packed_signed[j >> 1],
                                      builder_->makeUintConstant(16 * (j & 1)), component_width)),
            component_scale);
        component = builder_->createBinBuiltinCall(type_float_, ext_inst_glsl_std_450_,
                                                   GLSLstd450FMax, component_min, component);
        unpacked_16[i][j] = component;
      }
      unpacked = unpacked_16[i];
    } break;
    case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT: {
      const uint32_t i = format == xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT ? 1 : 0;
      std::array<std::array<spv::Id, 4>, 2> unpacked_16_float;
      unpacked_16_float[0][2] = const_float_0_;
      unpacked_16_float[0][3] = const_float_1_;
      for (uint32_t j = 0; j <= i; ++j) {
        spv::Id components_float2 = UnpackFloat16x2ExtendedRange(color_packed[j]);
        for (uint32_t k = 0; k < 2; ++k) {
          unpacked_16_float[i][2 * j + k] =
              builder_->createCompositeExtract(components_float2, type_float_, k);
        }
      }
      unpacked = unpacked_16_float[i];
    } break;

    default: {
      const uint32_t i = format == xenos::ColorRenderTargetFormat::k_32_32_FLOAT ? 1 : 0;
      std::array<std::array<spv::Id, 4>, 2> unpacked_32_float;
      unpacked_32_float[0][1] = const_float_0_;
      unpacked_32_float[0][2] = const_float_0_;
      unpacked_32_float[0][3] = const_float_1_;
      unpacked_32_float[1][2] = const_float_0_;
      unpacked_32_float[1][3] = const_float_1_;
      for (uint32_t j = 0; j <= i; ++j) {
        unpacked_32_float[i][j] =
            builder_->createUnaryOp(spv::OpBitcast, type_float_, color_packed[j]);
      }
      unpacked = unpacked_32_float[i];
    } break;
  }
  return unpacked;
}

spv::Id SpirvShaderTranslator::FSI_FlushNaNClampAndInBlending(spv::Id color_or_alpha,
                                                              spv::Id is_fixed_point,
                                                              spv::Id min_value,
                                                              spv::Id max_value) {
  spv::Id color_or_alpha_type = builder_->getTypeId(color_or_alpha);
  uint32_t component_count = uint32_t(builder_->getNumTypeConstituents(color_or_alpha_type));
  assert_true(builder_->isScalarType(color_or_alpha_type) ||
              builder_->isVectorType(color_or_alpha_type));
  assert_true(builder_->isFloatType(builder_->getScalarTypeId(color_or_alpha_type)));
  assert_true(builder_->getTypeId(min_value) == color_or_alpha_type);
  assert_true(builder_->getTypeId(max_value) == color_or_alpha_type);

  SpirvBuilder::IfBuilder if_fixed_point(is_fixed_point, spv::SelectionControlDontFlattenMask,
                                         *builder_);
  spv::Id color_or_alpha_clamped;
  {
    color_or_alpha_clamped = builder_->createTriBuiltinCall(
        color_or_alpha_type, ext_inst_glsl_std_450_, GLSLstd450FClamp,
        builder_->createTriOp(
            spv::OpSelect, color_or_alpha_type,
            builder_->createUnaryOp(spv::OpIsNan, type_bool_vectors_[component_count - 1],
                                    color_or_alpha),
            const_float_vectors_0_[component_count - 1], color_or_alpha),
        min_value, max_value);
  }
  if_fixed_point.makeEndIf();

  return if_fixed_point.createMergePhi(color_or_alpha_clamped, color_or_alpha);
}

spv::Id SpirvShaderTranslator::FSI_ApplyColorBlendFactor(
    spv::Id value, spv::Id is_fixed_point, spv::Id clamp_min_value, spv::Id clamp_max_value,
    spv::Id factor, spv::Id source_color, spv::Id source_alpha, spv::Id dest_color,
    spv::Id dest_alpha, spv::Id constant_color, spv::Id constant_alpha) {
  SpirvBuilder::IfBuilder factor_not_zero_if(
      builder_->createBinOp(spv::OpINotEqual, type_bool_, factor,
                            builder_->makeUintConstant(uint32_t(xenos::BlendFactor::kZero))),
      spv::SelectionControlDontFlattenMask, *builder_);

  spv::Block& block_factor_head = *builder_->getBuildPoint();
  spv::Block& block_factor_one = builder_->makeNewBlock();
  std::array<spv::Block*, 3> color_factor_blocks;
  std::array<spv::Block*, 3> one_minus_color_factor_blocks;
  std::array<spv::Block*, 3> alpha_factor_blocks;
  std::array<spv::Block*, 3> one_minus_alpha_factor_blocks;
  color_factor_blocks[0] = &builder_->makeNewBlock();
  one_minus_color_factor_blocks[0] = &builder_->makeNewBlock();
  alpha_factor_blocks[0] = &builder_->makeNewBlock();
  one_minus_alpha_factor_blocks[0] = &builder_->makeNewBlock();
  color_factor_blocks[1] = &builder_->makeNewBlock();
  one_minus_color_factor_blocks[1] = &builder_->makeNewBlock();
  alpha_factor_blocks[1] = &builder_->makeNewBlock();
  one_minus_alpha_factor_blocks[1] = &builder_->makeNewBlock();
  color_factor_blocks[2] = &builder_->makeNewBlock();
  one_minus_color_factor_blocks[2] = &builder_->makeNewBlock();
  alpha_factor_blocks[2] = &builder_->makeNewBlock();
  one_minus_alpha_factor_blocks[2] = &builder_->makeNewBlock();
  spv::Block& block_factor_source_alpha_saturate = builder_->makeNewBlock();
  spv::Block& block_factor_merge = builder_->makeNewBlock();
  builder_->createSelectionMerge(&block_factor_merge, spv::SelectionControlDontFlattenMask);
  {
    std::unique_ptr<spv::Instruction> factor_switch_op =
        std::make_unique<spv::Instruction>(spv::OpSwitch);
    factor_switch_op->addIdOperand(factor);

    factor_switch_op->addIdOperand(block_factor_one.getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kSrcColor));
    factor_switch_op->addIdOperand(color_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusSrcColor));
    factor_switch_op->addIdOperand(one_minus_color_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kSrcAlpha));
    factor_switch_op->addIdOperand(alpha_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusSrcAlpha));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kDstColor));
    factor_switch_op->addIdOperand(color_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusDstColor));
    factor_switch_op->addIdOperand(one_minus_color_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kDstAlpha));
    factor_switch_op->addIdOperand(alpha_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusDstAlpha));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kConstantColor));
    factor_switch_op->addIdOperand(color_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusConstantColor));
    factor_switch_op->addIdOperand(one_minus_color_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kConstantAlpha));
    factor_switch_op->addIdOperand(alpha_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusConstantAlpha));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kSrcAlphaSaturate));
    factor_switch_op->addIdOperand(block_factor_source_alpha_saturate.getId());
    builder_->getBuildPoint()->addInstruction(std::move(factor_switch_op));
  }
  block_factor_one.addPredecessor(&block_factor_head);
  for (uint32_t i = 0; i < 3; ++i) {
    color_factor_blocks[i]->addPredecessor(&block_factor_head);
    one_minus_color_factor_blocks[i]->addPredecessor(&block_factor_head);
    alpha_factor_blocks[i]->addPredecessor(&block_factor_head);
    one_minus_alpha_factor_blocks[i]->addPredecessor(&block_factor_head);
  }
  block_factor_source_alpha_saturate.addPredecessor(&block_factor_head);

  builder_->setBuildPoint(&block_factor_one);

  builder_->createBranch(&block_factor_merge);

  std::array<spv::Id, 3> color_factors = {
      source_color,
      dest_color,
      constant_color,
  };
  std::array<spv::Id, 3> alpha_factors = {
      source_alpha,
      dest_alpha,
      constant_alpha,
  };
  std::array<spv::Id, 3> color_factor_results;
  std::array<spv::Id, 3> one_minus_color_factor_results;
  std::array<spv::Id, 3> alpha_factor_results;
  std::array<spv::Id, 3> one_minus_alpha_factor_results;
  for (uint32_t i = 0; i < 3; ++i) {
    spv::Id color_factor = color_factors[i];
    spv::Id alpha_factor = alpha_factors[i];

    {
      builder_->setBuildPoint(color_factor_blocks[i]);
      color_factor_results[i] =
          builder_->createNoContractionBinOp(spv::OpFMul, type_float3_, value, color_factor);
      builder_->createBranch(&block_factor_merge);
    }

    {
      builder_->setBuildPoint(one_minus_color_factor_blocks[i]);
      one_minus_color_factor_results[i] = builder_->createNoContractionBinOp(
          spv::OpFMul, type_float3_, value,
          builder_->createNoContractionBinOp(spv::OpFSub, type_float3_, const_float3_1_,
                                             color_factor));
      builder_->createBranch(&block_factor_merge);
    }

    {
      builder_->setBuildPoint(alpha_factor_blocks[i]);
      alpha_factor_results[i] = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, type_float3_, value, alpha_factor);
      builder_->createBranch(&block_factor_merge);
    }

    {
      builder_->setBuildPoint(one_minus_alpha_factor_blocks[i]);
      one_minus_alpha_factor_results[i] = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, type_float3_, value,
          builder_->createNoContractionBinOp(spv::OpFSub, type_float_, const_float_1_,
                                             alpha_factor));
      builder_->createBranch(&block_factor_merge);
    }
  }

  spv::Id result_source_alpha_saturate;
  {
    builder_->setBuildPoint(&block_factor_source_alpha_saturate);
    result_source_alpha_saturate = builder_->createNoContractionBinOp(
        spv::OpVectorTimesScalar, type_float3_, value,
        builder_->createBinBuiltinCall(type_float_, ext_inst_glsl_std_450_, GLSLstd450NMin,
                                       source_alpha,
                                       builder_->createNoContractionBinOp(
                                           spv::OpFSub, type_float_, const_float_1_, dest_alpha)));
    builder_->createBranch(&block_factor_merge);
  }

  builder_->setBuildPoint(&block_factor_merge);
  id_vector_temp_.clear();
  id_vector_temp_.reserve(2 * 14);
  id_vector_temp_.push_back(value);
  id_vector_temp_.push_back(block_factor_one.getId());
  for (uint32_t i = 0; i < 3; ++i) {
    id_vector_temp_.push_back(color_factor_results[i]);
    id_vector_temp_.push_back(color_factor_blocks[i]->getId());
    id_vector_temp_.push_back(one_minus_color_factor_results[i]);
    id_vector_temp_.push_back(one_minus_color_factor_blocks[i]->getId());
    id_vector_temp_.push_back(alpha_factor_results[i]);
    id_vector_temp_.push_back(alpha_factor_blocks[i]->getId());
    id_vector_temp_.push_back(one_minus_alpha_factor_results[i]);
    id_vector_temp_.push_back(one_minus_alpha_factor_blocks[i]->getId());
  }
  id_vector_temp_.push_back(result_source_alpha_saturate);
  id_vector_temp_.push_back(block_factor_source_alpha_saturate.getId());
  spv::Id result_unclamped = builder_->createOp(spv::OpPhi, type_float3_, id_vector_temp_);
  spv::Id result = FSI_FlushNaNClampAndInBlending(result_unclamped, is_fixed_point, clamp_min_value,
                                                  clamp_max_value);

  factor_not_zero_if.makeEndIf();

  return factor_not_zero_if.createMergePhi(result, const_float3_0_);
}

spv::Id SpirvShaderTranslator::FSI_ApplyAlphaBlendFactor(spv::Id value, spv::Id is_fixed_point,
                                                         spv::Id clamp_min_value,
                                                         spv::Id clamp_max_value, spv::Id factor,
                                                         spv::Id source_alpha, spv::Id dest_alpha,
                                                         spv::Id constant_alpha) {
  SpirvBuilder::IfBuilder factor_not_zero_if(
      builder_->createBinOp(spv::OpINotEqual, type_bool_, factor,
                            builder_->makeUintConstant(uint32_t(xenos::BlendFactor::kZero))),
      spv::SelectionControlDontFlattenMask, *builder_);

  spv::Block& block_factor_head = *builder_->getBuildPoint();
  spv::Block& block_factor_one = builder_->makeNewBlock();
  std::array<spv::Block*, 3> alpha_factor_blocks;
  std::array<spv::Block*, 3> one_minus_alpha_factor_blocks;
  alpha_factor_blocks[0] = &builder_->makeNewBlock();
  one_minus_alpha_factor_blocks[0] = &builder_->makeNewBlock();
  alpha_factor_blocks[1] = &builder_->makeNewBlock();
  one_minus_alpha_factor_blocks[1] = &builder_->makeNewBlock();
  alpha_factor_blocks[2] = &builder_->makeNewBlock();
  one_minus_alpha_factor_blocks[2] = &builder_->makeNewBlock();
  spv::Block& block_factor_source_alpha_saturate = builder_->makeNewBlock();
  spv::Block& block_factor_merge = builder_->makeNewBlock();
  builder_->createSelectionMerge(&block_factor_merge, spv::SelectionControlDontFlattenMask);
  {
    std::unique_ptr<spv::Instruction> factor_switch_op =
        std::make_unique<spv::Instruction>(spv::OpSwitch);
    factor_switch_op->addIdOperand(factor);

    factor_switch_op->addIdOperand(block_factor_one.getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kSrcColor));
    factor_switch_op->addIdOperand(alpha_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusSrcColor));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kSrcAlpha));
    factor_switch_op->addIdOperand(alpha_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusSrcAlpha));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[0]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kDstColor));
    factor_switch_op->addIdOperand(alpha_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusDstColor));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kDstAlpha));
    factor_switch_op->addIdOperand(alpha_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusDstAlpha));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[1]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kConstantColor));
    factor_switch_op->addIdOperand(alpha_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusConstantColor));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kConstantAlpha));
    factor_switch_op->addIdOperand(alpha_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kOneMinusConstantAlpha));
    factor_switch_op->addIdOperand(one_minus_alpha_factor_blocks[2]->getId());
    factor_switch_op->addImmediateOperand(int32_t(xenos::BlendFactor::kSrcAlphaSaturate));
    factor_switch_op->addIdOperand(block_factor_source_alpha_saturate.getId());
    builder_->getBuildPoint()->addInstruction(std::move(factor_switch_op));
  }
  block_factor_one.addPredecessor(&block_factor_head);
  for (uint32_t i = 0; i < 3; ++i) {
    alpha_factor_blocks[i]->addPredecessor(&block_factor_head);
    one_minus_alpha_factor_blocks[i]->addPredecessor(&block_factor_head);
  }
  block_factor_source_alpha_saturate.addPredecessor(&block_factor_head);

  builder_->setBuildPoint(&block_factor_one);

  builder_->createBranch(&block_factor_merge);

  std::array<spv::Id, 3> alpha_factors = {
      source_alpha,
      dest_alpha,
      constant_alpha,
  };
  std::array<spv::Id, 3> alpha_factor_results;
  std::array<spv::Id, 3> one_minus_alpha_factor_results;
  for (uint32_t i = 0; i < 3; ++i) {
    spv::Id alpha_factor = alpha_factors[i];

    {
      builder_->setBuildPoint(alpha_factor_blocks[i]);
      alpha_factor_results[i] =
          builder_->createNoContractionBinOp(spv::OpFMul, type_float_, value, alpha_factor);
      builder_->createBranch(&block_factor_merge);
    }

    {
      builder_->setBuildPoint(one_minus_alpha_factor_blocks[i]);
      one_minus_alpha_factor_results[i] = builder_->createNoContractionBinOp(
          spv::OpFMul, type_float_, value,
          builder_->createNoContractionBinOp(spv::OpFSub, type_float_, const_float_1_,
                                             alpha_factor));
      builder_->createBranch(&block_factor_merge);
    }
  }

  spv::Id result_source_alpha_saturate;
  {
    builder_->setBuildPoint(&block_factor_source_alpha_saturate);
    result_source_alpha_saturate = builder_->createNoContractionBinOp(
        spv::OpFMul, type_float_, value,
        builder_->createBinBuiltinCall(type_float_, ext_inst_glsl_std_450_, GLSLstd450NMin,
                                       source_alpha,
                                       builder_->createNoContractionBinOp(
                                           spv::OpFSub, type_float_, const_float_1_, dest_alpha)));
    builder_->createBranch(&block_factor_merge);
  }

  builder_->setBuildPoint(&block_factor_merge);
  id_vector_temp_.clear();
  id_vector_temp_.reserve(2 * 8);
  id_vector_temp_.push_back(value);
  id_vector_temp_.push_back(block_factor_one.getId());
  for (uint32_t i = 0; i < 3; ++i) {
    id_vector_temp_.push_back(alpha_factor_results[i]);
    id_vector_temp_.push_back(alpha_factor_blocks[i]->getId());
    id_vector_temp_.push_back(one_minus_alpha_factor_results[i]);
    id_vector_temp_.push_back(one_minus_alpha_factor_blocks[i]->getId());
  }
  id_vector_temp_.push_back(result_source_alpha_saturate);
  id_vector_temp_.push_back(block_factor_source_alpha_saturate.getId());
  spv::Id result_unclamped = builder_->createOp(spv::OpPhi, type_float_, id_vector_temp_);
  spv::Id result = FSI_FlushNaNClampAndInBlending(result_unclamped, is_fixed_point, clamp_min_value,
                                                  clamp_max_value);

  factor_not_zero_if.makeEndIf();

  return factor_not_zero_if.createMergePhi(result, const_float_0_);
}

spv::Id SpirvShaderTranslator::FSI_BlendColorOrAlphaWithUnclampedResult(
    spv::Id is_fixed_point, spv::Id clamp_min_value, spv::Id clamp_max_value,
    spv::Id source_color_clamped, spv::Id source_alpha_clamped, spv::Id dest_color,
    spv::Id dest_alpha, spv::Id constant_color_clamped, spv::Id constant_alpha_clamped,
    spv::Id equation, spv::Id source_factor, spv::Id dest_factor) {
  bool is_alpha = source_color_clamped == spv::NoResult;
  assert_false(!is_alpha &&
               (dest_color == spv::NoResult || constant_color_clamped == spv::NoResult));
  assert_false(is_alpha &&
               (dest_color != spv::NoResult || constant_color_clamped != spv::NoResult));
  spv::Id value_type = is_alpha ? type_float_ : type_float3_;

  spv::Id term_source, term_dest;
  if (is_alpha) {
    term_source = FSI_ApplyAlphaBlendFactor(source_alpha_clamped, is_fixed_point, clamp_min_value,
                                            clamp_max_value, source_factor, source_alpha_clamped,
                                            dest_alpha, constant_alpha_clamped);
    term_dest = FSI_ApplyAlphaBlendFactor(dest_alpha, is_fixed_point, clamp_min_value,
                                          clamp_max_value, dest_factor, source_alpha_clamped,
                                          dest_alpha, constant_alpha_clamped);
  } else {
    term_source = FSI_ApplyColorBlendFactor(source_color_clamped, is_fixed_point, clamp_min_value,
                                            clamp_max_value, source_factor, source_color_clamped,
                                            source_alpha_clamped, dest_color, dest_alpha,
                                            constant_color_clamped, constant_alpha_clamped);
    term_dest = FSI_ApplyColorBlendFactor(dest_color, is_fixed_point, clamp_min_value,
                                          clamp_max_value, dest_factor, source_color_clamped,
                                          source_alpha_clamped, dest_color, dest_alpha,
                                          constant_color_clamped, constant_alpha_clamped);
  }

  spv::Block& block_equation_head = *builder_->getBuildPoint();
  spv::Block& block_equation_add = builder_->makeNewBlock();
  spv::Block& block_equation_subtract = builder_->makeNewBlock();
  spv::Block& block_equation_rev_subtract = builder_->makeNewBlock();
  spv::Block& block_equation_min = builder_->makeNewBlock();
  spv::Block& block_equation_max = builder_->makeNewBlock();
  spv::Block& block_equation_merge = builder_->makeNewBlock();
  builder_->createSelectionMerge(&block_equation_merge, spv::SelectionControlDontFlattenMask);
  {
    std::unique_ptr<spv::Instruction> equation_switch_op =
        std::make_unique<spv::Instruction>(spv::OpSwitch);
    equation_switch_op->addIdOperand(equation);

    equation_switch_op->addIdOperand(block_equation_add.getId());
    equation_switch_op->addImmediateOperand(int32_t(xenos::BlendOp::kSubtract));
    equation_switch_op->addIdOperand(block_equation_subtract.getId());
    equation_switch_op->addImmediateOperand(int32_t(xenos::BlendOp::kRevSubtract));
    equation_switch_op->addIdOperand(block_equation_rev_subtract.getId());
    equation_switch_op->addImmediateOperand(int32_t(xenos::BlendOp::kMin));
    equation_switch_op->addIdOperand(block_equation_min.getId());
    equation_switch_op->addImmediateOperand(int32_t(xenos::BlendOp::kMax));
    equation_switch_op->addIdOperand(block_equation_max.getId());
    builder_->getBuildPoint()->addInstruction(std::move(equation_switch_op));
  }
  block_equation_add.addPredecessor(&block_equation_head);
  block_equation_subtract.addPredecessor(&block_equation_head);
  block_equation_rev_subtract.addPredecessor(&block_equation_head);
  block_equation_min.addPredecessor(&block_equation_head);
  block_equation_max.addPredecessor(&block_equation_head);

  builder_->setBuildPoint(&block_equation_add);
  spv::Id result_add =
      builder_->createNoContractionBinOp(spv::OpFAdd, value_type, term_source, term_dest);
  builder_->createBranch(&block_equation_merge);

  builder_->setBuildPoint(&block_equation_subtract);
  spv::Id result_subtract =
      builder_->createNoContractionBinOp(spv::OpFSub, value_type, term_source, term_dest);
  builder_->createBranch(&block_equation_merge);

  builder_->setBuildPoint(&block_equation_rev_subtract);
  spv::Id result_rev_subtract =
      builder_->createNoContractionBinOp(spv::OpFSub, value_type, term_dest, term_source);
  builder_->createBranch(&block_equation_merge);

  builder_->setBuildPoint(&block_equation_min);
  spv::Id result_min = builder_->createBinBuiltinCall(value_type, ext_inst_glsl_std_450_,
                                                      GLSLstd450FMin, term_source, term_dest);
  builder_->createBranch(&block_equation_merge);

  builder_->setBuildPoint(&block_equation_max);
  spv::Id result_max = builder_->createBinBuiltinCall(value_type, ext_inst_glsl_std_450_,
                                                      GLSLstd450FMax, term_source, term_dest);
  builder_->createBranch(&block_equation_merge);

  builder_->setBuildPoint(&block_equation_merge);
  id_vector_temp_.clear();
  id_vector_temp_.push_back(result_add);
  id_vector_temp_.push_back(block_equation_add.getId());
  id_vector_temp_.push_back(result_subtract);
  id_vector_temp_.push_back(block_equation_subtract.getId());
  id_vector_temp_.push_back(result_rev_subtract);
  id_vector_temp_.push_back(block_equation_rev_subtract.getId());
  id_vector_temp_.push_back(result_min);
  id_vector_temp_.push_back(block_equation_min.getId());
  id_vector_temp_.push_back(result_max);
  id_vector_temp_.push_back(block_equation_max.getId());
  spv::Id result_unclamped = builder_->createOp(spv::OpPhi, value_type, id_vector_temp_);

  return FSI_FlushNaNClampAndInBlending(result_unclamped, is_fixed_point, clamp_min_value,
                                        clamp_max_value);
}

void SpirvShaderTranslator::FSI_AlphaToMaskSample(bool initialize, uint32_t sample_index,
                                                  float threshold_base, spv::Id threshold_offset,
                                                  float threshold_offset_scale, spv::Id alpha,
                                                  spv::Id& coverage_out) {
  spv::Id const_threshold_offset_scale = builder_->makeFloatConstant(-threshold_offset_scale);
  spv::Id threshold = builder_->createNoContractionBinOp(spv::OpFMul, type_float_, threshold_offset,
                                                         const_threshold_offset_scale);

  spv::Id const_threshold_base = builder_->makeFloatConstant(threshold_base);
  threshold =
      builder_->createNoContractionBinOp(spv::OpFAdd, type_float_, const_threshold_base, threshold);

  spv::Id sample_passes =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, type_bool_, alpha, threshold);

  if (edram_fragment_shader_interlock_) {
    spv::Id clear_mask = builder_->makeUintConstant(~(0b00010001u << sample_index));

    spv::Id mask_to_apply =
        builder_->createTriOp(spv::OpSelect, type_uint_, sample_passes,
                              builder_->makeUintConstant(0xFFFFFFFFu), clear_mask);

    coverage_out =
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, coverage_out, mask_to_apply);
  } else {
    if (initialize) {
      coverage_out = builder_->makeUintConstant(0u);
    }

    spv::Id sample_bit = builder_->makeUintConstant(1u << sample_index);

    spv::Id coverage_set =
        builder_->createBinOp(spv::OpBitwiseOr, type_uint_, coverage_out, sample_bit);
    coverage_out =
        builder_->createTriOp(spv::OpSelect, type_uint_, sample_passes, coverage_set, coverage_out);
  }
}

void SpirvShaderTranslator::FSI_AlphaToMask() {
  if (edram_fragment_shader_interlock_) {
    if (!current_shader().writes_color_target(0)) {
      return;
    }

    if (main_fsi_sample_mask_ == spv::NoResult) {
      return;
    }
    if (input_fragment_coordinates_ == spv::NoResult) {
      return;
    }
    if (output_or_var_fragment_data_[0] == spv::NoResult) {
      return;
    }

    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantAlphaToMask));
    spv::Id alpha_to_mask_constant = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);

    spv::Id alpha_to_mask_enabled = builder_->createBinOp(
        spv::OpINotEqual, type_bool_, alpha_to_mask_constant, builder_->makeUintConstant(0));

    spv::Block* block_before = builder_->getBuildPoint();
    spv::Id mask_before = main_fsi_sample_mask_;

    spv::Block& block_alpha_enabled = builder_->makeNewBlock();
    spv::Block& block_merge = builder_->makeNewBlock();

    builder_->createSelectionMerge(&block_merge, spv::SelectionControlDontFlattenMask);
    builder_->createConditionalBranch(alpha_to_mask_enabled, &block_alpha_enabled, &block_merge);

    builder_->setBuildPoint(&block_alpha_enabled);

    spv::Id frag_coord = builder_->createLoad(input_fragment_coordinates_, spv::NoPrecision);

    spv::Id frag_x_float = builder_->createCompositeExtract(frag_coord, type_float_, 0);
    spv::Id frag_y_float = builder_->createCompositeExtract(frag_coord, type_float_, 1);

    spv::Id frag_x = builder_->createUnaryOp(spv::OpConvertFToU, type_uint_, frag_x_float);
    spv::Id frag_y = builder_->createUnaryOp(spv::OpConvertFToU, type_uint_, frag_y_float);

    spv::Id y_bit =
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, frag_y, builder_->makeUintConstant(1));
    spv::Id x_bit =
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, frag_x, builder_->makeUintConstant(1));
    spv::Id x_bit_shifted = builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_, x_bit,
                                                  builder_->makeUintConstant(1));
    spv::Id offset_index =
        builder_->createBinOp(spv::OpBitwiseOr, type_uint_, y_bit, x_bit_shifted);

    spv::Id bit_position = builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_, offset_index,
                                                 builder_->makeUintConstant(1));
    spv::Id offset_shifted = builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                                   alpha_to_mask_constant, bit_position);
    spv::Id threshold_offset_uint = builder_->createBinOp(
        spv::OpBitwiseAnd, type_uint_, offset_shifted, builder_->makeUintConstant(0b11));
    spv::Id threshold_offset =
        builder_->createUnaryOp(spv::OpConvertUToF, type_float_, threshold_offset_uint);

    assert_true(output_or_var_fragment_data_[0] != spv::NoResult);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(3));
    spv::Id alpha = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassFunction, output_or_var_fragment_data_[0],
                                    id_vector_temp_),
        spv::NoPrecision);

    spv::Id coverage = main_fsi_sample_mask_;
    switch (FSI_GetMsaaSamples()) {
      case xenos::MsaaSamples::k4X:
        FSI_AlphaToMaskSample(false, 0, 0.75f, threshold_offset, 1.0f / 16.0f, alpha, coverage);
        FSI_AlphaToMaskSample(false, 1, 0.25f, threshold_offset, 1.0f / 16.0f, alpha, coverage);
        FSI_AlphaToMaskSample(false, 2, 0.5f, threshold_offset, 1.0f / 16.0f, alpha, coverage);
        FSI_AlphaToMaskSample(false, 3, 1.0f, threshold_offset, 1.0f / 16.0f, alpha, coverage);
        break;
      case xenos::MsaaSamples::k2X:
        FSI_AlphaToMaskSample(false, 0, 0.5f, threshold_offset, 1.0f / 8.0f, alpha, coverage);
        FSI_AlphaToMaskSample(false, 1, 1.0f, threshold_offset, 1.0f / 8.0f, alpha, coverage);
        break;
      default:
        FSI_AlphaToMaskSample(false, 0, 1.0f, threshold_offset, 1.0f / 4.0f, alpha, coverage);
        break;
    }

    spv::Block* block_alpha_enabled_end = builder_->getBuildPoint();
    builder_->createBranch(&block_merge);

    builder_->setBuildPoint(&block_merge);
    id_vector_temp_.clear();
    id_vector_temp_.push_back(coverage);
    id_vector_temp_.push_back(block_alpha_enabled_end->getId());
    id_vector_temp_.push_back(mask_before);
    id_vector_temp_.push_back(block_before->getId());
    main_fsi_sample_mask_ = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
  }

  if (output_fragment_sample_mask_ == spv::NoResult) {
    return;
  }

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(0));
  spv::Id sample_mask_element = builder_->createAccessChain(
      spv::StorageClassOutput, output_fragment_sample_mask_, id_vector_temp_);
  spv::Id full_coverage = builder_->makeIntConstant(-1);
  builder_->createStore(full_coverage, sample_mask_element);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantAlphaToMask));
  spv::Id alpha_to_mask_constant =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_system_constants_, id_vector_temp_),
                           spv::NoPrecision);

  spv::Id alpha_to_mask_enabled = builder_->createBinOp(
      spv::OpINotEqual, type_bool_, alpha_to_mask_constant, builder_->makeUintConstant(0));

  spv::Block& block_alpha_to_mask_enabled = builder_->makeNewBlock();
  spv::Block& block_alpha_to_mask_merge = builder_->makeNewBlock();

  builder_->createSelectionMerge(&block_alpha_to_mask_merge, spv::SelectionControlDontFlattenMask);
  builder_->createConditionalBranch(alpha_to_mask_enabled, &block_alpha_to_mask_enabled,
                                    &block_alpha_to_mask_merge);

  builder_->setBuildPoint(&block_alpha_to_mask_enabled);

  spv::Id frag_coord = builder_->createLoad(input_fragment_coordinates_, spv::NoPrecision);

  spv::Id frag_x_float = builder_->createCompositeExtract(frag_coord, type_float_, 0);
  spv::Id frag_y_float = builder_->createCompositeExtract(frag_coord, type_float_, 1);

  spv::Id frag_x = builder_->createUnaryOp(spv::OpConvertFToU, type_uint_, frag_x_float);
  spv::Id frag_y = builder_->createUnaryOp(spv::OpConvertFToU, type_uint_, frag_y_float);

  spv::Id y_bit =
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, frag_y, builder_->makeUintConstant(1));

  spv::Id x_bit =
      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, frag_x, builder_->makeUintConstant(1));
  spv::Id x_bit_shifted = builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_, x_bit,
                                                builder_->makeUintConstant(1));

  spv::Id offset_index = builder_->createBinOp(spv::OpBitwiseOr, type_uint_, y_bit, x_bit_shifted);

  spv::Id bit_position = builder_->createBinOp(spv::OpShiftLeftLogical, type_uint_, offset_index,
                                               builder_->makeUintConstant(1));

  spv::Id offset_shifted = builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                                                 alpha_to_mask_constant, bit_position);
  spv::Id threshold_offset_uint = builder_->createBinOp(
      spv::OpBitwiseAnd, type_uint_, offset_shifted, builder_->makeUintConstant(0b11));

  spv::Id threshold_offset =
      builder_->createUnaryOp(spv::OpConvertUToF, type_float_, threshold_offset_uint);

  id_vector_temp_.clear();
  id_vector_temp_.push_back(builder_->makeIntConstant(3));
  spv::Id alpha = builder_->createLoad(
      builder_->createAccessChain(spv::StorageClassFunction, output_or_var_fragment_data_[0],
                                  id_vector_temp_),
      spv::NoPrecision);

  spv::Id msaa_samples = LoadMsaaSamplesFromFlags();

  spv::Id msaa_enabled = builder_->createBinOp(spv::OpINotEqual, type_bool_, msaa_samples,
                                               builder_->makeUintConstant(0));

  spv::Block& block_msaa_head = builder_->makeNewBlock();
  spv::Block& block_msaa_enabled = builder_->makeNewBlock();
  spv::Block& block_msaa_disabled = builder_->makeNewBlock();
  spv::Block& block_msaa_merge = builder_->makeNewBlock();

  builder_->createSelectionMerge(&block_msaa_merge, spv::SelectionControlDontFlattenMask);
  builder_->createConditionalBranch(msaa_enabled, &block_msaa_enabled, &block_msaa_disabled);

  builder_->setBuildPoint(&block_msaa_enabled);

  spv::Id is_4x_msaa =
      builder_->createBinOp(spv::OpIEqual, type_bool_, msaa_samples, builder_->makeUintConstant(2));

  spv::Block& block_4x_msaa = builder_->makeNewBlock();
  spv::Block& block_2x_msaa = builder_->makeNewBlock();
  spv::Block& block_msaa_mode_merge = builder_->makeNewBlock();

  builder_->createSelectionMerge(&block_msaa_mode_merge, spv::SelectionControlDontFlattenMask);
  builder_->createConditionalBranch(is_4x_msaa, &block_4x_msaa, &block_2x_msaa);

  builder_->setBuildPoint(&block_4x_msaa);
  spv::Id coverage_4x = spv::NoResult;
  FSI_AlphaToMaskSample(true, 0, 0.75f, threshold_offset, 1.0f / 16.0f, alpha, coverage_4x);
  FSI_AlphaToMaskSample(false, 1, 0.25f, threshold_offset, 1.0f / 16.0f, alpha, coverage_4x);
  FSI_AlphaToMaskSample(false, 2, 0.5f, threshold_offset, 1.0f / 16.0f, alpha, coverage_4x);
  FSI_AlphaToMaskSample(false, 3, 1.0f, threshold_offset, 1.0f / 16.0f, alpha, coverage_4x);
  builder_->createBranch(&block_msaa_mode_merge);

  builder_->setBuildPoint(&block_2x_msaa);
  spv::Id coverage_2x = spv::NoResult;

  if (edram_fragment_shader_interlock_) {
    FSI_AlphaToMaskSample(true, 0, 0.5f, threshold_offset, 1.0f / 8.0f, alpha, coverage_2x);
    FSI_AlphaToMaskSample(false, 1, 1.0f, threshold_offset, 1.0f / 8.0f, alpha, coverage_2x);
  } else {
    if (native_2x_msaa_with_attachments_) {
      FSI_AlphaToMaskSample(true, 1, 0.5f, threshold_offset, 1.0f / 8.0f, alpha, coverage_2x);
      FSI_AlphaToMaskSample(false, 0, 1.0f, threshold_offset, 1.0f / 8.0f, alpha, coverage_2x);
    } else {
      FSI_AlphaToMaskSample(true, 0, 0.5f, threshold_offset, 1.0f / 8.0f, alpha, coverage_2x);
      FSI_AlphaToMaskSample(false, 3, 1.0f, threshold_offset, 1.0f / 8.0f, alpha, coverage_2x);
    }
  }
  builder_->createBranch(&block_msaa_mode_merge);

  builder_->setBuildPoint(&block_msaa_mode_merge);

  id_vector_temp_.clear();
  id_vector_temp_.reserve(2 * 2);
  id_vector_temp_.push_back(coverage_4x);
  id_vector_temp_.push_back(block_4x_msaa.getId());
  id_vector_temp_.push_back(coverage_2x);
  id_vector_temp_.push_back(block_2x_msaa.getId());
  spv::Id coverage_msaa_enabled = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
  builder_->createBranch(&block_msaa_merge);

  builder_->setBuildPoint(&block_msaa_disabled);
  spv::Id coverage_1x = spv::NoResult;
  FSI_AlphaToMaskSample(true, 0, 1.0f, threshold_offset, 1.0f / 4.0f, alpha, coverage_1x);
  builder_->createBranch(&block_msaa_merge);

  builder_->setBuildPoint(&block_msaa_merge);

  id_vector_temp_.clear();
  id_vector_temp_.reserve(2 * 2);
  id_vector_temp_.push_back(coverage_msaa_enabled);
  id_vector_temp_.push_back(block_msaa_mode_merge.getId());
  id_vector_temp_.push_back(coverage_1x);
  id_vector_temp_.push_back(block_msaa_disabled.getId());
  spv::Id coverage_final = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);

  if (!edram_fragment_shader_interlock_) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(builder_->makeIntConstant(0));
    spv::Id sample_mask_element = builder_->createAccessChain(
        spv::StorageClassOutput, output_fragment_sample_mask_, id_vector_temp_);
    spv::Id coverage_int = builder_->createUnaryOp(spv::OpBitcast, type_int_, coverage_final);
    builder_->createStore(coverage_int, sample_mask_element);

    spv::Id coverage_zero = builder_->createBinOp(spv::OpIEqual, type_bool_, coverage_final,
                                                  builder_->makeUintConstant(0));
    SpirvBuilder::IfBuilder coverage_discard_if(coverage_zero, spv::SelectionControlDontFlattenMask,
                                                *builder_);
    builder_->createNoResultOp(spv::OpKill);

    coverage_discard_if.makeEndIf(false);
  }

  builder_->createBranch(&block_alpha_to_mask_merge);
  builder_->setBuildPoint(&block_alpha_to_mask_merge);

  if (!edram_fragment_shader_interlock_ && var_main_zpd_coverage_ != spv::NoResult) {
    id_vector_temp_.clear();
    id_vector_temp_.push_back(const_int_0_);
    spv::Id sample_mask_element = builder_->createAccessChain(
        spv::StorageClassOutput, output_fragment_sample_mask_, id_vector_temp_);
    spv::Id alpha_to_coverage_mask = builder_->createUnaryOp(
        spv::OpBitcast, type_uint_, builder_->createLoad(sample_mask_element, spv::NoPrecision));
    builder_->createStore(
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                              builder_->createLoad(var_main_zpd_coverage_, spv::NoPrecision),
                              alpha_to_coverage_mask),
        var_main_zpd_coverage_);
  }
}

}
