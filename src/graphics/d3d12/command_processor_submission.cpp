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

#include <algorithm>
#include <optional>
#include <chrono>
#include <cstdarg>
#include <cstring>
#include <sstream>
#include <utility>
#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/dbg.h>
#include <rex/perf/counter.h>
#include <rex/graphics/d3d12/command_processor.h>
#include <rex/graphics/d3d12/graphics_system.h>
#include <rex/graphics/d3d12/shader.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/kernel/xboxkrnl/video.h>
#include <rex/logging.h>
#include <rex/memory/utils.h>
#include <rex/ui/d3d12/d3d12_presenter.h>
#include <rex/ui/d3d12/d3d12_util.h>
#if REXGLUE_SHADER_DXIL
#include <rex/graphics/pipeline/shader/spirv_fsi_system_constants.h>
#include <rex/graphics/pipeline/shader/spirv_translator.h>
#endif

namespace rex::graphics::d3d12 {

namespace {

class TickAccumulator {
 public:
  explicit TickAccumulator(uint64_t& total)
      : total_(total), start_(rex::chrono::Clock::QueryHostTickCount()) {}
  ~TickAccumulator() { total_ += rex::chrono::Clock::QueryHostTickCount() - start_; }
  TickAccumulator(const TickAccumulator&) = delete;
  TickAccumulator& operator=(const TickAccumulator&) = delete;

