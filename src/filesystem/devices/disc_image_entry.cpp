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

#include <rex/filesystem/devices/disc_image_entry.h>
#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/devices/disc_image_file.h>

#include <algorithm>

#include <rex/math.h>

namespace rex::filesystem {

DiscImageEntry::DiscImageEntry(DiscImageDevice* device, Entry* parent, const std::string_view path)
    : Entry(device, parent, path), disc_(device), data_offset_(0), data_size_(0) {}

DiscImageEntry::~DiscImageEntry() = default;

std::unique_ptr<DiscImageEntry> DiscImageEntry::Create(DiscImageDevice* device, Entry* parent,
                                                       const std::string_view name) {
  auto path = rex::string::utf8_join_guest_paths(parent->path(), name);
  auto entry = std::make_unique<DiscImageEntry>(device, parent, path);
  return std::move(entry);
}

X_STATUS DiscImageEntry::Open(uint32_t desired_access, File** out_file) {
  *out_file = nullptr;
  if (desired_access & (FileAccess::kGenericWrite | FileAccess::kGenericAll |
                        FileAccess::kFileWriteData | FileAccess::kFileAppendData))
    return X_STATUS_ACCESS_DENIED;
  *out_file = new DiscImageFile(desired_access, this);
  return X_STATUS_SUCCESS;
}

std::unique_ptr<memory::MappedMemory> DiscImageEntry::OpenMapped(memory::MappedMemory::Mode mode,
                                                                 size_t offset, size_t length) {
  if (mode != memory::MappedMemory::Mode::kRead) {
    return nullptr;
  }

  if (offset > data_size_ || (attributes() & kFileAttributeDirectory))
    return nullptr;
  const size_t real_length = length ? std::min(length, data_size_ - offset) : data_size_ - offset;

  class Snapshot : public memory::MappedMemory {
   public:
    explicit Snapshot(size_t size) : bytes_(size) {
      data_ = bytes_.data();
      size_ = size;
    }

   private:
    std::vector<uint8_t> bytes_;
  };
  auto snapshot = std::make_unique<Snapshot>(real_length);
  if (!ReadBytes(offset, {snapshot->data(), snapshot->size()}))
    return nullptr;
  return snapshot;
}

bool DiscImageEntry::ReadBytes(size_t offset, std::span<uint8_t> bytes) {
  return offset <= data_size_ && bytes.size() <= data_size_ - offset &&
         disc_->ReadBytes(data_offset_ + offset, bytes);
}

}
