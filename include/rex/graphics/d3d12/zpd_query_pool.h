/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-canary 3d233a5b2 (PR #1218),
 *              native query path only
 */

#pragma once

#include <cstdint>
#include <vector>

#include <rex/graphics/xenos_zpd_report.h>
#include <rex/ui/d3d12/d3d12_api.h>

namespace rex::ui::d3d12 {
class D3D12Provider;
}  // namespace rex::ui::d3d12

namespace rex::graphics::d3d12 {

class DeferredCommandList;

// D3D12 occlusion query pool for ZPD reports. Queries live in ID3D12QueryHeap,
// results are copied to a persistent readback buffer via ResolveQueryData.
//
// D3D12 requires BeginQuery and EndQuery to be recorded in the same command
// list, so segments split at EndSubmission.
//
// FlushResolveBatch coalesces pending indices into contiguous ranges to cut
// down on ResolveQueryData call count.
//
// ROV queries (RG-GDK-010a) don't use D3D12 occlusion queries: the ROV pixel
// shaders add their depth/stencil outcomes to a counter slot of four uint32
// lanes (XenosZPDReport::Counter) with UAV atomics. ClearCounter zeroes the
// slot when the query opens; a counter resolve copies it to a readback buffer.
class D3D12ZPDQueryPool {
 public:
  D3D12ZPDQueryPool() = default;
  D3D12ZPDQueryPool(const D3D12ZPDQueryPool&) = delete;
  D3D12ZPDQueryPool& operator=(const D3D12ZPDQueryPool&) = delete;
  ~D3D12ZPDQueryPool() { Shutdown(); }

  // `with_counter` also creates the ROV counter slots.
  bool EnsureInitialized(const ui::d3d12::D3D12Provider& provider, uint32_t requested_capacity,
                         bool with_counter = false);
  void Shutdown();

  bool initialized() const {
    return query_heap_ && readback_buffer_ && readback_mapping_ != nullptr && capacity_ != 0;
  }

  uint32_t capacity() const { return capacity_; }
  uint32_t free_index_count() const { return uint32_t(free_indices_.size()); }
  bool has_free_indices() const { return !free_indices_.empty(); }
  bool has_pending_resolve_batch() const {
    return !resolve_batch_indices_.empty() || !counter_resolve_batch_indices_.empty();
  }

  bool counter_initialized() const {
    return counter_buffer_ && counter_zero_buffer_ && counter_readback_mapping_ != nullptr &&
           capacity_ != 0;
  }
  ID3D12Resource* counter_buffer() const { return counter_buffer_.Get(); }
  // A raw UAV of the counter slots, or a null raw UAV without them.
  void WriteCounterRawUAVDescriptor(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE handle) const;

  bool AcquireQueryIndex(uint32_t& query_index, uint32_t& query_generation);
  void ReleaseQueryIndex(uint32_t query_index, uint32_t query_generation);
  bool GenerationMatches(uint32_t query_index, uint32_t query_generation) const;

  void BeginQuery(DeferredCommandList& deferred_command_list, uint32_t query_index) const;
  void EndQuery(DeferredCommandList& deferred_command_list, uint32_t query_index) const;
  // `counter`: resolve the query's counter slot instead of its occlusion query.
  void QueueQueryResolve(uint32_t query_index, bool counter = false);
  // Zeroes the slot, then leaves the buffer ready for the shaders' atomics.
  void ClearCounter(DeferredCommandList& deferred_command_list, uint64_t submission,
                    uint32_t query_index);

  void FlushResolveBatch(DeferredCommandList& deferred_command_list, uint64_t submission,
                         bool submission_open);

  XenosZPDReport GetQueryReadbackValue(uint32_t query_index, bool counter = false) const;
  // A hybrid query resolves both the native query and the counter slot.
  XenosZPDReport GetHybridReadbackValue(uint32_t query_index) const;

 private:
  struct ResolveRange {
    uint32_t start;
    uint32_t count;
  };

  // Buffers decay to COMMON when a submission finishes, so the tracked state
  // starts over for each submission.
  void TransitionCounterBuffer(DeferredCommandList& deferred_command_list, uint64_t submission,
                               D3D12_RESOURCE_STATES new_state);

  Microsoft::WRL::ComPtr<ID3D12QueryHeap> query_heap_;

  // Persistently mapped. Results readable once the fence signals.
  Microsoft::WRL::ComPtr<ID3D12Resource> readback_buffer_;
  uint64_t* readback_mapping_ = nullptr;

  Microsoft::WRL::ComPtr<ID3D12Resource> counter_buffer_;
  // One zeroed slot, the source of ClearCounter's copy. (The deferred command
  // list has no WriteBufferImmediate.)
  Microsoft::WRL::ComPtr<ID3D12Resource> counter_zero_buffer_;
  Microsoft::WRL::ComPtr<ID3D12Resource> counter_readback_buffer_;
  uint32_t* counter_readback_mapping_ = nullptr;
  D3D12_RESOURCE_STATES counter_buffer_state_ = D3D12_RESOURCE_STATE_COMMON;
  uint64_t counter_buffer_state_submission_ = UINT64_MAX;

  uint32_t capacity_ = 0;
  std::vector<uint32_t> free_indices_;

  // Bumped on each acquire so stale readbacks from a recycled slot get dropped.
  std::vector<uint32_t> index_generations_;

  std::vector<uint32_t> resolve_batch_indices_;
  std::vector<uint32_t> counter_resolve_batch_indices_;
  // Reusable scratch for coalesced contiguous ranges during flush.
  std::vector<ResolveRange> resolve_batch_ranges_;
};

}  // namespace rex::graphics::d3d12
