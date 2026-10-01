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

#include <algorithm>

#include <rex/literals.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/memory.h>

namespace rex::filesystem {

using namespace rex::literals;

const size_t kXESectorSize = 2_KiB;

DiscImageDevice::DiscImageDevice(const std::string_view mount_path,
                                 const std::filesystem::path& host_path)
    : Device(mount_path), name_("GDFX"), host_path_(host_path) {}

DiscImageDevice::~DiscImageDevice() = default;

bool DiscImageDevice::Initialize() {
  std::error_code ec;
  const auto size = std::filesystem::file_size(host_path_, ec);
  if (ec || size > SIZE_MAX) {
    REXFS_ERROR("Disc image size could not be read: {}", host_path_.string());
    return false;
  }
  file_handle_ = FileHandle::OpenExisting(host_path_, FileAccess::kGenericRead, true);
  if (!file_handle_) {
    REXFS_ERROR("Disc image could not be opened: {}", host_path_.string());
    return false;
  }

  ParseState state = {};
  state.size = static_cast<size_t>(size);
  disc_info_.host_size = state.size;
  auto result = Verify(&state);
  if (result != Error::kSuccess) {
    REXFS_ERROR("Failed to verify disc image header: {}", static_cast<int>(result));
    return false;
  }

  result = ReadAllEntries(&state);
  if (result != Error::kSuccess) {
    REXFS_ERROR("Failed to read all GDFX entries: {}", static_cast<int>(result));
    return false;
  }

  return true;
}

bool DiscImageDevice::ReadAt(size_t offset, std::span<uint8_t> output) const {
  if (!file_handle_ || offset > disc_info_.host_size ||
      output.size() > disc_info_.host_size - offset)
    return false;
  if (output.empty())
    return true;
  constexpr size_t kReadChunk = 8_MiB;
  while (!output.empty()) {
    const size_t length = std::min(output.size(), kReadChunk);
    size_t bytes_read = 0;
    if (!file_handle_->Read(offset, output.data(), length, &bytes_read) || bytes_read != length)
      return false;
    offset += length;
    output = output.subspan(length);
  }
  return true;
}

void DiscImageDevice::Dump(string::StringBuffer* string_buffer) {
  auto global_lock = global_critical_region_.Acquire();
  string_buffer->AppendFormat(
      "{}: {} files, {} bytes (game_offset={:#x}, root_sector={}, root_size={}, host_size={})\n",
      mount_path(), file_count_, total_file_size_, disc_info_.game_offset, disc_info_.root_sector,
      disc_info_.root_size, disc_info_.host_size);
}

Entry* DiscImageDevice::ResolvePath(const std::string_view path) {
  // The filesystem will have stripped our prefix off already, so the path will
  // be in the form:
  // some\PATH.foo
  REXFS_DEBUG("DiscImageDevice::ResolvePath({})", path);
  return root_entry_->ResolvePath(path);
}

DiscImageDevice::Error DiscImageDevice::Verify(ParseState* state) {
  // Find sector 32 of the game partition - try at a few points.
  static const size_t likely_offsets[] = {
      0x00000000, 0x0000FB20, 0x00020600, 0x02080000, 0x0FD90000,
  };
  bool magic_found = false;
  for (size_t n = 0; n < rex::countof(likely_offsets); n++) {
    state->game_offset = likely_offsets[n];
    if (VerifyMagic(state, state->game_offset + (32 * kXESectorSize))) {
      magic_found = true;
      break;
    }
  }
  if (!magic_found) {
    // File doesn't have the magic values - likely not a real GDFX source.
    return Error::kErrorFileMismatch;
  }

  // Read sector 32 to get FS state.
  const uint64_t header_offset = uint64_t(state->game_offset) + 32 * kXESectorSize;
  if (header_offset > state->size || 32 > state->size - header_offset) {
    return Error::kErrorReadError;
  }
  uint8_t header[32]{};
  if (!ReadAt(static_cast<size_t>(header_offset), header))
    return Error::kErrorReadError;
  const uint8_t* fs_ptr = header;
  state->root_sector = memory::load<uint32_t>(fs_ptr + 20);
  state->root_size = memory::load<uint32_t>(fs_ptr + 24);
  const uint64_t root_offset =
      uint64_t(state->game_offset) + uint64_t(state->root_sector) * kXESectorSize;
  if (root_offset > state->size)
    return Error::kErrorDamagedFile;
  state->root_offset = static_cast<size_t>(root_offset);
  if (state->root_size < 13 || state->root_size > 32_MiB) {
    return Error::kErrorDamagedFile;
  }
  if (state->root_size > state->size - state->root_offset)
    return Error::kErrorDamagedFile;

  disc_info_.game_offset = state->game_offset;
  disc_info_.root_sector = state->root_sector;
  disc_info_.root_size = state->root_size;
  disc_info_.host_size = state->size;

  return Error::kSuccess;
}

bool DiscImageDevice::VerifyMagic(ParseState* state, size_t offset) {
  if (offset > state->size || 20 > state->size - offset) {
    return false;
  }

  uint8_t magic[20]{};
  return ReadAt(offset, magic) && std::memcmp(magic, "MICROSOFT*XBOX*MEDIA", 20) == 0;
}

DiscImageDevice::Error DiscImageDevice::ReadAllEntries(ParseState* state) {
  std::vector<uint8_t> root_buffer(state->root_size);
  if (!ReadAt(state->root_offset, root_buffer))
    return Error::kErrorReadError;
  auto root_entry = new DiscImageEntry(this, nullptr, "", this);
  root_entry->attributes_ = kFileAttributeDirectory;
  root_entry_ = std::unique_ptr<Entry>(root_entry);

  if (!ReadEntry(state, root_buffer, 0, root_entry, 0)) {
    return Error::kErrorDamagedFile;
  }

  return Error::kSuccess;
}

bool DiscImageDevice::ReadEntry(ParseState* state, std::span<const uint8_t> buffer,
                                uint16_t entry_ordinal, DiscImageEntry* parent, unsigned depth) {
  const size_t entry_offset = size_t(entry_ordinal) * 4;
  if (depth > 128 || entry_offset > buffer.size() || buffer.size() - entry_offset < 14)
    return false;
  const uint8_t* p = buffer.data() + entry_offset;

  uint16_t node_l = memory::load<uint16_t>(p + 0);
  uint16_t node_r = memory::load<uint16_t>(p + 2);
  size_t sector = memory::load<uint32_t>(p + 4);
  size_t length = memory::load<uint32_t>(p + 8);
  uint8_t attributes = memory::load<uint8_t>(p + 12);
  uint8_t name_length = memory::load<uint8_t>(p + 13);
  if (name_length > buffer.size() - entry_offset - 14)
    return false;
  auto name_buffer = reinterpret_cast<const char*>(p + 14);

  if (node_l && !ReadEntry(state, buffer, node_l, parent, depth + 1)) {
    return false;
  }

  auto name = std::string(name_buffer, name_length);

  auto entry = DiscImageEntry::Create(this, parent, name, this);
  entry->attributes_ = attributes | kFileAttributeReadOnly;
  entry->size_ = length;
  entry->allocation_size_ = rex::round_up(length, bytes_per_sector());

  // Set to January 1, 1970 (UTC) in 100-nanosecond intervals
  entry->create_timestamp_ = 10000 * 11644473600000LL;
  entry->access_timestamp_ = 10000 * 11644473600000LL;
  entry->write_timestamp_ = 10000 * 11644473600000LL;

  if (attributes & kFileAttributeDirectory) {
    // Folder.
    entry->data_offset_ = 0;
    entry->data_size_ = 0;
    if (length) {
      // Not a leaf - read in children.
      const uint64_t folder_offset = uint64_t(state->game_offset) + sector * kXESectorSize;
      if (folder_offset > state->size || length > state->size - folder_offset || length < 14 ||
          length > 32_MiB) {
        // Out of bounds read.
        return false;
      }
      std::vector<uint8_t> folder(length);
      if (!ReadAt(static_cast<size_t>(folder_offset), folder) ||
          !ReadEntry(state, folder, 0, entry.get(), depth + 1)) {
        return false;
      }
    }
  } else {
    // File.
    const uint64_t data_offset = uint64_t(state->game_offset) + sector * kXESectorSize;
    if (data_offset > state->size || length > state->size - data_offset)
      return false;
    entry->data_offset_ = static_cast<size_t>(data_offset);
    entry->data_size_ = length;
    ++file_count_;
    total_file_size_ += length;
  }

  // Add to parent.
  parent->children_.emplace_back(std::move(entry));

  // Read next file in the list.
  if (node_r && !ReadEntry(state, buffer, node_r, parent, depth + 1)) {
    return false;
  }

  return true;
}

}  // namespace rex::filesystem
