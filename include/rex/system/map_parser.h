/**
 * @file        runtime/map_parser.h
 * @brief       Utilities for parsing symbol map files
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <expected>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include <rex/system/binary_types.h>

namespace rex::runtime {

struct MapParseOptions {
  uint32_t base_address = 0;

  bool functions_only = false;

  std::string_view prefix_filter;
};

enum class MapParseError { FileNotFound, FileReadError, InvalidFormat, Empty };

constexpr std::string_view to_string(MapParseError error) {
  switch (error) {
    case MapParseError::FileNotFound:
      return "File not found";
    case MapParseError::FileReadError:
      return "Failed to read file";
    case MapParseError::InvalidFormat:
      return "Invalid map format";
    case MapParseError::Empty:
      return "No symbols found";
  }
  return "Unknown error";
}

std::expected<std::vector<BinarySymbol>, MapParseError> ParseNmMap(
    const std::filesystem::path& map_path, const MapParseOptions& options = {});

std::expected<std::vector<BinarySymbol>, MapParseError> ParseNmMapString(
    std::string_view map_data, const MapParseOptions& options = {});

}
