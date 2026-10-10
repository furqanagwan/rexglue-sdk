/**
 * @file        tests/kernel/fault_report_test.cpp
 * @brief       A fatal guest access violation names the recompiled function it
 *              came from
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <rex/system/function_dispatcher.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "kernel_fixture.h"

namespace {

using namespace rex::testing;  // NOLINT

constexpr char kFaultChildEnv[] = "REXGLUE_FAULT_REPORT_CHILD";
constexpr uint32_t kCodeBase = 0x82E00000;
constexpr uint32_t kFaultingAddress = kCodeBase + 0x40;

constexpr uint32_t kUnmappedGuest = 0x3FFF0000;

void FaultingGuestFunction(PPCContext& ctx, uint8_t* base) {
  volatile uint32_t* p = reinterpret_cast<volatile uint32_t*>(base + kUnmappedGuest);
  ctx.r3.u64 = *p;
}

}

TEST_CASE("Fault report child", "[.fault-report-child]") {
  const char* log_path = std::getenv(kFaultChildEnv);
  REQUIRE(log_path);
  auto* kernel = Kernel();
  rex::AddSink(std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path, true));
  auto* dispatcher = kernel->function_dispatcher();
  REQUIRE(dispatcher->InitializeFunctionTable(kCodeBase, 0x1000, kCodeBase, 0x10000));
  REQUIRE(dispatcher->SetFunction(kFaultingAddress, &FaultingGuestFunction));
  PPCContext ctx{};
  dispatcher->GetFunction(kFaultingAddress)(ctx, kernel->memory()->virtual_membase());
  TerminateProcess(GetCurrentProcess(), 77);
}

TEST_CASE("A fatal guest access violation names the guest function", "[kernel][fault]") {
  TempDir root("rex_fault_report");
  const auto log_path = root.path / "child.log";

  wchar_t exe[MAX_PATH];
  REQUIRE(GetModuleFileNameW(nullptr, exe, MAX_PATH));
  std::wstring command = L"\"" + std::wstring(exe) + L"\" \"Fault report child\"";
  const std::wstring env(kFaultChildEnv, kFaultChildEnv + sizeof(kFaultChildEnv) - 1);
  REQUIRE(SetEnvironmentVariableW(env.c_str(), log_path.wstring().c_str()));
  STARTUPINFOW startup = {sizeof(startup)};
  PROCESS_INFORMATION process = {};
  const BOOL started = CreateProcessW(nullptr, command.data(), nullptr, nullptr, FALSE,
                                      CREATE_NO_WINDOW, nullptr, nullptr, &startup, &process);
  SetEnvironmentVariableW(env.c_str(), nullptr);
  REQUIRE(started);
  REQUIRE(WaitForSingleObject(process.hProcess, 60000) == WAIT_OBJECT_0);
  DWORD exit_code = 0;
  GetExitCodeProcess(process.hProcess, &exit_code);
  CloseHandle(process.hThread);
  CloseHandle(process.hProcess);
  CHECK(exit_code != 77);

  std::ifstream in(log_path);
  std::stringstream text;
  text << in.rdbuf();
  const std::string output = text.str();
  INFO(output);
  CHECK(output.find("Unhandled guest access violation: read of guest 0x3FFF0000") !=
        std::string::npos);
  CHECK(output.find("Unhandled guest fault at host kernel_tests") != std::string::npos);
  CHECK(output.find("in sub_82E00040+0x") != std::string::npos);
}
