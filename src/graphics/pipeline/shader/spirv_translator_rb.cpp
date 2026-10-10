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

spv::Id SpirvShaderTranslator::PreClampedFloat32To7e3(SpirvBuilder& builder, spv::Id f32_scalar,
                                                      spv::Id ext_inst_glsl_std_450) {
  spv::Id type_uint = builder.makeUintType(32);

  {
    spv::Id source_type = builder.getTypeId(f32_scalar);
    assert_true(builder.isScalarType(source_type));
    if (!builder.isUintType(source_type)) {
      f32_scalar = builder.createUnaryOp(spv::OpBitcast, type_uint, f32_scalar);
    }
  }

  spv::Id denormal_biased_f32;
  {
    spv::Instruction* denormal_insert_instruction =
        new spv::Instruction(builder.getUniqueId(), type_uint, spv::OpBitFieldInsert);
    denormal_insert_instruction->addIdOperand(f32_scalar);
    denormal_insert_instruction->addIdOperand(builder.makeUintConstant(1));
    denormal_insert_instruction->addIdOperand(builder.makeUintConstant(23));
    denormal_insert_instruction->addIdOperand(builder.makeUintConstant(9));
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(denormal_insert_instruction));
    denormal_biased_f32 = denormal_insert_instruction->getResultId();
  }

  spv::Id denormal_biased_f32_shift_amount;
  {
    spv::Instruction* denormal_shift_amount_instruction =
        new spv::Instruction(builder.getUniqueId(), type_uint, spv::OpExtInst);
    denormal_shift_amount_instruction->addIdOperand(ext_inst_glsl_std_450);
    denormal_shift_amount_instruction->addImmediateOperand(GLSLstd450UMin);
    denormal_shift_amount_instruction->addIdOperand(
        builder.createBinOp(spv::OpISub, type_uint, builder.makeUintConstant(125),
                            builder.createBinOp(spv::OpShiftRightLogical, type_uint, f32_scalar,
                                                builder.makeUintConstant(23))));
    denormal_shift_amount_instruction->addIdOperand(builder.makeUintConstant(24));
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(denormal_shift_amount_instruction));
    denormal_biased_f32_shift_amount = denormal_shift_amount_instruction->getResultId();
  }

  denormal_biased_f32 = builder.createBinOp(spv::OpShiftRightLogical, type_uint,
                                            denormal_biased_f32, denormal_biased_f32_shift_amount);

  spv::Id normal_biased_f32 = builder.createBinOp(spv::OpISub, type_uint, f32_scalar,
                                                  builder.makeUintConstant(UINT32_C(124) << 23));

  spv::Id biased_f32 =
      builder.createTriOp(spv::OpSelect, type_uint,
                          builder.createBinOp(spv::OpULessThan, builder.makeBoolType(), f32_scalar,
                                              builder.makeUintConstant(0x3E800000)),
                          denormal_biased_f32, normal_biased_f32);

  return builder.createTriOp(
      spv::OpBitFieldUExtract, type_uint,
      builder.createBinOp(
          spv::OpIAdd, type_uint,
          builder.createBinOp(spv::OpIAdd, type_uint, biased_f32, builder.makeUintConstant(0x7FFF)),
          builder.createTriOp(spv::OpBitFieldUExtract, type_uint, biased_f32,
                              builder.makeUintConstant(16), builder.makeUintConstant(1))),
      builder.makeUintConstant(16), builder.makeUintConstant(10));
}

spv::Id SpirvShaderTranslator::UnclampedFloat32To7e3(SpirvBuilder& builder, spv::Id f32_scalar,
                                                     spv::Id ext_inst_glsl_std_450) {
  spv::Id type_float = builder.makeFloatType(32);

  {
    spv::Id source_type = builder.getTypeId(f32_scalar);
    assert_true(builder.isScalarType(source_type));
    if (!builder.isFloatType(source_type)) {
      f32_scalar = builder.createUnaryOp(spv::OpBitcast, type_float, f32_scalar);
    }
  }

  {
    spv::Instruction* clamp_instruction =
        new spv::Instruction(builder.getUniqueId(), type_float, spv::OpExtInst);
    clamp_instruction->addIdOperand(ext_inst_glsl_std_450);
    clamp_instruction->addImmediateOperand(GLSLstd450NClamp);
    clamp_instruction->addIdOperand(f32_scalar);
    clamp_instruction->addIdOperand(builder.makeFloatConstant(0.0f));
    clamp_instruction->addIdOperand(builder.makeFloatConstant(31.875f));
    builder.getBuildPoint()->addInstruction(std::unique_ptr<spv::Instruction>(clamp_instruction));
    f32_scalar = clamp_instruction->getResultId();
  }

  return PreClampedFloat32To7e3(builder, f32_scalar, ext_inst_glsl_std_450);
}

spv::Id SpirvShaderTranslator::Float7e3To32(SpirvBuilder& builder, spv::Id f10_uint_scalar,
                                            uint32_t f10_shift, bool result_as_uint,
                                            spv::Id ext_inst_glsl_std_450) {
  assert_true(builder.isUintType(builder.getTypeId(f10_uint_scalar)));
  assert_true(f10_shift <= (32 - 10));

  spv::Id type_bool = builder.makeBoolType();
  spv::Id type_int = builder.makeIntType(32);
  spv::Id type_uint = builder.makeUintType(32);

  spv::Id f10_unbiased_exponent =
      builder.createTriOp(spv::OpBitFieldUExtract, type_uint, f10_uint_scalar,
                          builder.makeUintConstant(f10_shift + 7), builder.makeUintConstant(3));
  spv::Id f10_mantissa =
      builder.createTriOp(spv::OpBitFieldUExtract, type_uint, f10_uint_scalar,
                          builder.makeUintConstant(f10_shift), builder.makeUintConstant(7));

  spv::Id denormal_mantissa_msb;
  {
    spv::Instruction* denormal_mantissa_msb_instruction =
        new spv::Instruction(builder.getUniqueId(), type_int, spv::OpExtInst);
    denormal_mantissa_msb_instruction->addIdOperand(ext_inst_glsl_std_450);
    denormal_mantissa_msb_instruction->addImmediateOperand(GLSLstd450FindUMsb);
    denormal_mantissa_msb_instruction->addIdOperand(f10_mantissa);
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(denormal_mantissa_msb_instruction));
    denormal_mantissa_msb = denormal_mantissa_msb_instruction->getResultId();
  }
  denormal_mantissa_msb = builder.createUnaryOp(spv::OpBitcast, type_uint, denormal_mantissa_msb);

  spv::Id denormal_f32_unbiased_exponent = builder.createBinOp(
      spv::OpISub, type_uint, denormal_mantissa_msb, builder.makeUintConstant(6));

  spv::Id denormal_f32_mantissa =
      builder.createBinOp(spv::OpShiftLeftLogical, type_uint, f10_mantissa,
                          builder.createBinOp(spv::OpISub, type_uint, builder.makeUintConstant(7),
                                              denormal_mantissa_msb));

  spv::Id f10_mantissa_is_nonzero =
      builder.createBinOp(spv::OpINotEqual, type_bool, f10_mantissa, builder.makeUintConstant(0));

  denormal_f32_unbiased_exponent =
      builder.createTriOp(spv::OpSelect, type_uint, f10_mantissa_is_nonzero,
                          denormal_f32_unbiased_exponent, builder.makeUintConstant(uint32_t(-124)));
  denormal_f32_mantissa = builder.createTriOp(spv::OpSelect, type_uint, f10_mantissa_is_nonzero,
                                              denormal_f32_mantissa, builder.makeUintConstant(0));

  spv::Id f10_is_normal = builder.createBinOp(spv::OpINotEqual, type_bool, f10_unbiased_exponent,
                                              builder.makeUintConstant(0));
  spv::Id f32_unbiased_exponent =
      builder.createTriOp(spv::OpSelect, type_uint, f10_is_normal, f10_unbiased_exponent,
                          denormal_f32_unbiased_exponent);
  spv::Id f32_mantissa = builder.createTriOp(spv::OpSelect, type_uint, f10_is_normal, f10_mantissa,
                                             denormal_f32_mantissa);

  spv::Id f32_shifted;
  {
    spv::Instruction* f32_insert_instruction =
        new spv::Instruction(builder.getUniqueId(), type_uint, spv::OpBitFieldInsert);
    f32_insert_instruction->addIdOperand(f32_mantissa);
    f32_insert_instruction->addIdOperand(builder.createBinOp(
        spv::OpIAdd, type_uint, f32_unbiased_exponent, builder.makeUintConstant(124)));
    f32_insert_instruction->addIdOperand(builder.makeUintConstant(7));
    f32_insert_instruction->addIdOperand(builder.makeUintConstant(8));
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(f32_insert_instruction));
    f32_shifted = f32_insert_instruction->getResultId();
  }
  spv::Id f32 = builder.createBinOp(spv::OpShiftLeftLogical, type_uint, f32_shifted,
                                    builder.makeUintConstant(23 - 7));

  if (!result_as_uint) {
    f32 = builder.createUnaryOp(spv::OpBitcast, builder.makeFloatType(32), f32);
  }

  return f32;
}

