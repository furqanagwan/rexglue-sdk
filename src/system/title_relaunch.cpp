/**
 * @file        system/title_relaunch.cpp
 * @brief       Relaunching a title that launches its own executable
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/system/title_relaunch.h>

#include <atomic>
#include <cstring>
#include <fstream>
#include <mutex>
#include <string>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/platform.h>

#if REX_PLATFORM_WIN32
#include "../core/platform_win.h"

#include <shellapi.h>
#else
#include <unistd.h>
#include <spawn.h>
#if REX_PLATFORM_MAC
#include <crt_externs.h>
#include <mach-o/dyld.h>
#endif
extern char** environ;
#endif

REXCVAR_DEFINE_STRING(launch_data_file, "", "Runtime",
                      "Launch data from a previous run of this title, written when the title "
                      "relaunched itself. Set by the SDK; the file is deleted once read.")
    .lifecycle(rex::cvar::Lifecycle::kInitOnly);

namespace rex::system {
namespace {

constexpr char kFileMagic[4] = {'R', 'X', 'L', 'D'};

std::mutex g_mutex;
std::atomic<bool> g_requested{false};
std::vector<uint8_t> g_launch_data;
uint32_t g_launch_flags = 0;

constexpr const char* kArgumentPrefix = "--launch_data_file=";

#if REX_PLATFORM_WIN32

std::wstring QuoteArgument(const std::wstring& argument) {
  if (!argument.empty() && argument.find_first_of(L" \t\"") == std::wstring::npos) {
    return argument;
  }
  std::wstring quoted = L"\"";
  size_t backslashes = 0;
  for (wchar_t c : argument) {
    if (c == L'\\') {
      ++backslashes;
      continue;
    }
    if (c == L'"') {
      quoted.append(backslashes * 2 + 1, L'\\');
    } else {
      quoted.append(backslashes, L'\\');
    }
    backslashes = 0;
    quoted.push_back(c);
  }
  quoted.append(backslashes * 2, L'\\');
  quoted.push_back(L'"');
  return quoted;
}

bool StartProcess(const std::filesystem::path& data_file) {
  int argc = 0;
  wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if (!argv) {
    return false;
  }
  wchar_t executable[MAX_PATH * 4];
  if (!GetModuleFileNameW(nullptr, executable, static_cast<DWORD>(std::size(executable)))) {
    LocalFree(argv);
    return false;
  }
  std::wstring command_line = QuoteArgument(executable);
  const std::wstring prefix(kArgumentPrefix, kArgumentPrefix + std::strlen(kArgumentPrefix));
  for (int i = 1; i < argc; ++i) {
    std::wstring argument = argv[i];
    if (argument.rfind(prefix, 0) == 0) {
      continue;  // the previous run's launch data
    }
    command_line += L" " + QuoteArgument(argument);
  }
  LocalFree(argv);
  command_line += L" " + QuoteArgument(prefix + data_file.wstring());

  STARTUPINFOW startup_info{};
  startup_info.cb = sizeof(startup_info);
  PROCESS_INFORMATION process_info{};
  wchar_t working_directory[MAX_PATH * 4];
  GetCurrentDirectoryW(static_cast<DWORD>(std::size(working_directory)), working_directory);
  if (!CreateProcessW(executable, command_line.data(), nullptr, nullptr, FALSE, 0, nullptr,
                      working_directory, &startup_info, &process_info)) {
    REXSYS_ERROR("Title relaunch: CreateProcess failed ({})", GetLastError());
    return false;
  }
  CloseHandle(process_info.hThread);
  CloseHandle(process_info.hProcess);
  return true;
}

#else

bool StartProcess(const std::filesystem::path& data_file) {
  std::vector<std::string> arguments;
#if REX_PLATFORM_MAC
  char executable[4096];
  uint32_t size = sizeof(executable);
  if (_NSGetExecutablePath(executable, &size) != 0) {
    return false;
  }
  int argc = *_NSGetArgc();
  char** argv = *_NSGetArgv();
  for (int i = 0; i < argc; ++i) {
    arguments.emplace_back(argv[i]);
  }
#else
  std::error_code ec;
  const std::string executable = std::filesystem::read_symlink("/proc/self/exe", ec).string();
  if (ec) {
    return false;
  }
  std::ifstream cmdline("/proc/self/cmdline", std::ios::binary);
  std::string argument;
  while (std::getline(cmdline, argument, '\0')) {
    arguments.push_back(argument);
  }
#endif
  std::vector<char*> spawn_arguments;
  std::vector<std::string> kept;
  kept.push_back(std::string(executable));
  for (size_t i = 1; i < arguments.size(); ++i) {
    if (arguments[i].rfind(kArgumentPrefix, 0) != 0) {
      kept.push_back(arguments[i]);
    }
  }
  kept.push_back(std::string(kArgumentPrefix) + data_file.string());
  for (auto& item : kept) {
    spawn_arguments.push_back(item.data());
  }
  spawn_arguments.push_back(nullptr);
  pid_t pid = 0;
  const int result = posix_spawn(&pid, kept[0].c_str(), nullptr, nullptr,
                                 spawn_arguments.data(), environ);
  if (result != 0) {
    REXSYS_ERROR("Title relaunch: posix_spawn failed ({})", result);
    return false;
  }
  return true;
}

#endif

}  // namespace

void RequestTitleRelaunch(std::vector<uint8_t> launch_data, uint32_t launch_flags) {
  std::lock_guard lock(g_mutex);
  g_launch_data = std::move(launch_data);
  g_launch_flags = launch_flags;
  g_requested.store(true, std::memory_order_release);
}

bool IsTitleRelaunchRequested() {
  return g_requested.load(std::memory_order_acquire);
}

bool RelaunchProcess(const std::filesystem::path& data_dir) {
  std::vector<uint8_t> data;
  uint32_t flags = 0;
  {
    std::lock_guard lock(g_mutex);
    data = g_launch_data;
    flags = g_launch_flags;
  }
  std::error_code ec;
  std::filesystem::create_directories(data_dir, ec);
  const auto data_file = data_dir / "launch_data.bin";
  {
    std::ofstream out(data_file, std::ios::binary | std::ios::trunc);
    const uint32_t size = static_cast<uint32_t>(data.size());
    out.write(kFileMagic, sizeof(kFileMagic));
    out.write(reinterpret_cast<const char*>(&flags), sizeof(flags));
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    out.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(size));
    if (!out) {
      REXSYS_ERROR("Title relaunch: cannot write {}", data_file.string());
      return false;
    }
  }
  REXSYS_INFO("Relaunching title with {} bytes of launch data", data.size());
  return StartProcess(data_file);
}

bool TakeLaunchDataFile(std::vector<uint8_t>& launch_data, uint32_t& launch_flags) {
  const std::string path = REXCVAR_GET(launch_data_file);
  if (path.empty()) {
    return false;
  }
  std::ifstream in(std::filesystem::path(path), std::ios::binary);
  char magic[sizeof(kFileMagic)] = {};
  uint32_t size = 0;
  in.read(magic, sizeof(magic));
  in.read(reinterpret_cast<char*>(&launch_flags), sizeof(launch_flags));
  in.read(reinterpret_cast<char*>(&size), sizeof(size));
  if (!in || std::memcmp(magic, kFileMagic, sizeof(magic)) != 0 || size > (64u << 20)) {
    REXSYS_WARN("Title relaunch: ignoring unreadable launch data file {}", path);
    return false;
  }
  launch_data.resize(size);
  in.read(reinterpret_cast<char*>(launch_data.data()), static_cast<std::streamsize>(size));
  if (!in) {
    return false;
  }
  in.close();
  std::error_code ec;
  std::filesystem::remove(std::filesystem::path(path), ec);
  REXSYS_INFO("Title relaunch: loaded {} bytes of launch data", size);
  return true;
}

}  // namespace rex::system
