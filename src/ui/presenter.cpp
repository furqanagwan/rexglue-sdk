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
#include <atomic>
#include <cctype>
#include <utility>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/platform.h>
#include <rex/ui/presenter.h>
#include <rex/ui/window.h>

#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
#include <ffx_api/ffx_api.h>
#include <ffx_api/ffx_upscale.h>
#endif

REXCVAR_DEFINE_BOOL(host_present_from_non_ui_thread, true, "UI/Presenter",
                    "Allow presentation from non-UI thread");

REXCVAR_DEFINE_BOOL(present_letterbox, true, "UI/Presenter",
                    "Enable letterboxing for non-native aspect ratios");

REXCVAR_DEFINE_INT32(present_safe_area_x, 90, "UI/Presenter",
                     "Horizontal safe area percentage (0-100)")
    .range(0, 100);

REXCVAR_DEFINE_INT32(present_safe_area_y, 90, "UI/Presenter",
                     "Vertical safe area percentage (0-100)")
    .range(0, 100);

#if defined(REX_HAS_FIDELITYFX_SDK)
REXCVAR_DEFINE_STRING(present_effect, "bilinear", "UI/Presenter",
                      "Guest output effect: bilinear, cas, fsr, fsr2, fsr3")
    .allowed({"bilinear", "cas", "fsr", "fsr2", "fsr3"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_DOUBLE(present_cas_additional_sharpness,
                      rex::ui::Presenter::GuestOutputPaintConfig::kCasAdditionalSharpnessDefault,
                      "UI/Presenter", "Additional CAS sharpness in [0, 1]")
    .range(rex::ui::Presenter::GuestOutputPaintConfig::kCasAdditionalSharpnessMin,
           rex::ui::Presenter::GuestOutputPaintConfig::kCasAdditionalSharpnessMax)
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_INT32(present_fsr_max_upsampling_passes,
                     rex::ui::Presenter::GuestOutputPaintConfig::kFsrMaxUpscalingPassesMax,
                     "UI/Presenter", "Maximum chained FSR EASU passes")
    .range(1, int32_t(rex::ui::Presenter::GuestOutputPaintConfig::kFsrMaxUpscalingPassesMax))
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_DOUBLE(present_fsr_sharpness_reduction,
                      rex::ui::Presenter::GuestOutputPaintConfig::kFsrSharpnessReductionDefault,
                      "UI/Presenter", "FSR RCAS sharpness reduction in stops")
    .range(rex::ui::Presenter::GuestOutputPaintConfig::kFsrSharpnessReductionMin,
           rex::ui::Presenter::GuestOutputPaintConfig::kFsrSharpnessReductionMax)
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_STRING(
    present_fsr_quality_mode, "auto", "UI/Presenter",
    "Temporal FSR quality mode: auto, nativeaa, quality, balanced, performance, ultra_performance")
    .allowed({"auto", "nativeaa", "quality", "balanced", "performance", "ultra_performance"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);
#else
REXCVAR_DEFINE_STRING(present_effect, "bilinear", "UI/Presenter", "Guest output effect: bilinear")
    .allowed({"bilinear"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);
#endif

REXCVAR_DEFINE_BOOL(present_dither, false, "UI/Presenter",
                    "Enable output dithering in the final present pass")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_BOOL(present_allow_overscan_cutoff, false, "UI/Presenter",
                    "Allow overscan cutoff based on safe area settings")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

namespace {
using GuestOutputPaintConfig = rex::ui::Presenter::GuestOutputPaintConfig;

GuestOutputPaintConfig::Effect ParsePresentEffect(const std::string& effect_name) {
  std::string lowered = effect_name;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                 [](unsigned char c) { return char(std::tolower(c)); });
#if defined(REX_HAS_FIDELITYFX_SDK)
  if (lowered == "cas") {
    return GuestOutputPaintConfig::Effect::kCas;
  }
  if (lowered == "fsr") {
    return GuestOutputPaintConfig::Effect::kFsr;
  }
  if (lowered == "fsr2") {
    return GuestOutputPaintConfig::Effect::kFsr2;
  }
  if (lowered == "fsr3") {
    return GuestOutputPaintConfig::Effect::kFsr3;
  }
#endif
  return GuestOutputPaintConfig::Effect::kBilinear;
}

#if defined(REX_HAS_FIDELITYFX_SDK)
bool IsTemporalFsrCompatibilityEffect(GuestOutputPaintConfig::Effect effect) {
  return effect == GuestOutputPaintConfig::Effect::kFsr2 ||
         effect == GuestOutputPaintConfig::Effect::kFsr3;
}

GuestOutputPaintConfig::FsrQualityMode ParsePresentFsrQualityMode(const std::string& mode_name) {
  std::string lowered = mode_name;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) {
    c = static_cast<unsigned char>(std::tolower(c));
    return c == '-' ? '_' : char(c);
  });
  if (lowered == "nativeaa" || lowered == "native_aa" || lowered == "native") {
    return GuestOutputPaintConfig::FsrQualityMode::kNativeAa;
  }
  if (lowered == "quality") {
    return GuestOutputPaintConfig::FsrQualityMode::kQuality;
  }
  if (lowered == "balanced") {
    return GuestOutputPaintConfig::FsrQualityMode::kBalanced;
  }
  if (lowered == "performance") {
    return GuestOutputPaintConfig::FsrQualityMode::kPerformance;
  }
  if (lowered == "ultra_performance" || lowered == "ultra") {
    return GuestOutputPaintConfig::FsrQualityMode::kUltraPerformance;
  }
  return GuestOutputPaintConfig::FsrQualityMode::kAuto;
}

bool GetFsrQualityModeApiValue(GuestOutputPaintConfig::FsrQualityMode mode,
                               uint32_t& api_mode_out) {
  switch (mode) {
    case GuestOutputPaintConfig::FsrQualityMode::kAuto:
      return false;
    case GuestOutputPaintConfig::FsrQualityMode::kNativeAa:
#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
      api_mode_out = FFX_UPSCALE_QUALITY_MODE_NATIVEAA;
#else
      api_mode_out = 0;
#endif
      return true;
    case GuestOutputPaintConfig::FsrQualityMode::kQuality:
#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
      api_mode_out = FFX_UPSCALE_QUALITY_MODE_QUALITY;
#else
      api_mode_out = 1;
#endif
      return true;
    case GuestOutputPaintConfig::FsrQualityMode::kBalanced:
#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
      api_mode_out = FFX_UPSCALE_QUALITY_MODE_BALANCED;
#else
      api_mode_out = 2;
#endif
      return true;
    case GuestOutputPaintConfig::FsrQualityMode::kPerformance:
#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
      api_mode_out = FFX_UPSCALE_QUALITY_MODE_PERFORMANCE;
#else
      api_mode_out = 3;
#endif
      return true;
    case GuestOutputPaintConfig::FsrQualityMode::kUltraPerformance:
#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
      api_mode_out = FFX_UPSCALE_QUALITY_MODE_ULTRA_PERFORMANCE;
#else
      api_mode_out = 4;
#endif
      return true;
  }
  return false;
}

float GetFsrQualityModeRatioFallback(GuestOutputPaintConfig::FsrQualityMode mode) {
  switch (mode) {
    case GuestOutputPaintConfig::FsrQualityMode::kNativeAa:
      return 1.0f;
    case GuestOutputPaintConfig::FsrQualityMode::kQuality:
      return 1.5f;
    case GuestOutputPaintConfig::FsrQualityMode::kBalanced:
      return 1.7f;
    case GuestOutputPaintConfig::FsrQualityMode::kPerformance:
      return 2.0f;
    case GuestOutputPaintConfig::FsrQualityMode::kUltraPerformance:
      return 3.0f;
    case GuestOutputPaintConfig::FsrQualityMode::kAuto:
    default:
      return 1.0f;
  }
}

bool QueryTemporalFsrRenderResolutionFromQualityMode(uint32_t display_width,
                                                     uint32_t display_height,
                                                     GuestOutputPaintConfig::FsrQualityMode mode,
                                                     uint32_t& render_width_out,
                                                     uint32_t& render_height_out) {
  uint32_t api_mode = 0;
  if (!GetFsrQualityModeApiValue(mode, api_mode)) {
    return false;
  }

#if defined(REX_HAS_FIDELITYFX_RUNTIME) && REX_HAS_FIDELITYFX_RUNTIME
  ffxQueryDescUpscaleGetRenderResolutionFromQualityMode query_desc = {};
  query_desc.header.type = FFX_API_QUERY_DESC_TYPE_UPSCALE_GETRENDERRESOLUTIONFROMQUALITYMODE;
  query_desc.header.pNext = nullptr;
  query_desc.displayWidth = display_width;
  query_desc.displayHeight = display_height;
  query_desc.qualityMode = api_mode;
  query_desc.pOutRenderWidth = &render_width_out;
  query_desc.pOutRenderHeight = &render_height_out;
  if (ffxQuery(nullptr, &query_desc.header) == FFX_API_RETURN_OK && render_width_out &&
      render_height_out) {
    return true;
  }
#endif

  float ratio = GetFsrQualityModeRatioFallback(mode);
  render_width_out = std::max(uint32_t(1), uint32_t(float(display_width) / ratio + 0.5f));
  render_height_out = std::max(uint32_t(1), uint32_t(float(display_height) / ratio + 0.5f));
  return true;
}

void LogTemporalFsrCompatibilityPathOnce() {
  static std::atomic<bool> temporal_fsr_compatibility_logged = false;
  if (!temporal_fsr_compatibility_logged.exchange(true)) {
    REXLOG_WARN(
        "present_effect=fsr2/fsr3 uses an experimental temporal upscaler path "
        "with synthesized depth/motion inputs and may fall back to spatial FSR");
  }
}

void LogTemporalFsrQualityModeInputLimitOnce() {
  static std::atomic<bool> temporal_fsr_quality_mode_input_limit_logged = false;
  if (!temporal_fsr_quality_mode_input_limit_logged.exchange(true)) {
    REXLOG_WARN(
        "present_fsr_quality_mode requested a render size larger than the "
        "guest output; using guest output size");
  }
}
#endif

GuestOutputPaintConfig BuildGuestOutputPaintConfigFromCVar() {
  GuestOutputPaintConfig config;
  GuestOutputPaintConfig::Effect parsed_effect = ParsePresentEffect(REXCVAR_GET(present_effect));
#if defined(REX_HAS_FIDELITYFX_SDK)
  if (IsTemporalFsrCompatibilityEffect(parsed_effect)) {
    LogTemporalFsrCompatibilityPathOnce();
  }
#endif
  config.SetAllowOverscanCutoff(REXCVAR_GET(present_allow_overscan_cutoff));
  config.SetEffect(parsed_effect);
#if defined(REX_HAS_FIDELITYFX_SDK)
  config.SetCasAdditionalSharpness(float(REXCVAR_GET(present_cas_additional_sharpness)));
  config.SetFsrMaxUpsamplingPasses(
      uint32_t(std::max(int32_t(1), REXCVAR_GET(present_fsr_max_upsampling_passes))));
  config.SetFsrSharpnessReduction(float(REXCVAR_GET(present_fsr_sharpness_reduction)));
  config.SetFsrQualityMode(ParsePresentFsrQualityMode(REXCVAR_GET(present_fsr_quality_mode)));
#endif
  config.SetDither(REXCVAR_GET(present_dither));
  return config;
}

}

namespace rex {
namespace ui {

void Presenter::FatalErrorHostGpuLossCallback([[maybe_unused]] bool is_responsible,
                                              [[maybe_unused]] bool statically_from_ui_thread) {
  rex::FatalError("Graphics device lost (probably due to an internal error)");
}

Presenter::~Presenter() {
  assert_false(is_executing_ui_drawers_);

  if (dxgi_ui_tick_thread_.joinable()) {
    {
      std::scoped_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
      dxgi_ui_tick_thread_shutdown_ = true;
    }
    dxgi_ui_tick_control_condition_.notify_all();
    dxgi_ui_tick_thread_.join();
  }

  if (window_) {
    Window* old_window = window_;

    window_ = nullptr;
    old_window->SetPresenter(nullptr);
  }
}

void Presenter::SetWindowSurfaceFromUIThread(Window* new_window, Surface* new_surface) {
  assert_false(is_executing_ui_drawers_);

  assert_false(new_surface && !new_window);

  if (window_ == new_window && (!window_ || surface_ == new_surface)) {
    return;
  }

  if (surface_) {
    SetPaintModeFromUIThread(PaintMode::kNone);
    DisconnectPaintingFromSurfaceFromUIThread(
        SurfacePaintConnectionState::kUnconnectedRetryAtStateChange);
    surface_ = nullptr;
    UpdateSurfaceMonitorFromUIThread(true);
  }

  if (window_ != new_window) {
    if (window_) {
      Window* old_window = window_;

      window_ = nullptr;
      old_window->SetPresenter(nullptr);
    }

    window_ = new_window;
  }

  if (new_surface) {
    assert_true(paint_mode_ == PaintMode::kNone);
    surface_ = new_surface;
    UpdateSurfaceMonitorFromUIThread(true);
    assert_true(surface_paint_connection_state_ ==
                SurfacePaintConnectionState::kUnconnectedRetryAtStateChange);
    bool request_repaint;
    UpdateSurfacePaintConnectionFromUIThread(&request_repaint, true);

    if (request_repaint) {
      RequestPaintOrConnectionRecoveryViaWindow(true);
    }
  }
}

void Presenter::OnSurfaceMonitorUpdateFromUIThread(bool old_monitor_potentially_disconnected) {
  assert_false(is_executing_ui_drawers_);

  if (!surface_) {
    return;
  }

  UpdateSurfaceMonitorFromUIThread(old_monitor_potentially_disconnected);
}

void Presenter::OnSurfaceResizeFromUIThread() {
  assert_false(is_executing_ui_drawers_);

  if (!surface_) {
    return;
  }

  if (paint_mode_ == PaintMode::kGuestOutputThreadImmediately) {
    SetPaintModeFromUIThread(PaintMode::kUIThreadOnRequest);
  }

  bool request_repaint;
  UpdateSurfacePaintConnectionFromUIThread(&request_repaint, true);

  if (request_repaint) {
    RequestPaintOrConnectionRecoveryViaWindow(true);
  }
}

void Presenter::PaintFromUIThread(bool force_paint) {
  if (!InSurfaceOnMonitorFromUIThread()) {
    return;
  }

  assert_false(is_in_ui_thread_paint_);
  is_in_ui_thread_paint_ = true;
  request_guest_output_paint_after_current_ui_thread_paint_ = false;
  request_ui_paint_after_current_ui_thread_paint_ = false;

  bool draw_ui = !ui_drawers_.empty();
  bool do_paint = force_paint || draw_ui;

  if (ui_thread_paint_requested_.exchange(false, std::memory_order_relaxed)) {
    do_paint = true;
  }
  PaintResult paint_result = PaintResult::kNotPresented;
  bool request_repaint_at_tick = false;
  bool request_repaint_immediately = false;
  if (do_paint) {
    if (paint_mode_ == PaintMode::kGuestOutputThreadImmediately) {
      SetPaintModeFromUIThread(PaintMode::kUIThreadOnRequest);
    }

    if (surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedOutdated) {
      UpdateSurfacePaintConnectionFromUIThread(nullptr, false);
    }

    if (surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedPaintable) {
      SetPaintModeFromUIThread(PaintMode::kUIThreadOnRequest);

      WaitForUITickFromUIThread();

      paint_result = PaintAndPresent(draw_ui);
      if (surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedOutdated) {
        request_repaint_immediately = true;
      }
    }

    if (surface_paint_connection_state_ != SurfacePaintConnectionState::kConnectedPaintable) {
      SetPaintModeFromUIThread(PaintMode::kNone);
    }
  }

  if (paint_mode_ != PaintMode::kNone) {
    SetPaintModeFromUIThread(GetDesiredPaintModeFromUIThread(true));
  }
  is_in_ui_thread_paint_ = false;

  if (paint_result == PaintResult::kGpuLostExternally ||
      paint_result == PaintResult::kGpuLostResponsible) {
    if (host_gpu_loss_callback_) {
      host_gpu_loss_callback_(paint_result == PaintResult::kGpuLostResponsible, true);
    }

    return;
  }

  if (paint_mode_ != PaintMode::kNone) {
    if (request_guest_output_paint_after_current_ui_thread_paint_ ||
        (draw_ui && ui_drawers_.empty())) {
      request_repaint_immediately = true;
    }
    if (request_ui_paint_after_current_ui_thread_paint_ && !ui_drawers_.empty()) {
      request_repaint_at_tick = true;
    }
  }
  if (request_repaint_at_tick || request_repaint_immediately) {
    RequestPaintOrConnectionRecoveryViaWindow(request_repaint_immediately);
  }
}

bool Presenter::RefreshGuestOutput(
    uint32_t frontbuffer_width, uint32_t frontbuffer_height, uint32_t display_aspect_ratio_x,
    uint32_t display_aspect_ratio_y,
    std::function<bool(GuestOutputRefreshContext& context)> refresher) {
  GuestOutputProperties& writable_properties =
      guest_output_properties_[guest_output_mailbox_writable_];
  writable_properties.frontbuffer_width = frontbuffer_width;
  writable_properties.frontbuffer_height = frontbuffer_height;
  writable_properties.display_aspect_ratio_x = display_aspect_ratio_x;
  writable_properties.display_aspect_ratio_y = display_aspect_ratio_y;
  writable_properties.is_8bpc = false;
  bool is_active = writable_properties.IsActive();
  if (is_active) {
    if (!RefreshGuestOutputImpl(guest_output_mailbox_writable_, frontbuffer_width,
                                frontbuffer_height, refresher, writable_properties.is_8bpc)) {
      return false;
    }
    guest_output_active_last_refresh_ = true;
  } else {
    if (!guest_output_active_last_refresh_) {
      return false;
    }
    guest_output_active_last_refresh_ = false;
  }

  uint32_t last_acquired_and_ready =
      guest_output_mailbox_acquired_and_ready_.load(std::memory_order_relaxed);

  while (!guest_output_mailbox_acquired_and_ready_.compare_exchange_weak(
      last_acquired_and_ready,
      (last_acquired_and_ready & 3) | (guest_output_mailbox_writable_ << 2),
      std::memory_order_acq_rel, std::memory_order_relaxed)) {}

  uint32_t last_acquired = last_acquired_and_ready & 3;
  if (last_acquired == guest_output_mailbox_writable_) {
    guest_output_mailbox_writable_ = (guest_output_mailbox_writable_ + 1) % 3;
  } else {
    guest_output_mailbox_writable_ = (3 - last_acquired - guest_output_mailbox_writable_) % 3;
  }

  PaintResult paint_result = PaintResult::kNotPresented;
  {
    std::lock_guard<std::mutex> paint_mode_mutex_lock(paint_mode_mutex_);
    switch (paint_mode_) {
      case PaintMode::kNone:

        break;
      case PaintMode::kUIThreadOnRequest:

        RequestPaintOrConnectionRecoveryViaWindow(true);
        break;
      case PaintMode::kGuestOutputThreadImmediately:

        if (surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedPaintable) {
          paint_result = PaintAndPresent(false);
          if (surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedOutdated) {
            RequestPaintOrConnectionRecoveryViaWindow(true);
          }
        }
        break;
    }
  }

  if (host_gpu_loss_callback_) {
    if (paint_result == PaintResult::kGpuLostResponsible) {
      host_gpu_loss_callback_(true, false);
    } else if (paint_result == PaintResult::kGpuLostExternally) {
      host_gpu_loss_callback_(false, false);
    }
  }

  return is_active;
}

void Presenter::SetGuestOutputPaintConfigFromUIThread(const GuestOutputPaintConfig& new_config) {
  bool modified = false;
  bool request_repaint = false;
  if (guest_output_paint_config_.GetEffect() != new_config.GetEffect()) {
    modified = true;
    request_repaint = true;
  }
#if defined(REX_HAS_FIDELITYFX_SDK)
  if (guest_output_paint_config_.GetFsrSharpnessReduction() !=
      new_config.GetFsrSharpnessReduction()) {
    modified = true;
    if (new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr ||
        new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr2 ||
        new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr3) {
      request_repaint = true;
    }
  }
  if (guest_output_paint_config_.GetCasAdditionalSharpness() !=
      new_config.GetCasAdditionalSharpness()) {
    modified = true;
    if (new_config.GetEffect() == GuestOutputPaintConfig::Effect::kCas ||
        new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr ||
        new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr2 ||
        new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr3) {
      request_repaint = true;
    }
  }
#endif
  if (guest_output_paint_config_.GetDither() != new_config.GetDither()) {
    modified = true;
    request_repaint = true;
  }
#if defined(REX_HAS_FIDELITYFX_SDK)
  if (guest_output_paint_config_.GetFsrQualityMode() != new_config.GetFsrQualityMode()) {
    modified = true;
    if (new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr2 ||
        new_config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr3) {
      request_repaint = true;
    }
  }
#endif
  if (modified) {
    {
      std::unique_lock<std::mutex> config_lock(guest_output_paint_config_mutex_);
      guest_output_paint_config_ = new_config;
    }

    if (request_repaint && paint_mode_ != PaintMode::kNone) {
      if (is_in_ui_thread_paint_) {
        request_guest_output_paint_after_current_ui_thread_paint_ = true;
      } else {
        RequestPaintOrConnectionRecoveryViaWindow(true);
      }
    }
  }
}

void Presenter::AddUIDrawerFromUIThread(UIDrawer* drawer, size_t z_order) {
  assert_not_null(drawer);

  bool drawers_were_empty = ui_drawers_.empty();
  uint64_t drawer_last_draw = UINT64_MAX;

  for (auto it_existing = ui_drawers_.begin(); it_existing != ui_drawers_.end(); ++it_existing) {
    if (it_existing->second.drawer != drawer) {
      continue;
    }
    if (it_existing->first == z_order) {
      return;
    }

    drawer_last_draw = it_existing->second.last_draw;

    if (is_executing_ui_drawers_ && ui_draw_next_iterator_ == it_existing) {
      ++ui_draw_next_iterator_;
    }
    ui_drawers_.erase(it_existing);
    break;
  }
  auto it_new = ui_drawers_.emplace(z_order, UIDrawerReference(drawer, drawer_last_draw));

  if (is_executing_ui_drawers_ && z_order >= ui_draw_current_z_order_ &&
      (ui_draw_next_iterator_ == ui_drawers_.end() || z_order < ui_draw_next_iterator_->first)) {
    ui_draw_next_iterator_ = it_new;
  }
  HandleUIDrawersChangeFromUIThread(drawers_were_empty);
}

void Presenter::RemoveUIDrawerFromUIThread(UIDrawer* drawer) {
  assert_not_null(drawer);
  for (auto it_existing = ui_drawers_.begin(); it_existing != ui_drawers_.end(); ++it_existing) {
    if (it_existing->second.drawer != drawer) {
      continue;
    }

    if (is_executing_ui_drawers_ && ui_draw_next_iterator_ == it_existing) {
      ++ui_draw_next_iterator_;
    }
    ui_drawers_.erase(it_existing);
    HandleUIDrawersChangeFromUIThread(false);
    return;
  }
}

void Presenter::RequestUIPaintFromUIThread() {
  if (is_in_ui_thread_paint_) {
    request_ui_paint_after_current_ui_thread_paint_ = true;
    return;
  }

  if (!ui_drawers_.empty() && paint_mode_ != PaintMode::kNone) {
    window_->RequestPaint();
  }
}

bool Presenter::InitializeCommonSurfaceIndependent() {
  {
    std::lock_guard<std::mutex> config_lock(guest_output_paint_config_mutex_);
    guest_output_paint_config_ = BuildGuestOutputPaintConfigFromCVar();
  }

  dxgi_ui_tick_thread_ = std::thread(&Presenter::DXGIUITickThread, this);

  return true;
}

std::unique_lock<std::mutex> Presenter::ConsumeGuestOutput(
    uint32_t& mailbox_index_or_max_if_inactive_out, GuestOutputProperties* properties_out,
    GuestOutputPaintConfig* paint_config_out) {
  if (paint_config_out) {
    std::unique_lock<std::mutex> config_lock(guest_output_paint_config_mutex_);
    *paint_config_out = guest_output_paint_config_;
  }

  std::unique_lock<std::mutex> consumer_lock(guest_output_mailbox_consumer_mutex_);

  uint32_t old_acquired_and_ready =
      guest_output_mailbox_acquired_and_ready_.load(std::memory_order_relaxed);

  uint32_t desired_acquired_and_ready =
      (old_acquired_and_ready & ~uint32_t(3)) | (old_acquired_and_ready >> 2);

  while (old_acquired_and_ready != desired_acquired_and_ready &&
         !guest_output_mailbox_acquired_and_ready_.compare_exchange_weak(
             old_acquired_and_ready, desired_acquired_and_ready, std::memory_order_acq_rel,
             std::memory_order_relaxed)) {
    desired_acquired_and_ready =
        (old_acquired_and_ready & ~uint32_t(3)) | (old_acquired_and_ready >> 2);
  }
  uint32_t mailbox_index = desired_acquired_and_ready & 3;

  const GuestOutputProperties& properties = guest_output_properties_[mailbox_index];
  mailbox_index_or_max_if_inactive_out = properties.IsActive() ? mailbox_index : UINT32_MAX;
  if (properties_out) {
    *properties_out = properties;
  }
  return std::move(consumer_lock);
}

Presenter::GuestOutputPaintFlow Presenter::GetGuestOutputPaintFlow(
    const GuestOutputProperties& properties, uint32_t host_rt_width, uint32_t host_rt_height,
    uint32_t max_rt_width, uint32_t max_rt_height, const GuestOutputPaintConfig& config) const {
  GuestOutputPaintFlow flow = {};

  assert_not_zero(max_rt_width);
  assert_not_zero(max_rt_height);

  flow.letterbox_clear_rectangle_count = 1;
  flow.letterbox_clear_rectangles[0].width = host_rt_width;
  flow.letterbox_clear_rectangles[0].height = host_rt_height;

  if (!properties.IsActive() || !host_rt_width || !host_rt_height ||
      !surface_width_in_paint_connection_ || !surface_height_in_paint_connection_) {
    return flow;
  }

  flow.properties = properties;

  auto rescale_unsigned = [](uint32_t value, uint32_t new_scale, uint32_t old_scale) -> uint32_t {
    return uint32_t((uint64_t(value) * new_scale + (old_scale >> 1)) / old_scale);
  };
  auto rescale_signed = [](int32_t value, uint32_t new_scale, uint32_t old_scale) -> int32_t {
    return int32_t((int64_t(value) * new_scale + int32_t(old_scale >> 1) * (value < 0 ? -1 : 1)) /
                   old_scale);
  };

  uint32_t output_width, output_height;
  if (uint64_t(surface_width_in_paint_connection_) * properties.display_aspect_ratio_y >
      uint64_t(surface_height_in_paint_connection_) * properties.display_aspect_ratio_x) {
    uint32_t present_safe_area;
    if (config.GetAllowOverscanCutoff() && REXCVAR_GET(present_safe_area_y) > 0 &&
        REXCVAR_GET(present_safe_area_y) < 100) {
      present_safe_area = uint32_t(REXCVAR_GET(present_safe_area_y));
    } else {
      present_safe_area = 100;
    }

    output_height =
        rescale_unsigned(surface_width_in_paint_connection_, properties.display_aspect_ratio_y,
                         properties.display_aspect_ratio_x);
    bool letterbox = false;
    if (output_height * present_safe_area > surface_height_in_paint_connection_ * 100) {
      output_height = rescale_unsigned(surface_height_in_paint_connection_, 100, present_safe_area);
      letterbox = true;
    }
    if (letterbox && REXCVAR_GET(present_letterbox)) {
      output_width = rescale_unsigned(surface_height_in_paint_connection_ * 100,
                                      properties.display_aspect_ratio_x,
                                      properties.display_aspect_ratio_y * present_safe_area);

      flow.output_x = (int32_t(surface_width_in_paint_connection_) - int32_t(output_width)) / 2;
    } else {
      output_width = surface_width_in_paint_connection_;
      flow.output_x = 0;
    }

    flow.output_y = (int32_t(surface_height_in_paint_connection_) - int32_t(output_height)) / 2;
  } else {
    uint32_t present_safe_area;
    if (config.GetAllowOverscanCutoff() && REXCVAR_GET(present_safe_area_x) > 0 &&
        REXCVAR_GET(present_safe_area_x) < 100) {
      present_safe_area = uint32_t(REXCVAR_GET(present_safe_area_x));
    } else {
      present_safe_area = 100;
    }

    output_width =
        rescale_unsigned(surface_height_in_paint_connection_, properties.display_aspect_ratio_x,
                         properties.display_aspect_ratio_y);
    bool letterbox = false;
    if (output_width * present_safe_area > surface_width_in_paint_connection_ * 100) {
      output_width = rescale_unsigned(surface_width_in_paint_connection_, 100, present_safe_area);
      letterbox = true;
    }
    if (letterbox && REXCVAR_GET(present_letterbox)) {
      output_height = rescale_unsigned(surface_width_in_paint_connection_ * 100,
                                       properties.display_aspect_ratio_y,
                                       properties.display_aspect_ratio_x * present_safe_area);

      flow.output_y = (int32_t(surface_height_in_paint_connection_) - int32_t(output_height)) / 2;
    } else {
      output_height = surface_height_in_paint_connection_;
      flow.output_y = 0;
    }

    flow.output_x = (int32_t(surface_width_in_paint_connection_) - int32_t(output_width)) / 2;
  }

  if (host_rt_width != surface_width_in_paint_connection_) {
    flow.output_x =
        rescale_signed(flow.output_x, host_rt_width, surface_width_in_paint_connection_);
    output_width =
        rescale_unsigned(output_width, host_rt_width, surface_width_in_paint_connection_);
  }
  if (host_rt_height != surface_height_in_paint_connection_) {
    flow.output_y =
        rescale_signed(flow.output_y, host_rt_height, surface_height_in_paint_connection_);
    output_height =
        rescale_unsigned(output_height, host_rt_height, surface_height_in_paint_connection_);
  }

  int32_t output_right = flow.output_x + int32_t(output_width);
  int32_t output_bottom = flow.output_y + int32_t(output_height);

  if (flow.output_x >= 0 && flow.output_y >= 0 && flow.output_x <= 1 && flow.output_y <= 1 &&
      output_width < host_rt_width && output_height < host_rt_height) {
    static std::atomic<bool> logged_top_left_expand = false;
    if (!logged_top_left_expand.exchange(true)) {
      REXLOG_WARN(
          "Presenter: expanding guest output from {}x{} to host render target "
          "{}x{} to avoid top-left-only presentation",
          output_width, output_height, host_rt_width, host_rt_height);
    }
    output_width = host_rt_width;
    output_height = host_rt_height;
    output_right = int32_t(output_width);
    output_bottom = int32_t(output_height);
  }
  if (!output_width || !output_height || output_right <= 0 || output_bottom <= 0 ||
      flow.output_x >= int32_t(host_rt_width) || flow.output_y >= int32_t(host_rt_height)) {
    return flow;
  }

  uint32_t output_width_clamped = std::min(output_width, max_rt_width);
  uint32_t output_height_clamped = std::min(output_height, max_rt_height);

#if defined(REX_HAS_FIDELITYFX_SDK)
  if (config.GetEffect() == GuestOutputPaintConfig::Effect::kCas ||
      config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr ||
      config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr2 ||
      config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr3) {
    std::pair<uint32_t, uint32_t> ffx_last_size;
    if (flow.effect_count) {
      ffx_last_size = flow.effect_output_sizes[flow.effect_count - 1];
    } else {
      ffx_last_size.first = properties.frontbuffer_width;
      ffx_last_size.second = properties.frontbuffer_height;
    }
    bool is_temporal_effect = config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr2 ||
                              config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr3;
    bool temporal_quality_mode_forced =
        is_temporal_effect &&
        config.GetFsrQualityMode() != GuestOutputPaintConfig::FsrQualityMode::kAuto;
    if ((config.GetEffect() == GuestOutputPaintConfig::Effect::kFsr || is_temporal_effect) &&
        ((ffx_last_size.first < output_width_clamped ||
          ffx_last_size.second < output_height_clamped) ||
         temporal_quality_mode_forced)) {
      if (is_temporal_effect) {
        uint32_t temporal_input_width = ffx_last_size.first;
        uint32_t temporal_input_height = ffx_last_size.second;
        uint32_t quality_mode_render_width = 0;
        uint32_t quality_mode_render_height = 0;
        if (QueryTemporalFsrRenderResolutionFromQualityMode(
                output_width_clamped, output_height_clamped, config.GetFsrQualityMode(),
                quality_mode_render_width, quality_mode_render_height)) {
          quality_mode_render_width =
              std::max(uint32_t(1), std::min(quality_mode_render_width, output_width_clamped));
          quality_mode_render_height =
              std::max(uint32_t(1), std::min(quality_mode_render_height, output_height_clamped));
          if (quality_mode_render_width < temporal_input_width ||
              quality_mode_render_height < temporal_input_height) {
            temporal_input_width = quality_mode_render_width;
            temporal_input_height = quality_mode_render_height;
            if (temporal_input_width != ffx_last_size.first ||
                temporal_input_height != ffx_last_size.second) {
              assert_true(flow.effect_count < flow.effects.size());
              flow.effect_output_sizes[flow.effect_count] =
                  std::make_pair(temporal_input_width, temporal_input_height);

              flow.effects[flow.effect_count++] = GuestOutputPaintEffect::kCasResample;
              ffx_last_size.first = temporal_input_width;
              ffx_last_size.second = temporal_input_height;
            }
          } else if (quality_mode_render_width > temporal_input_width ||
                     quality_mode_render_height > temporal_input_height) {
            LogTemporalFsrQualityModeInputLimitOnce();
          }
        }

        ffx_last_size.first = output_width_clamped;
        ffx_last_size.second = output_height_clamped;
        assert_true(flow.effect_count < flow.effects.size());
        flow.effect_output_sizes[flow.effect_count] = ffx_last_size;
        flow.effects[flow.effect_count++] = GuestOutputPaintEffect::kFsrEasu;
      } else {
        uint32_t easu_max_passes = config.GetFsrMaxUpsamplingPasses();
        uint32_t easu_pass_count = 0;
        while (easu_pass_count < easu_max_passes &&
               (ffx_last_size.first < output_width_clamped ||
                ffx_last_size.second < output_height_clamped)) {
          ffx_last_size.first = std::min(ffx_last_size.first * uint32_t(2), output_width_clamped);
          ffx_last_size.second =
              std::min(ffx_last_size.second * uint32_t(2), output_height_clamped);
          assert_true(flow.effect_count < flow.effects.size());
          flow.effect_output_sizes[flow.effect_count] = ffx_last_size;
          flow.effects[flow.effect_count++] = GuestOutputPaintEffect::kFsrEasu;
          ++easu_pass_count;
        }
      }
      assert_true(flow.effect_count < flow.effects.size());
      flow.effect_output_sizes[flow.effect_count] = ffx_last_size;
      flow.effects[flow.effect_count++] = GuestOutputPaintEffect::kFsrRcas;
    } else {
      std::pair<uint32_t, uint32_t> pre_cas_size = ffx_last_size;
      ffx_last_size.first = std::min(ffx_last_size.first * uint32_t(2), output_width);
      ffx_last_size.second = std::min(ffx_last_size.second * uint32_t(2), output_height);
      assert_true(flow.effect_count < flow.effects.size());
      flow.effect_output_sizes[flow.effect_count] = ffx_last_size;
      flow.effects[flow.effect_count++] = ffx_last_size == pre_cas_size
                                              ? GuestOutputPaintEffect::kCasSharpen
                                              : GuestOutputPaintEffect::kCasResample;
    }
  }
#endif

  std::pair<uint32_t, uint32_t>* last_pre_bilinear_effect_size =
      flow.effect_count ? &flow.effect_output_sizes[flow.effect_count - 1] : nullptr;
  if (!last_pre_bilinear_effect_size || last_pre_bilinear_effect_size->first != output_width ||
      last_pre_bilinear_effect_size->second != output_height) {
    if (last_pre_bilinear_effect_size) {
#if defined(REX_HAS_FIDELITYFX_SDK)

      assert_false(flow.effects[flow.effect_count - 1] == GuestOutputPaintEffect::kFsrRcas &&
                   (last_pre_bilinear_effect_size->first > max_rt_width ||
                    last_pre_bilinear_effect_size->second > max_rt_height));
#endif
      last_pre_bilinear_effect_size->first =
          std::min(last_pre_bilinear_effect_size->first, max_rt_width);
      last_pre_bilinear_effect_size->second =
          std::min(last_pre_bilinear_effect_size->second, max_rt_height);
    }
    assert_true(flow.effect_count < flow.effects.size());
    flow.effect_output_sizes[flow.effect_count] = std::make_pair(output_width, output_height);
    flow.effects[flow.effect_count++] = GuestOutputPaintEffect::kBilinear;
  }

  assert_not_zero(flow.effect_count);

  if (config.GetDither()) {
    GuestOutputPaintEffect& last_effect = flow.effects[flow.effect_count - 1];
    switch (last_effect) {
      case GuestOutputPaintEffect::kBilinear:

        if (!properties.is_8bpc || flow.effect_count > 1 ||
            output_width != properties.frontbuffer_width ||
            output_height != properties.frontbuffer_height) {
          last_effect = GuestOutputPaintEffect::kBilinearDither;
        }
        break;
#if defined(REX_HAS_FIDELITYFX_SDK)
      case GuestOutputPaintEffect::kCasSharpen:
        last_effect = GuestOutputPaintEffect::kCasSharpenDither;
        break;
      case GuestOutputPaintEffect::kCasResample:
        last_effect = GuestOutputPaintEffect::kCasResampleDither;
        break;
      case GuestOutputPaintEffect::kFsrRcas:
        last_effect = GuestOutputPaintEffect::kFsrRcasDither;
        break;
#endif
      default:
        break;
    }
  }

#ifndef NDEBUG
  for (size_t i = 0; i + 1 < flow.effect_count; ++i) {
    assert_true(CanGuestOutputPaintEffectBeIntermediate(flow.effects[i]));
  }
  assert_true(CanGuestOutputPaintEffectBeFinal(flow.effects[flow.effect_count - 1]));
#endif

  if (flow.effect_count) {
    flow.letterbox_clear_rectangle_count = 0;
    uint32_t letterbox_mid_top = uint32_t(std::max(flow.output_y, int32_t(0)));

    if (letterbox_mid_top) {
      assert_true(flow.letterbox_clear_rectangle_count < flow.letterbox_clear_rectangles.size());
      GuestOutputPaintFlow::ClearRectangle& letterbox_clear_rectangle_top =
          flow.letterbox_clear_rectangles[flow.letterbox_clear_rectangle_count++];
      letterbox_clear_rectangle_top.x = 0;
      letterbox_clear_rectangle_top.y = 0;
      letterbox_clear_rectangle_top.width = host_rt_width;
      letterbox_clear_rectangle_top.height = letterbox_mid_top;
    }
    uint32_t letterbox_mid_bottom = std::min(uint32_t(output_bottom), host_rt_height);
    uint32_t letterbox_mid_height = letterbox_mid_bottom - letterbox_mid_top;

    if (flow.output_x > 0) {
      assert_true(flow.letterbox_clear_rectangle_count < flow.letterbox_clear_rectangles.size());
      GuestOutputPaintFlow::ClearRectangle& letterbox_clear_rectangle_left =
          flow.letterbox_clear_rectangles[flow.letterbox_clear_rectangle_count++];
      letterbox_clear_rectangle_left.x = 0;
      letterbox_clear_rectangle_left.y = letterbox_mid_top;
      letterbox_clear_rectangle_left.width = uint32_t(flow.output_x);
      letterbox_clear_rectangle_left.height = letterbox_mid_height;
    }

    if (uint32_t(output_right) < host_rt_width) {
      assert_true(flow.letterbox_clear_rectangle_count < flow.letterbox_clear_rectangles.size());
      GuestOutputPaintFlow::ClearRectangle& letterbox_clear_rectangle_right =
          flow.letterbox_clear_rectangles[flow.letterbox_clear_rectangle_count++];
      letterbox_clear_rectangle_right.x = uint32_t(output_right);
      letterbox_clear_rectangle_right.y = letterbox_mid_top;
      letterbox_clear_rectangle_right.width = host_rt_width - uint32_t(output_right);
      letterbox_clear_rectangle_right.height = letterbox_mid_height;
    }

    if (letterbox_mid_bottom < host_rt_height) {
      assert_true(flow.letterbox_clear_rectangle_count < flow.letterbox_clear_rectangles.size());
      GuestOutputPaintFlow::ClearRectangle& letterbox_clear_rectangle_top =
          flow.letterbox_clear_rectangles[flow.letterbox_clear_rectangle_count++];
      letterbox_clear_rectangle_top.x = 0;
      letterbox_clear_rectangle_top.y = letterbox_mid_bottom;
      letterbox_clear_rectangle_top.width = host_rt_width;
      letterbox_clear_rectangle_top.height = host_rt_height - letterbox_mid_bottom;
    }
  }

  return flow;
}

void Presenter::ExecuteUIDrawersFromUIThread(UIDrawContext& ui_draw_context) {
  assert_true(is_in_ui_thread_paint_);

  assert_false(is_executing_ui_drawers_);
  ui_draw_next_iterator_ = ui_drawers_.begin();
  is_executing_ui_drawers_ = true;
  while (ui_draw_next_iterator_ != ui_drawers_.end()) {
    auto it_current = ui_draw_next_iterator_++;

    if (it_current->second.last_draw != ui_draw_current_) {
      ui_draw_current_z_order_ = it_current->first;
      it_current->second.last_draw = ui_draw_current_;
      it_current->second.drawer->Draw(ui_draw_context);
    }
  }
  is_executing_ui_drawers_ = false;
  ++ui_draw_current_;
}

void Presenter::SetPaintModeFromUIThread(PaintMode new_mode) {
  if (paint_mode_ == new_mode) {
    return;
  }
  {
    std::lock_guard<std::mutex> lock(paint_mode_mutex_);
    paint_mode_ = new_mode;
  }
  UpdateUITicksNeededFromUIThread();
}

Presenter::PaintMode Presenter::GetDesiredPaintModeFromUIThread(bool is_paintable) const {
  if (!is_paintable) {
    return PaintMode::kNone;
  }
  if (!REXCVAR_GET(host_present_from_non_ui_thread)) {
    return PaintMode::kUIThreadOnRequest;
  }
  if (surface_paint_connection_has_implicit_vsync_) {
    return PaintMode::kUIThreadOnRequest;
  }
  if (!ui_drawers_.empty()) {
    return PaintMode::kUIThreadOnRequest;
  }

  return PaintMode::kGuestOutputThreadImmediately;
}

void Presenter::DisconnectPaintingFromSurfaceFromUIThread(SurfacePaintConnectionState new_state) {
  assert_false(IsConnectedSurfacePaintConnectionState(new_state));
  if (IsConnectedSurfacePaintConnectionState(surface_paint_connection_state_)) {
    DisconnectPaintingFromSurfaceFromUIThreadImpl();
  }
  surface_paint_connection_state_ = new_state;
  surface_paint_connection_has_implicit_vsync_ = false;
  surface_width_in_paint_connection_ = 0;
  surface_height_in_paint_connection_ = 0;
}

void Presenter::UpdateSurfacePaintConnectionFromUIThread(bool* repaint_needed_out,
                                                         bool update_paint_mode_to_desired) {
  assert_not_null(surface_);

  assert_true(paint_mode_ != PaintMode::kGuestOutputThreadImmediately);

  if (repaint_needed_out) {
    *repaint_needed_out = false;
  }

  if (surface_paint_connection_state_ !=
      SurfacePaintConnectionState::kUnconnectedSurfaceReportedUnusable) {
    uint32_t surface_width = 0, surface_height = 0;
    bool surface_area_available = surface_->GetSize(surface_width, surface_height);
    if (!surface_area_available) {
      DisconnectPaintingFromSurfaceFromUIThread(
          SurfacePaintConnectionState::kUnconnectedRetryAtStateChange);
    } else {
      bool is_reconnect = IsConnectedSurfacePaintConnectionState(surface_paint_connection_state_);
      bool is_vsync_implicit = false;
      SurfacePaintConnectResult connect_result = ConnectOrReconnectPaintingToSurfaceFromUIThread(
          *surface_, surface_width, surface_height,
          surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedPaintable,
          is_vsync_implicit);
      switch (connect_result) {
        case SurfacePaintConnectResult::kSuccess:
          if (repaint_needed_out) {
            *repaint_needed_out = true;
          }

        case SurfacePaintConnectResult::kSuccessUnchanged:

          surface_paint_connection_was_optimal_at_successful_paint_ = false;
          surface_paint_connection_state_ = SurfacePaintConnectionState::kConnectedPaintable;
          surface_paint_connection_has_implicit_vsync_ = is_vsync_implicit;
          surface_width_in_paint_connection_ = surface_width;
          surface_height_in_paint_connection_ = surface_height;
          if (!is_reconnect) {
            *repaint_needed_out = true;
          }
          break;
        case SurfacePaintConnectResult::kFailure:
          surface_paint_connection_state_ =
              SurfacePaintConnectionState::kUnconnectedRetryAtStateChange;
          break;
        case SurfacePaintConnectResult::kFailureSurfaceUnusable:
          surface_paint_connection_state_ =
              SurfacePaintConnectionState::kUnconnectedSurfaceReportedUnusable;
          break;
      }
    }
  }

  if (update_paint_mode_to_desired) {
    SetPaintModeFromUIThread(GetDesiredPaintModeFromUIThread(
        surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedPaintable));
  }
}

bool Presenter::RequestPaintOrConnectionRecoveryViaWindow(bool force_ui_thread_paint_tick) {
  assert_not_null(window_);
  assert_not_null(surface_);
  if (ui_thread_paint_requested_.exchange(true, std::memory_order_relaxed)) {
    return false;
  }
  if (force_ui_thread_paint_tick) {
    ForceUIThreadPaintTick();
  }
  window_->RequestPaint();
  return true;
}

void Presenter::UpdateSurfaceMonitorFromUIThread(bool old_monitor_potentially_disconnected) {
  HMONITOR surface_new_win32_monitor = nullptr;
  if (surface_) {
    HWND hwnd = static_cast<HWND>(window_->GetNativeWindowHandle());

    if (hwnd) {
      surface_new_win32_monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONULL);
    }
  }
  if (old_monitor_potentially_disconnected || surface_win32_monitor_ != surface_new_win32_monitor) {
    surface_win32_monitor_ = surface_new_win32_monitor;
    if (dxgi_ui_tick_factory_ && !dxgi_ui_tick_factory_->IsCurrent()) {
      {
        Microsoft::WRL::ComPtr<IDXGIOutput> old_factory_output_to_release;
        {
          std::scoped_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
          old_factory_output_to_release = std::move(dxgi_ui_tick_output_);
        }
      }
      dxgi_ui_tick_factory_.Reset();
    }
    if (!dxgi_ui_tick_factory_) {
      if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgi_ui_tick_factory_)))) {
        REXLOG_ERROR("Presenter: Failed to create a DXGI factory");
      }
    }
    Microsoft::WRL::ComPtr<IDXGIOutput> new_dxgi_output;
    if (dxgi_ui_tick_factory_ && surface_new_win32_monitor) {
      new_dxgi_output =
          GetDXGIOutputForMonitor(dxgi_ui_tick_factory_.Get(), surface_new_win32_monitor);
    }

    bool signal_dxgi_ui_tick_control;
    {
      std::unique_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
      bool dxgi_output_was_null = (dxgi_ui_tick_output_ == nullptr);
      dxgi_ui_tick_output_ = new_dxgi_output;
      signal_dxgi_ui_tick_control =
          dxgi_output_was_null && AreDXGIUITicksWaitable(dxgi_ui_tick_lock);
    }
    if (signal_dxgi_ui_tick_control) {
      dxgi_ui_tick_control_condition_.notify_all();
    }
  }
}

