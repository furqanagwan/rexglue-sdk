#pragma once
/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <functional>
#include <optional>
#include <string>

#include <rex/ppc/function.h>
#include <rex/system/export_resolver.h>
#include <rex/system/kernel_module.h>
#include <rex/system/kernel_state.h>

namespace rex::ui {
class ImGuiDialog;
}  // namespace rex::ui

namespace rex {
namespace kernel {
namespace xam {

bool xeXamIsUIActive();

/// Counts host system UI (the Xbox guide) as on screen for XamIsUIActive,
/// as XAM's own dialogs are counted.
void xeXamAddSystemUI();
void xeXamRemoveSystemUI();

/// A title's request for text (XamShowKeyboardUI).
struct KeyboardRequest {
  uint32_t user_index = 0;
  uint32_t flags = 0;  // VKBD_* modes, as the title passed them
  std::u16string title, description, default_text;
  size_t max_length = 0;  // characters, without the terminator
};
/// Shows a keyboard on the UI thread and returns it (a dialog that deletes
/// itself once closed), calling `done` with the text, or nothing when
/// cancelled, before it closes; null when it cannot show one.
using KeyboardDone = std::function<void(std::optional<std::u16string>)>;
using KeyboardProvider =
    std::function<rex::ui::ImGuiDialog*(const KeyboardRequest&, KeyboardDone done)>;
/// The console's own keyboard (RG-GDK-059), which XamShowKeyboardUI uses
/// ahead of the SDK's ImGui dialog. Empty to unset.
void xeXamSetKeyboardProvider(KeyboardProvider provider);

class XamModule : public system::KernelModule {
 public:
  XamModule(Runtime* emulator, system::KernelState* kernel_state);
  virtual ~XamModule();

  static void RegisterExportTable(rex::runtime::ExportResolver* export_resolver);

  struct LoaderData {
    bool launch_data_present = false;
    std::vector<uint8_t> launch_data;
    uint32_t launch_flags = 0;
    std::string launch_path;  // Full path to next xex
  };

  const LoaderData& loader_data() const { return loader_data_; }
  LoaderData& loader_data() { return loader_data_; }

 private:
  LoaderData loader_data_;
};

}  // namespace xam
}  // namespace kernel
}  // namespace rex
