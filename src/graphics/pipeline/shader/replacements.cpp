/**
 * @file        graphics/pipeline/shader/replacements.cpp
 * @brief       Per-title replacement host shaders matched by guest ucode hash
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/graphics/pipeline/shader/replacements.h>

#include <charconv>
#include <fstream>
#include <iterator>
#include <string>

#include <rex/logging.h>
#include <rex/filesystem.h>

namespace rex::graphics {

namespace {

bool ParseHex64(std::string_view text, uint64_t& value_out) {
  if (text.size() != 16) {
    return false;
  }
  const auto result = std::from_chars(text.data(), text.data() + text.size(), value_out, 16);
  return result.ec == std::errc() && result.ptr == text.data() + text.size();
}

}  // namespace

bool ShaderReplacements::ParseName(std::string_view file_name, Key& key_out) {
  constexpr std::string_view kExtension = ".dxbc";
  if (file_name.size() <= kExtension.size() || !file_name.ends_with(kExtension)) {
    return false;
  }
  file_name.remove_suffix(kExtension.size());
  const size_t dot = file_name.find('.');
  if (dot == std::string_view::npos) {
    return false;
  }
  const std::string_view stage = file_name.substr(dot + 1);
  std::string_view hashes = file_name.substr(0, dot);

  Key key;
  if (stage == "vs") {
    key.stage = Stage::kVertex;
  } else if (stage == "ps_rtv") {
    key.stage = Stage::kPixelRtv;
  } else if (stage == "ps_rov") {
    key.stage = Stage::kPixelRov;
  } else {
    return false;
  }
  const size_t underscore = hashes.find('_');
  if (underscore != std::string_view::npos) {
    uint64_t modification;
    if (!ParseHex64(hashes.substr(underscore + 1), modification)) {
      return false;
    }
    key.modification = modification;
    hashes = hashes.substr(0, underscore);
  }
  if (!ParseHex64(hashes, key.ucode_hash)) {
    return false;
  }
  key_out = key;
  return true;
}

bool ShaderReplacements::Add(const Key& key, std::vector<uint8_t> dxbc) {
  if (dxbc.size() < 32 ||
      std::string_view(reinterpret_cast<const char*>(dxbc.data()), 4) != "DXBC") {
    return false;
  }
  replacements_[MapKey(key.ucode_hash, key.stage, key.modification.has_value(),
                       key.modification.value_or(UINT64_MAX))] = std::move(dxbc);
  return true;
}

size_t ShaderReplacements::Load(const std::filesystem::path& folder) {
  std::error_code error;
  if (!std::filesystem::is_directory(folder, error)) {
    return 0;
  }
  size_t added = 0;
  for (const auto& entry : std::filesystem::directory_iterator(folder, error)) {
    if (!entry.is_regular_file(error)) {
      continue;
    }
    const std::string name = rex::path_to_utf8(entry.path().filename());
    Key key;
    if (!ParseName(name, key)) {
      if (entry.path().extension() == ".dxbc") {
        REXGPU_WARN("Shader replacement {}: name is not <HASH>[_<MODIFICATION>].<stage>.dxbc",
                    name);
      }
      continue;
    }
    std::ifstream file(entry.path(), std::ios::binary);
    std::vector<uint8_t> dxbc((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    if (!Add(key, std::move(dxbc))) {
      REXGPU_WARN("Shader replacement {}: not a DXBC container; ignored", name);
      continue;
    }
    ++added;
  }
  return added;
}

const std::vector<uint8_t>* ShaderReplacements::Find(uint64_t ucode_hash, Stage stage,
                                                     uint64_t modification) const {
  auto it = replacements_.find(MapKey(ucode_hash, stage, true, modification));
  if (it == replacements_.end()) {
    it = replacements_.find(MapKey(ucode_hash, stage, false, UINT64_MAX));
  }
  return it == replacements_.end() ? nullptr : &it->second;
}

}  // namespace rex::graphics
