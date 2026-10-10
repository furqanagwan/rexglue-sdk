/**
 * @file        rex/codegen/vtable_scanner.h
 * @brief       VTable scanner - RTTI-based vtable discovery
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
#include <vector>

#include <rex/codegen/binary_view.h>

namespace rex::codegen {

struct RTTITypeDescriptor {
  uint32_t pVFTable;
  uint32_t spare;
};

struct RTTICompleteObjectLocator {
  uint32_t signature;
  uint32_t offset;
  uint32_t cdOffset;
  uint32_t pTypeDescriptor;
  uint32_t pClassHierarchy;
};

struct VTableInfo {
  uint32_t vtableAddress;
  uint32_t colAddress;
  std::string className;
  std::vector<uint32_t> slots;
};

class VTableScanner {
 public:
  explicit VTableScanner(const BinaryView& binary);

  std::vector<VTableInfo> scan();

 private:
  const BinaryView& binary_;

  std::vector<uint32_t> findCompleteObjectLocators();

  std::optional<uint32_t> findVTableForCOL(uint32_t colAddr);

  std::vector<uint32_t> readVTableSlots(uint32_t vtableStart);

  std::string extractClassName(uint32_t colAddr);

  bool isExecutableAddress(uint32_t addr) const;

  std::optional<uint32_t> readDword(uint32_t addr) const;

  std::string readString(uint32_t addr, size_t maxLen = 256) const;
};

}
