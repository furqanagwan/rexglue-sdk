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

namespace {
class OwnedMappedMemory final : public memory::MappedMemory {
 public:
  explicit OwnedMappedMemory(size_t size) : storage_(size) {
    data_ = storage_.data();
    size_ = storage_.size();
  }

 private:
  std::vector<uint8_t> storage_;
};
}  // namespace

DiscImageEntry::DiscImageEntry(Device* device, Entry* parent, const std::string_view path,
                               DiscImageDevice* image)
    : Entry(device, parent, path), image_(image), data_offset_(0), data_size_(0) {}

DiscImageEntry::~DiscImageEntry() = default;

std::unique_ptr<DiscImageEntry> DiscImageEntry::Create(Device* device, Entry* parent,
                                                       const std::string_view name,
                                                       DiscImageDevice* image) {
  auto path = rex::string::utf8_join_guest_paths(parent->path(), name);
  auto entry = std::make_unique<DiscImageEntry>(device, parent, path, image);
  return std::move(entry);
}

X_STATUS DiscImageEntry::Open(uint32_t desired_access, File** out_file) {
  *out_file = new DiscImageFile(desired_access, this);
  return X_STATUS_SUCCESS;
}

std::unique_ptr<memory::MappedMemory> DiscImageEntry::OpenMapped(memory::MappedMemory::Mode mode,
                                                                 size_t offset, size_t length) {
  if (mode != memory::MappedMemory::Mode::kRead) {
    // Only allow reads.
    return nullptr;
  }

  if (offset > data_size_)
    return nullptr;
  size_t real_length = length ? std::min(length, data_size_ - offset) : data_size_ - offset;
  auto copy = std::make_unique<OwnedMappedMemory>(real_length);
  if (!image_->ReadAt(data_offset_ + offset, std::span<uint8_t>(copy->data(), real_length)))
    return nullptr;
  return copy;
}

}  // namespace rex::filesystem
