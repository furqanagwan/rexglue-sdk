/**
 * @file        ui/rex_app.cpp
 * @brief       ReXApp implementation - compiled as part of the consumer executable
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/rex_app.h>

#include <cstdlib>
#include <functional>
#include <string>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/ui/flags.h>
#include <rex/kernel/crt/heap.h>
#include <rex/data_locations.h>
#include <rex/filesystem.h>
#include <rex/logging/sink.h>
#include <rex/logging.h>
#include <rex/ui/overlay/achievement_toast.h>
#include <rex/ui/overlay/achievements_overlay.h>
#include <rex/ui/overlay/console_overlay.h>
#include <rex/ui/overlay/debug_overlay.h>
#include <rex/ui/overlay/settings_overlay.h>
#include <rex/audio/audio_backend.h>
#include <rex/audio/audio_system.h>
#include <rex/audio/downmix.h>
#include <rex/audio/flags.h>
#include <rex/input/input_system.h>
#include <rex/kernel/init.h>
#include <rex/string/numeric.h>
#include <rex/system.h>
#include <rex/system/achievement_manager.h>
#include <rex/system/gpu_plugin.h>
#include <rex/system/flags.h>
#include <rex/system/kernel_state.h>
#include <rex/system/util/xdbf_utils.h>
#include <rex/system/xthread.h>
#include <rex/thread.h>
#include <rex/ui/graphics_provider.h>
#include <rex/ui/guide/guide_notification.h>
#include <rex/ui/guide/title_update.h>
#include <rex/ui/guide/xbox_guide.h>
#include <rex/ui/keybinds.h>
#include <rex/ui/window_win.h>
#include <rex/version.h>

#include <fmt/format.h>
#include <imgui.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
#include <string_view>

REXCVAR_DEFINE_STRING(gpu_plugin, "", "GPU",
                      "GPU emulation plugin to load at startup (e.g. 'xenos'); empty disables "
                      "GPU emulation")
    .lifecycle(rex::cvar::Lifecycle::kInitOnly);

REXCVAR_DEFINE_STRING(gaming_runtime, "auto", "GDK",
                      "Microsoft Gaming Runtime at startup: auto (initialize it in GDK builds and "
                      "launch regardless), required (launch only when it is ready) or off")
    .allowed({"auto", "required", "off"})
    .lifecycle(rex::cvar::Lifecycle::kInitOnly);

REXCVAR_DEFINE_INT32(gaming_runtime_timeout_ms, 10000, "GDK",
                     "How long startup waits for the Gaming Runtime to initialize")
    .range(100, 120000)
    .lifecycle(rex::cvar::Lifecycle::kInitOnly);

namespace rex {

namespace {

// The height in pixels of the display the window is on, in its current
// mode (not scaled by the desktop's DPI setting); 0 when unknown.
int DisplayHeight(ui::Window* window) {
  auto* win32 = static_cast<ui::Win32Window*>(window);
  HMONITOR monitor = MonitorFromWindow(win32 ? win32->hwnd() : nullptr, MONITOR_DEFAULTTOPRIMARY);
  MONITORINFOEXW info = {};
  info.cbSize = sizeof(info);
  DEVMODEW mode = {};
  mode.dmSize = sizeof(mode);
  if (!GetMonitorInfoW(monitor, &info) ||
      !EnumDisplaySettingsW(info.szDevice, ENUM_CURRENT_SETTINGS, &mode)) {
    return 0;
  }
  return int(mode.dmPelsHeight);
}

// The draw resolution scale that fills the display: titles draw at 720p,
// so 3 for 2160p, 2 for 1440p and 1080p, 1 below.
int DisplayScale(int display_height) {
  return std::clamp((display_height + 360) / 720, 1, 3);
}

// Shows the title as the console would: its name from the XDBF string table,
// in the user's language when it has one, and its dashboard icon. Leaves the
// window as it is when the executable has no XDBF resource.
// The title's own XDBF name, in the user's language when it has one.
std::string TitleName(const system::KernelState& kernel_state) {
  const system::util::XdbfGameData db = kernel_state.title_xdbf();
  if (!db.is_valid()) {
    return {};
  }
  const system::XLanguage language =
      db.GetExistingLanguage(static_cast<system::XLanguage>(REXCVAR_GET(user_language)));
  std::string name = system::util::TitleDisplayName(db.title(language));
  if (name.empty()) {
    name = system::util::TitleDisplayName(db.title());
  }
  return name;
}

void ApplyTitleIdentity(ui::Window& window, const system::KernelState& kernel_state) {
  const system::util::XdbfGameData db = kernel_state.title_xdbf();
  if (!db.is_valid()) {
    REXLOG_WARN("Title has no XDBF resource; keeping the project name as the window title");
    return;
  }
  const std::string name = TitleName(kernel_state);
  if (!name.empty()) {
    window.SetTitle(name);
    REXLOG_INFO("Title: {}", name);
  }
  const system::util::XdbfBlock icon = db.icon();
  if (icon) {
    window.SetIcon(icon.buffer, icon.size);
  }
}

}  // namespace

// --- ReXApp ---

ReXApp::~ReXApp() {
  StopGuide();
}

ReXApp::ReXApp(ui::WindowedAppContext& ctx, std::string_view name, PPCImageInfo ppc_info,
               std::string_view usage)
    : WindowedApp(ctx, name, usage), ppc_info_(ppc_info) {}

std::unique_ptr<ui::ImGuiDialog> ReXApp::CreateAchievementsOverlay() {
  if (!runtime_ || !runtime_->kernel_state() || !imgui_drawer_ || !immediate_drawer_) {
    return nullptr;
  }
  return std::make_unique<ui::AchievementsOverlayDialog>(
      imgui_drawer_.get(), immediate_drawer_.get(), runtime_.get(), &achievements());
}

std::unique_ptr<ui::AchievementNotificationDialog> ReXApp::CreateAchievementNotificationDialog() {
  if (!imgui_drawer_ || !immediate_drawer_ || !runtime_) {
    return nullptr;
  }
  auto toast = std::make_unique<ui::AchievementToastDialog>(
      imgui_drawer_.get(), immediate_drawer_.get(), runtime_.get());
  if (!REXCVAR_GET(xbox_guide)) {
    return toast;
  }
  // The console's own popup (xam notify.xur) from the system update, with the
  // SDK toast when there is none.
  using Notification = ui::guide::GuideNotificationDialog;
  auto source = [this]() {
    Notification::Media media;
    if (guide_stop_.load(std::memory_order_acquire)) {
      media.unavailable = true;
      return media;
    }
    std::lock_guard<std::mutex> lock(guide_mutex_);
    media.assets = guide_assets_;
    media.unavailable = !guide_assets_ && !guide_error_.empty();
    if (media.assets && !guide_media_) {
      guide_media_ = std::make_unique<ui::guide::GuideMedia>(immediate_drawer_.get(), media.assets);
    }
    media.media = guide_media_.get();
    return media;
  };
  return std::make_unique<Notification>(
      imgui_drawer_.get(), std::move(source),
      ui::guide::GuideFonts{guide_font_regular_, guide_font_bold_}, std::move(toast));
}

namespace {

// This process's arguments after argv[0], without the title update ones: a
// restart must take the saved choice, and only a hand-over is marked.
std::wstring ForwardedArguments() {
  const std::wstring line = GetCommandLineW();
  std::vector<std::wstring> tokens;
  std::wstring token;
  bool quoted = false, any = false;
  for (wchar_t c : line) {
    if (c == L'"') {
      quoted = !quoted;
    }
    if (c == L' ' && !quoted) {
      if (any) {
        tokens.push_back(token);
      }
      token.clear();
      any = false;
      continue;
    }
    token += c;
    any = true;
  }
  if (any) {
    tokens.push_back(token);
  }
  std::wstring out;
  for (size_t i = 1; i < tokens.size(); ++i) {
    if (tokens[i].starts_with(L"--title_update=") ||
        tokens[i].starts_with(L"--title_update_handoff")) {
      continue;
    }
    out += L" " + tokens[i];
  }
  return out;
}

// Starts `executable` with this process's arguments. A hand-over is marked so
// the new one never hands back.
bool StartHandOff(const std::filesystem::path& executable, bool hand_off = true) {
  std::wstring command_line = L"\"" + executable.wstring() + L"\"" + ForwardedArguments();
  if (hand_off) {
    command_line += L" --title_update_handoff=true";
  }
  STARTUPINFOW startup = {sizeof(startup)};
  PROCESS_INFORMATION process = {};
  if (!CreateProcessW(executable.c_str(), command_line.data(), nullptr, nullptr, FALSE, 0, nullptr,
                      executable.parent_path().c_str(), &startup, &process)) {
    return false;
  }
  CloseHandle(process.hThread);
  CloseHandle(process.hProcess);
  REXLOG_INFO("{} {}", hand_off ? "Handed over to" : "Restarting as", executable.string());
  return true;
}

}  // namespace

system::AchievementManager& ReXApp::achievements() const {
  assert_not_null(runtime_);
  assert_not_null(runtime_->kernel_state());
  return runtime_->kernel_state()->achievements();
}

bool ReXApp::OnInitialize() {
  if (!SetupEnvironment()) {
    if (handed_off_) {
      app_context().QuitFromUIThread();
      return true;
    }
    return false;
  }
  if (!SetupPresentation())
    return false;

  auto paths = OnFinalizePaths(resolved_defaults_, MakeResumeCallback());
  if (!paths) {
    // Async: consumer will invoke resume when ready. OnInitialize returns
    // true so the event loop keeps pumping (wizard dialogs render).
    return true;
  }

  if (!ConstructRuntime(*paths))
    return false;
  LaunchModule();
  return true;
}

bool ReXApp::SetupEnvironment() {
  auto exe_dir = rex::filesystem::GetExecutableFolder();
  // Where an Xbox PC game keeps its files (docs/data-locations.md): saves
  // under Saved Games, caches, logs and settings under local app data.
  const auto locations = rex::filesystem::DefaultTitleDataLocations(
      rex::filesystem::GetSavedGamesFolder(), rex::filesystem::GetLocalAppDataFolder(), GetName());

  // Game data: cvar override, or the game files beside the executable
  std::filesystem::path game_dir;
  std::string game_data_cvar = REXCVAR_GET(game_data_root);
  if (!game_data_cvar.empty()) {
    game_dir = game_data_cvar;
  } else {
    game_dir = rex::filesystem::FindGameDataRoot(exe_dir);
  }

  // User data: cvar override, or Saved Games\<name>
  std::filesystem::path user_dir;
  std::string user_data_cvar = REXCVAR_GET(user_data_root);
  if (!user_data_cvar.empty()) {
    user_dir = user_data_cvar;
  } else {
    user_dir = locations.user_data;
  }

  // Update data: cvar override, or empty (opt-in)
  std::filesystem::path update_dir;
  std::string update_data_cvar = REXCVAR_GET(update_data_root);
  if (!update_data_cvar.empty()) {
    update_dir = update_data_cvar;
  }

  // Cache: cvar override, or local app data. With an explicit user data
  // folder and no cache override, the cache stays inside it as before.
  std::filesystem::path cache_dir;
  std::string cache_root_cvar = REXCVAR_GET(cache_root);
  if (!cache_root_cvar.empty()) {
    cache_dir = cache_root_cvar;
  } else if (!user_data_cvar.empty()) {
    cache_dir = user_dir / "cache";
  } else {
    cache_dir = locations.cache;
  }

  std::filesystem::path metadata_dir;
  std::string metadata_root_cvar = REXCVAR_GET(metadata_root);
  if (!metadata_root_cvar.empty()) {
    metadata_dir = metadata_root_cvar;
  }

  // Settings: a <name>.toml beside the executable still wins (development
  // builds and existing projects); otherwise the per-user one.
  auto config_path = exe_dir / (std::string(GetName()) + ".toml");
  if (!std::filesystem::exists(config_path)) {
    config_path = locations.config;
  }

  PathConfig path_config{game_dir, user_dir, update_dir, cache_dir, metadata_dir, config_path};
  OnConfigurePaths(path_config);
  game_data_root_ = path_config.game_data_root;
  user_data_root_ = path_config.user_data_root;
  update_data_root_ = path_config.update_data_root;
  cache_root_ = path_config.cache_root;
  metadata_root_ = path_config.metadata_root;
  config_path_ = path_config.config_path;
  resolved_defaults_ = std::move(path_config);

  // Load config FIRST so log cvars have final values
  if (std::filesystem::exists(config_path_))
    rex::cvar::LoadConfig(config_path_);

  std::string log_level_str = REXCVAR_GET(log_level);
  if (REXCVAR_GET(log_verbose) && log_level_str == "info")
    log_level_str = "trace";

  auto log_config =
      rex::BuildLogConfig(log_level_str, rex::ParseCategoryLevelsFromConfig(config_path_));
  log_config.app_name = std::string(GetName());
  log_config.log_dir = locations.logs;
  // Each run is one file now (no rotation), so the directory is bounded
  // instead: the 100 MiB the old 5 MiB x 20 rotation allowed. Titles can
  // change it, or turn it off with 0, in OnConfigureLogging.
  log_config.dir_budget_bytes = uint64_t(100) << 20;
  OnConfigureLogging(log_config);
  rex::ApplyLogCvarOverrides(log_config);
  rex::InitLogging(log_config);
  rex::RegisterLogLevelCallback();

  log_sink_ = std::make_shared<rex::LogCaptureSink>();
  rex::AddSink(log_sink_);

  OnPostInitLogging();

  if (std::filesystem::exists(config_path_))
    REXLOG_DEBUG("Loaded config: {}", config_path_.string());

  local_dir_ = locations.local;
  // Title updates are optional (docs/title-updates.md): the player's choice in
  // the guide (title_update) picks the executable, and the original is always
  // the fallback. An update build given --update_data_root runs as asked.
  if (!(ppc_info_.title_update && !update_data_cvar.empty())) {
    const auto choice = ui::guide::ChooseLaunch(
        ppc_info_.title_update, uint32_t(std::max(0, REXCVAR_GET(title_update))),
        rex::filesystem::GetExecutablePath(), locations.local, REXCVAR_GET(title_update_handoff));
    if (!choice.note.empty()) {
      REXLOG_INFO("Title update: {}", choice.note);
    }
    if (choice.hand_off) {
      if (StartHandOff(choice.executable)) {
        handed_off_ = true;
        return false;
      }
      REXLOG_WARN("Could not start {}; running this build", choice.executable.string());
    }
    if (choice.cannot_run) {
      auto msg = fmt::format(
          "This build runs title update {}, which isn't installed, and the original executable "
          "isn't beside it.",
          ppc_info_.title_update);
      REXLOG_ERROR("{}", msg);
      rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
      return false;
    }
    if (update_data_cvar.empty() && !choice.update.empty()) {
      update_data_root_ = choice.update;
      resolved_defaults_.update_data_root = choice.update;
    }
  }

  // Earlier builds kept user data in Documents\<name>, which OneDrive syncs.
  if (user_data_cvar.empty() && user_data_root_ == locations.user_data) {
    const auto legacy = rex::filesystem::GetUserFolder() / GetName();
    const auto move = rex::filesystem::MoveLegacyUserData(legacy, user_data_root_, cache_root_);
    if (move.moved || move.copied) {
      REXLOG_INFO("Moved user data from {} to {}{}", legacy.string(), user_data_root_.string(),
                  move.copied ? " (copied; the old folder was left in place)" : "");
    }
    if (move.moved_cache) {
      REXLOG_INFO("Moved the cache from {} to {}", (legacy / "cache").string(),
                  cache_root_.string());
    }
    if (!move.error.empty()) {
      REXLOG_WARN("Could not move user data from {} to {}: {}", legacy.string(),
                  user_data_root_.string(), move.error);
    }
  }

  REXLOG_INFO("{} starting, {}", GetName(), REXGLUE_BUILD_TITLE);
  // Already raised by the entry point; asking again reports it for the log.
  REXLOG_DEBUG("  Timer resolution: {:.1f} ms",
               double(rex::thread::RequestHighTimerResolution()) / 10000.0);
  if (!game_data_root_.empty()) {
    REXLOG_DEBUG("  Game directory: {}", game_data_root_.string());
  }
  if (!user_data_root_.empty()) {
    REXLOG_DEBUG("  User data:      {}", user_data_root_.string());
  }
  if (!update_data_root_.empty()) {
    REXLOG_DEBUG("  Update data:    {}", update_data_root_.string());
  }
  REXLOG_DEBUG("  Cache root:     {}", cache_root_.string());
  REXLOG_DEBUG("  Logs:           {}", log_config.log_dir.string());
  if (!metadata_root_.empty()) {
    REXLOG_DEBUG("  Metadata root:  {}", metadata_root_.string());
  }

  return InitializeGamingRuntime();
}

bool ReXApp::InitializeGamingRuntime() {
  const auto policy = system::ParseGamingRuntimePolicy(REXCVAR_GET(gaming_runtime))
                          .value_or(system::GamingRuntimePolicy::kAuto);
  if (policy == system::GamingRuntimePolicy::kOff) {
    return true;
  }
  gaming_runtime_ = std::make_unique<system::GamingRuntime>();
  const auto result = gaming_runtime_->Initialize(
      std::chrono::milliseconds(REXCVAR_GET(gaming_runtime_timeout_ms)));
  if (result.ok()) {
    REXLOG_INFO("Gaming Runtime ready");
  } else if (result.state == system::GamingRuntimeState::kUnavailable &&
             policy == system::GamingRuntimePolicy::kAuto) {
    REXLOG_DEBUG("Gaming Runtime: {}", result.message);
  } else {
    REXLOG_WARN("Gaming Runtime {}: {}", system::GamingRuntimeStateName(result.state),
                result.message);
  }
  if (OnGamingRuntimeInitialized(result, policy)) {
    return true;
  }
  REXLOG_ERROR("Startup stopped: the Gaming Runtime is {}",
               system::GamingRuntimeStateName(result.state));
  rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, result.message);
  return false;
}

bool ReXApp::ConstructRuntime(const PathConfig& paths) {
  if (paths.game_data_root.empty()) {
    auto msg = fmt::format(
        "Game files not found. Put the extracted disc in {} (default.xex at its top), or pass "
        "--game_data_root.",
        (rex::filesystem::GetExecutableFolder() / "game").string());
    REXLOG_ERROR("{}", msg);
    rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
    return false;
  }
  if (!std::filesystem::is_directory(paths.game_data_root)) {
    auto msg = fmt::format("--game_data_root does not exist: {}", paths.game_data_root.string());
    REXLOG_ERROR("{}", msg);
    rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
    return false;
  }

  game_data_root_ = paths.game_data_root;
  user_data_root_ = paths.user_data_root;
  update_data_root_ = paths.update_data_root;
  cache_root_ = paths.cache_root;
  metadata_root_ = paths.metadata_root;

  runtime_ =
      std::make_unique<rex::Runtime>(paths.game_data_root, paths.user_data_root,
                                     paths.update_data_root, paths.cache_root, paths.metadata_root);
  runtime_->set_app_context(&app_context());

  // Window and ImGui drawer already exist from SetupPresentation; publish them
  // to the runtime before Setup so hooks and native rendering see them.
  if (window_) {
    runtime_->set_display_window(window_.get());
  }
  if (imgui_drawer_) {
    runtime_->set_imgui_drawer(imgui_drawer_.get());
  }

  // Draw at the display's resolution unless the player chose one in the
  // guide (Preferences > Resolution) or on the command line. Not saved: it
  // follows the display from run to run.
  if (REXCVAR_GET(resolution_match_display) &&
      rex::cvar::GetFlagSource("resolution_scale") < rex::cvar::Source::kCommandLine) {
    const int scale = DisplayScale(DisplayHeight(window_.get()));
    rex::cvar::SetFlagFromCommandLine("resolution_scale", std::to_string(scale));
    REXLOG_INFO("Drawing at {}p to match the display (resolution_scale {})", 720 * scale, scale);
  }

  auto status = runtime_->Setup(ppc_info_, std::move(config_));
  if (XFAILED(status)) {
    REXLOG_ERROR("Runtime setup failed: {:08X}", status);
    return false;
  }

  if (window_ && runtime_->input_system()) {
    static_cast<rex::input::InputSystem*>(runtime_->input_system())->AttachWindow(window_.get());
  }

  if (ppc_info_.register_modules) {
    ppc_info_.register_modules(runtime_->kernel_state());
  }

  if (auto* input_sys = static_cast<rex::input::InputSystem*>(runtime_->input_system())) {
    input_sys->SetActiveCallback([this]() {
      if (window_ && !window_->HasFocus())
        return false;
      if (!imgui_drawer_ ||
          (!debug_overlay_ && !console_overlay_ && !settings_overlay_ && !achievements_overlay_))
        return true;
      return !imgui_drawer_->GetIO().WantCaptureMouse;
    });
  }

  std::string xex_image = "game:\\default.xex";
  OnLoadXexImage(xex_image);

  // Mirrors the game:\ / d:\ -> game_data_root mapping in Runtime::SetupVfs.
  {
    constexpr std::string_view kGameDevice = "game:\\";
    constexpr std::string_view kDDevice = "d:\\";
    std::string_view tail = xex_image;
    if (tail.starts_with(kGameDevice)) {
      tail.remove_prefix(kGameDevice.size());
    } else if (tail.starts_with(kDDevice)) {
      tail.remove_prefix(kDDevice.size());
    }
    std::string host_tail{tail};
    std::replace(host_tail.begin(), host_tail.end(), '\\', '/');
    auto xex_host = paths.game_data_root / host_tail;
    if (!std::filesystem::is_regular_file(xex_host)) {
      auto msg = fmt::format("Entrypoint XEX not found: {}", xex_host.string());
      REXLOG_ERROR("{}", msg);
      rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
      return false;
    }
  }

  // A title update build runs that update's code, so it loads the executable
  // patched by the same update (update_data_root, mounted at update:).
  runtime_->kernel_state()->set_title_update_version(ppc_info_.title_update);
  if (ppc_info_.title_update) {
    std::error_code ec;
    if (paths.update_data_root.empty() || !std::filesystem::exists(paths.update_data_root, ec)) {
      auto msg = fmt::format(
          "This build runs title update {}, which isn't installed. Pass its package or "
          "folder with --update_data_root.",
          ppc_info_.title_update);
      REXLOG_ERROR("{}", msg);
      rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
      return false;
    }
    REXLOG_INFO("Title update {} build, update from {}", ppc_info_.title_update,
                paths.update_data_root.string());
  }

  status = runtime_->LoadXexImage(xex_image);
  if (XFAILED(status)) {
    auto msg = fmt::format("Failed to load XEX ({}): {:08X}", xex_image, status);
    REXLOG_ERROR("{}", msg);
    rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
    return false;
  }

  if (ppc_info_.code_patches && *ppc_info_.code_patches) {
    REXLOG_INFO("Guest code patches compiled in: {}", ppc_info_.code_patches);
  }
  // Patches the player can switch in the guide: as they left them.
  ui::guide::ApplySavedCodePatches(ppc_info_.switchable_patches);
  for (const PPCSwitchablePatch* p = ppc_info_.switchable_patches; p && p->name; ++p) {
    REXLOG_INFO("Switchable {} \"{}\": {}", p->category, p->name, *p->active ? "on" : "off");
  }

  OnPostLoadXexImage();

  if (ppc_info_.rexcrt_heap) {
    if (!rex::kernel::crt::InitHeap(REXCVAR_GET(rexcrt_heap_size_mb), runtime_->memory())) {
      REXLOG_ERROR("Failed to initialize rexcrt heap");
      return false;
    }
  }

  OnPostSetup();

  return true;
}

bool ReXApp::SetupPresentation() {
  config_.gpu_plugin = REXCVAR_GET(gpu_plugin);
  config_.audio_factory = [](rex::runtime::FunctionDispatcher* dispatcher)
      -> std::unique_ptr<rex::system::IAudioSystem> {
    return rex::audio::CreateDefaultAudioSystem(dispatcher);
  };
  config_.input_factory = REX_INPUT_BACKEND(rex::input::CreateDefaultInputSystem);
  config_.kernel_init = rex::kernel::InitializeKernel;

  OnPreSetup(config_);

  if (!config_.graphics && !config_.gpu_plugin.empty()) {
    config_.graphics = rex::system::LoadGpuPlugin(config_.gpu_plugin);
    if (!config_.graphics) {
      // Fatal by design: no silent headless fallback.
      auto msg =
          fmt::format("Failed to load GPU plugin '{}'. See log for details.", config_.gpu_plugin);
      REXLOG_ERROR("{}", msg);
      rex::ShowSimpleMessageBox(rex::SimpleMessageBoxType::Error, msg);
      return false;
    }
  }

  if (config_.graphics) {
    X_STATUS status = config_.graphics->SetupPresentation(&app_context());
    if (XFAILED(status)) {
      REXLOG_ERROR("Graphics presentation setup failed: {:08X}", status);
      return false;
    }
  }

  // Create window
  window_ = rex::ui::Window::Create(app_context(), GetName());
  if (!window_) {
    REXLOG_ERROR("Failed to create window");
    return false;
  }

  // The project name until the title's own name and icon are known at launch.
  // The SDK build stamp is in the log and the debug overlay.
  window_->SetTitle(GetName());

  window_->AddListener(this);
  window_->AddInputListener(this, 0);

  if (REXCVAR_GET(fullscreen)) {
    window_->SetFullscreen(true);
  }
  window_->SetMonitor(REXCVAR_GET(monitor));

  auto on_window_cvar = [this](const char* name, std::function<void(std::string_view)> apply) {
    rex::cvar::RegisterChangeCallback(
        name, [this, apply = std::move(apply)](std::string_view, std::string_view value) {
          app_context().CallInUIThread([this, apply, value = std::string(value)] {
            if (window_) {
              apply(value);
            }
          });
        });
  };

  on_window_cvar("fullscreen", [this](std::string_view value) {
    window_->SetFullscreen(rex::string::from_string<bool>(value, false));
  });
  on_window_cvar("fullscreen_exclusive",
                 [this](std::string_view) { window_->RefreshFullscreen(); });
  on_window_cvar("monitor", [this](std::string_view value) {
    window_->SetMonitor(rex::string::from_string<int32_t>(value, 0));
  });
  auto apply_window_size = [this](std::string_view) {
    uint32_t width = 0;
    uint32_t height = 0;
    rex::ui::Window::ResolveConfiguredLogicalSize(width, height);
    window_->SetDesiredLogicalSize(width, height);
  };
  on_window_cvar("window_width", apply_window_size);
  on_window_cvar("window_height", apply_window_size);
  on_window_cvar("resolution", [this, apply_window_size](std::string_view value) {
    apply_window_size(value);
    window_->RefreshFullscreen();
  });

  window_->Open();

  auto* graphics_system = config_.graphics.get();
  if (graphics_system && graphics_system->presenter()) {
    // SDK mode: the emulated-Xenos presenter drives the overlays.
    auto* presenter = graphics_system->presenter();
    auto* provider = graphics_system->provider();
    if (provider) {
      immediate_drawer_ = provider->CreateImmediateDrawer();
      if (immediate_drawer_) {
        immediate_drawer_->SetPresenter(presenter);
        SetupOverlays(presenter, immediate_drawer_.get());
      }
    }
    window_->SetPresenter(presenter);
  } else if (!graphics_system) {
    // Detached mode: the app brings its own renderer and drives its own paint
    // loop. ReXApp owns the returned drawer via immediate_drawer_.
    immediate_drawer_ = OnCreateImmediateDrawer();
    if (immediate_drawer_) {
      SetupOverlays(/*presenter=*/nullptr, immediate_drawer_.get());
      // No window_->SetPresenter, no drawer SetPresenter: the app owns the
      // surface and the present cadence.
    }
  }

  return true;
}

