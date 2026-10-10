// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <filesystem>
#include <map>
#include <optional>
#include <string>

#include <rex/system/release_update.h>

// clang-format off
#include <windows.h>
#include <shellapi.h>
// clang-format on

namespace {

namespace fs = std::filesystem;
namespace update = rex::system::update;

constexpr DWORD kGameExitTimeoutMs = 60000;

struct Options {
  DWORD wait_process_id = 0;
  fs::path install_folder;
  fs::path package_root;
  fs::path previous_folder;
  fs::path launch;
  bool rollback = false;
};

std::optional<Options> ParseOptions() {
  int count = 0;
  LPWSTR* arguments = CommandLineToArgvW(GetCommandLineW(), &count);
  if (!arguments) {
    return std::nullopt;
  }
  std::map<std::wstring, std::wstring> values;
  Options options;
  for (int i = 1; i < count; ++i) {
    const std::wstring name = arguments[i];
    if (name == L"--rollback") {
      options.rollback = true;
    } else if (i + 1 < count) {
      values[name] = arguments[++i];
    }
  }
  LocalFree(arguments);
  options.wait_process_id = DWORD(std::wcstoul(values[L"--wait"].c_str(), nullptr, 10));
  options.install_folder = values[L"--install"];
  options.package_root = values[L"--package"];
  options.previous_folder = values[L"--previous"];
  options.launch = values[L"--launch"];
  if (options.install_folder.empty() || options.previous_folder.empty() ||
      (!options.rollback && options.package_root.empty())) {
    return std::nullopt;
  }
  return options;
}

bool WaitForGameExit(DWORD process_id) {
  if (!process_id) {
    return true;
  }
  HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, process_id);
  if (!process) {
    return true;
  }
  const bool exited = WaitForSingleObject(process, kGameExitTimeoutMs) == WAIT_OBJECT_0;
  CloseHandle(process);
  return exited;
}

void Launch(const fs::path& executable) {
  if (executable.empty()) {
    return;
  }
  std::wstring command_line = L"\"" + executable.wstring() + L"\"";
  STARTUPINFOW startup{};
  startup.cb = sizeof(startup);
  PROCESS_INFORMATION process = {};
  if (CreateProcessW(executable.c_str(), command_line.data(), nullptr, nullptr, FALSE, 0, nullptr,
                     executable.parent_path().c_str(), &startup, &process)) {
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
  }
}

void ShowError(const std::string& message) {
  const std::wstring text(message.begin(), message.end());
  MessageBoxW(nullptr, text.c_str(), L"Update failed", MB_OK | MB_ICONERROR);
}

}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  const auto options = ParseOptions();
  if (!options) {
    ShowError("The updater was started without its install, package and previous folders.");
    return 2;
  }
  if (!WaitForGameExit(options->wait_process_id)) {
    ShowError("The game didn't close, so nothing was changed.");
    return 3;
  }
  std::string error;
  const bool ok = options->rollback
                      ? update::RestorePreviousVersion(options->install_folder,
                                                       options->previous_folder, &error)
                      : update::InstallStagedUpdate(options->install_folder, options->package_root,
                                                    options->previous_folder, &error);
  if (!ok) {
    ShowError((options->rollback ? "The previous version couldn't be restored: "
                                 : "The update couldn't be installed, so the game was left as it "
                                   "was: ") +
              error);
  }
  Launch(options->launch);
  return ok ? 0 : 1;
}
