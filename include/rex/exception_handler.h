/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 *
 * @file        exception_handler.h
 * @brief       Unified exception handling, thread context, and register defs
 *
 * @remarks     Flattened from arch/{arm64,amd64}/host_thread_context.h,
 *              arch/host_thread_context.h, arch/{arm64,amd64}/exception_handler.h,
 *              and arch/exception_handler.h.
 *              Contains VIXL-derived ARM64 load/store decoding constants.
 */

#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <rex/assert.h>
#include <rex/platform.h>
#include <rex/vec128.h>

#if REX_ARCH_AMD64
#include <xmmintrin.h>
#endif

namespace rex::arch {

enum class Arm64Register {
  kX0,
  kX1,
  kX2,
  kX3,
  kX4,
  kX5,
  kX6,
  kX7,
  kX8,
  kX9,
  kX10,
  kX11,
  kX12,
  kX13,
  kX14,
  kX15,
  kX16,
  kX17,
  kX18,
  kX19,
  kX20,
  kX21,
  kX22,
  kX23,
  kX24,
  kX25,
  kX26,
  kX27,
  kX28,

  kX29,

  kX30,
  kSp,
  kPc,
  kPstate,
  kFpsr,
  kFpcr,

  kV0,
  kV1,
  kV2,
  kV3,
  kV4,
  kV5,
  kV6,
  kV7,
  kV8,
  kV9,
  kV10,
  kV11,
  kV12,
  kV13,
  kV14,
  kV15,
  kV16,
  kV17,
  kV18,
  kV19,
  kV20,
  kV21,
  kV22,
  kV23,
  kV24,
  kV25,
  kV26,
  kV27,
  kV28,
  kV29,
  kV30,
  kV31,
};

struct Arm64ThreadContextMembers {
  uint64_t x[31];
  uint64_t sp;
  uint64_t pc;
  uint64_t pstate;
  uint32_t fpsr;
  uint32_t fpcr;
  vec128_t v[32];
};

#if REX_ARCH_AMD64

enum class X64Register {
  kRip,
  kEflags,

  kIntRegisterFirst,

  kRax = kIntRegisterFirst,
  kRcx,
  kRdx,
  kRbx,
  kRsp,
  kRbp,
  kRsi,
  kRdi,
  kR8,
  kR9,
  kR10,
  kR11,
  kR12,
  kR13,
  kR14,
  kR15,
  kIntRegisterLast = kR15,

  kXmm0,
  kXmm1,
  kXmm2,
  kXmm3,
  kXmm4,
  kXmm5,
  kXmm6,
  kXmm7,
  kXmm8,
  kXmm9,
  kXmm10,
  kXmm11,
  kXmm12,
  kXmm13,
  kXmm14,
  kXmm15,
};

struct X64ThreadContextMembers {
  uint64_t rip;
  uint32_t eflags;
  union {
    struct {
      uint64_t rax;
      uint64_t rcx;
      uint64_t rdx;
      uint64_t rbx;
      uint64_t rsp;
      uint64_t rbp;
      uint64_t rsi;
      uint64_t rdi;
      uint64_t r8;
      uint64_t r9;
      uint64_t r10;
      uint64_t r11;
      uint64_t r12;
      uint64_t r13;
      uint64_t r14;
      uint64_t r15;
    };
    uint64_t int_registers[16];
  };
  union {
    struct {
      vec128_t xmm0;
      vec128_t xmm1;
      vec128_t xmm2;
      vec128_t xmm3;
      vec128_t xmm4;
      vec128_t xmm5;
      vec128_t xmm6;
      vec128_t xmm7;
      vec128_t xmm8;
      vec128_t xmm9;
      vec128_t xmm10;
      vec128_t xmm11;
      vec128_t xmm12;
      vec128_t xmm13;
      vec128_t xmm14;
      vec128_t xmm15;
    };
    vec128_t xmm_registers[16];
  };
};

#endif

#if REX_ARCH_AMD64
using HostRegister = X64Register;
#elif REX_ARCH_ARM64
using HostRegister = Arm64Register;
#else
enum class HostRegister {};
#endif

class HostThreadContext {
 public:
#if REX_ARCH_AMD64
  uint64_t rip;
  uint32_t eflags;
  union {
    struct {
      uint64_t rax;
      uint64_t rcx;
      uint64_t rdx;
      uint64_t rbx;
      uint64_t rsp;
      uint64_t rbp;
      uint64_t rsi;
      uint64_t rdi;
      uint64_t r8;
      uint64_t r9;
      uint64_t r10;
      uint64_t r11;
      uint64_t r12;
      uint64_t r13;
      uint64_t r14;
      uint64_t r15;
    };
    uint64_t int_registers[16];
  };
  union {
    struct {
      vec128_t xmm0;
      vec128_t xmm1;
      vec128_t xmm2;
      vec128_t xmm3;
      vec128_t xmm4;
      vec128_t xmm5;
      vec128_t xmm6;
      vec128_t xmm7;
      vec128_t xmm8;
      vec128_t xmm9;
      vec128_t xmm10;
      vec128_t xmm11;
      vec128_t xmm12;
      vec128_t xmm13;
      vec128_t xmm14;
      vec128_t xmm15;
    };
    vec128_t xmm_registers[16];
  };
#elif REX_ARCH_ARM64
  uint64_t x[31];
  uint64_t sp;
  uint64_t pc;
  uint64_t pstate;
  uint32_t fpsr;
  uint32_t fpcr;
  vec128_t v[32];
#endif

