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
  std::string executable_checksum;
  std::string title_name;
};
struct GameSourceResult {
  std::filesystem::path source_path;
  std::unique_ptr<filesystem::Device> device;
  GameSourceIdentity identity;
  std::string error;
  explicit operator bool() const { return device && error.empty(); }
};

uint32_t XexSourceTitleId(std::span<const uint8_t> header);

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

GameSourceExtraction ExtractGameSource(const std::filesystem::path& image,
                                       const std::filesystem::path& destination,
                                       const GameSourceIdentity& expected,
                                       const std::function<void(uint64_t, uint64_t)>& progress = {},
                                       const std::function<bool()>& cancelled = {},
                                       std::string_view executable = "default.xex");
}
