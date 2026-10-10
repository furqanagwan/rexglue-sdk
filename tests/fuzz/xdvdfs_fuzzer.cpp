// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include <rex/filesystem/devices/disc_image_device.h>
#include <rex/filesystem/file.h>

#include "walk_entries.h"

namespace {

class MemoryReader : public rex::filesystem::FileHandle {
 public:
  explicit MemoryReader(std::vector<uint8_t> bytes) : FileHandle({}), bytes_(std::move(bytes)) {}
  bool Read(size_t offset, void* buffer, size_t count, size_t* read) override {
    *read = 0;
    if (offset > bytes_.size()) {
      return false;
    }
    count = std::min(count, bytes_.size() - offset);
    std::memcpy(buffer, bytes_.data() + offset, count);
    *read = count;
    return true;
  }
  bool Write(size_t, const void*, size_t, size_t*) override { return false; }
  bool SetLength(size_t) override { return false; }
  bool Flush() override { return false; }

 private:
  std::vector<uint8_t> bytes_;
};

}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  auto reader = std::make_unique<MemoryReader>(std::vector<uint8_t>(data, data + size));
  rex::filesystem::DiscImageDevice device("disc:", std::move(reader), size);
  if (!device.Initialize()) {
    return 0;
  }
  rex::fuzz::WalkEntries(device.ResolvePath(""));
  return 0;
}
