/**
 * @file        rex/codegen/function_graph.h
 * @brief       Function graph - reactive model for function discovery and resolution
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <rex/codegen/function_node.h>

namespace rex::codegen {

class FunctionGraph {
 public:
  using MemoryReader = std::function<std::optional<uint32_t>(uint32_t addr)>;

  void addCodeBuffer(uint32_t baseAddress, const uint8_t* data, size_t size);

  const uint8_t* translateCode(uint32_t addr) const;

  const std::vector<CodeBuffer>& codeBuffers() const { return codeBuffers_; }

  void updateFunctionCodePointers();

  FunctionNode* addFunction(uint32_t base, uint32_t size, FunctionAuthority authority,
                            bool hasXrefs = false);

  FunctionNode* addFunction(uint32_t base, uint32_t size, FunctionAuthority authority,
                            std::string_view name, bool hasXrefs = false);

  FunctionNode* addImportFunction(uint32_t address, std::string_view resolvedName);

  FunctionNode* getFunction(uint32_t entryPoint);
  const FunctionNode* getFunction(uint32_t entryPoint) const;

  bool removeFunction(uint32_t entryPoint);

  FunctionNode* getFunctionContaining(uint32_t addr);
  const FunctionNode* getFunctionContaining(uint32_t addr) const;

  bool isEntryPoint(uint32_t addr) const;

  bool isImport(uint32_t addr) const;

  const std::unordered_map<uint32_t, std::unique_ptr<FunctionNode>>& functions() const {
    return functions_;
  }

  std::vector<FunctionNode*> getPendingFunctions();

  std::vector<FunctionNode*> getSealedFunctions();

  size_t functionCount() const { return functions_.size(); }
  size_t pendingCount() const;
  size_t sealedCount() const;

  void setFunctionName(uint32_t entry, std::string name);

  void setFunctionHasExceptionHandler(uint32_t entry, bool val);

  void setFunctionExceptionInfo(uint32_t entry, ExceptionInfo info);

  void addBlockToFunction(uint32_t entry, Block block);

  void addLabelToFunction(uint32_t entry, uint32_t label);

  void addCallToFunction(uint32_t entry, uint32_t site, CallTarget target);

  void addTailCallToFunction(uint32_t entry, uint32_t site, CallTarget target);

  void addJumpTableToFunction(uint32_t entry, JumpTable jt);

  void addUnresolvedJumpToFunction(uint32_t entry, uint32_t site, uint32_t target, bool isCall,
                                   bool conditional);

  size_t tryResolveFunction(uint32_t entry);

  void absorbRegionIntoFunction(uint32_t entry, uint32_t regionBase, uint32_t regionSize);

  bool trySealFunction(uint32_t entry);

  size_t sealAllReady();

  void sealAll();

  void setMemoryReader(MemoryReader reader) { memoryReader_ = std::move(reader); }

  void registerChunk(uint32_t base, uint32_t size);

  bool isVacant(uint32_t fromAddr, uint32_t targetAddr) const;

  bool isMergeableEntryPoint(uint32_t addr) const;

  size_t markFuncletRegisterSharing();

  TargetKind classifyTarget(uint32_t target, uint32_t callerAddr, bool isCallInstruction,
                            const FunctionNode* caller = nullptr) const;

 private:
  std::vector<CodeBuffer> codeBuffers_;
  std::unordered_map<uint32_t, std::unique_ptr<FunctionNode>> functions_;
  std::map<uint32_t, FunctionNode*> functionsByBase_;
  std::unordered_map<uint32_t, bool> functionHasXrefs_;
  std::vector<std::pair<uint32_t, uint32_t>> chunks_;
  MemoryReader memoryReader_;

  void notifyFunctionAdded(FunctionNode* newFunction);
};

}
