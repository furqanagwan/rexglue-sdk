/**
 * @file        rex/codegen/function_table_layout.h
 * @brief       Where each module's function dispatch table goes (RG-GDK-070)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

namespace rex::codegen {

struct ModuleImage {
  uint32_t base = 0;
  uint32_t size = 0;
};

inline std::vector<uint32_t> PlaceFunctionTables(const std::vector<ModuleImage>& images,
                                                 uint32_t thunk_reserve) {
  constexpr uint64_t kAlign = 0x10000;
  struct Range {
    uint64_t begin, end;
  };
  std::vector<Range> taken;
  for (const ModuleImage& image : images) {
    taken.push_back({image.base, uint64_t(image.base) + image.size});
  }
  auto overlaps = [&](uint64_t begin, uint64_t end) {
    return std::any_of(taken.begin(), taken.end(),
                       [&](const Range& r) { return begin < r.end && r.begin < end; });
  };

  std::vector<uint32_t> bases(images.size(), 0);
  std::vector<bool> placed(images.size(), false);
  auto table_size = [&](size_t i) { return (uint64_t(images[i].size) + thunk_reserve) * 2; };
  for (size_t i = 0; i < images.size(); ++i) {
    const uint64_t base = uint64_t(images[i].base) + images[i].size;
    if (!overlaps(base, base + table_size(i))) {
      taken.push_back({base, base + table_size(i)});
      bases[i] = uint32_t(base);
      placed[i] = true;
    }
  }
  for (size_t i = 0; i < images.size(); ++i) {
    if (placed[i]) {
      continue;
    }
    uint64_t highest = 0;
    for (const Range& r : taken) {
      highest = std::max(highest, r.end);
    }
    const uint64_t base = (highest + kAlign - 1) / kAlign * kAlign;
    taken.push_back({base, base + table_size(i)});
    bases[i] = uint32_t(base);
  }
  return bases;
}

}
