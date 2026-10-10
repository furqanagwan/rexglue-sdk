/**
 * @file        rex/graphics/pipeline/shader/replacements.h
 * @brief       Per-title replacement host shaders matched by guest ucode hash
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 *
 * @remarks     RG-GDK-067. Microsoft's backward compatibility emulator ships
 *              hand-written replacements for guest shaders that misbehave
 *              when upscaled or on PC GPUs; a title here ships its own the
 *              same way (docs/shader-replacements.md).
 */

#pragma once

#include <cstdint>
#include <filesystem>
#include <map>
#include <optional>
#include <string_view>
#include <tuple>
#include <vector>

namespace rex::graphics {

class ShaderReplacements {
 public:
  enum class Stage : uint8_t { kVertex, kPixelRtv, kPixelRov };

  struct Key {
    uint64_t ucode_hash = 0;
    Stage stage = Stage::kVertex;
    std::optional<uint64_t> modification;
  };

  static bool ParseName(std::string_view file_name, Key& key_out);

  size_t Load(const std::filesystem::path& folder);

  bool Add(const Key& key, std::vector<uint8_t> dxbc);

  const std::vector<uint8_t>* Find(uint64_t ucode_hash, Stage stage, uint64_t modification) const;

  size_t size() const { return replacements_.size(); }
  bool empty() const { return replacements_.empty(); }

 private:
  using MapKey = std::tuple<uint64_t, Stage, bool, uint64_t>;
  std::map<MapKey, std::vector<uint8_t>> replacements_;
};

}
