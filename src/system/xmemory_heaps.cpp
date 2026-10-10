/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <algorithm>
#include <cstring>
#include <utility>
#include <fmt/format.h>
#include <rex/assert.h>
#include <rex/chrono/clock.h>
#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/stream.h>
#include <rex/system/function_dispatcher.h>
#include <rex/system/mmio_handler.h>
#include <rex/system/xmemory.h>
#include <rex/thread.h>
#include <rex/system/xtypes.h>

namespace rex::memory {

rex::memory::PageAccess ToPageAccess(uint32_t protect);

VirtualHeap::VirtualHeap() = default;

VirtualHeap::~VirtualHeap() = default;

void VirtualHeap::Initialize(memory::Memory* memory, uint8_t* membase, HeapType heap_type,
                             uint32_t heap_base, uint32_t heap_size, uint32_t page_size) {
  BaseHeap::Initialize(memory, membase, heap_type, heap_base, heap_size, page_size);
}

PhysicalHeap::PhysicalHeap() : parent_heap_(nullptr) {}

PhysicalHeap::~PhysicalHeap() = default;

void PhysicalHeap::Initialize(memory::Memory* memory, uint8_t* membase, HeapType heap_type,
                              uint32_t heap_base, uint32_t heap_size, uint32_t page_size,
                              VirtualHeap* parent_heap) {
  uint32_t host_address_offset;
  if (heap_base >= 0xE0000000 && rex::memory::allocation_granularity() > 0x1000) {
    host_address_offset = 0x1000;
  } else {
    host_address_offset = 0;
  }

  BaseHeap::Initialize(memory, membase, heap_type, heap_base, heap_size, page_size,
                       host_address_offset);
  parent_heap_ = parent_heap;
  system_page_size_ = uint32_t(rex::memory::page_size());

  system_page_count_ =
      (size_t(heap_size_) + host_address_offset + (system_page_size_ - 1)) / system_page_size_;
  system_page_flags_.resize((system_page_count_ + 63) / 64);
}

bool PhysicalHeap::Alloc(uint32_t size, uint32_t alignment, uint32_t allocation_type,
                         uint32_t protect, bool top_down, uint32_t* out_address) {
  *out_address = 0;

  top_down = true;

  size = rex::round_up(size, page_size_);
  alignment = rex::round_up(alignment, page_size_);

  auto global_lock = AcquireHostPageReconcileLock();
  std::lock_guard<std::recursive_mutex> heap_lock(heap_mutex_);

  uint32_t parent_heap_start = GetPhysicalAddress(heap_base_);
  uint32_t parent_heap_end = GetPhysicalAddress(heap_base_ + (heap_size_ - 1));
  uint32_t parent_address;
  if (!parent_heap_->AllocRange(parent_heap_start, parent_heap_end, size, alignment,
                                allocation_type, protect, top_down, &parent_address)) {
    REXSYS_ERROR("PhysicalHeap::Alloc unable to alloc physical memory in parent heap");
    return false;
  }

  uint32_t address = heap_base_ + parent_address - parent_heap_start;
  if (!BaseHeap::AllocFixed(address, size, alignment, allocation_type, protect)) {
    REXSYS_ERROR("PhysicalHeap::Alloc unable to pin physical memory in physical heap");

    return false;
  }
  *out_address = address;
  return true;
}

bool PhysicalHeap::AllocFixed(uint32_t base_address, uint32_t size, uint32_t alignment,
                              uint32_t allocation_type, uint32_t protect) {
  size = rex::round_up(size, page_size_);
  alignment = rex::round_up(alignment, page_size_);

  auto global_lock = AcquireHostPageReconcileLock();
  std::lock_guard<std::recursive_mutex> heap_lock(heap_mutex_);

  uint32_t parent_base_address = GetPhysicalAddress(base_address);
  if (!parent_heap_->AllocFixed(parent_base_address, size, alignment, allocation_type, protect)) {
    REXSYS_ERROR("PhysicalHeap::Alloc unable to alloc physical memory in parent heap");
    return false;
  }

  uint32_t address = heap_base_ + parent_base_address - GetPhysicalAddress(heap_base_);
  if (!BaseHeap::AllocFixed(address, size, page_size_, allocation_type, protect)) {
    REXSYS_ERROR("PhysicalHeap::Alloc unable to pin physical memory in physical heap");

    return false;
  }

  return true;
}

bool PhysicalHeap::AllocRange(uint32_t low_address, uint32_t high_address, uint32_t size,
                              uint32_t alignment, uint32_t allocation_type, uint32_t protect,
                              bool top_down, uint32_t* out_address) {
  *out_address = 0;

  size = rex::round_up(size, page_size_);
  alignment = rex::round_up(alignment, page_size_);

  auto global_lock = AcquireHostPageReconcileLock();
  std::lock_guard<std::recursive_mutex> heap_lock(heap_mutex_);

  low_address = std::max(heap_base_, low_address);
  high_address = std::min(heap_base_ + (heap_size_ - 1), high_address);
  uint32_t parent_low_address = GetPhysicalAddress(low_address);
  uint32_t parent_high_address = GetPhysicalAddress(high_address);
  uint32_t parent_address;
  if (!parent_heap_->AllocRange(parent_low_address, parent_high_address, size, alignment,
                                allocation_type, protect, top_down, &parent_address)) {
    REXSYS_ERROR("PhysicalHeap::Alloc unable to alloc physical memory in parent heap");
    return false;
  }

  uint32_t address = heap_base_ + parent_address - GetPhysicalAddress(heap_base_);
  if (!BaseHeap::AllocFixed(address, size, page_size_, allocation_type, protect)) {
    REXSYS_ERROR("PhysicalHeap::Alloc unable to pin physical memory in physical heap");

    return false;
  }
  *out_address = address;
  return true;
}

bool PhysicalHeap::AllocSystemHeap(uint32_t size, uint32_t alignment, uint32_t allocation_type,
                                   uint32_t protect, bool top_down, uint32_t* out_address) {
  return Alloc(size, alignment, allocation_type, protect, top_down, out_address);
}

bool PhysicalHeap::Decommit(uint32_t address, uint32_t size) {
  auto global_lock = global_critical_region_.Acquire();

  uint32_t parent_address = GetPhysicalAddress(address);
  if (!parent_heap_->Decommit(parent_address, size)) {
    REXSYS_ERROR("PhysicalHeap::Decommit failed due to parent heap failure");
    return false;
  }

  TriggerCallbacks(std::move(global_lock), address, size, true, true);

  return BaseHeap::Decommit(address, size);
}

bool PhysicalHeap::Release(uint32_t base_address, uint32_t* out_region_size) {
  auto global_lock = global_critical_region_.Acquire();

  uint32_t parent_base_address = GetPhysicalAddress(base_address);
  if (!parent_heap_->Release(parent_base_address, out_region_size)) {
    REXSYS_ERROR("PhysicalHeap::Release failed due to parent heap failure");
    return false;
  }

  uint32_t region_size;
  if (QuerySize(base_address, &region_size)) {
    TriggerCallbacks(std::move(global_lock), base_address, region_size, true, true);
  }

  return BaseHeap::Release(base_address, out_region_size);
}

bool PhysicalHeap::Protect(uint32_t address, uint32_t size, uint32_t protect,
                           uint32_t* old_protect) {
  auto global_lock = global_critical_region_.Acquire();

  if (protect & memory::kMemoryProtectWrite) {
    TriggerCallbacks(std::move(global_lock), address, size, true, true, false);
  }

  if (!parent_heap_->Protect(GetPhysicalAddress(address), size, protect, old_protect)) {
    REXSYS_ERROR("PhysicalHeap::Protect failed due to parent heap failure");
    return false;
  }

  return BaseHeap::Protect(address, size, protect);
}

void PhysicalHeap::EnableAccessCallbacks(uint32_t physical_address, uint32_t length,
                                         bool enable_invalidation_notifications,
                                         bool enable_data_providers) {
  assert_false(enable_data_providers);
  if (!enable_invalidation_notifications && !enable_data_providers) {
    return;
  }
  uint32_t physical_address_offset = GetPhysicalAddress(heap_base_);
  if (physical_address < physical_address_offset) {
    if (physical_address_offset - physical_address >= length) {
      return;
    }
    length -= physical_address_offset - physical_address;
    physical_address = physical_address_offset;
  }
  uint32_t heap_relative_address = physical_address - physical_address_offset;
  if (heap_relative_address >= heap_size_) {
    return;
  }
  length = std::min(length, heap_size_ - heap_relative_address);
  if (length == 0) {
    return;
  }

  uint32_t system_page_first = (heap_relative_address + host_address_offset()) / system_page_size_;
  uint32_t system_page_last =
      (heap_relative_address + length - 1 + host_address_offset()) / system_page_size_;
  system_page_last = std::min(system_page_last, system_page_count_ - 1);
  assert_true(system_page_first <= system_page_last);

  rex::memory::PageAccess protect_access = enable_data_providers
                                               ? rex::memory::PageAccess::kNoAccess
                                               : rex::memory::PageAccess::kReadOnly;
  uint8_t* protect_base = membase_ + heap_base_;
  uint32_t protect_system_page_first = UINT32_MAX;
  auto global_lock = global_critical_region_.Acquire();
  for (uint32_t i = system_page_first; i <= system_page_last; ++i) {
    SystemPageFlagsBlock& page_flags_block = system_page_flags_[i >> 6];
    uint64_t page_flags_bit = uint64_t(1) << (i & 63);
    uint32_t guest_page_number =
        rex::sat_sub(i * system_page_size_, host_address_offset()) >> page_size_shift_;
    if (guest_page_number >= page_table_.size()) {
      REXSYS_ERROR("Access callback page OOB: system_page={} guest_page={} offset=0x{:X}", i,
                   guest_page_number, host_address_offset());
      assert_always();
      continue;
    }
    rex::memory::PageAccess current_page_access =
        ToPageAccess(page_table_[guest_page_number].current_protect);
    bool protect_system_page = false;

    if (current_page_access != rex::memory::PageAccess::kNoAccess) {
      if (enable_invalidation_notifications) {
        if (current_page_access != rex::memory::PageAccess::kReadOnly &&
            (page_flags_block.notify_on_invalidation & page_flags_bit) == 0) {
          protect_system_page = true;
          page_flags_block.notify_on_invalidation |= page_flags_bit;
        }
      }
    }
    if (protect_system_page) {
      if (protect_system_page_first == UINT32_MAX) {
        protect_system_page_first = i;
      }
    } else {
      if (protect_system_page_first != UINT32_MAX) {
        rex::memory::Protect(protect_base + protect_system_page_first * system_page_size_,
                             (i - protect_system_page_first) * system_page_size_, protect_access);
        protect_system_page_first = UINT32_MAX;
      }
    }
  }
  if (protect_system_page_first != UINT32_MAX) {
    rex::memory::Protect(protect_base + protect_system_page_first * system_page_size_,
                         (system_page_last + 1 - protect_system_page_first) * system_page_size_,
                         protect_access);
  }
}

bool PhysicalHeap::TriggerCallbacks(std::unique_lock<std::recursive_mutex> global_lock_locked_once,
                                    uint32_t virtual_address, uint32_t length, bool is_write,
                                    bool unwatch_exact_range, bool unprotect) {
  assert_true(is_write);
  if (!is_write) {
    return false;
  }

  if (virtual_address < heap_base_) {
    if (heap_base_ - virtual_address >= length) {
      return false;
    }
    length -= heap_base_ - virtual_address;
    virtual_address = heap_base_;
  }
  uint32_t heap_relative_address = virtual_address - heap_base_;
  if (heap_relative_address >= heap_size_) {
    return false;
  }
  length = std::min(length, heap_size_ - heap_relative_address);
  if (length == 0) {
    return false;
  }

  uint32_t system_page_first = (heap_relative_address + host_address_offset()) / system_page_size_;
  uint32_t system_page_last =
      (heap_relative_address + length - 1 + host_address_offset()) / system_page_size_;
  system_page_last = std::min(system_page_last, system_page_count_ - 1);
  assert_true(system_page_first <= system_page_last);
  uint32_t block_index_first = system_page_first >> 6;
  uint32_t block_index_last = system_page_last >> 6;

  bool any_watched = false;
  for (uint32_t i = block_index_first; i <= block_index_last; ++i) {
    uint64_t block = system_page_flags_[i].notify_on_invalidation;
    if (i == block_index_first) {
      block &= ~((uint64_t(1) << (system_page_first & 63)) - 1);
    }
    if (i == block_index_last && (system_page_last & 63) != 63) {
      block &= (uint64_t(1) << ((system_page_last & 63) + 1)) - 1;
    }
    if (block) {
      any_watched = true;
      break;
    }
  }
  if (!any_watched) {
    return false;
  }

  if (!unprotect) {
    unwatch_exact_range = true;
  }
  uint32_t physical_address_offset = GetPhysicalAddress(heap_base_);
  uint32_t physical_address_start =
      rex::sat_sub(system_page_first * system_page_size_, host_address_offset()) +
      physical_address_offset;
  uint32_t physical_length =
      std::min(rex::sat_sub(system_page_last * system_page_size_ + system_page_size_,
                            host_address_offset()) +
                   physical_address_offset - physical_address_start,
               heap_size_ - (physical_address_start - physical_address_offset));
  uint32_t unwatch_first = 0;
  uint32_t unwatch_last = UINT32_MAX;
  for (auto invalidation_callback : memory_->physical_memory_invalidation_callbacks_) {
    std::pair<uint32_t, uint32_t> callback_unwatch_range =
        invalidation_callback->first(invalidation_callback->second, physical_address_start,
                                     physical_length, unwatch_exact_range);
    if (!unwatch_exact_range) {
      unwatch_first = std::max(unwatch_first, callback_unwatch_range.first);
      unwatch_last = std::min(
          unwatch_last, rex::sat_add(callback_unwatch_range.first,
                                     std::max(callback_unwatch_range.second, uint32_t(1)) - 1));
    }
  }
  if (!unwatch_exact_range) {
    unwatch_first = std::min(unwatch_first, physical_address_start);
    unwatch_last = std::max(unwatch_last, physical_address_start + physical_length - 1);

    const uint32_t kMaxUnwatchExcess = 4 * 1024 * 1024;
    unwatch_first = std::max(unwatch_first, physical_address_start & ~(kMaxUnwatchExcess - 1));
    unwatch_last = std::min(
        unwatch_last, (physical_address_start + physical_length - 1) | (kMaxUnwatchExcess - 1));

    unwatch_first = rex::sat_sub(unwatch_first, physical_address_offset);
    unwatch_last = rex::sat_sub(unwatch_last, physical_address_offset);

    unwatch_first = std::min(unwatch_first, heap_size_ - 1);
    unwatch_last = std::min(unwatch_last, heap_size_ - 1);

    unwatch_first += host_address_offset();
    unwatch_last += host_address_offset();
    assert_true(unwatch_first <= unwatch_last);
    system_page_first = unwatch_first / system_page_size_;
    system_page_last = unwatch_last / system_page_size_;
    block_index_first = system_page_first >> 6;
    block_index_last = system_page_last >> 6;
  }

  if (unprotect) {
    uint8_t* protect_base = membase_ + heap_base_;
    uint32_t unprotect_system_page_first = UINT32_MAX;
    for (uint32_t i = system_page_first; i <= system_page_last; ++i) {
      bool unprotect_page =
          (system_page_flags_[i >> 6].notify_on_invalidation & (uint64_t(1) << (i & 63))) != 0;
      if (unprotect_page) {
        uint32_t guest_page_number =
            rex::sat_sub(i * system_page_size_, host_address_offset()) >> page_size_shift_;
        if (ToPageAccess(page_table_[guest_page_number].current_protect) !=
            rex::memory::PageAccess::kReadWrite) {
          unprotect_page = false;
        }
      }
      if (unprotect_page) {
        if (unprotect_system_page_first == UINT32_MAX) {
          unprotect_system_page_first = i;
        }
      } else {
        if (unprotect_system_page_first != UINT32_MAX) {
          rex::memory::Protect(protect_base + unprotect_system_page_first * system_page_size_,
                               (i - unprotect_system_page_first) * system_page_size_,
                               rex::memory::PageAccess::kReadWrite);
          unprotect_system_page_first = UINT32_MAX;
        }
      }
    }
    if (unprotect_system_page_first != UINT32_MAX) {
      rex::memory::Protect(protect_base + unprotect_system_page_first * system_page_size_,
                           (system_page_last + 1 - unprotect_system_page_first) * system_page_size_,
                           rex::memory::PageAccess::kReadWrite);
    }
  }

  for (uint32_t i = block_index_first; i <= block_index_last; ++i) {
    uint64_t mask = 0;
    if (i == block_index_first) {
      mask |= (uint64_t(1) << (system_page_first & 63)) - 1;
    }
    if (i == block_index_last && (system_page_last & 63) != 63) {
      mask |= ~((uint64_t(1) << ((system_page_last & 63) + 1)) - 1);
    }
    system_page_flags_[i].notify_on_invalidation &= mask;
  }

  return true;
}

std::unique_lock<std::recursive_mutex> PhysicalHeap::AcquireHostPageReconcileLock() const {
  auto lock = BaseHeap::AcquireHostPageReconcileLock();
  if (!lock.owns_lock() && parent_heap_ && parent_heap_->page_size() < memory_->system_page_size_) {
    lock = rex::thread::global_critical_region::AcquireDirect();
  }
  return lock;
}

bool PhysicalHeap::IsHostPageWriteWatched(uint32_t host_page_number) const {
  if (host_page_number >= system_page_count_) {
    return false;
  }
  return (system_page_flags_[host_page_number >> 6].notify_on_invalidation &
          (uint64_t(1) << (host_page_number & 63))) != 0;
}

uint32_t PhysicalHeap::GetPhysicalAddress(uint32_t address) const {
  assert_true(address >= heap_base_);
  address -= heap_base_;
  assert_true(address < heap_size_);
  if (heap_base_ >= 0xE0000000) {
    address += 0x1000;
  }
  return address;
}

}
