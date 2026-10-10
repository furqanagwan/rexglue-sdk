#pragma once
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

#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include <rex/memory/utils.h>
#include <rex/ppc/func.h>
#include <rex/system/mmio_handler.h>
#include <rex/thread/mutex.h>

namespace rex::stream {
class ByteStream;
}

namespace rex::memory::detail {

constexpr u32 PhysicalHostOffset(u32 guest_addr) noexcept {
  return (guest_addr >= 0xE0000000u) ? 0x1000u : 0u;
}

}

namespace rex::memory {

template <typename T = u8*>
inline T GuestPtr(u8* base, u32 guest_address) noexcept {
  return reinterpret_cast<T>(base + guest_address + detail::PhysicalHostOffset(guest_address));
}

class Memory;

enum SystemHeapFlag : uint32_t {
  kSystemHeapVirtual = 1 << 0,
  kSystemHeapPhysical = 1 << 1,

  kSystemHeapDefault = kSystemHeapVirtual,
};

enum class HeapType : uint8_t {
  kGuestVirtual,
  kGuestXex,
  kGuestPhysical,
  kHostPhysical,
};

enum MemoryAllocationFlag : uint32_t {
  kMemoryAllocationReserve = 1 << 0,
  kMemoryAllocationCommit = 1 << 1,
};

enum MemoryProtectFlag : uint32_t {
  kMemoryProtectRead = 1 << 0,
  kMemoryProtectWrite = 1 << 1,
  kMemoryProtectNoCache = 1 << 2,
  kMemoryProtectWriteCombine = 1 << 3,

  kMemoryProtectNoAccess = 0,
};

struct HeapAllocationInfo {
  uint32_t base_address;

  uint32_t allocation_base;

  uint32_t allocation_protect;

  uint32_t allocation_size;

  uint32_t region_size;

  uint32_t state;

  uint32_t protect;
};

union PageEntry {
  uint64_t qword;
  struct {
    uint32_t base_address : 20;

    uint32_t region_page_count : 20;

    uint32_t allocation_protect : 4;

    uint32_t current_protect : 4;

    uint32_t state : 2;
    uint32_t reserved : 14;
  };
};

class BaseHeap {
 public:
  virtual ~BaseHeap();

  uint32_t heap_base() const { return heap_base_; }

  uint32_t heap_size() const { return heap_size_; }

  uint32_t page_size() const { return page_size_; }

  HeapType heap_type() const { return heap_type_; }

  uint32_t host_address_offset() const { return host_address_offset_; }

  template <typename T = uint8_t*>
  inline T TranslateRelative(size_t relative_address) const {
    return reinterpret_cast<T>(membase_ + heap_base_ + host_address_offset_ + relative_address);
  }

  virtual void Dispose();

  void DumpMap();

  uint32_t GetTotalPageCount();
  uint32_t GetUnreservedPageCount();

  uint32_t total_page_count() const { return uint32_t(page_table_.size()); }
  uint32_t unreserved_page_count() const { return unreserved_page_count_; }
  uint32_t reserved_page_count() const { return total_page_count() - unreserved_page_count(); }

  virtual bool Alloc(uint32_t size, uint32_t alignment, uint32_t allocation_type, uint32_t protect,
                     bool top_down, uint32_t* out_address);

  virtual bool AllocFixed(uint32_t base_address, uint32_t size, uint32_t alignment,
                          uint32_t allocation_type, uint32_t protect);

  virtual bool AllocRange(uint32_t low_address, uint32_t high_address, uint32_t size,
                          uint32_t alignment, uint32_t allocation_type, uint32_t protect,
                          bool top_down, uint32_t* out_address);

  virtual bool AllocSystemHeap(uint32_t size, uint32_t alignment, uint32_t allocation_type,
                               uint32_t protect, bool top_down, uint32_t* out_address);

  virtual bool Decommit(uint32_t address, uint32_t size);

  virtual bool Release(uint32_t address, uint32_t* out_region_size = nullptr);

  virtual bool Protect(uint32_t address, uint32_t size, uint32_t protect,
                       uint32_t* old_protect = nullptr);

  bool QueryRegionInfo(uint32_t base_address, HeapAllocationInfo* out_info);

  bool QuerySize(uint32_t address, uint32_t* out_size);

  bool QueryBaseAndSize(uint32_t* in_out_address, uint32_t* out_size);

  bool QueryProtect(uint32_t address, uint32_t* out_protect);

  rex::memory::PageAccess QueryRangeAccess(uint32_t low_address, uint32_t high_address);

  bool Save(stream::ByteStream* stream);
  bool Restore(stream::ByteStream* stream);

  void Reset();

 protected:
  BaseHeap();

  bool SyncHostPageAccess(uint32_t start_page_number, uint32_t end_page_number);

