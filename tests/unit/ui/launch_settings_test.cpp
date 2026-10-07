// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <imgui.h>
#include <imgui_internal.h>
#include <fstream>
#include <rex/cvar.h>
#include <rex/ui/overlay/launch_settings.h>
#include <rex/ui/window_win.h>
#include <rex/ui/windowed_app_context_win.h>

namespace {
struct Harness {
  Harness() : context(GetModuleHandleW(nullptr), SW_HIDE) {
    REQUIRE(context.Initialize());
    window = rex::ui::Window::Create(context, "Launcher UI test", 800, 600);
    REQUIRE(window);
    REQUIRE(window->Open());
    drawer = std::make_unique<rex::ui::ImGuiDrawer>(window.get(), 64);
    auto& io = drawer->GetIO();
    // The test executable links ImGui for other suites, while the installed
    // UI implementation lives in the runtime DLL. Share the drawer's context.
    ImGui::SetCurrentContext(io.Ctx);
    io.DisplaySize = ImVec2(800, 600);
    io.DeltaTime = 1.0f / 60.0f;
    REQUIRE(io.Fonts->Build());
  }
  ~Harness() {
    delete dialog;
    drawer.reset();
    ImGui::SetCurrentContext(nullptr);
  }
  void Show(const std::filesystem::path& config, rex::ui::LaunchPadSource pad_source = {}) {
    dialog = new rex::ui::LaunchSettingsDialog(
        drawer.get(), "Synthetic game", config,
        [this](bool play) {
          dialog = nullptr;
          ++completed;
          accepted = play;
        },
        std::move(pad_source));
  }
  void Frame() {
    ImGui::SetCurrentContext(drawer->GetIO().Ctx);
    ImGui::NewFrame();
    if (dialog)
      dialog->Draw();
    ImGui::Render();
  }
  void Press(const char* label) {
    auto* menu = ImGui::FindWindowByName("Game settings");
    REQUIRE(menu);
    ImGui::ActivateItemByID(menu->GetID(label));  // Actual ImGui navigation activation.
    Frame();
  }
  rex::ui::Win32WindowedAppContext context;
  std::unique_ptr<rex::ui::Window> window;
  std::unique_ptr<rex::ui::ImGuiDrawer> drawer;
  rex::ui::LaunchSettingsDialog* dialog = nullptr;
  int completed = 0;
  bool accepted = false;
};
}  // namespace

TEST_CASE("Launcher Play and Exit complete once with the correct action", "[ui][launch_settings]") {
  Harness h;
  const auto config = std::filesystem::temp_directory_path() / "rex-launch-settings-test.toml";
  std::filesystem::remove(config);
  h.Show(config);
  h.Frame();
  h.Frame();
  REQUIRE(ImGui::GetDrawData()->TotalVtxCount > 0);
  SECTION("Exit does not save or launch") {
    h.Press("Exit");
    CHECK(h.completed == 1);
    CHECK_FALSE(h.accepted);
    CHECK_FALSE(std::filesystem::exists(config));
  }
  SECTION("Play without remember starts only this session") {
    h.Press("Remember settings");
    h.Press("Play");
    CHECK(h.completed == 1);
    CHECK(h.accepted);
    CHECK_FALSE(std::filesystem::exists(config));
  }
  CHECK(h.dialog == nullptr);
}

TEST_CASE("Destroying a launcher during shutdown never invokes Play", "[ui][launch_settings]") {
  Harness h;
  h.Show({});
  h.Frame();
  delete h.dialog;
  h.dialog = nullptr;
  CHECK(h.completed == 0);
}

