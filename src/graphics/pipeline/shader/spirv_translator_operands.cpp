

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

void SpirvShaderTranslator::UpdateExecConditionals(ParsedExecInstruction::Type type,
                                                   uint32_t bool_constant_index, bool condition) {
  if (type == ParsedExecInstruction::Type::kConditional) {
    if (cf_exec_conditional_merge_ && cf_exec_bool_constant_or_predicate_ == bool_constant_index &&
        cf_exec_condition_ == condition) {
      return;
    }
  } else if (type == ParsedExecInstruction::Type::kPredicated) {
    if (!cf_exec_predicate_written_ && cf_exec_conditional_merge_ &&
        cf_exec_bool_constant_or_predicate_ == kCfExecBoolConstantPredicate &&
        cf_exec_condition_ == condition) {
      return;
    }
  } else {
    assert_true(type == ParsedExecInstruction::Type::kUnconditional);
    if (!cf_exec_conditional_merge_) {
      return;
    }
  }

  CloseExecConditionals();

  if (type == ParsedExecInstruction::Type::kUnconditional) {
    return;
  }

  EnsureBuildPointAvailable();
  spv::Id condition_id;
  if (type == ParsedExecInstruction::Type::kConditional) {
    id_vector_temp_.clear();

    id_vector_temp_.push_back(const_int_0_);

    id_vector_temp_.push_back(builder_->makeIntConstant(int(bool_constant_index >> 7)));

    id_vector_temp_.push_back(builder_->makeIntConstant(int((bool_constant_index >> 5) & 3)));
    spv::Id bool_constant_scalar = builder_->createLoad(
        builder_->createAccessChain(spv::StorageClassUniform, uniform_bool_loop_constants_,
                                    id_vector_temp_),
        spv::NoPrecision);
    condition_id = builder_->createBinOp(
        spv::OpINotEqual, type_bool_,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type_uint_, bool_constant_scalar,
            builder_->makeUintConstant(uint32_t(1) << (bool_constant_index & 31))),
        const_uint_0_);
    cf_exec_bool_constant_or_predicate_ = bool_constant_index;
  } else if (type == ParsedExecInstruction::Type::kPredicated) {
    condition_id = builder_->createLoad(var_main_predicate_, spv::NoPrecision);
    cf_exec_bool_constant_or_predicate_ = kCfExecBoolConstantPredicate;
  } else {
    assert_unhandled_case(type);
    return;
  }
  cf_exec_condition_ = condition;
  cf_exec_conditional_merge_ =
      new spv::Block(builder_->getUniqueId(), builder_->getBuildPoint()->getParent());
  builder_->createSelectionMerge(cf_exec_conditional_merge_, spv::SelectionControlDontFlattenMask);
  spv::Block& inner_block = builder_->makeNewBlock();
  builder_->createConditionalBranch(condition_id,
                                    condition ? &inner_block : cf_exec_conditional_merge_,
                                    condition ? cf_exec_conditional_merge_ : &inner_block);
  builder_->setBuildPoint(&inner_block);
}

void SpirvShaderTranslator::UpdateInstructionPredication(bool predicated, bool condition) {
  if (!predicated) {
    CloseInstructionPredication();
    return;
  }

  if (cf_instruction_predicate_merge_) {
    if (cf_instruction_predicate_condition_ == condition) {
      return;
    }
    CloseInstructionPredication();
  }

  if (!cf_exec_predicate_written_ && cf_exec_conditional_merge_ &&
      cf_exec_bool_constant_or_predicate_ == kCfExecBoolConstantPredicate &&
      cf_exec_condition_ == condition) {
    return;
  }

  cf_instruction_predicate_condition_ = condition;
  EnsureBuildPointAvailable();
  spv::Id predicate_id = builder_->createLoad(var_main_predicate_, spv::NoPrecision);
  spv::Block& predicated_block = builder_->makeNewBlock();
  cf_instruction_predicate_merge_ =
      new spv::Block(builder_->getUniqueId(), builder_->getBuildPoint()->getParent());
  builder_->createSelectionMerge(cf_instruction_predicate_merge_, spv::SelectionControlMaskNone);
  builder_->createConditionalBranch(
      predicate_id, condition ? &predicated_block : cf_instruction_predicate_merge_,
      condition ? cf_instruction_predicate_merge_ : &predicated_block);
  builder_->setBuildPoint(&predicated_block);
}

void SpirvShaderTranslator::CloseInstructionPredication() {
  if (!cf_instruction_predicate_merge_) {
    return;
  }
  spv::Block& inner_block = *builder_->getBuildPoint();
  if (!inner_block.isTerminated()) {
    builder_->createBranch(cf_instruction_predicate_merge_);
  }
  inner_block.getParent().addBlock(cf_instruction_predicate_merge_);
  builder_->setBuildPoint(cf_instruction_predicate_merge_);
  cf_instruction_predicate_merge_ = nullptr;
}

void SpirvShaderTranslator::CloseExecConditionals() {
  CloseInstructionPredication();

  if (cf_exec_conditional_merge_) {
    spv::Block& inner_block = *builder_->getBuildPoint();
    if (!inner_block.isTerminated()) {
      builder_->createBranch(cf_exec_conditional_merge_);
    }
    inner_block.getParent().addBlock(cf_exec_conditional_merge_);
    builder_->setBuildPoint(cf_exec_conditional_merge_);
    cf_exec_conditional_merge_ = nullptr;
  }

  cf_exec_predicate_written_ = false;
}

