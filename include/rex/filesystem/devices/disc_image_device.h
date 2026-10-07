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

#pragma once

#include <memory>
#include <string>

#include <rex/filesystem/device.h>
#include <rex/filesystem.h>
#include <mutex>
#include <set>
#include <span>
#include <functional>

namespace rex::filesystem {

class DiscImageEntry;

class DiscImageDevice : public Device {
 public:
  DiscImageDevice(const std::string_view mount_path, const std::filesystem::path& host_path);
  // Reader injection for synthetic media and deterministic I/O failure tests.
  DiscImageDevice(std::string_view mount_path, std::unique_ptr<FileHandle> reader, size_t size);
  ~DiscImageDevice() override;

  bool Initialize() override;
  void Dump(string::StringBuffer* string_buffer) override;
  Entry* ResolvePath(const std::string_view path) override;

  struct DiscInfo {
    size_t game_offset;
    size_t root_sector;
    size_t root_size;
    size_t host_size;
  };

  const Entry* root() const { return root_entry_.get(); }
  uint64_t file_count() const { return file_count_; }
  uint64_t total_file_size() const { return total_file_size_; }
  const DiscInfo& disc_info() const { return disc_info_; }
  // Exact positioned read. Short reads and host errors are failures, never a
  // pointer into removable media. File handles remain serialized.
  bool ReadBytes(size_t offset, std::span<uint8_t> bytes);
  // Called only after a failed read; recovery is serialized across guest I/O.
  void SetFailureHandler(std::function<bool()> handler, std::function<bool()> allowed = {});
  // Caller validates the source executable too. Directory layout must match
  // before retaining existing guest file entries and replacing the reader.
  bool ReconnectFrom(DiscImageDevice& replacement);

  const std::string& name() const override { return name_; }
  uint32_t attributes() const override { return 0; }
  uint32_t component_name_max_length() const override { return 255; }

  uint32_t total_allocation_units() const override {
    return uint32_t(disc_info_.host_size / sectors_per_allocation_unit() / bytes_per_sector());
  }
  uint32_t available_allocation_units() const override { return 0; }
  uint32_t sectors_per_allocation_unit() const override { return 1; }
  uint32_t bytes_per_sector() const override { return 0x200; }

 private:
  std::string name_;
  std::filesystem::path host_path_;
  std::unique_ptr<Entry> root_entry_;
  std::unique_ptr<FileHandle> reader_;
  std::mutex reader_mutex_;
  std::mutex recovery_mutex_;
  std::function<bool()> failure_handler_;
  std::function<bool()> recovery_allowed_;
  std::string media_signature_;
  DiscInfo disc_info_{};
  uint64_t file_count_ = 0;
  uint64_t total_file_size_ = 0;

  std::set<size_t> directory_offsets_;
  size_t metadata_bytes_ = 0;
  bool ReadDirectory(size_t offset, size_t size, DiscImageEntry* parent, unsigned depth);
  bool ReadBytesOnce(size_t offset, std::span<uint8_t> bytes);
};

}  // namespace rex::filesystem
