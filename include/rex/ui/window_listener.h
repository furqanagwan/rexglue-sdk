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

#include <rex/ui/ui_event.h>

namespace rex {
namespace ui {

class WindowListener {
 public:
  virtual ~WindowListener() = default;

  virtual void OnOpened(UISetupEvent&) {}
  virtual void OnClosing(UIEvent&) {}

  virtual bool OnCloseRequested(UIEvent&) { return true; }

  virtual void OnMinimized(UIEvent&) {}
  virtual void OnRestored(UIEvent&) {}

  virtual void OnDpiChanged(UISetupEvent&) {}
  virtual void OnResize(UISetupEvent&) {}

  virtual void OnGotFocus(UISetupEvent&) {}
  virtual void OnLostFocus(UISetupEvent&) {}

  virtual void OnFileDrop(FileDropEvent&) {}
};

class WindowInputListener {
 public:
  virtual ~WindowInputListener() = default;

  virtual void OnKeyDown(KeyEvent&) {}
  virtual void OnKeyUp(KeyEvent&) {}
  virtual void OnKeyChar(KeyEvent&) {}

  virtual void OnMouseDown(MouseEvent&) {}
  virtual void OnMouseMove(MouseEvent&) {}
  virtual void OnMouseUp(MouseEvent&) {}
  virtual void OnMouseWheel(MouseEvent&) {}

  virtual void OnTouchEvent(TouchEvent&) {}
};

}
}