spv::Id SpirvShaderTranslator::GetStorageAddressingIndex(
    InstructionStorageAddressingMode addressing_mode, uint32_t storage_index,
    bool is_float_constant) {
  const Shader::ConstantRegisterMap& constant_register_map =
      current_shader().constant_register_map();
  EnsureBuildPointAvailable();
  spv::Id base_pointer = spv::NoResult;
  switch (addressing_mode) {
    case InstructionStorageAddressingMode::kAbsolute: {
      uint32_t static_storage_index = storage_index;
      if (is_float_constant) {
        static_storage_index = constant_register_map.GetPackedFloatConstantIndex(storage_index);
        assert_true(static_storage_index != UINT32_MAX);
        if (static_storage_index == UINT32_MAX) {
          static_storage_index = 0;
        }
      }
      return builder_->makeIntConstant(int(static_storage_index));
    }
    case InstructionStorageAddressingMode::kAddressRegisterRelative:
      base_pointer = var_main_address_register_;
      break;
    case InstructionStorageAddressingMode::kLoopRelative:

      id_vector_temp_util_.clear();
      id_vector_temp_util_.push_back(const_int_0_);
      base_pointer = builder_->createAccessChain(spv::StorageClassFunction, var_main_loop_address_,
                                                 id_vector_temp_util_);
      break;
  }
  assert_true(!is_float_constant || constant_register_map.float_dynamic_addressing);
  assert_true(base_pointer != spv::NoResult);
  spv::Id index = builder_->createLoad(base_pointer, spv::NoPrecision);
  if (storage_index) {
    index = builder_->createBinOp(spv::OpIAdd, type_int_, index,
                                  builder_->makeIntConstant(int(storage_index)));
  }

  uint32_t index_count = is_float_constant ? constant_register_map.float_count : register_count();
  if (index_count) {
    index = builder_->createTriBuiltinCall(type_int_, ext_inst_glsl_std_450_, GLSLstd450SClamp,
                                           index, const_int_0_,
                                           builder_->makeIntConstant(int(index_count - 1)));
  }
  return index;
}

spv::Id SpirvShaderTranslator::LoadOperandStorage(const InstructionOperand& operand) {
  spv::Id index =
      GetStorageAddressingIndex(operand.storage_addressing_mode, operand.storage_index,
                                operand.storage_source == InstructionStorageSource::kConstantFloat);
  EnsureBuildPointAvailable();
  spv::Id vec4_pointer = spv::NoResult;
  switch (operand.storage_source) {
    case InstructionStorageSource::kRegister:
      assert_true(var_main_registers_ != spv::NoResult);
      id_vector_temp_util_.clear();

      id_vector_temp_util_.push_back(index);
      vec4_pointer = builder_->createAccessChain(spv::StorageClassFunction, var_main_registers_,
                                                 id_vector_temp_util_);
      break;
    case InstructionStorageSource::kConstantFloat:
      assert_true(uniform_float_constants_ != spv::NoResult);
      id_vector_temp_util_.clear();

      id_vector_temp_util_.push_back(const_int_0_);

      id_vector_temp_util_.push_back(index);
      vec4_pointer = builder_->createAccessChain(spv::StorageClassUniform, uniform_float_constants_,
                                                 id_vector_temp_util_);
      break;
    default:
      assert_unhandled_case(operand.storage_source);
  }
  assert_true(vec4_pointer != spv::NoResult);
  return builder_->createLoad(vec4_pointer, spv::NoPrecision);
}

spv::Id SpirvShaderTranslator::ApplyOperandModifiers(spv::Id operand_value,
                                                     const InstructionOperand& original_operand,
                                                     bool invert_negate, bool force_absolute) {
  spv::Id type = builder_->getTypeId(operand_value);
  assert_true(type != spv::NoType);
  if (type == spv::NoType) {
    return operand_value;
  }
  if (original_operand.is_absolute_value || force_absolute) {
    EnsureBuildPointAvailable();
    operand_value = builder_->createUnaryBuiltinCall(type, ext_inst_glsl_std_450_, GLSLstd450FAbs,
                                                     operand_value);
  }
  if (original_operand.is_negated != invert_negate) {
    EnsureBuildPointAvailable();
    operand_value = builder_->createNoContractionUnaryOp(spv::OpFNegate, type, operand_value);
  }
  return operand_value;
}

spv::Id SpirvShaderTranslator::GetUnmodifiedOperandComponents(
    spv::Id operand_storage, const InstructionOperand& original_operand, uint32_t components) {
  assert_not_zero(components);
  if (!components) {
    return spv::NoResult;
  }
  assert_true(components <= 0b1111);
  if (components == 0b1111 && original_operand.IsStandardSwizzle()) {
    return operand_storage;
  }
  EnsureBuildPointAvailable();
  uint32_t component_count = rex::bit_count(components);
  if (component_count == 1) {
    uint32_t scalar_index;
    rex::bit_scan_forward(components, &scalar_index);
    return builder_->createCompositeExtract(
        operand_storage, type_float_,
        static_cast<unsigned int>(original_operand.GetComponent(scalar_index)) -
            static_cast<unsigned int>(SwizzleSource::kX));
  }
  uint_vector_temp_util_.clear();
  uint32_t components_remaining = components;
  uint32_t component_index;
  while (rex::bit_scan_forward(components_remaining, &component_index)) {
    components_remaining &= ~(uint32_t(1) << component_index);
    uint_vector_temp_util_.push_back(
        static_cast<unsigned int>(original_operand.GetComponent(component_index)) -
        static_cast<unsigned int>(SwizzleSource::kX));
  }
  return builder_->createRvalueSwizzle(spv::NoPrecision, type_float_vectors_[component_count - 1],
                                       operand_storage, uint_vector_temp_util_);
}

