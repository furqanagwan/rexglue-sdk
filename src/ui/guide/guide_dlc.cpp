/**
 * @file        ui/guide/guide_dlc.cpp
 * @brief       Games & Apps > Manage Game: installing a title's DLC (RG-GDK-041)
 *
 * Lists the title's downloadable content: what is installed, and the
 * content packages (STFS, content type 2, this title's ID) found in the DLC
 * folder beside the executable or picked with "Add Content from This PC".
 * A on a package that is not installed installs it with the content
 * manager, off the UI thread. The page is the console's own Options scene,
 * its checkboxes ticked for installed content.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/ui/guide/xbox_guide.h>

#include <algorithm>
#include <atomic>
#include <thread>

#include <windows.h>
#include <shobjidl.h>

#include <fmt/format.h>

#include <rex/filesystem.h>
#include <rex/filesystem/devices/stfs_container_device.h>
#include <rex/logging.h>
#include <rex/string/utf8.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xam/content_device.h>
#include <rex/system/xam/content_manager.h>
#include <rex/system/xcontent.h>
#include <rex/ui/guide/guide_layout.h>

namespace rex::ui::guide {
namespace {

constexpr float kRowHeight = 28.0f;
constexpr std::string_view kAddId = "btnAddContent";
constexpr size_t kMaxRows = 11;  // the list area of the Options scene

bool SameName(std::string_view a, std::string_view b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                    [](char x, char y) { return std::tolower(x) == std::tolower(y); });
}

// The Windows file picker, for content packages anywhere on this PC.
std::vector<std::filesystem::path> PickPackages() {
  std::vector<std::filesystem::path> picked;
  const HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
  IFileOpenDialog* dialog = nullptr;
  if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
                                 IID_PPV_ARGS(&dialog)))) {
    DWORD options = 0;
    dialog->GetOptions(&options);
    dialog->SetOptions(options | FOS_ALLOWMULTISELECT | FOS_FILEMUSTEXIST | FOS_FORCEFILESYSTEM);
    dialog->SetTitle(L"Add downloadable content");
    if (SUCCEEDED(dialog->Show(GetForegroundWindow()))) {
      IShellItemArray* items = nullptr;
      if (SUCCEEDED(dialog->GetResults(&items))) {
        DWORD count = 0;
        items->GetCount(&count);
        for (DWORD i = 0; i < count; ++i) {
          IShellItem* item = nullptr;
          PWSTR path = nullptr;
          if (SUCCEEDED(items->GetItemAt(i, &item)) &&
              SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &path))) {
            picked.emplace_back(path);
            CoTaskMemFree(path);
          }
          if (item) {
            item->Release();
          }
        }
        items->Release();
      }
    }
    dialog->Release();
  }
  if (SUCCEEDED(init)) {
    CoUninitialize();
  }
  return picked;
}

}  // namespace

struct XboxGuide::DlcJob {
  std::atomic<bool> done{false};
  bool pick = false;
  std::string file_name;  // install: the package being installed
  X_RESULT result = X_ERROR_SUCCESS;
  std::vector<std::filesystem::path> picked;
};

std::vector<XboxGuide::DlcEntry> XboxGuide::FindDlc() const {
  std::vector<DlcEntry> out;
  auto* kernel = host_.kernel_state;
  if (!kernel || !kernel->content_manager()) {
    return out;
  }
  const uint32_t title_id = kernel->title_id();
  for (const auto& content : kernel->content_manager()->ListContent(
           static_cast<uint32_t>(system::xam::DummyDeviceId::HDD), 0,
           system::XContentType::kMarketplaceContent, title_id)) {
    DlcEntry entry;
    entry.file_name = content.file_name();
    entry.name = string::to_utf8(content.display_name());
    entry.installed = true;
    out.push_back(std::move(entry));
  }
  auto add_package = [&](const std::filesystem::path& path) {
    auto header = filesystem::StfsContainerDevice::ReadPackageHeader(path);
    if (!header || header->metadata.content_type != system::XContentType::kMarketplaceContent ||
        header->metadata.execution_info.title_id != title_id) {
      return;
    }
    const std::string file_name = path_to_utf8(path.filename());
    auto it = std::find_if(out.begin(), out.end(),
                           [&](const DlcEntry& e) { return SameName(e.file_name, file_name); });
    if (it == out.end()) {
      out.push_back({});
      it = std::prev(out.end());
      it->file_name = file_name;
    }
    it->package = path;
    const std::string name =
        string::to_utf8(header->metadata.display_name(system::XLanguage::kEnglish));
    if (!name.empty()) {
      it->name = name;
    }
    it->description = string::to_utf8(header->metadata.description(system::XLanguage::kEnglish));
  };
  std::error_code ec;
  const std::filesystem::path folder = filesystem::GetExecutableFolder() / "DLC";
  for (auto it = std::filesystem::recursive_directory_iterator(folder, ec);
       !ec && it != std::filesystem::recursive_directory_iterator(); it.increment(ec)) {
    if (it->is_regular_file(ec)) {
      add_package(it->path());
    }
  }
  for (const auto& path : picked_packages_) {
    add_package(path);
  }
  for (DlcEntry& entry : out) {
    if (entry.name.empty()) {
      entry.name = entry.file_name;
    }
  }
  std::stable_sort(out.begin(), out.end(),
                   [](const DlcEntry& a, const DlcEntry& b) { return a.name < b.name; });
  return out;
}

void XboxGuide::OpenManageGame() {
  SettingsPage& page = PushPage(assets_->options_notifications, "Manage Game");
  manage_scene_ = page.scene;
  manage_rows_.clear();
  dlc_status_.clear();
  page.on_focus = [this] { ShowDlc(focus_); };
  page.on_select = [this](xui::Element* row) {
    if (dlc_job_) {
      return;  // one install or pick at a time
    }
    if (row->id() == kAddId) {
      auto job = std::make_shared<DlcJob>();
      job->pick = true;
      dlc_job_ = job;
      std::thread([job] {
        job->picked = PickPackages();
        job->done = true;
      }).detach();
      return;
    }
    const auto at = std::find(manage_rows_.begin(), manage_rows_.end(), row);
    if (at == manage_rows_.end() || size_t(at - manage_rows_.begin()) >= dlc_.size()) {
      return;
    }
    const DlcEntry& entry = dlc_[size_t(at - manage_rows_.begin())];
    if (entry.installed || entry.package.empty() || !host_.kernel_state) {
      return;
    }
    auto job = std::make_shared<DlcJob>();
    job->file_name = entry.file_name;
    dlc_job_ = job;
    dlc_status_ = fmt::format("Installing {}...", entry.name);
    ShowDlc(row);
    auto* content = host_.kernel_state->content_manager();
    const std::filesystem::path package = entry.package;
    // The install outlives the guide if it is closed meanwhile.
    std::thread([job, content, package] {
      job->result = content->InstallContent(package);
      job->done = true;
    }).detach();
  };
  FillManageGame();
}

void XboxGuide::FillManageGame() {
  xui::Element* scene = manage_scene_;
  xui::Element* model = scene->FindById("chkShow");
  if (!model) {
    return;
  }
  for (xui::Element* row : manage_rows_) {
    if (row == focus_) {
      focus_ = nullptr;
    }
    row->parent()->RemoveChild(row);
  }
  manage_rows_.clear();
  dlc_ = FindDlc();

  const float top = model->GetVector("Position").y;
  const size_t rows = std::min(dlc_.size(), kMaxRows - 1);
  auto add_row = [&](std::string id, std::string text, size_t i) {
    xui::Element* row = scene->CloneChild(*model, std::move(id));
    xui::Vec3 p = model->GetVector("Position");
    p.y = top + float(i) * kRowHeight;
    row->Set("Position", xui::Value{p});
    row->SetText(std::move(text));
    row->SetVisible(true);
    manage_rows_.push_back(row);
    return row;
  };
  for (size_t i = 0; i < rows; ++i) {
    add_row(fmt::format("chkDlc{}", i), dlc_[i].name, i)->SetChecked(dlc_[i].installed);
  }
  // The last row is a plain entry: the checkbox copy without its box.
  xui::Element* add = add_row(std::string(kAddId), "Add Content from This PC...", rows);
  for (std::string_view part : {"CheckboxRule", "Checkbox", "XuiImage"}) {
    if (xui::Element* e = add->FindById(part)) {
      e->Suppress();
    }
  }
  for (size_t i = 0; i < manage_rows_.size(); ++i) {
    manage_rows_[i]->Set(
        "NavUp", xui::Value{i > 0 ? std::string(manage_rows_[i - 1]->id()) : std::string()});
    manage_rows_[i]->Set(
        "NavDown", xui::Value{i + 1 < manage_rows_.size() ? std::string(manage_rows_[i + 1]->id())
                                                          : std::string()});
  }
  for (std::string_view id :
       {"chkShow", "chkSound", "chkShowMovies", "chkShowIPTV", "labelSoundDisabled"}) {
    if (xui::Element* e = scene->FindById(id)) {
      e->Suppress();
    }
  }
  if (xui::Element* status = scene->FindById("XuiLabel2")) {
    status->SetVisible(true);
  }
  SetFocus(manage_rows_.front(), /*initial=*/true);
  ShowDlc(manage_rows_.front());
}