bool Presenter::InSurfaceOnMonitorFromUIThread() const {
  if (!surface_) {
    return false;
  }
  return surface_win32_monitor_ != nullptr;
}

Presenter::PaintResult Presenter::PaintAndPresent(bool execute_ui_drawers) {
  assert_false(execute_ui_drawers && !is_in_ui_thread_paint_);
  assert_true(surface_paint_connection_state_ == SurfacePaintConnectionState::kConnectedPaintable);
  PaintResult result = PaintAndPresentImpl(execute_ui_drawers);
  switch (result) {
    case PaintResult::kPresented:
      surface_paint_connection_was_optimal_at_successful_paint_ = true;
      break;
    case PaintResult::kPresentedSuboptimal:

      if (surface_paint_connection_was_optimal_at_successful_paint_) {
        surface_paint_connection_state_ = SurfacePaintConnectionState::kConnectedOutdated;
      }
      break;
    case PaintResult::kNotPresentedConnectionOutdated:
      surface_paint_connection_state_ = SurfacePaintConnectionState::kConnectedOutdated;
      break;
    default:

      break;
  }
  return result;
}

void Presenter::HandleUIDrawersChangeFromUIThread(bool drawers_were_empty) {
  if (is_in_ui_thread_paint_) {
    if (!ui_drawers_.empty()) {
      request_ui_paint_after_current_ui_thread_paint_ = true;
    }
    return;
  }

  if (paint_mode_ == PaintMode::kNone) {
    return;
  }

  if (ui_drawers_.empty() != drawers_were_empty) {
    SetPaintModeFromUIThread(GetDesiredPaintModeFromUIThread(true));

    UpdateUITicksNeededFromUIThread();
  }

  ForceUIThreadPaintTick();
  window_->RequestPaint();
}

