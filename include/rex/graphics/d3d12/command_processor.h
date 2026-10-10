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

#include <algorithm>
#include <array>
#include <atomic>
#include <deque>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/command_processor.h>
#include <rex/graphics/debug_markers.h>
#include <rex/graphics/d3d12/deferred_command_list.h>
#include <rex/graphics/d3d12/graphics_system.h>
#include <rex/graphics/d3d12/pipeline_cache.h>
#include <rex/graphics/d3d12/primitive_processor.h>
#include <rex/graphics/d3d12/render_target_cache.h>
#include <rex/graphics/d3d12/shared_memory.h>
#include <rex/graphics/d3d12/texture_cache.h>
#include <rex/graphics/d3d12/zpd_query_pool.h>
#include <rex/graphics/pipeline/shader/dxbc.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/system/kernel_state.h>
#include <rex/ui/d3d12/d3d12_descriptor_heap_pool.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/d3d12/d3d12_upload_buffer_pool.h>
#include <rex/ui/d3d12/d3d12_util.h>

namespace rex::graphics::d3d12 {

class D3D12CommandProcessor : public CommandProcessor {
 public:
  explicit D3D12CommandProcessor(D3D12GraphicsSystem* graphics_system,
                                 system::KernelState* kernel_state);
  ~D3D12CommandProcessor();

  void ClearCaches() override;
  void InvalidateGpuMemory() override;

  void InitializeShaderStorage(const std::filesystem::path& cache_root, uint32_t title_id,
                               bool blocking) override;

  ui::d3d12::D3D12Provider& GetD3D12Provider() const {
    return *static_cast<ui::d3d12::D3D12Provider*>(graphics_system_->provider());
  }

  DeferredCommandList& GetDeferredCommandList() {
    assert_true(submission_open_);
    return deferred_command_list_;
  }

  uint64_t GetCurrentSubmission() const { return submission_current_; }

  enum class ResolveDownscaleMode : uint32_t {
    kTopLeft = 0,
    kCenter = 1,

    kAverage = 2,
  };

  bool DispatchResolveDownscale(uint32_t address, uint32_t length, uint32_t pixel_size_log2,
                                ResolveDownscaleMode mode, ID3D12Resource* dest,
                                uint64_t dest_offset);
  uint64_t GetCompletedSubmission() const override { return submission_completed_; }

  void NotifyQueueOperationsDoneDirectly() {
    queue_operations_done_since_submission_signal_ = true;
  }

  uint64_t GetCurrentFrame() const { return frame_current_; }
  uint64_t GetCompletedFrame() const { return frame_completed_; }

