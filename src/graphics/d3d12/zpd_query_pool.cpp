/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2026 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    ReXGlue, 2026 - Ported from xenia-canary 3d233a5b2 (PR #1218):
 *              native queries, and the ROV counter slots (RG-GDK-010a)
 */

#include <rex/graphics/d3d12/zpd_query_pool.h>

#include <algorithm>

#include <rex/assert.h>
#include <rex/graphics/d3d12/deferred_command_list.h>
#include <rex/logging.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/d3d12/d3d12_util.h>

namespace rex::graphics::d3d12 {

namespace {

bool CreateCounterResources(const ui::d3d12::D3D12Provider& provider, uint32_t capacity,
                            Microsoft::WRL::ComPtr<ID3D12Resource>& counter,
                            Microsoft::WRL::ComPtr<ID3D12Resource>& zero,
                            Microsoft::WRL::ComPtr<ID3D12Resource>& readback,
                            uint32_t*& readback_mapping) {
  ID3D12Device* device = provider.GetDevice();
  const uint64_t size = uint64_t(capacity) * XenosZPDReport::kCounterSizeBytes;
  D3D12_RESOURCE_DESC desc;
  ui::d3d12::util::FillBufferResourceDesc(desc, size, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
  if (FAILED(device->CreateCommittedResource(
          &ui::d3d12::util::kHeapPropertiesDefault, provider.GetHeapFlagCreateNotZeroed(), &desc,
          D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&counter)))) {
    return false;
  }

  ui::d3d12::util::FillBufferResourceDesc(desc, XenosZPDReport::kCounterSizeBytes,
                                          D3D12_RESOURCE_FLAG_NONE);
  if (FAILED(device->CreateCommittedResource(
          &ui::d3d12::util::kHeapPropertiesDefault, D3D12_HEAP_FLAG_NONE, &desc,
          D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&zero)))) {
    return false;
  }
  ui::d3d12::util::FillBufferResourceDesc(desc, size, D3D12_RESOURCE_FLAG_NONE);
  if (FAILED(device->CreateCommittedResource(
          &ui::d3d12::util::kHeapPropertiesReadback, provider.GetHeapFlagCreateNotZeroed(), &desc,
          D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback)))) {
    return false;
  }
  D3D12_RANGE read_range = {0, SIZE_T(size)};
  void* mapping = nullptr;
  if (FAILED(readback->Map(0, &read_range, &mapping))) {
    return false;
  }
  readback_mapping = static_cast<uint32_t*>(mapping);
  return true;
}

}

bool D3D12ZPDQueryPool::EnsureInitialized(const ui::d3d12::D3D12Provider& provider,
                                          uint32_t requested_capacity, bool with_counter) {
  if (initialized()) {
    if (!with_counter || counter_initialized()) {
      return true;
    }
    if (!CreateCounterResources(provider, capacity_, counter_buffer_, counter_zero_buffer_,
                                counter_readback_buffer_, counter_readback_mapping_)) {
      REXGPU_WARN("D3D12ZPDQueryPool: Failed to create the ROV counter slots");
      counter_buffer_.Reset();
      counter_zero_buffer_.Reset();
      counter_readback_buffer_.Reset();
      counter_readback_mapping_ = nullptr;
      return false;
    }
    return true;
  }

  ID3D12Device* device = provider.GetDevice();

  D3D12_QUERY_HEAP_DESC heap_desc = {};
  heap_desc.Type = D3D12_QUERY_HEAP_TYPE_OCCLUSION;
  heap_desc.Count = requested_capacity;
  heap_desc.NodeMask = 0;
  if (FAILED(device->CreateQueryHeap(&heap_desc, IID_PPV_ARGS(&query_heap_)))) {
    REXGPU_WARN(
        "D3D12ZPDQueryPool: Failed to create the ZPD query heap, falling back to fake sample "
        "counts");
    return false;
  }

  D3D12_RESOURCE_DESC buffer_desc;
  ui::d3d12::util::FillBufferResourceDesc(buffer_desc, sizeof(uint64_t) * requested_capacity,
                                          D3D12_RESOURCE_FLAG_NONE);
  if (FAILED(device->CreateCommittedResource(&ui::d3d12::util::kHeapPropertiesReadback,
                                             provider.GetHeapFlagCreateNotZeroed(), &buffer_desc,
                                             D3D12_RESOURCE_STATE_COPY_DEST, nullptr,
                                             IID_PPV_ARGS(&readback_buffer_)))) {
    REXGPU_WARN(
        "D3D12ZPDQueryPool: Failed to allocate the ZPD query readback buffer, falling back to "
        "fake sample counts");
    Shutdown();
    return false;
  }

  D3D12_RANGE read_range = {};
  read_range.Begin = 0;
  read_range.End = sizeof(uint64_t) * requested_capacity;
  void* mapping = nullptr;
  if (FAILED(readback_buffer_->Map(0, &read_range, &mapping))) {
    REXGPU_WARN(
        "D3D12ZPDQueryPool: Failed to map the ZPD query readback buffer, falling back to fake "
        "sample counts");
    Shutdown();
    return false;
  }

  readback_mapping_ = reinterpret_cast<uint64_t*>(mapping);
  capacity_ = requested_capacity;

  resolve_batch_indices_.clear();
  resolve_batch_ranges_.clear();

  free_indices_.clear();
  free_indices_.reserve(requested_capacity);
  for (uint32_t i = requested_capacity; i > 0; --i) {
    free_indices_.push_back(i - 1);
  }
  index_generations_.assign(requested_capacity, 0);

  if (with_counter &&
      !CreateCounterResources(provider, requested_capacity, counter_buffer_, counter_zero_buffer_,
                              counter_readback_buffer_, counter_readback_mapping_)) {
    REXGPU_WARN(
        "D3D12ZPDQueryPool: Failed to create the ROV counter slots, falling back to fake sample "
        "counts");
    Shutdown();
    return false;
  }
  return true;
}

