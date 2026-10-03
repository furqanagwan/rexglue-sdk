/**
 * @file        graphics/pipeline/render_target/scaling_list.cpp
 * @brief       The render target sizes a title has upscaled (ADR-012)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/graphics/pipeline/render_target/scaling_list.h>

#include <charconv>

namespace rex::graphics {

namespace {

bool ParseDimension(std::string_view text, uint32_t& value_out) {
  if (text.empty()) {
    return false;
  }
  const auto result = std::from_chars(text.data(), text.data() + text.size(), value_out);
  return result.ec == std::errc() && result.ptr == text.data() + text.size();
}

}  // namespace

bool ScalingResolutionList::Parse(std::string_view text, std::string* error_out) {
  entries_.clear();
  std::vector<Entry> entries;
  size_t position = 0;
  while (position < text.size()) {
    const size_t start = text.find_first_not_of(" \t,", position);
    if (start == std::string_view::npos) {
      break;
    }
    size_t end = text.find_first_of(" \t,", start);
    if (end == std::string_view::npos) {
      end = text.size();
    }
    const std::string_view item = text.substr(start, end - start);
    position = end;
    const size_t x = item.find_first_of("xX");
    Entry entry;
    if (x == std::string_view::npos || !ParseDimension(item.substr(0, x), entry.width) ||
        !ParseDimension(item.substr(x + 1), entry.height) || (!entry.width && !entry.height)) {
      if (error_out) {
        *error_out = std::string(item);
      }
      return false;
    }
    entries.push_back(entry);
  }
  entries_ = std::move(entries);
  return true;
}

bool ScalingResolutionList::Matches(uint32_t width, uint32_t height) const {
  if (entries_.empty()) {
    return true;
  }
  for (const Entry& entry : entries_) {
    if ((!entry.width || entry.width == width) && (!entry.height || entry.height == height)) {
      return true;
    }
  }
  return false;
}

}  // namespace rex::graphics