void ReXApp::SetupOverlays(rex::ui::Presenter* presenter, rex::ui::ImmediateDrawer* drawer) {
  imgui_drawer_ = std::make_unique<rex::ui::ImGuiDrawer>(
      window_.get(), 64,
      [this](ImFontAtlas* atlas) {
        if (REXCVAR_GET(xbox_guide)) {
          const ui::guide::GuideFonts fonts =
              ui::guide::AddGuideFonts(atlas, DisplayHeight(window_.get()));
          guide_font_regular_ = fonts.regular;
          guide_font_bold_ = fonts.bold;
        }
        OnConfigureFonts(atlas);
      },
      [this](ImGuiStyle& imgui_style, rex::ui::Style& ui_style) {
        OnConfigureStyle(imgui_style, ui_style);
      });
  // presenter is nullptr in detached mode; ImGuiDrawer tolerates that and the
  // gated eager font upload in SetImmediateDrawer is skipped (font uploads
  // lazily on the first Draw instead).
  imgui_drawer_->SetPresenterAndImmediateDrawer(presenter, drawer);
  rex::ui::RegisterBind("bind_debug_overlay", "F3", "Toggle debug overlay", [this] {
    if (debug_overlay_) {
      debug_overlay_.reset();
    } else {
      debug_overlay_ =
          std::make_unique<ui::DebugOverlayDialog>(imgui_drawer_.get(), frame_stats_provider_);
    }
  });
  rex::ui::RegisterBind("bind_console", "Backtick", "Toggle console overlay", [this] {
    if (console_overlay_) {
      console_overlay_.reset();
    } else {
      console_overlay_ = std::make_unique<ui::ConsoleDialog>(imgui_drawer_.get(), log_sink_);
    }
  });
  rex::ui::RegisterBind("bind_settings", "F4", "Toggle settings overlay", [this] {
    if (settings_overlay_) {
      settings_overlay_.reset();
    } else {
      settings_overlay_ = std::make_unique<ui::SettingsDialog>(imgui_drawer_.get(), config_path_);
    }
  });
  rex::ui::RegisterBind("bind_achievements", "F7", "Toggle achievements overlay", [this] {
    if (achievements_overlay_) {
      achievements_overlay_.reset();
    } else {
      achievements_overlay_ = CreateAchievementsOverlay();
    }
  });

  SetupGuide();
  OnCreateDialogs(imgui_drawer_.get());
}

