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
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include <imgui.h>

#include <rex/cvar.h>
#include <rex/image_info.h>
#include <rex/ui/guide/code_patch_states.h>
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
REXCVAR_DECLARE(bool, notifications_show);
REXCVAR_DECLARE(bool, notifications_sound);
REXCVAR_DECLARE(std::string, code_patch_states);
REXCVAR_DECLARE(bool, resolution_match_display);

namespace rex::ui::guide {

/// Where the guide looks for the console's system update: the
/// xbox_guide_system_update cvar, then `$SystemUpdate` beside the executable,
/// then %LOCALAPPDATA%\ReXGlue\$SystemUpdate.
std::vector<std::filesystem::path> SystemUpdateLocations();

/// The guide bundle the title build embedded (rexglue_configure_target), so
/// players need nothing for the guide. Called by the generated registration
/// at static initialisation; empty when the title was built without one.
bool RegisterEmbeddedGuide(const uint8_t* data, size_t size);
std::span<const uint8_t> EmbeddedGuide();

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
  // Preferences and the pages built on its scenes (hud).
  xui::Document options, options_vibration, options_notifications, options_voice;
  bool has_options = false;
  std::vector<std::string> hud_strings, xam_strings, profile_strings;

  static std::unique_ptr<GuideAssets> Load(const std::filesystem::path& path, std::string* error);
  /// From a guide bundle (see EmbeddedGuide).
  static std::unique_ptr<GuideAssets> LoadBundle(std::span<const uint8_t> bundle,
                                                 std::string* error);
  static std::unique_ptr<GuideAssets> FromUpdate(std::unique_ptr<xui::SystemUpdate> update,
                                                 std::string* error);
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
/// the ImGui drawer's font setup, before the atlas is built. The glyphs are
/// baked for `display_height` (the guide's text is sharp at 4K too).
GuideFonts AddGuideFonts(ImFontAtlas* atlas, int display_height = 0);

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
  /// The title's switchable code patches (null name ends the list).
  const PPCSwitchablePatch* patches = nullptr;
  /// The title's own cheat codes (null name ends the list).
  const PPCTitleCheat* cheats = nullptr;
  /// The draw resolution scale that matches the display (3 for 4K).
  int display_scale = 1;
  /// Writes changed settings to the title's config file.
  std::function<void()> save_settings;
  /// After the guide has closed; `exit_title` when the owner confirmed Xbox
  /// Home.
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
  enum class Screen { kMain, kAchievements, kAchievementDetail, kConfirm, kSettings };
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

  // Settings pages (guide_settings.cpp): Preferences and what it opens,
  // Patches and Cheats, each one of the console's own Options scenes.
  struct SettingsPage {
    xui::Element* scene = nullptr;
    xui::Element* return_focus = nullptr;  // focus on the page below
    std::function<void(xui::Element*)> on_select;
    std::function<void()> on_focus;  // after focus moves on the page
    std::function<void(xui::Element*, int)> on_adjust;
  };
  SettingsPage& PushPage(const xui::Document& scene, std::string heading);
  void PopPage();
  void HandleSettings(GuideAction action);
  void OpenPreferences();
  void OpenVibration();
  void OpenVolume();
  void OpenNotifications();
  void OpenResolution();
  void OpenPatches(std::string_view category);
  void OpenCheats();
  void SetSlider(xui::Element* slider, int value);

  // Games & Apps > Manage Game (guide_dlc.cpp): the title's downloadable
  // content, installed from packages on this PC.
  struct DlcEntry {
    std::filesystem::path package;  // empty when only installed
    std::string file_name;
    std::string name;
    std::string description;
    bool installed = false;
  };
  struct DlcJob;  // an install or file pick running off the UI thread
  void OpenManageGame();
  void FillManageGame();
  void ShowDlc(xui::Element* row);
  void PollManageGame();
  std::vector<DlcEntry> FindDlc() const;

  void BeginClose(bool exit_title);
  void UpdateClock();
  /// Shows player 1's battery, at most once a second.
  void UpdateControllerBattery();
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
  std::vector<SettingsPage> pages_;
  int queued_tab_ = 0;  // a tab switch that passes over a removed tab
  xui::Element* manage_scene_ = nullptr;
  std::vector<xui::Element*> manage_rows_;
  std::vector<DlcEntry> dlc_;
  std::vector<std::filesystem::path> picked_packages_;
  std::shared_ptr<DlcJob> dlc_job_;
  std::string dlc_status_;

  bool closing_ = false;
  bool exit_title_ = false;
  float dim_ = 0.0f;  // how far the title behind the guide is dimmed, 0 to 1
  std::chrono::steady_clock::time_point last_tick_;
  std::chrono::steady_clock::time_point opened_;
  int64_t clock_minute_ = -1;
  int64_t battery_second_ = -1;
};

}  // namespace rex::ui::guide