 private:
  uint64_t& total_;
  uint64_t start_;
};

}

namespace {

constexpr uint64_t kSubmissionMarkerColor = pix::Color(0x40, 0x80, 0xFF);
}

void D3D12CommandProcessor::CheckSubmissionFence(uint64_t await_submission) {
  if (await_submission >= submission_current_) {
    if (submission_open_) {
      EndSubmission(false);
    }

    if (queue_operations_done_since_submission_signal_) {
      UINT64 fence_value = ++queue_operations_since_submission_fence_last_;
      ID3D12CommandQueue* direct_queue = GetD3D12Provider().GetDirectQueue();
      if (SUCCEEDED(direct_queue->Signal(queue_operations_since_submission_fence_, fence_value) &&
                    SUCCEEDED(queue_operations_since_submission_fence_->SetEventOnCompletion(
                        fence_value, fence_completion_event_)))) {
        PROFILE_CMD_BUFFER_STALL();
        TickAccumulator fence_time(frame_timings_.fence_waits);
        WaitForSingleObject(fence_completion_event_, INFINITE);
        queue_operations_done_since_submission_signal_ = false;
      } else {
        REXGPU_ERROR(
            "Failed to await an out-of-submission queue operation completion "
            "Direct3D 12 fence");
      }
    }

    await_submission = submission_current_ - 1;
  }

  uint64_t submission_completed_before = submission_completed_;
  submission_completed_ = submission_fence_->GetCompletedValue();
  if (submission_completed_ < await_submission) {
    if (SUCCEEDED(
            submission_fence_->SetEventOnCompletion(await_submission, fence_completion_event_))) {
      PROFILE_CMD_BUFFER_STALL();
      TickAccumulator fence_time(frame_timings_.fence_waits);
      WaitForSingleObject(fence_completion_event_, INFINITE);
      submission_completed_ = submission_fence_->GetCompletedValue();
    }
  }
  if (submission_completed_ < await_submission) {
    REXGPU_ERROR("Failed to await a submission completion Direct3D 12 fence");
  }
  if (submission_completed_ <= submission_completed_before) {
    return;
  }

  while (command_allocator_submitted_first_) {
    if (command_allocator_submitted_first_->last_usage_submission > submission_completed_) {
      break;
    }
    if (command_allocator_writable_last_) {
      command_allocator_writable_last_->next = command_allocator_submitted_first_;
    } else {
      command_allocator_writable_first_ = command_allocator_submitted_first_;
    }
    command_allocator_writable_last_ = command_allocator_submitted_first_;
    command_allocator_submitted_first_ = command_allocator_submitted_first_->next;
    command_allocator_writable_last_->next = nullptr;
  }
  if (!command_allocator_submitted_first_) {
    command_allocator_submitted_last_ = nullptr;
  }

  while (!view_bindless_one_use_descriptors_.empty()) {
    if (view_bindless_one_use_descriptors_.front().second > submission_completed_) {
      break;
    }
    ReleaseViewBindlessDescriptorImmediately(view_bindless_one_use_descriptors_.front().first);
    view_bindless_one_use_descriptors_.pop_front();
  }

  while (!resources_for_deletion_.empty()) {
    if (resources_for_deletion_.front().first > submission_completed_) {
      break;
    }
    resources_for_deletion_.front().second->Release();
    resources_for_deletion_.pop_front();
  }

  shared_memory_->CompletedSubmissionUpdated();

  render_target_cache_->CompletedSubmissionUpdated();

  primitive_processor_->CompletedSubmissionUpdated();

  texture_cache_->CompletedSubmissionUpdated(submission_completed_);

  PumpQueryResolves();
  PumpPendingRetire();
}

void D3D12CommandProcessor::LogDeviceRemovalDiagnostics(ID3D12Device* device, HRESULT reason) {
  const char* reason_str = "Unknown";
  switch (reason) {
    case DXGI_ERROR_DEVICE_HUNG:
      reason_str = "DEVICE_HUNG (TDR - GPU command took too long)";
      break;
    case DXGI_ERROR_DEVICE_REMOVED:
      reason_str = "DEVICE_REMOVED (driver internal error or hot-unplug)";
      break;
    case DXGI_ERROR_DEVICE_RESET:
      reason_str = "DEVICE_RESET (bad GPU command)";
      break;
    case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
      reason_str = "DRIVER_INTERNAL_ERROR";
      break;
    case DXGI_ERROR_INVALID_CALL:
      reason_str = "INVALID_CALL";
      break;
  }
  REXGPU_ERROR("D3D12 device removed: HRESULT 0x{:08X} - {}", static_cast<unsigned>(reason),
               reason_str);

  Microsoft::WRL::ComPtr<ID3D12DeviceRemovedExtendedData> dred;
  if (FAILED(device->QueryInterface(IID_PPV_ARGS(&dred)))) {
    return;
  }

  D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT breadcrumbs = {};
  if (SUCCEEDED(dred->GetAutoBreadcrumbsOutput(&breadcrumbs))) {
    for (const D3D12_AUTO_BREADCRUMB_NODE* node = breadcrumbs.pHeadAutoBreadcrumbNode; node;
         node = node->pNext) {
      if (!node->pLastBreadcrumbValue || !node->pCommandHistory ||
          *node->pLastBreadcrumbValue == 0) {
        continue;
      }
      REXGPU_ERROR("DRED breadcrumb: completed {} of {} ops", *node->pLastBreadcrumbValue,
                   node->BreadcrumbCount);
      uint32_t last = std::min(*node->pLastBreadcrumbValue, node->BreadcrumbCount);
      uint32_t start = last > 3 ? last - 3 : 0;
      uint32_t end = std::min(last + 1, node->BreadcrumbCount);
      for (uint32_t i = start; i < end; i++) {
        REXGPU_ERROR("  [{}] op type {}{}", i, static_cast<int>(node->pCommandHistory[i]),
                     i == last ? " <-- FAULT" : "");
      }
    }
  }

  D3D12_DRED_PAGE_FAULT_OUTPUT page_fault = {};
  if (SUCCEEDED(dred->GetPageFaultAllocationOutput(&page_fault)) && page_fault.PageFaultVA != 0) {
    REXGPU_ERROR("DRED page fault at VA 0x{:016X}", page_fault.PageFaultVA);
  }
}

bool D3D12CommandProcessor::BeginSubmission(bool is_guest_command) {
#if XE_GPU_FINE_GRAINED_DRAW_SCOPES
  SCOPE_profile_cpu_f("gpu");
#endif

  if (device_removed_) {
    return false;
  }

  bool is_opening_frame = is_guest_command && !frame_open_;
  if (submission_open_ && !is_opening_frame) {
    return true;
  }

  ID3D12Device* device = GetD3D12Provider().GetDevice();
  HRESULT device_removed_reason = device->GetDeviceRemovedReason();
  if (FAILED(device_removed_reason)) {
    device_removed_ = true;
    LogDeviceRemovalDiagnostics(device, device_removed_reason);
    if (graphics_system_) {
      graphics_system_->OnHostGpuLossFromAnyThread(device_removed_reason !=
                                                   DXGI_ERROR_DEVICE_REMOVED);
    }
    return false;
  }

  CheckSubmissionFence(is_opening_frame ? closed_frame_submissions_[frame_current_ % kQueueFrames]
                                        : 0);

  if (is_opening_frame) {
    frame_completed_ = std::max(frame_current_, uint64_t(kQueueFrames)) - kQueueFrames;
    for (uint64_t frame = frame_completed_ + 1; frame < frame_current_; ++frame) {
      if (closed_frame_submissions_[frame % kQueueFrames] > submission_completed_) {
        break;
      }
      frame_completed_ = frame;
    }
  }

  if (!submission_open_) {
    submission_open_ = true;

    deferred_command_list_.Reset();

    debug_marker_regions_.CloseAll();

    OpenQuerySegment(false);

    ff_viewport_update_needed_ = true;
    ff_scissor_update_needed_ = true;
    ff_blend_factor_update_needed_ = true;
    ff_stencil_ref_update_needed_ = true;
    viewport_cache_valid_ = false;
    current_guest_pipeline_ = nullptr;
    current_external_pipeline_ = nullptr;
    current_graphics_root_signature_ = nullptr;
    current_graphics_root_up_to_date_ = 0;
    if (bindless_resources_used_) {
      deferred_command_list_.SetDescriptorHeaps(view_bindless_heap_,
                                                sampler_bindless_heap_current_);
    } else {
      view_bindful_heap_current_ = nullptr;
      sampler_bindful_heap_current_ = nullptr;
    }
    primitive_topology_ = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

    render_target_cache_->BeginSubmission();

    primitive_processor_->BeginSubmission();

    texture_cache_->BeginSubmission(submission_current_);
  }

  if (is_opening_frame) {
    frame_open_ = true;

    std::memset(current_float_constant_map_vertex_, 0, sizeof(current_float_constant_map_vertex_));
    std::memset(current_float_constant_map_pixel_, 0, sizeof(current_float_constant_map_pixel_));
    cbuffer_binding_system_.up_to_date = false;
    cbuffer_binding_dxil_system_.up_to_date = false;
    cbuffer_binding_dxil_runtime_data_.up_to_date = false;
    dxil_system_constants_shadow_.clear();
    std::memset(dxil_float_constant_map_vertex_, 0, sizeof(dxil_float_constant_map_vertex_));
    std::memset(dxil_float_constant_map_pixel_, 0, sizeof(dxil_float_constant_map_pixel_));
    cbuffer_binding_float_vertex_.up_to_date = false;
    cbuffer_binding_dxil_float_vertex_.up_to_date = false;
    cbuffer_binding_float_pixel_.up_to_date = false;
    cbuffer_binding_dxil_float_pixel_.up_to_date = false;
    cbuffer_binding_bool_loop_.up_to_date = false;
    cbuffer_binding_dxil_bool_loop_.up_to_date = false;
    cbuffer_binding_fetch_.up_to_date = false;
    cbuffer_binding_dxil_fetch_.up_to_date = false;
    current_shared_memory_binding_is_uav_.reset();
    if (bindless_resources_used_) {
      cbuffer_binding_descriptor_indices_vertex_.up_to_date = false;
      cbuffer_binding_descriptor_indices_pixel_.up_to_date = false;
    } else {
      draw_view_bindful_heap_index_ = ui::d3d12::D3D12DescriptorHeapPool::kHeapIndexInvalid;
      draw_sampler_bindful_heap_index_ = ui::d3d12::D3D12DescriptorHeapPool::kHeapIndexInvalid;
      bindful_textures_written_vertex_ = false;
      bindful_textures_written_pixel_ = false;
      bindful_samplers_written_vertex_ = false;
      bindful_samplers_written_pixel_ = false;
    }

    constant_buffer_pool_->Reclaim(frame_completed_);
    if (!bindless_resources_used_) {
      view_bindful_heap_pool_->Reclaim(frame_completed_);
      sampler_bindful_heap_pool_->Reclaim(frame_completed_);
    }
    EvictOldReadbackBuffers(readback_buffers_);
    EvictOldReadbackBuffers(memexport_readback_buffers_);

    primitive_processor_->BeginFrame();

    texture_cache_->BeginFrame();
  }

  return true;
}

bool D3D12CommandProcessor::EndSubmission(bool is_swap) {
  TickAccumulator submission_time(frame_timings_.submissions);
  const ui::d3d12::D3D12Provider& provider = GetD3D12Provider();

  if (submission_open_ && !command_allocator_writable_first_) {
    ID3D12CommandAllocator* command_allocator;
    if (FAILED(provider.GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                            IID_PPV_ARGS(&command_allocator)))) {
      REXGPU_ERROR("Failed to create a command allocator");

      return false;
    }
    command_allocator_writable_first_ = new CommandAllocator;
    command_allocator_writable_first_->command_allocator = command_allocator;
    command_allocator_writable_first_->last_usage_submission = 0;
    command_allocator_writable_first_->next = nullptr;
    command_allocator_writable_last_ = command_allocator_writable_first_;
  }