TEST_CASE("Launcher shoulders switch tabs once and controller A activates Play",
          "[ui][launch_settings]") {
  Harness h;
  rex::ui::LaunchPadState pad;
  h.Show({}, [&pad] { return std::optional(pad); });
  h.Frame();
  h.Frame();
  pad.next_tab = true;
  for (int frame = 0; frame < 5; ++frame)
    h.Frame();
  auto* menu = ImGui::FindWindowByName("Game settings");
  REQUIRE(menu);
  auto* tabs = ImGui::GetCurrentContext()->TabBars.GetByKey(menu->GetID("Settings"));
  REQUIRE(tabs);
  CHECK(tabs->SelectedTabId == ImHashStr("Audio", 0, tabs->ID));
  pad.next_tab = false;
  h.Frame();
  pad.next_tab = true;
  for (int frame = 0; frame < 3; ++frame)
    h.Frame();
  CHECK(tabs->SelectedTabId == ImHashStr("Language", 0, tabs->ID));
  pad.next_tab = false;
  h.Press("Remember settings");
  ImGui::FocusWindow(menu);
  ImGui::SetNavID(menu->GetID("Play"), ImGuiNavLayer_Main, menu->NavRootFocusScopeId, ImRect());
  ImGui::SetNavCursorVisible(true);
  ImGui::GetCurrentContext()->NavInitRequest = false;
  ImGui::GetCurrentContext()->NavInitResult = {};
  pad.activate = true;
  h.Frame();
  h.Frame();
  CAPTURE(ImGui::GetCurrentContext()->NavId, menu->GetID("Play"),
          ImGui::GetCurrentContext()->NavActivateId, ImGui::IsKeyDown(ImGuiKey_GamepadFaceDown));
  CHECK(h.completed == 1);
  CHECK(h.accepted);
  CHECK(h.dialog == nullptr);
}

TEST_CASE("Launcher saves settings and allows recovery from a save failure",
          "[ui][launch_settings]") {
  rex::cvar::testing::ResetAllForTesting();
  struct Reset {
    ~Reset() { rex::cvar::testing::ResetAllForTesting(); }
  } reset;
  REQUIRE(rex::cvar::SetFlagByName("user_language", "4"));
  Harness h;
  SECTION("Remember writes the chosen language") {
    const auto config =
        std::filesystem::temp_directory_path() / "rex-launch-settings-save-test.toml";
    std::filesystem::remove(config);
    h.Show(config);
    h.Frame();
    h.Frame();
    h.Press("Play");
    CHECK(h.completed == 1);
    CHECK(h.accepted);
    REQUIRE(std::filesystem::is_regular_file(config));
    std::ifstream file(config);
    const std::string content(std::istreambuf_iterator<char>(file), {});
    CHECK(content.find("user_language = 4") != std::string::npos);
    file.close();
    std::filesystem::remove(config);
  }
  SECTION("Failure keeps the menu open; session-only Play recovers") {
    h.Show(std::filesystem::temp_directory_path());  // A directory cannot be a config file.
    h.Frame();
    h.Frame();
    h.Press("Play");
    CHECK(h.completed == 0);
    REQUIRE(h.dialog);
    h.Press("Remember settings");
    h.Press("Play");
    CHECK(h.completed == 1);
    CHECK(h.accepted);
  }
}

TEST_CASE("Launcher controller navigation releases keys on disconnect and shutdown",
          "[ui][launch_settings]") {
  Harness h;
  std::optional<rex::ui::LaunchPadState> pad = rex::ui::LaunchPadState{};
  h.Show({}, [&pad] { return pad; });
  h.Frame();
  h.Frame();
  pad->x = 0.1f;
  h.Frame();
  h.Frame();
  CHECK_FALSE(ImGui::IsKeyDown(ImGuiKey_GamepadDpadRight));
  pad->x = 1.0f;
  h.Frame();
  h.Frame();
  CHECK(ImGui::IsKeyDown(ImGuiKey_GamepadDpadRight));
  CHECK(h.drawer->GetIO().BackendFlags & ImGuiBackendFlags_HasGamepad);
  pad.reset();
  h.Frame();
  h.Frame();
  CHECK_FALSE(ImGui::IsKeyDown(ImGuiKey_GamepadDpadRight));
  CHECK_FALSE(h.drawer->GetIO().BackendFlags & ImGuiBackendFlags_HasGamepad);
  pad = rex::ui::LaunchPadState{};
  pad->x = -1.0f;
  h.Frame();
  h.Frame();
  REQUIRE(ImGui::IsKeyDown(ImGuiKey_GamepadDpadLeft));
  delete h.dialog;
  h.dialog = nullptr;
  h.Frame();
  CHECK_FALSE(ImGui::IsKeyDown(ImGuiKey_GamepadDpadLeft));
  CHECK(h.completed == 0);
}
