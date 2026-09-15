/**
 * @file        system/guest_crash_report.cpp
 * @brief       Guest context logged when a fault is not handled
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/system/guest_crash_report.h>

#include <atomic>
#include <string>

#include <fmt/format.h>

#include <rex/logging.h>
#include <rex/platform.h>
#include <rex/ppc/context.h>
#include <rex/system/thread_state.h>

#if REX_PLATFORM_WIN32
#include "../core/platform_win.h"
#else
#include <dlfcn.h>
#endif

namespace rex::system {
namespace {

std::string DescribeHostAddress(uint64_t address) {
#if REX_PLATFORM_WIN32
  HMODULE module = nullptr;
  if (GetModuleHandleExW(
          GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
          reinterpret_cast<LPCWSTR>(address), &module)) {
    wchar_t path[MAX_PATH * 2];
    DWORD length = GetModuleFileNameW(module, path, static_cast<DWORD>(std::size(path)));
    std::wstring wide(path, length);
    const size_t slash = wide.find_last_of(L"\\/");
    std::string name;
    for (wchar_t c : wide.substr(slash == std::wstring::npos ? 0 : slash + 1)) {
      name.push_back(c < 0x80 ? static_cast<char>(c) : '?');
    }
    return fmt::format("{}+0x{:X}", name, address - reinterpret_cast<uint64_t>(module));
  }
#else
  Dl_info info{};
  if (dladdr(reinterpret_cast<void*>(address), &info) && info.dli_fname) {
    std::string name = info.dli_fname;
    const size_t slash = name.find_last_of('/');
    return fmt::format("{}+0x{:X}", slash == std::string::npos ? name : name.substr(slash + 1),
                       address - reinterpret_cast<uint64_t>(info.dli_fbase));
  }
#endif
  return fmt::format("0x{:X}", address);
}

}  // namespace

void LogGuestCrashContext(const char* what, uint64_t host_pc) {
  constexpr int kMaxReports = 5;
  static std::atomic<int> reports{0};
  if (reports.fetch_add(1, std::memory_order_relaxed) >= kMaxReports) {
    return;
  }
  REXSYS_ERROR("Guest fault: {} at {}", what, DescribeHostAddress(host_pc));
  runtime::ThreadState* thread_state = runtime::ThreadState::Get();
  if (!thread_state || !thread_state->context()) {
    REXSYS_ERROR("Guest fault: not on a guest thread");
    return;
  }
  const PPCContext& ctx = *thread_state->context();
  REXSYS_ERROR("Guest fault: guest thread {:X}, lr={:08X} ctr={:08X} r1={:08X} r2={:08X} r13={:08X}",
               thread_state->thread_id(), static_cast<uint32_t>(ctx.lr), ctx.ctr.u32, ctx.r1.u32,
               ctx.r2.u32, ctx.r13.u32);
  const uint32_t regs[] = {ctx.r0.u32,  ctx.r3.u32,  ctx.r4.u32,  ctx.r5.u32,  ctx.r6.u32,
                           ctx.r7.u32,  ctx.r8.u32,  ctx.r9.u32,  ctx.r10.u32, ctx.r11.u32,
                           ctx.r12.u32, ctx.r14.u32, ctx.r15.u32, ctx.r16.u32, ctx.r17.u32,
                           ctx.r18.u32, ctx.r19.u32, ctx.r20.u32, ctx.r21.u32, ctx.r22.u32,
                           ctx.r23.u32, ctx.r24.u32, ctx.r25.u32, ctx.r26.u32, ctx.r27.u32,
                           ctx.r28.u32, ctx.r29.u32, ctx.r30.u32, ctx.r31.u32};
  constexpr const char* names[] = {"r0",  "r3",  "r4",  "r5",  "r6",  "r7",  "r8",  "r9",
                                   "r10", "r11", "r12", "r14", "r15", "r16", "r17", "r18",
                                   "r19", "r20", "r21", "r22", "r23", "r24", "r25", "r26",
                                   "r27", "r28", "r29", "r30", "r31"};
  std::string line;
  for (size_t i = 0; i < std::size(regs); ++i) {
    line += fmt::format("{}={:08X}{}", names[i], regs[i], (i % 8 == 7) ? "\n  " : " ");
  }
  REXSYS_ERROR("Guest fault: registers\n  {}", line);
}

}  // namespace rex::system