  bool is_closing_frame = is_swap && frame_open_;

  if (is_closing_frame) {
    texture_cache_->EndFrame();

    primitive_processor_->EndFrame();
  }

  if (submission_open_) {
    assert_false(scratch_buffer_used_);

    {
      CloseQuerySegment();
      RecordZPDResolveBatch();
    }

    pipeline_cache_->EndSubmission();

    SubmitBarriers();

    ID3D12CommandQueue* direct_queue = provider.GetDirectQueue();

    ID3D12CommandAllocator* command_allocator =
        command_allocator_writable_first_->command_allocator;
    command_allocator->Reset();
    command_list_->Reset(command_allocator, nullptr);

    for (uint32_t i = debug_marker_regions_.CloseAll(); i; --i) {
      deferred_command_list_.EndDebugMarker();
    }
    deferred_command_list_.Execute(command_list_, command_list_1_);
    command_list_->Close();
    ID3D12CommandList* execute_command_lists[] = {command_list_};

    if (debug_markers_enabled_) {
      char label[64];
      snprintf(label, sizeof(label), "Frame %llu, submission %llu",
               static_cast<unsigned long long>(frame_current_),
               static_cast<unsigned long long>(submission_current_));
      uint64_t blob[pix::kMaxEventWords];
      UINT blob_size = pix::EncodeEvent(blob, pix::EventType::kBeginEvent, kSubmissionMarkerColor,
                                        direct_queue, label);
      direct_queue->BeginEvent(pix::kBlobV2Metadata, blob, blob_size);
    }
    direct_queue->ExecuteCommandLists(1, execute_command_lists);
    if (debug_markers_enabled_) {
      direct_queue->EndEvent();
    }
    command_allocator_writable_first_->last_usage_submission = submission_current_;
    if (command_allocator_submitted_last_) {
      command_allocator_submitted_last_->next = command_allocator_writable_first_;
    } else {
      command_allocator_submitted_first_ = command_allocator_writable_first_;
    }
    command_allocator_submitted_last_ = command_allocator_writable_first_;
    command_allocator_writable_first_ = command_allocator_writable_first_->next;
    command_allocator_submitted_last_->next = nullptr;
    if (!command_allocator_writable_first_) {
      command_allocator_writable_last_ = nullptr;
    }

    direct_queue->Signal(submission_fence_, submission_current_++);

    submission_open_ = false;

    PumpQueryResolves();
    PumpPendingRetire();

    queue_operations_done_since_submission_signal_ = false;
  }