  bool PushTransitionBarrier(ID3D12Resource* resource, D3D12_RESOURCE_STATES old_state,
                             D3D12_RESOURCE_STATES new_state,
                             UINT subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
  void PushAliasingBarrier(ID3D12Resource* old_resource, ID3D12Resource* new_resource);
  void PushUAVBarrier(ID3D12Resource* resource);
  void SubmitBarriers();

  ID3D12RootSignature* GetRootSignature(const DxbcShader* vertex_shader,
                                        const DxbcShader* pixel_shader, bool tessellated);
  bool bindless_resources_used() const { return bindless_resources_used_; }

  ID3D12RootSignature* GetDxilRootSignature() const { return root_signature_dxil_; }

  ui::d3d12::D3D12UploadBufferPool& GetConstantBufferPool() const { return *constant_buffer_pool_; }

  D3D12_CPU_DESCRIPTOR_HANDLE GetViewBindlessHeapCPUStart() const {
    assert_true(bindless_resources_used_);
    return view_bindless_heap_cpu_start_;
  }
  D3D12_GPU_DESCRIPTOR_HANDLE GetViewBindlessHeapGPUStart() const {
    assert_true(bindless_resources_used_);
    return view_bindless_heap_gpu_start_;
  }

  uint32_t RequestPersistentViewBindlessDescriptor();
  void ReleaseViewBindlessDescriptorImmediately(uint32_t descriptor_index);

  bool RequestOneUseSingleViewDescriptors(uint32_t count,
                                          ui::d3d12::util::DescriptorCpuGpuHandlePair* handles_out);

  enum class SystemBindlessView : uint32_t {

    kSharedMemoryRawSRVAndNullRawUAVStart,
    kSharedMemoryRawSRV = kSharedMemoryRawSRVAndNullRawUAVStart,
    kNullRawUAV,

    kNullRawSRVAndSharedMemoryRawUAVStart,
    kNullRawSRV = kNullRawSRVAndSharedMemoryRawUAVStart,
    kSharedMemoryRawUAV,

    kSharedMemoryRawSRVAndRawUAVStart,
    kSharedMemoryRawSRVForUAV = kSharedMemoryRawSRVAndRawUAVStart,
    kSharedMemoryRawUAVWithSRV,

    kSharedMemoryR32UintSRV,
    kSharedMemoryR32G32UintSRV,
    kSharedMemoryR32G32B32A32UintSRV,
    kSharedMemoryR32UintUAV,
    kSharedMemoryR32G32UintUAV,
    kSharedMemoryR32G32B32A32UintUAV,

    kEdramRawSRV,
    kEdramR32UintSRV,
    kEdramR32G32UintSRV,
    kEdramR32G32B32A32UintSRV,
    kEdramRawUAV,
    kEdramR32UintUAV,
    kEdramR32G32UintUAV,
    kEdramR32G32B32A32UintUAV,

    kZpdCounterRawUAV,

    kGammaRampTableSRV,
    kGammaRampPWLSRV,

    kUnboundedSRVsStart,
    kNullTexture2DArray = kUnboundedSRVsStart,
    kNullTexture3D,
    kNullTextureCube,

    kCount,
  };
  ui::d3d12::util::DescriptorCpuGpuHandlePair GetSystemBindlessViewHandlePair(
      SystemBindlessView view) const;
  ui::d3d12::util::DescriptorCpuGpuHandlePair GetSharedMemoryUintPow2BindlessSRVHandlePair(
      uint32_t element_size_bytes_pow2) const;
  ui::d3d12::util::DescriptorCpuGpuHandlePair GetSharedMemoryUintPow2BindlessUAVHandlePair(
      uint32_t element_size_bytes_pow2) const;
  ui::d3d12::util::DescriptorCpuGpuHandlePair GetEdramUintPow2BindlessSRVHandlePair(
      uint32_t element_size_bytes_pow2) const;
  ui::d3d12::util::DescriptorCpuGpuHandlePair GetEdramUintPow2BindlessUAVHandlePair(
      uint32_t element_size_bytes_pow2) const;

  ID3D12Resource* RequestScratchGPUBuffer(uint32_t size, D3D12_RESOURCE_STATES state);

  void ReleaseScratchGPUBuffer(ID3D12Resource* buffer, D3D12_RESOURCE_STATES new_state);

  ID3D12PipelineState* GetD3D12PipelineByHandle(void* handle) const {
    return pipeline_cache_->GetD3D12PipelineByHandle(handle);
  }

  void SetExternalPipeline(ID3D12PipelineState* pipeline);
  void SetExternalGraphicsRootSignature(ID3D12RootSignature* root_signature);
  void SetViewport(const D3D12_VIEWPORT& viewport);
  void SetScissorRect(const D3D12_RECT& scissor_rect);
  void SetStencilReference(uint32_t stencil_ref);
  void SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY primitive_topology);

  std::string GetWindowTitleText() const;

 protected:
  bool SetupContext() override;
  void ShutdownContext() override;

  void WriteRegister(uint32_t index, uint32_t value) override;
  void WriteRegistersFromMem(uint32_t start_index, uint32_t* base, uint32_t num_registers) override;

  void OnGammaRamp256EntryTableValueWritten() override;
  void OnGammaRampPWLValueWritten() override;

