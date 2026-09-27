/**
 * @file        stfs_container_test.cpp
 * @brief       STFS/SVOD reader on synthetic and malformed packages (RG-GDK-017)
 *
 * Packages are built here: a read-only STFS with one hash table, a file table
 * block and data blocks, and a single-file SVOD. The malformed cases are those
 * packages with one field damaged or cut short; each must be refused or read
 * partially, never read out of bounds or asserted on.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstring>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <rex/filesystem/devices/stfs_container_device.h>
#include <rex/filesystem/devices/stfs_xbox.h>
#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>

using namespace rex::filesystem;  // NOLINT
using rex::X_STATUS;

namespace {

constexpr size_t kBlock = 0x1000;
constexpr size_t kHeaderSize = sizeof(StfsHeader);  // 0x971A, rounded to 0xA000
constexpr size_t kHashTable = 0xA000;               // level 0 table for blocks 0-169
constexpr uint32_t kEnd = 0xFFFFFF;

// Block b (< 170) of a read-only STFS sits after the table: 0xA000 + (b+1) * 4K.
size_t BlockOffset(uint32_t b) {
  return kHashTable + (b + 1) * kBlock;
}

struct Package {
  std::vector<uint8_t> bytes;

  StfsHeader& header() { return *reinterpret_cast<StfsHeader*>(bytes.data()); }
  StfsHashTable& hashes() { return *reinterpret_cast<StfsHashTable*>(&bytes[kHashTable]); }
  StfsDirectoryEntry& entry(size_t i) {
    return reinterpret_cast<StfsDirectoryBlock*>(&bytes[BlockOffset(0)])->entries[i];
  }
};

// A package with one file, `name`, of `data` bytes in consecutive blocks
// starting at block 1.
Package MakeStfs(const std::string& name, const std::string& data) {
  const uint32_t data_blocks = uint32_t((data.size() + kBlock - 1) / kBlock);
  Package p;
  p.bytes.assign(BlockOffset(1 + data_blocks), 0);
  auto& h = p.header();
  h.header.magic = XContentPackageType::kCon;
  h.header.header_size = uint32_t(kHeaderSize);
  h.metadata.content_type = rex::system::XContentType::kSavedGame;
  h.metadata.volume_type = XContentVolumeType::kStfs;
  h.metadata.data_file_count = 0;
  auto& d = h.metadata.volume_descriptor.stfs;
  d.descriptor_length = sizeof(StfsVolumeDescriptor);
  d.flags.bits.read_only_format = 1;
  d.file_table_block_count = 1;
  d.set_file_table_block_number(0);
  d.total_block_count = 1 + data_blocks;

  p.hashes().entries[0].set_level0_next_block(kEnd);  // file table
  for (uint32_t b = 1; b <= data_blocks; ++b) {
    p.hashes().entries[b].set_level0_next_block(b == data_blocks ? kEnd : b + 1);
  }

  auto& e = p.entry(0);
  std::memcpy(e.name, name.data(), name.size());
  e.flags.name_length = uint8_t(name.size());
  e.set_valid_data_blocks(data_blocks);
  e.set_allocated_data_blocks(data_blocks);
  e.set_start_block_number(1);
  e.directory_index = 0xFFFF;
  e.length = uint32_t(data.size());
  std::memcpy(&p.bytes[BlockOffset(1)], data.data(), data.size());
  return p;
}

struct TempFile {
  explicit TempFile(const std::vector<uint8_t>& bytes, const std::string& name = "package") {
    dir = std::filesystem::temp_directory_path() /
          ("rex_stfs_" + std::to_string(reinterpret_cast<uintptr_t>(this)));
    std::filesystem::create_directories(dir);
    path = dir / name;
    std::ofstream(path, std::ios::binary)
        .write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
  }
  ~TempFile() {
    std::error_code ec;
    std::filesystem::remove_all(dir, ec);
  }
  std::filesystem::path dir;
  std::filesystem::path path;
};

std::unique_ptr<StfsContainerDevice> Mount(const std::filesystem::path& path) {
  auto device = std::make_unique<StfsContainerDevice>("\\Device\\Test", path);
  return device->Initialize() ? std::move(device) : nullptr;
}

std::string ReadAll(Entry* entry, size_t capacity = 3 * kBlock) {
  File* file = nullptr;
  REQUIRE(entry->Open(FileAccess::kGenericRead, &file) == X_STATUS_SUCCESS);
  std::string out(capacity, '\0');
  size_t read = 0;
  file->ReadSync({reinterpret_cast<uint8_t*>(out.data()), out.size()}, 0, &read);
  file->Destroy();
  out.resize(read);
  return out;
}

}  // namespace

TEST_CASE("A well-formed STFS package mounts and reads back", "[filesystem][stfs]") {
  const std::string data(kBlock + 100, 'x');
  TempFile file(MakeStfs("save.dat", data).bytes);
  auto device = Mount(file.path);
  REQUIRE(device);
  Entry* entry = device->ResolvePath("save.dat");
  REQUIRE(entry);
  CHECK(entry->size() == data.size());
  CHECK(ReadAll(entry) == data);
}

TEST_CASE("STFS path lookup ignores case", "[filesystem][stfs]") {
  TempFile file(MakeStfs("Save.Dat", "abc").bytes);
  auto device = Mount(file.path);
  REQUIRE(device);
  CHECK(device->ResolvePath("SAVE.DAT") == device->ResolvePath("save.dat"));
  CHECK(device->ResolvePath("save.dat"));
}

TEST_CASE("STFS names two entries apart only by case: the first one wins", "[filesystem][stfs]") {
  auto p = MakeStfs("a.bin", "first");
  auto& second = p.entry(1);
  second = p.entry(0);
  second.name[0] = 'A';
  TempFile file(p.bytes);
  auto device = Mount(file.path);
  REQUIRE(device);
  Entry* entry = device->ResolvePath("A.BIN");
  REQUIRE(entry);
  CHECK(entry->name() == "a.bin");
}

TEST_CASE("An STFS package cut short in its file table is refused", "[filesystem][stfs]") {
  auto p = MakeStfs("save.dat", "abc");
  p.bytes.resize(BlockOffset(0) + 0x200);
  TempFile file(p.bytes);
  CHECK_FALSE(Mount(file.path));
}

TEST_CASE("An STFS file whose data is cut short reads only what exists", "[filesystem][stfs]") {
  const std::string data(2 * kBlock, 'y');
  auto p = MakeStfs("save.dat", data);
  p.bytes.resize(BlockOffset(2) + 10);  // second data block mostly missing
  TempFile file(p.bytes);
  auto device = Mount(file.path);
  REQUIRE(device);
  CHECK(ReadAll(device->ResolvePath("save.dat")) == std::string(kBlock + 10, 'y'));
}

TEST_CASE("An STFS block chain that leaves the package stops there", "[filesystem][stfs]") {
  // Block 1 claims its successor is block 200, whose hash table would lie far
  // past the end of the file (xenia-canary #1226 crash shape).
  auto p = MakeStfs("save.dat", std::string(kBlock, 'z'));
  p.entry(0).length = uint32_t(3 * kBlock);
  p.entry(0).set_allocated_data_blocks(3);
  p.hashes().entries[1].set_level0_next_block(200);
  TempFile file(p.bytes);
  auto device = Mount(file.path);
  REQUIRE(device);
  // Block 1 and the out-of-package block 200 were recorded; reading stops at
  // the end of the file instead of misplacing data.
  CHECK(ReadAll(device->ResolvePath("save.dat")) == std::string(kBlock, 'z'));
}

TEST_CASE("An STFS file table chain that leaves the package is refused", "[filesystem][stfs]") {
  auto p = MakeStfs("save.dat", "abc");
  p.header().metadata.volume_descriptor.stfs.file_table_block_count = 2;
  p.hashes().entries[0].set_level0_next_block(200);
  TempFile file(p.bytes);
  CHECK_FALSE(Mount(file.path));
}

TEST_CASE("An STFS entry naming a parent it has not seen is refused", "[filesystem][stfs]") {
  auto p = MakeStfs("save.dat", "abc");
  p.entry(0).directory_index = 5;
  TempFile file(p.bytes);
  CHECK_FALSE(Mount(file.path));
}

TEST_CASE("An STFS entry naming a file as its parent is refused", "[filesystem][stfs]") {
  auto p = MakeStfs("save.dat", "abc");
  p.entry(1) = p.entry(0);
  p.entry(1).name[0] = 'x';
  p.entry(1).directory_index = 0;  // entry 0 is a file
  TempFile file(p.bytes);
  CHECK_FALSE(Mount(file.path));
}

TEST_CASE("An STFS name length past the name field is clamped", "[filesystem][stfs]") {
  auto p = MakeStfs("abcdefghijklmnopqrstuvwxyz0123456789ABCD", "abc");  // 40 chars
  p.entry(0).flags.name_length = 63;
  TempFile file(p.bytes);
  auto device = Mount(file.path);
  REQUIRE(device);
  CHECK(device->ResolvePath("abcdefghijklmnopqrstuvwxyz0123456789ABCD"));
}

TEST_CASE("An STFS package holding less data than its metadata says is refused",
          "[filesystem][stfs]") {
  auto p = MakeStfs("save.dat", "abc");
  const uint64_t data_size = p.bytes.size() - kHashTable;
  p.header().metadata.content_size = data_size;
  {
    TempFile whole(p.bytes);
    CHECK(Mount(whole.path));
  }
  p.header().metadata.content_size = data_size + kBlock;
  TempFile short_file(p.bytes);
  CHECK_FALSE(Mount(short_file.path));
}

TEST_CASE("A folder holding only files too small for a magic is not a package",
          "[filesystem][stfs]") {
  TempFile tiny({0x43, 0x4F}, "tiny.bin");
  auto device = std::make_unique<StfsContainerDevice>("\\Device\\Test", tiny.dir);
  CHECK_FALSE(device->Initialize());
}

TEST_CASE("An SVOD directory node that points back at itself is refused", "[filesystem][svod]") {
  // Single-file SVOD: the media magic at 0xD000 (block 0), root directory at
  // block 2 (0xE000). Node 0 links right to node 8, which links to itself.
  std::vector<uint8_t> bytes(0x13000, 0);  // reaches past the 0x12000 XSF probe
  auto& h = *reinterpret_cast<StfsHeader*>(bytes.data());
  h.header.magic = XContentPackageType::kLive;
  h.header.header_size = uint32_t(kHeaderSize);
  h.metadata.volume_type = XContentVolumeType::kSvod;
  h.metadata.data_file_count = 1;
  h.metadata.volume_descriptor.svod.descriptor_length = sizeof(SvodDeviceDescriptor);
  std::memcpy(&bytes[0xD000], "MICROSOFT*XBOX*MEDIA", 20);
  const uint32_t root_block = 2;
  std::memcpy(&bytes[0xD014], &root_block, 4);
  const uint32_t root_size = 0x800;
  std::memcpy(&bytes[0xD018], &root_size, 4);

  auto node = [&](size_t address, uint16_t right) {
    const uint16_t left = 0;
    std::memcpy(&bytes[address + 0], &left, 2);
    std::memcpy(&bytes[address + 2], &right, 2);
    bytes[address + 13] = 1;  // name length
    bytes[address + 14] = 'n';
  };
  node(0xE000, 8);
  node(0xE000 + 8 * 4, 8);
  TempFile file(bytes);
  CHECK_FALSE(Mount(file.path));
}
