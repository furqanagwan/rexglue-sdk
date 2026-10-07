// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once
#include <array>
#include <atomic>
#include <future>
#include <rex/system/game_source.h>
#include <rex/ui/imgui_dialog.h>
#include <rex/ui/overlay/launch_settings.h>
#include <rex/ui/guide/xbox_guide.h>
#include <rex/ui/xui/renderer.h>

namespace rex::ui {
struct GameSourceVisuals {
  std::shared_ptr<const guide::GuideAssets> assets;
  xui::RenderResources resources;
  std::function<void(std::string_view, std::string_view)> play_sound;
};
using GameSourceVisualsProvider = std::function<std::optional<GameSourceVisuals>()>;
class GameSourceConsoleBox;
class GameSourceConsoleDownloads;
// Self-owned first-run dialog. An empty completion path means Leave Game.
class GameSourceDialog : public ImGuiDialog {
 public:
  GameSourceDialog(ImGuiDrawer* drawer, system::GameSourceIdentity expected,
                   std::filesystem::path config,
                   std::function<void(std::filesystem::path)> completed,
                   std::filesystem::path initial = {}, std::string error = {},
                   std::string executable = "default.xex",
                   std::filesystem::path extraction_root = {}, LaunchPadSource pad_source = {},
                   GameSourceVisualsProvider visuals = {},
                   std::function<void(guide::GuideActivity)> activity_completed = {});
  ~GameSourceDialog() override;

 protected:
  void OnDraw(ImGuiIO& io) override;
  void OnClose() override;

 private:
  void Browse(bool folder);
  system::GameSourceIdentity expected_;
  std::filesystem::path config_;
  std::function<void(std::filesystem::path)> completed_;
  std::array<char, 4096> path_{};
  std::future<system::GameSourceResult> checking_;
  std::shared_ptr<std::atomic<bool>> check_cancel_ = std::make_shared<std::atomic<bool>>(false);
  std::future<system::GameSourceExtraction> extracting_;
  struct CopyProgress {
    std::atomic<uint64_t> done = 0;
    std::atomic<uint64_t> total = 0;
    std::atomic<bool> cancel = false;
  };
  std::shared_ptr<CopyProgress> copy_progress_;
  std::string executable_;
  std::filesystem::path extraction_root_;
  std::filesystem::path checking_path_;
  std::filesystem::path validated_;
  std::filesystem::path selected_;
  std::string error_;
  bool remember_ = true;
  LaunchPadSource pad_source_;
  GameSourceVisualsProvider visuals_;
  std::unique_ptr<GameSourceConsoleBox> console_box_;
  std::unique_ptr<GameSourceConsoleDownloads> console_downloads_;
  std::function<void(guide::GuideActivity)> activity_completed_;
};
class GameMediaRecoveryDialog : public ImGuiDialog {
 public:
  GameMediaRecoveryDialog(ImGuiDrawer* drawer, bool optical, std::string error,
                          std::function<void(bool)> completed, LaunchPadSource pad_source = {},
                          GameSourceVisualsProvider visuals = {});
  ~GameMediaRecoveryDialog() override;

 protected:
  void OnDraw(ImGuiIO& io) override;
  void OnClose() override;

 private:
  bool optical_, retry_ = false;
  std::string error_;
  std::function<void(bool)> completed_;
  LaunchPadSource pad_source_;
  GameSourceVisualsProvider visuals_;
  std::unique_ptr<GameSourceConsoleBox> console_box_;
};
}  // namespace rex::ui
