/**
 * @file        object_leak_test.cpp
 * @brief       Kernel objects created by exports are freed when closed
 *
 * NtCreateIoCompletion and NetDll_WSACreateEvent created their object with a
 * raw `new` and never dropped the creation reference, so closing the guest
 * handle never freed it (upstream ReXGlue 0c7b01a). Each object owns a host
 * handle, so a leak shows as a growing process handle count.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "kernel_fixture.h"

#include <rex/system/xio.h>
#include <rex/types.h>

namespace rex::kernel::xboxkrnl {
u32 NtCreateIoCompletion_entry(mapped_u32 out_handle, u32 desired_access,
                               mapped_void object_attribs, u32 num_concurrent_threads);
u32 NtRemoveIoCompletion_entry(u32 handle, mapped_u32 key_context, mapped_u32 apc_context,
                               ppc_ptr_t<rex::system::X_IO_STATUS_BLOCK> io_status_block,
                               mapped_u64 timeout);
u32 NtClose_entry(u32 handle);
}
namespace rex::kernel::xam {
u32 NetDll_WSACreateEvent_entry();
}

namespace {

namespace xboxkrnl = rex::kernel::xboxkrnl;
using rex::X_STATUS;
using rex::testing::Kernel;

constexpr int kObjects = 1000;

constexpr DWORD kSlack = 50;

DWORD HandleCount() {
  DWORD count = 0;
  GetProcessHandleCount(GetCurrentProcess(), &count);
  return count;
}

}

TEST_CASE("Closing an I/O completion port frees it", "[kernel][leak]") {
  uint32_t out_address = Kernel()->memory()->SystemHeapAlloc(4);
  REQUIRE(out_address);
  mapped_u32 out(Kernel()->memory()->TranslateVirtual<rex::be_u32*>(out_address), out_address);

  REQUIRE(xboxkrnl::NtCreateIoCompletion_entry(out, 0, nullptr, 0) == X_STATUS_SUCCESS);
  REQUIRE(xboxkrnl::NtClose_entry(uint32_t(*out)) == X_STATUS_SUCCESS);

  DWORD before = HandleCount();
  for (int i = 0; i < kObjects; ++i) {
    REQUIRE(xboxkrnl::NtCreateIoCompletion_entry(out, 0, nullptr, 0) == X_STATUS_SUCCESS);
    REQUIRE(xboxkrnl::NtClose_entry(uint32_t(*out)) == X_STATUS_SUCCESS);
  }
  DWORD after = HandleCount();
  INFO("handles before " << before << ", after " << after);
  CHECK(after < before + kSlack);
  Kernel()->memory()->SystemHeapFree(out_address);
}

TEST_CASE("Closing a WSA event frees it", "[kernel][leak]") {
  REQUIRE(Kernel());
  REQUIRE(xboxkrnl::NtClose_entry(rex::kernel::xam::NetDll_WSACreateEvent_entry()) ==
          X_STATUS_SUCCESS);
  DWORD before = HandleCount();
  for (int i = 0; i < kObjects; ++i) {
    REQUIRE(xboxkrnl::NtClose_entry(rex::kernel::xam::NetDll_WSACreateEvent_entry()) ==
            X_STATUS_SUCCESS);
  }
  DWORD after = HandleCount();
  INFO("handles before " << before << ", after " << after);
  CHECK(after < before + kSlack);
}

TEST_CASE("NtRemoveIoCompletion on a bad handle fails instead of crashing", "[kernel][leak]") {
  REQUIRE(Kernel());

  CHECK(xboxkrnl::NtRemoveIoCompletion_entry(0xF8FFFFF0, nullptr, nullptr, nullptr, nullptr) ==
        X_STATUS_INVALID_HANDLE);
}
