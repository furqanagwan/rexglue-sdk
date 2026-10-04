/**
 * @file        d3d12_agility.cpp
 * @brief       D3D12 Agility SDK exports for titles (RG-GDK-032)
 *
 * Compiled into a title by rexglue_configure_target when the SDK was built
 * with REXGLUE_SHADER_DXIL: the D3D12 runtime then loads the pinned Agility
 * SDK from the D3D12 folder beside the executable, as Microsoft's PC backward
 * compatibility packages do.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <windows.h>

extern "C" {
__declspec(dllexport) extern const UINT D3D12SDKVersion = REXGLUE_D3D12_SDK_VERSION;
__declspec(dllexport) extern const char* D3D12SDKPath = ".\\D3D12\\";
}
