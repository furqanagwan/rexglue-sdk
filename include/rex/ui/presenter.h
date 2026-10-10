#pragma once
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
#include <array>
#include <atomic>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/math.h>
#include <rex/platform.h>
#include <rex/types.h>
#include <rex/ui/flags.h>
#include <rex/ui/surface.h>
#include <rex/ui/ui_drawer.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <dxgi.h>
#include <windows.h>

#include <wrl/client.h>

namespace rex {
namespace ui {

class Presenter;
class Window;

class UIDrawContext {
 public:
  UIDrawContext(const UIDrawContext& context) = delete;
  UIDrawContext& operator=(const UIDrawContext& context) = delete;
  virtual ~UIDrawContext() = default;

  Presenter* presenter_or_null() const { return presenter_; }

  uint32_t render_target_width() const { return render_target_width_; }
  uint32_t render_target_height() const { return render_target_height_; }

 protected:
  explicit UIDrawContext(Presenter& presenter, uint32_t render_target_width,
                         uint32_t render_target_height)
      : presenter_(&presenter),
        render_target_width_(render_target_width),
        render_target_height_(render_target_height) {}

  explicit UIDrawContext(uint32_t render_target_width, uint32_t render_target_height)
      : presenter_(nullptr),
        render_target_width_(render_target_width),
        render_target_height_(render_target_height) {}

 private:
  Presenter* presenter_;
  uint32_t render_target_width_;
  uint32_t render_target_height_;
};

class AppUIDrawContext : public UIDrawContext {
 public:
  AppUIDrawContext(uint32_t render_target_width, uint32_t render_target_height)
      : UIDrawContext(render_target_width, render_target_height) {}
};

struct RawImage {
  uint32_t width = 0;
  uint32_t height = 0;
  size_t stride = 0;

  std::vector<uint8_t> data;
};

class Presenter {
 public:
  using HostGpuLossCallback =
      std::function<void(bool is_responsible, bool statically_from_ui_thread)>;
  static void FatalErrorHostGpuLossCallback(bool is_responsible, bool statically_from_ui_thread);

  class GuestOutputRefreshContext {
   public:
    GuestOutputRefreshContext(const GuestOutputRefreshContext& context) = delete;
    GuestOutputRefreshContext& operator=(const GuestOutputRefreshContext& context) = delete;
    virtual ~GuestOutputRefreshContext() = default;

    void SetIs8bpc(bool is_8bpc) { is_8bpc_out_ref_ = is_8bpc; }

   protected:
    GuestOutputRefreshContext(bool& is_8bpc_out_ref) : is_8bpc_out_ref_(is_8bpc_out_ref) {
      is_8bpc_out_ref = false;
    }

   private:
    bool& is_8bpc_out_ref_;
  };

  class GuestOutputPaintConfig {
   public:
    enum class Effect {
      kBilinear,
#if defined(REX_HAS_FIDELITYFX_SDK)
      kCas,

      kFsr,

      kFsr2,

      kFsr3,
#endif
    };

#if defined(REX_HAS_FIDELITYFX_SDK)
    enum class FsrQualityMode {

      kAuto,
      kNativeAa,
      kQuality,
      kBalanced,
      kPerformance,
      kUltraPerformance,
    };

    static constexpr float kCasAdditionalSharpnessMin = 0.0f;
    static constexpr float kCasAdditionalSharpnessMax = 1.0f;
    static constexpr float kCasAdditionalSharpnessDefault = 0.0f;
    static_assert(kCasAdditionalSharpnessDefault >= kCasAdditionalSharpnessMin &&
                  kCasAdditionalSharpnessDefault <= kCasAdditionalSharpnessMax);

    static constexpr uint32_t kFsrMaxUpscalingPassesMax = 4;

    static constexpr float kFsrSharpnessReductionMin = 0.0f;