  void IssueSwap(uint32_t frontbuffer_ptr, uint32_t frontbuffer_width,
                 uint32_t frontbuffer_height) override;

  void OnPrimaryBufferEnd() override;

  Shader* LoadShader(xenos::ShaderType shader_type, uint32_t guest_address,
                     const uint32_t* host_address, uint32_t dword_count) override;

  bool IssueDraw(xenos::PrimitiveType primitive_type, uint32_t index_count,
                 IndexBufferInfo* index_buffer_info, bool major_mode_explicit) override;
  bool IssueCopy() override;
  std::string TakeFrameTimingDetail() override;

 private:
  struct FrameTimings {
    uint64_t render_targets = 0;
    uint64_t pipelines = 0;
    uint64_t pipeline_awaits = 0;
    uint32_t pipeline_await_count = 0;
    uint64_t dxil_pipeline_setup = 0;
    uint64_t textures = 0;
    uint64_t copies = 0;
    uint64_t fence_waits = 0;

    uint64_t draws = 0;
    uint64_t submissions = 0;
    uint64_t swaps = 0;
  };
  FrameTimings frame_timings_;
  static constexpr uint32_t kQueueFrames = 3;

  enum RootParameter : UINT {

    kRootParameter_Bindful_FetchConstants = 0,

    kRootParameter_Bindful_FloatConstantsVertex,

    kRootParameter_Bindful_FloatConstantsPixel,

    kRootParameter_Bindful_SystemConstants,

    kRootParameter_Bindful_BoolLoopConstants,

    kRootParameter_Bindful_SharedMemoryAndEdram,

    kRootParameter_Bindful_Count_Base,

    kRootParameter_Bindful_Count_Max = kRootParameter_Bindful_Count_Base + 4,

    kRootParameter_Bindless_FetchConstants = 0,
    kRootParameter_Bindless_FloatConstantsVertex,
    kRootParameter_Bindless_FloatConstantsPixel,

    kRootParameter_Bindless_DescriptorIndicesPixel,
    kRootParameter_Bindless_DescriptorIndicesVertex,
    kRootParameter_Bindless_SystemConstants,
    kRootParameter_Bindless_BoolLoopConstants,

    kRootParameter_Bindless_SharedMemory,

    kRootParameter_Bindless_SamplerHeap,

    kRootParameter_Bindless_ViewHeap,

    kRootParameter_Bindless_Count,
  };

  enum DxilRootParameter : UINT {
    kRootParameter_Dxil_SystemConstants,
    kRootParameter_Dxil_FloatConstantsVertex,
    kRootParameter_Dxil_FloatConstantsPixel,
    kRootParameter_Dxil_BoolLoopConstants,
    kRootParameter_Dxil_FetchConstants,
    kRootParameter_Dxil_RuntimeData,
    kRootParameter_Dxil_VertexTextureIndices,
    kRootParameter_Dxil_PixelTextureIndices,
    kRootParameter_Dxil_VertexTextureRange,
    kRootParameter_Dxil_PixelTextureRange,
    kRootParameter_Dxil_VertexSamplerRange,
    kRootParameter_Dxil_PixelSamplerRange,
    kRootParameter_Dxil_SharedMemory,
    kRootParameter_Dxil_ZpdCounter,
    kRootParameter_Dxil_Edram,

    kRootParameter_Dxil_Count,
  };

  struct RootBindfulExtraParameterIndices {
    uint32_t textures_pixel;
    uint32_t samplers_pixel;
    uint32_t textures_vertex;
    uint32_t samplers_vertex;
    static constexpr uint32_t kUnavailable = UINT32_MAX;
  };

  static uint32_t GetRootBindfulExtraParameterIndices(
      const DxbcShader* vertex_shader, const DxbcShader* pixel_shader,
      RootBindfulExtraParameterIndices& indices_out);

  void CheckSubmissionFence(uint64_t await_submission);

  bool BeginSubmission(bool is_guest_command);

