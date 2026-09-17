#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <span>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include <rex/filesystem.h>
#include <rex/filesystem/devices/host_path_device.h>
#include <rex/filesystem/entry.h>
#include <rex/filesystem/vfs.h>

using rex::X_STATUS;
using rex::filesystem::FileAccess;
using rex::filesystem::FileAction;
using rex::filesystem::FileDisposition;
using rex::filesystem::HostPathDevice;
using rex::filesystem::VirtualFileSystem;

namespace {

constexpr std::string_view kMountPath = "\\TestStore";
constexpr std::string_view kSymlink = "test:";
constexpr std::string_view kGuestPath = "test:\\savegame.dat";
constexpr std::string_view kOriginal = "AAAA";

class ScopedStore {
 public:
  ScopedStore() {
    root_ = std::filesystem::temp_directory_path() /
            ("rexglue_vfs_overwrite_" + std::to_string(counter_++));
    std::error_code ec;
    std::filesystem::remove_all(root_, ec);
    std::filesystem::create_directories(root_, ec);

    FILE* file = rex::filesystem::OpenFile(host_path(), "wb");
    REQUIRE(file != nullptr);
    fwrite(kOriginal.data(), 1, kOriginal.size(), file);
    fclose(file);

    auto device = std::make_unique<HostPathDevice>(kMountPath, root_, false, true);
    REQUIRE(device->Initialize());
    REQUIRE(vfs_.RegisterDevice(std::move(device)));
    REQUIRE(vfs_.RegisterSymbolicLink(kSymlink, kMountPath));
  }

  ~ScopedStore() {
    std::error_code ec;
    std::filesystem::remove_all(root_, ec);
  }

  VirtualFileSystem& vfs() { return vfs_; }

  std::filesystem::path host_path() const { return root_ / "savegame.dat"; }

 private:
  static int counter_;
  std::filesystem::path root_;
  VirtualFileSystem vfs_;
};

int ScopedStore::counter_ = 0;

}  // namespace

TEST_CASE("VFS overwrite truncates in place instead of deleting", "[filesystem][vfs]") {
  ScopedStore store;

  rex::filesystem::File* reader = nullptr;
  FileAction action = FileAction::kDoesNotExist;
  REQUIRE(store.vfs().OpenFile(nullptr, kGuestPath, FileDisposition::kOpen,
                               FileAccess::kGenericRead, false, true, &reader,
                               &action) == X_STATUS_SUCCESS);
  REQUIRE(reader != nullptr);
  CHECK(action == FileAction::kOpened);

  rex::filesystem::File* writer = nullptr;
  REQUIRE(store.vfs().OpenFile(nullptr, kGuestPath, FileDisposition::kOverwriteIf,
                               FileAccess::kGenericWrite, false, true, &writer,
                               &action) == X_STATUS_SUCCESS);
  REQUIRE(writer != nullptr);
  CHECK(action == FileAction::kOverwritten);
  CHECK(std::filesystem::file_size(store.host_path()) == 0);

  const std::array<uint8_t, 1> payload{'B'};
  size_t written = 0;
  REQUIRE(writer->WriteSync(std::span<const uint8_t>(payload), 0, &written) == X_STATUS_SUCCESS);
  CHECK(written == payload.size());

  std::array<uint8_t, 8> buffer{};
  size_t read = 0;
  CHECK(reader->ReadSync(std::span<uint8_t>(buffer), 0, &read) == X_STATUS_SUCCESS);
  CHECK(read == payload.size());
  CHECK(buffer[0] == 'B');

  writer->Destroy();
  reader->Destroy();

  CHECK(std::filesystem::exists(store.host_path()));
  CHECK(std::filesystem::file_size(store.host_path()) == payload.size());
}

TEST_CASE("VFS overwrite of a file held open by a reader keeps the file", "[filesystem][vfs]") {
  ScopedStore store;

  rex::filesystem::File* reader = nullptr;
  FileAction action = FileAction::kDoesNotExist;
  REQUIRE(store.vfs().OpenFile(nullptr, kGuestPath, FileDisposition::kOpen,
                               FileAccess::kGenericRead, false, true, &reader,
                               &action) == X_STATUS_SUCCESS);

  rex::filesystem::File* writer = nullptr;
  REQUIRE(store.vfs().OpenFile(nullptr, kGuestPath, FileDisposition::kSuperscede,
                               FileAccess::kGenericWrite, false, true, &writer,
                               &action) == X_STATUS_SUCCESS);
  CHECK(action == FileAction::kSuperseded);

  writer->Destroy();
  reader->Destroy();

  CHECK(std::filesystem::exists(store.host_path()));
}

TEST_CASE("Host path title-update overlay replaces and extends the disc tree",
          "[filesystem][vfs][title_update]") {
  const auto root = std::filesystem::temp_directory_path() / "rexglue_title_update_overlay";
  const auto disc = root / "disc";
  const auto update = root / "update";
  std::error_code ec;
  std::filesystem::remove_all(root, ec);
  std::filesystem::create_directories(disc / "data", ec);
  std::filesystem::create_directories(update / "data", ec);

  auto write = [](const std::filesystem::path& path, std::string_view value) {
    FILE* file = rex::filesystem::OpenFile(path, "wb");
    REQUIRE(file != nullptr);
    REQUIRE(fwrite(value.data(), 1, value.size(), file) == value.size());
    fclose(file);
  };
  write(disc / "data" / "disc_only.bin", "disc");
  write(disc / "data" / "replaced.bin", "old");
  write(update / "data" / "replaced.bin", "new");
  write(update / "data" / "update_only.bin", "update");

  VirtualFileSystem vfs;
  auto device = std::make_unique<HostPathDevice>(kMountPath, update, true, false, disc);
  REQUIRE(device->Initialize());
  REQUIRE(vfs.RegisterDevice(std::move(device)));
  REQUIRE(vfs.RegisterSymbolicLink(kSymlink, kMountPath));

  auto* disc_only = vfs.ResolvePath("test:\\data\\disc_only.bin");
  auto* replaced = vfs.ResolvePath("test:\\data\\replaced.bin");
  auto* update_only = vfs.ResolvePath("test:\\data\\update_only.bin");
  REQUIRE(disc_only != nullptr);
  REQUIRE(replaced != nullptr);
  REQUIRE(update_only != nullptr);

  auto read = [&](std::string_view path) {
    rex::filesystem::File* file = nullptr;
    FileAction action = FileAction::kDoesNotExist;
    REQUIRE(vfs.OpenFile(nullptr, path, FileDisposition::kOpen, FileAccess::kGenericRead, false,
                         true, &file, &action) == X_STATUS_SUCCESS);
    std::array<uint8_t, 16> bytes{};
    size_t count = 0;
    REQUIRE(file->ReadSync(std::span<uint8_t>(bytes), 0, &count) == X_STATUS_SUCCESS);
    file->Destroy();
    return std::string(reinterpret_cast<const char*>(bytes.data()), count);
  };
  CHECK(read("test:\\data\\disc_only.bin") == "disc");
  CHECK(read("test:\\data\\replaced.bin") == "new");
  CHECK(read("test:\\data\\update_only.bin") == "update");

  auto* data = vfs.ResolvePath("test:\\data");
  REQUIRE(data != nullptr);
  CHECK(data->child_count() == 3);
  std::filesystem::remove_all(root, ec);
}