    static constexpr float kFsrSharpnessReductionMax = 2.0f;
    static constexpr float kFsrSharpnessReductionDefault = 0.2f;
    static_assert(kFsrSharpnessReductionDefault >= kFsrSharpnessReductionMin &&
                  kFsrSharpnessReductionDefault <= kFsrSharpnessReductionMax);
#endif

    bool GetAllowOverscanCutoff() const { return allow_overscan_cutoff_; }
    void SetAllowOverscanCutoff(bool new_allow_overscan_cutoff) {
      allow_overscan_cutoff_ = new_allow_overscan_cutoff;
    }

    Effect GetEffect() const { return effect_; }
    void SetEffect(Effect new_effect) { effect_ = new_effect; }

#if defined(REX_HAS_FIDELITYFX_SDK)
    float GetCasAdditionalSharpness() const { return cas_additional_sharpness_; }
    void SetCasAdditionalSharpness(float new_cas_additional_sharpness) {
      cas_additional_sharpness_ =
          std::min(kCasAdditionalSharpnessMax,
                   std::max(kCasAdditionalSharpnessMin, new_cas_additional_sharpness));
    }

    uint32_t GetFsrMaxUpsamplingPasses() const { return fsr_max_upsampling_passes_; }
    void SetFsrMaxUpsamplingPasses(uint32_t new_fsr_max_upsampling_passes) {
      fsr_max_upsampling_passes_ =
          std::min(kFsrMaxUpscalingPassesMax, std::max(uint32_t(1), new_fsr_max_upsampling_passes));
    }

    float GetFsrSharpnessReduction() const { return fsr_sharpness_reduction_; }
    void SetFsrSharpnessReduction(float new_fsr_sharpness_reduction) {
      fsr_sharpness_reduction_ =
          std::min(kFsrSharpnessReductionMax,
                   std::max(kFsrSharpnessReductionMin, new_fsr_sharpness_reduction));
    }

    FsrQualityMode GetFsrQualityMode() const { return fsr_quality_mode_; }
    void SetFsrQualityMode(FsrQualityMode new_fsr_quality_mode) {
      fsr_quality_mode_ = new_fsr_quality_mode;
    }
#endif

    bool GetDither() const { return dither_; }
    void SetDither(bool new_dither) { dither_ = new_dither; }

   private:
    bool allow_overscan_cutoff_ = false;
    Effect effect_ = Effect::kBilinear;
#if defined(REX_HAS_FIDELITYFX_SDK)
    float cas_additional_sharpness_ = kCasAdditionalSharpnessDefault;
    uint32_t fsr_max_upsampling_passes_ = kFsrMaxUpscalingPassesMax;
    float fsr_sharpness_reduction_ = kFsrSharpnessReductionDefault;
    FsrQualityMode fsr_quality_mode_ = FsrQualityMode::kAuto;
#endif
    bool dither_ = false;
  };

  Presenter(const Presenter& presenter) = delete;
  Presenter& operator=(const Presenter& presenter) = delete;
  virtual ~Presenter();

  virtual Surface::TypeFlags GetSupportedSurfaceTypes() const = 0;

  void SetWindowSurfaceFromUIThread(Window* new_window, Surface* new_surface);
  void OnSurfaceMonitorUpdateFromUIThread(bool old_monitor_potentially_disconnected);
  void OnSurfaceResizeFromUIThread();

  void PaintFromUIThread(bool force_paint = false);

  bool RefreshGuestOutput(uint32_t frontbuffer_width, uint32_t frontbuffer_height,
                          uint32_t display_aspect_ratio_x, uint32_t display_aspect_ratio_y,
                          std::function<bool(GuestOutputRefreshContext& context)> refresher);

  virtual bool CaptureGuestOutput(RawImage& image_out) = 0;
  const GuestOutputPaintConfig& GetGuestOutputPaintConfigFromUIThread() const {
    return guest_output_paint_config_;
  }

  void SetGuestOutputPaintConfigFromUIThread(const GuestOutputPaintConfig& new_config);