void Presenter::UpdateUITicksNeededFromUIThread() {
  bool new_needed = AreUITicksNeededFromUIThread();
  if (dxgi_ui_ticks_needed_ == new_needed) {
    return;
  }
  bool signal_dxgi_ui_tick_control;
  {
    std::unique_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
    dxgi_ui_ticks_needed_ = new_needed;
    signal_dxgi_ui_tick_control = AreDXGIUITicksWaitable(dxgi_ui_tick_lock);
  }
  if (signal_dxgi_ui_tick_control) {
    dxgi_ui_tick_control_condition_.notify_all();
  }
}

void Presenter::WaitForUITickFromUIThread() {
  if (!AreUITicksNeededFromUIThread()) {
    return;
  }
  std::unique_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
  uint64_t last_vblank_before_wait = dxgi_ui_tick_last_vblank_;
  while (true) {
    if (dxgi_ui_tick_force_requested_) {
      dxgi_ui_tick_force_requested_ = false;
      return;
    }
    if (!AreDXGIUITicksWaitable(dxgi_ui_tick_lock)) {
      return;
    }
    if (dxgi_ui_tick_last_vblank_ > dxgi_ui_tick_last_draw_) {
      dxgi_ui_tick_last_draw_ =
          std::min(last_vblank_before_wait + uint64_t(1), dxgi_ui_tick_last_vblank_);
      return;
    }
    dxgi_ui_tick_signal_condition_.wait(dxgi_ui_tick_lock);
  }
}

