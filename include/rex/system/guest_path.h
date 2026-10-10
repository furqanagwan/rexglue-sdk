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

std::string NormalizeGuestPath(std::string_view path);

bool GuestPathEndsWithModule(std::string_view path, std::string_view module_path);

std::optional<std::string> NormalizeDosDevicesRelativePath(std::string_view path);

}
