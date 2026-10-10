/**
 * @file        file_read_test.cpp
 * @brief       NtReadFile completion as on NT: APCs, status block, file event (RG-GDK-042)
 *
 * A caller told STATUS_PENDING has no way to learn a read finished except its
 * APC, event or status block, so an asynchronous handle gets its APC even
 * when the read failed (xenia-edge beb3230fe). The file object's own event is
 * a notification event: every wait returns once a request completes
 * (xenia-edge 8a027ef4f).
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "kernel_fixture.h"

#include <atomic>
#include <chrono>
#include <thread>

#include <rex/ppc.h>
#include <rex/system/function_dispatcher.h>
#include <rex/system/xio.h>
#include <rex/system/kernel_thread.h>
#include <rex/thread.h>
#include <rex/types.h>

namespace rex::kernel::xboxkrnl {
u32 NtReadFile_entry(u32 file_handle, u32 event_handle, mapped_void apc_routine_ptr,
                     mapped_void apc_context,
                     ppc_ptr_t<rex::system::X_IO_STATUS_BLOCK> io_status_block, mapped_void buffer,
                     u32 buffer_length, mapped_u64 byte_offset_ptr);
}

namespace {

namespace xboxkrnl = rex::kernel::xboxkrnl;
using rex::X_RESULT;
using rex::X_STATUS;
using rex::system::object_ref;
using rex::system::X_IO_STATUS_BLOCK;
using rex::system::XFile;
using rex::system::XThread;
using rex::testing::Kernel;

constexpr uint32_t kCodeBase = 0x82D00000;
constexpr uint32_t kReaderAddress = kCodeBase + 0x100;
constexpr uint32_t kApcAddress = kCodeBase + 0x200;
constexpr uint32_t kApcContext = 0x1234;

constexpr uint32_t kBadBuffer = 0xFFFFF000;

struct Request {
  uint32_t file_handle = 0;
  uint32_t buffer = 0;
  uint32_t length = 0;
  uint32_t status_block = 0;
};

Request g_request;
std::atomic<uint32_t> g_result{0};
std::atomic<int> g_apcs{0};
std::atomic<uint32_t> g_apc_context{0};
std::atomic<bool> g_done{false};

void Apc(PPCContext& ctx, uint8_t* base) {
  (void)base;
  g_apc_context = ctx.r3.u32;
  ++g_apcs;
}

void Reader(PPCContext& ctx, uint8_t* base) {
  (void)ctx;
  (void)base;
  auto* memory = Kernel()->memory();
  const Request& r = g_request;
  g_result = xboxkrnl::NtReadFile_entry(
      r.file_handle, 0, mapped_void(memory->TranslateVirtual(kApcAddress), kApcAddress),
      mapped_void(memory->TranslateVirtual(kApcContext), kApcContext),
      ppc_ptr_t<X_IO_STATUS_BLOCK>(memory->TranslateVirtual<X_IO_STATUS_BLOCK*>(r.status_block),
                                   r.status_block),
      mapped_void(memory->TranslateVirtual(r.buffer), r.buffer), r.length, nullptr);

  XThread::GetCurrentThread()->DeliverAPCs();
  g_done = true;
}

void RegisterFunctions() {
  static bool registered = [] {
    auto* dispatcher = Kernel()->function_dispatcher();
    REQUIRE(dispatcher->InitializeFunctionTable(kCodeBase, 0x1000, kCodeBase, 0x10000));
    REQUIRE(dispatcher->SetFunction(kReaderAddress, &Reader));
    REQUIRE(dispatcher->SetFunction(kApcAddress, &Apc));
    return true;
  }();
  (void)registered;
}

struct Outcome {
  uint32_t result;
  uint32_t status;
  uint32_t information;
  int apcs;
};

Outcome RunRead(XFile* file, uint32_t buffer, uint32_t length) {
  RegisterFunctions();
  auto* memory = Kernel()->memory();
  const uint32_t status_block = memory->SystemHeapAlloc(sizeof(X_IO_STATUS_BLOCK));
  REQUIRE(status_block);
  auto* block = memory->TranslateVirtual<X_IO_STATUS_BLOCK*>(status_block);
  block->status = 0xDEADBEEF;
  block->information = 0xDEADBEEF;
  g_request = {file->handle(), buffer, length, status_block};
  g_apcs = 0;
  g_apc_context = 0;
  g_done = false;

  auto thread =
      object_ref<XThread>(new XThread(Kernel(), 64 * 1024, 0, kReaderAddress, 0, 0, true));
  REQUIRE(thread->Create() == X_STATUS_SUCCESS);
  const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
  while (!g_done && std::chrono::steady_clock::now() < deadline) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  REQUIRE(g_done);
  Outcome out{g_result, block->status, block->information, g_apcs};
  if (out.apcs) {
    CHECK(g_apc_context == kApcContext);
  }
  memory->SystemHeapFree(status_block);
  return out;
}

struct TestFile {
  explicit TestFile(bool synchronous)
      : root("rex_file_read"), content(Kernel(), root.path), data(rex::testing::SaveData("READ")) {
    REQUIRE(content.CreateContent("rd", rex::testing::kXuid, data) == X_ERROR_SUCCESS);
    auto writer = rex::testing::OpenGuestFile(Kernel(), "rd", "f.dat");
    rex::testing::WriteGuest(writer.get(), "hello");
    writer->ReleaseHandle();
    writer.reset();
    rex::filesystem::File* host = nullptr;
    rex::filesystem::FileAction action;
    REQUIRE(Kernel()->file_system()->OpenFile(nullptr, "rd:\\f.dat",
                                              rex::filesystem::FileDisposition::kOpen,
                                              rex::filesystem::FileAccess::kGenericRead, false,
                                              true, &host, &action) == X_STATUS_SUCCESS);
    file = object_ref<XFile>(new XFile(Kernel(), host, synchronous));
  }
  ~TestFile() {
    file->ReleaseHandle();
    file.reset();
    content.CloseContent("rd");
  }
  rex::testing::TempDir root;
  rex::system::xam::ContentManager content;
  rex::system::xam::XCONTENT_AGGREGATE_DATA data;
  object_ref<XFile> file;
};

}

TEST_CASE("An asynchronous read that fails still delivers its APC", "[kernel][file_read]") {
  TestFile f(false);
  const Outcome out = RunRead(f.file.get(), kBadBuffer, 0x2000);

  CHECK(out.result == X_STATUS_PENDING);
  CHECK(out.status == X_STATUS_ACCESS_VIOLATION);
  CHECK(out.information == 0);
  CHECK(out.apcs == 1);
}

TEST_CASE("A failed read on a synchronous handle returns the error without an APC",
          "[kernel][file_read]") {
  TestFile f(true);
  const Outcome out = RunRead(f.file.get(), kBadBuffer, 0x2000);
  CHECK(out.result == X_STATUS_ACCESS_VIOLATION);
  CHECK(out.status == X_STATUS_ACCESS_VIOLATION);
  CHECK(out.apcs == 0);
}

TEST_CASE("A successful asynchronous read reports its count and delivers its APC",
          "[kernel][file_read]") {
  TestFile f(false);
  const uint32_t buffer = Kernel()->memory()->SystemHeapAlloc(16);
  REQUIRE(buffer);
  const Outcome out = RunRead(f.file.get(), buffer, 5);
  CHECK(out.result == X_STATUS_PENDING);
  CHECK(out.status == X_STATUS_SUCCESS);
  CHECK(out.information == 5);
  CHECK(out.apcs == 1);
  CHECK(std::string(Kernel()->memory()->TranslateVirtual<const char*>(buffer), 5) == "hello");
  Kernel()->memory()->SystemHeapFree(buffer);
}

TEST_CASE("The file's event stays signalled for every wait until the next request",
          "[kernel][file_read]") {
  TestFile f(false);
  const uint32_t buffer = Kernel()->memory()->SystemHeapAlloc(16);
  REQUIRE(buffer);
  uint32_t bytes_read = 0;
  REQUIRE(f.file->Read(buffer, 5, 0, &bytes_read, 0) == X_STATUS_SUCCESS);

  uint64_t no_wait = 0;
  CHECK(f.file->Wait(3, 1, 0, &no_wait) == X_STATUS_SUCCESS);
  CHECK(f.file->Wait(3, 1, 0, &no_wait) == X_STATUS_SUCCESS);
  Kernel()->memory()->SystemHeapFree(buffer);
}
