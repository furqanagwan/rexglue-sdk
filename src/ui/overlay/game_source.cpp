// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/ui/overlay/game_source.h>
#include <rex/ui/guide/message_box.h>
#include <cmath>

#include <chrono>
#include <cstring>
#include <imgui.h>
#include <rex/cvar.h>
#include <rex/string.h>
#include <rex/filesystem/devices/optical_disc_reader.h>
#include <windows.h>
#include <shobjidl.h>
#include <wrl/client.h>

namespace rex::ui {
// Own the parsed skin for every element pointer retained by the neutral model.
class GameSourceConsoleBox {
 public:
  static std::unique_ptr<GameSourceConsoleBox> Create(const GameSourceVisualsProvider& provider,
                                                      std::string title, std::string body,
                                                      std::span<const std::string> choices,
                                                      size_t initial = 0) {
    if (!provider)
      return nullptr;
    auto visuals = provider();
    if (!visuals || !visuals->assets)
      return nullptr;
    auto panel = std::unique_ptr<GameSourceConsoleBox>(new GameSourceConsoleBox);
    panel->visuals_ = std::move(*visuals);
    xui::SceneContext context;
    context.skin = &panel->visuals_.assets->skin;
    context.package = "huduiskin";
    context.play_sound = panel->visuals_.play_sound;
    panel->box_ = guide::MessageBoxScene::Create(context, std::move(title), std::move(body),
                                                 choices, initial);
    if (!panel->box_)
      return nullptr;
    panel->count_ = choices.size();
    guide::HideGuideButtonLetters(&panel->box_->root());
    panel->box_->root().Set("Position", xui::Value{xui::Vec3{}});
    const float width = panel->box_->root().width(), height = panel->box_->root().height();
    if (!std::isfinite(width) || !std::isfinite(height) || width <= 0 || height <= 0 ||
        width > 4096 || height > 4096)
      return nullptr;
    return panel;
  }
  std::optional<size_t> Draw(ImGuiIO& io, bool enabled) {
    auto& root = box_->root();
    const ImVec2 available = ImGui::GetContentRegionAvail();
    const auto cursor = ImGui::GetCursorScreenPos();
    const float scale = std::min(available.x / root.width(), available.y / root.height());
    const ImVec2 origin(cursor.x + (available.x - root.width() * scale) * 0.5f,
                        cursor.y + (available.y - root.height() * scale) * 0.5f);
    std::optional<size_t> chosen;
    const size_t initial = box_->focused_choice();
    ImGui::PushID("Console choices");
    for (size_t i = 0; i < count_; ++i) {
      box_->SetEnabled(i, enabled);
      const auto id = "Button" + std::to_string(i);
      auto* button = root.FindById(id);
      xui::Vec3 position{};
      for (auto* element = button; element && element != &root; element = element->parent()) {
        const auto p = element->position();
        position.x += p.x;
        position.y += p.y;
      }
      ImGui::SetCursorScreenPos(
          ImVec2(origin.x + position.x * scale, origin.y + position.y * scale));
      const ImVec2 size(std::max(1.0f, button->width() * scale),
                        std::max(1.0f, button->height() * scale));
      if (first_ && initial == i)
        ImGui::SetKeyboardFocusHere();
      const bool pressed = ImGui::InvisibleButton(id.c_str(), size, ImGuiButtonFlags_EnableNav);
      if (ImGui::IsItemFocused() || ImGui::IsItemHovered() || pressed)
        box_->Focus(i);
      if (pressed && enabled)
        chosen = box_->Activate();
      if (first_ && initial == i)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::PopID();
    if (first_)
      box_->Focus(initial);
    first_ = false;
    root.Advance(std::clamp(double(io.DeltaTime), 0.0, 0.25) * xui::kFramesPerSecond);
    xui::Render(ImGui::GetWindowDrawList(), root, origin, scale, 1, visuals_.resources);
    ImGui::SetCursorScreenPos(origin);
    ImGui::Dummy(ImVec2(root.width() * scale, root.height() * scale));
    return chosen;
  }

 private:
  GameSourceVisuals visuals_;
  std::unique_ptr<guide::MessageBoxScene> box_;
  size_t count_ = 0;
  bool first_ = true;
};

class GameSourceConsoleDownloads {
 public:
  static std::unique_ptr<GameSourceConsoleDownloads> Create(
      const GameSourceVisualsProvider& provider) {
    if (!provider)
      return nullptr;
    auto visuals = provider();
    if (!visuals || !visuals->assets || !visuals->assets->has_options)
      return nullptr;
    auto panel = std::unique_ptr<GameSourceConsoleDownloads>(new GameSourceConsoleDownloads);
    panel->visuals_ = std::move(*visuals);
    xui::SceneContext context;
    context.skin = &panel->visuals_.assets->skin;
    context.package = "hud/hud";
    context.play_sound = panel->visuals_.play_sound;
    panel->scene_ =
        guide::ActiveDownloadsScene::Create(panel->visuals_.assets->options_notifications, context);
    if (!panel->scene_)
      return nullptr;
    guide::HideGuideButtonLetters(&panel->scene_->root());
    auto& root = panel->scene_->root();
    root.Set("Position", xui::Value{xui::Vec3{}});
    if (!std::isfinite(root.width()) || !std::isfinite(root.height()) || root.width() <= 0 ||
        root.height() <= 0 || root.width() > 4096 || root.height() > 4096)
      return nullptr;
    return panel;
  }
  void Draw(ImGuiIO& io, guide::GuideActivity activity) {
    scene_->Update({std::move(activity)});
    auto& root = scene_->root();
    const auto origin = ImGui::GetCursorScreenPos();
    const float scale = std::max(1.0f, ImGui::GetContentRegionAvail().x) / root.width();
    auto* row = scene_->row(0);
    xui::Vec3 position{};
    for (auto* element = row; element && element != &root; element = element->parent()) {
      const auto p = element->position();
      position.x += p.x;
      position.y += p.y;
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x + position.x * scale, origin.y + position.y * scale));
    if (ImGui::InvisibleButton(
            "Cancel source copy",
            ImVec2(std::max(1.0f, row->width() * scale), std::max(1.0f, row->height() * scale)),
            ImGuiButtonFlags_EnableNav))
      scene_->Activate();
    root.Advance(std::clamp(double(io.DeltaTime), 0.0, 0.25) * xui::kFramesPerSecond);
    xui::Render(ImGui::GetWindowDrawList(), root, origin, scale, 1, visuals_.resources);
    ImGui::SetCursorScreenPos(origin);
    ImGui::Dummy(ImVec2(root.width() * scale, root.height() * scale));
  }

