// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <cstdint>
#include <vector>

#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>

namespace rex::fuzz {

inline void ReadEntry(filesystem::Entry* entry) {
  filesystem::File* file = nullptr;
  if (entry->Open(filesystem::FileAccess::kGenericRead, &file) != X_STATUS_SUCCESS || !file) {
    return;
  }
  std::vector<uint8_t> buffer(4096);
  size_t read = 0;
  file->ReadSync(buffer, 0, &read);
  if (entry->size() > buffer.size()) {
    file->ReadSync(buffer, entry->size() - buffer.size(), &read);
  }
  file->Destroy();
}

inline void WalkEntries(filesystem::Entry* entry, int depth = 0) {
  if (!entry || depth > 64) {
    return;
  }
  for (const auto& child : entry->children()) {
    if (child->attributes() & filesystem::kFileAttributeDirectory) {
      WalkEntries(child.get(), depth + 1);
    } else {
      ReadEntry(child.get());
    }
  }
}

}
