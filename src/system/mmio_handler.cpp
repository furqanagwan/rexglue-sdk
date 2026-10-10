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

#include <algorithm>
#include <cstring>
#include <utility>

#include <rex/assert.h>
#include <rex/exception_handler.h>
#include <rex/logging.h>
#include <rex/memory.h>
#include <rex/platform.h>
#include <rex/system/mmio_handler.h>
#include <rex/types.h>

using namespace rex::arch;

namespace rex::runtime {

MMIOHandler* MMIOHandler::global_handler_ = nullptr;

MMIOHandler* MMIOHandler::global_handler() {
  return global_handler_;
}

std::unique_ptr<MMIOHandler> MMIOHandler::Install(uint8_t* virtual_membase,
                                                  uint8_t* physical_membase, uint8_t* membase_end,
                                                  HostToGuestVirtual host_to_guest_virtual,
                                                  const void* host_to_guest_virtual_context,
                                                  AccessViolationCallback access_violation_callback,
                                                  void* access_violation_callback_context) {
  assert_null(global_handler_);
  if (global_handler_) {
    return nullptr;
  }

  auto handler = std::unique_ptr<MMIOHandler>(new MMIOHandler(
      virtual_membase, physical_membase, membase_end, host_to_guest_virtual,
      host_to_guest_virtual_context, access_violation_callback, access_violation_callback_context));

  arch::ExceptionHandler::Install(ExceptionCallbackThunk, handler.get());

  global_handler_ = handler.get();
  return handler;
}

MMIOHandler::MMIOHandler(uint8_t* virtual_membase, uint8_t* physical_membase, uint8_t* membase_end,
                         HostToGuestVirtual host_to_guest_virtual,
                         const void* host_to_guest_virtual_context,
                         AccessViolationCallback access_violation_callback,
                         void* access_violation_callback_context)
    : virtual_membase_(virtual_membase),
      physical_membase_(physical_membase),
      memory_end_(membase_end),
      host_to_guest_virtual_(host_to_guest_virtual),
      host_to_guest_virtual_context_(host_to_guest_virtual_context),
      access_violation_callback_(access_violation_callback),
      access_violation_callback_context_(access_violation_callback_context) {}

MMIOHandler::~MMIOHandler() {
  arch::ExceptionHandler::Uninstall(ExceptionCallbackThunk, this);

  if (global_handler_ == this) {
    global_handler_ = nullptr;
  } else {
    REXLOG_ERROR("~MMIOHandler: global_handler_ does not match this instance");
  }
}

bool MMIOHandler::RegisterRange(uint32_t virtual_address, uint32_t mask, uint32_t size,
                                void* context, MMIOReadCallback read_callback,
                                MMIOWriteCallback write_callback) {
  mapped_ranges_.push_back({
      virtual_address,
      mask,
      size,
      context,
      read_callback,
      write_callback,
  });
  return true;
}

MMIORange* MMIOHandler::LookupRange(uint32_t virtual_address) {
  for (auto& range : mapped_ranges_) {
    if ((virtual_address & range.mask) == range.address) {
      return &range;
    }
  }
  return nullptr;
}

bool MMIOHandler::CheckLoad(uint32_t virtual_address, uint32_t* out_value) {
  for (const auto& range : mapped_ranges_) {
    if ((virtual_address & range.mask) == range.address) {
      *out_value =
          static_cast<uint32_t>(range.read(nullptr, range.callback_context, virtual_address));
      return true;
    }
  }
  return false;
}

bool MMIOHandler::CheckStore(uint32_t virtual_address, uint32_t value) {
  for (const auto& range : mapped_ranges_) {
    if ((virtual_address & range.mask) == range.address) {
      range.write(nullptr, range.callback_context, virtual_address, value);
      return true;
    }
  }
  return false;
}

bool MMIOHandler::TryDecodeLoadStore(const uint8_t* p, DecodedLoadStore& decoded_out) {
  std::memset(&decoded_out, 0, sizeof(decoded_out));
#if REX_ARCH_AMD64
  uint8_t i = 0;
  uint8_t rex = 0;
  if ((p[i] & 0xF0) == 0x40) {
    rex = p[0];
    ++i;
  }
  if (p[i] == 0x0F && p[i + 1] == 0x38 && p[i + 2] == 0xF1) {
    decoded_out.is_load = false;
    decoded_out.byte_swap = true;
    i += 3;
  } else if (p[i] == 0x0F && p[i + 1] == 0x38 && p[i + 2] == 0xF0) {
    decoded_out.is_load = true;
    decoded_out.byte_swap = true;
    i += 3;
  } else if (p[i] == 0x89) {
    decoded_out.is_load = false;
    decoded_out.byte_swap = false;
    ++i;
  } else if (p[i] == 0x8B) {
    decoded_out.is_load = true;
    decoded_out.byte_swap = false;
    ++i;
  } else if (p[i] == 0xC7) {
    decoded_out.is_load = false;
    decoded_out.byte_swap = false;
    decoded_out.is_constant = true;
    ++i;
  } else {
    return false;
  }

  uint8_t rex_b = rex & 0b0001;
  uint8_t rex_x = rex & 0b0010;
  uint8_t rex_r = rex & 0b0100;
  uint8_t rex_w = rex & 0b1000;

  uint8_t modrm = p[i++];
  uint8_t mod = (modrm & 0b11000000) >> 6;
  uint8_t reg = (modrm & 0b00111000) >> 3;
  uint8_t rm = (modrm & 0b00000111);
  decoded_out.value_reg = reg + (rex_r ? 8 : 0);
  decoded_out.mem_has_base = false;
  decoded_out.mem_base_reg = 0;
  decoded_out.mem_has_index = false;
  decoded_out.mem_index_reg = 0;
  decoded_out.mem_scale = 1;
  decoded_out.mem_displacement = 0;
  bool has_sib = false;
  switch (rm) {
    case 0b100:
      has_sib = true;
      break;
    case 0b101:
      if (mod == 0b00) {
        return false;
      }
      decoded_out.mem_has_base = true;
      decoded_out.mem_base_reg = rm + (rex_b ? 8 : 0);
      break;
    default:
      decoded_out.mem_has_base = true;
      decoded_out.mem_base_reg = rm + (rex_b ? 8 : 0);
      break;
  }
  if (has_sib) {
    uint8_t sib = p[i++];
    decoded_out.mem_scale = 1 << ((sib & 0b11000000) >> 8);
    uint8_t sib_index = (sib & 0b00111000) >> 3;
    uint8_t sib_base = (sib & 0b00000111);
    switch (sib_index) {
      case 0b100:

        break;
      default:
        decoded_out.mem_has_index = true;
        decoded_out.mem_index_reg = sib_index + (rex_x ? 8 : 0);
        decoded_out.mem_index_size = sizeof(uint64_t);
        break;
    }
    switch (sib_base) {
      case 0b101:

        assert_zero(mod);
        return false;
      default:
        decoded_out.mem_has_base = true;
        decoded_out.mem_base_reg = sib_base + (rex_b ? 8 : 0);
        break;
    }
  }
  switch (mod) {
    case 0b00: {
      decoded_out.mem_displacement += 0;
    } break;
    case 0b01: {
      decoded_out.mem_displacement += int8_t(p[i++]);
    } break;
    case 0b10: {
      decoded_out.mem_displacement += memory::load<int32_t>(p + i);
      i += 4;
    } break;
  }
  if (decoded_out.is_constant) {
    decoded_out.constant = memory::load<int32_t>(p + i);
    i += 4;
  }
  decoded_out.length = i;
  return true;

#elif REX_ARCH_ARM64
  decoded_out.length = sizeof(uint32_t);
  uint32_t instruction = *reinterpret_cast<const uint32_t*>(p);

  if ((instruction & kArm64LoadStoreAnyFMask) != kArm64LoadStoreAnyFixed) {
    return false;
  }

  if ((instruction & kArm64LoadStorePairAnyFMask) == kArm64LoadStorePairAnyFixed) {
    return false;
  }

  uint8_t value_reg_base;
  switch (Arm64LoadStoreOp(instruction & kArm64LoadStoreMask)) {
    case Arm64LoadStoreOp::kSTR_w:
      decoded_out.is_load = false;
      value_reg_base = DecodedLoadStore::kArm64ValueRegX0;
      break;
    case Arm64LoadStoreOp::kLDR_w:
      decoded_out.is_load = true;
      value_reg_base = DecodedLoadStore::kArm64ValueRegX0;
      break;
    case Arm64LoadStoreOp::kSTR_s:
      decoded_out.is_load = false;
      value_reg_base = DecodedLoadStore::kArm64ValueRegV0;
      break;
    case Arm64LoadStoreOp::kLDR_s:
      decoded_out.is_load = true;
      value_reg_base = DecodedLoadStore::kArm64ValueRegV0;
      break;
    default:
      return false;
  }

  decoded_out.value_reg = value_reg_base + (instruction & 31);
  if (decoded_out.is_load && decoded_out.value_reg == DecodedLoadStore::kArm64ValueRegZero) {
    decoded_out.is_constant = true;
    decoded_out.constant = 0;
  }

  decoded_out.mem_has_base = true;

  decoded_out.mem_base_reg = (instruction >> 5) & 31;

  bool is_unsigned_offset =
      (instruction & kArm64LoadStoreUnsignedOffsetFMask) == kArm64LoadStoreUnsignedOffsetFixed;
  if (is_unsigned_offset) {
    uint32_t unsigned_offset = (instruction >> 10) & 4095;
    decoded_out.mem_displacement = ptrdiff_t(sizeof(uint32_t) * unsigned_offset);
  } else {
    Arm64LoadStoreOffsetFixed offset =
        Arm64LoadStoreOffsetFixed(instruction & kArm64LoadStoreOffsetFMask);
    int32_t signed_offset = int32_t(instruction << (32 - (9 + 12))) >> (32 - 9);
    switch (offset) {
      case Arm64LoadStoreOffsetFixed::kUnscaledOffset: {
        decoded_out.mem_displacement = signed_offset;
      } break;
      case Arm64LoadStoreOffsetFixed::kPostIndex: {
        decoded_out.mem_base_writeback = true;
        decoded_out.mem_base_writeback_offset = signed_offset;
      } break;
      case Arm64LoadStoreOffsetFixed::kPreIndex: {
        decoded_out.mem_base_writeback = true;
        decoded_out.mem_base_writeback_offset = signed_offset;
        decoded_out.mem_displacement = signed_offset;
      } break;
      case Arm64LoadStoreOffsetFixed::kRegisterOffset: {
        decoded_out.mem_index_reg = (instruction >> 16) & 31;
        if (decoded_out.mem_index_reg != DecodedLoadStore::kArm64RegZero) {
          decoded_out.mem_has_index = true;
          uint32_t extend_mode = (instruction >> 13) & 0b111;
          if (!(extend_mode & 0b010)) {
            return false;
          }
          decoded_out.mem_index_size = (extend_mode & 0b001) ? sizeof(uint64_t) : sizeof(uint32_t);
          decoded_out.mem_index_sign_extend = (extend_mode & 0b100) != 0;
          decoded_out.mem_scale = (instruction & (UINT32_C(1) << 12)) ? sizeof(uint32_t) : 1;
        }
      } break;
      default:
        return false;
    }
  }

  return true;

#else
#error TryDecodeLoadStore not implemented for the target CPU architecture.
  return false;
#endif
}

bool MMIOHandler::ExceptionCallbackThunk(arch::Exception* ex, void* data) {
  return reinterpret_cast<MMIOHandler*>(data)->ExceptionCallback(ex);
}

bool MMIOHandler::ExceptionCallback(arch::Exception* ex) {
  if (ex->code() != arch::Exception::Code::kAccessViolation) {
    return false;
  }
  arch::Exception::AccessViolationOperation operation = ex->access_violation_operation();
  if (operation != arch::Exception::AccessViolationOperation::kRead &&
      operation != arch::Exception::AccessViolationOperation::kWrite) {
    return false;
  }
  bool is_write = operation == arch::Exception::AccessViolationOperation::kWrite;
  if (ex->fault_address() < uint64_t(virtual_membase_) ||
      ex->fault_address() > uint64_t(memory_end_)) {
    return false;
  }
  void* fault_host_address = reinterpret_cast<void*>(ex->fault_address());

  const MMIORange* range = nullptr;
  uint32_t fault_guest_virtual_address = 0;
  if (ex->fault_address() < uint64_t(physical_membase_)) {
    fault_guest_virtual_address =
        host_to_guest_virtual_(host_to_guest_virtual_context_, fault_host_address);
    for (const auto& test_range : mapped_ranges_) {
      if ((fault_guest_virtual_address & test_range.mask) == test_range.address) {
        range = &test_range;
        break;
      }
    }
  }
  if (!range) {
    auto lock = global_critical_region_.Acquire();
    memory::PageAccess cur_access;
    size_t page_length = memory::page_size();
    memory::QueryProtect(fault_host_address, page_length, cur_access);
    if (cur_access != memory::PageAccess::kNoAccess &&
        (!is_write || cur_access != memory::PageAccess::kReadOnly)) {
      return true;
    }

    bool handled = false;
    if (access_violation_callback_) {
      handled = access_violation_callback_(std::move(lock), access_violation_callback_context_,
                                           fault_host_address, is_write);
    }
    if (!handled && unhandled_fault_reporter_) {
      unhandled_fault_reporter_(unhandled_fault_reporter_context_, ex->pc());
    }
    return handled;
  }

  auto rip = ex->pc();
  auto p = reinterpret_cast<const uint8_t*>(rip);
  DecodedLoadStore decoded_load_store;
  if (!TryDecodeLoadStore(p, decoded_load_store)) {
    REXLOG_ERROR("Unable to decode MMIO load or store instruction at {:p}",
                 static_cast<const void*>(p));
    assert_always("Unknown MMIO instruction type");
    return false;
  }

  arch::HostThreadContext& thread_context = *ex->thread_context();

#if REX_ARCH_ARM64

  uintptr_t mem_base_writeback_address = 0;
  if (decoded_load_store.mem_has_base && decoded_load_store.mem_base_writeback) {
    if (decoded_load_store.mem_base_reg == DecodedLoadStore::kArm64MemBaseRegSp) {
      mem_base_writeback_address = thread_context.sp;
    } else {
      assert_true(decoded_load_store.mem_base_reg <= 30);
      mem_base_writeback_address = thread_context.x[decoded_load_store.mem_base_reg];
    }
    mem_base_writeback_address += decoded_load_store.mem_base_writeback_offset;
  }
#endif

  uint8_t value_reg = decoded_load_store.value_reg;
  if (decoded_load_store.is_load) {
    uint32_t value = range->read(nullptr, range->callback_context, fault_guest_virtual_address);
    if (!decoded_load_store.byte_swap) {
      value = rex::byte_swap(value);
    }
#if REX_ARCH_AMD64
    ex->ModifyIntRegister(value_reg) = value;
#elif REX_ARCH_ARM64
    if (value_reg >= DecodedLoadStore::kArm64ValueRegX0 &&
        value_reg <= (DecodedLoadStore::kArm64ValueRegX0 + 30)) {
      ex->ModifyXRegister(value_reg - DecodedLoadStore::kArm64ValueRegX0) = value;
    } else if (value_reg >= DecodedLoadStore::kArm64ValueRegV0 &&
               value_reg <= (DecodedLoadStore::kArm64ValueRegV0 + 31)) {
      ex->ModifyVRegister(value_reg - DecodedLoadStore::kArm64ValueRegV0).u32[0] = value;
    } else {
      assert_true(value_reg == DecodedLoadStore::kArm64ValueRegZero);
    }
#else
#error Register value writing not implemented for the target CPU architecture.
#endif
  } else {
    uint32_t value;
    if (decoded_load_store.is_constant) {
      value = uint32_t(decoded_load_store.constant);
    } else {
#if REX_ARCH_AMD64
      value = uint32_t(thread_context.int_registers[value_reg]);
#elif REX_ARCH_ARM64
      if (value_reg >= DecodedLoadStore::kArm64ValueRegX0 &&
          value_reg <= (DecodedLoadStore::kArm64ValueRegX0 + 30)) {
        value = uint32_t(thread_context.x[value_reg - DecodedLoadStore::kArm64ValueRegX0]);
      } else if (value_reg >= DecodedLoadStore::kArm64ValueRegV0 &&
                 value_reg <= (DecodedLoadStore::kArm64ValueRegV0 + 31)) {
        value = thread_context.v[value_reg - DecodedLoadStore::kArm64ValueRegV0].u32[0];
      } else {
        assert_true(value_reg == DecodedLoadStore::kArm64ValueRegZero);
        value = 0;
      }
#else
#error Register value reading not implemented for the target CPU architecture.
#endif
      if (!decoded_load_store.byte_swap) {
        value = rex::byte_swap(value);
      }
    }
    range->write(nullptr, range->callback_context, fault_guest_virtual_address, value);
  }

#if REX_ARCH_ARM64

  if (decoded_load_store.mem_has_base && decoded_load_store.mem_base_writeback) {
    if (decoded_load_store.mem_base_reg == DecodedLoadStore::kArm64MemBaseRegSp) {
      thread_context.sp = mem_base_writeback_address;
    } else {
      assert_true(decoded_load_store.mem_base_reg <= 30);
      ex->ModifyXRegister(decoded_load_store.mem_base_reg) = mem_base_writeback_address;
    }
  }
#endif

  ex->set_resume_pc(rip + decoded_load_store.length);

  return true;
}

}
