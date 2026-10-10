/**
 * @file        rex/platform/env.h
 * @brief       Platform-agnostic environment variable access (UTF-8).
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

namespace rex::platform::env {

std::optional<std::string> get(std::string_view name);

bool set(std::string_view name, std::string_view value);

bool unset(std::string_view name);

}
