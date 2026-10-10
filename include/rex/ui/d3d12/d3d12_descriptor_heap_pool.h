/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstdint>

#include <rex/ui/d3d12/d3d12_provider.h>

namespace rex::ui::d3d12 {

class D3D12DescriptorHeapPool {
 public:
  static constexpr uint64_t kHeapIndexInvalid = UINT64_MAX;

  D3D12DescriptorHeapPool(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type,
                          uint32_t page_size);
  ~D3D12DescriptorHeapPool();

  void Reclaim(uint64_t completed_submission_index);
  void ChangeSubmissionTimeline();
  void ClearCache();

  uint64_t Request(uint64_t submission_index, uint64_t previous_heap_index,
                   uint32_t count_for_partial_update, uint32_t count_for_full_update,
                   uint32_t& index_out);

  ID3D12DescriptorHeap* GetLastRequestHeap() const { return writable_first_->heap.Get(); }
  D3D12_CPU_DESCRIPTOR_HANDLE GetLastRequestHeapCPUStart() const {
    return writable_first_->cpu_start;
  }
  D3D12_GPU_DESCRIPTOR_HANDLE GetLastRequestHeapGPUStart() const {
    return writable_first_->gpu_start;
  }

 private:
  ID3D12Device* device_;
  D3D12_DESCRIPTOR_HEAP_TYPE type_;
  uint32_t page_size_;

  struct Page {
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;
    D3D12_CPU_DESCRIPTOR_HANDLE cpu_start;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_start;
    uint64_t last_submission_index;
    Page* next;
  };

  Page* writable_first_ = nullptr;
  Page* writable_last_ = nullptr;

  Page* submitted_first_ = nullptr;
  Page* submitted_last_ = nullptr;

  uint64_t current_heap_index_ = 0;
  uint32_t current_page_used_ = 0;
};

}
