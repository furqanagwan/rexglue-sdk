/**
 * @file        content_test.cpp
 * @brief       XAM content flush, durable headers and crash persistence (RG-GDK-017)
 *
 * One Runtime per process (its guest Memory is process-wide), set up without a
 * title image; each case uses its own ContentManager over a temporary content
 * root, so saves are disposable copies.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include "kernel_fixture.h"

using rex::X_RESULT;
using rex::X_STATUS;
using rex::system::KernelState;
using rex::system::object_ref;
using rex::system::XContentType;
using rex::system::XFile;
using rex::system::xam::ContentManager;
using rex::system::xam::XCONTENT_AGGREGATE_DATA;

namespace {

using namespace rex::testing;  // NOLINT

constexpr char kCrashChildEnv[] = "REXGLUE_CONTENT_CRASH_CHILD";

}  // namespace

TEST_CASE("Content flush makes written saves durable and reports success", "[kernel][content]") {
  KernelState* kernel = Kernel();
  TempDir root("rex_content_flush");
  ContentManager content(kernel, root.path);
  const auto data = SaveData("SLOT1");

  REQUIRE(content.CreateContent("save", kXuid, data) == X_ERROR_SUCCESS);
  REQUIRE(content.WriteContentHeaderFile(kXuid, data) == X_ERROR_SUCCESS);
  auto file = OpenGuestFile(kernel, "save", "profile.dat");
  WriteGuest(file.get(), "progress=42");

  CHECK(content.FlushContent("save") == X_ERROR_SUCCESS);
  // Some titles flush with other casing than they created with.
  CHECK(content.FlushContent("SAVE") == X_ERROR_SUCCESS);
  CHECK(ReadHost(PackagePath(root.path, "SLOT1") / "profile.dat") == "progress=42");

  file->ReleaseHandle();
  file.reset();
  CHECK(content.CloseContent("save") == X_ERROR_SUCCESS);
}

TEST_CASE("Content flush of a root that is not open fails", "[kernel][content]") {
  TempDir root("rex_content_flush_missing");
  ContentManager content(Kernel(), root.path);
  CHECK(content.FlushContent("nosuchroot") == X_ERROR_FILE_NOT_FOUND);
}

TEST_CASE("Content flush reports a file that could not be flushed", "[kernel][content]") {
  KernelState* kernel = Kernel();
  TempDir root("rex_content_flush_fail");
  ContentManager content(kernel, root.path);
  const auto data = SaveData("SLOT2");
  REQUIRE(content.CreateContent("save2", kXuid, data) == X_ERROR_SUCCESS);
  REQUIRE(content.WriteContentHeaderFile(kXuid, data) == X_ERROR_SUCCESS);

  auto real = OpenGuestFile(kernel, "save2", "a.dat");
  object_ref<XFile> failing(new XFile(kernel, new FailingFlushFile(real->entry()), true));
  CHECK(content.FlushContent("save2") == X_ERROR_WRITE_FAULT);

  failing->ReleaseHandle();
  failing.reset();
  CHECK(content.FlushContent("save2") == X_ERROR_SUCCESS);
  real->ReleaseHandle();
  real.reset();
  content.CloseContent("save2");
}

TEST_CASE("Content flush restores a header lost before it was written", "[kernel][content]") {
  TempDir root("rex_content_header_restore");
  ContentManager content(Kernel(), root.path);
  const auto data = SaveData("SLOT3");
  // Created, but the process stopped before XamContentCreate wrote the header.
  REQUIRE(content.CreateContent("save3", kXuid, data) == X_ERROR_SUCCESS);
  REQUIRE_FALSE(std::filesystem::exists(HeaderPath(root.path, "SLOT3")));

  CHECK(content.FlushContent("save3") == X_ERROR_SUCCESS);
  XCONTENT_AGGREGATE_DATA read_back;
  REQUIRE(content.ReadContentHeaderFile("SLOT3", kXuid, kTitleId, XContentType::kSavedGame,
                                        read_back) == X_ERROR_SUCCESS);
  CHECK(read_back == data);
  CHECK(read_back.display_name() == u"Slot 1");
  content.CloseContent("save3");
}

TEST_CASE("Content headers are replaced whole, never left truncated", "[kernel][content]") {
  TempDir root("rex_content_header_atomic");
  ContentManager content(Kernel(), root.path);
  auto data = SaveData("SLOT4");
  const auto header = HeaderPath(root.path, "SLOT4");

  REQUIRE(content.WriteContentHeaderFile(kXuid, data, 0x1234) == X_ERROR_SUCCESS);
  CHECK(std::filesystem::file_size(header) == sizeof(XCONTENT_AGGREGATE_DATA) + 4);

  // A torn header and a stray temporary from an earlier crash.
  std::filesystem::resize_file(header, 7);
  { std::ofstream(header.string() + ".tmp") << "junk"; }
  data.set_display_name(u"Slot 1 (renamed)");
  REQUIRE(content.WriteContentHeaderFile(kXuid, data) == X_ERROR_SUCCESS);
  CHECK(std::filesystem::file_size(header) == sizeof(XCONTENT_AGGREGATE_DATA));
  CHECK_FALSE(std::filesystem::exists(header.string() + ".tmp"));

  XCONTENT_AGGREGATE_DATA read_back;
  REQUIRE(content.ReadContentHeaderFile("SLOT4", kXuid, kTitleId, XContentType::kSavedGame,
                                        read_back) == X_ERROR_SUCCESS);
  CHECK(read_back.display_name() == u"Slot 1 (renamed)");
}

// Runs in a child process: writes a save, flushes it and dies without any
// cleanup, as a crash would.
TEST_CASE("Content crash child", "[.content-crash-child]") {
  const char* dir = std::getenv(kCrashChildEnv);
  REQUIRE(dir);
  KernelState* kernel = Kernel();
  ContentManager content(kernel, std::filesystem::path(dir));
  const auto data = SaveData("CRASHSAVE");
  REQUIRE(content.CreateContent("save", kXuid, data) == X_ERROR_SUCCESS);
  REQUIRE(content.WriteContentHeaderFile(kXuid, data) == X_ERROR_SUCCESS);
  auto file = OpenGuestFile(kernel, "save", "slot.dat");
  WriteGuest(file.get(), "checkpoint=7");
  REQUIRE(content.FlushContent("save") == X_ERROR_SUCCESS);
  TerminateProcess(GetCurrentProcess(), 77);
}

TEST_CASE("A flushed save survives a crash and is listed after restart", "[kernel][content]") {
  TempDir root("rex_content_crash");

  wchar_t exe[MAX_PATH];
  REQUIRE(GetModuleFileNameW(nullptr, exe, MAX_PATH));
  std::wstring command = L"\"" + std::wstring(exe) + L"\" \"Content crash child\"";
  REQUIRE(SetEnvironmentVariableW(
      std::wstring(kCrashChildEnv, kCrashChildEnv + sizeof(kCrashChildEnv) - 1).c_str(),
      root.path.wstring().c_str()));
  STARTUPINFOW startup = {sizeof(startup)};
  PROCESS_INFORMATION process = {};
  const BOOL started = CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE,
                                      CREATE_NO_WINDOW, nullptr, nullptr, &startup, &process);
  SetEnvironmentVariableW(
      std::wstring(kCrashChildEnv, kCrashChildEnv + sizeof(kCrashChildEnv) - 1).c_str(), nullptr);
  REQUIRE(started);
  REQUIRE(WaitForSingleObject(process.hProcess, 60000) == WAIT_OBJECT_0);
  DWORD exit_code = 0;
  GetExitCodeProcess(process.hProcess, &exit_code);
  CloseHandle(process.hThread);
  CloseHandle(process.hProcess);
  REQUIRE(exit_code == 77);  // died where the crash was injected

  // "Restart": a fresh content manager over the same root.
  ContentManager content(Kernel(), root.path);
  const auto listed = content.ListContent(1, kXuid, XContentType::kSavedGame, kTitleId);
  REQUIRE(listed.size() == 1);
  CHECK(listed[0].file_name() == "CRASHSAVE");
  CHECK(listed[0].display_name() == u"Slot 1");
  CHECK(ReadHost(PackagePath(root.path, "CRASHSAVE") / "slot.dat") == "checkpoint=7");
}
