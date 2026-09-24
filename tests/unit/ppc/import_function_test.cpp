/**
 * Tests for ArgTranslator stack argument support and ImportFunction isolation.
 */

#include <cstdint>
#include <cstring>

#include <catch2/catch_test_macros.hpp>

#include <rex/ppc/context.h>
#include <rex/ppc/function.h>
#include <rex/system/xio.h>

namespace rex::kernel::xboxkrnl {
u32 NtOpenFile_entry(mapped_u32 handle_out, u32 desired_access,
                     ppc_ptr_t<rex::system::X_OBJECT_ATTRIBUTES> object_attributes,
                     ppc_ptr_t<rex::system::X_IO_STATUS_BLOCK> io_status_block, u32 share_access,
                     u32 open_options);
}

using namespace rex::ppc;

// Fake 64KB guest memory block for tests
alignas(64) static uint8_t g_test_mem[0x10000] = {};

static uint32_t g_share_access = 0;
static uint32_t g_open_options = 0;

static u32 CaptureNtOpenFileRegisters(mapped_u32, u32, ppc_ptr_t<rex::system::X_OBJECT_ATTRIBUTES>,
                                      ppc_ptr_t<rex::system::X_IO_STATUS_BLOCK>, u32 share_access,
                                      u32 open_options) {
  g_share_access = share_access;
  g_open_options = open_options;
  return 0x1234;
}

TEST_CASE("NtOpenFile keeps ShareAccess in r7 and OpenOptions in r8", "[ppc][kernel]") {
  PPCContext ctx{};
  ctx.r3.u64 = 0x100;
  ctx.r4.u64 = 0x200;
  ctx.r5.u64 = 0x300;
  ctx.r6.u64 = 0x400;
  ctx.r7.u64 = 0x00000003;  // Share read/write.
  ctx.r8.u64 = 0x00000040;  // FILE_NON_DIRECTORY_FILE.

  HostToGuestFunction<&CaptureNtOpenFileRegisters>(ctx, g_test_mem);
  CHECK(g_share_access == 0x00000003);
  CHECK(g_open_options == 0x00000040);
  CHECK(ctx.r3.u64 == 0x1234);

  // Link and invoke the real six-argument export. A five-argument definition
  // cannot satisfy this call, even if the generic translator above works.
  ctx.r3.u64 = 0;
  ctx.r4.u64 = 0;
  ctx.r5.u64 = 0;  // Invalid object attributes are rejected before file I/O.
  ctx.r6.u64 = 0;
  ctx.r7.u64 = 0x00000003;
  ctx.r8.u64 = 0x00000040;
  HostToGuestFunction<&rex::kernel::xboxkrnl::NtOpenFile_entry>(ctx, g_test_mem);
  CHECK(ctx.r3.u64 == 0xC000000Du);  // X_STATUS_INVALID_PARAMETER.
}

TEST_CASE("SetIntegerArgumentValue writes stack args for index > 7", "[ppc][arg_translator]") {
  PPCContext ctx{};
  ctx.r1.u32 = 0x8000;

  ArgTranslator::SetIntegerArgumentValue(ctx, g_test_mem, 8, 0xDEADBEEF);

  uint64_t readback = ArgTranslator::GetIntegerArgumentValue(ctx, g_test_mem, 8);
  CHECK(readback == 0xDEADBEEF);
}

TEST_CASE("SetIntegerArgumentValue writes multiple stack args at correct offsets",
          "[ppc][arg_translator]") {
  PPCContext ctx{};
  ctx.r1.u32 = 0x8000;
  std::memset(g_test_mem + 0x8000, 0, 0x100);

  ArgTranslator::SetIntegerArgumentValue(ctx, g_test_mem, 8, 0x11111111);
  ArgTranslator::SetIntegerArgumentValue(ctx, g_test_mem, 9, 0x22222222);
  ArgTranslator::SetIntegerArgumentValue(ctx, g_test_mem, 10, 0x33333333);

  CHECK(ArgTranslator::GetIntegerArgumentValue(ctx, g_test_mem, 8) == 0x11111111);
  CHECK(ArgTranslator::GetIntegerArgumentValue(ctx, g_test_mem, 9) == 0x22222222);
  CHECK(ArgTranslator::GetIntegerArgumentValue(ctx, g_test_mem, 10) == 0x33333333);
}

TEST_CASE("SetIntegerArgumentValue still works for register args 0-7", "[ppc][arg_translator]") {
  PPCContext ctx{};
  ArgTranslator::SetIntegerArgumentValue(ctx, g_test_mem, 0, 0xAAAA);
  ArgTranslator::SetIntegerArgumentValue(ctx, g_test_mem, 7, 0xBBBB);
  CHECK(ctx.r3.u64 == 0xAAAA);
  CHECK(ctx.r10.u64 == 0xBBBB);
}