  void AddUIDrawerFromUIThread(UIDrawer* drawer, size_t z_order);
  void RemoveUIDrawerFromUIThread(UIDrawer* drawer);

  void RequestUIPaintFromUIThread();

 protected:
  enum class PaintResult {
    kPresented,
    kPresentedSuboptimal,

    kNotPresented,
    kNotPresentedConnectionOutdated,
    kGpuLostExternally,
    kGpuLostResponsible,
  };

  enum class SurfacePaintConnectResult {

    kSuccessUnchanged,
    kSuccess,
    kFailure,
    kFailureSurfaceUnusable,
  };

  static constexpr uint32_t kGuestOutputMailboxSize = 3;

  struct GuestOutputProperties {
    uint32_t frontbuffer_width;
    uint32_t frontbuffer_height;

    uint32_t display_aspect_ratio_x;
    uint32_t display_aspect_ratio_y;
    bool is_8bpc;

    GuestOutputProperties() { SetToInactive(); }

    bool IsActive() const {
      return frontbuffer_width && frontbuffer_height && display_aspect_ratio_x &&
             display_aspect_ratio_y;
    }

    void SetToInactive() {
      frontbuffer_width = 0;
      frontbuffer_height = 0;
      display_aspect_ratio_x = 0;
      display_aspect_ratio_y = 0;
      is_8bpc = false;
    }
  };

  enum class GuestOutputPaintEffect {
    kBilinear,
    kBilinearDither,
#if defined(REX_HAS_FIDELITYFX_SDK)
    kCasSharpen,
    kCasSharpenDither,
    kCasResample,
    kCasResampleDither,
    kFsrEasu,
    kFsrRcas,
    kFsrRcasDither,
#endif

    kCount,
  };

  static constexpr bool CanGuestOutputPaintEffectBeIntermediate(GuestOutputPaintEffect effect) {
    switch (effect) {
      case GuestOutputPaintEffect::kBilinear:

      case GuestOutputPaintEffect::kBilinearDither:
#if defined(REX_HAS_FIDELITYFX_SDK)
      case GuestOutputPaintEffect::kCasSharpenDither:
      case GuestOutputPaintEffect::kCasResampleDither:
      case GuestOutputPaintEffect::kFsrRcasDither:
#endif
        return false;
      default:

        return true;
    };
  }

  static constexpr bool CanGuestOutputPaintEffectBeFinal(GuestOutputPaintEffect effect) {
    switch (effect) {
#if defined(REX_HAS_FIDELITYFX_SDK)
      case GuestOutputPaintEffect::kFsrEasu:
        return false;
#endif
      default:
        return true;
    };
  }

#if defined(REX_HAS_FIDELITYFX_SDK)

  static constexpr size_t kMaxGuestOutputPaintEffects =
      GuestOutputPaintConfig::kFsrMaxUpscalingPassesMax + 2;
#else

  static constexpr size_t kMaxGuestOutputPaintEffects = 1;
#endif

  struct GuestOutputPaintFlow {
    static constexpr size_t kMaxClearRectangles = 4;

    struct ClearRectangle {
      uint32_t x;
      uint32_t y;
      uint32_t width;
      uint32_t height;
    };

    GuestOutputProperties properties;

    size_t effect_count;
    std::array<GuestOutputPaintEffect, kMaxGuestOutputPaintEffects> effects;
    std::array<std::pair<uint32_t, uint32_t>, kMaxGuestOutputPaintEffects> effect_output_sizes;

    int32_t output_x;
    int32_t output_y;

    size_t letterbox_clear_rectangle_count;
    std::array<ClearRectangle, kMaxClearRectangles> letterbox_clear_rectangles;

    void GetEffectInputSize(size_t effect_index, uint32_t& width_out, uint32_t& height_out) const {
      assert_true(effect_index < effect_count);
      if (!effect_index) {
        width_out = properties.frontbuffer_width;
        height_out = properties.frontbuffer_height;
        return;
      }
      const std::pair<uint32_t, uint32_t>& intermediate_size =
          effect_output_sizes[effect_index - 1];
      width_out = intermediate_size.first;
      height_out = intermediate_size.second;
    }

