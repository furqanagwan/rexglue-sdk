/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <filesystem>
#include <iterator>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <rex/platform.h>
#include <rex/string.h>

namespace rex {

std::string path_to_utf8(const std::filesystem::path& path);
std::u16string path_to_utf16(const std::filesystem::path& path);
std::filesystem::path to_path(const std::string_view source);
std::filesystem::path to_path(const std::u16string_view source);

namespace filesystem {

std::filesystem::path GetExecutablePath();

std::filesystem::path GetExecutableFolder();

std::filesystem::path GetUserFolder();

bool CreateParentFolder(const std::filesystem::path& path);

bool CreateEmptyFile(const std::filesystem::path& path);

bool WriteFileDurably(const std::filesystem::path& path, std::span<const uint8_t> bytes);

FILE* OpenFile(const std::filesystem::path& path, const std::string_view mode);

bool Seek(FILE* file, int64_t offset, int origin);

int64_t Tell(FILE* file);

bool TruncateStdioFile(FILE* file, uint64_t length);

struct FileAccess {
  static const uint32_t kGenericRead = 0x80000000;

  static const uint32_t kGenericWrite = 0x40000000;
  static const uint32_t kGenericExecute = 0x20000000;
  static const uint32_t kGenericAll = 0x10000000;
  static const uint32_t kFileReadData = 0x00000001;
  static const uint32_t kFileWriteData = 0x00000002;
  static const uint32_t kFileAppendData = 0x00000004;
};

class FileHandle {
 public:
  static std::unique_ptr<FileHandle> OpenExisting(const std::filesystem::path& path,
                                                  uint32_t desired_access,
                                                  bool allow_share_delete = false);

  virtual ~FileHandle() = default;

  const std::filesystem::path& path() const { return path_; }

  virtual bool Read(size_t file_offset, void* buffer, size_t buffer_length,
                    size_t* out_bytes_read) = 0;

  virtual bool Write(size_t file_offset, const void* buffer, size_t buffer_length,
                     size_t* out_bytes_written) = 0;

  virtual bool SetLength(size_t length) = 0;

  virtual bool Flush() = 0;

 protected:
  explicit FileHandle(const std::filesystem::path& path) : path_(path) {}

  std::filesystem::path path_;
};

struct FileInfo {
  enum class Type {
    kFile,
    kDirectory,
  };
  Type type;
  std::filesystem::path name;
  std::filesystem::path path;
  size_t total_size;
  uint64_t create_timestamp;
  uint64_t access_timestamp;
  uint64_t write_timestamp;
};
bool GetInfo(const std::filesystem::path& path, FileInfo* out_info);
std::vector<FileInfo> ListFiles(const std::filesystem::path& path);

}
}
