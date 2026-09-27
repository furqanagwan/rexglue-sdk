/**
 * @file        kernel_fixture.h
 * @brief       Shared image-less Runtime and content helpers for kernel_tests
 *
 * One Runtime per process (its guest Memory is process-wide), set up without a
 * title image. Content cases each use their own ContentManager over a
 * temporary root, so saves are disposable copies.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <memory>
#include <span>
#include <string>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>
#include <rex/filesystem/vfs.h>
#include <rex/logging.h>
#include <rex/runtime.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xam/content_manager.h>
#include <rex/system/xfile.h>
#include <rex/system/xobject.h>

namespace rex::testing {

using rex::X_RESULT;
using rex::X_STATUS;
using rex::system::KernelState;
using rex::system::object_ref;
using rex::system::XContentType;
using rex::system::XFile;
using rex::system::xam::XCONTENT_AGGREGATE_DATA;

constexpr uint64_t kXuid = 0xE000000012345678ull;
constexpr uint32_t kTitleId = 0x4D5307E6;
inline KernelState* Kernel() {
  static std::filesystem::path root = [] {
    rex::InitLogging();
    auto path = std::filesystem::temp_directory_path() /
                ("rexglue_kernel_tests_" + std::to_string(GetCurrentProcessId()));
    std::filesystem::create_directories(path);
    return path;
  }();
  static std::unique_ptr<rex::Runtime> runtime = [] {
    auto r = std::make_unique<rex::Runtime>(root);
    REQUIRE(r->Setup(rex::RuntimeConfig{}) == X_STATUS_SUCCESS);
    return r;
  }();
  return runtime->kernel_state();
}

struct TempDir {
  explicit TempDir(const std::string& name)
      : path(std::filesystem::temp_directory_path() /
             (name + "_" + std::to_string(GetCurrentProcessId()) + "_" +
              std::to_string(GetTickCount64()))) {
    std::filesystem::create_directories(path);
  }
  ~TempDir() {
    std::error_code ec;
    std::filesystem::remove_all(path, ec);
  }
  std::filesystem::path path;
};

inline XCONTENT_AGGREGATE_DATA SaveData(const std::string& file_name) {
  XCONTENT_AGGREGATE_DATA data = {};
  data.device_id = 1;
  data.content_type = XContentType::kSavedGame;
  data.set_display_name(u"Slot 1");
  data.set_file_name(file_name);
  data.xuid = kXuid;
  data.title_id = kTitleId;
  return data;
}

inline std::filesystem::path HeaderPath(const std::filesystem::path& root,
                                        const std::string& file_name) {
  return root / "E000000012345678" / "4D5307E6" / "Headers" / "00000001" / (file_name + ".header");
}

inline std::filesystem::path PackagePath(const std::filesystem::path& root,
                                         const std::string& file_name) {
  return root / "E000000012345678" / "4D5307E6" / "00000001" / file_name;
}

// Opens `path` inside mounted root `root_name` for writing, as the guest's
// NtCreateFile would, and wraps it in a kernel file object.
inline object_ref<XFile> OpenGuestFile(KernelState* kernel, const std::string& root_name,
                                       const std::string& path) {
  rex::filesystem::File* file = nullptr;
  rex::filesystem::FileAction action;
  const X_STATUS status = kernel->file_system()->OpenFile(
      nullptr, root_name + ":\\" + path, rex::filesystem::FileDisposition::kOverwriteIf,
      rex::filesystem::FileAccess::kGenericRead | rex::filesystem::FileAccess::kGenericWrite, false,
      true, &file, &action);
  REQUIRE(status == X_STATUS_SUCCESS);
  REQUIRE(file);
  return object_ref<XFile>(new XFile(kernel, file, true));
}

inline void WriteGuest(XFile* file, const std::string& bytes) {
  size_t written = 0;
  REQUIRE(file->file()->WriteSync({reinterpret_cast<const uint8_t*>(bytes.data()), bytes.size()}, 0,
                                  &written) == X_STATUS_SUCCESS);
  REQUIRE(written == bytes.size());
}

inline std::string ReadHost(const std::filesystem::path& path) {
  std::ifstream in(path, std::ios::binary);
  return std::string(std::istreambuf_iterator<char>(in), {});
}

// A file whose host flush fails, standing in for a disk that rejects it.
class FailingFlushFile : public rex::filesystem::File {
 public:
  explicit FailingFlushFile(rex::filesystem::Entry* entry)
      : File(rex::filesystem::FileAccess::kGenericWrite, entry) {}
  void Destroy() override { delete this; }
  X_STATUS ReadSync(std::span<uint8_t>, size_t, size_t*) override { return X_STATUS_SUCCESS; }
  X_STATUS WriteSync(std::span<const uint8_t>, size_t, size_t*) override {
    return X_STATUS_SUCCESS;
  }
  X_STATUS Flush() override { return X_STATUS_UNEXPECTED_IO_ERROR; }
};

}  // namespace rex::testing