    void GetEffectOutputOffset(size_t effect_index, int32_t& x_out, int32_t& y_out) const {
      assert_true(effect_index < effect_count);
      if (effect_index + 1 < effect_count) {
        x_out = 0;
        y_out = 0;
        return;
      }
      x_out = output_x;
      y_out = output_y;
    }
  };

  struct BilinearConstants {
    int32_t output_offset[2];
    float output_size_inv[2];

    void Initialize(const GuestOutputPaintFlow& flow, size_t effect_index) {
      flow.GetEffectOutputOffset(effect_index, output_offset[0], output_offset[1]);
      const std::pair<uint32_t, uint32_t>& output_size = flow.effect_output_sizes[effect_index];
      output_size_inv[0] = 1.0f / float(output_size.first);
      output_size_inv[1] = 1.0f / float(output_size.second);
    }
  };

#if defined(REX_HAS_FIDELITYFX_SDK)
  static constexpr float CalculateCasPostSetupSharpness(float sharpness) {
    return -1.0f / (8.0f - 3.0f * sharpness);
  }

  struct CasSharpenConstants {
    int32_t output_offset[2];
    float sharpness_post_setup;

    void Initialize(const GuestOutputPaintFlow& flow, size_t effect_index,
                    const GuestOutputPaintConfig& config) {
      flow.GetEffectOutputOffset(effect_index, output_offset[0], output_offset[1]);
      sharpness_post_setup = CalculateCasPostSetupSharpness(config.GetCasAdditionalSharpness());
    }
  };

  struct CasResampleConstants {
    int32_t output_offset[2];

    float input_output_size_ratio[2];
    float sharpness_post_setup;

    void Initialize(const GuestOutputPaintFlow& flow, size_t effect_index,
                    const GuestOutputPaintConfig& config) {
      flow.GetEffectOutputOffset(effect_index, output_offset[0], output_offset[1]);
      uint32_t input_width, input_height;
      flow.GetEffectInputSize(effect_index, input_width, input_height);
      const std::pair<uint32_t, uint32_t>& output_size = flow.effect_output_sizes[effect_index];
      input_output_size_ratio[0] = float(input_width) / float(output_size.first);
      input_output_size_ratio[1] = float(input_height) / float(output_size.second);
      sharpness_post_setup = CalculateCasPostSetupSharpness(config.GetCasAdditionalSharpness());
    }
  };

  struct FsrEasuConstants {
    float input_output_size_ratio[2];
    float input_size_inv[2];

    void Initialize(const GuestOutputPaintFlow& flow, size_t effect_index) {
      uint32_t input_width, input_height;
      flow.GetEffectInputSize(effect_index, input_width, input_height);
      const std::pair<uint32_t, uint32_t>& output_size = flow.effect_output_sizes[effect_index];
      input_output_size_ratio[0] = float(input_width) / float(output_size.first);
      input_output_size_ratio[1] = float(input_height) / float(output_size.second);
      input_size_inv[0] = 1.0f / float(input_width);
      input_size_inv[1] = 1.0f / float(input_height);
    }
  };

  struct FsrRcasConstants {
    int32_t output_offset[2];
    float sharpness_post_setup;

    static float CalculatePostSetupSharpness(float sharpness_reduction_stops) {
      return std::exp2f(-sharpness_reduction_stops);
    }

    void Initialize(const GuestOutputPaintFlow& flow, size_t effect_index,
                    const GuestOutputPaintConfig& config) {
      flow.GetEffectOutputOffset(effect_index, output_offset[0], output_offset[1]);
      sharpness_post_setup = CalculatePostSetupSharpness(config.GetFsrSharpnessReduction());
    }
  };
#endif

