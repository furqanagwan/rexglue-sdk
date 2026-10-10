/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <rex/ui/d3d12/d3d12_api.h>

namespace rex::ui::d3d12 {

class D3D12SubmissionTracker {
 public:
  D3D12SubmissionTracker() = default;
  D3D12SubmissionTracker(const D3D12SubmissionTracker& submission_tracker) = delete;
  D3D12SubmissionTracker& operator=(const D3D12SubmissionTracker& submission_tracker) = delete;
  ~D3D12SubmissionTracker() { Shutdown(); }

  bool Initialize(ID3D12Device* device, ID3D12CommandQueue* queue);
  void Shutdown();

  void SetQueue(ID3D12CommandQueue* new_queue);

  UINT64 GetCurrentSubmission() const { return submission_current_; }

  UINT64 GetCompletedSubmission() const {
    return fence_ ? fence_->GetCompletedValue() : (GetCurrentSubmission() - 1);
  }

  bool AwaitSubmissionCompletion(UINT64 submission_index);
  bool AwaitAllSubmissionsCompletion() {
    return AwaitSubmissionCompletion(GetCurrentSubmission() - 1);
  }

  bool NextSubmission();

  bool TrySignalEnqueueing();

 private:
  UINT64 submission_current_ = 1;
  UINT64 submission_signal_queued_ = 0;
  HANDLE fence_completion_event_ = nullptr;
  Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
  Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue_;
};

}
