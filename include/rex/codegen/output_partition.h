/**
 * @file        rex/codegen/output_partition.h
 * @brief       Stable assignment of guest functions to recomp output files
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace rex::codegen {

inline constexpr std::string_view kPartitionFileName = "codegen.partition.json";

struct FunctionSize {
  uint32_t address;
  size_t bytes;
};

class OutputPartition {
 public:
  static OutputPartition Load(const std::filesystem::path& path);

  std::vector<std::vector<size_t>> Assign(std::span<const FunctionSize> entries,
                                          size_t maxFileBytes);

  std::string Serialize() const;

 private:
  std::unordered_map<uint32_t, size_t> addressToFile_;
  size_t fileCount_ = 0;
  size_t maxFileBytes_ = 0;
};

}
