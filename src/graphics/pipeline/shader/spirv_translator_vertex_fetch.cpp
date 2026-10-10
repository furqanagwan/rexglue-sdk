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
#include <climits>
#include <cmath>
#include <fmt/format.h>
#include <SPIRV/GLSL.std.450.h>
#include <rex/assert.h>
#include <rex/math.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/spirv_compatibility.h>

namespace rex::graphics {

bool SpirvShaderTranslator::IsGuestPixelCenterFetchNeeded() const {
  return is_pixel_shader() && !is_depth_only_fragment_shader_ &&
         (GetCurrentDrawResolutionScaleX() > 1 || GetCurrentDrawResolutionScaleY() > 1) &&
         (current_shader().point_fetch_coordinate_registers() & GetModificationInterpolatorMask());
}

void SpirvShaderTranslator::ProcessVertexFetchInstruction(
    const ParsedVertexFetchInstruction& instr) {
  if (BisectSkipsInstruction()) {
    return;
  }
  UpdateInstructionPredication(instr.is_predicated, instr.predicate_condition);

  uint32_t used_result_components = instr.result.GetUsedResultComponents();
  uint32_t needed_words =
      xenos::GetVertexFormatNeededWords(instr.attributes.data_format, used_result_components);

  if (!needed_words && instr.is_mini_fetch) {
    StoreResult(instr.result, spv::NoResult);
    return;
  }

  EnsureBuildPointAvailable();

  uint32_t fetch_constant_word_0_index = instr.operands[1].storage_index << 1;
  uint32_t fetch_constant_word_1_index = fetch_constant_word_0_index + 1;

  id_vector_temp_.clear();

  id_vector_temp_.push_back(const_int_0_);

  id_vector_temp_.push_back(builder_->makeIntConstant(int(fetch_constant_word_1_index >> 2)));

  id_vector_temp_.push_back(builder_->makeIntConstant(int(fetch_constant_word_1_index & 3)));
  spv::Id fetch_constant_word_1 =
      builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                       uniform_fetch_constants_, id_vector_temp_),
                           spv::NoPrecision);

  spv::Id address;

  spv::Id fetch_end;
  if (instr.is_mini_fetch) {
    address = builder_->createLoad(var_main_vfetch_address_, spv::NoPrecision);
    fetch_end = builder_->createLoad(var_main_vfetch_bound_, spv::NoPrecision);
  } else {
    id_vector_temp_.clear();

    id_vector_temp_.push_back(const_int_0_);

    id_vector_temp_.push_back(builder_->makeIntConstant(int(fetch_constant_word_0_index >> 2)));

    id_vector_temp_.push_back(builder_->makeIntConstant(int(fetch_constant_word_0_index & 3)));
    spv::Id fetch_constant_word_0 =
        builder_->createLoad(builder_->createAccessChain(spv::StorageClassUniform,
                                                         uniform_fetch_constants_, id_vector_temp_),
                             spv::NoPrecision);

    address = builder_->createUnaryOp(
        spv::OpBitcast, type_int_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint_,
            builder_->createBinOp(spv::OpShiftRightLogical, type_uint_, fetch_constant_word_0,
                                  builder_->makeUintConstant(2)),
            builder_->makeUintConstant(0x1FFFFFFF >> 2)));

    fetch_end = builder_->createBinOp(
        spv::OpIAdd, type_int_, address,
        builder_->createUnaryOp(
            spv::OpBitcast, type_int_,
            builder_->createBinOp(
                spv::OpBitwiseAnd, type_uint_,
                builder_->createBinOp(spv::OpShiftRightLogical, type_uint_, fetch_constant_word_1,
                                      builder_->makeUintConstant(2)),
                builder_->makeUintConstant((uint32_t(1) << 24) - 1))));
    builder_->createStore(fetch_end, var_main_vfetch_bound_);
    if (instr.attributes.stride) {
      spv::Id index =
          GetOperandComponents(LoadOperandStorage(instr.operands[0]), instr.operands[0], 0b0001);
      if (instr.attributes.is_index_rounded) {
        index = builder_->createNoContractionBinOp(spv::OpFAdd, type_float_, index,
                                                   builder_->makeFloatConstant(0.5f));
      }
      index =
          builder_->createUnaryOp(spv::OpConvertFToS, type_int_,
                                  builder_->createUnaryBuiltinCall(
                                      type_float_, ext_inst_glsl_std_450_, GLSLstd450Floor, index));
      if (instr.attributes.stride > 1) {
        index = builder_->createBinOp(spv::OpIMul, type_int_, index,
                                      builder_->makeIntConstant(int(instr.attributes.stride)));
      }
      address = builder_->createBinOp(spv::OpIAdd, type_int_, address, index);
    }

    builder_->createStore(address, var_main_vfetch_address_);
  }

  if (!needed_words) {
    StoreResult(instr.result, spv::NoResult);
    return;
  }

  unsigned int word_composite_indices[4] = {};
  spv::Id word_composite_constituents[4];
  uint32_t word_count = 0;
  uint32_t words_remaining = needed_words;
  uint32_t word_index;
  while (rex::bit_scan_forward(words_remaining, &word_index)) {
    words_remaining &= ~(1 << word_index);
    spv::Id word_address = address;

    int32_t word_offset = instr.attributes.offset + word_index;
    if (word_offset) {
      word_address = builder_->createBinOp(spv::OpIAdd, type_int_, word_address,
                                           builder_->makeIntConstant(int(word_offset)));
    }
    word_composite_indices[word_index] = word_count;

    spv::Id loaded_word = LoadUint32FromSharedMemory(word_address);
    spv::Id word_in_bounds =
        builder_->createBinOp(spv::OpULessThan, type_bool_, word_address, fetch_end);
    word_composite_constituents[word_count++] = builder_->createTriOp(
        spv::OpSelect, type_uint_, word_in_bounds, loaded_word, const_uint_0_);
  }
  spv::Id words;
  if (word_count > 1) {
    id_vector_temp_.clear();
    id_vector_temp_.insert(id_vector_temp_.cend(), word_composite_constituents,
                           word_composite_constituents + word_count);
    words = builder_->createCompositeConstruct(type_uint_vectors_[word_count - 1], id_vector_temp_);
  } else {
    words = word_composite_constituents[0];
  }

  words = EndianSwap32Uint(
      words, builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, fetch_constant_word_1,
                                   builder_->makeUintConstant(0b11)));

  spv::Id result = spv::NoResult;

  uint32_t used_format_components =
      used_result_components &
      ((1 << xenos::GetVertexFormatComponentCount(instr.attributes.data_format)) - 1);

  assert_not_zero(used_format_components);
  uint32_t used_format_component_count = rex::bit_count(used_format_components);
  spv::Id result_type = type_float_vectors_[used_format_component_count - 1];
  bool format_is_packed = false;
  int packed_widths[4] = {}, packed_offsets[4] = {};
  uint32_t packed_words[4] = {};
  switch (instr.attributes.data_format) {
    case xenos::VertexFormat::k_8_8_8_8:
      format_is_packed = true;
      packed_widths[0] = packed_widths[1] = packed_widths[2] = packed_widths[3] = 8;
      packed_offsets[1] = 8;
      packed_offsets[2] = 16;
      packed_offsets[3] = 24;
      break;
    case xenos::VertexFormat::k_2_10_10_10:
      format_is_packed = true;
      packed_widths[0] = packed_widths[1] = packed_widths[2] = 10;
      packed_widths[3] = 2;
      packed_offsets[1] = 10;
      packed_offsets[2] = 20;
      packed_offsets[3] = 30;
      break;
    case xenos::VertexFormat::k_10_11_11:
      format_is_packed = true;
      packed_widths[0] = packed_widths[1] = 11;
      packed_widths[2] = 10;
      packed_offsets[1] = 11;
      packed_offsets[2] = 22;
      break;
    case xenos::VertexFormat::k_11_11_10:
      format_is_packed = true;
      packed_widths[0] = 10;
      packed_widths[1] = packed_widths[2] = 11;
      packed_offsets[1] = 10;
      packed_offsets[2] = 21;
      break;
    case xenos::VertexFormat::k_16_16:
      format_is_packed = true;
      packed_widths[0] = packed_widths[1] = 16;
      packed_offsets[1] = 16;
      break;
    case xenos::VertexFormat::k_16_16_16_16:
      format_is_packed = true;
      packed_widths[0] = packed_widths[1] = packed_widths[2] = packed_widths[3] = 16;
      packed_offsets[1] = packed_offsets[3] = 16;
      packed_words[2] = packed_words[3] = 1;
      break;

    case xenos::VertexFormat::k_16_16_FLOAT:
    case xenos::VertexFormat::k_16_16_16_16_FLOAT: {
      spv::Id word_needed_component_values[2] = {};
      for (uint32_t i = 0; i < 2; ++i) {
        uint32_t word_needed_components = (used_format_components >> (i * 2)) & 0b11;
        if (!word_needed_components) {
          continue;
        }
        spv::Id word;
        if (word_count > 1) {
          word = builder_->createCompositeExtract(words, type_uint_, word_composite_indices[i]);
        } else {
          word = words;
        }
        word = builder_->createUnaryBuiltinCall(type_float2_, ext_inst_glsl_std_450_,
                                                GLSLstd450UnpackHalf2x16, word);
        if (word_needed_components != 0b11) {
          word = builder_->createCompositeExtract(word, type_float_,
                                                  (word_needed_components & 0b01) ? 0 : 1);
        }
        word_needed_component_values[i] = word;
      }
      if (word_needed_component_values[1] == spv::NoResult) {
        result = word_needed_component_values[0];
      } else if (word_needed_component_values[0] == spv::NoResult) {
        result = word_needed_component_values[1];
      } else {
        std::unique_ptr<spv::Instruction> composite_construct_op =
            std::make_unique<spv::Instruction>(builder_->getUniqueId(), result_type,
                                               spv::OpCompositeConstruct);
        composite_construct_op->addIdOperand(word_needed_component_values[0]);
        composite_construct_op->addIdOperand(word_needed_component_values[1]);
        result = composite_construct_op->getResultId();
        builder_->getBuildPoint()->addInstruction(std::move(composite_construct_op));
      }
    } break;

    case xenos::VertexFormat::k_32:
    case xenos::VertexFormat::k_32_32:
    case xenos::VertexFormat::k_32_32_32_32:
      assert_true(used_format_components == needed_words);
      if (instr.attributes.is_signed) {
        result = builder_->createUnaryOp(spv::OpBitcast,
                                         type_int_vectors_[used_format_component_count - 1], words);
        result = builder_->createUnaryOp(spv::OpConvertSToF, result_type, result);
      } else {
        result = builder_->createUnaryOp(spv::OpConvertUToF, result_type, words);
      }
      if (!instr.attributes.is_integer) {
        if (instr.attributes.is_signed) {
          switch (instr.attributes.signed_rf_mode) {
            case xenos::SignedRepeatingFractionMode::kZeroClampMinusOne:
              result = builder_->createNoContractionBinOp(
                  spv::OpVectorTimesScalar, result_type, result,
                  builder_->makeFloatConstant(1.0f / 2147483647.0f));

              break;
            case xenos::SignedRepeatingFractionMode::kNoZero: {
              result = builder_->createNoContractionBinOp(
                  spv::OpVectorTimesScalar, result_type, result,
                  builder_->makeFloatConstant(1.0f / 2147483647.5f));
              spv::Id const_no_zero = builder_->makeFloatConstant(0.5f / 2147483647.5f);
              if (used_format_component_count > 1) {
                id_vector_temp_.clear();
                id_vector_temp_.insert(id_vector_temp_.cend(), used_format_component_count,
                                       const_no_zero);
                const_no_zero = builder_->makeCompositeConstant(result_type, id_vector_temp_);
              }
              result = builder_->createNoContractionBinOp(spv::OpFAdd, result_type, result,
                                                          const_no_zero);
            } break;
            default:
              assert_unhandled_case(instr.attributes.signed_rf_mode);
          }
        } else {
          result =
              builder_->createNoContractionBinOp(spv::OpVectorTimesScalar, result_type, result,
                                                 builder_->makeFloatConstant(1.0f / 4294967295.0f));
        }
      }
      break;

    case xenos::VertexFormat::k_32_FLOAT:
    case xenos::VertexFormat::k_32_32_FLOAT:
    case xenos::VertexFormat::k_32_32_32_32_FLOAT:
    case xenos::VertexFormat::k_32_32_32_FLOAT:
      assert_true(used_format_components == needed_words);
      result = builder_->createUnaryOp(spv::OpBitcast, type_float_vectors_[word_count - 1], words);
      break;

    default:
      assert_unhandled_case(instr.attributes.data_format);
  }

  if (format_is_packed) {
    assert_true(result == spv::NoResult);

    if (instr.attributes.is_signed) {
      words = builder_->createUnaryOp(spv::OpBitcast, type_int_vectors_[word_count - 1], words);
    }
    int extracted_widths[4] = {};
    spv::Id extracted_components[4] = {};
    uint32_t extracted_component_count = 0;
    unsigned int extraction_word_current_index = UINT_MAX;

    spv::Id extraction_word_current = words;
    for (uint32_t i = 0; i < 4; ++i) {
      if (!(used_format_components & (1 << i))) {
        continue;
      }
      if (word_count > 1) {
        unsigned int extraction_word_new_index = word_composite_indices[packed_words[i]];
        if (extraction_word_current_index != extraction_word_new_index) {
          extraction_word_current_index = extraction_word_new_index;
          extraction_word_current = builder_->createCompositeExtract(
              words, instr.attributes.is_signed ? type_int_ : type_uint_,
              extraction_word_new_index);
        }
      }
      int extraction_width = packed_widths[i];
      assert_not_zero(extraction_width);
      extracted_widths[extracted_component_count] = extraction_width;
      extracted_components[extracted_component_count] = builder_->createTriOp(
          instr.attributes.is_signed ? spv::OpBitFieldSExtract : spv::OpBitFieldUExtract,
          instr.attributes.is_signed ? type_int_ : type_uint_, extraction_word_current,
          builder_->makeIntConstant(packed_offsets[i]),
          builder_->makeIntConstant(extraction_width));
      ++extracted_component_count;
    }

    assert_true(extracted_component_count == used_format_component_count);
    if (used_format_component_count > 1) {
      id_vector_temp_.clear();
      id_vector_temp_.insert(id_vector_temp_.cend(), extracted_components,
                             extracted_components + used_format_component_count);
      result = builder_->createCompositeConstruct(
          instr.attributes.is_signed ? type_int_vectors_[used_format_component_count - 1]
                                     : type_uint_vectors_[used_format_component_count - 1],
          id_vector_temp_);
    } else {
      result = extracted_components[0];
    }

    result = builder_->createUnaryOp(
        instr.attributes.is_signed ? spv::OpConvertSToF : spv::OpConvertUToF, result_type, result);

    if (!instr.attributes.is_integer) {
      float packed_scales[4];
      bool packed_scales_same = true;
      for (uint32_t i = 0; i < used_format_component_count; ++i) {
        int extracted_width = extracted_widths[i];

        assert_true(extracted_width >= 2);
        packed_scales_same &= extracted_width != extracted_widths[0];
        float packed_scale_inv;
        if (instr.attributes.is_signed) {
          packed_scale_inv = float((uint32_t(1) << (extracted_width - 1)) - 1);
          if (instr.attributes.signed_rf_mode == xenos::SignedRepeatingFractionMode::kNoZero) {
            packed_scale_inv += 0.5f;
          }
        } else {
          packed_scale_inv = float((uint32_t(1) << extracted_width) - 1);
        }
        packed_scales[i] = 1.0f / packed_scale_inv;
      }
      spv::Id const_packed_scale = builder_->makeFloatConstant(packed_scales[0]);
      spv::Op packed_scale_mul_op;
      if (used_format_component_count > 1) {
        if (packed_scales_same) {
          packed_scale_mul_op = spv::OpVectorTimesScalar;
        } else {
          packed_scale_mul_op = spv::OpFMul;
          id_vector_temp_.clear();
          id_vector_temp_.push_back(const_packed_scale);
          for (uint32_t i = 1; i < used_format_component_count; ++i) {
            id_vector_temp_.push_back(builder_->makeFloatConstant(packed_scales[i]));
          }
          const_packed_scale = builder_->makeCompositeConstant(result_type, id_vector_temp_);
        }
      } else {
        packed_scale_mul_op = spv::OpFMul;
      }
      result = builder_->createNoContractionBinOp(packed_scale_mul_op, result_type, result,
                                                  const_packed_scale);
      if (instr.attributes.is_signed) {
        switch (instr.attributes.signed_rf_mode) {
          case xenos::SignedRepeatingFractionMode::kZeroClampMinusOne: {
            spv::Id const_minus_1 = builder_->makeFloatConstant(-1.0f);
            if (used_format_component_count > 1) {
              id_vector_temp_.clear();
              id_vector_temp_.resize(used_format_component_count, const_minus_1);
              const_minus_1 = builder_->makeCompositeConstant(result_type, id_vector_temp_);
            }
            result = builder_->createBinBuiltinCall(result_type, ext_inst_glsl_std_450_,
                                                    GLSLstd450FMax, result, const_minus_1);
          } break;
          case xenos::SignedRepeatingFractionMode::kNoZero:
            id_vector_temp_.clear();
            for (uint32_t i = 0; i < used_format_component_count; ++i) {
              id_vector_temp_.push_back(builder_->makeFloatConstant(0.5f * packed_scales[i]));
            }
            result = builder_->createNoContractionBinOp(
                spv::OpFAdd, result_type, result,
                used_format_component_count > 1
                    ? builder_->makeCompositeConstant(result_type, id_vector_temp_)
                    : id_vector_temp_[0]);
            break;
          default:
            assert_unhandled_case(instr.attributes.signed_rf_mode);
        }
      }
    }
  }

  if (result != spv::NoResult) {
    if (instr.attributes.exp_adjust) {
      result = builder_->createNoContractionBinOp(
          spv::OpVectorTimesScalar, builder_->getTypeId(result), result,
          builder_->makeFloatConstant(std::ldexp(1.0f, instr.attributes.exp_adjust)));
    }

    uint32_t used_missing_components = used_result_components & ~used_format_components;
    if (used_missing_components) {
      std::unique_ptr<spv::Instruction> composite_construct_op = std::make_unique<spv::Instruction>(
          builder_->getUniqueId(), type_float_vectors_[rex::bit_count(used_result_components) - 1],
          spv::OpCompositeConstruct);
      composite_construct_op->addIdOperand(result);
      composite_construct_op->addIdOperand(
          const_float_vectors_0_[rex::bit_count(used_missing_components) - 1]);
      result = composite_construct_op->getResultId();
      builder_->getBuildPoint()->addInstruction(std::move(composite_construct_op));
    }
  }
  StoreResult(instr.result, result);
  BisectSnapshotAfterInstruction();
}

}
