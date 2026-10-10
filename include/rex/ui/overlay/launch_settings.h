// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <filesystem>
#include <functional>
#include <optional>
#include <string>

#include <rex/ui/imgui_dialog.h>

namespace rex::ui {

struct LaunchPadState {
  float x = 0;
  float y = 0;
  bool activate = false;
  bool cancel = false;
  bool previous_tab = false;
  bool next_tab = false;
};
using LaunchPadSource = std::function<std::optional<LaunchPadState>()>;

LaunchPadState PollLaunchPad(ImGuiIO& io, const LaunchPadSource& source,
                             bool forward_to_imgui = true);
void ReleaseLaunchPad(ImGuiIO& io);

class LaunchSettingsDialog : public ImGuiDialog {
 public:
  LaunchSettingsDialog(ImGuiDrawer* drawer, std::string title, std::filesystem::path config_path,
                       std::function<void(bool)> completed, LaunchPadSource pad_source = {});
  ~LaunchSettingsDialog() override;

 protected:
  void OnDraw(ImGuiIO& io) override;
  void OnClose() override;

 private:
  void Toggle(const char* label, const char* flag);
  void Choice(const char* label, const char* flag, const char* const* names,
              const char* const* values, int count);
  void Set(const char* flag, const char* value);
  void PollGamepad(ImGuiIO& io);
  ImGuiTabItemFlags TabFlags(int index) const;

  std::string title_;
  std::filesystem::path config_path_;
  std::function<void(bool)> completed_;
  LaunchPadSource pad_source_;
  LaunchPadState previous_pad_;
  int selected_tab_ = 0;
  int requested_tab_ = -1;
  std::string error_;
  bool play_ = false;
  bool remember_ = true;
};

}