void ReXApp::LaunchModule() {
  app_context().CallInUIThreadDeferred([this]() {
    // Register the achievement notification callback now that the runtime and
    // KernelState are guaranteed to exist. Done here (not OnCreateDialogs)
    // because KernelState is null during SetupPresentation.
    if (!achievement_notification_) {
      achievement_notification_ =
          std::shared_ptr<ui::AchievementNotificationDialog>(CreateAchievementNotificationDialog());
    }
    if (achievement_notification_ && achievement_notification_listener_ == 0 && runtime_ &&
        runtime_->kernel_state()) {
      std::weak_ptr<ui::AchievementNotificationDialog> notification = achievement_notification_;
      achievement_notification_listener_ = achievements().RegisterNotificationCallback(
          [notification](const rex::system::AchievementEvent& event) {
            if (auto dialog = notification.lock()) {
              dialog->Push(event);
            }
          });
    }

    OnPreLaunchModule();

    auto main_thread = runtime_->PrepareModuleLaunch();
    if (!main_thread) {
      REXLOG_ERROR("Failed to launch module");
      app_context().QuitFromUIThread();
      return;
    }

    if (window_) {
      ApplyTitleIdentity(*window_, *runtime_->kernel_state());
    }

    auto* graphics_system = runtime_->graphics_system();
    if (graphics_system && !runtime_->cache_root().empty()) {
      uint32_t title_id = runtime_->kernel_state()->title_id();
      if (title_id != 0) {
        REXLOG_INFO("Initializing shader storage for title {:08X}...", title_id);
        graphics_system->InitializeShaderStorage(runtime_->cache_root(), title_id, true);
      }
    }

    OnPostLaunchModule(main_thread.get());
    StartGuidePoller();
    main_thread->Resume();

    module_thread_ = std::thread([this, main_thread = std::move(main_thread)]() mutable {
      main_thread->Wait(0, 0, 0, nullptr);
      OnGuestThreadExit(main_thread.get());
      REXLOG_INFO("Execution complete");
      if (!shutting_down_.load(std::memory_order_acquire)) {
        app_context().CallInUIThread([this]() { app_context().QuitFromUIThread(); });
      }
    });
  });
}

