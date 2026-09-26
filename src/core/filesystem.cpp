/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <algorithm>

#include <rex/filesystem.h>

namespace rex {
namespace filesystem {

bool CreateParentFolder(const std::filesystem::path& path) {
  if (path.has_parent_path()) {
    auto parent_path = path.parent_path();
    if (!std::filesystem::exists(parent_path)) {
      return std::filesystem::create_directories(parent_path);
    }
  }
  return true;
}

bool WriteFileDurably(const std::filesystem::path& path, std::span<const uint8_t> bytes) {
  auto temp_path = path;
  temp_path += ".tmp";
  if (!CreateEmptyFile(temp_path)) {
    return false;
  }
  {
    auto handle = FileHandle::OpenExisting(temp_path, FileAccess::kFileWriteData);
    size_t written = 0;
    if (!handle || !handle->Write(0, bytes.data(), bytes.size(), &written) ||
        written != bytes.size() || !handle->Flush()) {
      handle.reset();
      std::error_code ec;
      std::filesystem::remove(temp_path, ec);
      return false;
    }
  }
  std::error_code ec;
  std::filesystem::rename(temp_path, path, ec);
  if (ec) {
    std::filesystem::remove(temp_path, ec);
    return false;
  }
  return true;
}

}  // namespace filesystem
}  // namespace rex
