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

#include <rex/filesystem/entry.h>
#include <rex/filesystem/file.h>
#include <rex/filesystem/vfs.h>
#include <rex/logging.h>
#include <rex/runtime.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xam/content_manager.h>
#include <rex/system/xfile.h>
#include <rex/system/xobject.h>

using rex::X_RESULT;
using rex::X_STATUS;
using rex::system::KernelState;
using rex::system::object_ref;
using rex::system::XContentType;
using rex::system::XFile;
using rex::system::xam::ContentManager;
using rex::system::xam::XCONTENT_AGGREGATE_DATA;

namespace {

constexpr uint64_t kXuid = 0xE000000012345678ull;
constexpr uint32_t kTitleId = 0x4D5307E6;
constexpr char kCrashChildEnv[] = "REXGLUE_CONTENT_CRASH_CHILD";

KernelState* Kernel() {
  static std::filesystem::path root = [] {
    rex::InitLogging();
    auto path = std::filesystem::temp_directory_path() /
                ("rexglue_kernel_tests_" + std::to_string(GetCurrentProcessId()));
    std::filesystem::create_directories(path);
    return path;
  }();
  static std::unique_ptr<rex::Runtime> runtime = [] {
    auto r = std::make_unique<rex::Runtime>(root);
    REQUIRE(r->Setup(rex::RuntimeConfig{}) == X_STATUS_SUCCESS);
    return r;
  }();
  return runtime->kernel_state();
}

struct TempDir {
  explicit TempDir(const std::string& name)
      : path(std::filesystem::temp_directory_path() /
             (name + "_" + std::to_string(GetCurrentProcessId()) + "_" +
              std::to_string(GetTickCount64()))) {
    std::filesystem::create_directories(path);
  }
  ~TempDir() {
    std::error_code ec;
    std::filesystem::remove_all(path, ec);
  }
  std::filesystem::path path;
};

XCONTENT_AGGREGATE_DATA SaveData(const std::string& file_name) {
  XCONTENT_AGGREGATE_DATA data = {};
  data.device_id = 1;
  data.content_type = XContentType::kSavedGame;
  data.set_display_name(u"Slot 1");
  data.set_file_name(file_name);
  data.xuid = kXuid;
  data.title_id = kTitleId;
  return data;
}

std::filesystem::path HeaderPath(const std::filesystem::path& root, const std::string& file_name) {
  return root / "E000000012345678" / "4D5307E6" / "Headers" / "00000001" / (file_name + ".header");
}

std::filesystem::path PackagePath(const std::filesystem::path& root, const std::string& file_name) {
  return root / "E000000012345678" / "4D5307E6" / "00000001" / file_name;
}

// Opens `path` inside mounted root `root_name` for writing, as the guest's
// NtCreateFile would, and wraps it in a kernel file object.
object_ref<XFile> OpenGuestFile(KernelState* kernel, const std::string& root_name,
                                const std::string& path) {
  rex::filesystem::File* file = nullptr;
  rex::filesystem::FileAction action;
  const X_STATUS status = kernel->file_system()->OpenFile(
      nullptr, root_name + ":\\" + path, rex::filesystem::FileDisposition::kOverwriteIf,
      rex::filesystem::FileAccess::kGenericRead | rex::filesystem::FileAccess::kGenericWrite, false,
      true, &file, &action);
  REQUIRE(status == X_STATUS_SUCCESS);
  REQUIRE(file);
  return object_ref<XFile>(new XFile(kernel, file, true));
}

void WriteGuest(XFile* file, const std::string& bytes) {
  size_t written = 0;
  REQUIRE(file->file()->WriteSync({reinterpret_cast<const uint8_t*>(bytes.data()), bytes.size()}, 0,
                                  &written) == X_STATUS_SUCCESS);
  REQUIRE(written == bytes.size());
}

std::string ReadHost(const std::filesystem::path& path) {
  std::ifstream in(path, std::ios::binary);
  return std::string(std::istreambuf_iterator<char>(in), {});
}

// A file whose host flush fails, standing in for a disk that rejects it.
class FailingFlushFile : public rex::filesystem::File {
 public:
  explicit FailingFlushFile(rex::filesystem::Entry* entry)
      : File(rex::filesystem::FileAccess::kGenericWrite, entry) {}
  void Destroy() override { delete this; }
  X_STATUS ReadSync(std::span<uint8_t>, size_t, size_t*) override { return X_STATUS_SUCCESS; }
  X_STATUS WriteSync(std::span<const uint8_t>, size_t, size_t*) override {
    return X_STATUS_SUCCESS;
  }
  X_STATUS Flush() override { return X_STATUS_UNEXPECTED_IO_ERROR; }
};

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
