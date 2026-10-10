/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <sstream>

#include <fmt/format.h>

#include <rex/cvar.h>
#include <rex/logging.h>
#include <rex/string.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xam/user_profile.h>

#include <windows.h>

REXCVAR_DEFINE_STRING(user_gamertag, "", "Kernel",
                      "The profile's gamertag. Empty: the Xbox account signed in to this PC "
                      "(the Xbox app), else User");

namespace rex {
namespace system {
namespace xam {
namespace {

constexpr size_t kMaxGamertag = 15;

std::string SignedInGamertag() {
  wchar_t value[64] = {};
  DWORD size = sizeof(value);
  if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\XboxLive", L"Gamertag", RRF_RT_REG_SZ,
                   nullptr, value, &size) != ERROR_SUCCESS) {
    return {};
  }
  return rex::string::to_utf8(std::u16string(reinterpret_cast<const char16_t*>(value)));
}

std::string ProfileName() {
  std::string name = REXCVAR_GET(user_gamertag);
  if (name.empty()) {
    name = SignedInGamertag();
  }
  if (name.empty()) {
    return "User";
  }
  if (name.size() > kMaxGamertag) {
    name.resize(kMaxGamertag);
    while (!name.empty() && (uint8_t(name.back()) & 0xC0) == 0x80) {
      name.pop_back();
    }
    if (!name.empty() && (uint8_t(name.back()) & 0x80)) {
      name.pop_back();
    }
  }
  return name;
}

}

UserProfile::UserProfile() {
  xuid_ = 0xB13EBABEBABEBABE;
  name_ = ProfileName();

  AddSetting(std::make_unique<Int32Setting>(0x10040002, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040003, 3));

  AddSetting(std::make_unique<Int32Setting>(0x10040004, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040005, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040006, 0xFA));

  AddSetting(std::make_unique<FloatSetting>(0x5004000B, 0.0f));

  AddSetting(std::make_unique<Int32Setting>(0x1004000C, 0));

  AddSetting(std::make_unique<Int32Setting>(0x1004000D, 0));

  AddSetting(std::make_unique<Int32Setting>(0x1004000E, 0x64));

  AddSetting(std::make_unique<UnicodeSetting>(0x402C0011, u""));

  AddSetting(std::make_unique<Int32Setting>(0x10040012, 1));

  AddSetting(std::make_unique<Int32Setting>(0x10040013, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040015, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040018, 0));

  AddSetting(std::make_unique<Int32Setting>(0x1004001D, 0xFFFF0000u));

  AddSetting(std::make_unique<Int32Setting>(0x1004001E, 0xFF00FF00u));

  AddSetting(std::make_unique<Int32Setting>(0x10040022, 1));

  AddSetting(std::make_unique<Int32Setting>(0x10040023, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040024, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040026, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040027, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040028, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040029, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040038, 0));

  AddSetting(std::make_unique<Int32Setting>(0x10040039, 0));

  AddSetting(std::make_unique<UnicodeSetting>(0x4064000F, u"gamercard_picture_key"));

  AddSetting(std::make_unique<BinarySetting>(0x63E83FFF));

  AddSetting(std::make_unique<BinarySetting>(0x63E83FFE));

  AddSetting(std::make_unique<BinarySetting>(0x63E83FFD));
}

bool UserProfile::AddSetting(std::unique_ptr<Setting> setting) {
  std::lock_guard<std::mutex> lock(settings_mutex_);
  bool saved = true;
  if (setting->is_title_specific()) {
    if (kernel_state_) {
      setting->loaded_title_id = kernel_state_->title_id();
      setting->title_loaded = true;
    }
    if (setting->is_set) {
      saved = SaveSetting(setting.get());
    }
  }

  const uint32_t setting_id = setting->setting_id;
  settings_[setting_id] = std::shared_ptr<Setting>(std::move(setting));
  return saved;
}

std::shared_ptr<UserProfile::Setting> UserProfile::GetSetting(uint32_t setting_id) {
  std::lock_guard<std::mutex> lock(settings_mutex_);
  const auto& it = settings_.find(setting_id);
  if (it == settings_.end()) {
    return nullptr;
  }
  std::shared_ptr<UserProfile::Setting> setting = it->second;

  if (setting->is_title_specific() &&
      (!setting->title_loaded || kernel_state_->title_id() != setting->loaded_title_id)) {
    setting = LoadSetting(setting_id);
    it->second = setting;
  }
  return setting;
}

std::shared_ptr<UserProfile::Setting> UserProfile::LoadSetting(uint32_t setting_id) {
  auto setting = std::make_shared<BinarySetting>(setting_id);
  setting->loaded_title_id = kernel_state_->title_id();
  setting->title_loaded = true;
  auto content_dir = kernel_state_->content_manager()->ResolveGameUserContentPath();
  auto file_path = content_dir / fmt::format("{:08X}", setting_id);
  std::error_code ec;
  const auto size = std::filesystem::file_size(file_path, ec);
  if (ec) {
    return setting;
  }
  auto file = rex::filesystem::OpenFile(file_path, "rb");
  if (!file) {
    return setting;
  }
  std::vector<uint8_t> serialized_data(size);
  const size_t read = fread(serialized_data.data(), 1, serialized_data.size(), file);
  fclose(file);
  if (read != serialized_data.size()) {
    REXSYS_ERROR("Could not read profile setting {:08X} from {}", setting_id,
                 rex::path_to_utf8(file_path));
    return setting;
  }
  setting->Deserialize(serialized_data);
  return setting;
}

bool UserProfile::SaveSetting(UserProfile::Setting* setting) {
  if (setting->is_title_specific()) {
    auto serialized_setting = setting->Serialize();
    auto content_dir = kernel_state_->content_manager()->ResolveGameUserContentPath();
    std::error_code ec;
    std::filesystem::create_directories(content_dir, ec);
    auto setting_id = fmt::format("{:08X}", setting->setting_id);
    auto file_path = content_dir / setting_id;

    if (!rex::filesystem::WriteFileDurably(file_path, serialized_setting)) {
      REXSYS_ERROR("Could not save profile setting {:08X} to {}", setting->setting_id,
                   rex::path_to_utf8(file_path));
      return false;
    }
    return true;
  } else {
    REXSYS_WARN("Attempting to save unsupported profile setting to disk");
    return true;
  }
}

}
}
}
