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
}

namespace rex {
namespace kernel {
namespace xam {

bool xeXamIsUIActive();

void xeXamAddSystemUI();
void xeXamRemoveSystemUI();

struct KeyboardRequest {
  uint32_t user_index = 0;
  uint32_t flags = 0;
  std::u16string title, description, default_text;
  size_t max_length = 0;
};

using KeyboardDone = std::function<void(std::optional<std::u16string>)>;
using KeyboardProvider =
    std::function<rex::ui::ImGuiDialog*(const KeyboardRequest&, KeyboardDone done)>;

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
    std::string launch_path;
  };

  const LoaderData& loader_data() const { return loader_data_; }
  LoaderData& loader_data() { return loader_data_; }

 private:
  LoaderData loader_data_;
};

}
}
}
