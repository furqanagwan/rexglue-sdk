/**
 * @file        rexglue/commands/http_client.h
 * @brief       HTTP GET for the build-time catalogue and update commands (RG-GDK-050)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace rexglue::cli {

std::optional<std::vector<uint8_t>> HttpGet(const std::string& url, std::string* error,
                                            int timeout_ms = 30000);

}
