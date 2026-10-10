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

#ifndef REX_GRAPHICS_PIPELINE_SHADER_SPIRV_BUILDER_H_
#define REX_GRAPHICS_PIPELINE_SHADER_SPIRV_BUILDER_H_

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include <SPIRV/SpvBuilder.h>
#include <rex/assert.h>

namespace rex::graphics {

class SpirvBuilder : public spv::Builder {
 public:
  SpirvBuilder(unsigned int spv_version, unsigned int user_number, spv::SpvBuildLogger* logger)
      : spv::Builder(spv_version, user_number, logger) {}

  void SetAllowContraction(bool allow) { allow_contraction_ = allow; }
  bool AllowsContraction() const { return allow_contraction_; }

  void SetNoContractionAll(bool all) { no_contraction_all_ = all; }

  spv::Id createUnaryOp(spv::Op op_code, spv::Id type_id, spv::Id operand) {
    spv::Id result = spv::Builder::createUnaryOp(op_code, type_id, operand);
    MarkNoContractionAll(op_code, result);
    return result;
  }
  spv::Id createBinOp(spv::Op op_code, spv::Id type_id, spv::Id operand1, spv::Id operand2) {
    spv::Id result = spv::Builder::createBinOp(op_code, type_id, operand1, operand2);
    MarkNoContractionAll(op_code, result);
    return result;
  }

  using spv::Builder::createSelectionMerge;

  void createBranch(spv::Block* block) { spv::Builder::createBranch(true, block); }

  spv::Function* makeFunctionEntry(spv::Decoration precision, spv::Id returnType, const char* name,
                                   const std::vector<spv::Id>& paramTypes,
                                   const std::vector<std::vector<spv::Decoration>>& precisions,
                                   spv::Block** entry = nullptr) {
    return spv::Builder::makeFunctionEntry(precision, returnType, name, spv::LinkageType::Max,
                                           paramTypes, precisions, entry);
  }

  spv::Id createAccessChain(spv::StorageClass storage_class, spv::Id base,
                            const std::vector<spv::Id>& offsets) {
    clearAccessChain();
    setAccessChainLValue(base);
    for (const auto& offset : offsets) {
      accessChainPush(offset, {}, 0);
    }

    spv::Id result = spv::Builder::createAccessChain(storage_class, base, offsets);

    clearAccessChain();

    return result;
  }

  spv::Id createQuadOp(spv::Op op_code, spv::Id type_id, spv::Id operand1, spv::Id operand2,
                       spv::Id operand3, spv::Id operand4);

  spv::Id createNoContractionUnaryOp(spv::Op op_code, spv::Id type_id, spv::Id operand);
  spv::Id createNoContractionBinOp(spv::Op op_code, spv::Id type_id, spv::Id operand1,
                                   spv::Id operand2);

  spv::Id createUnaryBuiltinCall(spv::Id result_type, spv::Id builtins, int entry_point,
                                 spv::Id operand);
  spv::Id createBinBuiltinCall(spv::Id result_type, spv::Id builtins, int entry_point,
                               spv::Id operand1, spv::Id operand2);
  spv::Id createTriBuiltinCall(spv::Id result_type, spv::Id builtins, int entry_point,
                               spv::Id operand1, spv::Id operand2, spv::Id operand3);

  spv::Id smearFloatConstant(float value, spv::Id value_type);

  class IfBuilder {
   public:
    IfBuilder(spv::Id condition, spv::SelectionControlMask control, SpirvBuilder& builder,
              unsigned int thenWeight = 0, unsigned int elseWeight = 0);

    ~IfBuilder() {
#ifndef NDEBUG
      assert_true(currentBranch == Branch::kMerge);
#endif
    }

    void makeBeginElse(bool branchToMerge = true);
    void makeEndIf(bool branchToMerge = true);

    spv::Id getThenPhiParent() const { return thenPhiParent; }
    spv::Id getElsePhiParent() const { return elsePhiParent; }

    spv::Id createMergePhi(spv::Id then_variable, spv::Id else_variable) const;

   private:
    enum class Branch {
      kThen,
      kElse,
      kMerge,
    };

    IfBuilder(const IfBuilder& ifBuilder) = delete;
    IfBuilder& operator=(const IfBuilder& ifBuilder) = delete;

    SpirvBuilder& builder;
    spv::Id condition;
    spv::SelectionControlMask control;
    unsigned int thenWeight;
    unsigned int elseWeight;

    spv::Function& function;

    spv::Block* headerBlock;
    spv::Block* thenBlock;
    spv::Block* elseBlock;
    spv::Block* mergeBlock;

    spv::Id thenPhiParent;
    spv::Id elsePhiParent;

#ifndef NDEBUG
    Branch currentBranch = Branch::kThen;
#endif
  };

  class SwitchBuilder {
   public:
    SwitchBuilder(spv::Id selector, spv::SelectionControlMask selection_control,
                  SpirvBuilder& builder);
    ~SwitchBuilder() { assert_true(current_branch_ == Branch::kMerge); }

    void makeBeginDefault();
    void makeBeginCase(unsigned int literal);
    void addCurrentCaseLiteral(unsigned int literal);
    void makeEndSwitch();

    spv::Id getDefaultPhiParent() const { return default_phi_parent_; }

   private:
    enum class Branch {
      kSelection,
      kDefault,
      kCase,
      kMerge,
    };

    void endSegment();

    SpirvBuilder& builder_;
    spv::Id selector_;
    spv::SelectionControlMask selection_control_;

    spv::Function& function_;

    spv::Block* header_block_;
    spv::Block* merge_block_;
    spv::Block* default_block_ = nullptr;

    std::vector<std::pair<unsigned int, spv::Id>> cases_;

    spv::Id default_phi_parent_;

    Branch current_branch_ = Branch::kSelection;
  };

 private:
  void MarkNoContractionAll(spv::Op op_code, spv::Id result);

  bool allow_contraction_ = false;
  bool no_contraction_all_ = false;
};

}

#endif
