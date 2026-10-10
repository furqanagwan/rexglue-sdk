/**
 * @file        rex/ui/image_decode.h
 * @brief       Minimal host-side PNG decode helper (wraps stb_image).
 *
 * @copyright   Copyright (c) 2026 Rien Gupta <rgupta9@scu.edu>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once
#include <cstdint>
#include <vector>

namespace rex::ui {

std::vector<uint8_t> DecodeImageRGBA(const uint8_t* data, size_t size, int& out_width,
                                     int& out_height);

}