void SpirvShaderTranslator::GetOperandScalarXY(spv::Id operand_storage,
                                               const InstructionOperand& original_operand,
                                               spv::Id& a_out, spv::Id& b_out, bool invert_negate,
                                               bool force_absolute) {
  spv::Id a = GetOperandComponents(operand_storage, original_operand, 0b0001, invert_negate,
                                   force_absolute);
  a_out = a;
  b_out = original_operand.GetComponent(0) != original_operand.GetComponent(1)
              ? GetOperandComponents(operand_storage, original_operand, 0b0010, invert_negate,
                                     force_absolute)
              : a;
}

spv::Id SpirvShaderTranslator::GetAbsoluteOperand(spv::Id operand_storage,
                                                  const InstructionOperand& original_operand) {
  if (original_operand.is_absolute_value && !original_operand.is_negated) {
    return operand_storage;
  }
  EnsureBuildPointAvailable();
  return builder_->createUnaryBuiltinCall(builder_->getTypeId(operand_storage),
                                          ext_inst_glsl_std_450_, GLSLstd450FAbs, operand_storage);
}

void SpirvShaderTranslator::StoreResult(const InstructionResult& result, spv::Id value) {
  uint32_t used_write_mask = result.GetUsedWriteMask();
  if (!used_write_mask) {
    return;
  }

  if (result.storage_target == InstructionStorageTarget::kRegister) {
    if (result.storage_addressing_mode == InstructionStorageAddressingMode::kAbsolute) {
      if (result.storage_index < xenos::kMaxInterpolators) {
        main_interpolators_unmodified_ &=
            ~(uint64_t(used_write_mask) << (result.storage_index * 4));
      }
    } else {
      main_interpolators_unmodified_ = 0;
    }
  }

  EnsureBuildPointAvailable();

  spv::Id target_pointer = spv::NoResult;
  switch (result.storage_target) {
    case InstructionStorageTarget::kNone:
      break;
    case InstructionStorageTarget::kRegister: {
      assert_true(var_main_registers_ != spv::NoResult);

      spv::Id register_index =
          GetStorageAddressingIndex(result.storage_addressing_mode, result.storage_index);
      id_vector_temp_util_.clear();

      id_vector_temp_util_.push_back(register_index);
      target_pointer = builder_->createAccessChain(spv::StorageClassFunction, var_main_registers_,
                                                   id_vector_temp_util_);
    } break;
    case InstructionStorageTarget::kInterpolator: {
      assert_true(is_vertex_shader());
      target_pointer = input_output_interpolators_[result.storage_index];

    } break;
    case InstructionStorageTarget::kPosition: {
      assert_true(is_vertex_shader());
      id_vector_temp_util_.clear();
      id_vector_temp_util_.push_back(builder_->makeIntConstant(kOutputPerVertexMemberPosition));
      target_pointer = builder_->createAccessChain(spv::StorageClassOutput, output_per_vertex_,
                                                   id_vector_temp_util_);
    } break;
    case InstructionStorageTarget::kPointSizeEdgeFlagKillVertex: {
      assert_true(is_vertex_shader());
      assert_zero(used_write_mask & 0b1000);
      target_pointer = var_main_point_size_edge_flag_kill_vertex_;
    } break;
    case InstructionStorageTarget::kColor: {
      assert_true(is_pixel_shader());
      assert_not_zero(used_write_mask);
      assert_true(current_shader().writes_color_target(result.storage_index));
      target_pointer = output_or_var_fragment_data_[result.storage_index];
      if (var_main_fsi_color_written_ != spv::NoResult) {
        builder_->createStore(
            builder_->createBinOp(
                spv::OpBitwiseOr, type_uint_,
                builder_->createLoad(var_main_fsi_color_written_, spv::NoPrecision),
                builder_->makeUintConstant(uint32_t(1) << result.storage_index)),
            var_main_fsi_color_written_);
      }
    } break;
    case InstructionStorageTarget::kExportAddress: {
      target_pointer = var_main_memexport_address_;
    } break;
    case InstructionStorageTarget::kExportData: {
      target_pointer = var_main_memexport_data_[result.storage_index];
      if (target_pointer != spv::NoResult) {
        assert_true(var_main_memexport_data_written_ != spv::NoResult);
        builder_->createStore(
            builder_->createBinOp(
                spv::OpBitwiseOr, type_uint_,
                builder_->createLoad(var_main_memexport_data_written_, spv::NoPrecision),
                builder_->makeUintConstant(uint32_t(1) << result.storage_index)),
            var_main_memexport_data_written_);
      }
    } break;
    case InstructionStorageTarget::kDepth: {
      assert_true(is_pixel_shader());
      assert_true(used_write_mask == 0b0001);
      assert_true(current_shader().writes_depth());
      assert_true(output_or_var_fragment_depth_ != spv::NoResult);
      target_pointer = output_or_var_fragment_depth_;

      if (value != spv::NoResult && !result.is_clamped) {
        value =
            builder_->createTriBuiltinCall(type_float_, ext_inst_glsl_std_450_, GLSLstd450NClamp,
                                           value, const_float_0_, const_float_1_);
      }
    } break;
    default:

      assert_unhandled_case(result.storage_target);
      break;
  }
  if (target_pointer == spv::NoResult) {
    return;
  }

  uint32_t constant_values;
  uint32_t constant_components = result.GetUsedConstantComponents(constant_values);
  if (value == spv::NoResult) {
    constant_components = used_write_mask;
  }
  uint32_t non_constant_components = used_write_mask & ~constant_components;

  unsigned int value_num_components =
      value != spv::NoResult ? static_cast<unsigned int>(builder_->getNumComponents(value)) : 0;

  if (result.is_clamped && non_constant_components) {
    value = builder_->createTriBuiltinCall(type_float_vectors_[value_num_components - 1],
                                           ext_inst_glsl_std_450_, GLSLstd450NClamp, value,
                                           const_float_vectors_0_[value_num_components - 1],
                                           const_float_vectors_1_[value_num_components - 1]);
  }

  uint32_t used_result_components = result.GetUsedResultComponents();
  unsigned int result_unswizzled_value_components[4] = {};
  if (value_num_components > 1) {
    unsigned int value_component = 0;
    uint32_t used_result_components_remaining = used_result_components;
    uint32_t result_component;
    while (rex::bit_scan_forward(used_result_components_remaining, &result_component)) {
      used_result_components_remaining &= ~(uint32_t(1) << result_component);
      result_unswizzled_value_components[result_component] =
          std::min(value_component++, value_num_components - 1);
    }
  }

  unsigned int result_swizzled_value_components[4] = {};
  for (uint32_t i = 0; i < 4; ++i) {
    if (!(non_constant_components & (1 << i))) {
      continue;
    }
    SwizzleSource swizzle = result.components[i];
    assert_true(swizzle >= SwizzleSource::kX && swizzle <= SwizzleSource::kW);
    result_swizzled_value_components[i] =
        result_unswizzled_value_components[uint32_t(swizzle) - uint32_t(SwizzleSource::kX)];
  }

  spv::Id target_type = builder_->getDerefTypeId(target_pointer);
  unsigned int target_num_components = builder_->getNumTypeComponents(target_type);
  assert_true(target_num_components ==
              GetInstructionStorageTargetUsedComponentCount(result.storage_target));
  uint32_t target_component_mask = (1 << target_num_components) - 1;
  assert_zero(used_write_mask & ~target_component_mask);

  spv::Id value_to_store;
  if (target_component_mask == used_write_mask) {
    if (!constant_components) {
      if (target_num_components > 1) {
        if (value_num_components > 1) {
          bool is_identity_swizzle = target_num_components == value_num_components;
          for (uint32_t i = 0; is_identity_swizzle && i < target_num_components; ++i) {
            is_identity_swizzle &= result_swizzled_value_components[i] == i;
          }
          if (is_identity_swizzle) {
            value_to_store = value;
          } else {
            uint_vector_temp_util_.clear();
            uint_vector_temp_util_.insert(uint_vector_temp_util_.cend(),
                                          result_swizzled_value_components,
                                          result_swizzled_value_components + target_num_components);
            value_to_store = builder_->createRvalueSwizzle(spv::NoPrecision, target_type, value,
                                                           uint_vector_temp_util_);
          }
        } else {
          value_to_store = builder_->smearScalar(spv::NoPrecision, value, target_type);
        }
      } else {
        if (value_num_components > 1) {
          value_to_store = builder_->createCompositeExtract(value, type_float_,
                                                            result_swizzled_value_components[0]);
        } else {
          value_to_store = value;
        }
      }
    } else if (!non_constant_components) {
      if (target_num_components > 1) {
        id_vector_temp_util_.clear();
        for (uint32_t i = 0; i < target_num_components; ++i) {
          id_vector_temp_util_.push_back((constant_values & (1 << i)) ? const_float_1_
                                                                      : const_float_0_);
        }
        value_to_store = builder_->makeCompositeConstant(target_type, id_vector_temp_util_);
      } else {
        value_to_store = (constant_values & 0b0001) ? const_float_1_ : const_float_0_;
      }
    } else {
      assert_true(target_num_components > 1);
      if (value_num_components > 1) {
        std::unique_ptr<spv::Instruction> shuffle_op = std::make_unique<spv::Instruction>(
            builder_->getUniqueId(), target_type, spv::OpVectorShuffle);
        shuffle_op->addIdOperand(value);
        shuffle_op->addIdOperand(const_float2_0_1_);
        for (uint32_t i = 0; i < target_num_components; ++i) {
          shuffle_op->addImmediateOperand((constant_components & (1 << i))
                                              ? value_num_components + ((constant_values >> i) & 1)
                                              : result_swizzled_value_components[i]);
        }
        value_to_store = shuffle_op->getResultId();
        builder_->getBuildPoint()->addInstruction(std::move(shuffle_op));
      } else {
        id_vector_temp_util_.clear();
        for (uint32_t i = 0; i < target_num_components; ++i) {
          if (constant_components & (1 << i)) {
            id_vector_temp_util_.push_back((constant_values & (1 << i)) ? const_float_1_
                                                                        : const_float_0_);
          } else {
            id_vector_temp_util_.push_back(value);
          }
        }
        value_to_store = builder_->createCompositeConstruct(target_type, id_vector_temp_util_);
      }
    }
  } else {
    assert_true(target_num_components > 1);
    value_to_store = builder_->createLoad(target_pointer, spv::NoPrecision);

    if (constant_components) {
      std::unique_ptr<spv::Instruction> shuffle_op = std::make_unique<spv::Instruction>(
          builder_->getUniqueId(), target_type, spv::OpVectorShuffle);
      shuffle_op->addIdOperand(value_to_store);
      shuffle_op->addIdOperand(const_float2_0_1_);
      for (uint32_t i = 0; i < target_num_components; ++i) {
        shuffle_op->addImmediateOperand((constant_components & (1 << i))
                                            ? target_num_components + ((constant_values >> i) & 1)
                                            : i);
      }
      value_to_store = shuffle_op->getResultId();
      builder_->getBuildPoint()->addInstruction(std::move(shuffle_op));
    }
    if (non_constant_components) {
      if (value_num_components > 1) {
        std::unique_ptr<spv::Instruction> shuffle_op = std::make_unique<spv::Instruction>(
            builder_->getUniqueId(), target_type, spv::OpVectorShuffle);
        shuffle_op->addIdOperand(value_to_store);
        shuffle_op->addIdOperand(value);
        for (uint32_t i = 0; i < target_num_components; ++i) {
          shuffle_op->addImmediateOperand((non_constant_components & (1 << i))
                                              ? target_num_components +
                                                    result_swizzled_value_components[i]
                                              : i);
        }
        value_to_store = shuffle_op->getResultId();
        builder_->getBuildPoint()->addInstruction(std::move(shuffle_op));
      } else {
        for (uint32_t i = 0; i < target_num_components; ++i) {
          if (non_constant_components & (1 << i)) {
            value_to_store = builder_->createCompositeInsert(value, value_to_store, target_type, i);
          }
        }
      }
    }
  }

  if (result.storage_target == InstructionStorageTarget::kPointSizeEdgeFlagKillVertex &&
      used_write_mask & 0b001) {
    spv::Id point_size =
        builder_->createUnaryOp(spv::OpBitcast, type_int_,
                                builder_->createCompositeExtract(value_to_store, type_float_, 0));
    id_vector_temp_util_.clear();
    id_vector_temp_util_.push_back(
        builder_->makeIntConstant(kSystemConstantPointVertexDiameterMin));
    spv::Id point_vertex_diameter_min = builder_->createUnaryOp(
        spv::OpBitcast, type_int_,
        builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                        id_vector_temp_util_),
            spv::NoPrecision));
    point_size = builder_->createBinBuiltinCall(type_int_, ext_inst_glsl_std_450_, GLSLstd450SMax,
                                                point_vertex_diameter_min, point_size);
    id_vector_temp_util_.clear();
    id_vector_temp_util_.push_back(
        builder_->makeIntConstant(kSystemConstantPointVertexDiameterMax));
    spv::Id point_vertex_diameter_max = builder_->createUnaryOp(
        spv::OpBitcast, type_int_,
        builder_->createLoad(
            builder_->createAccessChain(spv::StorageClassUniform, uniform_system_constants_,
                                        id_vector_temp_util_),
            spv::NoPrecision));
    point_size = builder_->createBinBuiltinCall(type_int_, ext_inst_glsl_std_450_, GLSLstd450SMin,
                                                point_vertex_diameter_max, point_size);
    value_to_store = builder_->createCompositeInsert(
        builder_->createUnaryOp(spv::OpBitcast, type_float_, point_size), value_to_store,
        type_float3_, 0);
  }

  builder_->createStore(value_to_store, target_pointer);
}

