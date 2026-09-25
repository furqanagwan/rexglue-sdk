/**
 * @file        gpu_fixture.h
 * @brief       Headless PM4 fixture host for the Xenos GPU plugin (RG-GDK-006)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <rex/graphics/xenos.h>
#include <rex/runtime.h>
#include <rex/ui/d3d12/d3d12_provider.h>

namespace rex::testing {

// Drives the GPU plugin the way a title does, without a title: a Runtime with
// no image, the "xenos" plugin loaded through the plugin ABI, a primary ring
// buffer in guest physical memory and CP_RB_WPTR writes through the MMIO path.
// Packets are appended with Submit() and Flush() waits for a fence packet, so
// every result read back afterwards is ordered after all submitted work.
class GpuFixture {
 public:
  using CvarList = std::initializer_list<std::pair<const char*, const char*>>;

  // Returns nullptr and sets error when the plugin or the D3D12 device can't
  // be created, so callers can skip rather than fail. cvars are applied after
  // REXGLUE_GPU_FIXTURE_CVARS, so they can also set cvars the GPU plugin
  // registers and that are only read when the GPU starts.
  static std::unique_ptr<GpuFixture> Create(std::string* error, CvarList cvars = {});
  ~GpuFixture();

  memory::Memory* memory() const { return runtime_->memory(); }
  const ui::d3d12::D3D12Provider& provider() const;

  // Guest physical memory, returned as a physical address as the GPU sees it.
  uint32_t AllocPhysical(uint32_t size, uint32_t alignment = 0x1000);
  // Writes through the host view of physical memory, which has no access
  // watches: the GPU emulation's own view, not what a guest CPU write does.
  void WriteDwords(uint32_t address, const std::vector<uint32_t>& dwords);
  // Writes as the guest CPU would, through the guest virtual view the memory
  // was allocated in, so write watches on GPU-owned pages fire.
  void WriteDwordsAsGuest(uint32_t address, const std::vector<uint32_t>& dwords);
  uint32_t ReadDword(uint32_t address) const;

  // Appends packet dwords to the ring and moves the write pointer. Without a
  // read pointer write-back the ring must not wrap; with one, Submit waits on
  // the write-back for free space and wraps, as D3D does, and returns false if
  // the command processor stops making room.
  bool Submit(const std::vector<uint32_t>& dwords);
  // Arms the CP_RB_RPTR write-back at a guest physical address, with
  // RB_BLKSZ (log2 quadwords between updates) as the guest passes it.
  uint32_t EnableReadPointerWriteBack(uint32_t block_size_log2);
  uint32_t ring_dwords() const { return kRingDwords; }
  uint32_t write_index() const { return write_index_; }
  // Submits a fence write and waits for the command processor to reach it.
  bool Flush(std::chrono::milliseconds timeout = std::chrono::seconds(10));

  // Adapter, driver and capabilities that a fixture result must be recorded
  // with to be reproducible.
  std::string Metadata() const;

  // Packet builders. Memory addresses carry the endian swap mode in their low
  // two bits, as on the real command processor.
  static std::vector<uint32_t> MemWrite(uint32_t address, std::initializer_list<uint32_t> values,
                                        graphics::xenos::Endian endian);
  static std::vector<uint32_t> SetRegisters(uint32_t first_register,
                                            std::initializer_list<uint32_t> values);
  static std::vector<uint32_t> RegToMem(uint32_t reg, uint32_t address,
                                        graphics::xenos::Endian endian);
  static std::vector<uint32_t> IndirectBuffer(uint32_t address, uint32_t dword_count);

 private:
  GpuFixture() = default;

  static constexpr uint32_t kRingSizeLog2 = 13;  // 8 KB quadwords = 64 KB.
  static constexpr uint32_t kRingDwords = (uint32_t(1) << (kRingSizeLog2 + 3)) / 4;

  std::filesystem::path root_;
  std::unique_ptr<Runtime> runtime_;
  uint32_t ring_ = 0;
  uint32_t write_index_ = 0;
  uint32_t fence_address_ = 0;
  uint32_t fence_value_ = 0;
  uint32_t read_pointer_writeback_ = 0;
  // Guest virtual minus physical address for AllocPhysical allocations.
  uint32_t physical_to_virtual_ = 0;
};

}  // namespace rex::testing
