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

#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/devices/disc_image_entry.h>
#include <rex/filesystem/devices/optical_disc_reader.h>

#include <array>
#include <cstring>
#include <vector>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/memory.h>
#include <rex/hash.h>

namespace rex::filesystem {
namespace {
constexpr size_t kSector = 2048;
constexpr size_t kMaxDirectory = 32 * 1024 * 1024;
constexpr size_t kMaxMetadata = 256 * 1024 * 1024;
constexpr std::string_view kMagic = "MICROSOFT*XBOX*MEDIA";
}  // namespace

DiscImageDevice::DiscImageDevice(std::string_view mount_path,
                                 const std::filesystem::path& host_path)
    : Device(mount_path), name_("GDFX"), host_path_(host_path) {}

DiscImageDevice::DiscImageDevice(std::string_view mount_path, std::unique_ptr<FileHandle> reader,
                                 size_t size)
    : Device(mount_path), name_("GDFX"), reader_(std::move(reader)) {
  disc_info_.host_size = size;
}

DiscImageDevice::~DiscImageDevice() = default;

bool DiscImageDevice::ReadBytes(size_t offset, std::span<uint8_t> bytes) {
  if (offset > disc_info_.host_size || bytes.size() > disc_info_.host_size - offset)
    return false;
  if (ReadBytesOnce(offset, bytes))
    return true;
  std::function<bool()> handler;
  std::function<bool()> allowed;
  {
    std::lock_guard lock(reader_mutex_);
    handler = failure_handler_;
    allowed = recovery_allowed_;
  }
  if (!handler || (allowed && !allowed()))
    return false;
  std::lock_guard recovery_lock(recovery_mutex_);
  // Another guest I/O thread may already have repaired this source.
  if (ReadBytesOnce(offset, bytes))
    return true;
  while (handler()) {
    if (ReadBytesOnce(offset, bytes))
      return true;
  }
  return false;
}

void DiscImageDevice::SetFailureHandler(std::function<bool()> handler,
                                        std::function<bool()> allowed) {
  std::lock_guard lock(reader_mutex_);
  failure_handler_ = std::move(handler);
  recovery_allowed_ = std::move(allowed);
}

bool DiscImageDevice::ReconnectFrom(DiscImageDevice& replacement) {
  if (&replacement == this || !replacement.root_entry_ || !replacement.reader_ ||
      media_signature_.empty() || replacement.media_signature_ != media_signature_)
    return false;
  std::scoped_lock lock(reader_mutex_, replacement.reader_mutex_);
  reader_ = std::move(replacement.reader_);
  return true;
}

bool DiscImageDevice::ReadBytesOnce(size_t offset, std::span<uint8_t> bytes) {
  std::lock_guard lock(reader_mutex_);
  if (!reader_ || offset > disc_info_.host_size || bytes.size() > disc_info_.host_size - offset)
    return false;
  // FileHandle's Windows implementation uses DWORD read lengths. Bounded
  // chunks also prevent a single request from consuming enormous buffers.
  while (!bytes.empty()) {
    const size_t count = std::min(bytes.size(), size_t(1024 * 1024));
    size_t read = 0;
    if (!reader_->Read(offset, bytes.data(), count, &read) || read != count)
      return false;
    offset += count;
    bytes = bytes.subspan(count);
  }
  return true;
}

bool DiscImageDevice::Initialize() {
  root_entry_.reset();
  file_count_ = total_file_size_ = metadata_bytes_ = 0;
  directory_offsets_.clear();
  media_signature_.clear();
  if (!reader_ && IsOpticalDiscPath(host_path_))
    reader_ = OpenOpticalDisc(host_path_, &disc_info_.host_size);
  if (!reader_ && IsOpticalDiscPath(host_path_))
    return false;
  if (!reader_) {
    FileInfo info{};
    if (!GetInfo(host_path_, &info) || info.type != FileInfo::Type::kFile)
      return false;
    disc_info_.host_size = info.total_size;
    reader_ = FileHandle::OpenExisting(host_path_, FileAccess::kGenericRead, true);
    if (!reader_)
      return false;
  }
  // Preserve the existing supported game-partition offsets.
  constexpr size_t offsets[] = {0, 0xFB20, 0x20600, 0x2080000, 0xFD90000};
  std::array<uint8_t, kSector> header{};
  bool found = false;
  for (const size_t offset : offsets) {
    if (ReadBytes(offset + 32 * kSector, header) &&
        std::memcmp(header.data(), kMagic.data(), kMagic.size()) == 0 &&
        std::memcmp(header.data() + kSector - kMagic.size(), kMagic.data(), kMagic.size()) == 0) {
      disc_info_.game_offset = offset;
      found = true;
      break;
    }
  }
  if (!found) {
    REXFS_ERROR("No readable XDVDFS game partition in disc image");
    return false;
  }
  disc_info_.root_sector = memory::load<uint32_t>(header.data() + 20);
  disc_info_.root_size = memory::load<uint32_t>(header.data() + 24);
  media_signature_ = hash_bytes(
      std::string(reinterpret_cast<const char*>(header.data()), header.size()) + ":" +
      std::to_string(disc_info_.game_offset) + ":" + std::to_string(disc_info_.host_size));
  auto root = std::make_unique<DiscImageEntry>(this, nullptr, "");
  root->attributes_ = kFileAttributeDirectory | kFileAttributeReadOnly;
  const size_t offset = disc_info_.game_offset + disc_info_.root_sector * kSector;
  if (!ReadDirectory(offset, disc_info_.root_size, root.get(), 0)) {
    file_count_ = total_file_size_ = 0;
    REXFS_ERROR("Damaged or unreadable XDVDFS directory");
    return false;
  }
  root_entry_ = std::move(root);
  return true;
}

void DiscImageDevice::Dump(string::StringBuffer* buffer) {
  auto lock = global_critical_region_.Acquire();
  buffer->AppendFormat(
      "{}: {} files, {} bytes (game_offset={:#x}, root_sector={}, root_size={}, host_size={})\n",
      mount_path(), file_count_, total_file_size_, disc_info_.game_offset, disc_info_.root_sector,
      disc_info_.root_size, disc_info_.host_size);
}

Entry* DiscImageDevice::ResolvePath(std::string_view path) {
  return root_entry_ ? root_entry_->ResolvePath(path) : nullptr;
}

bool DiscImageDevice::ReadDirectory(size_t offset, size_t size, DiscImageEntry* parent,
                                    unsigned depth) {
  if (size < 14 || size > kMaxDirectory || depth > 256 || metadata_bytes_ > kMaxMetadata - size ||
      !directory_offsets_.insert(offset).second || offset > disc_info_.host_size ||
      size > disc_info_.host_size - offset)
    return false;
  metadata_bytes_ += size;
  std::vector<uint8_t> data(size);
  if (!ReadBytes(offset, data))
    return false;
  media_signature_ = hash_bytes(
      media_signature_ + std::string(reinterpret_cast<const char*>(data.data()), data.size()));
  // Iterative in-order traversal preserves directory enumeration order without
  // recursing down a malicious, unbalanced directory-entry tree.
  struct Visit {
    uint16_t ordinal;
    bool emit;
  };
  std::vector<Visit> pending{{0, false}};
  std::set<uint16_t> visited;
  while (!pending.empty()) {
    const auto visit = pending.back();
    pending.pop_back();
    const size_t pos = size_t(visit.ordinal) * 4;
    if (pos > size || size - pos < 14)
      return false;
    const auto* node = data.data() + pos;
    const uint16_t left = memory::load<uint16_t>(node);
    const uint16_t right = memory::load<uint16_t>(node + 2);
    if (!visit.emit) {
      if (!visited.insert(visit.ordinal).second)
        return false;
      if (right)
        pending.push_back({right, false});
      pending.push_back({visit.ordinal, true});
      if (left)
        pending.push_back({left, false});
      continue;
    }
    const size_t sector = memory::load<uint32_t>(node + 4);
    const size_t length = memory::load<uint32_t>(node + 8);
    const uint8_t attributes = node[12];
    const size_t name_size = node[13];
    if (!name_size || name_size > size - pos - 14)
      return false;
    std::string name(reinterpret_cast<const char*>(node + 14), name_size);
    if (name == "." || name == ".." ||
        std::any_of(name.begin(), name.end(),
                    [](unsigned char c) { return c < 32 || c == '/' || c == '\\' || c == ':'; }) ||
        parent->GetChild(name))
      return false;
    const size_t file_offset = disc_info_.game_offset + sector * kSector;
    if (file_offset > disc_info_.host_size || length > disc_info_.host_size - file_offset)
      return false;
    auto entry = DiscImageEntry::Create(this, parent, name);
    entry->attributes_ = attributes | kFileAttributeReadOnly;
    entry->size_ = length;
    entry->allocation_size_ = rex::round_up(length, bytes_per_sector());
    entry->create_timestamp_ = entry->access_timestamp_ = entry->write_timestamp_ =
        10000 * 11644473600000LL;
    if (attributes & kFileAttributeDirectory) {
      if (length && !ReadDirectory(file_offset, length, entry.get(), depth + 1))
        return false;
    } else {
      entry->data_offset_ = file_offset;
      entry->data_size_ = length;
      ++file_count_;
      total_file_size_ += length;
    }
    parent->children_.emplace_back(std::move(entry));
  }
  return true;
}
}  // namespace rex::filesystem