  bool EndSubmission(bool is_swap);

  bool CanEndSubmissionImmediately() const;
  bool AwaitAllQueueOperationsCompletion() {
    CheckSubmissionFence(submission_current_);
    return submission_completed_ + 1 >= submission_current_;
  }
  void LogDeviceRemovalDiagnostics(ID3D12Device* device, HRESULT reason);

  void UpdateDebugMarkersEnabled();

  uint64_t PushDebugMarker(uint64_t color, const char* format, ...);
  void PopDebugMarker(uint64_t token);
  void InsertDebugMarker(uint64_t color, const char* format, ...);
  bool debug_markers_enabled() const { return debug_markers_enabled_; }

  class DebugMarkerScope {
   public:
    explicit DebugMarkerScope(D3D12CommandProcessor& command_processor, uint64_t token)
        : command_processor_(command_processor), token_(token) {}
    ~DebugMarkerScope() { command_processor_.PopDebugMarker(token_); }
    DebugMarkerScope(const DebugMarkerScope&) = delete;
    DebugMarkerScope& operator=(const DebugMarkerScope&) = delete;

   private:
    D3D12CommandProcessor& command_processor_;
    uint64_t token_;
  };

  void ClearCommandAllocatorCache();

  uint64_t RequestViewBindfulDescriptors(uint64_t previous_heap_index,
                                         uint32_t count_for_partial_update,
                                         uint32_t count_for_full_update,
                                         D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle_out,
                                         D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle_out);
  uint64_t RequestSamplerBindfulDescriptors(uint64_t previous_heap_index,
                                            uint32_t count_for_partial_update,
                                            uint32_t count_for_full_update,
                                            D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle_out,
                                            D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle_out);

  void UpdateFixedFunctionState(const draw_util::ViewportInfo& viewport_info,
                                const draw_util::Scissor& scissor, bool primitive_polygonal,
                                reg::RB_DEPTHCONTROL normalized_depth_control);
  void UpdateSystemConstantValues(bool shared_memory_is_uav, bool primitive_polygonal,
                                  uint32_t line_loop_closing_index, xenos::Endian index_endian,
                                  const draw_util::ViewportInfo& viewport_info,
                                  uint32_t used_texture_mask,
                                  reg::RB_DEPTHCONTROL normalized_depth_control,
                                  uint32_t normalized_color_mask);
  bool UpdateBindings(const D3D12Shader* vertex_shader, const D3D12Shader* pixel_shader,
                      ID3D12RootSignature* root_signature, bool shared_memory_is_uav);
#if REXGLUE_SHADER_DXIL

  bool UpdateBindingsDxil(const SpirvShader* vertex_shader, const SpirvShader* pixel_shader,
                          bool memexport_used, bool primitive_polygonal,
                          const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
                          const draw_util::ViewportInfo& viewport_info, uint32_t used_texture_mask,
                          reg::RB_DEPTHCONTROL normalized_depth_control,
                          uint32_t normalized_color_mask);
  uint32_t GetOrCreateDxilBindlessSamplerIndex(D3D12TextureCache::SamplerParameters parameters);
  bool SwitchToNewBindlessSamplerHeap();
#endif
  bool IssueCopy_ReadbackResolvePath();
  bool IssueDraw_MemexportReadbackFullPath(uint32_t total_size);
  bool IssueDraw_MemexportReadbackFastPath(uint32_t total_size);

