// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once
#include <filesystem>
#include <functional>
#include <memory>
#include <span>
#include <string>
#include <rex/filesystem/device.h>

namespace rex::system {
struct GameSourceIdentity {
  uint32_t title_id = 0;
  std::string executable_checksum;  // XXH3-128 of the original XEX file, not an entitlement.
  std::string title_name;           // The XDBF display name, for messages; empty when unknown.
};
struct GameSourceResult {
  std::filesystem::path source_path;
  std::unique_ptr<filesystem::Device> device;
  GameSourceIdentity identity;
  std::string error;
  explicit operator bool() const { return device && error.empty(); }
};
// Header-only inspection; encrypted/compressed payloads are not decoded.
uint32_t XexSourceTitleId(std::span<const uint8_t> header);
// The display name in a whole XEX file's XDBF resource (decrypting and
// decompressing its image), or empty. Safe on arbitrary bytes.
std::string XexTitleName(std::span<const uint8_t> xex);
GameSourceResult InspectGameSource(const std::filesystem::path& path,
                                   std::string_view executable = "default.xex",
                                   const GameSourceIdentity& expected = {},
                                   const std::function<bool()>& cancelled = {});
struct GameSourceExtraction {
  std::filesystem::path folder;
  std::string error;
  bool cancelled = false;
  explicit operator bool() const { return !folder.empty() && error.empty() && !cancelled; }
};
// Copy a validated image to a new folder. Existing destinations are preserved;
// only an owned staging directory is cleaned up on cancellation or failure.
GameSourceExtraction ExtractGameSource(const std::filesystem::path& image,
                                       const std::filesystem::path& destination,
                                       const GameSourceIdentity& expected,
                                       const std::function<void(uint64_t, uint64_t)>& progress = {},
                                       const std::function<bool()>& cancelled = {},
                                       std::string_view executable = "default.xex");
}  // namespace rex::system
