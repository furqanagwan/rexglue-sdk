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

/// Replacement DXBC for translated guest shaders, keyed by the guest ucode hash
/// and host stage, optionally narrowed to one translator modification. A file
/// is named `<HASH>[_<MODIFICATION>].<stage>.dxbc`, both in 16 hex digits as
/// `dump_shaders` writes them, with stage `vs`, `ps_rtv` or `ps_rov` (pixel
/// shaders differ between the two render target paths).
class ShaderReplacements {
 public:
  enum class Stage : uint8_t { kVertex, kPixelRtv, kPixelRov };

  struct Key {
    uint64_t ucode_hash = 0;
    Stage stage = Stage::kVertex;
    std::optional<uint64_t> modification;
  };

  /// Parses a replacement file name; false for anything else.
  static bool ParseName(std::string_view file_name, Key& key_out);

  /// Adds every well-named DXBC file in `folder`; others are skipped with a
  /// warning. Returns the number added.
  size_t Load(const std::filesystem::path& folder);

  /// Adds one replacement. False (and nothing added) unless `dxbc` is a DXBC
  /// container.
  bool Add(const Key& key, std::vector<uint8_t> dxbc);

  /// The replacement for a translation: the one for its exact modification,
  /// else the one for any modification, else nullptr (translate as usual).
  const std::vector<uint8_t>* Find(uint64_t ucode_hash, Stage stage, uint64_t modification) const;

  size_t size() const { return replacements_.size(); }
  bool empty() const { return replacements_.empty(); }

 private:
  // Modification UINT64_MAX with has_modification false is "any".
  using MapKey = std::tuple<uint64_t, Stage, bool, uint64_t>;
  std::map<MapKey, std::vector<uint8_t>> replacements_;
};

}  // namespace rex::graphics
