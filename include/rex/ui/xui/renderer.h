/**
 * @file        rex/ui/xui/renderer.h
 * @brief       Draws live XUI elements onto an ImGui draw list (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <functional>
#include <string_view>

#include <imgui.h>

namespace rex::ui::xui {

class Element;

// Text style bits, read from the skin's named label visuals (docs/xbox-guide.md).
enum TextStyleFlags : uint32_t {
  kTextBold = 0x0001,
  kTextNoWrap = 0x0010,
  kTextRight = 0x0200,
  kTextCenter = 0x0400,
  kTextVerticalCenter = 0x1000,
  kTextEllipsis = 0x4000,
};

/// XUI point sizes to scene units. Measured against a 1080p capture of the
/// dashboard 2.0.17559 guide, where "Xbox Home" stands 24 of its row's 61
/// pixels (RG-GDK-043); the earlier 1.2, from the scenes' proportions alone,
/// drew text a quarter too small.
constexpr float kPointToSceneUnits = 1.6f;

struct RenderResources {
  /// Texture for a scene image path, resolved against `package`. Returns an
  /// empty ImTextureRef when missing and sets the image's pixel size.
  std::function<ImTextureID(std::string_view path, std::string_view package, int* width,
                            int* height)>
      texture;
  ImFont* regular_font = nullptr;
  ImFont* bold_font = nullptr;
  /// Draws an image path as vectors instead of its texture, so it stays sharp
  /// at any resolution. `to_screen` maps the image element's own units.
  /// Returns false to draw the path as usual.
  std::function<bool(ImDrawList& list, std::string_view path,
                     const std::function<ImVec2(ImVec2)>& to_screen, float opacity)>
      vector_image;
};

/// Draws `root` with scene unit (x, y) at screen (origin + scale * (x, y)).
void Render(ImDrawList* list, const Element& root, ImVec2 origin, float scale, float opacity,
            const RenderResources& resources);

}  // namespace rex::ui::xui
