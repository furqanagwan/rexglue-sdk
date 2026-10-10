/**
 * @file        rex/codegen/test_support.h
 * @brief       Test support utilities
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <string_view>

#include <rex/system/module.h>

namespace rex::codegen {

class TestModule : public runtime::Module {
 public:
  TestModule();
  ~TestModule() override = default;

  void Load(uint32_t base_address, const uint8_t* data, size_t size);

  const std::string& name() const override { return name_; }
  void set_name(const std::string& name) { name_ = name; }
  bool is_executable() const override { return true; }
  uint32_t base_address() const override { return base_address_; }
  uint32_t image_size() const override { return size_; }
  uint32_t entry_point() const override { return base_address_; }
  bool ContainsAddress(uint32_t address) override;

 private:
  std::string name_{"test"};
  uint32_t base_address_ = 0;
  uint32_t size_ = 0;
};

class CodegenContext;

void AnalyzeTestBinary(CodegenContext& ctx, std::string_view testName,
                       const std::map<size_t, std::string>& symbols, uint32_t baseAddress,
                       const uint8_t* data, size_t dataSize);

}