spv::Id SpirvShaderTranslator::PreClampedDepthTo20e4(SpirvBuilder& builder, spv::Id f32_scalar,
                                                     bool round_to_nearest_even,
                                                     bool remap_from_0_to_0_5,
                                                     spv::Id ext_inst_glsl_std_450) {
  uint32_t remap_bias = uint32_t(remap_from_0_to_0_5);

  spv::Id type_uint = builder.makeUintType(32);

  {
    spv::Id source_type = builder.getTypeId(f32_scalar);
    assert_true(builder.isScalarType(source_type));
    if (!builder.isUintType(source_type)) {
      f32_scalar = builder.createUnaryOp(spv::OpBitcast, type_uint, f32_scalar);
    }
  }

  spv::Id denormal_biased_f32;
  {
    spv::Instruction* denormal_insert_instruction =
        new spv::Instruction(builder.getUniqueId(), type_uint, spv::OpBitFieldInsert);
    denormal_insert_instruction->addIdOperand(f32_scalar);
    denormal_insert_instruction->addIdOperand(builder.makeUintConstant(1));
    denormal_insert_instruction->addIdOperand(builder.makeUintConstant(23));
    denormal_insert_instruction->addIdOperand(builder.makeUintConstant(9));
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(denormal_insert_instruction));
    denormal_biased_f32 = denormal_insert_instruction->getResultId();
  }

  spv::Id denormal_biased_f32_shift_amount;
  {
    spv::Instruction* denormal_shift_amount_instruction =
        new spv::Instruction(builder.getUniqueId(), type_uint, spv::OpExtInst);
    denormal_shift_amount_instruction->addIdOperand(ext_inst_glsl_std_450);
    denormal_shift_amount_instruction->addImmediateOperand(GLSLstd450UMin);
    denormal_shift_amount_instruction->addIdOperand(
        builder.createBinOp(spv::OpISub, type_uint, builder.makeUintConstant(113 - remap_bias),
                            builder.createBinOp(spv::OpShiftRightLogical, type_uint, f32_scalar,
                                                builder.makeUintConstant(23))));
    denormal_shift_amount_instruction->addIdOperand(builder.makeUintConstant(24));
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(denormal_shift_amount_instruction));
    denormal_biased_f32_shift_amount = denormal_shift_amount_instruction->getResultId();
  }

  denormal_biased_f32 = builder.createBinOp(spv::OpShiftRightLogical, type_uint,
                                            denormal_biased_f32, denormal_biased_f32_shift_amount);

  spv::Id normal_biased_f32 =
      builder.createBinOp(spv::OpISub, type_uint, f32_scalar,
                          builder.makeUintConstant((UINT32_C(112) - remap_bias) << 23));

  spv::Id biased_f32 = builder.createTriOp(
      spv::OpSelect, type_uint,
      builder.createBinOp(spv::OpULessThan, builder.makeBoolType(), f32_scalar,
                          builder.makeUintConstant(0x38800000 - (remap_bias << 23))),
      denormal_biased_f32, normal_biased_f32);

  if (round_to_nearest_even) {
    biased_f32 = builder.createBinOp(
        spv::OpIAdd, type_uint,
        builder.createBinOp(spv::OpIAdd, type_uint, biased_f32, builder.makeUintConstant(3)),
        builder.createTriOp(spv::OpBitFieldUExtract, type_uint, biased_f32,
                            builder.makeUintConstant(3), builder.makeUintConstant(1)));
  }
  return builder.createTriOp(spv::OpBitFieldUExtract, type_uint, biased_f32,
                             builder.makeUintConstant(3), builder.makeUintConstant(24));
}

spv::Id SpirvShaderTranslator::Depth20e4To32(SpirvBuilder& builder, spv::Id f24_uint_scalar,
                                             uint32_t f24_shift, bool remap_to_0_to_0_5,
                                             bool result_as_uint, spv::Id ext_inst_glsl_std_450) {
  assert_true(builder.isUintType(builder.getTypeId(f24_uint_scalar)));
  assert_true(f24_shift <= (32 - 24));

  uint32_t remap_bias = uint32_t(remap_to_0_to_0_5);

  spv::Id type_bool = builder.makeBoolType();
  spv::Id type_int = builder.makeIntType(32);
  spv::Id type_uint = builder.makeUintType(32);

  spv::Id f24_unbiased_exponent =
      builder.createTriOp(spv::OpBitFieldUExtract, type_uint, f24_uint_scalar,
                          builder.makeUintConstant(f24_shift + 20), builder.makeUintConstant(4));
  spv::Id f24_mantissa =
      builder.createTriOp(spv::OpBitFieldUExtract, type_uint, f24_uint_scalar,
                          builder.makeUintConstant(f24_shift), builder.makeUintConstant(20));

  spv::Id denormal_mantissa_msb;
  {
    spv::Instruction* denormal_mantissa_msb_instruction =
        new spv::Instruction(builder.getUniqueId(), type_int, spv::OpExtInst);
    denormal_mantissa_msb_instruction->addIdOperand(ext_inst_glsl_std_450);
    denormal_mantissa_msb_instruction->addImmediateOperand(GLSLstd450FindUMsb);
    denormal_mantissa_msb_instruction->addIdOperand(f24_mantissa);
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(denormal_mantissa_msb_instruction));
    denormal_mantissa_msb = denormal_mantissa_msb_instruction->getResultId();
  }
  denormal_mantissa_msb = builder.createUnaryOp(spv::OpBitcast, type_uint, denormal_mantissa_msb);

  spv::Id denormal_f32_unbiased_exponent = builder.createBinOp(
      spv::OpISub, type_uint, denormal_mantissa_msb, builder.makeUintConstant(19));

  spv::Id denormal_f32_mantissa =
      builder.createBinOp(spv::OpShiftLeftLogical, type_uint, f24_mantissa,
                          builder.createBinOp(spv::OpISub, type_uint, builder.makeUintConstant(20),
                                              denormal_mantissa_msb));

  spv::Id f24_mantissa_is_nonzero =
      builder.createBinOp(spv::OpINotEqual, type_bool, f24_mantissa, builder.makeUintConstant(0));

  denormal_f32_unbiased_exponent = builder.createTriOp(
      spv::OpSelect, type_uint, f24_mantissa_is_nonzero, denormal_f32_unbiased_exponent,
      builder.makeUintConstant(uint32_t(-int32_t(112 - remap_bias))));
  denormal_f32_mantissa = builder.createTriOp(spv::OpSelect, type_uint, f24_mantissa_is_nonzero,
                                              denormal_f32_mantissa, builder.makeUintConstant(0));

  spv::Id f24_is_normal = builder.createBinOp(spv::OpINotEqual, type_bool, f24_unbiased_exponent,
                                              builder.makeUintConstant(0));
  spv::Id f32_unbiased_exponent =
      builder.createTriOp(spv::OpSelect, type_uint, f24_is_normal, f24_unbiased_exponent,
                          denormal_f32_unbiased_exponent);
  spv::Id f32_mantissa = builder.createTriOp(spv::OpSelect, type_uint, f24_is_normal, f24_mantissa,
                                             denormal_f32_mantissa);

  spv::Id f32_shifted;
  {
    spv::Instruction* f32_insert_instruction =
        new spv::Instruction(builder.getUniqueId(), type_uint, spv::OpBitFieldInsert);
    f32_insert_instruction->addIdOperand(f32_mantissa);
    f32_insert_instruction->addIdOperand(builder.createBinOp(
        spv::OpIAdd, type_uint, f32_unbiased_exponent, builder.makeUintConstant(112 - remap_bias)));
    f32_insert_instruction->addIdOperand(builder.makeUintConstant(20));
    f32_insert_instruction->addIdOperand(builder.makeUintConstant(8));
    builder.getBuildPoint()->addInstruction(
        std::unique_ptr<spv::Instruction>(f32_insert_instruction));
    f32_shifted = f32_insert_instruction->getResultId();
  }
  spv::Id f32 = builder.createBinOp(spv::OpShiftLeftLogical, type_uint, f32_shifted,
                                    builder.makeUintConstant(23 - 20));

  if (!result_as_uint) {
    f32 = builder.createUnaryOp(spv::OpBitcast, builder.makeFloatType(32), f32);
  }

  return f32;
}