void D3D12ZPDQueryPool::Shutdown() {
  resolve_batch_indices_.clear();
  counter_resolve_batch_indices_.clear();
  resolve_batch_ranges_.clear();
  free_indices_.clear();
  index_generations_.clear();

  capacity_ = 0;

  if (readback_mapping_ && readback_buffer_) {
    D3D12_RANGE written_range = {0, 0};
    readback_buffer_->Unmap(0, &written_range);
  }

  readback_mapping_ = nullptr;
  readback_buffer_.Reset();
  query_heap_.Reset();

  if (counter_readback_mapping_ && counter_readback_buffer_) {
    D3D12_RANGE written_range = {0, 0};
    counter_readback_buffer_->Unmap(0, &written_range);
  }
  counter_readback_mapping_ = nullptr;
  counter_readback_buffer_.Reset();
  counter_zero_buffer_.Reset();
  counter_buffer_.Reset();
  counter_buffer_state_ = D3D12_RESOURCE_STATE_COMMON;
  counter_buffer_state_submission_ = UINT64_MAX;
}

bool D3D12ZPDQueryPool::AcquireQueryIndex(uint32_t& query_index, uint32_t& query_generation) {
  if (free_indices_.empty()) {
    query_index = UINT32_MAX;
    query_generation = 0;
    return false;
  }

  query_index = free_indices_.back();
  free_indices_.pop_back();

  assert_true(query_index < index_generations_.size());

  query_generation = ++index_generations_[query_index];
  return true;
}

void D3D12ZPDQueryPool::ReleaseQueryIndex(uint32_t query_index, uint32_t query_generation) {
  if (!GenerationMatches(query_index, query_generation)) {
    return;
  }

  ++index_generations_[query_index];
  free_indices_.push_back(query_index);
}

bool D3D12ZPDQueryPool::GenerationMatches(uint32_t query_index, uint32_t query_generation) const {
  return query_index < index_generations_.size() &&
         index_generations_[query_index] == query_generation;
}

void D3D12ZPDQueryPool::BeginQuery(DeferredCommandList& deferred_command_list,
                                   uint32_t query_index) const {
  assert_true(query_heap_ && query_index < capacity_);
  deferred_command_list.D3DBeginQuery(query_heap_.Get(), D3D12_QUERY_TYPE_OCCLUSION, query_index);
}

void D3D12ZPDQueryPool::EndQuery(DeferredCommandList& deferred_command_list,
                                 uint32_t query_index) const {
  assert_true(query_heap_ && query_index < capacity_);
  deferred_command_list.D3DEndQuery(query_heap_.Get(), D3D12_QUERY_TYPE_OCCLUSION, query_index);
}

void D3D12ZPDQueryPool::QueueQueryResolve(uint32_t query_index, bool counter) {
  assert_true(query_index < capacity_);
  (counter ? counter_resolve_batch_indices_ : resolve_batch_indices_).push_back(query_index);
}

void D3D12ZPDQueryPool::WriteCounterRawUAVDescriptor(ID3D12Device* device,
                                                     D3D12_CPU_DESCRIPTOR_HANDLE handle) const {
  if (counter_buffer_) {
    ui::d3d12::util::CreateBufferRawUAV(device, handle, counter_buffer_.Get(),
                                        uint32_t(capacity_ * XenosZPDReport::kCounterSizeBytes));
  } else {
    ui::d3d12::util::CreateBufferRawUAV(device, handle, nullptr, 0);
  }
}

void D3D12ZPDQueryPool::TransitionCounterBuffer(DeferredCommandList& deferred_command_list,
                                                uint64_t submission,
                                                D3D12_RESOURCE_STATES new_state) {
  if (submission != counter_buffer_state_submission_) {
    counter_buffer_state_ = D3D12_RESOURCE_STATE_COMMON;
    counter_buffer_state_submission_ = submission;
  }
  if (counter_buffer_state_ == new_state) {
    return;
  }
  D3D12_RESOURCE_BARRIER barrier = {};
  barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Transition.pResource = counter_buffer_.Get();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = counter_buffer_state_;
  barrier.Transition.StateAfter = new_state;
  deferred_command_list.D3DResourceBarrier(1, &barrier);
  counter_buffer_state_ = new_state;
}

