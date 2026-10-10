/**
 * @file        rex/kernel/xboxkrnl/xconfig.h
 * @brief       Console configuration values shared by XConfig reads and XAM
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>

namespace rex::kernel::xboxkrnl {

inline constexpr uint32_t kXConfigUserVideoFlags = 0x00040000;

inline constexpr uint32_t kXConfigUserAudioFlags = 0x00010001;

}