spv::Id SpirvShaderTranslator::EndianSwap32Uint(spv::Id value, spv::Id endian) {
  spv::Id type = builder_->getTypeId(value);
  spv::Id const_uint_8_scalar = builder_->makeUintConstant(8);
  spv::Id const_uint_00ff00ff_scalar = builder_->makeUintConstant(0x00FF00FF);
  spv::Id const_uint_16_scalar = builder_->makeUintConstant(16);
  spv::Id const_uint_8_typed, const_uint_00ff00ff_typed, const_uint_16_typed;
  int num_components = builder_->getNumTypeComponents(type);
  if (num_components > 1) {
    id_vector_temp_.clear();
    id_vector_temp_.insert(id_vector_temp_.cend(), num_components, const_uint_8_scalar);
    const_uint_8_typed = builder_->makeCompositeConstant(type, id_vector_temp_);
    id_vector_temp_.clear();
    id_vector_temp_.insert(id_vector_temp_.cend(), num_components, const_uint_00ff00ff_scalar);
    const_uint_00ff00ff_typed = builder_->makeCompositeConstant(type, id_vector_temp_);
    id_vector_temp_.clear();
    id_vector_temp_.insert(id_vector_temp_.cend(), num_components, const_uint_16_scalar);
    const_uint_16_typed = builder_->makeCompositeConstant(type, id_vector_temp_);
  } else {
    const_uint_8_typed = const_uint_8_scalar;
    const_uint_00ff00ff_typed = const_uint_00ff00ff_scalar;
    const_uint_16_typed = const_uint_16_scalar;
  }

  spv::Id is_8in16 = builder_->createBinOp(
      spv::OpIEqual, type_bool_, endian,
      builder_->makeUintConstant(static_cast<unsigned int>(xenos::Endian::k8in16)));
  spv::Id is_8in32 = builder_->createBinOp(
      spv::OpIEqual, type_bool_, endian,
      builder_->makeUintConstant(static_cast<unsigned int>(xenos::Endian::k8in32)));
  spv::Id is_8in16_or_8in32 =
      builder_->createBinOp(spv::OpLogicalOr, type_bool_, is_8in16, is_8in32);
  SpirvBuilder::IfBuilder if_8in16(is_8in16_or_8in32, spv::SelectionControlMaskNone, *builder_);
  spv::Id swapped_8in16;
  {
    swapped_8in16 = builder_->createBinOp(
        spv::OpBitwiseOr, type,
        builder_->createBinOp(
            spv::OpBitwiseAnd, type,
            builder_->createBinOp(spv::OpShiftRightLogical, type, value, const_uint_8_typed),
            const_uint_00ff00ff_typed),
        builder_->createBinOp(
            spv::OpShiftLeftLogical, type,
            builder_->createBinOp(spv::OpBitwiseAnd, type, value, const_uint_00ff00ff_typed),
            const_uint_8_typed));
  }
  if_8in16.makeEndIf();
  value = if_8in16.createMergePhi(swapped_8in16, value);

  spv::Id is_16in32 = builder_->createBinOp(
      spv::OpIEqual, type_bool_, endian,
      builder_->makeUintConstant(static_cast<unsigned int>(xenos::Endian::k16in32)));
  spv::Id is_8in32_or_16in32 =
      builder_->createBinOp(spv::OpLogicalOr, type_bool_, is_8in32, is_16in32);
  SpirvBuilder::IfBuilder if_16in32(is_8in32_or_16in32, spv::SelectionControlMaskNone, *builder_);
  spv::Id swapped_16in32;
  {
    swapped_16in32 = builder_->createQuadOp(
        spv::OpBitFieldInsert, type,
        builder_->createBinOp(spv::OpShiftRightLogical, type, value, const_uint_16_typed), value,
        builder_->makeIntConstant(16), builder_->makeIntConstant(16));
  }
  if_16in32.makeEndIf();
  value = if_16in32.createMergePhi(swapped_16in32, value);

  return value;
}

