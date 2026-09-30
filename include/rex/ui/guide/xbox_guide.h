/**
 * @file        rex/ui/guide/xbox_guide.h
 * @brief       The Xbox 360 guide, run from the console's own scenes (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <imgui.h>

#include <rex/cvar.h>
#include <rex/system/achievement_store.h>
#include <rex/ui/guide/guide_input.h>
#include <rex/ui/imgui_dialog.h>
#include <rex/ui/overlay/achievement_icon_cache.h>
#include <rex/ui/xui/document.h>
#include <rex/ui/xui/renderer.h>
#include <rex/ui/xui/runtime.h>
#include <rex/ui/xui/system_update.h>

namespace rex {
class Runtime;
namespace audio {
struct PcmSound;
class UiSoundPlayer;
}  // namespace audio
namespace input {
class InputSystem;
}  // namespace input
namespace system {
class AchievementManager;
class KernelState;
}  // namespace system
}  // namespace rex

namespace rex::ui {
class ImmediateDrawer;
class ImmediateTexture;
}  // namespace rex::ui

REXCVAR_DECLARE(bool, xbox_guide);
REXCVAR_DECLARE(std::string, xbox_guide_system_update);

namespace rex::ui::guide {

/// Where the guide looks for the console's system update: the
/// xbox_guide_system_update cvar, then `$SystemUpdate` beside the executable,
/// then %LOCALAPPDATA%\ReXGlue\$SystemUpdate.
std::vector<std::filesystem::path> SystemUpdateLocations();

/// The scenes and strings the guide uses, parsed once from the owner's system
/// update.
struct GuideAssets {
  std::unique_ptr<xui::SystemUpdate> update;
  xui::Document skin;      // huduiskin: control visuals, message boxes
  xui::Document backdrop;  // xam hudbkgnd: the HUD frame the guide opens in
  xui::Document main;      // hud GuideMain: tabs and blades
  xui::Document home_tab, games_tab, settings_tab;
  xui::Document achievements, achievement_details;  // gamerprofile
  bool has_achievement_scenes = false;
  xui::Document notify;  // xam: the notification popup
  bool has_notify = false;
  std::vector<std::string> hud_strings, xam_strings, profile_strings;

  static std::unique_ptr<GuideAssets> Load(const std::filesystem::path& path, std::string* error);
};

/// The first string in `strings` starting with `prefix` (tables are per
/// language; matching on English text keeps this independent of order).
std::string FindString(const std::vector<std::string>& strings, std::string_view prefix,
                       std::string_view fallback);

struct GuideFonts {
  ImFont* regular = nullptr;
  ImFont* bold = nullptr;
};

/// Adds Segoe UI (the host stand-in for Segoe Xbox) to the atlas. Call from
/// the ImGui drawer's font setup, before the atlas is built.
GuideFonts AddGuideFonts(ImFontAtlas* atlas);

/// Textures and sounds from the system update, kept across openings.
class GuideMedia {
 public:
  GuideMedia(ImmediateDrawer* immediate_drawer, std::shared_ptr<const GuideAssets> assets);
  ~GuideMedia();

  ImTextureID Texture(std::string_view path, std::string_view package, int* width, int* height);
  void PlaySound(std::string_view file, std::string_view package);

 private:
  struct Image {
    std::unique_ptr<ImmediateTexture> texture;
    int width = 0, height = 0;
  };

  ImmediateDrawer* immediate_drawer_;
  std::shared_ptr<const GuideAssets> assets_;
  std::map<std::string, Image, std::less<>> images_;
  std::map<std::string, std::shared_ptr<const audio::PcmSound>, std::less<>> sounds_;
  std::unique_ptr<audio::UiSoundPlayer> player_;
};

struct GuideHost {
  input::InputSystem* input = nullptr;
  system::KernelState* kernel_state = nullptr;
  system::AchievementManager* achievements = nullptr;
  Runtime* runtime = nullptr;  // the title's XDBF achievement icons
  ImmediateDrawer* immediate_drawer = nullptr;
  std::string title_name;
  /// After the guide has closed; `exit_title` when the owner confirmed Xbox
  /// Home or Turn Off.
  std::function<void(bool exit_title)> on_closed;
};

/// The guide over a running title. It owns itself, as XAM dialogs do: it
/// deletes itself after its close animation and then calls on_closed.
class XboxGuide final : public ImGuiDialog {
 public:
  XboxGuide(ImGuiDrawer* drawer, std::shared_ptr<const GuideAssets> assets, GuideMedia* media,
            GuideFonts fonts, GuideHost host, uint16_t held_buttons);
  ~XboxGuide() override;

  /// Closes with the console's close animation (the chord pressed again).
  void Dismiss();

 protected:
  void OnDraw(ImGuiIO& io) override;
  void OnClose() override;

 private:
  enum class Screen { kMain, kAchievements, kAchievementDetail, kConfirm };
  enum class Confirm { kXboxHome, kTurnOff };

  void Handle(GuideAction action);
  void HandleMain(GuideAction action);
  void HandleAchievements(GuideAction action);
  void HandleConfirm(GuideAction action);
  void Activate(xui::Element* control);

  void SwitchTab(int tab);
  xui::Element* FirstFocusable(xui::Element* root);
  void SetFocus(xui::Element* control, bool initial = false);
  void SetLegends(std::string_view a, std::string_view b, std::string_view y);
  void ConfigureMain();

  void OpenAchievements();
  void ShowAchievement(size_t index);
  void ScrollAchievements();
  void OpenAchievementDetail();
  void CloseAchievements();

  void OpenConfirm(Confirm confirm);
  void CloseConfirm();

  void BeginClose(bool exit_title);
  void UpdateClock();
  ImTextureID Texture(std::string_view path, std::string_view package, int* width, int* height);

  std::shared_ptr<const GuideAssets> assets_;
  GuideMedia* media_;
  GuideFonts fonts_;
  GuideHost host_;
  GuidePad pad_;
  AchievementIconCache icons_;
  xui::RenderResources render_;

  xui::SceneContext backdrop_context_, hud_context_, skin_context_, profile_context_;
  std::unique_ptr<xui::Element> backdrop_;
  xui::Element* hud_root_ = nullptr;  // HUDRootScene
  xui::Element* app_host_ = nullptr;
  xui::Element* error_host_ = nullptr;
  xui::Element* main_ = nullptr;
  xui::Element* tabs_ = nullptr;
  xui::Element* tab_scenes_[5] = {};
  xui::Element* tab_focus_[5] = {};
  int tab_ = 2;  // Home
  xui::Element* focus_ = nullptr;

  Screen screen_ = Screen::kMain;
  std::vector<system::AchievementInfo> achievement_list_;
  xui::Element* achievements_ = nullptr;
  xui::Element* details_ = nullptr;
  size_t selected_ = 0;
  size_t first_row_ = 0;
  int columns_ = 1;
  int visible_rows_ = 1;

  Confirm confirm_ = Confirm::kXboxHome;
  xui::Element* message_ = nullptr;
  xui::Element* return_focus_ = nullptr;
  std::vector<xui::Element*> pending_removal_;  // detached once the backdrop stops

  bool closing_ = false;
  bool exit_title_ = false;
  std::chrono::steady_clock::time_point last_tick_;
  std::chrono::steady_clock::time_point opened_;
  int64_t clock_minute_ = -1;
};

}  // namespace rex::ui::guide