 private:
  GameSourceVisuals visuals_;
  std::unique_ptr<guide::ActiveDownloadsScene> scene_;
};

GameSourceDialog::GameSourceDialog(ImGuiDrawer* drawer, system::GameSourceIdentity expected,
                                   std::filesystem::path config,
                                   std::function<void(std::filesystem::path)> completed,
                                   std::filesystem::path initial, std::string error,
                                   std::string executable, std::filesystem::path extraction_root,
                                   LaunchPadSource pad_source, GameSourceVisualsProvider visuals,
                                   std::function<void(guide::GuideActivity)> activity_completed)
    : ImGuiDialog(drawer),
      expected_(std::move(expected)),
      config_(std::move(config)),
      completed_(std::move(completed)),
      initial_source_(initial),
      executable_(std::move(executable)),
      extraction_root_(std::move(extraction_root)),
      error_(std::move(error)),
      pad_source_(std::move(pad_source)),
      visuals_(std::move(visuals)),
      activity_completed_(std::move(activity_completed)) {
  const auto text = rex::string::to_utf8(initial.u16string());
  std::memcpy(path_.data(), text.data(), std::min(text.size(), path_.size() - 1));
}

GameSourceDialog::~GameSourceDialog() {
  if (pad_source_)
    ReleaseLaunchPad(GetIO());
  *check_cancel_ = true;
  if (copy_progress_)
    copy_progress_->cancel = true;
}

void GameSourceDialog::ShowConsoleScreen(ConsoleScreen screen, std::string title, std::string body,
                                         std::vector<std::string> choices, size_t initial) {
  console_initialized_ = true;
  console_screen_ = screen;
  console_choices_ = std::move(choices);
  console_box_ = GameSourceConsoleBox::Create(visuals_, std::move(title), std::move(body),
                                              console_choices_, initial);
  console_mode_ = bool(console_box_);
}

void GameSourceDialog::BeginSourceCheck(std::filesystem::path path) {
  path_.fill(0);
  const auto text = rex::string::to_utf8(path.u16string());
  if (text.size() >= path_.size()) {
    ShowConsoleScreen(ConsoleScreen::kError, "Game files", "The selected path is too long.",
                      {"Choose another source", "Leave Game"}, 0);
    return;
  }
  std::memcpy(path_.data(), text.data(), text.size());
  validated_.clear();
  error_.clear();
  checking_path_ = std::move(path);
  const auto expected = expected_;
  *check_cancel_ = false;
  checking_ = std::async(std::launch::async, [path = checking_path_, expected,
                                              executable = executable_, cancel = check_cancel_] {
    return system::InspectGameSource(path, executable, expected,
                                     [cancel] { return cancel->load(); });
  });
  ShowConsoleScreen(ConsoleScreen::kChecking, "Checking game files",
                    "Checking the game title and executable. Please wait.", {"Please wait"});
}

void GameSourceDialog::CollectOpticalDrives() {
  optical_drives_.clear();
  const DWORD drives = GetLogicalDrives();
  for (int i = 0; i < 26; ++i) {
    if (!(drives & (1u << i)))
      continue;
    const std::wstring drive{wchar_t(L'A' + i), L':', L'\\'};
    if (GetDriveTypeW(drive.c_str()) == DRIVE_CDROM)
      optical_drives_.push_back(std::string(1, char('A' + i)) + ":");
  }
}

void GameSourceDialog::CompleteConsoleSelection(bool remember) {
  const auto path = rex::string::to_utf8(validated_.u16string());
  if (!cvar::SetFlagByName("game_source", path)) {
    ShowConsoleScreen(ConsoleScreen::kError, "Game files",
                      "The source setting could not be applied.",
                      {"Choose another source", "Leave Game"}, 0);
  } else if (remember && !cvar::TrySaveConfig(config_)) {
    ShowConsoleScreen(ConsoleScreen::kSaveFailed, "Game files",
                      "The source could not be saved. Use it once, or choose another source.",
                      {"Use once", "Choose another source", "Leave Game"}, 0);
  } else {
    selected_ = validated_;
    Close();
  }
}

void GameSourceDialog::StartExtraction() {
  copy_progress_ = std::make_shared<CopyProgress>();
  const auto destination = extraction_root_ / ("game-" + expected_.executable_checksum);
  const auto source = validated_;
  const auto expected = expected_;
  const auto progress = copy_progress_;
  const auto executable = executable_;
  extracting_ =
      std::async(std::launch::async, [source, destination, expected, progress, executable] {
        return system::ExtractGameSource(
            source, destination, expected,
            [progress](uint64_t done, uint64_t total) {
              progress->done = done;
              progress->total = total;
            },
            [progress] { return progress->cancel.load(); }, executable);
      });
  console_box_.reset();
}

void GameSourceDialog::HandleConsoleChoice(size_t choice) {
  if (choice >= console_choices_.size())
    return;
  switch (console_screen_) {
    case ConsoleScreen::kSource:
      if (choice == 0) {
        Browse(false);
      } else if (choice == 1) {
        Browse(true);
      } else if (choice == 2) {
        CollectOpticalDrives();
        if (optical_drives_.empty()) {
          ShowConsoleScreen(ConsoleScreen::kError, "Disc drive", "No optical drive is available.",
                            {"Choose another source", "Leave Game"}, 0);
        } else {
          optical_drive_page_ = 0;
          std::vector<std::string> choices;
          const auto first = optical_drive_page_ * 2;
          for (size_t i = first; i < std::min(first + 2, optical_drives_.size()); ++i)
            choices.push_back(optical_drives_[i]);
          if (first + 2 < optical_drives_.size())
            choices.push_back("More drives");
          choices.push_back("Back");
          ShowConsoleScreen(ConsoleScreen::kDrives, "Disc drive",
                            "Choose the drive containing your Xbox 360 disc.", std::move(choices));
        }
      } else {
        Close();
      }
      break;
    case ConsoleScreen::kDrives: {
      const size_t first = optical_drive_page_ * 2;
      const size_t drive_count = std::min<size_t>(2, optical_drives_.size() - first);
      if (choice < drive_count) {
        BeginSourceCheck(std::filesystem::path("\\\\.\\" + optical_drives_[first + choice]));
      } else if (first + 2 < optical_drives_.size() && choice == drive_count) {
        ++optical_drive_page_;
        std::vector<std::string> choices;
        const auto next = optical_drive_page_ * 2;
        for (size_t i = next; i < std::min(next + 2, optical_drives_.size()); ++i)
          choices.push_back(optical_drives_[i]);
        if (next + 2 < optical_drives_.size())
          choices.push_back("More drives");
        choices.push_back("Back");
        ShowConsoleScreen(ConsoleScreen::kDrives, "Disc drive",
                          "Choose the drive containing your Xbox 360 disc.", std::move(choices));
      } else if (optical_drive_page_ && choice + 1 == console_choices_.size()) {
        --optical_drive_page_;
        std::vector<std::string> choices;
        const auto previous = optical_drive_page_ * 2;
        for (size_t i = previous; i < std::min(previous + 2, optical_drives_.size()); ++i)
          choices.push_back(optical_drives_[i]);
        if (previous + 2 < optical_drives_.size())
          choices.push_back("More drives");
        choices.push_back("Back");
        ShowConsoleScreen(ConsoleScreen::kDrives, "Disc drive",
                          "Choose the drive containing your Xbox 360 disc.", std::move(choices));
      } else {
        ShowConsoleScreen(ConsoleScreen::kSource, "Game files", "Choose your Xbox 360 game source.",
                          {"Choose a disc image (ISO)", "Choose an extracted folder",
                           "Read from a disc drive", "Leave Game"},
                          0);
      }
      break;
    }
    case ConsoleScreen::kChecking:
      break;
    case ConsoleScreen::kVerified:
      if (console_choices_[choice] == "Use this source") {
        CompleteConsoleSelection(true);
      } else if (console_choices_[choice] == "Extract to this PC") {
        StartExtraction();
      } else if (console_choices_[choice] == "Choose another source") {
        ShowConsoleScreen(ConsoleScreen::kSource, "Game files", "Choose your Xbox 360 game source.",
                          {"Choose a disc image (ISO)", "Choose an extracted folder",
                           "Read from a disc drive", "Leave Game"},
                          0);
      } else {
        Close();
      }
      break;
    case ConsoleScreen::kError:
      if (choice == 0) {
        ShowConsoleScreen(ConsoleScreen::kSource, "Game files", "Choose your Xbox 360 game source.",
                          {"Choose a disc image (ISO)", "Choose an extracted folder",
                           "Read from a disc drive", "Leave Game"},
                          0);
      } else {
        Close();
      }
      break;
    case ConsoleScreen::kSaveFailed:
      if (choice == 0) {
        CompleteConsoleSelection(false);
      } else if (choice == 1) {
        ShowConsoleScreen(ConsoleScreen::kSource, "Game files", "Choose your Xbox 360 game source.",
                          {"Choose a disc image (ISO)", "Choose an extracted folder",
                           "Read from a disc drive", "Leave Game"},
                          0);
      } else {
        Close();
      }
      break;
    case ConsoleScreen::kCopied:
      if (choice == 0) {
        CompleteConsoleSelection(true);
      } else if (choice == 1) {
        ShowConsoleScreen(ConsoleScreen::kSource, "Game files", "Choose your Xbox 360 game source.",
                          {"Choose a disc image (ISO)", "Choose an extracted folder",
                           "Read from a disc drive", "Leave Game"},
                          0);
      } else {
        Close();
      }
      break;
  }
}

void GameSourceDialog::Browse(bool folder) {
  const HRESULT initialized = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
  struct Uninitialize {
    bool own;
    ~Uninitialize() {
      if (own)
        CoUninitialize();
    }
  } cleanup{SUCCEEDED(initialized)};
  Microsoft::WRL::ComPtr<IFileOpenDialog> dialog;
  if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
                              IID_PPV_ARGS(&dialog)))) {
    error_ = "The file picker could not be opened. Enter the path below.";
    if (console_mode_)
      ShowConsoleScreen(ConsoleScreen::kError, "Game files", error_,
                        {"Choose another source", "Leave Game"}, 0);
    return;
  }
  DWORD options = 0;
  dialog->GetOptions(&options);
  dialog->SetOptions(options | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST |
                     (folder ? FOS_PICKFOLDERS : FOS_FILEMUSTEXIST));
  if (!folder) {
    const COMDLG_FILTERSPEC filter[] = {{L"Xbox 360 disc images", L"*.iso"}};
    dialog->SetFileTypes(1, filter);
  }
  dialog->SetTitle(folder ? L"Choose an extracted game folder" : L"Choose a game disc image");
  if (FAILED(dialog->Show(nullptr)))
    return;
  Microsoft::WRL::ComPtr<IShellItem> item;
  PWSTR value = nullptr;
  if (SUCCEEDED(dialog->GetResult(&item)) &&
      SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &value))) {
    const auto text = rex::string::to_utf8(std::filesystem::path(value).u16string());
    if (text.size() < path_.size()) {
      const std::filesystem::path selected_path(value);
      if (console_mode_) {
        BeginSourceCheck(selected_path);
      } else {
        path_.fill(0);
        std::memcpy(path_.data(), text.data(), text.size());
        validated_.clear();
        error_.clear();
      }
    } else {
      error_ = "The selected path is too long.";
      if (console_mode_)
        ShowConsoleScreen(ConsoleScreen::kError, "Game files", error_,
                          {"Choose another source", "Leave Game"}, 0);
    }
    CoTaskMemFree(value);
  }
}