spv::Id SpirvShaderTranslator::EndianSwap128Uint4(spv::Id value, spv::Id endian) {
  spv::Id is_8in64 = builder_->createBinOp(
      spv::OpIEqual, type_bool_, endian,
      builder_->makeUintConstant(static_cast<unsigned int>(xenos::Endian128::k8in64)));
  uint_vector_temp_.clear();
  uint_vector_temp_.push_back(1);
  uint_vector_temp_.push_back(0);
  uint_vector_temp_.push_back(3);
  uint_vector_temp_.push_back(2);
  value = builder_->createTriOp(
      spv::OpSelect, type_uint4_, builder_->smearScalar(spv::NoPrecision, is_8in64, type_bool4_),
      builder_->createRvalueSwizzle(spv::NoPrecision, type_uint4_, value, uint_vector_temp_),
      value);

  spv::Id is_8in128 = builder_->createBinOp(
      spv::OpIEqual, type_bool_, endian,
      builder_->makeUintConstant(static_cast<unsigned int>(xenos::Endian128::k8in128)));
  uint_vector_temp_.clear();
  uint_vector_temp_.push_back(3);
  uint_vector_temp_.push_back(2);
  uint_vector_temp_.push_back(1);
  uint_vector_temp_.push_back(0);
  value = builder_->createTriOp(
      spv::OpSelect, type_uint4_, builder_->smearScalar(spv::NoPrecision, is_8in128, type_bool4_),
      builder_->createRvalueSwizzle(spv::NoPrecision, type_uint4_, value, uint_vector_temp_),
      value);

  endian = builder_->createTriOp(
      spv::OpSelect, type_uint_,
      builder_->createBinOp(spv::OpLogicalOr, type_bool_, is_8in64, is_8in128),
      builder_->makeUintConstant(static_cast<unsigned int>(xenos::Endian128::k8in32)), endian);

  return EndianSwap32Uint(value, endian);
}