  if (is_closing_frame) {
    if (REXCVAR_GET(clear_memory_page_state) && shared_memory_) {
      shared_memory_->SetSystemPageBlocksValidWithGpuDataWritten();
    }
    frame_open_ = false;

    closed_frame_submissions_[(frame_current_++) % kQueueFrames] = submission_current_ - 1;

    if (cache_clear_requested_ && AwaitAllQueueOperationsCompletion()) {
      cache_clear_requested_ = false;

      ClearCommandAllocatorCache();

      ui::d3d12::util::ReleaseAndNull(scratch_buffer_);
      scratch_buffer_size_ = 0;

      if (bindless_resources_used_) {
        texture_cache_bindless_sampler_map_.clear();
        for (const auto& sampler_bindless_heap_overflowed : sampler_bindless_heaps_overflowed_) {
          sampler_bindless_heap_overflowed.first->Release();
        }
        sampler_bindless_heaps_overflowed_.clear();
        sampler_bindless_heap_allocated_ = 0;
      } else {
        sampler_bindful_heap_pool_->ClearCache();
        view_bindful_heap_pool_->ClearCache();
      }
      constant_buffer_pool_->ClearCache();

      texture_cache_->ClearCache();

      primitive_processor_->ClearCache();

      render_target_cache_->ClearCache();

      shared_memory_->ClearCache();
    }
  }

  return true;
}

bool D3D12CommandProcessor::CanEndSubmissionImmediately() const {
  return !submission_open_ || !pipeline_cache_->IsCreatingPipelines();
}

