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

// XCONFIG_USER_VIDEO_FLAGS as the console reports it.
inline constexpr uint32_t kXConfigUserVideoFlags = 0x00040000;

// XCONFIG_USER_AUDIO_FLAGS: analog stereo (0x00010001), the value Xenia
// Canary and Edge report by default. XGetAudioFlags returns the same value.
inline constexpr uint32_t kXConfigUserAudioFlags = 0x00010001;

}  // namespace rex::kernel::xboxkrnl