spv::Id SpirvShaderTranslator::LoadUint32FromSharedMemory(spv::Id address_dwords_int) {
  spv::StorageClass storage_class = features_.spirv_version >= spv::Spv_1_3
                                        ? spv::StorageClassStorageBuffer
                                        : spv::StorageClassUniform;

  uint32_t binding_count_log2 = GetSharedMemoryStorageBufferCountLog2();

  if (!binding_count_log2) {
    id_vector_temp_.clear();

    id_vector_temp_.push_back(const_int_0_);
    id_vector_temp_.push_back(address_dwords_int);
    return builder_->createLoad(
        builder_->createAccessChain(storage_class, buffers_shared_memory_, id_vector_temp_),
        spv::NoPrecision);
  }

  uint32_t binding_address_bits = (29 - 2) - binding_count_log2;
  spv::Id binding_index =
      builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                            builder_->createUnaryOp(spv::OpBitcast, type_uint_, address_dwords_int),
                            builder_->makeUintConstant(binding_address_bits));
  spv::Id binding_address = builder_->createBinOp(
      spv::OpBitwiseAnd, type_int_, address_dwords_int,
      builder_->makeIntConstant(int((uint32_t(1) << binding_address_bits) - 1)));

  auto value_phi_op =
      std::make_unique<spv::Instruction>(builder_->getUniqueId(), type_uint_, spv::OpPhi);

  value_phi_op->addIdOperand(const_uint_0_);
  value_phi_op->addIdOperand(builder_->getBuildPoint()->getId());

  SpirvBuilder::SwitchBuilder binding_switch(binding_index, spv::SelectionControlDontFlattenMask,
                                             *builder_);
  uint32_t binding_count = uint32_t(1) << binding_count_log2;

  id_vector_temp_.clear();
  id_vector_temp_.push_back(spv::NoResult);

  id_vector_temp_.push_back(const_int_0_);
  id_vector_temp_.push_back(binding_address);

  for (uint32_t i = 0; i < binding_count; ++i) {
    binding_switch.makeBeginCase(i);
    id_vector_temp_[0] = builder_->makeIntConstant(int(i));
    value_phi_op->addIdOperand(builder_->createLoad(
        builder_->createAccessChain(storage_class, buffers_shared_memory_, id_vector_temp_),
        spv::NoPrecision));
    value_phi_op->addIdOperand(builder_->getBuildPoint()->getId());
  }

  binding_switch.makeEndSwitch();

  spv::Id value_phi_result = value_phi_op->getResultId();
  builder_->getBuildPoint()->addInstruction(std::move(value_phi_op));
  return value_phi_result;
}

