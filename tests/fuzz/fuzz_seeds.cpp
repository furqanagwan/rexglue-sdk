// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include <rex/filesystem/devices/stfs_container_device.h>
#include <rex/filesystem/devices/stfs_xbox.h>

namespace {

using Bytes = std::vector<uint8_t>;
using namespace rex::filesystem;  // NOLINT

void AppendBigEndian(Bytes& out, uint64_t value, int width) {
  for (int i = width - 1; i >= 0; --i) {
    out.push_back(uint8_t(value >> (8 * i)));
  }
}

void PutBigEndian32(Bytes& bytes, size_t offset, uint32_t value) {
  for (int i = 0; i < 4; ++i) {
    bytes[offset + i] = uint8_t(value >> (24 - 8 * i));
  }
}

void PutLittleEndian32(Bytes& bytes, size_t offset, uint32_t value) {
  for (int i = 0; i < 4; ++i) {
    bytes[offset + i] = uint8_t(value >> (8 * i));
  }
}

Bytes Xdbf(std::string_view title) {
  Bytes xstr;
  AppendBigEndian(xstr, 0x58535452, 4);
  AppendBigEndian(xstr, 1, 4);
  AppendBigEndian(xstr, 0, 4);
  AppendBigEndian(xstr, 1, 2);
  AppendBigEndian(xstr, 0x8000, 2);
  AppendBigEndian(xstr, title.size(), 2);
  xstr.insert(xstr.end(), title.begin(), title.end());
  Bytes xdbf;
  AppendBigEndian(xdbf, 0x58444246, 4);
  AppendBigEndian(xdbf, 1, 4);
  AppendBigEndian(xdbf, 1, 4);
  AppendBigEndian(xdbf, 1, 4);
  AppendBigEndian(xdbf, 0, 4);
  AppendBigEndian(xdbf, 0, 4);
  AppendBigEndian(xdbf, 3, 2);
  AppendBigEndian(xdbf, 1, 8);
  AppendBigEndian(xdbf, 0, 4);
  AppendBigEndian(xdbf, xstr.size(), 4);
  xdbf.insert(xdbf.end(), xstr.begin(), xstr.end());
  return xdbf;
}

Bytes Xex(std::string_view title) {
  constexpr uint32_t kBase = 0x82000000, kHeaderSize = 0x400, kResource = 0x10;
  const Bytes xdbf = Xdbf(title);
  Bytes bytes(kHeaderSize);
  std::memcpy(bytes.data(), "XEX2", 4);
  PutBigEndian32(bytes, 0x08, kHeaderSize);
  PutBigEndian32(bytes, 0x10, 0x200);
  PutBigEndian32(bytes, 0x14, 3);
  PutBigEndian32(bytes, 0x18, 0x00040006);
  PutBigEndian32(bytes, 0x1C, 0x100);
  PutBigEndian32(bytes, 0x20, 0x000002FF);
  PutBigEndian32(bytes, 0x24, 0x140);
  PutBigEndian32(bytes, 0x28, 0x000003FF);
  PutBigEndian32(bytes, 0x2C, 0x180);
  PutBigEndian32(bytes, 0x100 + 12, 0x12345678);
  PutBigEndian32(bytes, 0x140, 20);
  std::memcpy(bytes.data() + 0x144, "12345678", 8);
  PutBigEndian32(bytes, 0x14C, kBase + kResource);
  PutBigEndian32(bytes, 0x150, uint32_t(xdbf.size()));
  PutBigEndian32(bytes, 0x180, 8);
  PutBigEndian32(bytes, 0x200 + 4, kResource + uint32_t(xdbf.size()));
  PutBigEndian32(bytes, 0x200 + 0x110, kBase);
  bytes.resize(kHeaderSize + kResource);
  bytes.insert(bytes.end(), xdbf.begin(), xdbf.end());
  return bytes;
}

Bytes Xdvdfs(const Bytes& payload) {
  constexpr size_t kSector = 2048;
  constexpr size_t kRoot = 33 * kSector;
  constexpr size_t kPayload = 35 * kSector;
  Bytes bytes(kPayload + payload.size());
  std::memcpy(bytes.data() + 32 * kSector, "MICROSOFT*XBOX*MEDIA", 20);
  std::memcpy(bytes.data() + 33 * kSector - 20, "MICROSOFT*XBOX*MEDIA", 20);
  PutLittleEndian32(bytes, 32 * kSector + 20, 33);
  PutLittleEndian32(bytes, 32 * kSector + 24, 32);
  PutLittleEndian32(bytes, kRoot + 4, 35);
  PutLittleEndian32(bytes, kRoot + 8, uint32_t(payload.size()));
  bytes[kRoot + 13] = 11;
  std::memcpy(bytes.data() + kRoot + 14, "default.xex", 11);
  std::memcpy(bytes.data() + kPayload, payload.data(), payload.size());
  return bytes;
}

Bytes Stfs(const std::string& name, const std::string& data) {
  constexpr size_t kBlock = 0x1000;
  constexpr size_t kHashTable = 0xA000;
  constexpr uint32_t kEnd = 0xFFFFFF;
  auto block_offset = [](uint32_t block) { return kHashTable + (block + 1) * kBlock; };
  const uint32_t data_blocks = uint32_t((data.size() + kBlock - 1) / kBlock);
  Bytes bytes(block_offset(1 + data_blocks));
  auto& header = *reinterpret_cast<StfsHeader*>(bytes.data());
  header.header.magic = XContentPackageType::kCon;
  header.header.header_size = uint32_t(sizeof(StfsHeader));
  header.metadata.content_type = rex::system::XContentType::kSavedGame;
  header.metadata.volume_type = XContentVolumeType::kStfs;
  auto& descriptor = header.metadata.volume_descriptor.stfs;
  descriptor.descriptor_length = sizeof(StfsVolumeDescriptor);
  descriptor.flags.bits.read_only_format = 1;
  descriptor.file_table_block_count = 1;
  descriptor.set_file_table_block_number(0);
  descriptor.total_block_count = 1 + data_blocks;
  auto& hashes = *reinterpret_cast<StfsHashTable*>(&bytes[kHashTable]);
  hashes.entries[0].set_level0_next_block(kEnd);
  for (uint32_t block = 1; block <= data_blocks; ++block) {
    hashes.entries[block].set_level0_next_block(block == data_blocks ? kEnd : block + 1);
  }
  auto& entry = reinterpret_cast<StfsDirectoryBlock*>(&bytes[block_offset(0)])->entries[0];
  std::memcpy(entry.name, name.data(), name.size());
  entry.flags.name_length = uint8_t(name.size());
  entry.set_valid_data_blocks(data_blocks);
  entry.set_allocated_data_blocks(data_blocks);
  entry.set_start_block_number(1);
  entry.directory_index = 0xFFFF;
  entry.length = uint32_t(data.size());
  std::memcpy(&bytes[block_offset(1)], data.data(), data.size());
  return bytes;
}

bool Write(const std::filesystem::path& path, const Bytes& bytes) {
  std::filesystem::create_directories(path.parent_path());
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
  return bool(out);
}

}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::fprintf(stderr, "usage: fuzz_seeds OUTPUT_DIRECTORY\n");
    return 2;
  }
  const std::filesystem::path root = argv[1];
  const Bytes xex = Xex("Seed Title");
  const bool written =
      Write(root / "xex" / "named.xex", xex) &&
      Write(root / "xdbf" / "title.xdbf", Xdbf("Seed Title")) &&
      Write(root / "xdvdfs" / "image.iso", Xdvdfs(xex)) &&
      Write(root / "stfs" / "small.con", Stfs("save.dat", "seed")) &&
      Write(root / "stfs" / "two_blocks.con", Stfs("data.bin", std::string(0x1000 + 100, 'x')));
  return written ? 0 : 1;
}
