#pragma once
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

#include <cstdint>

#include <rex/assert.h>

namespace rex {
namespace ui {

class Surface {
 public:
  enum TypeIndex {

    kTypeIndex_AndroidNativeWindow,

    kTypeIndex_WaylandSurface,
    kTypeIndex_XcbWindow,

    kTypeIndex_Win32Hwnd,

    kTypeIndex_CAMetalLayer,
  };
  using TypeFlags = uint32_t;
  enum : TypeFlags {
    kTypeFlag_AndroidNativeWindow = TypeFlags(1) << kTypeIndex_AndroidNativeWindow,
    kTypeFlag_WaylandSurface = TypeFlags(1) << kTypeIndex_WaylandSurface,
    kTypeFlag_XcbWindow = TypeFlags(1) << kTypeIndex_XcbWindow,
    kTypeFlag_Win32Hwnd = TypeFlags(1) << kTypeIndex_Win32Hwnd,
    kTypeFlag_CAMetalLayer = TypeFlags(1) << kTypeIndex_CAMetalLayer,
  };

  Surface(const Surface& surface) = delete;
  Surface& operator=(const Surface& surface) = delete;
  virtual ~Surface() = default;

  virtual TypeIndex GetType() const = 0;

  bool GetSize(uint32_t& width_out, uint32_t& height_out) {
    uint32_t width, height;
    if (!GetSizeImpl(width, height) || !width || !height) {
      width_out = 0;
      height_out = 0;
      return false;
    }
    width_out = width;
    height_out = height;
    return true;
  }

 protected:
  Surface() = default;

  virtual bool GetSizeImpl(uint32_t& width_out, uint32_t& height_out) const = 0;
};

}
}