  virtual std::unique_lock<std::recursive_mutex> AcquireHostPageReconcileLock() const;

  virtual bool IsHostPageWriteWatched(uint32_t host_page_number) const { return false; }

  void Initialize(memory::Memory* memory, uint8_t* membase, HeapType heap_type, uint32_t heap_base,
                  uint32_t heap_size, uint32_t page_size, uint32_t host_address_offset = 0);

  memory::Memory* memory_;
  uint8_t* membase_;
  HeapType heap_type_;
  uint32_t heap_base_;
  uint32_t heap_size_;
  uint32_t page_size_;
  uint32_t page_size_shift_ = 0;
  uint32_t host_address_offset_;
  uint32_t unreserved_page_count_ = 0;
  rex::thread::global_critical_region global_critical_region_;
  std::recursive_mutex heap_mutex_;
  std::vector<PageEntry> page_table_;
};

class VirtualHeap : public BaseHeap {
 public:
  VirtualHeap();
  ~VirtualHeap() override;

  void Initialize(memory::Memory* memory, uint8_t* membase, HeapType heap_type, uint32_t heap_base,
                  uint32_t heap_size, uint32_t page_size);
};

class PhysicalHeap : public BaseHeap {
 public:
  PhysicalHeap();
  ~PhysicalHeap() override;

  void Initialize(memory::Memory* memory, uint8_t* membase, HeapType heap_type, uint32_t heap_base,
                  uint32_t heap_size, uint32_t page_size, VirtualHeap* parent_heap);

  bool Alloc(uint32_t size, uint32_t alignment, uint32_t allocation_type, uint32_t protect,
             bool top_down, uint32_t* out_address) override;
  bool AllocFixed(uint32_t base_address, uint32_t size, uint32_t alignment,
                  uint32_t allocation_type, uint32_t protect) override;
  bool AllocRange(uint32_t low_address, uint32_t high_address, uint32_t size, uint32_t alignment,
                  uint32_t allocation_type, uint32_t protect, bool top_down,
                  uint32_t* out_address) override;
  bool AllocSystemHeap(uint32_t size, uint32_t alignment, uint32_t allocation_type,
                       uint32_t protect, bool top_down, uint32_t* out_address) override;
  bool Decommit(uint32_t address, uint32_t size) override;
  bool Release(uint32_t base_address, uint32_t* out_region_size = nullptr) override;
  bool Protect(uint32_t address, uint32_t size, uint32_t protect,
               uint32_t* old_protect = nullptr) override;

  void EnableAccessCallbacks(uint32_t physical_address, uint32_t length,
                             bool enable_invalidation_notifications, bool enable_data_providers);

  bool TriggerCallbacks(std::unique_lock<std::recursive_mutex> global_lock_locked_once,
                        uint32_t virtual_address, uint32_t length, bool is_write,
                        bool unwatch_exact_range, bool unprotect = true);

  uint32_t GetPhysicalAddress(uint32_t address) const;

 protected:
  bool IsHostPageWriteWatched(uint32_t host_page_number) const override;

  std::unique_lock<std::recursive_mutex> AcquireHostPageReconcileLock() const override;

  VirtualHeap* parent_heap_;

  uint32_t system_page_size_;
  uint32_t system_page_count_;

  struct SystemPageFlagsBlock {
    uint64_t notify_on_invalidation;
  };

  std::vector<SystemPageFlagsBlock> system_page_flags_;
};

class Memory {
 public:
  Memory();
  ~Memory();

  bool Initialize();

  void Reset();

  const std::filesystem::path& file_name() const { return file_name_; }

  inline uint8_t* virtual_membase() const { return virtual_membase_; }

  template <typename T = uint8_t*>
  inline T TranslateVirtual(uint32_t guest_address) const {
    uint8_t* host_address = virtual_membase_ + guest_address;
    const auto heap = LookupHeap(guest_address);
    if (heap) {
      host_address += heap->host_address_offset();
    }
    return reinterpret_cast<T>(host_address);
  }

  inline uint8_t* physical_membase() const { return physical_membase_; }

  template <typename T = uint8_t*>
  inline T TranslatePhysical(uint32_t guest_address) const {
    return reinterpret_cast<T>(physical_membase_ + (guest_address & 0x1FFFFFFF));
  }

  uint32_t HostToGuestVirtual(const void* host_address) const;

  uint32_t GetPhysicalAddress(uint32_t address) const;

  void Zero(uint32_t address, uint32_t size);

  void Fill(uint32_t address, uint32_t size, uint8_t value);

  void Copy(uint32_t dest, uint32_t src, uint32_t size);

  uint32_t SearchAligned(uint32_t start, uint32_t end, const uint32_t* values, size_t value_count);

