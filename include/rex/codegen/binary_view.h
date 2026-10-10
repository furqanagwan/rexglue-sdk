/**
 * @file        rex/codegen/binary_view.h
 * @brief       Self-contained binary view that owns section data
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace rex::runtime {
class Module;
}

namespace rex::codegen {

struct SectionView {
  std::string_view name;
  uint32_t baseAddress;
  uint32_t size;
  const uint8_t* data;
  bool executable;

  bool contains(uint32_t addr) const { return addr >= baseAddress && addr < baseAddress + size; }

  const uint8_t* translate(uint32_t addr) const {
    if (!contains(addr))
      return nullptr;
    return data + (addr - baseAddress);
  }

  uint32_t end() const { return baseAddress + size; }
};

struct ImportSymbol {
  uint32_t address;
  std::string name;
};

class BinaryView {
 public:
  static BinaryView fromModule(const runtime::Module& module);

  BinaryView(BinaryView&&) noexcept = default;
  BinaryView& operator=(BinaryView&&) noexcept = default;
  BinaryView(const BinaryView&) = delete;
  BinaryView& operator=(const BinaryView&) = delete;

  const uint8_t* translate(uint32_t addr) const;
  bool isExecutable(uint32_t addr) const;
  const SectionView* findSection(uint32_t addr) const;
  const SectionView* findSectionByName(std::string_view name) const;

  bool writeCode(uint32_t addr, std::span<const uint8_t> bytes);
  std::span<const SectionView> sections() const { return sections_; }

  uint32_t baseAddress() const { return baseAddress_; }
  uint32_t imageSize() const { return imageSize_; }
  uint32_t entryPoint() const { return entryPoint_; }
  uint32_t exceptionDirectoryAddr() const { return exceptionDirectoryAddr_; }
  uint32_t exceptionDirectorySize() const { return exceptionDirectorySize_; }
  uint32_t exportTableAddr() const { return exportTableAddr_; }

  uint32_t importThunkTableStart() const { return importThunkTableStart_; }

  bool isInImportExportRange(uint32_t addr) const {
    return importThunkTableStart_ != 0 && addr >= importThunkTableStart_ &&
           addr < importExportRangeEnd_;
  }

  std::span<const ImportSymbol> importSymbols() const { return importSymbols_; }

 public:
  BinaryView() = default;

 private:
  std::vector<SectionView> sections_;
  std::vector<std::string> sectionNames_;
  std::vector<std::vector<uint8_t>> sectionData_;

  uint32_t baseAddress_ = 0;
  uint32_t imageSize_ = 0;
  uint32_t entryPoint_ = 0;
  uint32_t exceptionDirectoryAddr_ = 0;
  uint32_t exceptionDirectorySize_ = 0;
  uint32_t exportTableAddr_ = 0;
  uint32_t importThunkTableStart_ = 0;
  uint32_t importExportRangeEnd_ = 0;

  std::vector<ImportSymbol> importSymbols_;
};

}