  ID3D12Resource* RequestReadbackBuffer(uint32_t size);
  struct ReadbackBuffer {
    ID3D12Resource* buffers[2] = {nullptr, nullptr};
    uint32_t sizes[2] = {0, 0};
    void* mapped_data[2] = {nullptr, nullptr};
    uint64_t submission_written[2] = {0, 0};
    uint32_t written_size[2] = {0, 0};
    uint32_t current_index = 0;
    uint64_t last_used_frame = 0;
  };
  void EvictOldReadbackBuffers(std::unordered_map<uint64_t, ReadbackBuffer>& buffer_map);
  static constexpr uint32_t kReadbackBufferSizeIncrement = 16 * 1024 * 1024;
  static constexpr size_t kMaxReadbackBuffers = 256;
  static constexpr uint64_t kReadbackBufferEvictionAgeFrames = 60;
  static inline uint32_t AlignReadbackBufferSize(uint32_t size) {
    if (size < 1 * 1024 * 1024) {
      return rex::align(size, 256u * 1024u);
    }
    if (size < 4 * 1024 * 1024) {
      return rex::align(size, 1u * 1024u * 1024u);
    }
    return rex::align(size, kReadbackBufferSizeIncrement);
  }
  static inline uint64_t MakeReadbackResolveKey(uint32_t address, uint32_t length) {
    return (uint64_t(address) << 32) | uint64_t(length);
  }
  static inline uint64_t MakeMemexportReadbackKey(uint32_t first_base_address_dwords,
                                                  uint32_t total_size) {
    return (uint64_t(first_base_address_dwords) << 32) | uint64_t(total_size);
  }

  void PollCompletedSubmission() override;
  void EnsureZPDQueryResources() override;
  bool IsZPDQueryPoolReady() const override;
  bool CanOpenZPDQuery() const override { return submission_open_; }
  QueryOpenResult OpenZPDQuery(bool can_close_submission) override;
  bool CloseZPDQuery(ReportHandle report_handle, const VIZQueryHandle& viz,
                     uint64_t& out_submission) override;
  void AwaitVIZQueryResolve(uint64_t wait_for_submission) override;

  bool EnsureVIZPredicateBuffer();
  void PumpQueryResolves() override;
  bool AwaitQueryResolve(ReportHandle report_handle, uint64_t wait_for_submission) override;
  void RecordZPDResolveBatch();
  void InvalidateAllVertexBufferResidency();
  void InvalidateVertexBufferResidency(uint32_t vfetch_index);
  void InvalidateVertexBufferResidencyRange(uint32_t first_vfetch, uint32_t last_vfetch);

  void WriteGammaRampSRV(bool is_pwl, D3D12_CPU_DESCRIPTOR_HANDLE handle) const;

  bool device_removed_ = false;

  bool cache_clear_requested_ = false;

  HANDLE fence_completion_event_ = nullptr;

  bool submission_open_ = false;

  uint64_t submission_current_ = 1;
  uint64_t submission_completed_ = 0;
  ID3D12Fence* submission_fence_ = nullptr;

  ID3D12Fence* queue_operations_since_submission_fence_ = nullptr;
  uint64_t queue_operations_since_submission_fence_last_ = 0;
  bool queue_operations_done_since_submission_signal_ = false;

  bool frame_open_ = false;

  uint64_t frame_current_ = 1;
  uint64_t frame_completed_ = 0;

  uint64_t closed_frame_submissions_[kQueueFrames] = {};

  struct CommandAllocator {
    ID3D12CommandAllocator* command_allocator;
    uint64_t last_usage_submission;
    CommandAllocator* next;
  };
  CommandAllocator* command_allocator_writable_first_ = nullptr;
  CommandAllocator* command_allocator_writable_last_ = nullptr;
  CommandAllocator* command_allocator_submitted_first_ = nullptr;
  CommandAllocator* command_allocator_submitted_last_ = nullptr;
  ID3D12GraphicsCommandList* command_list_ = nullptr;
  ID3D12GraphicsCommandList1* command_list_1_ = nullptr;
  DeferredCommandList deferred_command_list_;

  bool debug_markers_enabled_ = false;
  DebugMarkerRegions debug_marker_regions_;

  void UpdateFrameCapture();
  uint64_t guest_swaps_ = 0;
  bool frame_capture_active_ = false;