void XboxGuide::ShowDlc(xui::Element* row) {
  if (!manage_scene_ || !row) {
    return;
  }
  auto set_text = [&](std::string_view id, std::string text) {
    if (xui::Element* e = manage_scene_->FindById(id)) {
      e->SetText(std::move(text));
    }
  };
  std::string body;
  std::string status = dlc_status_;
  std::string action;
  if (row->id() == kAddId) {
    body = fmt::format(
        "Install downloadable content from a package on this PC.\r\n\r\nPackages in the DLC "
        "folder beside the game are listed here already{}.",
        dlc_.empty() ? "; none were found" : "");
    action = "Select";
  } else if (auto at = std::find(manage_rows_.begin(), manage_rows_.end(), row);
             at != manage_rows_.end() && size_t(at - manage_rows_.begin()) < dlc_.size()) {
    const DlcEntry& entry = dlc_[size_t(at - manage_rows_.begin())];
    body = entry.description.empty() ? entry.name : entry.description;
    if (status.empty()) {
      status =
          entry.installed ? "Installed. The game may need a restart to use it." : "Not installed.";
    }
    if (!entry.installed && !entry.package.empty()) {
      action = "Install";
    }
  }
  set_text("XuiLabel1", std::move(body));
  set_text("XuiLabel2", std::move(status));
  SetLegends(dlc_job_ ? "" : action, manage_scene_->GetString("LegendB"), "");
}