void SpirvShaderTranslator::StoreUint32ToSharedMemory(spv::Id value, spv::Id address_dwords_int,
                                                      spv::Id replace_mask) {
  spv::StorageClass storage_class = features_.spirv_version >= spv::Spv_1_3
                                        ? spv::StorageClassStorageBuffer
                                        : spv::StorageClassUniform;

  spv::Id keep_mask = spv::NoResult;
  if (replace_mask != spv::NoResult) {
    keep_mask = builder_->createUnaryOp(spv::OpNot, type_uint_, replace_mask);
    value = builder_->createBinOp(spv::OpBitwiseAnd, type_uint_, value, replace_mask);
  }

  auto store = [&](spv::Id pointer) {
    if (replace_mask != spv::NoResult) {
      spv::Id const_scope_device =
          builder_->makeUintConstant(static_cast<unsigned int>(spv::ScopeDevice));
      spv::Id const_semantics_relaxed = const_uint_0_;
      builder_->createQuadOp(spv::OpAtomicAnd, type_uint_, pointer, const_scope_device,
                             const_semantics_relaxed, keep_mask);
      builder_->createQuadOp(spv::OpAtomicOr, type_uint_, pointer, const_scope_device,
                             const_semantics_relaxed, value);
    } else {
      builder_->createStore(value, pointer);
    }
  };

  uint32_t binding_count_log2 = GetSharedMemoryStorageBufferCountLog2();

  if (!binding_count_log2) {
    id_vector_temp_.clear();

    id_vector_temp_.push_back(const_int_0_);
    id_vector_temp_.push_back(address_dwords_int);
    store(builder_->createAccessChain(storage_class, buffers_shared_memory_, id_vector_temp_));
    return;
  }

  uint32_t binding_address_bits = (29 - 2) - binding_count_log2;
  spv::Id binding_index =
      builder_->createBinOp(spv::OpShiftRightLogical, type_uint_,
                            builder_->createUnaryOp(spv::OpBitcast, type_uint_, address_dwords_int),
                            builder_->makeUintConstant(binding_address_bits));
  spv::Id binding_address = builder_->createBinOp(
      spv::OpBitwiseAnd, type_int_, address_dwords_int,
      builder_->makeIntConstant(int((uint32_t(1) << binding_address_bits) - 1)));

  SpirvBuilder::SwitchBuilder binding_switch(binding_index, spv::SelectionControlDontFlattenMask,
                                             *builder_);
  uint32_t binding_count = uint32_t(1) << binding_count_log2;

  id_vector_temp_.clear();
  id_vector_temp_.push_back(spv::NoResult);

  id_vector_temp_.push_back(const_int_0_);
  id_vector_temp_.push_back(binding_address);

  for (uint32_t i = 0; i < binding_count; ++i) {
    binding_switch.makeBeginCase(i);
    id_vector_temp_[0] = builder_->makeIntConstant(int(i));
    store(builder_->createAccessChain(storage_class, buffers_shared_memory_, id_vector_temp_));
  }

  binding_switch.makeEndSwitch();
}