std::function<void(PathConfig)> ReXApp::MakeResumeCallback() {
  return [this](PathConfig paths) {
    if (shutting_down_.load(std::memory_order_acquire))
      return;
    if (!ConstructRuntime(std::move(paths))) {
      app_context().QuitFromUIThread();
      return;
    }
    LaunchModule();
  };
}

void ReXApp::OnKeyDown(ui::KeyEvent& e) {
  rex::ui::ProcessKeyEvent(e);
}

void ReXApp::OnClosing(ui::UIEvent& e) {
  (void)e;
  REXLOG_INFO("Window closing, shutting down...");
  shutting_down_.store(true, std::memory_order_release);
  if (runtime_ && runtime_->kernel_state()) {
    runtime_->kernel_state()->TerminateTitle();
  }
  // Hard-exit rather than run subsystem teardown, which can deadlock on a host
  // lock still held by a straggler TerminateTitle left running. Flush (not
  // ShutdownLogging, which frees loggers a straggler may still use); the OS
  // reclaims the rest.
  REXLOG_INFO("Title terminated; hard-exiting process.");
  rex::FlushLogging();
  std::_Exit(0);
}

bool ReXApp::OnCloseRequested(ui::UIEvent& e) {
  (void)e;
  return OnWindowCloseRequested();
}

