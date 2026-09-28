/**
 * @file        main.cpp
 * @brief       Minimal SDK title for the Gaming Runtime deployment smoke (RG-GDK-022)
 *
 * Starts the Gaming Runtime the way ReXApp does (rex::system::GamingRuntime,
 * off-thread with a timeout), records whether the process has package
 * identity, bumps a save counter where ReXApp keeps user data by default
 * (Saved Games/<name>, outside the package), uninitializes and exits. It is a
 * GUI-subsystem program so a `wdapp launch` shows no console; the report goes
 * to %REXGLUE_GDK_SMOKE_OUT% when set, else gdk_smoke_result.txt beside the
 * executable, else (an installed package is read-only) beside the save.
 * scripts/gdk_smoke.ps1 runs it unpackaged, registered and installed.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/data_locations.h>
#include <rex/filesystem.h>
#include <rex/system/gaming_runtime.h>

// The GDK headers need the Windows headers first.
#include <windows.h>

#include <appmodel.h>

#include <XGameRuntime.h>

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

std::filesystem::path ReportPath() {
  wchar_t out[MAX_PATH];
  if (const DWORD n = GetEnvironmentVariableW(L"REXGLUE_GDK_SMOKE_OUT", out, MAX_PATH);
      n > 0 && n < MAX_PATH) {
    return std::wstring(out, n);
  }
  wchar_t module[MAX_PATH];
  const DWORD length = GetModuleFileNameW(nullptr, module, MAX_PATH);
  return std::filesystem::path(std::wstring(module, length)).parent_path() / "gdk_smoke_result.txt";
}

// ReXApp's default user_data_root is Saved Games / <app name>.
int BumpSaveCounter() {
  const auto dir = rex::filesystem::GetSavedGamesFolder() / "rexglue_gdk_smoke";
  std::filesystem::create_directories(dir);
  const auto path = dir / "save.txt";
  int count = 0;
  if (std::ifstream in(path); in) {
    in >> count;
  }
  const std::string text = std::to_string(++count);
  if (!rex::filesystem::WriteFileDurably(
          path, {reinterpret_cast<const uint8_t*>(text.data()), text.size()})) {
    return -1;
  }
  return count;
}

}  // namespace

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  std::ofstream report(ReportPath(), std::ios::trunc);
  if (!report) {
    // An installed package's folder is read-only: report beside the save.
    const auto dir = rex::filesystem::GetSavedGamesFolder() / "rexglue_gdk_smoke";
    std::filesystem::create_directories(dir);
    report.open(dir / "gdk_smoke_result.txt", std::ios::trunc);
  }
  report << "edition: " << _GRDK_EDITION << "\n";

  rex::system::GamingRuntime runtime;
  const auto result = runtime.Initialize();
  report << "runtime: " << rex::system::GamingRuntimeStateName(result.state) << "\n";
  report << "message: " << result.message << "\n";
  if (!result.ok()) {
    return 1;
  }

  // Windows package identity (wdapp register, MSIX) ...
  UINT32 full_name_length = 0;
  std::wstring full_name;
  if (GetCurrentPackageFullName(&full_name_length, nullptr) == ERROR_INSUFFICIENT_BUFFER) {
    full_name.resize(full_name_length);
    if (GetCurrentPackageFullName(&full_name_length, full_name.data()) == ERROR_SUCCESS) {
      full_name.resize(full_name_length - 1);
    } else {
      full_name.clear();
    }
  }
  report << "appx: "
         << (full_name.empty() ? std::string("none")
                               : std::string(full_name.begin(), full_name.end()))
         << "\n";
  // ... and the GDK's installation identity (a game install).
  const bool packaged = XPackageIsPackagedProcess();
  report << "packaged: " << (packaged ? "yes" : "no") << "\n";
  if (packaged) {
    char identifier[XPACKAGE_IDENTIFIER_MAX_LENGTH] = {};
    const HRESULT hr = XPackageGetCurrentProcessPackageIdentifier(sizeof(identifier), identifier);
    report << "package: " << (SUCCEEDED(hr) ? identifier : "(unavailable)") << "\n";
  }

  report << "save: " << BumpSaveCounter() << "\n";

  runtime.Uninitialize();
  report << "uninitialized: "
         << (runtime.state() == rex::system::GamingRuntimeState::kNotInitialized ? "yes" : "no")
         << "\n";
  report << "exit: 0\n";
  return 0;
}
