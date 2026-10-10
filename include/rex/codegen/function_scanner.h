/**
 * @file        rex/codegen/function_scanner.h
 * @brief       Function scanner and block discovery
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <rex/codegen/config.h>
#include <rex/codegen/function_graph.h>
#include <rex/result.h>
#include <rex/types.h>

namespace rex::codegen {

struct CodeRegion;
class BinaryView;
class DecodedBinary;

struct DiscoveredBlock {
  rex::guest_addr_t base = 0;
  rex::guest_addr_t end = 0;
  bool has_terminator = false;
  int64_t projectedSize = -1;
  std::vector<rex::guest_addr_t> successors;
};

struct FunctionBlocks {
  rex::guest_addr_t entry = 0;
  std::vector<DiscoveredBlock> blocks;
  rex::u32 pdata_size = 0;
  std::vector<JumpTable> jump_tables;
  std::vector<rex::guest_addr_t> external_calls;
  std::vector<rex::guest_addr_t> tail_calls;
};

class FunctionScanner {
 public:
  explicit FunctionScanner(const BinaryView& binary);

  std::optional<JumpTable> detect_jump_table(rex::guest_addr_t bctr_address);

  FunctionBlocks discover_blocks(rex::guest_addr_t entry_point, rex::u32 pdata_size = 0);

  template <typename T>
  const T* translate_address(rex::guest_addr_t guest_addr) const;

  bool isExecutableSection(rex::guest_addr_t address) const;

  void setKnownSwitchTables(const std::unordered_set<uint32_t>& addresses) {
    known_switch_tables_ = addresses;
  }

  void setChunks(const std::unordered_map<uint32_t, FunctionConfig>& chunks) { chunks_ = chunks; }

  void setBlTargets(const std::unordered_set<uint32_t>& targets) { bl_targets_ = targets; }

  const std::unordered_set<uint32_t>& getBlTargets() const { return bl_targets_; }

  void setKnownCallables(const std::unordered_set<uint32_t>& callables) {
    known_callables_ = callables;
  }

  bool isKnownCallable(uint32_t address) const { return known_callables_.contains(address); }

  void setDataRegions(const std::vector<std::pair<uint32_t, uint32_t>>& regions) {
    data_regions_ = regions;
  }

  bool isInDataRegion(uint32_t address) const {
    for (const auto& [start, end] : data_regions_) {
      if (address >= start && address < end)
        return true;
    }
    return false;
  }

  void setCodeRegions(const std::vector<CodeRegion>* regions) { code_regions_ = regions; }

  const CodeRegion* findRegionContaining(uint32_t address) const;

  bool isInternalBranch(uint32_t currentAddr, uint32_t targetAddr, uint32_t functionEntry) const;

  bool isWithinChunk(uint32_t address, uint32_t function_entry) const {
    for (const auto& [chunk_start, cfg] : chunks_) {
      if (cfg.parent == function_entry) {
        uint32_t chunk_end =
            cfg.end ? cfg.end : (cfg.size ? chunk_start + cfg.size : chunk_start + 0x1000);
        if (address >= chunk_start && address < chunk_end) {
          return true;
        }
      }
    }
    return false;
  }

  uint32_t findChunkParent(uint32_t address) const {
    auto it = chunks_.find(address);
    if (it != chunks_.end()) {
      return it->second.parent;
    }

    for (const auto& [chunk_start, cfg] : chunks_) {
      uint32_t chunk_end =
          cfg.end ? cfg.end : (cfg.size ? chunk_start + cfg.size : chunk_start + 0x1000);
      if (address >= chunk_start && address < chunk_end) {
        return cfg.parent;
      }
    }
    return 0;
  }

 private:
  const BinaryView* binary_ = nullptr;
  std::unordered_set<uint32_t> known_switch_tables_;
  std::unordered_map<uint32_t, FunctionConfig> chunks_;
  std::unordered_set<uint32_t> bl_targets_;
  std::unordered_set<uint32_t> known_callables_;
  std::vector<std::pair<uint32_t, uint32_t>> data_regions_;
  const std::vector<CodeRegion>* code_regions_ = nullptr;

  bool is_prologue_pattern(rex::guest_addr_t address);
  bool is_epilogue_pattern(rex::guest_addr_t address);
  bool is_restgprlr_function(rex::guest_addr_t address);
};

struct UnresolvedBranch {
  uint32_t site;
  uint32_t target;
  bool isCall;
  bool isConditional;
};

struct BlockDiscoveryResult {
  std::vector<Block> blocks;
  std::vector<UnresolvedBranch> unresolvedBranches;
  std::vector<JumpTable> jumpTables;
  std::set<uint32_t> labels;

  std::vector<rex::codegen::ppc::Instruction*> instructions;

  std::vector<uint32_t> externalCalls;
  std::vector<uint32_t> tailCalls;
};

BlockDiscoveryResult discoverBlocks(
    DecodedBinary& decoded, uint32_t entryPoint, const CodeRegion& containingRegion,
    const std::unordered_set<uint32_t>& knownFunctions, uint32_t pdataSize = 0,
    const std::unordered_map<uint32_t, JumpTable>* manualSwitchTables = nullptr);

std::optional<JumpTable> detectJumpTable(DecodedBinary& decoded, uint32_t bctrAddr,
                                         const CodeRegion& containingRegion, uint32_t funcStart,
                                         uint32_t funcEnd);

}
