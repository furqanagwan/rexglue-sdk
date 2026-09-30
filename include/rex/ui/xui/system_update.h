/**
 * @file        rex/ui/xui/system_update.h
 * @brief       The dashboard XUI packages, read from the user's own system update (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <rex/ui/xui/package.h>

namespace rex::ui::xui {

struct XexResource {
  std::string name;
  std::vector<uint8_t> bytes;
};

/// The named resources of an unencrypted XEX2 image (uncompressed, basic or
/// LZX-compressed), as the console's system XEXs are.
std::optional<std::vector<XexResource>> ReadXexResources(std::span<const uint8_t> xex,
                                                         std::string* error);

/// XUIZ packages from the console's system XEXs, keyed "module/resource":
/// "hud/hud", "huduiskin/skin", "xam/shrdres", "gamerprofile/gp"...
class SystemUpdate {
 public:
  /// The system XEXs the guide reads, as they are named in the update package.
  static constexpr std::string_view kModules[] = {"hud", "huduiskin", "xam", "gamerprofile"};

  /// `path` is a `$SystemUpdate` folder, the `su20076000_00000000` package in
  /// it, or a folder holding the `$flash_<module>.xex` files.
  static std::unique_ptr<SystemUpdate> Load(const std::filesystem::path& path, std::string* error);

  /// Adds the XUIZ resources of one system XEX. Used by Load and by tests.
  bool AddModule(std::string_view module, std::span<const uint8_t> xex, std::string* error);

  const Package* Find(std::string_view module_resource) const;
  const std::map<std::string, Package>& packages() const { return packages_; }

 private:
  std::map<std::string, Package> packages_;
};

}  // namespace rex::ui::xui