void D3D12ZPDQueryPool::ClearCounter(DeferredCommandList& deferred_command_list,
                                     uint64_t submission, uint32_t query_index) {
  assert_true(counter_initialized() && query_index < capacity_);

  TransitionCounterBuffer(deferred_command_list, submission, D3D12_RESOURCE_STATE_COPY_DEST);
  deferred_command_list.D3DCopyBufferRegion(
      counter_buffer_.Get(), uint64_t(query_index) * XenosZPDReport::kCounterSizeBytes,
      counter_zero_buffer_.Get(), 0, XenosZPDReport::kCounterSizeBytes);

  TransitionCounterBuffer(deferred_command_list, submission, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
}

void D3D12ZPDQueryPool::ResolveQueryTo(DeferredCommandList& deferred_command_list,
                                       uint32_t query_index, ID3D12Resource* dest,
                                       uint64_t dest_offset) const {
  assert_true(initialized() && query_index < capacity_);
  deferred_command_list.D3DResolveQueryData(query_heap_.Get(), D3D12_QUERY_TYPE_OCCLUSION,
                                            query_index, 1, dest, dest_offset);
}

void D3D12ZPDQueryPool::CopyCounterZPassTo(DeferredCommandList& deferred_command_list,
                                           uint64_t submission, uint32_t query_index,
                                           ID3D12Resource* dest, uint64_t dest_offset) {
  assert_true(counter_initialized() && query_index < capacity_);

  TransitionCounterBuffer(deferred_command_list, submission, D3D12_RESOURCE_STATE_COPY_SOURCE);
  deferred_command_list.D3DCopyBufferRegion(
      dest, dest_offset, counter_buffer_.Get(),
      uint64_t(query_index) * XenosZPDReport::kCounterSizeBytes +
          XenosZPDReport::kZPass * sizeof(uint32_t),
      sizeof(uint32_t));
  TransitionCounterBuffer(deferred_command_list, submission, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
}

void D3D12ZPDQueryPool::FlushResolveBatch(DeferredCommandList& deferred_command_list,
                                          uint64_t submission, bool submission_open) {
  if (!submission_open || !has_pending_resolve_batch()) {
    return;
  }
  assert_true(initialized());

  auto build_ranges = [this](std::vector<uint32_t>& indices) {
    std::sort(indices.begin(), indices.end());
    resolve_batch_ranges_.clear();
    uint32_t range_start = 0;
    uint32_t range_count = 0;
    for (uint32_t index : indices) {
      if (range_count == 0) {
        range_start = index;
        range_count = 1;
        continue;
      }
      if (index == range_start + range_count) {
        ++range_count;
        continue;
      }
      resolve_batch_ranges_.push_back({range_start, range_count});
      range_start = index;
      range_count = 1;
    }
    if (range_count != 0) {
      resolve_batch_ranges_.push_back({range_start, range_count});
    }
    indices.clear();
  };

  if (!resolve_batch_indices_.empty()) {
    build_ranges(resolve_batch_indices_);
    for (const ResolveRange& range : resolve_batch_ranges_) {
      deferred_command_list.D3DResolveQueryData(query_heap_.Get(), D3D12_QUERY_TYPE_OCCLUSION,
                                                range.start, range.count, readback_buffer_.Get(),
                                                range.start * sizeof(uint64_t));
    }
  }

  if (counter_resolve_batch_indices_.empty()) {
    return;
  }
  assert_true(counter_initialized());

  TransitionCounterBuffer(deferred_command_list, submission, D3D12_RESOURCE_STATE_COPY_SOURCE);
  build_ranges(counter_resolve_batch_indices_);
  for (const ResolveRange& range : resolve_batch_ranges_) {
    uint64_t offset = uint64_t(range.start) * XenosZPDReport::kCounterSizeBytes;
    uint64_t size = uint64_t(range.count) * XenosZPDReport::kCounterSizeBytes;
    deferred_command_list.D3DCopyBufferRegion(counter_readback_buffer_.Get(), offset,
                                              counter_buffer_.Get(), offset, size);
  }
  TransitionCounterBuffer(deferred_command_list, submission, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
}

XenosZPDReport D3D12ZPDQueryPool::GetHybridReadbackValue(uint32_t query_index) const {
  assert_true(query_index < capacity_);
  assert_not_null(readback_mapping_);
  assert_not_null(counter_readback_mapping_);
  return XenosZPDReport::FromNativeQueryAndTotal(
      readback_mapping_[query_index],
      counter_readback_mapping_[query_index * XenosZPDReport::kCount + XenosZPDReport::kTotal]);
}

XenosZPDReport D3D12ZPDQueryPool::GetQueryReadbackValue(uint32_t query_index, bool counter) const {
  assert_true(query_index < capacity_);
  if (counter) {
    assert_not_null(counter_readback_mapping_);
    return XenosZPDReport::FromCounterSlot(counter_readback_mapping_ +
                                           query_index * XenosZPDReport::kCount);
  }
  assert_not_null(readback_mapping_);
  return XenosZPDReport::FromNativeQuery(readback_mapping_[query_index]);
}

}