spv::Id SpirvShaderTranslator::PWLGammaToLinear(SpirvBuilder* builder_, spv::Id gamma,
                                                bool pre_saturated,
                                                spv::Id ext_inst_glsl_std_450_) {
  spv::Id value_type = builder_->getTypeId(gamma);
  assert_true(builder_->isFloatType(builder_->getScalarTypeId(value_type)));
  bool is_vector = builder_->isVectorType(value_type);
  assert_true(is_vector || builder_->isFloatType(value_type));
  int num_components = builder_->getNumTypeComponents(value_type);
  assert_true(num_components < 4);
  spv::Id bool_type = is_vector ? builder_->makeVectorType(builder_->makeBoolType(), num_components)
                                : builder_->makeBoolType();

  spv::Id const_vector_0 = builder_->smearFloatConstant(0.0f, value_type);

  if (!pre_saturated) {
    gamma = builder_->createTriBuiltinCall(value_type, ext_inst_glsl_std_450_, GLSLstd450NClamp,
                                           gamma, const_vector_0,
                                           builder_->smearFloatConstant(1.0f, value_type));
  }

  spv::Id is_piece_at_least_3 =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, bool_type, gamma,
                            builder_->smearFloatConstant(192.0f / 255.0f, value_type));
  spv::Id scale_3_or_2 =
      builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_3,
                            builder_->smearFloatConstant(8.0f / 1024.0f, value_type),
                            builder_->smearFloatConstant(4.0f / 1024.0f, value_type));
  spv::Id offset_3_or_2 = builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_3,
                                                builder_->smearFloatConstant(-1024.0f, value_type),
                                                builder_->smearFloatConstant(-256.0f, value_type));

  spv::Id is_piece_at_least_1 =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, bool_type, gamma,
                            builder_->smearFloatConstant(64.0f / 255.0f, value_type));
  spv::Id scale_1_or_0 =
      builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_1,
                            builder_->smearFloatConstant(2.0f / 1024.0f, value_type),
                            builder_->smearFloatConstant(1.0f / 1024.0f, value_type));
  spv::Id offset_1_or_0 =
      builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_1,
                            builder_->smearFloatConstant(-64.0f, value_type), const_vector_0);

  spv::Id is_piece_at_least_2 =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, bool_type, gamma,
                            builder_->smearFloatConstant(96.0f / 255.0f, value_type));
  spv::Id scale = builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_2,
                                        scale_3_or_2, scale_1_or_0);
  spv::Id offset = builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_2,
                                         offset_3_or_2, offset_1_or_0);

  spv::Op value_times_scalar_opcode = is_vector ? spv::OpVectorTimesScalar : spv::OpFMul;

  spv::Id linear = builder_->createNoContractionBinOp(
      spv::OpFAdd, value_type,
      builder_->createNoContractionBinOp(
          spv::OpFMul, value_type,
          builder_->createNoContractionBinOp(value_times_scalar_opcode, value_type, gamma,
                                             builder_->makeFloatConstant(255.0f * 1024.0f)),
          scale),
      offset);

  linear = builder_->createNoContractionBinOp(
      spv::OpFAdd, value_type, linear,
      builder_->createUnaryBuiltinCall(
          value_type, ext_inst_glsl_std_450_, GLSLstd450Trunc,
          builder_->createNoContractionBinOp(spv::OpFMul, value_type, linear, scale)));

  linear = builder_->createNoContractionBinOp(value_times_scalar_opcode, value_type, linear,
                                              builder_->makeFloatConstant(1.0f / 1023.0f));
  return linear;
}

spv::Id SpirvShaderTranslator::LinearToPWLGamma(SpirvBuilder* builder_, spv::Id linear,
                                                bool pre_saturated,
                                                spv::Id ext_inst_glsl_std_450_) {
  spv::Id value_type = builder_->getTypeId(linear);
  assert_true(builder_->isFloatType(builder_->getScalarTypeId(value_type)));
  bool is_vector = builder_->isVectorType(value_type);
  assert_true(is_vector || builder_->isFloatType(value_type));
  int num_components = builder_->getNumTypeComponents(value_type);
  assert_true(num_components < 4);
  spv::Id bool_type = is_vector ? builder_->makeVectorType(builder_->makeBoolType(), num_components)
                                : builder_->makeBoolType();

  spv::Id const_vector_0 = builder_->smearFloatConstant(0.0f, value_type);

  if (!pre_saturated) {
    linear = builder_->createTriBuiltinCall(value_type, ext_inst_glsl_std_450_, GLSLstd450NClamp,
                                            linear, const_vector_0,
                                            builder_->smearFloatConstant(1.0f, value_type));
  }

  spv::Id is_piece_at_least_3 =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, bool_type, linear,
                            builder_->smearFloatConstant(512.0f / 1023.0f, value_type));
  spv::Id scale_3_or_2 =
      builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_3,
                            builder_->smearFloatConstant(1023.0f / 8.0f, value_type),
                            builder_->smearFloatConstant(1023.0f / 4.0f, value_type));
  spv::Id offset_3_or_2 =
      builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_3,
                            builder_->smearFloatConstant(128.0f / 255.0f, value_type),
                            builder_->smearFloatConstant(64.0f / 255.0f, value_type));

  spv::Id is_piece_at_least_1 =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, bool_type, linear,
                            builder_->smearFloatConstant(64.0f / 1023.0f, value_type));
  spv::Id scale_1_or_0 =
      builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_1,
                            builder_->smearFloatConstant(1023.0f / 2.0f, value_type),
                            builder_->smearFloatConstant(1023.0f, value_type));
  spv::Id offset_1_or_0 = builder_->createTriOp(
      spv::OpSelect, value_type, is_piece_at_least_1,
      builder_->smearFloatConstant(32.0f / 255.0f, value_type), const_vector_0);

  spv::Id is_piece_at_least_2 =
      builder_->createBinOp(spv::OpFOrdGreaterThanEqual, bool_type, linear,
                            builder_->smearFloatConstant(128.0f / 1023.0f, value_type));
  spv::Id scale = builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_2,
                                        scale_3_or_2, scale_1_or_0);
  spv::Id offset = builder_->createTriOp(spv::OpSelect, value_type, is_piece_at_least_2,
                                         offset_3_or_2, offset_1_or_0);

  return builder_->createNoContractionBinOp(
      spv::OpFAdd, value_type,
      builder_->createNoContractionBinOp(
          is_vector ? spv::OpVectorTimesScalar : spv::OpFMul, value_type,
          builder_->createUnaryBuiltinCall(
              value_type, ext_inst_glsl_std_450_, GLSLstd450Trunc,
              builder_->createNoContractionBinOp(spv::OpFMul, value_type, linear, scale)),
          builder_->makeFloatConstant(1.0f / 255.0f)),
      offset);
}

}