  struct ViewportCacheKey {
    uint32_t pa_cl_clip_cntl;
    uint32_t pa_cl_vte_cntl;
    uint32_t pa_su_sc_mode_cntl;
    uint32_t pa_su_vtx_cntl;
    uint32_t pa_sc_window_offset;
    uint32_t normalized_depth_control;
    uint32_t vport_regs[6];
    uint32_t flags;
    bool operator==(const ViewportCacheKey&) const = default;
  };
  ViewportCacheKey previous_viewport_key_{};
  draw_util::ViewportInfo previous_viewport_info_{};
  bool viewport_cache_valid_ = false;

  bool bindless_resources_used_ = false;

  std::unique_ptr<D3D12SharedMemory> shared_memory_;

  std::unique_ptr<D3D12RenderTargetCache> render_target_cache_;

  std::unique_ptr<ui::d3d12::D3D12UploadBufferPool> constant_buffer_pool_;

  static constexpr uint32_t kViewBindfulHeapSize = 32768;
  static_assert(kViewBindfulHeapSize <= D3D12_MAX_SHADER_VISIBLE_DESCRIPTOR_HEAP_SIZE_TIER_1);
  std::unique_ptr<ui::d3d12::D3D12DescriptorHeapPool> view_bindful_heap_pool_;

  ID3D12DescriptorHeap* view_bindful_heap_current_;

  static constexpr uint32_t kViewBindlessHeapSize = 262144;
  static_assert(kViewBindlessHeapSize <= D3D12_MAX_SHADER_VISIBLE_DESCRIPTOR_HEAP_SIZE_TIER_2);
  ID3D12DescriptorHeap* view_bindless_heap_ = nullptr;
  D3D12_CPU_DESCRIPTOR_HANDLE view_bindless_heap_cpu_start_;
  D3D12_GPU_DESCRIPTOR_HANDLE view_bindless_heap_gpu_start_;
  uint32_t view_bindless_heap_allocated_ = 0;
  std::vector<uint32_t> view_bindless_heap_free_;

  std::deque<std::pair<uint32_t, uint64_t>> view_bindless_one_use_descriptors_;

  static constexpr uint32_t kSamplerHeapSize = 2000;
  static_assert(kSamplerHeapSize <= D3D12_MAX_SHADER_VISIBLE_SAMPLER_HEAP_SIZE);
  std::unique_ptr<ui::d3d12::D3D12DescriptorHeapPool> sampler_bindful_heap_pool_;
  ID3D12DescriptorHeap* sampler_bindful_heap_current_;
  ID3D12DescriptorHeap* sampler_bindless_heap_current_ = nullptr;
  D3D12_CPU_DESCRIPTOR_HANDLE sampler_bindless_heap_cpu_start_;
  D3D12_GPU_DESCRIPTOR_HANDLE sampler_bindless_heap_gpu_start_;

  uint32_t sampler_bindless_heap_allocated_ = 0;

  std::deque<std::pair<ID3D12DescriptorHeap*, uint64_t>> sampler_bindless_heaps_overflowed_;

  std::unordered_map<uint32_t, uint32_t> texture_cache_bindless_sampler_map_;

  std::unordered_map<uint32_t, ID3D12RootSignature*> root_signatures_bindful_;
  ID3D12RootSignature* root_signature_bindless_vs_ = nullptr;
  ID3D12RootSignature* root_signature_bindless_ds_ = nullptr;
  ID3D12RootSignature* root_signature_dxil_ = nullptr;

  std::unique_ptr<D3D12PrimitiveProcessor> primitive_processor_;

  std::unique_ptr<PipelineCache> pipeline_cache_;

  std::unique_ptr<D3D12TextureCache> texture_cache_;

  Microsoft::WRL::ComPtr<ID3D12Resource> gamma_ramp_buffer_;
  D3D12_RESOURCE_STATES gamma_ramp_buffer_state_;

  Microsoft::WRL::ComPtr<ID3D12Resource> gamma_ramp_upload_buffer_;
  uint8_t* gamma_ramp_upload_buffer_mapping_ = nullptr;
  bool gamma_ramp_256_entry_table_up_to_date_ = false;
  bool gamma_ramp_pwl_up_to_date_ = false;

