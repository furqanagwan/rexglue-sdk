/**
 * @file        graphics/pipeline/shader/storage_seed.cpp
 * @brief       A shader cache shipped with a title, seeding the player's (RG-GDK-064)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/graphics/pipeline/shader/storage_seed.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iterator>
#include <optional>
#include <unordered_set>
#include <vector>

#include <fmt/format.h>

#include <rex/hash.h>

namespace rex::graphics {
namespace {

using Bytes = std::vector<uint8_t>;

std::optional<Bytes> ReadFile(const std::filesystem::path& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return std::nullopt;
  }
  return Bytes(std::istreambuf_iterator<char>(file), {});
}

struct Record {
  uint64_t hash;
  std::span<const uint8_t> bytes;  // the whole record
};

// The valid records after the header, in order, stopping at the first
// damaged or cut-off one. Empty when the header is not `format`'s.
std::optional<std::vector<Record>> Records(const Bytes& file, const StorageFormat& format) {
  if (file.size() < format.header.size() ||
      !std::equal(format.header.begin(), format.header.end(), file.begin())) {
    return std::nullopt;
  }
  std::vector<Record> records;
  size_t at = format.header.size();
  for (;;) {
    size_t size = format.record_size, covered_at = 8;
    if (!format.record_size) {
      if (file.size() - at < 12) {
        break;
      }
      uint32_t field;
      std::memcpy(&field, &file[at + 8], 4);
      size = 12 + size_t(field & 0x7FFFFFFF) * 4;
      covered_at = 12;
    }
    if (size < covered_at || file.size() - at < size) {
      break;
    }
    uint64_t hash;
    std::memcpy(&hash, &file[at], 8);
    if (XXH3_64bits(&file[at + covered_at], size - covered_at) != hash) {
      break;
    }
    records.push_back({hash, std::span<const uint8_t>(&file[at], size)});
    at += size;
  }
  return records;
}

bool Write(const std::filesystem::path& path, std::span<const uint8_t> header,
           std::span<const Record> first, std::span<const Record> second, std::string* error) {
  const std::filesystem::path temp = path.string() + ".seed";
  {
    std::ofstream file(temp, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(header.data()), std::streamsize(header.size()));
    for (std::span<const Record> records : {first, second}) {
      for (const Record& r : records) {
        file.write(reinterpret_cast<const char*>(r.bytes.data()), std::streamsize(r.bytes.size()));
      }
    }
    if (!file) {
      *error = fmt::format("could not write {}", temp.string());
      return false;
    }
  }
  std::error_code ec;
  std::filesystem::rename(temp, path, ec);
  if (ec) {
    std::filesystem::remove(temp, ec);
    *error = fmt::format("could not replace {}", path.string());
    return false;
  }
  return true;
}

}  // namespace

SeedOutcome SeedStorageFile(const std::filesystem::path& shipped, const std::filesystem::path& user,
                            const StorageFormat& format) {
  SeedOutcome outcome;
  const auto shipped_bytes = ReadFile(shipped);
  if (!shipped_bytes) {
    return outcome;
  }
  const auto shipped_records = Records(*shipped_bytes, format);
  if (!shipped_records) {
    outcome.result = SeedResult::kStale;
    return outcome;
  }
  const auto user_bytes = ReadFile(user);
  const auto user_records = user_bytes ? Records(*user_bytes, format) : std::nullopt;
  if (!user_records) {
    // The player has none, or another version's, which the pipeline cache
    // would discard.
    if (!Write(user, format.header, *shipped_records, {}, &outcome.error)) {
      outcome.result = SeedResult::kFailed;
      return outcome;
    }
    outcome.result = SeedResult::kCopied;
    outcome.added = shipped_records->size();
    return outcome;
  }
  std::unordered_set<uint64_t> known;
  for (const Record& r : *user_records) {
    known.insert(r.hash);
  }
  std::vector<Record> missing;
  for (const Record& r : *shipped_records) {
    if (known.insert(r.hash).second) {
      missing.push_back(r);
    }
  }
  if (missing.empty()) {
    outcome.result = SeedResult::kUpToDate;
    return outcome;
  }
  if (!Write(user, format.header, *user_records, missing, &outcome.error)) {
    outcome.result = SeedResult::kFailed;
    return outcome;
  }
  outcome.result = SeedResult::kMerged;
  outcome.added = missing.size();
  return outcome;
}

}  // namespace rex::graphics