  explicit Presenter(HostGpuLossCallback host_gpu_loss_callback)
      : host_gpu_loss_callback_(host_gpu_loss_callback) {}

  bool InitializeCommonSurfaceIndependent();

  virtual SurfacePaintConnectResult ConnectOrReconnectPaintingToSurfaceFromUIThread(
      Surface& new_surface, uint32_t new_surface_width, uint32_t new_surface_height,
      bool was_paintable, bool& is_vsync_implicit_out) = 0;

  virtual void DisconnectPaintingFromSurfaceFromUIThreadImpl() = 0;

  [[nodiscard]] std::unique_lock<std::mutex> ConsumeGuestOutput(
      uint32_t& mailbox_index_or_max_if_inactive_out, GuestOutputProperties* properties_out,
      GuestOutputPaintConfig* paint_config_out);

  GuestOutputPaintFlow GetGuestOutputPaintFlow(const GuestOutputProperties& properties,
                                               uint32_t host_rt_width, uint32_t host_rt_height,
                                               uint32_t max_rt_width, uint32_t max_rt_height,
                                               const GuestOutputPaintConfig& config) const;

  virtual bool RefreshGuestOutputImpl(
      uint32_t mailbox_index, uint32_t frontbuffer_width, uint32_t frontbuffer_height,
      std::function<bool(GuestOutputRefreshContext& context)> refresher, bool& is_8bpc_out_ref) = 0;

  static uint32_t Packed10bpcRGBTo8bpcBytes(uint32_t rgb10) {
    if constexpr (std::endian::native == std::endian::big) {
      return (uint32_t(float(rgb10 & 0x3FF) * (255.0f / 1023.0f) + 0.5f) << 24) |
             (uint32_t(float((rgb10 >> 10) & 0x3FF) * (255.0f / 1023.0f) + 0.5f) << 16) |
             (uint32_t(float((rgb10 >> 20) & 0x3FF) * (255.0f / 1023.0f) + 0.5f) << 8) |
             uint32_t(0xFF);
    }
    return uint32_t(float(rgb10 & 0x3FF) * (255.0f / 1023.0f) + 0.5f) |
           (uint32_t(float((rgb10 >> 10) & 0x3FF) * (255.0f / 1023.0f) + 0.5f) << 8) |
           (uint32_t(float((rgb10 >> 20) & 0x3FF) * (255.0f / 1023.0f) + 0.5f) << 16) |
           (uint32_t(0xFF) << 24);
  }

  virtual PaintResult PaintAndPresentImpl(bool execute_ui_drawers) = 0;

  void ExecuteUIDrawersFromUIThread(UIDrawContext& ui_draw_context);

 private:
  enum class PaintMode {

    kNone,

    kUIThreadOnRequest,

    kGuestOutputThreadImmediately,
  };

  enum class SurfacePaintConnectionState {

    kUnconnectedRetryAtStateChange,

    kUnconnectedSurfaceReportedUnusable,

    kConnectedPaintable,

    kConnectedOutdated,
  };

  static constexpr bool IsConnectedSurfacePaintConnectionState(
      SurfacePaintConnectionState connection_state) {
    return connection_state == SurfacePaintConnectionState::kConnectedPaintable ||
           connection_state == SurfacePaintConnectionState::kConnectedOutdated;
  }

  struct UIDrawerReference {
    UIDrawer* drawer;
    uint64_t last_draw;

    explicit UIDrawerReference(UIDrawer* drawer, uint64_t last_draw = UINT64_MAX)
        : drawer(drawer), last_draw(last_draw) {}
  };

  void SetPaintModeFromUIThread(PaintMode new_mode);

  PaintMode GetDesiredPaintModeFromUIThread(bool is_paintable) const;

  void UpdateSurfacePaintConnectionFromUIThread(bool* repaint_needed_out,
                                                bool update_paint_mode_to_desired);

  void DisconnectPaintingFromSurfaceFromUIThread(SurfacePaintConnectionState new_state);

