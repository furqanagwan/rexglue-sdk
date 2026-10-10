/**
 * @file        rex/graphics/pipeline/shader/storage_seed.h
 * @brief       A shader cache shipped with a title, seeding the player's (RG-GDK-064)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <span>
#include <string>

namespace rex::graphics {

struct StorageFormat {
  std::span<const uint8_t> header;

  size_t record_size = 0;
};

enum class SeedResult {
  kNoShippedFile,
  kStale,
  kCopied,
  kMerged,
  kUpToDate,
  kFailed,
};

struct SeedOutcome {
  SeedResult result = SeedResult::kNoShippedFile;
  size_t added = 0;
  std::string error;
};

SeedOutcome SeedStorageFile(const std::filesystem::path& shipped, const std::filesystem::path& user,
                            const StorageFormat& format);

}
