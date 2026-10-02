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

/// The shape of a persistent shader storage file (the "shareable" files the
/// pipeline cache keeps per title): a header, then records that each start
/// with the 64-bit XXH3 hash of the bytes they cover, which is also the
/// record's identity.
struct StorageFormat {
  /// The header a file of the running SDK's version starts with.
  std::span<const uint8_t> header;
  /// Fixed-size records (pipeline descriptions, `.xpso`): the record's size;
  /// the hash covers the rest of it. 0: shader records (`.xsh`), a 12-byte
  /// head (the hash, then a 32-bit field whose low 31 bits are the ucode's
  /// dword count) and the ucode, which the hash covers.
  size_t record_size = 0;
};

enum class SeedResult {
  kNoShippedFile,  // nothing shipped for this file
  kStale,          // shipped for another SDK version or damaged: ignored
  kCopied,         // the player had none (or another version's): shipped copy used
  kMerged,         // shipped records the player lacked appended
  kUpToDate,       // the player has every shipped record
  kFailed,         // the player's file could not be written
};

struct SeedOutcome {
  SeedResult result = SeedResult::kNoShippedFile;
  size_t added = 0;  // records copied or appended
  std::string error;
};

/// Brings the shipped storage file `shipped` into the player's `user` file,
/// before the pipeline cache opens it: a player without one (or with another
/// version's) gets the shipped file; otherwise the shipped records the player
/// lacks are appended after the player's valid records. Damaged tails stop
/// reading, as the pipeline cache's own loading does. The file is rewritten
/// beside and moved into place, so a failure leaves the player's file as it
/// was.
SeedOutcome SeedStorageFile(const std::filesystem::path& shipped, const std::filesystem::path& user,
                            const StorageFormat& format);

}  // namespace rex::graphics
