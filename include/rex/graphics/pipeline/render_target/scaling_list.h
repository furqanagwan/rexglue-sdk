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

/// A title's list of render target sizes to upscale, in the syntax of
/// Microsoft's backward compatibility launch arguments: space-separated
/// `WxH`, 0 meaning any (`720x0 844x0 0x240`). A size matches an entry when
/// every non-zero dimension of the entry is equal. `none` matches nothing:
/// every resolve at the guest's size (with resolve_downscale_average, full
/// supersampling).
class ScalingResolutionList {
 public:
  struct Entry {
    uint32_t width = 0;
    uint32_t height = 0;
  };

  /// Parses `text`; false (and an empty list) if any entry is malformed or
  /// `0x0`, with the bad entry in `error_out`.
  bool Parse(std::string_view text, std::string* error_out = nullptr);

  /// Whether a render target of this size is upscaled. An empty list scales
  /// everything (the behaviour without a list); `none` nothing.
  bool Matches(uint32_t width, uint32_t height) const;

  bool empty() const { return entries_.empty(); }
  const std::vector<Entry>& entries() const { return entries_; }

 private:
  std::vector<Entry> entries_;
  bool none_ = false;
};

}  // namespace rex::graphics