  struct ApplyGammaConstants {
    uint32_t size[2];
  };
  enum class ApplyGammaRootParameter : UINT {
    kConstants,
    kDestination,
    kSource,
    kRamp,

    kCount,
  };
  Microsoft::WRL::ComPtr<ID3D12RootSignature> apply_gamma_root_signature_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> apply_gamma_table_pipeline_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> apply_gamma_table_fxaa_luma_pipeline_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> apply_gamma_pwl_pipeline_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> apply_gamma_pwl_fxaa_luma_pipeline_;

  struct FxaaConstants {
    uint32_t size[2];
    float size_inv[2];
  };
  enum class FxaaRootParameter : UINT {
    kConstants,
    kDestination,
    kSource,

    kCount,
  };
  Microsoft::WRL::ComPtr<ID3D12RootSignature> fxaa_root_signature_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> fxaa_pipeline_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> fxaa_extreme_pipeline_;

  struct ResolveDownscaleConstants {
    uint32_t scale_x;
    uint32_t scale_y;
    uint32_t pixel_size_log2;
    uint32_t length_dwords;
    uint32_t mode;
  };
  enum class ResolveDownscaleRootParameter : UINT {
    kConstants,
    kSource,
    kDestination,

    kCount,
  };
  Microsoft::WRL::ComPtr<ID3D12RootSignature> resolve_downscale_root_signature_;
  Microsoft::WRL::ComPtr<ID3D12PipelineState> resolve_downscale_pipeline_;
  Microsoft::WRL::ComPtr<ID3D12Resource> resolve_downscale_buffer_;
  uint32_t resolve_downscale_buffer_size_ = 0;

  static constexpr DXGI_FORMAT kFxaaSourceTextureFormat = DXGI_FORMAT_R16G16B16A16_UNORM;

  Microsoft::WRL::ComPtr<ID3D12Resource> fxaa_source_texture_;
  uint64_t fxaa_source_texture_submission_ = 0;

  std::vector<D3D12_RESOURCE_BARRIER> barriers_;

  std::deque<std::pair<uint64_t, ID3D12Resource*>> resources_for_deletion_;

  static constexpr uint32_t kScratchBufferSizeIncrement = 16 * 1024 * 1024;
  ID3D12Resource* scratch_buffer_ = nullptr;
  uint32_t scratch_buffer_size_ = 0;
  D3D12_RESOURCE_STATES scratch_buffer_state_;
  bool scratch_buffer_used_ = false;

  ID3D12Resource* readback_buffer_ = nullptr;
  uint32_t readback_buffer_size_ = 0;
  std::unordered_map<uint64_t, ReadbackBuffer> readback_buffers_;
  std::unordered_map<uint64_t, ReadbackBuffer> memexport_readback_buffers_;

  std::unique_ptr<D3D12ZPDQueryPool> zpd_host_query_pool_;

  uint32_t zpd_active_query_index_ = UINT32_MAX;
  uint32_t zpd_active_query_generation_ = 0;

  struct PendingQueryResolve {
    uint64_t submission = 0;
    uint32_t query_index = UINT32_MAX;
    uint32_t query_generation = 0;
    uint32_t scale_area = 1;
    ReportHandle report_handle = kInvalidReportHandle;

    bool counter = false;

    bool hybrid = false;

    VIZQueryHandle viz;
  };
  Microsoft::WRL::ComPtr<ID3D12Resource> viz_predicate_buffer_;
  D3D12_RESOURCE_STATES viz_predicate_buffer_state_ = D3D12_RESOURCE_STATE_COMMON;
  bool viz_predicate_buffer_failed_ = false;
  std::deque<PendingQueryResolve> zpd_resolves_in_flight_;

  bool zpd_active_query_is_rov_ = false;

  bool zpd_active_query_is_hybrid_ = false;

