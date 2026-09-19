/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2015 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

// NOTE: This file is auto-included by platform.h on Windows.
// It contains Windows-specific headers and definitions.

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <windowsx.h>

#include <ObjBase.h>
#include <SDKDDKVer.h>
#include <bcrypt.h>
#include <dwmapi.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <shobjidl.h>
#include <tpcshrd.h>
#undef DeleteBitmap
#undef DeleteFile
#undef GetFirstChild


namespace rex::platform_win {

inline HANDLE CreateFileForApp(LPCWSTR path, DWORD desired_access, DWORD share_mode,
                               DWORD creation_disposition, DWORD flags_and_attributes) {
  return CreateFileW(path, desired_access, share_mode, nullptr, creation_disposition,
                     flags_and_attributes, nullptr);
}

inline BOOL GetFileAttributesForApp(LPCWSTR path, WIN32_FILE_ATTRIBUTE_DATA* data) {
  return GetFileAttributesExW(path, GetFileExInfoStandard, data);
}

inline HANDLE FindFirstFileForApp(LPCWSTR pattern, WIN32_FIND_DATAW* data) {
  return FindFirstFileW(pattern, data);
}

}  // namespace rex::platform_win