void ReXApp::OnResize(ui::UISetupEvent& e) {
  (void)e;
  if (!window_) {
    return;
  }
  OnWindowPixelSizeChanged(window_->GetActualPhysicalWidth(), window_->GetActualPhysicalHeight());
  OnWindowResized(window_->GetActualLogicalWidth(), window_->GetActualLogicalHeight());
}

void ReXApp::OnDpiChanged(ui::UISetupEvent& e) {
  (void)e;
  if (!window_) {
    return;
  }
  OnDpiScaleChanged(float(window_->GetDpi()) / float(window_->GetMediumDpi()));
}

void ReXApp::OnGotFocus(ui::UISetupEvent& e) {
  (void)e;
  OnWindowFocusChanged(true);
}

void ReXApp::OnLostFocus(ui::UISetupEvent& e) {
  (void)e;
  OnWindowFocusChanged(false);
}

void ReXApp::OnMinimized(ui::UIEvent& e) {
  (void)e;
  rex::audio::SetAppConstrained(true);
  if (REXCVAR_GET(audio_mute_minimized)) {
    REXLOG_INFO("Window minimized: the game's audio is silenced until it is restored");
  }
  OnWindowMinimized();
}

void ReXApp::OnRestored(ui::UIEvent& e) {
  (void)e;
  if (rex::audio::AppConstrained() && REXCVAR_GET(audio_mute_minimized)) {
    REXLOG_INFO("Window restored: the game's audio plays again");
  }
  rex::audio::SetAppConstrained(false);
  OnWindowRestored();
}

