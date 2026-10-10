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

#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>

#ifndef XXH_INLINE_ALL
#define XXH_INLINE_ALL
#endif

#include <xxhash.h>

namespace rex {

template <typename Key>
struct IdentityHasher {
  size_t operator()(const Key& key) const { return static_cast<size_t>(key); }
};

template <typename Key>
struct XXHasher {
  size_t operator()(const Key& key) const {
    return static_cast<size_t>(XXH3_64bits(&key, sizeof(key)));
  }
};

std::string hash_bytes(std::string_view data);

std::string hash_file(const std::filesystem::path& path);

}