  bool zpd_hybrid_supported_ = false;
  struct VertexBufferState {
    uint32_t address = UINT32_MAX;
    uint32_t size = UINT32_MAX;
  };
  std::array<VertexBufferState, 96> vertex_buffer_states_{};
  uint64_t vertex_buffers_in_sync_[2] = {};

  D3D12_VIEWPORT ff_viewport_;
  D3D12_RECT ff_scissor_;
  float ff_blend_factor_[4];
  uint32_t ff_stencil_ref_;
  bool ff_viewport_update_needed_;
  bool ff_scissor_update_needed_;
  bool ff_blend_factor_update_needed_;
  bool ff_stencil_ref_update_needed_;

  void* current_guest_pipeline_;
  ID3D12PipelineState* current_external_pipeline_;

  ID3D12RootSignature* current_graphics_root_signature_;

  RootBindfulExtraParameterIndices current_graphics_root_bindful_extras_;

  uint32_t current_graphics_root_up_to_date_;

  DxbcShaderTranslator::SystemConstants system_constants_;

  uint64_t current_float_constant_map_vertex_[4];
  uint64_t current_float_constant_map_pixel_[4];

  struct ConstantBufferBinding {
    D3D12_GPU_VIRTUAL_ADDRESS address;
    bool up_to_date;
  };
  ConstantBufferBinding cbuffer_binding_system_;
  ConstantBufferBinding cbuffer_binding_float_vertex_;
  ConstantBufferBinding cbuffer_binding_float_pixel_;
  ConstantBufferBinding cbuffer_binding_bool_loop_;
  ConstantBufferBinding cbuffer_binding_fetch_;
  ConstantBufferBinding cbuffer_binding_descriptor_indices_vertex_;
  ConstantBufferBinding cbuffer_binding_descriptor_indices_pixel_;

  ConstantBufferBinding cbuffer_binding_dxil_system_;
  ConstantBufferBinding cbuffer_binding_dxil_float_vertex_;
  ConstantBufferBinding cbuffer_binding_dxil_float_pixel_;
  ConstantBufferBinding cbuffer_binding_dxil_bool_loop_;
  ConstantBufferBinding cbuffer_binding_dxil_fetch_;
  ConstantBufferBinding cbuffer_binding_dxil_runtime_data_;
  std::vector<uint8_t> dxil_system_constants_shadow_;
  uint64_t dxil_float_constant_map_vertex_[4] = {};
  uint64_t dxil_float_constant_map_pixel_[4] = {};

  std::optional<bool> current_shared_memory_binding_is_uav_;

  uint64_t draw_view_bindful_heap_index_;
  uint64_t draw_sampler_bindful_heap_index_;

  bool bindful_textures_written_vertex_;
  bool bindful_textures_written_pixel_;
  bool bindful_samplers_written_vertex_;
  bool bindful_samplers_written_pixel_;

  size_t current_texture_layout_uid_vertex_;
  size_t current_texture_layout_uid_pixel_;
  size_t current_sampler_layout_uid_vertex_;
  size_t current_sampler_layout_uid_pixel_;

  std::vector<D3D12TextureCache::TextureSRVKey> current_texture_srv_keys_vertex_;
  std::vector<D3D12TextureCache::TextureSRVKey> current_texture_srv_keys_pixel_;
  std::vector<D3D12TextureCache::SamplerParameters> current_samplers_vertex_;
  std::vector<D3D12TextureCache::SamplerParameters> current_samplers_pixel_;
  std::vector<uint32_t> current_sampler_bindless_indices_vertex_;
  std::vector<uint32_t> current_sampler_bindless_indices_pixel_;

  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_shared_memory_srv_and_edram_;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_shared_memory_uav_and_edram_;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_textures_vertex_;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_textures_pixel_;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_samplers_vertex_;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle_samplers_pixel_;

  D3D_PRIMITIVE_TOPOLOGY primitive_topology_;

  std::vector<draw_util::MemExportRange> memexport_ranges_;
};

}
