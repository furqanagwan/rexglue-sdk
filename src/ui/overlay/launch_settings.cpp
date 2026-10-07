// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/ui/overlay/launch_settings.h>

#include <rex/cvar.h>
#include <rex/string/numeric.h>

#include <algorithm>
#include <cmath>

#include <imgui.h>

namespace rex::ui {

LaunchSettingsDialog::LaunchSettingsDialog(ImGuiDrawer* drawer, std::string title,
                                           std::filesystem::path config_path,
                                           std::function<void(bool)> completed,
                                           LaunchPadSource pad_source)
    : ImGuiDialog(drawer),
      title_(std::move(title)),
      config_path_(std::move(config_path)),
      completed_(std::move(completed)),
      pad_source_(std::move(pad_source)) {}

LaunchSettingsDialog::~LaunchSettingsDialog() {
  if (pad_source_) {
    auto& io = GetIO();
    io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
    for (const auto key :
         {ImGuiKey_GamepadFaceDown, ImGuiKey_GamepadFaceRight, ImGuiKey_GamepadDpadLeft,
          ImGuiKey_GamepadDpadRight, ImGuiKey_GamepadDpadUp, ImGuiKey_GamepadDpadDown}) {
      io.AddKeyEvent(key, false);
    }
  }
}

void LaunchSettingsDialog::PollGamepad(ImGuiIO& io) {
  if (!pad_source_)
    return;
  const auto pad = pad_source_();
  const auto state = pad.value_or(LaunchPadState{});
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  if (pad)
    io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
  else
    io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
  io.AddKeyEvent(ImGuiKey_GamepadFaceDown, state.activate);
  io.AddKeyEvent(ImGuiKey_GamepadFaceRight, state.cancel);
  auto direction = [&io](ImGuiKey key, float axis) {
    const float value = std::isfinite(axis) ? std::clamp((axis - 0.25f) / 0.75f, 0.0f, 1.0f) : 0;
    io.AddKeyAnalogEvent(key, value > 0, value);
  };
  direction(ImGuiKey_GamepadDpadLeft, -state.x);
  direction(ImGuiKey_GamepadDpadRight, state.x);
  direction(ImGuiKey_GamepadDpadUp, state.y);
  direction(ImGuiKey_GamepadDpadDown, -state.y);
  if (state.next_tab && !previous_pad_.next_tab)
    requested_tab_ = (selected_tab_ + 1) % 3;
  else if (state.previous_tab && !previous_pad_.previous_tab)
    requested_tab_ = (selected_tab_ + 2) % 3;
  previous_pad_ = state;
}

ImGuiTabItemFlags LaunchSettingsDialog::TabFlags(int index) const {
  return requested_tab_ == index ? ImGuiTabItemFlags_SetSelected : ImGuiTabItemFlags_None;
}

void LaunchSettingsDialog::Set(const char* flag, const char* value) {
  if (!cvar::SetFlagByName(flag, value)) {
    error_ = "This setting could not be applied.";
  } else {
    error_.clear();
  }
}

void LaunchSettingsDialog::Toggle(const char* label, const char* flag) {
  if (!cvar::GetFlagInfo(flag))
    return;
  bool value = rex::string::from_string<bool>(cvar::GetFlagByName(flag), false);
  if (ImGui::Checkbox(label, &value))
    Set(flag, value ? "true" : "false");
}

void LaunchSettingsDialog::Choice(const char* label, const char* flag, const char* const* names,
                                  const char* const* values, int count) {
  if (!cvar::GetFlagInfo(flag))
    return;
  const auto value = cvar::GetFlagByName(flag);
  int selected = -1;
  for (int i = 0; i < count; ++i)
    if (value == values[i])
      selected = i;
  if (ImGui::BeginCombo(label, selected >= 0 ? names[selected] : "Custom")) {
    for (int i = 0; i < count; ++i) {
      if (ImGui::Selectable(names[i], selected == i))
        Set(flag, values[i]);
      if (selected == i)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }
}

void LaunchSettingsDialog::OnDraw(ImGuiIO& io) {
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  PollGamepad(io);
  ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
                          ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
  ImGui::SetNextWindowSize(ImVec2(560, 0), ImGuiCond_FirstUseEver);
  ImGui::Begin("Game settings", nullptr, ImGuiWindowFlags_NoCollapse);
  ImGui::TextUnformatted(title_.c_str());
  ImGui::Separator();
  if (ImGui::BeginTabBar("Settings")) {
    if (ImGui::BeginTabItem("Graphics", nullptr, TabFlags(0))) {
      selected_tab_ = 0;
      Toggle("Fullscreen", "fullscreen");
      Toggle("Vertical sync", "vsync");
      constexpr const char* antialiasing[] = {"Off", "FXAA", "FXAA (strong)"};
      constexpr const char* antialiasing_values[] = {"none", "fxaa", "fxaa_extreme"};
      Choice("Anti-aliasing", "swap_post_effect", antialiasing, antialiasing_values, 3);
      constexpr const char* filtering[] = {"Game default", "Off", "1x", "2x", "4x", "8x", "16x"};
      constexpr const char* filtering_values[] = {"-1", "0", "1", "2", "3", "4", "5"};
      Choice("Texture filtering", "anisotropic_override", filtering, filtering_values, 7);
      // The runtime creates the command processor/texture cache after this
      // dialog. Keep both axes together, including titles with custom defaults.
      if (cvar::GetFlagInfo("draw_resolution_scale_x") &&
          cvar::GetFlagInfo("draw_resolution_scale_y")) {
        const auto scale = cvar::GetFlagByName("resolution_scale");
        const auto x = cvar::HasNonDefaultValue("resolution_scale") &&
                               !cvar::HasNonDefaultValue("draw_resolution_scale_x")
                           ? scale
                           : cvar::GetFlagByName("draw_resolution_scale_x");
        const auto y = cvar::HasNonDefaultValue("resolution_scale") &&
                               !cvar::HasNonDefaultValue("draw_resolution_scale_y")
                           ? scale
                           : cvar::GetFlagByName("draw_resolution_scale_y");
        const bool can_match = cvar::GetFlagInfo("resolution_match_display") != nullptr;
        const bool match_display =
            can_match &&
            rex::string::from_string<bool>(cvar::GetFlagByName("resolution_match_display"), false);
        const auto preview = match_display ? "Match display" : (x == y ? x + "x" : "Custom");
        if (ImGui::BeginCombo("Render scale", preview.c_str())) {
          if (can_match && ImGui::Selectable("Match display", match_display)) {
            Set("resolution_match_display", "true");
          }
          for (int i = 1; i <= 4; ++i) {
            const auto value = std::to_string(i);
            if (ImGui::Selectable((value + "x").c_str())) {
              if (can_match)
                Set("resolution_match_display", "false");
              Set("resolution_scale", value.c_str());
              Set("draw_resolution_scale_x", value.c_str());
              Set("draw_resolution_scale_y", value.c_str());
            }
          }
          ImGui::EndCombo();
        }
        ImGui::TextWrapped(
            "Higher render scales need more GPU memory. Results depend on the game.");
      }
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Audio", nullptr, TabFlags(1))) {
      selected_tab_ = 1;
      if (cvar::GetFlagInfo("audio_volume")) {
        int volume = rex::string::from_string<int>(cvar::GetFlagByName("audio_volume"), 100);
        if (ImGui::SliderInt("Volume", &volume, 0, 100, "%d%%")) {
          Set("audio_volume", std::to_string(volume).c_str());
        }
      }
      Toggle("Mute", "audio_mute");
      Toggle("Mute while minimised", "audio_mute_minimized");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Language", nullptr, TabFlags(2))) {
      selected_tab_ = 2;
      constexpr const char* names[] = {"System",
                                       "English",
                                       "Japanese",
                                       "German",
                                       "French",
                                       "Spanish",
                                       "Italian",
                                       "Korean",
                                       "Chinese (Traditional)",
                                       "Portuguese",
                                       "Chinese (Simplified)",
                                       "Polish",
                                       "Russian"};
      constexpr const char* values[] = {"0", "1", "2", "3",  "4",  "5", "6",
                                        "7", "8", "9", "10", "11", "12"};
      Choice("Game language", "user_language", names, values, 13);
      ImGui::TextWrapped(
          "The game must include the selected language. Missing title metadata uses its available "
          "language.");
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
    requested_tab_ = -1;
  }
  ImGui::Separator();
  if (pad_source_ && (io.BackendFlags & ImGuiBackendFlags_HasGamepad)) {
    ImGui::TextUnformatted("D-pad/stick: navigate   A: select   B: back   LB/RB: tabs");
  }
  ImGui::Checkbox("Remember settings", &remember_);
  if (!error_.empty())
    ImGui::TextWrapped("%s", error_.c_str());
  if (ImGui::Button("Play", ImVec2(140, 0))) {
    if (remember_ && !cvar::TrySaveConfig(config_path_)) {
      error_ = "Settings could not be saved. Uncheck Remember settings to play without saving.";
    } else {
      play_ = true;
      Close();
    }
  }
  ImGui::SameLine();
  if (ImGui::Button("Exit", ImVec2(140, 0)))
    Close();
  ImGui::End();
}

void LaunchSettingsDialog::OnClose() {
  if (completed_)
    completed_(play_);
}

}  // namespace rex::ui