void ReXApp::OnDestroy() {
  // Notify subclass before cleanup
  OnShutdown();

  StopGuide();

  // Unregister overlay keybinds before destroying dialogs
  rex::ui::UnregisterBind("bind_debug_overlay");
  rex::ui::UnregisterBind("bind_console");
  rex::ui::UnregisterBind("bind_settings");
  rex::ui::UnregisterBind("bind_achievements");

  // ImGui cleanup (reverse of setup)
  if (achievement_notification_listener_ != 0) {
    if (runtime_ && runtime_->kernel_state()) {
      achievements().UnregisterCallback(achievement_notification_listener_);
    }
    achievement_notification_listener_ = 0;
  }
  achievement_notification_.reset();
  achievements_overlay_.reset();
  settings_overlay_.reset();
  console_overlay_.reset();
  debug_overlay_.reset();
  if (imgui_drawer_) {
    imgui_drawer_->SetPresenterAndImmediateDrawer(nullptr, nullptr);
    imgui_drawer_.reset();
  }
  // immediate_drawer_ was already unlinked from imgui_drawer_ above. Detach it
  // from its presenter so SDK mode runs OnLeavePresenter() before disposal; in
  // detached mode the drawer never had a presenter, so SetPresenter(nullptr) is
  // a no-op.
  if (immediate_drawer_) {
    immediate_drawer_->SetPresenter(nullptr);
    immediate_drawer_.reset();
  }
  if (runtime_) {
    runtime_->set_display_window(nullptr);
    runtime_->set_imgui_drawer(nullptr);
  }
  // Window/runtime cleanup
  if (window_) {
    window_->SetPresenter(nullptr);
  }
  if (module_thread_.joinable()) {
    module_thread_.join();
  }
  if (window_) {
    window_->RemoveInputListener(this);
    window_->RemoveListener(this);
  }
  window_.reset();
  runtime_.reset();
  // Last: the guest runtime's audio, input and GPU services are gone.
  gaming_runtime_.reset();
  if (restart_on_exit_) {
    // The guide changed the title update choice; the new process picks the
    // executable for it.
    StartHandOff(rex::filesystem::GetExecutablePath(), /*hand_off=*/false);
  }
}

