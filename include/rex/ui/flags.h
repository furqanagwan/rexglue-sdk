/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <rex/cvar.h>

// Presenter
REXCVAR_DECLARE(bool, present_render_pass_clear);
REXCVAR_DECLARE(bool, present_letterbox);
REXCVAR_DECLARE(int32_t, present_safe_area_x);
REXCVAR_DECLARE(int32_t, present_safe_area_y);
REXCVAR_DECLARE(std::string, present_effect);
REXCVAR_DECLARE(double, present_cas_additional_sharpness);
REXCVAR_DECLARE(int32_t, present_fsr_max_upsampling_passes);
REXCVAR_DECLARE(double, present_fsr_sharpness_reduction);
REXCVAR_DECLARE(std::string, present_fsr_quality_mode);
REXCVAR_DECLARE(bool, present_dither);
REXCVAR_DECLARE(bool, present_allow_overscan_cutoff);
REXCVAR_DECLARE(bool, host_present_from_non_ui_thread);
REXCVAR_DECLARE(int32_t, window_width);
REXCVAR_DECLARE(int32_t, window_height);
REXCVAR_DECLARE(bool, fullscreen);
REXCVAR_DECLARE(int32_t, monitor);
REXCVAR_DECLARE(std::string, video_driver);
REXCVAR_DECLARE(std::string, ui_backend);

// Display (guest video mode; defined in src/ui/window.cpp)
REXCVAR_DECLARE(int32_t, video_mode_width);
REXCVAR_DECLARE(int32_t, video_mode_height);
REXCVAR_DECLARE(double, video_mode_refresh_rate);
REXCVAR_DECLARE(std::string, resolution);

REXCVAR_DECLARE(bool, d3d12_debug);
REXCVAR_DECLARE(bool, d3d12_break_on_error);
REXCVAR_DECLARE(bool, d3d12_break_on_warning);
REXCVAR_DECLARE(int32_t, d3d12_adapter);
REXCVAR_DECLARE(int32_t, d3d12_queue_priority);
REXCVAR_DECLARE(bool, d3d12_allow_variable_refresh_rate_and_tearing);
