/**
 * @file        native_guest_renderer_test.cpp
 * @brief       Unit tests for the native renderer registry
 *
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/native_guest_renderer.h>

using namespace rex::graphics;

namespace {

bool RenderIfAsked(const NativeGuestOutputRenderContext&, void* user_data) {
  return *static_cast<bool*>(user_data);
}

bool KeepPitch512(uint32_t surface_pitch, void*) {
  return surface_pitch != 512;
}

}  // namespace

TEST_CASE("No renderer leaves emulation in charge", "[native_render]") {
  SetNativeGuestOutputRenderer(nullptr, nullptr);
  CHECK_FALSE(HasNativeGuestOutputRenderer());
  CHECK_FALSE(TryRenderNativeGuestOutput({}));
  CHECK_FALSE(IsNativeGuestOutputActive());
  CHECK_FALSE(ShouldSuppressEmulatedDraws());

  uint32_t width = 1280, display_width = 1280, display_height = 720;
  SetNativeGuestOutputWideAspect(21.0 / 9.0);
  CHECK_FALSE(ApplyNativeGuestOutputWideAspect(width, 720, display_width, display_height));
  CHECK(width == 1280);
  SetNativeGuestOutputWideAspect(0.0);
}

TEST_CASE("A renderer that yields keeps emulated draws", "[native_render]") {
  bool render = false;
  SetNativeGuestOutputRenderer(RenderIfAsked, &render);
  CHECK(HasNativeGuestOutputRenderer());
  CHECK_FALSE(TryRenderNativeGuestOutput({}));
  CHECK_FALSE(ShouldSuppressEmulatedDraws());

  render = true;
  CHECK(TryRenderNativeGuestOutput({}));
  CHECK(IsNativeGuestOutputActive());
  CHECK(ShouldSuppressEmulatedDraws());

  // Ultrawide only applies while the renderer serves frames.
  uint32_t width = 1280, display_width = 1280, display_height = 720;
  SetNativeGuestOutputWideAspect(21.0 / 9.0);
  CHECK(ApplyNativeGuestOutputWideAspect(width, 720, display_width, display_height));
  CHECK(width == 1680);
  CHECK(display_width == 1680);
  SetNativeGuestOutputWideAspect(0.0);

  SetNativeGuestOutputRenderer(nullptr, nullptr);
  CHECK_FALSE(TryRenderNativeGuestOutput({}));
}

TEST_CASE("Pass suppression defaults to framebuffer passes, games can override",
          "[native_render]") {
  SetNativeGuestOutputPassFilter(nullptr, nullptr);
  CHECK(ShouldSuppressPassAtPitch(1280));
  CHECK_FALSE(ShouldSuppressPassAtPitch(1024));

  SetNativeGuestOutputPassFilter(KeepPitch512, nullptr);
  CHECK(ShouldSuppressPassAtPitch(1024));
  CHECK_FALSE(ShouldSuppressPassAtPitch(512));
  SetNativeGuestOutputPassFilter(nullptr, nullptr);
}
