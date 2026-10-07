// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <thread>
#include <imgui.h>
#include <imgui_internal.h>
#include <rex/cvar.h>
#include <rex/hash.h>
#include <rex/ui/overlay/game_source.h>
#include <rex/ui/window_win.h>
#include <rex/ui/windowed_app_context_win.h>

namespace {
struct SourceHarness {
  SourceHarness() : context(GetModuleHandleW(nullptr), SW_HIDE) {
    rex::cvar::testing::ResetAllForTesting();
    REQUIRE(context.Initialize());
    window = rex::ui::Window::Create(context, "Source UI test", 800, 600);
    REQUIRE(window->Open());
    drawer = std::make_unique<rex::ui::ImGuiDrawer>(window.get(), 64);
    auto& io = drawer->GetIO();
    ImGui::SetCurrentContext(io.Ctx);
    io.DisplaySize = ImVec2(800, 600);
    io.DeltaTime = 1.0f / 60;
    REQUIRE(io.Fonts->Build());
    root = std::filesystem::temp_directory_path() / "rex-source-ui-test";
    REQUIRE_FALSE(std::filesystem::exists(root));
    std::filesystem::create_directory(root);
    std::array<uint8_t, 128> xex{};
    std::memcpy(xex.data(), "XEX2", 4);
    xex[23] = 1;
    xex[25] = 4;
    xex[27] = 6;
    xex[31] = 32;
    xex[47] = 7;
    {
      std::ofstream output(root / "default.xex", std::ios::binary);
      output.write(reinterpret_cast<char*>(xex.data()), xex.size());
    }
    expected = {7, rex::hash_file(root / "default.xex")};
  }
  ~SourceHarness() {
    delete dialog;
    drawer.reset();
    ImGui::SetCurrentContext(nullptr);
    std::error_code ec;
    std::filesystem::remove(root / "default.xex", ec);
    std::filesystem::remove(root / "settings.toml", ec);
    std::filesystem::remove(root, ec);
    rex::cvar::testing::ResetAllForTesting();
  }
  void Show(rex::ui::LaunchPadSource pad = {}) {
    dialog = new rex::ui::GameSourceDialog(
        drawer.get(), expected, root / "settings.toml",
        [this](std::filesystem::path source) {
          dialog = nullptr;
          ++completed;
          selected = std::move(source);
        },
        root, "", "default.xex", {}, std::move(pad));
    Frame();
    Frame();
  }
  void Frame(rex::ui::ImGuiDialog* extra = nullptr) {
    ImGui::SetCurrentContext(drawer->GetIO().Ctx);
    ImGui::NewFrame();
    if (dialog)
      dialog->Draw();
    if (extra)
      extra->Draw();
    ImGui::Render();
  }
  void Press(const char* label) {
    auto* wizard = ImGui::FindWindowByName("Choose game files");
    REQUIRE(wizard);
    ImGui::ActivateItemByID(wizard->GetID(label));
    Frame();
  }
  rex::ui::Win32WindowedAppContext context;
  std::unique_ptr<rex::ui::Window> window;
  std::unique_ptr<rex::ui::ImGuiDrawer> drawer;
  rex::ui::GameSourceDialog* dialog = nullptr;
  rex::system::GameSourceIdentity expected;
  std::filesystem::path root, selected;
  int completed = 0;
};
}  // namespace

TEST_CASE("First-run source UI validates before saving and completing", "[ui][game_source]") {
  SourceHarness h;
  h.Show();
  h.Press("Use this source");
  CHECK(h.completed == 0);
  h.Press("Check source");
  for (int i = 0; i < 500 && !h.completed; ++i) {
    h.Frame();
    h.Press("Use this source");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  REQUIRE(h.completed == 1);
  CHECK(h.selected == h.root);
  CHECK(std::filesystem::exists(h.root / "settings.toml"));
  CHECK(rex::cvar::GetFlagByName("game_source") == rex::string::to_utf8(h.root.u16string()));
}

TEST_CASE("First-run source UI rejects a different title and Leave Game cancels",
          "[ui][game_source]") {
  SourceHarness h;
  h.expected.title_id = 9;
  h.Show();
  h.Press("Check source");
  for (int i = 0; i < 50; ++i) {
    h.Frame();
    h.Press("Use this source");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  CHECK(h.completed == 0);
  CHECK_FALSE(std::filesystem::exists(h.root / "settings.toml"));
  h.Press("Leave Game");
  CHECK(h.completed == 1);
  CHECK(h.selected.empty());
}

TEST_CASE("First-run source shutdown does not resume guest launch", "[ui][game_source]") {
  SourceHarness h;
  h.Show();
  delete h.dialog;
  h.dialog = nullptr;
  CHECK(h.completed == 0);
}

TEST_CASE("Media recovery UI completes Retry or Leave once, but shutdown never retries",
          "[ui][game_source][media_recovery]") {
  SourceHarness h;
  int completed = 0;
  bool retry = false;
  rex::ui::GameMediaRecoveryDialog* dialog = nullptr;
  dialog = new rex::ui::GameMediaRecoveryDialog(h.drawer.get(), false, "", [&](bool chosen) {
    dialog = nullptr;
    ++completed;
    retry = chosen;
  });
  h.Frame(dialog);
  h.Frame(dialog);
  auto* window = ImGui::FindWindowByName("Game source unavailable");
  REQUIRE(window);
  SECTION("Retry") {
    ImGui::ActivateItemByID(window->GetID("Retry"));
    h.Frame(dialog);
    CHECK(completed == 1);
    CHECK(retry);
  }
  SECTION("Leave") {
    ImGui::ActivateItemByID(window->GetID("Leave Game"));
    h.Frame(dialog);
    CHECK(completed == 1);
    CHECK_FALSE(retry);
  }
  SECTION("Shutdown") {
    delete dialog;
    dialog = nullptr;
    CHECK(completed == 0);
  }
  CHECK(dialog == nullptr);
}

TEST_CASE("Source and recovery controller navigation releases disconnected and disposed pads",
          "[ui][game_source][media_recovery]") {
  SourceHarness h;
  std::optional<rex::ui::LaunchPadState> pad = rex::ui::LaunchPadState{};
  rex::ui::GameMediaRecoveryDialog* recovery = nullptr;
  SECTION("Source selection") {
    h.Show([&pad] { return pad; });
  }
  SECTION("Media recovery") {
    recovery = new rex::ui::GameMediaRecoveryDialog(
        h.drawer.get(), false, "", [](bool) {}, [&pad] { return pad; });
  }
  auto frame = [&] {
    h.Frame(recovery);
    h.Frame(recovery);
  };
  frame();
  pad->y = 1;
  frame();
  CHECK(ImGui::IsKeyDown(ImGuiKey_GamepadDpadUp));
  CHECK(h.drawer->GetIO().BackendFlags & ImGuiBackendFlags_HasGamepad);
  pad.reset();
  frame();
  CHECK_FALSE(ImGui::IsKeyDown(ImGuiKey_GamepadDpadUp));
  CHECK_FALSE(h.drawer->GetIO().BackendFlags & ImGuiBackendFlags_HasGamepad);
  pad = rex::ui::LaunchPadState{};
  pad->x = -1;
  frame();
  CHECK(ImGui::IsKeyDown(ImGuiKey_GamepadDpadLeft));
  delete recovery;
  recovery = nullptr;
  delete h.dialog;
  h.dialog = nullptr;
  frame();
  CHECK_FALSE(ImGui::IsKeyDown(ImGuiKey_GamepadDpadLeft));
  CHECK(h.completed == 0);
}