void SpirvShaderTranslator::CompleteFragmentShaderInMain() {
  BisectOverrideColorOutput();

  uint32_t fsi_sample_count = edram_fragment_shader_interlock_ ? FSI_GetSampleCount() : 0;

  if (edram_fragment_shader_interlock_ && !FSI_IsDepthStencilEarly()) {
    FSI_LoadSampleMask();
  }

  bool fsi_pixel_potentially_killed = false;

  if (current_shader().kills_pixels()) {
    if (edram_fragment_shader_interlock_) {
      fsi_pixel_potentially_killed = true;
      if (!features_.demote_to_helper_invocation) {
        assert_true(var_main_kill_pixel_ != spv::NoResult);
        main_fsi_sample_mask_ = builder_->createTriOp(
            spv::OpSelect, type_uint_, builder_->createLoad(var_main_kill_pixel_, spv::NoPrecision),
            const_uint_0_, main_fsi_sample_mask_);
      }
    } else {
      if (!features_.demote_to_helper_invocation) {
        assert_true(var_main_kill_pixel_ != spv::NoResult);
        SpirvBuilder::IfBuilder kill_pixel_if(
            builder_->createLoad(var_main_kill_pixel_, spv::NoPrecision),
            spv::SelectionControlMaskNone, *builder_);

        builder_->createNoResultOp(spv::OpKill);

        kill_pixel_if.makeEndIf(false);
      }
    }
  }

  uint32_t color_targets_written = current_shader().writes_color_targets();

  if ((color_targets_written & 0b1) && !IsExecutionModeEarlyFragmentTests()) {
    spv::Id fsi_sample_mask_in_rt_0_alpha_tests = spv::NoResult;
    spv::Block* block_rt_0_alpha_tests_rt_written_head = nullptr;
    spv::Block* block_rt_0_alpha_tests_rt_written_merge = nullptr;
    builder_->makeNewBlock();
    if (var_main_fsi_color_written_ != spv::NoResult) {
      if (edram_fragment_shader_interlock_) {
        fsi_sample_mask_in_rt_0_alpha_tests = main_fsi_sample_mask_;
      }
      spv::Id rt_0_written = builder_->createBinOp(
          spv::OpINotEqual, type_bool_,
          builder_->createBinOp(spv::OpBitwiseAnd, type_uint_,
                                builder_->createLoad(var_main_fsi_color_written_, spv::NoPrecision),
                                builder_->makeUintConstant(0b1)),
          const_uint_0_);
      block_rt_0_alpha_tests_rt_written_head = builder_->getBuildPoint();
      spv::Block& block_rt_0_alpha_tests_rt_written = builder_->makeNewBlock();
      block_rt_0_alpha_tests_rt_written_merge = &builder_->makeNewBlock();
      builder_->createSelectionMerge(block_rt_0_alpha_tests_rt_written_merge,
                                     spv::SelectionControlDontFlattenMask);
      {
        std::unique_ptr<spv::Instruction> rt_0_written_branch_conditional_op =
            std::make_unique<spv::Instruction>(spv::OpBranchConditional);
        rt_0_written_branch_conditional_op->addIdOperand(rt_0_written);
        rt_0_written_branch_conditional_op->addIdOperand(block_rt_0_alpha_tests_rt_written.getId());
        rt_0_written_branch_conditional_op->addIdOperand(
            block_rt_0_alpha_tests_rt_written_merge->getId());

        rt_0_written_branch_conditional_op->addImmediateOperand(2);
        rt_0_written_branch_conditional_op->addImmediateOperand(1);
        builder_->getBuildPoint()->addInstruction(std::move(rt_0_written_branch_conditional_op));
      }
      block_rt_0_alpha_tests_rt_written.addPredecessor(block_rt_0_alpha_tests_rt_written_head);
      block_rt_0_alpha_tests_rt_written_merge->addPredecessor(
          block_rt_0_alpha_tests_rt_written_head);
      builder_->setBuildPoint(&block_rt_0_alpha_tests_rt_written);
    }

    spv::Id alpha_test_function = builder_->createTriOp(
        spv::OpBitFieldUExtract, type_uint_, main_system_constant_flags_,
        builder_->makeUintConstant(kSysFlag_AlphaPassIfLess_Shift), builder_->makeUintConstant(3));

    SpirvBuilder::IfBuilder if_alpha_test_function_is_non_always(
        builder_->createBinOp(
            spv::OpINotEqual, type_bool_, alpha_test_function,
            builder_->makeUintConstant(uint32_t(xenos::CompareFunction::kAlways))),
        spv::SelectionControlDontFlattenMask, *builder_);
    {
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(3));
      spv::Id alpha_test_alpha = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassFunction, output_or_var_fragment_data_[0],
                                      id_vector_temp_),
          spv::NoPrecision);
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantAlphaTestReference));
      spv::Id alpha_test_reference = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                      id_vector_temp_),
          spv::NoPrecision);

      SpirvBuilder::IfBuilder if_alpha_test_function_is_not_equal(
          builder_->createBinOp(
              spv::OpIEqual, type_bool_, alpha_test_function,
              builder_->makeUintConstant(uint32_t(xenos::CompareFunction::kNotEqual))),
          spv::SelectionControlDontFlattenMask, *builder_, 1, 2);
      spv::Id alpha_test_result_not_equal;
      {
        alpha_test_result_not_equal = builder_->createBinOp(spv::OpFUnordNotEqual, type_bool_,
                                                            alpha_test_alpha, alpha_test_reference);
      }
      if_alpha_test_function_is_not_equal.makeBeginElse();
      spv::Id alpha_test_result_non_not_equal;
      {
        static constexpr spv::Op kAlphaTestOps[] = {spv::OpFOrdLessThan, spv::OpFOrdEqual,
                                                    spv::OpFOrdGreaterThan};
        for (uint32_t i = 0; i < 3; ++i) {
          spv::Id alpha_test_comparison_result = builder_->createBinOp(
              spv::OpLogicalAnd, type_bool_,
              builder_->createBinOp(kAlphaTestOps[i], type_bool_, alpha_test_alpha,
                                    alpha_test_reference),
              builder_->createBinOp(
                  spv::OpINotEqual, type_bool_,
                  builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, alpha_test_function,
                                        builder_->makeUintConstant(UINT32_C(1) << i)),
                  const_uint_0_));
          if (i) {
            alpha_test_result_non_not_equal =
                builder_->createBinOp(spv::OpLogicalOr, type_bool_, alpha_test_result_non_not_equal,
                                      alpha_test_comparison_result);
          } else {
            alpha_test_result_non_not_equal = alpha_test_comparison_result;
          }
        }
      }
      if_alpha_test_function_is_not_equal.makeEndIf();
      spv::Id alpha_test_result = if_alpha_test_function_is_not_equal.createMergePhi(
          alpha_test_result_not_equal, alpha_test_result_non_not_equal);

      if (edram_fragment_shader_interlock_ && !features_.demote_to_helper_invocation) {
        fsi_pixel_potentially_killed = true;
        fsi_sample_mask_in_rt_0_alpha_tests =
            builder_->createTriOp(spv::OpSelect, type_uint_, alpha_test_result,
                                  fsi_sample_mask_in_rt_0_alpha_tests, const_uint_0_);
      } else {
        SpirvBuilder::IfBuilder alpha_test_kill_if(
            builder_->createUnaryOp(spv::OpLogicalNot, type_bool_, alpha_test_result),
            spv::SelectionControlDontFlattenMask, *builder_);
        bool branch_to_alpha_test_kill_merge = true;
        if (edram_fragment_shader_interlock_) {
          assert_true(features_.demote_to_helper_invocation);
          fsi_pixel_potentially_killed = true;

          builder_->addExtension("SPV_EXT_demote_to_helper_invocation");
          builder_->addCapability(spv::CapabilityDemoteToHelperInvocationEXT);
          builder_->createNoResultOp(spv::OpDemoteToHelperInvocationEXT);
        } else {
          builder_->createNoResultOp(spv::OpKill);

          branch_to_alpha_test_kill_merge = false;
        }
        alpha_test_kill_if.makeEndIf(branch_to_alpha_test_kill_merge);
      }
    }
    if_alpha_test_function_is_non_always.makeEndIf();

    FSI_AlphaToMask();

    if (block_rt_0_alpha_tests_rt_written_merge) {
      builder_->createBranch(block_rt_0_alpha_tests_rt_written_merge);
      spv::Block& block_rt_0_alpha_tests_rt_written_end = *builder_->getBuildPoint();
      builder_->setBuildPoint(block_rt_0_alpha_tests_rt_written_merge);
      if (edram_fragment_shader_interlock_ && !features_.demote_to_helper_invocation) {
        id_vector_temp_.clear();
        id_vector_temp_.push_back(fsi_sample_mask_in_rt_0_alpha_tests);
        id_vector_temp_.push_back(block_rt_0_alpha_tests_rt_written_end.getId());
        id_vector_temp_.push_back(main_fsi_sample_mask_);
        id_vector_temp_.push_back(block_rt_0_alpha_tests_rt_written_head->getId());
        main_fsi_sample_mask_ = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
      } else if (edram_fragment_shader_interlock_) {
        id_vector_temp_.clear();
        id_vector_temp_.push_back(main_fsi_sample_mask_);
        id_vector_temp_.push_back(block_rt_0_alpha_tests_rt_written_end.getId());
        id_vector_temp_.push_back(fsi_sample_mask_in_rt_0_alpha_tests);
        id_vector_temp_.push_back(block_rt_0_alpha_tests_rt_written_head->getId());
        main_fsi_sample_mask_ = builder_->createOp(spv::OpPhi, type_uint_, id_vector_temp_);
      }
    }
  }

  if (IsZpdTotal()) {
    FBO_AddMSAASamplesToZPDTotal();
  }

  spv::Block* block_fsi_if_after_kill = nullptr;
  spv::Block* block_fsi_if_after_kill_merge = nullptr;

  spv::Block* block_fsi_if_after_depth_stencil = nullptr;
  spv::Block* block_fsi_if_after_depth_stencil_merge = nullptr;

  if (edram_fragment_shader_interlock_) {
    if (fsi_pixel_potentially_killed) {
      if (features_.demote_to_helper_invocation) {
        id_vector_temp_.clear();

        main_fsi_sample_mask_ = builder_->createTriOp(
            spv::OpSelect, type_uint_,
            builder_->createOp(spv::OpIsHelperInvocationEXT, type_bool_, id_vector_temp_),
            const_uint_0_, main_fsi_sample_mask_);
      }

      spv::Id pixel_not_killed =
          builder_->createBinOp(spv::OpINotEqual, type_bool_, main_fsi_sample_mask_, const_uint_0_);
      block_fsi_if_after_kill = &builder_->makeNewBlock();
      block_fsi_if_after_kill_merge = &builder_->makeNewBlock();
      builder_->createSelectionMerge(block_fsi_if_after_kill_merge,
                                     spv::SelectionControlDontFlattenMask);
      builder_->createConditionalBranch(pixel_not_killed, block_fsi_if_after_kill,
                                        block_fsi_if_after_kill_merge);
      builder_->setBuildPoint(block_fsi_if_after_kill);
    }

    spv::Id color_write_depth_stencil_condition = spv::NoResult;
    if (FSI_IsDepthStencilEarly()) {
      for (uint32_t i = 0; i < fsi_sample_count; ++i) {
        spv::Id sample_late_depth_stencil_write_needed = builder_->createBinOp(
            spv::OpINotEqual, type_bool_,
            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_fsi_sample_mask_,
                                  builder_->makeUintConstant(uint32_t(1) << (4 + i))),
            const_uint_0_);
        SpirvBuilder::IfBuilder if_sample_late_depth_stencil_write_needed(
            sample_late_depth_stencil_write_needed, spv::SelectionControlDontFlattenMask,
            *builder_);
        spv::Id depth_stencil_sample_address = FSI_AddSampleOffset(main_fsi_address_depth_, i);
        id_vector_temp_.clear();

        id_vector_temp_.push_back(const_int_0_);
        id_vector_temp_.push_back(depth_stencil_sample_address);
        builder_->createStore(main_fsi_late_write_depth_stencil_[i],
                              builder_->createAccessChain(features_.spirv_version >= spv::Spv_1_3
                                                              ? spv::StorageClassStorageBuffer
                                                              : spv::StorageClassUniform,
                                                          buffer_edram_, id_vector_temp_));
        if_sample_late_depth_stencil_write_needed.makeEndIf();
      }
      if (color_targets_written) {
        color_write_depth_stencil_condition = builder_->createBinOp(
            spv::OpINotEqual, type_bool_,
            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_fsi_sample_mask_,
                                  builder_->makeUintConstant((uint32_t(1) << 4) - 1)),
            const_uint_0_);
      }
    } else {
      FSI_LoadEdramOffsets();

      builder_->createNoResultOp(spv::OpBeginInvocationInterlockEXT);

      FSI_DepthStencilTest(fsi_pixel_potentially_killed || (color_targets_written & 0b1));
      if (color_targets_written) {
        color_write_depth_stencil_condition = builder_->createBinOp(
            spv::OpINotEqual, type_bool_, main_fsi_sample_mask_, const_uint_0_);
      }
    }

    FSI_AddMSAASamplesToZPD(true, zpd_full_counters_ && !FSI_IsDepthStencilEarly());

    if (color_write_depth_stencil_condition != spv::NoResult) {
      block_fsi_if_after_depth_stencil = &builder_->makeNewBlock();
      block_fsi_if_after_depth_stencil_merge = &builder_->makeNewBlock();
      builder_->createSelectionMerge(block_fsi_if_after_depth_stencil_merge,
                                     spv::SelectionControlDontFlattenMask);
      builder_->createConditionalBranch(color_write_depth_stencil_condition,
                                        block_fsi_if_after_depth_stencil,
                                        block_fsi_if_after_depth_stencil_merge);
      builder_->setBuildPoint(block_fsi_if_after_depth_stencil);
    }
  }

  if (color_targets_written) {
    spv::Id fsi_color_targets_written = spv::NoResult;
    spv::Id fsi_const_int_1 = spv::NoResult;
    spv::Id fsi_const_edram_size_dwords = spv::NoResult;
    spv::Id fsi_samples_covered[4] = {};
    if (edram_fragment_shader_interlock_) {
      fsi_color_targets_written =
          builder_->createLoad(var_main_fsi_color_written_, spv::NoPrecision);
      fsi_const_int_1 = builder_->makeIntConstant(1);

      fsi_const_edram_size_dwords = builder_->makeUintConstant(
          xenos::kEdramTileWidthSamples * draw_resolution_scale_x_ *
          xenos::kEdramTileHeightSamples * draw_resolution_scale_y_ * xenos::kEdramTileCount);
      for (uint32_t i = 0; i < fsi_sample_count; ++i) {
        fsi_samples_covered[i] = builder_->createBinOp(
            spv::OpINotEqual, type_bool_,
            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_fsi_sample_mask_,
                                  builder_->makeUintConstant(uint32_t(1) << i)),
            const_uint_0_);
      }
    }
    uint32_t color_targets_remaining = color_targets_written;
    uint32_t color_target_index;
    while (rex::bit_scan_forward(color_targets_remaining, &color_target_index)) {
      color_targets_remaining &= ~(UINT32_C(1) << color_target_index);
      spv::Id color_variable = output_or_var_fragment_data_[color_target_index];
      spv::Id color = builder_->createLoad(color_variable, spv::NoPrecision);

      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantColorExpBias));
      id_vector_temp_.push_back(builder_->makeIntConstant(int32_t(color_target_index)));
      color = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, type_float4_, color,
          builder_->createLoad(
              builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                          id_vector_temp_),
              spv::NoPrecision));

      if (edram_fragment_shader_interlock_) {
        spv::Id fsi_color_written = builder_->createBinOp(
            spv::OpINotEqual, type_bool_,
            builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, fsi_color_targets_written,
                                  builder_->makeUintConstant(uint32_t(1) << color_target_index)),
            const_uint_0_);

        SpirvBuilder::IfBuilder if_fsi_color_written(
            fsi_color_written, spv::SelectionControlDontFlattenMask, *builder_, 2, 1);

        spv::Id rt_uint2_index_array = builder_->makeIntConstant(color_target_index >> 1);
        spv::Id rt_uint2_index_element[] = {
            builder_->makeIntConstant((color_target_index & 1) << 1),
            builder_->makeIntConstant(((color_target_index & 1) << 1) + 1),
        };

        id_vector_temp_.clear();
        id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramRTKeepMask));
        id_vector_temp_.push_back(rt_uint2_index_array);
        id_vector_temp_.push_back(rt_uint2_index_element[0]);
        spv::Id rt_keep_mask[2];
        rt_keep_mask[0] = builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                        id_vector_temp_),
            spv::NoPrecision);
        id_vector_temp_.back() = rt_uint2_index_element[1];
        rt_keep_mask[1] = builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                        id_vector_temp_),
            spv::NoPrecision);

        spv::Id const_uint32_max = builder_->makeUintConstant(UINT32_MAX);
        spv::Id rt_write_mask_not_empty = builder_->createBinOp(
            spv::OpLogicalOr, type_bool_,
            builder_->createBinOp(spv::OpINotEqual, type_bool_, rt_keep_mask[0], const_uint32_max),
            builder_->createBinOp(spv::OpINotEqual, type_bool_, rt_keep_mask[1], const_uint32_max));
        SpirvBuilder::IfBuilder if_rt_write_mask_not_empty(
            rt_write_mask_not_empty, spv::SelectionControlDontFlattenMask, *builder_);

        spv::Id const_int_rt_index = builder_->makeIntConstant(color_target_index);

        xenos::ColorRenderTargetFormat rt_format = FSI_GetRtFormat(color_target_index);
        uint32_t rt_format_flags = RenderTargetCache::AddPSIColorFormatFlags(rt_format);
        bool rt_is_64bpp = (rt_format_flags & RenderTargetCache::kPSIColorFormatFlag_64bpp) != 0;
        spv::Id rt_is_64bpp_id = builder_->makeBoolConstant(rt_is_64bpp);

        id_vector_temp_.clear();
        id_vector_temp_.push_back(
            builder_->makeIntConstant(kSystemConstantEdramRTBaseDwordsScaled));
        id_vector_temp_.push_back(const_int_rt_index);

        spv::Id rt_sample_0_address = builder_->createUnaryOp(
            spv::OpBitcast, type_int_,
            builder_->createBinOp(
                spv::OpUMod, type_uint_,
                builder_->createBinOp(
                    spv::OpIAdd, type_uint_,
                    builder_->createLoad(
                        builder_->createAccessChain(spv::StorageClassUniform,
                                                    uniform_system_constants_, id_vector_temp_),
                        spv::NoPrecision),
                    builder_->createTriOp(spv::OpSelect, type_uint_, rt_is_64bpp_id,
                                          main_fsi_offset_64bpp_, main_fsi_offset_32bpp_)),
                fsi_const_edram_size_dwords));

        auto emit_overwrite_path = [&]() {
          {
            std::array<spv::Id, 2> color_packed = FSI_ClampAndPackColor(color, rt_format);

            spv::Id rt_keep_mask_not_empty = builder_->createBinOp(
                spv::OpLogicalOr, type_bool_,
                builder_->createBinOp(spv::OpINotEqual, type_bool_, rt_keep_mask[0], const_uint_0_),
                builder_->createBinOp(spv::OpINotEqual, type_bool_, rt_keep_mask[1],
                                      const_uint_0_));

            SpirvBuilder::IfBuilder if_rt_keep_mask_not_empty(
                rt_keep_mask_not_empty, spv::SelectionControlDontFlattenMask, *builder_);
            {
              std::array<spv::Id, 2> color_packed_masked;
              for (uint32_t i = 0; i < 2; ++i) {
                color_packed_masked[i] = builder_->createBinOp(
                    spv::OpBitwiseAnd, type_uint_, color_packed[i],
                    builder_->createUnaryOp(spv::OpNot, type_uint_, rt_keep_mask[i]));
              }
              for (uint32_t i = 0; i < fsi_sample_count; ++i) {
                SpirvBuilder::IfBuilder if_sample_covered(
                    fsi_samples_covered[i], spv::SelectionControlDontFlattenMask, *builder_);
                spv::Id rt_sample_address =
                    FSI_AddSampleOffset(rt_sample_0_address, i, rt_is_64bpp_id);
                id_vector_temp_.clear();

                id_vector_temp_.push_back(const_int_0_);
                id_vector_temp_.push_back(rt_sample_address);
                spv::Id rt_access_chain_0 = builder_->createAccessChain(
                    features_.spirv_version >= spv::Spv_1_3 ? spv::StorageClassStorageBuffer
                                                            : spv::StorageClassUniform,
                    buffer_edram_, id_vector_temp_);
                builder_->createStore(
                    builder_->createBinOp(
                        spv::OpBitwiseOr, type_uint_,
                        builder_->createBinOp(
                            spv::OpBitwiseAnd, type_uint_,
                            builder_->createLoad(rt_access_chain_0, spv::NoPrecision),
                            rt_keep_mask[0]),
                        color_packed_masked[0]),
                    rt_access_chain_0);
                if (rt_is_64bpp) {
                  id_vector_temp_.back() = builder_->createBinOp(
                      spv::OpIAdd, type_int_, rt_sample_address, fsi_const_int_1);
                  spv::Id rt_access_chain_1 = builder_->createAccessChain(
                      features_.spirv_version >= spv::Spv_1_3 ? spv::StorageClassStorageBuffer
                                                              : spv::StorageClassUniform,
                      buffer_edram_, id_vector_temp_);
                  builder_->createStore(
                      builder_->createBinOp(
                          spv::OpBitwiseOr, type_uint_,
                          builder_->createBinOp(
                              spv::OpBitwiseAnd, type_uint_,
                              builder_->createLoad(rt_access_chain_1, spv::NoPrecision),
                              rt_keep_mask[1]),
                          color_packed_masked[1]),
                      rt_access_chain_1);
                }
                if_sample_covered.makeEndIf();
              }
            }
            if_rt_keep_mask_not_empty.makeBeginElse();
            {
              for (uint32_t i = 0; i < fsi_sample_count; ++i) {
                SpirvBuilder::IfBuilder if_sample_covered(
                    fsi_samples_covered[i], spv::SelectionControlDontFlattenMask, *builder_);
                spv::Id rt_sample_address =
                    FSI_AddSampleOffset(rt_sample_0_address, i, rt_is_64bpp_id);
                id_vector_temp_.clear();

                id_vector_temp_.push_back(const_int_0_);
                id_vector_temp_.push_back(rt_sample_address);
                builder_->createStore(color_packed[0], builder_->createAccessChain(
                                                           features_.spirv_version >= spv::Spv_1_3
                                                               ? spv::StorageClassStorageBuffer
                                                               : spv::StorageClassUniform,
                                                           buffer_edram_, id_vector_temp_));
                if (rt_is_64bpp) {
                  id_vector_temp_.back() = builder_->createBinOp(
                      spv::OpIAdd, type_int_, id_vector_temp_.back(), fsi_const_int_1);
                  builder_->createStore(color_packed[1], builder_->createAccessChain(
                                                             features_.spirv_version >= spv::Spv_1_3
                                                                 ? spv::StorageClassStorageBuffer
                                                                 : spv::StorageClassUniform,
                                                             buffer_edram_, id_vector_temp_));
                }
                if_sample_covered.makeEndIf();
              }
            }
            if_rt_keep_mask_not_empty.makeEndIf();
          }
        };
        if (FSI_GetNoBlending()) {
          emit_overwrite_path();
        } else {
          id_vector_temp_.clear();
          id_vector_temp_.push_back(
              builder_->makeIntConstant(kSystemConstantEdramRTBlendFactorsOps));
          id_vector_temp_.push_back(const_int_rt_index);
          spv::Id rt_blend_factors_equations = builder_->createLoad(
              builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                          id_vector_temp_),
              spv::NoPrecision);

          spv::Id rt_blend_enabled =
              builder_->createBinOp(spv::OpINotEqual, type_bool_, rt_blend_factors_equations,
                                    builder_->makeUintConstant(0x00010001));
          SpirvBuilder::IfBuilder if_rt_blend_enabled(
              rt_blend_enabled, spv::SelectionControlDontFlattenMask, *builder_);
          {
            spv::Id rt_color_is_fixed_point = builder_->makeBoolConstant(
                (rt_format_flags & RenderTargetCache::kPSIColorFormatFlag_FixedPointColor) != 0);
            spv::Id rt_alpha_is_fixed_point = builder_->makeBoolConstant(
                (rt_format_flags & RenderTargetCache::kPSIColorFormatFlag_FixedPointAlpha) != 0);
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramRTClamp));
            id_vector_temp_.push_back(const_int_rt_index);
            spv::Id rt_clamp = builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                            id_vector_temp_),
                spv::NoPrecision);
            spv::Id rt_clamp_color_min = builder_->smearScalar(
                spv::NoPrecision, builder_->createCompositeExtract(rt_clamp, type_float_, 0),
                type_float3_);
            spv::Id rt_clamp_alpha_min = builder_->createCompositeExtract(rt_clamp, type_float_, 1);
            spv::Id rt_clamp_color_max = builder_->smearScalar(
                spv::NoPrecision, builder_->createCompositeExtract(rt_clamp, type_float_, 2),
                type_float3_);
            spv::Id rt_clamp_alpha_max = builder_->createCompositeExtract(rt_clamp, type_float_, 3);

            spv::Id blend_factor_width = builder_->makeUintConstant(5);
            spv::Id blend_equation_width = builder_->makeUintConstant(3);
            spv::Id rt_color_source_factor = builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, rt_blend_factors_equations, const_uint_0_,
                blend_factor_width);
            spv::Id rt_color_equation = builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, rt_blend_factors_equations, blend_factor_width,
                blend_equation_width);
            spv::Id rt_color_dest_factor = builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, rt_blend_factors_equations,
                builder_->makeUintConstant(8), blend_factor_width);
            spv::Id rt_alpha_source_factor = builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, rt_blend_factors_equations,
                builder_->makeUintConstant(16), blend_factor_width);
            spv::Id rt_alpha_equation = builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, rt_blend_factors_equations,
                builder_->makeUintConstant(21), blend_equation_width);
            spv::Id rt_alpha_dest_factor = builder_->createTriOp(
                spv::OpBitFieldUExtract, type_uint_, rt_blend_factors_equations,
                builder_->makeUintConstant(24), blend_factor_width);

            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->makeIntConstant(kSystemConstantEdramBlendConstant));
            spv::Id blend_constant_unclamped = builder_->createLoad(
                builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                            id_vector_temp_),
                spv::NoPrecision);
            uint_vector_temp_.clear();
            uint_vector_temp_.push_back(0);
            uint_vector_temp_.push_back(1);
            uint_vector_temp_.push_back(2);
            spv::Id blend_constant_color_unclamped = builder_->createRvalueSwizzle(
                spv::NoPrecision, type_float3_, blend_constant_unclamped, uint_vector_temp_);
            spv::Id blend_constant_color_clamped = FSI_FlushNaNClampAndInBlending(
                blend_constant_color_unclamped, rt_color_is_fixed_point, rt_clamp_color_min,
                rt_clamp_color_max);
            spv::Id blend_constant_alpha_clamped = FSI_FlushNaNClampAndInBlending(
                builder_->createCompositeExtract(blend_constant_unclamped, type_float_, 3),
                rt_alpha_is_fixed_point, rt_clamp_alpha_min, rt_clamp_alpha_max);

            uint_vector_temp_.clear();
            uint_vector_temp_.push_back(0);
            uint_vector_temp_.push_back(1);
            uint_vector_temp_.push_back(2);
            spv::Id source_color_unclamped = builder_->createRvalueSwizzle(
                spv::NoPrecision, type_float3_, color, uint_vector_temp_);
            spv::Id source_color_clamped =
                FSI_FlushNaNClampAndInBlending(source_color_unclamped, rt_color_is_fixed_point,
                                               rt_clamp_color_min, rt_clamp_color_max);
            spv::Id source_alpha_clamped = FSI_FlushNaNClampAndInBlending(
                builder_->createCompositeExtract(color, type_float_, 3), rt_alpha_is_fixed_point,
                rt_clamp_alpha_min, rt_clamp_alpha_max);

            std::array<spv::Id, 2> rt_replace_mask;
            for (uint32_t i = 0; i < 2; ++i) {
              rt_replace_mask[i] = builder_->createUnaryOp(spv::OpNot, type_uint_, rt_keep_mask[i]);
            }

            for (uint32_t i = 0; i < fsi_sample_count; ++i) {
              SpirvBuilder::IfBuilder if_sample_covered(
                  fsi_samples_covered[i], spv::SelectionControlDontFlattenMask, *builder_);

              spv::Id rt_sample_address =
                  FSI_AddSampleOffset(rt_sample_0_address, i, rt_is_64bpp_id);
              id_vector_temp_.clear();

              id_vector_temp_.push_back(const_int_0_);
              id_vector_temp_.push_back(rt_sample_address);
              spv::Id rt_access_chain_0 = builder_->createAccessChain(
                  features_.spirv_version >= spv::Spv_1_3 ? spv::StorageClassStorageBuffer
                                                          : spv::StorageClassUniform,
                  buffer_edram_, id_vector_temp_);
              id_vector_temp_.back() =
                  builder_->createBinOp(spv::OpIAdd, type_int_, rt_sample_address, fsi_const_int_1);
              spv::Id rt_access_chain_1 = builder_->createAccessChain(
                  features_.spirv_version >= spv::Spv_1_3 ? spv::StorageClassStorageBuffer
                                                          : spv::StorageClassUniform,
                  buffer_edram_, id_vector_temp_);

              std::array<spv::Id, 2> dest_packed;
              dest_packed[0] = builder_->createLoad(rt_access_chain_0, spv::NoPrecision);
              dest_packed[1] = rt_is_64bpp
                                   ? builder_->createLoad(rt_access_chain_1, spv::NoPrecision)
                                   : const_uint_0_;
              std::array<spv::Id, 4> dest_unpacked = FSI_UnpackColor(dest_packed, rt_format);
              id_vector_temp_.clear();
              id_vector_temp_.push_back(dest_unpacked[0]);
              id_vector_temp_.push_back(dest_unpacked[1]);
              id_vector_temp_.push_back(dest_unpacked[2]);
              spv::Id dest_color =
                  builder_->createCompositeConstruct(type_float3_, id_vector_temp_);

              spv::Id result_color = FSI_BlendColorOrAlphaWithUnclampedResult(
                  rt_color_is_fixed_point, rt_clamp_color_min, rt_clamp_color_max,
                  source_color_clamped, source_alpha_clamped, dest_color, dest_unpacked[3],
                  blend_constant_color_clamped, blend_constant_alpha_clamped, rt_color_equation,
                  rt_color_source_factor, rt_color_dest_factor);
              spv::Id result_alpha = FSI_BlendColorOrAlphaWithUnclampedResult(
                  rt_alpha_is_fixed_point, rt_clamp_alpha_min, rt_clamp_alpha_max, spv::NoResult,
                  source_alpha_clamped, spv::NoResult, dest_unpacked[3], spv::NoResult,
                  blend_constant_alpha_clamped, rt_alpha_equation, rt_alpha_source_factor,
                  rt_alpha_dest_factor);

              spv::Id result_float4;
              {
                std::unique_ptr<spv::Instruction> result_composite_construct_op =
                    std::make_unique<spv::Instruction>(builder_->getUniqueId(), type_float4_,
                                                       spv::OpCompositeConstruct);
                result_composite_construct_op->addIdOperand(result_color);
                result_composite_construct_op->addIdOperand(result_alpha);
                result_float4 = result_composite_construct_op->getResultId();
                builder_->getBuildPoint()->addInstruction(std::move(result_composite_construct_op));
              }
              std::array<spv::Id, 2> result_packed =
                  FSI_ClampAndPackColor(result_float4, rt_format);
              builder_->createStore(
                  builder_->createBinOp(
                      spv::OpBitwiseOr, type_uint_,
                      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, dest_packed[0],
                                            rt_keep_mask[0]),
                      builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, result_packed[0],
                                            rt_replace_mask[0])),
                  rt_access_chain_0);
              if (rt_is_64bpp) {
                builder_->createStore(
                    builder_->createBinOp(
                        spv::OpBitwiseOr, type_uint_,
                        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, dest_packed[1],
                                              rt_keep_mask[1]),
                        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, result_packed[1],
                                              rt_replace_mask[1])),
                    rt_access_chain_1);
              }

              if_sample_covered.makeEndIf();
            }
          }
          if_rt_blend_enabled.makeBeginElse();
          emit_overwrite_path();
          if_rt_blend_enabled.makeEndIf();
        }

        if_rt_write_mask_not_empty.makeEndIf();
        if_fsi_color_written.makeEndIf();
      } else {
        uint_vector_temp_.clear();
        uint_vector_temp_.push_back(0);
        uint_vector_temp_.push_back(1);
        uint_vector_temp_.push_back(2);
        spv::Id color_rgb =
            builder_->createRvalueSwizzle(spv::NoPrecision, type_float3_, color, uint_vector_temp_);
        spv::Id is_gamma = builder_->createBinOp(
            spv::OpINotEqual, type_bool_,
            builder_->createBinOp(
                spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                builder_->makeUintConstant(kSysFlag_ConvertColor0ToGamma << color_target_index)),
            const_uint_0_);
        SpirvBuilder::IfBuilder if_gamma(is_gamma, spv::SelectionControlDontFlattenMask, *builder_);
        spv::Id color_rgb_gamma = SpirvShaderTranslator::LinearToPWLGamma(
            builder_.get(), color_rgb, false, ext_inst_glsl_std_450_);
        if_gamma.makeEndIf();
        color_rgb = if_gamma.createMergePhi(color_rgb_gamma, color_rgb);
        {
          std::unique_ptr<spv::Instruction> color_rgba_shuffle_op =
              std::make_unique<spv::Instruction>(builder_->getUniqueId(), type_float4_,
                                                 spv::OpVectorShuffle);
          color_rgba_shuffle_op->addIdOperand(color_rgb);
          color_rgba_shuffle_op->addIdOperand(color);
          color_rgba_shuffle_op->addImmediateOperand(0);
          color_rgba_shuffle_op->addImmediateOperand(1);
          color_rgba_shuffle_op->addImmediateOperand(2);
          color_rgba_shuffle_op->addImmediateOperand(3 + 3);
          color = color_rgba_shuffle_op->getResultId();
          builder_->getBuildPoint()->addInstruction(std::move(color_rgba_shuffle_op));
        }

        builder_->createStore(color, color_variable);
      }
    }
  }

  if (!edram_fragment_shader_interlock_) {
    Modification shader_modification = GetHostRtShaderModification();
    xenos::BlendFactor rt0_rgb_premult_factor =
        shader_modification.pixel.rt0_blend_rgb_factor_for_premult;
    xenos::BlendFactor rt0_a_premult_factor =
        shader_modification.pixel.rt0_blend_a_factor_for_premult;

    uint32_t color_targets_to_copy = current_shader().writes_color_targets();
    uint32_t color_target_index;
    while (rex::bit_scan_forward(color_targets_to_copy, &color_target_index)) {
      color_targets_to_copy &= ~(UINT32_C(1) << color_target_index);
      spv::Id var_color = output_or_var_fragment_data_[color_target_index];
      spv::Id out_color = output_fragment_data_[color_target_index];
      if (var_color != spv::NoResult && out_color != spv::NoResult) {
        spv::Id color = builder_->createLoad(var_color, spv::NoPrecision);

        if (color_target_index == 0 && (rt0_rgb_premult_factor != xenos::BlendFactor::kOne ||
                                        rt0_a_premult_factor != xenos::BlendFactor::kOne)) {
          auto extract_rgb = [&](spv::Id vec4) -> spv::Id {
            uint_vector_temp_.clear();
            uint_vector_temp_.push_back(0);
            uint_vector_temp_.push_back(1);
            uint_vector_temp_.push_back(2);
            return builder_->createRvalueSwizzle(spv::NoPrecision, type_float3_, vec4,
                                                 uint_vector_temp_);
          };

          auto get_factor_value = [&](xenos::BlendFactor factor, bool for_alpha) -> spv::Id {
            spv::Id src_color = color;
            switch (factor) {
              case xenos::BlendFactor::kZero:
                return for_alpha ? const_float_0_ : const_float3_0_;
              case xenos::BlendFactor::kOne:
                return for_alpha ? const_float_1_ : const_float3_1_;
              case xenos::BlendFactor::kSrcColor:
                return for_alpha ? builder_->createCompositeExtract(src_color, type_float_, 3)
                                 : extract_rgb(src_color);
              case xenos::BlendFactor::kOneMinusSrcColor: {
                spv::Id src = for_alpha
                                  ? builder_->createCompositeExtract(src_color, type_float_, 3)
                                  : extract_rgb(src_color);
                spv::Id one = for_alpha ? const_float_1_ : const_float3_1_;
                return builder_->createBinOp(spv::OpFSub, for_alpha ? type_float_ : type_float3_,
                                             one, src);
              }
              case xenos::BlendFactor::kSrcAlpha: {
                spv::Id alpha = builder_->createCompositeExtract(src_color, type_float_, 3);
                if (for_alpha) {
                  return alpha;
                }
                return builder_->smearScalar(spv::NoPrecision, alpha, type_float3_);
              }
              case xenos::BlendFactor::kOneMinusSrcAlpha: {
                spv::Id alpha = builder_->createCompositeExtract(src_color, type_float_, 3);
                spv::Id one_minus_alpha =
                    builder_->createBinOp(spv::OpFSub, type_float_, const_float_1_, alpha);
                if (for_alpha) {
                  return one_minus_alpha;
                }
                return builder_->smearScalar(spv::NoPrecision, one_minus_alpha, type_float3_);
              }
              case xenos::BlendFactor::kConstantColor:
              case xenos::BlendFactor::kConstantAlpha: {
                id_vector_temp_.clear();
                id_vector_temp_.push_back(
                    builder_->makeIntConstant(kSystemConstantEdramBlendConstant));
                spv::Id blend_constant = builder_->createLoad(
                    builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                                id_vector_temp_),
                    spv::NoPrecision);
                if (factor == xenos::BlendFactor::kConstantAlpha) {
                  spv::Id alpha = builder_->createCompositeExtract(blend_constant, type_float_, 3);
                  if (for_alpha) {
                    return alpha;
                  }
                  return builder_->smearScalar(spv::NoPrecision, alpha, type_float3_);
                }
                if (for_alpha) {
                  return builder_->createCompositeExtract(blend_constant, type_float_, 3);
                }
                return extract_rgb(blend_constant);
              }
              case xenos::BlendFactor::kOneMinusConstantColor:
              case xenos::BlendFactor::kOneMinusConstantAlpha: {
                id_vector_temp_.clear();
                id_vector_temp_.push_back(
                    builder_->makeIntConstant(kSystemConstantEdramBlendConstant));
                spv::Id blend_constant = builder_->createLoad(
                    builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                                id_vector_temp_),
                    spv::NoPrecision);
                spv::Id constant_value;
                if (factor == xenos::BlendFactor::kOneMinusConstantAlpha) {
                  spv::Id alpha = builder_->createCompositeExtract(blend_constant, type_float_, 3);
                  if (for_alpha) {
                    constant_value = alpha;
                  } else {
                    constant_value = builder_->smearScalar(spv::NoPrecision, alpha, type_float3_);
                  }
                } else {
                  if (for_alpha) {
                    constant_value =
                        builder_->createCompositeExtract(blend_constant, type_float_, 3);
                  } else {
                    constant_value = extract_rgb(blend_constant);
                  }
                }
                spv::Id one = for_alpha ? const_float_1_ : const_float3_1_;
                return builder_->createBinOp(spv::OpFSub, for_alpha ? type_float_ : type_float3_,
                                             one, constant_value);
              }
              default:

                return for_alpha ? const_float_1_ : const_float3_1_;
            }
          };

          if (rt0_rgb_premult_factor != xenos::BlendFactor::kOne) {
            spv::Id rgb_factor = get_factor_value(rt0_rgb_premult_factor, false);
            spv::Id rgb = extract_rgb(color);
            rgb = builder_->createBinOp(spv::OpFMul, type_float3_, rgb, rgb_factor);

            spv::Id alpha = builder_->createCompositeExtract(color, type_float_, 3);
            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->createCompositeExtract(rgb, type_float_, 0));
            id_vector_temp_.push_back(builder_->createCompositeExtract(rgb, type_float_, 1));
            id_vector_temp_.push_back(builder_->createCompositeExtract(rgb, type_float_, 2));
            id_vector_temp_.push_back(alpha);
            color = builder_->createCompositeConstruct(type_float4_, id_vector_temp_);
          }

          if (rt0_a_premult_factor != xenos::BlendFactor::kOne) {
            spv::Id a_factor = get_factor_value(rt0_a_premult_factor, true);
            spv::Id alpha = builder_->createCompositeExtract(color, type_float_, 3);
            alpha = builder_->createBinOp(spv::OpFMul, type_float_, alpha, a_factor);

            id_vector_temp_.clear();
            id_vector_temp_.push_back(builder_->createCompositeExtract(color, type_float_, 0));
            id_vector_temp_.push_back(builder_->createCompositeExtract(color, type_float_, 1));
            id_vector_temp_.push_back(builder_->createCompositeExtract(color, type_float_, 2));
            id_vector_temp_.push_back(alpha);
            color = builder_->createCompositeConstruct(type_float4_, id_vector_temp_);
          }
        }

        builder_->createStore(color, out_color);
      }
    }
  }

  CompleteFragmentShader_DSV_DepthTo24Bit();

  if (edram_fragment_shader_interlock_) {
    if (block_fsi_if_after_depth_stencil_merge) {
      builder_->createBranch(block_fsi_if_after_depth_stencil_merge);
      builder_->setBuildPoint(block_fsi_if_after_depth_stencil_merge);
    }

    if (block_fsi_if_after_kill_merge) {
      builder_->createBranch(block_fsi_if_after_kill_merge);
      builder_->setBuildPoint(block_fsi_if_after_kill_merge);
    }

    if (FSI_IsDepthStencilEarly()) {
      builder_->createBranch(main_fsi_early_depth_stencil_execute_quad_merge_);
      builder_->setBuildPoint(main_fsi_early_depth_stencil_execute_quad_merge_);
    }

    builder_->createNoResultOp(spv::OpEndInvocationInterlockEXT);
  }
}

