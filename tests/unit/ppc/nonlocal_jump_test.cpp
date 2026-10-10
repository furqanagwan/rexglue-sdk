// Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <rex/ppc/nonlocal_jump.h>
#include <thread>

using rex::ppc::NonlocalJumpFrame;

namespace {

__declspec(noinline) void Deeper(PPCContext& ctx, uint32_t address, int32_t value) {
  struct ScribbleOnUnwind {
    PPCContext& ctx;
    ~ScribbleOnUnwind() { ctx.r14.u64 = 888; }
  } scribble{ctx};
  NonlocalJumpFrame inner;
  if (setjmp(inner.Save(0x2000, ctx)) == 0) {
    ctx.r1.u64 = 999;
    ctx.r14.u64 = 999;
    NonlocalJumpFrame::Jump(address, value);
  } else
    inner.Restore(ctx);
}

__declspec(noinline) void RoundTrip(PPCContext& ctx, int32_t value) {
  NonlocalJumpFrame frame;
  if (setjmp(frame.Save(0x1000, ctx)) == 0) {
    ctx.r3.s64 = 0;
    Deeper(ctx, 0x1000, value);
    ctx.r15.u64 = 999;
  } else
    frame.Restore(ctx);
}

__declspec(noinline) void TwoBuffers(PPCContext& ctx) {
  NonlocalJumpFrame frame;
  if (setjmp(frame.Save(0x1000, ctx)) == 0) {
    ctx.r14.u64 = 22;
    if (setjmp(frame.Save(0x1004, ctx)) == 0)
      NonlocalJumpFrame::Jump(0x1000, 7);
    else
      frame.Restore(ctx);
  } else
    frame.Restore(ctx);
}
}

TEST_CASE("Native guest jumps restore state and unwind nested frames", "[ppc][crt-jump]") {
  for (int32_t value : {0, 1, -7, 42}) {
    PPCContext ctx{};
    ctx.r1.u64 = 0x123400;
    ctx.r14.u64 = 11;
    ctx.r15.u64 = 33;
    RoundTrip(ctx, value);
    CHECK(ctx.r3.s64 == (value ? value : 1));
    CHECK(ctx.r1.u64 == 0x123400);
    CHECK(ctx.r14.u64 == 11);
    CHECK(ctx.r15.u64 == 33);
    CHECK_FALSE(NonlocalJumpFrame::IsActive(0x1000));
    CHECK_FALSE(NonlocalJumpFrame::IsActive(0x2000));
  }
}

TEST_CASE("Different guest buffers in one native frame retain separate snapshots",
          "[ppc][crt-jump]") {
  PPCContext ctx{};
  ctx.r14.u64 = 11;
  TwoBuffers(ctx);
  CHECK(ctx.r14.u64 == 11);
  CHECK(ctx.r3.s64 == 7);
  CHECK_FALSE(NonlocalJumpFrame::IsActive(0x1000));
  CHECK_FALSE(NonlocalJumpFrame::IsActive(0x1004));
}

TEST_CASE("Expired and foreign-thread guest jump buffers are rejected", "[ppc][crt-jump]") {
  PPCContext ctx{};
  {
    NonlocalJumpFrame frame;
    if (setjmp(frame.Save(0x3000, ctx)) == 0)
      ctx.r3.s64 = 0;
    bool active = true;
    std::thread worker([&active] { active = NonlocalJumpFrame::IsActive(0x3000); });
    worker.join();
    CHECK_FALSE(active);
  }
  CHECK_THROWS_WITH(NonlocalJumpFrame::Jump(0x3000, 1),
                    "Guest longjmp has no active setjmp on this thread");
}