  static const char* GetRegisterName(HostRegister reg);
  std::string GetStringFromValue(HostRegister reg, bool hex) const;
};

// Copyright 2015, VIXL authors

//   * Redistributions of source code must retain the above copyright notice,

//   * Redistributions in binary form must reproduce the above copyright notice,

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS CONTRIBUTORS "AS IS" AND

// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE

constexpr uint32_t kArm64LoadLiteralFMask = UINT32_C(0x3B000000);
constexpr uint32_t kArm64LoadLiteralFixed = UINT32_C(0x18000000);

constexpr uint32_t kArm64LoadStoreAnyFMask = UINT32_C(0x0A000000);
constexpr uint32_t kArm64LoadStoreAnyFixed = UINT32_C(0x08000000);

constexpr uint32_t kArm64LoadStorePairAnyFMask = UINT32_C(0x3A000000);
constexpr uint32_t kArm64LoadStorePairAnyFixed = UINT32_C(0x28000000);
constexpr uint32_t kArm64LoadStorePairLoadBit = UINT32_C(1) << 22;

constexpr uint32_t kArm64LoadStoreMask = UINT32_C(0xC4C00000);
enum class Arm64LoadStoreOp : uint32_t {
  kSTRB_w = UINT32_C(0x00000000),
  kSTRH_w = UINT32_C(0x40000000),
  kSTR_w = UINT32_C(0x80000000),
  kSTR_x = UINT32_C(0xC0000000),
  kLDRB_w = UINT32_C(0x00400000),
  kLDRH_w = UINT32_C(0x40400000),
  kLDR_w = UINT32_C(0x80400000),
  kLDR_x = UINT32_C(0xC0400000),
  kLDRSB_x = UINT32_C(0x00800000),
  kLDRSH_x = UINT32_C(0x40800000),
  kLDRSW_x = UINT32_C(0x80800000),
  kLDRSB_w = UINT32_C(0x00C00000),
  kLDRSH_w = UINT32_C(0x40C00000),
  kSTR_b = UINT32_C(0x04000000),
  kSTR_h = UINT32_C(0x44000000),
  kSTR_s = UINT32_C(0x84000000),
  kSTR_d = UINT32_C(0xC4000000),
  kSTR_q = UINT32_C(0x04800000),
  kLDR_b = UINT32_C(0x04400000),
  kLDR_h = UINT32_C(0x44400000),
  kLDR_s = UINT32_C(0x84400000),
  kLDR_d = UINT32_C(0xC4400000),
  kLDR_q = UINT32_C(0x04C00000),
  kPRFM = UINT32_C(0xC0800000),
};

constexpr uint32_t kArm64LoadStoreOffsetFMask = UINT32_C(0x3B200C00);
enum class Arm64LoadStoreOffsetFixed : uint32_t {
  kUnscaledOffset = UINT32_C(0x38000000),
  kPostIndex = UINT32_C(0x38000400),
  kPreIndex = UINT32_C(0x38000C00),
  kRegisterOffset = UINT32_C(0x38200800),
};

constexpr uint32_t kArm64LoadStoreUnsignedOffsetFMask = UINT32_C(0x3B000000);
constexpr uint32_t kArm64LoadStoreUnsignedOffsetFixed = UINT32_C(0x39000000);

bool IsArm64LoadPrefetchStore(uint32_t instruction, bool& is_store_out);

class Exception {
 public:
  enum class Code {
    kInvalidException = 0,
    kAccessViolation,
    kIllegalInstruction,
  };