void XboxGuide::PollManageGame() {
  if (!dlc_job_ || !dlc_job_->done) {
    return;
  }
  const auto job = std::move(dlc_job_);
  if (!manage_scene_ || pages_.empty() || pages_.back().scene != manage_scene_) {
    return;  // the page was left meanwhile
  }
  if (job->pick) {
    picked_packages_.insert(picked_packages_.end(), job->picked.begin(), job->picked.end());
    const size_t before = dlc_.size();
    FillManageGame();
    if (!job->picked.empty() && dlc_.size() == before) {
      dlc_status_ = "No downloadable content for this game was in the files chosen.";
      ShowDlc(focus_);
    }
    return;
  }
  if (job->result == X_ERROR_SUCCESS) {
    REXLOG_INFO("Xbox guide: installed {}", job->file_name);
    dlc_status_ = "Installed. The game may need a restart to use it.";
    media_->PlaySound("btn_selectG.xma", "xam/skin");
  } else {
    REXLOG_WARN("Xbox guide: installing {} failed: {:08X}", job->file_name, job->result);
    dlc_status_ = fmt::format("The content could not be installed (error {:08X}).", job->result);
  }
  const std::string keep = dlc_status_;
  FillManageGame();
  dlc_status_ = keep;
  ShowDlc(focus_);
  dlc_status_.clear();
}

}  // namespace rex::ui::guide