void GameSourceDialog::OnDraw(ImGuiIO& io) {
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  PollLaunchPad(io, pad_source_);
  if (extracting_.valid() &&
      extracting_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    try {
      const auto result = extracting_.get();
      error_ =
          result.cancelled ? "Extraction cancelled; the game source is unchanged." : result.error;
      if (activity_completed_) {
        guide::GuideActivity activity;
        activity.title = "Game source extraction";
        activity.status = result.cancelled ? "Cancelled" : result ? "Completed" : "Failed";
        activity.details = result ? "Game files copied to this PC." : error_;
        activity_completed_(std::move(activity));
      }
      if (result) {
        validated_ = result.folder;
        const auto text = rex::string::to_utf8(validated_.u16string());
        if (text.size() < path_.size()) {
          path_.fill(0);
          std::memcpy(path_.data(), text.data(), text.size());
        }
        if (console_mode_)
          ShowConsoleScreen(ConsoleScreen::kCopied, "Game files copied",
                            "The game files are ready on this PC.",
                            {"Use this source", "Choose another source", "Leave Game"}, 0);
      } else if (console_mode_) {
        ShowConsoleScreen(ConsoleScreen::kError, "Game files could not be copied", error_,
                          {"Choose another source", "Leave Game"}, 0);
      }
    } catch (const std::exception& error) {
      error_ = error.what();
      if (console_mode_)
        ShowConsoleScreen(ConsoleScreen::kError, "Game files could not be copied", error_,
                          {"Choose another source", "Leave Game"}, 0);
    }
  }
  if (checking_.valid() &&
      checking_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    try {
      auto result = checking_.get();
      error_ = result.error;
      if (result) {
        validated_ = result.source_path;
        if (console_mode_) {
          const bool can_extract =
              !extraction_root_.empty() && (filesystem::IsOpticalDiscPath(validated_) ||
                                            std::filesystem::is_regular_file(validated_));
          std::vector<std::string> choices{"Use this source"};
          if (can_extract)
            choices.push_back("Extract to this PC");
          choices.push_back("Choose another source");
          choices.push_back("Leave Game");
          ShowConsoleScreen(ConsoleScreen::kVerified, "Game files verified",
                            "This game source matches the executable in this build.",
                            std::move(choices), 0);
        }
      } else if (console_mode_) {
        ShowConsoleScreen(ConsoleScreen::kError, "Game files not recognized", error_,
                          {"Choose another source", "Leave Game"}, 0);
      }
    } catch (const std::exception& error) {
      error_ = error.what();
      if (console_mode_)
        ShowConsoleScreen(ConsoleScreen::kError, "Game files not recognized", error_,
                          {"Choose another source", "Leave Game"}, 0);
    }
  }
  if (!console_initialized_) {
    if (expected_.title_id && !expected_.executable_checksum.empty()) {
      ShowConsoleScreen(ConsoleScreen::kSource, "Game files", "Choose your Xbox 360 game source.",
                        {"Choose a disc image (ISO)", "Choose an extracted folder",
                         "Read from a disc drive", "Leave Game"},
                        0);
    } else {
      ShowConsoleScreen(ConsoleScreen::kError, "Game files",
                        "This build has no source fingerprint. Regenerate its code to enable "
                        "first-run source selection.",
                        {"Leave Game"}, 0);
    }
  }
  if (console_mode_ && !initial_source_.empty()) {
    auto initial = std::move(initial_source_);
    initial_source_.clear();
    BeginSourceCheck(std::move(initial));
  }
  if (console_mode_) {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowBgAlpha(0.0f);
    constexpr ImGuiWindowFlags kOverlayFlags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::Begin("##GameSourceGuideOverlay", nullptr, kOverlayFlags);
    ImGui::GetWindowDrawList()->AddRectFilled(
        viewport->Pos,
        ImVec2(viewport->Pos.x + viewport->Size.x, viewport->Pos.y + viewport->Size.y),
        IM_COL32(0, 0, 0, 185));
    if (extracting_.valid()) {
      const uint64_t total = copy_progress_->total;
      const uint64_t done = copy_progress_->done;
      if (!console_downloads_)
        console_downloads_ = GameSourceConsoleDownloads::Create(visuals_);
      if (console_downloads_) {
        guide::GuideActivity activity;
        activity.title = "Game source extraction";
        activity.status =
            total ? std::to_string(unsigned(std::min(100.0, double(done) / double(total) * 100))) +
                        "%"
                  : "Checking source";
        activity.details = "Copying game files to this PC. Select this item to cancel.";
        activity.cancel = [progress = copy_progress_] { progress->cancel = true; };
        console_downloads_->Draw(io, std::move(activity));
      } else {
        ImGui::ProgressBar(total ? float(double(done) / double(total)) : 0);
      }
    } else if (console_box_) {
      const auto chosen = console_box_->Draw(io, !checking_.valid());
      if (chosen)
        HandleConsoleChoice(*chosen);
    }
    ImGui::End();
    return;
  }
  ImGui::SetNextWindowSize(ImVec2(650, 0), ImGuiCond_FirstUseEver);
  ImGui::Begin("Choose game files", nullptr, ImGuiWindowFlags_NoCollapse);
  ImGui::TextWrapped(
      "Choose your Xbox 360 game files. The executable must match this recomp build.");
  const bool identified = expected_.title_id && !expected_.executable_checksum.empty();
  if (!identified)
    ImGui::TextWrapped(
        "This build has no source fingerprint. Regenerate its code to enable first-run source "
        "selection.");
  ImGui::BeginDisabled(checking_.valid() || extracting_.valid());
  if (ImGui::Button("Choose an extracted folder"))
    Browse(true);
  ImGui::SameLine();
  if (ImGui::Button("Choose a disc image (ISO)"))
    Browse(false);
  if (ImGui::Button("Read from disc drive"))
    ImGui::OpenPopup("Optical drives");
  if (ImGui::BeginPopup("Optical drives")) {
    bool found = false;
    const DWORD drives = GetLogicalDrives();
    for (int i = 0; i < 26; ++i) {
      if (!(drives & (1u << i)))
        continue;
      const std::wstring drive{wchar_t(L'A' + i), L':', L'\\'};
      if (GetDriveTypeW(drive.c_str()) != DRIVE_CDROM)
        continue;
      found = true;
      const std::string label = std::string(1, char('A' + i)) + ":";
      if (ImGui::Selectable(label.c_str())) {
        const std::string source = "\\\\.\\" + label;
        path_.fill(0);
        std::memcpy(path_.data(), source.data(), source.size());
        validated_.clear();
        error_.clear();
      }
    }
    if (!found)
      ImGui::TextUnformatted("No optical drive is available.");
    ImGui::EndPopup();
  }
  if (ImGui::InputText("Source path", path_.data(), path_.size())) {
    validated_.clear();
    error_.clear();
  }
  ImGui::BeginDisabled(!identified || !path_[0]);
  if (ImGui::Button("Check source")) {
    validated_.clear();
    checking_path_ = rex::to_path(path_.data());
    const auto expected = expected_;
    *check_cancel_ = false;
    checking_ = std::async(std::launch::async, [path = checking_path_, expected,
                                                executable = executable_, cancel = check_cancel_] {
      return system::InspectGameSource(path, executable, expected,
                                       [cancel] { return cancel->load(); });
    });
  }
  ImGui::EndDisabled();
  ImGui::EndDisabled();
  if (checking_.valid()) {
    ImGui::TextUnformatted("Checking game identity and executable checksum...");
    if (ImGui::Button("Cancel check"))
      *check_cancel_ = true;
  }
  if (!error_.empty())
    ImGui::TextWrapped("%s", error_.c_str());
  if (!validated_.empty())
    ImGui::TextUnformatted("Game files match this build.");
  if (!extracting_.valid() && !checking_.valid() && !validated_.empty() &&
      !extraction_root_.empty() &&
      (filesystem::IsOpticalDiscPath(validated_) || std::filesystem::is_regular_file(validated_))) {
    if (ImGui::Button("Extract to this PC")) {
      copy_progress_ = std::make_shared<CopyProgress>();
      const auto destination = extraction_root_ / ("game-" + expected_.executable_checksum);
      extracting_ =
          std::async(std::launch::async, [source = validated_, destination, expected = expected_,
                                          progress = copy_progress_, executable = executable_] {
            return system::ExtractGameSource(
                source, destination, expected,
                [progress](uint64_t done, uint64_t total) {
                  progress->done = done;
                  progress->total = total;
                },
                [progress] { return progress->cancel.load(); }, executable);
          });
    }
  }
  if (extracting_.valid()) {
    const uint64_t total = copy_progress_->total;
    const uint64_t done = copy_progress_->done;
    if (!console_downloads_)
      console_downloads_ = GameSourceConsoleDownloads::Create(visuals_);
    if (console_downloads_) {
      guide::GuideActivity activity;
      activity.title = "Game source extraction";
      activity.status =
          total
              ? std::to_string(unsigned(std::min(100.0, double(done) / double(total) * 100))) + "%"
              : "Checking source";
      activity.details = "Copying game files to this PC. Select this item to cancel.";
      activity.cancel = [progress = copy_progress_] { progress->cancel = true; };
      console_downloads_->Draw(io, std::move(activity));
    } else {
      ImGui::ProgressBar(total ? float(double(done) / double(total)) : 0);
      ImGui::Text("Copying game files: %llu / %llu bytes", (unsigned long long)done,
                  (unsigned long long)total);
    }
    if (ImGui::Button("Cancel extraction"))
      copy_progress_->cancel = true;
  }
  ImGui::Checkbox("Remember source", &remember_);
  ImGui::BeginDisabled(validated_.empty() || checking_.valid() || extracting_.valid());
  if (ImGui::Button("Use this source")) {
    const auto path = rex::string::to_utf8(validated_.u16string());
    if (!cvar::SetFlagByName("game_source", path)) {
      error_ = "The source setting could not be applied.";
    } else if (remember_ && !cvar::TrySaveConfig(config_)) {
      error_ = "The source could not be saved. Uncheck Remember source to use it for this session.";
    } else {
      selected_ = validated_;
      Close();
    }
  }
  ImGui::EndDisabled();
  ImGui::SameLine();
  if (ImGui::Button("Leave Game"))
    Close();
  ImGui::TextWrapped(
      "An ISO can be used directly or copied to this PC. Ordinary PC optical drives cannot read an "
      "Xbox 360 disc's game partition.");
  ImGui::End();
}
void GameSourceDialog::OnClose() {
  if (completed_)
    completed_(selected_);
}
GameMediaRecoveryDialog::GameMediaRecoveryDialog(ImGuiDrawer* drawer, bool optical,
                                                 std::string error,
                                                 std::function<void(bool)> completed,
                                                 LaunchPadSource pad_source,
                                                 GameSourceVisualsProvider visuals)
    : ImGuiDialog(drawer),
      optical_(optical),
      error_(std::move(error)),
      completed_(std::move(completed)),
      pad_source_(std::move(pad_source)),
      visuals_(std::move(visuals)) {}