void D3D12CommandProcessor::ClearCommandAllocatorCache() {
  while (command_allocator_submitted_first_) {
    auto next = command_allocator_submitted_first_->next;
    command_allocator_submitted_first_->command_allocator->Release();
    delete command_allocator_submitted_first_;
    command_allocator_submitted_first_ = next;
  }
  command_allocator_submitted_last_ = nullptr;
  while (command_allocator_writable_first_) {
    auto next = command_allocator_writable_first_->next;
    command_allocator_writable_first_->command_allocator->Release();
    delete command_allocator_writable_first_;
    command_allocator_writable_first_ = next;
  }
  command_allocator_writable_last_ = nullptr;
}

void D3D12CommandProcessor::EvictOldReadbackBuffers(
    std::unordered_map<uint64_t, ReadbackBuffer>& buffer_map) {
  if (buffer_map.empty()) {
    return;
  }
  const uint64_t eviction_frame_floor = (frame_current_ > kReadbackBufferEvictionAgeFrames)
                                            ? (frame_current_ - kReadbackBufferEvictionAgeFrames)
                                            : 0;
  for (auto it = buffer_map.begin(); it != buffer_map.end();) {
    ReadbackBuffer& readback = it->second;
    bool evict =
        buffer_map.size() > kMaxReadbackBuffers || readback.last_used_frame < eviction_frame_floor;
    if (!evict) {
      ++it;
      continue;
    }
    for (uint32_t i = 0; i < 2; ++i) {
      if (readback.buffers[i]) {
        if (readback.mapped_data[i]) {
          readback.buffers[i]->Unmap(0, nullptr);
        }
        readback.buffers[i]->Release();
      }
      readback.buffers[i] = nullptr;
      readback.mapped_data[i] = nullptr;
      readback.sizes[i] = 0;
      readback.submission_written[i] = 0;
      readback.written_size[i] = 0;
    }
    it = buffer_map.erase(it);
  }
}

ID3D12Resource* D3D12CommandProcessor::RequestReadbackBuffer(uint32_t size) {
  if (size == 0) {
    return nullptr;
  }
  size = rex::align(size, kReadbackBufferSizeIncrement);
  if (size > readback_buffer_size_) {
    const ui::d3d12::D3D12Provider& provider = GetD3D12Provider();
    ID3D12Device* device = provider.GetDevice();
    D3D12_RESOURCE_DESC buffer_desc;
    ui::d3d12::util::FillBufferResourceDesc(buffer_desc, size, D3D12_RESOURCE_FLAG_NONE);
    ID3D12Resource* buffer;
    if (FAILED(device->CreateCommittedResource(
            &ui::d3d12::util::kHeapPropertiesReadback, provider.GetHeapFlagCreateNotZeroed(),
            &buffer_desc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&buffer)))) {
      REXGPU_ERROR("Failed to create a {} MB readback buffer", size >> 20);
      return nullptr;
    }
    if (readback_buffer_ != nullptr) {
      readback_buffer_->Release();
    }
    readback_buffer_ = buffer;
    readback_buffer_size_ = size;
  }
  return readback_buffer_;
}

void D3D12CommandProcessor::EnsureZPDQueryResources() {
  if ((zpd_mode_ == ZPDMode::kFake && !REXCVAR_GET(occlusion_query_viz)) || !zpd_host_query_pool_ ||
      IsZPDQueryPoolReady()) {
    return;
  }

  bool rov = render_target_cache_->GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;
  zpd_host_query_pool_->EnsureInitialized(GetD3D12Provider(), kZPDQueryPoolCapacity,
                                          rov || zpd_hybrid_supported_);
  if ((rov || zpd_hybrid_supported_) && bindless_resources_used_) {
    zpd_host_query_pool_->WriteCounterRawUAVDescriptor(
        GetD3D12Provider().GetDevice(),
        GetD3D12Provider().OffsetViewDescriptor(view_bindless_heap_cpu_start_,
                                                uint32_t(SystemBindlessView::kZpdCounterRawUAV)));
  }

  draw_view_bindful_heap_index_ = ui::d3d12::D3D12DescriptorHeapPool::kHeapIndexInvalid;
}

bool D3D12CommandProcessor::IsZPDQueryPoolReady() const {
  if (!zpd_host_query_pool_ || !zpd_host_query_pool_->initialized()) {
    return false;
  }
  return render_target_cache_->GetPath() != RenderTargetCache::Path::kPixelShaderInterlock ||
         zpd_host_query_pool_->counter_initialized();
}