void ReXApp::SetGuestFrameStats(ui::DebugOverlayDialog::FrameStatsProvider provider) {
  frame_stats_provider_ = provider;
  if (debug_overlay_) {
    debug_overlay_->SetStatsProvider(provider);
  }
}

// --- Xbox guide (RG-GDK-041) ---

void ReXApp::SetupGuide() {
  if (!REXCVAR_GET(xbox_guide) || guide_loader_.joinable()) {
    return;
  }
  rex::ui::RegisterBind("bind_xbox_guide", "Home", "Open or close the Xbox guide",
                        [this] { ToggleGuide(); });
  // Reading the system update decompresses XAM; keep it off the UI thread.
  guide_loader_ = std::thread([this] {
    std::string errors;
    // The guide the title build embedded comes first, unless a system update
    // was named explicitly.
    if (const auto bundle = ui::guide::EmbeddedGuide();
        !bundle.empty() && REXCVAR_GET(xbox_guide_system_update).empty()) {
      std::string error;
      std::shared_ptr<const ui::guide::GuideAssets> assets =
          ui::guide::GuideAssets::LoadBundle(bundle, &error);
      if (assets) {
        REXLOG_INFO("Xbox guide: using the guide built into the title ({} KiB)",
                    bundle.size() / 1024);
        std::lock_guard<std::mutex> lock(guide_mutex_);
        guide_assets_ = std::move(assets);
        return;
      }
      errors += fmt::format("built-in guide: {}. ", error);
    }
    for (const std::filesystem::path& location : ui::guide::SystemUpdateLocations()) {
      std::error_code ec;
      if (!std::filesystem::exists(location, ec)) {
        continue;
      }
      std::string error;
      std::shared_ptr<const ui::guide::GuideAssets> assets =
          ui::guide::GuideAssets::Load(location, &error);
      if (assets) {
        REXLOG_INFO("Xbox guide: using the system update at {}", location.string());
        std::lock_guard<std::mutex> lock(guide_mutex_);
        guide_assets_ = std::move(assets);
        return;
      }
      errors += fmt::format("{}: {}. ", location.string(), error);
    }
    if (errors.empty()) {
      errors =
          "This build has no guide built in: build the title with REXGLUE_SYSTEM_UPDATE "
          "set to a $SystemUpdate folder (dashboard 2.0.17559).";
    }
    REXLOG_INFO("Xbox guide unavailable: {}", errors);
    std::lock_guard<std::mutex> lock(guide_mutex_);
    guide_error_ = std::move(errors);
  });
}

