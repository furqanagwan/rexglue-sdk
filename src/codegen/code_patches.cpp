/**
 * @file        codegen/code_patches.cpp
 * @brief       Guest code patches applied to the image before analysis
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <map>

#include <fmt/format.h>

#include <rex/codegen/binary_view.h>
#include <rex/codegen/code_patches.h>
#include <rex/logging.h>

#include "codegen_logging.h"

namespace rex::codegen {

Result<std::vector<std::string>> ApplyCodePatches(BinaryView& binary,
                                                  const std::vector<CodePatch>& patches) {
  // Check everything before writing anything.
  std::map<uint32_t, std::pair<uint32_t, const CodePatch*>> claimed;  // start -> end, owner
  for (const auto& patch : patches) {
    if (!patch.enabled) {
      continue;
    }
    if (!patch.error.empty()) {
      return Err<std::vector<std::string>>(
          ErrorCategory::Config,
          fmt::format("Patch \"{}\" ({}): {}", patch.name, patch.source, patch.error));
    }
    for (const auto& write : patch.writes) {
      const uint32_t start = write.address;
      const uint32_t end = start + static_cast<uint32_t>(write.bytes.size());
      const auto* section = binary.findSection(start);
      if (!section || !section->executable || end > section->end()) {
        return Err<std::vector<std::string>>(
            ErrorCategory::Config,
            fmt::format("Patch \"{}\" writes 0x{:08X}, outside the code sections. Only guest code "
                        "can be patched: the running title loads the original image.",
                        patch.name, start));
      }
      auto next = claimed.lower_bound(start);
      const bool overlapsNext = next != claimed.end() && next->first < end;
      const bool overlapsPrev = next != claimed.begin() && std::prev(next)->second.first > start;
      if (overlapsNext || overlapsPrev) {
        const auto* other = overlapsNext ? next->second.second : std::prev(next)->second.second;
        return Err<std::vector<std::string>>(
            ErrorCategory::Config, fmt::format("Patches \"{}\" and \"{}\" both write 0x{:08X}",
                                               other->name, patch.name, start));
      }
      claimed.emplace(start, std::make_pair(end, &patch));
    }
  }

  std::vector<std::string> applied;
  for (const auto& patch : patches) {
    if (!patch.enabled) {
      REXCODEGEN_INFO("Patch \"{}\" is disabled", patch.name);
      continue;
    }
    for (const auto& write : patch.writes) {
      binary.writeCode(write.address, write.bytes);
    }
    REXCODEGEN_INFO("Applied patch \"{}\" ({} writes)", patch.name, patch.writes.size());
    applied.push_back(patch.name);
  }
  return applied;
}

}  // namespace rex::codegen
