/**
 * @file        rex/codegen/function_node.h
 * @brief       FunctionNode - core object representing a function in the graph
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <rex/codegen/function_types.h>

namespace rex::codegen {

class FunctionNode {
  friend class FunctionGraph;

 public:
  FunctionNode(uint32_t base, uint32_t size, FunctionAuthority authority);

  uint32_t base() const { return base_; }
  uint32_t size() const { return size_; }
  uint32_t end() const { return base_ + size_; }
  const std::string& name() const { return name_; }

  const uint8_t* code() const { return code_; }
  bool hasCode() const { return code_ != nullptr; }

  FunctionAuthority authority() const { return authority_; }
  FunctionState state() const { return state_; }

  bool isRegistered() const { return state_ == FunctionState::kRegistered; }
  bool isDiscovered() const { return state_ == FunctionState::kDiscovered; }
  bool isSealed() const { return state_ == FunctionState::kSealed; }

  bool isPending() const { return state_ != FunctionState::kSealed; }

  bool isImport() const { return authority_ == FunctionAuthority::IMPORT; }
  bool isHelper() const { return authority_ == FunctionAuthority::HELPER; }

  bool canDiscover() const { return state_ == FunctionState::kRegistered; }

  void discover(std::vector<Block> blocks,
                std::vector<rex::codegen::ppc::Instruction*> instructions,
                std::set<uint32_t> labels);

  void discoverAsImport();

  bool canSeal() const;

  void seal();

  const FunctionAnalysis& analysis() const;

  std::string emitCpp(const EmitContext& ctx) const;

  std::span<rex::codegen::ppc::Instruction* const> instructions() const { return instructions_; }

  const std::vector<Block>& blocks() const { return blocks_; }
  bool containsAddress(uint32_t addr) const;

  bool isWithinBounds(uint32_t addr) const { return addr >= base_ && addr < base_ + size_; }

  const std::set<uint32_t>& labels() const { return labels_; }
  bool isLabel(uint32_t addr) const { return labels_.contains(addr); }

  const std::vector<CallEdge>& calls() const { return calls_; }

  const std::vector<CallEdge>& tailCalls() const { return tailCalls_; }

  const std::vector<JumpTable>& jumpTables() const { return jumpTables_; }

  const std::vector<UnresolvedJump>& unresolvedJumps() const { return unresolvedJumps_; }

  bool hasUnresolvedJumps() const { return !unresolvedJumps_.empty(); }

  bool hasExceptionHandler() const { return hasExceptionHandler_; }

  const std::optional<ExceptionInfo>& exceptionInfo() const { return exceptionInfo_; }
  bool hasExceptionInfo() const { return exceptionInfo_.has_value() && exceptionInfo_->hasInfo(); }

  void setName(std::string name) { name_ = std::move(name); }

  bool sharesRegisters() const { return sharesRegisters_; }
  void setSharesRegisters(bool val) { sharesRegisters_ = val; }

 private:
  void setCode(const uint8_t* ptr) { code_ = ptr; }
  void setHasExceptionHandler(bool val) { hasExceptionHandler_ = val; }
  void setExceptionInfo(ExceptionInfo info) { exceptionInfo_ = std::move(info); }

  void addBlock(Block block);
  void addLabel(uint32_t addr);

  void addCall(uint32_t site, CallTarget target);
  void addTailCall(uint32_t site, CallTarget target);
  void addJumpTable(JumpTable jt);
  void addUnresolvedJump(uint32_t site, uint32_t target, bool isCall, bool conditional);

  bool tryResolveAgainst(FunctionNode* newFunction);
  bool tryResolveAgainstImport(uint32_t importAddr, const std::string& importName);
  bool tryResolveAsInternalLabel(uint32_t target);

  void absorbRegion(uint32_t regionBase, uint32_t regionSize);

  void removeUnresolvedJump(uint32_t site);

 private:
  uint32_t base_;
  uint32_t size_;
  std::string name_;
  const uint8_t* code_ = nullptr;
  FunctionAuthority authority_;
  FunctionState state_ = FunctionState::kRegistered;
  bool hasExceptionHandler_ = false;
  bool sharesRegisters_ = false;

  std::vector<Block> blocks_;
  std::vector<rex::codegen::ppc::Instruction*> instructions_;
  std::set<uint32_t> labels_;

  std::vector<CallEdge> calls_;
  std::vector<CallEdge> tailCalls_;
  std::vector<JumpTable> jumpTables_;

  std::vector<UnresolvedJump> unresolvedJumps_;

  std::optional<ExceptionInfo> exceptionInfo_;

  std::optional<FunctionAnalysis> analysis_;
};

}