GameMediaRecoveryDialog::~GameMediaRecoveryDialog() {
  if (pad_source_)
    ReleaseLaunchPad(GetIO());
}
void GameMediaRecoveryDialog::OnDraw(ImGuiIO& io) {
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  PollLaunchPad(io, pad_source_);
  ImGui::SetNextWindowSize(ImVec2(600, 0), ImGuiCond_FirstUseEver);
  ImGui::Begin("Game source unavailable", nullptr, ImGuiWindowFlags_NoCollapse);
  ImGui::TextWrapped("%s",
                     optical_ ? "Reinsert the disc." : "Reconnect the drive with the disc image.");
  if (!error_.empty())
    ImGui::TextWrapped("%s", error_.c_str());
  const std::string choices[] = {"Retry", "Leave Game"};
  if (!console_box_)
    console_box_ = GameSourceConsoleBox::Create(
        visuals_, "Game source unavailable",
        error_.empty()
            ? (optical_ ? "Reinsert the disc." : "Reconnect the drive with the disc image.")
            : error_,
        choices, 1);
  std::optional<size_t> chosen;
  if (console_box_)
    chosen = console_box_->Draw(io, true);
  if ((console_box_ && chosen == 0) || (!console_box_ && ImGui::Button("Retry"))) {
    retry_ = true;
    Close();
  }
  if (!console_box_) {
    ImGui::SameLine();
    if (focus_leave_)
      ImGui::SetKeyboardFocusHere();
  }
  if ((console_box_ && chosen == 1) || (!console_box_ && ImGui::Button("Leave Game")))
    Close();
  focus_leave_ = false;
  ImGui::End();
}
void GameMediaRecoveryDialog::OnClose() {
  if (completed_)
    completed_(retry_);
}
}  // namespace rex::ui
