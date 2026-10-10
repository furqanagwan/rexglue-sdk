/**
 * @file        rex/platform/console.h
 * @brief       Platform-agnostic terminal capability queries.
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <cstdio>

namespace rex::platform::console {

bool is_tty(FILE* stream);

bool enable_ansi_escapes(FILE* stream);

void set_utf8_output_codepage();

}
