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

#include <array>
#include <memory>
#include <utility>

#include <rex/math.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/d3d12/d3d12_submission_tracker.h>
#include <rex/ui/presenter.h>
#include <rex/ui/surface.h>

namespace rex::ui::d3d12 {

class D3D12UIDrawContext final : public UIDrawContext {
 public:
  D3D12UIDrawContext(Presenter& presenter, uint32_t render_target_width,
                     uint32_t render_target_height, ID3D12GraphicsCommandList* command_list,
                     UINT64 submission_index_current, UINT64 submission_index_completed)
      : UIDrawContext(presenter, render_target_width, render_target_height),
        command_list_(command_list),
        submission_index_current_(submission_index_current),
        submission_index_completed_(submission_index_completed) {}

  ID3D12GraphicsCommandList* command_list() const { return command_list_.Get(); }
  UINT64 submission_index_current() const { return submission_index_current_; }
  UINT64 submission_index_completed() const { return submission_index_completed_; }

 private:
  Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list_;
  UINT64 submission_index_current_;
  UINT64 submission_index_completed_;
};

class D3D12Presenter final : public Presenter {
 public:
  static constexpr DXGI_FORMAT kGuestOutputFormat = DXGI_FORMAT_R10G10B10A2_UNORM;
  static constexpr D3D12_RESOURCE_STATES kGuestOutputInternalState =
      D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

  static constexpr DXGI_FORMAT kGuestOutputIntermediateFormat = DXGI_FORMAT_R10G10B10A2_UNORM;

  static constexpr DXGI_FORMAT kSwapChainFormat = DXGI_FORMAT_B8G8R8A8_UNORM;

  class D3D12GuestOutputRefreshContext final : public GuestOutputRefreshContext {
   public:
    D3D12GuestOutputRefreshContext(bool& is_8bpc_out_ref, ID3D12Resource* resource)
        : GuestOutputRefreshContext(is_8bpc_out_ref), resource_(resource) {}

    ID3D12Resource* resource_uav_capable() const { return resource_.Get(); }

   private:
    Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
  };

  static std::unique_ptr<D3D12Presenter> Create(HostGpuLossCallback host_gpu_loss_callback,
                                                const D3D12Provider& provider) {
    auto presenter =
        std::unique_ptr<D3D12Presenter>(new D3D12Presenter(host_gpu_loss_callback, provider));
    if (!presenter->InitializeSurfaceIndependent()) {
      return nullptr;
    }
    return presenter;
  }

  ~D3D12Presenter();

  const D3D12Provider& provider() const { return provider_; }

  Surface::TypeFlags GetSupportedSurfaceTypes() const override;

  bool CaptureGuestOutput(RawImage& image_out) override;

  void AwaitUISubmissionCompletionFromUIThread(UINT64 submission_index) {
    ui_submission_tracker_.AwaitSubmissionCompletion(submission_index);
  }

 protected:
  SurfacePaintConnectResult ConnectOrReconnectPaintingToSurfaceFromUIThread(
      Surface& new_surface, uint32_t new_surface_width, uint32_t new_surface_height,
      bool was_paintable, bool& is_vsync_implicit_out) override;
  void DisconnectPaintingFromSurfaceFromUIThreadImpl() override;

  bool RefreshGuestOutputImpl(uint32_t mailbox_index, uint32_t frontbuffer_width,
                              uint32_t frontbuffer_height,
                              std::function<bool(GuestOutputRefreshContext& context)> refresher,
                              bool& is_8bpc_out) override;

  PaintResult PaintAndPresentImpl(bool execute_ui_drawers) override;

 private:
  struct GuestOutputPaintRectangleConstants {
    union {
      struct {
        float x;
        float y;
      };
      float offset[2];
    };
    union {
      struct {
        float width;
        float height;
      };
      float size[2];
    };
  };

  enum class GuestOutputPaintRootParameter : UINT {
    kSource,
    kRectangle,
    kEffectConstants,

    kCount,
  };

  enum GuestOutputPaintRootSignatureIndex : size_t {
    kGuestOutputPaintRootSignatureIndexBilinear,
#if defined(REX_HAS_FIDELITYFX_SDK)
    kGuestOutputPaintRootSignatureIndexCasSharpen,
    kGuestOutputPaintRootSignatureIndexCasResample,
    kGuestOutputPaintRootSignatureIndexFsrEasu,
    kGuestOutputPaintRootSignatureIndexFsrRcas,
#endif

    kGuestOutputPaintRootSignatureCount,
  };