  bool RequestPaintOrConnectionRecoveryViaWindow(bool force_ui_thread_paint_tick);

  void UpdateSurfaceMonitorFromUIThread(bool old_monitor_potentially_disconnected);

  bool InSurfaceOnMonitorFromUIThread() const;

  PaintResult PaintAndPresent(bool execute_ui_drawers);

  void HandleUIDrawersChangeFromUIThread(bool drawers_were_empty);

  bool AreUITicksNeededFromUIThread() const {
    return !ui_drawers_.empty() && paint_mode_ != PaintMode::kNone &&
           !surface_paint_connection_has_implicit_vsync_;
  }
  void UpdateUITicksNeededFromUIThread();
  void WaitForUITickFromUIThread();

  void ForceUIThreadPaintTick();

  HostGpuLossCallback host_gpu_loss_callback_;

  Window* window_ = nullptr;

  Surface* surface_ = nullptr;

  std::mutex paint_mode_mutex_;

  PaintMode paint_mode_ = PaintMode::kNone;

  SurfacePaintConnectionState surface_paint_connection_state_ =
      SurfacePaintConnectionState::kUnconnectedRetryAtStateChange;

  bool surface_paint_connection_was_optimal_at_successful_paint_ = false;

  bool surface_paint_connection_has_implicit_vsync_ = false;

  uint32_t surface_width_in_paint_connection_ = 0;
  uint32_t surface_height_in_paint_connection_ = 0;

  std::atomic<bool> ui_thread_paint_requested_{false};

  std::mutex guest_output_paint_config_mutex_;

  GuestOutputPaintConfig guest_output_paint_config_;

  static_assert(kGuestOutputMailboxSize == 3);

  std::atomic<uint32_t> guest_output_mailbox_acquired_and_ready_{0};

  uint32_t guest_output_mailbox_writable_ = 1;

  std::mutex guest_output_mailbox_consumer_mutex_;

  std::array<GuestOutputProperties, kGuestOutputMailboxSize> guest_output_properties_;

  bool guest_output_active_last_refresh_ = false;

  std::multimap<size_t, UIDrawerReference> ui_drawers_;

  size_t ui_draw_current_ = 0;
  size_t ui_draw_current_z_order_;
  std::multimap<size_t, UIDrawerReference>::iterator ui_draw_next_iterator_;
  bool is_executing_ui_drawers_ = false;

  bool is_in_ui_thread_paint_ = false;
  bool request_guest_output_paint_after_current_ui_thread_paint_;
  bool request_ui_paint_after_current_ui_thread_paint_;

  static Microsoft::WRL::ComPtr<IDXGIOutput> GetDXGIOutputForMonitor(IDXGIFactory1* factory,
                                                                     HMONITOR monitor);
  bool AreDXGIUITicksWaitable(
      [[maybe_unused]] const std::unique_lock<std::mutex>& dxgi_ui_tick_lock) {
    return dxgi_ui_ticks_needed_ && !dxgi_ui_tick_thread_shutdown_ && dxgi_ui_tick_output_;
  }
  void DXGIUITickThread();

  HMONITOR surface_win32_monitor_ = nullptr;

  Microsoft::WRL::ComPtr<IDXGIFactory1> dxgi_ui_tick_factory_;

  uint64_t dxgi_ui_tick_last_draw_ = 0;

  std::mutex dxgi_ui_tick_mutex_;
  uint64_t dxgi_ui_tick_last_vblank_ = 1;

  Microsoft::WRL::ComPtr<IDXGIOutput> dxgi_ui_tick_output_;

  bool dxgi_ui_ticks_needed_ = false;

  bool dxgi_ui_tick_thread_shutdown_ = false;
  bool dxgi_ui_tick_force_requested_ = false;

  std::condition_variable dxgi_ui_tick_control_condition_;

  std::condition_variable dxgi_ui_tick_signal_condition_;

  std::thread dxgi_ui_tick_thread_;
};

}
}