  bool AddVirtualMappedRange(uint32_t virtual_address, uint32_t mask, uint32_t size, void* context,
                             runtime::MMIOReadCallback read_callback,
                             runtime::MMIOWriteCallback write_callback);

  runtime::MMIORange* LookupVirtualMappedRange(uint32_t virtual_address);

  typedef std::pair<uint32_t, uint32_t> (*PhysicalMemoryInvalidationCallback)(
      void* context_ptr, uint32_t physical_address_start, uint32_t length, bool exact_range);

  void* RegisterPhysicalMemoryInvalidationCallback(PhysicalMemoryInvalidationCallback callback,
                                                   void* callback_context);

  void UnregisterPhysicalMemoryInvalidationCallback(void* callback_handle);

  void EnablePhysicalMemoryAccessCallbacks(uint32_t physical_address, uint32_t length,
                                           bool enable_invalidation_notifications,
                                           bool enable_data_providers);

  bool TriggerPhysicalMemoryCallbacks(
      std::unique_lock<std::recursive_mutex> global_lock_locked_once, uint32_t virtual_address,
      uint32_t length, bool is_write, bool unwatch_exact_range, bool unprotect = true);

  uint32_t SystemHeapAlloc(uint32_t size, uint32_t alignment = 0x20,
                           uint32_t system_heap_flags = kSystemHeapDefault);

  void SystemHeapFree(uint32_t address, uint32_t* out_region_size = nullptr);

  const BaseHeap* LookupHeap(uint32_t address) const;

  inline BaseHeap* LookupHeap(uint32_t address) {
    return const_cast<BaseHeap*>(const_cast<const memory::Memory*>(this)->LookupHeap(address));
  }

  BaseHeap* LookupHeapByType(bool physical, uint32_t page_size);

  void GetHeapsPageStatsSummary(const BaseHeap* const* provided_heaps, size_t heaps_count,
                                uint32_t& unreserved_pages, uint32_t& reserved_pages,
                                uint32_t& used_pages, uint32_t& reserved_bytes);

  VirtualHeap* GetPhysicalHeap();

  void DumpMap();

  bool Save(stream::ByteStream* stream);
  bool Restore(stream::ByteStream* stream);

  bool InitializeFunctionTable(uint32_t code_base, uint32_t code_size, uint32_t table_base);
  bool DestroyFunctionTable(uint32_t code_base);

  bool SetFunction(uint32_t guest_address, PPCFunc* host_function);
  bool HasAnyFunctionTable() const;

 private:
  int MapViews(uint8_t* mapping_base);
  void UnmapViews();

  static uint32_t HostToGuestVirtualThunk(const void* context, const void* host_address);

  bool AccessViolationCallback(std::unique_lock<std::recursive_mutex> global_lock_locked_once,
                               void* host_address, bool is_write);
  static bool AccessViolationCallbackThunk(
      std::unique_lock<std::recursive_mutex> global_lock_locked_once, void* context,
      void* host_address, bool is_write);

  std::filesystem::path file_name_;
  uint32_t system_page_size_ = 0;
  uint32_t system_allocation_granularity_ = 0;
  uint8_t* virtual_membase_ = nullptr;
  uint8_t* physical_membase_ = nullptr;

  struct FunctionTableEntry {
    uint32_t table_base;
    uint32_t code_base;
    uint32_t code_size;
    uint32_t thunk_reserve;
  };
  std::vector<FunctionTableEntry> function_tables_;
  mutable std::mutex function_tables_mutex_;

  rex::memory::FileMappingHandle mapping_ = rex::memory::kFileMappingHandleInvalid;
  uint8_t* mapping_base_ = nullptr;
  union {
    struct {
      uint8_t* v00000000;
      uint8_t* v40000000;
      uint8_t* v7F000000;
      uint8_t* v80000000;
      uint8_t* v90000000;
      uint8_t* vA0000000;
      uint8_t* vC0000000;
      uint8_t* vE0000000;
      uint8_t* physical;
    };
    uint8_t* all_views[9];
  } views_ = {{0, 0, 0, 0, 0, 0, 0, 0, 0}};

  std::unique_ptr<runtime::MMIOHandler> mmio_handler_;

  struct {
    VirtualHeap v00000000;
    VirtualHeap v40000000;
    VirtualHeap v80000000;
    VirtualHeap v90000000;

    VirtualHeap physical;
    PhysicalHeap vA0000000;
    PhysicalHeap vC0000000;
    PhysicalHeap vE0000000;
  } heaps_;

  friend class BaseHeap;

  friend class PhysicalHeap;
  rex::thread::global_critical_region global_critical_region_;
  std::vector<std::pair<PhysicalMemoryInvalidationCallback, void*>*>
      physical_memory_invalidation_callbacks_;
};

}
