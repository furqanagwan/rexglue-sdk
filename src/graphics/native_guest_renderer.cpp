/**
 * Native renderer registry. Ported from the Skate 3 recompilation's SDK
 * (github.com/mchughalex/rexglue-skate3, BSD-3-Clause); the Skate 3 pass
 * selection became SetNativeGuestOutputPassFilter.
 */

#include <rex/graphics/native_guest_renderer.h>

#include <algorithm>
#include <atomic>
#include <string>

#include <rex/cvar.h>

// Defined here (shared TU) rather than in a backend's command_processor.cpp
// so both D3D12 and Vulkan see the same definition.
REXCVAR_DEFINE_BOOL(native_render_suppress_emulated_draws, true, "GPU",
                    "While the registered native guest-output renderer is actively "
                    "replacing frames, skip emulated draw and resolve execution in the "
                    "command processor (PM4 parsing, fences, queries and memexport draws "
                    "still run). Menus/pause yield to the emulated path and execute "
                    "normally.")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_INT32(native_render_suppress_mode, 0, "GPU",
                     "Which emulated passes to suppress while the native guest-output "
                     "renderer is active and the game registered no pass filter. 0 = "
                     "framebuffer-sized passes only (surface pitch >= 1280); smaller "
                     "render-to-texture passes still run, so anything the renderer reads "
                     "back from guest memory stays correct. 1 = suppress every pass "
                     "(performance probing; breaks such readbacks).")
    .range(0, 1)
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(native_render_suppress_exempt_depth_only, true, "GPU",
                    "Within the suppression-EXEMPT passes (see "
                    "native_render_suppress_mode), also skip draws with no pixel shader "
                    "(depth/stencil-only: shadow-map casters, z-prepasses). Their output "
                    "feeds only the suppressed scene passes; the native renderer builds "
                    "its own shadows, and on Vulkan this stream is the dominant "
                    "remaining emulated GPU cost. Disable if a composition pass the "
                    "renderer samples depth/stencil-tests against its own no-PS lay-down.")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

