// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <windows.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

#include <rex/filesystem/devices/stfs_container_device.h>

#include "walk_entries.h"

namespace {

std::filesystem::path PackagePath() {
  static const std::filesystem::path path = [] {
    auto dir = std::filesystem::temp_directory_path() /
               ("rex_stfs_fuzz_" + std::to_string(GetCurrentProcessId()));
    std::filesystem::create_directories(dir);
    return dir / "package";
  }();
  return path;
}

}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const auto path = PackagePath();
  {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<const char*>(data), std::streamsize(size));
  }
  rex::filesystem::StfsContainerDevice device("\\Device\\Fuzz", path);
  if (!device.Initialize()) {
    return 0;
  }
  rex::fuzz::WalkEntries(device.ResolvePath(""));
  return 0;
}