  enum class AccessViolationOperation {
    kUnknown,
    kRead,
    kWrite,
  };

  void InitializeAccessViolation(HostThreadContext* thread_context, uint64_t fault_address,
                                 AccessViolationOperation operation) {
    code_ = Code::kAccessViolation;
    thread_context_ = thread_context;
    fault_address_ = fault_address;
    access_violation_operation_ = operation;
  }
  void InitializeIllegalInstruction(HostThreadContext* thread_context) {
    code_ = Code::kIllegalInstruction;
    thread_context_ = thread_context;
  }

  Code code() const { return code_; }

  HostThreadContext* thread_context() const { return thread_context_; }

  uint64_t pc() const {
#if REX_ARCH_AMD64
    return thread_context_->rip;
#elif REX_ARCH_ARM64
    return thread_context_->pc;
#else
    assert_always();
    return 0;
#endif
  }

  void set_resume_pc(uint64_t pc) {
#if REX_ARCH_AMD64
    thread_context_->rip = pc;
#elif REX_ARCH_ARM64
    thread_context_->pc = pc;
#else
    assert_always();
#endif
  }

#if REX_ARCH_AMD64

  uint64_t& ModifyIntRegister(uint32_t index) {
    assert_true(index <= 15);
    modified_int_registers_ |= UINT16_C(1) << index;
    return thread_context_->int_registers[index];
  }
  uint16_t modified_int_registers() const { return modified_int_registers_; }
  vec128_t& ModifyXmmRegister(uint32_t index) {
    assert_true(index <= 15);
    modified_xmm_registers_ |= UINT16_C(1) << index;
    return thread_context_->xmm_registers[index];
  }
  uint16_t modified_xmm_registers() const { return modified_xmm_registers_; }
#elif REX_ARCH_ARM64
  uint64_t& ModifyXRegister(uint32_t index) {
    assert_true(index <= 30);
    modified_x_registers_ |= UINT32_C(1) << index;
    return thread_context_->x[index];
  }
  uint32_t modified_x_registers() const { return modified_x_registers_; }
  vec128_t& ModifyVRegister(uint32_t index) {
    assert_true(index <= 31);
    modified_v_registers_ |= UINT32_C(1) << index;
    return thread_context_->v[index];
  }
  uint32_t modified_v_registers() const { return modified_v_registers_; }
#endif

  uint64_t fault_address() const { return fault_address_; }

  AccessViolationOperation access_violation_operation() const {
    return access_violation_operation_;
  }

 private:
  Code code_ = Code::kInvalidException;
  HostThreadContext* thread_context_ = nullptr;
#if REX_ARCH_AMD64
  uint16_t modified_int_registers_ = 0;
  uint16_t modified_xmm_registers_ = 0;
#elif REX_ARCH_ARM64
  uint32_t modified_x_registers_ = 0;
  uint32_t modified_v_registers_ = 0;
#endif
  uint64_t fault_address_ = 0;
  AccessViolationOperation access_violation_operation_ = AccessViolationOperation::kUnknown;
};

class ExceptionHandler {
 public:
  typedef bool (*Handler)(Exception* ex, void* data);

  static void Install(Handler fn, void* data);

  static void Uninstall(Handler fn, void* data);
};

}