namespace rex::graphics {
namespace {

std::atomic<NativeGuestOutputRenderer> g_renderer{nullptr};
std::atomic<void*> g_renderer_user_data{nullptr};
// True while the registered renderer actually replaced the last presented
// frame (false when it yields: menus, early-outs, no renderer).
std::atomic<bool> g_native_output_active{false};
std::atomic<NativeGuestOutputPostProcessor> g_post_processor{nullptr};
std::atomic<void*> g_post_processor_user_data{nullptr};
std::atomic<bool> g_post_process_requested{false};

}  // namespace

void SetNativeGuestOutputRenderer(NativeGuestOutputRenderer renderer, void* user_data) {
  g_renderer_user_data.store(user_data, std::memory_order_release);
  g_renderer.store(renderer, std::memory_order_release);
}

bool TryRenderNativeGuestOutput(const NativeGuestOutputRenderContext& context) {
  NativeGuestOutputRenderer renderer = g_renderer.load(std::memory_order_acquire);
  if (renderer == nullptr) {
    g_native_output_active.store(false, std::memory_order_relaxed);
    return false;
  }
  void* user_data = g_renderer_user_data.load(std::memory_order_acquire);
  const bool rendered = renderer(context, user_data);
  g_native_output_active.store(rendered, std::memory_order_relaxed);
  return rendered;
}

bool HasNativeGuestOutputRenderer() {
  return g_renderer.load(std::memory_order_acquire) != nullptr;
}

void SetNativeGuestOutputPostProcessor(NativeGuestOutputPostProcessor post_processor,
                                       void* user_data) {
  g_post_processor_user_data.store(user_data, std::memory_order_release);
  g_post_processor.store(post_processor, std::memory_order_release);
}

bool HasNativeGuestOutputPostProcessor() {
  return g_post_processor.load(std::memory_order_acquire) != nullptr;
}

void InvokeNativeGuestOutputPostProcessor(const NativeGuestOutputRenderContext& context) {
  NativeGuestOutputPostProcessor post_processor =
      g_post_processor.load(std::memory_order_acquire);
  if (post_processor == nullptr) {
    return;
  }
  post_processor(context, g_post_processor_user_data.load(std::memory_order_acquire));
}

void RequestNativeGuestOutputPostProcess(bool requested) {
  g_post_process_requested.store(requested, std::memory_order_release);
}

bool IsNativeGuestOutputPostProcessRequested() {
  return g_post_process_requested.load(std::memory_order_acquire);
}

bool IsNativeGuestOutputActive() {
  return g_native_output_active.load(std::memory_order_relaxed);
}

namespace {
std::atomic<double> g_wide_aspect{0.0};
}  // namespace

void SetNativeGuestOutputWideAspect(double aspect) {
  g_wide_aspect.store(aspect > 0.0 ? aspect : 0.0, std::memory_order_relaxed);
}

double GetNativeGuestOutputWideAspect() {
  return g_wide_aspect.load(std::memory_order_relaxed);
}

bool ApplyNativeGuestOutputWideAspect(uint32_t& guest_output_width, uint32_t guest_output_height,
                                      uint32_t& display_width, uint32_t& display_height) {
  const double aspect = g_wide_aspect.load(std::memory_order_relaxed);
  if (aspect <= 0.0 || !guest_output_width || !guest_output_height ||
      !HasNativeGuestOutputRenderer() ||
      !g_native_output_active.load(std::memory_order_relaxed)) {
    return false;
  }
  // Even width keeps every half-resolution derived target (bloom, SSAO,
  // menu snapshots) an exact divide.
  uint32_t wide_width =
      uint32_t(std::clamp(aspect * double(guest_output_height) + 0.5, 1.0, 16384.0)) & ~1u;
  if (wide_width <= guest_output_width) {
    return false;
  }
  guest_output_width = wide_width;
  // The display aspect is the actual pixel aspect: the presenter maps the
  // wide image edge-to-edge on a matching window.
  display_width = guest_output_width;
  display_height = guest_output_height;
  return true;
}

bool ShouldSuppressEmulatedDraws() {
  return REXCVAR_GET(native_render_suppress_emulated_draws) &&
         g_native_output_active.load(std::memory_order_relaxed);
}

bool ShouldSuppressExemptDepthOnlyDraws() {
  return REXCVAR_GET(native_render_suppress_exempt_depth_only);
}

namespace {
std::atomic<NativeGuestOutputPassFilter> g_pass_filter{nullptr};
std::atomic<void*> g_pass_filter_user_data{nullptr};
}  // namespace

void SetNativeGuestOutputPassFilter(NativeGuestOutputPassFilter filter, void* user_data) {
  g_pass_filter_user_data.store(user_data, std::memory_order_release);
  g_pass_filter.store(filter, std::memory_order_release);
}

bool ShouldSuppressPassAtPitch(uint32_t surface_pitch) {
  if (NativeGuestOutputPassFilter filter = g_pass_filter.load(std::memory_order_acquire)) {
    return filter(surface_pitch, g_pass_filter_user_data.load(std::memory_order_acquire));
  }
  return REXCVAR_GET(native_render_suppress_mode) == 1 || surface_pitch >= 1280;
}

}  // namespace rex::graphics

namespace rex::graphics::nrhi {
namespace {

// Set once during app startup before any CreateShader (see native_rhi.h);
// lives in this shared TU so every backend reads the same value.
std::string g_shader_bytecode_cache_dir;

}  // namespace

void SetShaderBytecodeCacheDirectory(const char* path) {
  g_shader_bytecode_cache_dir = path != nullptr ? path : "";
}

const char* GetShaderBytecodeCacheDirectory() {
  return g_shader_bytecode_cache_dir.c_str();
}

}  // namespace rex::graphics::nrhi
