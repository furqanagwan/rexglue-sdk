/**
 * @file        rex/graphics/pipeline/render_target/scaling_list.h
 * @brief       The render target sizes a title has upscaled (ADR-012)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace rex::graphics {

class ScalingResolutionList {
 public:
  struct Entry {
    uint32_t width = 0;
    uint32_t height = 0;
  };

  bool Parse(std::string_view text, std::string* error_out = nullptr);

  bool Matches(uint32_t width, uint32_t height) const;

  bool empty() const { return entries_.empty(); }
  const std::vector<Entry>& entries() const { return entries_; }

 private:
  std::vector<Entry> entries_;
  bool none_ = false;
};

}