CommandProcessor::QueryOpenResult D3D12CommandProcessor::OpenZPDQuery(bool can_close_submission) {
  bool is_pool_exhausted = !zpd_host_query_pool_->has_free_indices();
  if (is_pool_exhausted) {
    PumpQueryResolves();
    is_pool_exhausted = !zpd_host_query_pool_->has_free_indices();
  }

  if (is_pool_exhausted) {
    if (zpd_mode_ != ZPDMode::kStrict) {
      return QueryOpenResult::kPoolExhausted;
    }

    uint64_t wait_for = 0;
    if (!zpd_resolves_in_flight_.empty()) {
      wait_for = zpd_resolves_in_flight_.front().submission;
    }

    if (wait_for > GetCompletedSubmission()) {
      if (wait_for >= GetCurrentSubmission()) {
        if (can_close_submission) {
          if (!EndSubmission(false)) {
            return QueryOpenResult::kFailed;
          }
        }
        return QueryOpenResult::kDeferred;
      }

      CheckSubmissionFence(wait_for);
      PumpQueryResolves();
      is_pool_exhausted = !zpd_host_query_pool_->has_free_indices();
    }
  }

  if (is_pool_exhausted) {
    return QueryOpenResult::kDeferred;
  }

  if (!zpd_host_query_pool_->AcquireQueryIndex(zpd_active_query_index_,
                                               zpd_active_query_generation_)) {
    return QueryOpenResult::kFailed;
  }
  zpd_active_query_is_rov_ =
      render_target_cache_->GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;
  zpd_active_query_is_hybrid_ = !zpd_active_query_is_rov_ && zpd_hybrid_supported_ &&
                                zpd_active_segment_.count_total &&
                                zpd_host_query_pool_->counter_initialized();
  if (zpd_active_query_is_hybrid_) {
    zpd_host_query_pool_->ClearCounter(deferred_command_list_, GetCurrentSubmission(),
                                       zpd_active_query_index_);
  }
  if (zpd_active_query_is_rov_) {
    zpd_host_query_pool_->ClearCounter(deferred_command_list_, GetCurrentSubmission(),
                                       zpd_active_query_index_);
    return QueryOpenResult::kOpened;
  }
  zpd_host_query_pool_->BeginQuery(deferred_command_list_, zpd_active_query_index_);
  return QueryOpenResult::kOpened;
}

bool D3D12CommandProcessor::CloseZPDQuery(ReportHandle report_handle, const VIZQueryHandle& viz,
                                          uint64_t& out_submission) {
  if (!zpd_active_query_is_rov_) {
    zpd_host_query_pool_->EndQuery(deferred_command_list_, zpd_active_query_index_);
  }
  zpd_host_query_pool_->QueueQueryResolve(zpd_active_query_index_, zpd_active_query_is_rov_);
  if (zpd_active_query_is_hybrid_) {
    zpd_host_query_pool_->QueueQueryResolve(zpd_active_query_index_, true);
  }

  if (viz.generation != kInvalidVIZGeneration) {
    if (CanArmVIZPredicate(viz.id, viz.generation) && EnsureVIZPredicateBuffer()) {
      const uint64_t predicate_offset = uint64_t(viz.id) * sizeof(uint64_t);
      PushTransitionBarrier(viz_predicate_buffer_.Get(), viz_predicate_buffer_state_,
                            D3D12_RESOURCE_STATE_COPY_DEST);
      viz_predicate_buffer_state_ = D3D12_RESOURCE_STATE_COPY_DEST;
      SubmitBarriers();
      if (zpd_active_query_is_rov_) {
        zpd_host_query_pool_->CopyCounterZPassTo(deferred_command_list_, GetCurrentSubmission(),
                                                 zpd_active_query_index_,
                                                 viz_predicate_buffer_.Get(), predicate_offset);
      } else {
        zpd_host_query_pool_->ResolveQueryTo(deferred_command_list_, zpd_active_query_index_,
                                             viz_predicate_buffer_.Get(), predicate_offset);
      }
      ArmVIZPredicate(viz.id, viz.generation);
    } else {
      BlockVIZPredicate(viz.id, viz.generation);
    }
  }

  PendingQueryResolve resolve;
  resolve.counter = zpd_active_query_is_rov_;
  resolve.hybrid = zpd_active_query_is_hybrid_;
  resolve.submission = GetCurrentSubmission();
  resolve.query_index = zpd_active_query_index_;
  resolve.query_generation = zpd_active_query_generation_;
  resolve.scale_area = GetZPDScaleArea();
  resolve.report_handle = report_handle;
  resolve.viz = viz;
  zpd_resolves_in_flight_.push_back(resolve);

  out_submission = resolve.submission;

  zpd_active_query_index_ = UINT32_MAX;
  zpd_active_query_generation_ = 0;
  zpd_active_query_is_rov_ = false;
  zpd_active_query_is_hybrid_ = false;
  return true;
}

