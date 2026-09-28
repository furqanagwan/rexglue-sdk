// Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
#pragma once

#include <csetjmp>
#include <memory>
#include <stdexcept>
#include <unordered_map>

#include <rex/ppc/context.h>

namespace rex::ppc {

// Windows native non-local jumps only. setjmp MUST execute in the generated
// caller, never inside a helper that returns. Generated callers keep all guest
// registers in ctx: native automatic locals are not restored by longjmp.
class NonlocalJumpFrame {
  struct State;
  struct Saved {
    jmp_buf native;
    PPCContext guest;
    State* owner;
    int32_t result;
  };
  using Buffers = std::unordered_map<uint32_t, Saved>;
  struct State {
    Buffers buffers;
    Saved* resumed = nullptr;
  };
  static auto& Active() {
    static thread_local std::unordered_map<uint32_t, Saved*> active;
    return active;
  }

 public:
  NonlocalJumpFrame() : state_(std::make_unique<State>()) {}
  NonlocalJumpFrame(const NonlocalJumpFrame&) = delete;
  NonlocalJumpFrame& operator=(const NonlocalJumpFrame&) = delete;
  ~NonlocalJumpFrame() {
    for (auto& [address, saved] : state_->buffers) {
      auto it = Active().find(address);
      if (it != Active().end() && it->second == &saved)
        Active().erase(it);
    }
  }

  jmp_buf& Save(uint32_t address, const PPCContext& ctx) {
    auto& saved = state_->buffers[address];
    saved.guest = ctx;
    saved.owner = state_.get();
    Active()[address] = &saved;
    return saved.native;
  }

  static bool IsActive(uint32_t address) { return Active().contains(address); }

  void Restore(PPCContext& ctx) {
    auto* saved = state_->resumed;
    if (!saved)
      throw std::runtime_error("Guest setjmp resumed without a saved context");
    // Restore AFTER the native unwind: skipped frame destructors may modify ctx.
    ctx = saved->guest;
    ctx.r3.s64 = saved->result;
    state_->resumed = nullptr;
  }

  [[noreturn]] static void Jump(uint32_t address, int32_t value) {
    auto it = Active().find(address);
    if (it == Active().end())
      throw std::runtime_error("Guest longjmp has no active setjmp on this thread");
    auto* saved = it->second;
    saved->result = value ? value : 1;
    saved->owner->resumed = saved;
    // Generated callers restore from heap state after resuming, so setjmp is
    // a controlling expression, with no modified native local result.
    std::longjmp(saved->native, 1);
  }

 private:
  // Keep mutable snapshots off the native stack. Multiple buffers saved by the
  // same generated function must not overwrite a shared automatic PPCContext.
  const std::unique_ptr<State> state_;
};
}  // namespace rex::ppc
