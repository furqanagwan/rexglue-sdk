/**
 * @file        system/function_dispatcher.h
 * @brief       Guest function dispatch coordinator for recompiled code
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 *
 * @remarks     Derived from Xenia's runtime::Processor (Ben Vanik, 2020).
 *              Stripped of emulation-era dead code and renamed to reflect its
 *              role as a function dispatch table rather than a CPU emulator.
 */

#pragma once

#include <filesystem>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/memory.h>
#include <rex/memory/mapped_memory.h>
#include <rex/ppc/func.h>
#include <rex/system/export_resolver.h>
#include <rex/system/thread_state.h>
#include <rex/thread/mutex.h>

namespace rex::runtime {

class ExportResolver;
class ThreadState;

class IModuleRegistrar {
 public:
  virtual bool SetFunction(uint32_t guest_address, ::PPCFunc* func) = 0;

 protected:
  ~IModuleRegistrar() = default;
};

class FunctionDispatcher : public IModuleRegistrar {
 public:
  using RegisterFn = void (*)(IModuleRegistrar*);

  FunctionDispatcher(memory::Memory* memory, ExportResolver* export_resolver);
  ~FunctionDispatcher();

  memory::Memory* memory() const { return memory_; }
  ExportResolver* export_resolver() const { return export_resolver_; }

  uint64_t Execute(ThreadState* thread_state, uint32_t address, uint64_t args[], size_t arg_count);
  uint64_t ExecuteInterrupt(ThreadState* thread_state, uint32_t address, uint64_t args[],
                            size_t arg_count);

  uint64_t ExecuteTrap(ThreadState* thread_state, uint32_t address, uint64_t args[],
                       size_t arg_count);

  static constexpr uint32_t kThunkReserveSize = 0x10000;

  bool InitializeFunctionTable(uint32_t code_base, uint32_t code_size, uint32_t image_base,
                               uint32_t image_size, bool is_entrypoint = false,
                               uint32_t table_base = 0);
  bool SetFunction(uint32_t guest_address, ::PPCFunc* func) override;
  ::PPCFunc* GetFunction(uint32_t guest_address);

  uint32_t FindGuestFunctionByHostPc(uint64_t host_pc, uint64_t* host_entry = nullptr) const;
  bool HasAnyFunctionTable() const { return !module_tables_.empty(); }

  uint32_t AllocateThunk(::PPCFunc* func, uint32_t caller_address);

  uint32_t FindCallerModuleBase(uint32_t guest_address);

  void RegisterModule(const std::string& module_id, uint32_t code_base, RegisterFn register_func);

  std::optional<std::pair<uint32_t, uint32_t>> UnregisterModule(const std::string& module_id);

 private:
  bool Execute(ThreadState* thread_state, uint32_t address);

  struct ModuleTableInfo {
    uint32_t code_base;
    uint32_t code_size;
    uint32_t image_base;
    uint32_t image_size;
    uint32_t table_base;
    uint32_t next_thunk_address;
    uint32_t thunk_limit;
  };

  ModuleTableInfo* FindModuleByAddress(uint32_t guest_address);

  memory::Memory* memory_ = nullptr;
  ExportResolver* export_resolver_ = nullptr;

  rex::thread::global_critical_region global_critical_region_;

  std::unordered_map<uint32_t, ::PPCFunc*> function_table_;

  std::vector<ModuleTableInfo> module_tables_;

  uint32_t entrypoint_code_base_ = 0;

  bool recording_ = false;
  std::vector<uint32_t> recording_addresses_;

  struct ModuleRegistration {
    uint32_t code_base;
    std::vector<uint32_t> addresses;
  };

  std::unordered_map<std::string, ModuleRegistration> module_addresses_;

  mutable std::recursive_mutex dispatch_mutex_;
};

bool AppendIndirectTrace(const std::filesystem::path& path, uint32_t guest_address);

}