void D3D12CommandProcessor::PumpQueryResolves() {
  if (!zpd_host_query_pool_ || zpd_resolves_in_flight_.empty()) {
    return;
  }

  uint64_t completed = GetCompletedSubmission();
  while (!zpd_resolves_in_flight_.empty() &&
         zpd_resolves_in_flight_.front().submission <= completed) {
    PendingQueryResolve resolve = zpd_resolves_in_flight_.front();
    zpd_resolves_in_flight_.pop_front();

    if (zpd_host_query_pool_->GenerationMatches(resolve.query_index, resolve.query_generation)) {
      XenosZPDReport raw_counts =
          resolve.hybrid
              ? zpd_host_query_pool_->GetHybridReadbackValue(resolve.query_index)
              : zpd_host_query_pool_->GetQueryReadbackValue(resolve.query_index, resolve.counter);
      zpd_host_query_pool_->ReleaseQueryIndex(resolve.query_index, resolve.query_generation);
      if (resolve.report_handle != kInvalidReportHandle) {
        OnZPDQueryResolved(resolve.report_handle, raw_counts, resolve.scale_area);
      }
      if (resolve.viz.generation != kInvalidVIZGeneration) {
        OnVIZQueryResolved(resolve.viz.id, resolve.viz.generation, raw_counts.z_pass != 0);
      }
    }
  }
}

bool D3D12CommandProcessor::AwaitQueryResolve(ReportHandle report_handle,
                                              uint64_t wait_for_submission) {
  assert_not_zero(wait_for_submission);

  if (wait_for_submission >= GetCurrentSubmission()) {
    if (!submission_open_) {
      return false;
    }
    if (!CanEndSubmissionImmediately()) {
      pipeline_cache_->AwaitPipelineCompletion();
    }
    if (!CanEndSubmissionImmediately() || !EndSubmission(false)) {
      return false;
    }
  }

  if (wait_for_submission > GetCompletedSubmission()) {
    CheckSubmissionFence(wait_for_submission);
  }

  PumpQueryResolves();

  const ZPDReport* report = FindZPDReport(report_handle);
  return !report || !report->pending_segments;
}

bool D3D12CommandProcessor::EnsureVIZPredicateBuffer() {
  if (viz_predicate_buffer_) {
    return true;
  }
  if (viz_predicate_buffer_failed_) {
    return false;
  }
  D3D12_RESOURCE_DESC buffer_desc;
  ui::d3d12::util::FillBufferResourceDesc(buffer_desc, sizeof(uint64_t) * viz_queries_.size(),
                                          D3D12_RESOURCE_FLAG_NONE);

  if (FAILED(GetD3D12Provider().GetDevice()->CreateCommittedResource(
          &ui::d3d12::util::kHeapPropertiesDefault, D3D12_HEAP_FLAG_NONE, &buffer_desc,
          D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&viz_predicate_buffer_)))) {
    REXGPU_ERROR("VIZ/D3D12: Failed to create the predicate buffer");
    viz_predicate_buffer_failed_ = true;
    return false;
  }
  viz_predicate_buffer_state_ = D3D12_RESOURCE_STATE_COMMON;
  return true;
}

void D3D12CommandProcessor::AwaitVIZQueryResolve(uint64_t wait_for_submission) {
  if (wait_for_submission >= GetCurrentSubmission()) {
    return;
  }
  if (wait_for_submission > GetCompletedSubmission()) {
    CheckSubmissionFence(wait_for_submission);
  }
  PumpQueryResolves();
}

void D3D12CommandProcessor::RecordZPDResolveBatch() {
  if (zpd_host_query_pool_) {
    zpd_host_query_pool_->FlushResolveBatch(deferred_command_list_, GetCurrentSubmission(),
                                            submission_open_);
  }
}

}
