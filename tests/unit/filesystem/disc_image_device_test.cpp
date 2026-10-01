/**
 * @file disc_image_device_test.cpp
 * @brief Synthetic XDVDFS reads and host read failures (RG-GDK-058).
 * @copyright Copyright (c) 2026 Tom Clay
 * @license BSD 3-Clause License
 */

#include <algorithm>
#include <array>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>
#include <rex/filesystem/vfs.h>

using rex::X_STATUS;

namespace {

constexpr size_t kSector = 2048;
constexpr size_t kRoot = 33 * kSector;
constexpr size_t kFile = 34 * kSector;

void Store32(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
  for (size_t i = 0; i < 4; ++i)
    bytes[offset + i] = uint8_t(value >> (i * 8));
}

struct Image {
  std::filesystem::path path =
      std::filesystem::temp_directory_path() /
      ("rexglue_synthetic_disc_reader_" +
       std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".iso");

  explicit Image(bool valid = true, bool has_xex = true, bool valid_xex = true) {
    std::vector<uint8_t> bytes(kFile + 4);
    constexpr char kMagic[] = "MICROSOFT*XBOX*MEDIA";
    std::copy_n(kMagic, 20, bytes.begin() + 32 * kSector);
    Store32(bytes, 32 * kSector + 20, valid ? 33 : 99);
    Store32(bytes, 32 * kSector + 24, 64);
    Store32(bytes, kRoot + 4, 34);
    Store32(bytes, kRoot + 8, 4);
    bytes[kRoot + 13] = 11;
    constexpr char kName[] = "default.xex";
    std::copy_n(kName, 11, bytes.begin() + kRoot + 14);
    if (!has_xex)
      bytes[kRoot + 14] = 'x';
    std::copy_n(valid_xex ? "XEX2" : "BAD!", 4, bytes.begin() + kFile);
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
  }
  ~Image() {
    std::error_code ec;
    std::filesystem::remove(path, ec);
  }
};

}  // namespace

TEST_CASE("XDVDFS reads files through the host file handle", "[filesystem][disc]") {
  Image image;
  rex::filesystem::DiscImageDevice device("game:", image.path);
  REQUIRE(device.Initialize());
  auto* entry = device.ResolvePath("default.xex");
  REQUIRE(entry != nullptr);
  auto mapped = entry->OpenMapped(rex::memory::MappedMemory::Mode::kRead);
  REQUIRE(mapped != nullptr);
  REQUIRE(mapped->size() == 4);
  CHECK(std::memcmp(mapped->data(), "XEX2", 4) == 0);

  rex::filesystem::File* file = nullptr;
  REQUIRE(entry->Open(rex::filesystem::FileAccess::kGenericRead, &file) == X_STATUS_SUCCESS);
  REQUIRE(file != nullptr);
  std::array<uint8_t, 4> buffer{};
  size_t read = 0;
  REQUIRE(file->ReadSync(buffer, 0, &read) == X_STATUS_SUCCESS);
  CHECK(read == 4);
  CHECK(std::memcmp(buffer.data(), "XEX2", 4) == 0);

  std::filesystem::resize_file(image.path, 32 * kSector);
  CHECK(file->ReadSync(buffer, 0, &read) == X_STATUS_UNEXPECTED_IO_ERROR);
  CHECK(read == 0);
  file->Destroy();
}

TEST_CASE("XDVDFS rejects an out-of-range root directory", "[filesystem][disc]") {
  Image image(false);
  rex::filesystem::DiscImageDevice device("game:", image.path);
  CHECK_FALSE(device.Initialize());
}

TEST_CASE("XDVDFS requires a root XEX2 executable", "[filesystem][disc]") {
  Image missing_xex(true, false);
  rex::filesystem::DiscImageDevice missing("game:", missing_xex.path);
  CHECK_FALSE(missing.Initialize());

  Image invalid_xex(true, true, false);
  rex::filesystem::DiscImageDevice invalid("game:", invalid_xex.path);
  CHECK_FALSE(invalid.Initialize());
}

TEST_CASE("VFS resolves a checked XDVDFS image through game:", "[filesystem][disc]") {
  Image image;
  rex::filesystem::VirtualFileSystem vfs;
  auto device = std::make_unique<rex::filesystem::DiscImageDevice>(
      "\\Device\\Harddisk0\\Partition1", image.path);
  REQUIRE(device->Initialize());
  REQUIRE(vfs.RegisterDevice(std::move(device)));
  REQUIRE(vfs.RegisterSymbolicLink("game:", "\\Device\\Harddisk0\\Partition1"));
  auto* entry = vfs.ResolvePath("game:\\default.xex");
  REQUIRE(entry != nullptr);
  auto mapped = entry->OpenMapped(rex::memory::MappedMemory::Mode::kRead);
  REQUIRE(mapped != nullptr);
  CHECK(std::memcmp(mapped->data(), "XEX2", 4) == 0);
}
