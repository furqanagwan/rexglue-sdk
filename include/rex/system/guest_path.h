/**
 * @file        rex/system/guest_path.h
 * @brief       Guest path normalization for Xbox 360 VFS paths
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace rex::system {

/**
 * Normalize a guest path to the canonical form used as a key for runtime
 * lookups: device prefix stripped, separators canonicalized to forward
 * slashes, redundant `..` segments resolved, leading slashes removed,
 * and ASCII lowercased. Codegen-side canonicalization
 * (rex::codegen::CanonicalizeModuleGuestPath) layers a project-scoped prefix
 * strip on top of this; both must agree on this base form for runtime
 * lookups to find the registered module.
 */
std::string NormalizeGuestPath(std::string_view path);

/**
 * Whether normalized `path` names `module_path` (normalized, relative to the
 * game root) through a device path: it ends with `/module_path`. Modules
 * loaded by a bare name are joined to the executable's device path
 * (\Device\Harddisk0\Partition1\...), which NormalizeGuestPath keeps.
 */
bool GuestPathEndsWithModule(std::string_view path, std::string_view module_path);

/// Return an unqualified ObDosDevices name suitable for opening relative to
/// the title directory. A trailing separator names the directory itself.
std::optional<std::string> NormalizeDosDevicesRelativePath(std::string_view path);

}  // namespace rex::system
