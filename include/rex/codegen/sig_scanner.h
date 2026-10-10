/**
 * @file        rex/codegen/sig_scanner.h
 * @brief       Signature scanner for pattern-based function discovery
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
#include <string>
#include <unordered_map>
#include <vector>

#include <rex/system/module.h>

namespace rex::codegen {

struct Signature {
  std::string name;
  std::vector<uint32_t> pattern;
  std::vector<uint32_t> mask;
  size_t entryOffset = 0;
  std::optional<size_t> size;
};

class SigScanner {
 public:
  explicit SigScanner(const runtime::Module& module);

  std::vector<uint32_t> scan(const Signature& sig);

  std::unordered_map<std::string, std::vector<uint32_t>> scanAll(
      const std::vector<Signature>& sigs);

  static std::vector<Signature> helperSignatures();
  static std::vector<Signature> hleSignatures();

 private:
  const runtime::Module& module_;

  std::vector<uint32_t> scanRange(uint32_t start, uint32_t end,
                                  const std::vector<uint32_t>& pattern,
                                  const std::vector<uint32_t>& mask, size_t entryOffset);
};

}