void Presenter::ForceUIThreadPaintTick() {
  std::scoped_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
  dxgi_ui_tick_force_requested_ = true;
}

Microsoft::WRL::ComPtr<IDXGIOutput> Presenter::GetDXGIOutputForMonitor(IDXGIFactory1* factory,
                                                                       HMONITOR monitor) {
  Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
  for (UINT adapter_index = 0;
       SUCCEEDED(factory->EnumAdapters(adapter_index, adapter.ReleaseAndGetAddressOf()));
       ++adapter_index) {
    Microsoft::WRL::ComPtr<IDXGIOutput> output;
    for (UINT output_index = 0; SUCCEEDED(adapter->EnumOutputs(output_index, &output));
         ++output_index) {
      DXGI_OUTPUT_DESC output_desc;
      if (SUCCEEDED(output->GetDesc(&output_desc)) && output_desc.Monitor == monitor) {
        return std::move(output);
      }
    }
  }
  return nullptr;
}

void Presenter::DXGIUITickThread() {
  std::unique_lock<std::mutex> dxgi_ui_tick_lock(dxgi_ui_tick_mutex_);
  while (true) {
    if (dxgi_ui_tick_thread_shutdown_) {
      return;
    }
    if (!AreDXGIUITicksWaitable(dxgi_ui_tick_lock)) {
      dxgi_ui_tick_control_condition_.wait(dxgi_ui_tick_lock);
      continue;
    }

    bool wait_succeeded;
    {
      Microsoft::WRL::ComPtr<IDXGIOutput> dxgi_output = dxgi_ui_tick_output_;
      dxgi_ui_tick_lock.unlock();
      wait_succeeded = SUCCEEDED(dxgi_ui_tick_output_->WaitForVBlank());
    }
    dxgi_ui_tick_lock.lock();
    if (wait_succeeded) {
      ++dxgi_ui_tick_last_vblank_;
    } else {
      dxgi_ui_tick_output_.Reset();
    }
    dxgi_ui_tick_signal_condition_.notify_all();
  }
}

}
}
