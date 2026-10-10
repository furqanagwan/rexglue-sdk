// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.

#include <fstream>

#include <imgui.h>
#include <imgui_internal.h>
#include <rex/filesystem.h>
#include <rex/rex_app.h>

class LaunchSettingsConsumer : public rex::ReXApp {
 public:
  explicit LaunchSettingsConsumer(rex::ui::WindowedAppContext& context)
      : ReXApp(context, "LaunchSettingsConsumer", rex::PPCImageInfo{}) {}

  static std::unique_ptr<rex::ui::WindowedApp> Create(rex::ui::WindowedAppContext& context) {
    return std::make_unique<LaunchSettingsConsumer>(context);
  }

 protected:
  void OnConfigurePaths(rex::PathConfig& paths) override {
    const auto root = rex::filesystem::GetExecutableFolder() / "smoke-data";
    paths.game_data_root = root / "no-game";
    paths.user_data_root = root / "saves";
    paths.cache_root = root / "cache";
    paths.config_path = root / "config.toml";
    std::filesystem::create_directories(paths.game_data_root);
  }

  void OnPostSetup() override { guest_started_ = true; }

  void OnCreateDialogs(rex::ui::ImGuiDrawer* drawer) override {
    probe_ = std::make_unique<Probe>(drawer, [this](bool rendered) {
      std::ofstream report(rex::filesystem::GetExecutableFolder() / "launcher-result.txt");
      report << (rendered && !guest_started_ ? "PASS" : "FAIL")
             << ": launcher rendered before guest setup; shutdown requested\n";
      app_context().CallInUIThreadDeferred([this] { app_context().QuitFromUIThread(); });
    });
  }

  void OnShutdown() override { probe_.reset(); }

 private:
  class Probe : public rex::ui::ImGuiDialog {
   public:
    Probe(rex::ui::ImGuiDrawer* drawer, std::function<void(bool)> done)
        : ImGuiDialog(drawer), done_(std::move(done)) {}

   protected:
    void OnDraw(ImGuiIO&) override {
      const auto* menu = ImGui::FindWindowByName("Game settings");
      rendered_ |= menu && menu->WasActive && menu->DrawList->VtxBuffer.Size > 0;
      if (++frames_ == 8)
        done_(rendered_);
    }

   private:
    std::function<void(bool)> done_;
    int frames_ = 0;
    bool rendered_ = false;
  };
  std::unique_ptr<Probe> probe_;
  bool guest_started_ = false;
};

REX_DEFINE_APP(launch_settings_consumer, LaunchSettingsConsumer::Create)
