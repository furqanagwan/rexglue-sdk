// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/ui/overlay/game_source.h>

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
GameSourceDialog::GameSourceDialog(ImGuiDrawer* drawer, system::GameSourceIdentity expected,
                                   std::filesystem::path config,
                                   std::function<void(std::filesystem::path)> completed,
                                   std::filesystem::path initial, std::string error,
                                   std::string executable, std::filesystem::path extraction_root,
                                   LaunchPadSource pad_source)
    : ImGuiDialog(drawer),
      expected_(std::move(expected)),
      config_(std::move(config)),
      completed_(std::move(completed)),
      executable_(std::move(executable)),
      extraction_root_(std::move(extraction_root)),
      error_(std::move(error)),
      pad_source_(std::move(pad_source)) {
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
      path_.fill(0);
      std::memcpy(path_.data(), text.data(), text.size());
      validated_.clear();
      error_.clear();
    } else {
      error_ = "The selected path is too long.";
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
      if (result) {
        validated_ = result.folder;
        const auto text = rex::string::to_utf8(validated_.u16string());
        if (text.size() < path_.size()) {
          path_.fill(0);
          std::memcpy(path_.data(), text.data(), text.size());
        }
      }
    } catch (const std::exception& error) {
      error_ = error.what();
    }
  }
  if (checking_.valid() &&
      checking_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
    try {
      auto result = checking_.get();
      error_ = result.error;
      if (result)
        validated_ = result.source_path;
    } catch (const std::exception& error) {
      error_ = error.what();
    }
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
    ImGui::ProgressBar(total ? float(double(done) / double(total)) : 0);
    ImGui::Text("Copying game files: %llu / %llu bytes", (unsigned long long)done,
                (unsigned long long)total);
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
                                                 LaunchPadSource pad_source)
    : ImGuiDialog(drawer),
      optical_(optical),
      error_(std::move(error)),
      completed_(std::move(completed)),
      pad_source_(std::move(pad_source)) {}
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
  if (ImGui::Button("Retry")) {
    retry_ = true;
    Close();
  }
  ImGui::SameLine();
  if (ImGui::Button("Leave Game"))
    Close();
  ImGui::End();
}
void GameMediaRecoveryDialog::OnClose() {
  if (completed_)
    completed_(retry_);
}
}  // namespace rex::ui