void ReXApp::StartGuidePoller() {
  auto* input =
      runtime_ ? static_cast<rex::input::InputSystem*>(runtime_->input_system()) : nullptr;
  if (!REXCVAR_GET(xbox_guide) || !input || guide_poller_.joinable()) {
    return;
  }
  guide_poller_ = std::thread([this, input] {
    std::array<ui::guide::GuideChord, 4> chords;
    while (!guide_stop_.load(std::memory_order_acquire)) {
      const auto connected = input->GetConnectedUsers();
      for (uint32_t user = 0; user < chords.size(); ++user) {
        uint16_t buttons = 0;
        // Polling a missing XInput pad is slow; only read connected users.
        if (connected.test(user) || (user == 0 && connected.none())) {
          rex::input::X_INPUT_STATE state = {};
          if (input->GetStateForUI(user, &state) == X_ERROR_SUCCESS) {
            buttons = state.gamepad.buttons;
          }
        }
        if (chords[user].Update(buttons)) {
          app_context().CallInUIThread([this] { ToggleGuide(); });
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
  });
}

void ReXApp::StopGuide() {
  guide_stop_.store(true, std::memory_order_release);
  if (guide_poller_.joinable()) {
    guide_poller_.join();
  }
  if (guide_loader_.joinable()) {
    guide_loader_.join();
  }
  if (guide_) {
    delete guide_;  // detaches from the ImGui drawer and releases guest input
    guide_ = nullptr;
  }
  guide_media_.reset();
  rex::ui::UnregisterBind("bind_xbox_guide");
}

void ReXApp::ToggleGuide() {
  if (!REXCVAR_GET(xbox_guide) || !imgui_drawer_ || shutting_down_.load() || !runtime_ ||
      !runtime_->kernel_state()) {
    return;
  }
  if (guide_) {
    guide_->Dismiss();
    return;
  }
  std::shared_ptr<const ui::guide::GuideAssets> assets;
  std::string error;
  {
    std::lock_guard<std::mutex> lock(guide_mutex_);
    assets = guide_assets_;
    error = guide_error_;
  }
  if (!assets) {
    // Still loading, or no system update: say which, once.
    if (!error.empty() && !guide_unavailable_shown_) {
      guide_unavailable_shown_ = true;
      ui::ImGuiDialog::ShowMessageBox(imgui_drawer_.get(), "Xbox Guide", error);
    }
    return;
  }
  {
    std::lock_guard<std::mutex> lock(guide_mutex_);
    if (!guide_media_) {
      guide_media_ = std::make_unique<ui::guide::GuideMedia>(immediate_drawer_.get(), assets);
    }
  }
  auto* input = static_cast<rex::input::InputSystem*>(runtime_->input_system());
  uint16_t held = 0;
  if (input) {
    rex::input::X_INPUT_STATE state = {};
    if (input->GetStateForUI(input->GetLastUsedUser(), &state) == X_ERROR_SUCCESS) {
      held = state.gamepad.buttons;
    }
  }
  ui::guide::GuideHost host;
  host.input = input;
  host.kernel_state = runtime_->kernel_state();
  host.achievements = &achievements();
  host.runtime = runtime_.get();
  host.immediate_drawer = immediate_drawer_.get();
  host.title_name = TitleName(*runtime_->kernel_state());
  host.patches = ppc_info_.switchable_patches;
  host.cheats = ppc_info_.title_cheats;
  host.dlc = ppc_info_.title_dlc;
  host.title_update = ppc_info_.title_update;
  host.title_updates = ppc_info_.title_updates;
  host.local_dir = local_dir_;
  host.restart_title = [this] { restart_on_exit_ = true; };
  host.display_scale = DisplayScale(DisplayHeight(window_.get()));
  host.save_settings = [this] { rex::cvar::SaveConfig(config_path_); };
  host.on_closed = [this](bool exit_title) {
    guide_ = nullptr;
    if (exit_title) {
      REXLOG_INFO("Xbox guide: exiting the title");
      app_context().CallInUIThreadDeferred([this] {
        if (window_) {
          window_->RequestClose();
        }
      });
    }
  };
  guide_ = new ui::guide::XboxGuide(imgui_drawer_.get(), std::move(assets), guide_media_.get(),
                                    {guide_font_regular_, guide_font_bold_}, std::move(host), held);
}

}  // namespace rex
