/**
 * @file        ui/agility_exports.cpp
 * @brief       The two symbols d3d12.dll reads to load the Agility SDK
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

// d3d12.dll looks for these by name in the executable, before anything of ours
// runs and before a device exists, which is why they cannot live in one of the
// DLLs: exporting them from rexruntime would never be seen. This file is
// compiled into the host executable by rexglue_configure_target.
//
// D3D12SDKPath is relative to the executable and must name a folder, with the
// separators and the trailing slash as written. rexglue_stage_agility_sdk puts
// D3D12Core.dll there.
//
// When the DLL is missing or its version does not match, Direct3D falls back to
// the D3D12Core that ships with Windows rather than failing, so a build that
// lost its staging step degrades to whatever the OS has instead of refusing to
// start. REXGLUE_AGILITY_SDK_VERSION is generated into <rex/version.h> from the
// package the SDK was built against, so the number exported here and the binary
// staged beside it cannot drift apart.

#if defined(_WIN32)

#include <stdint.h>

#include <rex/version.h>

#ifndef REXGLUE_AGILITY_SDK_VERSION
#error "<rex/version.h> did not define REXGLUE_AGILITY_SDK_VERSION"
#endif

extern "C" {
__declspec(dllexport) extern const uint32_t D3D12SDKVersion = REXGLUE_AGILITY_SDK_VERSION;
__declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\";
}

#endif  // _WIN32
