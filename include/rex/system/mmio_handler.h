/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include <rex/platform.h>
#include <rex/thread/mutex.h>

namespace rex::arch {
class Exception;
class HostThreadContext;
}

namespace rex::runtime {

typedef uint32_t (*MMIOReadCallback)(void* ppc_context, void* callback_context, uint32_t addr);
typedef void (*MMIOWriteCallback)(void* ppc_context, void* callback_context, uint32_t addr,
                                  uint32_t value);

struct MMIORange {
  uint32_t address;
  uint32_t mask;
  uint32_t size;
  void* callback_context;
  MMIOReadCallback read;
  MMIOWriteCallback write;
};

class MMIOHandler {
 public:
  virtual ~MMIOHandler();

  typedef uint32_t (*HostToGuestVirtual)(const void* context, const void* host_address);
  typedef bool (*AccessViolationCallback)(
      std::unique_lock<std::recursive_mutex> global_lock_locked_once, void* context,
      void* host_address, bool is_write);

  static std::unique_ptr<MMIOHandler> Install(uint8_t* virtual_membase, uint8_t* physical_membase,
                                              uint8_t* membase_end,
                                              HostToGuestVirtual host_to_guest_virtual,
                                              const void* host_to_guest_virtual_context,
                                              AccessViolationCallback access_violation_callback,
                                              void* access_violation_callback_context);
  static MMIOHandler* global_handler();

  using UnhandledFaultReporter = void (*)(void* context, uint64_t host_pc);
  void SetUnhandledFaultReporter(UnhandledFaultReporter reporter, void* context) {
    unhandled_fault_reporter_ = reporter;
    unhandled_fault_reporter_context_ = context;
  }

  bool RegisterRange(uint32_t virtual_address, uint32_t mask, uint32_t size, void* context,
                     MMIOReadCallback read_callback, MMIOWriteCallback write_callback);
  MMIORange* LookupRange(uint32_t virtual_address);

  bool CheckLoad(uint32_t virtual_address, uint32_t* out_value);
  bool CheckStore(uint32_t virtual_address, uint32_t value);

 protected:
  MMIOHandler(uint8_t* virtual_membase, uint8_t* physical_membase, uint8_t* membase_end,
              HostToGuestVirtual host_to_guest_virtual, const void* host_to_guest_virtual_context,
              AccessViolationCallback access_violation_callback,
              void* access_violation_callback_context);

  static bool ExceptionCallbackThunk(arch::Exception* ex, void* data);
  bool ExceptionCallback(arch::Exception* ex);

  uint8_t* virtual_membase_;
  uint8_t* physical_membase_;
  uint8_t* memory_end_;

  std::vector<MMIORange> mapped_ranges_;

  HostToGuestVirtual host_to_guest_virtual_;
  const void* host_to_guest_virtual_context_;

  AccessViolationCallback access_violation_callback_;
  void* access_violation_callback_context_;

  UnhandledFaultReporter unhandled_fault_reporter_ = nullptr;
  void* unhandled_fault_reporter_context_ = nullptr;

  static MMIOHandler* global_handler_;

  rex::thread::global_critical_region global_critical_region_;

 private:
  struct DecodedLoadStore {
    static constexpr uint8_t kArm64RegZero = 31;

    static constexpr uint8_t kArm64MemBaseRegSp = kArm64RegZero;

    static constexpr uint8_t kArm64ValueRegX0 = 0;
    static constexpr uint8_t kArm64ValueRegZero = kArm64ValueRegX0 + kArm64RegZero;
    static constexpr uint8_t kArm64ValueRegV0 = 32;

    size_t length;

    bool is_load;

    bool byte_swap;

    uint8_t value_reg;

    bool mem_has_base;

    uint8_t mem_base_reg;

    bool mem_base_writeback;
    int32_t mem_base_writeback_offset;
    bool mem_has_index;
    uint8_t mem_index_reg;
    uint8_t mem_index_size;
    bool mem_index_sign_extend;
    uint8_t mem_scale;
    ptrdiff_t mem_displacement;
    bool is_constant;
    int32_t constant;
  };

  static bool TryDecodeLoadStore(const uint8_t* p, DecodedLoadStore& decoded_out);
};

}