  static constexpr GuestOutputPaintRootSignatureIndex GetGuestOutputPaintRootSignatureIndex(
      GuestOutputPaintEffect effect) {
    switch (effect) {
      case GuestOutputPaintEffect::kBilinear:
      case GuestOutputPaintEffect::kBilinearDither:
        return kGuestOutputPaintRootSignatureIndexBilinear;
#if defined(REX_HAS_FIDELITYFX_SDK)
      case GuestOutputPaintEffect::kCasSharpen:
      case GuestOutputPaintEffect::kCasSharpenDither:
        return kGuestOutputPaintRootSignatureIndexCasSharpen;
      case GuestOutputPaintEffect::kCasResample:
      case GuestOutputPaintEffect::kCasResampleDither:
        return kGuestOutputPaintRootSignatureIndexCasResample;
      case GuestOutputPaintEffect::kFsrEasu:
        return kGuestOutputPaintRootSignatureIndexFsrEasu;
      case GuestOutputPaintEffect::kFsrRcas:
      case GuestOutputPaintEffect::kFsrRcasDither:
        return kGuestOutputPaintRootSignatureIndexFsrRcas;
#endif
      default:
        assert_unhandled_case(effect);
        return kGuestOutputPaintRootSignatureCount;
    }
  }

  struct PaintContext {
    explicit PaintContext() = default;
    PaintContext(const PaintContext& paint_context) = delete;
    PaintContext& operator=(const PaintContext& paint_context) = delete;

    static constexpr uint32_t kSwapChainBufferCount = 3;

    enum RTVIndex : UINT {

      kRTVIndexSwapChainBuffer0,

      kRTVIndexGuestOutputIntermediate0 = kRTVIndexSwapChainBuffer0 + kSwapChainBufferCount,

      kRTVCount = kRTVIndexGuestOutputIntermediate0 + kGuestOutputMailboxSize - 1,
    };

    enum ViewIndex : UINT {

      kViewIndexGuestOutput0Srv,

      kViewIndexGuestOutputIntermediate0Srv = kViewIndexGuestOutput0Srv + kGuestOutputMailboxSize,

      kViewCount = kViewIndexGuestOutputIntermediate0Srv + kMaxGuestOutputPaintEffects - 1,
    };

    void AwaitSwapChainUsageCompletion() {
      present_submission_tracker.AwaitAllSubmissionsCompletion();

      paint_submission_tracker.AwaitAllSubmissionsCompletion();
    }

    void DestroySwapChain();

    D3D12SubmissionTracker paint_submission_tracker;

    D3D12SubmissionTracker present_submission_tracker;

    std::array<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>, kSwapChainBufferCount>
        command_allocators;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap;

    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> view_heap;

    std::array<std::pair<UINT64, Microsoft::WRL::ComPtr<ID3D12Resource>>, kGuestOutputMailboxSize>
        guest_output_resource_paint_refs;

    std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kMaxGuestOutputPaintEffects - 1>
        guest_output_intermediate_textures;
    UINT64 guest_output_intermediate_texture_last_usage = 0;

    uint32_t swap_chain_width = 0;
    uint32_t swap_chain_height = 0;
    bool swap_chain_allows_tearing = false;
    Microsoft::WRL::ComPtr<IDXGISwapChain3> swap_chain;
    std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, kSwapChainBufferCount> swap_chain_buffers;
  };

  explicit D3D12Presenter(HostGpuLossCallback host_gpu_loss_callback, const D3D12Provider& provider)
      : Presenter(host_gpu_loss_callback), provider_(provider) {}

  bool dxgi_supports_tearing() const { return dxgi_supports_tearing_; }

  bool InitializeSurfaceIndependent();

#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
  bool EnsureTemporalUpscalerContext(uint32_t render_width, uint32_t render_height,
                                     uint32_t output_width, uint32_t output_height);
  bool DispatchTemporalUpscaler(ID3D12GraphicsCommandList* command_list,
                                ID3D12Resource* input_resource, uint32_t input_width,
                                uint32_t input_height, ID3D12Resource* output_resource,
                                uint32_t output_width, uint32_t output_height,
                                const GuestOutputPaintConfig& config);
  void DestroyTemporalUpscalerContext();
#endif

  const D3D12Provider& provider_;

  bool dxgi_supports_tearing_ = false;

  std::array<Microsoft::WRL::ComPtr<ID3D12RootSignature>, kGuestOutputPaintRootSignatureCount>
      guest_output_paint_root_signatures_;
  std::array<Microsoft::WRL::ComPtr<ID3D12PipelineState>, size_t(GuestOutputPaintEffect::kCount)>
      guest_output_paint_intermediate_pipelines_;
  std::array<Microsoft::WRL::ComPtr<ID3D12PipelineState>, size_t(GuestOutputPaintEffect::kCount)>
      guest_output_paint_final_pipelines_;

  std::array<std::pair<UINT64, Microsoft::WRL::ComPtr<ID3D12Resource>>, kGuestOutputMailboxSize>
      guest_output_resources_;

  D3D12SubmissionTracker guest_output_resource_refresher_submission_tracker_;

  D3D12SubmissionTracker ui_submission_tracker_;

  PaintContext paint_context_;

#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
  void* temporal_upscaler_context_ = nullptr;
  uint32_t temporal_upscaler_max_render_width_ = 0;
  uint32_t temporal_upscaler_max_render_height_ = 0;
  uint32_t temporal_upscaler_max_output_width_ = 0;
  uint32_t temporal_upscaler_max_output_height_ = 0;
  bool temporal_upscaler_provider_logged_ = false;
#endif
};

}