void SpirvShaderTranslator::CompleteFragmentShader_DSV_DepthTo24Bit() {
  if (edram_fragment_shader_interlock_ || output_fragment_depth_ == spv::NoResult) {
    return;
  }
  bool shader_writes_depth = current_shader().writes_depth();
  bool is_float24 = DSV_IsWritingFloat24Depth();
  bool apply_polygon_offset = DSV_IsApplyingPolygonOffset() && !shader_writes_depth;
  assert_true(shader_writes_depth || is_float24 || apply_polygon_offset);

  spv::Id depth_value;
  if (shader_writes_depth) {
    depth_value = builder_->createLoad(output_or_var_fragment_depth_, spv::NoPrecision);
  } else {
    spv::Id host_depth;
    if (apply_polygon_offset) {
      assert_true(input_front_facing_ != spv::NoResult);
      assert_true(main_fbo_depth_unbiased_ != spv::NoResult);
      assert_true(main_fbo_depth_derivatives_[0] != spv::NoResult);
      assert_true(main_fbo_depth_derivatives_[1] != spv::NoResult);
      auto load_system_constant_float = [&](SystemConstantIndex index) {
        id_vector_temp_.clear();
        id_vector_temp_.push_back(builder_->makeIntConstant(index));
        return builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                        id_vector_temp_),
            spv::NoPrecision);
      };
      spv::Id depth_dx = builder_->createUnaryBuiltinCall(
          type_float_, ext_inst_glsl_std_450_, GLSLstd450FAbs, main_fbo_depth_derivatives_[0]);
      spv::Id depth_dy = builder_->createUnaryBuiltinCall(
          type_float_, ext_inst_glsl_std_450_, GLSLstd450FAbs, main_fbo_depth_derivatives_[1]);
      spv::Id depth_max_slope = builder_->createBinBuiltinCall(type_float_, ext_inst_glsl_std_450_,
                                                               GLSLstd450FMax, depth_dx, depth_dy);
      spv::Id front_facing = builder_->createLoad(input_front_facing_, spv::NoPrecision);
      spv::Id poly_offset_scale = builder_->createTriOp(
          spv::OpSelect, type_float_, front_facing,
          load_system_constant_float(kSystemConstantEdramPolyOffsetFrontScale),
          load_system_constant_float(kSystemConstantEdramPolyOffsetBackScale));
      spv::Id poly_offset_offset = builder_->createTriOp(
          spv::OpSelect, type_float_, front_facing,
          load_system_constant_float(kSystemConstantEdramPolyOffsetFrontOffset),
          load_system_constant_float(kSystemConstantEdramPolyOffsetBackOffset));
      spv::Id poly_offset = builder_->createNoContractionBinOp(
          spv::OpFAdd, type_float_,
          builder_->createNoContractionBinOp(spv::OpFMul, type_float_, depth_max_slope,
                                             poly_offset_scale),
          poly_offset_offset);
      host_depth = builder_->createNoContractionBinOp(spv::OpFAdd, type_float_,
                                                      main_fbo_depth_unbiased_, poly_offset);
    } else {
      assert_true(input_fragment_coordinates_ != spv::NoResult);
      id_vector_temp_.clear();
      id_vector_temp_.push_back(builder_->makeIntConstant(2));
      host_depth = builder_->createLoad(
          builder_->createAccessChain(spv::StorageClassInput, input_fragment_coordinates_,
                                      id_vector_temp_),
          spv::NoPrecision);
    }
    if (is_float24) {
      depth_value = builder_->createBinOp(spv::OpFMul, type_float_, host_depth,
                                          builder_->makeFloatConstant(2.0f));
      depth_value =
          builder_->createTriBuiltinCall(type_float_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
                                         depth_value, const_float_0_, const_float_1_);
    } else {
      depth_value = host_depth;
    }
  }

  if (!is_float24) {
    if (!shader_writes_depth) {
      builder_->createStore(depth_value, output_fragment_depth_);
      return;
    }

    spv::Id depth_float24_flag = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, main_system_constant_flags_,
                              builder_->makeUintConstant(kSysFlag_DepthFloat24)),
        const_uint_0_);
    spv::Id depth_scaled = builder_->createBinOp(spv::OpFMul, type_float_, depth_value,
                                                 builder_->makeFloatConstant(0.5f));
    spv::Id depth_remapped = builder_->createTriOp(spv::OpSelect, type_float_, depth_float24_flag,
                                                   depth_scaled, depth_value);
    builder_->createStore(depth_remapped, output_fragment_depth_);
    return;
  }

  Modification::DepthStencilMode mode = GetHostRtShaderModification().pixel.depth_stencil_mode;
  if (mode == Modification::DepthStencilMode::kFloat24Truncating ||
      mode == Modification::DepthStencilMode::kFloat24TruncatingPolygonOffset) {
    spv::Id depth_uint = builder_->createUnaryOp(spv::OpBitcast, type_uint_, depth_value);

    spv::Id representable = builder_->createBinOp(spv::OpUGreaterThanEqual, type_bool_, depth_uint,
                                                  builder_->makeUintConstant(0x2E800000));
    SpirvBuilder::IfBuilder representable_if(representable, spv::SelectionControlDontFlattenMask,
                                             *builder_);
    {
      spv::Id exponent =
          builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, depth_uint,
                                builder_->makeUintConstant(23), builder_->makeUintConstant(8));

      spv::Id trunc_bits_signed =
          builder_->createBinOp(spv::OpISub, type_int_, builder_->makeIntConstant(116),
                                builder_->createUnaryOp(spv::OpBitcast, type_int_, exponent));
      trunc_bits_signed =
          builder_->createBinBuiltinCall(type_int_, ext_inst_glsl_std_450_, GLSLstd450SMax,
                                         trunc_bits_signed, builder_->makeIntConstant(3));
      spv::Id trunc_bits = builder_->createUnaryOp(spv::OpBitcast, type_uint_, trunc_bits_signed);
      spv::Id truncated_uint = builder_->createQuadOp(spv::OpBitFieldInsert, type_uint_, depth_uint,
                                                      builder_->makeUintConstant(0),
                                                      builder_->makeUintConstant(0), trunc_bits);
      spv::Id truncated_f32 = builder_->createUnaryOp(spv::OpBitcast, type_float_, truncated_uint);
      spv::Id remapped = builder_->createBinOp(spv::OpFMul, type_float_, truncated_f32,
                                               builder_->makeFloatConstant(0.5f));
      builder_->createStore(remapped, output_fragment_depth_);
    }
    representable_if.makeBeginElse();
    { builder_->createStore(const_float_0_, output_fragment_depth_); }
    representable_if.makeEndIf();
  } else {
    spv::Id f24_uint =
        PreClampedDepthTo20e4(*builder_, depth_value, true, false, ext_inst_glsl_std_450_);
    spv::Id depth_f32 = Depth20e4To32(*builder_, f24_uint, 0, true, false, ext_inst_glsl_std_450_);
    builder_->createStore(depth_f32, output_fragment_depth_);
  }
}

spv::Id SpirvShaderTranslator::LoadMsaaSamplesFromFlags() {
  return builder_->createTriOp(spv::OpBitFieldUExtract, type_uint_, main_system_constant_flags_,
                               builder_->makeUintConstant(kSysFlag_MsaaSamples_Shift),
                               builder_->makeUintConstant(2));
}

}
